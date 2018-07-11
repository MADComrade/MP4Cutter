#include "tkhd.h"
#include <iomanip>

TKHD::TKHD():Atom(TKHD_NAME, TKHD_DIG_NAME)
{
    m_data.resize(60,0);
}

TKHD::~TKHD()
{

}

void TKHD::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV3);
    uint32_t pos = startPos;
    stream.setPos(pos);
    m_size = stream.readSizeAtom();
    pos+=OFFSET_TITLE;
    stream.setPos(pos);
    m_verFlag = stream.readUInt32();
    m_creationTime = stream.readUInt32();
    m_modificationTime = stream.readUInt32();
    m_trackID = stream.readBigEndianUInt32();
    stream.readBigEndianUInt32();
    m_duration = stream.readBigEndianUInt32();
    stream.read(&(m_data[0]),m_data.size());
    startPos += m_size;
}

void TKHD::setNewDuration(uint32_t time)
{
    m_duration = time * m_singletonSettings.getTimeScaleVideo(); // для универсальности передавать time scale
}

void TKHD::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(TKHD_NAME);
    stream.writeUInt32(m_verFlag);
    stream.writeUInt32(m_creationTime);
    stream.writeUInt32(m_modificationTime);
    stream.writeLitToBigEndian(m_trackID);
    stream.writeLitToBigEndian(m_reserved);
    stream.writeLitToBigEndian(m_duration);
    stream.write(&(m_data[0]),m_data.size());
}

