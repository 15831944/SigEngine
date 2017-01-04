// MemoryTreeSplay.h: interface for the CMemoryTreeSplay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYTREESPLAY_H__68F08BFD_9BAF_42EE_8068_E0AD4C5FE840__INCLUDED_)
#define AFX_MEMORYTREESPLAY_H__68F08BFD_9BAF_42EE_8068_E0AD4C5FE840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryTreeSplay : public CMemoryTree  
{
  public:
            CMemoryTreeSplay(const char* i_panStringName = "CMemoryTreeSplay");
};

#endif // !defined(AFX_MEMORYTREESPLAY_H__68F08BFD_9BAF_42EE_8068_E0AD4C5FE840__INCLUDED_)
