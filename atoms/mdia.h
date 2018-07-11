#ifndef MDIA_H
#define MDIA_H
#include "atom.h"
#include <map>
#include <memory>
#include "mdhd.h"
#include "hdlr.h"
#include "minf.h"

class MDIA:public Atom
{
public:
    MDIA();
    ~MDIA();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    TRAK_TYPE getTrakType();
    virtual void prepareData();
    virtual void writeAtom(StreamWriter& stream);
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    std::unique_ptr<MDHD> m_mdhd;
    std::unique_ptr<HDLR> m_hdlr;
    std::unique_ptr<MINF> m_minf;
};

#endif // MDIA_H
