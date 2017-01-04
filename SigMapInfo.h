// SigMapInfo.h: interface for the CSigMapInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGMAPINFO_H__CDDA1458_0757_4E54_A6C3_F7E94A5E1EC0__INCLUDED_)
#define AFX_SIGMAPINFO_H__CDDA1458_0757_4E54_A6C3_F7E94A5E1EC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#include "SigParseText.h"

class EXPSIGENGINE CSigMapInfo : public CSigParseText
{
  public:
    CSigMapInfo(const char* i_panStringName /* = "CSigMapInfo"*/, BOOL i_bCreateOwnContainer = TRUE);
    CSigMapInfo(BOOL i_bCreateOwnContainer = FALSE);
    virtual ~CSigMapInfo(void);

    BOOL FileLoad(char*          i_panStringFile,  CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileLoad(CSigContainer* i_poSigContainer, CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileLoad(                                 CSkinProgress* i_poSkinProgress = NULL);

    BOOL FileSave(char*          i_panStringFile,  CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileSave(CSigContainer* i_poSigContainer, CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileSave(                                 CSkinProgress* i_poSkinProgress = NULL);

  protected:
    typedef enum eMapInfoCommandSet
    { eMIFMID_VERSION = 0
    , eMIFMID_CHARSET
    , eMIFMID_DELIMITER
    , eMIFMID_UNIQUE
    , eMIFMID_INDEX
    , eMIFMID_COORDSYS
    ,   eMIFMID_PROJECTION
    ,   eMIFMID_AFFINE
    ,   eMIFMID_UNITS
    ,   eMIFMID_BOUNDS
    , eMIFMID_TRANSFORM
    , eMIFMID_COLUMNS
    ,   eMIFMID_CHAR // Type de colonne
    ,   eMIFMID_INTEGER
    ,   eMIFMID_SMALLINT
    ,   eMIFMID_DECIMAL
    ,   eMIFMID_FLOAT
    ,   eMIFMID_DATE
    ,   eMIFMID_LOGICAL
    , eMIFMID_DATA
    ,     eMIFMID_SYMBOL // Attributs
    ,     eMIFMID_PEN
    ,     eMIFMID_BRUSH
    ,     eMIFMID_FONT
    ,     eMIFMID_SMOOTH
    ,     eMIFMID_SPACING
    ,     eMIFMID_JUSTIFY
    ,     eMIFMID_LEFT
    ,     eMIFMID_CENTER
    ,     eMIFMID_RIGHT
    ,     eMIFMID_ANGLE
    ,     eMIFMID_LABEL
    ,     eMIFMID_SIMPLE
    ,     eMIFMID_ARROW
    ,   eMIFMID_POINT // Objets
    ,   eMIFMID_LINE
    ,   eMIFMID_PLINE
    ,   eMIFMID_MULTIPLE
    ,   eMIFMID_REGION
    ,   eMIFMID_ARC
    ,   eMIFMID_TEXT
    ,   eMIFMID_RECT
    ,   eMIFMID_ROUNDRECT
    ,   eMIFMID_ELLIPSE
    ,   eMIFMID_MULTIPOINT
    ,   eMIFMID_COLLECTION
    , eMIFMID__END
    } eMICS;

    int mp_anHashTable[eMIFMID__END];

    //

    BOOL _Initialize(BOOL i_bCreateOwnContainer = TRUE);

    BOOL _IsHashed(int i_nIndex, XString i_poStrHash = "");
    BOOL _IsHashed(int i_nIndex, int i_nHashed);
};

#endif // !defined(AFX_SIGMAPINFO_H__CDDA1458_0757_4E54_A6C3_F7E94A5E1EC0__INCLUDED_)
