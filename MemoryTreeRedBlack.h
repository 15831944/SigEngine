// MemoryTreeRedBlack.h: interface for the CMemoryTreeRedBlack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYTREEREDBLACK_H__65D419B6_9BAE_4869_B0CF_2EDE6C7639D8__INCLUDED_)
#define AFX_MEMORYTREEREDBLACK_H__65D419B6_9BAE_4869_B0CF_2EDE6C7639D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryTreeRedBlack : public CMemoryTree
{
  public :
            CMemoryTreeRedBlack(const char* i_panStringName = "CMemoryTreeRedBlack");

    // Additionnal opertation -------------------------------------------------

    // Node addition
    virtual int  AddNode(void* i_panNodeBuffer, int i_nNodeKey, int i_nNodeData = 0, int i_nNodeParent = -1);

    // Slot removation
    virtual void RemoveNodeAt(int i_nNodeIndex = -1);

  protected :
    virtual void _RotateLeft (int i_nNodeX);
    virtual void _RotateRight(int i_nNodeY);
};

#endif // !defined(AFX_MEMORYTREEREDBLACK_H__65D419B6_9BAE_4869_B0CF_2EDE6C7639D8__INCLUDED_)
