// MemoryArray.h: interface for the CMemoryArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYARRAY_H__1031B287_F322_47BC_A498_143DE9A30A00__INCLUDED_)
#define AFX_MEMORYARRAY_H__1031B287_F322_47BC_A498_143DE9A30A00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryArray : public CMemoryPool
{ // Fragmented sorted memory buffer
  public :
            CMemoryArray(const char* i_panStringName = "CMemoryArray");

  protected :
    // These methods have changed from CMemoryPool
    virtual sMBP* _ExpandBuffer(int i_nSlotReach);
    virtual int   _ReduceBuffer(int i_nSlotReach);
};

#endif // !defined(AFX_MEMORYARRAY_H__1031B287_F322_47BC_A498_143DE9A30A00__INCLUDED_)
