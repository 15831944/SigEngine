// MemoryStringContainer.h: interface for the CMemoryStringContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYSTRINGCONTAINER_H__75A3FAEC_285E_4573_A02E_4785F7481887__INCLUDED_)
#define AFX_MEMORYSTRINGCONTAINER_H__75A3FAEC_285E_4573_A02E_4785F7481887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

static unsigned char g_panAccent[256+1] = "                                 !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂∑∏π∫ªºΩæø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄€‹›ﬁﬂ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛ˇ";
static unsigned char g_panNoAcce[256+1] = "                                 !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂∑∏π∫ªºΩæøAAAAAAACEEEEIIIIDNOOOOOXOUUUUYPBaaaaaaaceeeeiiiidnoooooxouuuuypy";
static unsigned char g_panNormal[256+1] = "                                       '     -./0123456789       ABCDEFGHIJKLMNOPQRSTUVWXYZ      abcdefghijklmnopqrstuvwxyz                                                                     AAAAAAACEEEEIIIIDNOOOOOXOUUUUYPBaaaaaaaceeeeiiiidnoooooxouuuuypy";
static unsigned char g_panNoCase[256+1] = "                                       '     -./0123456789       ABCDEFGHIJKLMNOPQRSTUVWXYZ      ABCDEFGHIJKLMNOPQRSTUVWXYZ                                                                     AAAAAAACEEEEIIIIDNOOOOOXOUUUUYPBAAAAAAACEEEEIIIIDNOOOOOXOUUUUYPY";

//#define TEST_NEWMETHOD

class EXPSIGENGINE CMemoryStringContainer : public ClassUtils
{
  public:
    CMemoryStringContainer(const char* i_panStringName = "CMemoryStringContainer");
    virtual ~CMemoryStringContainer();

    // Array creation
    virtual int   CreateBuffer(int i_nBufferSize, BOOL i_bZeroMemory = TRUE) = 0;

    // String addition
    virtual int   AddStringHead(const char* i_panStringBuffer, bool i_bForce = false) = 0;
    virtual int   AddStringTail(const char* i_panStringBuffer, bool i_bForce = false) = 0;
    virtual void  operator +=  (const char* i_panStringBuffer) = 0;

    // String insertion
    virtual int   InsertStringAt   (const char* i_panStringBuffer, int i_nStringIndex) = 0;
    virtual int   InsertStringAfter(const char* i_panStringBuffer, int i_nStringIndex) = 0;
    virtual int   InsertStringDicho(const char* i_panStringBuffer, int i_nByteToCompare = 4, BOOL i_bBigEndian = FALSE) = 0;

    // String removation
    virtual void  RemoveStringAll  (void) = 0;
    virtual int   RemoveStringHead (void) = 0;
    virtual int   RemoveStringTail (void) = 0;
    virtual int   RemoveStringAt   (int i_nStringIndex) = 0;
    virtual int   RemoveStringAfter(int i_nStringIndex) = 0;
    virtual void  operator -=      (int i_nStringIndex) = 0;

    // Simple stack mimick
    virtual int   Push(const char* i_panStringBuffer) = 0;
    virtual int   Push(void) = 0;
    virtual int   Pop (char* o_panStringBuffer) = 0;
    virtual char* Pop (void) = 0;

    // String content manipulator
    virtual int   GetStringLength(const char* i_panStringBuffer) = 0;
    virtual int   GetStringLength(int i_nStringIndex) = 0;
    virtual int   GetStringIndex (const char* i_panStringBuffer, int i_nStringLenght = -1) = 0;
    virtual int   GetStringCompare(const char* i_panStringFrom, const char* i_panStringTo) = 0;
    virtual int   GetStringDiff(const char* i_panStringFrom, const char* i_panStringTo) = 0;

    // String information
    virtual int   GetStringCount(int i_nStringIndex) = 0;
    virtual void  SetStringCount(int i_nStringIndex, unsigned int i_nStringCount) = 0;
    virtual int   IncStringCount(int i_nStringIndex) = 0;
    virtual int   DecStringCount(int i_nStringIndex) = 0;

