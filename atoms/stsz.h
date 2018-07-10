#ifndef STSZ_H
#define STSZ_H

#include "atom.h"

class STSZ:public Atom
{
public:
    STSZ();
    ~STSZ();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    virtual void writeAtom(StreamWriter& stream);
    void prepareDataForWrite(uint32_t begTime, uint32_t endTime, uint32_t delta, TRAK_TYPE type=TRAK_TYPE::VIDEO);
    uint32_t getAmountChunks()const;
    uint32_t getEndChunkSize()const;
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    std::vector<uint32_t> m_chunkSize;
    uint32_t m_verFlag{0};
    uint32_t m_sampleSize{0};
    uint32_t m_amountChunk{0};

    uint32_t m_endChunkSize{0};
};

#endif // STSZ_H
