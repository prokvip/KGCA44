#pragma once
#include <assert.h>
#include <stdio.h>
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
};

enum WORK {
    PRINT, NEW_DATA, FILE_SAVE, FILE_LOAD,
    UPDATE, FIND, DELETE, SORT, SAMPLE_DATA, EXIT = 99
};