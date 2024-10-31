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
struct TNode
{
    TCharacter data;
    int     iKey;
    TNode* pNext;
    TNode* pPrev;
    // 고유한 키 생성
    static  unsigned int iKeyIndex;
};
struct TNodeCharacter
{
    TCharacter data;
    int     iKey;
    TNodeCharacter* pNext;
    TNodeCharacter* pPrev;
    // 고유한 키 생성
    static  unsigned int iKeyIndex;
};
struct TNodeStudent
{
    TStudent data;
    int     iKey;
    TNodeStudent* pNext;
    TNodeStudent* pPrev;
    // 고유한 키 생성
    static  unsigned int iKeyIndex;
};
enum WORK {
    PRINT, NEW_DATA, FILE_SAVE, FILE_LOAD,
    UPDATE, FIND, DELETE, SORT, SAMPLE_DATA, EXIT = 99
};