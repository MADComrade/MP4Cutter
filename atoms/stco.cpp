#include "stco.h"
#include "SingletonSettings.h"
STCO::STCO():Atom(STCO_NAME, STCO_DIG_NAME)
{

}

STCO::~STCO()
{

}

void STCO::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV6);
    m_size = stream.readSizeAtom();
    uint32_t pos = startPos+OFFSET_TITLE;
    stream.setPos(pos);
    m_verFlag = stream.readUInt32();
    m_amountChunk = stream.readBigEndianUInt32();
    m_chunkOffset.resize(m_amountChunk,0);
    for(int i=0;i<m_amountChunk;i++){
        m_chunkOffset[i]=stream.readBigEndianUInt32();
    }
    startPos +=m_size;
}

void STCO::prepareDataForWrite(uint32_t begTime, uint32_t endTime, uint32_t delta, TRAK_TYPE type)
{
    if(type == TRAK_TYPE::VIDEO){
        SingletonSettings& sing = SingletonSettings::getInstance();
        sing.setArrayChunkOffsetVideo(m_chunkOffset);
        uint32_t endPos = (endTime*delta)+delta;
        uint32_t countResize = m_chunkOffset.size() - endPos + begTime;
        m_startCutOffset = m_chunkOffset[begTime];
        sing.setBeginOffsetVideo(m_startCutOffset);
        m_endCutOffset = m_chunkOffset[endPos-1];
        sing.setEndOffsetVideo(m_endCutOffset);
        if(endPos < (m_chunkOffset.size()-1)){
            m_chunkOffset.erase(m_chunkOffset.begin()+endPos,m_chunkOffset.end());
        }
        if(begTime > 0){
            m_chunkOffset.erase(m_chunkOffset.begin(),m_chunkOffset.begin()+begTime);
        }
        uint32_t oldOffset = m_chunkOffset[0];
        uint32_t tempOffset{0};
        m_chunkOffset[0] = 40;
        for(uint32_t i=1;i<m_chunkOffset.size();i++){
            tempOffset = m_chunkOffset[i];
            m_chunkOffset[i] =(m_chunkOffset[i] - oldOffset)+m_chunkOffset[i-1];
            oldOffset = tempOffset;
        }
        uint32_t resizeAmount = countResize*BYTE32; // ?
        m_size -=resizeAmount;
        resizeAtom(resizeAmount,DIRECT_RESIZE::DECREASED);
    }else{

    }
}

std::pair<uint32_t, uint32_t> STCO::getOldOffset() const
{
    return std::pair<uint32_t,uint32_t>(m_startCutOffset,m_endCutOffset);
}

void STCO::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(STCO_NAME);
    stream.writeUInt32(m_verFlag);
    stream.writeLitToBigEndian(m_chunkOffset.size());
    for(int i=0;i<m_chunkOffset.size();i++){
        stream.writeLitToBigEndian(m_chunkOffset[i]);
    }
}

void STCO::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{
    callback()->resizeAtom(size,direction);
}
