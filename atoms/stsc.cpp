#include "stsc.h"
#include "SingletonSettings.h"

using namespace std;
STSC::STSC(TRAK_TYPE type):
    Atom(STSC_NAME, STSC_DIG_NAME),
    m_trakType(type)
{
	
}

STSC::~STSC()
{

}

void STSC::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV6);
    m_size = stream.readSizeAtom();
    uint32_t pos = startPos+OFFSET_TITLE;
    stream.setPos(pos);
    m_verFlag = stream.readUInt32();
    m_amount = stream.readBigEndianUInt32();
    m_data.resize(m_amount);
    for(int i=0;i<m_amount;i++){
        m_data[i].m_firstChunk=stream.readBigEndianUInt32();
        m_data[i].m_samplesPerChunk=stream.readBigEndianUInt32();
        m_data[i].m_samplesIndex=stream.readBigEndianUInt32();
    }
    startPos +=m_size;
}

void STSC::prepareData()
{
    if(m_trakType == TRAK_TYPE::VIDEO){
    }else{
        pair<uint32_t,uint32_t> idEndData = m_singletonSettings.getEndIdChunkAudio();
        int32_t size = m_data.size();
        if((m_data.size()==1)&&(idEndData.second>0))
        {
            m_amount++;
            StscData oldData = m_data[0];
            oldData.m_firstChunk = (m_singletonSettings.getIDEndChunkAudio()-m_singletonSettings.getIDBeginChunkAudio())+1;
            oldData.m_samplesPerChunk = 2;//idEndData.second;
            oldData.m_samplesIndex = 1;
            m_data.push_back(oldData);
        }
        int32_t resize = size - m_data.size();
        if(resize == 0)
            return;
        uint32_t atomResize = (abs(size)*3*4);
        if(resize<0){
            m_size += atomResize;
            resizeAtom(atomResize,DIRECT_RESIZE::INCREASED);
        }else{
            m_size -=atomResize;
            resizeAtom(atomResize,DIRECT_RESIZE::DECREASED);
        }
    }
}

void STSC::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(STSC_NAME);
    stream.writeUInt32(m_verFlag);
    stream.writeLitToBigEndian(m_amount);
    for(int i=0;i<m_amount;i++){
        stream.writeLitToBigEndian( m_data[i].m_firstChunk);
        stream.writeLitToBigEndian( m_data[i].m_samplesPerChunk);
        stream.writeLitToBigEndian(m_data[i].m_samplesIndex);
    }
}

void STSC::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{
    callback()->resizeAtom(size,direction);
}

