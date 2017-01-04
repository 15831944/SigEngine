// MemoryStringPool.cpp: implementation of the CMemoryStringPool class.
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
CMemoryStringPool::CMemoryStringPool
( const char* i_panStringName // = "CMemoryStringPool"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryStringPool");

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
CMemoryStringPool::~CMemoryStringPool()
{
#ifdef _DEBUG
  TRACE
  ( "%s::~%s : %d/%d (%d%%) unused bytes left (%d/%d string%s free)\n"
  , (CString) mp_oStrObjectName
  , (CString) mp_oStrObjectClass
  , GetBufferFree()
  , GetBufferSize()
  , (int) (((LONGLONG) GetBufferFree() * 100) / GetBufferSize())
  , mp_oTreeString.GetSlotFree()
  , mp_oTreeString.GetSlotTotal()
  , (mp_oTreeString.GetSlotFree() > 1) ? "s" : ""
  );
#endif // _DEBUG

  _DeleteBuffer();
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
int CMemoryStringPool::CreateBuffer
( int  i_nBufferSize
, BOOL i_bZeroMemory
)
{
  if(i_nBufferSize <= 0)
  { // Test slot size
#ifdef _DEBUG
    TRACE
    ( "ERROR : %s::CreateBuffer(i_nBufferSize <= 0) = Wrong buffer size\n"
    , (CString) mp_oStrObjectName
    );
    
//    ASSERT(!(i_nBufferSize <= 0));
#endif // _DEBUG

    return (-1);
  }
  else
  { // Everything OK
    mp_bZeroMemory = i_bZeroMemory;

    // Delete the previous buffers
    _DeleteBuffer();

    // Create string descriptor tree
    if((i_nBufferSize >> 6) == 0)
    {
      mp_oTreeString.CreateBuffer
      ( sizeof(sMSP)
      , 8 // 8 strings
      );
    }
    else
    {
      mp_oTreeString.CreateBuffer
      ( sizeof(sMSP)
      , i_nBufferSize >> 6 // Average of 64 bytes per string
      );
    }

    sMBP l_sTempoMBP;

    // Create the new buffer
    l_sTempoMBP.nBufferSize   = ALIGN(i_nBufferSize); // 8 bytes boundary, helps 64 bits CPU
    l_sTempoMBP.panBuffer     = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)] + sizeof(sMBP);
    l_sTempoMBP.panBufferPrev = NULL;
    l_sTempoMBP.panBufferNext = NULL;
    l_sTempoMBP.nBufferBegin  = 0;
    l_sTempoMBP.nBufferHead   = 0;
    l_sTempoMBP.nBufferTail   = 0;
    l_sTempoMBP.nBufferEnd    = l_sTempoMBP.nBufferSize;

    // Zero memory if needed
    if(mp_bZeroMemory == TRUE)
    {
      ZeroMemory
      ( l_sTempoMBP.panBuffer
      , l_sTempoMBP.nBufferSize
      );
    }
    else{}

    // Copy sMBP chunk at the beginning of the buffer
    mp_psBufferFirst = (sMBP*) l_sTempoMBP.panBuffer - 1;
    *(mp_psBufferFirst) = l_sTempoMBP;

    // Double linked buffers
    mp_psBufferTail = mp_psBufferFirst;
    mp_psBufferPrev = mp_psBufferFirst;

#ifdef _DEBUG
    TRACE
    ( "%s::CreateBuffer(BufferSize = %d, ZeroMemory = %s)\n"
    , (CString) mp_oStrObjectName
    , i_nBufferSize
    , (mp_bZeroMemory  == TRUE) ? "YES" : "NO"
    );
#endif // _DEBUG

    return true;
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
int CMemoryStringPool::AddStringHead
( const char* i_panStringBuffer
,       bool  i_bForce // = false
)
{
  sMSP l_sStringPointer = {0, 0, 0, 0};

  _EncodeString(l_sStringPointer, i_panStringBuffer);

#ifndef TEST_NEWMETHOD
  int l_nStringIndex = mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase);
#else // TEST_NEWMETHOD
  int l_nStringIndex = mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
  int l_nStringLocation;
#endif // TEST_NEWMETHOD
  int l_nStringSize;
  int l_nStringHole;

  if
  (
       (l_nStringIndex != -1)
    && (i_bForce == false)
  )
  { // The string is already in the buffer
    mp_oTreeString.SetNodeCount(l_nStringIndex, mp_oTreeString.GetNodeCount(l_nStringIndex) + 1);
  }
  else
  { // Get string size
#ifndef TEST_NEWMETHOD
    l_nStringSize  = GetStringLength(i_panStringBuffer);
#else // TEST_NEWMETHOD
    l_nStringSize  = l_sStringPointer.nLength;
#endif // TEST_NEWMETHOD
    l_nStringHole  = ALIGN(l_nStringSize);
    
    // Stack the string in the buffer
#ifndef TEST_NEWMETHOD
    l_sStringPointer.nLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#else // TEST_NEWMETHOD
    l_nStringLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#endif // TEST_NEWMETHOD

    // Add the string descriptor in the tree
    l_nStringIndex = mp_oTreeString.AddSlotHead((BYTE*) &l_sStringPointer);

    // Set string properties
    mp_oTreeString.SetNodeSize(l_nStringIndex, l_nStringSize);
    mp_oTreeString.SetNodeHole(l_nStringIndex, l_nStringHole);
    mp_oTreeString.SetNodeCount(l_nStringIndex, 1);
#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
    mp_oTreeString.SetNodeData(l_nStringIndex, l_nStringLocation);
#endif // TEST_NEWMETHOD
  }

  return l_nStringIndex;
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
int CMemoryStringPool::AddStringTail
( const char* i_panStringBuffer
,       bool  i_bForce // = false
)
{
  sMSP  l_sStringPointer = {0, 0, 0, 0};
  sMSP* l_psMSP;
  int   l_nStringIndex = -1;
  int   l_nStringSize;
  int   l_nStringHole;
#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
  int   l_nStringLocation;
#endif // TEST_NEWMETHOD

  if(i_panStringBuffer != NULL)
  {
    if(*i_panStringBuffer != 0)
    {
      _EncodeString(l_sStringPointer, i_panStringBuffer);

#ifndef TEST_NEWMETHOD
      l_nStringIndex = mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase);
#else // TEST_NEWMETHOD
      l_nStringIndex = mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
#endif // TEST_NEWMETHOD

      if
      (
           (l_nStringIndex != -1)
        && (i_bForce == false)
      )
      { // The string is already in the buffer
        mp_oTreeString.SetNodeCount(l_nStringIndex, mp_oTreeString.GetNodeCount(l_nStringIndex) + 1);
      }
      else
      { // Get string size
#ifndef TEST_NEWMETHOD
        l_nStringSize  = GetStringLength(i_panStringBuffer);
#else // TEST_NEWMETHOD
        l_nStringSize  = l_sStringPointer.nLength;
#endif // TEST_NEWMETHOD
        l_nStringHole  = ALIGN(l_nStringSize);
    
        // Stack the string in the buffer
#ifndef TEST_NEWMETHOD
        l_sStringPointer.nLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#else // TEST_NEWMETHOD
        l_nStringLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#endif // TEST_NEWMETHOD

        // Add the string descriptor in the tree
        l_nStringIndex = mp_oTreeString.AddSlotTail((BYTE*) &l_sStringPointer);

        // Set string properties
        mp_oTreeString.SetNodeSize(l_nStringIndex, l_nStringSize);
        mp_oTreeString.SetNodeHole(l_nStringIndex, l_nStringHole);
        mp_oTreeString.SetNodeCount(l_nStringIndex, 1);
#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
        mp_oTreeString.SetNodeData(l_nStringIndex, l_nStringLocation);
#endif // TEST_NEWMETHOD
      }
    }
    else
    { // Queue empty string
      l_psMSP = (sMSP*) mp_oTreeString.GetSlotPointer(0);

      if(l_psMSP != NULL)
      { // Try to get the first NULL char to stuff an empty string
#ifndef TEST_NEWMETHOD
        l_sStringPointer.nLocation = mp_oTreeString.GetNodeSize(0) + 1;
#else // TEST_NEWMETHOD
        l_sStringPointer.nLength   = 0;
        l_nStringLocation = mp_oTreeString.GetNodeSize(0) + 1;
#endif // TEST_NEWMETHOD
      }
      else{}

      l_nStringIndex = mp_oTreeString.AddSlotTail((BYTE*) &l_sStringPointer);

      // Set string properties
      mp_oTreeString.SetNodeSize(l_nStringIndex, 0);
      mp_oTreeString.SetNodeHole(l_nStringIndex, 0);
      mp_oTreeString.SetNodeCount(l_nStringIndex, 1);
#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
      mp_oTreeString.SetNodeData(l_nStringIndex, l_nStringLocation);
#endif // TEST_NEWMETHOD
    }
  }
  else{}

  return l_nStringIndex;
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
void CMemoryStringPool::operator +=
( const char* i_panStringBuffer
)
{
  AddStringTail(i_panStringBuffer);
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
int CMemoryStringPool::InsertStringAt
( const char* i_panStringBuffer
,       int   i_nStringIndex
)
{
  sMSP l_sStringPointer = {0, 0, 0, 0};

  _EncodeString(l_sStringPointer, i_panStringBuffer);

#ifndef TEST_NEWMETHOD
  int l_nStringIndex = mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase);
#else // TEST_NEWMETHOD
  int l_nStringIndex = mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
  int l_nStringLocation;
#endif // TEST_NEWMETHOD
  int l_nStringSize;
  int l_nStringHole;

  if(l_nStringIndex != -1)
  { // The string is already in the buffer
    mp_oTreeString.SetNodeCount(l_nStringIndex, mp_oTreeString.GetNodeCount(l_nStringIndex) + 1);
  }
  else
  { // Get string size
#ifndef TEST_NEWMETHOD
    l_nStringSize  = GetStringLength(i_panStringBuffer);
#else // TEST_NEWMETHOD
    l_nStringSize  = l_sStringPointer.nLength;
#endif // TEST_NEWMETHOD
    l_nStringHole  = ALIGN(l_nStringSize);
    
    // Stack the string in the buffer
#ifndef TEST_NEWMETHOD
    l_sStringPointer.nLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#else // TEST_NEWMETHOD
    l_nStringLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#endif // TEST_NEWMETHOD

    // Add the string descriptor in the tree
    l_nStringIndex = mp_oTreeString.InsertSlotAt((BYTE*) &l_sStringPointer, i_nStringIndex);

    // Set string properties
    mp_oTreeString.SetNodeSize(l_nStringIndex, l_nStringSize);
    mp_oTreeString.SetNodeHole(l_nStringIndex, l_nStringHole);
    mp_oTreeString.SetNodeCount(l_nStringIndex, 1);
#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
    mp_oTreeString.SetNodeData(l_nStringIndex, l_nStringLocation);
#endif // TEST_NEWMETHOD
  }

  return l_nStringIndex;
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
int CMemoryStringPool::InsertStringAfter
( const char* i_panStringBuffer
,       int   i_nStringIndex
)
{
  return InsertStringAt(i_panStringBuffer, i_nStringIndex + 1);
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
int CMemoryStringPool::InsertStringDicho
( const char* i_panStringBuffer
,       int   i_nByteToCompare  // = 4
,       BOOL  i_bBigEndian      // = FALSE
)
{
  sMSP l_sStringPointer = {0, 0, 0, 0};

  _EncodeString(l_sStringPointer, i_panStringBuffer);

#ifndef TEST_NEWMETHOD
  int l_nStringIndex = mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase);
#else // TEST_NEWMETHOD
  int l_nStringIndex = mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
  int l_nStringLocation;
#endif // TEST_NEWMETHOD
  int l_nStringSize;
  int l_nStringHole;

  if(l_nStringIndex != -1)
  { // The string is already in the buffer
    mp_oTreeString.SetNodeCount(l_nStringIndex, mp_oTreeString.GetNodeCount(l_nStringIndex) + 1);
  }
  else
  { // Get string size
#ifndef TEST_NEWMETHOD
    l_nStringSize  = GetStringLength(i_panStringBuffer);
#else // TEST_NEWMETHOD
    l_nStringSize  = l_sStringPointer.nLength;
#endif // TEST_NEWMETHOD
    l_nStringHole  = ALIGN(l_nStringSize);
    
    // Stack the string in the buffer
#ifndef TEST_NEWMETHOD
    l_sStringPointer.nLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#else // TEST_NEWMETHOD
    l_nStringLocation = _StreamString(i_panStringBuffer, l_nStringHole, l_nStringSize);
#endif // TEST_NEWMETHOD

    // Add the string descriptor in the tree
    l_nStringIndex = mp_oTreeString.InsertSlotDicho((BYTE*) &l_sStringPointer);

    // Set string properties
    mp_oTreeString.SetNodeSize(l_nStringIndex, l_nStringSize);
    mp_oTreeString.SetNodeHole(l_nStringIndex, l_nStringHole);
    mp_oTreeString.SetNodeCount(l_nStringIndex, 1);
#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
    mp_oTreeString.SetNodeData(l_nStringIndex, l_nStringLocation);
#endif // TEST_NEWMETHOD
  }

  return l_nStringIndex;
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
void CMemoryStringPool::RemoveStringAll
( void
)
{
  mp_psBufferFirst->nBufferBegin = 0;
  mp_psBufferFirst->nBufferHead  = 0;
  mp_psBufferFirst->nBufferTail  = 0;

  // Double linked buffers
  mp_psBufferTail = mp_psBufferFirst;
  mp_psBufferPrev = mp_psBufferFirst;

  // Free all string locators
  mp_oTreeString.RemoveNodeAll(); // RemoveSlotAll
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
int CMemoryStringPool::RemoveStringHead
( void
)
{
  return mp_oTreeString.RemoveSlotHead();
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
int CMemoryStringPool::RemoveStringTail
( void
)
{
  return mp_oTreeString.RemoveSlotTail();
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
int CMemoryStringPool::RemoveStringAt
( int i_nStringIndex
)
{
  return mp_oTreeString.RemoveSlotAt(i_nStringIndex);
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
int CMemoryStringPool::RemoveStringAfter
( int i_nStringIndex
)
{
  return mp_oTreeString.RemoveSlotAfter(i_nStringIndex);
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
void CMemoryStringPool::operator -=
( int i_nStringIndex
)
{
  RemoveStringAt(i_nStringIndex);
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
int CMemoryStringPool::Push
( const char* i_panStringBuffer
)
{
  return AddStringTail(i_panStringBuffer);
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
int CMemoryStringPool::Push
( void
)
{
  return mp_oTreeString.Push();
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
int CMemoryStringPool::Pop
( char* o_panStringBuffer
)
{
  return GetStringBuffer(o_panStringBuffer, mp_oTreeString.Pop(NULL));
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
char* CMemoryStringPool::Pop
( void
)
{
  return _LocateString(mp_oTreeString.Pop(NULL));
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
int CMemoryStringPool::GetStringLength
( const char* i_panStringBuffer
)
{
  int l_nStringLength = 1; // + Null char

  while(*i_panStringBuffer != 0)
  {
    i_panStringBuffer += 1;
    l_nStringLength   += 1;
  }

  return l_nStringLength;
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
int CMemoryStringPool::GetStringLength
( int i_nStringIndex
)
{
  return mp_oTreeString.GetNodeSize(i_nStringIndex);
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
int CMemoryStringPool::GetStringIndex
( const char* i_panStringBuffer
,       int   i_nStringLenght // = -1
)
{
  sMSP l_sStringPointer = {0, 0, 0, 0};

  _EncodeString(l_sStringPointer, i_panStringBuffer, i_nStringLenght);

#ifndef TEST_NEWMETHOD
  return mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase);
#else // TEST_NEWMETHOD
  return mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer);
#endif // TEST_NEWMETHOD
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
int CMemoryStringPool::GetStringCompare
( const char* i_panStringFrom
, const char* i_panStringTo
)
{
  while
  (
       (*i_panStringFrom != 0)
    && (*i_panStringTo   != 0)
    && (*i_panStringFrom != *i_panStringTo)
  )
  {
    i_panStringFrom += 1;
    i_panStringTo   += 1;
  }

  return *i_panStringFrom - *i_panStringTo;
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
int CMemoryStringPool::GetStringDiff
( const char* i_panStringFrom
, const char* i_panStringTo
)
{
  int l_nIndex = 0;

  while
  (
       (*i_panStringFrom != 0)
    && (*i_panStringTo   != 0)
    && (*i_panStringFrom != *i_panStringTo)
  )
  {
    i_panStringFrom += 1;
    i_panStringTo   += 1;
    l_nIndex        += 1;
  }

  return l_nIndex;
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
int CMemoryStringPool::GetStringCount
( int i_nStringIndex
)
{
  return mp_oTreeString.GetNodeCount(i_nStringIndex);
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
void CMemoryStringPool::SetStringCount
(          int i_nStringIndex
, unsigned int i_nStringCount
)
{
  mp_oTreeString.SetNodeCount(i_nStringIndex, i_nStringCount);
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
int CMemoryStringPool::IncStringCount
( int i_nStringIndex
)
{
  return mp_oTreeString.IncNodeCount(i_nStringIndex);
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
int CMemoryStringPool::DecStringCount
( int i_nStringIndex
)
{
  return mp_oTreeString.DecNodeCount(i_nStringIndex);
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
int CMemoryStringPool::GetStringData
( int i_nStringIndex
)
{
  return mp_oTreeString.GetNodeData(i_nStringIndex);
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
void CMemoryStringPool::SetStringData
( int i_nStringIndex
, int i_nStringData
)
{
  mp_oTreeString.SetNodeData(i_nStringIndex, i_nStringData);
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
int CMemoryStringPool::GetStringHole
( int i_nStringIndex
)
{
  return mp_oTreeString.GetNodeHole(i_nStringIndex);
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
int CMemoryStringPool::GetStringSize
( int i_nStringIndex
)
{
  return mp_oTreeString.GetNodeCount(i_nStringIndex);
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
int CMemoryStringPool::GetStringBuffer
( char* o_panStringBuffer
, int   i_nStringIndex
)
{
  char* l_panString = _LocateString(i_nStringIndex);
  int   l_nStringLenght;

  if(l_panString != NULL)
  {
    l_nStringLenght = mp_oTreeString.GetNodeSize(i_nStringIndex);

#ifdef USEMEMCPY
    MEMCPY
#else
    memcpy
#endif // USEMEMCPY
    ( o_panStringBuffer
    , l_panString
    , l_nStringLenght
    );

    return l_nStringLenght;
  }
  else
  {
    return 0;
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
int CMemoryStringPool::SetStringBuffer
( const char* i_panStringBuffer
,       int   i_nStringIndex
)
{
  int   l_nStringLenght = GetStringLength(i_panStringBuffer);
  int   l_nStringHole   = mp_oTreeString.GetNodeHole(i_nStringIndex);

  if(l_nStringLenght > l_nStringHole)
  {
    l_nStringLenght = l_nStringHole;
  }
  else{}

#ifdef USEMEMCPY
  MEMCPY
#else
  memcpy
#endif // USEMEMCPY
  ( _LocateString(i_nStringIndex)
  , (void*) i_panStringBuffer
  , l_nStringLenght
  );

  return l_nStringLenght;
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
char* CMemoryStringPool::GetStringPointer
( int i_nStringIndex
)
{
  return _LocateString(i_nStringIndex);
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
char* CMemoryStringPool::operator []
( int i_nStringIndex
)
{
  return GetStringPointer(i_nStringIndex);
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
void CMemoryStringPool::Sort
( void
)
{
  mp_oTreeString.SortInt();
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
void CMemoryStringPool::RemoveOnCountThreshold
( int i_nNodeCountMax
)
{
  mp_oTreeString.RemoveOnCountThreshold(i_nNodeCountMax);
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
int CMemoryStringPool::GetBufferSize
( void
)
{
  int l_nBufferSize = 0;

  // Get the right buffer
  sMBP* l_psMBP = (sMBP*) mp_psBufferFirst->panBuffer;

  while(l_psMBP != NULL)
  {
    l_psMBP -= 1;

    l_nBufferSize += l_psMBP->nBufferSize;

    l_psMBP = (sMBP*) l_psMBP->panBufferNext;
  }

  return l_nBufferSize;
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
int CMemoryStringPool::GetBufferFree
( void
)
{
  int l_nBufferFree = 0;

  // Get the right buffer
  sMBP* l_psMBP = (sMBP*) mp_psBufferFirst->panBuffer;

  while(l_psMBP != NULL)
  {
    l_psMBP -= 1;

    // Get the free space at the end of each block
    l_nBufferFree += l_psMBP->nBufferEnd - l_psMBP->nBufferTail;

    l_psMBP = (sMBP*) l_psMBP->panBufferNext;
  }

  return l_nBufferFree;
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
int CMemoryStringPool::GetStringCount
( const char* i_panStringBuffer
)
{
  sMSP l_sStringPointer = {0, 0, 0, 0};

  _EncodeString(l_sStringPointer, i_panStringBuffer);

#ifndef TEST_NEWMETHOD
  return mp_oTreeString.GetNodeCount(mp_oTreeString.GetNodeIndex(l_sStringPointer.nHashNoCase));
#else // TEST_NEWMETHOD
  return mp_oTreeString.GetNodeCount(mp_oTreeString.GetNodeIndexCRC(&l_sStringPointer));
#endif // TEST_NEWMETHOD
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
int CMemoryStringPool::GetStringTail
( void
)
{
  return mp_oTreeString.GetSlotTail();
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
int CMemoryStringPool::GetStringNumber
( void
)
{
  return mp_oTreeString.GetNodeNumber();
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
int CMemoryStringPool::GetStringSize
( void
)
{
  return 8;
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
int CMemoryStringPool::GetStringFree
( void
)
{
  return mp_oTreeString.GetSlotFree();
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
bool CMemoryStringPool::SaveToFile
( CFile& i_roFileOut
)
{
  sMBP  l_sTempoMBP;
  sMBP* l_psMBP = mp_psBufferFirst;

  // Tree saving first
  mp_oTreeString.SaveToFile(i_roFileOut);

  // Block informations

  // int   nBufferSize   = Size of the saved buffer, length to read back
  // char* panBuffer     = NULL
  // char* panBufferPrev = NULL
  // char* panBufferNext = NULL
  // int   nBufferBegin  = 0
  // int   nBufferHead   = 0
  // int   nBufferTail   = Tail location
  // int   nBufferEnd    = Size of struct sMBP

  l_sTempoMBP.nBufferSize   = mp_psBufferTail->nBufferTail;
  l_sTempoMBP.panBuffer     = NULL;
  l_sTempoMBP.panBufferPrev = NULL;
  l_sTempoMBP.panBufferNext = NULL;
  l_sTempoMBP.nBufferBegin  = 0;
  l_sTempoMBP.nBufferHead   = 0;
  l_sTempoMBP.nBufferTail   = mp_psBufferTail->nBufferTail;
  l_sTempoMBP.nBufferEnd    = sizeof(sMBP);

  i_roFileOut.Write
  ( &l_sTempoMBP
  , sizeof(sMBP)
  );

  l_psMBP = (sMBP*) mp_psBufferFirst->panBuffer;

  while(l_psMBP != NULL)
  { // Save all blocks up to the current defined tail, not further
    l_psMBP -= 1;

    if(l_psMBP->nBufferBegin < mp_psBufferTail->nBufferTail)
    {
      if(l_psMBP != mp_psBufferTail)
      { // Save the whole block
        i_roFileOut.Write
        ( l_psMBP->panBuffer
        , l_psMBP->nBufferSize
        );
      }
      else
      { // Save up to the tail
        i_roFileOut.Write
        ( l_psMBP->panBuffer
        , l_psMBP->nBufferTail - l_psMBP->nBufferBegin
        );
      }

      l_psMBP = (sMBP*) l_psMBP->panBufferNext;
    }
    else
    {
      l_psMBP = NULL;
    }
  }

  return true;
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
bool CMemoryStringPool::LoadFromFile
( CFile& i_roFileIn
)
{
  sMBP l_sTempoMBP;
  bool l_bResult = false;

  if(mp_oTreeString.LoadFromFile(i_roFileIn) == true)
  {
    if
    (
         i_roFileIn.Read
         ( &l_sTempoMBP
         , sizeof(sMBP)
         )
      == sizeof(sMBP)
    )
    {
      // int   nBufferSize   = Size of the saved buffer, length to read back
      // char* panBuffer     = NULL
      // char* panBufferPrev = NULL
      // char* panBufferNext = NULL
      // int   nBufferBegin  = 0
      // int   nBufferHead   = 0
      // int   nBufferTail   = Tail location
      // int   nBufferEnd    = Size of struct sMBP

      if(l_sTempoMBP.nBufferEnd == sizeof(sMBP))
      {
        if((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) != NULL)
        {
          _DeleteBuffer(); // Erase everything, we're changing of buffer

          mp_psBufferFirst = (sMBP*) l_sTempoMBP.panBuffer;

          // Double linked buffers
          mp_psBufferTail = mp_psBufferFirst;
          mp_psBufferPrev = mp_psBufferFirst;

          mp_psBufferFirst->nBufferSize   = l_sTempoMBP.nBufferSize;
          mp_psBufferFirst->panBufferPrev = NULL;
          mp_psBufferFirst->panBufferNext = NULL;
          mp_psBufferFirst->nBufferBegin  = 0;
          mp_psBufferFirst->nBufferHead   = 0;
          mp_psBufferFirst->nBufferTail   = l_sTempoMBP.nBufferTail;
          mp_psBufferFirst->nBufferEnd    = l_sTempoMBP.nBufferTail;

          l_sTempoMBP.panBuffer       += l_sTempoMBP.nBufferEnd; // sizeof(sMBP)
          mp_psBufferFirst->panBuffer  = l_sTempoMBP.panBuffer;

          if
          (
               i_roFileIn.Read
               ( l_sTempoMBP.panBuffer
               , l_sTempoMBP.nBufferSize
               )
            == l_sTempoMBP.nBufferSize
          )
          {
            return true;
          }
          else{}
        }
        else{}
      }
      else{}
    }
    else{}
  }
  else{}

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
void CMemoryStringPool::_DeleteBuffer
(
)
{
  sMBP* l_psMBP = mp_psBufferFirst;

  if(l_psMBP != NULL)
  {
    // Scan all blocks
    while(l_psMBP->panBufferNext != NULL)
    {
      l_psMBP = (sMBP*) l_psMBP->panBufferNext - 1;

      // Delete previous buffer, now out of scope
      delete [] ((sMBP*) ((sMBP*) l_psMBP->panBufferPrev - 1)->panBuffer - 1);
    }

    // Delete current remaining buffer
    delete [] ((sMBP*) l_psMBP->panBuffer - 1);
  }
  else{}

  mp_psBufferFirst = NULL;
  mp_psBufferTail  = NULL;
  mp_psBufferPrev  = NULL;
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
CMemoryStringPool::sMBP*
CMemoryStringPool::_ExpandBuffer
( int i_nByteReach
)
{
  sMBP* l_psMBP = _LocateBuffer(i_nByteReach);

  int  l_nDivider = 1;
  sMBP l_sTempoMBP;

  // New buffer to replace to old one, thus starting from 0
  l_sTempoMBP.panBufferPrev = NULL;
  l_sTempoMBP.panBufferNext = NULL;
  l_sTempoMBP.nBufferBegin  = 0;
  l_sTempoMBP.nBufferHead   = 0;
  l_sTempoMBP.nBufferTail   = mp_psBufferTail->nBufferTail;
  l_sTempoMBP.nBufferEnd    = 0;

  while(l_sTempoMBP.nBufferEnd < i_nByteReach)
  {
    l_sTempoMBP.nBufferEnd += mp_psBufferFirst->nBufferEnd;
  }

  l_sTempoMBP.nBufferSize = l_sTempoMBP.nBufferEnd;

  // Create the new buffer
  while
  (
       ((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) == NULL)
    && (l_nDivider < 8)
  )
  { // If buffer size is too big, try to allocate a smaller block
    do
    {
      if(l_sTempoMBP.nBufferEnd > i_nByteReach)
      { // Reduce
        l_sTempoMBP.nBufferEnd -= mp_psBufferFirst->nBufferEnd >> l_nDivider;
      }
      else
      { // Increase
        l_sTempoMBP.nBufferEnd += mp_psBufferFirst->nBufferEnd >> l_nDivider;
      }
    }
    while(l_sTempoMBP.nBufferEnd > i_nByteReach);

    l_sTempoMBP.nBufferSize = l_sTempoMBP.nBufferEnd;

    l_nDivider += 1;
  }

  if(l_sTempoMBP.panBuffer != NULL)
  {
    l_sTempoMBP.panBuffer += sizeof(sMBP);

    // Zero memory if needed
    if(mp_bZeroMemory == TRUE)
    {
      ZeroMemory
      ( l_sTempoMBP.panBuffer
      , l_sTempoMBP.nBufferSize
      );
    }
    else{}

    // Set the new chunk
    *((sMBP*) l_sTempoMBP.panBuffer - 1) = l_sTempoMBP;

#ifdef _DEBUG
    TRACE
    ( "%s::_ExpandBuffer(%d+%d->%d slot%s) moved from [0x%08X->0x%08X[ to [0x%08X->0x%08X[ (%d bytes)\n"
    , (CString) mp_oStrObjectName
    , GetStringNumber()
    , l_sTempoMBP.nBufferEnd - GetStringNumber()
    , l_sTempoMBP.nBufferEnd
    , (l_sTempoMBP.nBufferEnd > 1) ? "s" : ""
    , mp_psBufferFirst->panBuffer - sizeof(sMBP)
    , mp_psBufferFirst->panBuffer + mp_psBufferFirst->nBufferSize
    , l_sTempoMBP.panBuffer - sizeof(sMBP)
    , l_sTempoMBP.panBuffer + l_sTempoMBP.nBufferSize
    , l_sTempoMBP.nBufferSize + sizeof(sMBP)
    );
#endif // _DEBUG

    // To help memory mapping
    char* l_panArrayFrom;
    char* l_panArrayTo = l_sTempoMBP.panBuffer;
    int   l_nCopySize;

    l_psMBP = (sMBP*) mp_psBufferFirst->panBuffer;

    while(l_psMBP != NULL)
    { // Copy remaining blocks content
      l_psMBP -= 1; // - sizeof(sMBP)

      l_panArrayFrom = l_psMBP->panBuffer;

      if(l_psMBP->nBufferTail < i_nByteReach)
      {
        l_nCopySize = l_psMBP->nBufferTail - l_psMBP->nBufferBegin;
      }
      else
      {
        l_nCopySize = i_nByteReach - l_psMBP->nBufferTail;
      }

#ifdef USEMEMMOVE
      MEMMOVE
#else
      memmove
#endif // USEMEMMOVE
      ( l_panArrayTo   // New pool
      , l_panArrayFrom // Old pool
      , l_nCopySize    // Copy only used slots
      );

      l_panArrayTo += l_nCopySize;
      l_psMBP       = (sMBP*) l_psMBP->panBufferNext;
    }
    
    _DeleteBuffer(); // Delete old blocks

    mp_psBufferFirst = (sMBP*) l_sTempoMBP.panBuffer - 1; // Switch for the new block

    // Double linked buffers
    mp_psBufferTail = mp_psBufferFirst;
    mp_psBufferPrev = mp_psBufferFirst;
  
    return mp_psBufferFirst;
  }
  else
  {
#ifdef _DEBUG
    TRACE
    ( "ERROR : %s::_ExpandBuffer(FAILED) = Block misexpansion\n"
    , (CString) mp_oStrObjectName
    );
#endif // _DEBUG

    return NULL;
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
int CMemoryStringPool::_ReduceBuffer
( int i_nByteReach
)
{
  // Start from the farther slot to reach
  sMBP* l_psMBP = _LocateBuffer(1<<31);

  while
  (
       (l_psMBP > NULL)
    && (l_psMBP->nBufferBegin > i_nByteReach)
  )
  {
    if(l_psMBP->panBufferNext != NULL)
    {
      delete [] (sMBP*) (l_psMBP->panBufferNext - 1);
      l_psMBP->panBufferNext = NULL;
    }
    else{}

    l_psMBP = (sMBP*) (l_psMBP->panBufferPrev - 1);
  }

  mp_psBufferTail = l_psMBP;

  int  l_nDivider = 1;
  sMBP l_sTempoMBP;

  // New buffer to replace to old one, thus starting from 0
  l_sTempoMBP.panBufferPrev = NULL;
  l_sTempoMBP.panBufferNext = NULL;
  l_sTempoMBP.nBufferBegin    = 0;
  l_sTempoMBP.nBufferHead     = 0;
  l_sTempoMBP.nBufferTail     = 0;
  l_sTempoMBP.nBufferEnd      = 0;

  while(l_sTempoMBP.nBufferEnd < i_nByteReach)
  {
    l_sTempoMBP.nBufferEnd += mp_psBufferFirst->nBufferEnd;
  }

  l_sTempoMBP.nBufferSize = l_sTempoMBP.nBufferEnd;

  // Create the new buffer
  while
  (
       ((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) == NULL)
    && (l_nDivider < 8)
  )
  { // If buffer size is too big, try to allocate a smaller block
    do
    {
      if(l_sTempoMBP.nBufferEnd > i_nByteReach)
      { // Reduce
        l_sTempoMBP.nBufferEnd -= mp_psBufferFirst->nBufferEnd >> l_nDivider;
      }
      else
      { // Increase
        l_sTempoMBP.nBufferEnd += mp_psBufferFirst->nBufferEnd >> l_nDivider;
      }
    }
    while(l_sTempoMBP.nBufferEnd > i_nByteReach);

    l_nDivider += 1;
    
    l_sTempoMBP.nBufferSize = l_sTempoMBP.nBufferEnd;
  }

  if(l_sTempoMBP.panBuffer != NULL)
  {
    l_sTempoMBP.panBuffer += sizeof(sMBP);

    // Zero memory if needed
    if(mp_bZeroMemory == TRUE)
    {
      ZeroMemory
      ( l_sTempoMBP.panBuffer
      , l_sTempoMBP.nBufferSize
      );
    }
    else{}

    // Set the new chunk
    *((sMBP*) l_sTempoMBP.panBuffer - 1) = l_sTempoMBP;

#ifdef _DEBUG
    TRACE
    ( "%s::_ReduceBuffer(%d-%d->%d slot%s) moved from [0x%08X->0x%08X[ to [0x%08X->0x%08X[ (%d bytes)\n"
    , (CString) mp_oStrObjectName
    , GetStringNumber()
    , GetStringNumber() - l_sTempoMBP.nBufferEnd
    , l_sTempoMBP.nBufferEnd
    , (l_sTempoMBP.nBufferEnd > 1) ? "s" : ""
    , mp_psBufferFirst->panBuffer - sizeof(sMBP)
    , mp_psBufferFirst->panBuffer + mp_psBufferFirst->nBufferSize
    , l_sTempoMBP.panBuffer - sizeof(sMBP)
    , l_sTempoMBP.panBuffer + l_sTempoMBP.nBufferSize
    , l_sTempoMBP.nBufferSize + sizeof(sMBP)
    );
#endif // _DEBUG

    l_psMBP = (sMBP*) mp_psBufferFirst->panBuffer;

    // To help memory mapping
    char* l_panArrayFrom;
    char* l_panArrayTo = l_sTempoMBP.panBuffer;
    int   l_nCopySize;

    while(l_psMBP != NULL)
    { // Copy remaining blocks content
      l_psMBP -= 1; // - sizeof(sMBP)

      l_panArrayFrom = l_psMBP->panBuffer;

      if(l_psMBP->nBufferTail < i_nByteReach)
      {
        l_nCopySize = l_psMBP->nBufferTail - l_psMBP->nBufferBegin;
      }
      else
      {
        l_nCopySize = i_nByteReach - l_psMBP->nBufferTail;
      }

#ifdef USEMEMMOVE
      MEMMOVE
#else
      memmove
#endif // USEMEMMOVE
      ( l_panArrayTo   // New pool
      , l_panArrayFrom // Old pool
      , l_nCopySize    // Copy only used slots
      );

      l_panArrayTo += l_nCopySize;
      l_psMBP       = (sMBP*) mp_psBufferFirst->panBuffer;
    }
    
    _DeleteBuffer(); // Delete old blocks

    mp_psBufferFirst = (sMBP*) l_sTempoMBP.panBuffer - 1; // Switch for the new block

    // Double linked buffers
    mp_psBufferTail = mp_psBufferFirst;
    mp_psBufferPrev = mp_psBufferFirst;
  
    return mp_psBufferFirst->nBufferEnd;
  }
  else
  {
#ifdef _DEBUG
    TRACE
    ( "ERROR : %s::_ReduceBuffer(FAILED) = Block misreducing\n"
    , (CString) mp_oStrObjectName
    );
#endif // _DEBUG

    return (-1);
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
CMemoryStringPool::sMBP*
CMemoryStringPool::_LocateBuffer
( int i_nByteIndex
)
{
  if(i_nByteIndex == (1<<31))
  { // Get the farther end, beyon the tail
    mp_psBufferPrev = mp_psBufferTail;

    while(mp_psBufferPrev->panBufferNext != NULL)
    {
      mp_psBufferPrev = (sMBP*) mp_psBufferPrev->panBufferNext - 1;
    }
  }
  else
  {
    if
    (
         (mp_psBufferPrev == NULL)
      || (mp_psBufferPrev->nBufferBegin > i_nByteIndex)
      || (mp_psBufferPrev->nBufferEnd   <= i_nByteIndex)
    )
    {
      if(i_nByteIndex < (mp_psBufferTail->nBufferTail >> 1))
      { // From start
        mp_psBufferPrev = mp_psBufferFirst;

        while
        (
             (mp_psBufferPrev->nBufferEnd <= i_nByteIndex)
          && (mp_psBufferPrev->panBufferNext != NULL)
        )
        { // Next buffer
          mp_psBufferPrev = (sMBP*) mp_psBufferPrev->panBufferNext - 1;
        }
      }
      else
      { // From end
        mp_psBufferPrev = mp_psBufferTail;

        while
        (
             (mp_psBufferPrev->nBufferBegin > i_nByteIndex)
          && (mp_psBufferPrev->panBufferPrev != NULL)
        )
        { // Previous buffer
          mp_psBufferPrev = (sMBP*) mp_psBufferPrev->panBufferPrev - 1;
        }
      }
    }
    else{}
  }

  return mp_psBufferPrev;
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
void CMemoryStringPool::_EncodeString
( sMSP&       o_rsStringPointer
, const char* i_panStringBuffer
, int         i_nStringSize // = -1
, bool        i_bStuffing   // = false
)
{
  unsigned int  l_nHash;
  int           l_nLoop = i_nStringSize;
  unsigned char l_nChar;

  // Init

  o_rsStringPointer.nHashRaw    = 0;
  o_rsStringPointer.nHashCase   = 0;
  o_rsStringPointer.nHashNoCase = 0;

  if
  (
       (i_bStuffing == true)
    && (l_nLoop     <  0)
  )
  { // Avoid too much stuffing
    l_nLoop = 256;
  }
  else{}

#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
  o_rsStringPointer.nLength     = min(l_nLoop, GetStringLength(i_panStringBuffer));
#endif // TEST_NEWMETHOD

  l_nChar = *i_panStringBuffer;

  while
  (
       (l_nLoop != 0)
    && (
            (
                 (i_bStuffing == false)
              && (l_nChar != 0)
            )
         || (i_bStuffing == true)
       )
  )
  {
    o_rsStringPointer.nHashRaw    <<= 4;
    o_rsStringPointer.nHashCase   <<= 4;
    o_rsStringPointer.nHashNoCase <<= 4;

    if(l_nChar == 0)
    { // Stuffing
      o_rsStringPointer.nHashRaw    += ' ';
      o_rsStringPointer.nHashCase   += ' ';
      o_rsStringPointer.nHashNoCase += ' ';
    }
    else
    { // See "MemoryStringContainer.h"
      o_rsStringPointer.nHashRaw    +=             l_nChar;
      o_rsStringPointer.nHashCase   += g_panNormal[l_nChar];
      o_rsStringPointer.nHashNoCase += g_panNoCase[l_nChar];

      // Next character
      i_panStringBuffer += 1;
      l_nChar = *i_panStringBuffer;
    }

    // RAW
    l_nHash = o_rsStringPointer.nHashRaw & 0xF0000000; // (unsigned int) 0xF << (32 - 4)
    if(l_nHash != 0)
    {
      o_rsStringPointer.nHashRaw ^= l_nHash >> 24; // 32 - 8
      o_rsStringPointer.nHashRaw ^= l_nHash;
    }
    else{}

    // CASE
    l_nHash = o_rsStringPointer.nHashCase & 0xF0000000;
    if(l_nHash != 0)
    {
      o_rsStringPointer.nHashCase ^= l_nHash >> 24;
      o_rsStringPointer.nHashCase ^= l_nHash;
    }
    else{}

    // NOCASE
    l_nHash = o_rsStringPointer.nHashNoCase & 0xF0000000;
    if(l_nHash != 0)
    {
      o_rsStringPointer.nHashNoCase ^= l_nHash >> 24;
      o_rsStringPointer.nHashNoCase ^= l_nHash;
    }
    else{}

    l_nLoop -= 1;
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
int CMemoryStringPool::_StreamString
( const char*    i_panStringBuffer
, unsigned short i_nStringHole
, unsigned short i_nStringSize
, int            i_nStringLocation // = -1
)
{
  int l_nStringLocation;

  if(i_nStringLocation == -1)
  { // Default location, queue the string
    while((mp_psBufferTail->nBufferEnd - mp_psBufferTail->nBufferTail) < i_nStringHole)
    { // When not enough place, reserve the remaining place for a future usage (reserve a dummy string then free it)
      RemoveStringAt(mp_oTreeString.AllocNode(0, mp_psBufferTail->nBufferEnd - mp_psBufferTail->nBufferTail));

      // Expand the buffer up to a new one
      _ExpandBuffer(mp_psBufferTail->nBufferEnd + i_nStringHole);
    }

    // Get the current tail
    l_nStringLocation = mp_psBufferTail->nBufferTail;
  }
  else
  { // Use the requested Location, may overwritte some data
    l_nStringLocation = i_nStringLocation;
  }

  sMBP* l_psMBP = _LocateBuffer(l_nStringLocation);

  if(l_psMBP != NULL)
  {
#ifdef USEMEMCPY
    MEMCPY
#else
    memcpy
#endif // USEMEMCPY
    ( &l_psMBP->panBuffer[l_nStringLocation - l_psMBP->nBufferBegin]
    , (void*) i_panStringBuffer
    , i_nStringSize
    );

    if(i_nStringLocation == -1)
    { // If we requested the tail, moving it accordingly
      mp_psBufferTail->nBufferTail += i_nStringHole;
    }
    else{} // Requested Location, existing place, don't move the Tail

    return l_nStringLocation;
  }
  else
  { // If no Buffer found, return the default Location
    return 0;
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
char* CMemoryStringPool::_LocateString
( int i_nStringIndex
)
{
  sMBP* l_psMBP;
  sMSP* l_psMSP;
#ifndef TEST_NEWMETHOD
#else // TEST_NEWMETHOD
  int   l_nStringLocation;
#endif // TEST_NEWMETHOD

  if
  (
       (i_nStringIndex < mp_oTreeString.GetSlotTail()) // Do not reserve another slot
    && ((l_psMSP = (sMSP*) mp_oTreeString.GetSlotPointer(i_nStringIndex))  != NULL)
    && (l_psMSP->nHashRaw != 0) // If string have a hash (is valid)
  )
  { // If Slot found, get String location
#ifndef TEST_NEWMETHOD
    l_psMBP = _LocateBuffer(l_psMSP->nLocation);
#else // TEST_NEWMETHOD
    l_psMBP = _LocateBuffer(l_nStringLocation = mp_oTreeString.GetNodeData(i_nStringIndex));
#endif // TEST_NEWMETHOD

    // Return String address
#ifndef TEST_NEWMETHOD
    return &l_psMBP->panBuffer[l_psMSP->nLocation - l_psMBP->nBufferBegin];
#else // TEST_NEWMETHOD
    return &l_psMBP->panBuffer[l_nStringLocation  - l_psMBP->nBufferBegin];
#endif // TEST_NEWMETHOD
  }
  else
  { // If no Slot found or bad index, return NULL
    return NULL;
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
int CMemoryStringPool::_SearchString
( const char* i_panStringBuffer
,       int   i_nStringIndex // = -1
)
{
  int   l_nStringIndex;
  char* l_panString;

  if(i_nStringIndex < 0)
  { // Start from the Head
    l_nStringIndex = 0;
  }
  else
  { // Start from the requested index
    l_nStringIndex = i_nStringIndex;
  }

  while
  (
       ((l_panString = _LocateString(l_nStringIndex)) != NULL)
    && (GetStringCompare(i_panStringBuffer, l_panString) != 0)
  )
  { // As long as the strings doesn't match, try the next one
    l_nStringIndex += 1;
  }

  if(l_panString != NULL)
  { // If the strings matches, return the correct index
    return i_nStringIndex;
  }
  else
  { // Tail reached, return invalid index
    return -1;
  }
}








// ADDITIVE CODING : STRING HASH FUNCTIONS







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
unsigned int CMemoryStringPool::_HashRS(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int b      = 378551;
  unsigned int a      = 63689;
  unsigned int hash   = 0;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash = hash * a + i_panStringBuffer[i];
    a    = a * b;
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashJS(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int hash   = 1315423911;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash ^= ((hash << 5) + i_panStringBuffer[i] + (hash >> 2));
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashPJW(const char* i_panStringBuffer)
{
  unsigned int length            = GetStringLength(i_panStringBuffer) - 1;
  unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
  unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
  unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
  unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
  unsigned int hash              = 0;
  unsigned int test              = 0;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash = (hash << OneEighth) + i_panStringBuffer[i];

    if((test = hash & HighBits)  != 0)
    {
       hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
    }
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashELF(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int hash   = 0;
  unsigned int x      = 0;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash = (hash << 4) + i_panStringBuffer[i];
    if((x = hash & 0xF0000000L) != 0)
    {
       hash ^= (x >> 24);
       hash &= ~x;
    }
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashBKDR(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int seed   = 131; // 31 131 1313 13131 131313 etc..
  unsigned int hash   = 0;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash = (hash * seed) + i_panStringBuffer[i];
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashSDBM(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int hash   = 0;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash = i_panStringBuffer[i] + (hash << 6) + (hash << 16) - hash;
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashDJB(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int hash   = 5381;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash = ((hash << 5) + hash) + i_panStringBuffer[i];
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashDEK(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int hash   = length;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash = ((hash << 5) ^ (hash >> 27)) ^ i_panStringBuffer[i];
  }

  return (hash & 0x7FFFFFFF);
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
unsigned int CMemoryStringPool::_HashAP(const char* i_panStringBuffer)
{
  unsigned int length = GetStringLength(i_panStringBuffer) - 1;
  unsigned int hash   = 0;

  for
  ( unsigned int i = 0
  ; i < length
  ; i++
  )
  {
    hash
    ^= ((i & 1) == 0)
    ? (  (hash <<  7) ^ i_panStringBuffer[i] ^ (hash >> 3))
    : (~((hash << 11) ^ i_panStringBuffer[i] ^ (hash >> 5)))
    ;
  }

  return (hash & 0x7FFFFFFF);
}
