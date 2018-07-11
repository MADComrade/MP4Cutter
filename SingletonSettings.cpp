#include "SingletonSettings.h"

SingletonSettings& SingletonSettings::getInstance() {
	static SingletonSettings instance;
	return instance;
}


void SingletonSettings::setPeriodTime(uint32_t begTime, uint32_t endTime) {
	m_beginTime = begTime;
	m_endTime = endTime;
    m_newDuration = endTime - begTime;
    m_idBeginChunkVideo = m_beginTime * m_deltaVideo;
    m_idEndChunkVideo = m_endTime * m_deltaVideo;
    m_idBegChunkWithIFrame = m_beginTime * m_delta;
    m_idEndChunkWithIFrame = m_endTime * m_delta;
    double endIntPart;
    double startIntPart;

    double fractStartPos = modf(((begTime * static_cast<float>(m_timeScaleAudio))/m_deltaAudio)/4.0f,&startIntPart);
    double fractEndPos = modf(((endTime * static_cast<float>(m_timeScaleAudio))/m_deltaAudio)/4.0f,&endIntPart);

    m_idBeginChunkAudio = static_cast<uint32_t>(startIntPart)+3;
    m_idEndChunkAudio = static_cast<uint32_t>(endIntPart)+3;
    m_offsetStartAudioPos = getOffsetAudioChunk(fractStartPos);
    m_offsetEndtAudioPos = getOffsetAudioChunk(fractEndPos);
}

uint32_t SingletonSettings::getBeginTime() {
	return m_beginTime;
}

uint32_t SingletonSettings::getEndTime() {
    return m_endTime;
}

uint32_t SingletonSettings::getNewDuration() const
{
    return m_newDuration;
}

void SingletonSettings::setTimeScaleAudio(uint32_t timeScale) {
    m_timeScaleAudio = timeScale;
}

void SingletonSettings::setTimeScaleVideo(uint32_t timeScale) {
    m_timeScaleVideo = timeScale;
}

uint32_t SingletonSettings::getTimeScaleAudio() {
    return m_timeScaleAudio;
}

uint32_t SingletonSettings::getTimeScaleVideo() {
    return m_timeScaleVideo;
}

void SingletonSettings::setDeltaAudio(uint32_t delta) {
	m_deltaAudio = delta;
}

void SingletonSettings::setDeltaVideo(uint32_t delta) {
    m_deltaVideo = delta;
}

void SingletonSettings::setDelta(uint32_t delta)
{
    m_delta = delta;
}

uint32_t SingletonSettings::getDeltaAudio() const {
	return m_deltaAudio;	
}

uint32_t SingletonSettings::getDeltaVideo() const {
    return m_deltaVideo;
}

uint32_t SingletonSettings::getDelta() const
{
    return m_delta;
}

void SingletonSettings::setBeginOffsetAudio(uint32_t offset) {
	m_beginOffsetAudio = offset;
}

void SingletonSettings::setEndOffsetAudio(uint32_t offset) {
	m_endOffsetAudio = offset;
}

void SingletonSettings::setBeginOffsetVideo(uint32_t offset) {
	m_beginOffsetVideo = offset;
}

void SingletonSettings::setEndOffsetVideo(uint32_t offset) {
    m_endOffsetVideo = offset;
}

std::pair<uint32_t, uint32_t> SingletonSettings::getOffsetAudio()
{
    return std::pair<uint32_t, uint32_t>(m_beginOffsetAudio,m_endOffsetAudio);
}

std::pair<uint32_t, uint32_t> SingletonSettings::getOffsetVideo()
{
    return std::pair<uint32_t, uint32_t>(m_beginOffsetVideo,m_endOffsetVideo);
}

std::pair<uint32_t, uint32_t> SingletonSettings::getStartIdChunkAudio()
{
    return std::pair<uint32_t, uint32_t>(m_idBeginChunkAudio,m_offsetStartAudioPos);
}

std::pair<uint32_t, uint32_t> SingletonSettings::getEndIdChunkAudio()
{
    return std::pair<uint32_t, uint32_t>(m_idEndChunkAudio,m_offsetEndtAudioPos);
}

