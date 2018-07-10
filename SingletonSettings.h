#ifndef SINGLETONSETTINGS_H
#define SINGLETONSETTINGS_H

#include <iostream>
#include <vector>

class SingletonSettings
{
public:
	static SingletonSettings& getInstance();

	void setDeltaAudio(uint32_t delta);
	void setDeltaVideo(uint32_t delta);
    void setDeltaIFrame(uint32_t delta);

    uint32_t getDeltaAudio() const;
    uint32_t getDeltaVideo() const;
    uint32_t getDeltaIFrame() const;

	void setPeriodTime(uint32_t begTime, uint32_t endTime);

    void setTimeScaleAudio(uint32_t timeScale);
    void setTimeScaleVideo(uint32_t timeScale);

	uint32_t getBeginTime();
	uint32_t getEndTime();

    uint32_t getNewDuration() const;

	uint32_t getTimeScaleAudio();
	uint32_t getTimeScaleVideo();

	uint32_t getScaledBeginTimeVideo();
	uint32_t getScaledEndTimeVideo();

	uint32_t getScaledBeginTimeAudio();
	uint32_t getScaledEndTimeAudio();
	
    void setBeginOffsetAudio(uint32_t offset);
    void setEndOffsetAudio(uint32_t offset);

    void setBeginOffsetVideo(uint32_t offset);
    void setEndOffsetVideo(uint32_t offset);

    std::pair<uint32_t,uint32_t> getOffsetAudio();
    std::pair<uint32_t,uint32_t> getOffsetVideo();

    std::pair<uint32_t,uint32_t> getStartIdChunkAudio();
    std::pair<uint32_t,uint32_t> getEndIdChunkAudio();

	void setArrayChunkOffsetAudio(std::vector<uint32_t> &arrayChunkOffset);
	void setArrayChunkOffsetVideo(std::vector<uint32_t> &arrayChunkOffset);

    std::vector<uint32_t>& getArrayChunkOffsetAudio();
    std::vector<uint32_t>& getArrayChunkOffsetVideo();

	void setIDBeginChunkAudio(uint32_t idChunk);
	void setIDEndChunkAudio(uint32_t idChunk);

	void setIDBeginChunkVideo(uint32_t idChunk);
	void setIDEndChunkVideo(uint32_t idChunk);

	uint32_t getIDBeginChunkAudio();
	uint32_t getIDEndChunkAudio();

	uint32_t getIDBeginChunkVideo();
	uint32_t getIDEndChunkVideo();

    uint32_t getIdBegChunkWithIFrame() const;
    uint32_t getIdEndChunkWithIFrame() const;

    uint32_t getFirstChunkAudioSize() const;
    void setFirstChunkAudioSize(const uint32_t &firstChunkAudioSize);

    uint32_t getLastChunkAudioSize() const;
    void setLastChunkAudioSize(const uint32_t &lastChunkAudioSize);

    uint32_t getAmountChunkAudio() const;
    void setAmountChunkAudio(const uint32_t &amountChunkAudio);

    uint32_t getAmountChunkVideo() const;
    void setAmountChunkVideo(const uint32_t &amountChunkVideo);

    uint32_t getLastChunkVideoSize() const;
    void setLastChunkVideoSize(const uint32_t &lastChunkVideoSize);

    uint32_t getBeginOffsetFile() const;
    void setBeginOffsetFile(const uint32_t &beginOffsetFile);

    uint32_t getSizeCut() const;
    void setSizeCut(const uint32_t &sizeCut);

private:
    SingletonSettings() {}
    SingletonSettings(const SingletonSettings&) {}
    SingletonSettings& operator=(SingletonSettings&) {}

    uint32_t getOffsetAudioChunk(double fractPos);
    uint32_t    m_beginTime{ 0 };
    uint32_t	m_endTime{ 0 };

    uint32_t	m_newDuration{ 0 };
    uint32_t	m_timeScaleVideo{ 0 };

    uint32_t	m_timeScaleAudio{ 0 };

    uint32_t	m_deltaAudio{ 0 };
    uint32_t	m_deltaVideo{ 0 };
    uint32_t	m_deltaIFrame{ 0 };

    uint32_t	m_beginOffsetAudio{ 0 };
    uint32_t	m_endOffsetAudio{ 0 };

    uint32_t	m_beginOffsetVideo{ 0 };
    uint32_t	m_endOffsetVideo{ 0 };

    uint32_t    m_beginOffsetFile{0};
    uint32_t    m_sizeCut{0};

    uint32_t	m_idBeginChunkVideo{ 0 };
    uint32_t	m_idEndChunkVideo{ 0 };
    uint32_t	m_idBegChunkWithIFrame{ 0 };
    uint32_t	m_idEndChunkWithIFrame{ 0 };

    uint32_t	m_idBeginChunkAudio{ 0 };
    uint32_t	m_idEndChunkAudio{ 0 };

    uint32_t	m_firstChunkAudioSize{ 0 };
    uint32_t	m_lastChunkAudioSize{ 0 };
    uint32_t	m_lastChunkVideoSize{ 0 };

    uint32_t	m_amountChunkAudio{ 0 };
    uint32_t	m_amountChunkVideo{ 0 };

    uint32_t m_offsetStartAudioPos{0};
    uint32_t m_offsetEndtAudioPos{0};

    std::vector<uint32_t>* pm_chunkOffsetAudio{ nullptr };
    std::vector<uint32_t>* pm_chunkOffsetVideo{ nullptr };
};

#endif
