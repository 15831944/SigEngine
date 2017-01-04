// MemoryTree.cpp: implementation of the CMemoryTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE D'ARBORESCENCE AUTO-DIMENSIONNABLE ======================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
CMemoryTree::CMemoryTree
( const char* i_panStringName // = "CMemoryTree"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryTree");
#endif // _DEBUG

  mp_nSlotSizeHead = sizeof(sMNP); // Size of slot header (DO NOT ALIGN)

  mp_psNodeRoot = NULL; // Root node
  mp_psNodeNull = NULL; // Null node, used for Red-Black tree
  mp_psNodeFree = NULL; // Queue of unused nodes
  mp_psNodePrev = NULL; // Previously requested node
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::AddNode
( void* i_panNodeBuffer
, int   i_nNodeKey
, int   i_nNodeData   // = 0
, int   i_nNodeParent // = -1
)
{ // Add a node from key (starting from another node)
  sMNP* l_psNodeLoop = NULL;
  sMNP* l_psNodeNew  = NULL; // Empty struct ready to be added in array
  int   l_nResult    = 1;

  if(mp_psNodeRoot == NULL)
  { // Create the root
    l_psNodeLoop = _MallocNode();

    if(l_psNodeLoop != NULL)
    {
      mp_psNodeRoot = l_psNodeLoop;

      l_psNodeLoop->nKey  = i_nNodeKey;
      l_psNodeLoop->nData = i_nNodeData;

      SetSlotBuffer(i_panNodeBuffer, l_psNodeLoop->nIndexNode);
    }
    else{}
  }
  else
  {
    if(i_nNodeParent == -1)
    {
      l_psNodeLoop = mp_psNodeRoot;
    }
    else
    {
      l_psNodeLoop = _LocateNode(i_nNodeParent);
    }

    while
    (
         (l_psNodeLoop != NULL)
      && (l_nResult != 0)
    )
    {
      l_nResult = l_psNodeLoop->nKey - i_nNodeKey;
    
      if(l_nResult == 0)
      {
//        l_psNodeLoop->nCount += 1;
      }
      else
      {
        if(l_nResult > 0)
        { // l_psNodeLoop->nKey > i_nNodeKey
          if(l_psNodeLoop->nIndexLeft == -1)
          {
            l_psNodeNew = _MallocNode();

            if(l_psNodeNew != NULL)
            {
              l_psNodeNew->nKey  = i_nNodeKey;
              l_psNodeNew->nData = i_nNodeData;

              SetSlotBuffer(i_panNodeBuffer, l_psNodeNew->nIndexNode);

              l_psNodeNew->nIndexParent = l_psNodeLoop->nIndexNode; // Current node index
              l_psNodeLoop->nIndexLeft  = l_psNodeNew->nIndexNode;
            }
            else{}

            l_psNodeLoop = l_psNodeNew;
          }
          else
          {
            l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexLeft);
          }
        }
        else
        { // l_psNodeLoop->nKey < i_nNodeKey
          if(l_psNodeLoop->nIndexRight == -1)
          {
            l_psNodeNew = _MallocNode();

            if(l_psNodeNew != NULL)
            {
              l_psNodeNew->nKey  = i_nNodeKey;
              l_psNodeNew->nData = i_nNodeData;

              SetSlotBuffer(i_panNodeBuffer, l_psNodeNew->nIndexNode);

              l_psNodeNew->nIndexParent = l_psNodeLoop->nIndexNode; // Current node index
              l_psNodeLoop->nIndexRight = l_psNodeNew->nIndexNode;
            }
            else{}

            l_psNodeLoop = l_psNodeNew;
          }
          else
          {
            l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexRight);
          }
        }
      }
    }
  }

  if(l_psNodeLoop != NULL)
  {
    IncNodeCount(l_psNodeLoop->nIndexNode);

    return l_psNodeLoop->nIndexNode;
  }
  else
  {
    return -1;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::AddNodeCRC
( void* i_panNodeBuffer
)
{
  DWORD l_nCrc32 = mp_oCrc32.CalcCRC(i_panNodeBuffer, mp_nSlotSizeData);
  int   l_nIndex = GetNodeIndex((int) l_nCrc32);

  if(l_nIndex < 0)
  { // If the Slot was not found, add it
    l_nIndex = AddNode(i_panNodeBuffer, l_nCrc32);
  }
  else{}

  return l_nIndex;
}

// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Ajout d'une méthode de création/modification de Node
/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::SetNode
( void* i_panNodeBuffer
, int   i_nNodeKey
, int   i_nNodeData   // = 0
, int   i_nNodeParent // = -1
)
{ // Set a node from key (starting from another node), add it if necessary
  sMNP* l_psNodeLoop = _LocateNode(GetNodeIndex(i_nNodeKey, i_nNodeParent));

  if(l_psNodeLoop == NULL)
  {
    return AddNode
    ( i_panNodeBuffer
    , i_nNodeKey
    , i_nNodeData
    , i_nNodeParent
    );
  }
  else
  {
    SetSlotBuffer
    ( i_panNodeBuffer
    , l_psNodeLoop->nIndexNode
    );

    SetNodeData
    ( l_psNodeLoop->nIndexNode
    , i_nNodeData
    );

    return l_psNodeLoop->nIndexNode;
  }
}
// MODIF_KOCH 070328

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::InsertNode
( void* i_panNodeBuffer
, int   i_nNodeKey
, int   i_nNodeData   // = 0
, int   i_nNodeParent // = -1
)
{ // Insert a node from key (starting from another node)
  return AddNode
  ( i_panNodeBuffer
  , i_nNodeKey
  , i_nNodeData
  , i_nNodeParent
  );
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::ConnectNode
( int i_nNodeIndex
, int i_nNodeKey
, int i_nNodeData   // = 0
, int i_nNodeParent // = -1
)
{ // Add a node from key (starting from another node)
  sMNP* l_psNodeLoop = NULL;
  sMNP* l_psNodeNew  = _LocateNode(i_nNodeIndex);
  int   l_nResult    = 1;

  if(mp_psNodeRoot == NULL)
  { // Create the root
    l_psNodeLoop = _MallocNode();

    if(l_psNodeLoop != NULL)
    {
      mp_psNodeRoot = l_psNodeLoop;

      l_psNodeLoop->nKey  = i_nNodeKey;
      l_psNodeLoop->nData = i_nNodeData;
    }
    else{}
  }
  else
  {
    if(i_nNodeParent == -1)
    {
      l_psNodeLoop = mp_psNodeRoot;
    }
    else
    {
      l_psNodeLoop = _LocateNode(i_nNodeParent);
    }

    while
    (
         (l_psNodeLoop != NULL)
      && (l_nResult    != 0)
    )
    {
      l_nResult = l_psNodeLoop->nKey - i_nNodeKey;
    
      if(l_nResult == 0)
      {
        l_psNodeLoop->nCount += 1;
      }
      else
      {
        if(l_nResult > 0)
        {
          if(l_psNodeLoop->nIndexLeft == -1)
          {
            if(l_psNodeNew != NULL)
            {
              l_psNodeNew->nKey  = i_nNodeKey;
              l_psNodeNew->nData = i_nNodeData;

              l_psNodeNew->nIndexParent = l_psNodeLoop->nIndexNode; // Current node index
              l_psNodeLoop->nIndexLeft  = l_psNodeNew->nIndexNode;
            }
            else{}

            l_psNodeLoop = l_psNodeNew;
          }
          else
          {
            l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexLeft);
          }

        }
        else
        {
          if(l_psNodeLoop->nIndexRight == -1)
          {
            if(l_psNodeNew != NULL)
            {
              l_psNodeNew->nKey  = i_nNodeKey;
              l_psNodeNew->nData = i_nNodeData;

              l_psNodeNew->nIndexParent = l_psNodeLoop->nIndexNode; // Current node index
              l_psNodeLoop->nIndexRight = l_psNodeNew->nIndexNode;
            }
            else{}

            l_psNodeLoop = l_psNodeNew;
          }
          else
          {
            l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexRight);
          }
        }
      }
    }
  }

  if(l_psNodeLoop != NULL)
  {
    return l_psNodeLoop->nIndexNode;
  }
  else
  {
    return -1;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::RemoveNodeAll
( void
)
{ // Remove all nodes
  sMNP* l_psNodeLoop   = mp_psNodeRoot;
  sMNP* l_psNodeParent = NULL;

  while
  (
       (l_psNodeLoop != NULL)
    && (l_psNodeLoop->nIndexNode != -1)
  )
  {
    if(l_psNodeLoop->nIndexLeft != -1)
    {
      l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexLeft);
    }
    else if(l_psNodeLoop->nIndexRight != -1)
    {
      l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexRight);
    }
    else
    {
      l_psNodeParent = _LocateNode(l_psNodeLoop->nIndexParent);

      if
      (
           (l_psNodeParent != NULL)
        && (l_psNodeParent->nIndexNode != -1)
      )
      {
        if(l_psNodeLoop->nIndexNode == l_psNodeParent->nIndexRight)
        {
          l_psNodeParent->nIndexRight = -1;
        }
        else
        {
          l_psNodeParent->nIndexLeft = -1;
        }
      }
      else{}

      _DeleteNode(l_psNodeLoop->nIndexNode);

      l_psNodeLoop = l_psNodeParent;
    }
  }

  mp_psNodeRoot = NULL; // TEST TEST TEST TEST
} // 

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::RemoveNodeAt
( int i_nNodeIndex // = -1
)
{
  sMNP* l_psNode = NULL;

  if(i_nNodeIndex == -1)
  {
//    l_psNode = mp_psNodeRoot;
  }
  else
  {
    l_psNode = _LocateNode(i_nNodeIndex);
  }

  if
  (
       (l_psNode->nIndexLeft  == -1)
    || (l_psNode->nIndexRight == -1)
  )
  { // 0 or 1 child
  }
  else
  { // If the node has two childs, split its successor and put it in its place
    l_psNode = _LocateNode(GetNodeSuccessor(l_psNode->nIndexNode));
  }
  
  _DeleteNode(l_psNode->nIndexNode);
}
   
