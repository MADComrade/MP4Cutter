#ifndef STSD_H
#define STSD_H
#include "atom.h"

class STSD:public Atom
{
public:
    STSD();
    ~STSD();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    virtual void writeAtom(StreamWriter& stream);
private:
    std::vector<uint8_t> m_data;    
};

#endif // STSD_H
