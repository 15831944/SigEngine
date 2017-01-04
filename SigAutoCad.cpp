// SigAutoCad.cpp: implementation of the CSigAutoCad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SigAutoCad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE DE FORMAT ===============================================================================================

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
CSigAutoCad::CSigAutoCad
( const char* i_panStringName
, BOOL        i_bCreateOwnContainer // = TRUE
)
{
#ifdef _DEBUG
  SetClassName(i_panStringName);
#endif // _DEBUG

  _Initialize(i_bCreateOwnContainer);
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
CSigAutoCad::CSigAutoCad
( BOOL i_bCreateOwnContainer // = FALSE
)
{
  _Initialize(i_bCreateOwnContainer);
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
CSigAutoCad::~CSigAutoCad
(
)
{
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
BOOL CSigAutoCad::_Initialize
( BOOL i_bCreateOwnContainer // = TRUE
)
{
  int   l_nLoop;
  char* l_panHashTable[]
  = 
  { "SECTION"                      // eDXF_SECTION    -> HEADER
  , "HEADER"                       // eDXF_HEADER
  ,   "$ACADMAINTVER"              // eDXF_$ACADMAINTVER
  ,   "$ACADVER"                   // eDXF_$ACADVER
  ,   "$ANGBASE"                   // eDXF_$ANGBASE
  ,   "$ANGDIR"                    // eDXF_$ANGDIR
//  ,   "$ATTDIA"                    // eDXF_$ATTDIA
  ,   "$ATTMODE"                   // eDXF_$ATTMODE
//  ,   "$ATTREQ"                    // eDXF_$ATTREQ
  ,   "$AUNITS"                    // eDXF_$AUNITS
  ,   "$AUPREC"                    // eDXF_$AUPREC
//  ,   "$AXISMODE"                  // eDXF_$AXISMODE
//  ,   "$AXISUNIT"                  // eDXF_$AXISUNIT
//  ,   "$BLIPMODE"                  // eDXF_$BLIPMODE
  ,   "$CECOLOR"                   // eDXF_$CECOLOR
  ,   "$CELTSCALE"                 // eDXF_$CELTSCALE
  ,   "$CELTYPE"                   // eDXF_$CELTYPE
  ,   "$CELWEIGHT"                 // eDXF_$CELWEIGHT
  ,   "$CEPSNID"                   // eDXF_$CEPSNID
  ,   "$CEPSNTYPE"                 // eDXF_$CEPSNTYPE
  ,   "$CHAMFERA"                  // eDXF_$CHAMFERA
  ,   "$CHAMFERB"                  // eDXF_$CHAMFERB
  ,   "$CHAMFERC"                  // eDXF_$CHAMFERC
  ,   "$CHAMFERD"                  // eDXF_$CHAMFERD
  ,   "$CLAYER"                    // eDXF_$CLAYER
  ,   "$CMLJUST"                   // eDXF_$CMLJUST
  ,   "$CMLSCALE"                  // eDXF_$CMLSCALE
  ,   "$CMLSTYLE"                  // eDXF_$CMLSTYLE
  ,   "$CSHADOW"                   // eDXF_$CSHADOW
//  ,   "$COORDS"                    // eDXF_$COORDS
  ,   "$DIMADEC"                   // eDXF_$DIMADEC
  ,   "$DIMALT"                    // eDXF_$DIMALT
  ,   "$DIMALTD"                   // eDXF_$DIMALTD
  ,   "$DIMALTF"                   // eDXF_$DIMALTF
  ,   "$DIMALTRND"                 // eDXF_$DIMALTRND
  ,   "$DIMALTTD"                  // eDXF_$DIMALTTD
  ,   "$DIMALTTZ"                  // eDXF_$DIMALTTZ
  ,   "$DIMALTU"                   // eDXF_$DIMALTU
  ,   "$DIMALTZ"                   // eDXF_$DIMALTZ
  ,   "$DIMAPOST"                  // eDXF_$DIMAPOST
  ,   "$DIMASO"                    // eDXF_$DIMASO
  ,   "$DIMASSOC"                  // eDXF_$DIMASSOC
  ,   "$DIMASZ"                    // eDXF_$DIMASZ
  ,   "$DIMATFIT"                  // eDXF_$DIMATFIT
  ,   "$DIMAUNIT"                  // eDXF_$DIMAUNIT
  ,   "$DIMAZIN"                   // eDXF_$DIMAZIN
  ,   "$DIMBLK"                    // eDXF_$DIMBLK
  ,   "$DIMBLK1"                   // eDXF_$DIMBLK1
  ,   "$DIMBLK2"                   // eDXF_$DIMBLK2
  ,   "$DIMCEN"                    // eDXF_$DIMCEN
  ,   "$DIMCLRD"                   // eDXF_$DIMCLRD
  ,   "$DIMCLRE"                   // eDXF_$DIMCLRE
  ,   "$DIMCLRT"                   // eDXF_$DIMCLRT
  ,   "$DIMDEC"                    // eDXF_$DIMDEC
  ,   "$DIMDLE"                    // eDXF_$DIMDLE
  ,   "$DIMDLI"                    // eDXF_$DIMDLI
  ,   "$DIMDSEP"                   // eDXF_$DIMDSEP
  ,   "$DIMEXE"                    // eDXF_$DIMEXE
  ,   "$DIMEXO"                    // eDXF_$DIMEXO
  ,   "$DIMFAC"                    // eDXF_$DIMFAC
  ,   "$DIMGAP"                    // eDXF_$DIMGAP
  ,   "$DIMJUST"                   // eDXF_$DIMJUST
  ,   "$DIMLDRBLK"                 // eDXF_$DIMLDRBLK
  ,   "$DIMLFAC"                   // eDXF_$DIMLFAC
  ,   "$DIMLIM"                    // eDXF_$DIMLIM
  ,   "$DIMLUNIT"                  // eDXF_$DIMLUNIT
  ,   "$DIMLWD"                    // eDXF_$DIMLWD
  ,   "$DIMLWE"                    // eDXF_$DIMLWE
  ,   "$DIMPOST"                   // eDXF_$DIMPOST
  ,   "$DIMRND"                    // eDXF_$DIMRND
  ,   "$DIMSAH"                    // eDXF_$DIMSAH
  ,   "$DIMSCALE"                  // eDXF_$DIMSCALE
  ,   "$DIMSD1"                    // eDXF_$DIMSD1
  ,   "$DIMSD2"                    // eDXF_$DIMSD2
  ,   "$DIMSE1"                    // eDXF_$DIMSE1
  ,   "$DIMSE2"                    // eDXF_$DIMSE2
  ,   "$DIMSHO"                    // eDXF_$DIMSHO
  ,   "$DIMSOXD"                   // eDXF_$DIMSOXD
  ,   "$DIMSTYLE"                  // eDXF_$DIMSTYLE
  ,   "$DIMTAD"                    // eDXF_$DIMTAD
  ,   "$DIMTDEC"                   // eDXF_$DIMTDEC
  ,   "$DIMTFAC"                   // eDXF_$DIMTFAC
  ,   "$DIMTIH"                    // eDXF_$DIMTIH
  ,   "$DIMTIX"                    // eDXF_$DIMTIX
  ,   "$DIMTM"                     // eDXF_$DIMTM
  ,   "$DIMTMOVE"                  // eDXF_$DIMTMOVE
  ,   "$DIMTOFL"                   // eDXF_$DIMTOFL
  ,   "$DIMTOH"                    // eDXF_$DIMTOH
  ,   "$DIMTOL"                    // eDXF_$DIMTOL
  ,   "$DIMTOLJ"                   // eDXF_$DIMTOLJ
  ,   "$DIMTP"                     // eDXF_$DIMTP
  ,   "$DIMTSZ"                    // eDXF_$DIMTSZ
  ,   "$DIMTVP"                    // eDXF_$DIMTVP
  ,   "$DIMTXSTY"                  // eDXF_$DIMTXSTY
  ,   "$DIMTXT"                    // eDXF_$DIMTXT
  ,   "$DIMTZIN"                   // eDXF_$DIMTZIN
  ,   "$DIMUPT"                    // eDXF_$DIMUPT
  ,   "$DIMZIN"                    // eDXF_$DIMZIN
  ,   "$DISPSILH"                  // eDXF_$DISPSILH
//  ,   "$DRAGMODE"                  // eDXF_$DRAGMODE
  ,   "$DRAGVS"                    // eDXF_$DRAGVS
  ,   "$DWGCODEPAGE"               // eDXF_$DWGCODEPAGE
  ,   "$ELEVATION"                 // eDXF_$ELEVATION
  ,   "$ENDCAPS"                   // eDXF_$ENDCAPS
  ,   "$EXTMAX"                    // eDXF_$EXTMAX
  ,   "$EXTMIN"                    // eDXF_$EXTMIN
  ,   "$EXTNAMES"                  // eDXF_$EXTNAMES
  ,   "$FILLETRAD"                 // eDXF_$FILLETRAD
  ,   "$FILLMODE"                  // eDXF_$FILLMODE
  ,   "$FINGERPRINTGUID"           // eDXF_$FINGERPRINTGUID
  ,   "$HALOGAP"                   // eDXF_$HALOGAP
//  ,   "$HANDLING"                  // eDXF_$HANDLING
  ,   "$HANDSEED"                  // eDXF_$HANDSEED
  ,   "$HIDETEXT"                  // eDXF_$HIDETEXT
  ,   "$HYPERLINKBASE"             // eDXF_$HYPERLINKBASE
  ,   "$INDEXCTL"                  // eDXF_$INDEXCTL
  ,   "$INSBASE"                   // eDXF_$INSBASE
  ,   "$INSUNITS"                  // eDXF_$INSUNITS
  ,   "$INTERFERECOLOR"            // eDXF_$INTERFERECOLOR
  ,   "$INTERFEREOBJVS"            // eDXF_$INTERFEREOBJVS
  ,   "$INTERFEREVPVS"             // eDXF_$INTERFEREVPVS
  ,   "$INTERSECTIONCOLOR"         // eDXF_$INTERSECTIONCOLOR
  ,   "$INTERSECTIONDISPLAY"       // eDXF_$INTERSECTIONDISPLAY
  ,   "$JOINSTYLE"                 // eDXF_$JOINSTYLE
  ,   "$LIMCHECK"                  // eDXF_$LIMCHECK
  ,   "$LIMMAX"                    // eDXF_$LIMMAX
  ,   "$LIMMIN"                    // eDXF_$LIMMIN
  ,   "$LTSCALE"                   // eDXF_$LTSCALE
  ,   "$LUNITS"                    // eDXF_$LUNITS
  ,   "$LUPREC"                    // eDXF_$LUPREC
  ,   "$LWDISPLAY"                 // eDXF_$LWDISPLAY
  ,   "$MAXACTVP"                  // eDXF_$MAXACTVP
  ,   "$MEASUREMENT"               // eDXF_$MEASUREMENT
  ,   "$MENU"                      // eDXF_$MENU
  ,   "$MIRRTEXT"                  // eDXF_$MIRRTEXT
  ,   "$OBSCOLOR"                  // eDXF_$OBSCOLOR
  ,   "$OBSLTYPE"                  // eDXF_$OBSLTYPE
  ,   "$ORTHOMODE"                 // eDXF_$ORTHOMODE
//  ,   "$OSMODE"                    // eDXF_$OSMODE
  ,   "$PDMODE"                    // eDXF_$PDMODE
  ,   "$PDSIZE"                    // eDXF_$PDSIZE
  ,   "$PELEVATION"                // eDXF_$PELEVATION
  ,   "$PEXTMAX"                   // eDXF_$PEXTMAX
  ,   "$PEXTMIN"                   // eDXF_$PEXTMIN
  ,   "$PINSBASE"                  // eDXF_$PINSBASE
  ,   "$PLIMCHECK"                 // eDXF_$PLIMCHECK
  ,   "$PLIMMAX"                   // eDXF_$PLIMMAX
  ,   "$PLIMMIN"                   // eDXF_$PLIMMIN
  ,   "$PLINEGEN"                  // eDXF_$PLINEGEN
  ,   "$PLINEWID"                  // eDXF_$PLINEWID
  ,   "$PROJECTNAME"               // eDXF_$PROJECTNAME
  ,   "$PROXYGRAPHICS"             // eDXF_$PROXYGRAPHICS
  ,   "$PSLTSCALE"                 // eDXF_$PSLTSCALE
  ,   "$PSTYLEMODE"                // eDXF_$PSTYLEMODE
  ,   "$PSVPSCALE"                 // eDXF_$PSVPSCALE
  ,   "$PUCSBASE"                  // eDXF_$PUCSBASE
  ,   "$PUCSNAME"                  // eDXF_$PUCSNAME
  ,   "$PUCSORG"                   // eDXF_$PUCSORG
  ,   "$PUCSORGBACK"               // eDXF_$PUCSORGBACK
  ,   "$PUCSORGBOTTOM"             // eDXF_$PUCSORGBOTTOM
  ,   "$PUCSORGFRONT"              // eDXF_$PUCSORGFRONT
  ,   "$PUCSORGLEFT"               // eDXF_$PUCSORGLEFT
  ,   "$PUCSORGRIGHT"              // eDXF_$PUCSORGRIGHT
  ,   "$PUCSORGTOP"                // eDXF_$PUCSORGTOP
  ,   "$PUCSORTHOREF"              // eDXF_$PUCSORTHOREF
  ,   "$PUCSORTHOVIEW"             // eDXF_$PUCSORTHOVIEW
  ,   "$PUCSXDIR"                  // eDXF_$PUCSXDIR
  ,   "$PUCSYDIR"                  // eDXF_$PUCSYDIR
  ,   "$QTEXTMODE"                 // eDXF_$QTEXTMODE
  ,   "$REGENMODE"                 // eDXF_$REGENMODE
  ,   "$SHADEDGE"                  // eDXF_$SHADEDGE
  ,   "$SHADEDIF"                  // eDXF_$SHADEDIF
  ,   "$SHADOWPLANELOCATION"       // eDXF_$SHADOWPLANELOCATION
  ,   "$SKETCHINC"                 // eDXF_$SKETCHINC
  ,   "$SKPOLY"                    // eDXF_$SKPOLY
  ,   "$SORTENTS"                  // eDXF_$SORTENTS
  ,   "$SPLFRAME"                  // eDXF_$SPLFRAME
  ,   "$SPLINESEGS"                // eDXF_$SPLINESEGS
  ,   "$SPLINETYPE"                // eDXF_$SPLINETYPE
  ,   "$SURFTAB1"                  // eDXF_$SURFTAB1
  ,   "$SURFTAB2"                  // eDXF_$SURFTAB2
  ,   "$SURFTYPE"                  // eDXF_$SURFTYPE
  ,   "$SURFU"                     // eDXF_$SURFU
  ,   "$SURFV"                     // eDXF_$SURFV
  ,   "$TDCREATE"                  // eDXF_$TDCREATE
  ,   "$TDINDWG"                   // eDXF_$TDINDWG
  ,   "$TDUCREATE"                 // eDXF_$TDUCREATE
  ,   "$TDUPDATE"                  // eDXF_$TDUPDATE
  ,   "$TDUSRTIMER"                // eDXF_$TDUSRTIMER
  ,   "$TDUUPDATE"                 // eDXF_$TDUUPDATE
  ,   "$TEXTSIZE"                  // eDXF_$TEXTSIZE
  ,   "$TEXTSTYLE"                 // eDXF_$TEXTSTYLE
  ,   "$THICKNESS"                 // eDXF_$THICKNESS
  ,   "$TILEMODE"                  // eDXF_$TILEMODE
  ,   "$TRACEWID"                  // eDXF_$TRACEWID
  ,   "$TREEDEPTH"                 // eDXF_$TREEDEPTH
  ,   "$UCSBASE"                   // eDXF_$UCSBASE
  ,   "$UCSNAME"                   // eDXF_$UCSNAME
  ,   "$UCSORG"                    // eDXF_$UCSORG
  ,   "$UCSORGBACK"                // eDXF_$UCSORGBACK
  ,   "$UCSORGBOTTOM"              // eDXF_$UCSORGBOTTOM
  ,   "$UCSORGFRONT"               // eDXF_$UCSORGFRONT
  ,   "$UCSORGLEFT"                // eDXF_$UCSORGLEFT
  ,   "$UCSORGRIGHT"               // eDXF_$UCSORGRIGHT
  ,   "$UCSORGTOP"                 // eDXF_$UCSORGTOP
  ,   "$UCSORTHOREF"               // eDXF_$UCSORTHOREF
  ,   "$UCSORTHOVIEW"              // eDXF_$UCSORTHOVIEW
  ,   "$UCSXDIR"                   // eDXF_$UCSXDIR
  ,   "$UCSYDIR"                   // eDXF_$UCSYDIR
  ,   "$UNITMODE"                  // eDXF_$UNITMODE
  ,   "$USERI1"                    // eDXF_$USERI1
  ,   "$USERI2"                    // eDXF_$USERI2
  ,   "$USERI3"                    // eDXF_$USERI3
  ,   "$USERI4"                    // eDXF_$USERI4
  ,   "$USERI5"                    // eDXF_$USERI5
  ,   "$USERR1"                    // eDXF_$USERR1
  ,   "$USERR2"                    // eDXF_$USERR2
  ,   "$USERR3"                    // eDXF_$USERR3
  ,   "$USERR4"                    // eDXF_$USERR4
  ,   "$USERR5"                    // eDXF_$USERR5
  ,   "$USRTIMER"                  // eDXF_$USRTIMER
  ,   "$VERSIONGUID"               // eDXF_$VERSIONGUID
  ,   "$VISRETAIN"                 // eDXF_$VISRETAIN
  ,   "$WORLDVIEW"                 // eDXF_$WORLDVIEW
  ,   "$XCLIPFRAME"                // eDXF_$XCLIPFRAME
  ,   "$XEDIT"                     // eDXF_$XEDIT
  , "CLASSES"                      // eDXF_CLASSES
  ,   "CLASS"                      // eDXF_CLASS
  , "TABLES"                       // eDXF_TABLES
  ,   "TABLE"                      // eDXF_TABLE
  ,     "APPID"                    // eDXF_APPID
  ,     "BLOCKRECORD"              // eDXF_BLOCKRECORD
  ,     "DIMSTYLE"                 // eDXF_DIMSTYLE
  ,     "LAYER"                    // eDXF_LAYER
  ,     "LTYPE"                    // eDXF_LTYPE
  ,     "STYLE"                    // eDXF_STYLE
  ,     "UCS"                      // eDXF_UCS
  ,     "VIEW"                     // eDXF_VIEW
  ,     "VPORT"                    // eDXF_VPORT
  ,       "$FASTZOOM"              // eDXF_$FASTZOOM
  ,       "$GRIDMODE"              // eDXF_$GRIDMODE
  ,       "$GRIDUNIT"              // eDXF_$GRIDUNIT
  ,       "$SNAPANG"               // eDXF_$SNAPANG
  ,       "$SNAPBASE"              // eDXF_$SNAPBASE
  ,       "$SNAPISOPAIR"           // eDXF_$SNAPISOPAIR
  ,       "$SNAPMODE"              // eDXF_$SNAPMODE
  ,       "$SNAPSTYLE"             // eDXF_$SNAPSTYLE
  ,       "$SNAPUNIT"              // eDXF_$SNAPUNIT
  ,       "$VIEWCTR"               // eDXF_$VIEWCTR
  ,       "$VIEWDIR"               // eDXF_$VIEWDIR
  ,       "$VIEWSIZE"              // eDXF_$VIEWSIZE
  ,   "ENDTAB"                     // eDXF_ENDTAB
  , "BLOCKS"                       // eDXF_BLOCKS     -> DATA SECTION
  ,   "BLOCK"                      // eDXF_BLOCK
  ,   "ENDBLK"                     // eDXF_ENDBLK
  , "ENTITIES"                     // eDXF_ENTITIES   -> OBJECT TYPES
  ,   "3DFACE"                     // eDXF_3DFACE
  ,   "3DSOLID"                    // eDXF_3DSOLID
  ,   "ACAD_PROXY_ENTITY"          // eDXF_ACAD_PROXY_ENTITY
  ,   "ARC"                        // eDXF_ARC
  ,   "ATTDEF"                     // eDXF_ATTDEF
  ,   "ATTRIB"                     // eDXF_ATTRIB
  ,   "BODY"                       // eDXF_BODY
  ,   "CIRCLE"                     // eDXF_CIRCLE
  ,   "DIMENSION"                  // eDXF_DIMENSION
  ,   "ELLIPSE"                    // eDXF_ELLIPSE
  ,   "HATCH"                      // eDXF_HATCH
  ,   "HELIX"                      // eDXF_HELIX
  ,   "IMAGE"                      // eDXF_IMAGE
  ,   "INSERT"                     // eDXF_INSERT
  ,   "LEADER"                     // eDXF_LEADER
  ,   "LIGHT"                      // eDXF_LIGHT
  ,   "LINE"                       // eDXF_LINE
  ,   "LWPOLYLINE"                 // eDXF_LWPOLYLINE
  ,   "MLINE"                      // eDXF_MLINE
  ,   "MTEXT"                      // eDXF_MTEXT
  ,   "OLEFRAME"                   // eDXF_OLEFRAME
  ,   "OLE2FRAME"                  // eDXF_OLE2FRAME
  ,   "POINT"                      // eDXF_POINT
  ,   "POLYLINE"                   // eDXF_POLYLINE
  ,   "RAY"                        // eDXF_RAY
  ,   "REGION"                     // eDXF_REGION
//  ,   "SECTION"                    // eDXF_SECTION
  ,   "SEQEND"                     // eDXF_SEQEND
  ,   "SHAPE"                      // eDXF_SHAPE
  ,   "SOLID"                      // eDXF_SOLID
  ,   "SPLINE"                     // eDXF_SPLINE
  ,   "SUN"                        // eDXF_SUN
  ,   "SURFACE"                    // eDXF_SURFACE
//  ,   "TABLE"                      // eDXF_TABLE
  ,   "TEXT"                       // eDXF_TEXT
  ,   "TOLERANCE"                  // eDXF_TOLERANCE
  ,   "TRACE"                      // eDXF_TRACE
  ,   "UNDERLAY"                   // eDXF_UNDERLAY
  ,   "VERTEX"                     // eDXF_VERTEX
  ,   "VIEWPORT"                   // eDXF_VIEWPORT
  ,   "WIPEOUT"                    // eDXF_WIPEOUT
  ,   "XLINE"                      // eDXF_XLINE
  ,   "ENDSEC"                     // eDXF_ENDSEC
  , "OBJECT"                       // eDXF_OBJECT
  ,   "ACAD_PROXY_OBJECT"          // eDXF_ACAD_PROXY_OBJECT
  ,   "ACDBDICTIONARYWDFLT"        // eDXF_ACDBDICTIONARYWDFLT
  ,   "ACDBPLACEHOLDER"            // eDXF_ACDBPLACEHOLDER
  ,   "DATATABLE"                  // eDXF_DATATABLE
  ,   "DICTIONARY"                 // eDXF_DICTIONARY
  ,   "DICTIONARYVAR"              // eDXF_DICTIONARYVAR
  ,   "DIMASSOC"                   // eDXF_DIMASSOC
  ,   "FIELD"                      // eDXF_FIELD
  ,   "GROUP"                      // eDXF_GROUP
  ,   "IDBUFFER"                   // eDXF_IDBUFFER
  ,   "IMAGEDEF"                   // eDXF_IMAGEDEF
  ,   "IMAGEDEF_REACTOR"           // eDXF_IMAGEDEF_REACTOR
  ,   "LAYER_INDEX"                // eDXF_LAYER_INDEX
  ,   "LAYER_FILTER"               // eDXF_LAYER_FILTER
  ,   "LAYOUT"                     // eDXF_LAYOUT
  ,   "LIGHTLIST"                  // eDXF_LIGHTLIST
  ,   "MATERIAL"                   // eDXF_MATERIAL
  ,   "MLINESTYLE"                 // eDXF_MLINESTYLE
  ,   "OBJECT_PTR"                 // eDXF_OBJECT_PTR
  ,   "PLOTSETTINGS"               // eDXF_PLOTSETTINGS
  ,   "RASTERVARIABLES"            // eDXF_RASTERVARIABLES
  ,   "RENDER"                     // eDXF_RENDER
  ,   "RENDERENVIRONMENT"          // eDXF_RENDERENVIRONMENT
  ,   "METALRAYRENDEREINGSETTINGS" // eDXF_METALRAYRENDEREINGSETTINGS
  ,   "RENDERGLOBAL"               // eDXF_RENDERGLOBAL
//  ,   "SECTION"                    // eDXF_SECTION
  ,   "SPATIAL_INDEX"              // eDXF_SPATIAL_INDEX
  ,   "SPATIAL_FILTER"             // eDXF_SPATIAL_FILTER
  ,   "SORTENTSTABLE"              // eDXF_SORTENTSTABLE
  ,   "SUNSTUDY"                   // eDXF_SUNSTUDY
  ,   "TABLESTYLE"                 // eDXF_TABLESTYLE
  ,   "UNDERLAYDEFINITION"         // eDXF_UNDERLAYDEFINITION
  ,   "VISUALSTYLE"                // eDXF_VISUALSTYLE
  ,   "VBA_PROJECT"                // eDXF_VBA_PROJECT
  ,   "WIPEOUTVARIABLES"           // eDXF_WIPEOUTVARIABLES
  ,   "XRECORD"                    // eDXF_XRECORD
  , "THUMBNAILIMAGE"               // eDXF_THUMBNAILIMAGE
  , "EOF"                          // eDXF_EOF
  };

#ifdef _DEBUG
  // Si ça plante là, c'est qu'il y a plus d'enum eDXF que d'entrée au tableau de HASH
  ASSERT((sizeof(l_panHashTable) / sizeof(char*)) == eDXF__END);
#endif // _DEBUG

  m_oStrFileExtObjects  = ".dxf";
  m_oStrFileExtDataBase = ""; // Pas de base de donnée (bah oui, c'est comme ça, c'est dur la vie)

  mp_oasArrayHash.CreateBuffer(4, eDXF__END + 1); // On range les hash

  for
  ( l_nLoop  = 0
  ; l_nLoop <  eDXF__END
  ; l_nLoop += 1
  )
  {
    mp_anHashTable[l_nLoop] = SHASH(l_panHashTable[l_nLoop]);
    mp_oasArrayHash.AddNode(&mp_anHashTable[l_nLoop], mp_anHashTable[l_nLoop]); // Arbre binaire pour une recherche rapide
  }

  if(i_bCreateOwnContainer == TRUE)
  {
    return CreateContainer();
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
BOOL CSigAutoCad::_IsHashed
( int     i_nIndex
, XString i_poStrHash
)
{
  if(i_poStrHash.IsEmpty() == TRUE)
  {
    return (mp_anHashTable[i_nIndex] == m_nHashed); // précédent chargement de line
  }
  else
  {
    return (mp_anHashTable[i_nIndex] == SHASH(i_poStrHash));
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
BOOL CSigAutoCad::_IsHashed
( int i_nIndex
, int i_nHashed
)
{
  return (mp_anHashTable[i_nIndex] == i_nHashed);
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
BOOL CSigAutoCad::FileLoad
( char*          i_panStringFile
, CSkinProgress* i_poSkinProgress // = NULL
)
{
  if(m_poSigContainer == NULL)
  {
    CreateContainer();
  }
  else{}

  FileSelect(i_panStringFile);

  return FileLoad(i_poSkinProgress);
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
BOOL CSigAutoCad::FileLoad
( CSigContainer* i_poSigContainer
, CSkinProgress* i_poSkinProgress // = NULL
)
{
  CSigContainer* l_poSigPreviousContainer = m_poSigContainer;
  BOOL           l_bResult;

  if(i_poSigContainer != NULL)
  {
    m_poSigContainer = i_poSigContainer;

    l_bResult = FileLoad(i_poSkinProgress);

    m_poSigContainer = l_poSigPreviousContainer;
  }
  else
  {
    l_bResult = FALSE;
  }

  return l_bResult;
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
BOOL CSigAutoCad::FileLoad
( CSkinProgress* i_poSkinProgress // = NULL
)
{
  XString                 l_oStrObject;
  XString                 l_oStrTempo;

  int                     l_nGroupId;
  eACCS                   l_nSection = (eACCS) -1; // Parent d'Entity
  eACCS                   l_nGroup   = (eACCS) -1; // Type de Section (Group 2)
  eACCS                   l_nObject  = (eACCS) -1; // Objet en cours
  eACCS                   l_nCommand = (eACCS) -1; // Commande (VPORT de HEADER, POLYLINE en attente de VERTEX ou SEQEND)
  eACCS                   l_nEntity  = (eACCS) -1; // L'Entity à traiter

  int                     l_nLoop;
  int                     l_nSize;
  int                     l_nFlag;

  double                  l_nTempo;

  int                     l_nObjOffset;

  int                     l_nAcadFlag;
  XStringArray            l_aoStrAcadData;

  int                     l_nAcadFlagEntity;
  XStringArray            l_aoStrAcadDataEntity;

#ifndef USE_POLYGON
  sCoord                  l_sCoord;
#endif // USE_POLYGON

//  CSigContainer::sSigText l_sSigText;
//  CMemoryTreeRedBlack     l_oasTreeKey("l_oasTreeKey");
  CMemoryTree             l_oasTreeKey("l_oasTreeKey");
  CMemoryStringTree       l_oTreeStringData("l_oTreeStringData");

//  CMemoryTreeRedBlack     l_oasTreeKeyEntity("l_oasTreeKeyEntity");
  CMemoryTree             l_oasTreeKeyEntity("l_oasTreeKeyEntity");
  CMemoryStringTree       l_oTreeStringDataEntity("l_oTreeStringDataEntity");

  CSigPolygon             l_oVertexBuffer("l_oVertexBuffer"); // Pour stocker temporairement les vertex avant de générer un objet complet

  //

#ifdef _DEBUG
  l_oasTreeKey.SetClassName("l_oasTreeKey");
  l_oTreeStringData.SetClassName("l_oTreeStringData");
  l_oVertexBuffer.SetClassName("l_oVertexBuffer");
#endif // _DEBUG

  if(m_poSigContainer != NULL)
  {
    if(*m_oPathSplitter.GetPath() == '\0')
    {
      m_oStrLastError = "Choisissez un fichier à parser avec FileSelect() au préalable...";

      return FALSE;
    }
    else
    {
      l_oasTreeKey.CreateBuffer(4, 32);           // 32 slots, suffisant pour stocker 32 clés par Entitée
      l_oTreeStringData.CreateBuffer(1024);       // 1 KiB, c'est suffisant pour contenir une Entitée à la fois

      l_oasTreeKeyEntity.CreateBuffer(4, 32);     // 32 slots, suffisant pour stocker 32 clés par Entitée
      l_oTreeStringDataEntity.CreateBuffer(1024); // 1 KiB, c'est suffisant pour contenir une Entitée à la fois

      if(FileOpen() == TRUE)
      {
        if(i_poSkinProgress != NULL)
        {
          i_poSkinProgress->SetRange
          ( 0
          , m_poSigFile[CSigContainer::eSigFileId_OBJECTS]->GetSize()
          );
        }
        else{}

        l_nObjOffset = GetPos(CSigContainer::eSigFileId_OBJECTS);

        while
        (
             (m_bStop == FALSE)
          && (LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS, TRUE, ' ', TRUE, TRUE)) // <--- GROUP ID
        )
        {
          l_nGroupId = ATOI(GetElement(0)); // <--- GROUP ID

          // - - - 8< - - - - - - - -
          //   0       <--- GROUP ID
          // CIRCLE    <--- ID NAME (si GROUP ID = 0)
          //   8
          // 0
          //  10
          // 393.049856
          //  20       <--- GROUP ID
          // 152.25    <--- DATA  (si GROUP ID != 0)
          //  30
          // 0
          //  40
          // 1.5
          //   0
          // ARC
          //   8
          // 0
          // - - - 8< - - - - - - - -

          if
          (
                (l_nGroupId == 0) // SECTION / GROUP / BLOCK / ENTITY
            || ((l_nGroupId == 2) && (l_nSection == eDXF_SECTION) && (l_nGroup == eDXF_SECTION)) // NAME (SECTION TYPE)
            || ((l_nGroupId == 9) && (l_nSection == eDXF_SECTION) && (l_nGroup == eDXF_HEADER))  // VARIABLE (HEADER ONLY)
          )
          {
            if
            (
                 (l_nSection >= eDXF_SECTION)
              && (l_nEntity  >= eDXF_$ACADMAINTVER) // Dans le groupe HEADER
            )
            { // Valide la Section ou l'Entitée précédente
              switch(l_nGroup)
              {
                case eDXF_HEADER : // -----------------------------------------
                  switch(l_nEntity)
                  {
                    case eDXF_$ACADMAINTVER :
                      break;
                    case eDXF_$ACADVER :
                      break;
                    case eDXF_$ANGBASE :
                      break;
                    case eDXF_$ANGDIR :
                      break;
//                    case eDXF_$ATTDIA :
                    case eDXF_$ATTMODE :
                      break;
//                    case eDXF_$ATTREQ :
                    case eDXF_$AUNITS :
                      break;
                    case eDXF_$AUPREC :
                      break;
//                    case eDXF_$AXISMODE :
//                    case eDXF_$AXISUNIT :
//                    case eDXF_$BLIPMODE :
                    case eDXF_$CECOLOR :
                      break;
                    case eDXF_$CELTSCALE :
                      break;
                    case eDXF_$CELTYPE :
                      break;
                    case eDXF_$CELWEIGHT :
                      break;
                    case eDXF_$CEPSNID :
                      break;
                    case eDXF_$CEPSNTYPE :
                      break;
                    case eDXF_$CHAMFERA :
                      break;
                    case eDXF_$CHAMFERB :
                      break;
                    case eDXF_$CHAMFERC :
                      break;
                    case eDXF_$CHAMFERD :
                      break;
                    case eDXF_$CLAYER :
                      break;
                    case eDXF_$CMLJUST :
                      break;
                    case eDXF_$CMLSCALE :
                      break;
                    case eDXF_$CMLSTYLE :
                      break;
                    case eDXF_$CSHADOW :
                      break;
//                    case eDXF_$COORDS :
                    case eDXF_$DIMADEC :
                      break;
                    case eDXF_$DIMALT :
                      break;
                    case eDXF_$DIMALTD :
                      break;
                    case eDXF_$DIMALTF :
                      break;
                    case eDXF_$DIMALTRND :
                      break;
                    case eDXF_$DIMALTTD :
                      break;
                    case eDXF_$DIMALTTZ :
                      break;
                    case eDXF_$DIMALTU :
                      break;
                    case eDXF_$DIMALTZ :
                      break;
                    case eDXF_$DIMAPOST :
                      break;
                    case eDXF_$DIMASO :
                      break;
                    case eDXF_$DIMASSOC :
                      break;
                    case eDXF_$DIMASZ :
                      break;
                    case eDXF_$DIMATFIT :
                      break;
                    case eDXF_$DIMAUNIT :
                      break;
                    case eDXF_$DIMAZIN :
                      break;
                    case eDXF_$DIMBLK :
                      break;
                    case eDXF_$DIMBLK1 :
                      break;
                    case eDXF_$DIMBLK2 :
                      break;
                    case eDXF_$DIMCEN :
                      break;
                    case eDXF_$DIMCLRD :
                      break;
                    case eDXF_$DIMCLRE :
                      break;
                    case eDXF_$DIMCLRT :
                      break;
                    case eDXF_$DIMDEC :
                      break;
                    case eDXF_$DIMDLE :
                      break;
                    case eDXF_$DIMDLI :
                      break;
                    case eDXF_$DIMDSEP :
                      break;
                    case eDXF_$DIMEXE :
                      break;
                    case eDXF_$DIMEXO :
                      break;
                    case eDXF_$DIMFAC :
                      break;
                    case eDXF_$DIMGAP :
                      break;
                    case eDXF_$DIMJUST :
                      break;
                    case eDXF_$DIMLDRBLK :
                      break;
                    case eDXF_$DIMLFAC :
                      break;
                    case eDXF_$DIMLIM :
                      break;
                    case eDXF_$DIMLUNIT :
                      break;
                    case eDXF_$DIMLWD :
                      break;
                    case eDXF_$DIMLWE :
                      break;
                    case eDXF_$DIMPOST :
                      break;
                    case eDXF_$DIMRND :
                      break;
                    case eDXF_$DIMSAH :
                      break;
                    case eDXF_$DIMSCALE :
                      break;
                    case eDXF_$DIMSD1 :
                      break;
                    case eDXF_$DIMSD2 :
                      break;
                    case eDXF_$DIMSE1 :
                      break;
                    case eDXF_$DIMSE2 :
                      break;
                    case eDXF_$DIMSHO :
                      break;
                    case eDXF_$DIMSOXD :
                      break;
                    case eDXF_$DIMSTYLE :
                      break;
                    case eDXF_$DIMTAD :
                      break;
                    case eDXF_$DIMTDEC :
                      break;
                    case eDXF_$DIMTFAC :
                      break;
                    case eDXF_$DIMTIH :
                      break;
                    case eDXF_$DIMTIX :
                      break;
                    case eDXF_$DIMTM :
                      break;
                    case eDXF_$DIMTMOVE :
                      break;
                    case eDXF_$DIMTOFL :
                      break;
                    case eDXF_$DIMTOH :
                      break;
                    case eDXF_$DIMTOL :
                      break;
                    case eDXF_$DIMTOLJ :
                      break;
                    case eDXF_$DIMTP :
                      break;
                    case eDXF_$DIMTSZ :
                      break;
                    case eDXF_$DIMTVP :
                      break;
                    case eDXF_$DIMTXSTY :
                      break;
                    case eDXF_$DIMTXT :
                      break;
                    case eDXF_$DIMTZIN :
                      break;
                    case eDXF_$DIMUPT :
                      break;
                    case eDXF_$DIMZIN :
                      break;
                    case eDXF_$DISPSILH :
                      break;
//                    case eDXF_$DRAGMODE :
                    case eDXF_$DRAGVS :
                      break;
                    case eDXF_$DWGCODEPAGE :
                      break;
                    case eDXF_$ELEVATION :
                      break;
                    case eDXF_$ENDCAPS :
                      break;
                    case eDXF_$EXTMAX :
                      break;
                    case eDXF_$EXTMIN :
                      break;
                    case eDXF_$EXTNAMES :
                      break;
                    case eDXF_$FILLETRAD :
                      break;
                    case eDXF_$FILLMODE :
                      break;
                    case eDXF_$FINGERPRINTGUID :
                      break;
//                    case eDXF_$FLATLAND :
                    case eDXF_$HALOGAP :
                      break;
//                    case eDXF_$HANDLING :
                    case eDXF_$HANDSEED :
                      break;
                    case eDXF_$HIDETEXT :
                      break;
                    case eDXF_$HYPERLINKBASE :
                      break;
                    case eDXF_$INDEXCTL :
                      break;
                    case eDXF_$INSBASE :
                      break;
                    case eDXF_$INSUNITS :
                      break;
                    case eDXF_$INTERFERECOLOR :
                      break;
                    case eDXF_$INTERFEREOBJVS :
                      break;
                    case eDXF_$INTERFEREVPVS :
                      break;
                    case eDXF_$INTERSECTIONCOLOR :
                      break;
                    case eDXF_$INTERSECTIONDISPLAY :
                      break;
                    case eDXF_$JOINSTYLE :
                      break;
                    case eDXF_$LIMCHECK :
                      break;
                    case eDXF_$LIMMAX :
                      break;
                    case eDXF_$LIMMIN :
                      break;
                    case eDXF_$LTSCALE :
                      break;
                    case eDXF_$LUNITS :
                      break;
                    case eDXF_$LUPREC :
                      break;
                      break;
                    case eDXF_$LWDISPLAY :
                      break;
                    case eDXF_$MAXACTVP :
                      break;
                    case eDXF_$MEASUREMENT :
                      break;
                    case eDXF_$MENU :
                      break;
                    case eDXF_$MIRRTEXT :
                      break;
                    case eDXF_$OBSCOLOR :
                      break;
                    case eDXF_$OBSLTYPE :
                      break;
                    case eDXF_$ORTHOMODE :
                      break;
//                    case eDXF_$OSMODE :
                    case eDXF_$PDMODE :
                      break;
                    case eDXF_$PDSIZE :
                      break;
                    case eDXF_$PELEVATION :
                      break;
                    case eDXF_$PEXTMAX :
                      break;
                    case eDXF_$PEXTMIN :
                      break;
                    case eDXF_$PINSBASE :
                      break;
                    case eDXF_$PLIMCHECK :
                      break;
                    case eDXF_$PLIMMAX :
                      break;
                    case eDXF_$PLIMMIN :
                      break;
                    case eDXF_$PLINEGEN :
                      break;
                    case eDXF_$PLINEWID :
                      break;
                    case eDXF_$PROJECTNAME :
                      break;
                    case eDXF_$PROXYGRAPHICS :
                      break;
                    case eDXF_$PSLTSCALE :
                      break;
                    case eDXF_$PSTYLEMODE :
                      break;
                    case eDXF_$PSVPSCALE :
                      break;
                    case eDXF_$PUCSBASE :
                      break;
                    case eDXF_$PUCSNAME :
                      break;
                    case eDXF_$PUCSORG :
                      break;
                    case eDXF_$PUCSORGBACK :
                      break;
                    case eDXF_$PUCSORGBOTTOM :
                      break;
                    case eDXF_$PUCSORGFRONT :
                      break;
                    case eDXF_$PUCSORGLEFT :
                      break;
                    case eDXF_$PUCSORGRIGHT :
                      break;
                    case eDXF_$PUCSORGTOP :
                      break;
                    case eDXF_$PUCSORTHOREF :
                      break;
                    case eDXF_$PUCSORTHOVIEW :
                      break;
                    case eDXF_$PUCSXDIR :
                      break;
                    case eDXF_$PUCSYDIR :
                      break;
                    case eDXF_$QTEXTMODE :
                      break;
                    case eDXF_$REGENMODE :
                      break;
                    case eDXF_$SHADEDGE :
                      break;
                    case eDXF_$SHADEDIF :
                      break;
                    case eDXF_$SHADOWPLANELOCATION :
                      break;
                    case eDXF_$SKETCHINC :
                      break;
                    case eDXF_$SKPOLY :
                      break;
                    case eDXF_$SORTENTS :
                      break;
                    case eDXF_$SPLFRAME :
                      break;
                    case eDXF_$SPLINESEGS :
                      break;
                    case eDXF_$SPLINETYPE :
                      break;
                    case eDXF_$SURFTAB1 :
                      break;
                    case eDXF_$SURFTAB2 :
                      break;
                    case eDXF_$SURFTYPE :
                      break;
                    case eDXF_$SURFU :
                      break;
                    case eDXF_$SURFV :
                      break;
                    case eDXF_$TDCREATE :
                      break;
                    case eDXF_$TDINDWG :
                      break;
                    case eDXF_$TDUCREATE :
                      break;
                    case eDXF_$TDUPDATE :
                      break;
                    case eDXF_$TDUSRTIMER :
                      break;
                    case eDXF_$TDUUPDATE :
                      break;
                    case eDXF_$TEXTSIZE :
                      break;
                    case eDXF_$TEXTSTYLE :
                      break;
                    case eDXF_$THICKNESS :
                      break;
                    case eDXF_$TILEMODE :
                      break;
                    case eDXF_$TRACEWID :
                      break;
                    case eDXF_$TREEDEPTH :
                      break;
                    case eDXF_$UCSBASE :
                      break;
                    case eDXF_$UCSNAME :
                      break;
                    case eDXF_$UCSORG :
                      break;
                    case eDXF_$UCSORGBACK :
                      break;
                    case eDXF_$UCSORGBOTTOM :
                      break;
                    case eDXF_$UCSORGFRONT :
                      break;
                    case eDXF_$UCSORGLEFT :
                      break;
                    case eDXF_$UCSORGRIGHT :
                      break;
                    case eDXF_$UCSORGTOP :
                      break;
                    case eDXF_$UCSORTHOREF :
                      break;
                    case eDXF_$UCSORTHOVIEW :
                      break;
                    case eDXF_$UCSXDIR :
                      break;
                    case eDXF_$UCSYDIR :
                      break;
                    case eDXF_$UNITMODE :
                      break;
                    case eDXF_$USERI1 :
                      break;
                    case eDXF_$USERI2 :
                      break;
                    case eDXF_$USERI3 :
                      break;
                    case eDXF_$USERI4 :
                      break;
                    case eDXF_$USERI5 :
                      break;
                    case eDXF_$USERR1 :
                      break;
                    case eDXF_$USERR2 :
                      break;
                    case eDXF_$USERR3 :
                      break;
                    case eDXF_$USERR4 :
                      break;
                    case eDXF_$USERR5 :
                      break;
                    case eDXF_$USRTIMER :
                      break;
                    case eDXF_$VERSIONGUID :
                      break;
                    case eDXF_$VISRETAIN :
                      break;
                    case eDXF_$WORLDVIEW :
                      break;
                    case eDXF_$XCLIPFRAME :
                      break;
                    case eDXF_$XEDIT :
                      break;
                    default :
                      break;
                  }
                  break;
                case eDXF_CLASSES : // ----------------------------------------
                  switch(l_nEntity)
                  {
                    case eDXF_CLASS :
                      break;
                    default :
                      break;
                  }
                  break;
                case eDXF_TABLES : // -----------------------------------------
                  switch(l_nCommand)
                  {
                    case eDXF_VPORT :
                      switch(l_nEntity)
                      {
                        case eDXF_$FASTZOOM :
                          break;
                        case eDXF_$GRIDMODE :
                          break;
                        case eDXF_$GRIDUNIT :
                          break;
                        case eDXF_$SNAPANG :
                          break;
                        case eDXF_$SNAPBASE :
                          break;
                        case eDXF_$SNAPISOPAIR :
                          break;
                        case eDXF_$SNAPMODE :
                          break;
                        case eDXF_$SNAPSTYLE :
                          break;
                        case eDXF_$SNAPUNIT :
                          break;
                        case eDXF_$VIEWCTR :
                          break;
                        case eDXF_$VIEWDIR :
                          break;
                        case eDXF_$VIEWSIZE :
                          break;
                        default :
                          break;
                      }
                      break;
                    default :
                      switch(l_nEntity)
                      {
                        case eDXF_APPID :
                          break;
                        case eDXF_BLOCKRECORD :
                          break;
                        case eDXF_DIMSTYLE :
                          break;
                        case eDXF_LAYER :
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                          m_poSigContainer->AddLayer(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2))));
// MODIF_KOCH 070328
                          break;
                        case eDXF_LTYPE :
                          break;
                        case eDXF_STYLE :
                          break;
                        case eDXF_UCS :
                          break;
                        case eDXF_VIEW :
                          break;
                        case eDXF_VPORT :
                          break;
                        default :
                          break;
                      }
                      break;
                  }
                  break;
                case eDXF_BLOCKS : // -----------------------------------------
                  switch(l_nEntity)
                  {
                    case eDXF_BLOCK :
                      // On garde le nom du bloc que l'on réinjectera ensuite comme nom d'Entity (-> 2)
                      m_bBlockMode = TRUE; // Block SANS PARENT, et avec Nom enregistré

                      AddObject
                      ( CSigContainer::eOBJTYP_BLOCK
                      , 1 // Un seul objet, pour l'instant on ne connais pas le nombre exact d'enfants
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      m_bBlockMode = FALSE; // Container, référencés d'après le Block inséré
                      break;
                    case eDXF_ENDBLK :
                      EndObject(CSigContainer::eOBJTYP_BLOCK);
                      break;
                    default :
                      break;
                  }
//                PAS DE BREAK, ON CONTINUE DANS LA SECTION ENTITIES
                case eDXF_ENTITIES : // ---------------------------------------
                  switch(l_nEntity)
                  {
                    case eDXF_3DFACE :
                      break;
                    case eDXF_3DSOLID :
                      break;
                    case eDXF_ACAD_PROXY_ENTITY :
                      break;
                    case eDXF_ARC :
                      AddObject
                      ( CSigContainer::eOBJTYP_ARC
                      , 0
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      l_nTempo = ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(40)))); // Rayon

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) - l_nTempo // X1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) - l_nTempo // Y1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))))            // Z1
                      );

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) + l_nTempo // X2
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) + l_nTempo // Y2
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))))            // Z2
                      );

                      AddPoint
                      ( l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(50))) // Angle départ A
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(51))) // Angle de fin B
                      );
                      break;
                    case eDXF_ATTDEF :
                      break;
                    case eDXF_ATTRIB :
                      // On traitera le ATTRIB dans SEQEND
                      break;
                    case eDXF_BODY :
                      break;
                    case eDXF_CIRCLE :
                      AddObject
                      ( CSigContainer::eOBJTYP_ELLIPSE
                      , 0
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      l_nTempo = ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(40)))); // Rayon

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) - l_nTempo // X1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) - l_nTempo // Y1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))))            // Z1
                      );

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) + l_nTempo // X2
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) + l_nTempo // Y2
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))))            // Z2
                      );

                      break;
                    case eDXF_DIMENSION :
                      break;