    virtual int   GetStringData(int i_nStringIndex) = 0;
    virtual void  SetStringData(int i_nStringIndex, int i_nStringData) = 0;

    virtual int   GetStringHole(int i_nStringIndex) = 0;
    
    virtual int   GetStringSize(int i_nStringIndex) = 0;

    // String content manipulator
    virtual int   GetStringBuffer(      char* o_panStringBuffer, int i_nStringIndex) = 0;
    virtual int   SetStringBuffer(const char* i_panStringBuffer, int i_nStringIndex) = 0;

    // String address fetcher
    virtual char* GetStringPointer(int i_nStringIndex) = 0;
    virtual char* operator []     (int i_nStringIndex) = 0;

    // String tool
    virtual void Sort(void) = 0;
    virtual void RemoveOnCountThreshold(int i_nNodeCountMax) = 0;

    // Pool information
    virtual int   GetBufferSize(void) = 0;
    virtual int   GetBufferFree(void) = 0;

    // String information
    virtual int   GetStringCount(const char* i_panStringBuffer) = 0;
    virtual int   GetStringTail(void) = 0;
    virtual int   GetStringNumber(void) = 0;
    virtual int   GetStringSize(void) = 0;
    virtual int   GetStringFree(void) = 0;

    // Disk operation
    virtual bool  SaveToFile  (CFile& i_roFileOut) = 0;
    virtual bool  LoadFromFile(CFile& i_roFileIn) = 0;

  protected :
    typedef struct sMemoryBlockPointer
    { int   nBufferSize
    ; char* panBuffer
    ; char* panBufferPrev
    ; char* panBufferNext
    ; int   nBufferBegin
    ; int   nBufferHead
    ; int   nBufferTail
    ; int   nBufferEnd
    ;} sMBP, *psMBP; // 32 bytes

    typedef struct sMemoryStringPointer
#ifndef TEST_NEWMETHOD
    { int nLocation   // String location in the buffer
#else // TEST_NEWMETHOD
    { int nLength     // String length
#endif // TEST_NEWMETHOD
    ; int nHashRaw    // Raw string hashing
    ; int nHashCase   // Case sensitive hashing
    ; int nHashNoCase // Case insensitive hashing
    ;} sMSP, *psMSP; // 16 bytes

  protected :
    virtual void  _DeleteBuffer(void) = 0;
    virtual sMBP* _ExpandBuffer(int i_nByteReach) = 0;
    virtual int   _ReduceBuffer(int i_nByteReach) = 0;
    virtual sMBP* _LocateBuffer(int i_nByteIndex) = 0;

    virtual void  _EncodeString(sMSP& o_rsStringPointer, const char* i_panStringBuffer, int i_nStringSize = -1, bool i_bStuffing = false) = 0;
    virtual int   _StreamString(const char* i_panStringBuffer, unsigned short  i_nStringHole, unsigned short  i_nStringSize, int i_nStringLocation = -1) = 0;
    virtual char* _LocateString(int i_nStringIndex) = 0;
    virtual int   _SearchString(const char* i_panStringBuffer, int i_nStringIndex = -1) = 0;

  protected :
    BOOL  mp_bZeroMemory;   // Zero buffer memory on new buffer alloction

    sMBP* mp_psBufferFirst; // Buffer First
    sMBP* mp_psBufferTail;  // Buffer Tail
    sMBP* mp_psBufferPrev;  // Previously requested buffer

    // Array of string slots
#ifndef FAVOR_REDBLACK
    CMemoryTree         mp_oTreeString;
#else
    CMemoryTreeRedBlack mp_oTreeString;
#endif // FAVOR_REDBLACK
};

#endif // !defined(AFX_MEMORYSTRINGCONTAINER_H__75A3FAEC_285E_4573_A02E_4785F7481887__INCLUDED_)
