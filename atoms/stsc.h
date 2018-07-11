#ifndef STSC_H
#define STSC_H

#include "atom.h"

class STSC:public Atom
{
public:
    STSC(TRAK_TYPE type);
    ~STSC();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    void prepareData();
    virtual void writeAtom(StreamWriter& stream);
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    uint32_t m_verFlag{0};
    uint32_t m_amount{0};
    std::vector<StscData> m_data;
    TRAK_TYPE m_trakType{TRAK_TYPE::VIDEO};
};

#endif // STSC_H
