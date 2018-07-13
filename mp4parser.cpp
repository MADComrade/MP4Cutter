//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ----------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#include "mp4parser.h"
#include <iostream>
#include "SingletonSettings.h"

//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------ОПРЕДЕЛЕНИЕ МЕТОДОВ----------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

//**************************************************************************************//
//--------------------------------------------------------------------------------------//
//---------------------------КЛАСС НАСТРОЙКИ ПАРСИНГА MP4-------------------------------//
//--------------------------------------------------------------------------------------//
//**************************************************************************************//
using namespace std;                                                                    // использование пространства имен STD

//**************************************************************************************//
//------------конструктор---------------------------------------------------------------//
MP4Parser::MP4Parser()
{

}

//**************************************************************************************//
//------------деконструктор-------------------------------------------------------------//
MP4Parser::~MP4Parser()
{

}

//**************************************************************************************//
//------------общий парсинг структуры MP4 по атомам-------------------------------------//
void MP4Parser::parse(StreamReader &stream)
{
    uint32_t startPos{0};                                                               //задана беззнаковая переменная startPos=0(???), 4 байтная
    string titleName = stream.getTitleAtom();                                           //получение типа(названия) атома
    if(titleName.compare(FTYP_NAME)){                                                   //если название атома не совпало с ftyp
        exit(-25);                                                                      //то выход с кодом ошибки
    }
    m_ftyp = make_unique<FTYP>();                                                       //создание умного указателя unique_ptr на атом FTYP ???
    m_ftyp->parse(stream, startPos);                                                    //вызов виртуальной функции парсинга атома ftyp в файле ftyp.срр ???
    uint32_t offset{0};                                                                 //задана беззнаковая переменная offset=0(???), 4 байтная
    do{
        startPos += offset;                                                             //перенос начальной позиции в файле на величину offset
        stream.setPos(startPos);                                                        //установка указателя файла на новую позицию startPos
        offset = stream.readSizeAtom();                                                 //присваивание offset размера сhunk атома
        titleName = stream.getTitleAtom();                                              //присваивание titleName имени атома
    }while(titleName.compare(MOOV_NAME));                                               //все это выполняется пока titleName не будет совпадать с названием атома moov
    m_moov = make_unique<MOOV>();                                                       //создание умного указателя unique_ptr на атом MOOV ???
    m_moov->parse(stream,startPos);                                                     //вызов виртуальной функции парсинга атома moov в файле moov.срр ???
}

//**************************************************************************************//
//------------обработка данных----------------------------------------------------------//
void MP4Parser::prepareData(uint32_t begTime, uint32_t endTime)
{
    m_mdatInfo = m_moov->prepareData(begTime,endTime);                                  //получение данных атома mdat
}

//**************************************************************************************//
//------------запись обработанных данных при парсинге в новый MP4 файл------------------//
void MP4Parser::writeOnlyVideo(StreamReader &inStream, StreamWriter &outStream)
{
    m_ftyp->writeAtom(outStream);                                                       //записать в новый MP4 файл данные атома ftyp
    uint32_t mdatSize = (m_mdatInfo.second - m_mdatInfo.first)+OFFSET_TITLE;            //вычисление размера атома mdat ???
    uint32_t buf = m_mdatInfo.second - m_mdatInfo.first;                                //вычисление размера блока данных атома mdat без учета его блока size и блока name ???
    outStream.writeLitToBigEndian(mdatSize);                                            //написание в новом файле MP4 размера атома mdat не Little, а BigEndian
    outStream.writeAtomName(MDAT_NAME);                                                 //записать в новом файле MP4 имя атома MDAT_NAM

    uint32_t BlockSize = 4096000;
    streamsize blockBytes = (mdatSize - OFFSET_TITLE)/BlockSize;
    streamsize blockEndBytes = (mdatSize - OFFSET_TITLE)%BlockSize;
    streamsize startPos = m_mdatInfo.first;
    streamsize endPos = m_mdatInfo.first+BlockSize;
    vector<uint8_t> dataV (BlockSize,0);                                                //создать вектор dataValue размером BlockSize и заполнить все выделенные ячейки памяти нулями
    for (int i=0;i<blockBytes;i++){
        inStream.getBlock(&( dataV[ 0 ] ),startPos,dataV.size());                       //чтение в исходном файле MP4 по адресу dataV[ 0 ] данных длиной dataV.size(), начиная с позиции исходного MP4 файла startPos ???
        outStream.write(reinterpret_cast< uint8_t * >(&( dataV[ 0 ] )), dataV.size());  //запись в новый файл MP4 данных длиной dataV.size() по адресу dataV[ 0 ] ???
        startPos = endPos;
        endPos +=BlockSize;
    }

    if(blockEndBytes !=0){
        dataV.resize(blockEndBytes,0);
        inStream.getBlock(&( dataV[ 0 ] ),startPos,dataV.size());
        outStream.write(reinterpret_cast< uint8_t * >(&( dataV[ 0 ] )), dataV.size());
    }

    m_moov->writeAudioAndVideo(outStream);
}
