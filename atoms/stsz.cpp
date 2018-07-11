#include "stsz.h"

using namespace std;
STSZ::STSZ(TRAK_TYPE type):
    Atom(STSZ_NAME, STSZ_DIG_NAME),
    m_trakType(type)
{

}

STSZ::~STSZ()
{

}

void STSZ::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV6);
    m_size = stream.readSizeAtom();
    uint32_t pos = startPos+OFFSET_TITLE;
    stream.setPos(pos);
    m_verFlag = stream.readUInt32();
    m_sampleSize = stream.readBigEndianUInt32();
    m_amountChunk = stream.readBigEndianUInt32();
    m_chunkSize.resize(m_amountChunk,0);
    for(auto i=0;i<m_amountChunk;i++){
        m_chunkSize[i]=stream.readBigEndianUInt32();
    }
    startPos +=m_size;
}

void STSZ::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(STSZ_NAME);
    stream.writeUInt32(m_verFlag);
    stream.writeLitToBigEndian(m_sampleSize);
    stream.writeLitToBigEndian(m_chunkSize.size());
    for(int i=0;i<m_chunkSize.size();i++){
        stream.writeLitToBigEndian(m_chunkSize[i]);
    }
}

void STSZ::prepareData()
{
    if(m_trakType == TRAK_TYPE::VIDEO){
        uint32_t begTime = m_singletonSettings.getIDBeginChunkVideo();
        uint32_t endTime = m_singletonSettings.getEndTime();
        uint32_t delta = m_singletonSettings.getDelta();

        uint32_t endPos = (endTime*delta)+delta;
        uint32_t countResize = m_chunkSize.size();
        if(endPos != (m_chunkSize.size()-1)){
            m_chunkSize.erase(m_chunkSize.begin()+endPos,m_chunkSize.end());
        }
        if(begTime != 0){
            m_chunkSize.erase(m_chunkSize.begin(),m_chunkSize.begin()+begTime);
        }
        m_singletonSettings.setLastChunkVideoSize(m_chunkSize[m_chunkSize.size()-1]);
        uint32_t resizeAmount =(countResize-m_chunkSize.size())*BYTE32;
        m_size -=resizeAmount;
        resizeAtom(resizeAmount,DIRECT_RESIZE::DECREASED);

    }else{

        pair<uint32_t,uint32_t> idStartData = m_singletonSettings.getStartIdChunkAudio();
        pair<uint32_t,uint32_t> idEndData = m_singletonSettings.getEndIdChunkAudio();
        idStartData.first =idStartData.first*4-3;
        idEndData.first =idEndData.first*4-3;
        uint32_t m_offsetStartSize{0};
        uint32_t m_offsetEndSize{0};
        if(idStartData.second != 0){
            for(int i = idStartData.first; i<idStartData.first+idStartData.second;i++){
                m_offsetStartSize += m_chunkSize[i];
            }
        }
        m_singletonSettings.setFirstChunkAudioSize(m_offsetStartSize);
        if(idEndData.second != 0){
            for(int i = idEndData.first; i<idEndData.first+idEndData.second;i++){
                m_offsetEndSize += m_chunkSize[i];
            }
        }
        m_singletonSettings.setLastChunkAudioSize(m_offsetEndSize);
        //uint32_t endPos = idEndData.first+idEndData.second-2;
        //uint32_t startPos = idStartData.first-1;
        uint32_t countResize = m_chunkSize.size();// - endPos + startPos; ///????? endPos +-1
        if(idEndData.first != (m_chunkSize.size()-1)){
            m_chunkSize.erase(m_chunkSize.begin()+idEndData.first+idEndData.second-2,m_chunkSize.end());
        }
        if(idStartData.first != 0){
            m_chunkSize.erase(m_chunkSize.begin(),m_chunkSize.begin()+idStartData.first-1); ///????? startPos +-1
        }
        m_singletonSettings.setAmountChunkAudio(m_chunkSize.size());
        m_singletonSettings.setArrayChunkOffsetAudio(m_chunkSize);
        uint32_t resizeAmount = (countResize-m_chunkSize.size())*BYTE32;
        m_size -=resizeAmount;
        resizeAtom(resizeAmount,DIRECT_RESIZE::DECREASED);
    }
}

uint32_t STSZ::getAmountChunks() const
{
    return m_chunkSize.size();
}

uint32_t STSZ::getEndChunkSize() const
{
    return m_chunkSize[m_chunkSize.size()-1];
}

void STSZ::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{
    callback()->resizeAtom(size,direction);
}
