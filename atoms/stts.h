#ifndef STTS_H
#define STTS_H
#include "atom.h"
#include <vector>

class STTS: public Atom
{
public:
    STTS(TRAK_TYPE type);
    ~STTS();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    void prepareData();
    uint32_t newAmountChunk() const;
    virtual void writeAtom(StreamWriter& stream);
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    uint32_t m_verFlag{0};
    uint32_t m_amount{0};
    std::vector<SttsData> m_data;

    uint32_t m_newAmountChunk{0}; // пока 1, потом переделать на вектор
    TRAK_TYPE m_trakType{TRAK_TYPE::VIDEO};
};

#endif // STTS_H
