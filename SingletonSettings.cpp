﻿//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ----------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#include "SingletonSettings.h"

//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------ОПРЕДЕЛЕНИЕ МЕТОДОВ----------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

//**************************************************************************************//
//--------------------------------------------------------------------------------------//
//---------------------------КЛАСС НАСТРОЙКИ НА ОСНОВЕ ПАТТЕРНА ОДИНОЧКА----------------//
//--------------------------------------------------------------------------------------//
//**************************************************************************************//

//**************************************************************************************//
//------------выдача объекта SingletonSettings------------------------------------------//
SingletonSettings& SingletonSettings::getInstance() {
	static SingletonSettings instance;													// создание объекта SingletonSettings, создается один раз, при вызове метода
	return instance;																	// возврат объекта
}

//**************************************************************************************//
//------------установка промежутка времени обработки------------------------------------//
void SingletonSettings::setPeriodTime(uint32_t begTime, uint32_t endTime) {
	m_beginTime = begTime;																// установка начала обработки
	m_endTime = endTime;																// установка конца обработки
	m_newDuration = endTime - begTime;													// вычисление продолжительности обработанного видео 
	m_idBeginChunkVideo = m_beginTime * m_deltaVideo;									// вычисление чанка видео на начало обработки
	m_idEndChunkVideo = m_endTime * m_deltaVideo;										// вычисление чанка видео на конец обработки
	m_idBegChunkWithIFrame = m_beginTime * m_delta;										// вычисление ключевого чанка на начало обработки
	m_idEndChunkWithIFrame = m_endTime * m_delta;										// вычисление ключевого чанка на конец обработки
	double endIntPart;																	// выделение целой части ID последнего чанка для аудио
	double startIntPart;																// выделение целой части ID первого чанка для аудио

	double fractStartPos = modf(((begTime * static_cast<float>(m_timeScaleAudio)) / m_deltaAudio) / 4.0f, &startIntPart);	// выделение дробной части ID начального чанка для аудио
	double fractEndPos = modf(((endTime * static_cast<float>(m_timeScaleAudio)) / m_deltaAudio) / 4.0f, &endIntPart);		// выделение дробной части ID последнего чанка для аудио

	m_idBeginChunkAudio = static_cast<uint32_t>(startIntPart) + 2;						// вычисление чанка аудио на начало обработки
	m_idEndChunkAudio = static_cast<uint32_t>(endIntPart) + 2;							// вычисление чанка аудио на конец обработки
	m_offsetStartAudioPos = getOffsetAudioChunk(fractStartPos);							// вычисление смещение ID начального чанка аудио
	m_offsetEndtAudioPos = getOffsetAudioChunk(fractEndPos);							// вычисление смещение ID конечного чанка аудио
}

//**************************************************************************************//
//------------выдача времени начала обработки-------------------------------------------//
uint32_t SingletonSettings::getBeginTime() {
	return m_beginTime;
}

//**************************************************************************************//
//------------выдача времени окончания обработки----------------------------------------//
uint32_t SingletonSettings::getEndTime() {
	return m_endTime;
}

//**************************************************************************************//
//------------выдача продолжительности обработанного видео------------------------------//
uint32_t SingletonSettings::getNewDuration() const {
	return m_newDuration;
}

//**************************************************************************************//
//------------установка коэффициента масштабирования аудио------------------------------//
void SingletonSettings::setTimeScaleAudio(uint32_t timeScale) {
	m_timeScaleAudio = timeScale;
}

//**************************************************************************************//
//------------установка коэффициента масштабирования видео------------------------------//
void SingletonSettings::setTimeScaleVideo(uint32_t timeScale) {
	m_timeScaleVideo = timeScale;
}

//**************************************************************************************//
//------------выдача коэффициента масштабирования аудио---------------------------------//
uint32_t SingletonSettings::getTimeScaleAudio() {
	return m_timeScaleAudio;
}

//**************************************************************************************//
//------------выдача коэффициента масштабирования видео---------------------------------//
uint32_t SingletonSettings::getTimeScaleVideo() {
	return m_timeScaleVideo;
}

//**************************************************************************************//
//------------установка дельты времени аудио--------------------------------------------//
void SingletonSettings::setDeltaAudio(uint32_t delta) {
	m_deltaAudio = delta;
}

//**************************************************************************************//
//------------установка дельты времени видео--------------------------------------------//
void SingletonSettings::setDeltaVideo(uint32_t delta) {
	m_deltaVideo = delta;
}

//**************************************************************************************//
//------------установка дельты времени для ключевых кадров видео------------------------//
void SingletonSettings::setDelta(uint32_t delta) {
	m_delta = delta;
}

