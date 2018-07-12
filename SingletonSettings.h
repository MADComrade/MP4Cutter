#ifndef SINGLETONSETTINGS_H
#define SINGLETONSETTINGS_H

//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ----------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------ОПРЕДЕЛЕНИЕ КЛАССОВ----------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

//**************************************************************************************//
//---------------------------класс настройки на основе паттерна одиночка----------------//
class SingletonSettings {
public:
	//----------------------------------------------------------------------------------//
	//----------------------------публичные методы--------------------------------------//
	//----------------------------------------------------------------------------------//
	static SingletonSettings& getInstance();											// выдача объекта класса

	void setDeltaAudio(uint32_t delta);													// установка дельты времени аудио
	void setDeltaVideo(uint32_t delta);													// установка дельты времени видео
	void setDelta(uint32_t delta);														// установка дельты времени для ключевых кадров видео

	uint32_t getDeltaAudio() const;														// выдача дельты времени аудио
	uint32_t getDeltaVideo() const;														// выдача дельты времени видео
	uint32_t getDelta() const;															// выдача дельты времени для ключевых кадров видео

	void setPeriodTime(uint32_t begTime, uint32_t endTime);								// установка промежутка времени обработки

	void setTimeScaleAudio(uint32_t timeScale);											// установка коэффициента масштабирования аудио
	void setTimeScaleVideo(uint32_t timeScale);											// установка коэффициента масштабирования видео

	uint32_t getBeginTime();															// выдача времени начала обработки
	uint32_t getEndTime();																// выдача времени окончания обработки

	uint32_t getNewDuration() const;													// выдача продолжительности обработанного видео

	uint32_t getTimeScaleAudio();														// выдача коэффициента масштабирования аудио
	uint32_t getTimeScaleVideo();														// выдача коэффициента масштабирования видео

	void setBeginOffsetAudio(uint32_t offset);											// установка начального сдвига аудио
	void setEndOffsetAudio(uint32_t offset);											// установка конечного сдвига аудио

	void setBeginOffsetVideo(uint32_t offset);											// установка начального сдвига видео
	void setEndOffsetVideo(uint32_t offset);											// установка конечного сдвига видео

	std::pair<uint32_t, uint32_t> getOffsetAudio();										// выдача начального и конечного сдвига аудио
	std::pair<uint32_t, uint32_t> getOffsetVideo();										// выдача начального и конечного сдвига видео

	std::pair<uint32_t, uint32_t> getStartIdChunkAudio();								// выдача начального ID и сдвига аудио
	std::pair<uint32_t, uint32_t> getEndIdChunkAudio();									// выдача конечного ID и сдвига аудио

	void setArrayChunkOffsetAudio(std::vector<uint32_t> &arrayChunkOffset);				// установка массива сдвигов чанков аудио
	void setArrayChunkOffsetVideo(std::vector<uint32_t> &arrayChunkOffset);				// установка массива сдвигов чанков видео

	std::vector<uint32_t>& getArrayChunkOffsetAudio();									// выдача массива сдвигов чанков аудио
	std::vector<uint32_t>& getArrayChunkOffsetVideo();									// выдача массива сдвигов чанков видео

	void setIDBeginChunkAudio(uint32_t idChunk);										// установка начального ID чанка аудио
	void setIDEndChunkAudio(uint32_t idChunk);											// установка конечного ID чанка аудио

	void setIDBeginChunkVideo(uint32_t idChunk);										// установка начального ID чанка видео
	void setIDEndChunkVideo(uint32_t idChunk);											// установка конечного ID чанка видео

	uint32_t getIDBeginChunkAudio();													// выдача начального ID чанка аудио
	uint32_t getIDEndChunkAudio();														// выдача конечного ID чанка аудио

	uint32_t getIDBeginChunkVideo();													// выдача начального ID чанка видео
	uint32_t getIDEndChunkVideo();														// выдача конечного ID чанка видео

	uint32_t getIdBegChunkWithIFrame() const;											// установка ID последнего чанка с ключевым кадром
	uint32_t getIdEndChunkWithIFrame() const;											// выдача ID последнего чанка с ключевым кадром видео

	uint32_t getFirstChunkAudioSize() const;											// выдача размера первого чанка аудио
	void setFirstChunkAudioSize(const uint32_t &firstChunkAudioSize);					// установка размера первого чанка аудио

	uint32_t getLastChunkAudioSize() const;												// выдача размера последнего чанка аудио
	void setLastChunkAudioSize(const uint32_t &lastChunkAudioSize);						// установка размера последнего чанка аудио

