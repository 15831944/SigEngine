// MemoryTreeRedBlack.cpp: implementation of the CMemoryTreeRedBlack class.
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
CMemoryTreeRedBlack::CMemoryTreeRedBlack
( const char* i_panStringName // = "CMemoryTreeRedBlack"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryTreeRedBlack");
#endif // _DEBUG
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
int CMemoryTreeRedBlack::AddNode
( void* i_panNodeBuffer
, int   i_nNodeKey
, int   i_nNodeData  // = 0
, int   i_nNodeParent // = -1
)
{
  sMNP* l_psNodeX = _LocateNode(CMemoryTree::AddNode(i_panNodeBuffer, i_nNodeKey, i_nNodeData, i_nNodeParent));
  sMNP* l_psNodeY;
  sMNP* l_psNodeZ = l_psNodeX;
  sMNP* l_psNodeP;
  bool  l_bNodeRight;

  //   |
  //   P
  //  / \
  // .   Y
  //    / \
  //   .   X

  // 1- Every node is either red or black
  // 2- Every leaf (nil) is black
  // 3- If a node is red, then both its children are black
  // 4- Every simple path from a node to a descendant leaf contains the same number of black nodes

  if(l_psNodeX->nCount < 2)
  { // If the node is new, let makes some changes above
    l_psNodeX->eColor = eNC_RED;
    
    l_psNodeY = _LocateNode(l_psNodeX->nIndexParent);

    while
    ( // AS LONG AS *NOT* root *AND* parent is red
         (l_psNodeX != mp_psNodeRoot)
      && (l_psNodeY->eColor == eNC_RED)
    )
    { // Locate parent's parent node, cache it
      l_psNodeP = _LocateNode(l_psNodeY->nIndexParent);
    
      if
      (
           l_psNodeX->nIndexParent
        == l_psNodeP->nIndexRight
      )
      { // If Y is P's right children
        l_bNodeRight = true;
        l_psNodeY = _LocateNode(l_psNodeP->nIndexRight);
      }
      else
      { // If Y is P's left children
        l_bNodeRight = false;
        l_psNodeY = _LocateNode(l_psNodeP->nIndexLeft);
      }
    
      if(l_psNodeY->eColor == eNC_RED)
      {
        l_psNodeY->eColor = eNC_BLACK;

        l_psNodeY = _LocateNode(l_psNodeX->nIndexParent);
        l_psNodeY->eColor = eNC_BLACK;

        l_psNodeX = l_psNodeP; // Get up from 2 levels and loop
        l_psNodeX->eColor = eNC_RED;

        l_psNodeY = _LocateNode(l_psNodeX->nIndexParent);
      }
      else
      {
        l_psNodeY = _LocateNode(l_psNodeX->nIndexParent);

        if
        (
             (
                  (l_bNodeRight == true)
               && (l_psNodeX->nIndexNode == l_psNodeY->nIndexRight)
             )
          || (
                  (l_bNodeRight == false)
               && (l_psNodeX->nIndexNode == l_psNodeY->nIndexLeft)
             )
        )
        {
          l_psNodeX = l_psNodeY; // Get up from 1 level and rotate
          l_psNodeY = l_psNodeP;
          l_psNodeP = _LocateNode(l_psNodeY->nIndexParent);

          if(l_bNodeRight)
          {
            _RotateRight(l_psNodeX->nIndexNode);
          }
          else
          {
            _RotateLeft(l_psNodeX->nIndexNode);
          }
        }
        else{}

        l_psNodeY->eColor = eNC_BLACK;
        l_psNodeP->eColor = eNC_RED;

        if(l_bNodeRight == true)
        {
          _RotateRight(l_psNodeP->nIndexNode);
        }
        else
        {
          _RotateLeft(l_psNodeP->nIndexNode);
        }
      }
    } // while

    mp_psNodeRoot->eColor = eNC_BLACK;
  }
  else{}

//  IncNodeCount(l_psNodeZ->nIndexNode); // C'est fait dans le CMemoryTree::AddNode utilisé plus haut

  return l_psNodeZ->nIndexNode;
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
void CMemoryTreeRedBlack::RemoveNodeAt
( int i_nNodeIndex // = -1
)
{
  sMNP* l_psNodeSplit;
  sMNP* l_psNodeChild;
  sMNP* l_psNodeLoop;
  sMNP* l_psNodeTempo;

  bool l_bNodeRight;

  if(i_nNodeIndex == -1)
  {
    l_psNodeSplit = mp_psNodeRoot;
  }
  else
  {
    l_psNodeSplit = _LocateNode(i_nNodeIndex);
  }

  if
  (
       (l_psNodeSplit->nIndexLeft  == -1)
    || (l_psNodeSplit->nIndexRight == -1)
  )
  { 
  }
  else
  { // If the node has two childs, split its successor and put it in its place
    l_psNodeSplit = _LocateNode(GetNodeSuccessor(l_psNodeSplit->nIndexNode));
  }
  
  if(l_psNodeSplit->nIndexLeft == -1)
  {
    l_psNodeChild = _LocateNode(l_psNodeSplit->nIndexRight);
  }
  else
  {
    l_psNodeChild = _LocateNode(l_psNodeSplit->nIndexLeft);
  }

  if(l_psNodeChild->nIndexNode != -1)
  { // Connect child to splited node parent
    l_psNodeChild->nIndexParent = l_psNodeSplit->nIndexParent;
  }
  else{}

  // Connect splited node parent to child
  if(l_psNodeSplit->nIndexParent == -1)
  {
    mp_psNodeRoot = l_psNodeChild;
  }
  else
  {
    l_psNodeTempo = _LocateNode(l_psNodeSplit->nIndexParent);

    if(l_psNodeSplit->nIndexNode != l_psNodeTempo->nIndexLeft)
    {
      l_psNodeTempo->nIndexRight = l_psNodeChild->nIndexNode;
    }
    else
    {
      l_psNodeTempo->nIndexLeft  = l_psNodeChild->nIndexNode;
    }
  }

  // RedBlack specific --------------------------------------------------------

  if(l_psNodeSplit->eColor == eNC_BLACK)
  {
    while
    (
         (l_psNodeChild != mp_psNodeRoot)
      && (l_psNodeChild->eColor == eNC_BLACK)
    )
    {
      l_psNodeTempo = _LocateNode(l_psNodeChild->nIndexParent);

      if(l_psNodeChild->nIndexNode == l_psNodeTempo->nIndexLeft)
      {
        l_bNodeRight = true;
        l_psNodeLoop = _LocateNode(l_psNodeTempo->nIndexRight);
      }
      else
      {
        l_bNodeRight = false;
        l_psNodeLoop = _LocateNode(l_psNodeTempo->nIndexLeft);
      }

      if(l_psNodeLoop->eColor == eNC_RED)
      {
        l_psNodeLoop->eColor  = eNC_BLACK;
        l_psNodeTempo->eColor = eNC_RED;

        if(l_bNodeRight == true)
        {
          _RotateLeft(l_psNodeTempo->nIndexNode);
          l_psNodeLoop = _LocateNode(l_psNodeTempo->nIndexRight);
        }
        else
        {
          _RotateRight(l_psNodeTempo->nIndexNode);
          l_psNodeLoop = _LocateNode(l_psNodeTempo->nIndexLeft);
        }
      }
      else{}

      if
      (
            (_LocateNode(l_psNodeLoop->nIndexLeft)->eColor  == eNC_BLACK)
         && (_LocateNode(l_psNodeLoop->nIndexRight)->eColor == eNC_BLACK)
      )
      {
        l_psNodeLoop->eColor = eNC_RED;

        l_psNodeChild = _LocateNode(l_psNodeChild->nIndexParent);
      }
      else
      {
        l_psNodeTempo = _LocateNode(l_psNodeChild->nIndexParent);

        if
        (
             (
                  (l_bNodeRight == true)
               && (_LocateNode(l_psNodeLoop->nIndexRight)->eColor == eNC_BLACK)
             )
          || (
                  (l_bNodeRight == false)
               && (_LocateNode(l_psNodeLoop->nIndexLeft)->eColor  == eNC_BLACK)
             )
        )
        {
          l_psNodeLoop->eColor = eNC_RED;

          if(l_bNodeRight == true)
          {
            _LocateNode(l_psNodeLoop->nIndexLeft)->eColor = eNC_BLACK;
            _RotateRight(l_psNodeLoop->nIndexNode);

            l_psNodeLoop = _LocateNode(l_psNodeTempo->nIndexRight);
          }
          else
          {
            _LocateNode(l_psNodeLoop->nIndexRight)->eColor = eNC_BLACK;
            _RotateLeft(l_psNodeLoop->nIndexNode);

            l_psNodeLoop = _LocateNode(l_psNodeTempo->nIndexLeft);
          }
        }
        else{}

        l_psNodeLoop->eColor  = l_psNodeTempo->eColor;
        l_psNodeTempo->eColor = eNC_BLACK;

        if(l_bNodeRight == true)
        {
          l_psNodeLoop->nIndexRight = eNC_BLACK;

          _RotateLeft(l_psNodeTempo->nIndexNode);
        }
        else
        {
          l_psNodeLoop->nIndexLeft  = eNC_BLACK;

          _RotateRight(l_psNodeTempo->nIndexNode);
        }

        l_psNodeChild = mp_psNodeRoot;
      }
    } // while

    l_psNodeChild->eColor = eNC_BLACK;
  }
  else{}

  // RedBlack specific --------------------------------------------------------

  // Put spliced node in place of node (if required)
  if(l_psNodeSplit->nIndexNode != i_nNodeIndex)
  {
    l_psNodeTempo = _LocateNode(i_nNodeIndex);

    l_psNodeTempo->nIndexParent = l_psNodeSplit->nIndexParent;
    l_psNodeTempo->nIndexLeft   = l_psNodeSplit->nIndexLeft;
    l_psNodeTempo->nIndexRight  = l_psNodeSplit->nIndexRight;

//    MEMCPY
//    ( _LocateNode(i_nNodeIndex)
//    , _LocateNode(l_psNodeSplit->nIndexNode)
//    , sizeof(sMNP)
//    );

    _DeleteNode(l_psNodeSplit->nIndexNode); // Delete the spliced node
  }
  else
  {
    _DeleteNode(i_nNodeIndex); // Delete the node
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
void CMemoryTreeRedBlack::_RotateLeft
( int i_nNodeX
)
{
  //   P                            P
  //   |                            |
  //   X                            Y
  //  / \                          / \
  // A   Y         ---->          X   C
  //    / \     _RotateLeft      / \
  //   B   C                    A   B

  sMNP* l_psNodeX = _LocateNode(i_nNodeX);
  sMNP* l_psNodeY = _LocateNode(l_psNodeX->nIndexRight);
  sMNP* l_psNodeP;

  // Switch B on the right of X
  //   P
  //   |
  //   X---Y
  //  / \ / \
  // A   B   C
  l_psNodeX->nIndexRight = l_psNodeY->nIndexLeft;

  if(l_psNodeY->nIndexLeft != -1)
  { // Set X as B's new parent
    _LocateNode(l_psNodeY->nIndexLeft)->nIndexParent = l_psNodeX->nIndexNode;
  }
  else{}

  // Give Y new parent X's previous parent
  //     P
  //    / \
  //   X   Y
  //  / \ / \
  // A   B   C
  l_psNodeY->nIndexParent = l_psNodeX->nIndexParent;

  if(l_psNodeX->nIndexParent == -1)
  { // If X was root, set Y as new root
    mp_psNodeRoot = l_psNodeY;
  }
  else
  { // Select X's parent, and make some changes at this level
    l_psNodeP = _LocateNode(l_psNodeX->nIndexParent);

    if(l_psNodeX->nIndexNode == l_psNodeP->nIndexRight)
    { // If X was the right child, now makes Y as right child
      //     P
      //    / \
      //   X   Y
      //  / \ / \
      // A   B   C
      l_psNodeP->nIndexRight = l_psNodeY->nIndexNode;
    }
    else
    { // If X was the left child, now makes Y as left child
      //     P
      //    / \
      //   Y   Y
      //  / \ / \
      // A   B   C
      l_psNodeP->nIndexLeft  = l_psNodeY->nIndexNode;
    }
  }

  // Set X as Y's left child
  //   P
  //   |\
  //   | Y
  //   |/ \
  //   X   C
  //  / \
  // A   B
  l_psNodeY->nIndexLeft = l_psNodeX->nIndexNode;

  // Set Y as X's new parent
  //     P
  //     |
  //     Y
  //    / \
  //   X   C
  //  / \
  // A   B
  l_psNodeX->nIndexParent = l_psNodeY->nIndexNode;
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
void CMemoryTreeRedBlack::_RotateRight
( int i_nNodeY
)
{
  //     P                       P
  //     |                       |  
  //     Y    _RotateRight       X  
  //    / \       ---->         / \  
  //   X   C                   A   Y  
  //  / \                         / \  
  // A   B                       B   C

  sMNP* l_psNodeY = _LocateNode(i_nNodeY);
  sMNP* l_psNodeX = _LocateNode(l_psNodeY->nIndexLeft);
  sMNP* l_psNodeP;

  // Switch B on the left of Y
  //       P
  //       |
  //   X---Y
  //  / \ / \
  // A   B   C
  l_psNodeY->nIndexLeft = l_psNodeX->nIndexRight;

  if(l_psNodeX->nIndexRight != -1)
  { // Set Y as B's new parent
    _LocateNode(l_psNodeX->nIndexRight)->nIndexParent = l_psNodeY->nIndexNode;
  }
  else{}

  // Give X new parent Y's previous parent
  //     P
  //    / \
  //   X   Y
  //  / \ / \
  // A   B   C
  l_psNodeX->nIndexParent = l_psNodeY->nIndexParent;

  if(l_psNodeY->nIndexParent == -1)
  { // If Y was root, set X as new root
    mp_psNodeRoot = l_psNodeX;
  }
  else
  { // Select Y's parent, and make some changes at this level
    l_psNodeP = _LocateNode(l_psNodeY->nIndexParent);

    if(l_psNodeY->nIndexNode == l_psNodeP->nIndexRight)
    { // If Y was the right child, now makes X as right child
      //     P
      //    / \
      //   X   X
      //  / \ / \
      // A   B   C
      l_psNodeP->nIndexRight = l_psNodeX->nIndexNode;
    }
    else
    { // If Y was the left child, now makes X as left child
      //     P
      //    / \
      //   X   Y
      //  / \ / \
      // A   B   C
      l_psNodeP->nIndexLeft  = l_psNodeX->nIndexNode;
    }
  }

  // Set Y as X's right child
  //     P
  //    /|
  //   X |
  //  / \|
  // A   Y
  //    / \
  //   B   C
  l_psNodeX->nIndexRight = l_psNodeY->nIndexNode;

  // Set X as Y's new parent
  //   P
  //   |
  //   X
  //  / \
  // A   Y
  //    / \
  //   B   C
  l_psNodeY->nIndexParent = l_psNodeX->nIndexNode;
} // 100 %
