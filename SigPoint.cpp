// SigPoint.cpp: implementation of the sSigPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SigPoint.h"

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
sSigPoint::sSigPoint
(
)
{
  nLonX = D2R(0.0);
  nLatY = D2R(0.0);
  nAltZ = D2R(0.0);
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
sSigPoint::sSigPoint
( double i_nLonX
, double i_nLatY
, double i_nAltZ // = 0.0
)
{
  nLonX = D2R(i_nLonX);
  nLatY = D2R(i_nLatY);
  nAltZ = D2R(i_nAltZ);
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
sSigPoint sSigPoint::operator-
( sSigPoint i_sSigPoint
)
{
  return sSigPoint
  ( nLonX - i_sSigPoint.nLonX
  , nLatY - i_sSigPoint.nLatY
  , nAltZ - i_sSigPoint.nAltZ
  );
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
sSigPoint sSigPoint::operator-
(
)
{
  return sSigPoint
  ( 0.0 - nLonX
  , 0.0 - nLatY
  , 0.0 - nAltZ
  );
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
sSigPoint sSigPoint::operator-=
( sSigPoint i_sSigPoint
)
{
  nLonX -= i_sSigPoint.nLonX;
  nLatY -= i_sSigPoint.nLatY;
  nAltZ -= i_sSigPoint.nAltZ;
  
  return *this;
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
sSigPoint sSigPoint::operator+
( sSigPoint i_sSigPoint
)
{
  return sSigPoint
  ( nLonX + i_sSigPoint.nLonX
  , nLatY + i_sSigPoint.nLatY
  , nAltZ + i_sSigPoint.nAltZ
  );
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
sSigPoint sSigPoint::operator+=
( sSigPoint i_sSigPoint
)
{
  nLonX += i_sSigPoint.nLonX;
  nLatY += i_sSigPoint.nLatY;
  nAltZ += i_sSigPoint.nAltZ;
  
  return *this;
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
tREAL sSigPoint::operator*
( sSigPoint i_sSigPoint
)
{
  return
    nLonX * i_sSigPoint.nLonX
  + nLatY * i_sSigPoint.nLatY
  + nAltZ * i_sSigPoint.nAltZ
  ;
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
sSigPoint sSigPoint::operator*
( tREAL i_nFactor
)
{
  return sSigPoint
  ( nLonX * i_nFactor
  , nLatY * i_nFactor
  , nAltZ * i_nFactor
  );
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
sSigPoint sSigPoint::operator*=
( tREAL i_nFactor
)
{
  nLonX *= i_nFactor;
  nLatY *= i_nFactor;
  nAltZ *= i_nFactor;
  
  return *this;
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
sSigPoint sSigPoint::operator/
( tREAL i_nFactor
)
{
  return sSigPoint
  ( nLonX / i_nFactor
  , nLatY / i_nFactor
  , nAltZ / i_nFactor
  );
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
sSigPoint sSigPoint::operator/=
( tREAL i_nFactor
)
{
  nLonX /= i_nFactor;
  nLatY /= i_nFactor;
  nAltZ /= i_nFactor;
  
  return *this;
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
sSigPoint sSigPoint::operator^
( sSigPoint i_sSigPoint
)
{
  return sSigPoint
  ( nLatY * i_sSigPoint.nAltZ - i_sSigPoint.nLatY * nAltZ
  , nAltZ * i_sSigPoint.nLonX - i_sSigPoint.nAltZ * nLonX
  , nLonX * i_sSigPoint.nLatY - i_sSigPoint.nLonX * nLatY
  );
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
// MODIF_KOCH 070416
// DK 070416 (SIGPOINT) : Correction de la surcharge d'operateur
sSigPoint sSigPoint::operator=
( sSigPoint i_sSigPoint
)
{
  nLonX = i_sSigPoint.nLonX;
  nLatY = i_sSigPoint.nLatY;
  nAltZ = i_sSigPoint.nAltZ;

  return *this;
}
// MODIF_KOCH 070416

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
// MODIF_KOCH 070416
// DK 070416 (SIGPOINT) : Correction de la surcharge d'operateur
/*
sSigPoint sSigPoint::operator=
( sSigPoint& i_sSigPoint
)
{
  nLonX = i_sSigPoint.nLonX;
  nLatY = i_sSigPoint.nLatY;
  nAltZ = i_sSigPoint.nAltZ;

  return *this;
}
*/
// MODIF_KOCH 070416

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
BOOL sSigPoint::operator==
( sSigPoint& i_roSigPoint
)
{
  if
  (
       (ABSO(nLonX - i_roSigPoint.nLonX) > cEPSILON)
    || (ABSO(nLatY - i_roSigPoint.nLatY) > cEPSILON)
    || (ABSO(nAltZ - i_roSigPoint.nAltZ) > cEPSILON)
  )
  {
	  return FALSE;
  }
  else
  {
	  return TRUE;
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
BOOL sSigPoint::operator!=
( sSigPoint& i_roSigPoint
)
{
  return !(*this == i_roSigPoint);
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
tREAL sSigPoint::Dot
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
)
{
  return 
    i_oSigPointA.nLonX * i_oSigPointB.nLonX
  + i_oSigPointA.nLatY * i_oSigPointB.nLatY
  + i_oSigPointA.nAltZ * i_oSigPointB.nAltZ
  ;
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
sSigPoint sSigPoint::Cross
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
)
{
  return sSigPoint
  ( i_oSigPointA.nLatY * i_oSigPointB.nAltZ - i_oSigPointB.nLatY * i_oSigPointA.nAltZ
  , i_oSigPointB.nLonX * i_oSigPointA.nAltZ - i_oSigPointA.nLonX * i_oSigPointB.nAltZ
  , i_oSigPointA.nLonX * i_oSigPointB.nLatY - i_oSigPointB.nLonX * i_oSigPointA.nLatY
  );
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
tREAL sSigPoint::Length2
(
)
{
  return
    nLonX * nLonX
  + nLatY * nLatY
  + nAltZ * nAltZ
  ;
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
tREAL sSigPoint::Length
(
)
{
  return D2R
  (
    sqrt
    ( nLonX * nLonX
    + nLatY * nLatY
    + nAltZ * nAltZ
    )
  );
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
void sSigPoint::Scale
( tREAL i_nFactor
)
{
  nLonX *= i_nFactor;
  nLatY *= i_nFactor;
  nAltZ *= i_nFactor;
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
void sSigPoint::Normalise
( void
)
{
  tREAL l_nLength = Length();

  if(l_nLength != D2R(0.0))
  {
    Scale(D2R(1.0) / l_nLength);
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
sSigVector sSigPoint::Normal
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
)
{
  return Cross
  ( i_oSigPointB - i_oSigPointA
  , i_oSigPointC - i_oSigPointA
  );
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
tREAL sSigPoint::Angle
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
)
{
  sSigVector l_oSigPointV = i_oSigPointB - i_oSigPointA;
  sSigVector l_oSigPointU = i_oSigPointC - i_oSigPointB;

  return Angle(l_oSigPointV, l_oSigPointU);

/*
  double l_nCosA;

  l_nCosA
  = (l_oSigPointU * l_oSigPointV)
  / D2R
    ( sqrt
      (
        R2D
        (   l_oSigPointU.Length2()
          * l_oSigPointV.Length2()
        )
      )
    )
  ; 

  return D2R
  (
    max
    ( 0.0
    , acos(l_nCosA) * cRAD2DEG
    )
  );
*/
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
tREAL sSigPoint::Angle
( sSigVector l_oSigPointV
, sSigVector l_oSigPointU
)
{
  double l_nCosA
  = (l_oSigPointU * l_oSigPointV)
  / D2R
    ( sqrt
      (
        R2D
        (   l_oSigPointU.Length2()
          * l_oSigPointV.Length2()
        )
      )
    )
  ; 

  return D2R
  (
    max
    ( 0.0
    , acos(l_nCosA) * cRAD2DEG
    )
  );
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
tREAL sSigPoint::TriArea2
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
)
{
  return TriArea2
  ( i_oSigPointB - i_oSigPointA
  , i_oSigPointC - i_oSigPointA
  );

/*
  sSigVector l_nSigPointX = Cross(i_oSigPointB - i_oSigPointA, i_oSigPointC - i_oSigPointA);

  if(l_nSigPointX.nAltZ < D2R(0.0))
  {
    return -l_nSigPointX.Length();
  }
  else
  {
    return  l_nSigPointX.Length();
  }
*/
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
tREAL sSigPoint::TriArea2
( sSigVector l_oSigPointU
, sSigVector l_oSigPointV
)
{
  sSigVector l_nSigPointX = Cross(l_oSigPointU,l_oSigPointV);

  if(l_nSigPointX.nAltZ < D2R(0.0))
  {
    return -l_nSigPointX.Length();
  }
  else
  {
    return  l_nSigPointX.Length();
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
sSigPoint sSigPoint::GetClosestPoint
( sSigPoint& i_roSigPointA
, sSigPoint& i_roSigPointB
, sSigPoint& i_roSigPointP
)
{
  if
  (
      ABSO(i_roSigPointA.nLonX - i_roSigPointB.nLonX)
    < cEPSILON
  )
  { // Vertical line
    return sSigPoint
    ( i_roSigPointA.nLonX
    , i_roSigPointP.nLatY
    , i_roSigPointA.nAltZ
    );
  }
  else
  {
    if
    (
        ABSO(i_roSigPointB.nLatY - i_roSigPointA.nLatY)
      < cEPSILON
    )
    { // Horizontal line
      return sSigPoint
      ( i_roSigPointP.nLonX
      , i_roSigPointA.nLatY
      , i_roSigPointA.nAltZ
      );
    }
    else
    {
      tREAL l_nSlope = (i_roSigPointB.nLatY - i_roSigPointA.nLatY) / (i_roSigPointB.nLonX - i_roSigPointA.nLonX);
      tREAL l_nCross =  i_roSigPointA.nLatY - i_roSigPointA.nLonX * l_nSlope;
      tREAL l_nPoint = l_nSlope / (l_nSlope * l_nSlope + 1) * (i_roSigPointP.nLatY - l_nCross + i_roSigPointP.nLonX / l_nSlope);

      return sSigPoint
      ( l_nPoint
      , l_nPoint * l_nSlope + l_nCross
      , i_roSigPointA.nAltZ
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
BOOL sSigPoint::IntersectProp
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
, sSigPoint i_oSigPointD
)
{
  if
  (
       Colinear(i_oSigPointA, i_oSigPointB, i_oSigPointC)
    || Colinear(i_oSigPointA, i_oSigPointB, i_oSigPointD)
    || Colinear(i_oSigPointC, i_oSigPointD, i_oSigPointA)
    || Colinear(i_oSigPointC, i_oSigPointD, i_oSigPointB)
  )
  {
    return FALSE;
  }
  else
  {
    return 
       XOR
       ( Left(i_oSigPointA, i_oSigPointB, i_oSigPointC)
       , Left(i_oSigPointA, i_oSigPointB, i_oSigPointD)
       )
    && XOR
       ( Left(i_oSigPointC, i_oSigPointD, i_oSigPointA)
       , Left(i_oSigPointC, i_oSigPointD, i_oSigPointB)
       )
    ;
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
BOOL sSigPoint::Intersect
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
, sSigPoint i_oSigPointD
)
{
  if
  (
       (IntersectProp(i_oSigPointA, i_oSigPointB, i_oSigPointC, i_oSigPointD) == TRUE)
    || (Between(i_oSigPointA, i_oSigPointB, i_oSigPointC) == TRUE)
    || (Between(i_oSigPointA, i_oSigPointB, i_oSigPointD) == TRUE)
    || (Between(i_oSigPointC, i_oSigPointD, i_oSigPointA) == TRUE)
    || (Between(i_oSigPointC, i_oSigPointD, i_oSigPointB) == TRUE)
  )
  {
    return TRUE;
  }
  else
  {
    return FALSE;
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
BOOL sSigPoint::Left
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
)
{
  tREAL l_nCross
  = (i_oSigPointB.nLonX - i_oSigPointA.nLonX)
  * (i_oSigPointC.nLatY - i_oSigPointA.nLatY)
  - (i_oSigPointC.nLonX - i_oSigPointA.nLonX)
  * (i_oSigPointB.nLatY - i_oSigPointA.nLatY)
  ;

  return (l_nCross > D2R(0.0));
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
BOOL sSigPoint::LeftOn
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
)
{
  tREAL l_nCross
  = (i_oSigPointB.nLonX - i_oSigPointA.nLonX)
  * (i_oSigPointC.nLatY - i_oSigPointA.nLatY)
  - (i_oSigPointC.nLonX - i_oSigPointA.nLonX)
  * (i_oSigPointB.nLatY - i_oSigPointA.nLatY)
  ;

  return (l_nCross >= D2R(0.0));
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
BOOL sSigPoint::Colinear
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
)
{
  tREAL l_nCross
  = (i_oSigPointB.nLonX - i_oSigPointA.nLonX)
  * (i_oSigPointC.nLatY - i_oSigPointA.nLatY)
  - (i_oSigPointC.nLonX - i_oSigPointA.nLonX)
  * (i_oSigPointB.nLatY - i_oSigPointA.nLatY)
  ;

  return (ABSO(l_nCross) < cEPSILON);
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
BOOL sSigPoint::Between
( sSigPoint i_oSigPointA
, sSigPoint i_oSigPointB
, sSigPoint i_oSigPointC
)
{
  if(Colinear(i_oSigPointA, i_oSigPointB, i_oSigPointC) == TRUE)
  {

    if(i_oSigPointA.nLonX != i_oSigPointB.nLonX)
    {
      return
         (
              (i_oSigPointA.nLonX <= i_oSigPointC.nLonX)
           && (i_oSigPointC.nLonX <= i_oSigPointB.nLonX)
         )
      || (
              (i_oSigPointA.nLonX >= i_oSigPointC.nLonX)
           && (i_oSigPointC.nLonX >= i_oSigPointB.nLonX)
         )
      ;
    }
    else
    {
      return
         (
              (i_oSigPointA.nLatY <= i_oSigPointC.nLatY)
           && (i_oSigPointC.nLatY <= i_oSigPointB.nLatY)
         )
      || (
              (i_oSigPointA.nLatY >= i_oSigPointC.nLatY)
           && (i_oSigPointC.nLatY >= i_oSigPointB.nLatY)
         )
      ;
    }
  }
  else
  {
    return FALSE;
  }
}