//                    case eDXF_ENDSEC : // Fin de Section, on ne traite pas ce cas ici
                    case eDXF_ELLIPSE :
                      AddObject
                      ( CSigContainer::eOBJTYP_ARC
                      , 0
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      l_nTempo = ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(40)))); // Rapport

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) - l_nTempo // X1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) - l_nTempo // Y1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))))            // Z1
                      );

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(11)))) + l_nTempo // X2
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(21)))) + l_nTempo // Y2
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(31))))            // Z2
                      );

                      AddPoint
                      ( l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(41))) // Angle départ A
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(42))) // Angle de fin B
                      );
                      break;
                    case eDXF_HATCH :
                      break;
                    case eDXF_HELIX :
                      break;
                    case eDXF_IMAGE :
                      break;
                    case eDXF_INSERT :
                      // Copie un objet de la banque Blocks
#ifdef USE_POLYGON
                      m_poSigContainer->CopyFromBlock
                      (      l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) // X1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) // Y1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30)))) // Z1
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support de la rotation et homothétie d'un bloc
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(50)))) // Rot
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(41)))) // SX
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(42)))) // SY
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(43)))) // SZ
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      ,      l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );
#endif // USE_POLYGON
                      break;
                    case eDXF_LEADER :
                      break;
                    case eDXF_LIGHT :
                      break;
                    case eDXF_LINE :
                      AddObject
                      ( CSigContainer::eOBJTYP_LINE
                      , 0
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      AddPoint
                      ( l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10))) // X1
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20))) // Y1
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))) // Z1
                      );

                      AddPoint
                      ( l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(11))) // X2
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(21))) // Y2
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(31))) // Z2
                      );
                      break;
                    case eDXF_LWPOLYLINE :
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Gestion de l'objet LWPOLYLINE
                      l_nSize = l_oVertexBuffer.GetSize();
                      l_nFlag = ATOI(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(70)))) & 1;

                      if(l_nSize > 0)
                      {
                        AddObject
                        ( CSigContainer::eOBJTYP_POLYLINE
                        , l_nSize + l_nFlag
                        , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                        , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
                        );

                        for
                        ( l_nLoop  = 0
                        ; l_nLoop <  l_nSize
                        ; l_nLoop += 1
                        )
                        { // Ajoute le point avec casting sur 'sSigPoint'
#ifndef USE_POLYGON
                          l_sCoord.nLonX = l_oVertexBuffer[l_nLoop].nLonX;
                          l_sCoord.nLatY = l_oVertexBuffer[l_nLoop].nLatY;
                          l_sCoord.nAltZ = l_oVertexBuffer[l_nLoop].nAltZ;

                          m_poSigContainer->AddPoint(&l_sCoord);
#else // USE_POLYGON
                          m_poSigContainer->AddPoint(&l_oVertexBuffer[l_nLoop]);
#endif // USE_POLYGON
                        }

                        if(l_nFlag != 0)
                        { // Si c'est un Polygone fermé, on boucle
#ifndef USE_POLYGON
                          l_sCoord.nLonX = l_oVertexBuffer[0].nLonX;
                          l_sCoord.nLatY = l_oVertexBuffer[0].nLatY;
                          l_sCoord.nAltZ = l_oVertexBuffer[0].nAltZ;

                          m_poSigContainer->AddPoint(&l_sCoord);
#else // USE_POLYGON
                          m_poSigContainer->AddPoint(&l_oVertexBuffer[0]);
#endif // USE_POLYGON
                        }
                      }
                      else{}
