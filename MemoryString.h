// MemoryString.h: interface for the CMemoryString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYSTRING_H__1E69930E_C523_440C_8FEA_CF5A53088312__INCLUDED_)
#define AFX_MEMORYSTRING_H__1E69930E_C523_440C_8FEA_CF5A53088312__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryString : public ClassUtils
{
  public:
    CMemoryString();
    virtual ~CMemoryString();

/*
    CMemoryString();
    CMemoryString(CMemoryString& stringSrc);
    CMemoryString(char ch, int nRepeat = 1);
    CMemoryString(char* string);
    CMemoryString(char* string, int nLength);
    CMemoryString(int num);
    CMemoryString(double num);

    int   GetLength();
    bool  IsEmpty();
    void  Empty();
    char  GetAt(int nIndex);

    char  operator [] (int nIndex);
    char& operator [] (int nIndex);
    
    void  SetAt(int nIndex, char ch);

    operator char* ();
    operator char* ();

    CMemoryString& operator =(CMemoryString& stringSrc);
    CMemoryString& operator =(char ch);
    CMemoryString& operator =(char* string);
    CMemoryString& operator =(int num);
    CMemoryString& operator =(double num);
    CMemoryString& operator =(float num);

    CMemoryString& operator +=(CMemoryString& string);
    CMemoryString& operator +=(char ch);
    CMemoryString& operator +=(char* string);
    CMemoryString& operator +=(int num);
    CMemoryString& operator +=(double num);
    CMemoryString& operator +=(float num);

    void Cat(char ch);
    void Cat(char* string);
    void Cat(CMemoryString& string);

    CMemoryString operator + (CMemoryString& string1, CMemoryString& string2);
    CMemoryString operator + (CMemoryString& string, char ch);
    CMemoryString operator + (char ch, CMemoryString& string);
    CMemoryString operator + (CMemoryString& string1, char* string2);
    CMemoryString operator + (char* string1, CMemoryString& string2);
    CMemoryString operator + (int num, CMemoryString& string);
    CMemoryString operator + (CMemoryString& string, int num);

    bool operator == (CMemoryString& s1, CMemoryString& s2);
    bool operator == (CMemoryString& s1, char* s2);
    bool operator == (char* s1, CMemoryString& s2);

    bool operator != (CMemoryString& s1, CMemoryString& s2);
    bool operator != (CMemoryString& s1, char* s2);
    bool operator != (char* s1, CMemoryString& s2);
    bool operator != (CMemoryString& s1, char* s2);

    bool operator < (CMemoryString& s1, CMemoryString& s2);
    bool operator < (CMemoryString& s1, char* s2);
    bool operator < (char* s1, CMemoryString& s2);

    bool operator > (CMemoryString& s1, CMemoryString& s2);
    bool operator > (CMemoryString& s1, char* s2);
    bool operator > (char* s1, CMemoryString& s2);

    bool operator <= (CMemoryString& s1, CMemoryString& s2);
    bool operator <= (CMemoryString& s1, char* s2);
    bool operator <= (char* s1, CMemoryString& s2);

    bool operator >= (CMemoryString& s1, CMemoryString& s2);
    bool operator >= (CMemoryString& s1, char* s2);
    bool operator >= (char* s1, CMemoryString& s2);

    int Compare(char* string);
    int Compare(CMemoryString& string);
    int CompareNoCase(char* string);
    int Collate(char* string);
    int CollateNoCase(char* string);

    int Close(char* string);

    bool CompareGlob(CMemoryString& glob);

    CMemoryString Mid(int nFirst);
    CMemoryString Mid(int nFirst, int nCount);
    CMemoryString Left(int nCount);
    CMemoryString Right(int nCount);
    CMemoryString SpanIncluding(char* string);
    CMemoryString SpanExcluding(char* string);

    char* ToChar(int nStart = 0,int nCount = -1);

    int    ToInt(int nStart = 0);
    double ToDouble( int nStart = 0 );

    void MakeUpper();
    void MakeLower();
    void MakeReverse();

    int Replace(char chOld, char chNew);
    int Replace(char* stringOld, char* stringNew);
    int Remove(char ch);
    int Insert(int nIndex, char ch);
    int Insert(int nIndex, char* string);
    int Delete(int nIndex, int nCount = 1);

    void Format(char* sFormat, ...);

    void Trim();
    void Trim(char ch);
    void Trim(char* string);

    void TrimLeft();
    void TrimLeft(char ch);
    void TrimLeft(char* string);

    void TrimRight();
    void TrimRight(char ch);
    void TrimRight(char* string);

    int Find(char ch, int nStart = 0);
    int Find(char* string, int nStart = 0);

    int ReverseFind(char ch);
    int ReverseFind(char* string);
    int FindOneOf  (char* string);

    char* GetBuffer(int nMinBufLength = -1);
    void  ReleaseBuffer(int nNewLength = -1);
    char* GetBufferSetLength(int nNewLength);
    void  FreeExtra();
    char* LockBuffer();
    void  UnlockBuffer();
*/
};

#endif // !defined(AFX_MEMORYSTRING_H__1E69930E_C523_440C_8FEA_CF5A53088312__INCLUDED_)
