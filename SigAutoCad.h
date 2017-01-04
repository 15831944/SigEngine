// SigAutoCad.h: interface for the CSigAutoCad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGAUTOCAD_H__0FF9C941_25F7_4817_A1DC_DB865B3E0B0C__INCLUDED_)
#define AFX_SIGAUTOCAD_H__0FF9C941_25F7_4817_A1DC_DB865B3E0B0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#include "SigParseText.h"

class EXPSIGENGINE CSigAutoCad : public CSigParseText  
{
  public:
    CSigAutoCad(const char* i_panStringName /* = "CSigAutoCad"*/, BOOL i_bCreateOwnContainer = TRUE);
    CSigAutoCad(BOOL i_bCreateOwnContainer = FALSE);
    virtual ~CSigAutoCad(void);

    BOOL FileLoad(char*          i_panStringFile,  CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileLoad(CSigContainer* i_poSigContainer, CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileLoad(                                 CSkinProgress* i_poSkinProgress = NULL);

    BOOL FileSave(char*          i_panStringFile,  CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileSave(CSigContainer* i_poSigContainer, CSkinProgress* i_poSkinProgress = NULL);
    BOOL FileSave(                                 CSkinProgress* i_poSkinProgress = NULL);

  protected:
    typedef enum eAutoCadCommandSet
    { eDXF_SECTION = 0                  // 0
    , eDXF_HEADER                       // .2
    ,   eDXF_$ACADMAINTVER              // ..9
    ,   eDXF_$ACADVER                   // ..9
    ,   eDXF_$ANGBASE                   // ..9
    ,   eDXF_$ANGDIR                    // ..9
//    ,   eDXF_$ATTDIA                  // ..9
    ,   eDXF_$ATTMODE                   // ..9
//    ,   eDXF_$ATTREQ                  // ..9
    ,   eDXF_$AUNITS                    // ..9
    ,   eDXF_$AUPREC                    // ..9
//    ,   eDXF_$AXISMODE                // ..9
//    ,   eDXF_$AXISUNIT                // ..9
//    ,   eDXF_$BLIPMODE                // ..9
    ,   eDXF_$CECOLOR                   // ..9
    ,   eDXF_$CELTSCALE                 // ..9
    ,   eDXF_$CELTYPE                   // ..9
    ,   eDXF_$CELWEIGHT                 // ..9
    ,   eDXF_$CEPSNID                   // ..9
    ,   eDXF_$CEPSNTYPE                 // ..9
    ,   eDXF_$CHAMFERA                  // ..9
    ,   eDXF_$CHAMFERB                  // ..9
    ,   eDXF_$CHAMFERC                  // ..9
    ,   eDXF_$CHAMFERD                  // ..9
    ,   eDXF_$CLAYER                    // ..9
    ,   eDXF_$CMLJUST                   // ..9
    ,   eDXF_$CMLSCALE                  // ..9
    ,   eDXF_$CMLSTYLE                  // ..9
    ,   eDXF_$CSHADOW                   // ..9
//    ,   eDXF_$COORDS                  // ..9
    ,   eDXF_$DIMADEC                   // ..9
    ,   eDXF_$DIMALT                    // ..9
    ,   eDXF_$DIMALTD                   // ..9
    ,   eDXF_$DIMALTF                   // ..9
    ,   eDXF_$DIMALTRND                 // ..9
    ,   eDXF_$DIMALTTD                  // ..9
    ,   eDXF_$DIMALTTZ                  // ..9
    ,   eDXF_$DIMALTU                   // ..9
    ,   eDXF_$DIMALTZ                   // ..9
    ,   eDXF_$DIMAPOST                  // ..9
    ,   eDXF_$DIMASO                    // ..9
    ,   eDXF_$DIMASSOC                  // ..9
    ,   eDXF_$DIMASZ                    // ..9
    ,   eDXF_$DIMATFIT                  // ..9
    ,   eDXF_$DIMAUNIT                  // ..9
    ,   eDXF_$DIMAZIN                   // ..9
    ,   eDXF_$DIMBLK                    // ..9
    ,   eDXF_$DIMBLK1                   // ..9
    ,   eDXF_$DIMBLK2                   // ..9
    ,   eDXF_$DIMCEN                    // ..9
    ,   eDXF_$DIMCLRD                   // ..9
    ,   eDXF_$DIMCLRE                   // ..9
    ,   eDXF_$DIMCLRT                   // ..9
    ,   eDXF_$DIMDEC                    // ..9
    ,   eDXF_$DIMDLE                    // ..9
    ,   eDXF_$DIMDLI                    // ..9
    ,   eDXF_$DIMDSEP                   // ..9
    ,   eDXF_$DIMEXE                    // ..9
    ,   eDXF_$DIMEXO                    // ..9
    ,   eDXF_$DIMFAC                    // ..9
    ,   eDXF_$DIMGAP                    // ..9
    ,   eDXF_$DIMJUST                   // ..9
    ,   eDXF_$DIMLDRBLK                 // ..9
    ,   eDXF_$DIMLFAC                   // ..9
    ,   eDXF_$DIMLIM                    // ..9
    ,   eDXF_$DIMLUNIT                  // ..9
    ,   eDXF_$DIMLWD                    // ..9
    ,   eDXF_$DIMLWE                    // ..9
    ,   eDXF_$DIMPOST                   // ..9
    ,   eDXF_$DIMRND                    // ..9
    ,   eDXF_$DIMSAH                    // ..9
    ,   eDXF_$DIMSCALE                  // ..9
    ,   eDXF_$DIMSD1                    // ..9
    ,   eDXF_$DIMSD2                    // ..9
    ,   eDXF_$DIMSE1                    // ..9
    ,   eDXF_$DIMSE2                    // ..9
    ,   eDXF_$DIMSHO                    // ..9
    ,   eDXF_$DIMSOXD                   // ..9
    ,   eDXF_$DIMSTYLE                  // ..9
    ,   eDXF_$DIMTAD                    // ..9
    ,   eDXF_$DIMTDEC                   // ..9
    ,   eDXF_$DIMTFAC                   // ..9
    ,   eDXF_$DIMTIH                    // ..9
    ,   eDXF_$DIMTIX                    // ..9
    ,   eDXF_$DIMTM                     // ..9
    ,   eDXF_$DIMTMOVE                  // ..9
    ,   eDXF_$DIMTOFL                   // ..9
    ,   eDXF_$DIMTOH                    // ..9
    ,   eDXF_$DIMTOL                    // ..9
    ,   eDXF_$DIMTOLJ                   // ..9
    ,   eDXF_$DIMTP                     // ..9
    ,   eDXF_$DIMTSZ                    // ..9
    ,   eDXF_$DIMTVP                    // ..9
    ,   eDXF_$DIMTXSTY                  // ..9
    ,   eDXF_$DIMTXT                    // ..9
    ,   eDXF_$DIMTZIN                   // ..9
    ,   eDXF_$DIMUPT                    // ..9
    ,   eDXF_$DIMZIN                    // ..9
    ,   eDXF_$DISPSILH                  // ..9
//    ,   eDXF_$DRAGMODE                // ..9
    ,   eDXF_$DRAGVS                    // ..9
    ,   eDXF_$DWGCODEPAGE               // ..9
    ,   eDXF_$ELEVATION                 // ..9
    ,   eDXF_$ENDCAPS                   // ..9
    ,   eDXF_$EXTMAX                    // ..9
    ,   eDXF_$EXTMIN                    // ..9
    ,   eDXF_$EXTNAMES                  // ..9
    ,   eDXF_$FILLETRAD                 // ..9
    ,   eDXF_$FILLMODE                  // ..9
    ,   eDXF_$FINGERPRINTGUID           // ..9
//    ,   eDXF_$FLATLAND                  // ..9
    ,   eDXF_$HALOGAP                   // ..9
//    ,   eDXF_$HANDLING                // ..9
    ,   eDXF_$HANDSEED                  // ..9
    ,   eDXF_$HIDETEXT                  // ..9
    ,   eDXF_$HYPERLINKBASE             // ..9
    ,   eDXF_$INDEXCTL                  // ..9
    ,   eDXF_$INSBASE                   // ..9
    ,   eDXF_$INSUNITS                  // ..9
    ,   eDXF_$INTERFERECOLOR            // ..9
    ,   eDXF_$INTERFEREOBJVS            // ..9
    ,   eDXF_$INTERFEREVPVS             // ..9
    ,   eDXF_$INTERSECTIONCOLOR         // ..9
    ,   eDXF_$INTERSECTIONDISPLAY       // ..9
    ,   eDXF_$JOINSTYLE                 // ..9
    ,   eDXF_$LIMCHECK                  // ..9
    ,   eDXF_$LIMMAX                    // ..9
    ,   eDXF_$LIMMIN                    // ..9
    ,   eDXF_$LTSCALE                   // ..9
    ,   eDXF_$LUNITS                    // ..9
    ,   eDXF_$LUPREC                    // ..9
    ,   eDXF_$LWDISPLAY                 // ..9
    ,   eDXF_$MAXACTVP                  // ..9
    ,   eDXF_$MEASUREMENT               // ..9
    ,   eDXF_$MENU                      // ..9
    ,   eDXF_$MIRRTEXT                  // ..9
    ,   eDXF_$OBSCOLOR                  // ..9
    ,   eDXF_$OBSLTYPE                  // ..9
    ,   eDXF_$ORTHOMODE                 // ..9
//    ,   eDXF_$OSMODE                  // ..9
    ,   eDXF_$PDMODE                    // ..9
    ,   eDXF_$PDSIZE                    // ..9
    ,   eDXF_$PELEVATION                // ..9
    ,   eDXF_$PEXTMAX                   // ..9
    ,   eDXF_$PEXTMIN                   // ..9
    ,   eDXF_$PINSBASE                  // ..9
    ,   eDXF_$PLIMCHECK                 // ..9
    ,   eDXF_$PLIMMAX                   // ..9
    ,   eDXF_$PLIMMIN                   // ..9
    ,   eDXF_$PLINEGEN                  // ..9
    ,   eDXF_$PLINEWID                  // ..9
    ,   eDXF_$PROJECTNAME               // ..9
    ,   eDXF_$PROXYGRAPHICS             // ..9
    ,   eDXF_$PSLTSCALE                 // ..9
    ,   eDXF_$PSTYLEMODE                // ..9
    ,   eDXF_$PSVPSCALE                 // ..9
    ,   eDXF_$PUCSBASE                  // ..9
    ,   eDXF_$PUCSNAME                  // ..9
    ,   eDXF_$PUCSORG                   // ..9
    ,   eDXF_$PUCSORGBACK               // ..9
    ,   eDXF_$PUCSORGBOTTOM             // ..9
    ,   eDXF_$PUCSORGFRONT              // ..9
    ,   eDXF_$PUCSORGLEFT               // ..9
    ,   eDXF_$PUCSORGRIGHT              // ..9
    ,   eDXF_$PUCSORGTOP                // ..9
    ,   eDXF_$PUCSORTHOREF              // ..9
    ,   eDXF_$PUCSORTHOVIEW             // ..9
    ,   eDXF_$PUCSXDIR                  // ..9
    ,   eDXF_$PUCSYDIR                  // ..9
    ,   eDXF_$QTEXTMODE                 // ..9
    ,   eDXF_$REGENMODE                 // ..9
    ,   eDXF_$SHADEDGE                  // ..9
    ,   eDXF_$SHADEDIF                  // ..9
    ,   eDXF_$SHADOWPLANELOCATION       // ..9
    ,   eDXF_$SKETCHINC                 // ..9
    ,   eDXF_$SKPOLY                    // ..9
    ,   eDXF_$SORTENTS                  // ..9
    ,   eDXF_$SPLFRAME                  // ..9
    ,   eDXF_$SPLINESEGS                // ..9
    ,   eDXF_$SPLINETYPE                // ..9
    ,   eDXF_$SURFTAB1                  // ..9
    ,   eDXF_$SURFTAB2                  // ..9
    ,   eDXF_$SURFTYPE                  // ..9
    ,   eDXF_$SURFU                     // ..9
    ,   eDXF_$SURFV                     // ..9
    ,   eDXF_$TDCREATE                  // ..9
    ,   eDXF_$TDINDWG                   // ..9
    ,   eDXF_$TDUCREATE                 // ..9
    ,   eDXF_$TDUPDATE                  // ..9
    ,   eDXF_$TDUSRTIMER                // ..9
    ,   eDXF_$TDUUPDATE                 // ..9
    ,   eDXF_$TEXTSIZE                  // ..9
    ,   eDXF_$TEXTSTYLE                 // ..9
    ,   eDXF_$THICKNESS                 // ..9
    ,   eDXF_$TILEMODE                  // ..9
    ,   eDXF_$TRACEWID                  // ..9
    ,   eDXF_$TREEDEPTH                 // ..9
    ,   eDXF_$UCSBASE                   // ..9
    ,   eDXF_$UCSNAME                   // ..9
    ,   eDXF_$UCSORG                    // ..9
    ,   eDXF_$UCSORGBACK                // ..9
    ,   eDXF_$UCSORGBOTTOM              // ..9
    ,   eDXF_$UCSORGFRONT               // ..9
    ,   eDXF_$UCSORGLEFT                // ..9
    ,   eDXF_$UCSORGRIGHT               // ..9
    ,   eDXF_$UCSORGTOP                 // ..9
    ,   eDXF_$UCSORTHOREF               // ..9
    ,   eDXF_$UCSORTHOVIEW              // ..9
    ,   eDXF_$UCSXDIR                   // ..9
    ,   eDXF_$UCSYDIR                   // ..9
    ,   eDXF_$UNITMODE                  // ..9
    ,   eDXF_$USERI1                    // ..9
    ,   eDXF_$USERI2                    // ..9
    ,   eDXF_$USERI3                    // ..9
    ,   eDXF_$USERI4                    // ..9
    ,   eDXF_$USERI5                    // ..9
    ,   eDXF_$USERR1                    // ..9
    ,   eDXF_$USERR2                    // ..9
    ,   eDXF_$USERR3                    // ..9
    ,   eDXF_$USERR4                    // ..9
    ,   eDXF_$USERR5                    // ..9
    ,   eDXF_$USRTIMER                  // ..9
    ,   eDXF_$VERSIONGUID               // ..9
    ,   eDXF_$VISRETAIN                 // ..9
    ,   eDXF_$WORLDVIEW                 // ..9
    ,   eDXF_$XCLIPFRAME                // ..9
    ,   eDXF_$XEDIT                     // ..9
    , eDXF_CLASSES                      // .2
    ,   eDXF_CLASS                      // 0
    , eDXF_TABLES                       // .2
    ,   eDXF_TABLE                      // 0
    ,     eDXF_APPID                    // 0
    ,     eDXF_BLOCKRECORD              // 0
    ,     eDXF_DIMSTYLE                 // 0
    ,     eDXF_LAYER                    // 0
    ,     eDXF_LTYPE                    // 0
    ,     eDXF_STYLE                    // 0
    ,     eDXF_UCS                      // 0
    ,     eDXF_VIEW                     // 0
    ,     eDXF_VPORT                    // 0
    ,       eDXF_$FASTZOOM              // ..9
    ,       eDXF_$GRIDMODE              // ..9
    ,       eDXF_$GRIDUNIT              // ..9
    ,       eDXF_$SNAPANG               // ..9
    ,       eDXF_$SNAPBASE              // ..9
    ,       eDXF_$SNAPISOPAIR           // ..9
    ,       eDXF_$SNAPMODE              // ..9
    ,       eDXF_$SNAPSTYLE             // ..9
    ,       eDXF_$SNAPUNIT              // ..9
    ,       eDXF_$VIEWCTR               // ..9
    ,       eDXF_$VIEWDIR               // ..9
    ,       eDXF_$VIEWSIZE              // ..9
    ,   eDXF_ENDTAB                     // 0
    , eDXF_BLOCKS                       // .2
    ,   eDXF_BLOCK                      // 0
    ,   eDXF_ENDBLK                     // 0
    , eDXF_ENTITIES                     // .2 <- Objets
    ,   eDXF_3DFACE                     // 0
    ,   eDXF_3DSOLID                    // 0
    ,   eDXF_ACAD_PROXY_ENTITY          // 0
    ,   eDXF_ARC                        // 0
    ,   eDXF_ATTDEF                     // 0
    ,   eDXF_ATTRIB                     // 0
    ,   eDXF_BODY                       // 0
    ,   eDXF_CIRCLE                     // 0
    ,   eDXF_DIMENSION                  // 0
    ,   eDXF_ELLIPSE                    // 0
    ,   eDXF_HATCH                      // 0
    ,   eDXF_HELIX                      // 0
    ,   eDXF_IMAGE                      // 0
    ,   eDXF_INSERT                     // 0
    ,   eDXF_LEADER                     // 0
    ,   eDXF_LIGHT                      // 0
    ,   eDXF_LINE                       // 0
    ,   eDXF_LWPOLYLINE                 // 0
    ,   eDXF_MLINE                      // 0
    ,   eDXF_MTEXT                      // 0
    ,   eDXF_OLEFRAME                   // 0
    ,   eDXF_OLE2FRAME                  // 0
    ,   eDXF_POINT                      // 0
    ,   eDXF_POLYLINE                   // 0
    ,   eDXF_RAY                        // 0
    ,   eDXF_REGION                     // 0
//    ,   eDXF_SECTION                    // 0
    ,   eDXF_SEQEND                     // 0
    ,   eDXF_SHAPE                      // 0
    ,   eDXF_SOLID                      // 0
    ,   eDXF_SPLINE                     // 0
    ,   eDXF_SUN                        // 0
    ,   eDXF_SURFACE                    // 0
//    ,   eDXF_TABLE                      // 0
    ,   eDXF_TEXT                       // 0
    ,   eDXF_TOLERANCE                  // 0
    ,   eDXF_TRACE                      // 0
    ,   eDXF_UNDERLAY                   // 0
    ,   eDXF_VERTEX                     // 0
    ,   eDXF_VIEWPORT                   // 0
    ,   eDXF_WIPEOUT                    // 0
    ,   eDXF_XLINE                      // 0
    ,   eDXF_ENDSEC                     // 0
    , eDXF_OBJECT                       // .2
    ,   eDXF_ACAD_PROXY_OBJECT          // 0
    ,   eDXF_ACDBDICTIONARYWDFLT        // 0
    ,   eDXF_ACDBPLACEHOLDER            // 0
    ,   eDXF_DATATABLE                  // 0
    ,   eDXF_DICTIONARY                 // 0
    ,   eDXF_DICTIONARYVAR              // 0
    ,   eDXF_DIMASSOC                   // 0
    ,   eDXF_FIELD                      // 0
    ,   eDXF_GROUP                      // 0
    ,   eDXF_IDBUFFER                   // 0
    ,   eDXF_IMAGEDEF                   // 0
    ,   eDXF_IMAGEDEF_REACTOR           // 0
    ,   eDXF_LAYER_INDEX                // 0
    ,   eDXF_LAYER_FILTER               // 0
    ,   eDXF_LAYOUT                     // 0
    ,   eDXF_LIGHTLIST                  // 0
    ,   eDXF_MATERIAL                   // 0
    ,   eDXF_MLINESTYLE                 // 0
    ,   eDXF_OBJECT_PTR                 // 0
    ,   eDXF_PLOTSETTINGS               // 0
    ,   eDXF_RASTERVARIABLES            // 0
    ,   eDXF_RENDER                     // 0
    ,   eDXF_RENDERENVIRONMENT          // 0
    ,   eDXF_METALRAYRENDEREINGSETTINGS // 0
    ,   eDXF_RENDERGLOBAL               // 0
//    ,   eDXF_SECTION                    // 0
    ,   eDXF_SPATIAL_INDEX              // 0
    ,   eDXF_SPATIAL_FILTER             // 0
    ,   eDXF_SORTENTSTABLE              // 0
    ,   eDXF_SUNSTUDY                   // 0
    ,   eDXF_TABLESTYLE                 // 0
    ,   eDXF_UNDERLAYDEFINITION         // 0
    ,   eDXF_VISUALSTYLE                // 0
    ,   eDXF_VBA_PROJECT                // 0
    ,   eDXF_WIPEOUTVARIABLES           // 0
    ,   eDXF_XRECORD                    // 0
    , eDXF_THUMBNAILIMAGE               // .2
    , eDXF_EOF                          // 0
    , eDXF__END
    } eACCS;

    int mp_anHashTable[eDXF__END];

    //

    BOOL _Initialize(BOOL i_bCreateOwnContainer = TRUE);

    BOOL _IsHashed(int i_nIndex, XString i_poStrHash = "");
    BOOL _IsHashed(int i_nIndex, int i_nHashed);

    void _WriteDxfTag(int tag_number, const char* tag_name);
    void _WriteDxfXy (double i_nLonX, double i_nLatY, int i_nRef = 0);
    void _WriteDxfXyz(double i_nLonX, double i_nLatY, double i_nAltY, int i_nRef = 0);
    void _WriteDxfData(CSigContainer::sSigObject* i_psSigObject);

    CString             mp_oStrTempo;
    CMemoryTreeRedBlack mp_oasArrayHash;
};

#endif // !defined(AFX_SIGAUTOCAD_H__0FF9C941_25F7_4817_A1DC_DB865B3E0B0C__INCLUDED_)
