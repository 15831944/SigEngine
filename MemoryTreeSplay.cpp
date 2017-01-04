// MemoryTreeSplay.cpp: implementation of the CMemoryTreeSplay class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Memory.h"

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
CMemoryTreeSplay::CMemoryTreeSplay
( const char* i_panStringName // = "CMemoryTreeSplay"
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName); // Default object name

  _SetClassType("CMemoryTreeSplay");
#endif // _DEBUG
}

