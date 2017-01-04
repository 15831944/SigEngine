// MemoryArray.cpp: implementation of the CMemoryArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE DE TABLEAU AUTO-DIMENSIONNABLE ==========================================================================

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
CMemoryArray::CMemoryArray
( const char* i_panStringName  // = "CMemoryArray"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryArray");
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
CMemoryArray::sMBP*
CMemoryArray::_ExpandBuffer
( int i_nSlotReach
)
{
  sMBP* l_psMBP = _LocateBuffer(i_nSlotReach);

  while(l_psMBP->nSlotEnd <= i_nSlotReach)
  {
    if(l_psMBP->panBufferNext != NULL)
    { // If a block already exists, let switch on it
      l_psMBP = (sMBP*) l_psMBP->panBufferNext - 1;
    }
    else
    { // No currently allocated block
      int  l_nDivider = 1;
      sMBP l_sTempoMBP;

      l_sTempoMBP.panBufferPrev = l_psMBP->panBuffer;
      l_sTempoMBP.panBufferNext = NULL;
      l_sTempoMBP.nSlotBegin    = l_psMBP->nSlotEnd;
      l_sTempoMBP.nSlotHead     = l_psMBP->nSlotEnd;
      l_sTempoMBP.nSlotTail     = l_psMBP->nSlotEnd; // mp_psBufferTail->nSlotTail;
      l_sTempoMBP.nSlotEnd      = l_psMBP->nSlotEnd + (l_psMBP->nSlotEnd - l_psMBP->nSlotBegin);

      l_sTempoMBP.nBufferSize   = (l_sTempoMBP.nSlotEnd - l_sTempoMBP.nSlotBegin) * mp_nSlotSizeHole;

      // Create the new buffer
      while
      (
           ((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) == NULL)
        && (l_nDivider < 8)
      )
      { // If buffer size is too big, try to allocate a smaller block
        l_sTempoMBP.nSlotEnd    = l_psMBP->nSlotEnd + ((l_psMBP->nSlotEnd - l_psMBP->nSlotBegin) >> l_nDivider);
        l_sTempoMBP.nBufferSize = (l_sTempoMBP.nSlotEnd - l_sTempoMBP.nSlotBegin) * mp_nSlotSizeHole;

        l_nDivider += 1;
      }

      if(l_sTempoMBP.panBuffer != NULL)
      {
        l_sTempoMBP.panBuffer += sizeof(sMBP); // Write corect address first in the temp structure

        // Zero memory if needed
        if(mp_bZeroMemory == TRUE)
        {
          ZeroMemory
          ( l_sTempoMBP.panBuffer
          , l_sTempoMBP.nBufferSize
          );
        }
        else{}

        *((sMBP*) l_sTempoMBP.panBuffer - 1) = l_sTempoMBP;

#ifdef _DEBUG
        TRACE
        ( "%s::_ExpandBuffer(%d+%d->%d slot%s) allocated at [0x%08X->0x%08X[ (+%d->%d bytes)\n"
        , (CString) mp_oStrObjectName
        , GetSlotTotal()
        , l_sTempoMBP.nSlotEnd - GetSlotTotal()
        , l_sTempoMBP.nSlotEnd
        , (l_sTempoMBP.nSlotEnd > 1) ? "s" : ""
        , l_sTempoMBP.panBuffer - sizeof(sMBP)
        , l_sTempoMBP.panBuffer + l_sTempoMBP.nBufferSize
        , l_sTempoMBP.nBufferSize + sizeof(sMBP)
        , GetBufferSize() + l_sTempoMBP.nBufferSize + sizeof(sMBP)
        );
#endif // _DEBUG

        l_psMBP->panBufferNext = l_sTempoMBP.panBuffer;

        l_psMBP = (sMBP*) l_sTempoMBP.panBuffer - 1;

        // Double linked buffers
        mp_psBufferTail = l_psMBP;
        mp_psBufferPrev = l_psMBP;
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
    }
  }
  
  return l_psMBP;
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
int CMemoryArray::_ReduceBuffer
( int i_nSlotReach
)
{
  // Start from the farther slot to reach
  sMBP* l_psMBP = _LocateBuffer(1<<31);

  while
  (
       (l_psMBP > NULL)
    && (l_psMBP->nSlotBegin >= i_nSlotReach)
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

  if(l_psMBP != NULL)
  {
    return mp_psBufferTail->nSlotTail;
  }
  else
  {
    return -1;
  }
} // 100 %
