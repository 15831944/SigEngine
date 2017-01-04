// SigPolygonPool.h: interface for the CSigPolygonPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGPOLYGONPOOL_H__F8BAC5FE_9130_472C_95DC_52F08504B17D__INCLUDED_)
#define AFX_SIGPOLYGONPOOL_H__F8BAC5FE_9130_472C_95DC_52F08504B17D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SigPoint.h"
#include "Memory.h"


class EXPSIGENGINE CSigPolygonPool : public ClassUtils
{
  public:
    struct sSigPolygon
    { int nStart
    ; int nIndex
    ; int nSize
    ; int nCache
    ;};

  private:
    struct sSigPolygonCache
    { tREAL     nArea
    ; sSigPoint sSigPointCentre
    ; int       nPointNumber
    ;};

  private:
    CMemoryArray mp_oasArraySigPolygon; // sSigPolygon
    CMemoryArray mp_oasArraySigCache;   // sSigPolygonCache
    CMemoryArray mp_oasArraySigPoint;   // sSigPoint (12(16)/24(32) bytes)

    sSigPoint    mp_sSigPoint;

  public:
    CSigPolygon               (const char* i_panStrName = "CSigPolygon");
    virtual ~CSigPolygon      ();

    virtual void SetClassName (const char* i_panStrName);

  public:
    int        ReservePolygon  (int i_nPointNumber); // Return a PolygonIndex
    BOOL       DeletePolygon   (int i_nPolygonIndex);

  public:
    BOOL       IsClosed        (int i_nPolygonIndex);
    void       Close           (int i_nPolygonIndex);

    int        GetSize         (int i_nPolygonIndex);
    int        SetSize         (int i_nPolygonIndex, int          i_nPointNumber);

    void       Add             (int i_nPolygonIndex, sSigPoint&   i_roSigPoint);
    int        SetAt           (int i_nPolygonIndex, int          i_nSigPointIndex, sSigPoint& i_roSigPoint);
    int        InsertAt        (int i_nPolygonIndex, int          i_nSigPointIndex, sSigPoint& i_roSigPoint);

    void       Delete          (int i_nPolygonIndex, int          i_nSigPointIndex);
    void       Trim            (int i_nPolygonIndex, int          i_nSigPointStart, int i_nSigPointEnd);
    void       RemoveAll       (int i_nPolygonIndex);

    BOOL       InSpan          (int i_nPolygonIndex, int          i_nSigPointStart, int i_nSigPointEnd, int i_nSigPointIndex);
    BOOL       InSpanProper    (int i_nPolygonIndex, int          i_nSigPointStart, int i_nSigPointEnd, int i_nSigPointIndex);

    BOOL       PointIn         (int i_nPolygonIndex, sSigPoint&   i_roSigPoint);
    int        PointSeparation (int i_nPolygonIndex, int          i_nSigPointStart, int i_nSigPointEnd);
    sSigPoint  GetClosestPoint (int i_nPolygonIndex, sSigPoint&   i_roSigPoint,     int *o_pnSigPointIndex = NULL);

    BOOL       Diagonal        (int i_nPolygonIndex, int          i_nSigPointStart, int i_nSigPointEnd);
    void       Translate       (int i_nPolygonIndex, sSigVector   i_oSigVector);
    void       Rationalise     (int i_nPolygonIndex, int          i_nAngle);
    tREAL      SegmentLength   (int i_nPolygonIndex, int          i_nSigPointStart, int i_nSigPointEnd);

    tREAL      Area            (int i_nPolygonIndex);
    sSigPoint  Centroid        (int i_nPolygonIndex, bool         i_bRefresh = false);
//    BOOL       GetAttributes   (int i_nPolygonIndex, tREAL*        o_pnArea, sSigPoint *o_poSigPointCentre, sSigPoint *o_poSigPointNormal, tREAL *o_pnSlope, tREAL *o_pnAspect);

    BOOL       Intersected     (int i_nPolygonIndex, sSigPoint&   i_roSigPointA, sSigPoint& i_roSigPointB);
    BOOL       IntersectedProp (int i_nPolygonIndex, sSigPoint&   i_roSigPointA, sSigPoint& i_roSigPointB);


    BOOL       Triangulate     (int i_nPolygonIndex, CSigPolygon* o_poSigPolygonTri);
    BOOL       TriangCenter    (int i_nPolygonIndex, CSigPolygon* o_poSigPolygonTri, sSigPoint& i_roSigPointCentre);
    BOOL       TriangDelauney  (int i_nPolygonIndex, CSigPolygon* o_poSigPolygonTri);

    void       NaturalSpline   (int i_nPolygonIndex, double*&     o_rpnSplineCoeffB, double*& o_rpnSplineCoeffC, double*& o_rpnSplineCoeffD);

    tREAL      Curvature       (int i_nPolygonIndex, int          i_nSigPointIndex);
    tREAL      Curvature       (int i_nPolygonIndex, int          i_nSigPointIndex, int i_nSampleSize);

    int        Simplify        (int i_nPolygonIndex, CSigPolygon* o_poSigPolygonSimple, float i_nTolerance);
    BOOL       Clipping        (int i_nPolygonIndex, CSigPolygon* o_poSigPolygonSimple, CSigPolygon& i_roSigPolygonSrc, int i_nClippingMode);

    sSigPoint& operator[]      (int i_nPolygonIndex, int          i_nSigPointIndex);
    sSigPoint& Point           (int i_nPolygonIndex, int          i_nSigPointIndex);
    void       operator=       (int i_nPolygonIndex, CSigPolygon& i_oSigPoint);

  private:
    BOOL       _Diagonalie     (int i_nPolygonIndex, int i, int j);

    BOOL       _InCone         (int i_nPolygonIndex, int          i_nSigPointStart, int i_nSigPointEnd);
    void       _SimplifyDP     (int i_nPolygonIndex, float        i_nTolerance, CSigPolygon* i_poSigPolyVertex, int i_nIndexStart, int i_nIndexEnd);

};

#endif // !defined(AFX_SIGPOLYGONPOOL_H__F8BAC5FE_9130_472C_95DC_52F08504B17D__INCLUDED_)
