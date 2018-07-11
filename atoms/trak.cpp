#include "trak.h"
#include "../interfaces/callbackinterface.h"

using namespace std;
TRAK::TRAK():Atom(TRAK_NAME, TRAK_DIG_NAME)
{
    m_tkhd = make_unique<TKHD>();
    m_mdia = make_unique<MDIA>();
    m_mdia->setCallback(this);
    m_type = TRAK_TYPE::VIDEO;
}

TRAK::~TRAK()
{

}

void TRAK::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV2);
    uint32_t pos = startPos;
    m_size = stream.readSizeAtom();
    pos = startPos+OFFSET_TITLE;
    stream.setPos(pos);
    m_tkhd->parse(stream,pos);
    m_mdia->parse(stream,pos);
    setTrakType(m_mdia->getTrakType());
    startPos += m_size;
}

void TRAK::setTrakType(TRAK_TYPE type)
{
    m_type = type;
}

void TRAK::prepareData()
{
    m_tkhd->setNewDuration(m_singletonSettings.getNewDuration());
    m_mdia->prepareData();
}

void TRAK::writeAtom(StreamWriter &stream)
{
        stream.writeLitToBigEndian(m_size);
        stream.writeAtomName(TRAK_NAME);
        m_tkhd->writeAtom(stream);
        m_mdia->writeAtom(stream);
}

void TRAK::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{
    if(direction == DIRECT_RESIZE::INCREASED){
        this->m_size +=size;
    }else{
        this->m_size -=size;
    }
    m_callback->resizeAtom(size,direction);
}
