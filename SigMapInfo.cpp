// SigMapInfo.cpp: implementation of the CSigMapInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SigMapInfo.h"

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
CSigMapInfo::CSigMapInfo
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
CSigMapInfo::CSigMapInfo
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
CSigMapInfo::~CSigMapInfo
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
BOOL CSigMapInfo::_Initialize
( BOOL i_bCreateOwnContainer // = TRUE
)
{
  int   l_nLoop;
//  int   l_nTempo;

  char* l_panHashTable[]
  = 
  { "VERSION"      // eMIFMID_VERSION    -> HEADER
  , "CHARSET"      // eMIFMID_CHARSET
  , "DELIMITER"    // eMIFMID_DELIMITER
  , "UNIQUE"       // eMIFMID_UNIQUE
  , "INDEX"        // eMIFMID_INDEX
  , "COORDSYS"     // eMIFMID_COORDSYS
  ,   "PROJECTION" // eMIFMID_PROJECTION
  ,   "AFFINE"     // eMIFMID_AFFINE
  ,   "UNITS"      // eMIFMID_UNITS
  ,   "BOUNDS"     // eMIFMID_BOUNDS
  , "TRANSFORM"    // eMIFMID_TRANSFORM
  , "COLUMNS"      // eMIFMID_COLUMNS
  ,   "CHAR"       // eMIFMID_CHAR       -> COLUMNS
  ,   "INTEGER"    // eMIFMID_INTEGER
  ,   "SMALLINT"   // eMIFMID_SMALLINT
  ,   "DECIMAL"    // eMIFMID_DECIMAL
  ,   "FLOAT"      // eMIFMID_FLOAT
  ,   "DATE"       // eMIFMID_DATE
  ,   "LOGICAL"    // eMIFMID_LOGICAL
  , "DATA"         // eMIFMID_DATA       -> DATA SECTION
  ,     "SYMBOL"   // eMIFMID_SYMBOL     -> ATTRIBUTES
  ,     "PEN"      // eMIFMID_PEN
  ,     "BRUSH"    // eMIFMID_BRUSH
  ,     "FONT"     // eMIFMID_FONT
  ,     "SMOOTH"   // eMIFMID_SMOOTH
  ,     "SPACING"  // eMIFMID_SPACING
  ,     "JUSTIFY"  // eMIFMID_JUSTIFY
  ,     "LEFT"     // eMIFMID_LEFT
  ,     "CENTER"   // eMIFMID_CENTER
  ,     "RIGHT"    // eMIFMID_RIGHT
  ,     "ANGLE"    // eMIFMID_ANGLE
  ,     "LABEL"    // eMIFMID_LABEL
  ,     "SIMPLE"   // eMIFMID_SIMPLE
  ,     "ARROW"    // eMIFMID_ARROW
  ,   "POINT"      // eMIFMID_POINT      -> OBJECT TYPES
  ,   "LINE"       // eMIFMID_LINE
  ,   "PLINE"      // eMIFMID_PLINE
  ,   "MULTIPLE"   // eMIFMID_MULTIPLE
  ,   "REGION"     // eMIFMID_REGION
  ,   "ARC"        // eMIFMID_ARC
  ,   "TEXT"       // eMIFMID_TEXT
  ,   "RECT"       // eMIFMID_RECT
  ,   "ROUNDRECT"  // eMIFMID_ROUNDRECT
  ,   "ELLIPSE"    // eMIFMID_ELLIPSE
  ,   "MULTIPOINT" // eMIFMID_MULTIPOINT
  ,   "COLLECTION" // eMIFMID_COLLECTION
  };

#ifdef _DEBUG
  // Si ça plante là, c'est qu'il y a plus d'enum eMIFMID que d'entrée au tableau de HASH
  ASSERT((sizeof(l_panHashTable) / sizeof(char*)) == eMIFMID__END);
#endif // _DEBUG

  m_oStrFileExtObjects  = ".mif";
  m_oStrFileExtDataBase = ".mid";

  for
  ( l_nLoop  = 0
  ; l_nLoop <  eMIFMID__END
  ; l_nLoop += 1
  )
  {
//    l_nTempo = IPOW(26,l_nLoop); // Pour debug
    mp_anHashTable[l_nLoop] = SHASH(l_panHashTable[l_nLoop]);
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
BOOL CSigMapInfo::_IsHashed
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
BOOL CSigMapInfo::_IsHashed
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
BOOL CSigMapInfo::FileLoad
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
BOOL CSigMapInfo::FileLoad
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
BOOL CSigMapInfo::FileLoad
( CSkinProgress* i_poSkinProgress // = NULL
)
{
  XString                 l_oStrObject;
  XString                 l_oStrTempo;
  XString                 l_oStrTrash;

  int                     l_nLoop;
  int                     l_nTempo;
  int                     l_nObjOffset;

  int                     l_nCplxObjHashed;

  CSigContainer::sSigText l_sSigText;

  //

  if(m_poSigContainer != NULL)
  {
    if(*m_oPathSplitter.GetPath() == '\0')
    {
      m_oStrLastError = "Choisissez un fichier à parser avec FileSelect() au préalable...";

      return FALSE;
    }
    else
    {
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
          && (LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS, TRUE))
        )
        { // Section HEADER =====================================================
          if(_IsHashed(eMIFMID_VERSION) == TRUE) // ------------------------------
          { // La version du fichier
            l_oStrTempo = GetElement(1);
            l_oStrTempo.Remove('"');
            m_poSigContainer->m_sHeader.nVersion = ATOI(l_oStrTempo); // 300 ou plus
          }
          else if(_IsHashed(eMIFMID_CHARSET) == TRUE) // -------------------------
          { //
            l_oStrTempo = GetElement(1);
            l_oStrTempo.Remove('"');
            m_poSigContainer->m_sHeader.nCharset = m_poSigContainer->AddString(l_oStrTempo);
          }
          else if(_IsHashed(eMIFMID_DELIMITER) == TRUE) // -----------------------
          { // On extrait le délimiteur
            l_oStrTempo = GetElement(1);
            l_oStrTempo.Remove('"');
            m_oStrDataDelimiter = l_oStrTempo.GetAt(0);
          }
          else if(_IsHashed(eMIFMID_UNIQUE) == TRUE) // ------------------------
          { // Système de coordonnées
// MODIF_KOCH
  // ==== PAS FINI SIG !
// MODIF_KOCH
          }
          else if(_IsHashed(eMIFMID_INDEX) == TRUE) // ------------------------
          { // Système de coordonnées
            l_oStrTempo  = GetElement(1) + GetElement(2) + GetElement(3) + GetElement(4); // Liste des colonnes indexées
            l_oStrTempo.Remove(' '); // Supprime l'espace pour que ce soit parsé correctement

            ParseFunctionArguments(l_oStrTempo);
// MODIF_KOCH
  // ==== PAS FINI SIG !
// MODIF_KOCH
          }
          else if(_IsHashed(eMIFMID_COORDSYS) == TRUE) // ------------------------
          { // Système de coordonnées
            if(GetElement(1).CollateNoCase("Earth") == 0)
            { // Syntax 1
              m_poSigContainer->m_sHeader.sProjection.nSyntax = 0;

              if(GetElement(2).CollateNoCase("Projection") == 0)
              {
                l_oStrTempo = m_oStrLineData;
                l_oStrTempo.MakeLower();
                l_oStrTempo = l_oStrTempo.Mid(l_oStrTempo.Find("projection"));

                if(l_oStrTempo.Find("bounds") >= 0)
                { // Attention, Bounds est sur la même ligne !
                  l_oStrTrash = l_oStrTempo.Mid(l_oStrTempo.Find("bounds")); // On garde Bounds pour plus tard
                  l_oStrTempo = l_oStrTempo.Left(l_oStrTempo.Find("bounds"));
                }
                else{}

//                l_oStrTempo.Replace("projection", "projection,"); // S'assure que le parsing soit correctement effectué

                ParseFunctionArguments(l_oStrTempo);
              }
              else{}
            }
            else if(GetElement(1).CollateNoCase("Nonearth") == 0)
            { // Syntax 2
              m_poSigContainer->m_sHeader.sProjection.nSyntax = 1;
            }
            else if(GetElement(1).CollateNoCase("Layout") == 0)
            { // Syntax 3
              m_poSigContainer->m_sHeader.sProjection.nSyntax = 2;

              // CoordSys Layout Units %paperunitname% -> %paperunitname% is a string representing a paper unit of measure (e.g. -in" for inches)
//              m_poSigContainer->m_sHeader.sProjection.anUnitName = m_poSigContainer->AddString(GetElement(2));
              strcpy
              ( m_poSigContainer->m_sHeader.sProjection.anUnitName
              , GetElement(3)
              );
            }
            else if(GetElement(1).CollateNoCase("Table") == 0)
            { // Syntax 4
              m_poSigContainer->m_sHeader.sProjection.nSyntax = 3;

              // CoordSys Table %tablename% -> %tablename% is the name of an open table
              m_poSigContainer->m_sHeader.sProjection.nTypeOrTableName = m_poSigContainer->AddString(GetElement(2));
            }
            else if(GetElement(1).CollateNoCase("Window") == 0)
            { // Syntax 5
              m_poSigContainer->m_sHeader.sProjection.nSyntax = 4;

              // CoordSys Window %window_id% -> %window_id% is an Integer window identifier corresponding to a Map or Layout window
              m_poSigContainer->m_sHeader.sProjection.nDatumOrWindowID = ATOI(GetElement(2));
            }
            else{}
          }
          else{}
          
          // Traitement discontinu si on sort de COORDSYS
          if(_IsHashed(eMIFMID_PROJECTION) == TRUE) // ------------------------
          {
            m_poSigContainer->m_sHeader.sProjection.nTypeOrTableName   = ATOI(GetElement(1)); // 3

            l_nTempo = ATOI(GetElement(2)); // 1002 (9999 est spécial)

            m_poSigContainer->m_sHeader.sProjection.nDatumOrWindowID   = l_nTempo;

            if
            (
                 (l_nTempo == 999)
              || (l_nTempo == 9999)
            )
            { // Datum spécifique/utilisateur
              if(m_poSigContainer->m_sHeader.sProjection.nTypeOrTableName = 3)
              { // France Métropole
                l_nTempo = 12;
              }
              else if(m_poSigContainer->m_sHeader.sProjection.nTypeOrTableName = 8)
              { // France DOM
                l_nTempo = 12;
              }
              else
              {
                l_nTempo = 3;
              }
            }
            else
            {
              l_nTempo = 3;
            }

            strcpy
            ( m_poSigContainer->m_sHeader.sProjection.anUnitName
            ,  GetElement(l_nTempo+0)
            );

            m_poSigContainer->m_sHeader.sProjection.nOriginLon         = ATOD(GetElement(l_nTempo+1)); // 0.000000000000
            m_poSigContainer->m_sHeader.sProjection.nOriginLat         = ATOD(GetElement(l_nTempo+2)); // 46.800000000000
            m_poSigContainer->m_sHeader.sProjection.nStandartParallel1 = ATOD(GetElement(l_nTempo+3)); // 45.898918964419
            m_poSigContainer->m_sHeader.sProjection.nStandartParallel2 = ATOD(GetElement(l_nTempo+4)); // 47.696014502038
            m_poSigContainer->m_sHeader.sProjection.nAzimut            = ATOD(GetElement(l_nTempo+5)); // 600000.000
            m_poSigContainer->m_sHeader.sProjection.nScaleFactor       = ATOD(GetElement(l_nTempo+6)); // 2200000.000
            m_poSigContainer->m_sHeader.sProjection.nFalseEasting      = ATOD(GetElement(l_nTempo+7));
            m_poSigContainer->m_sHeader.sProjection.nFalseNorthing     = ATOD(GetElement(l_nTempo+8));
            m_poSigContainer->m_sHeader.sProjection.nRange             = ATOD(GetElement(l_nTempo+9));

            if(l_oStrTrash.IsEmpty() == FALSE)
            { // Parse Bounds récupéré plus haut
              ParseFunctionArguments(l_oStrTrash); // Simule la lecture depuis le fichier pour '_IsHashed'
              l_oStrTrash.Empty();
            }
            else{}
          }
          else{}
          
          if(_IsHashed(eMIFMID_AFFINE) == TRUE) // ------------------------
          {
            strcpy
            ( m_poSigContainer->m_sHeader.sAffine.anUnitName
            ,  GetElement(2)
            );

            m_poSigContainer->m_sHeader.sAffine.nXaxisScaleStretch = ATOD(GetElement(3));
            m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew    = ATOD(GetElement(4));
            m_poSigContainer->m_sHeader.sAffine.nXaxisShift        = ATOD(GetElement(5));
            m_poSigContainer->m_sHeader.sAffine.nYaxisScaleStretch = ATOD(GetElement(6));
            m_poSigContainer->m_sHeader.sAffine.nYaxisRotatSkew    = ATOD(GetElement(7));
            m_poSigContainer->m_sHeader.sAffine.nYaxisShift        = ATOD(GetElement(8));
          }
          else if(_IsHashed(eMIFMID_UNITS) == TRUE) // ------------------------
          {
            strcpy
            ( m_poSigContainer->m_sHeader.sAffine.anUnitName
            , GetElement(1)
            );
          }
          else if(_IsHashed(eMIFMID_BOUNDS) == TRUE) // ------------------------
          {
//            m_oStrLineData.Replace(')', ','); // (,)(,) -> (,,(,, -> (,,,,

            ParseFunctionArguments(m_oStrLineData);
          }
          else if(_IsHashed(eMIFMID_TRANSFORM) == TRUE) // ------------------------
          {
            l_oStrTempo  = GetElement(1) + GetElement(2) + GetElement(3) + GetElement(4); // Xmultiplier, Ymultiplier, Xdisplacement, Ydisplacement
            l_oStrTempo.Remove(' '); // Supprime l'espace pour que ce soit parsé correctement

            ParseFunctionArguments(l_oStrTempo);

            m_poSigContainer->m_sHeader.sTransform.sTransformMultiplier.nLonX   = ATOD(GetElement(0)); // Xmultiplier
            m_poSigContainer->m_sHeader.sTransform.sTransformMultiplier.nLatY   = ATOD(GetElement(1)); // Ymultiplier
            m_poSigContainer->m_sHeader.sTransform.sTransformDisplacement.nLonX = ATOD(GetElement(2)); // Xdisplacement
            m_poSigContainer->m_sHeader.sTransform.sTransformDisplacement.nLatY = ATOD(GetElement(3)); // Ydisplacement
          }
          else if(_IsHashed(eMIFMID_COLUMNS) == TRUE) // -------------------------
          {
            l_nLoop = ATOI(GetElement(1)); // Nombre de colonnes

            while
            (
                 (l_nLoop != 0)
              && (LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS) != 0)
            )
            {
              l_oStrObject = GetElement(0); // Nom
              l_oStrTempo  = GetElement(1) + GetElement(2) + GetElement(3) + GetElement(4); // Type

              l_oStrTempo.Remove(' '); // dans le cas de "char (x)", supprime l'espace pour que ce soit parsé correctement

              ParseFunctionArguments(l_oStrTempo); // Parse le type, surtout pour char(X) et decimal(X, Y)

              if(_IsHashed(eMIFMID_CHAR) == TRUE) // .............................
              {
                AddColumn
                ( l_oStrObject
                , CSigContainer::eCOLTYP_CHAR
                , ATOI(GetElement(1)) // X, nombre de caractères
                );
              }
              else if(_IsHashed(eMIFMID_INTEGER) == TRUE) // .....................
              {
                AddColumn
                ( l_oStrObject
                , CSigContainer::eCOLTYP_INTERGER
//                , sizeof(int)
                );
              }
              else if(_IsHashed(eMIFMID_SMALLINT) == TRUE) // ....................
              {
                AddColumn
                ( l_oStrObject
                , CSigContainer::eCOLTYP_SMALLINT
//                , sizeof(short)
                );
              }
              else if(_IsHashed(eMIFMID_DECIMAL) == TRUE) // .....................
              {
                AddColumn
                ( l_oStrObject
                , CSigContainer::eCOLTYP_DECIMAL
                , (ATOI(GetElement(1)) << 8) // X
                | (ATOI(GetElement(2))     ) // Y
                );
              }
              else if(_IsHashed(eMIFMID_FLOAT) == TRUE) // .......................
              {
                AddColumn
                ( l_oStrObject
                , CSigContainer::eCOLTYP_FLOAT
//                , sizeof(float)
                );
              }
              else if(_IsHashed(eMIFMID_DATE) == TRUE) // ........................
              {
                AddColumn
                ( l_oStrObject
                , CSigContainer::eCOLTYP_DATE
//                , 6
                );
              }
              else if(_IsHashed(eMIFMID_LOGICAL) == TRUE) // .....................
              {
                AddColumn
                ( l_oStrObject
                , CSigContainer::eCOLTYP_LOGICAL
//                , 1
                );
              }
              else{}

              l_nLoop -= 1;
            }

// MODIF_KOCH
            // ATTENTION : les données du fichier MID ne sont plus stockées dans mp_asStringPool !!!
            m_poSigContainer->PrepareColumnStorage(); // On prépare les tableaux pour stocker les données
// MODIF_KOCH
          }
          else if(_IsHashed(eMIFMID_DATA) == TRUE)
          { // UNE FOIS QUE L'ON RENTRE DANS LA SECTION 'DATA', ON EN SORT PLUS JUSQU'A LA FIN DU FICHIER
            while
            (
                 (m_bStop == FALSE)
              && (LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS, TRUE))
            )
            { // Section DATA ===================================================
              if(GetElement(0).Find('(') >= 0)
              {
                ParseFunctionArguments();
              }
              else{}

              l_oStrTempo      = GetElement(0); // Peut être un objet complexe (pour les messages d'erreur)
              l_nCplxObjHashed = m_nHashed;     // Besoin plus bas pour _IsHashed(objets_complexes, l_nCplxObjHashed)

              // On traite d'abord les attributs des objets, pour une question de simplification de la boucle de parsing.

              // En principe on a déjà lu un objet quand il s'agit de traiter un paramètre/attribut
              // Si ce n'est pas le cas, c'est que le fichier est foireux et que ça va planter grââââve de toute façon
              if(_IsHashed(eMIFMID_SYMBOL) == TRUE)
              {
                CSigContainer::sSigSymbol l_sSigSymbol;
            
                ParseFunctionArguments();

                l_sSigSymbol.nType  = m_aoStrLineElements.GetSize();
                l_sSigSymbol.nColor = ATOI(GetElement(2));
                l_sSigSymbol.nSize  = ATOI(GetElement(3));

                switch(l_sSigSymbol.nType)
                {
                  case 7 :
                    l_sSigSymbol.nFontOrFileNameIndex = m_poSigContainer->AddString(GetElement(4)); // Fontname
                    l_sSigSymbol.nFontOrCustomStyle   = ATOI(GetElement(5));
                    l_sSigSymbol.nRotation            = ATOD(GetElement(6));
                  case 4 :
                    l_sSigSymbol.nShape = ATOI(GetElement(1));
                    break;
                  case 5 :
                    l_sSigSymbol.nFontOrFileNameIndex = m_poSigContainer->AddString(GetElement(1)); // Filename
                    l_sSigSymbol.nFontOrCustomStyle   = ATOI(GetElement(4));
                  default :
                    break;
                }

                m_poSigContainer->SetObjectSymbol(l_sSigSymbol);
              }
              else if(_IsHashed(eMIFMID_PEN) == TRUE)
              {
                CSigContainer::sSigPen l_sSigPen;

                ParseFunctionArguments();

                l_sSigPen.nWidth   = ATOI(GetElement(1)); // width
                l_sSigPen.nPattern = ATOI(GetElement(2)); // pattern
                l_sSigPen.nColor   = ATOI(GetElement(3)); // color

                m_poSigContainer->SetObjectPen(l_sSigPen);
              }
              else if(_IsHashed(eMIFMID_BRUSH) == TRUE)
              {
                CSigContainer::sSigBrush l_sSigBrush;

                ParseFunctionArguments();

                l_sSigBrush.nPattern   = ATOI(GetElement(1)); // pattern
                l_sSigBrush.nForeColor = ATOI(GetElement(2)); // forecolor
            
                if(m_aoStrLineElements.GetSize() == 4)
                {
                  l_sSigBrush.nBackColor = ATOI(GetElement(3)); // backcolor
                }
                else
                {
                  l_sSigBrush.nBackColor = l_sSigBrush.nForeColor;
                }

                m_poSigContainer->SetObjectBrush(l_sSigBrush);
              }
              else if(_IsHashed(eMIFMID_FONT) == TRUE)
              {
                CSigContainer::sSigFont l_sSigFont;

                ParseFunctionArguments();

                l_sSigFont.nFontNameIndex = m_poSigContainer->AddString(GetElement(1)); // fontname
                l_sSigFont.nStyle         = ATOI(GetElement(2)); // style
                l_sSigFont.nSize          = ATOI(GetElement(3)); // size
                l_sSigFont.nForeColor     = ATOI(GetElement(4)); // forecolor
            
                if(m_aoStrLineElements.GetSize() == 6)
                {
                  l_sSigFont.nBackColor = ATOI(GetElement(5)); // backcolor
                }
                else
                {
                  l_sSigFont.nBackColor = l_sSigFont.nForeColor;
                }

                m_poSigContainer->SetObjectFont(l_sSigFont);
              }
              else if(_IsHashed(eMIFMID_SMOOTH) == TRUE)
              {
                CSigContainer::sSigSmooth l_sSigSmooth;

                l_sSigSmooth.bSmooth = TRUE; // for pline

                m_poSigContainer->SetObjectSmooth(l_sSigSmooth);
              }
              else if(_IsHashed(eMIFMID_SPACING) == TRUE)
              {
                l_sSigText.nValid  |= CSigContainer::eSIGTXT_SPACING;
                l_sSigText.nSpacing = ATOD(GetElement(1));

                m_poSigContainer->SetObjectText(l_sSigText);
              }
              else if(_IsHashed(eMIFMID_JUSTIFY) == TRUE)
              {
                l_sSigText.nValid |= CSigContainer::eSIGTXT_JUSTIFY;

                if(_IsHashed(eMIFMID_LEFT, GetElement(1)) == TRUE)
                {
                  l_sSigText.nJustify = 0;
                }
                else if(_IsHashed(eMIFMID_CENTER, GetElement(1)) == TRUE)
                {
                  l_sSigText.nJustify = 1;
                }
                else if(_IsHashed(eMIFMID_RIGHT, GetElement(1)) == TRUE)
                {
                  l_sSigText.nJustify = 2;
                }
                else{}

                m_poSigContainer->SetObjectText(l_sSigText);
              }
              else if(_IsHashed(eMIFMID_ANGLE) == TRUE)
              {
                l_sSigText.nValid |= CSigContainer::eSIGTXT_ANGLE;
                l_sSigText.nAngle  = ATOD(GetElement(1));

                m_poSigContainer->SetObjectText(l_sSigText);
              }
              else if(_IsHashed(eMIFMID_LABEL) == TRUE)
              {
                l_sSigText.nValid |= CSigContainer::eSIGTXT_LABEL;

                if(_IsHashed(eMIFMID_SIMPLE, GetElement(2)) == TRUE)
                {
                  l_sSigText.nLabelLine = 0;
                }
                else if(_IsHashed(eMIFMID_ARROW, GetElement(2)) == TRUE)
                {
                  l_sSigText.nLabelLine = 1;
                }
                else{}

                l_sSigText.nX = ATOD(GetElement(3));
                l_sSigText.nY = ATOD(GetElement(4));

                m_poSigContainer->SetObjectText(l_sSigText);
              }
              else if(_IsHashed(eMIFMID_CENTER) == TRUE)
              { // Center X Y
                SetObjectCenter
                ( ATOD(GetElement(1))
                , ATOD(GetElement(2))
                );
              }
              else
              { // LECTURE DES OBJETS (PUISQUE CE N'EST PAS UN ATTRIBUT)
#ifdef DEBUGSTUFF
                l_oStrObject = l_oStrTempo;

                if(GetPos(CSigContainer::eSigFileId_OBJECTS) > 0x06fffb0)
                {
                  l_nTempo = l_nTempo;
                }
                else{}
#endif // DEBUGSTUFF

                l_sSigText.nValid = 0; // SPECIFIC

                if(_IsHashed(eMIFMID_POINT) == TRUE) // --------------------------
                { // Point
                  AddObject(CSigContainer::eOBJTYP_POINT);

                  AddPoint(GetElement(1), GetElement(2)); // X Y
                }
                else if(_IsHashed(eMIFMID_LINE) == TRUE) // ----------------------
                { // Line
                  AddObject(CSigContainer::eOBJTYP_LINE);

                  AddPoint(GetElement(1), GetElement(2)); // X1 Y1
                  AddPoint(GetElement(3), GetElement(4)); // X2 Y2
                }
                else if(_IsHashed(eMIFMID_PLINE) == TRUE) // ---------------------
                { // Polyline
                  int l_nBound;

                  if(_IsHashed(eMIFMID_MULTIPLE, GetElement(1)) == TRUE)
                  {
                    l_oStrTempo = GetElement(1); // On récupère le tag pour la gestion des objets complexes

                    l_nLoop = ATOI(GetElement(2)); // numsections
                    AddObject(CSigContainer::eOBJTYP_MULTIPLE, l_nLoop); // Nombre d'objets

                    // On charge le nombre de points du premier (ou seul) polygone
                    LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);
                    l_nTempo = ATOI(GetElement(0));

                    l_nBound = 2; // ATTENTION A CA, TEST PLUS BAS !!!
                  }
                  else
                  {
                    l_nLoop = 1; // 1 numsection

                    if(GetElement(1) == "")
                    { // Si le nombre de points est sur la ligne suivante
                      LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);
                      l_nTempo = ATOI(GetElement(0));

                      l_nBound = 0; // ATTENTION A CA, TEST PLUS BAS !!!
                    }
                    else
                    { // Si le nombre de points est sur la même ligne
                      l_nTempo = ATOI(GetElement(1));

                      l_nBound = 1; // ATTENTION A CA, TEST PLUS BAS !!!
                    }
                  }

                  // Vérifie que le format de la ligne 'Pline' était le bon
                  if(m_aoStrLineElements.GetUpperBound() != l_nBound)
                  { // Erreur s'il ne reste pas des arguments à lire
                    Stop();

                    m_oStrLastError.Format
                    ( "L'objet %s à l'offset 0x%08X comporte un nombre de points %d erroné."
                    , l_oStrTempo
                    , l_nObjOffset
                    , l_nTempo
                    );
                  }
                  else
                  {
                    if(_IsHashed(eMIFMID_PLINE) == TRUE)
                    { // Si c'est une Polyline simple, il faut créer l'objet avec le nombre de points
                      AddObject(CSigContainer::eOBJTYP_POLYLINE, l_nTempo); // Il faut créer l'objet avant d'en charger les données
                    }
                    else{}
                  }
                }
                else if(_IsHashed(eMIFMID_REGION) == TRUE) // --------------------
                { // Region
                  l_nLoop = ATOI(GetElement(1)); // numpolygons
                  AddObject(CSigContainer::eOBJTYP_REGION, l_nLoop); // Nombre d'objets

                  // On charge le nombre de points du premier (ou seul) polygone
                  LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);
                  l_nTempo = ATOI(GetElement(0));

                  if(m_aoStrLineElements.GetUpperBound() != 0)
                  {
                    Stop();

                    m_oStrLastError.Format
                    ( "L'objet %s à l'offset 0x%08X comporte un nombre de points %d erroné."
                    , l_oStrTempo
                    , l_nObjOffset
                    , l_nTempo
                    );
                  }
                  else{}
                }
                else if(_IsHashed(eMIFMID_ARC) == TRUE) // -----------------------
                { // Arc
                  AddObject(CSigContainer::eOBJTYP_ARC);

                  AddPoint(GetElement(1), GetElement(2)); // X1 Y1
                  AddPoint(GetElement(3), GetElement(4)); // X2 Y2
                  LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);
                  AddPoint(GetElement(0), GetElement(1)); // A B
                }
                else if(_IsHashed(eMIFMID_TEXT) == TRUE) // ----------------------
                { // Text
                  CSigContainer::sSigObject* l_psTempoObject;

                  l_psTempoObject = AddObject(CSigContainer::eOBJTYP_TEXT);

                  l_oStrTempo = GetElement(1); // textstring
                  l_oStrTempo.Remove('"');

                  if(l_psTempoObject != NULL)
                  {
                    l_psTempoObject->nTextIndex = AddString(l_oStrTempo);
                  }
                  else{}

                  LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);
//                  AddRow(m_aoStrLineElements);

                  AddPoint(GetElement(0), GetElement(1)); // X1 Y1
                  AddPoint(GetElement(2), GetElement(3)); // X2 Y2
                }
                else if(_IsHashed(eMIFMID_RECT) == TRUE) // ----------------------
                { // Rectangle
                  AddObject(CSigContainer::eOBJTYP_RECTANGLE);
                
                  AddPoint(GetElement(1), GetElement(2)); // X1 Y1
                  AddPoint(GetElement(3), GetElement(4)); // X2 Y2
                }
                else if(_IsHashed(eMIFMID_ROUNDRECT) == TRUE) // -----------------
                { // Rounded rectangle
                  AddObject(CSigContainer::eOBJTYP_ROUNDRECT);
                
                  AddPoint(GetElement(1), GetElement(2)); // X1 Y1
                  AddPoint(GetElement(3), GetElement(4)); // X2 Y2
                  LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);
                  AddPoint(GetElement(0), (XString) "0.0"); // A
                }
                else if(_IsHashed(eMIFMID_ELLIPSE) == TRUE) // -------------------
                { // Ellipse
                  AddObject(CSigContainer::eOBJTYP_ELLIPSE);
                
                  AddPoint(GetElement(1), GetElement(2)); // X1 Y1
                  AddPoint(GetElement(3), GetElement(4)); // X2 Y2
                }
                else if(_IsHashed(eMIFMID_MULTIPOINT) == TRUE)
                {
                  l_nLoop = 1; // 1 section
                  l_nTempo = ATOI(GetElement(1)); // nombre de points

                  AddObject(CSigContainer::eOBJTYP_MULTIPOINT, l_nTempo); // Il faut créer l'objet avant d'en charger les données
                }
                else if(_IsHashed(eMIFMID_COLLECTION) == TRUE)
                {
// MODIF_KOCH
  // ==== PAS FINI SIG !
// MODIF_KOCH
                }
                else
                {
                  Stop();

                  m_oStrLastError.Format
                  ( "L'objet %s à l'offset 0x%08X n'est pas geré."
                  , l_oStrTempo
                  , GetPos(CSigContainer::eSigFileId_OBJECTS)
                  );
                }