// MODIF_KOCH 070328
                      break;
                    case eDXF_MLINE :
                      break;
                    case eDXF_MTEXT :
                      break;
                    case eDXF_OLEFRAME :
                      break;
                    case eDXF_OLE2FRAME :
                      break;
                    case eDXF_POINT :
                      AddObject
                      ( CSigContainer::eOBJTYP_POINT
                      , 0
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      AddPoint
                      ( l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10))) // X
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20))) // Y
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))) // Z
                      );
                      break;
                    case eDXF_POLYLINE :
                      // On traitera le POLYLINE dans SEQEND, mais là il faut sauvegarder temporairement les paramètres qui seront remplacés par ceux des VERTEX
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      l_nLoop = l_oasTreeKey.GetNodeMin();
                      while(l_nLoop != -1)
                      {
// MODIF_KOCH 070328
                        l_nFlag = *((int*) l_oasTreeKey.GetSlotPointer(l_nLoop));

                        l_nSize = l_oTreeStringDataEntity.AddString
                        ( l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_nLoop))
                        , l_nFlag
                        ); // String Data = l_nGroupId

                        l_oasTreeKeyEntity.AddNode
                        ( &l_nFlag
                        , l_nFlag
                        , l_nSize
                        );

// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                        l_nLoop = l_oasTreeKey.GetNodeSuccessor(l_nLoop);
                      }
