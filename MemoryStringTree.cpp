// MemoryStringTree.cpp: implementation of the CMemoryStringTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE DE CHAINE AUTO-DIMENSIONNABLE ===========================================================================

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
CMemoryStringTree::CMemoryStringTree
( const char* i_panStrName // = "CMemoryStringTree"
)
{
#ifdef _DEBUG
  SetClassName(i_panStrName); // Default object name

  _SetClassType("CMemoryStringTree");

  mp_oTreeString.SetClassName(mp_oStrObjectName+"::mp_oTreeString");
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
void CMemoryStringTree::SetClassName
( const char* i_panStrName
)
{
#ifdef _DEBUG
  CMemoryStringArray::SetClassName(i_panStrName); // Default object name

  _SetClassType("CMemoryStringTree");

  mp_oTreeString.SetClassName(mp_oStrObjectName+"::mp_oTreeString");
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
int CMemoryStringTree::AddString
( char* i_panStringBuffer
, int   i_nNodeData    // = 0
, int   i_nStringIndex // = -1
)
{ // Add a string (starting from another string)
  sMSP  l_sStringPointer = {0, 0, 0, 0};
  sMSP* l_psMSP;
  int   l_nStringIndex   = -1;
  int   l_nStringSize;
  int   l_nStringHole;

  if(i_panStringBuffer != NULL)
  {
    _EncodeString(l_sStringPointer, i_panStringBuffer);

#ifndef TEST_NEWMETHOD
    l_nStringIndex = mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase, i_nStringIndex);
#else // TEST_NEWMETHOD
    l_nStringIndex = mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
#endif // TEST_NEWMETHOD

    if(l_nStringIndex != -1)
    { // The string is already in the buffer
      mp_oTreeString.IncNodeCount(l_nStringIndex);
    }
    else
    { // Get string size
#ifndef TEST_NEWMETHOD
      l_nStringSize  = GetStringLength(i_panStringBuffer); // Includes the trailing Null char
#else // TEST_NEWMETHOD
      l_nStringSize  = l_sStringPointer.nLength; // Includes the trailing Null char
#endif // TEST_NEWMETHOD
      l_nStringHole  = ALIGN(l_nStringSize);
    
      // Get a old/new node
      l_nStringIndex = mp_oTreeString.AllocNode(l_sStringPointer.nHashNoCase, l_nStringSize);
//      l_nStringIndex = mp_oTreeString.AddNode(&buffer, l_sStringPointer.nHashNoCase); // <- IMPOSSIBLE

      // Set string properties
      mp_oTreeString.SetNodeSize(l_nStringIndex, l_nStringSize);

      // Set string properties
      if(mp_oTreeString.GetNodeHole(l_nStringIndex) == 0)
      {
        mp_oTreeString.SetNodeHole(l_nStringIndex, l_nStringHole);
      }
      else{}

      // Get string descriptor
      l_psMSP = (sMSP*) mp_oTreeString.GetSlotPointer(l_nStringIndex);

      // Stack the string in the buffer
#ifndef TEST_NEWMETHOD
      l_sStringPointer.nLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize, (l_psMSP->nHashRaw != 0) ? l_psMSP->nLocation : -1);
#else // TEST_NEWMETHOD
      mp_oTreeString.SetNodeData
      ( l_nStringIndex
      , _StreamString
        ( i_panStringBuffer
        , l_nStringHole
        , l_nStringSize
        , (l_psMSP->nHashRaw != 0)
        ? mp_oTreeString.GetNodeData(l_nStringIndex)
        : -1
        )
      );
#endif // TEST_NEWMETHOD

      // Put the string descriptor in the tree
      *(l_psMSP) = l_sStringPointer;

      // Connect or reconnect the string
      mp_oTreeString.ConnectNode(l_nStringIndex, l_sStringPointer.nHashNoCase, i_nNodeData);
    }
  }
  else{}

  return l_nStringIndex;
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
int CMemoryStringTree::InsertString
( char* i_panStringBuffer
, int   i_nNodeData    // = 0
, int   i_nStringIndex // = -1
)
{ // Insert a string (starting from another string)
  return AddString
  ( i_panStringBuffer
  , i_nNodeData
  , i_nStringIndex
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
int CMemoryStringTree::FindTriesHead
( char* i_panStringBuffer
)
{
  sMSP  l_sStringPointer = {0, 0, 0, 0};
  int   l_nStringIndex   = -1;
  int   l_nLoop          = GetStringLength(i_panStringBuffer) - 1;
  char* l_panTest;

  while
  (
       (l_nLoop > 0)
    && (l_nStringIndex == -1)
  )
  {
    _EncodeString(l_sStringPointer, i_panStringBuffer, l_nLoop);
   
    // Look if the substring is known
#ifndef TEST_NEWMETHOD
    l_nStringIndex = mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase);
#else // TEST_NEWMETHOD
    l_nStringIndex = mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
#endif // TEST_NEWMETHOD

    if(l_nStringIndex != -1)
    { // Test for coherence
      l_panTest = GetStringPointer(l_nStringIndex);
      if
      (
        SCMP
        ( l_panTest
        , i_panStringBuffer
        , FALSE
        , FALSE
        , GetStringLength(l_panTest) - 1
        )
        != 0
      )
      { // Wrong index
        l_nStringIndex = -1;
      }
      else{}
    }
    else{}

/*
    if(l_nStringIndex != -1)
    { // Test first 4 char for coherence
      if(*((int*) GetStringPointer(l_nStringIndex)) != *((int*) i_panStringBuffer))
      { // Wrong index
        l_nStringIndex = -1;
      }
      else{}
    }
    else{}
*/
    l_nLoop -= 1;
  }

  return l_nStringIndex;
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
int CMemoryStringTree::FindTriesTail
( char* i_panStringBuffer
)
{
  sMSP l_sStringPointer = {0, 0, 0, 0};
  int  l_nStringIndex   = -1;
  int  l_nStringLenght  = GetStringLength(i_panStringBuffer) - 1;
  int  l_nLoop          = l_nStringLenght;

  while
  (
       (l_nLoop > 0)
    && (l_nStringIndex == -1)
  )
  { // Encode up to the last 16 characters
    _EncodeString(l_sStringPointer, i_panStringBuffer + l_nLoop);
    
#ifndef TEST_NEWMETHOD
    l_nStringIndex = mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase);
#else // TEST_NEWMETHOD
    l_nStringIndex = mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
#endif // TEST_NEWMETHOD

    l_nLoop -= 1;
  }

  return l_nStringIndex;
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
char* CMemoryStringTree::FindTriesQueue
( char* i_panStringBuffer
)
{
  int l_nStringIndex = FindTriesHead(i_panStringBuffer);

  if(l_nStringIndex != -1)
  {
    return i_panStringBuffer + GetStringLength(l_nStringIndex) - 1;
  }
  else
  {
    return i_panStringBuffer;
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
int CMemoryStringTree::_SearchString
( const char* i_panStringBuffer
,       int   i_nStringIndex // = -1
)
{
  int   l_nLoop        = 0;
  int   l_nStringIndex = i_nStringIndex;
  char* l_panString    = GetStringPointer(l_nStringIndex);

  while(l_panString != NULL)
  {
    if(i_panStringBuffer[l_nLoop] == l_panString[l_nLoop])
    {
      l_nLoop += 1;
    }
    else
    {
      if(i_panStringBuffer[l_nLoop] < l_panString[l_nLoop])
      {
        l_nStringIndex = mp_oTreeString.GetNodeLeft(l_nStringIndex);
      }
      else
      {
        l_nStringIndex = mp_oTreeString.GetNodeRight(l_nStringIndex);
      }

      l_panString = GetStringPointer(l_nStringIndex);
    }
  }

  return l_nStringIndex;
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
void CMemoryStringTree::_ConnectString
( int i_nStringIndex
)
{
  int   l_nLoop           = 0;
  int   l_nStringIndex    = i_nStringIndex;
  int   l_nStringPrev     = l_nStringIndex;
  char* l_panStringBuffer = GetStringPointer(l_nStringIndex);
  char* l_panStringTree   = GetStringPointer(-1);
  char  l_nResult;

  while(l_panStringTree != NULL)
  {
    l_nResult = l_panStringBuffer[l_nLoop] - l_panStringTree[l_nLoop];

    if(l_nResult == 0)
    {
      l_nLoop += 1;
    }
    else
    {
      l_nStringPrev = l_nStringIndex;

      if(l_nResult < 0)
      {
        l_nStringIndex = mp_oTreeString.GetNodeLeft(l_nStringIndex);
      }
      else
      {
        l_nStringIndex = mp_oTreeString.GetNodeRight(l_nStringIndex);
      }

      if(l_nStringIndex == -1)
      {
        if(l_nResult < 0)
        {
          mp_oTreeString.SetNodeLeft(l_nStringPrev, i_nStringIndex);
        }
        else
        {
          mp_oTreeString.SetNodeRight(l_nStringPrev, i_nStringIndex);
        }
      }
      else
      {
        l_panStringTree = GetStringPointer(l_nStringIndex);
      }
    }
  }
}

