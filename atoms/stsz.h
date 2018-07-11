#ifndef STSZ_H
#define STSZ_H

#include "atom.h"

class STSZ:public Atom
{
public:
    STSZ(TRAK_TYPE type);
    ~STSZ();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    virtual void writeAtom(StreamWriter& stream);
    void prepareData();
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
    TRAK_TYPE m_trakType{TRAK_TYPE::VIDEO};
};

#endif // STSZ_H
