#ifndef ATOM_H
#define ATOM_H
#include "../interfaces/parserinterface.h"
#include "../interfaces/callbackinterface.h"
#include "../streamwriter.h"
#include "../SingletonSettings.h"

const std::string MOOV_NAME = "moov";
const std::string MVHD_NAME = "mvhd";
const std::string TRAK_NAME = "trak";
const std::string TKHD_NAME = "tkhd";
const std::string MDIA_NAME = "mdia";
const std::string MDHD_NAME = "mdhd";
const std::string HDLR_NAME = "hdlr";
const std::string MINF_NAME = "minf";
const std::string VMHD_NAME = "vmhd";
const std::string SMHD_NAME = "smhd";
const std::string DINF_NAME = "dinf";
const std::string STBL_NAME = "stbl";
const std::string STSC_NAME = "stsc";
const std::string STTS_NAME = "stts";
const std::string STSD_NAME = "stsd";
const std::string STSS_NAME = "stss";
const std::string STCO_NAME = "stco";
const std::string STSZ_NAME = "stsz";
const std::string FTYP_NAME = "ftyp";
const std::string MDAT_NAME = "mdat";

const uint32_t MOOV_DIG_NAME = 0x6D6F6F76;
const uint32_t MVHD_DIG_NAME = 0X6D766864;
const uint32_t TRAK_DIG_NAME = 0X7472616B;
const uint32_t TKHD_DIG_NAME = 0X746B6864;
const uint32_t MDIA_DIG_NAME = 0X6D646961;
const uint32_t MDHD_DIG_NAME = 0X6D646864;
const uint32_t HDLR_DIG_NAME = 0X68646C72;
const uint32_t MINF_DIG_NAME = 0X6D696E66;
const uint32_t VMHD_DIG_NAME = 0X766D6864;
const uint32_t SMHD_DIG_NAME = 0X736D6864;
const uint32_t DINF_DIG_NAME = 0X64696E66;
const uint32_t STBL_DIG_NAME = 0X7374626C;
const uint32_t STSC_DIG_NAME = 0X73747363;
const uint32_t STTS_DIG_NAME = 0X73747473;
const uint32_t STSD_DIG_NAME = 0X73747364;
const uint32_t STSS_DIG_NAME = 0X73747373;
const uint32_t STCO_DIG_NAME = 0X7374636F;
const uint32_t STSZ_DIG_NAME = 0X7374737A;
const uint32_t FTYP_DIG_NAME = 0X66747970;
const uint32_t MDAT_DIG_NAME = 0X6D646174;

const uint32_t OFFSET_TITLE = 8;
const uint32_t BYTE32 = 4;
const int LV1 = 0;
const int LV2 = 10;
const int LV3 = 15;
const int LV4 = 20;
const int LV5 = 25;
const int LV6 = 30;

const std::string VIDE = "vide";
const std::string SOUN = "soun";
const std::string HINT = "hint";

enum class TRAK_TYPE{
    VIDEO,
    AUDIO,
    HINT
};

struct StscData
{
    uint32_t m_firstChunk{0};
    uint32_t m_samplesPerChunk{0};
    uint32_t m_samplesIndex{0};
};

struct SttsData
{
    uint32_t m_sampleCount{0};
    uint32_t m_sampleDelta{0};
};

class Atom : public ParserInterface, public CallbackInterface
{
public:
    Atom(std::string atomTextName, uint32_t atomDigitName);
    ~Atom();
    uint32_t offset() const;
    uint32_t size() const;
    uint32_t atomDigitName() const;
    std::string atomTextName() const;
    virtual void parse(StreamReader& stream, uint32_t& startPos)=0;
    virtual void writeAtom(StreamWriter& stream);
    void setCallback(CallbackInterface *callback);
    virtual void prepareData(){}

protected:
    void printAtomName(int lv);
    void setOffset(const uint32_t &offset);
    void setSize(const uint32_t &size);
    virtual void resizeAtom(uint32_t size, DIRECT_RESIZE direction);
    CallbackInterface *callback() const;
    void setAtomDigitName(const uint32_t &atomDigitName);
    void setAtomTextName(const std::string &atomTextName);

    CallbackInterface* m_callback{nullptr};
    uint32_t m_offset{0};
    uint32_t m_size{0};
    uint32_t m_atomDigitName{0};
    std::string m_atomTextName{0};
    SingletonSettings& m_singletonSettings{SingletonSettings::getInstance()};
};
#endif // ATOM_H
