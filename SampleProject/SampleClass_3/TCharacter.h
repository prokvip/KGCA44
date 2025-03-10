#pragma once
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>


struct TStudent
{
    char m_szName[4];
    int  m_iIndex;
    int m_iKor;
    int m_iEng;
    int m_iMat;
    int m_iTotal;
    float m_fAverage;
    friend std::ostream& operator <<(std::ostream& os, TStudent* a)
    {
        os << a->m_iKor;
        return os;
    }
    friend std::ostream& operator <<(std::ostream& os, TStudent& a)
    {
        os << a.m_iKor;
        return os;
    };
};

struct TCharacter
{
    char m_szName[4];
    int  m_iIndex;
    int m_iKor;
    int m_iEng;
    int m_iMat;
    int m_iTotal;
    float m_fAverage;
    friend std::ostream& operator <<(std::ostream& os, TCharacter* a)
    {
        os << a->m_iKor;
        return os;
    }
    friend std::ostream& operator <<(std::ostream& os, TCharacter& a)
    {
        os << a.m_iKor;
        return os;
    };
};

enum WORK {
    PRINT, NEW_DATA, FILE_SAVE, FILE_LOAD,
    UPDATE, FIND, DELETE, SORT, SAMPLE_DATA, EXIT = 99
};