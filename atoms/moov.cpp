#include "moov.h"
#include "../interfaces/parserinterface.h"
#include "../interfaces/callbackinterface.h"
#include <memory>
#include <iostream>

using namespace std;

MOOV::MOOV():Atom(MOOV_NAME, MOOV_DIG_NAME)
{
    m_mvhd = make_unique<MVHD>();
    m_videoTrak= make_unique<TRAK>();
    m_audioTrak= make_unique<TRAK>();
    m_videoTrak->setCallback(this);
    m_audioTrak->setCallback(this);
    m_parseMap[MVHD_NAME]=dynamic_cast<ParserInterface*>(m_mvhd.get());
    m_parseMap[VIDE]=dynamic_cast<ParserInterface*>(m_videoTrak.get());
    m_parseMap[SOUN]=dynamic_cast<ParserInterface*>(m_audioTrak.get());
}

MOOV::~MOOV()
{

}

void MOOV::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{
    if(direction == DIRECT_RESIZE::INCREASED){
        this->m_size +=size;
    }else{
        this->m_size -=size;
    }
}

void MOOV::parse(StreamReader &stream, uint32_t& startPos)
{
    if(stream.getTitleAtom()==MOOV_NAME){
        printAtomName(LV1);
        m_offset = startPos;
        m_size = stream.readSizeAtom();
        uint32_t foundPos = startPos+OFFSET_TITLE;
        uint32_t atomSize{0}; //??
        string titleName;
        while (foundPos<(m_size+startPos)) {
            stream.setPos(foundPos);
            atomSize = stream.readSizeAtom(); //??
            titleName =stream.getTitleAtom();
            if(titleName==TRAK_NAME){
                stream.setPos(foundPos+156);
                titleName = stream.getDataInAtom();
                stream.setPos(foundPos);
                std::cout<<"=======\n"<<titleName.c_str()<<"\n======="<<std::endl;
            }
            auto search = m_parseMap.find(titleName);
            if(search != m_parseMap.end()){
                m_parseMap.at(titleName)->parse(stream, foundPos);                
            }else{
                foundPos += atomSize;
            }
        }
    }else{
        exit(-2);
    }
    startPos += m_size;
}

std::pair<uint32_t, uint32_t> MOOV::prepareData(uint32_t begTime, uint32_t endTime)
{
    m_singletonSettings.setPeriodTime(begTime,endTime);
    m_mvhd->setNewDuration(m_singletonSettings.getNewDuration());
    m_videoTrak->prepareData();
    m_audioTrak->prepareData();
    return std::pair<uint32_t, uint32_t>(m_singletonSettings.getBeginOffsetFile(),m_singletonSettings.getSizeCut());
}

void MOOV::writeAudioAndVideo(StreamWriter &outStream)
{
    //m_size -=m_videoTrak->size();
    m_mvhd->setNextTrakID(2);
    outStream.writeLitToBigEndian(m_size);
    outStream.writeAtomName(MOOV_NAME);
    m_mvhd->writeAtom(outStream);
    m_videoTrak->writeAtom(outStream);
    m_audioTrak->writeAtom(outStream);
}




