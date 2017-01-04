// SigPoint.h: interface for the sSigPoint struct.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGPOINT_H__F3D5D50A_4A89_4433_AB49_B190B989405F__INCLUDED_)
#define AFX_SIGPOINT_H__F3D5D50A_4A89_4433_AB49_B190B989405F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <float.h>

#define cDEG2RAD     0.01745329251994329576923 /*6888888889*/
#define cRAD2DEG     57.2957795130823208767982 /*16517724*/
#define cEPSILON     0.001
// MODIF_KOCH 070416
#define cPI          3.14159265358979323846264
// MODIF_KOCH 070416
#define cHALF_PI     1.57079632679489661923132
#define cTWO_PI      6.28318530717958647692528
#define cREAL_MAX    DBL_MAX

typedef double tREAL;

#define D2R(x)   (x)
#define F2R(x)   (x)
#define R2D(x)   (x)
#define R2F(x)   ((float) (x))

#define I2R(x) ((double) (x))
inline int R2I(double d0) { double d1 = d0 + 6755399441055744.0; return *(int*) &d1; }

/*
#define cDEG2RAD     0.0175f
#define cRAD2DEG     57.2957795f
#define cEPSILON     0.001f
#define cPI          3.14159265358979323846264f
#define cHALF_PI     1.57079632679489661923132f
#define cTWO_PI      6.28318530717958647692528f
#define cREAL_MAX    FLT_MAX

typedef float tREAL;

#define D2R(x)   ((float) (x))
#define F2R(x)   (x)
#define R2D(x)   (x)
#define R2F(x)   (x)

#define I2R(x) ((float) (x))
inline int R2I(float d0) { double d1 = d0 + 4503601774854144.0; return (*(int*) &d1) - 0x80000000; }
*/

#define ABSO(x) ((x) < D2R(0.0) ? -(x) : (x))
#define XOR(x,y) (!x^!y)

// STRUCT DEFINITION

#define sSigVector sSigPoint

struct EXPSIGENGINE sSigPoint
{ tREAL nLonX
; tREAL nLatY
; tREAL nAltZ
; union
  { struct
    { unsigned int bMark  : 1
    ; unsigned int bKeep  : 1
    ; unsigned int nStuff : 30
    ;} sFlag;
    unsigned int nFlat;
  } uFlag

;   sSigPoint                  ();
;   sSigPoint                  (double i_nLonX, double i_nLatY, double i_nAltZ = 0.0);

;   sSigPoint  operator-       (sSigPoint  i_sSigPoint)
;   sSigPoint  operator-       (void);
;   sSigPoint  operator-=      (sSigPoint  i_sSigPoint)

;   sSigPoint  operator+       (sSigPoint  i_sSigPoint)
;   sSigPoint  operator+=      (sSigPoint  i_sSigPoint)

;   tREAL      operator*       (sSigPoint  i_sSigPoint)
;   sSigPoint  operator*       (tREAL       i_nFactor)
;   sSigPoint  operator*=      (tREAL       i_nFactor)

;   sSigPoint  operator/       (tREAL       i_nFactor)
;   sSigPoint  operator/=      (tREAL       i_nFactor)

;   sSigPoint  operator^       (sSigPoint  i_sSigPoint)

;   sSigPoint  operator=       (sSigPoint  i_sSigPoint)
// MODIF_KOCH 070416
// DK 070416 (SIGPOINT) : Correction de la surcharge d'operateur
//;   sSigPoint  operator=       (sSigPoint& i_sSigPoint)
// MODIF_KOCH 070416

;   BOOL       operator==      (sSigPoint& i_roSigPoint)
;   BOOL       operator!=      (sSigPoint& i_roSigPoint)

;   tREAL      Dot             (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB)
;   sSigPoint  Cross           (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB)

;   tREAL      Length2         (void)
;   tREAL      Length          (void)

;   void       Scale           (tREAL i_nFactor)

;   void       Normalise       (void)
;   sSigVector Normal          (sSigPoint  i_oSigPointA, sSigPoint  i_oSigPointB, sSigPoint i_oSigPointC)

;   tREAL      Angle           (sSigPoint  i_oSigPointA, sSigPoint  i_oSigPointB, sSigPoint i_oSigPointC)
;   tREAL      Angle           (sSigVector i_oSigPointV, sSigVector i_oSigPointU)

;   tREAL      TriArea2        (sSigPoint  i_oSigPointA, sSigPoint  i_oSigPointB, sSigPoint i_oSigPointC)
;   tREAL      TriArea2        (sSigVector i_oSigPointU, sSigVector i_oSigPointV)

;   sSigPoint  GetClosestPoint (sSigPoint& start,        sSigPoint& end,          sSigPoint& i_sSigPoint)

;   BOOL       IntersectProp   (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB,  sSigPoint i_oSigPointC, sSigPoint i_oSigPointD)
;   BOOL       Intersect       (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB,  sSigPoint i_oSigPointC, sSigPoint i_oSigPointD)

;   BOOL       Left            (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB,  sSigPoint i_oSigPointC)
;   BOOL       LeftOn          (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB,  sSigPoint i_oSigPointC)

;   BOOL       Colinear        (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB,  sSigPoint i_oSigPointC)

;   BOOL       Between         (sSigPoint  i_oSigPointA, sSigPoint i_oSigPointB,  sSigPoint i_oSigPointC)

;}; // 12/24 bytes

#endif // !defined(AFX_SIGPOINT_H__F3D5D50A_4A89_4433_AB49_B190B989405F__INCLUDED_)