//**************************************************************************************//
//------------выдача дельты времени аудио-----------------------------------------------//
uint32_t SingletonSettings::getDeltaAudio() const {
	return m_deltaAudio;
}

//**************************************************************************************//
//------------выдача дельты времени видео-----------------------------------------------//
uint32_t SingletonSettings::getDeltaVideo() const {
	return m_deltaVideo;
}

//**************************************************************************************//
//------------выдача дельты времени для ключевых кадров видео---------------------------//
uint32_t SingletonSettings::getDelta() const {
	return m_delta;
}

//**************************************************************************************//
//------------установка начального сдвига аудио-----------------------------------------//
void SingletonSettings::setBeginOffsetAudio(uint32_t offset) {
	m_beginOffsetAudio = offset;
}

//**************************************************************************************//
//------------установка конечного сдвига аудио------------------------------------------//
void SingletonSettings::setEndOffsetAudio(uint32_t offset) {
	m_endOffsetAudio = offset;
}

//**************************************************************************************//
//------------установка начального сдвига видео-----------------------------------------//
void SingletonSettings::setBeginOffsetVideo(uint32_t offset) {
	m_beginOffsetVideo = offset;
}

//**************************************************************************************//
//------------установка конечного сдвига видео------------------------------------------//
void SingletonSettings::setEndOffsetVideo(uint32_t offset) {
	m_endOffsetVideo = offset;
}

//**************************************************************************************//
//------------выдача начального и конечного сдвига аудио--------------------------------//
std::pair<uint32_t, uint32_t> SingletonSettings::getOffsetAudio() {
	return std::pair<uint32_t, uint32_t>(m_beginOffsetAudio, m_endOffsetAudio);
}

//**************************************************************************************//
//------------выдача начального и конечного сдвига видео--------------------------------//
std::pair<uint32_t, uint32_t> SingletonSettings::getOffsetVideo() {
	return std::pair<uint32_t, uint32_t>(m_beginOffsetVideo, m_endOffsetVideo);
}

//**************************************************************************************//
//------------выдача начального ID и сдвига аудио---------------------------------------//
std::pair<uint32_t, uint32_t> SingletonSettings::getStartIdChunkAudio() {
	return std::pair<uint32_t, uint32_t>(m_idBeginChunkAudio, m_offsetStartAudioPos);
}

//**************************************************************************************//
//------------выдача конечного ID и сдвига аудио----------------------------------------//
std::pair<uint32_t, uint32_t> SingletonSettings::getEndIdChunkAudio() {
	return std::pair<uint32_t, uint32_t>(m_idEndChunkAudio, m_offsetEndtAudioPos);
}

//**************************************************************************************//
//------------установка массива сдвигов чанков аудио------------------------------------//
void SingletonSettings::setArrayChunkOffsetAudio(std::vector<uint32_t> &arrayChunkOffset) {
	pm_chunkOffsetAudio = &arrayChunkOffset;
}

//**************************************************************************************//
//------------установка массива сдвигов чанков видео------------------------------------//
void SingletonSettings::setArrayChunkOffsetVideo(std::vector<uint32_t> &arrayChunkOffset) {
	pm_chunkOffsetVideo = &arrayChunkOffset;
}

//**************************************************************************************//
//------------выдача массива сдвигов чанков аудио---------------------------------------//
std::vector<uint32_t>& SingletonSettings::getArrayChunkOffsetAudio() {
	return *pm_chunkOffsetAudio;
}

//**************************************************************************************//
//------------выдача массива сдвигов чанков видео---------------------------------------//
std::vector<uint32_t>& SingletonSettings::getArrayChunkOffsetVideo() {
	return *pm_chunkOffsetVideo;
}

//**************************************************************************************//
//------------установка начального ID чанка аудио---------------------------------------//
void SingletonSettings::setIDBeginChunkAudio(uint32_t idChunk) {
	m_idBeginChunkAudio = idChunk;
}

//**************************************************************************************//
//------------установка конечного ID чанка аудио----------------------------------------//
void SingletonSettings::setIDEndChunkAudio(uint32_t idChunk) {
	m_idEndChunkAudio = idChunk;
}

//**************************************************************************************//
//------------установка начального ID чанка видео---------------------------------------//
void SingletonSettings::setIDBeginChunkVideo(uint32_t idChunk) {
	m_idBeginChunkVideo = idChunk;
}

//**************************************************************************************//
//------------установка конечного ID чанка видео----------------------------------------//
void SingletonSettings::setIDEndChunkVideo(uint32_t idChunk) {
	m_idEndChunkVideo = idChunk;
}

//**************************************************************************************//
//------------выдача начального ID чанка аудио------------------------------------------//
uint32_t SingletonSettings::getIDBeginChunkAudio() {
	return m_idBeginChunkAudio;
}

