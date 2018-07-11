#ifndef MOOV_H
#define MOOV_H

#include "atom.h"
#include "mvhd.h"
#include "trak.h"
#include <map>
#include <memory>


class ParserInterface;
class MOOV: public Atom
{
public:
    MOOV();
    ~MOOV();
    virtual void parse(StreamReader& stream, uint32_t& startPos);
    std::pair<uint32_t, uint32_t> prepareData(uint32_t begTime, uint32_t endTime);
    void writeAudioAndVideo(StreamWriter& outStream);

protected:
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);

private:
    std::unique_ptr<MVHD> m_mvhd;
    std::unique_ptr<TRAK> m_videoTrak;
    std::unique_ptr<TRAK> m_audioTrak;
    std::map<std::string,ParserInterface*> m_parseMap;
};

#endif // MOOV_H
