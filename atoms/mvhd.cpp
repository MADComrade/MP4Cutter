#include "mvhd.h"

MVHD::MVHD():Atom(MVHD_NAME, MVHD_DIG_NAME)
{
    m_data.resize(76,0);
}

MVHD::~MVHD()
{

}

void MVHD::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV2);
    uint32_t pos = startPos;
    stream.setPos(pos);
    m_size = stream.readSizeAtom();
    pos+=OFFSET_TITLE;
    stream.setPos(pos);
    m_verFlag = stream.readUInt32();
    m_creationTime = stream.readUInt32();
    m_modificationTime = stream.readUInt32();
    m_timeScale = stream.readBigEndianUInt32();
    m_singletonSettings.setTimeScaleVideo(m_timeScale);
    m_duration = stream.readBigEndianUInt32();
    stream.read(&(m_data[0]),m_data.size());
    m_nextTrackID = stream.readBigEndianUInt32();
    startPos += m_size;
}

void MVHD::setNewDuration(uint32_t time)
{
    m_duration = time * m_timeScale;
}

void MVHD::setNextTrakID(uint32_t id)
{
    m_nextTrackID = id;
}

void MVHD::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(MVHD_NAME);
    stream.writeUInt32(m_verFlag);
    stream.writeUInt32(m_creationTime);
    stream.writeUInt32(m_modificationTime);
    stream.writeLitToBigEndian(m_timeScale);
    stream.writeLitToBigEndian(m_duration);
    stream.write(&(m_data[0]),m_data.size());
    stream.writeLitToBigEndian(m_nextTrackID);
}

