// Sigcontainer.h: interface for the CSigcontainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGCONTAINER_H__7741A401_52EE_484F_B166_73D6DC298E9E__INCLUDED_)
#define AFX_SIGCONTAINER_H__7741A401_52EE_484F_B166_73D6DC298E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SigPolygon.h"
#include "Memory.h"

//#define SEGARRAY_SIZE (1<<16) // 128 Ko

#define MAX_LEVEL 16
#define USE_POLYGON

// ===

struct sCoordIO
{ double I[2]
; double O[3]
;}; // 40 bytes

//#define sCoord sSigPoint

///*
struct sCoord
{ double nLonX
; double nLatY
; double nAltZ
;}; // 24 bytes
//*/

// ===

class EXPSIGENGINE CSigContainer : public ClassUtils
{
  public:
    CSigContainer(const char* i_panStringName = "CSigContainer");
    virtual ~CSigContainer(void);
    
    // ENUM

    typedef enum eSigObjectType
    { eOBJTYP_ROOT = 0
    , eOBJTYP_BLOCK      //     DXF
    , eOBJTYP_POINT      // MIF DXF
    , eOBJTYP_LINE       // MIF DXF
    , eOBJTYP_POLYLINE   // MIF DXF
    , eOBJTYP_MULTIPLE   // MIF 
    , eOBJTYP_REGION     // MIF 
    , eOBJTYP_ARC        // MIF DXF
    , eOBJTYP_TEXT       // MIF DXF
/*
    , eOBJTYP_CIRCLE     //     DXF -> ELLIPSE
    , eOBJTYP_TRACE      //     DXF
    , eOBJTYP_SOLID      //     DXF
    , eOBJTYP_SHAPE      //     DXF
    , eOBJTYP_BLOCK      //     DXF
    , eOBJTYP_ENDBLK     //     DXF
    , eOBJTYP_ATTDEF     //     DXF
    , eOBJTYP_ATTRIB     //     DXF
    , eOBJTYP_SHAPE      //     DXF
    , eOBJTYP_VERTEX     //     DXF
    , eOBJTYP_SEQEND     //     DXF
    , eOBJTYP_3DFACE     //     DXF
    , eOBJTYP_VIEWPORT   //     DXF
    , eOBJTYP_DIMENSION  //     DXF
*/
    , eOBJTYP_RECTANGLE  // MIF 
    , eOBJTYP_ROUNDRECT  // MIF 
    , eOBJTYP_ELLIPSE    // MIF 
    , eOBJTYP_MULTIPOINT // MIF
    , eOBJTYP_COLLECTION // MIF
    , eOBJTYP__ANY // Pour la recherche de tous les objets
    , eOBJTYP__END
    } eSOT;

    typedef enum eSigColumnType
    { eCOLTYP_CHAR = 0
    , eCOLTYP_INTERGER
    , eCOLTYP_SMALLINT
    , eCOLTYP_DECIMAL
    , eCOLTYP_FLOAT
    , eCOLTYP_DATE
    , eCOLTYP_LOGICAL
    , eCOLTYP__END
    } eSCT;

    typedef enum eSigFileId
    { eSigFileId_OBJECTS = 0
    , eSigFileId_DATABASE
    , eSigFileId__END
    } eSFI;

    typedef enum eSigText
    { eSIGTXT_SPACING = 1<<0
    , eSIGTXT_JUSTIFY = 1<<1
    , eSIGTXT_ANGLE   = 1<<2
    , eSIGTXT_LABEL   = 1<<3
    , eSIGTXT_CENTER  = 1<<4
    } eSTEXT;

    // STRUCT

    typedef struct sSigSymbol
    { int      nType
    ; int      nShape
    ; COLORREF nColor
    ; int      nSize
    ; int      nFontOrFileNameIndex
    ; int      nFontOrCustomStyle
    ; double   nRotation
    ;} sSSYMBOL; // 32 bytes

    typedef struct sSigPen
    { int      nWidth
    ; int      nPattern
    ; COLORREF nColor
    ;} sSPEN; // 12 bytes

    typedef struct sSigBrush
    { int      nPattern
    ; COLORREF nForeColor
    ; COLORREF nBackColor
    ;} sSBRUSH; // 12 bytes

    typedef struct sSigFont
    { int      nFontNameIndex
    ; int      nStyle
    ; int      nSize
    ; COLORREF nForeColor
    ; COLORREF nBackColor
    ;} sSFONT; // 20 bytes

    typedef struct sSigSmooth
    { BOOL     bSmooth
    ;} sSSMOOTH; // 4 bytes

    typedef struct sSigText
    { int    nValid
    ; double nSpacing
    ; int    nJustify // PAS ENUM, CHAMPS DE BITS
    ; double nAngle
    ; int    nLabelLine
    ; double nX
    ; double nY
    ;} sSTEXT; // 44 bytes

