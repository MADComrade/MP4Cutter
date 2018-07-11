#ifndef STCO_H
#define STCO_H
#include "atom.h"

class STCO:public Atom
{
public:
    STCO(TRAK_TYPE type);
    ~STCO();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    void prepareData();
    std::pair<uint32_t,uint32_t> getOldOffset() const;
    virtual void writeAtom(StreamWriter& stream);
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    std::vector<uint32_t> m_chunkOffset;
    uint32_t m_verFlag{0};
    uint32_t m_amountChunk{0};

    uint32_t m_startCutOffset{0};
    uint32_t m_endCutOffset{0};
    TRAK_TYPE m_trakType{TRAK_TYPE::VIDEO};
};

#endif // STCO_H
