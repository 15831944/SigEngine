// MemoryPool.h: interface for the CMemoryPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYPOOL_H__4C2ACB8E_7E23_4AF1_97CB_7B91BAEFADBE__INCLUDED_)
#define AFX_MEMORYPOOL_H__4C2ACB8E_7E23_4AF1_97CB_7B91BAEFADBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryPool : public CMemoryContainer
{ // Continuous sorted memory buffer
  public :
            CMemoryPool(const char* i_panStringName = "CMemoryPool");
    virtual ~CMemoryPool(void);

    // Pool creation
    virtual int   CreateBuffer(int i_nSlotSize, int i_nSlotNumber, BOOL i_bZeroMemory = TRUE);

    // Slot addition
    virtual int   AddSlotHead(void* i_panSlotBuffer);
    virtual int   AddSlotTail(void* i_panSlotBuffer, int i_nSizeData = -1);
    virtual void  operator +=(void* i_panSlotBuffer);

    // Slot insertion
    virtual int   InsertSlotAt   (void* i_panSlotBuffer, int i_nSlotIndex);
    virtual int   InsertSlotAfter(void* i_panSlotBuffer, int i_nSlotIndex);
    virtual int   InsertSlotDicho(void* i_panSlotBuffer, int i_nByteToCompare = 4, BOOL i_bBigEndian = FALSE);

    // Slot removation
    virtual void  RemoveSlotAll  (void);
    virtual int   RemoveSlotHead (void);
    virtual int   RemoveSlotTail (void);
    virtual int   RemoveSlotAt   (int i_nSlotIndex);
    virtual int   RemoveSlotAfter(int i_nSlotIndex);
    virtual void  operator -=    (int i_nSlotIndex);

    // Simple stack mimick
    virtual int   Push(void* i_panSlotBuffer);
    virtual int   Push(void);
    virtual int   Pop (void* o_panSlotBuffer);
    virtual void* Pop (void);

    // Slot content manipulator
    virtual int   GetSlotBuffer(void* o_panSlotBuffer, int i_nSlotIndex);
    virtual int   SetSlotBuffer(void* i_panSlotBuffer, int i_nSlotIndex);

    // Slot address fetcher
    virtual void* GetSlotPointer(int i_nSlotIndex);
    virtual void* operator []   (int i_nSlotIndex);

    // Pool information
    virtual int   GetBufferSize(void);
    virtual int   GetBufferFree(void);

    // Slot information
    virtual int   GetSlotTail(void);
    virtual int   GetSlotTotal(void);
    virtual int   GetSlotHole(void);
    virtual int   GetSlotSize(void);
    virtual int   GetSlotFree(void);

    // Slot tool
    virtual void  SortInt  (int i_nIntToCompare   = 1, bool i_bSignedInt = true, bool i_bBigEndian = false);
    virtual void  SortFloat(int i_nFloatToCompare = 1);
    virtual void  SortSwap(void);
    virtual int   GetSlotSorted(int i_nNodeIndex);

    // Disk operation
    virtual bool  SaveToFile  (CFile& i_roFileOut);
    virtual bool  LoadFromFile(CFile& i_roFileIn);

  protected :
    virtual void  _DeleteBuffer(void);
    virtual sMBP* _ExpandBuffer(int i_nSlotReach);
    virtual int   _ReduceBuffer(int i_nSlotReach);
    virtual sMBP* _LocateBuffer(int i_nSlotIndex);

    // Sort
    virtual void  _SwapSlot(int i_nSlotSrc, int i_nSlotDst);
    virtual void  _ResetIndices(void);
    virtual bool  _ResizeIndices(unsigned int i_nArraySize);
};

#endif // !defined(AFX_MEMORYPOOL_H__4C2ACB8E_7E23_4AF1_97CB_7B91BAEFADBE__INCLUDED_)