/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeNumber
( void
)
{ // Get number of nodes in the tree
  int   l_nNodeFree = 0;
  sMNP* l_nNodeNext = mp_psNodeFree;

  while(l_nNodeNext != NULL)
  {
    l_nNodeNext  = _LocateNode(l_nNodeNext->nIndexParent);
    l_nNodeFree += 1;
  }

  return GetSlotTail() - l_nNodeFree;
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeIndex
( int i_nNodeKey
, int i_nNodeIndex // = -1
)
{ // Get node index from key (starting from another node)
  sMNP* l_psNodeLoop = NULL;
  int   l_nResult;

  if(i_nNodeIndex == -1)
  {
    l_psNodeLoop = mp_psNodeRoot;
  }
  else
  {
    l_psNodeLoop = _LocateNode(i_nNodeIndex);
  }

  while
  (
       (l_psNodeLoop != NULL)
    && (l_psNodeLoop->nIndexNode != -1)
    && ((l_nResult = l_psNodeLoop->nKey - i_nNodeKey) != 0)
  )
  {
    if(l_nResult < 0)
    {
      l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexRight);
    }
    else
    {
      l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexLeft);
    }
  }

  if(l_psNodeLoop != NULL)
  {
    return l_psNodeLoop->nIndexNode;
  }
  else
  {
    return -1;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeIndexCRC
( void* i_panNodeBuffer
)
{
  DWORD l_nCrc32 = mp_oCrc32.CalcCRC(i_panNodeBuffer, mp_nSlotSizeData);

  return GetNodeIndex((int) l_nCrc32);
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeMin
( int i_nNodeIndex // = -1
)
{ // Get node index of minimum key (starting from another node)
  sMNP* l_psNodeLoop = NULL;

  if(i_nNodeIndex == -1)
  {
    l_psNodeLoop = mp_psNodeRoot;
  }
  else
  {
    l_psNodeLoop = _LocateNode(i_nNodeIndex);
  }

  while
  (
       (l_psNodeLoop->nIndexNode != -1)
    && (l_psNodeLoop->nIndexLeft != -1)
  )
  {
    l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexLeft);
  }

  return l_psNodeLoop->nIndexNode;
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeMax
( int i_nNodeIndex // = -1
)
{ // Get node index of maximum key (starting from another node)
  sMNP* l_psNodeLoop = NULL;

  if(i_nNodeIndex == -1)
  {
    l_psNodeLoop = mp_psNodeRoot;
  }
  else
  {
    l_psNodeLoop = _LocateNode(i_nNodeIndex);
  }

  while
  (
       (l_psNodeLoop->nIndexNode  != -1)
    && (l_psNodeLoop->nIndexRight != -1)
  )
  {
    l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexRight);
  }

  return l_psNodeLoop->nIndexNode;
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodePredecessor
( int i_nNodeIndex // = -1
)
{ // Get predecessor node index (starting from another node)
  sMNP* l_psNodeLoop = NULL;

  if(i_nNodeIndex == -1)
  {
    l_psNodeLoop = mp_psNodeRoot;
  }
  else
  {
    l_psNodeLoop = _LocateNode(i_nNodeIndex);
  }

  if(l_psNodeLoop->nIndexLeft != -1)
  { // Return the right most node in the left subtree
    return GetNodeMax(l_psNodeLoop->nIndexLeft);
  }
  else
  {
    while
    (
         (l_psNodeLoop->nIndexParent != -1)
//      && (l_psNodeLoop->nIndexNode   != _LocateNode(l_psNodeLoop->nIndexParent)->nIndexRight)
      && (l_psNodeLoop->nIndexNode   == _LocateNode(l_psNodeLoop->nIndexParent)->nIndexLeft)
    )
    { // Go up from node until we find a node that is the right of its parent
      l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexParent);
    }

    return l_psNodeLoop->nIndexParent;
  }
} // 100 %
   
/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeSuccessor
( int i_nNodeIndex // = -1
)
{ // Get successor node index (starting from another node)
  sMNP* l_psNodeLoop = NULL;

  if(i_nNodeIndex == -1)
  {
    l_psNodeLoop = mp_psNodeRoot;
  }
  else
  {
    l_psNodeLoop = _LocateNode(i_nNodeIndex);
  }

  if(l_psNodeLoop->nIndexRight != -1)
  { // Return the left most node in the right subtree
    return GetNodeMin(l_psNodeLoop->nIndexRight);
  }
  else
  {
    while
    (
         (l_psNodeLoop->nIndexParent != -1)
//      && (l_psNodeLoop->nIndexNode   != _LocateNode(l_psNodeLoop->nIndexParent)->nIndexLeft)
      && (l_psNodeLoop->nIndexNode   == _LocateNode(l_psNodeLoop->nIndexParent)->nIndexRight)
    )
    { // Go up from node until we find a node that is the left of its parent
      l_psNodeLoop = _LocateNode(l_psNodeLoop->nIndexParent);
    }

    return l_psNodeLoop->nIndexParent;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeLeft
( int i_nNodeIndex // = -1
)
{
  sMNP* l_psNodeLoop = NULL;

  if(i_nNodeIndex == -1)
  {
    l_psNodeLoop = mp_psNodeRoot;
  }
  else
  {
    l_psNodeLoop = _LocateNode(i_nNodeIndex);
  }

  if(l_psNodeLoop != NULL)
  {
    return l_psNodeLoop->nIndexLeft;
  }
  else
  {
    return -1;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeRight
( int i_nNodeIndex // = -1
)
{
  sMNP* l_psNodeLoop = NULL;

  if(i_nNodeIndex == -1)
  {
    l_psNodeLoop = mp_psNodeRoot;
  }
  else
  {
    l_psNodeLoop = _LocateNode(i_nNodeIndex);
  }

  if(l_psNodeLoop != NULL)
  {
    return l_psNodeLoop->nIndexRight;
  }
  else
  {
    return -1;
  }
}    

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::SetNodeLeft
( int i_nNodeIndex
, int i_nNodeLeft
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    l_psMNP->nIndexLeft = i_nNodeLeft;
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::SetNodeRight
( int i_nNodeIndex
, int i_nNodeRight
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    l_psMNP->nIndexRight = i_nNodeRight;
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeCount
( int i_nNodeIndex
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    return l_psMNP->nCount;
  }
  else
  {
    return -1;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::SetNodeCount
(          int i_nNodeIndex
, unsigned int i_nNodeCount
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    l_psMNP->nCount = i_nNodeCount;
  }
  else{}
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::IncNodeCount
( int i_nNodeIndex
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    l_psMNP->nCount += 1;
    
    return l_psMNP->nCount;
  }
  else
  {
    return -1;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::DecNodeCount
( int i_nNodeIndex
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);
  
  if(l_psMNP != NULL)
  {
    if(l_psMNP->nCount > 0)
    {
      l_psMNP->nCount -= 1;
    }
    else{}

    return l_psMNP->nCount;
  }
  else
  {
    return -1;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeData
( int i_nNodeIndex
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    return l_psMNP->nData;
  }
  else
  {
    return -1; // Used for GetStringData, in case of stringA[stringB.GetStringData(non_existing_index)], it returns NULL
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::SetNodeData
( int i_nNodeIndex
, int i_nNodeData
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    l_psMNP->nData = i_nNodeData;
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeHole
( int i_nNodeIndex
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    return l_psMNP->nHole;
  }
  else
  {
    return -1;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::SetNodeHole
(          int   i_nNodeIndex
, unsigned short i_nNodeHole
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    l_psMNP->nHole = i_nNodeHole;
  }
  else{}
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::GetNodeSize
( int i_nNodeIndex
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    return l_psMNP->nSize;
  }
  else
  {
    return -1;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::SetNodeSize
(          int   i_nNodeIndex
, unsigned short i_nNodeSize
)
{
  sMNP* l_psMNP = _LocateNode(i_nNodeIndex);

  if(l_psMNP != NULL)
  {
    l_psMNP->nSize = i_nNodeSize;
  }
  else{}
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::RemoveOnCountThreshold
( unsigned int i_nNodeCountMax
)
{
  sMNP* l_psNode = _LocateNode(GetNodeMin());
  while(l_psNode != NULL)
  { 
    if(l_psNode->nCount <= i_nNodeCountMax)
    {
      _DeleteNode(l_psNode->nIndexNode);
    }
    else{}

    l_psNode = _LocateNode(GetNodeSuccessor(l_psNode->nIndexNode));
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CMemoryTree::AllocNode
(          int   i_nNodeKey
, unsigned short i_nNodeSize // = 0
)
{
  sMNP* l_psMNP = _MallocNode(i_nNodeSize);

  if(mp_psNodeRoot == NULL)
  { // Set the root if not yet set
    mp_psNodeRoot = l_psMNP;
  }
  else{}

  l_psMNP->nKey  = i_nNodeKey;
  l_psMNP->nSize = i_nNodeSize;

  return l_psMNP->nIndexNode;
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
bool CMemoryTree::LoadFromFile
( CFile& i_roFileIn
)
{
  bool l_bResult = CMemoryPool::LoadFromFile(i_roFileIn);

  mp_psNodeRoot = (sMNP*) mp_psBufferFirst->panBuffer;

  return l_bResult;
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CMemoryTree::_DeleteNode
( int i_nNodeIndex
)
{
  sMNP* l_psNode       = _LocateNode(i_nNodeIndex);
  sMNP* l_poNodeParent = _LocateNode(l_psNode->nIndexParent);
  sMNP* l_poNodeChild;

  if(l_psNode->nIndexLeft != -1)
  { // If there is a child
    l_poNodeChild = _LocateNode(l_psNode->nIndexLeft);
  }
  else
  {
    l_poNodeChild = _LocateNode(l_psNode->nIndexRight);
  }

  if(l_poNodeChild != NULL)
  { // Connect the child to the parent
    l_poNodeChild->nIndexParent = l_psNode->nIndexParent;

    if(l_psNode->nIndexParent == -1)
    { // Change the root if the current node IS the root
      mp_psNodeRoot = l_poNodeChild;
    }
    else
    { // If there is a parent
      if(l_poNodeParent->nIndexLeft == l_psNode->nIndexNode)
      { // If the node was his left parent's child
        l_poNodeParent->nIndexLeft  = l_poNodeChild->nIndexNode;
      }
      else
      {
        l_poNodeParent->nIndexRight = l_poNodeChild->nIndexNode;
      }
    }
  }
  else{}

  if
  (
       (mp_bZeroMemory == TRUE)
    && (GetSlotPointer(i_nNodeIndex) != NULL)
  )
  {
    ZeroMemory
    ( GetSlotPointer(i_nNodeIndex)
    , mp_nSlotSizeData // mp_nSlotSizeHole
    );
  }
  else{}

  if(mp_psNodeFree != NULL)
  { // Queue the deleted node
    l_psNode->nIndexParent = mp_psNodeFree->nIndexNode;
  }
  else
  { // End the queue here
    l_psNode->nIndexParent = -1;
  }

  // Add in the queue
  mp_psNodeFree = l_psNode;
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
CMemoryTree::sMNP*
CMemoryTree::_LocateNode
( int i_nNodeIndex
)
{
  if(i_nNodeIndex == -1)
  {
    return NULL;
  }
/*
  { // Root
    if(mp_psNodeRoot == NULL)
    {
      mp_psNodeRoot = _MallocNode();
    }
    else{}

    return mp_psNodeRoot;
  }
*/
  else
  {
    if
    (
         (mp_psNodePrev != NULL)
      && (mp_psNodePrev->nIndexNode == i_nNodeIndex)
    )
    { // Already found
    }
    else
    { // Get the slot pointer
      mp_psNodePrev = (sMNP*) GetSlotPointer(i_nNodeIndex) - 1;
    }

    return mp_psNodePrev;
  }
} // 100 %

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
CMemoryTree::sMNP*
CMemoryTree::_MallocNode
( unsigned short i_nNodeSize // = 0
)
{
  int   l_nNodeIndex;
  sMNP* l_psNodePrev = NULL;

  if(mp_psNodeFree != NULL)
  { // Get an unused slot from the queue
    mp_psNodePrev = mp_psNodeFree; // Get first free node
    l_psNodePrev  = mp_psNodeFree;

    while
    (
         (mp_psNodePrev->nHole < i_nNodeSize)
      && (mp_psNodePrev->nIndexParent != -1) // Avoid NULL
    )
    { // Look-up for the first hole big enough
      l_psNodePrev  = mp_psNodePrev;
      mp_psNodePrev = _LocateNode(mp_psNodePrev->nIndexParent); // Next free node
    }

    if(mp_psNodePrev->nHole < i_nNodeSize)
    { // Hole to little, leave things intact
      mp_psNodePrev = NULL; // Malloc a new hole
    }
    else
    { // Restore the free node
      if(mp_psNodeFree == mp_psNodePrev)
      { // Unlink the free node
        l_psNodePrev  = mp_psNodePrev; // SIDE EFFECT IN LOCATENODE
        mp_psNodeFree = _LocateNode(mp_psNodeFree->nIndexParent); // Get the next free node
        mp_psNodePrev = l_psNodePrev; // SIDE EFFECT IN LOCATENODE
      }
      else
      {
        l_psNodePrev->nIndexParent = mp_psNodePrev->nIndexParent; // Link next free node
      }

      mp_psNodePrev->nSize = i_nNodeSize; // New requested size

      l_nNodeIndex = mp_psNodePrev->nIndexNode; // Previous node index
    }
  }
  else
  {
    mp_psNodePrev = NULL;
  }

  if(mp_psNodePrev == NULL)
  { // Allocate a node from the array
    l_nNodeIndex = AddSlotTail(NULL); // New node

    mp_psNodePrev = (sMNP*) GetSlotPointer(l_nNodeIndex) - 1;

    mp_psNodePrev->nHole = 0;
//    mp_psNodePrev->nSize = 0;
  }
  else{}
    
  if(mp_psNodePrev != NULL)
  { // Initialise the new node
    mp_psNodePrev->nKey         = 0;
    mp_psNodePrev->nData        = 0;
//    mp_psNodePrev->nHole        = 0;
    mp_psNodePrev->nSize        = 0;
    mp_psNodePrev->nCount       = 0;
    mp_psNodePrev->nBalance     = 0;
    mp_psNodePrev->eColor       = eNC_RED;
    mp_psNodePrev->nBalance     = 0;
    mp_psNodePrev->nIndexNode   = l_nNodeIndex;
    mp_psNodePrev->nIndexParent = -1;
    mp_psNodePrev->nIndexLeft   = -1;
    mp_psNodePrev->nIndexRight  = -1;
  }
  else{}

/*
  // WARNING COULD OVERWRITE REMOVE ALL NODES' "ROOT TO NULL"
  if(mp_psNodeRoot == NULL)
  { // Set the root
    mp_psNodeRoot = mp_psNodePrev;
  }
  else{}
*/

  return mp_psNodePrev;
} // 100 %
