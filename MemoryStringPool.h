// MemoryStringPool.h: interface for the CMemoryStringPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYSTRINGPOOL_H__833FB9C7_68F9_4E62_94EB_AAA3BD45D625__INCLUDED_)
#define AFX_MEMORYSTRINGPOOL_H__833FB9C7_68F9_4E62_94EB_AAA3BD45D625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryStringPool : public CMemoryStringContainer
{
  public:
    CMemoryStringPool(const char* i_panStringName = "CMemoryStringPool");
    virtual ~CMemoryStringPool();

    // Array creation
    virtual int   CreateBuffer(int i_nBufferSize, BOOL i_bZeroMemory = TRUE);

    // String addition
    virtual int   AddStringHead(const char* i_panStringBuffer, bool i_bForce = false);
    virtual int   AddStringTail(const char* i_panStringBuffer, bool i_bForce = false);
    virtual void  operator +=  (const char* i_panStringBuffer);

    // String insertion
    virtual int   InsertStringAt   (const char* i_panStringBuffer, int i_nStringIndex);
    virtual int   InsertStringAfter(const char* i_panStringBuffer, int i_nStringIndex);
    virtual int   InsertStringDicho(const char* i_panStringBuffer, int i_nByteToCompare = 4, BOOL i_bBigEndian = FALSE);

    // String removation
    virtual void  RemoveStringAll  (void);
    virtual int   RemoveStringHead (void);
    virtual int   RemoveStringTail (void);
    virtual int   RemoveStringAt   (int i_nStringIndex);
    virtual int   RemoveStringAfter(int i_nStringIndex);
    virtual void  operator -=      (int i_nStringIndex);

    // Simple stack mimick
    virtual int   Push(const char* i_panStringBuffer);
    virtual int   Push(void);
    virtual int   Pop (char* o_panStringBuffer);
    virtual char* Pop (void);

    // String content manipulator
    virtual int   GetStringLength(const char* i_panStringBuffer);
    virtual int   GetStringLength(int i_nStringIndex);
    virtual int   GetStringIndex (const char* i_panStringBuffer, int i_nStringLenght = -1);
    virtual int   GetStringCompare(const char* i_panStringFrom, const char* i_panStringTo);
    virtual int   GetStringDiff(const char* i_panStringFrom, const char* i_panStringTo);

    // Slot information
    virtual int   GetStringCount(int i_nStringIndex);
    virtual void  SetStringCount(int i_nStringIndex, unsigned int i_nStringCount);
    virtual int   IncStringCount(int i_nStringIndex);
    virtual int   DecStringCount(int i_nStringIndex);

    virtual int   GetStringData(int i_nStringIndex);
    virtual void  SetStringData(int i_nStringIndex, int i_nStringData);

    virtual int   GetStringHole(int i_nStringIndex);
    
    virtual int   GetStringSize(int i_nStringIndex);

    // String content manipulator
    virtual int   GetStringBuffer(      char* o_panStringBuffer, int i_nStringIndex);
    virtual int   SetStringBuffer(const char* i_panStringBuffer, int i_nStringIndex);

    // String address fetcher
    virtual char* GetStringPointer(int i_nStringIndex);
    virtual char* operator []     (int i_nStringIndex);

    // String tool
    virtual void  Sort(void);
    virtual void  RemoveOnCountThreshold(int i_nNodeCountMax);

    // Pool information
    virtual int   GetBufferSize(void);
    virtual int   GetBufferFree(void);

    // String information
    virtual int   GetStringCount(const char* i_panStringBuffer);
    virtual int   GetStringTail(void);
    virtual int   GetStringNumber(void);
    virtual int   GetStringSize(void);
    virtual int   GetStringFree(void);

    // Disk operation
    virtual bool  SaveToFile  (CFile& i_roFileOut);
    virtual bool  LoadFromFile(CFile& i_roFileIn);

  protected :
    virtual void  _DeleteBuffer(void);
    virtual sMBP* _ExpandBuffer(int i_nByteReach);
    virtual int   _ReduceBuffer(int i_nByteReach);
    virtual sMBP* _LocateBuffer(int i_nByteIndex);

    virtual void  _EncodeString(sMSP& o_rsStringPointer, const char* i_panStringBuffer, int i_nStringSize = -1, bool i_bStuffing = false);
    virtual int   _StreamString(const char* i_panStringBuffer, unsigned short  i_nStringHole, unsigned short  i_nStringSize, int i_nStringLocation = -1);
    virtual char* _LocateString(int i_nStringIndex);
    virtual int   _SearchString(const char* i_panStringBuffer, int i_nStringIndex = -1);

    // Hash functions library
    unsigned int _HashRS  (const char* i_panStringBuffer);
    unsigned int _HashJS  (const char* i_panStringBuffer);
    unsigned int _HashPJW (const char* i_panStringBuffer);
    unsigned int _HashELF (const char* i_panStringBuffer);
    unsigned int _HashBKDR(const char* i_panStringBuffer);
    unsigned int _HashSDBM(const char* i_panStringBuffer);
    unsigned int _HashDJB (const char* i_panStringBuffer);
    unsigned int _HashDEK (const char* i_panStringBuffer);
    unsigned int _HashAP  (const char* i_panStringBuffer);
};

#endif // !defined(AFX_MEMORYSTRINGPOOL_H__833FB9C7_68F9_4E62_94EB_AAA3BD45D625__INCLUDED_)
