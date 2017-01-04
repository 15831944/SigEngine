// SigPolygon.cpp: implementation of the CSigPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SigPolygon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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
CSigPolygon::CSigPolygon
( const char* i_panStrName // = "CSigPolygon"
)
{
#ifdef _DEBUG
  SetClassName(i_panStrName); // Default object name

  _SetClassType("CSigPolygon");
#endif // _DEBUG

  mp_oasArraySigPoint.CreateBuffer(sizeof(sSigPoint), 64);
} // OK

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
CSigPolygon::CSigPolygon
( int i_nSigPointNumber
, const char* i_panStrName // = "CSigPolygon"
)
{
#ifdef _DEBUG
  SetClassName(i_panStrName); // Default object name

  _SetClassType("CSigPolygon");
#endif // _DEBUG

  mp_oasArraySigPoint.CreateBuffer(sizeof(sSigPoint), i_nSigPointNumber);
} // OK

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
CSigPolygon::~CSigPolygon
(
)
{
} // OK

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
void CSigPolygon::SetClassName
( const char* i_panStrName
)
{
  mp_oStrObjectName = i_panStrName;

  mp_oasArraySigPoint.SetClassName(mp_oStrObjectName+"::mp_oasArraySigPoint");
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
BOOL CSigPolygon::IsClosed
( void
)
{
  return
     *((sSigPoint*) mp_oasArraySigPoint[0])
  == *((sSigPoint*) mp_oasArraySigPoint[GetSize() - 1]);
} // OK

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
void CSigPolygon::Close
( void
)
{
  if(IsClosed() == FALSE)
  {
    mp_oasArraySigPoint.AddSlotTail(mp_oasArraySigPoint[0]);
  }
  else{}
} // OK

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
int CSigPolygon::GetSize
( void
)
{
  return mp_oasArraySigPoint.GetSlotTail();
} // OK

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
int CSigPolygon::SetSize
( int i_nPointNumber
)
{
  return GetSize();

//  sSigPoint l_sSigPointDummy(0.0, 0.0, 0.0);

//  mp_oasArraySigPoint.RemoveSlotAll();

//  return mp_oasArraySigPoint.InsertSlotAt(&l_sSigPointDummy, i_nPointNumber);
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
void CSigPolygon::Add
( sSigPoint& i_roSigPoint
)
{
  mp_oasArraySigPoint.AddSlotTail(&i_roSigPoint);
} // OK

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
int CSigPolygon::SetAt
( int        i_nSigPointIndex
, sSigPoint& i_roSigPoint
)
{
  return mp_oasArraySigPoint.SetSlotBuffer(&i_roSigPoint, i_nSigPointIndex);
} // OK

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
int CSigPolygon::InsertAt
( int        i_nSigPointIndex
, sSigPoint& i_roSigPoint
)
{
  return mp_oasArraySigPoint.InsertSlotAt(&i_roSigPoint, i_nSigPointIndex);
} // OK

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
void CSigPolygon::Delete
( int i_nSigPointIndex
)
{
  mp_oasArraySigPoint.RemoveSlotAt(i_nSigPointIndex);
} // OK

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
void CSigPolygon::Trim
( int i_nSigPointStart
, int i_nSigPointEnd
)
{
  int l_nLoop;
  int l_nSize = GetSize();

  ASSERT((i_nSigPointEnd   >= 0) && (i_nSigPointEnd   < l_nSize));
  ASSERT((i_nSigPointStart >= 0) && (i_nSigPointStart < l_nSize));

  int l_nHead = i_nSigPointStart;
  int l_nTail = l_nSize - i_nSigPointEnd;

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nHead
  ; l_nLoop += 1
  )
  {
    mp_oasArraySigPoint.RemoveSlotHead();
  }

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nTail
  ; l_nLoop += 1
  )
  {
    mp_oasArraySigPoint.RemoveSlotTail();
  }
} // OK

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
void CSigPolygon::RemoveAll
(
)
{
  mp_oasArraySigPoint.RemoveSlotAll();

//  mp_nCachePointNumber = 0;
} // OK

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
BOOL CSigPolygon::InSpan
( int i_nSigPointStart
, int i_nSigPointEnd
, int i_nSigPointIndex
)
{
  if
  (
       (i_nSigPointIndex <  0)
    || (i_nSigPointIndex >= GetSize())
  )
  {
    return FALSE;
  }
  else
  {
    if(i_nSigPointStart <= i_nSigPointEnd) 
    {
      return 
         (i_nSigPointIndex >= i_nSigPointStart)
      && (i_nSigPointIndex <= i_nSigPointEnd)
      ;
    }
    else
    {
      return
      !(
            (i_nSigPointIndex > i_nSigPointEnd)
         && (i_nSigPointIndex < i_nSigPointStart)
       )
      ;
    }
  }
} // OK

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
BOOL CSigPolygon::InSpanProper
( int i_nSigPointStart
, int i_nSigPointEnd
, int i_nSigPointIndex
)
{
  if
  (
       (i_nSigPointIndex < 0)
    || (i_nSigPointIndex >= GetSize())
  )
  {
    return FALSE;
  }
  else
  {
    if(i_nSigPointStart <= i_nSigPointEnd)
    {
      return
         (i_nSigPointIndex >  i_nSigPointStart)
      && (i_nSigPointIndex <  i_nSigPointEnd)
      ;
    }
    else
    {
      return
      !(
            (i_nSigPointIndex >= i_nSigPointEnd)
         && (i_nSigPointIndex <= i_nSigPointStart)
       )
      ;
    }
  }
} // OK

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
BOOL CSigPolygon::PointIn
( sSigPoint& i_roSigPoint
)
{
  int        l_nLoop;
  int        l_nSize = GetSize();
  int        l_nCrossCount;

  bool       l_bFlagX;
  bool       l_bFlagYA;
  bool       l_bFlagYB;

  tREAL      l_nDistA;
  tREAL      l_nDistB;

  sSigPoint* l_psSigPointA;
  sSigPoint* l_psSigPointB;

  //

  l_psSigPointA = (sSigPoint*) mp_oasArraySigPoint[l_nSize - 1];
  l_nDistA      = l_psSigPointA->nLatY - i_roSigPoint.nLatY;
  l_bFlagYA     = l_nDistA >= 0.0;
  l_nCrossCount = 0;

  //
  
  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    if(l_nLoop & 0x1)
    {
      l_psSigPointA = (sSigPoint*) mp_oasArraySigPoint[l_nLoop];
      l_nDistA      = l_psSigPointA->nLatY - i_roSigPoint.nLatY;
      l_bFlagYA     = l_nDistA >= 0.0;
    }
    else
    {
      l_psSigPointB = (sSigPoint*) mp_oasArraySigPoint[l_nLoop];
      l_nDistB      = l_psSigPointB->nLatY - i_roSigPoint.nLatY;
      l_bFlagYB     = l_nDistB >= 0.0;
    }

    if(l_bFlagYA != l_bFlagYB)
    {
      l_bFlagX = l_psSigPointA->nLonX >= i_roSigPoint.nLonX;

      if(l_bFlagX == (l_psSigPointB->nLonX >= i_roSigPoint.nLonX))
      {
        if(l_bFlagX == true)
        {
          l_nCrossCount += 1;
        }
        else{}
      }
      else
      {
        if
        (
             (
                  l_psSigPointA->nLonX - l_nDistA
               * (l_psSigPointB->nLonX - l_psSigPointA->nLonX)
               / (l_psSigPointB->nLatY - l_psSigPointA->nLatY)
             )
          >= i_roSigPoint.nLonX
        )
        {
          l_nCrossCount += 1;
        }
        else{}
      }
    }
  }

  return (l_nCrossCount & 0x01) != 0 ;
} // OK

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
int CSigPolygon::PointSeparation
( int i_nSigPointStart
, int i_nSigPointEnd
)
{
  int l_nSize = GetSize();
  int l_nDist;

  ASSERT((i_nSigPointStart >= 0) && (i_nSigPointStart < l_nSize));
  ASSERT((i_nSigPointEnd   >= 0) && (i_nSigPointEnd   < l_nSize));

  if(IsClosed() == FALSE)
  {
    l_nDist = i_nSigPointEnd - i_nSigPointStart;
  }
  else
  {
    l_nDist = abs(i_nSigPointEnd - i_nSigPointStart);
    l_nDist = min(l_nDist, abs(l_nSize - 1 - l_nDist));
  }

  return l_nDist;
} // OK

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
sSigPoint CSigPolygon::GetClosestPoint
( sSigPoint& i_roSigPoint
, int*       o_pnSigPointIndex // = NULL
)
{
  tREAL      l_nDistMin = cREAL_MAX;
  tREAL      l_nDist;
  int        l_nSigPointIndex;
  int        l_nLoop;
  int        l_nSize = GetSize();
  sSigPoint* l_psSigPoint;

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1)
  {
    l_psSigPoint = (sSigPoint*) mp_oasArraySigPoint[l_nLoop];

    l_nDist
    = (i_roSigPoint.nLonX - l_psSigPoint->nLonX)
    * (i_roSigPoint.nLonX - l_psSigPoint->nLonX)
    + (i_roSigPoint.nLatY - l_psSigPoint->nLatY)
    * (i_roSigPoint.nLatY - l_psSigPoint->nLatY)
    ;
    
    if(l_nDist < l_nDistMin)
    {
      l_nDistMin       = l_nDist;
      l_nSigPointIndex = l_nLoop;
    }
    else{}
  }

  if(o_pnSigPointIndex != NULL)
  {
    *o_pnSigPointIndex = l_nSigPointIndex;
  }
  else{}

  return *((sSigPoint*) mp_oasArraySigPoint[l_nSigPointIndex]);
} // OK

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
BOOL CSigPolygon::Diagonal
( int i_nSigPointStart
, int i_nSigPointEnd
)
{
  return
     (_InCone    (i_nSigPointStart, i_nSigPointEnd) == TRUE)
  && (_Diagonalie(i_nSigPointStart, i_nSigPointEnd) == TRUE)
  ;
} // OK

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
BOOL CSigPolygon::_Diagonalie
( int i_nSigPointStart
, int i_nSigPointEnd
)
{
  int l_nLoop;
  int l_nSize = GetSize();
  int l_nPlus;

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_nPlus = (l_nLoop + 1) % l_nSize;

    if
    (
      !(
            (l_nLoop == i_nSigPointStart)
         || (l_nLoop == i_nSigPointEnd)
         || (l_nPlus == i_nSigPointStart)
         || (l_nPlus == i_nSigPointEnd)
       )
    )
    {
      if
      (
        mp_sSigPoint.Intersect
        ( Point(i_nSigPointStart)
        , Point(i_nSigPointEnd)
        , Point(l_nLoop)
        , Point(l_nPlus)
        )
      )
      {
        return  FALSE;
      }
      else{}
    }
  }

  return  TRUE;
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
void CSigPolygon::Translate
( sSigVector i_oSigVector
)
{
  int l_nLoop;
  int l_nSize = GetSize();

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    *((sSigPoint*) mp_oasArraySigPoint[l_nLoop]) += i_oSigVector;
  }
} // OK

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
void CSigPolygon::Rationalise
( int i_nAngle
)
{
  int        l_nLoop;
  int        l_nSize       = GetSize() - 1;
  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0]; // Loop - 1
  sSigPoint* l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[1]; // Loop
  sSigPoint* l_psSigPoint2;

  for
  ( l_nLoop  = 1
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  ) 
  {
    l_psSigPoint2 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

    if
    (
        mp_sSigPoint.Angle
        ( *(l_psSigPoint0)
        , *(l_psSigPoint1)
        , *(l_psSigPoint2)
        )
      < i_nAngle
    )
    {
      mp_oasArraySigPoint.RemoveSlotAt(l_nLoop);
    }
    else{}

    // Shift pointers
    l_psSigPoint0 = l_psSigPoint1;
    l_psSigPoint1 = l_psSigPoint2;
  }
} // OK

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
tREAL CSigPolygon::SegmentLength
( int i_nSigPointStart
, int i_nSigPointEnd
)
{
  int        l_nLoop;
  int        l_nSize  = GetSize();

  tREAL      l_nWidth = D2R(0.0);

  sSigVector l_oSigVector;

  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0]; // Loop
  sSigPoint* l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nSize - 1]; // Loop + 1

  if
  (
       (i_nSigPointStart <  0)
    || (i_nSigPointStart >= l_nSize)
    || (i_nSigPointEnd   <  0)
    || (i_nSigPointEnd   >  l_nSize)
  )
  {
  }
  else
  {
    if
    (
         (i_nSigPointStart != 0)
      && (i_nSigPointEnd   == l_nSize)
    )
    {
      l_oSigVector  = *l_psSigPoint0 - *l_psSigPoint1;
      l_nWidth     += l_oSigVector.Length();

      for
      ( l_nLoop  = 0
      , l_nSize -= 1
      ; l_nLoop <  l_nSize
      ; l_nLoop += 1
      )
      {
        l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

        l_oSigVector  = *l_psSigPoint1 - *l_psSigPoint0;
        l_nWidth     += l_oSigVector.Length();

        // Shift pointers
        l_psSigPoint0 = l_psSigPoint1;
      }
    }
    else
    {
      if(i_nSigPointStart > i_nSigPointEnd)
      {
        l_oSigVector  = *l_psSigPoint0 - *l_psSigPoint1;
        l_nWidth     += l_oSigVector.Length();

        for
        ( l_nLoop  = 0
        ; l_nLoop <  i_nSigPointEnd
        ; l_nLoop += 1
        )
        { // 0---->End.....Start.......l_nSize
          l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

          l_oSigVector  = *l_psSigPoint1 - *l_psSigPoint0;
          l_nWidth     += l_oSigVector.Length();

          // Shift pointers
          l_psSigPoint0 = l_psSigPoint1;
        }

        l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[i_nSigPointStart]; // Loop

        for
        ( l_nLoop  = i_nSigPointStart
        , l_nSize -= 1
        ; l_nLoop <  l_nSize
        ; l_nLoop += 1
        )
        { // 0.....End.....Start------>l_nSize
          l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

          l_oSigVector  = *l_psSigPoint1 - *l_psSigPoint0;
          l_nWidth     += l_oSigVector.Length();

          // Shift pointers
          l_psSigPoint0 = l_psSigPoint1;
        }
      }
      else
      {
        if(i_nSigPointStart < i_nSigPointEnd)
        {
          l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[i_nSigPointStart]; // Loop

          for
          ( l_nLoop  = i_nSigPointStart
          ; l_nLoop <  i_nSigPointEnd
          ; l_nLoop += 1
          )
          { // 0.....Start---->End.......l_nSize
            l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

            l_oSigVector  = *l_psSigPoint1 - *l_psSigPoint0;
            l_nWidth     += l_oSigVector.Length();

            // Shift pointers
            l_psSigPoint0 = l_psSigPoint1;
          }
        }
        else{}
      }
    }
  }

  return l_nWidth;
} // OK

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
tREAL CSigPolygon::Area
(
)
{
  int        l_nLoop;
  int        l_nSize       = GetSize() - 1;
  tREAL      l_nArea       = D2R(0.0);
  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0]; // 0
  sSigPoint* l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[1]; // Loop
  sSigPoint* l_psSigPoint2;

  for
  ( l_nLoop  = 1
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigPoint2 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

    l_nArea
    += mp_sSigPoint.TriArea2
       ( *(l_psSigPoint0)
       , *(l_psSigPoint1)
       , *(l_psSigPoint2)
       )
    ;

    // Shift pointers
    l_psSigPoint1 = l_psSigPoint2;
  }

  if(l_nArea < D2R(0.0))
  {
    l_nArea = -l_nArea;
  }
  else{}

  return D2R(0.5) * l_nArea;
} // OK

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
sSigPoint CSigPolygon::Centroid
( bool i_bRefresh // = false
)
{
  int        l_nLoop;
  int        l_nSize       = GetSize();

  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0]; // 0
  sSigPoint* l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[1]; // Loop + 1
  sSigPoint* l_psSigPoint2;

  sSigPoint  l_oSigPointMid;

  tREAL      l_nArea;

  if
  (
       (mp_nCachePointNumber != l_nSize)
    || (i_bRefresh           == true)
  )
  {
    mp_nCachePointNumber    = l_nSize;

    mp_sSigPointCacheCentre = sSigPoint(D2R(0.0), D2R(0.0), D2R(0.0));
    mp_nCacheArea           = D2R(0.0);

    for
    ( l_nLoop  = 0
    , l_nSize -= 2
    ; l_nLoop <  l_nSize
    ; l_nLoop += 1
    )
    {
      l_psSigPoint2 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 2]; // Loop + 2

      l_oSigPointMid = (*l_psSigPoint0 + *l_psSigPoint1 + *l_psSigPoint2) / 3.0;
      l_nArea        = mp_sSigPoint.TriArea2(*l_psSigPoint0, *l_psSigPoint1, *l_psSigPoint2);

      l_oSigPointMid.Scale(l_nArea);

      mp_nCacheArea           += l_nArea;
      mp_sSigPointCacheCentre += l_oSigPointMid;

      // Shift pointers
      l_psSigPoint1 = l_psSigPoint2;
    }

    if(mp_nCacheArea > cEPSILON)
    {
      mp_sSigPointCacheCentre.Scale(D2R(1.0) / mp_nCacheArea); 
    }
    else
    {
      mp_sSigPointCacheCentre = sSigPoint( D2R(0.0), D2R(0.0), D2R(0.0) );

      if(IsClosed() == TRUE)
      {
        l_nSize += 1; // GetSize() - 1
      }
      else
      {
        l_nSize += 2; // GetSize()
      }

      for
      ( l_nLoop  = 0
      ; l_nLoop <  l_nSize
      ; l_nLoop += 1
      )
      {
        mp_sSigPointCacheCentre += *((sSigPoint*) mp_oasArraySigPoint[l_nLoop]);
      }

      mp_sSigPointCacheCentre.Scale(D2R(1.0 / (double) l_nSize));
    }
  }
  else{}

  return mp_sSigPointCacheCentre;
} // OK

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
/*
BOOL CSigPolygon::GetAttributes
( tREAL     *o_pnArea
, sSigPoint *o_poSigPointCentre
, sSigPoint *o_poSigPointNormal
, tREAL     *o_pnSlope
, tREAL     *o_pnAspect
)
{
  sSigPoint  SubMidPoint;
  tREAL      SubArea;
  sSigVector SubNorm;
  int        nNumUniquePoints = (IsClosed()) ? GetSize()-1 : GetSize();

  *o_pnArea           = D2R(0.0);        // Partial area sum
  *o_poSigPointNormal = sSigPoint( D2R(0.0), D2R(0.0), D2R(0.0) );
  *o_poSigPointCentre = sSigPoint( D2R(0.0), D2R(0.0), D2R(0.0) );

  CSigPolygon i_oSigPoint(nNumUniquePoints);  // Save current polygon
  if (!i_oSigPoint.GetSize()) return FALSE;
  for (int l_nLoop=0; l_nLoop < i_oSigPoint.GetSize(); l_nLoop++) i_oSigPoint[l_nLoop] = mp_paoSigPoint[l_nLoop];

    // i_nSigPointStart triangulating
  while (i_oSigPoint.GetSize() > 3) {
    BOOL bCornerCut = FALSE;
    for (l_nLoop = 0; l_nLoop < i_oSigPoint.GetSize(); l_nLoop++ ) {

      int iPlus1 = l_nLoop+1;        if (iPlus1 == i_oSigPoint.GetSize()) iPlus1 = 0;
      int iPlus2 = (iPlus1+1); if (iPlus2 == i_oSigPoint.GetSize()) iPlus2 = 0;
      
      if (i_oSigPoint.Diagonal(l_nLoop, iPlus2)) {

        SubArea     = TriArea2(i_oSigPoint[l_nLoop], i_oSigPoint[iPlus1], i_oSigPoint[iPlus2]);
        SubMidPoint = i_oSigPoint[l_nLoop] + i_oSigPoint[iPlus1] + i_oSigPoint[iPlus2];
        SubNorm    = SubNorm.Normal(i_oSigPoint[l_nLoop], i_oSigPoint[iPlus1], i_oSigPoint[iPlus2]);

        *o_pnArea     += SubArea;
        *o_poSigPointCentre += (SubMidPoint * SubArea);
        *o_poSigPointNormal     += (SubNorm * SubArea);

        i_oSigPoint.Delete(iPlus1);
        bCornerCut = TRUE;
        break;
      }
      if (Colinear(i_oSigPoint[l_nLoop], i_oSigPoint[iPlus1], i_oSigPoint[iPlus2])) {
        i_oSigPoint.Delete(iPlus1);
        bCornerCut = TRUE;
        break;
      }
    }
    if (!bCornerCut) break;    // Couldn't cut at all!
  }

  // Should be left with a single triangle
  //ASSERT(i_oSigPoint.GetSize() == 3);

  SubArea     = TriArea2(i_oSigPoint[0], i_oSigPoint[1], i_oSigPoint[2]);  *o_pnArea     += SubArea;
  SubMidPoint = i_oSigPoint[0] + i_oSigPoint[1] + i_oSigPoint[2];      *o_poSigPointCentre += (SubMidPoint * SubArea);
  SubNorm    = Normal(i_oSigPoint[0], i_oSigPoint[1], i_oSigPoint[2]);    *o_poSigPointNormal     += (SubNorm * SubArea);

  *o_poSigPointCentre /= 3.0;
  o_poSigPointNormal->Normalise();

  if (*o_pnArea > cEPSILON)     // Triangle or greater
    *o_poSigPointCentre /= (*o_pnArea);
  else             // all l_paoSigPoint coincident or colinear, so get average
  {
    *o_poSigPointCentre = sSigPoint( D2R(0.0), D2R(0.0), D2R(0.0) );
    for (l_nLoop=0; l_nLoop<nNumUniquePoints; l_nLoop++) *o_poSigPointCentre += mp_paoSigPoint[l_nLoop];
    *o_poSigPointCentre /= I2R(nNumUniquePoints);
  }
  *o_pnArea = (*o_pnArea < D2R(0.0))? D2R(-0.5) * *o_pnArea : D2R(0.5) * *o_pnArea;

  // Slope ( Slope = 1/Slope(Norm) )
  if (o_poSigPointNormal->z < cEPSILON)
    *o_pnSlope = cREAL_MAX;
  else
    *o_pnSlope = D2R(sqrt( R2D(o_poSigPointNormal->x*o_poSigPointNormal->x + o_poSigPointNormal->y*o_poSigPointNormal->y))) / o_poSigPointNormal->z;
  
  // Aspect
  if (*o_pnSlope < 0.01)
    *o_pnAspect = D2R(0.0);
  else {
    *o_pnAspect = D2R(atan2(R2D(o_poSigPointNormal->y), R2D(o_poSigPointNormal->x))) * cRAD2DEG;
    *o_pnAspect = D2R(90.0) - *o_pnAspect; 
    if (*o_pnAspect < D2R(0.0)) *o_pnAspect += D2R(360.0);
  }

  return TRUE;
}
*/
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
BOOL CSigPolygon::Intersected
( sSigPoint& i_roSigPointA
, sSigPoint& i_roSigPointB
)
{
  int        l_nLoop;
  int        l_nSize       = GetSize() - 1;
  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0]; // Loop
  sSigPoint* l_psSigPoint1;
  tREAL      l_nLength;
  tREAL      l_nDist;

  l_nLength
  = (i_roSigPointA.nLonX - i_roSigPointB.nLonX)
  * (i_roSigPointA.nLonX - i_roSigPointB.nLonX)
  + (i_roSigPointA.nLatY - i_roSigPointB.nLatY)
  * (i_roSigPointA.nLatY - i_roSigPointB.nLatY)
  ;

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

    l_nDist
    = (i_roSigPointA.nLonX - l_psSigPoint0->nLonX)
    * (i_roSigPointA.nLonX - l_psSigPoint0->nLonX)
    + (i_roSigPointA.nLatY - l_psSigPoint0->nLatY)
    * (i_roSigPointA.nLatY - l_psSigPoint0->nLatY)
    ;
    
    if(l_nDist <= l_nLength)
    {
      if
      (
         mp_sSigPoint.Intersect
         ( i_roSigPointA
         , i_roSigPointB
         , *(l_psSigPoint0)
         , *(l_psSigPoint1)
         )
      )
      {
        return TRUE;
      }
      else{}
    }
    else{}

    // Shift pointers
    l_psSigPoint0 = l_psSigPoint1;
  }

  return FALSE;
} // OK

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
BOOL CSigPolygon::IntersectedProp
( sSigPoint& i_roSigPointA
, sSigPoint& i_roSigPointB
)
{
  int        l_nLoop;
  int        l_nSize       = GetSize() - 1;
  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0];
  sSigPoint* l_psSigPoint1;
  tREAL      l_nLength;
  tREAL      l_nDist;

  l_nLength
  = (i_roSigPointA.nLonX - i_roSigPointB.nLonX)
  * (i_roSigPointA.nLonX - i_roSigPointB.nLonX)
  + (i_roSigPointA.nLatY - i_roSigPointB.nLatY)
  * (i_roSigPointA.nLatY - i_roSigPointB.nLatY)
  ;

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1];

    l_nDist
    = (i_roSigPointA.nLonX - l_psSigPoint0->nLonX)
    * (i_roSigPointA.nLonX - l_psSigPoint0->nLonX)
    + (i_roSigPointA.nLatY - l_psSigPoint0->nLatY)
    * (i_roSigPointA.nLatY - l_psSigPoint0->nLatY)
    ;
    
    if (l_nDist <= l_nLength)
    {
      if
      (
        mp_sSigPoint.IntersectProp
        ( i_roSigPointA
        , i_roSigPointB
         , *(l_psSigPoint0)
         , *(l_psSigPoint1)
        )
      )
      {
        return TRUE;
      }
      else{}
    }
    else{}

    // Shift pointers
    l_psSigPoint0 = l_psSigPoint1;
  }

  return FALSE;
} // OK

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
BOOL CSigPolygon::Triangulate
( CSigPolygon* o_poSigPolygonTri
)
{
  int         l_nLoop;
  int         l_nSize = GetSize();
  int         l_nTail;
  int         l_nIndexA;
  int         l_nIndexB;
  bool        l_bCornerCut    = true;
  CSigPolygon l_oSigPolyTempo = *this;

  while
  (
       (l_oSigPolyTempo.GetSize() > 3)
    && (l_bCornerCut == true)
  )
  {
    l_bCornerCut = false;

    for
    ( l_nLoop  = 0
    , l_nTail  = l_oSigPolyTempo.GetSize()
    ; l_nLoop <  l_nTail && l_bCornerCut == false
    ; l_nLoop += 1
    )
    {
      if((l_nLoop + 1) == l_nTail)
      {
        l_nIndexA = 0;
      }
      else
      {
        l_nIndexA = l_nLoop + 1;
      }

      if((l_nLoop + 2) == l_nTail)
      {
        l_nIndexB = 0;
      }
      else
      {
        l_nIndexB = l_nLoop + 2;
      }

      if(l_oSigPolyTempo.Diagonal(l_nLoop, l_nIndexB))
      {
        o_poSigPolygonTri->Add(l_oSigPolyTempo[l_nLoop]);
        o_poSigPolygonTri->Add(l_oSigPolyTempo[l_nIndexA]);
        o_poSigPolygonTri->Add(l_oSigPolyTempo[l_nIndexB]);

        l_oSigPolyTempo.Delete(l_nIndexA);
        l_bCornerCut = true;
      }
      else
      {
        if
        (
           mp_sSigPoint.Colinear
           ( l_oSigPolyTempo[l_nLoop]
           , l_oSigPolyTempo[l_nIndexA]
           , l_oSigPolyTempo[l_nIndexB]
           )
        )
        {
          l_oSigPolyTempo.Delete(l_nIndexA);

          l_bCornerCut = true;
        }
        else
        {
          l_nTail = l_oSigPolyTempo.GetSize();
        }
      }
    }
  }

  if(l_bCornerCut == true)
  {
    ASSERT(l_oSigPolyTempo.GetSize() == 3);

    o_poSigPolygonTri->Add(l_oSigPolyTempo[0]);
    o_poSigPolygonTri->Add(l_oSigPolyTempo[1]);
    o_poSigPolygonTri->Add(l_oSigPolyTempo[2]);
  }
  else{}

  return (l_bCornerCut == true) ? TRUE : FALSE;
} // OK

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
BOOL CSigPolygon::TriangCenter
( CSigPolygon* o_poSigPolygonTri
, sSigPoint&   i_roSigPointCentre
)
{
  int        l_nLoop;
  int        l_nSize = GetSize() - 1;
  sSigPoint* l_psSigPoint0;
  sSigPoint* l_psSigPoint1;

  o_poSigPolygonTri->RemoveAll();

  if(l_nSize == 3) 
  {
    for
    ( l_nLoop  = 0
    ; l_nLoop <  l_nSize
    ; l_nLoop += 1
    )
    {
      o_poSigPolygonTri->Add(*((sSigPoint*) mp_oasArraySigPoint[l_nLoop]));
    }
  } 
  else 
  {
    l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0]; // Loop

    for
    ( l_nLoop  = 0
    ; l_nLoop <  l_nSize
    ; l_nLoop += 1
    )
    {
      l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

      o_poSigPolygonTri->Add(i_roSigPointCentre);
      o_poSigPolygonTri->Add(*l_psSigPoint0); // Loop
      o_poSigPolygonTri->Add(*l_psSigPoint1); // Loop + 1

      // Shift pointers
      l_psSigPoint0 = l_psSigPoint1;
    }
  }

  return TRUE;
} // OK

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
BOOL CSigPolygon::TriangDelauney
( CSigPolygon* o_poSigPolygonTri
)
{
  int        l_anLoop[4];
  int        l_nSize = GetSize();
  tREAL*      l_panLength;
  sSigPoint* l_apsSigPoint[4];
  sSigPoint  l_oSigPointNormal;
  tREAL      l_anTempo[6];
  bool       l_bAbove;

  o_poSigPolygonTri->RemoveAll();

  l_panLength = new tREAL[l_nSize];

  for
  ( l_anLoop[0]  = 0
  ; l_anLoop[0] <  l_nSize
  ; l_anLoop[0] += 1
  )
  {
    l_apsSigPoint[0] = (sSigPoint*) mp_oasArraySigPoint[l_anLoop[0]];

    l_panLength[l_anLoop[0]]
    = l_apsSigPoint[0]->nLonX * l_apsSigPoint[0]->nLonX
    + l_apsSigPoint[0]->nLatY * l_apsSigPoint[0]->nLatY
    ;
  }

  // For each triple (l_anLoop[0],l_anLoop[1],l_anLoop[2]) 
  for
  ( l_anLoop[0]  = 0
  ; l_anLoop[0] <  l_nSize - 2
  ; l_anLoop[0] += 1
  )
  {
    l_apsSigPoint[0] = (sSigPoint*) mp_oasArraySigPoint[l_anLoop[0]];

    for
    ( l_anLoop[1]  = l_anLoop[0] + 1
    ; l_anLoop[1] <  l_nSize
    ; l_anLoop[1] += 1
    )
    {
      l_apsSigPoint[1] = (sSigPoint*) mp_oasArraySigPoint[l_anLoop[1]];

      for
      ( l_anLoop[2]  = l_anLoop[0] + 1
      ; l_anLoop[2] <  l_nSize
      ; l_anLoop[2] += 1
      )
      {
        if(l_anLoop[1] != l_anLoop[2])
        {
          l_apsSigPoint[2] = (sSigPoint*) mp_oasArraySigPoint[l_anLoop[2]];

          // Cache some stuff
          l_anTempo[0] = l_panLength[l_anLoop[1]] - l_panLength[l_anLoop[0]];
          l_anTempo[1] = l_panLength[l_anLoop[2]] - l_panLength[l_anLoop[0]];
          l_anTempo[2] = l_apsSigPoint[1]->nLonX - l_apsSigPoint[0]->nLonX;
          l_anTempo[3] = l_apsSigPoint[2]->nLonX - l_apsSigPoint[0]->nLonX;
          l_anTempo[4] = l_apsSigPoint[1]->nLatY - l_apsSigPoint[0]->nLatY;
          l_anTempo[5] = l_apsSigPoint[2]->nLatY - l_apsSigPoint[0]->nLatY;

          l_oSigPointNormal.nLonX
          = (l_anTempo[4] * l_anTempo[1])
          - (l_anTempo[5] * l_anTempo[0]);

          l_oSigPointNormal.nLatY
          = (l_anTempo[3] * l_anTempo[0])
          - (l_anTempo[2] * l_anTempo[1]);

          l_oSigPointNormal.nAltZ
          = (l_anTempo[2] * l_anTempo[5])
          - (l_anTempo[3] * l_anTempo[4])
          ;

          l_bAbove = (l_oSigPointNormal.nAltZ < 0);

          if(l_bAbove == true)
          {
            for
            ( l_anLoop[3]  = 0
            ; l_anLoop[3] <  l_nSize
            ; l_anLoop[3] += 1
            )
            {
              l_apsSigPoint[3] = (sSigPoint*) mp_oasArraySigPoint[l_anLoop[3]];

              l_bAbove
              =  l_bAbove
              && (
                     (l_apsSigPoint[3]->nLonX  - l_apsSigPoint[0]->nLonX)  * l_oSigPointNormal.nLonX
                   + (l_apsSigPoint[3]->nLatY  - l_apsSigPoint[0]->nLatY)  * l_oSigPointNormal.nLatY
                   + (l_panLength[l_anLoop[3]] - l_panLength[l_anLoop[0]]) * l_oSigPointNormal.nAltZ
                 )
              <= 0
              ;
            }
          }
          else{}

          if(l_bAbove == true)
          {
            o_poSigPolygonTri->Add(*l_apsSigPoint[0]);
            o_poSigPolygonTri->Add(*l_apsSigPoint[1]);
            o_poSigPolygonTri->Add(*l_apsSigPoint[2]);
          }
          else{}
        }
      }
    }
  }

  delete [] l_panLength;

  return TRUE;
} // OK

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
void CSigPolygon::NaturalSpline
( double*& o_rpnSplineCoeffB
, double*& o_rpnSplineCoeffC
, double*& o_rpnSplineCoeffD
)
{
  int        l_nLoop;
  int        l_nSize = GetSize() - 1;

  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0]; // Loop - 1
  sSigPoint* l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[1]; // Loop
  sSigPoint* l_psSigPoint2; // Loop + 1

  double*    h     = new double[l_nSize];
  double*    hdiff = new double[l_nSize];
  double*    alpha = new double[l_nSize];
  double*    ell   = new double[l_nSize + 1];
  double*    mu    = new double[l_nSize];
  double*    z     = new double[l_nSize + 1];
  double     recip;
  double     oneThird = 1.0 / 3.0;

  ell[0]       = 1.0;
  mu[0]        = 0.0;
  z[0]         = 0.0;
  ell[l_nSize] = 1.0;
  z[l_nSize]   = 0.0;

  for
  ( l_nLoop  = 1
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigPoint2 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop + 1]; // Loop + 1

    h[l_nLoop]     = l_psSigPoint2->nLonX - l_psSigPoint1->nLonX;
    hdiff[l_nLoop] = l_psSigPoint2->nLonX - l_psSigPoint0->nLonX;

    alpha[l_nLoop]
    = 3.0
    * (
          l_psSigPoint2->nLatY * h[l_nLoop - 1]
        - l_psSigPoint1->nLatY * hdiff[l_nLoop]
        + l_psSigPoint0->nLatY * h[l_nLoop]
      )
    / (h[l_nLoop - 1] * h[l_nLoop])
    ;

    // Shift pointers
    l_psSigPoint0 = l_psSigPoint1;
    l_psSigPoint1 = l_psSigPoint2;
  }

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    ell[l_nLoop] = 2.0 * hdiff[l_nLoop] - h[l_nLoop - 1] * mu[l_nLoop - 1];
    recip        = 1.0 / ell[l_nLoop];
    mu[l_nLoop]  = recip * h[l_nLoop];
    z[l_nLoop]   = recip * (alpha[l_nLoop] - h[l_nLoop - 1] * z[l_nLoop - 1]);
  }

  o_rpnSplineCoeffB = new double[l_nSize];
  o_rpnSplineCoeffC = new double[l_nSize + 1];
  o_rpnSplineCoeffD = new double[l_nSize];

  o_rpnSplineCoeffC[l_nSize] = 0.0;

  l_psSigPoint2 = (sSigPoint*) mp_oasArraySigPoint[l_nSize]; // Loop + 1

  for
  ( l_nLoop  = l_nSize - 1
  ; l_nLoop >= 0
  ; l_nLoop -= 1
  )
  {
    l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop]; // Loop

    o_rpnSplineCoeffC[l_nLoop]
    = z[l_nLoop]
    - mu[l_nLoop] * o_rpnSplineCoeffC[l_nLoop + 1]
    ;
    
    recip = 1.0 / h[l_nLoop];

    o_rpnSplineCoeffB[l_nLoop]
    = recip
    * (
          l_psSigPoint2->nLatY
        - l_psSigPoint1->nLatY
      )
    - h[l_nLoop]
    * (
          o_rpnSplineCoeffC[l_nLoop + 1]
        + 2.0 * o_rpnSplineCoeffC[l_nLoop]
      )
    * oneThird
    ;
    
    o_rpnSplineCoeffD[l_nLoop]
    = oneThird
    * recip
    * (
          o_rpnSplineCoeffC[l_nLoop+1]
        - o_rpnSplineCoeffC[l_nLoop]
      )
    ;

    // Shift pointers downward
    l_psSigPoint2 = l_psSigPoint1;
  }

  delete[] h;
  delete[] hdiff;
  delete[] alpha;
  delete[] ell;
  delete[] mu;
  delete[] z;
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
tREAL CSigPolygon::Curvature
( int i_nSigPointIndex
)
{
  sSigVector l_oSigVectorA;
  sSigVector l_oSigVectorB;
  sSigVector l_oSigVectorC;

  sSigPoint* l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[i_nSigPointIndex - 1]; // Loop - 1
  sSigPoint* l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[i_nSigPointIndex];     // Loop
  sSigPoint* l_psSigPoint2 = (sSigPoint*) mp_oasArraySigPoint[i_nSigPointIndex + 1]; // Loop + 1

  tREAL      l_nLengthN;
  tREAL      l_nLengthA;
  tREAL      l_nLengthB;
  tREAL      l_nCurvature = 0.0;

  if
  (
       (i_nSigPointIndex > 0)
    && (i_nSigPointIndex < GetSize() - 1)
  )
  {
    l_nLengthN
    = D2R
      (
        sqrt
        ( 
            (l_psSigPoint1->nLonX - l_psSigPoint0->nLonX)
          * (l_psSigPoint1->nLonX - l_psSigPoint0->nLonX)
          + (l_psSigPoint1->nLatY - l_psSigPoint0->nLatY)
          * (l_psSigPoint1->nLatY - l_psSigPoint0->nLatY)
        )
      )
    ;
  
    ASSERT(l_nLengthN > D2R(0.0));

    l_nLengthA = D2R(1.0) / l_nLengthN;

    l_oSigVectorA.nLonX = (l_psSigPoint1->nLonX - l_psSigPoint0->nLonX) * l_nLengthA;
    l_oSigVectorA.nLatY = (l_psSigPoint1->nLatY - l_psSigPoint0->nLatY) * l_nLengthA;

    l_nLengthN
    = D2R
      (
        sqrt
        (
            (l_psSigPoint2->nLonX - l_psSigPoint1->nLonX)
          * (l_psSigPoint2->nLonX - l_psSigPoint1->nLonX)
          + (l_psSigPoint2->nLatY - l_psSigPoint1->nLatY)
          * (l_psSigPoint2->nLatY - l_psSigPoint1->nLatY)
        )
      )
    ;

    ASSERT(l_nLengthN > D2R(0.0));

    l_nLengthB = D2R(1.0) / l_nLengthN;

    l_oSigVectorB.nLonX = (l_psSigPoint2->nLonX - l_psSigPoint1->nLonX) * l_nLengthB;
    l_oSigVectorB.nLatY = (l_psSigPoint2->nLatY - l_psSigPoint1->nLatY) * l_nLengthB;
    l_oSigVectorC.nLonX = (l_oSigVectorB.nLonX  - l_oSigVectorA.nLonX)  * l_nLengthA;
    l_oSigVectorC.nLatY = (l_oSigVectorB.nLatY  - l_oSigVectorA.nLatY)  * l_nLengthA;

    l_nCurvature
    = D2R
      (
        sqrt
        (
            l_oSigVectorC.nLonX * l_oSigVectorC.nLonX
          + l_oSigVectorC.nLatY * l_oSigVectorC.nLatY
        )
      )
    ;

    if
    (
      mp_sSigPoint.Left
      ( *l_psSigPoint0
      , *l_psSigPoint1
      , *l_psSigPoint2
      )
      == FALSE
    )
    {
      l_nCurvature = -l_nCurvature;
    }
    else{}
  }
  else{}

  return l_nCurvature;
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
tREAL CSigPolygon::Curvature
( int i_nSigPointIndex
, int i_nSampleSize
)
{
  int    l_nLoop;
  int    l_nSize = GetSize();

  int    nMinPt;
  int    nMaxPt;
  int    nPoint;

  tREAL  IndexDistance;
  tREAL  distance;

  double numerator;
  double denomenator;

  double *b1;
  double *c1;
  double *d1;
  double *b2;
  double *c2;
  double *d2;

  sSigPoint* l_psSigPoint0; // Loop
  sSigPoint* l_psSigPoint1; // Loop + 1

  ASSERT
  (
       i_nSigPointIndex >= 0
    && i_nSigPointIndex <  l_nSize
  );

  // Get a range of point on the polygon to sample
  if(i_nSampleSize > i_nSigPointIndex)
  {
    nMinPt = 0;
  }
  else
  {
    nMinPt = i_nSigPointIndex - i_nSampleSize;
  }

  if(i_nSigPointIndex + i_nSampleSize >= l_nSize)
  {
    nMaxPt = GetSize() - 1;
  }
  else
  {
    nMaxPt = i_nSigPointIndex + i_nSampleSize;
  }

  // Store these l_paoSigPoint in a temporary polygon
  CSigPolygon XVals; // (nMaxPt - nMinPt + 1);
  CSigPolygon YVals; // (nMaxPt - nMinPt + 1);

  IndexDistance = 0.0;
  distance      = 0.0;

  l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[nMinPt - 1]; // Loop - 1

  for
  ( l_nLoop  = nMinPt
  ; l_nLoop <= nMaxPt
  ; l_nLoop += 1
  )
  {
    l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop]; // Loop

    if(l_nLoop > nMinPt)
    {
      distance
      += D2R
         (
            sqrt(
                    (l_psSigPoint1->nLonX - l_psSigPoint0->nLonX)
                  * (l_psSigPoint1->nLonX - l_psSigPoint0->nLonX)
                  + (l_psSigPoint1->nLatY - l_psSigPoint0->nLatY)
                  * (l_psSigPoint1->nLatY - l_psSigPoint0->nLatY)
                )
         )
      ;
    }
    else{}

    XVals.Add
    (
      sSigPoint
      ( distance
      , l_psSigPoint1->nLonX
      , 0.0
      )
    );

    YVals.Add
    (
      sSigPoint
      ( distance
      , l_psSigPoint1->nLatY
      , 0.0
      )
    );

/*
    XVals[l_nLoop].nLonX = distance;
    XVals[l_nLoop].nLatY = l_psSigPoint1->nLonX;
    YVals[l_nLoop].nLonX = distance;
    YVals[l_nLoop].nLatY = l_psSigPoint1->nLatY;
*/

    if(l_nLoop == i_nSigPointIndex)
    {
      IndexDistance = distance;
    }
    else{}

    // Shift pointers
    l_psSigPoint0 = l_psSigPoint1;
  }

  // fit a spline to the l_paoSigPoint in the temp polygon.

  XVals.NaturalSpline(b1, c1, d1);
  YVals.NaturalSpline(b2, c2, d2);

  // The point in question is i_nSigPointIndex-nMinPt. The spline curve for this point is 
  nPoint = i_nSigPointIndex - nMinPt;

  numerator   = b1[nPoint] * 2.0 * c2[nPoint] - b2[nPoint] * 2.0 * c1[nPoint];
  denomenator = pow(b1[nPoint] * b1[nPoint] + b2[nPoint] * b2[nPoint], 1.5);
  
  delete [] b1;
  delete [] c1;
  delete [] d1;
  delete [] b2;
  delete [] c2;
  delete [] d2;

  if(denomenator > 0)
  {
    return D2R(numerator / denomenator);
  }
  else
  {
    return D2R(0.0);  // could be nonzero in the limit
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
int CSigPolygon::Simplify
( CSigPolygon* o_poSigPolygonSimple
, float        i_nTolerance
)
{
  int        l_nLoop;
  int        l_nSize = GetSize();
  tREAL      l_nTolSquare = i_nTolerance * i_nTolerance;
  sSigPoint  l_oSigPoint;

  sSigPoint* l_psSigPoint0; // Loop - 1
  sSigPoint* l_psSigPoint1; // Loop

  //

  l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[0];
  l_psSigPoint0->uFlag.sFlag.bMark = 1;
  l_psSigPoint0->uFlag.sFlag.bKeep = 1;

  for
  ( l_nLoop  = 1
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop]; // Loop
    l_psSigPoint1->uFlag.sFlag.bKeep = 0;

    l_oSigPoint = *l_psSigPoint1 - *l_psSigPoint0;

    if((l_oSigPoint * l_oSigPoint) >= l_nTolSquare)
    {
      l_psSigPoint1->uFlag.sFlag.bMark = 1;

      // Shift pointers
      l_psSigPoint0 = l_psSigPoint1;
    }
    else
    {
      l_psSigPoint1->uFlag.sFlag.bMark = 0;
    }
  }

  l_psSigPoint0 = (sSigPoint*) mp_oasArraySigPoint[l_nSize - 1];
  l_psSigPoint0->uFlag.sFlag.bMark = 1;
  l_psSigPoint0->uFlag.sFlag.bKeep = 1;

  _SimplifyDP
  ( i_nTolerance
  , this
  , 0 // Start
  , l_nSize // End
  );

  o_poSigPolygonSimple->RemoveAll();

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigPoint1 = (sSigPoint*) mp_oasArraySigPoint[l_nLoop]; // Loop

    if(l_psSigPoint1->uFlag.sFlag.bKeep != 0)
    {
      o_poSigPolygonSimple->Add(*l_psSigPoint1);
    }
  }

//  if(IsClosed())
//  {
//    o_poSigPolygonSimple->Close();
//  }
//  else{}

  return o_poSigPolygonSimple->GetSize();
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
void CSigPolygon::_SimplifyDP
( float        i_nTolerance
, CSigPolygon* i_poSigPolyVertex
, int          i_nIndexStart
, int          i_nIndexEnd
)
{
  if(i_nIndexEnd > i_nIndexStart + 1)
  {
    int        l_nLoop;
    int        l_nScan      = i_nIndexStart;
    tREAL      l_nDistMax   = 0.0f;
    tREAL      l_nTolSquare = i_nTolerance * i_nTolerance;

    sSigPoint* l_psSigPoint0 = (sSigPoint*) i_poSigPolyVertex->mp_oasArraySigPoint[i_nIndexStart]; // Loop
    sSigPoint* l_psSigPoint1 = (sSigPoint*) i_poSigPolyVertex->mp_oasArraySigPoint[i_nIndexEnd];   // Loop + 1
    sSigPoint* l_psSigPoint2;
    sSigPoint* l_psSigPoint3;

    sSigVector u  = *l_psSigPoint1 - *l_psSigPoint0; // segment direction vector
    sSigVector w;

    tREAL      cu = u * u;   // segment length squared

    sSigPoint  Pb; // base of perpendicular from i_poSigPolyVertex[l_nLoop] to S
    sSigPoint  l_oSigPoint;

    tREAL      b;
    tREAL      cw;
    tREAL      l_nDistSquare; // l_nDistSquare = distance i_poSigPolyVertex[l_nLoop] to S squared

    //

    for
    ( l_nLoop  = i_nIndexStart + 1
    ; l_nLoop <  i_nIndexEnd
    ; l_nLoop += 1
    )
    {
      l_psSigPoint2 = (sSigPoint*) i_poSigPolyVertex->mp_oasArraySigPoint[l_nLoop];

      if(l_psSigPoint2->uFlag.sFlag.bMark != 0)
      {
        w  = *l_psSigPoint2 - *l_psSigPoint0;
        cw = w * u;

        if(cw <= 0)
        {
          l_oSigPoint = *l_psSigPoint2 - *l_psSigPoint0;
        }
        else
        {
          if(cu <= cw)
          {
            l_oSigPoint = *l_psSigPoint2 - *l_psSigPoint1;
          }
          else
          {
            b  = cw / cu;
          
            Pb = *l_psSigPoint0 + u * b;

            l_oSigPoint = *l_psSigPoint2 - Pb;
          }
        }

        l_nDistSquare = l_oSigPoint * l_oSigPoint;

        if(l_nDistMax < l_nDistSquare)
        {
          l_psSigPoint3 = l_psSigPoint2;
          l_nDistMax    = l_nDistSquare;
        }
        else{}
      }
    } 

    if(l_nDistMax > l_nTolSquare)
    {
      l_psSigPoint3->uFlag.sFlag.bKeep = 1;

      _SimplifyDP
      ( i_nTolerance
      , i_poSigPolyVertex
      , i_nIndexStart
      , l_nScan
      );
      
      _SimplifyDP
      ( i_nTolerance
      , i_poSigPolyVertex
      , l_nScan
      , i_nIndexEnd
      );
    }
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
BOOL CSigPolygon::Clipping
( CSigPolygon* o_poSigPolygonSimple
, CSigPolygon& i_roSigPolygonSrc
, int          i_nClippingMode
)
{
/*
  GPC_DIFF  // Difference
  GPC_INT   // Intersection
  GPC_XOR   // Exclusive or
  GPC_UNION // Union
*/
/*
  gpc_polygon subject;
  gpc_polygon clip;
  gpc_polygon result;

  gpc_read_polygon2(this, &subject);
  gpc_read_polygon2(&i_roSigPolygonSrc, &clip);

  gpc_polygon_clip
  ( (gpc_op) i_nClippingMode // 
  , &subject
  , &clip
  , &result
  );

  gpc_write_polygon2(o_poSigPolygonSimple, &result);

  gpc_free_polygon(&subject);
  gpc_free_polygon(&clip);
  gpc_free_polygon(&result);
*/
  return o_poSigPolygonSimple->GetSize() > 0;
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
sSigPoint& CSigPolygon::operator[]
( int i_nSigPointIndex
)
{
  return Point(i_nSigPointIndex);
} // OK

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
sSigPoint& CSigPolygon::Point
( int i_nSigPointIndex
)
{
  ASSERT(i_nSigPointIndex >= 0 && i_nSigPointIndex < GetSize());

  return *((sSigPoint*) mp_oasArraySigPoint[i_nSigPointIndex]);
} // OK

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
void CSigPolygon::operator=
( CSigPolygon& i_oSigPoint
)
{
  int l_nLoop;
  int l_nSize;

  if(this != &i_oSigPoint)
  {
    RemoveAll();

    for
    ( l_nLoop  = 0
    , l_nSize  = i_oSigPoint.GetSize()
    ; l_nLoop <  l_nSize
    ; l_nLoop += 1
    )
    {
      Add(i_oSigPoint[l_nLoop]);
    }
  }
} // OK

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
BOOL CSigPolygon::_InCone
( int i_nSigPointStart
, int i_nSigPointEnd
)
{
  sSigPoint* l_psSigPointStart = (sSigPoint*) mp_oasArraySigPoint[i_nSigPointStart];
  sSigPoint* l_psSigPointEnd   = (sSigPoint*) mp_oasArraySigPoint[i_nSigPointEnd];
  sSigPoint* l_psSigPointPlus  = (sSigPoint*) mp_oasArraySigPoint[(i_nSigPointStart + 1)             % GetSize()];
  sSigPoint* l_psSigPointMinus = (sSigPoint*) mp_oasArraySigPoint[(i_nSigPointStart + GetSize() - 1) % GetSize()];

  if(mp_sSigPoint.LeftOn(*l_psSigPointMinus, *l_psSigPointStart, *l_psSigPointPlus))
  {
    return 
       mp_sSigPoint.Left(*l_psSigPointStart, *l_psSigPointEnd,   *l_psSigPointMinus)
    && mp_sSigPoint.Left(*l_psSigPointEnd,   *l_psSigPointStart, *l_psSigPointPlus);
  }
  else
  {
    return
    !(
          mp_sSigPoint.LeftOn(*l_psSigPointStart, *l_psSigPointEnd,   *l_psSigPointPlus)
       && mp_sSigPoint.LeftOn(*l_psSigPointEnd,   *l_psSigPointStart, *l_psSigPointMinus)
     )
    ;
  }
} // OK
