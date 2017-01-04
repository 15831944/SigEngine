// MemoryContainer.h: interface for the CMemoryContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYCONTAINER_H__F5D7C35E_A5E7_4885_BFFF_9AC4510B5075__INCLUDED_)
#define AFX_MEMORYCONTAINER_H__F5D7C35E_A5E7_4885_BFFF_9AC4510B5075__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryContainer : public ClassUtils
{
  public:
            CMemoryContainer(const char* i_panStringName = "CMemoryContainer");
    virtual ~CMemoryContainer() = 0;

    // Array creation
    virtual int   CreateBuffer(int i_nSlotSize, int i_nSlotNumber, BOOL i_bZeroMemory = TRUE) = 0;

    // Slot addition
    virtual int   AddSlotHead(void* i_panSlotBuffer) = 0;
    virtual int   AddSlotTail(void* i_panSlotBuffer, int i_nSizeData = -1) = 0;
    virtual void  operator +=(void* i_panSlotBuffer) = 0;

    // Slot insertion
    virtual int   InsertSlotAt   (void* i_panSlotBuffer, int i_nSlotIndex) = 0;
    virtual int   InsertSlotAfter(void* i_panSlotBuffer, int i_nSlotIndex) = 0;
    virtual int   InsertSlotDicho(void* i_panSlotBuffer, int i_nByteToCompare = 4, BOOL i_bBigEndian = FALSE) = 0;

    // Slot removation
    virtual void  RemoveSlotAll  (void) = 0;
    virtual int   RemoveSlotHead (void) = 0;
    virtual int   RemoveSlotTail (void) = 0;
    virtual int   RemoveSlotAt   (int i_nSlotIndex) = 0;
    virtual int   RemoveSlotAfter(int i_nSlotIndex) = 0;
    virtual void  operator -=    (int i_nSlotIndex) = 0;

    // Simple stack mimick
    virtual int   Push(void* i_panSlotBuffer) = 0;
    virtual int   Push(void) = 0;
    virtual int   Pop (void* o_panSlotBuffer) = 0;
    virtual void* Pop (void) = 0;

    // Slot content manipulator
    virtual int   GetSlotBuffer(void* o_panSlotBuffer, int i_nSlotIndex) = 0;
    virtual int   SetSlotBuffer(void* i_panSlotBuffer, int i_nSlotIndex) = 0;

    // Slot address fetcher
    virtual void* GetSlotPointer(int i_nSlotIndex) = 0;
    virtual void* operator []   (int i_nSlotIndex) = 0;

    // Pool information
    virtual int   GetBufferSize(void) = 0;
    virtual int   GetBufferFree(void) = 0;

    // Slot information
    virtual int   GetSlotTail(void) = 0;
    virtual int   GetSlotTotal(void) = 0;
    virtual int   GetSlotHole(void) = 0;
    virtual int   GetSlotSize(void) = 0;
    virtual int   GetSlotFree(void) = 0;

    // Slot tool
    virtual void  SortInt  (int i_nIntToCompare   = 1, bool i_bSignedInt = true, bool i_bBigEndian = false) = 0;
    virtual void  SortFloat(int i_nFloatToCompare = 1) = 0;
    virtual void  SortSwap(void) = 0;
    virtual int   GetSlotSorted(int i_nNodeIndex) = 0;

    // Disk operation
    virtual bool  SaveToFile  (CFile& i_roFileOut) = 0;
    virtual bool  LoadFromFile(CFile& i_roFileIn) = 0;

  protected :
    typedef struct sMemoryBlockPointer
    { int   nBufferSize
    ; char* panBuffer
    ; char* panBufferPrev
    ; char* panBufferNext
    ; int   nSlotBegin
    ; int   nSlotHead
    ; int   nSlotTail
    ; int   nSlotEnd
    ;} sMBP, *psMBP; // 32 bytes

  protected :
    virtual void  _DeleteBuffer(void) = 0;
    virtual sMBP* _ExpandBuffer(int i_nSlotReach) = 0;
    virtual int   _ReduceBuffer(int i_nSlotReach) = 0;
    virtual sMBP* _LocateBuffer(int i_nSlotIndex) = 0;

    // Sort
    virtual void  _SwapSlot(int i_nSlotSrc, int i_nSlotDst) = 0;
    virtual void  _ResetIndices(void) = 0;
    virtual bool  _ResizeIndices(unsigned int i_nArraySize) = 0;

  protected :
    int   mp_nSlotSizeHead; // Size of slot header
    int   mp_nSlotSizeHole; // Size of slot space
    int   mp_nSlotSizeData; // Size of slot data

    BOOL  mp_bZeroMemory;   // Zero buffer memory on new buffer allocation

    sMBP* mp_psBufferFirst; // Buffer First
    sMBP* mp_psBufferTail;  // Buffer Tail
    sMBP* mp_psBufferPrev;  // Previously requested buffer

    // Sort
    unsigned int   mp_anHistogram[256*4];
    unsigned int   mp_anOffset[256];
    unsigned int   mp_nIndiceSizeCurrent;
    unsigned int   mp_nIndiceSizePrevious;
    unsigned int*  mp_panIndiceArray1;
    unsigned int*  mp_panIndiceArray2;
};

#endif // !defined(AFX_MEMORYCONTAINER_H__F5D7C35E_A5E7_4885_BFFF_9AC4510B5075__INCLUDED_)
