// MemoryTreeAvl.h: interface for the CMemoryTreeAvl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYTREEAVL_H__6F5A9DE1_EBD5_44DD_A91C_91C5346F7DFF__INCLUDED_)
#define AFX_MEMORYTREEAVL_H__6F5A9DE1_EBD5_44DD_A91C_91C5346F7DFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryTreeAvl : public CMemoryTree
{
  public :
            CMemoryTreeAvl(const char* i_panStringName = "CMemoryTreeAvl");

    // Node addition
    virtual int  AddNode(void* i_panNodeBuffer, int i_nNodeKey, int i_nNodeData = 0, int i_nNodeParent = -1);

    // Slot removation
    virtual void RemoveNodeAt(int i_nNodeIndex = -1);
  protected :

    virtual void _Balance(int i_nNodeA, eNR i_eRotate, int i_nHeight);
    virtual void _Restore(int i_nNodeA);

    virtual void _RotateLL(int i_nNodeA);
    virtual void _RotateLR(int i_nNodeA);
    virtual void _RotateRL(int i_nNodeA);
    virtual void _RotateRR(int i_nNodeA);
};

#endif // !defined(AFX_MEMORYTREEAVL_H__6F5A9DE1_EBD5_44DD_A91C_91C5346F7DFF__INCLUDED_)
