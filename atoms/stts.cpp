#include "stts.h"
#include "SingletonSettings.h"

STTS::STTS():Atom(STTS_NAME, STTS_DIG_NAME)
{

}

STTS::~STTS()
{

}

void STTS::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV6);
    m_size = stream.readSizeAtom();
    uint32_t pos = startPos+OFFSET_TITLE;
    stream.setPos(pos);
    m_verFlag = stream.readUInt32();
    m_amount = stream.readBigEndianUInt32();
    m_data.resize(m_amount);
    for(auto i=0;i<m_amount;i++){
        m_data[i].m_sampleCount=stream.readBigEndianUInt32();
        m_data[i].m_sampleDelta=stream.readBigEndianUInt32();
    }

    if(m_type == TRAK_TYPE::VIDEO){
        SingletonSettings::getInstance().setDeltaVideo(m_data[0].m_sampleDelta);
    }else{
        SingletonSettings::getInstance().setDeltaAudio(m_data[0].m_sampleDelta);
    }
    startPos +=m_size;
}

void STTS::prepareDataForWrite(uint32_t begTime, uint32_t endTime, uint32_t delta, TRAK_TYPE type)
{
    if(type == TRAK_TYPE::VIDEO){
        for(auto i=0;i<m_amount;i++){
            m_data[i].m_sampleCount = (delta * endTime) + delta - begTime;
            m_newAmountChunk = m_data[i].m_sampleCount;
        }
    }else{
        for(auto i=0;i<m_amount;i++){
            m_data[i].m_sampleCount = delta;
            m_newAmountChunk = m_data[i].m_sampleCount;
        }
    }
}

void STTS::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{

}

uint32_t STTS::newAmountChunk() const
{
    return m_newAmountChunk;
}

void STTS::setTrakType(TRAK_TYPE type)
{
    m_type = type;
}

void STTS::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(STTS_NAME);
    stream.writeUInt32(m_verFlag);
    stream.writeLitToBigEndian(m_amount);
    for(int i=0;i<m_amount;i++){
        stream.writeLitToBigEndian( m_data[i].m_sampleCount);
        stream.writeLitToBigEndian( m_data[i].m_sampleDelta);
    }
}
