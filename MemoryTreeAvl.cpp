// MemoryTreeAvl.cpp: implementation of the CMemoryTreeAvl class.
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
CMemoryTreeAvl::CMemoryTreeAvl
( const char* i_panStringName // = "CMemoryTreeAvl"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryTreeAvl");
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
int CMemoryTreeAvl::AddNode
( void* i_panNodeBuffer
, int   i_nNodeKey
, int   i_nNodeData  // = 0
, int   i_nNodeParent // = -1
)
{
  int l_nNodeIndex = CMemoryTree::AddNode(i_panNodeBuffer, i_nNodeKey, i_nNodeData, i_nNodeParent);

  sMNP* l_psNode = _LocateNode(l_nNodeIndex);

  while
  (
       (l_psNode != NULL)
    && (l_psNode->nIndexParent != -1)
  )
  { // Rebalance the tree
    if(l_psNode->nKey < i_nNodeKey)
    {
      _Balance(l_psNode->nIndexNode, eNR_L, 1);
    }
    else
    {
      _Balance(l_psNode->nIndexNode, eNR_R, 1);
    }

    l_psNode = _LocateNode(l_psNode->nIndexParent);
  }

  return l_nNodeIndex;
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
void CMemoryTreeAvl::RemoveNodeAt
( int i_nNodeIndex // = -1
)
{ // Remove a node
  sMNP* l_psNode;

  if(i_nNodeIndex == -1)
  {
    l_psNode = mp_psNodeRoot;
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
  {
    l_psNode = _LocateNode(l_psNode->nIndexRight);

    while(l_psNode->nIndexLeft)
    {
      l_psNode = _LocateNode(l_psNode->nIndexLeft);
    }
  }
  else{}

  _DeleteNode(l_psNode->nIndexNode);

  _Restore(l_psNode->nIndexParent);
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
void CMemoryTreeAvl::_Balance
( int i_nNodeA
, eNR i_eRotate
, int i_nHeight
)
{ // Balance the tree

  //   P
  //   |
  //   A
  //  / \
  // B   C

  sMNP* l_psNodeA = _LocateNode(i_nNodeA);
  sMNP* l_psNodeP = _LocateNode(l_psNodeA->nIndexParent);

  l_psNodeA = l_psNodeP;

  while(l_psNodeA != NULL)
  {
    if
    (
         ((i_eRotate  < eNR_R) && (l_psNodeA->nBalance ==  1))
      || ((i_eRotate >= eNR_R) && (l_psNodeA->nBalance == -1))
    )
    {
      switch(i_eRotate)
      {
        case eNR_LR :
          _RotateLR(l_psNodeA->nIndexNode);
          return;

        case eNR_LL :
          _RotateLL(l_psNodeA->nIndexNode);
          return;

        case eNR_RL :
          _RotateRL(l_psNodeA->nIndexNode);
          return;

        case eNR_RR :
          _RotateRR(l_psNodeA->nIndexNode);
          return;

        default :
          break;
      }
    }
    else{}

    switch(i_eRotate)
    {
      case eNR_L :
      case eNR_LR :
      case eNR_LL :
        l_psNodeA->nBalance += 1;
        break;

      case eNR_R :
      case eNR_RL :
      case eNR_RR :
        l_psNodeA->nBalance -= 1;
        break;

      default :
        break;
    }

    if(l_psNodeA->nHeight >= i_nHeight)
    { // Return if the height of the current node is GE to the new height
      return;
    }
    else
    {
      l_psNodeA->nHeight += 1;

      // Cache A's parent
      l_psNodeP = _LocateNode(l_psNodeA->nIndexParent);

      if(l_psNodeP != NULL)
      {
        if(i_eRotate  < eNR_R)
        {
          if(l_psNodeP->nIndexLeft == l_psNodeA->nIndexNode)
          {
            i_eRotate = eNR_LL;
          }
          else
          {
            i_eRotate = eNR_RL;
          }
        }
        else
        {
          if(l_psNodeP->nIndexLeft == l_psNodeA->nIndexNode)
          {
            i_eRotate = eNR_LR;
          }
          else
          {
            i_eRotate = eNR_RR;
          }
        }
      }
      else{}

      l_psNodeA = l_psNodeP; // Get 1 level up
    }
  } // while
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
void CMemoryTreeAvl::_Restore
( int i_nNodeA
)
{ // Call this function after removing a node from the AVL-tree

  //   |
  //   A
  //  / \
  // B   C

  sMNP* l_psNodeA = _LocateNode(i_nNodeA);
  sMNP* l_psNodeB = _LocateNode(l_psNodeA->nIndexLeft);
  sMNP* l_psNodeC = _LocateNode(l_psNodeA->nIndexRight);

  int l_nHeight = l_psNodeA->nHeight;

  // Set A's height and balance
  if
  (
       (l_psNodeA->nIndexLeft  != -1)
    && (l_psNodeA->nIndexRight != -1)
  )
  { // Two childs
    if(l_psNodeB->nHeight >= l_psNodeC->nHeight)
    {
      l_psNodeA->nHeight = l_psNodeB->nHeight;
    }
    else
    {
      l_psNodeA->nHeight = l_psNodeC->nHeight;
    }

    l_psNodeA->nHeight += 1;
    l_psNodeA->nBalance = l_psNodeB->nHeight - l_psNodeC->nHeight;
  }
  else
  {
    if
    (
         (l_psNodeA->nIndexLeft  == -1)
      && (l_psNodeA->nIndexRight == -1)
    )
    { // No child
      l_psNodeA->nBalance = 0;
    }
    else
    { // One child
      if(l_psNodeA->nIndexLeft != -1)
      {
        l_psNodeA->nBalance = l_psNodeB->nHeight;
      }
      else
      {
        l_psNodeA->nBalance = 0 - l_psNodeC->nHeight;
      }
    }
  }

  // Rotate on A's balance
  if(l_psNodeA->nBalance == 2)
  {
    if(l_psNodeB->nBalance == 1)
    {
      _RotateLL(l_psNodeA->nIndexNode);
    }
    else
    {
      _RotateLR(l_psNodeA->nIndexNode);
    }
  }
  else
  {
    if(l_psNodeA->nBalance == -2)
    {
      if(l_psNodeC->nBalance == -1)
      {
        _RotateRR(l_psNodeA->nIndexNode);
      }
      else
      {
        _RotateRL(l_psNodeA->nIndexNode);
      }
    }
  }

  if(l_psNodeA->nHeight != l_nHeight)
  { // If Height changed, Restore the parent
    if(l_psNodeA->nIndexParent != -1)
    {
      _Restore(l_psNodeA->nIndexParent);
    }
    else{}
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
void CMemoryTreeAvl::_RotateLL
( int i_nNodeA
)
{
  //       P                      P
  //       |                      |
  //       A                      B
  //      / \                   /   \
  //     B   Ar  _RotateLR    Bl     A
  //    / \        ---->     /  \   / \
  //   Bl  C               Bll Blr C   Ar
  //  / \
  // Bll Blr

  sMNP* l_psNodeA = _LocateNode(i_nNodeA);
  sMNP* l_psNodeB = _LocateNode(l_psNodeA->nIndexLeft);
  sMNP* l_psNodeC = _LocateNode(l_psNodeB->nIndexRight);
  sMNP* l_psNodeP = _LocateNode(l_psNodeA->nIndexParent);

  if(l_psNodeA->nIndexParent != -1)
  { // If A have a parent, switch it's child to B
    if(l_psNodeP->nIndexLeft == l_psNodeA->nIndexNode)
    {
      l_psNodeP->nIndexLeft  = l_psNodeB->nIndexNode;
    }
    else
    {
      l_psNodeP->nIndexRight = l_psNodeB->nIndexNode;
    }
  }
  else
  { // If node A was root, now it's node B turn to be root
    mp_psNodeRoot = l_psNodeB;
  }

  // Set A's parent as B's new parent
  //     P
  //     |\
  //     | A
  //     |/ \
  //     B   Ar
  //    / \
  //   Bl  C
  //  / \
  // Bll Blr
  l_psNodeB->nIndexParent = l_psNodeA->nIndexParent;

  // Set A as right child of B (B is less than A)
  //       P
  //      /|
  //     B |
  //    /|\|
  //  Bl C A
  //  / \   \
  // Bll Blr Ar
  l_psNodeB->nIndexRight = l_psNodeA->nIndexNode;

  // Set B as new A's parent
  //     P
  //     |
  //     B
  //    /|\
  //  Bl C A
  //  / \   \
  // Bll Blr Ar
  l_psNodeA->nIndexParent = l_psNodeB->nIndexNode;

  if(l_psNodeC != NULL)
  { // Set C as A's left child (C is less than A, but greater than B)
    //      P
    //      |
    //      B
    //    / | \
    //   Bl C--A
    //  / \      \
    // Bll Blr    Ar
    l_psNodeA->nIndexLeft = l_psNodeC->nIndexNode;

    // Set A as C's new parent
    //        P
    //        |
    //        B
    //      /   \
    //     Bl    A
    //    / \   / \
    // Bll Blr C   Ar
    l_psNodeC->nIndexParent = l_psNodeA->nIndexNode;

    // Cache Ar -> Set A's height and balance
    l_psNodeP = _LocateNode(l_psNodeA->nIndexRight);

    if(l_psNodeC->nHeight >= l_psNodeP->nHeight)
    {
      l_psNodeA->nHeight = l_psNodeC->nHeight;
    }
    else
    {
      l_psNodeA->nHeight = l_psNodeP->nHeight;
    }

    l_psNodeA->nHeight += 1;
    l_psNodeA->nBalance = l_psNodeC->nHeight - l_psNodeP->nHeight;
  }
  else
  {
    l_psNodeA->nIndexLeft = -1;

    l_psNodeA->nHeight  = 0;
    l_psNodeA->nBalance = 0;
  }

  // Cache Bl -> Set B's height and balance
  l_psNodeP = _LocateNode(l_psNodeB->nIndexLeft);

  if(l_psNodeP->nHeight >= l_psNodeA->nHeight)
  {
    l_psNodeB->nHeight = l_psNodeP->nHeight;
  }
  else
  {
    l_psNodeB->nHeight = l_psNodeA->nHeight;
  }

  l_psNodeB->nHeight += 1;
  l_psNodeB->nBalance = l_psNodeP->nHeight - l_psNodeA->nHeight;
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
void CMemoryTreeAvl::_RotateLR
( int i_nNodeA
)
{
  //     P                    P
  //     |                    |
  //     A                    C
  //    / \                 /   \ 
  //   B   Ar  _RotateLR   B     A
  //  / \        ---->    / \   / \
  // Bl  C               Bl  D E   Ar
  //    / \
  //   D   E

  sMNP* l_psNodeA = _LocateNode(i_nNodeA);
  sMNP* l_psNodeB = _LocateNode(l_psNodeA->nIndexLeft);
  sMNP* l_psNodeC = _LocateNode(l_psNodeB->nIndexRight);
  sMNP* l_psNodeD = _LocateNode(l_psNodeC->nIndexLeft);
  sMNP* l_psNodeE = _LocateNode(l_psNodeC->nIndexRight);
  sMNP* l_psNodeP = _LocateNode(l_psNodeA->nIndexParent);
  sMNP* l_psNodeQ = _LocateNode(l_psNodeB->nIndexLeft); // Cache Bl

  if(l_psNodeA->nIndexParent != -1)
  { // If A have a parent, switch it's child to C
    if(l_psNodeP->nIndexLeft == l_psNodeA->nIndexNode)
    {
      l_psNodeP->nIndexLeft = l_psNodeC->nIndexParent;
    }
    else
    {
      l_psNodeP->nIndexRight = l_psNodeC->nIndexParent;
    }
  }
  else
  { // If A was root, now it's B turn to be root
    mp_psNodeRoot = l_psNodeC;
  }

  // Set A's parent as C's new parent
  //     A
  //    /|\
  //   B P Ar
  //  / \|
  // Bl  C
  //    / \
  //   D   E
  l_psNodeC->nIndexParent = l_psNodeA->nIndexParent;

  // Set B as C's left child
  //      A
  //     /|\
  //    / P Ar
  //   |  |
  //   |  C
  //   | / \
  //   BD   E
  //  /
  // Bl
  l_psNodeC->nIndexLeft   = l_psNodeB->nIndexNode;

  // Set A as C's right child
  //         P
  //        /|
  //       / |
  //      C  |
  //     / \ |
  //   BD---EA
  //  /       \
  // Bl        Ar
  l_psNodeC->nIndexRight  = l_psNodeA->nIndexNode;

  // Set C as A's new parent
  //      P
  //      |
  //      C
  //     / \
  //   BD---EA
  //  /       \
  // Bl        Ar
  l_psNodeA->nIndexParent = l_psNodeC->nIndexNode;

  // Set C as B's new parent
  //      P
  //      |
  //      C
  //     / \
  //   BD   EA
  //  /       \
  // Bl        Ar
  l_psNodeB->nIndexParent = l_psNodeC->nIndexNode;

  if(l_psNodeD != NULL)
  { // Set D as B's right child
    //     P
    //     |
    //     C
    //    /|\
    //   B | EA
    //  / \|   \
    // Bl  D    Ar
    l_psNodeB->nIndexRight  = l_psNodeD->nIndexNode;

    // Set B as D's new parent
    //     P
    //     |
    //     C
    //    / \
    //   B   EA
    //  / \    \
    // Bl  D    Ar
    l_psNodeD->nIndexParent = l_psNodeB->nIndexNode;
  }
  else
  {
    //     P
    //     |
    //     C
    //    / \
    //   B   EA
    //  /      \
    // Bl       Ar
    l_psNodeB->nIndexRight = -1;
  }

  if(l_psNodeE != NULL)
  { // Set E as A's left child
    //      P
    //      |
    //      C
    //    /  |\
    //   B   | A
    //  / \  |/ \
    // Bl  D E   Ar
    l_psNodeA->nIndexLeft   = l_psNodeE->nIndexNode;

    // Set A as E's new parent
    //      P
    //      |
    //      C
    //    /   \
    //   B     A
    //  / \   / \
    // Bl  D E   Ar
    l_psNodeE->nIndexParent = l_psNodeA->nIndexNode;
  }
  else
  {
    //     P
    //     |
    //     C
    //    / \
    //   B   A
    //  / \   \
    // Bl  D   Ar
    l_psNodeA->nIndexLeft = -1;
  }

  // Cache Ar
  l_psNodeP = _LocateNode(l_psNodeA->nIndexRight);

  // Cache Bl
//  l_psNodeQ = _LocateNode(l_psNodeB->nIndexLeft);

  if(l_psNodeD != NULL)
  {
    // Set A's height and balance
    l_psNodeA->nHeight  = l_psNodeP->nHeight + 1;
    l_psNodeA->nBalance = -1;

    if(l_psNodeQ->nHeight >= l_psNodeD->nHeight)
    {
      l_psNodeB->nHeight = l_psNodeQ->nHeight;
    }
    else
    {
      l_psNodeB->nHeight = l_psNodeD->nHeight;
    }
    
    // Set B's height and balance
    l_psNodeB->nHeight += 1;
    l_psNodeB->nBalance = l_psNodeQ->nHeight - l_psNodeD->nHeight;
  }
  else
  {
    if(l_psNodeE != NULL)
    {
      if(l_psNodeE->nHeight >= l_psNodeP->nHeight)
      {
        l_psNodeA->nHeight = l_psNodeE->nHeight;
      }
      else
      {
        l_psNodeA->nHeight = l_psNodeP->nHeight;
      }
    
      // Set A's height and balance
      l_psNodeA->nHeight += 1;
      l_psNodeA->nBalance = l_psNodeE->nHeight - l_psNodeP->nHeight;

      // Set B's height and balance
      l_psNodeB->nHeight  = l_psNodeQ->nHeight + 1;
      l_psNodeB->nBalance = 1;
    }
    else
    {
      l_psNodeA->nHeight  = 0;
      l_psNodeA->nBalance = 0;

      l_psNodeB->nHeight  = 0;
      l_psNodeB->nBalance = 0;
    }
  }

  if(l_psNodeB->nHeight >= l_psNodeA->nHeight)
  {
    l_psNodeC->nHeight = l_psNodeB->nHeight;
  }
  else
  {
    l_psNodeC->nHeight = l_psNodeA->nHeight;
  }

  // Set C's height and balance
  l_psNodeC->nHeight += 1;
  l_psNodeC->nBalance = l_psNodeB->nHeight - l_psNodeA->nHeight;
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
void CMemoryTreeAvl::_RotateRL
( int i_nNodeA
)
{
  //   P                      P
  //   |                      |
  //   A                      C
  //  / \                   /   \
  // Al  B    _RotateRL    A     B
  //    / \     ---->     / \   / \
  //   C   Br            Al  D E   Br
  //  / \
  // D   E

  sMNP* l_psNodeA = _LocateNode(i_nNodeA);
  sMNP* l_psNodeB = _LocateNode(l_psNodeA->nIndexRight);
  sMNP* l_psNodeC = _LocateNode(l_psNodeB->nIndexLeft);
  sMNP* l_psNodeD = _LocateNode(l_psNodeC->nIndexLeft);
  sMNP* l_psNodeE = _LocateNode(l_psNodeC->nIndexRight);
  sMNP* l_psNodeP = _LocateNode(l_psNodeA->nIndexParent);
  sMNP* l_psNodeQ = _LocateNode(l_psNodeB->nIndexRight); // Cache Br

  if(l_psNodeA->nIndexParent != -1)
  { // If A have a parent, switch it's child to C
    if(l_psNodeP->nIndexLeft == l_psNodeA->nIndexNode)
    {
      l_psNodeP->nIndexLeft  = l_psNodeC->nIndexNode;
    }
    else
    {
      l_psNodeP->nIndexRight = l_psNodeC->nIndexNode;
    }
  }
  else
  { // If A was root, now it's B turn to be root
    mp_psNodeRoot = l_psNodeC;
  }

  // Set A's parent as C's new parent
  //    P
  //    |
  //    A
  //   /|\
  // Al P B
  //    |/ \
  //    C   Br
  //   / \
  //  D   E
  l_psNodeC->nIndexParent = l_psNodeA->nIndexParent;

  // Set A as C's left child
  //   P
  //   |\
  //   | C
  //   |/|\
  //   AD| E
  //  / \|
  // Al  B
  //      \
  //       Br
  l_psNodeC->nIndexLeft = l_psNodeA->nIndexNode;

  // Set B as C's right child
  //   P
  //   |\
  //   | C
  //   |/ \
  //   AD--BE
  //  /     \
  // Al      Br
  l_psNodeC->nIndexRight = l_psNodeB->nIndexNode;

  // Set C as A's new parent
  //     P
  //     |
  //     C
  //    / \
  //   AD--BE
  //  /     \
  // Al      Br
  l_psNodeA->nIndexParent = l_psNodeC->nIndexNode;

  // Set C as B's new parent
  //     P
  //     |
  //     C
  //    / \
  //   AD  BE
  //  /     \
  // Al      Br
  l_psNodeB->nIndexParent = l_psNodeC->nIndexNode;

  if(l_psNodeD != NULL)
  { // Set D as A's right child
    //     P
    //     |
    //     C
    //    /|\
    //   A-D BE
    //  /     \
    // Al      Br
    l_psNodeA->nIndexRight  = l_psNodeD->nIndexNode;

    // Set A as D's new parent
    //     P
    //     |
    //     C
    //    / \
    //   A   BE
    //  / \   \
    // Al  D   Br
    l_psNodeD->nIndexParent = l_psNodeA->nIndexNode;
  }
  else
  {
    //     P
    //     |
    //     C
    //    / \
    //   A   BE
    //  /     \
    // Al      Br
    l_psNodeA->nIndexRight = -1;
  }

  if(l_psNodeE != NULL)
  { // Set E as B's left child
    //     P
    //     |
    //     C
    //    /|\
    //   A E-B
    //  / \   \
    // Al  D   Br
    l_psNodeB->nIndexLeft   = l_psNodeE->nIndexNode;

    // Set B as E's new parent
    //      P
    //      |
    //      C
    //    /   \
    //   A     B
    //  / \   / \
    // Al  D E  Br
    l_psNodeE->nIndexParent = l_psNodeB->nIndexNode;
  }
  else
  {
    l_psNodeB->nIndexLeft = -1;
  }

  // Cache Al
  l_psNodeP = _LocateNode(l_psNodeA->nIndexLeft);

  // Cache Br
//  l_psNodeQ = _LocateNode(l_psNodeB->nIndexRight);

  if(l_psNodeD != NULL)
  {
    if(l_psNodeP->nHeight >= l_psNodeD->nHeight)
    {
      l_psNodeA->nHeight = l_psNodeP->nHeight;
    }
    else
    {
      l_psNodeA->nHeight = l_psNodeD->nHeight;
    }

    // Set A's height and balance
    l_psNodeA->nHeight += 1;
    l_psNodeA->nBalance = l_psNodeP->nHeight - l_psNodeD->nHeight;

    // Set B's height and balance
    l_psNodeB->nHeight  = l_psNodeQ->nHeight + 1;
    l_psNodeB->nBalance = -1;
  }
  else
  {
    if(l_psNodeE != NULL)
    { // Set A's height and balance
      l_psNodeA->nHeight  = l_psNodeP->nHeight + 1;
      l_psNodeA->nBalance = 1;

      if(l_psNodeE->nHeight >= l_psNodeQ->nHeight)
      {
        l_psNodeB->nHeight = l_psNodeE->nHeight;
      }
      else
      {
        l_psNodeB->nHeight = l_psNodeQ->nHeight;
      }

      // Set B's height and balance
      l_psNodeB->nHeight += 1;
      l_psNodeB->nBalance = l_psNodeE->nHeight - l_psNodeQ->nHeight;
    }
    else
    {
      l_psNodeA->nHeight  = 0;
      l_psNodeA->nBalance = 0;

      l_psNodeB->nHeight  = 0;
      l_psNodeB->nBalance = 0;
    }
  }

  if(l_psNodeA->nHeight >= l_psNodeB->nHeight)
  {
    l_psNodeC->nHeight = l_psNodeA->nHeight;
  }
  else
  {
    l_psNodeC->nHeight = l_psNodeB->nHeight;
  }

  // Set C's height and balance
  l_psNodeC->nHeight += 1;
  l_psNodeC->nBalance = l_psNodeA->nHeight - l_psNodeB->nHeight;
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
void CMemoryTreeAvl::_RotateRR
( int i_nNodeA
)
{
  //   P                       P
  //   |                       |
  //   A                       B
  //  / \                    /   \
  // Al  B     _RotateRR    A     Br
  //    / \      ---->     / \   / \
  //   C   Br             Al  C Brl Brr
  //      / \
  //     Brl Brr

  sMNP* l_psNodeA = _LocateNode(i_nNodeA);
  sMNP* l_psNodeB = _LocateNode(l_psNodeA->nIndexRight);
  sMNP* l_psNodeC = _LocateNode(l_psNodeB->nIndexLeft);
  sMNP* l_psNodeP = _LocateNode(l_psNodeA->nIndexParent);

  if(l_psNodeA->nIndexParent != -1)
  { // If A have a parent, switch it's child to B
    if(l_psNodeP->nIndexLeft == l_psNodeA->nIndexNode)
    {
      l_psNodeP->nIndexLeft  = l_psNodeB->nIndexNode;
    }
    else
    {
      l_psNodeP->nIndexRight = l_psNodeB->nIndexNode;
    }
  }
  else
  { // If A was root, now it's B turn to be root
    mp_psNodeRoot = l_psNodeB;
  }

  // Set A's parent as B's new parent
  //     P
  //    /|
  //   A |
  //  / \|
  // Al  B
  //    / \
  //   C   Br
  //      / \
  //     Brl Brr
  l_psNodeB->nIndexParent = l_psNodeA->nIndexParent;

  // Set A as left child of B (B is greater than A)
  //    P
  //    |\
  //    | B
  //    |/|\
  //    A C Br
  //   /   / \
  // Al   Brl Brr
  l_psNodeB->nIndexLeft = l_psNodeA->nIndexNode;

  // Set B as new A's parent
  //      P
  //      |
  //      B
  //     /|\
  //    A C Br
  //   /   / \
  // Al   Brl Brr
  l_psNodeA->nIndexParent = l_psNodeB->nIndexNode;

  if(l_psNodeC != NULL)
  { // Set C as A's right child (C is greater than A, but less than B)
    //       P
    //       |
    //       B
    //     / | \
    //    A--C  Br
    //   /     / \
    // Al     Brl Brr
    l_psNodeA->nIndexRight  = l_psNodeC->nIndexNode;

    // Set A as C's new parent
    //       P
    //       |
    //       B
    //     /   \
    //    A     Br
    //   / \   / \
    // Al   C Brl Brr
    l_psNodeC->nIndexParent = l_psNodeA->nIndexNode;

    // Cache Al -> Set A's height and balance
    l_psNodeP = _LocateNode(l_psNodeA->nIndexLeft);

    if(l_psNodeP->nHeight >= l_psNodeC->nHeight)
    {
      l_psNodeA->nHeight = l_psNodeP->nHeight;
    }
    else
    {
      l_psNodeA->nHeight = l_psNodeC->nHeight;
    }

    l_psNodeA->nHeight += 1;
    l_psNodeA->nBalance = l_psNodeP->nHeight - l_psNodeC->nHeight;
  }
  else
  {
    l_psNodeA->nIndexRight = -1 ;

    l_psNodeA->nHeight  = 0;
    l_psNodeA->nBalance = 0;
  }

  // Cache Br -> Set B's height and balance
  l_psNodeP = _LocateNode(l_psNodeB->nIndexRight);

  if(l_psNodeA->nHeight >= l_psNodeP->nHeight)
  {
    l_psNodeB->nHeight = l_psNodeA->nHeight;
  }
  else
  {
    l_psNodeB->nHeight = l_psNodeP->nHeight;
  }

  l_psNodeB->nHeight += 1;
  l_psNodeB->nBalance = l_psNodeA->nHeight - l_psNodeP->nHeight;
} // 100 %