    typedef struct sSigObject
    { eSigObjectType eObjectType // eSigObjectType
    ; int            nObjectName
    ; int            nObjectComment
    ; int            nObjectIndex
    ; int            nParentIndex
    ; int            nPointIndex
#ifndef USE_POLYGON
    ; int            nPointNumber
#else // USE_POLYGON
    ; CSigPolygon*   poPolygon // No embedded object, must create it on purpose
#endif // USE_POLYGON
    ; sCoord         sCornerTopLeft
    ; sCoord         sCornerBottomRight
    ; sCoord         sCenter

    ; int            nLayerName
    ; int            nRowDataIndex
    ; int            nTextIndex

    ; int            nIndexSymbol
    ; int            nIndexPen
    ; int            nIndexBrush
    ; int            nIndexFont
    ; int            nIndexSmooth
    ; int            nIndexText
    ;} sSOBJECT; // 104 bytes

    // Column
    typedef struct sSigColumn // Colonne
    { int nNameIndex;
    ; int nType
    ; int nSize
    ;} sSCOLUMN; // 12 bytes

    // Header
    typedef struct sSigProjection
    { int    nSyntax
    ; int    nTypeOrTableName
    ; int    nDatumOrWindowID
    ; char   anUnitName[8]
    ; double nOriginLon
    ; double nOriginLat
    ; double nStandartParallel1
    ; double nStandartParallel2
    ; double nAzimut
    ; double nScaleFactor
    ; double nFalseEasting
    ; double nFalseNorthing
    ; double nRange
    ;} sSPROJ; // 56 bytes

    typedef struct sSigAffine
    { char   anUnitName[8]
    ; double nXaxisScaleStretch
    ; double nXaxisRotatSkew
    ; double nXaxisShift
    ; double nYaxisScaleStretch
    ; double nYaxisRotatSkew
    ; double nYaxisShift
    ;} sSAFFINE; // 32 bytes

    typedef struct sSigBound
    { sCoord sMin
    ; sCoord sMax
    ;} sSBOUND; // 24 bytes

    typedef struct sSigTransform
    { sCoord sTransformMultiplier
    ; sCoord sTransformDisplacement
    ;} sSTRANS;

    typedef struct sSigHeader
    { short    nSignature
    ; short    nVersion
    ; int      nName
    ; int      nCharset
    ; sSPROJ   sProjection
    ; sSAFFINE sAffine
    ; sSBOUND  sBound
    ; sSTRANS  sTransform
    ;} sSHEAD; // 140 bytes

    // Member

    sSHEAD      m_sHeader;

    // Container


    void        ResetContainer(BOOL i_bCreation = FALSE);
    void        CreateRoot(void);
    void        PrepareColumnStorage(void);

    CSigContainer::sSigObject*
                AddObject(sSigObject* i_psSigObject = NULL, BOOL i_bBlockMode = FALSE);

    int         HierarchyDown(void);
    int         HierarchyUp(void);

    CSigContainer::sSigObject*
                GetFirstObject(eSigObjectType i_eType, int i_nIndexStart = 1, bool i_bAllChild = false);
    CSigContainer::sSigObject*
                GetNextObject (eSigObjectType i_eType, bool i_bAllChild = false);

    // Object
    void        ResetTempoObject(void);
    CSigContainer::sSigObject*
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                CreateObject(eSigObjectType i_eObjectType, int i_nPointNumber, const char* i_panStrObjectName = NULL, const char* i_panStrLayerName = NULL);
// MODIF_KOCH 070328

#ifndef USE_POLYGON
    int         AddPoint(sCoord*     i_psPoint);
#else // USE_POLYGON
    int         AddPoint(sSigPoint*  i_poPoint);
#endif // USE_POLYGON
    int         AddPoint(double      i_nPointLonX, double   i_nPointLatY, double   i_nPointAltZ = 0.0);
    int         AddPoint(const char* i_panLonX, const char* i_panLatY, const char* i_panAltZ = NULL);

#ifndef USE_POLYGON
    sCoord      GetCenter(void);
#else // USE_POLYGON
    sSigPoint   GetCenter(void);
#endif // USE_POLYGON
    int         GetObjectNumber(void);
    int         GetObjectSearch(void);

    //

