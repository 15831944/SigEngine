// MemoryPool.cpp: implementation of the CMemoryPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE DE MEMOIRE AUTO-DIMENSIONNABLE ==========================================================================

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
CMemoryPool::CMemoryPool
( const char* i_panStringName  // = "CMemoryPool"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryPool");
#endif // _DEBUG
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
CMemoryPool::~CMemoryPool
(
)
{
#ifdef _DEBUG
  if(GetBufferSize() > 0)
  {
    TRACE
    ( "%s::~%s : %d/%d (%d%%) unused bytes left (%d/%d slot%s free)\n"
    , (CString) mp_oStrObjectName
    , (CString) mp_oStrObjectClass
    , GetBufferFree()
    , GetBufferSize()
    , (int) (((LONGLONG) GetBufferFree() * 100) / GetBufferSize())
    , GetSlotFree()
    , GetSlotTotal()
    , (GetSlotFree() > 1) ? "s" : ""
    );
  }
  else{}
#endif // _DEBUG

  _DeleteBuffer();

  // Sort
  if(mp_panIndiceArray1 != NULL)
  {
    delete [] mp_panIndiceArray1;
  }
  else{}

  if(mp_panIndiceArray2 != NULL)
  {
    delete [] mp_panIndiceArray2;
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
int CMemoryPool::CreateBuffer
( int  i_nSlotSize
, int  i_nSlotNumber
, BOOL i_bZeroMemory
)
{
#ifdef _DEBUG
  if(i_nSlotNumber == 1)
  { // On essaye de déterminer le CONNARD qui ne réserve qu'un seul slot (vachement 'utile')
    i_nSlotNumber = i_nSlotNumber;
  }
  else{}
#endif // _DEBUG

  if(i_nSlotSize <= 0)
  { // Test slot size
#ifdef _DEBUG
    TRACE
    ( "ERROR : %s::CreateBuffer(i_nSlotSize (%d) <= 0) = Wrong slot size\n"
    , (CString) mp_oStrObjectName
    , i_nSlotSize
    );
    
//    ASSERT(!(i_nSlotSize <= 0));
#endif // _DEBUG

    return (-1);
  }
  else
  {
    if(i_nSlotNumber <= 0)
    { // Test number of slot
#ifdef _DEBUG
      TRACE
      ( "ERROR : %s::CreateBuffer(i_nSlotNumber (%d) <= 0) = Wrong slot number\n"
      , (CString) mp_oStrObjectName
      , i_nSlotNumber
      );
      
//      ASSERT(!(i_nSlotNumber <= 0));
#endif // _DEBUG

      return (-2);
    }
    else
    { // Everything OK
      mp_nSlotSizeHole = ALIGN(i_nSlotSize) + mp_nSlotSizeHead; // 8 bytes boundary, helps 64 bits CPU
      mp_nSlotSizeData = i_nSlotSize;
      mp_bZeroMemory   = i_bZeroMemory;

      // Delete the previous buffers
      _DeleteBuffer();

      sMBP l_sTempoMBP;

      // Create the new buffer
      l_sTempoMBP.nBufferSize   = i_nSlotNumber * mp_nSlotSizeHole;
      l_sTempoMBP.panBuffer     = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)] + sizeof(sMBP);
      l_sTempoMBP.panBufferPrev = NULL;
      l_sTempoMBP.panBufferNext = NULL;
      l_sTempoMBP.nSlotBegin    = 0;
      l_sTempoMBP.nSlotHead     = 0;
      l_sTempoMBP.nSlotTail     = 0;
      l_sTempoMBP.nSlotEnd      = i_nSlotNumber;

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
      ( "%s::CreateBuffer(SlotSize = %d, SlotNumber = %d, BufferSize = %d, ZeroMemory = %s)\n"
      , (CString) mp_oStrObjectName
      , mp_nSlotSizeData
      , i_nSlotNumber
      , l_sTempoMBP.nBufferSize
      , (mp_bZeroMemory  == TRUE) ? "YES" : "NO"
      );
#endif // _DEBUG

      return true;
    }
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
int CMemoryPool::AddSlotHead
( void* i_panSlotBuffer
)
{
  return InsertSlotAt(i_panSlotBuffer, 0);
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
int CMemoryPool::AddSlotTail
( void* i_panSlotBuffer
, int   i_nSizeData // = -1
)
{
  if(mp_psBufferTail->nSlotTail >= mp_psBufferTail->nSlotEnd)
  { // If no more place left, try to expand the Pool
    if((mp_psBufferTail = _ExpandBuffer(mp_psBufferTail->nSlotTail)) == NULL)
    {
#ifdef _DEBUG
      TRACE
      ( "ERROR : %s::AddSlotTail((mp_psBufferTail = _ExpandBuffer(mp_psBufferTail->nSlotTail)) == NULL) = Buffer expansion failed\n"
      , (CString) mp_oStrObjectName
      );
#endif // _DEBUG

      return (-1);
    }
    else{}
  }
  else{}

  if(i_nSizeData < 0)
  { // Copy slot size
    i_nSizeData = mp_nSlotSizeData;
  }
  else{}

  if
  (
       (i_panSlotBuffer != NULL)
    && (i_nSizeData > 0)
  )
  {
#ifdef USEMEMCPY
    MEMCPY
#else
    memcpy
#endif // USEMEMCPY
    ( &mp_psBufferTail->panBuffer[((mp_psBufferTail->nSlotTail - mp_psBufferTail->nSlotBegin) * mp_nSlotSizeHole) + mp_nSlotSizeHead] // Current tail location
    , i_panSlotBuffer
    , i_nSizeData // Copy requested size
    );
  }
  else{}
  
  // New tail location
  mp_psBufferTail->nSlotTail += 1;

  return mp_psBufferTail->nSlotTail - 1; // Slot index
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
void CMemoryPool::operator +=
( void* i_panSlotBuffer
)
{
  AddSlotTail(i_panSlotBuffer);
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
int CMemoryPool::InsertSlotAt
( void* i_panSlotBuffer
, int   i_nSlotIndex
)
{
  sMBP* l_psMBP;
  sMBP* l_psTailMBP;

  if(mp_psBufferTail->nSlotTail == i_nSlotIndex)
  {
    return AddSlotTail(i_panSlotBuffer);
  }
  else
  {
    // Get the right buffer
    l_psMBP = _LocateBuffer(i_nSlotIndex);

    if(i_nSlotIndex > l_psMBP->nSlotTail)
    { // Test if index beyon tail
      l_psMBP->nSlotTail = i_nSlotIndex;
    }
    else{}

    if(l_psMBP->nSlotTail >= l_psMBP->nSlotEnd)
    { // Try to expand the buffer
      if(_ExpandBuffer(l_psMBP->nSlotTail) == NULL)
      {
#ifdef _DEBUG
        TRACE
        ( "ERROR : %s::InsertSlotAt(_ExpandBuffer(l_psMBP->nSlotTail) == NULL) = Buffer expansion failed\n"
        , (CString) mp_oStrObjectName
        );
#endif // _DEBUG

        return (-1);
      }
      else{}
    }
    else{}

    // Get the right buffer again, if something has changed since the buffer expansion
    l_psMBP     = _LocateBuffer(i_nSlotIndex);
    l_psTailMBP = mp_psBufferTail; // Start from Tail

    // To help memory mapping
    char* l_panArrayFrom;
    char* l_panArrayTo;

    while(l_psTailMBP != l_psMBP)
    {
      // Current block, many slots
      l_panArrayFrom = l_psTailMBP->panBuffer;            // BlockXn[0]
      l_panArrayTo   = l_panArrayFrom + mp_nSlotSizeHole; // BlockXn[1]

      // Create a little place for the new slot
#ifdef USEMEMMOVE
      MEMMOVE
#else
      memmove
#endif // USEMEMMOVE
      ( l_panArrayTo
      , l_panArrayFrom
      , (l_psTailMBP->nSlotTail - l_psTailMBP->nSlotBegin) * mp_nSlotSizeHole
      );

      l_psTailMBP = (sMBP*) l_psTailMBP->panBufferPrev - 1;

      // Previous block, last slot
      l_panArrayTo   = l_panArrayFrom; // BlockXn[0]
      l_panArrayFrom = &l_psTailMBP->panBuffer[((l_psTailMBP->nSlotEnd - l_psTailMBP->nSlotBegin - 1) * mp_nSlotSizeHole) + mp_nSlotSizeHead]; // BlockXn-1[End-1]

#ifdef USEMEMMOVE
      MEMMOVE
#else
      memmove
#endif // USEMEMMOVE
      ( l_panArrayTo
      , l_panArrayFrom
      , mp_nSlotSizeHole // One slot
      );
    }

    // First block, many slots
    l_panArrayFrom = &l_psTailMBP->panBuffer[((i_nSlotIndex - l_psTailMBP->nSlotBegin + 0) * mp_nSlotSizeHole) + mp_nSlotSizeHead];
    l_panArrayTo   = l_panArrayFrom + mp_nSlotSizeHole; // BlockX[Index+1]

#ifdef USEMEMMOVE
    MEMMOVE
#else
    memmove
#endif // USEMEMMOVE
    ( l_panArrayTo   // To   : Indexed+1 slot
    , l_panArrayFrom // From : indexed   slot
    , (l_psTailMBP->nSlotEnd - l_psTailMBP->nSlotTail) * mp_nSlotSizeHole
    );

    // Copy the new slot
#ifdef USEMEMCPY
    MEMCPY
#else
    memcpy
#endif // USEMEMCPY
    ( l_panArrayFrom // To : Indexed slot
    , i_panSlotBuffer
    , mp_nSlotSizeData
    );

    // New tail location
    mp_psBufferTail->nSlotTail += 1;
  
    return i_nSlotIndex;
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
int CMemoryPool::InsertSlotAfter
( void* i_panSlotBuffer
, int   i_nSlotIndex
)
{
  return InsertSlotAt(i_panSlotBuffer, i_nSlotIndex + 1);
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
int CMemoryPool::InsertSlotDicho
( void* i_panSlotBuffer
, int   i_nByteToCompare  // = 4
, BOOL  i_bBigEndian      // = FALSE
)
{
  int   l_nMin = 0;
  int   l_nMed;
  int   l_nMax = mp_psBufferTail->nSlotTail;

  char* l_panSlot;
  short l_nLoop;

  //

  if
  (
       (i_nByteToCompare <= 0)
    || (i_nByteToCompare >  mp_nSlotSizeData)
  )
  {
    i_nByteToCompare = mp_nSlotSizeData;
  }
  else{}

  if(i_bBigEndian == TRUE)
  { // From start
    while(l_nMax > (l_nMin + 1))
    {
      l_nMed  = (l_nMin + l_nMax) >> 1;
      l_nLoop = 0;

      l_panSlot = (char*) GetSlotPointer(l_nMed);

      while
      (
           (l_panSlot[l_nLoop] ==  ((char*) i_panSlotBuffer)[l_nLoop])
        && (l_nLoop < i_nByteToCompare)
      )
      {
        l_nLoop += 1;
      }

      if(l_nLoop == i_nByteToCompare)
      { // Bytes are the same, return the index
        l_nMin = l_nMed;
        l_nMax = l_nMed;
      }
      else
      {
        if(l_panSlot[l_nLoop] > ((char*) i_panSlotBuffer)[l_nLoop])
        {
          l_nMax = l_nMed;
        }
        else
        {
          l_nMin = l_nMed;
        }
      }
    }
  }
  else
  { // From end
    while(l_nMax > (l_nMin + 1))
    {
      l_nMed  = (l_nMin + l_nMax) >> 1;
      l_nLoop = i_nByteToCompare - 1;

      l_panSlot = (char*) GetSlotPointer(l_nMed);

      while
      (
           (l_panSlot[l_nLoop] == ((char*) i_panSlotBuffer)[l_nLoop])
        && (l_nLoop >= 0)
      )
      {
        l_nLoop -= 1;
      }

      if(l_nLoop < 0)
      { // Bytes are the same, return the index
        l_nMin = l_nMed;
        l_nMax = l_nMed;
      }
      else
      {
        if(l_panSlot[l_nLoop] > ((char*) i_panSlotBuffer)[l_nLoop])
        {
          l_nMax = l_nMed;
        }
        else
        {
          l_nMin = l_nMed;
        }
      }
    }
  }

  if(l_nMin != l_nMax)
  {
    return InsertSlotAt(i_panSlotBuffer, l_nMin);
  }
  else
  {
    return l_nMin;
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
void CMemoryPool::RemoveSlotAll
(
)
{
  mp_psBufferPrev = mp_psBufferFirst;

  if(mp_psBufferPrev != NULL)
  {
    mp_psBufferPrev = (sMBP*) mp_psBufferPrev->panBuffer;

    while(mp_psBufferPrev != NULL)
    { // Restore Tail
      mp_psBufferPrev -= 1; // sMBP* -> Current

      mp_psBufferPrev->nSlotHead = mp_psBufferPrev->nSlotBegin;
      mp_psBufferPrev->nSlotTail = mp_psBufferPrev->nSlotBegin;

      mp_psBufferPrev = (sMBP*) mp_psBufferPrev->panBufferNext;
    }
  }
  else{}

  mp_psBufferTail = mp_psBufferFirst; // Start from the first buffer
  mp_psBufferPrev = mp_psBufferFirst;
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
int CMemoryPool::RemoveSlotHead
( void
)
{
  return RemoveSlotAt(0);
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
int CMemoryPool::RemoveSlotTail
( void
)
{
  if(mp_psBufferTail->nSlotTail > mp_psBufferTail->nSlotHead)
  { // Decrease from 1 slot
    mp_psBufferTail->nSlotTail -= 1;
  }
  else{}

  if
  (
       (mp_psBufferTail->nSlotTail == mp_psBufferTail->nSlotHead)
    && (mp_psBufferTail->panBufferPrev != NULL)
  )
  { // If a block is empty, switch the tail at the end of the previous block
    mp_psBufferTail = (sMBP*) mp_psBufferTail->panBufferPrev - 1;
    mp_psBufferTail->nSlotTail = mp_psBufferTail->nSlotEnd;
  }
  else{}

  // Try to delete unused allocated blocks
  return _ReduceBuffer(mp_psBufferTail->nSlotTail);
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
int CMemoryPool::RemoveSlotAt
( int i_nSlotIndex
)
{
  if(mp_psBufferTail->nSlotTail == i_nSlotIndex)
  {
    return RemoveSlotTail();
  }
  else
  {
    // Get the right buffer
    sMBP* l_psMBP = _LocateBuffer(i_nSlotIndex);

    if(l_psMBP->nSlotTail <= l_psMBP->nSlotHead)
    {
#ifdef _DEBUG
      TRACE
      ( "ERROR : %s::RemoveSlotAt(l_psMBP->nSlotTail (%d) <= l_psMBP->nSlotHead (%d)) = All slots already empty\n"
      , (CString) mp_oStrObjectName
      , l_psMBP->nSlotTail
      , l_psMBP->nSlotHead
      );
#endif // _DEBUG

      return (-1);
    }
    else
    {
      if(i_nSlotIndex >= l_psMBP->nSlotTail)
      {
#ifdef _DEBUG
        TRACE
        ( "ERROR : %s::RemoveSlotAt(i_nSlotIndex (%d) >= l_psMBP->nSlotTail (%d)) = Wrong slot index\n"
        , (CString) mp_oStrObjectName
        , i_nSlotIndex
        , l_psMBP->nSlotTail
        );
#endif // _DEBUG

        return (-2);
      }
      else
      {
        sMBP* l_psTailMBP = mp_psBufferTail; // Start from Tail

        // To help memory mapping
        char* l_panArrayFrom;
        char* l_panArrayTo;

        // First block, many slots
        l_panArrayTo   = &l_psMBP->panBuffer[((i_nSlotIndex - l_psMBP->nSlotBegin + 0) * mp_nSlotSizeHole) + mp_nSlotSizeHead];
        l_panArrayFrom = l_panArrayTo + mp_nSlotSizeHole; // BlockX[Index+1]

#ifdef USEMEMMOVE
        MEMMOVE
#else
        memmove
#endif // USEMEMMOVE
        ( l_panArrayTo   // To   : Indexed   slot
        , l_panArrayFrom // From : indexed+1 slot
        , (l_psMBP->nSlotTail - i_nSlotIndex - 1) * mp_nSlotSizeHole
        );

        while
        (
             (l_psMBP != l_psTailMBP)
          && (l_psMBP->panBufferNext != NULL)
        )
        {
          // Previous block, last slot
          l_panArrayTo = &l_psMBP->panBuffer[((l_psMBP->nSlotEnd - l_psMBP->nSlotBegin - 1) * mp_nSlotSizeHole) + mp_nSlotSizeHead]; // BlockX[End-1]

          l_psMBP = (sMBP*) l_psMBP->panBufferNext - 1;

          // Current block, one slot
          l_panArrayFrom = l_psMBP->panBuffer; // BlockX+1[0]

#ifdef USEMEMMOVE
          MEMMOVE
#else
          memmove
#endif // USEMEMMOVE
          ( l_panArrayTo
          , l_panArrayFrom
          , mp_nSlotSizeHole // One slot
          );

          // Current block, many slots
          l_panArrayTo    = l_panArrayFrom;    // BlockX+1[0]
          l_panArrayFrom += mp_nSlotSizeHole ; // BlockX+1[1]

#ifdef USEMEMMOVE
          MEMMOVE
#else
          memmove
#endif // USEMEMMOVE
          ( l_panArrayTo
          , l_panArrayFrom
          , (l_psTailMBP->nSlotTail - l_psTailMBP->nSlotBegin - 1) * mp_nSlotSizeHole
          );
        }

        return RemoveSlotTail(); // Place the new tail
      }
    }
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
int CMemoryPool::RemoveSlotAfter
( int i_nSlotIndex
)
{
  return RemoveSlotAt(i_nSlotIndex + 1);
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
void CMemoryPool::operator -=
( int i_nSlotIndex
)
{
  RemoveSlotAt(i_nSlotIndex);
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
int CMemoryPool::Push
( void* i_panSlotBuffer
)
{
  return AddSlotTail(i_panSlotBuffer);
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
int CMemoryPool::Push
( void
)
{
  return AddSlotTail(NULL); // Copy nothing, just allocate a slot
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
int CMemoryPool::Pop
( void* o_panSlotBuffer
)
{
  if
  (
       (mp_psBufferTail->nSlotTail == mp_psBufferTail->nSlotHead)
    && (mp_psBufferTail->panBufferPrev != NULL)
  )
  { // If a block is empty, switch the tail at the end of the previous block
    mp_psBufferTail = (sMBP*) mp_psBufferTail->panBufferPrev - 1;
    mp_psBufferTail->nSlotTail = mp_psBufferTail->nSlotEnd;
  }
  else{}

  if(mp_psBufferTail->nSlotTail > mp_psBufferTail->nSlotHead)
  { // If beyon first slot of the first block
    mp_psBufferTail->nSlotTail -= 1;

    // Copy slot data
#ifdef USEMEMCPY
    MEMCPY
#else
    memcpy
#endif // USEMEMCPY
    ( o_panSlotBuffer
    , &mp_psBufferTail->panBuffer[(mp_psBufferTail->nSlotTail - mp_psBufferTail->nSlotBegin + 0) * mp_nSlotSizeHole + mp_nSlotSizeHead] // From : indexed slot in the pool
    , mp_nSlotSizeData
    );

    return true;
  }
  else
  {
    return false;
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
void* CMemoryPool::Pop
( void
)
{
  if
  (
       (mp_psBufferTail->nSlotTail == mp_psBufferTail->nSlotHead)
    && (mp_psBufferTail->panBufferPrev != NULL)
  )
  { // If a block is empty, switch the tail at the end of the previous block
    mp_psBufferTail = (sMBP*) mp_psBufferTail->panBufferPrev - 1;
    mp_psBufferTail->nSlotTail = mp_psBufferTail->nSlotEnd;
  }
  else{}

  if(mp_psBufferTail->nSlotTail > mp_psBufferTail->nSlotHead)
  { // If beyon first slot of the first block
    mp_psBufferTail->nSlotTail -= 1; // Just relocate the tail
    
    // Don't copy slot data but don't erase it either, at least right now...
    return &mp_psBufferTail->panBuffer[((mp_psBufferTail->nSlotTail - mp_psBufferTail->nSlotBegin + 0) * mp_nSlotSizeHole) + mp_nSlotSizeHead];
    // BETTER HURRY UP TO READ THE DATA BEFORE IT IS OVERWRITTEN BY A NEWLY INSERTED SLOT !!!
  }
  else
  {
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
int CMemoryPool::GetSlotBuffer
( void* o_panSlotBuffer
, int   i_nSlotIndex
)
{
  // Get the right buffer
  sMBP* l_psMBP = _LocateBuffer(i_nSlotIndex);

  if(l_psMBP->nSlotBegin > i_nSlotIndex)
  {
#ifdef _DEBUG
    TRACE
    ( "ERROR : %s::GetSlotData(l_psMBP->nSlotBegin (%d) > i_nSlotIndex (%d)) = Wrong slot index\n"
    , (CString) mp_oStrObjectName
    , l_psMBP->nSlotBegin
    , i_nSlotIndex
    );

//    ASSERT(!(l_psMBP->nSlotBegin > i_nSlotIndex));
#endif // _DEBUG

    return (-1);
  }
  else
  {

    if(l_psMBP->nSlotTail <= i_nSlotIndex) 
    {
#ifdef _DEBUG
      TRACE
      ( "ERROR : %s::GetSlotData(l_psMBP->nSlotTail (%d) <= i_nSlotIndex (%d)) = Wrong slot index\n"
      , (CString) mp_oStrObjectName
      , l_psMBP->nSlotTail
      , i_nSlotIndex
      );
    
//      ASSERT(!(l_psMBP->nSlotTail <= i_nSlotIndex));
#endif // _DEBUG

      return (-2); 
    }
    else
    {
      if(o_panSlotBuffer == NULL)
      {
#ifdef _DEBUG
        TRACE
        ( "ERROR : %s::GetSlotData(o_panSlotBuffer == NULL) = No output address\n"
        , (CString) mp_oStrObjectName
        );

//        ASSERT(!(o_panSlotBuffer == NULL));
#endif // _DEBUG

        return (-3);
      }
      else
      { // Copy the slot inside the buffer
#ifdef USEMEMCPY
        MEMCPY
#else
        memcpy
#endif // USEMEMCPY
        ( o_panSlotBuffer
        , &l_psMBP->panBuffer[((i_nSlotIndex - l_psMBP->nSlotBegin + 0) * mp_nSlotSizeHole) + mp_nSlotSizeHead] // From : indexed slot in the pool
        , mp_nSlotSizeData
        );
  
        return true;
      }
    }
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
int CMemoryPool::SetSlotBuffer
( void* i_panSlotBuffer
, int   i_nSlotIndex
)
{
  // Get the right buffer
  sMBP* l_psMBP = _LocateBuffer(i_nSlotIndex);

  if(l_psMBP->nSlotBegin > i_nSlotIndex)
  {
#ifdef _DEBUG
    TRACE
    ( "ERROR : %s::SetSlotData(l_psMBP->nSlotBegin (%d) > i_nSlotIndex (%d)) = Wrong slot index\n"
    , (CString) mp_oStrObjectName
    , l_psMBP->nSlotBegin
    , i_nSlotIndex
    );
    
//    ASSERT(!(l_psMBP->nSlotBegin > i_nSlotIndex));
#endif // _DEBUG

    return (-1);
  }
  else
  {
    if(l_psMBP->nSlotTail <= i_nSlotIndex) 
    {
#ifdef _DEBUG
      TRACE
      ( "ERROR : %s::SetSlotData(l_psMBP->nSlotTail (%d) <= i_nSlotIndex (%d)) = Wrong slot index\n"
      , (CString) mp_oStrObjectName
      , l_psMBP->nSlotTail
      , i_nSlotIndex
      );
    
//      ASSERT(!(l_psMBP->nSlotTail <= i_nSlotIndex));
#endif // _DEBUG

      return (-2); 
    }
    else
    {
      if(i_panSlotBuffer == NULL)
      {
#ifdef _DEBUG
        TRACE
        ( "ERROR : %s::SetSlotData(i_panSlotBuffer == NULL) = No input address\n"
        , (CString) mp_oStrObjectName
        );
    
//        ASSERT(!(i_panSlotBuffer == NULL));
#endif // _DEBUG

        return (-3);
      }
      else
      { // Copy the slot inside the buffer
#ifdef USEMEMCPY
        MEMCPY
#else
        memcpy
#endif // USEMEMCPY
        ( &l_psMBP->panBuffer[((i_nSlotIndex - l_psMBP->nSlotBegin + 0) * mp_nSlotSizeHole) + mp_nSlotSizeHead] // To   : indexed slot in the pool
        , i_panSlotBuffer
        , mp_nSlotSizeData
        );

        return true;
      }
    }
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
void* CMemoryPool::GetSlotPointer
( int i_nSlotIndex
)
{
  if(i_nSlotIndex < 0)
  {
    return NULL;
  }
  else
  {
    // Get the right buffer
    sMBP* l_psMBP = _LocateBuffer(i_nSlotIndex);

    if(l_psMBP->nSlotBegin > i_nSlotIndex)
    {
      return NULL;
    }
    else
    {
      if(l_psMBP->nSlotTail < i_nSlotIndex) 
      {
        return NULL; 
      }
      else
      {
        if
        (
             (l_psMBP->nSlotTail <= i_nSlotIndex)
          && (l_psMBP->nSlotTail >= l_psMBP->nSlotEnd)
        )
        { // Try to expand the buffer if we requested the Tail
          if(_ExpandBuffer(l_psMBP->nSlotTail) == NULL)
          {
            return NULL;
          }
          else{}
        }
        else{}

        // Relocate the index if it changed
        l_psMBP = _LocateBuffer(i_nSlotIndex);

        return &l_psMBP->panBuffer[((i_nSlotIndex - l_psMBP->nSlotBegin) * mp_nSlotSizeHole) + mp_nSlotSizeHead]; // To   : indexed slot in the pool
      }
    }
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
void* CMemoryPool::operator []
( int i_nSlotIndex
)
{
  return GetSlotPointer(i_nSlotIndex);
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
int CMemoryPool::GetBufferSize
(
)
{
  int l_nBufferSize = 0;

  // Get the right buffer
  if(mp_psBufferFirst != NULL)
  {
    sMBP* l_psMBP = (sMBP*) mp_psBufferFirst->panBuffer;

    while(l_psMBP != NULL)
    {
      l_psMBP -= 1;

      l_nBufferSize += l_psMBP->nBufferSize;

      l_psMBP = (sMBP*) l_psMBP->panBufferNext;
    }
  }
  else{}

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
int CMemoryPool::GetBufferFree
(
)
{
  return GetSlotFree() * mp_nSlotSizeHole;
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
int CMemoryPool::GetSlotTail
(
)
{
  if(mp_psBufferTail != NULL)
  {
    return mp_psBufferTail->nSlotTail;
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
int CMemoryPool::GetSlotTotal
(
)
{
  sMBP* l_psMBP = _LocateBuffer(1<<31);

  if(l_psMBP != NULL)
  {
    return l_psMBP->nSlotEnd;
  }
  else
  {
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
int CMemoryPool::GetSlotHole
( void
)
{
  return mp_nSlotSizeHole;
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
int CMemoryPool::GetSlotSize
( void
)
{
  return mp_nSlotSizeData;
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
int CMemoryPool::GetSlotFree
(
)
{
  if(mp_psBufferTail != NULL)
  {
    return mp_psBufferTail->nSlotEnd - mp_psBufferTail->nSlotTail;
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
void CMemoryPool::SortInt
( int  i_nIntToCompare // = 1
, bool i_bSignedInt    // = TRUE, 
, bool i_bBigEndian    // = FALSE
)
{
           int   l_nIntOffset;
//           int   l_nIntIndex;

  unsigned int   l_nByteIndex;
  unsigned int   l_nLoop;
  bool           l_bSorted;

  unsigned char* l_panByteArray;

  unsigned int   l_nSlotIndex;
  unsigned int   l_nSlotEnd = GetSlotTail();

  unsigned int*  l_panHistoByte0;
  unsigned int*  l_panHistoByte1;
  unsigned int*  l_panHistoByte2;
  unsigned int*  l_panHistoByte3;

  unsigned int   l_nDataPrev;
  unsigned int   l_nDataTempo;

  unsigned int   l_nNegByteCount;

  unsigned int*  l_panHistoCounter;
  unsigned char  l_nByteFromInt;
  bool           l_nPassDone;

//  unsigned char* l_panIndiceByte;
  unsigned int*  l_panIndiceArray;
  unsigned int*  l_panIndiceEnd;

  if(l_nSlotEnd > 0)
  {
    // Resize lists if needed
    if(l_nSlotEnd != mp_nIndiceSizePrevious)
    {
      if(l_nSlotEnd > mp_nIndiceSizeCurrent)
      {
        _ResizeIndices(l_nSlotEnd);
      }
      else
      {
        _ResetIndices();
      }

      mp_nIndiceSizePrevious = l_nSlotEnd;
    }

    for
    ( l_nIntOffset  = i_nIntToCompare - 1
    ; l_nIntOffset >= 0
    ; l_nIntOffset -= 1
    )
    {
      // Clear histogram counters
      ZeroMemory
      ( mp_anHistogram
      , 256 * 4 * sizeof(unsigned int)
      );

      // Prepare for temporal coherence
      l_nDataPrev      = *((unsigned int*) GetSlotPointer(mp_panIndiceArray1[0]) + l_nIntOffset);
      l_bSorted        = true;
      l_panIndiceArray = mp_panIndiceArray1;

      // Prepare to count
      l_panHistoByte0  = &mp_anHistogram[0];   // Histogram for first pass (LSB)
      l_panHistoByte1  = &mp_anHistogram[256]; // Histogram for second pass
      l_panHistoByte2  = &mp_anHistogram[512]; // Histogram for third pass
      l_panHistoByte3  = &mp_anHistogram[768]; // Histogram for last pass (MSB)

      for
      ( l_nSlotIndex  = 0
      ; l_nSlotIndex  < l_nSlotEnd
      ; l_nSlotIndex += 1
      )
      {
        l_panByteArray = (unsigned char*) ((unsigned int*) GetSlotPointer(l_nSlotIndex) + l_nIntOffset);
        
        // Read input array in previous sorted order
        l_nDataTempo = *((unsigned int*) GetSlotPointer(*l_panIndiceArray++) + l_nIntOffset);

        // Check whether already sorted or not
        if
        (
             ((i_bSignedInt == false) && (      l_nDataTempo <       l_nDataPrev))
          || ((i_bSignedInt == true)  && ((int) l_nDataTempo < (int) l_nDataPrev))
        )
        {
          l_bSorted = false;

          break;
        }

        // Update for next iteration
        l_nDataPrev = l_nDataTempo;

        // Create histograms
        l_panHistoByte0[*l_panByteArray++]++;
        l_panHistoByte1[*l_panByteArray++]++;
        l_panHistoByte2[*l_panByteArray++]++;
        l_panHistoByte3[*l_panByteArray++]++;
      }

      if(l_bSorted == false)
      {
        for
        (
        ; l_nSlotIndex  < l_nSlotEnd
        ; l_nSlotIndex += 1
        )
        { // Create histograms without the previous overhead
          l_panByteArray = (unsigned char*) ((unsigned int*) GetSlotPointer(l_nSlotIndex) + l_nIntOffset);
        
          l_panHistoByte0[*l_panByteArray++]++;
          l_panHistoByte1[*l_panByteArray++]++;
          l_panHistoByte2[*l_panByteArray++]++;
          l_panHistoByte3[*l_panByteArray++]++;
        }

        // Compute negative values involved if needed
        l_nNegByteCount = 0;

        if(i_bSignedInt == true)
        {
          l_panHistoByte3 = &mp_anHistogram[768]; // Last 128 indexes ($80 to $FF = MSB) deals with the sign

          for
          ( l_nLoop  = 128
          ; l_nLoop  < 256
          ; l_nLoop += 1
          )
          { // 768 for last histogram, 128 for negative part
            l_nNegByteCount += l_panHistoByte3[l_nLoop];
          }
        }

        // Radix sort, l_nByteIndex is the pass number (0=LSB, 3=MSB)
        for
        ( l_nByteIndex  = 0
        ; l_nByteIndex  < 4
        ; l_nByteIndex += 1
        )
        {
          l_panHistoCounter = &mp_anHistogram[l_nByteIndex << 8]; // Current counter

          l_nPassDone = true;

          // Get first byte
          l_nByteFromInt = *(((unsigned char*) ((unsigned int*) GetSlotPointer(0) + l_nIntOffset)) + l_nByteIndex);

          // Check that byte's counter
          if(l_panHistoCounter[l_nByteFromInt] == l_nSlotEnd)
          {
            l_nPassDone = false;
          }
          else{}

          if(l_nPassDone == true)
          {
            if
            (
                 (l_nByteIndex != 3)
              || (i_bSignedInt == false)
            )
            { // Here we deal with positive values only
              mp_anOffset[0] = 0; // Create offsets

              for
              ( l_nLoop  = 1
              ; l_nLoop  < 256
              ; l_nLoop += 1
              )
              {
                mp_anOffset[l_nLoop] = mp_anOffset[l_nLoop - 1] + l_panHistoCounter[l_nLoop - 1];
              }
            }
            else
            { // First positive number takes place after the negative ones
              mp_anOffset[0] = l_nNegByteCount;

              for
              ( l_nLoop  = 1
              ; l_nLoop  < 128
              ; l_nLoop += 1
              )
              { // 1 to 128 for positive numbers
                mp_anOffset[l_nLoop] = mp_anOffset[l_nLoop - 1] + l_panHistoCounter[l_nLoop - 1];
              }

              // Fixing the wrong place for negative values
              mp_anOffset[128] = 0;

              for
              ( l_nLoop  = 129
              ; l_nLoop  < 256
              ; l_nLoop += 1
              )
              {
                mp_anOffset[l_nLoop] = mp_anOffset[l_nLoop - 1] + l_panHistoCounter[l_nLoop - 1];
              }
            }

            // Perform Radix Sort
//            l_panIndiceByte  = (unsigned char*) ((unsigned int*) GetSlotPointer(l_nSlotIndex) + l_nIntOffset);
            l_panIndiceArray = mp_panIndiceArray1;
            l_panIndiceEnd   = &mp_panIndiceArray1[l_nSlotEnd];

//            l_panIndiceByte += l_nByteIndex;

            while(l_panIndiceArray != l_panIndiceEnd)
            {
              l_nLoop = *l_panIndiceArray++;

              mp_panIndiceArray2[mp_anOffset[*((unsigned char*) ((unsigned int*) GetSlotPointer(l_nLoop) + l_nIntOffset) + l_nByteIndex)]++] = l_nLoop;
            }

            // Swap pointers for next pass
            l_panIndiceArray   = mp_panIndiceArray1;
            mp_panIndiceArray1 = mp_panIndiceArray2;
            mp_panIndiceArray2 = l_panIndiceArray;
          }
        }
      }
      else{}
    }
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
void CMemoryPool::SortFloat
( int  i_nFloatToCompare // = 1
)
{
           int   l_nFloatOffset;
//           int   l_nFloatIndex;

//  unsigned int*  l_panIntArray;
  unsigned int   l_nByteIndex;
  unsigned int   l_nLoop;
  bool           l_bSorted;

  unsigned char* l_panByteArray;

  unsigned int   l_nSlotIndex;
  unsigned int   l_nSlotEnd = GetSlotTail();

  unsigned int*  l_panHistoByte0;
  unsigned int*  l_panHistoByte1;
  unsigned int*  l_panHistoByte2;
  unsigned int*  l_panHistoByte3;

  float          l_nDataPrev;
  float          l_nDataTempo;

  unsigned int   l_nNegByteCount;

  unsigned int*  l_panHistoCounter;
  unsigned char  l_nByteFromInt;
  bool           l_nPassDone;

  unsigned int   l_nByteRadix;

//  unsigned char* l_panIndiceByte;
  unsigned int*  l_panIndiceArray;
  unsigned int*  l_panIndiceEnd;

  // Checkings
  if(l_nSlotEnd > 0)
  {
    // Resize lists if needed
    if(l_nSlotEnd != mp_nIndiceSizePrevious)
    {
      if(l_nSlotEnd > mp_nIndiceSizeCurrent)
      {
        _ResizeIndices(l_nSlotEnd);
      }
      else
      {
        _ResetIndices();
      }

      mp_nIndiceSizePrevious = l_nSlotEnd;
    }
    else{}

    for
    ( l_nFloatOffset  = i_nFloatToCompare - 1
    ; l_nFloatOffset >= 0
    ; l_nFloatOffset -= 1
    )
    {
      // Clear counters
      ZeroMemory
      ( mp_anHistogram
      , 256 * 4 * sizeof(unsigned int)
      );

      // Prepare for temporal coherence
      l_nDataPrev      = *((float*) GetSlotPointer(mp_panIndiceArray1[0]) + l_nFloatOffset);
      l_bSorted        = true;  // Optimism...
      l_panIndiceArray = mp_panIndiceArray1;

      // Prepare to count
//      l_panIntArray    = (unsigned int*) i_panFloatArray;

      l_panHistoByte0  = &mp_anHistogram[0];    // Histogram for first pass (LSB)
      l_panHistoByte1  = &mp_anHistogram[256];  // Histogram for second pass     
      l_panHistoByte2  = &mp_anHistogram[512];  // Histogram for third pass      
      l_panHistoByte3  = &mp_anHistogram[768];  // Histogram for last pass (MSB) 

      for
      ( l_nSlotIndex  = 0
      ; l_nSlotIndex  < l_nSlotEnd
      ; l_nSlotIndex += 1
      )
      {
        l_panByteArray = (unsigned char*) ((float*) GetSlotPointer(l_nSlotIndex) + l_nFloatOffset);
        
        // Read input array in previous sorted order
        l_nDataTempo = *((float*) GetSlotPointer(*l_panIndiceArray++) + l_nFloatOffset);

        // Check whether already sorted or not
        if(l_nDataTempo < l_nDataPrev)
        {
          l_bSorted = false;

          break; // Early out
        }
        else{}

        // Update for next iteration
        l_nDataPrev = l_nDataTempo;

        // Create histograms
        l_panHistoByte0[*l_panByteArray++]++;
        l_panHistoByte1[*l_panByteArray++]++;
        l_panHistoByte2[*l_panByteArray++]++;
        l_panHistoByte3[*l_panByteArray++]++;
      }

      if(l_bSorted == false)
      {
        for
        (
        ; l_nSlotIndex  < l_nSlotEnd
        ; l_nSlotIndex += 1
        )
        { // Create histograms without the previous overhead
          l_panByteArray = (unsigned char*) ((float*) GetSlotPointer(l_nSlotIndex) + l_nFloatOffset);

          l_panHistoByte0[*l_panByteArray++]++;
          l_panHistoByte1[*l_panByteArray++]++;
          l_panHistoByte2[*l_panByteArray++]++;
          l_panHistoByte3[*l_panByteArray++]++;
        }

        // Compute negative values involved if needed
        l_nNegByteCount = 0;

        l_panHistoByte3 = &mp_anHistogram[768]; // Last 128 indexes ($80 to $FF = MSB) deals with the sign
        for
        ( l_nLoop  = 128
        ; l_nLoop  < 256
        ; l_nLoop += 1
        )
        { // 768 for last histogram, 128 for negative part
          l_nNegByteCount += l_panHistoByte3[l_nLoop];
        }
  
        // Radix sort, l_nByteIndex is the pass number (0=LSB, 3=MSB)
        for
        ( l_nByteIndex  = 0
        ; l_nByteIndex  < 4
        ; l_nByteIndex += 1
        )
        { // Should we care about negative values?
          if(l_nByteIndex != 3)
          { // Here we deal with positive values only
            l_panHistoCounter = &mp_anHistogram[l_nByteIndex << 8]; // Current counter

            l_nPassDone = true;

            // Get first byte
            l_nByteFromInt = *((((unsigned char*) ((float*) GetSlotPointer(0) + l_nFloatOffset))) + l_nByteIndex);

            // Check that byte's counter
            if(l_panHistoCounter[l_nByteFromInt] == l_nSlotEnd)
            {
              l_nPassDone = false;
            }
            else{}

            if(l_nPassDone == true)
            {
              mp_anOffset[0] = 0; // Create offsets

              for
              ( l_nLoop  = 1
              ; l_nLoop  < 256
              ; l_nLoop += 1
              )
              {
                mp_anOffset[l_nLoop] = mp_anOffset[l_nLoop - 1] + l_panHistoCounter[l_nLoop - 1];
              }

              // Perform Radix Sort
              l_panIndiceArray = mp_panIndiceArray1;
              l_panIndiceEnd   = &mp_panIndiceArray1[l_nSlotEnd];

              while(l_panIndiceArray != l_panIndiceEnd)
              {
                l_nLoop = *l_panIndiceArray++;

                mp_panIndiceArray2[mp_anOffset[*((unsigned char*) ((unsigned int*) GetSlotPointer(l_nLoop) + l_nFloatOffset) + l_nByteIndex)]++] = l_nLoop;
              }

              // Swap pointers for next pass
              l_panIndiceArray   = mp_panIndiceArray1;
              mp_panIndiceArray1 = mp_panIndiceArray2;
              mp_panIndiceArray2 = l_panIndiceArray;
            }
          }
          else
          { // This is a special case to correctly handle negative values
            l_panHistoCounter = &mp_anHistogram[l_nByteIndex << 8]; // Current counter

            // Reset flag. The sorting pass is supposed to be performed. (default)
            l_nPassDone = true;

            // Get first byte
            l_nByteFromInt = *(((unsigned char*) ((float*) GetSlotPointer(0) + l_nFloatOffset)) + l_nByteIndex);

            // Check that byte's counter
            if(l_panHistoCounter[l_nByteFromInt] == l_nSlotEnd)
            {
              l_nPassDone = false;
            }
            else{}

            if(l_nPassDone == true)
            {
              // Create biased offsets, in order for negative numbers to be sorted as well
              mp_anOffset[0] = l_nNegByteCount; // First positive number takes place after the negative ones

              for
              ( l_nLoop  = 1
              ; l_nLoop  < 128
              ; l_nLoop += 1
              )
              { // 1 to 128 for positive numbers
                mp_anOffset[l_nLoop] = mp_anOffset[l_nLoop - 1] + l_panHistoCounter[l_nLoop - 1];
              }

              // We must reverse the sorting order for negative numbers
              mp_anOffset[255] = 0;

              for
              ( l_nLoop  = 0
              ; l_nLoop  < 127
              ; l_nLoop += 1
              )
              { // Fixing the wrong order for negative values
                mp_anOffset[254 - l_nLoop] = mp_anOffset[255 - l_nLoop] + l_panHistoCounter[255 - l_nLoop];
              }

              for
              ( l_nLoop  = 128
              ; l_nLoop  < 256
              ; l_nLoop += 1
              )
              { // Fixing the wrong place for negative values
                mp_anOffset[l_nLoop] += l_panHistoCounter[l_nLoop];
              }

              // Perform Radix Sort
              for
              ( l_nLoop  = 0
              ; l_nLoop  < l_nSlotEnd
              ; l_nLoop += 1
              )
              {
                l_nByteRadix = *((unsigned int*) GetSlotPointer(mp_panIndiceArray1[l_nLoop]) + l_nFloatOffset) >> 24; // Radix byte

                if(l_nByteRadix < 128)
                {
                  mp_panIndiceArray2[mp_anOffset[l_nByteRadix]++] = mp_panIndiceArray1[l_nLoop];
                } // Number is positive, same as above
                else
                {
                  mp_panIndiceArray2[--mp_anOffset[l_nByteRadix]] = mp_panIndiceArray1[l_nLoop];
                } // Number is negative, flip the sorting order
              }

              // Swap pointers for next pass
              l_panIndiceArray   = mp_panIndiceArray1;
              mp_panIndiceArray1 = mp_panIndiceArray2;
              mp_panIndiceArray2 = l_panIndiceArray;
            }
            else
            {
              // The pass is useless, yet we still have to reverse the order of current list if all values are negative.
              if(l_nByteFromInt >= 128)
              {
                for
                ( l_nLoop  = 0
                ; l_nLoop  < l_nSlotEnd
                ; l_nLoop += 1
                )
                {
                  mp_panIndiceArray2[l_nLoop] = mp_panIndiceArray1[l_nSlotEnd - l_nLoop - 1];
                }

                // Swap pointers for next pass
                l_panIndiceArray   = mp_panIndiceArray1;
                mp_panIndiceArray1 = mp_panIndiceArray2;
                mp_panIndiceArray2 = l_panIndiceArray;
              }
            }
          }
        }
      }
      else{}
    }
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
void CMemoryPool::SortSwap
( void
)
{
  unsigned int l_nLoop;
  unsigned int l_nSwap;
  unsigned int l_nStop = 0;
  unsigned int l_nTail = GetSlotTail();

  if
  (
       (mp_panIndiceArray1     != NULL)
    && (mp_panIndiceArray2     != NULL)
    && (mp_nIndiceSizePrevious == l_nTail)
  )
  {
    for
    ( l_nLoop  = 0
    ; l_nLoop  < l_nTail
    ; l_nLoop += 1
    )
    { // Prepare the reindexing of the sorted indices
      mp_panIndiceArray2[mp_panIndiceArray1[l_nLoop]] = l_nLoop;
    }

    do
    {
      for
      ( l_nLoop  = 0
      , l_nSwap  = mp_panIndiceArray2[l_nLoop]
      ;  (l_nLoop  < l_nTail)
      && (l_nSwap == l_nLoop)
      ; l_nLoop += 1
      , l_nSwap  = mp_panIndiceArray2[l_nLoop]
      )
      {
      }

      if(l_nLoop < l_nTail)
      {
        l_nStop = l_nSwap; // First swaped slot, don't swap it twice on end

        while
        (
             (l_nSwap != l_nLoop)
          && (l_nStop != l_nLoop)
        )
        {
          _SwapSlot(l_nSwap, l_nLoop);

          // Reindex the sorted indices and block further sorting
          mp_panIndiceArray2[l_nLoop] = l_nLoop;

          l_nLoop = mp_panIndiceArray1[l_nLoop]; // Next step
          l_nSwap = mp_panIndiceArray2[l_nLoop]; // Next place
        }

        mp_panIndiceArray2[l_nLoop] = l_nLoop;
      }
      else{}
    }
    while(l_nLoop < l_nTail);

    for
    ( l_nLoop  = 0
    ; l_nLoop  < l_nTail
    ; l_nLoop += 1
    )
    { // Recreate the indexing of the sorted indices
      mp_panIndiceArray2[mp_panIndiceArray1[l_nLoop]] = l_nLoop;
    }

    unsigned int* l_panIndiceArray = mp_panIndiceArray1;

    mp_panIndiceArray1 = mp_panIndiceArray2; // New order
    mp_panIndiceArray2 = l_panIndiceArray; // SCRAMBLED
  }
  else{}

  mp_nIndiceSizePrevious = 0; // Reinit sorting
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
int CMemoryPool::GetSlotSorted
( int i_nNodeIndex
)
{
  if
  (
       (mp_panIndiceArray1 != NULL)
    && (i_nNodeIndex >= 0)
  )
  {
    return mp_panIndiceArray1[i_nNodeIndex];
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
bool CMemoryPool::SaveToFile
( CFile& i_roFileOut
)
{
  sMBP  l_sTempoMBP;
  sMBP* l_psMBP;

  // Block informations

  // int   nBufferSize   = Size of the saved buffer, length to read back
  // char* panBuffer     = NULL
  // char* panBufferPrev = NULL
  // char* panBufferNext = NULL
  // int   nSlotBegin    = Size of data
  // int   nSlotHead     = Head size
  // int   nSlotTail     = Tail location
  // int   nSlotEnd      = Size of struct sMBP

  l_sTempoMBP.nBufferSize   = mp_psBufferTail->nSlotTail * mp_nSlotSizeHole;
  l_sTempoMBP.panBuffer     = NULL;
  l_sTempoMBP.panBufferPrev = NULL;
  l_sTempoMBP.panBufferNext = NULL;
  l_sTempoMBP.nSlotBegin    = mp_nSlotSizeData;
  l_sTempoMBP.nSlotHead     = mp_nSlotSizeHead;
  l_sTempoMBP.nSlotTail     = mp_psBufferTail->nSlotTail;
  l_sTempoMBP.nSlotEnd      = sizeof(sMBP);

  i_roFileOut.Write
  ( &l_sTempoMBP
  , sizeof(sMBP)
  );

  l_psMBP = (sMBP*) mp_psBufferFirst->panBuffer;

  while(l_psMBP != NULL)
  { // Save all blocks up to the current defined tail, not further
    l_psMBP -= 1;

    if(l_psMBP->nSlotBegin < mp_psBufferTail->nSlotTail)
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
        , (l_psMBP->nSlotTail - l_psMBP->nSlotBegin) * mp_nSlotSizeHole
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
bool CMemoryPool::LoadFromFile
( CFile& i_roFileIn
)
{
  sMBP l_sTempoMBP;
  bool l_bResult = false;

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
    // int   nSlotBegin    = Size of data
    // int   nSlotHead     = Head size
    // int   nSlotTail     = Tail location
    // int   nSlotEnd      = Size of struct sMBP

    if(l_sTempoMBP.nSlotEnd == sizeof(sMBP))
    { // Struct size OK
      if((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) != NULL)
      {
        _DeleteBuffer(); // Erase everything, we're changing of buffer

        mp_psBufferFirst = (sMBP*) l_sTempoMBP.panBuffer;

        // Double linked buffers
        mp_psBufferTail = mp_psBufferFirst;
        mp_psBufferPrev = mp_psBufferFirst;

        mp_nSlotSizeHead = l_sTempoMBP.nSlotHead; // Size of slot header
        mp_nSlotSizeHole = l_sTempoMBP.nBufferSize / l_sTempoMBP.nSlotTail; // Size of slot space
        mp_nSlotSizeData = l_sTempoMBP.nSlotBegin; // Size of slot data

        mp_psBufferFirst->nBufferSize   = l_sTempoMBP.nBufferSize;
        mp_psBufferFirst->panBufferPrev = NULL;
        mp_psBufferFirst->panBufferNext = NULL;
        mp_psBufferFirst->nSlotBegin    = 0;
        mp_psBufferFirst->nSlotHead     = 0;
        mp_psBufferFirst->nSlotTail     = l_sTempoMBP.nSlotTail;
        mp_psBufferFirst->nSlotEnd      = l_sTempoMBP.nSlotTail;

        l_sTempoMBP.panBuffer          += l_sTempoMBP.nSlotEnd; // sizeof(sMBP)

        mp_psBufferFirst->panBuffer     = l_sTempoMBP.panBuffer;

        if
        (
             i_roFileIn.Read
             ( mp_psBufferFirst->panBuffer
             , mp_psBufferFirst->nBufferSize
             )
          == l_sTempoMBP.nBufferSize
        )
        {
          l_bResult = true;
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
void CMemoryPool::_DeleteBuffer
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

    if(l_psMBP->panBuffer != NULL)
    { // Delete current remaining buffer
      delete [] ((sMBP*) l_psMBP->panBuffer - 1);
    }
    else{}
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
CMemoryPool::sMBP*
CMemoryPool::_ExpandBuffer
( int i_nSlotReach
)
{
  sMBP* l_psMBP = _LocateBuffer(i_nSlotReach);

  int  l_nDivider = 1;
  sMBP l_sTempoMBP;

  // New buffer to replace to old one, thus starting from 0
  l_sTempoMBP.panBufferPrev = NULL;
  l_sTempoMBP.panBufferNext = NULL;
  l_sTempoMBP.nSlotBegin    = 0;
  l_sTempoMBP.nSlotHead     = 0;
  l_sTempoMBP.nSlotTail     = mp_psBufferTail->nSlotTail;
  l_sTempoMBP.nSlotEnd      = 0;

  while(l_sTempoMBP.nSlotEnd <= i_nSlotReach)
  {
    l_sTempoMBP.nSlotEnd += mp_psBufferFirst->nSlotEnd;
  }

  l_sTempoMBP.nBufferSize = l_sTempoMBP.nSlotEnd * mp_nSlotSizeHole;

  if(l_sTempoMBP.nBufferSize != l_psMBP->nBufferSize)
  { // Create the new buffer
    while
    (
         ((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) == NULL)
      && (l_nDivider < 8)
    )
    { // If buffer size is too big, try to allocate a smaller block
      do
      {
        if(l_sTempoMBP.nSlotEnd > i_nSlotReach)
        { // Reduce
          l_sTempoMBP.nSlotEnd -= mp_psBufferFirst->nSlotEnd >> l_nDivider;
        }
        else
        { // Increase
          l_sTempoMBP.nSlotEnd += mp_psBufferFirst->nSlotEnd >> l_nDivider;
        }
      }
      while(l_sTempoMBP.nSlotEnd > i_nSlotReach);

      l_sTempoMBP.nBufferSize = l_sTempoMBP.nSlotEnd * mp_nSlotSizeHole;

      l_nDivider += 1;
    }
  }
  else{}

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
    , GetSlotTotal()
    , l_sTempoMBP.nSlotEnd - GetSlotTotal()
    , l_sTempoMBP.nSlotEnd
    , (l_sTempoMBP.nSlotEnd > 1) ? "s" : ""
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

      if(l_psMBP->nSlotTail < i_nSlotReach)
      {
        l_nCopySize = (l_psMBP->nSlotTail - l_psMBP->nSlotBegin) * mp_nSlotSizeHole;
      }
      else
      {
        l_nCopySize = (i_nSlotReach       - l_psMBP->nSlotBegin) * mp_nSlotSizeHole;
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
int CMemoryPool::_ReduceBuffer
( int i_nSlotReach
)
{ // Start from the farther slot to reach
  sMBP* l_psMBP = _LocateBuffer(1<<31);

  while
  (
       (l_psMBP > NULL)
    && (l_psMBP->nSlotBegin > i_nSlotReach)
  )
  {
    if(l_psMBP->panBufferNext != NULL)
    {
      delete [] ((sMBP*) l_psMBP->panBufferNext - 1);
      l_psMBP->panBufferNext = NULL;
    }
    else{}

    l_psMBP = (sMBP*) l_psMBP->panBufferPrev - 1;
  }

  mp_psBufferTail = l_psMBP;

  int  l_nDivider = 1;
  sMBP l_sTempoMBP;

  // New buffer to replace to old one, thus starting from 0
  l_sTempoMBP.panBuffer     = NULL;
  l_sTempoMBP.panBufferPrev = NULL;
  l_sTempoMBP.panBufferNext = NULL;
  l_sTempoMBP.nSlotBegin    = 0;
  l_sTempoMBP.nSlotHead     = 0;
  l_sTempoMBP.nSlotTail     = mp_psBufferTail->nSlotTail;
  l_sTempoMBP.nSlotEnd      = 0;

  while(l_sTempoMBP.nSlotEnd <= i_nSlotReach)
  {
    l_sTempoMBP.nSlotEnd += mp_psBufferFirst->nSlotEnd;
  }

  l_sTempoMBP.nBufferSize = l_sTempoMBP.nSlotEnd * mp_nSlotSizeHole;

  if(l_sTempoMBP.nBufferSize != l_psMBP->nBufferSize)
  { // Create the new buffer
    while
    (
         ((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) == NULL)
      && (l_nDivider < 8)
    )
    { // If buffer size is too big, try to allocate a smaller block
      do
      {
        if(l_sTempoMBP.nSlotEnd > i_nSlotReach)
        { // Reduce
          l_sTempoMBP.nSlotEnd -= mp_psBufferFirst->nSlotEnd >> l_nDivider;
        }
        else
        { // Increase
          l_sTempoMBP.nSlotEnd += mp_psBufferFirst->nSlotEnd >> l_nDivider;
        }
      }
      while(l_sTempoMBP.nSlotEnd > i_nSlotReach);

      l_nDivider += 1;
    
      l_sTempoMBP.nBufferSize = l_sTempoMBP.nSlotEnd * mp_nSlotSizeHole;
    }
  }
  else{}

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
    , GetSlotTotal()
    , GetSlotTotal() - l_sTempoMBP.nSlotEnd
    , l_sTempoMBP.nSlotEnd
    , (l_sTempoMBP.nSlotEnd > 1) ? "s" : ""
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

      if(l_psMBP->nSlotTail < i_nSlotReach)
      {
        l_nCopySize = (l_psMBP->nSlotTail - l_psMBP->nSlotBegin) * mp_nSlotSizeHole;
      }
      else
      {
        l_nCopySize = (i_nSlotReach       - l_psMBP->nSlotTail) * mp_nSlotSizeHole;
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
  
    return mp_psBufferFirst->nSlotEnd;
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
CMemoryPool::sMBP*
CMemoryPool::_LocateBuffer
( int i_nSlotIndex
)
{
  if(i_nSlotIndex == (1<<31))
  { // Get the farther end, beyon the tail
    mp_psBufferPrev = mp_psBufferTail;

    while
    (
         (mp_psBufferPrev != NULL)
      && (mp_psBufferPrev->panBufferNext != NULL)
    )
    {
      mp_psBufferPrev = (sMBP*) mp_psBufferPrev->panBufferNext - 1;
    }
  }
  else
  {
    if
    (
         (mp_psBufferPrev == NULL)
      || (mp_psBufferPrev->nSlotBegin  > i_nSlotIndex)
      || (mp_psBufferPrev->nSlotEnd   <= i_nSlotIndex)
    )
    {
      if(i_nSlotIndex < (mp_psBufferTail->nSlotTail >> 1))
      { // From start
        mp_psBufferPrev = mp_psBufferFirst;

        while
        (
             (mp_psBufferPrev->nSlotEnd <= i_nSlotIndex)
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
             (mp_psBufferPrev->nSlotBegin > i_nSlotIndex)
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
void CMemoryPool::_SwapSlot
( int i_nSlotSrc
, int i_nSlotDst
)
{
  void* l_panSlotEmpty;
  void* l_panSlotSource;
  void* l_panSlotDest;

  if(i_nSlotSrc != i_nSlotDst)
  {
    l_panSlotEmpty  = GetSlotPointer(GetSlotTail());
    l_panSlotSource = GetSlotPointer(i_nSlotSrc);
    l_panSlotDest   = GetSlotPointer(i_nSlotDst);

    if
    (
         (l_panSlotEmpty  != NULL)
      && (l_panSlotSource != NULL)
      && (l_panSlotDest   != NULL)
    )
    {
      // Save Destination Slot
#ifdef USEMEMCPY
      MEMCPY
#else
      memcpy
#endif // USEMEMCPY
      ( l_panSlotEmpty
      , l_panSlotDest
      , mp_nSlotSizeData
      );

      // Copy Source to Destination
#ifdef USEMEMCPY
      MEMCPY
#else
      memcpy
#endif // USEMEMCPY
      ( l_panSlotDest
      , l_panSlotSource
      , mp_nSlotSizeData
      );

      // Copy saved Destination to Source
#ifdef USEMEMCPY
      MEMCPY
#else
      memcpy
#endif // USEMEMCPY
      ( l_panSlotSource
      , l_panSlotEmpty
      , mp_nSlotSizeData
      );
    }
    else{}
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
void CMemoryPool::_ResetIndices
( void
)
{
  unsigned int l_nLoop;

  for
  ( l_nLoop  = 0
  ; l_nLoop  < mp_nIndiceSizeCurrent
  ; l_nLoop += 1
  )
  {
    mp_panIndiceArray1[l_nLoop] = l_nLoop;
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
bool CMemoryPool::_ResizeIndices
( unsigned int i_nArraySize
)
{
  if(mp_panIndiceArray1 != NULL)
  {
    delete [] mp_panIndiceArray1;
  }
  else{}

  if(mp_panIndiceArray2 != NULL)
  {
    delete [] mp_panIndiceArray2;
  }
  else{}

  mp_panIndiceArray1 = new unsigned int[i_nArraySize];
  if(mp_panIndiceArray1 == NULL)
  {
    return false;
  }
  else
  {
    mp_panIndiceArray2 = new unsigned int[i_nArraySize];
    if(mp_panIndiceArray2 == NULL)
    {
      return false;
    }
    else
    {
      mp_nIndiceSizeCurrent = i_nArraySize;

      _ResetIndices();

      return true;
    }
  }
}

