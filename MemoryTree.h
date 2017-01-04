// MemoryTree.h: interface for the CMemoryTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYTREE_H__E0964EEF_F358_4251_B762_A2BEC175292E__INCLUDED_)
#define AFX_MEMORYTREE_H__E0964EEF_F358_4251_B762_A2BEC175292E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Memory.h"

class EXPSIGENGINE CMemoryTree : public CMemoryArray
{
  public :
            CMemoryTree(const char* i_panStringName = "CMemoryTree");

    // Additionnal operation --------------------------------------------------

    // Node addition
    virtual int   AddNode   (void* i_panNodeBuffer, int i_nNodeKey, int i_nNodeData = 0, int i_nNodeParent = -1);
    virtual int   AddNodeCRC(void* i_panNodeBuffer);
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Ajout d'une méthode de création/modification de Node
    virtual int   SetNode   (void* i_panNodeBuffer, int i_nNodeKey, int i_nNodeData = 0, int i_nNodeParent = -1);
// MODIF_KOCH 070328

    // Node insertion
    virtual int   InsertNode(void* i_panNodeBuffer, int i_nNodeKey, int i_nNodeData = 0, int i_nNodeParent = -1);

    // Node reconnection
    virtual int   ConnectNode(int i_nNodeIndex,     int i_nNodeKey, int i_nNodeData = 0, int i_nNodeParent = -1);

    // Node removation
    virtual void  RemoveNodeAll(void);
    virtual void  RemoveNodeAt(int i_nNodeIndex = -1);

    // Node information
    virtual int   GetNodeNumber(void);
    virtual int   GetNodeIndex(int i_nNodeKey, int i_nNodeIndex = -1);
    virtual int   GetNodeIndexCRC(void* i_panNodeBuffer);

    virtual int   GetNodeMin(int i_nNodeIndex = -1);
    virtual int   GetNodeMax(int i_nNodeIndex = -1);
    
    virtual int   GetNodePredecessor(int i_nNodeIndex = -1);
    virtual int   GetNodeSuccessor  (int i_nNodeIndex = -1);

    virtual int   GetNodeLeft (int i_nNodeIndex = -1);
    virtual int   GetNodeRight(int i_nNodeIndex = -1);

    virtual void  SetNodeLeft (int i_nNodeIndex, int i_nNodeLeft);
    virtual void  SetNodeRight(int i_nNodeIndex, int i_nNodeRight);
    
    // Slot information
    virtual int   GetNodeCount(int i_nNodeIndex);
    virtual void  SetNodeCount(int i_nNodeIndex, unsigned int i_nNodeCount);
    virtual int   IncNodeCount(int i_nNodeIndex);
    virtual int   DecNodeCount(int i_nNodeIndex);

    virtual int   GetNodeData(int i_nNodeIndex);
    virtual void  SetNodeData(int i_nNodeIndex, int i_nNodeData);

    virtual int   GetNodeHole(int i_nNodeIndex);
    virtual void  SetNodeHole(int i_nNodeIndex, unsigned short i_nNodeHole);
    
    virtual int   GetNodeSize(int i_nNodeIndex);
    virtual void  SetNodeSize(int i_nNodeIndex, unsigned short i_nNodeSize);

    // Node tool
    virtual void  RemoveOnCountThreshold(unsigned int i_nNodeCountMax);
    virtual int   AllocNode(int i_nNodeKey, unsigned short i_nNodeSize = 0);

    // Disk operation
    virtual bool  LoadFromFile(CFile& i_roFileIn);

    // Anti-DlHell
    virtual void  MinVer061103(void){}; // Un appel à cette fonction pour filtrer les ancinnes DLL SigEngine
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support de la rotation et homothétie d'un bloc
    virtual void  MinVer070328(void){}; // Un appel à cette fonction pour filtrer les ancinnes DLL SigEngine
// MODIF_KOCH 070328

  protected :
    enum eNC
    { eNC_RED = 0
    , eNC_BLACK
    , eNC__NUM
    };

    enum eNR
    { eNR_L = 0
    , eNR_LL
    , eNR_LR
    , eNR_R
    , eNR_RL
    , eNR_RR
    , eNR__NUM
    };

  protected :
    typedef struct sMemoryNodePointer
    {          int   nKey         // Key   data
    ;          int   nData        // Extra data
    ; unsigned short nHole        // Used for variable lenght slots, such strings
    ; unsigned short nSize        // Used for variable lenght slots, such strings
    ; unsigned int   nCount
    ;          short nHeight      // Used for AVL tree
    ;          short nBalance     // Used for AVL tree
    ;          eNC   eColor       // Used for Red-Black tree
    ;          int   nIndexNode
    ;          int   nIndexParent
    ;          int   nIndexLeft
    ;          int   nIndexRight
    ;} sMNP, *psMNP; // 40 bytes

  protected :
    virtual void  _DeleteNode(int i_nNodeIndex);
    virtual sMNP* _LocateNode(int i_nNodeIndex);
    virtual sMNP* _MallocNode(unsigned short i_nNodeSize = 0);

  protected :
    sMNP* mp_psNodeRoot; // Root node
    sMNP* mp_psNodeNull; // Null node, used for Red-Black tree
    sMNP* mp_psNodeFree; // Queue of unused nodes
    sMNP* mp_psNodePrev; // Previously requested node

    CRC32 mp_oCrc32;
};

#endif // !defined(AFX_MEMORYTREE_H__E0964EEF_F358_4251_B762_A2BEC175292E__INCLUDED_)
