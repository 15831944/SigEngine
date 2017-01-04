// Sigcontainer.cpp: implementation of the CSigcontainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SigContainer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE D'ENVIRONNEMENT =========================================================================================

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
CSigContainer::CSigContainer
( const char* i_panStringName
)
{
  m_poTreeStringData = NULL;
  m_panTempoRowData  = NULL;
  mp_psSigObject     = NULL;

#ifdef _DEBUG
  SetClassName(i_panStringName);
#endif // _DEBUG

  mp_oasArrayObject.CreateBuffer(sizeof(sSigObject), 1<<10); // Blocks of 1024 sSigObject
#ifndef USE_POLYGON
  mp_oasArrayPoints.CreateBuffer(sizeof(sCoord),     1<<14); // Blocks of 16384 sCoord
#endif // USE_POLYGON
  mp_oasArrayColumn.CreateBuffer(sizeof(sSigColumn),     8);

  mp_oasArraySymbol.CreateBuffer(sizeof(sSigSymbol),     4); // Blocks of 4 sSigSymbol
  mp_oasArrayPen.CreateBuffer   (sizeof(sSigPen),        4);
  mp_oasArrayBrush.CreateBuffer (sizeof(sSigBrush),      4);
  mp_oasArrayFont.CreateBuffer  (sizeof(sSigFont),       4);
  mp_oasArraySmooth.CreateBuffer(sizeof(sSigSmooth),     4);
  mp_oasArrayText.CreateBuffer  (sizeof(sSigText),       4);

  mp_oasArrayObjectData.CreateBuffer(sizeof(int), 1); // 1 ligne d'index pour commencer
  mp_asStringBuffer.CreateBuffer(1<<12); // Buffer de 4 Ko
  mp_asStringBlock.CreateBuffer(1<<12); // Buffer de 4 Ko

  ResetContainer(); // Initialise les variables

  CreateRoot();
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
void CSigContainer::SetClassName
( const char* i_panStrName
)
{
  mp_oStrObjectName = i_panStrName;

  mp_oasArrayObject.SetClassName(mp_oStrObjectName+"::mp_oasArrayObject");
#ifndef USE_POLYGON
  mp_oasArrayPoints.SetClassName(mp_oStrObjectName+"::mp_oasArrayPoints");
#endif // USE_POLYGON
  mp_oasArrayColumn.SetClassName(mp_oStrObjectName+"::mp_oasArrayColumn");

  mp_oasArraySymbol.SetClassName(mp_oStrObjectName+"::mp_oasArraySymbol");
  mp_oasArrayPen.SetClassName   (mp_oStrObjectName+"::mp_oasArrayPen");
  mp_oasArrayBrush.SetClassName (mp_oStrObjectName+"::mp_oasArrayBrush");
  mp_oasArrayFont.SetClassName  (mp_oStrObjectName+"::mp_oasArrayFont");
  mp_oasArraySmooth.SetClassName(mp_oStrObjectName+"::mp_oasArraySmooth");
  mp_oasArrayText.SetClassName  (mp_oStrObjectName+"::mp_oasArrayText");

  mp_asStringBuffer.SetClassName (mp_oStrObjectName+"::mp_asStringBuffer");
  mp_asStringBlock.SetClassName (mp_oStrObjectName+"::mp_asStringBlock");

  mp_oasArrayObjectData.SetClassName (mp_oStrObjectName+"::mp_oasArrayObjectData");
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
CSigContainer::~CSigContainer
(
)
{
#ifdef _DEBUG
  int l_nFree;
  int l_nSize;

  int l_nClmn = mp_oasArrayColumn.GetSlotTail();
  int l_nLoop;

  l_nFree
  = mp_oasArrayObject.GetBufferFree()
#ifndef USE_POLYGON
  + mp_oasArrayPoints.GetBufferFree()
#endif // USE_POLYGON
  + mp_oasArrayColumn.GetBufferFree()
  + mp_oasArraySymbol.GetBufferFree()
  + mp_oasArrayPen.GetBufferFree()
  + mp_oasArrayBrush.GetBufferFree()
  + mp_oasArrayFont.GetBufferFree()
  + mp_oasArraySmooth.GetBufferFree()
  + mp_oasArrayText.GetBufferFree()
  + mp_asStringBuffer.GetBufferFree()
  + mp_asStringBlock.GetBufferFree()
  ;

  l_nSize
  = mp_oasArrayObject.GetBufferSize()
#ifndef USE_POLYGON
  + mp_oasArrayPoints.GetBufferSize()
#endif // USE_POLYGON
  + mp_oasArrayColumn.GetBufferSize()
  + mp_oasArraySymbol.GetBufferSize()
  + mp_oasArrayPen.GetBufferSize()
  + mp_oasArrayBrush.GetBufferSize()
  + mp_oasArrayFont.GetBufferSize()
  + mp_oasArraySmooth.GetBufferSize()
  + mp_oasArrayText.GetBufferSize()
  + mp_asStringBuffer.GetBufferSize()
  + mp_asStringBlock.GetBufferSize()
  ;

  if(m_poTreeStringData != NULL)
  {
    for
    ( l_nLoop  = 0
    ; l_nLoop <  l_nClmn
    ; l_nLoop += 1
    )
    {
      l_nFree += m_poTreeStringData[l_nLoop].GetBufferFree();
      l_nSize += m_poTreeStringData[l_nLoop].GetBufferSize();
    }
  }
  else{}

  TRACE
  ( "%s::~CSigContainer : %d/%d (%d%%) unused byte%s left\n"
  , mp_oStrObjectName
  , l_nFree
  , l_nSize
  , (int) (((LONGLONG) l_nFree * 100) / l_nSize)
  , (l_nFree > 1) ? "s" : ""
  );
#endif // _DEBUG

  ResetContainer();
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
void CSigContainer::ResetContainer
( BOOL i_bCreation // = FALSE
)
{
  sSHEAD l_sHeader =
  { 'S'<<8|'C' // short    nSignature
  , 0x1<<8|0   // short    nVersion
  , (-1)       // int      nName
  , (-1)       // int      nCharset
  , { (-1)       // int    nSyntax : -1 = Lat/Lon
    , (-1)       // int    nTypeOrTableName
    , 0          // int    nDatumOrWindowID
    , ""         // char   anUnitName[8]
    , 0.0f       // float  nOriginLon
    , 0.0f       // float  nOriginLat
    , 0.0f       // float  nStandartParallel1
    , 0.0f       // float  nStandartParallel2
    , 0.0f       // float  nAzimut
    , 0.0f       // float  nScaleFactor
    , 0.0f       // float  nFalseEasting
    , 0.0f       // float  nFalseNorthing
    , 0.0f       // float  nRange
    }          // sSPROJ   sProjection
  , { ""         // char   anUnitName[8]
    , 0.0f       // float  nXaxisScaleStretch
    , 0.0f       // float  nXaxisRotatSkew
    , 0.0f       // float  nXaxisShift
    , 0.0f       // float  nYaxisScaleStretch
    , 0.0f       // float  nYaxisRotatSkew
    , 0.0f       // float  nYaxisShift
    }          // sSAFFINE sAffine
  , { { 0.0        // double nLonX
      , 0.0        // double nLatY
      , 0.0        // double nAltZ
      }          //sCoord sMin
    , { 0.0        // double nLonX
      , 0.0        // double nLatY
      , 0.0        // double nAltZ
      }          //sCoord sMax
    }          // sSBOUND  sBound
  , { { 0.0        // double nLonX
      , 0.0        // double nLatY
      , 0.0        // double nAltZ
      }          //sCoord sTransformMultiplier
    , { 0.0        // double nLonX
      , 0.0        // double nLatY
      , 0.0        // double nAltZ
      }          //sCoord sTransformDisplacement
    }          // sSTRANS  sTransform
  };

  m_sHeader = l_sHeader;

  //

  ResetTempoObject();

  //

#ifdef USE_POLYGON
  int l_nSize = mp_oasArrayObject.GetSlotTail();
  int l_nLoop;

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    mp_psSigObject = (sSigObject*) mp_oasArrayObject.GetSlotPointer(l_nLoop);

    if(mp_psSigObject->poPolygon != NULL)
    { // Efface chaque CSigPolygon de chaque objet
      delete mp_psSigObject->poPolygon;
      mp_psSigObject->poPolygon = NULL;
    }
    else{}
  }
#endif // USE_POLYGON

//  mp_psSigObject  = NULL;

  mp_oasArrayObject.RemoveSlotAll();
#ifndef USE_POLYGON
  mp_oasArrayPoints.RemoveSlotAll();
#endif // USE_POLYGON
  mp_oasArrayColumn.RemoveSlotAll();

  mp_oasArraySymbol.RemoveSlotAll();
  mp_oasArrayPen.RemoveSlotAll();
  mp_oasArrayBrush.RemoveSlotAll();
  mp_oasArrayFont.RemoveSlotAll();
  mp_oasArraySmooth.RemoveSlotAll();
  mp_oasArrayText.RemoveSlotAll();

  if(m_poTreeStringData != NULL) delete [] m_poTreeStringData;
  if(m_panTempoRowData  != NULL) delete [] m_panTempoRowData;

  mp_oasArrayObjectData.RemoveSlotAll();
  mp_asStringBuffer.RemoveStringAll();
  mp_asStringBlock.RemoveStringAll();

  mp_nObjectIndex = 0;
#ifndef USE_POLYGON
  mp_nPointIndex  = 0;
#endif // USE_POLYGON

  mp_nHierarchyLevel = 0;

  mp_bFirstBoundHeader = true;
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
void CSigContainer::CreateRoot
(
)
{
  CreateObject
  ( eOBJTYP_ROOT
  , 0 // Pas de point pour le Root
  );

  mp_nHierarchyLevel = 0; // On force le niveau 0

  // La hiérarchie, l'index et le parent avec le même index
  mp_anHierarchy[mp_nHierarchyLevel] = mp_nObjectIndex;

  mp_sTempoObject.nObjectIndex       = mp_nObjectIndex;
  mp_sTempoObject.nParentIndex       = mp_nObjectIndex;

  mp_oasArrayObject.AddSlotTail(&mp_sTempoObject); // Ajoute le Root

  // BUG PROBABLE, SI JAMAIS Y'A UN OS : AddSlotTail renvoir l'index de
  // l'objet dans l'Array, une foit ajouté (un Array ajoute TOUJOURS)
  // Normalement c'est ça qu'on doit utiliser plutôt que mp_nObjectIndex
  // qui 'devrait' être à 0. Parce qu'en mode debug, si jamais mp_nObjectIndex
  // est mal initialisé, ...

  mp_nObjectIndex += 1; // ATTENTION, le Root est TOUJOURS 0

  HierarchyDown();
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
void CSigContainer::PrepareColumnStorage
( void
)
{
  int         l_nLoop;
  int         l_nSize = mp_oasArrayColumn.GetSlotTail();
  CString     l_oStrTempo;
  sSigColumn* l_psSigColumn;

  if(m_poTreeStringData != NULL) delete [] m_poTreeStringData;
  if(m_panTempoRowData  != NULL) delete [] m_panTempoRowData;

  m_poTreeStringData = new CMemoryStringTree[l_nSize];
  m_panTempoRowData  = new int[l_nSize]; // Buffer temporaire

  mp_oasArrayObjectData.CreateBuffer(sizeof(int) * l_nSize, 1<<14); // 16384 lignes d'index

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigColumn = (sSigColumn*) mp_oasArrayColumn.GetSlotPointer(l_nLoop);

    l_oStrTempo.Format
    ( "%s::m_poTreeStringData[%d/%d](%s)"
    , mp_oStrObjectName
    , l_nLoop + 1 // +1, histoire de cohérence ((n-1)+1/n), hein...
    , l_nSize
    , mp_asStringBuffer.GetStringPointer(l_psSigColumn->nNameIndex)
    );

//    m_poTreeStringData[l_nLoop].SetClassName(mp_oStrObjectName+"::mp_asStringBuffer");
    m_poTreeStringData[l_nLoop].SetClassName(l_oStrTempo);
    m_poTreeStringData[l_nLoop].CreateBuffer(1<<16); // Buffer de 64 Ko
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
CSigContainer::sSigObject*
CSigContainer::AddObject
( sSigObject* i_psSigObject
, BOOL        i_bBlockMode // = FALSE
)
{
//  m_sHeader.sBound.sMin.nLonX = min(m_sHeader.sBound.sMin.nLonX, i_psSigObject->sCornerTopLeft.nLonX);
//  m_sHeader.sBound.sMax.nLonX = max(m_sHeader.sBound.sMax.nLonX, i_psSigObject->sCornerBottomRight.nLonX);
//  m_sHeader.sBound.sMax.nLatY = max(m_sHeader.sBound.sMax.nLatY, i_psSigObject->sCornerTopLeft.nLatY);
//  m_sHeader.sBound.sMin.nLatY = min(m_sHeader.sBound.sMin.nLatY, i_psSigObject->sCornerBottomRight.nLatY);

  if
  (
       (i_psSigObject->sCornerTopLeft.nLonX != 0.0)
    && (i_psSigObject->sCornerTopLeft.nLonX < m_sHeader.sBound.sMin.nLonX)
  )
  {
    m_sHeader.sBound.sMin.nLonX = i_psSigObject->sCornerTopLeft.nLonX;
  }
  else{}
  
  if
  (
       (i_psSigObject->sCornerBottomRight.nLonX != 0.0)
    && (i_psSigObject->sCornerBottomRight.nLonX > m_sHeader.sBound.sMax.nLonX)
  )
  {
    m_sHeader.sBound.sMax.nLonX = i_psSigObject->sCornerBottomRight.nLonX;
  }
  else{}
  
  if
  (
       (i_psSigObject->sCornerTopLeft.nLatY != 0.0)
    && (i_psSigObject->sCornerTopLeft.nLatY > m_sHeader.sBound.sMax.nLatY)
  )
  {
    m_sHeader.sBound.sMax.nLatY = i_psSigObject->sCornerTopLeft.nLatY;
  }
  else{}
  
  if
  (
       (i_psSigObject->sCornerBottomRight.nLatY != 0.0)
    && (i_psSigObject->sCornerBottomRight.nLatY < m_sHeader.sBound.sMin.nLatY)
  )
  {
    m_sHeader.sBound.sMin.nLatY = i_psSigObject->sCornerBottomRight.nLatY;
  }
  else{}

  //

  mp_nObjectIndex = mp_oasArrayObject.AddSlotTail(i_psSigObject); // &mp_sTempoObject);
  mp_psSigObject  = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectIndex);

  mp_anHierarchy[mp_nHierarchyLevel] = mp_nObjectIndex;

  mp_psSigObject->nObjectIndex       = mp_nObjectIndex;

/*
#ifdef _DEBUG
  CString l_oStrTempo;
  CString l_oStrType;

  switch(mp_psSigObject->eObjectType)
  {
    case eOBJTYP_ROOT :
      l_oStrType = "eOBJTYP_ROOT";
      break;
    case eOBJTYP_BLOCK :
      l_oStrType = "eOBJTYP_BLOCK";
      break;
    case eOBJTYP_POINT :
      l_oStrType = "eOBJTYP_POINT";
      break;
    case eOBJTYP_LINE :
      l_oStrType = "eOBJTYP_LINE";
      break;
    case eOBJTYP_POLYLINE :
      l_oStrType = "eOBJTYP_POLYLINE";
      break;
    case eOBJTYP_MULTIPLE :
      l_oStrType = "eOBJTYP_MULTIPLE";
      break;
    case eOBJTYP_REGION :
      l_oStrType = "eOBJTYP_REGION";
      break;
    case eOBJTYP_ARC :
      l_oStrType = "eOBJTYP_ARC";
      break;
    case eOBJTYP_TEXT :
      l_oStrType = "eOBJTYP_TEXT";
      break;
    case eOBJTYP_RECTANGLE :
      l_oStrType = "eOBJTYP_RECTANGLE";
      break;
    case eOBJTYP_ROUNDRECT :
      l_oStrType = "eOBJTYP_ROUNDRECT";
      break;
    case eOBJTYP_ELLIPSE :
      l_oStrType = "eOBJTYP_ELLIPSE";
      break;
    case eOBJTYP_MULTIPOINT :
      l_oStrType = "eOBJTYP_MULTIPOINT";
      break;
    case eOBJTYP_COLLECTION :
      l_oStrType = "eOBJTYP_COLLECTION";
      break;
    case eOBJTYP__ANY :
      l_oStrType = "eOBJTYP__ANY";
      break;
    case eOBJTYP__END :
      l_oStrType = "eOBJTYP__END";
      break;
    default :
      l_oStrType = "??UNKNOW??";
      break;
  }

  l_oStrTempo.Format
  ( "%s::mp_oasArrayObject(%d->%s)->poPolygon(%d)"
  , mp_oStrObjectName
  , mp_nObjectIndex
  , l_oStrType
  , mp_psSigObject->poPolygon->GetSize()
  );

  mp_psSigObject->poPolygon->SetClassName(l_oStrTempo);
#endif // _DEBUG
*/

  if(i_bBlockMode == FALSE)
  {
    mp_psSigObject->nParentIndex     = mp_anHierarchy[mp_nHierarchyLevel - 1]; // Le parent
  }
  else
  {
    mp_psSigObject->nParentIndex     = -1; // <--- BLOCK !!!

    if(mp_psSigObject->nObjectName != -1)
    { // Enregistre comme étant un Block
      mp_asStringBlock.SetStringData
      ( mp_asStringBlock.AddString(GetString(mp_psSigObject->nObjectName))
      , mp_nObjectIndex // mp_psSigObject->nObjectIndex // i_psSigObject->nObjectIndex
      );
    }
  }

  //

  return mp_psSigObject;
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
int CSigContainer::HierarchyDown
(
)
{
  if(mp_nHierarchyLevel < (MAX_LEVEL - 2))
  {
    mp_nHierarchyLevel += 1;
  }
  else{}

  return mp_nHierarchyLevel;
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
int CSigContainer::HierarchyUp
(
)
{
  if(mp_nHierarchyLevel > 1)
  {
    mp_nHierarchyLevel -= 1;
  }
  else{}

  // Restore pointer on previous Parent (eg. for Attributes storing)
  mp_psSigObject = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_anHierarchy[mp_nHierarchyLevel]);

  return mp_nHierarchyLevel;
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
CSigContainer::sSigObject*
CSigContainer::GetFirstObject
( eSigObjectType i_eType
, int            i_nIndexStart // = 1
, bool           i_bAllChild   // = false
)
{
  if(i_nIndexStart < 0)
  {
    mp_nObjectSearch = 0;
  }
  else
  {
/*
    if(i_nIndexStart >= mp_oasArrayObject.GetSlotTail())
    {
      mp_nObjectSearch = mp_oasArrayObject.GetSlotTail() - 1;
    }
    else
*/
    {
      mp_nObjectSearch = i_nIndexStart;
    }
  }

  return GetNextObject(i_eType, i_bAllChild);
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
CSigContainer::sSigObject*
CSigContainer::GetNextObject
( eSigObjectType i_eType
, bool           i_bAllChild // = false
)
{
  sSigObject* l_poSearch;
  int         l_nIndexMax;

  //

  l_poSearch  = NULL;
  l_nIndexMax = mp_oasArrayObject.GetSlotTail();

//  if(m_bStop == FALSE)
  {
    if(mp_nObjectSearch < l_nIndexMax)
    {
      do
      {
        l_poSearch = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch);

        mp_nObjectSearch += 1;

        if((mp_nObjectSearch % 1000) == 0)
        { // Release message pressure every 1000 lines
          PeekAndPump();
        }
        else{}
      }
      while
      (
           (l_poSearch != NULL)
        && (i_eType < eOBJTYP__ANY)
        && (mp_nObjectSearch < l_nIndexMax)
        && (
                (l_poSearch->eObjectType != i_eType)
             || ( // If right Type not relatives to Root
                     (i_bAllChild              == false)
                  && (l_poSearch->nParentIndex != 0)
                )
             || (l_poSearch->nParentIndex < 0) // BLOCK !!!
           )
/*
        && ( // Only relatives to Root (avoid Region/Polyline collision)
                 (l_poSearch->nParentIndex == 0)
             || ((l_poSearch->nParentIndex != 0) == i_bAllChild)
           )
*/
      );
    }
    else{}

    if
    (
         (l_poSearch != NULL)
      && (
              (i_eType == l_poSearch->eObjectType)
           || (i_eType == eOBJTYP__ANY)
         )
      && ( // Only relatives to Root (avoid Region/Polyline collision)
               (l_poSearch->nParentIndex == 0)
           || ((l_poSearch->nParentIndex >  0) == i_bAllChild)
         )
    )
    {
      return l_poSearch;
    }
    else
    {
      return NULL;
    }
  }
//  else
  {
    return NULL;
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
void CSigContainer::ResetTempoObject
(
)
{
  sSigObject l_sObject =
  { eOBJTYP_ROOT // eSigObjectType eObjectType
  , -1           // int            nObjectName
  , -1           // int            nObjectComment
  , 0            // int            nObjectIndex
  , 0            // int            nParentIndex
  , 0            // int            nPointIndex
#ifndef USE_POLYGON
  , 0            // int            nPointNumber
#else // USE_POLYGON
  , NULL         // CSigPolygon*   poPolygon
#endif // USE_POLYGON
  , { 0.0        // double nLonX
    , 0.0        // double nLatY
    , 0.0        // double nAltZ
    }          // sCoord         sCornerTopLeft
  , { 0.0        // double nLonX
    , 0.0        // double nLatY
    , 0.0        // double nAltZ
    }          // sCoord         sCornerBottomRight
  , { 0.0        // double nLonX
    , 0.0        // double nLatY
    , 0.0        // double nAltZ
    }          // sCoord         sCenter
  , -1           // int            nLayerName
  , -1           // int            nRowDataIndex
  , -1           // int            nTextIndex
  , -1           // int            nIndexSymbol
  , -1           // int            nIndexPen
  , -1           // int            nIndexBrush
  , -1           // int            nIndexFont
  , -1           // int            nIndexSmooth
  , -1           // int            nIndexText
  };

  mp_sTempoObject = l_sObject;

  //

  mp_nPointIndex = 0;

  mp_bFirstBoundObject = true;
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
CSigContainer::sSigObject*
CSigContainer::CreateObject
( eSigObjectType i_eObjectType
, int            i_nPointNumber
, const char*    i_panStrObjectName // = NULL
)
{
  ResetTempoObject();

  //

  mp_sTempoObject.eObjectType   = i_eObjectType;
#ifndef USE_POLYGON
  mp_sTempoObject.nPointIndex   = mp_oasArrayPoints.GetSlotTail();
  mp_sTempoObject.nPointNumber  = i_nPointNumber;
#else // USE_POLYGON
  mp_sTempoObject.nPointIndex   = 0;
//  if(mp_sTempoObject.poPolygon != NULL) delete mp_sTempoObject.poPolygon;

#ifdef _DEBUG
  CString l_oStrTempo;
  CString l_oStrType;

  switch(i_eObjectType)
  {
    case eOBJTYP_ROOT :
      l_oStrType = "eOBJTYP_ROOT";
      break;
    case eOBJTYP_BLOCK :
      l_oStrType = "eOBJTYP_BLOCK";
      break;
    case eOBJTYP_POINT :
      l_oStrType = "eOBJTYP_POINT";
      break;
    case eOBJTYP_LINE :
      l_oStrType = "eOBJTYP_LINE";
      break;
    case eOBJTYP_POLYLINE :
      l_oStrType = "eOBJTYP_POLYLINE";
      break;
    case eOBJTYP_MULTIPLE :
      l_oStrType = "eOBJTYP_MULTIPLE";
      break;
    case eOBJTYP_REGION :
      l_oStrType = "eOBJTYP_REGION";
      break;
    case eOBJTYP_ARC :
      l_oStrType = "eOBJTYP_ARC";
      break;
    case eOBJTYP_TEXT :
      l_oStrType = "eOBJTYP_TEXT";
      break;
    case eOBJTYP_RECTANGLE :
      l_oStrType = "eOBJTYP_RECTANGLE";
      break;
    case eOBJTYP_ROUNDRECT :
      l_oStrType = "eOBJTYP_ROUNDRECT";
      break;
    case eOBJTYP_ELLIPSE :
      l_oStrType = "eOBJTYP_ELLIPSE";
      break;
    case eOBJTYP_MULTIPOINT :
      l_oStrType = "eOBJTYP_MULTIPOINT";
      break;
    case eOBJTYP_COLLECTION :
      l_oStrType = "eOBJTYP_COLLECTION";
      break;
    case eOBJTYP__ANY :
      l_oStrType = "eOBJTYP__ANY";
      break;
    case eOBJTYP__END :
      l_oStrType = "eOBJTYP__END";
      break;
    default :
      l_oStrType = "??UNKNOW??";
      break;
  }

  l_oStrTempo.Format
  ( "%s::mp_oasArrayObject(%s)->poPolygon(%d)"
  , mp_oStrObjectName
  , l_oStrType
  , i_nPointNumber
  );

  mp_sTempoObject.poPolygon     = new CSigPolygon(i_nPointNumber, l_oStrTempo);
#else
  mp_sTempoObject.poPolygon     = new CSigPolygon(i_nPointNumber);
#endif // _DEBUG

//  mp_sTempoObject.poPolygon->SetSize(i_nPointNumber);
#endif // USE_POLYGON

  if(i_panStrObjectName != NULL)
  {
    mp_sTempoObject.nObjectName = AddString(i_panStrObjectName);
  }
  else{}

  return (sSigObject*) &mp_sTempoObject;
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
int CSigContainer::AddPoint
#ifndef USE_POLYGON
( sCoord* i_psPoint
)
{
//  if(mp_nPointIndex < (mp_sTempoObject.nPointNumber - 2))
  if(mp_nPointIndex < mp_sTempoObject.nPointNumber)
  {
    mp_nPointIndex = mp_oasArrayPoints.AddSlotTail(i_psPoint);

//    mp_nPointIndex += 1; // Garde une certaine cohérence dans la suite des points

    // BUG PROBABLE : Si on essaye d'insérer des points d'un autre objet, ils
    // vont sans doute s'intercaler avec ceux du précédent objet. Pas d'entrelacement
    // possible...

    if(mp_bFirstBoundObject == false)
    {
      if(mp_sTempoObject.sCornerTopLeft.nLonX > i_psPoint->nLonX)
      {
        mp_sTempoObject.sCornerTopLeft.nLonX = i_psPoint->nLonX;
      }
      else{}

      if(mp_sTempoObject.sCornerTopLeft.nLatY < i_psPoint->nLatY)
      {
        mp_sTempoObject.sCornerTopLeft.nLatY     = i_psPoint->nLatY;
      }
      else{}

      if(mp_sTempoObject.sCornerBottomRight.nLonX < i_psPoint->nLonX)
      {
        mp_sTempoObject.sCornerBottomRight.nLonX = i_psPoint->nLonX;
      }
      else{}

      if(mp_sTempoObject.sCornerBottomRight.nLatY > i_psPoint->nLatY)
      {
        mp_sTempoObject.sCornerBottomRight.nLatY = i_psPoint->nLatY;
      }
      else{}
    }
    else
    { // Première fois
      mp_sTempoObject.sCornerTopLeft.nLonX     = i_psPoint->nLonX;
      mp_sTempoObject.sCornerTopLeft.nLatY     = i_psPoint->nLatY;
      mp_sTempoObject.sCornerBottomRight.nLonX = i_psPoint->nLonX;
      mp_sTempoObject.sCornerBottomRight.nLatY = i_psPoint->nLatY;

      mp_bFirstBoundObject = false;
    }
    
    if(mp_bFirstBoundHeader == false)
    {
      if(m_sHeader.sBound.sMin.nLonX > i_psPoint->nLonX)
      {
        m_sHeader.sBound.sMin.nLonX = i_psPoint->nLonX;
      }
      else{}

      if(m_sHeader.sBound.sMin.nLatY > i_psPoint->nLatY)
      {
        m_sHeader.sBound.sMin.nLatY = i_psPoint->nLatY;
      }
      else{}

      if(m_sHeader.sBound.sMax.nLonX < i_psPoint->nLonX)
      {
        m_sHeader.sBound.sMax.nLonX = i_psPoint->nLonX;
      }
      else{}

      if(m_sHeader.sBound.sMax.nLatY < i_psPoint->nLatY)
      {
        m_sHeader.sBound.sMax.nLatY = i_psPoint->nLatY;
      }
      else{}
    }
    else
    { // Première fois
      m_sHeader.sBound.sMin.nLonX = i_psPoint->nLonX;
      m_sHeader.sBound.sMin.nLatY = i_psPoint->nLatY;
      m_sHeader.sBound.sMax.nLonX = i_psPoint->nLonX;
      m_sHeader.sBound.sMax.nLatY = i_psPoint->nLatY;

      mp_bFirstBoundHeader = false;
    }
  }
  else{}

  return mp_nPointIndex;
}
#else // USE_POLYGON
( sSigPoint* i_poPoint
)
{
  if(i_poPoint != NULL)
  {
    mp_psSigObject->poPolygon->Add(*i_poPoint);

    mp_psSigObject->nPointIndex += 1; // Garde une certaine cohérence dans la suite des points

    if(mp_bFirstBoundObject == false)
    {
      if(mp_sTempoObject.sCornerTopLeft.nLonX > i_poPoint->nLonX)
      {
        mp_sTempoObject.sCornerTopLeft.nLonX = i_poPoint->nLonX;
      }
      else{}

      if(mp_sTempoObject.sCornerTopLeft.nLatY < i_poPoint->nLatY)
      {
        mp_sTempoObject.sCornerTopLeft.nLatY     = i_poPoint->nLatY;
      }
      else{}

      if(mp_sTempoObject.sCornerBottomRight.nLonX < i_poPoint->nLonX)
      {
        mp_sTempoObject.sCornerBottomRight.nLonX = i_poPoint->nLonX;
      }
      else{}

      if(mp_sTempoObject.sCornerBottomRight.nLatY > i_poPoint->nLatY)
      {
        mp_sTempoObject.sCornerBottomRight.nLatY = i_poPoint->nLatY;
      }
      else{}
    }
    else
    { // Première fois
      mp_sTempoObject.sCornerTopLeft.nLonX     = i_poPoint->nLonX;
      mp_sTempoObject.sCornerTopLeft.nLatY     = i_poPoint->nLatY;
      mp_sTempoObject.sCornerBottomRight.nLonX = i_poPoint->nLonX;
      mp_sTempoObject.sCornerBottomRight.nLatY = i_poPoint->nLatY;

      mp_bFirstBoundObject = false;
    }
  
    if(mp_bFirstBoundHeader == false)
    {
      if(m_sHeader.sBound.sMin.nLonX > i_poPoint->nLonX)
      {
        m_sHeader.sBound.sMin.nLonX = i_poPoint->nLonX;
      }
      else{}

      if(m_sHeader.sBound.sMin.nLatY > i_poPoint->nLatY)
      {
        m_sHeader.sBound.sMin.nLatY = i_poPoint->nLatY;
      }
      else{}

      if(m_sHeader.sBound.sMax.nLonX < i_poPoint->nLonX)
      {
        m_sHeader.sBound.sMax.nLonX = i_poPoint->nLonX;
      }
      else{}

      if(m_sHeader.sBound.sMax.nLatY < i_poPoint->nLatY)
      {
        m_sHeader.sBound.sMax.nLatY = i_poPoint->nLatY;
      }
      else{}
    }
    else
    { // Première fois
      m_sHeader.sBound.sMin.nLonX = i_poPoint->nLonX;
      m_sHeader.sBound.sMin.nLatY = i_poPoint->nLatY;
      m_sHeader.sBound.sMax.nLonX = i_poPoint->nLonX;
      m_sHeader.sBound.sMax.nLatY = i_poPoint->nLatY;

      mp_bFirstBoundHeader = false;
    }

    return mp_nPointIndex;
  }
  else
  {
    return -1;
  }
}
#endif // USE_POLYGON

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
int CSigContainer::AddPoint
( double i_nPointLonX
, double i_nPointLatY
, double i_nPointAltZ // = 0.0
)
{
#ifndef USE_POLYGON
  sCoord l_sCoord;

  l_sCoord.nLonX = i_nPointLonX;
  l_sCoord.nLatY = i_nPointLatY;
  l_sCoord.nAltZ = i_nPointAltZ;

  return AddPoint(&l_sCoord);
#else // USE_POLYGON
  sSigPoint l_oCoord
  ( i_nPointLonX
  , i_nPointLatY
  , i_nPointAltZ
  );

  return AddPoint(&l_oCoord);
#endif // USE_POLYGON
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
int CSigContainer::AddPoint
( const char* i_panLonX
, const char* i_panLatY
, const char* i_panAltZ // = NULL
)
{
#ifndef USE_POLYGON
  sCoord l_sCoord;

  //

  l_sCoord.nLonX = ATOD(i_panLonX);
  l_sCoord.nLatY = ATOD(i_panLatY);
  l_sCoord.nAltZ = ATOD(i_panAltZ);
  
  return AddPoint(&l_sCoord);
#else // USE_POLYGON
  sSigPoint l_oCoord
  ( ATOD(i_panLonX)
  , ATOD(i_panLatY)
  , ATOD(i_panAltZ)
  );

  return AddPoint(&l_oCoord);
#endif // USE_POLYGON
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
#ifndef USE_POLYGON
sCoord CSigContainer::GetCenter
(
)
{
  sCoord l_sCenter;

  l_sCenter.nLonX
  = m_sHeader.sBound.sMin.nLonX
  + (
        (m_sHeader.sBound.sMax.nLonX - m_sHeader.sBound.sMin.nLonX)
      / 2.0
    )
  ;
  
  l_sCenter.nLatY
  = m_sHeader.sBound.sMin.nLatY
  + (
        (m_sHeader.sBound.sMax.nLatY - m_sHeader.sBound.sMin.nLatY)
      / 2.0
    )
  ;

  return l_sCenter;
}
#else // USE_POLYGON
sSigPoint CSigContainer::GetCenter
(
)
{
  sSigPoint l_oCenter
  ( m_sHeader.sBound.sMin.nLonX
  + (
        (m_sHeader.sBound.sMax.nLonX - m_sHeader.sBound.sMin.nLonX)
      / 2.0
    )
  , m_sHeader.sBound.sMin.nLatY
  + (
        (m_sHeader.sBound.sMax.nLatY - m_sHeader.sBound.sMin.nLatY)
      / 2.0
    )
  , 0.0
  );

  return l_oCenter;
}
#endif // USE_POLYGON

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
int CSigContainer::GetObjectNumber
( void
)
{
  return mp_oasArrayObject.GetSlotTail();
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
int CSigContainer::GetObjectSearch
( void
)
{
  return mp_nObjectSearch;
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
int CSigContainer::AddColumn
( const sSigColumn& i_psSigColumn
)
{
  return mp_oasArrayColumn.AddSlotTail((void*) &i_psSigColumn);
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
int CSigContainer::AddColumn
( const char* i_panColName
, int         i_nColType
, int         i_nColSize // = 0
)
{
  if
  (
       (i_panColName != NULL)
    && (i_nColType >= eCOLTYP_CHAR)
    && (i_nColType <  eCOLTYP__END)
  )
  {
    sSigColumn l_sTempoColumn;

    l_sTempoColumn.nNameIndex = AddString(i_panColName);
    l_sTempoColumn.nType      = i_nColType;

    switch(i_nColType)
    {
      case eCOLTYP_INTERGER :
        l_sTempoColumn.nSize = sizeof(int);
        break;
      case eCOLTYP_SMALLINT :
        l_sTempoColumn.nSize = sizeof(short);
        break;
      case eCOLTYP_FLOAT :
        l_sTempoColumn.nSize = sizeof(float);
        break;
      case eCOLTYP_DATE :
        l_sTempoColumn.nSize = 6;
        break;
      case eCOLTYP_LOGICAL :
        l_sTempoColumn.nSize = 1;
        break;
      case eCOLTYP_CHAR :
      case eCOLTYP_DECIMAL :
      default :
        l_sTempoColumn.nSize = i_nColSize;
    }

    return mp_oasArrayColumn.AddSlotTail((void*) &l_sTempoColumn);
  }
  else
  {
    return (-1);
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
int CSigContainer::GetColumnCount
( void
)
{
  return mp_oasArrayColumn.GetSlotTail();
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
int CSigContainer::AddColumnString
( const char* i_panString
, int         i_nColumnIndex
)
{
#ifdef _DEBUG
  if
  (
       (i_panString[ 0] == 'R')
    && (i_panString[ 1] == 'O')
    && (i_panString[ 2] == 'U')
    && (i_panString[ 3] == 'F')
    && (i_panString[ 4] == 'F')
    && (i_panString[ 5] == 'I')
    && (i_panString[ 6] == 'G')
    && (i_panString[ 7] == 'N')
    && (i_panString[ 8] == 'A')
    && (i_panString[ 9] == 'C')
    && (i_panString[10] == '-')
    && (i_panString[11] == 'S')
  )
  { // Mettre un point d'arret ici pour vérifier l'insertion de "ROUFFIGNAC-"
    i_panString = i_panString;
  }
#endif // _DEBUG

  if(mp_sTempoObject.nRowDataIndex == -1)
  { // Si une ligne n'a pas encore étée réservée
    mp_sTempoObject.nRowDataIndex = mp_oasArrayObjectData.AddSlotTail(NULL); // Ne copie rien
  }
  else{}

  // Pointeur sur le tableau d'index des chaines
  int* l_panRowData = (int*) mp_oasArrayObjectData.GetSlotPointer(mp_sTempoObject.nRowDataIndex);

  // On récupère l'index de la chaine insérée dans le bon tableau (faut suivre, je vous l'accorde)
  l_panRowData[i_nColumnIndex] = m_poTreeStringData[i_nColumnIndex].AddString((char*) i_panString);

  // Et on renvoie l'index du tableau de chaines
  return mp_sTempoObject.nRowDataIndex;
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
char* CSigContainer::GetColumnString
( int         i_nColumnIndex
, sSigObject* i_psSigObjectFrom // = NULL
)
{
  int* l_panSigRowData = NULL;

  if(i_psSigObjectFrom == NULL)
  { // Si pas d'objet spécifié, on suppose que c'est l'objet en cours de recherche
    i_psSigObjectFrom = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch - 1);
  }
  else{}

  // Pointeur sur le tableau d'index des chaines
  l_panSigRowData = (int*) mp_oasArrayObjectData.GetSlotPointer(i_psSigObjectFrom->nRowDataIndex);

  // On récupère le pointeur sur la chaine de caractère dans la bonne colonne
  if
  (
       (i_nColumnIndex  >= 0)
    && (l_panSigRowData != NULL)
  )
  {
    return m_poTreeStringData[i_nColumnIndex].GetStringPointer(l_panSigRowData[i_nColumnIndex]);
  }
  else
  {
    return NULL;
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
char* CSigContainer::GetColumnString
( int i_nColumnIndex
, int i_nLineIndex
)
{
  if
  (
       (i_nColumnIndex <  mp_oasArrayColumn.GetSlotTail())
    && (m_poTreeStringData[i_nColumnIndex].GetStringPointer(i_nLineIndex) != NULL)
  )
  {
    return m_poTreeStringData[i_nColumnIndex].GetStringPointer(i_nLineIndex);
  }
  else
  {
    return NULL;
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
int CSigContainer::GetColumnIndex
( const char* i_panString
)
{
  int         l_nCode = -1;
  int         l_nLoop = 0;
  int         l_nSize = mp_oasArrayColumn.GetSlotTail();
  sSigColumn* l_psSigColumn = NULL;

  for
  ( l_nLoop  = 0
  ; l_nLoop <  l_nSize
  ; l_nLoop += 1
  )
  {
    l_psSigColumn = (sSigColumn*) mp_oasArrayColumn.GetSlotPointer(l_nLoop);

    if
    (
         (l_psSigColumn != NULL)
      && (stricmp(i_panString, GetString(l_psSigColumn->nNameIndex)) == 0)
    )
    { // Si c'est la bonne colonne
//      return l_nLoop;
      l_nCode = l_nLoop;
      break; 
    }
    else{}
  }

  return l_nCode;
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
CSigContainer::sSigColumn* CSigContainer::GetColumnPointer
( int i_nColumnIndex
)
{
  return (sSigColumn*) mp_oasArrayColumn.GetSlotPointer(i_nColumnIndex);
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
int CSigContainer::AddString
( const char* i_panString
)
{ // Ajoute une chaine au buffer 'global'
  return mp_asStringBuffer.AddString((char*) i_panString);
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
char* CSigContainer::GetString
( int i_nStringIndex
)
{ // Récupère une chaine du buffer 'global'
  return mp_asStringBuffer[i_nStringIndex];
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
#ifndef USE_POLYGON
sCoord* CSigContainer::GetCoord
( int i_nCoordIndex
)
{
  return (sCoord*) mp_oasArrayPoints[i_nCoordIndex];
}
#else // USE_POLYGON
sSigPoint& CSigContainer::GetCoord
( int i_nCoordIndex
)
{
  return mp_psSigObject->poPolygon->Point(i_nCoordIndex);
}
#endif // USE_POLYGON

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
int CSigContainer::SetObjectSymbol
( const sSigSymbol& i_psSigSymbol
)
{
  if(mp_psSigObject->nIndexSymbol < 0)
  { // Ajoute
    mp_psSigObject->nIndexSymbol = mp_oasArraySymbol.AddNodeCRC((void*) &i_psSigSymbol);
  }
  else
  { // Remplace
    mp_oasArraySymbol.SetSlotBuffer((void*) &i_psSigSymbol, mp_psSigObject->nIndexSymbol);
  }

  return mp_psSigObject->nIndexSymbol;
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
int CSigContainer::SetObjectPen
( const sSigPen& i_psSigPen
)
{
  if(mp_psSigObject->nIndexPen < 0)
  { // Ajoute
    mp_psSigObject->nIndexPen = mp_oasArrayPen.AddNodeCRC((void*) &i_psSigPen);
  }
  else
  { // Remplace
    mp_oasArrayPen.SetSlotBuffer((void*) &i_psSigPen, mp_psSigObject->nIndexPen);
  }

  return mp_psSigObject->nIndexPen;
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
int CSigContainer::SetObjectBrush
( const sSigBrush& i_psSigBrush
)
{
  if(mp_psSigObject->nIndexBrush < 0)
  { // Ajoute
    mp_psSigObject->nIndexBrush = mp_oasArrayBrush.AddNodeCRC((void*) &i_psSigBrush);
  }
  else
  { // Remplace
    mp_oasArrayBrush.SetSlotBuffer((void*) &i_psSigBrush, mp_psSigObject->nIndexBrush);
  }

  return mp_psSigObject->nIndexBrush;
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
int CSigContainer::SetObjectFont
( const sSigFont& i_psSigFont
)
{
  if(mp_psSigObject->nIndexFont < 0)
  { // Ajoute
    mp_psSigObject->nIndexFont = mp_oasArrayFont.AddNodeCRC((void*) &i_psSigFont);
  }
  else
  { // Remplace
    mp_oasArrayFont.SetSlotBuffer((void*) &i_psSigFont, mp_psSigObject->nIndexFont);
  }

  return mp_psSigObject->nIndexFont;
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
int CSigContainer::SetObjectSmooth
( const sSigSmooth& i_psSigSmooth
)
{
  if(mp_psSigObject->nIndexSmooth < 0)
  { // Ajoute
    mp_psSigObject->nIndexSmooth = mp_oasArraySmooth.AddNodeCRC((void*) &i_psSigSmooth);
  }
  else
  { // Remplace
    mp_oasArraySmooth.SetSlotBuffer((void*) &i_psSigSmooth, mp_psSigObject->nIndexSmooth);
  }

  return mp_psSigObject->nIndexSmooth;
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
int CSigContainer::SetObjectText
( const sSigText& i_psSigText
)
{
  if(mp_psSigObject->nIndexText < 0)
  { // Ajoute
    mp_psSigObject->nIndexText = mp_oasArrayText.AddNodeCRC((void*) &i_psSigText);
  }
  else
  { // Remplace
    mp_oasArrayText.SetSlotBuffer((void*) &i_psSigText, mp_psSigObject->nIndexText);
  }

  return mp_psSigObject->nIndexText;
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
CSigContainer::sSigSymbol* CSigContainer::GetObjectSymbol
( int i_nSigSymbol // = (-1)
)
{
  sSigObject* l_poSearch;
  
  if(i_nSigSymbol == (-1))
  {
    l_poSearch   = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch);
    i_nSigSymbol = l_poSearch->nIndexSymbol;
  }
  else{}

  return (sSigSymbol*) mp_oasArraySymbol.GetSlotPointer(i_nSigSymbol);
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
CSigContainer::sSigPen* CSigContainer::GetObjectPen   
( int i_nSigPen    // = (-1)
)
{
  sSigObject* l_poSearch;
  
  if(i_nSigPen == (-1))
  {
    l_poSearch = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch);
    i_nSigPen  = l_poSearch->nIndexPen;
  }
  else{}

  return (sSigPen*) mp_oasArrayPen.GetSlotPointer(i_nSigPen);
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
CSigContainer::sSigBrush* CSigContainer::GetObjectBrush 
( int i_nSigBrush  // = (-1)
)
{
  sSigObject* l_poSearch;
  
  if(i_nSigBrush == (-1))
  {
    l_poSearch  = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch);
    i_nSigBrush = l_poSearch->nIndexBrush;
  }
  else{}

  return (sSigBrush*) mp_oasArrayBrush.GetSlotPointer(i_nSigBrush);
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
CSigContainer::sSigFont* CSigContainer::GetObjectFont  
( int i_nSigFont   // = (-1)
)
{
  sSigObject* l_poSearch;
  
  if(i_nSigFont == (-1))
  {
    l_poSearch = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch);
    i_nSigFont = l_poSearch->nIndexFont;
  }
  else{}

  return (sSigFont*) mp_oasArrayFont.GetSlotPointer(i_nSigFont);
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
CSigContainer::sSigSmooth* CSigContainer::GetObjectSmooth
( int i_nSigSmooth // = (-1)
)
{
  sSigObject* l_poSearch;
  
  if(i_nSigSmooth == (-1))
  {
    l_poSearch   = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch);
    i_nSigSmooth = l_poSearch->nIndexSmooth;
  }
  else{}

  return (sSigSmooth*) mp_oasArraySmooth.GetSlotPointer(i_nSigSmooth);
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
CSigContainer::sSigText* CSigContainer::GetObjectText  
( int i_nSigText   // = (-1)
)
{
  sSigObject* l_poSearch;
  
  if(i_nSigText == (-1))
  {
    l_poSearch = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_nObjectSearch);
    i_nSigText = l_poSearch->nIndexText;
  }
  else{}

  return (sSigText*) mp_oasArrayText.GetSlotPointer(i_nSigText);
}

#ifdef USE_POLYGON
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
int CSigContainer::CopyObjectsFrom
( CSigContainer* i_poSigContainer
, sCoord&        i_rsCoordMin
, sCoord&        i_rsCoordMax
, BOOL           i_bClipObjects // = FALSE
)
{
  int         l_nCounter = 0;

  int         l_nSize[2];
  int         l_nLoop[2];

  CUIntArray  l_oanColIndex;

  sSigObject* l_psSigObject;
  sSigObject* l_psNewObject;

  // Source
  sSigSymbol* l_psSigSymbol;
  sSigPen*    l_psSigPen;
  sSigBrush*  l_psSigBrush;
  sSigFont*   l_psSigFont;
  sSigSmooth* l_psSigSmooth;
  sSigText*   l_psSigText;
  sSigColumn* l_psSigColumn;  

  // Destination
  sSigSymbol  l_sSigSymbol;
  sSigPen     l_sSigPen;
  sSigBrush   l_sSigBrush;
  sSigFont    l_sSigFont;
  sSigSmooth  l_sSigSmooth;
  sSigText    l_sSigText;
  sSigColumn  l_sSigColumn;  

  sSigPoint   l_o3Point;

  bool        l_bPtInRect;
  bool        l_bPtInHead = false;

  char*       l_panTempo;

  //

  m_sHeader = i_poSigContainer->m_sHeader;

  m_sHeader.nName    = AddString(i_poSigContainer->GetString(i_poSigContainer->m_sHeader.nName));
  m_sHeader.nCharset = AddString(i_poSigContainer->GetString(i_poSigContainer->m_sHeader.nCharset));

  if(m_sHeader.sProjection.nSyntax == 3)
  {
    m_sHeader.sProjection.nTypeOrTableName = AddString(i_poSigContainer->GetString(i_poSigContainer->m_sHeader.sProjection.nTypeOrTableName));
  }
  else{}

  m_sHeader.sBound.sMin.nLonX = 0.0;
  m_sHeader.sBound.sMin.nLatY = 0.0;
  m_sHeader.sBound.sMin.nAltZ = 0.0;

  m_sHeader.sBound.sMax.nLonX = 0.0;
  m_sHeader.sBound.sMax.nLatY = 0.0;
  m_sHeader.sBound.sMax.nAltZ = 0.0;

  // GENERATION DE LA LISTE DES COLONNES A COPIER

  l_nSize[0] = GetColumnCount();
  l_nSize[1] = i_poSigContainer->GetColumnCount();

  if(l_nSize[0] < 1)
  { // Si pas de colonne, on copie toutes celles de chez smith d'en face
    for
    ( l_nLoop[1]  = 0
    ; l_nLoop[1] <  l_nSize[1]
    ; l_nLoop[1] += 1
    )
    {
      l_psSigColumn = i_poSigContainer->GetColumnPointer(l_nLoop[1]);

      l_sSigColumn.nNameIndex = AddString(i_poSigContainer->GetString(l_psSigColumn->nNameIndex));
      l_sSigColumn.nSize      = l_psSigColumn->nSize;
      l_sSigColumn.nType      = l_psSigColumn->nType;

      AddColumn(l_sSigColumn);

      l_oanColIndex.Add(l_nLoop[1]);
    }

    l_nSize[0] = GetColumnCount();

    PrepareColumnStorage();
  }
  else
  { // Si nLatY'a des colonnes, on les gardes et on fait une table de correspondance des colonnes
    sSigColumn* l_psDstColumn;  

    for
    ( l_nLoop[0]  = 0
    ; l_nLoop[0] <  l_nSize[0]
    ; l_nLoop[0] += 1
    )
    {
      l_psSigColumn = GetColumnPointer(l_nLoop[0]);

      for
      ( l_nLoop[1]  = 0
      ; l_nLoop[1] <  l_nSize[1]
      ; l_nLoop[1] += 1
      )
      {
        l_psDstColumn = i_poSigContainer->GetColumnPointer(l_nLoop[1]);

        if
        (
             stricmp
             ( GetString(l_psSigColumn->nNameIndex)
             , i_poSigContainer->GetString(l_psDstColumn->nNameIndex)
             ) == 0
          && (l_psSigColumn->nType == l_psDstColumn->nType)
          && (l_psSigColumn->nSize == l_psDstColumn->nSize)
        )
        { // Colonne identique
          break;
        }
        else{}
      }

      if(l_nLoop[1] < l_nSize[1])
      {
        l_oanColIndex.Add(l_nLoop[1]);
      }
      else
      {
        l_oanColIndex.Add(-1); // Colonne inconnues, ne pas copier
      }
    }
  }

  // SCAN DES OBJETS ET COPIE SI NECESSAIRE

  l_psSigObject = i_poSigContainer->GetFirstObject(eOBJTYP__ANY);
  while(l_psSigObject != NULL)
  {
    if(l_psSigObject->eObjectType > eOBJTYP_ROOT)
    { // Si objet valide, on va vérifier si on doit le copier
      l_bPtInRect = false;

      if(i_bClipObjects == FALSE)
      { // Pas de clipping, on vérifie 'juste' si le centre de l'objet est dans la bonne zone
        if
        (
             (l_psSigObject->poPolygon != NULL)
          && (l_psSigObject->poPolygon->GetSize() > 0) // IMPORTANT
        )
        { // Le centre de l'objet
          l_o3Point = l_psSigObject->poPolygon->Centroid();

          l_bPtInRect
          =  (l_o3Point.nLonX > i_rsCoordMin.nLonX)
          && (l_o3Point.nLonX < i_rsCoordMax.nLonX)
          && (l_o3Point.nLatY > i_rsCoordMin.nLatY)
          && (l_o3Point.nLatY < i_rsCoordMax.nLatY)
          ;
        }
        else
        { // L'enveloppe de l'objet
          if
          (
               ( // X-axis
                    (l_psSigObject->sCornerBottomRight.nLonX > i_rsCoordMin.nLonX)
                 && (l_psSigObject->sCornerTopLeft.nLonX     < i_rsCoordMax.nLonX)
               )
            && ( // Y-axis
                    (l_psSigObject->sCornerBottomRight.nLatY < i_rsCoordMax.nLatY)
                 && (l_psSigObject->sCornerTopLeft.nLatY     > i_rsCoordMin.nLatY)
               )
          )
          {
            l_bPtInRect = true;
          }
          else{}
        }
      }
      else
      { // Clipping, on vérifie si l'objet se trouve dans la bonne zone









      }

      if(l_bPtInRect == true)
      { // Si l'objet est considéré à l'interieur de la zone voulue/valide...






// CREATION D'UN PARENT SI BESOIN






        l_psNewObject
        = AddObject
          (
            CreateObject
            ( l_psSigObject->eObjectType
            , l_psSigObject->poPolygon->GetSize()
            )
          )
        ;

        // Les dimensions de l'objet
        l_psNewObject->sCornerTopLeft     = l_psSigObject->sCornerTopLeft;
        l_psNewObject->sCornerBottomRight = l_psSigObject->sCornerBottomRight;

        // On copie les points directement par le conteneur CSigPolygon
        *l_psNewObject->poPolygon = *l_psSigObject->poPolygon;

        // On copie les attributs
        if((l_psSigSymbol = i_poSigContainer->GetObjectSymbol(l_psSigObject->nIndexSymbol)) != NULL)
        {
          l_sSigSymbol = *l_psSigSymbol;

          if(l_sSigSymbol.nFontOrFileNameIndex >= 0)
          { // On corrige l'index de la chaine
            l_sSigSymbol.nFontOrFileNameIndex
            = AddString(i_poSigContainer->GetString(l_sSigSymbol.nFontOrFileNameIndex));
          }
          else{}

          SetObjectSymbol(l_sSigSymbol);
        }else{}

        if((l_psSigPen = i_poSigContainer->GetObjectPen(l_psSigObject->nIndexPen)) != NULL)
        {
          l_sSigPen = *l_psSigPen;
          SetObjectPen(l_sSigPen);
        }else{}

        if((l_psSigBrush = i_poSigContainer->GetObjectBrush(l_psSigObject->nIndexBrush)) != NULL)
        {
          l_sSigBrush = *l_psSigBrush;
          SetObjectBrush(l_sSigBrush);
        }else{}

        if((l_psSigFont = i_poSigContainer->GetObjectFont(l_psSigObject->nIndexFont)) != NULL)
        {
          l_sSigFont = *l_psSigFont;

          if(l_sSigFont.nFontNameIndex >= 0)
          { // On corrige l'index de la chaine
            l_sSigFont.nFontNameIndex
            = AddString(i_poSigContainer->GetString(l_sSigFont.nFontNameIndex));
          }
          else{}

          SetObjectFont(l_sSigFont);
        }else{}

        if((l_psSigSmooth = i_poSigContainer->GetObjectSmooth(l_psSigObject->nIndexSmooth)) != NULL)
        {
          l_sSigSmooth = *l_psSigSmooth;
          SetObjectSmooth(l_sSigSmooth);
        }else{}

        if((l_psSigText = i_poSigContainer->GetObjectText(l_psSigObject->nIndexText)) != NULL)
        {
          l_sSigText = *l_psSigText;
          SetObjectText(l_sSigText);
        }else{}

        // On copie les données MID de l'objet
        for
        ( l_nLoop[0]  = 0
        ; l_nLoop[0] <  l_nSize[0]
        ; l_nLoop[0] += 1
        )
        {
          if(l_oanColIndex[l_nLoop[0]] >= 0)
          { // Copie la donnée de la colonne
            l_panTempo = i_poSigContainer->GetColumnString(l_oanColIndex[l_nLoop[0]], l_psSigObject);

            if(l_panTempo != NULL)
            {
              AddColumnString
              ( l_panTempo
              , l_nLoop[0]
              );
            }
            else
            {
//              ASSERT(l_panTempo != NULL);
            }
          }
          else{}
        }

        // Objet copié
        l_nCounter += 1;
      }
    }
    else{}

    l_psSigObject = i_poSigContainer->GetNextObject(eOBJTYP__ANY);
  }

  // RECALCUL DU BOUNDING BOX DU CONTAINER

  l_psSigObject = GetFirstObject(eOBJTYP__ANY);
  while(l_psSigObject != NULL)
  {
    if(l_psSigObject->eObjectType > eOBJTYP_ROOT)
    { // Si objet valide
      if
      (
           (l_psSigObject->poPolygon != NULL)
        && (l_psSigObject->poPolygon->GetSize() > 0) // IMPORTANT
      )
      {
        l_o3Point = l_psSigObject->poPolygon->Point(0);

        if(l_bPtInHead == false)
        {
          m_sHeader.sBound.sMin.nLonX = l_o3Point.nLonX;
          m_sHeader.sBound.sMin.nLatY = l_o3Point.nLatY;
          m_sHeader.sBound.sMin.nAltZ = 0.0; // l_o3Point.nAltZ;

          m_sHeader.sBound.sMax.nLonX = l_o3Point.nLonX;
          m_sHeader.sBound.sMax.nLatY = l_o3Point.nLatY;
          m_sHeader.sBound.sMax.nAltZ = 0.0; // l_o3Point.nAltZ;
        }
        else{}

        l_psSigObject->sCornerTopLeft.nLonX = l_o3Point.nLonX;
        l_psSigObject->sCornerTopLeft.nLatY = l_o3Point.nLatY;
        l_psSigObject->sCornerTopLeft.nAltZ = l_o3Point.nAltZ;
        
        l_psSigObject->sCornerBottomRight.nLonX = l_o3Point.nLonX;
        l_psSigObject->sCornerBottomRight.nLatY = l_o3Point.nLatY;
        l_psSigObject->sCornerBottomRight.nAltZ = l_o3Point.nAltZ;

        l_nSize[0] = l_psSigObject->poPolygon->GetSize();

        for
        ( l_nLoop[0]  = 1
        ; l_nLoop[0] <  l_nSize[0]
        ; l_nLoop[0] += 1
        )
        {
          l_o3Point = l_psSigObject->poPolygon->Point(l_nLoop[0]);

          if(l_o3Point.nLonX < m_sHeader.sBound.sMin.nLonX) m_sHeader.sBound.sMin.nLonX = l_o3Point.nLonX;
          if(l_o3Point.nLonX > m_sHeader.sBound.sMax.nLonX) m_sHeader.sBound.sMax.nLonX = l_o3Point.nLonX;

          if(l_o3Point.nLatY < m_sHeader.sBound.sMin.nLatY) m_sHeader.sBound.sMin.nLatY = l_o3Point.nLatY;
          if(l_o3Point.nLatY > m_sHeader.sBound.sMax.nLatY) m_sHeader.sBound.sMax.nLatY = l_o3Point.nLatY;

          if(l_o3Point.nAltZ < m_sHeader.sBound.sMin.nAltZ) m_sHeader.sBound.sMin.nAltZ = l_o3Point.nAltZ;
          if(l_o3Point.nAltZ > m_sHeader.sBound.sMax.nAltZ) m_sHeader.sBound.sMax.nAltZ = l_o3Point.nAltZ;

          //

          if(l_o3Point.nLonX < l_psSigObject->sCornerTopLeft.nLonX)     l_psSigObject->sCornerTopLeft.nLonX     = l_o3Point.nLonX;
          if(l_o3Point.nLonX > l_psSigObject->sCornerBottomRight.nLonX) l_psSigObject->sCornerBottomRight.nLonX = l_o3Point.nLonX;

          if(l_o3Point.nLatY < l_psSigObject->sCornerBottomRight.nLatY) l_psSigObject->sCornerBottomRight.nLatY = l_o3Point.nLatY;
          if(l_o3Point.nLatY > l_psSigObject->sCornerTopLeft.nLatY)     l_psSigObject->sCornerTopLeft.nLatY     = l_o3Point.nLatY;

//          if(l_o3Point.nAltZ < l_psSigObject->sCornerTopLeft.nAltZ)     l_psSigObject->sCornerTopLeft.nAltZ     = l_o3Point.nAltZ;
//          if(l_o3Point.nAltZ > l_psSigObject->sCornerBottomRight.nAltZ) l_psSigObject->sCornerBottomRight.nAltZ = l_o3Point.nAltZ;
        }

        l_psSigObject->sCenter.nLonX = (l_psSigObject->sCornerBottomRight.nLonX + l_psSigObject->sCornerTopLeft.nLonX) / 2.0;
        l_psSigObject->sCenter.nLatY = (l_psSigObject->sCornerBottomRight.nLatY + l_psSigObject->sCornerTopLeft.nLatY) / 2.0;
      }
      else{}
    }
    else{}

    l_psSigObject = GetNextObject(eOBJTYP__ANY);
  }

  return l_nCounter;
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
int CSigContainer::CopyFromBlock
( const char* i_panStrBlockName
, double      i_nShiftLonX // = 0.0
, double      i_nShiftLatY // = 0.0
, double      i_nShiftAltZ // = 0.0
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support de la rotation et homothétie d'un bloc
, double      i_nRotation  // = 0.0
, double      i_nScaleX    // = 0.0
, double      i_nScaleY    // = 0.0
, double      i_nScaleZ    // = 0.0
// MODIF_KOCH 070328
)
{
  sSigObject* l_psSigObject;
  sSigObject* l_psOffObject = NULL;
  sSigObject* l_psSrcObject = (sSigObject*) mp_oasArrayObject.GetSlotPointer(mp_asStringBlock.GetStringData(mp_asStringBlock.GetStringIndex(i_panStrBlockName)));
  sSigObject* l_psDstObject;
  int         l_nCopyCount = 0;

  if
  ( // Si y'a une source
       (l_psSrcObject != NULL)
    && (l_psSrcObject->eObjectType == eOBJTYP_BLOCK)
  )
  {
    l_psSigObject = l_psSrcObject;

    while
    ( // On boucle les enfants d'un Block
          (l_psSigObject->eObjectType == eOBJTYP_BLOCK)
       && ((l_psSrcObject = GetFirstObject(CSigContainer::eOBJTYP__ANY, l_psSrcObject->nObjectIndex + 1, true))   != NULL)
       && (l_psSrcObject->nParentIndex == l_psSigObject->nObjectIndex) // Appartient à la Region
       && ((l_psDstObject = AddObject(CreateObject(l_psSrcObject->eObjectType, l_psSrcObject->poPolygon->GetSize()))) != NULL)
    )
    {
      // On copie les points directement par le conteneur CSigPolygon
      *l_psDstObject->poPolygon = *l_psSrcObject->poPolygon;

      // On tourne et/ou agrandit/réduit et/ou déplace le polygone si besoin
      if
      (
           (i_nShiftLonX != 0.0)
        || (i_nShiftLatY != 0.0)
        || (i_nShiftAltZ != 0.0)
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support de la rotation et homothétie d'un bloc
/*
        || (i_nRotation  != 0.0)
        || (i_nScaleX    != 0.0)
        || (i_nScaleY    != 0.0)
        || (i_nScaleZ    != 0.0)
*/
// MODIF_KOCH 070328
      )
      {
        int    l_nLoop;
        int    l_nSize;
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support de la rotation et homothétie d'un bloc
        double l_nAngle = i_nRotation * cDEG2RAD;
        double l_nCos   = cos(l_nAngle);
        double l_nSin   = sin(l_nAngle);
        double l_nLonX;
        double l_nLatY;
// MODIF_KOCH 070328

        for
        ( l_nLoop  = 0
        , l_nSize  = l_psDstObject->poPolygon->GetSize()
        ; l_nLoop <  l_nSize
        ; l_nLoop += 1
        )
        {
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support de la rotation et homothétie d'un bloc
/*
          if(i_nScaleX != 0.0)
          {
            l_psDstObject->poPolygon->Point(l_nLoop).nLonX *= i_nScaleX;
          }
          else{}

          if(i_nScaleY != 0.0)
          {
            l_psDstObject->poPolygon->Point(l_nLoop).nLatY *= i_nScaleY;
          }
          else{}

          if(i_nScaleZ != 0.0)
          {
            l_psDstObject->poPolygon->Point(l_nLoop).nAltZ *= i_nScaleZ;
          }
          else{}
*/
/*
          if(i_nRotation != 0.0)
          {
            l_nLonX = l_psDstObject->poPolygon->Point(l_nLoop).nLonX;
            l_nLatY = l_psDstObject->poPolygon->Point(l_nLoop).nLatY;

            l_psDstObject->poPolygon->Point(l_nLoop).nLonX
            = (l_nLonX ) // - l_nCentreX)
            * l_nCos
            - (l_nLatY ) // - l_nCentreY)
            * l_nSin
            // + l_nCentreX
            ;

            l_psDstObject->poPolygon->Point(l_nLoop).nLatY
            = (l_nLonX ) // - l_nCentreX)
            * l_nSin
            + (l_nLatY ) // - l_nCentreY)
            * l_nCos
            // + l_nCentreX
            ;
          }
          else{}
*/
// MODIF_KOCH 070328

          l_psDstObject->poPolygon->Point(l_nLoop).nLonX += i_nShiftLonX;
          l_psDstObject->poPolygon->Point(l_nLoop).nLatY += i_nShiftLatY;
          l_psDstObject->poPolygon->Point(l_nLoop).nAltZ += i_nShiftAltZ;
        }
      }
      else{}

      // Les dimensions de l'objet
      l_psDstObject->sCornerTopLeft     = l_psSrcObject->sCornerTopLeft;
      l_psDstObject->sCornerBottomRight = l_psSrcObject->sCornerBottomRight;
      l_psDstObject->sCenter            = l_psSrcObject->sCenter;

      // On copie les attributs
      l_psDstObject->nLayerName         = l_psSigObject->nLayerName;
      l_psDstObject->nRowDataIndex      = l_psSigObject->nRowDataIndex;
      l_psDstObject->nTextIndex         = l_psSigObject->nTextIndex;

      l_psDstObject->nIndexSymbol       = l_psSigObject->nIndexSymbol;
      l_psDstObject->nIndexPen          = l_psSigObject->nIndexPen;
      l_psDstObject->nIndexBrush        = l_psSigObject->nIndexBrush;
      l_psDstObject->nIndexFont         = l_psSigObject->nIndexFont;
      l_psDstObject->nIndexSmooth       = l_psSigObject->nIndexSmooth;
      l_psDstObject->nIndexText         = l_psSigObject->nIndexText;

      l_nCopyCount += 1;
    }

    return l_nCopyCount;
  }
/*
  if
  ( // Si y'a une source
       (l_psSrcObject != NULL)
    && ((l_psDstObject = AddObject(CreateObject(l_psSrcObject->eObjectType, l_psSrcObject->poPolygon->GetSize(), i_panStrBlockName))) != NULL)
  )
  {
    l_psSigObject = l_psSrcObject;
    l_psOffObject = l_psDstObject;

    if
    (
         (l_psSigObject->eObjectType == eOBJTYP_BLOCK)
      || (l_psSigObject->eObjectType == eOBJTYP_REGION)
    )
    {
      HierarchyDown();
    }
    else{}

    do
    {
      // On copie les points directement par le conteneur CSigPolygon
      *l_psDstObject->poPolygon         = *l_psSrcObject->poPolygon;

      // Les dimensions de l'objet
      l_psDstObject->sCornerTopLeft     = l_psSrcObject->sCornerTopLeft;
      l_psDstObject->sCornerBottomRight = l_psSrcObject->sCornerBottomRight;
      l_psDstObject->sCenter            = l_psSrcObject->sCenter;

      // On copie les attributs
      l_psDstObject->nLayerName         = l_psSrcObject->nLayerName;
      l_psDstObject->nRowDataIndex      = l_psSrcObject->nRowDataIndex;
      l_psDstObject->nTextIndex         = l_psSrcObject->nTextIndex;

      l_psDstObject->nIndexSymbol       = l_psSrcObject->nIndexSymbol;
      l_psDstObject->nIndexPen          = l_psSrcObject->nIndexPen;
      l_psDstObject->nIndexBrush        = l_psSrcObject->nIndexBrush;
      l_psDstObject->nIndexFont         = l_psSrcObject->nIndexFont;
      l_psDstObject->nIndexSmooth       = l_psSrcObject->nIndexSmooth;
      l_psDstObject->nIndexText         = l_psSrcObject->nIndexText;
    }
    while
    ( // On boucle les enfants d'un Block ou d'une Region
          (
               ( // Block, n'importe quel type d'objet
                      (l_psSigObject->eObjectType == eOBJTYP_BLOCK)
                  && ((l_psSrcObject = GetFirstObject(CSigContainer::eOBJTYP__ANY, l_psSrcObject->nObjectIndex + 1, true))   != NULL)
               )
            || ( // Region, uniquement les Polylines
                      (l_psSigObject->eObjectType == eOBJTYP_REGION)
                  && ((l_psSrcObject = GetFirstObject(CSigContainer::eOBJTYP_POLYLINE, l_psSrcObject->nObjectIndex + 1, true))   != NULL)
               )
          )
       && (l_psSrcObject->nParentIndex == l_psSigObject->nObjectIndex) // Appartient à la Region
       && ((l_psDstObject = AddObject(CreateObject(l_psSrcObject->eObjectType, l_psSrcObject->poPolygon->GetSize()))) != NULL)
    );

    if
    (
         (l_psSigObject->eObjectType == eOBJTYP_BLOCK)
      || (l_psSigObject->eObjectType == eOBJTYP_REGION)
    )
    {
      HierarchyUp();
    }
    else{}

    return l_psOffObject->nObjectIndex; // Première copie (la Region dans le cas d'une Region)
  }
*/
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
void CSigContainer::Simplify(float i_nTolerance)
{
  CSigPolygon l_oPolygon;
  int         l_nSize;
  int         l_nLoop;
  float       l_nTolerance;
  float       l_nTolDivide = 1.0f;
  double      l_nAreaMin   = i_nTolerance * i_nTolerance; // Surface minumum

  if(i_nTolerance > 0.0f)
  {
    for
    ( l_nLoop  = 0
    , l_nSize  = mp_oasArrayObject.GetSlotTail()
    ; l_nLoop <  l_nSize
    ; l_nLoop += 1
    )
    {
      mp_psSigObject = (sSigObject*) mp_oasArrayObject.GetSlotPointer(l_nLoop);

      l_nTolerance = 1.0f; // Nouveau polygone, on redémarre la boucle de tolérance

//      if
      while
      (
           (mp_psSigObject->poPolygon != NULL)
        && (mp_psSigObject->poPolygon->GetSize() >= 3)
        && (l_nTolerance <= l_nTolDivide)
      )
      { // On simplyfie le polygone progressivement
//        float l_nTest = (l_nTolerance * i_nTolerance) / l_nTolDivide;

        mp_psSigObject->poPolygon->Simplify
        ( &l_oPolygon
        , (l_nTolerance * i_nTolerance) / l_nTolDivide
        );

        if
        (
             (
                  (mp_psSigObject->poPolygon->GetSize() >  2)
               && (l_oPolygon.GetSize()                 <= 2)
             )
          || (l_oPolygon.Area() < l_nAreaMin)
        )
        { // Si ce n'est plus un polygone, on l'efface
          mp_psSigObject->poPolygon->RemoveAll();
//          mp_psSigObject->poPolygon->FreeExtra(); // DANGEREUX ICI !!!
        }
        else
        {
          if(l_oPolygon.GetSize() < mp_psSigObject->poPolygon->GetSize())
          { // On recopie le polygone simplifié
            *(mp_psSigObject->poPolygon) = l_oPolygon;
          }
          else{}
        }

        l_nTolerance += 1.0f;
      }
//      else{}
    }
  }
  else{}
}
#endif // USE_POLYGON