    int         AddColumn(const sSigColumn& i_psSigColumn);
    int         AddColumn(const char* i_panColName, int i_nColType, int i_nColSize = 0);
    int         GetColumnCount(void);
    int         AddColumnString(const char* i_panString, int i_nColumnIndex);
    char*       GetColumnString(int i_nColumnIndex, sSigObject* i_psSigObjectFrom = NULL);
    char*       GetColumnString(int i_nColumnIndex, int i_nLineIndex);
    int         GetColumnIndex(const char* i_panString);
    sSigColumn* GetColumnPointer(int i_nColumnIndex);

// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
    int         AddLayer(const char* i_panStrLayerName);
    int         GetLayerCount(void);
    char*       GetLayerName(int i_nLayerIndex);
    int         GetLayerIndex(const char* i_panStrLayerName);
    bool        GetLayerStatus(int i_nLayerIndex);
    void        SetLayerStatus(int i_nLayerIndex, bool i_bVisible = true);
// MODIF_KOCH 070328

    int         AddString(const char* i_panString);
    char*       GetString(int i_nStringIndex);

#ifndef USE_POLYGON
    sCoord*     GetCoord(int i_nCoordIndex);
#else // USE_POLYGON
    sSigPoint&  GetCoord(int i_nCoordIndex);
#endif // USE_POLYGON

    int         SetObjectSymbol(const sSigSymbol& i_psSigSymbol);
    int         SetObjectPen   (const sSigPen&    i_psSigPen);
    int         SetObjectBrush (const sSigBrush&  i_psSigBrush);
    int         SetObjectFont  (const sSigFont&   i_psSigFont);
    int         SetObjectSmooth(const sSigSmooth& i_psSigSmooth);
    int         SetObjectText  (const sSigText&   i_psSigText);

    sSigSymbol* GetObjectSymbol(int i_nSigSymbol = (-1));
    sSigPen*    GetObjectPen   (int i_nSigPen    = (-1));
    sSigBrush*  GetObjectBrush (int i_nSigBrush  = (-1));
    sSigFont*   GetObjectFont  (int i_nSigFont   = (-1));
    sSigSmooth* GetObjectSmooth(int i_nSigSmooth = (-1));
    sSigText*   GetObjectText  (int i_nSigText   = (-1));

#ifdef USE_POLYGON
    int         CopyObjectsFrom(CSigContainer* i_poSigContainer, sCoord& i_rsCoordMin, sCoord& i_rsCoordMax, BOOL i_bClipObjects = FALSE);
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support de la rotation et homothétie d'un bloc
// DK 070328 (LWPOLYLINE) : Support des couches logiques
    int         CopyFromBlock(const char* i_panStrBlockName, double i_nShiftLonX = 0.0, double i_nShiftLatY = 0.0, double i_nShiftAltZ = 0.0, double i_nRotation = 0.0, double i_nScaleX = 0.0, double i_nScaleY = 0.0, double i_nScaleZ = 0.0, const char* i_panStrLayerName = NULL);
// MODIF_KOCH 070328

    void        Simplify(float i_nTolerance);
#endif // USE_POLYGON

    //

    void        SetClassName(const char* i_panStrName);

  protected:
    sSigObject          mp_sTempoObject;
    sSigObject*         mp_psSigObject;

    // SIG DATA
    CMemoryArray        mp_oasArrayObject; // sSigObject (104 bytes)
#ifndef USE_POLYGON
    CMemoryArray        mp_oasArrayPoints; // sCoord     (24 bytes)
#endif // USE_POLYGON
    CMemoryArray        mp_oasArrayColumn; // sSigColumn (12 bytes)

    CMemoryTreeRedBlack mp_oasArraySymbol; // sSigSymbol (32 bytes)
    CMemoryTreeRedBlack mp_oasArrayPen;    // sSigPen    (12 bytes)
    CMemoryTreeRedBlack mp_oasArrayBrush;  // sSigBrush  (12 bytes)
    CMemoryTreeRedBlack mp_oasArrayFont;   // sSigFont   (20 bytes)
    CMemoryTreeRedBlack mp_oasArraySmooth; // sSigSmooth ( 4 bytes)
    CMemoryTreeRedBlack mp_oasArrayText;   // sSigText   (44 bytes)

    CMemoryStringTree*  m_poTreeStringData;
    CMemoryArray        mp_oasArrayObjectData;
    int*                m_panTempoRowData;

    CMemoryStringTree   mp_asStringBuffer;
    CMemoryStringTree   mp_asStringBlock; // Block name
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
    CMemoryStringTree   mp_asStringLayer; // Layer name
// MODIF_KOCH 070328

    int                 mp_nObjectIndex;
    int                 mp_nPointIndex;

    int                 mp_anHierarchy[MAX_LEVEL];
    int                 mp_nHierarchyLevel;

    int                 mp_nObjectSearch;

    bool                mp_bFirstBoundHeader;
    bool                mp_bFirstBoundObject;
};

#endif // !defined(AFX_SIGCONTAINER_H__7741A401_52EE_484F_B166_73D6DC298E9E__INCLUDED_)