// CHARGEMENT DES DONNEES DEPUIS LE FICHIER MID
                // On charge la ligne de données correspondante
                if(LoadNextLineParsed(CSigContainer::eSigFileId_DATABASE, FALSE, m_oStrDataDelimiter) != FALSE)
                { // On découpe la ligne et on range chaque élément dans la bonne colonne
                  AddRow(m_aoStrLineElements);
                }
                else{}

// ON TERMINE PAR LE CHARGEMENT DES OBJETS DITS 'COMPLEXES' (PLUSIEURS POINTS ET SECTIONS)
                // Les objets complexes
                if
                (
                     (_IsHashed(eMIFMID_PLINE,      l_nCplxObjHashed) == TRUE) // -------
                  || (_IsHashed(eMIFMID_MULTIPLE,   l_nCplxObjHashed) == TRUE) // -------
                  || (_IsHashed(eMIFMID_REGION,     l_nCplxObjHashed) == TRUE) // -------
                  || (_IsHashed(eMIFMID_MULTIPOINT, l_nCplxObjHashed) == TRUE) // -------
                )
                { // Polyline, Multiple ou Region
                  if
                  (
                       (_IsHashed(eMIFMID_MULTIPLE, l_nCplxObjHashed) == TRUE)
                    || (_IsHashed(eMIFMID_REGION,   l_nCplxObjHashed) == TRUE)
                  )
                  {
                    AddObject(CSigContainer::eOBJTYP_POLYLINE, l_nTempo); // On crée une nouvelle Polyline
                  }
                  else{}

                  while
                  (
                       (m_bStop == FALSE)
                    && (l_nLoop != 0)
                  )
                  { // Pour chaque section
#ifdef DEBUGSTUFF
                    if(GetPos(CSigContainer::eSigFileId_OBJECTS) > 3143670)
                    { // Aide pour le débug...
                      l_nTempo = l_nTempo;
                    }
                    else{}

                    if(l_nTempo > 2000)
                    {
                      l_nTempo = l_nTempo;
                    }
                    else{}
#endif // DEBUGSTUFF

                    while
                    (
                         (m_bStop == FALSE)
                      && (l_nTempo != 0)
                    )
                    { // On charge les points qui composent les objets complexes
                      l_nTempo -= 1;

                      LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);
                      if(AddPoint(GetElement(0), GetElement(1)) < 0)
                      {
                        Stop();

                        m_oStrLastError.Format
                        ( "L'objet %s à l'offset 0x%08X comporte un paramètre %s non geré."
                        , l_oStrTempo
                        , l_nObjOffset
                        , GetElement(0)
                        );
                      }
                      else{}

                      if
                      (
                           (i_poSkinProgress != NULL)
                        && ((l_nTempo % 500) == 0)
                      )
                      { // On met à jour la barre de progression toutes les 500 lignes
                        StepToPos(CSigContainer::eSigFileId_OBJECTS, i_poSkinProgress);
                      }
                      else{}
                    }

                    l_nLoop -= 1;

                    if(l_nLoop != 0)
                    { // S'il reste des polygones à charger, on charge le nombre de points du polygone suivant
                      l_nObjOffset = GetPos(CSigContainer::eSigFileId_OBJECTS); // On sauve le pointeur sur le début de l'objet
                    
                      LoadNextLineParsed(CSigContainer::eSigFileId_OBJECTS);

                      l_nTempo = ATOI(GetElement(0));

                      if(m_aoStrLineElements.GetUpperBound() != 0)
                      {
                        Stop();

                        m_oStrLastError.Format
                        ( "L'objet %s à l'offset 0x%08X comporte un nombre de points %d erroné."
                        , l_oStrTempo
                        , l_nObjOffset
                        , l_nTempo
                        );
                      }
                      else
                      {
                        AddObject(CSigContainer::eOBJTYP_POLYLINE, l_nTempo); // On crée une nouvelle Polyline
                      }
                    }
                    else{}
                  }
            
                  if
                  (
                       (_IsHashed(eMIFMID_MULTIPLE, l_nCplxObjHashed) == TRUE)
                    || (_IsHashed(eMIFMID_REGION,   l_nCplxObjHashed) == TRUE)
                  )
                  {
                    if(_IsHashed(eMIFMID_MULTIPLE, l_nCplxObjHashed) == TRUE)
                    {
                      EndObject(CSigContainer::eOBJTYP_MULTIPLE);
                    }
                    else
                    {
                      EndObject(CSigContainer::eOBJTYP_REGION);
                    }
                  }
                  else{}
                }
                else{} // FIN OBJETS COMPLEXES
              } // Objet

              l_nObjOffset = GetPos(CSigContainer::eSigFileId_OBJECTS); // On sauve le pointeur à la position de l'objet suivant (plus facile pour le débug)

              if(i_poSkinProgress != NULL)
              {
                StepToPos
                ( CSigContainer::eSigFileId_OBJECTS
                , i_poSkinProgress
                );
              }
              else{}
            } // While
          } // Data
          else{}

          l_nObjOffset = GetPos(CSigContainer::eSigFileId_OBJECTS); // On sauve le pointeur à la position de l'objet suivant (plus facile pour le débug)

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
BOOL CSigMapInfo::FileSave
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
BOOL CSigMapInfo::FileSave
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
BOOL CSigMapInfo::FileSave
( CSkinProgress* i_poSkinProgress // = NULL
)
{
  CString                    l_oStrTempo;
  CString                    l_oStrFormat;

#ifndef USE_POLYGON
  sCoord                     l_asSigPoint[2];
#else // USE_POLYGON
  sSigPoint                  l_asSigPoint[2];
#endif // USE_POLYGON
  
  int                        l_nParent;
  int                        l_nColSize;
  int                        l_nColLoop;
  int                        l_nMulSize;
//  int                        l_nMulLoop;
  int                        l_nObjSize;
  int                        l_nObjLoop;

  bool                       l_bSkipObject;

  CSigContainer::sSigColumn* l_psSigColumn;
  CSigContainer::sSigObject* l_psSigObject;
  CSigContainer::sSigSymbol* l_psSigSymbol;
  CSigContainer::sSigPen*    l_psSigPen;
  CSigContainer::sSigBrush*  l_psSigBrush;
  CSigContainer::sSigFont*   l_psSigFont;
  CSigContainer::sSigSmooth* l_psSigSmooth;
  CSigContainer::sSigText*   l_psSigText;

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

  // Ecriture VERSION (Version 300)
  l_oStrTempo.Format
  ( "Version %d\n"
  , m_poSigContainer->m_sHeader.nVersion
  );

  WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

  // Ecriture CHARSET (Charset "WindowsLatin1")
  if(m_poSigContainer->m_sHeader.nCharset >= 0)
  {
    l_oStrTempo.Format
    ( "Charset \"%s\"\n"
    , m_poSigContainer->GetString(m_poSigContainer->m_sHeader.nCharset)
    );

    WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
  }
  else{}

  // Ecriture DELIMITER (Delimiter ";" -> si différent de '\t')
  if(m_oStrDataDelimiter != '\t')
  {
    l_oStrTempo.Format
    ( "Delimiter \"%c\"\n"
    , (int) m_oStrDataDelimiter
    );

    WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
  }
  else{}

  // Ecriture de COORDSYS (CoordSys Earth Projection 3, 1002, "m",
  //                                                               0.000000000000, 46.800000000000, 45.898918964419, 47.696014502038,
  //                                                                                                                                  600000.000, 2200000.000)
  switch(m_poSigContainer->m_sHeader.sProjection.nSyntax)
  {
    case 0 : // CoordSys Earth
      l_oStrTempo.Format
      ( "CoordSys Earth Projection %d, %d, \"%s\""
      , m_poSigContainer->m_sHeader.sProjection.nTypeOrTableName
      , m_poSigContainer->m_sHeader.sProjection.nDatumOrWindowID
      , m_poSigContainer->m_sHeader.sProjection.anUnitName
      );

      if
      (
           (m_poSigContainer->m_sHeader.sProjection.nOriginLon         != 0.0)
        || (m_poSigContainer->m_sHeader.sProjection.nOriginLat         != 0.0)
        || (m_poSigContainer->m_sHeader.sProjection.nStandartParallel1 != 0.0)
        || (m_poSigContainer->m_sHeader.sProjection.nStandartParallel2 != 0.0)
      )
      {
        l_oStrFormat.Format
        ( ", %.12f, %.12f, %.12f, %.12f"
        , m_poSigContainer->m_sHeader.sProjection.nOriginLon
        , m_poSigContainer->m_sHeader.sProjection.nOriginLat
        , m_poSigContainer->m_sHeader.sProjection.nStandartParallel1
        , m_poSigContainer->m_sHeader.sProjection.nStandartParallel2
        );

        l_oStrTempo += l_oStrFormat;

        if
        (
             (m_poSigContainer->m_sHeader.sProjection.nAzimut      != 0.0)
          || (m_poSigContainer->m_sHeader.sProjection.nScaleFactor != 0.0)
        )
        {
          l_oStrFormat.Format
          ( ", %.3f, %.3f"
          , m_poSigContainer->m_sHeader.sProjection.nAzimut
          , m_poSigContainer->m_sHeader.sProjection.nScaleFactor
          );

          l_oStrTempo += l_oStrFormat;

          if
          (
               (m_poSigContainer->m_sHeader.sProjection.nFalseEasting  != 0.0)
            || (m_poSigContainer->m_sHeader.sProjection.nFalseNorthing != 0.0)
            || (m_poSigContainer->m_sHeader.sProjection.nRange         != 0.0)
          )
          {
            l_oStrFormat.Format
            ( ", %f, %f, %f"
            , m_poSigContainer->m_sHeader.sProjection.nFalseEasting
            , m_poSigContainer->m_sHeader.sProjection.nFalseNorthing
            , m_poSigContainer->m_sHeader.sProjection.nRange
            );

            l_oStrTempo += l_oStrFormat;
          }
          else{}
        }
        else{}
      }
      else{}

      l_oStrTempo = l_oStrTempo + "\n";

      WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

      if
      (
           (m_poSigContainer->m_sHeader.sAffine.nXaxisScaleStretch != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew    != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nXaxisShift        != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nYaxisScaleStretch != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew    != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nYaxisShift        != 0.0)
      )
      {
        l_oStrTempo.Format
        ( "Affine Units %s, %f, %f, %f, %f, %f, %f\n"
        , m_poSigContainer->m_sHeader.sAffine.anUnitName
        , m_poSigContainer->m_sHeader.sAffine.nXaxisScaleStretch
        , m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew
        , m_poSigContainer->m_sHeader.sAffine.nXaxisShift
        , m_poSigContainer->m_sHeader.sAffine.nYaxisScaleStretch
        , m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew
        , m_poSigContainer->m_sHeader.sAffine.nYaxisShift
        );

        WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
      }
      else{}

/*
      if
      (
           (m_poSigContainer->m_sHeader.sBound.sMin.nLonX != m_poSigContainer->m_sHeader.sBound.sMax.nLonX)
        || (m_poSigContainer->m_sHeader.sBound.sMin.nLatY != m_poSigContainer->m_sHeader.sBound.sMax.nLatY)
      )
      {
        l_oStrTempo.Format
        ( "Bounds (%f, %f) (%f, %f)\n"
        , m_poSigContainer->m_sHeader.sBound.sMin.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMin.nLatY
        , m_poSigContainer->m_sHeader.sBound.sMax.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMax.nLatY
        );

        WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
      }
      else{}
*/
      break;
    case 1 : // CoordSys Nonearth
      l_oStrTempo = "CoordSys Nonearth";

      WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

      if
      (
           (m_poSigContainer->m_sHeader.sAffine.nXaxisScaleStretch != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew    != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nXaxisShift        != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nYaxisScaleStretch != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew    != 0.0)
        || (m_poSigContainer->m_sHeader.sAffine.nYaxisShift        != 0.0)
      )
      {
        l_oStrTempo.Format
        ( "Affine Units %s, %f, %f, %f, %f, %f, %f\n"
        , m_poSigContainer->m_sHeader.sAffine.anUnitName
        , m_poSigContainer->m_sHeader.sAffine.nXaxisScaleStretch
        , m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew
        , m_poSigContainer->m_sHeader.sAffine.nXaxisShift
        , m_poSigContainer->m_sHeader.sAffine.nYaxisScaleStretch
        , m_poSigContainer->m_sHeader.sAffine.nXaxisRotatSkew
        , m_poSigContainer->m_sHeader.sAffine.nYaxisShift
        );

        WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
      }
      else{}

      l_oStrTempo.Format
      ( "Units %s\n"
      , m_poSigContainer->m_sHeader.sProjection.anUnitName
      );

      WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

/*
      if
      (
           (m_poSigContainer->m_sHeader.sBound.sMin.nLonX != m_poSigContainer->m_sHeader.sBound.sMax.nLonX)
        || (m_poSigContainer->m_sHeader.sBound.sMin.nLatY != m_poSigContainer->m_sHeader.sBound.sMax.nLatY)
      )
      {
        l_oStrTempo.Format
        ( "Bounds (%f, %f) (%f, %f)\n"
        , m_poSigContainer->m_sHeader.sBound.sMin.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMin.nLatY
        , m_poSigContainer->m_sHeader.sBound.sMax.nLonX
        , m_poSigContainer->m_sHeader.sBound.sMax.nLatY
        );

        WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
      }
      else{}
*/
      break;
    case 2 : // CoordSys Layout
      l_oStrTempo.Format
      ( "CoordSys Layout Units %s\n"
      , m_poSigContainer->m_sHeader.sProjection.anUnitName
      );

      WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
      break;
    case 3 : // CoordSys Table
      l_oStrTempo.Format
      ( "CoordSys Table %s\n"
      , m_poSigContainer->GetString(m_poSigContainer->m_sHeader.sProjection.nTypeOrTableName)
      );

      WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
      break;
    case 4 : // CoordSys Window
      l_oStrTempo.Format
      ( "CoordSys Window %d\n"
      , m_poSigContainer->m_sHeader.sProjection.nDatumOrWindowID
      );

      WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
      break;
    case -1 : // Lat/Lon
    default :
      break;
  }

  // Ecriture de TRANSFORM (Transform -1,0,0,0)
  if
  (
       (m_poSigContainer->m_sHeader.sTransform.sTransformMultiplier.nLonX   != 0.0)
    || (m_poSigContainer->m_sHeader.sTransform.sTransformMultiplier.nLatY   != 0.0)
    || (m_poSigContainer->m_sHeader.sTransform.sTransformDisplacement.nLonX != 0.0)
    || (m_poSigContainer->m_sHeader.sTransform.sTransformDisplacement.nLatY != 0.0)
  )
  { // Seulement si y'a une transformation appliquée
    l_oStrTempo.Format
    ( "Transform %f, %f, %f, %f\n"
    , m_poSigContainer->m_sHeader.sTransform.sTransformMultiplier.nLonX
    , m_poSigContainer->m_sHeader.sTransform.sTransformMultiplier.nLatY
    , m_poSigContainer->m_sHeader.sTransform.sTransformDisplacement.nLonX
    , m_poSigContainer->m_sHeader.sTransform.sTransformDisplacement.nLatY
    );

    WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
  }
  else{}

  // Ecriture de COLUMNS (Columns 3)
  l_nColSize = m_poSigContainer->GetColumnCount();

  if(l_nColSize > 0)
  {
    l_oStrTempo.Format
    ( "Columns %d\n"
    , l_nColSize
    );

    WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

    for
    ( l_nColLoop  = 0
    ; l_nColLoop <  l_nColSize
    ; l_nColLoop += 1
    )
    {
      l_psSigColumn = (CSigContainer::sSigColumn*) m_poSigContainer->GetColumnPointer(l_nColLoop);

      switch(l_psSigColumn->nType)
      {
        case CSigContainer::eCOLTYP_CHAR :
          l_oStrTempo.Format
          ( "  %s char(%d)\n"
          , m_poSigContainer->GetString(l_psSigColumn->nNameIndex)
          , l_psSigColumn->nSize
          );
          break;
        case CSigContainer::eCOLTYP_INTERGER :
          l_oStrTempo.Format
          ( "  %s integer\n"
          , m_poSigContainer->GetString(l_psSigColumn->nNameIndex)
          );
          break;
        case CSigContainer::eCOLTYP_SMALLINT :
          l_oStrTempo.Format
          ( "  %s smallint\n"
          , m_poSigContainer->GetString(l_psSigColumn->nNameIndex)
          );
          break;
        case CSigContainer::eCOLTYP_DECIMAL :
          l_oStrTempo.Format
          ( "  %s decimal(%d, %d)\n"
          , m_poSigContainer->GetString(l_psSigColumn->nNameIndex)
          , l_psSigColumn->nSize >> 8
          , l_psSigColumn->nSize & 0xFF
          );
          break;
        case CSigContainer::eCOLTYP_FLOAT :
          l_oStrTempo.Format
          ( "  %s float\n"
          , m_poSigContainer->GetString(l_psSigColumn->nNameIndex)
          );
          break;
        case CSigContainer::eCOLTYP_DATE :
          l_oStrTempo.Format
          ( "  %s date\n"
          , m_poSigContainer->GetString(l_psSigColumn->nNameIndex)
          );
          break;
        case CSigContainer::eCOLTYP_LOGICAL :
          l_oStrTempo.Format
          ( "  %s logical\n"
          , m_poSigContainer->GetString(l_psSigColumn->nNameIndex)
          );
          break;
        default :
          l_oStrTempo.Format
          ( "  BAD_FORMAT(%d)\n"
          , l_nColLoop
          );
          break;
      }

      WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
    }
  }
  else{}

  // Section DATA =============================================================

  WriteLine(CSigContainer::eSigFileId_OBJECTS, "Data\n");

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

            l_oStrTempo.Format
            ( "Point %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
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

            l_oStrTempo.Format
            ( "Line %f %f %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            break;
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
              case CSigContainer::eOBJTYP_REGION :
                l_oStrTempo.Format
                ( "Region %d\n"
                , l_nMulSize
                );
                break;
              case CSigContainer::eOBJTYP_MULTIPLE :
                l_oStrTempo.Format
                ( "Pline Multiple %d\n"
                , l_nMulSize
                );
                break;
              case CSigContainer::eOBJTYP_POLYLINE :
                l_oStrTempo = "Pline\n";
                break;
            }
        
            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

            do
            {
              // Nonbre de points
#ifndef USE_POLYGON
              l_nObjSize = l_psSigObject->nPointNumber;
#else // USE_POLYGON
              l_nObjSize = l_psSigObject->poPolygon->GetSize();
#endif // USE_POLYGON

              if(l_nObjSize > 0)
              {
                l_oStrTempo.Format
                ( "  %d\n"
                , l_nObjSize
                );

                WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

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

                  l_oStrTempo.Format
                  ( "%f %f\n"
                  , l_asSigPoint[0].nLonX
                  , l_asSigPoint[0].nLatY
                  );

                  WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
                }
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

            l_oStrTempo.Format
            ( "Arc %f %f %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 2);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(2);
#endif // USE_POLYGON

            l_oStrTempo.Format
            ( "%f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            break;
          case CSigContainer::eOBJTYP_TEXT :
            // Ecriture TEXT (Text "textstring" \n X1 Y1 X2 Y2)
            l_oStrTempo.Format
            ( "Text \"%s\"\n"
            , m_poSigContainer->GetString(l_psSigObject->nTextIndex)
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

            l_oStrTempo.Format
            ( "%f %f %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            break;
          case CSigContainer::eOBJTYP_RECTANGLE :
            // Ecriture RECT (Rect X1 Y1 X2 Y2)
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

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
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

            l_oStrTempo.Format
            ( "Roundrect %f %f %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);

#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 2);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(2);
#endif // USE_POLYGON

            l_oStrTempo.Format
            ( "%f\n"
            , l_asSigPoint[0].nLonX
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            break;
          case CSigContainer::eOBJTYP_ELLIPSE :
            // Ecriture ELLIPSE (Ellipse X1 Y1 X2 Y2)
#ifndef USE_POLYGON
            l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
            l_asSigPoint[1] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 1);
#else // USE_POLYGON
            l_asSigPoint[0] = l_psSigObject->poPolygon->Point(0);
            l_asSigPoint[1] = l_psSigObject->poPolygon->Point(1);
#endif // USE_POLYGON

            l_oStrTempo.Format
            ( "Ellipse %f %f %f %f\n"
            , l_asSigPoint[0].nLonX
            , l_asSigPoint[0].nLatY
            , l_asSigPoint[1].nLonX
            , l_asSigPoint[1].nLatY
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
          case CSigContainer::eOBJTYP_MULTIPOINT :
            // Ecriture MULTIPOINT (Multipoint num_points)
#ifndef USE_POLYGON
            l_nObjSize = l_psSigObject->nPointNumber;
#else // USE_POLYGON
            l_nObjSize = l_psSigObject->poPolygon->GetSize();
#endif // USE_POLYGON

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
#ifndef USE_POLYGON
              l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + l_nObjLoop);
#else // USE_POLYGON
              l_asSigPoint[0] = l_psSigObject->poPolygon->Point(l_nObjLoop);
#endif // USE_POLYGON

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
          default :
            // Ecriture NONE
            l_oStrTempo = "None";

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            break;
        }

        // ATTRIBUTS --------------------------------------------------------------

        // Ecriture SYMBOL (Symbol(shape, color, size)) -> POINT

        if(l_psSigObject->eObjectType == CSigContainer::eOBJTYP_POINT)
        {
          if
          (
               (l_psSigObject->nIndexSymbol >= 0)
            && ((l_psSigSymbol = (CSigContainer::sSigSymbol*) m_poSigContainer->GetObjectSymbol(l_psSigObject->nIndexSymbol)) != NULL)
          )
          {
            switch(l_psSigSymbol->nType)
            {
              case 7 : // TrueType Font Syntax = Symbol(shape, color, size, fontname, fontstyle, rotation) 
                l_oStrTempo.Format
                ( "  Symbol(%d, %d, %d, %s, %d, %f)\n"
                , l_psSigSymbol->nShape
                , l_psSigSymbol->nColor
                , l_psSigSymbol->nSize
                , m_poSigContainer->GetString(l_psSigSymbol->nFontOrFileNameIndex)
                , l_psSigSymbol->nFontOrCustomStyle
                , l_psSigSymbol->nRotation
                );
                break;
              case 5 : // Custom Bitmap File Syntax = Symbol(filename, color, size, customstyle)
                l_oStrTempo.Format
                ( "  Symbol(%s, %d, %d, %d)\n"
                , m_poSigContainer->GetString(l_psSigSymbol->nFontOrFileNameIndex)
                , l_psSigSymbol->nColor
                , l_psSigSymbol->nSize
                , l_psSigSymbol->nFontOrCustomStyle
                );
                break;
              case 4 : // MapInfo 3.0 Syntax = Symbol(shape, color, size)
              default :
                l_oStrTempo.Format
                ( "  Symbol(%d, %d, %d)\n"
                , l_psSigSymbol->nShape
                , l_psSigSymbol->nColor
                , l_psSigSymbol->nSize
                );
                break;
            }

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
          }
          else{}
        }
        else{}

        // Ecriture PEN (Pen(width, pattern, color)) -> LINE, PLINE, REGION, ARC, RECT, ROUNDRECT, ELLIPSE

        if
        (
             (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_LINE)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_POLYLINE)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_REGION)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_ARC)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_RECTANGLE)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_ROUNDRECT)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_ELLIPSE)
        )
        {
          if
          (
               (l_psSigObject->nIndexPen >= 0)
            && ((l_psSigPen = (CSigContainer::sSigPen*) m_poSigContainer->GetObjectPen(l_psSigObject->nIndexPen)) != NULL)
          )
          {
            l_oStrTempo.Format
            ( "  Pen(%d, %d, %d)\n"
            , l_psSigPen->nWidth
            , l_psSigPen->nPattern
            , l_psSigPen->nColor
            );

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
          }
          else{}
        }
        else{}

        // Ecriture BRUSH (Brush(pattern, forecolor, [backcolor])) -> REGION, RECT, ROUNDRECT, ELLIPSE, 

        if
        (
             (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_REGION)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_RECTANGLE)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_ROUNDRECT)
          || (l_psSigObject->eObjectType == CSigContainer::eOBJTYP_ELLIPSE)
        )
        {
          if
          (
               (l_psSigObject->nIndexBrush >= 0)
            && ((l_psSigBrush = (CSigContainer::sSigBrush*) m_poSigContainer->GetObjectBrush(l_psSigObject->nIndexBrush)) != NULL)
          )
          {
            if(l_psSigBrush->nForeColor != l_psSigBrush->nBackColor)
            {
              l_oStrTempo.Format
              ( "  Brush(%d, %d, %d)\n"
              , l_psSigBrush->nPattern
              , l_psSigBrush->nForeColor
              , l_psSigBrush->nBackColor
              );
            }
            else
            {
              l_oStrTempo.Format
              ( "  Brush(%d, %d)\n"
              , l_psSigBrush->nPattern
              , l_psSigBrush->nForeColor
              );
            }

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
          }
          else{}
        }
        else{}

        // Ecriture FONT (FONT ("fontname", style, size, forecolor [, backcolor] )) -> TEXT

        if(l_psSigObject->eObjectType == CSigContainer::eOBJTYP_TEXT)
        {
          if
          (
               (l_psSigObject->nIndexFont >= 0)
            && ((l_psSigFont = (CSigContainer::sSigFont*) m_poSigContainer->GetObjectFont(l_psSigObject->nIndexFont)) != NULL)
          )
          {
            if(l_psSigFont->nForeColor != l_psSigFont->nBackColor)
            {
              l_oStrTempo.Format
              ( "  Font(\"%s\", %d, %d, %d, %d)\n"
              , m_poSigContainer->GetString(l_psSigFont->nFontNameIndex)
              , l_psSigFont->nStyle
              , l_psSigFont->nSize
              , l_psSigFont->nForeColor
              , l_psSigFont->nBackColor
              );
            }
            else
            {
              l_oStrTempo.Format
              ( "  Font(\"%s\", %d, %d, %d)\n"
              , m_poSigContainer->GetString(l_psSigFont->nFontNameIndex)
              , l_psSigFont->nStyle
              , l_psSigFont->nSize
              , l_psSigFont->nForeColor
              );
            }

            WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
          }
          else{}
        }
        else{}

        // Ecriture SMOOTH (Smooth) -> PLINE

        if(l_psSigObject->eObjectType == CSigContainer::eOBJTYP_POLYLINE)
        {
          if
          (
               (l_psSigObject->nIndexSmooth >= 0)
            && ((l_psSigSmooth = (CSigContainer::sSigSmooth*) m_poSigContainer->GetObjectSmooth(l_psSigObject->nIndexSmooth)) != NULL)
          )
          {
            if(l_psSigSmooth->bSmooth == TRUE)
            {
              l_oStrTempo = "  Smooth\n";

              WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            }
            else{}
          }
          else{}
        }
        else{}

        if(l_psSigObject->eObjectType == CSigContainer::eOBJTYP_TEXT)
        {
          if
          (
               (l_psSigObject->nIndexText >= 0)
            && ((l_psSigText = (CSigContainer::sSigText*) m_poSigContainer->GetObjectText(l_psSigObject->nIndexText)) != NULL)
          )
          {
            // Ecriture SPACING (Spacing {1.0 | 1.5 | 2.0}) -> TEXT
            if((l_psSigText->nValid & CSigContainer::eSIGTXT_SPACING) != 0)
            {
              l_oStrTempo.Format
              ( "  Spacing %f\n"
              , l_psSigText->nSpacing
              );

              WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            }
            else{}

            // Ecriture JUSTIFY (Justify {Left | Center | Right}) -> TEXT
            if((l_psSigText->nValid & CSigContainer::eSIGTXT_JUSTIFY) != 0)
            {
              switch(l_psSigText->nJustify)
              {
                case 0 : // LEFT
                  l_oStrTempo = "  Justify Left";
                  break;
                case 1 : // CENTER
                  l_oStrTempo = "  Justify Center";
                  break;
                case 2 : // RIGHT
                  l_oStrTempo = "  Justify Right";
                  break;
                default :
                  l_oStrTempo = ""; //"  Justify None";
                  break;
              }

              if(l_oStrTempo.IsEmpty() == FALSE)
              {
                WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
              }
              else{}
            }
            else{}

            // Ecriture ANGLE (Angle text_angle) -> TEXT
            if((l_psSigText->nValid & CSigContainer::eSIGTXT_ANGLE) != 0)
            {
              l_oStrTempo.Format
              ( "  Angle %f\n"
              , l_psSigText->nAngle
              );

              WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            }
            else{}

            // Ecriture LABEL (Label Line {simple | arrow} X Y) -> TEXT
            if((l_psSigText->nValid & CSigContainer::eSIGTXT_LABEL) != 0)
            {
              switch(l_psSigText->nLabelLine)
              {
                case 0 : // SIMPLE
                  l_oStrTempo.Format
                  ( "  Label Line Simple %f %f\n"
                  , l_psSigText->nX
                  , l_psSigText->nY
                  );
                  break;
                case 1 : // ARROW
                  l_oStrTempo.Format
                  ( "  Label Line Arrow %f %f\n"
                  , l_psSigText->nX
                  , l_psSigText->nY
                  );
                  break;
                default :
                  l_oStrTempo.Format
                  ( "  Label Line None %f %f\n"
                  , l_psSigText->nX
                  , l_psSigText->nY
                  );
                  break;
              }
        
              WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
            }
            else{}
          }
          else{}
        }
        else{}

        // Ecriture CENTER (Center X Y) -> REGION

        if(l_psSigObject->eObjectType == CSigContainer::eOBJTYP_REGION)
        {
          if
          (
               (l_psSigObject->nIndexText >= 0)
            && ((l_psSigText = (CSigContainer::sSigText*) m_poSigContainer->GetObjectText(l_psSigObject->nIndexText)) != NULL)
          )
          {
            if((l_psSigText->nValid & CSigContainer::eSIGTXT_CENTER) != 0)
            {
              if
              (
                   (l_psSigObject->sCenter.nLonX != 0.0)
                && (l_psSigObject->sCenter.nLatY != 0.0)
              )
              {
                l_oStrTempo.Format
                ( "  Center %f %f\n"
                , l_psSigObject->sCenter.nLonX
                , l_psSigObject->sCenter.nLatY
                );

                WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
              }
              else
              {
#ifndef USE_POLYGON
                if(l_psSigObject->nPointNumber > 0)
#else // USE_POLYGON
                if(l_psSigObject->poPolygon != NULL)
#endif // USE_POLYGON
                {
#ifndef USE_POLYGON
                  l_asSigPoint[0] = *m_poSigContainer->GetCoord(l_psSigObject->nPointIndex + 0);
#else // USE_POLYGON
                  l_asSigPoint[0] = l_psSigObject->poPolygon->Centroid();
#endif // USE_POLYGON

                  l_oStrTempo.Format
                  ( "  Center %f %f\n"
                  , l_asSigPoint[0].nLonX
                  , l_asSigPoint[0].nLatY
                  );

                  WriteLine(CSigContainer::eSigFileId_OBJECTS, l_oStrTempo);
                }
                else{}
              }
            }
            else{}
          }
          else{}
        }
        else{}

        // DONNEES ----------------------------------------------------------------

        if(l_nColSize > 0)
        { // Première colonne
          l_oStrTempo = m_poSigContainer->GetColumnString(0, l_psSigObject);

          for
          ( l_nColLoop  = 1
          ; l_nColLoop <  l_nColSize
          ; l_nColLoop += 1
          )
          { // Colonnes suivantes, si il y en a...
            l_oStrTempo = l_oStrTempo + m_oStrDataDelimiter + m_poSigContainer->GetColumnString(l_nColLoop, l_psSigObject);
          }

          l_oStrTempo += "\n";

          WriteLine(CSigContainer::eSigFileId_DATABASE, l_oStrTempo);
        }
        else{}

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

  FileFlush();

  return FileClose();
}
