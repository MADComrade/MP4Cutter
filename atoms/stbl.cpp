#include "stbl.h"

using namespace std;

STBL::STBL():Atom(STBL_NAME, STBL_DIG_NAME)
{
    m_mapperAtomBuild[STCO_NAME] = STCO_DIG_NAME;
    m_mapperAtomBuild[STSC_NAME] = STSC_DIG_NAME;
    m_mapperAtomBuild[STSD_NAME] = STSD_DIG_NAME;
    m_mapperAtomBuild[STSZ_NAME] = STSZ_DIG_NAME;
    m_mapperAtomBuild[STSS_NAME] = STSS_DIG_NAME;
    m_mapperAtomBuild[STTS_NAME] = STTS_DIG_NAME;
}

STBL::STBL(TRAK_TYPE type):STBL()
{
    m_trakType = type;
}

STBL::~STBL()
{

}

void STBL::setTrakType(TRAK_TYPE type)
{
    m_trakType = type;
}

void STBL::parse(StreamReader &stream, uint32_t &startPos)
{
    printAtomName(LV5);
    m_size = stream.readSizeAtom();
    uint32_t pos = startPos+OFFSET_TITLE;
    uint32_t atomSize;
    string atomName;
    while (pos<(m_size+startPos)) {
        stream.setPos(pos);
        atomSize = stream.readSizeAtom();
        atomName =stream.getTitleAtom();
        if(m_mapperAtomBuild.find(atomName)!=m_mapperAtomBuild.end()){
            buildAndParseAtom(atomName,stream,pos);
        }else{
            pos +=atomSize;
        }

    }
    startPos += m_size;
}

void STBL::prepareData()
{

    if(m_trakType == TRAK_TYPE::VIDEO){

        m_stss->prepareData();
        m_stsz->prepareData();
        m_stco->prepareData();
        m_stts->prepareData();

        std::pair<uint32_t, uint32_t> dumpPos = m_stco->getOldOffset();
        dumpPos.second += m_stsz->getEndChunkSize();
        m_singletonSettings.setEndOffsetVideo(dumpPos.second);

    }else if(m_trakType == TRAK_TYPE::AUDIO){
        m_stsz->prepareData();
        m_stco->prepareData();
        m_stts->prepareData();
        m_stsc->prepareData();
    }else{
        exit(2);
    }
}

void STBL::writeAtom(StreamWriter &stream)
{
    stream.writeLitToBigEndian(m_size);
    stream.writeAtomName(STBL_NAME);
    if(m_trakType == TRAK_TYPE::VIDEO){
        m_stsc->writeAtom(stream);
        m_stts->writeAtom(stream);
        m_stsd->writeAtom(stream);
        m_stss->writeAtom(stream);
        m_stco->writeAtom(stream);
        m_stsz->writeAtom(stream);
    } else if(m_trakType == TRAK_TYPE::AUDIO){
        m_stsc->writeAtom(stream);
        m_stts->writeAtom(stream);
        m_stsd->writeAtom(stream);
        m_stco->writeAtom(stream);
        m_stsz->writeAtom(stream);
    }
}

void STBL::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{
    if(direction == DIRECT_RESIZE::INCREASED){
        this->m_size +=size;
    }else{
        this->m_size -=size;
    }
    m_callback->resizeAtom(size,direction);
}

void STBL::buildAndParseAtom(std::string atomName, StreamReader &stream, uint32_t &startPos)
{
    switch (m_mapperAtomBuild[atomName]) {
    case STCO_DIG_NAME:
        m_stco = make_unique<STCO>(m_trakType);
        m_stco->setCallback(this);
        m_stco->parse(stream,startPos);
        break;
    case STSC_DIG_NAME:
        m_stsc = make_unique<STSC>(m_trakType);
        m_stsc->setCallback(this);
        m_stsc->parse(stream,startPos);
        break;
    case STSD_DIG_NAME:
        m_stsd = make_unique<STSD>();
        m_stsd->setCallback(this);
        m_stsd->parse(stream,startPos);
        break;
    case STSZ_DIG_NAME:
        m_stsz = make_unique<STSZ>(m_trakType);
        m_stsz->setCallback(this);
        m_stsz->parse(stream,startPos);
        break;
    case STSS_DIG_NAME:
        m_stss = make_unique<STSS>(m_trakType);
        m_stss->setCallback(this);
        m_stss->parse(stream,startPos);
        break;
    case STTS_DIG_NAME:
        m_stts = make_unique<STTS>(m_trakType);
        m_stts->setCallback(this);
        m_stts->parse(stream,startPos);
        break;
    default:
        break;
    }
}
