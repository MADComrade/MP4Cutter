#include "stsz.h"
#include "SingletonSettings.h"

using namespace std;
STSZ::STSZ():Atom(STSZ_NAME, STSZ_DIG_NAME)
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
    m_sempleSize = stream.readBigEndianUInt32();
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
    stream.writeLitToBigEndian(m_sempleSize);
    stream.writeLitToBigEndian(m_chunkSize.size());
    for(int i=0;i<m_chunkSize.size();i++){
        stream.writeLitToBigEndian(m_chunkSize[i]);
    }
}

void STSZ::prepareDataForWrite(uint32_t begTime, uint32_t endTime, uint32_t delta, TRAK_TYPE type)
{
    SingletonSettings& sig = SingletonSettings::getInstance();
    //uint32_t amountTime= endTime - begTime;
    if(type == TRAK_TYPE::VIDEO){
        uint32_t endPos = (endTime*delta)+delta; /// TODO: Передать delta
        uint32_t countResize = m_chunkSize.size() - endPos + begTime; ///?????
        if(endPos != (m_chunkSize.size()-1)){
            m_chunkSize.erase(m_chunkSize.begin()+endPos,m_chunkSize.end());
        }
        if(begTime != 0){
            m_chunkSize.erase(m_chunkSize.begin(),m_chunkSize.begin()+begTime);
        }
        sig.setLastChunkVideoSize(m_chunkSize[m_chunkSize.size()-1]);
        uint32_t resizeAmount =countResize*BYTE32;
        m_size -=resizeAmount;
        resizeAtom(resizeAmount,DIRECT_RESIZE::DECREASED);
    }else{

        pair<uint32_t,uint32_t> idStartData = sig.getStartIdChunkAudio();
        pair<uint32_t,uint32_t> idEndData = sig.getEndIdChunkAudio();
        idStartData.first *=4;
        idEndData.first *=4;
        uint32_t m_offsetStartSize{0};
        uint32_t m_offsetEndSize{0};
        if(idStartData.second != 0){
            for(int i = idStartData.first; i<idStartData.first+idStartData.second;i++){
                m_offsetStartSize += m_chunkSize[i];
            }
        }
        sig.setFirstChunkAudioSize(m_offsetStartSize);
        if(idEndData.second != 0){
            for(int i = idEndData.first; i<idEndData.first+idEndData.second;i++){
                m_offsetEndSize += m_chunkSize[i];
            }
        }
        sig.setLastChunkAudioSize(m_offsetEndSize);
        uint32_t endPos = idEndData.first+idEndData.second-2;
        uint32_t startPos = idStartData.first-1;
        uint32_t countResize = m_chunkSize.size();// - endPos + startPos; ///????? endPos +-1
        if(idEndData.first != (m_chunkSize.size()-1)){
            m_chunkSize.erase(m_chunkSize.begin()+idEndData.first+idEndData.second-2,m_chunkSize.end());
        }
        if(begTime != 0){
            m_chunkSize.erase(m_chunkSize.begin(),m_chunkSize.begin()+idStartData.first-1); ///????? startPos +-1
        }
        sig.setAmountChunkAudio(m_chunkSize.size());
        sig.setArrayChunkOffsetAudio(m_chunkSize);
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
