// MemoryStringTree.h: interface for the CMemoryStringTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYSTRINGTREE_H__5FAA533A_0652_4A84_B57F_80C7FDEFE139__INCLUDED_)
#define AFX_MEMORYSTRINGTREE_H__5FAA533A_0652_4A84_B57F_80C7FDEFE139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryStringTree : public CMemoryStringArray
{
  public:
    CMemoryStringTree(const char* i_panStringName = "CMemoryStringTree");

    void SetClassName(const char* i_panStrName);

    // Additionnal operation --------------------------------------------------

    // String addition
    virtual int   AddString   (char* i_panStringBuffer, int i_nNodeData = 0, int i_nStringIndex = -1);

    // String insertion
    virtual int   InsertString(char* i_panStringBuffer, int i_nNodeData = 0, int i_nStringIndex = -1);

    // String information
    virtual int   FindTriesHead (char* i_panStringBuffer);
    virtual int   FindTriesTail (char* i_panStringBuffer);
    virtual char* FindTriesQueue(char* i_panStringBuffer);

  protected :
    virtual int   _SearchString(const char* i_panStringBuffer, int i_nStringIndex = -1);
    virtual void  _ConnectString(int i_nStringIndex);
};

#endif // !defined(AFX_MEMORYSTRINGTREE_H__5FAA533A_0652_4A84_B57F_80C7FDEFE139__INCLUDED_)
