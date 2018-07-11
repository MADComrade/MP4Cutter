#include "mdhd.h"

MDHD::MDHD():Atom(MDHD_NAME, MDHD_DIG_NAME)
{

}

MDHD::~MDHD()
{

}

void MDHD::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV4);
    uint32_t pos = startPos;
    m_size = stream.readSizeAtom();
    pos = startPos+OFFSET_TITLE;
    stream.setPos(pos);
    m_verFlag = stream.readUInt32();
    m_creationTime = stream.readUInt32();
    m_modificationTime = stream.readUInt32();
    m_timeScale = stream.readBigEndianUInt32();
    m_duration = stream.readBigEndianUInt32();
    m_language = stream.readUInt32();
    startPos += m_size;
}

void MDHD::setNewDuration(uint32_t time)
{
    m_duration = time * m_timeScale;
}

void MDHD::setTrakType(TRAK_TYPE type)
{
    m_type = type;
    if(type == TRAK_TYPE::AUDIO){
        m_singletonSettings.setTimeScaleAudio(m_timeScale);
    }
}

void MDHD::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(MDHD_NAME);
    stream.writeUInt32(m_verFlag);
    stream.writeUInt32(m_creationTime);
    stream.writeUInt32(m_modificationTime);
    stream.writeLitToBigEndian(m_timeScale);
    stream.writeLitToBigEndian(m_duration);
    stream.writeUInt32(m_language);
}