	uint32_t getAmountChunkAudio() const;												// выдача кол-ва чанков аудио
	void setAmountChunkAudio(const uint32_t &amountChunkAudio);							// установка кол-ва чанков аудио

	uint32_t getAmountChunkVideo() const;												// выдача кол-ва чанков видео
	void setAmountChunkVideo(const uint32_t &amountChunkVideo);							// установка кол-ва чанков видео

	uint32_t getLastChunkVideoSize() const;												// выдача размера последнего чанка видео
	void setLastChunkVideoSize(const uint32_t &lastChunkVideoSize);						// установка размера последнего чанка видео

	uint32_t getBeginOffsetFile() const;												// установка размера вырезаемого видео
	void setBeginOffsetFile(const uint32_t &beginOffsetFile);							//

	uint32_t getSizeCut() const;														// выдача размера вырезаемого видео
	void setSizeCut(const uint32_t &sizeCut);											// установка размера вырезаемого видео

private:
	//----------------------------------------------------------------------------------//
	//----------------------------приватные методы--------------------------------------//
	//----------------------------------------------------------------------------------//
	SingletonSettings() {}																// конструктор
	SingletonSettings(const SingletonSettings&) {}										// конструктор
	SingletonSettings& operator=(SingletonSettings&) {}									// перегрузка оператора присваивания

	uint32_t getOffsetAudioChunk(double fractPos);										// вычисление смещения чанка аудио
	//----------------------------------------------------------------------------------//
	//----------------------------приватные атрибуты------------------------------------//
	//----------------------------------------------------------------------------------//
	uint32_t    m_beginTime{ 0 };														// время начала обработки
	uint32_t	m_endTime{ 0 };															// время конца обработки

	uint32_t	m_newDuration{ 0 };														// продолжительность выходного видео

	uint32_t	m_timeScaleVideo{ 0 };;													// масштабирование видео
	uint32_t	m_timeScaleAudio{ 0 };													// масштабирование аудио

	uint32_t	m_deltaAudio{ 0 };														// дельта аудио
	uint32_t	m_deltaVideo{ 0 };														// дельта видео
	uint32_t	m_delta{ 0 };															// дельта ключевого кадра видео 

	uint32_t	m_beginOffsetAudio{ 0 };												// начальный сдвиг аудио
	uint32_t	m_endOffsetAudio{ 0 };													// конечный сдвиг аудио

	uint32_t	m_beginOffsetVideo{ 0 };												// начальный сдвиг видео
	uint32_t	m_endOffsetVideo{ 0 };													// конечный сдвиг видео

	uint32_t    m_beginOffsetFile{ 0 };													// сдвиг отнсительно начала файла для вырезания
	uint32_t    m_sizeCut{ 0 };															// размер выходного видео

	uint32_t	m_idBeginChunkVideo{ 0 };												// ID чанка видео на начало обработки
	uint32_t	m_idEndChunkVideo{ 0 };													// ID чанка видео на конец обработки
	uint32_t	m_idBegChunkWithIFrame{ 0 };											// ID чанка ключевого кадра видео на начало обработки
	uint32_t	m_idEndChunkWithIFrame{ 0 };											// ID чанка ключевого кадра видео на конец обработки 

	uint32_t	m_idBeginChunkAudio{ 0 };												// ID чанка аудио на начало обработки
	uint32_t	m_idEndChunkAudio{ 0 };													// ID чанка аудио на конец обработки

	uint32_t	m_firstChunkAudioSize{ 0 };												// размер первого чанка аудио
	uint32_t	m_lastChunkAudioSize{ 0 };												// размер последнего чанка аудио
	uint32_t	m_lastChunkVideoSize{ 0 };												// размер первого чанка видео

	uint32_t	m_amountChunkAudio{ 0 };												// кол-во чанков аудио 
	uint32_t	m_amountChunkVideo{ 0 };												// кол-во чанков видео

	uint32_t m_offsetStartAudioPos{ 0 };												// сдвиг позиции начала аудио
	uint32_t m_offsetEndtAudioPos{ 0 };													// сдвиг позиции конца аудио

	std::vector<uint32_t>* pm_chunkOffsetAudio{ nullptr };								// массив сдвигов аудио из stco
	std::vector<uint32_t>* pm_chunkOffsetVideo{ nullptr };								// массив сдвигов видео из stco
};

#endif
