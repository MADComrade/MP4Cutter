#include "atom.h"
#include <iomanip>
#include <iostream>

Atom::Atom(std::string atomTextName, uint32_t atomDigitName):
    ParserInterface(),
    CallbackInterface(),
    m_atomTextName(atomTextName),
    m_atomDigitName(atomDigitName)
{
}

Atom::~Atom()
{

}

uint32_t Atom::offset() const
{
    return m_offset;
}

void Atom::setOffset(const uint32_t &offset)
{
    m_offset = offset;
}

uint32_t Atom::size() const
{
    return m_size;
}

void Atom::setSize(const uint32_t &size)
{
    m_size = size;
}

uint32_t Atom::atomDigitName() const
{
    return m_atomDigitName;
}

std::string Atom::atomTextName() const
{
    return m_atomTextName;
}

void Atom::writeAtom(StreamWriter &stream)
{

}

void Atom::setCallback(CallbackInterface *callback)
{
    m_callback = callback;
}

void Atom::printAtomName(int lv)
{
    std::cout<<std::setw(lv)<<atomTextName().c_str()<<std::endl;
}

CallbackInterface *Atom::callback() const
{
    return m_callback;
}

void Atom::setAtomTextName(const std::string &atomTextName)
{
    m_atomTextName = atomTextName;
}

void Atom::setAtomDigitName(const uint32_t &atomDigitName)
{
    m_atomDigitName = atomDigitName;
}

void Atom::resizeAtom(uint32_t size, DIRECT_RESIZE direction)
{

}
