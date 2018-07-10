#include "stco.h"
#include "SingletonSettings.h"

using namespace std;
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
    SingletonSettings& sing = SingletonSettings::getInstance();
    if(type == TRAK_TYPE::VIDEO){
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
        //        uint32_t oldOffset = m_chunkOffset[0];
        //        uint32_t tempOffset{0};
        //        m_chunkOffset[0] = 40;
        //        for(uint32_t i=1;i<m_chunkOffset.size();i++){
        //            tempOffset = m_chunkOffset[i];
        //            m_chunkOffset[i] =(m_chunkOffset[i] - oldOffset)+m_chunkOffset[i-1];
        //            oldOffset = tempOffset;
        //        }
        uint32_t resizeAmount = countResize*BYTE32; // ?
        m_size -=resizeAmount;
        resizeAtom(resizeAmount,DIRECT_RESIZE::DECREASED);
    }else{
        pair<uint32_t,uint32_t> idStartData = sing.getStartIdChunkAudio();
        pair<uint32_t,uint32_t> idEndData = sing.getEndIdChunkAudio();
        uint32_t countResize = m_chunkOffset.size();
        vector<uint32_t>& stcoVideoOffset = sing.getArrayChunkOffsetVideo();

        if(idEndData.first < (m_chunkOffset.size()-1)){
            m_chunkOffset.erase(m_chunkOffset.begin()+idEndData.first,m_chunkOffset.end());
        }

        if(idStartData.first > 0){
            m_chunkOffset.erase(m_chunkOffset.begin(),m_chunkOffset.begin()+idStartData.first-1);
        }
        sing.setBeginOffsetAudio(m_chunkOffset[0]);
        sing.setEndOffsetAudio(m_chunkOffset[m_chunkOffset.size()-1]);
        uint32_t oldChunkOffset = m_chunkOffset[0];
        uint32_t tempOffset{0};
        uint32_t newChunkOffset = oldChunkOffset;// = m_chunkOffset[0]+sing.getFirstChunkAudioSize();
        vector<uint32_t> testAudio;
        vector<uint32_t> testVideo;
        uint32_t oldVideoOffset = stcoVideoOffset[0];

        if(oldChunkOffset<stcoVideoOffset[0]){
            sing.setBeginOffsetFile(oldChunkOffset);
            ///soun
            for(uint32_t i=1;i<m_chunkOffset.size();i++){
                testAudio.push_back(m_chunkOffset[i]-m_chunkOffset[i-1]);
            }

            m_chunkOffset[0] = 40;
            for(uint32_t i=1;i<m_chunkOffset.size();i++){
                tempOffset = m_chunkOffset[i];
                m_chunkOffset[i] =testAudio[i-1]+m_chunkOffset[i-1];
                newChunkOffset = tempOffset;
            }

            ///vide
            for(uint32_t i=1;i<stcoVideoOffset.size();i++){
                testVideo.push_back(stcoVideoOffset[i]-stcoVideoOffset[i-1]);
            }
            uint32_t oldChunkOffsetVideo = stcoVideoOffset[0];
            stcoVideoOffset[0] = (stcoVideoOffset[0]-oldChunkOffset)+40;

            for(uint32_t i=1;i<stcoVideoOffset.size();i++){
                tempOffset = stcoVideoOffset[i];
                stcoVideoOffset[i] =(stcoVideoOffset[i] - oldChunkOffsetVideo)+stcoVideoOffset[i-1];
                oldChunkOffsetVideo = tempOffset;
            }

            uint32_t videoEndPart = sing.getOffsetVideo().second + sing.getLastChunkVideoSize();
            uint32_t audioEndPart = sing.getOffsetAudio().second + sing.getLastChunkAudioSize();
            if(videoEndPart>audioEndPart){
                sing.setSizeCut(videoEndPart);
            }else{
                sing.setSizeCut(audioEndPart);
            }
        }else{
            ///////////////////////////////////////////////////////////////////////////////////////////
            ///vide
            ///
            sing.setBeginOffsetFile(stcoVideoOffset[0]);
            for(uint32_t i=1;i<stcoVideoOffset.size();i++){
                testVideo.push_back(stcoVideoOffset[i]-stcoVideoOffset[i-1]);
            }

            uint32_t oldChunkOffsetVideo = stcoVideoOffset[0];
            stcoVideoOffset[0] = 40;

            for(uint32_t i=1;i<stcoVideoOffset.size();i++){
                tempOffset = stcoVideoOffset[i];
                stcoVideoOffset[i] =(stcoVideoOffset[i] - oldChunkOffsetVideo)+stcoVideoOffset[i-1];
                oldChunkOffsetVideo = tempOffset;
            }
            ///soun
            for(uint32_t i=1;i<m_chunkOffset.size();i++){
                testAudio.push_back(m_chunkOffset[i]-m_chunkOffset[i-1]);
            }

            m_chunkOffset[0]=(m_chunkOffset[0]-oldVideoOffset)+40;
            for(uint32_t i=1;i<m_chunkOffset.size();i++){
                tempOffset = m_chunkOffset[i];
                m_chunkOffset[i] =(m_chunkOffset[i] - newChunkOffset)+m_chunkOffset[i-1];
                newChunkOffset = tempOffset;
            }

            uint32_t videoEndPart = sing.getOffsetVideo().second + sing.getLastChunkVideoSize();
            uint32_t audioEndPart = sing.getOffsetAudio().second + sing.getLastChunkAudioSize();
            if(videoEndPart>audioEndPart){
                sing.setSizeCut(videoEndPart);
            }else{
                sing.setSizeCut(audioEndPart);
            }
        }

        uint32_t resizeAmount = (countResize-m_chunkOffset.size())*BYTE32;
        m_size -=resizeAmount;
        resizeAtom(resizeAmount,DIRECT_RESIZE::DECREASED);
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
