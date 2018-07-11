#ifndef STBL_H
#define STBL_H

#include "atom.h"
#include "stsc.h"
#include "stsd.h"
#include "stss.h"
#include "stsz.h"
#include "stco.h"
#include "stts.h"

#include <map>
#include <memory>


class STBL:public Atom
{
public:
    STBL();
    STBL(TRAK_TYPE type);
    ~STBL();    
    void setTrakType(TRAK_TYPE type);
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    virtual void prepareData();
    virtual void writeAtom(StreamWriter& stream);
protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    void buildAndParseAtom(std::string atomName, StreamReader& stream, uint32_t& startPos);
    TRAK_TYPE m_trakType{TRAK_TYPE::VIDEO};
    std::unique_ptr<STSC> m_stsc;
    std::unique_ptr<STSD> m_stsd;
    std::unique_ptr<STSS> m_stss;
    std::unique_ptr<STSZ> m_stsz;
    std::unique_ptr<STCO> m_stco;
    std::unique_ptr<STTS> m_stts;
    std::map<std::string,uint32_t> m_mapperAtomBuild;
};

#endif // STBL_H
