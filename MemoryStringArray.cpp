// MemoryStringArray.cpp: implementation of the CMemoryStringArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE DE TABLEAU DE CHAINES AUTO-DIMENSIONNABLE ===============================================================

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
CMemoryStringArray::CMemoryStringArray
( const char* i_panStringName // = "CMemoryStringArray"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryStringArray");

  mp_oTreeString.SetClassName(mp_oStrObjectName+"::mp_oTreeString");
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
CMemoryStringArray::sMBP*
CMemoryStringArray::_ExpandBuffer
( int i_nByteReach
)
{
  sMBP* l_psMBP = _LocateBuffer(i_nByteReach);

  while(l_psMBP->nBufferEnd < i_nByteReach)
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
      l_sTempoMBP.nBufferBegin  = l_psMBP->nBufferEnd;
      l_sTempoMBP.nBufferHead   = l_psMBP->nBufferEnd;
      l_sTempoMBP.nBufferTail   = l_psMBP->nBufferEnd; // mp_psBufferTail->nBufferTail;
      l_sTempoMBP.nBufferEnd    = l_psMBP->nBufferEnd + (l_psMBP->nBufferEnd - l_psMBP->nBufferBegin);

      l_sTempoMBP.nBufferSize   = l_sTempoMBP.nBufferEnd - l_sTempoMBP.nBufferBegin;

      // Create the new buffer
      while
      (
           ((l_sTempoMBP.panBuffer = new char[l_sTempoMBP.nBufferSize + sizeof(sMBP)]) == NULL)
        && (l_nDivider < 8)
      )
      { // If buffer size is too big, try to allocate a smaller block
        l_sTempoMBP.nBufferEnd  = l_psMBP->nBufferEnd + ((l_psMBP->nBufferEnd - l_psMBP->nBufferBegin) >> l_nDivider);
        l_sTempoMBP.nBufferSize = l_sTempoMBP.nBufferEnd - l_sTempoMBP.nBufferBegin;

        l_nDivider += 1;
      }

      if(l_sTempoMBP.panBuffer != NULL)
      {
        l_sTempoMBP.panBuffer += sizeof(sMBP); // Write corect address first in the temp structure
        *((sMBP*) l_sTempoMBP.panBuffer - 1) = l_sTempoMBP;

#ifdef _DEBUG
        TRACE
        ( "%s::_ExpandBuffer(%d+%d->%d byte%s) allocated at [0x%08X->0x%08X[ (+%d->%d bytes)\n"
        , (CString) mp_oStrObjectName
        , GetBufferSize()
        , l_sTempoMBP.nBufferEnd - GetBufferSize()
        , l_sTempoMBP.nBufferEnd
        , (l_sTempoMBP.nBufferEnd > 1) ? "s" : ""
        , l_sTempoMBP.panBuffer - sizeof(sMBP)
        , l_sTempoMBP.panBuffer + l_sTempoMBP.nBufferSize
        , l_sTempoMBP.nBufferSize + sizeof(sMBP)
        , GetBufferSize() + l_sTempoMBP.nBufferSize + sizeof(sMBP)
        );
#endif // _DEBUG

        l_psMBP->panBufferNext = l_sTempoMBP.panBuffer;

        l_psMBP = (sMBP*) l_psMBP->panBufferNext - 1;

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
int CMemoryStringArray::_ReduceBuffer
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
      delete [] ((sMBP*) l_psMBP->panBufferNext - 1); // - sizeof(sMBP)
      l_psMBP->panBufferNext = NULL;
    }
    else{}

    l_psMBP = (sMBP*) l_psMBP->panBufferPrev - 1; // - sizeof(sMBP)
  }

  mp_psBufferTail = l_psMBP;

  if(l_psMBP != NULL)
  {
    return mp_psBufferTail->nBufferTail;
  }
  else
  {
    return -1;
  }
} // 100 %
