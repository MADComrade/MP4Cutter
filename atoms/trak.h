#ifndef TRAK_H
#define TRAK_H

#include "atom.h"
#include "tkhd.h"
#include "mdia.h"
#include <map>
#include <memory>

class TRAK: public Atom
{
public:
    TRAK();
   ~TRAK();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    void setTrakType(TRAK_TYPE type = TRAK_TYPE::VIDEO);
    virtual void prepareData();
    virtual void writeAtom(StreamWriter& stream);
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    std::unique_ptr<TKHD> m_tkhd;
    std::unique_ptr<MDIA> m_mdia;
    TRAK_TYPE m_type;

};

#endif // TRAK_H
