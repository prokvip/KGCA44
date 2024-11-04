#include "TCharacter.h"

std::ostream& operator <<(std::ostream& os, TStudent& a)
{
    os << a.m_iKor;
    return os;
}

std::ostream& operator <<(std::ostream& os, TCharacter& a)
{
    os << a.m_iKor;
    return os;
}