// MODIF_KOCH 070328

                      l_nAcadFlagEntity = l_nAcadFlag;
                      l_aoStrAcadDataEntity.RemoveAll();
                      l_nAcadFlag = 0; // Annule la section ACAD générale

                      for
                      ( l_nLoop  = 0
                      ; l_nLoop <  l_aoStrAcadData.GetSize()
                      ; l_nLoop += 1
                      )
                      {
                        l_aoStrAcadDataEntity.Add(l_aoStrAcadData.GetAt(l_nLoop));
                      }
                      break;
                    case eDXF_RAY :
                      break;
                    case eDXF_REGION :
                      break;
//                    case eDXF_SECTION : // On traite la Section comme... une Section
//                    case eDXF_SEQEND :  // On traite le SEQEND plus bas, dès que l'on sait que la séquence est finie
                    case eDXF_SHAPE :
                      break;
                    case eDXF_SOLID :
                      break;
                    case eDXF_SPLINE :
                      break;
                    case eDXF_SUN :
                      break;
                    case eDXF_SURFACE :
                      break;
//                    case eDXF_TABLE : // On traite la Table comme un Groupe à part
                    case eDXF_TEXT :
                      CSigContainer::sSigObject* l_psTempoObject;

                      l_psTempoObject = AddObject
                      ( CSigContainer::eOBJTYP_TEXT
                      , 0
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      l_oStrTempo = l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(1))); // textstring
                      l_oStrTempo.Remove('"');

                      if(l_psTempoObject != NULL)
                      {
                        l_psTempoObject->nTextIndex = AddString(l_oStrTempo);
                      }
                      else{}

                      l_nTempo = (double) l_oStrTempo.GetLength();

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) - l_nTempo // X1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) - l_nTempo // Y1
                      , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))))            // Z1
                      );

                      m_poSigContainer->AddPoint // Avec casting sur 'double'
                      ( ATOD
                        (      l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(11)))
                        , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) + l_nTempo
                        ) // X2
                      , ATOD
                        (      l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(21)))
                        , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) + l_nTempo
                        ) // Y2
                      , ATOD
                        (      l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(31)))
                        , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30))))
                        ) // Z2
                      );
                      break;
                    case eDXF_TOLERANCE :
                      break;
                    case eDXF_TRACE :
                      break;
                    case eDXF_UNDERLAY :
                      break;
                    case eDXF_VERTEX :
                      l_oVertexBuffer.Add
                      ( sSigPoint
                        ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) // X
                        , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) // Y
                        , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(30)))) // Z
                        )
                      );
                      break;
                    case eDXF_VIEWPORT :
                      break;
                    case eDXF_WIPEOUT :
                      break;
                    case eDXF_XLINE :
                      break;
                    default :
                      break;
                  }
                  break;
                case eDXF_OBJECT : // -----------------------------------------
                  switch(l_nEntity)
                  {
                    case eDXF_ACAD_PROXY_OBJECT :
                      break;
                    case eDXF_ACDBDICTIONARYWDFLT :
                      break;
                    case eDXF_ACDBPLACEHOLDER :
                      break;
                    case eDXF_DATATABLE :
                      break;
                    case eDXF_DICTIONARY :
                      break;
                    case eDXF_DICTIONARYVAR :
                      break;
                    case eDXF_DIMASSOC :
                      break;
                    case eDXF_FIELD :
                      break;
                    case eDXF_GROUP :
                      break;
                    case eDXF_IDBUFFER :
                      break;
                    case eDXF_IMAGEDEF :
                      break;
                    case eDXF_IMAGEDEF_REACTOR :
                      break;
                    case eDXF_LAYER_INDEX :
                      break;
                    case eDXF_LAYER_FILTER :
                      break;
                    case eDXF_LAYOUT :
                      break;
                    case eDXF_LIGHTLIST :
                      break;
                    case eDXF_MATERIAL :
                      break;
                    case eDXF_MLINESTYLE :
                      break;
                    case eDXF_OBJECT_PTR :
                      break;
                    case eDXF_PLOTSETTINGS :
                      break;
                    case eDXF_RASTERVARIABLES :
                      break;
                    case eDXF_RENDER :
                      break;
                    case eDXF_RENDERENVIRONMENT :
                      break;
                    case eDXF_METALRAYRENDEREINGSETTINGS :
                      break;
                    case eDXF_RENDERGLOBAL :
                      break;
//                    case eDXF_SECTION :
                    case eDXF_SPATIAL_INDEX :
                      break;
                    case eDXF_SPATIAL_FILTER :
                      break;
                    case eDXF_SORTENTSTABLE :
                      break;
                    case eDXF_SUNSTUDY :
                      break;
                    case eDXF_TABLESTYLE :
                      break;
                    case eDXF_UNDERLAYDEFINITION :
                      break;
                    case eDXF_VISUALSTYLE :
                      break;
                    case eDXF_VBA_PROJECT :
                      break;
                    case eDXF_WIPEOUTVARIABLES :
                      break;
                    case eDXF_XRECORD :
                      break;
                    default :
                      break;
                  }
                  break;
                case eDXF_THUMBNAILIMAGE : // ---------------------------------
                  break;
                default : // --------------------------------------------------
                  break;
              }
            }
            else{}

            // Charge la nouvelle Section
            LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS, TRUE, ' ', TRUE, TRUE); // <--- ID NAME (voir schéma plus haut)

            l_nEntity = (eACCS) mp_oasArrayHash.GetNodeIndex(m_nHashed); // Renvoie en principe le eDXF_xxx correspondant (trop facile)

            switch(l_nEntity)
            { // Changement de Section
              case eDXF_SEQEND         : // <--- Termine un Objet en cours
                switch(l_nCommand)
                { // Valide le POLYLINE ou l'ATTRIB en cours
                  case eDXF_ATTRIB :
                  default :
                    break;
                  case eDXF_POLYLINE :
                    // ATTENTION : On récupère les données des banques 'Entity' sauvegardées avant les VERTEX
                    l_nSize = l_oVertexBuffer.GetSize();
                    l_nFlag = ATOI(l_oTreeStringDataEntity.GetStringPointer(l_oasTreeKeyEntity.GetNodeData(l_oasTreeKeyEntity.GetNodeIndex(70)))) & 1;

                    if(l_nSize > 0)
                    {
                      char* l_nTest1 = l_oTreeStringDataEntity.GetStringPointer(l_oasTreeKeyEntity.GetNodeData(l_oasTreeKeyEntity.GetNodeIndex(2)));
                      char* l_nTest2 = l_oTreeStringDataEntity.GetStringPointer(l_oasTreeKeyEntity.GetNodeData(l_oasTreeKeyEntity.GetNodeIndex(8)));

                      AddObject
                      ( CSigContainer::eOBJTYP_POLYLINE
                      , l_nSize + l_nFlag
                      , l_oTreeStringDataEntity.GetStringPointer(l_oasTreeKeyEntity.GetNodeData(l_oasTreeKeyEntity.GetNodeIndex(2)))
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
                      , l_oTreeStringDataEntity.GetStringPointer(l_oasTreeKeyEntity.GetNodeData(l_oasTreeKeyEntity.GetNodeIndex(8)))
// MODIF_KOCH 070328
                      );

                      for
                      ( l_nLoop  = 0
                      ; l_nLoop <  l_nSize
                      ; l_nLoop += 1
                      )
                      { // Ajoute le point avec casting sur 'sSigPoint'
#ifndef USE_POLYGON
                        l_sCoord.nLonX = l_oVertexBuffer[l_nLoop].nLonX;
                        l_sCoord.nLatY = l_oVertexBuffer[l_nLoop].nLatY;
                        l_sCoord.nAltZ = l_oVertexBuffer[l_nLoop].nAltZ;

                        m_poSigContainer->AddPoint(&l_sCoord);
#else // USE_POLYGON
                        m_poSigContainer->AddPoint(&l_oVertexBuffer[l_nLoop]);
#endif // USE_POLYGON
                      }

                      if(l_nFlag != 0)
                      { // Si c'est un Polygone fermé, on boucle
#ifndef USE_POLYGON
                        l_sCoord.nLonX = l_oVertexBuffer[0].nLonX;
                        l_sCoord.nLatY = l_oVertexBuffer[0].nLatY;
                        l_sCoord.nAltZ = l_oVertexBuffer[0].nAltZ;

                        m_poSigContainer->AddPoint(&l_sCoord);
#else // USE_POLYGON
                        m_poSigContainer->AddPoint(&l_oVertexBuffer[0]);
#endif // USE_POLYGON
                      }
                    }
                    else{}

                    l_oasTreeKeyEntity.RemoveNodeAll();
                    l_oTreeStringDataEntity.RemoveStringAll();

                    // Recopie la section ACAD de l'objet en général
                    l_nAcadFlag = l_nAcadFlagEntity;
                    l_aoStrAcadData.RemoveAll();

                    for
                    ( l_nLoop  = 0
                    ; l_nLoop <  l_aoStrAcadDataEntity.GetSize()
                    ; l_nLoop += 1
                    )
                    {
                      l_aoStrAcadData.Add(l_aoStrAcadDataEntity.GetAt(l_nLoop));
                    }

                    // On se débarrasse des données de l'objet
                    l_nAcadFlagEntity = 0;
                    l_aoStrAcadDataEntity.RemoveAll();
                    break;
                } // ATTENTION : On va vider tous les buffers vu que l'on en a plus besoin
              case eDXF_TABLE          : // Démarre une Table
              case eDXF_ENDTAB         : // Termine une Table
              case eDXF_ATTRIB         : 
              case eDXF_POLYLINE       : 
              case eDXF_ENDSEC         : // Termine une Section
              case eDXF_EOF            : // Fin de fichier, on nettoie un peu avant de sortir
              default :
                l_oVertexBuffer.RemoveAll();         // On efface les vertex
              case eDXF_VERTEX         : // <--- Ben oui, tant que l'on recoit des VERTEX, on les gardes jusqu'à SEQEND
                l_oasTreeKey.RemoveNodeAll();        // On efface les clés
                l_oTreeStringData.RemoveStringAll(); // On efface les données

                // Ajoute les données avant de s'en débarraser (ICI A CAUSE DE L'AJOUT DU POLYLINE JUSTE AU-DESSUS)
                if
                (
                     (l_nAcadFlag == 4) // (ACAD_CLOSE)
                  && (l_aoStrAcadData.GetSize() > 0)
                )
                {
                  int l_nAcadLoop;
                  int l_nAcadSize = l_aoStrAcadData.GetSize();

                  if(m_poSigContainer->GetColumnCount() == 0)
                  { // S'il n'y a pas encore d'emplacement réservé pour les colonnes, on prépare ça
                    for
                    ( l_nAcadLoop  = 0
                    ; l_nAcadLoop <  l_nAcadSize
                    ; l_nAcadLoop += 1
                    )
                    { // Ajoute une colonne en CHAR
                      AddColumn
                      ( l_aoStrAcadData[l_nAcadLoop].Left(l_aoStrAcadData[l_nAcadLoop].Find("="))
                      , CSigContainer::eCOLTYP_CHAR
                      , 80 // Suffisement grand, mais inutile puisque non tronqué dans la base
                      );
                    }

                    m_poSigContainer->PrepareColumnStorage(); // On prépare les tableaux pour stocker les données
                  }
                  else{}

                  if(m_poSigContainer->GetColumnCount() != 0)
                  {
                    for
                    ( l_nAcadLoop  = 0
                    ; l_nAcadLoop <  l_nAcadSize
                    ; l_nAcadLoop += 1
                    )
                    { // On supprime le nom des colonnes
                      l_aoStrAcadData[l_nAcadLoop] = l_aoStrAcadData[l_nAcadLoop].Mid(l_aoStrAcadData[l_nAcadLoop].Find("=") + 1);
                    }

                    AddRow(l_aoStrAcadData);
                  }
                  else{}
                }
                else{}

                // On se débarrasse des données
                l_nAcadFlag = 0;
                l_aoStrAcadData.RemoveAll();
              case eDXF_SECTION        : // Démarre une Section ou un Groupe, on a déjà purgé à la fin de Section précédente
              case eDXF_HEADER         : 
              case eDXF_CLASSES        :
              case eDXF_TABLES         :
                break;
              case eDXF_BLOCKS         :
                m_bBlockMode = TRUE; // Block
                break;
              case eDXF_ENTITIES       :
                m_bBlockMode = FALSE; // Container
              case eDXF_OBJECT         :
              case eDXF_THUMBNAILIMAGE :
                break;
            }

            switch(l_nEntity)
            { // Changement de Section
              case eDXF_EOF            : // Fin de fichier, on ne parse pas d'avantage
                m_bStop = TRUE; // On sort du de la boucle de lecture
              case eDXF_SECTION        : // Démarre une Section
                l_nSection = l_nEntity;
              case eDXF_HEADER         :
              case eDXF_CLASSES        :
              case eDXF_TABLES         :
              case eDXF_BLOCKS         : // <--- Section Blocks, contient des objets nommés qui seront streamés avec Insert dans la section Entities
              case eDXF_ENTITIES       :
              case eDXF_OBJECT         :
              case eDXF_THUMBNAILIMAGE :
                l_nGroup = l_nEntity;
              case eDXF_ENDTAB         : // Termine une Table
              case eDXF_ENDSEC         : // Termine une Section
                l_nCommand = (eACCS) -1;
                l_nEntity  = (eACCS) -1; // On ne valide rien au coup suivant, début/fin de Section/Groupe
                break;
              case eDXF_VPORT          : // <- WARNING !!! TRICKY :)
              case eDXF_ATTRIB         :
              case eDXF_POLYLINE       :
              case eDXF_SEQEND         :
                l_nCommand = l_nEntity; // On va traiter un Objet qui se termine par SEQEND
              default :
//                l_nEntity = l_nEntity; // On traitera l'Entity détectée plus haut au tour suivant (surtout si c'est un 9 dans le HEADER)
                break;
            }
          }
          else
          { // On charge les données dans un tableau jusqu'à la Section ou Entity suivant
            LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS, TRUE, ' ', TRUE, TRUE); // <--- DATA

            // - - - 8< - - - - - - - -
            // 1001
            // ACAD
            // 1002
            // {
            // 1000
            // superficie_ha=71087.26
            // 1000
            // ETAT=EXISTANT
            // 1000
            // PERIMETER_km=231.17283485357
            // 1000
            // code=1
            // 1000
            // NOM=GATINAIS
            // 1002
            // }
            // - - - 8< - - - - - - - -

            switch(l_nGroupId)
            {
              case 1000 :
                if(l_nAcadFlag == 2)
                {
                  l_aoStrAcadData.Add(m_oStrLineData);
                }
                else{}
                break;
              case 1001 :
                if(m_oStrLineData.CollateNoCase("ACAD") == 0)
                {
                  l_nAcadFlag = 1; // 0 -> 1 (ACAD_SECTION)
                }
                else{}
                break;
              case 1002 :
                if(m_oStrLineData.CollateNoCase("{") == 0)
                {
                  l_nAcadFlag += 1; // 1 -> 2 (ACAD_OPEN)
                }
                else if(m_oStrLineData.CollateNoCase("}") == 0)
                {
                  l_nAcadFlag += 2; // 2 -> 4 (ACAD_CLOSE)
                }
                else{}
                break;
              default :
                // Lecture des Attributs que l'on range dans un arbre, on valide à la Section / Entitée suivante
                // Cette 'astuce' est possible grâce à la Section EOF qui permet de terminer le parsing proprement
                l_nSize = l_oTreeStringData.AddString
                ( m_oStrLineData.GetBuffer(0)
                , l_nGroupId // String Data = l_nGroupId
                );

// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Modification d'un Node existant
                l_oasTreeKey.SetNode
// MODIF_KOCH 070328
                ( &l_nGroupId
                , l_nGroupId // On sauve l'index de la chaine, Key = l_nGroupId
                , l_nSize
                );
                break;
            }

// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Gestion de l'objet LWPOLYLINE
            if(l_nEntity == eDXF_LWPOLYLINE)
            {
              // Si on est dans un LWPOLYLINE, charger les VERTEX un-à-un
              switch(l_nGroupId)
              {
                case 20 :
                  // Récupère le point chargé juste avant (et pas encore écrasé par le suivant)
                  l_oVertexBuffer.Add
                  ( sSigPoint
                    ( ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(10)))) // X
                    , ATOD(l_oTreeStringData.GetStringPointer(l_oasTreeKey.GetNodeData(l_oasTreeKey.GetNodeIndex(20)))) // Y
                    , 0.0                                                                                               // Z
                    )
                  );

                  l_nLoop -= 1;
                  break;
                case 90 :
                  l_nLoop = ATOD(m_oStrLineData.GetBuffer(0));
                  break;
              }
            }
            else{}
// MODIF_KOCH 070328
          }

          l_nObjOffset = GetPos(CSigContainer::eSigFileId_OBJECTS); // On sauve le pointeur à la position de l'objet suivant (plus facile pour le débug)

#ifdef _DEBUG
          if(l_nObjOffset >= 2097150) // Nature2000_pSIC -> READ ERROR
//          if(l_nObjOffset >= 3977320) // Nature2000_pSIC -> ENTITIES
          {
            l_nObjOffset = l_nObjOffset;
          }
          else{}