void SingletonSettings::setArrayChunkOffsetAudio(std::vector<uint32_t> &arrayChunkOffset) {
	pm_chunkOffsetAudio = &arrayChunkOffset;
}

void SingletonSettings::setArrayChunkOffsetVideo(std::vector<uint32_t> &arrayChunkOffset) {
    pm_chunkOffsetVideo = &arrayChunkOffset;
}

std::vector<uint32_t>& SingletonSettings::getArrayChunkOffsetAudio() {
	return *pm_chunkOffsetAudio;
}

std::vector<uint32_t>& SingletonSettings::getArrayChunkOffsetVideo() {
	return *pm_chunkOffsetVideo;
}


void SingletonSettings::setIDBeginChunkAudio(uint32_t idChunk) {
	m_idBeginChunkAudio = idChunk;
}

void SingletonSettings::setIDEndChunkAudio(uint32_t idChunk) {
	m_idEndChunkAudio = idChunk;
}

void SingletonSettings::setIDBeginChunkVideo(uint32_t idChunk) {
	m_idBeginChunkVideo = idChunk;
}

void SingletonSettings::setIDEndChunkVideo(uint32_t idChunk) {
	m_idEndChunkVideo = idChunk;
}

uint32_t SingletonSettings::getIDBeginChunkAudio() {
	return m_idBeginChunkAudio;
}

uint32_t SingletonSettings::getIDEndChunkAudio() {
	return m_idEndChunkAudio;
}

uint32_t SingletonSettings::getIDBeginChunkVideo() {
	return m_idBeginChunkVideo;
}

uint32_t SingletonSettings::getIDEndChunkVideo() {
    return m_idEndChunkVideo;
}

uint32_t SingletonSettings::getOffsetAudioChunk(double fractPos)
{
    if((fractPos>=0)&&(fractPos<0.25f)){
        return 0;
    }
    else if((fractPos>=0.25f)&&(fractPos<0.5f)){
        return 1;
    }else if((fractPos>=0.5f)&&(fractPos<0.75f)){
        return 2;
    }else{
        return 3;
    }
}

uint32_t SingletonSettings::getSizeCut() const
{
    return m_sizeCut;
}

void SingletonSettings::setSizeCut(const uint32_t &sizeCut)
{
    m_sizeCut = sizeCut;
}

uint32_t SingletonSettings::getBeginOffsetFile() const
{
    return m_beginOffsetFile;
}

void SingletonSettings::setBeginOffsetFile(const uint32_t &beginOffsetFile)
{
    m_beginOffsetFile = beginOffsetFile;
}

uint32_t SingletonSettings::getLastChunkVideoSize() const
{
    return m_lastChunkVideoSize;
}

void SingletonSettings::setLastChunkVideoSize(const uint32_t &lastChunkVideoSize)
{
    m_lastChunkVideoSize = lastChunkVideoSize;
}

uint32_t SingletonSettings::getAmountChunkVideo() const
{
    return m_amountChunkVideo;
}

void SingletonSettings::setAmountChunkVideo(const uint32_t &amountChunkVideo)
{
    m_amountChunkVideo = amountChunkVideo;
}

uint32_t SingletonSettings::getAmountChunkAudio() const
{
    return m_amountChunkAudio;
}

void SingletonSettings::setAmountChunkAudio(const uint32_t &amountChunkAudio)
{
    m_amountChunkAudio = amountChunkAudio;
}

uint32_t SingletonSettings::getLastChunkAudioSize() const
{
    return m_lastChunkAudioSize;
}

void SingletonSettings::setLastChunkAudioSize(const uint32_t &lastChunkAudioSize)
{
    m_lastChunkAudioSize = lastChunkAudioSize;
}

uint32_t SingletonSettings::getFirstChunkAudioSize() const
{
    return m_firstChunkAudioSize;
}

void SingletonSettings::setFirstChunkAudioSize(const uint32_t &firstChunkAudioSize)
{
    m_firstChunkAudioSize = firstChunkAudioSize;
}

uint32_t SingletonSettings::getIdEndChunkWithIFrame() const
{
    return m_idEndChunkWithIFrame;
}

uint32_t SingletonSettings::getIdBegChunkWithIFrame() const
{
    return m_idBegChunkWithIFrame;
}
