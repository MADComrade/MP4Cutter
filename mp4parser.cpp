#include "mp4parser.h"
#include <iostream>
#include "SingletonSettings.h"

using namespace std;

MP4Parser::MP4Parser()
{

}

MP4Parser::~MP4Parser()
{

}

void MP4Parser::parse(StreamReader &stream)
{
    uint32_t startPos{0};
    string titleName = stream.getTitleAtom();
    if(titleName.compare(FTYP_NAME)){
        exit(-25);
    }
    m_ftyp = make_unique<FTYP>();
    m_ftyp->parse(stream, startPos);
    uint32_t offset{0};
    do{
        startPos += offset;
        stream.setPos(startPos);
        offset = stream.readSizeAtom();
        titleName = stream.getTitleAtom();
    }while(titleName.compare(MOOV_NAME));
    m_moov = make_unique<MOOV>();
    m_moov->parse(stream,startPos);
}

void MP4Parser::prepareData(uint32_t begTime, uint32_t endTime)
{
    m_mdatInfo = m_moov->prepareData(begTime,endTime);
}

void MP4Parser::writeOnlyVideo(StreamReader &inStream, StreamWriter &outStream)
{
    m_ftyp->writeAtom(outStream);
    uint32_t mdatSize = (m_mdatInfo.second - m_mdatInfo.first)+OFFSET_TITLE;
    uint32_t buf = m_mdatInfo.second - m_mdatInfo.first;
    outStream.writeLitToBigEndian(mdatSize);
    outStream.writeAtomName(MDAT_NAME);

    uint32_t BlockSize = 4096000;
    streamsize blockBytes = (mdatSize - OFFSET_TITLE)/BlockSize;
    streamsize blockEndBytes = (mdatSize - OFFSET_TITLE)%BlockSize;
    streamsize startPos = m_mdatInfo.first;
    streamsize endPos = m_mdatInfo.first+BlockSize;
    vector<uint8_t> dataV (BlockSize,0);
    for (int i=0;i<blockBytes;i++){
        inStream.getBlock(&( dataV[ 0 ] ),startPos,dataV.size());
        outStream.write(reinterpret_cast< uint8_t * >(&( dataV[ 0 ] )), dataV.size());
        startPos = endPos;
        endPos +=BlockSize;
    }

    if(blockEndBytes !=0){
        dataV.resize(blockEndBytes,0);
        inStream.getBlock(&( dataV[ 0 ] ),startPos,dataV.size());
        outStream.write(reinterpret_cast< uint8_t * >(&( dataV[ 0 ] )), dataV.size());
    }

    m_moov->writeAudioAndVideo(outStream);
}
