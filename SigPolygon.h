// SigPolygon.h: interface for the CSigPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGPOLYGON_H__525276DC_88F6_45F7_B731_263D4EAFD486__INCLUDED_)
#define AFX_SIGPOLYGON_H__525276DC_88F6_45F7_B731_263D4EAFD486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SigPoint.h"
#include "Memory.h"

class EXPSIGENGINE CSigPolygon : public ClassUtils
{
  private:
    CMemoryArray mp_oasArraySigPoint; // sSigPoint (12/24 bytes)
    sSigPoint    mp_sSigPoint;

/*
	  int		     mp_nPointNumber;
	  int		     mp_nPointIndex;
	  sSigPoint* mp_paoSigPoint;
*/

	  tREAL      mp_nCacheArea;
	  sSigPoint  mp_sSigPointCacheCentre;
    int        mp_nCachePointNumber;

  public:
    CSigPolygon                (const char* i_panStrName = "CSigPolygon");
	  CSigPolygon                (int i_nSigPointNumber, const char* i_panStrName = "CSigPolygon");
    virtual ~CSigPolygon       ();

    virtual void SetClassName  (const char* i_panStrName);

  public:
    BOOL       IsClosed        (void);
    void       Close           (void);

    int        GetSize         (void);
    int        SetSize         (int          i_nPointNumber);

    void       Add             (sSigPoint&   i_roSigPoint);
    int        SetAt           (int          i_nSigPointIndex, sSigPoint& i_roSigPoint);
    int        InsertAt        (int          i_nSigPointIndex, sSigPoint& i_roSigPoint);

    void       Delete          (int          i_nSigPointIndex);
    void       Trim            (int          i_nSigPointStart, int i_nSigPointEnd);
    void       RemoveAll       (void);

    BOOL       InSpan          (int          i_nSigPointStart, int i_nSigPointEnd, int i_nSigPointIndex);
    BOOL       InSpanProper    (int          i_nSigPointStart, int i_nSigPointEnd, int i_nSigPointIndex);

    BOOL       PointIn         (sSigPoint&   i_roSigPoint);
    int        PointSeparation (int          i_nSigPointStart, int i_nSigPointEnd);
    sSigPoint  GetClosestPoint (sSigPoint&   i_roSigPoint,     int *o_pnSigPointIndex = NULL);

    BOOL       Diagonal        (int          i_nSigPointStart, int i_nSigPointEnd);
    void       Translate       (sSigVector   i_oSigVector);
    void       Rationalise     (int          i_nAngle);
    tREAL      SegmentLength   (int          i_nSigPointStart, int i_nSigPointEnd);

    tREAL      Area            (void);
    sSigPoint  Centroid        (bool         i_bRefresh = false);
//    BOOL       GetAttributes   (tREAL*        o_pnArea, sSigPoint *o_poSigPointCentre, sSigPoint *o_poSigPointNormal, tREAL *o_pnSlope, tREAL *o_pnAspect);

    BOOL       Intersected     (sSigPoint&   i_roSigPointA, sSigPoint& i_roSigPointB);
    BOOL       IntersectedProp (sSigPoint&   i_roSigPointA, sSigPoint& i_roSigPointB);


    BOOL       Triangulate     (CSigPolygon* o_poSigPolygonTri);
    BOOL       TriangCenter    (CSigPolygon* o_poSigPolygonTri, sSigPoint& i_roSigPointCentre);
    BOOL       TriangDelauney  (CSigPolygon* o_poSigPolygonTri);

    void       NaturalSpline   (double*&     o_rpnSplineCoeffB, double*& o_rpnSplineCoeffC, double*& o_rpnSplineCoeffD);

    tREAL      Curvature       (int          i_nSigPointIndex);
    tREAL      Curvature       (int          i_nSigPointIndex, int i_nSampleSize);

    int        Simplify        (CSigPolygon* o_poSigPolygonSimple, float i_nTolerance);
    BOOL       Clipping        (CSigPolygon* o_poSigPolygonSimple, CSigPolygon& i_roSigPolygonSrc, int i_nClippingMode);

    sSigPoint& operator[]      (int          i_nSigPointIndex);
    sSigPoint& Point           (int          i_nSigPointIndex);
    void       operator=       (CSigPolygon& i_oSigPoint);

  private:
    BOOL       _Diagonalie     (int i, int j);

    BOOL       _InCone         (int          i_nSigPointStart, int i_nSigPointEnd);
    void       _SimplifyDP     (float        i_nTolerance, CSigPolygon* i_poSigPolyVertex, int i_nIndexStart, int i_nIndexEnd);
};

#endif // !defined(AFX_SIGPOLYGON_H__525276DC_88F6_45F7_B731_263D4EAFD486__INCLUDED_)
