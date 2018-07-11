#include "minf.h"
#include "../interfaces/callbackinterface.h"

using namespace std;

MINF::MINF(TRAK_TYPE type):
    Atom(MINF_NAME, MINF_DIG_NAME),
    m_trakType(type)
{
    m_dinf = make_unique<DINF>();
}

MINF::~MINF()
{

}


void MINF::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV4);
    uint32_t pos = startPos;
    m_size = stream.readSizeAtom();
    pos = startPos+OFFSET_TITLE;
    stream.setPos(pos);
    if(m_trakType == TRAK_TYPE::VIDEO){
        m_vmhd = make_unique<VMHD>();
        m_vmhd->parse(stream,pos);
    } else if(m_trakType == TRAK_TYPE::AUDIO){
        m_smhd = make_unique<SMHD>();
        m_smhd->parse(stream,pos);
    }else{
        exit(100);
    }
    m_dinf->parse(stream,pos);
    m_stbl = make_unique<STBL>(m_trakType);
    m_stbl->setCallback(this);
    m_stbl->parse(stream,pos);
    startPos += m_size;
}

void MINF::prepareData()
{
    m_stbl->prepareData();
}

void MINF::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(MINF_NAME);
    if(m_trakType == TRAK_TYPE::VIDEO){
        m_vmhd->writeAtom(stream);
    } else if(m_trakType == TRAK_TYPE::AUDIO){
        m_smhd->writeAtom(stream);
    }
    m_dinf->writeAtom(stream);
    m_stbl->writeAtom(stream); /// TODO
}

void MINF::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{
    if(direction == DIRECT_RESIZE::INCREASED){
        this->m_size +=size;
    }else{
        this->m_size -=size;
    }
    m_callback->resizeAtom(size,direction);
}