#endif // _DEBUG

          if(i_poSkinProgress != NULL)
          {
            StepToPos
            ( CSigContainer::eSigFileId_OBJECTS
            , i_poSkinProgress
            );
          }
          else{}
        }

        return TRUE;
      }
      else
      {
        m_oStrLastError = "Impossible d'ouvrir le fichier";

        return FALSE;
      }
    }
  }
  else
  {
    m_oStrLastError = "Attend, y'a même pas de container attaché, tu veux ma mort ?";

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
BOOL CSigAutoCad::FileSave
( char*          i_panStringFile
, CSkinProgress* i_poSkinProgress // = NULL
)
{
  FileSelect(i_panStringFile);
  FileCreate(i_panStringFile);

  return FileSave(i_poSkinProgress);
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
BOOL CSigAutoCad::FileSave
( CSigContainer* i_poSigContainer
, CSkinProgress* i_poSkinProgress // = NULL
)
{
  CSigContainer* l_poSigPreviousContainer = m_poSigContainer;
  BOOL           l_bResult;

  if(i_poSigContainer != NULL)
  {
    m_poSigContainer = i_poSigContainer;

    l_bResult = FileSave(i_poSkinProgress);

    m_poSigContainer = l_poSigPreviousContainer;
  }
  else
  {
    l_bResult = FALSE;
  }

  return l_bResult;
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
BOOL CSigAutoCad::FileSave
( CSkinProgress* i_poSkinProgress // = NULL
)
{
  CString                    l_oStrTempo;
  CString                    l_oStrFormat;
  CString                    l_oStrLayer = "0"; // Par défaut, couche 0, TOUJOURS !
  CString                    l_oStrColor;

#ifndef USE_POLYGON
  sCoord                     l_asSigPoint[2];
#else // USE_POLYGON
  sSigPoint                  l_asSigPoint[2];
#endif // USE_POLYGON
  
  int                        l_nParent;
//  int                        l_nColSize;
//  int                        l_nColLoop;
  int                        l_nMulSize;
//  int                        l_nMulLoop;
  int                        l_nObjSize;
  int                        l_nObjLoop;

  bool                       l_bSkipObject;

//  CSigContainer::sSigColumn* l_psSigColumn;
  CSigContainer::sSigObject* l_psSigObject;
//  CSigContainer::sSigSymbol* l_psSigSymbol;
//  CSigContainer::sSigPen*    l_psSigPen;
//  CSigContainer::sSigBrush*  l_psSigBrush;
//  CSigContainer::sSigFont*   l_psSigFont;
//  CSigContainer::sSigSmooth* l_psSigSmooth;
//  CSigContainer::sSigText*   l_psSigText;

  //

  if(i_poSkinProgress != NULL)
  {
    i_poSkinProgress->SetRange
    ( 0
    , m_poSigContainer->GetObjectNumber()
    );
  }
  else{}

  m_bStop = FALSE; // Si si si, c'est important :)

  // Section HEADER ===========================================================

  // Création du HEADER du fichier '.DXF'
  _WriteDxfTag(0, "SECTION");
    _WriteDxfTag(2, "HEADER");
      _WriteDxfTag(9, "$ACADVER");
        _WriteDxfTag(1, "AC1009"); // R11 & R12 ("AC1009" -> R10)
      _WriteDxfTag(9, "$EXTMIN");
        _WriteDxfXyz
        ( m_poSigContainer->m_sHeader.sBound.sMin.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMin.nLatY
        , 0
        ); // XYZ
      _WriteDxfTag(9, "$EXTMAX");
        _WriteDxfXyz
        ( m_poSigContainer->m_sHeader.sBound.sMax.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMax.nLatY
        , 0
        ); // XYZ
/*
      _WriteDxfTag(9, "$LIMMIN");
        _WriteDxfXy
        ( m_poSigContainer->m_sHeader.sBound.sMin.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMin.nLatY
        ); // XY seulement
      _WriteDxfTag(9, "$LIMMAX");
        _WriteDxfXy
        ( m_poSigContainer->m_sHeader.sBound.sMax.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMax.nLatY
        ); // XY seulement
*/
  _WriteDxfTag(0, "ENDSEC");

  // Les styles de lignes, ne RIEN toucher, c'est du standard
  _WriteDxfTag(0, "SECTION");
    _WriteDxfTag(2, "TABLES");
      _WriteDxfTag(0, "TABLE");
        _WriteDxfTag(2, "LTYPE");
          _WriteDxfTag(70, "     3");
        _WriteDxfTag(0, "LTYPE");
          _WriteDxfTag(2, "CONTINUOUS");
          _WriteDxfTag(70, "     0");
          _WriteDxfTag(3,  "Solid Line");
          _WriteDxfTag(72, "    65");
          _WriteDxfTag(73, "     0");
          _WriteDxfTag(40, "0.0");
        _WriteDxfTag(0, "LTYPE");
          _WriteDxfTag(2, "DASHED");
          _WriteDxfTag(70, "     0");
          _WriteDxfTag(3,  "_ _ _ _ _");
          _WriteDxfTag(72, "    65");
          _WriteDxfTag(73, "     2");
          _WriteDxfTag(40, "0.75");
          _WriteDxfTag(49, "0.5");
          _WriteDxfTag(49, "-0.25");
        _WriteDxfTag(0, "LTYPE");
          _WriteDxfTag(2, "DOT");
          _WriteDxfTag(70, "     0");
          _WriteDxfTag(3,  ". . . . .");
          _WriteDxfTag(72, "    65");
          _WriteDxfTag(73, "     2");
          _WriteDxfTag(40, "1.0");
          _WriteDxfTag(49, "0.0");
          _WriteDxfTag(49, "-1.0");
      _WriteDxfTag(0, "ENDTAB");
  _WriteDxfTag(0, "ENDSEC");

  // Section DATA =============================================================

// *******************************************
/*

  // Les blocs, entitées complexes (régions à trous par exemple)
  _WriteDxfTag(0, "SECTION");
  _WriteDxfTag(2, "BLOCKS");
  // Création des 'blocks' uniquement pour les 'Pline (Multiple)' ou les 'Region (Multiple)'

  for
  ( hlen = 1
  ; hlen <= CoordIndex
  ; hlen += 1
  )
  { // On scanne toutes les lignes de donnée
    olen = m_View.IsObjectParent(hlen);

    if(olen != 0)
    { // On encapsule les objets complexes dans un groupe
      _WriteDxfTag(0, "BLOCK");
      _WriteDxfTag(8, "0");
      _WriteDxfTag(62, "     1");

      csTempo = "REGION" + (CString) _itoa(polyx, ligne, 10);
      cslBlock.AddTail(csTempo);
      _WriteDxfTag(2, csTempo.GetBuffer(0));
      polyx += 1;

      _WriteDxfTag(70, "    64");
      _WriteDxfXyz(0, 0, 0);

      for
      ( vlen = hlen + 1
      ; vlen <= hlen + olen
      ; vlen += 1
      )
      { // Vérifier parentalité, parce qu'à la fin, on reste en 'simple', mais avec parent ROOT !
        _WriteDxfObject(l_psSigObject);
      }

      _WriteDxfTag(0, "ENDBLK");
      _WriteDxfTag(8, "0");  
  
      hlen += olen; // on reprend à la fin du groupe    
    }
  }

  _WriteDxfTag(0, "ENDSEC");

*/
// *******************************************

/*
  // Les blocs, entitées complexes (régions à trous par exemple)
  _WriteDxfTag(0, "SECTION");
  _WriteDxfTag(2, "BLOCKS");

  _WriteDxfTag(0, "ENDSEC");
*/

  // Les entitées simples
  _WriteDxfTag(0, "SECTION");
  _WriteDxfTag(2, "ENTITIES");

  l_psSigObject = m_poSigContainer->GetFirstObject(CSigContainer::eOBJTYP__ANY);
  while(l_psSigObject != NULL)
  {
    l_nParent     = 0; // En règle générale, mais là c'est juste pour le test REGION et MULTIPLE
    l_bSkipObject = false;

    if(l_psSigObject->eObjectType >  CSigContainer::eOBJTYP_ROOT)
    {
      switch(l_psSigObject->eObjectType)
      { // Vérification sommaire de la validité de l'objet
        case CSigContainer::eOBJTYP_POINT :
#ifndef USE_POLYGON
          l_bSkipObject = l_psSigObject->nPointNumber < 1;
#else // USE_POLYGON
          l_bSkipObject = l_psSigObject->poPolygon->GetSize() < 1;
#endif // USE_POLYGON
          break;
        case CSigContainer::eOBJTYP_LINE :
        case CSigContainer::eOBJTYP_TEXT :
        case CSigContainer::eOBJTYP_RECTANGLE :
        case CSigContainer::eOBJTYP_ELLIPSE :
#ifndef USE_POLYGON
          l_bSkipObject = l_psSigObject->nPointNumber < 2;
#else // USE_POLYGON
          l_bSkipObject = l_psSigObject->poPolygon->GetSize() < 2;
#endif // USE_POLYGON
          break;
        case CSigContainer::eOBJTYP_POLYLINE :
        case CSigContainer::eOBJTYP_ARC :
        case CSigContainer::eOBJTYP_ROUNDRECT :
#ifndef USE_POLYGON
          l_bSkipObject = l_psSigObject->nPointNumber < 3;
#else // USE_POLYGON
          l_bSkipObject = l_psSigObject->poPolygon->GetSize() < 3;
#endif // USE_POLYGON
          break;
        case CSigContainer::eOBJTYP_BLOCK :
        case CSigContainer::eOBJTYP_REGION :
        case CSigContainer::eOBJTYP_MULTIPLE :
        case CSigContainer::eOBJTYP_MULTIPOINT :
        case CSigContainer::eOBJTYP_COLLECTION :
        default :
          break;
      }

      if(l_bSkipObject == false)
      { // Si l'objet est correct, on l'écrit
        switch(l_psSigObject->eObjectType)
        {
          case CSigContainer::eOBJTYP_POINT :
            // Ecriture POINT (Point X Y)
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
#endif // USE_POLYGON

            _WriteDxfTag(0, "POINT");

            if(l_oStrLayer.IsEmpty() == FALSE) _WriteDxfTag(8, l_oStrLayer);
            if(l_oStrColor.IsEmpty() == FALSE) _WriteDxfTag(62, l_oStrColor);

            _WriteDxfData(l_psSigObject);

            _WriteDxfXyz
            ( l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[0].nAltZ
            );
            break;
          case CSigContainer::eOBJTYP_LINE :
            // Ecriture LINE (Line X1 Y1 X2 Y2)
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

            _WriteDxfTag(0, "LINE");

            if(l_oStrLayer.IsEmpty() == FALSE) _WriteDxfTag(8, l_oStrLayer);
            if(l_oStrColor.IsEmpty() == FALSE) _WriteDxfTag(62, l_oStrColor);

            _WriteDxfData(l_psSigObject);

            _WriteDxfXyz
            ( l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[0].nAltZ
            , 0 // Point n
            );

            _WriteDxfXyz
            ( l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            , l_asSigPoint[1].nAltZ
            , 1 // Point n+1
            );
            break;
          case CSigContainer::eOBJTYP_BLOCK :
            // Ecriture BLOCK (Multi objets)
          case CSigContainer::eOBJTYP_REGION :
            // Ecriture REGION (Region numpolygons)
          case CSigContainer::eOBJTYP_MULTIPLE :
            // Ecriture MULTIPLE (Pline Multiple numsections \n numpoints)
            l_nParent  = l_psSigObject->nObjectIndex;

//            l_nMulSize = l_psSigObject->nPointIndex; // Nombre d'objets
            l_nMulSize = 0; // Nombre d'objets valides

            do
            { // On calcule le nombre d'objets avec des vrais points dedans
#ifndef USE_POLYGON
              if(l_psSigObject->nPointNumber > 0)
#else // USE_POLYGON
              if(l_psSigObject->poPolygon->GetSize() > 0)
#endif // USE_POLYGON
              {
                l_nMulSize += 1;
              }
              else{}
            }
            while
            ( // On continue de charger tant qu'il y a lieu de le faire
                 (l_nParent != 0) // Tadaaaaaaa, l'astuce est ici !!!
              && ((l_psSigObject = m_poSigContainer->GetNextObject(CSigContainer::eOBJTYP__ANY)) != NULL)
              && (l_psSigObject->nParentIndex == l_nParent)
            );
            break;

//            ASSERT(l_nMulSize == l_psSigObject->nPointIndex);

            // On se recale sur le parent
            l_psSigObject = m_poSigContainer->GetFirstObject(CSigContainer::eOBJTYP__ANY, l_nParent);
          case CSigContainer::eOBJTYP_POLYLINE :
            // Ecriture PLINE (Pline \n numpoints)
            switch(l_psSigObject->eObjectType)
            {
              case CSigContainer::eOBJTYP_MULTIPLE :
                _WriteDxfTag(0, "MULTIPLE"); // BAAAAAAAAAAAAAAAAAD !
                break;
              case CSigContainer::eOBJTYP_REGION :
              case CSigContainer::eOBJTYP_POLYLINE :
                _WriteDxfTag(0, "POLYLINE");
                break;
            }

            if(l_oStrLayer.IsEmpty() == FALSE) _WriteDxfTag(8, l_oStrLayer);
            if(l_oStrColor.IsEmpty() == FALSE) _WriteDxfTag(62, l_oStrColor);

            _WriteDxfData(l_psSigObject);

            do
            {
              // Nombre de points
#ifndef USE_POLYGON
              l_nObjSize = l_psSigObject->nPointNumber;
#else // USE_POLYGON
              l_nObjSize = l_psSigObject->poPolygon->GetSize();
#endif // USE_POLYGON

              if(l_nObjSize > 0)
              {
/*
                l_oStrTempo.Format
                ( "  %d\n"
                , l_nObjSize 
                );

                WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
*/

#ifndef USE_POLYGON
                l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
                l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + l_nObjSize - 1);
#else // USE_POLYGON
                l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
                l_asSigPoint[1] = l_psSigObject->poPolygon->Point(l_nObjSize - 1);
#endif // USE_POLYGON

#ifndef USE_POLYGON
                if
                (
                     (l_asSigPoint[0].nLonX == l_asSigPoint[1].nLonX)
                  && (l_asSigPoint[0].nLatY == l_asSigPoint[1].nLatY)
                  && (l_asSigPoint[0].nAltZ == l_asSigPoint[1].nAltZ)
                )
#else // USE_POLYGON
                if(l_asSigPoint[0] == l_asSigPoint[1])
#endif // USE_POLYGON
                { // Si c'est un polygone fermé
                  _WriteDxfTag(70, "     1"); // 0 = ouvert

                  l_nObjSize -= 1; // On ne le ferme pas
                }
                else{}

                // Séquence émotion... heu... points
                _WriteDxfTag(66, "     1"); // !!! IMPORTANT - SEPARE LES CARACTERISTISQUES DE L'OBJET DES POINTS !!!

                for
                ( l_nObjLoop  = 0
                ; l_nObjLoop <  l_nObjSize
                ; l_nObjLoop += 1
                )
                {
#ifndef USE_POLYGON
                  l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + l_nObjLoop);
#else // USE_POLYGON
                  l_asSigPoint[0] = l_psSigObject->poPolygon->Point(l_nObjLoop);
#endif // USE_POLYGON

                  _WriteDxfTag(0, "VERTEX");
                  _WriteDxfTag(8, "0");

                  _WriteDxfXyz
                  ( l_asSigPoint[0].nLonX
                  , l_asSigPoint[0].nLatY
                  , l_asSigPoint[0].nAltZ
                  );
                }

                _WriteDxfTag(0, "SEQEND");
                _WriteDxfTag(8, "0");
              }
              else{}
            }
            while
            ( // On continue de charger tant qu'il y a lieu de le faire
                 (l_nParent != 0) // Tadaaaaaaa, l'astuce est ici !!!
              && ((l_psSigObject = m_poSigContainer->GetNextObject(CSigContainer::eOBJTYP__ANY)) != NULL)
              && (l_psSigObject->nParentIndex == l_nParent)
            );
            break;

          case CSigContainer::eOBJTYP_ARC :
            // Ecriture ARC (Arc X1 Y1 X2 Y2 \n A B)
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

            _WriteDxfTag(0, "ARC");

            if(l_oStrLayer.IsEmpty()  == FALSE) _WriteDxfTag(8, l_oStrLayer);
            if(l_oStrColor.IsEmpty() == FALSE) _WriteDxfTag(62, l_oStrColor);

            _WriteDxfData(l_psSigObject);

            _WriteDxfXyz
            ( l_asSigPoint[0].nLonX <  l_asSigPoint[1].nLonX
            ? l_asSigPoint[0].nLonX + (l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            : l_asSigPoint[0].nLonX - (l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            , l_asSigPoint[0].nLatY <  l_asSigPoint[1].nLatY
            ? l_asSigPoint[0].nLatY + (l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            : l_asSigPoint[0].nLatY - (l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            , l_asSigPoint[0].nAltZ <  l_asSigPoint[1].nAltZ
            ? l_asSigPoint[0].nAltZ + (l_asSigPoint[1].nAltZ - l_asSigPoint[0].nAltZ) / 2
            : l_asSigPoint[0].nAltZ - (l_asSigPoint[1].nAltZ - l_asSigPoint[0].nAltZ) / 2
            );

            l_oStrTempo.Format
            ( "  %d\n"
            , abs(l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) < abs(l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY)
            ? abs(l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            : abs(l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            );

            _WriteDxfTag(40, l_oStrTempo); // RADIUS

            // ANGLE

#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 2);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(2);
#endif // USE_POLYGON

            l_oStrTempo.Format
            ( "  %d\n"
            , l_asSigPoint[0].nLonX
            );

            _WriteDxfTag(50, l_oStrTempo); // START ANGLE

            l_oStrTempo.Format
            ( "  %d\n"
            , l_asSigPoint[0].nLatY
            );

            _WriteDxfTag(51, l_oStrTempo); // END ANGLE
            break;
          case CSigContainer::eOBJTYP_TEXT :
            // Ecriture TEXT (Text "textstring" \n X1 Y1 X2 Y2)
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

            _WriteDxfTag(0, "TEXT");

            if(l_oStrLayer.IsEmpty() == FALSE) _WriteDxfTag(8, l_oStrLayer);
            if(l_oStrColor.IsEmpty() == FALSE) _WriteDxfTag(62, l_oStrColor);

            _WriteDxfData(l_psSigObject);

            _WriteDxfXyz
            ( l_asSigPoint[0].nLonX <  l_asSigPoint[1].nLonX
            ? l_asSigPoint[0].nLonX + (l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            : l_asSigPoint[0].nLonX - (l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            , l_asSigPoint[0].nLatY <  l_asSigPoint[1].nLatY
            ? l_asSigPoint[0].nLatY + (l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            : l_asSigPoint[0].nLatY - (l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            , 0
            );

            l_oStrTempo.Format
            ( "  %d\n"
            , 10
            );

            _WriteDxfTag(40, l_oStrTempo); // HEIGHT

            _WriteDxfTag(1, m_poSigContainer->GetString(l_psSigObject->nTextIndex)); // TEXT
            break;
/*
          case CSigContainer::eOBJTYP_RECTANGLE :
            // Ecriture RECT (Rect X1 Y1 X2 Y2)
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);

            l_oStrTempo.Format
            ( "Rect %f %f %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            break;
          case CSigContainer::eOBJTYP_ROUNDRECT :
            // Ecriture ROUNDRECT (Roundrect X1 Y1 X2 Y2 \n A) 
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);

            l_oStrTempo.Format
            ( "Roundrect %f %f %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(2);

            l_oStrTempo.Format
            ( "%f\n"
            , l_asSigPoint[0].nLonX
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            break;
*/
          case CSigContainer::eOBJTYP_ELLIPSE :
            // Ecriture ELLIPSE (Ellipse X1 Y1 X2 Y2)
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

            _WriteDxfTag(0, "CIRCLE");

            if(l_oStrLayer.IsEmpty() == FALSE) _WriteDxfTag(8, l_oStrLayer);
            if(l_oStrColor.IsEmpty() == FALSE) _WriteDxfTag(62, l_oStrColor);

            _WriteDxfData(l_psSigObject);

            _WriteDxfXyz
            ( l_asSigPoint[0].nLonX <  l_asSigPoint[1].nLonX
            ? l_asSigPoint[0].nLonX + (l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            : l_asSigPoint[0].nLonX - (l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            , l_asSigPoint[0].nLatY <  l_asSigPoint[1].nLatY
            ? l_asSigPoint[0].nLatY + (l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            : l_asSigPoint[0].nLatY - (l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            , l_asSigPoint[0].nAltZ <  l_asSigPoint[1].nAltZ
            ? l_asSigPoint[0].nAltZ + (l_asSigPoint[1].nAltZ - l_asSigPoint[0].nAltZ) / 2
            : l_asSigPoint[0].nAltZ - (l_asSigPoint[1].nAltZ - l_asSigPoint[0].nAltZ) / 2
            );

            l_oStrTempo.Format
            ( "  %d\n"
            , abs(l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) < abs(l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY)
            ? abs(l_asSigPoint[1].nLonX - l_asSigPoint[0].nLonX) / 2
            : abs(l_asSigPoint[1].nLatY - l_asSigPoint[0].nLatY) / 2
            );

            _WriteDxfTag(40, l_oStrTempo); // RADIUS
            break;
/*
          case CSigContainer::eOBJTYP_MULTIPOINT :
            // Ecriture MULTIPOINT (Multipoint num_points)
            l_nObjSize = l_psSigObject->poPolygon->GetSize();

            l_oStrTempo.Format
            ( "Multipoint %d\n"
            , l_nObjSize
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

            for
            ( l_nObjLoop  = 0
            ; l_nObjLoop <  l_nObjSize
            ; l_nObjLoop += 1
            )
            {
              l_asSigPoint[0] = l_psSigObject->poPolygon->Point(l_nObjLoop);

              l_oStrTempo.Format
              ( "%f %f\n"
              , l_asSigPoint[0].nLonX
              , l_asSigPoint[0].nLatY
              );

              WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            }
            break;
          case CSigContainer::eOBJTYP_COLLECTION :
            // Ecriture COLLECTION (Collection num_parts)

  // MODIF_KOCH
            // ==== PAS FINI SIG !
  // MODIF_KOCH
            break;
*/
          default :
            // Ecriture NONE
            _WriteDxfTag(0, "NONE");

            if(l_oStrLayer.IsEmpty()  == FALSE) _WriteDxfTag(8, l_oStrLayer);
            break;

        }

// *******************************************
/*
        // ATTRIBUTS --------------------------------------------------------------
*/
// *******************************************

        // DONNEES ----------------------------------------------------------------

//        _WriteDxfData(l_psSigObject);

        if(i_poSkinProgress != NULL)
        {
          i_poSkinProgress->SetPos
          ( l_psSigObject->nObjectIndex
          );
        }
        else{}

        PeekAndPump(); // Release message pressure
      }
      else{} // l_bSkipObject
    }
    else{}

    // LA SUITE ---------------------------------------------------------------

    if(l_nParent == 0)
    { // Si on ne sort pas d'un objet complexe (REGION ou MULTIPLE ou COLLECTION), on sauve l'objet suivant
      l_psSigObject = m_poSigContainer->GetNextObject(CSigContainer::eOBJTYP__ANY);
    }
    else{}
  }

  // Cloture LOGIQUE et PHYSIQUE du fichier '.DXF'
  _WriteDxfTag(0, "ENDSEC");
  _WriteDxfTag(0, "EOF");

  FileFlush();

  return FileClose();
}

// Nombre de chiffres après la virgule pour l'écriture des coordonnées
#define FPREC "10"

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
void CSigAutoCad::_WriteDxfTag
( int   tag_number
, const char* tag_name
)
{
  mp_oStrTempo.Format
  ( "  %d\n"
    "%s\n"
  , tag_number
  , tag_name
  );

  WriteLine(CSigContainer::eSigFileId_OBJECTS, mp_oStrTempo);
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
void CSigAutoCad::_WriteDxfXy
( double i_nLonX
, double i_nLatY
, int    i_nRef // = 0
)
{
  mp_oStrTempo.Format
  ( " %d\n""%"FPREC"f\n" // X
    " %d\n""%"FPREC"f\n" // Y
  , 10 + i_nRef , i_nLonX
  , 20 + i_nRef , i_nLatY
  );

  WriteLine(CSigContainer::eSigFileId_OBJECTS, mp_oStrTempo);
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
void CSigAutoCad::_WriteDxfXyz
( double i_nLonX
, double i_nLatY
, double i_nAltY
, int    i_nRef // = 0
)
{
  mp_oStrTempo.Format
  ( " %d\n""%."FPREC"g\n" // X
    " %d\n""%."FPREC"g\n" // Y
    " %d\n""%."FPREC"g\n" // Z
  , 10 + i_nRef , i_nLonX
  , 20 + i_nRef , i_nLatY
  , 30 + i_nRef , i_nAltY
  );

  WriteLine(CSigContainer::eSigFileId_OBJECTS, mp_oStrTempo);
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
void CSigAutoCad::_WriteDxfData
( CSigContainer::sSigObject* i_psSigObject
)
{
  CString                    l_oStrTempo;

  int                        l_nColSize;
  int                        l_nColLoop;

  CSigContainer::sSigColumn* l_psSigColumn;

  // - - - 8< - - - - - - - -
  // 1001
  // ACAD
  // 1002
  // {
  // 1000
  // superficie_ha=71087.26
  // 1000
  // ETAT=EXISTANT
  // 1000
  // PERIMETER_km=231.17283485357
  // 1000
  // code=1
  // 1000
  // NOM=GATINAIS
  // 1002
  // }
  // - - - 8< - - - - - - - -

  l_nColSize = m_poSigContainer->GetColumnCount();

  if(l_nColSize > 0)
  {
    _WriteDxfTag(1001, "ACAD");
    _WriteDxfTag(1002, "{");

    for
    ( l_nColLoop  = 0
    ; l_nColLoop <  l_nColSize
    ; l_nColLoop += 1
    )
    {
      l_psSigColumn = (CSigContainer::sSigColumn*) m_poSigContainer->GetColumnPointer(l_nColLoop);

      if(l_psSigColumn != NULL)
      {
        l_oStrTempo.Format
        ( "%s=%s"
        , m_poSigContainer->GetString(l_psSigColumn->nNameIndex) // Nom de la colonne
        , m_poSigContainer->GetColumnString(l_nColLoop, i_psSigObject) // Donnée
        );
      }
      else{}

      _WriteDxfTag(1000, l_oStrTempo);
    }

    _WriteDxfTag(1002, "}");
  }
  else{}
}
