// MemoryStringArray.h: interface for the CMemoryStringArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYSTRINGARRAY_H__14880AC9_4166_45B4_BED0_E02AEA586626__INCLUDED_)
#define AFX_MEMORYSTRINGARRAY_H__14880AC9_4166_45B4_BED0_E02AEA586626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryStringArray : public CMemoryStringPool
{
  public:
    CMemoryStringArray(const char* i_panStringName = "CMemoryStringArray");

  protected :
    // These methods have changed from CMemoryStringPool
    virtual sMBP* _ExpandBuffer(int i_nSlotReach);
    virtual int   _ReduceBuffer(int i_nSlotReach);
};

#endif // !defined(AFX_MEMORYSTRINGARRAY_H__14880AC9_4166_45B4_BED0_E02AEA586626__INCLUDED_)
