#ifndef MINF_H
#define MINF_H

#include "atom.h"
#include "vmhd.h"
#include "smhd.h"
#include "dinf.h"
#include "stbl.h"
#include <map>
#include <memory>

class MINF:public Atom
{
public:
    MINF(TRAK_TYPE type);
    ~MINF();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    virtual void prepareData();
    virtual void writeAtom(StreamWriter& stream);
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    TRAK_TYPE m_trakType;
    std::unique_ptr<VMHD> m_vmhd;
    std::unique_ptr<SMHD> m_smhd;
    std::unique_ptr<DINF> m_dinf;
    std::unique_ptr<STBL> m_stbl;
};

#endif // MINF_H