//**************************************************************************************//
//------------выдача конечного ID чанка аудио-------------------------------------------//
uint32_t SingletonSettings::getIDEndChunkAudio() {
	return m_idEndChunkAudio;
}

//**************************************************************************************//
//------------выдача начального ID чанка видео------------------------------------------//
uint32_t SingletonSettings::getIDBeginChunkVideo() {
	return m_idBeginChunkVideo;
}

//**************************************************************************************//
//------------выдача конечного ID чанка видео-------------------------------------------//
uint32_t SingletonSettings::getIDEndChunkVideo() {
	return m_idEndChunkVideo;
}

//**************************************************************************************//
//------------вычисление смещения чанка аудио-------------------------------------------//
uint32_t SingletonSettings::getOffsetAudioChunk(double fractPos)
{
	if ((fractPos >= 0) && (fractPos < 0.25f)) {
		return 0;
	}
	else if ((fractPos >= 0.25f) && (fractPos < 0.5f)) {
		return 1;
	}
	else if ((fractPos >= 0.5f) && (fractPos < 0.75f)) {
		return 2;
	}
	else {
		return 3;
	}
}

//**************************************************************************************//
//------------выдача размера вырезаемого видео------------------------------------------//
uint32_t SingletonSettings::getSizeCut() const {
	return m_sizeCut;
}

//**************************************************************************************//
//------------установка размера выходного видео-----------------------------------------//
void SingletonSettings::setSizeCut(const uint32_t &sizeCut) {
	m_sizeCut = sizeCut;
}

//**************************************************************************************//
//------------установка размера выходного видео-----------------------------------------//
uint32_t SingletonSettings::getBeginOffsetFile() const {
	return m_beginOffsetFile;
}

//**************************************************************************************//
//------------установка начального сдвига отнсительно начала файла для вырезания--------//
void SingletonSettings::setBeginOffsetFile(const uint32_t &beginOffsetFile) {
	m_beginOffsetFile = beginOffsetFile;
}

//**************************************************************************************//
//------------выдача размера последнего чанка видео-------------------------------------//
uint32_t SingletonSettings::getLastChunkVideoSize() const {
	return m_lastChunkVideoSize;
}

//**************************************************************************************//
//------------установка размера последнего чанка видео----------------------------------//
void SingletonSettings::setLastChunkVideoSize(const uint32_t &lastChunkVideoSize) {
	m_lastChunkVideoSize = lastChunkVideoSize;
}

//**************************************************************************************//
//------------выдача кол-ва чанков видео------------------------------------------------//
uint32_t SingletonSettings::getAmountChunkVideo() const {
	return m_amountChunkVideo;
}

//**************************************************************************************//
//------------установка кол-ва чанков видео---------------------------------------------//
void SingletonSettings::setAmountChunkVideo(const uint32_t &amountChunkVideo) {
	m_amountChunkVideo = amountChunkVideo;
}

//**************************************************************************************//
//------------выдача кол-ва чанков аудио------------------------------------------------//
uint32_t SingletonSettings::getAmountChunkAudio() const {
	return m_amountChunkAudio;
}

//**************************************************************************************//
//------------установка кол-ва чанков аудио---------------------------------------------//
void SingletonSettings::setAmountChunkAudio(const uint32_t &amountChunkAudio) {
	m_amountChunkAudio = amountChunkAudio;
}

//**************************************************************************************//
//------------выдача размера последнего чанка аудио-------------------------------------//
uint32_t SingletonSettings::getLastChunkAudioSize() const {
	return m_lastChunkAudioSize;
}

//**************************************************************************************//
//------------установка размера последнего чанка аудио----------------------------------//
void SingletonSettings::setLastChunkAudioSize(const uint32_t &lastChunkAudioSize) {
	m_lastChunkAudioSize = lastChunkAudioSize;
}

//**************************************************************************************//
//------------выдача размера первого чанка аудио----------------------------------------//
uint32_t SingletonSettings::getFirstChunkAudioSize() const {
	return m_firstChunkAudioSize;
}

//**************************************************************************************//
//------------установка размера первого чанка аудио-------------------------------------//
void SingletonSettings::setFirstChunkAudioSize(const uint32_t &firstChunkAudioSize) {
	m_firstChunkAudioSize = firstChunkAudioSize;
}

//**************************************************************************************//
//------------выдача ID последнего чанка с ключевым кадром видео------------------------//
uint32_t SingletonSettings::getIdEndChunkWithIFrame() const {
	return m_idEndChunkWithIFrame;
}

//**************************************************************************************//
//------------установка ID последнего чанка с ключевым кадром---------------------------//
uint32_t SingletonSettings::getIdBegChunkWithIFrame() const {
	return m_idBegChunkWithIFrame;
}