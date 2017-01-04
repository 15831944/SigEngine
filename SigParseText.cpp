// SigParseText.cpp: implementation of the CSig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SigParseText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// === CLASSE DE BASE : PARSEUR =======================================================================================

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
CSigParseText::CSigParseText
( const char* i_panStringName
)
{
  int  l_nLoop;

  //

#ifdef _DEBUG
  SetClassName(i_panStringName);
#endif // _DEBUG

  for
  ( l_nLoop  = 0
  ; l_nLoop <  CSigContainer::eSigFileId__END
  ; l_nLoop += 1
  )
  { // Les pointeurs CFileIO*
    m_poSigFile[l_nLoop] = NULL;
  }

  m_poSigContainer    = NULL;
  m_psSigObject       = NULL;

  m_oStrDataDelimiter = '\t'; // ';'; // Delimiteur par défaut

  m_oStrLastError     = ""; // Message d'erreur par défaut
  m_bStop             = FALSE;

  m_bBlockMode        = FALSE; // Container

  FileClose();
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
CSigParseText::~CSigParseText
(
)
{
  FileClose();

  AttachContainer(NULL);
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
BOOL CSigParseText::AttachContainer
( CSigContainer* i_poSigContainer
, BOOL           i_bRename // = TRUE
)
{
  if(i_poSigContainer != NULL)
  {
    if(m_poSigContainer != NULL)
    { // A la hussard, même s'il appartient à quelqu'un d'autre
      delete m_poSigContainer;
    }
    else{}

    m_poSigContainer = i_poSigContainer;

#ifdef _DEBUG
    if(i_bRename == TRUE)
    {
      m_poSigContainer->SetClassName(mp_oStrObjectName+"::m_poSigContainer");
    }
    else{}
#endif // _DEBUG

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
void CSigParseText::DetachContainer
( void
)
{
  m_poSigContainer = NULL; // Evite de se faire effacer à la destruction de l'objet
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
BOOL CSigParseText::CreateContainer
(
)
{
//  CSigContainer* l_poSigContainer = new CSigContainer(mp_oStrObjectName+"::m_poSigContainer");

  return AttachContainer(new CSigContainer(mp_oStrObjectName+"::m_poSigContainer"));
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
BOOL CSigParseText::AddColumn
( const char* i_panColName
, int         i_nColType
, int         i_nColSize // = 0
)
{
  if(m_poSigContainer != NULL)
  {
    m_poSigContainer->AddColumn
    ( i_panColName
    , i_nColType
    , i_nColSize
    );

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
CSigContainer::sSigObject*
CSigParseText::AddObject
( CSigContainer::eSigObjectType i_eObjectType
, int                           i_nPointNumber     // = 0
, const char*                   i_panStrObjectName // = NULL
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
, const char*                   i_panStrLayerName  // = NULL
// MODIF_KOCH 070328
)
{
  int l_nPointNumber;

  m_psSigObject = NULL;

  if(m_poSigContainer != NULL)
  {
    switch(i_eObjectType)
    {
      case CSigContainer::eOBJTYP_POLYLINE :
        l_nPointNumber = i_nPointNumber;
        break;
      case CSigContainer::eOBJTYP_ROOT :
      case CSigContainer::eOBJTYP_BLOCK :
      case CSigContainer::eOBJTYP_MULTIPLE :
      case CSigContainer::eOBJTYP_REGION :
        l_nPointNumber = 0;
        break;
      case CSigContainer::eOBJTYP_POINT :
        l_nPointNumber = 1;
        break;
      case CSigContainer::eOBJTYP_LINE :
      case CSigContainer::eOBJTYP_TEXT :
      case CSigContainer::eOBJTYP_RECTANGLE :
      case CSigContainer::eOBJTYP_ELLIPSE :
        l_nPointNumber = 2;
        break;
      case CSigContainer::eOBJTYP_ARC :
      case CSigContainer::eOBJTYP_ROUNDRECT :
        l_nPointNumber = 3;
        break;
      default :
        break;
    }

    if(i_eObjectType == CSigContainer::eOBJTYP_ROOT)
    {
      m_poSigContainer->CreateRoot();
    }
    else
    {
      m_psSigObject = m_poSigContainer->AddObject
      ( m_poSigContainer->CreateObject
        ( i_eObjectType
        , l_nPointNumber
        , i_panStrObjectName
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
        , i_panStrLayerName
// MODIF_KOCH 070328
        )
      , m_bBlockMode // <-- BLOCK !!!
      );

      if
      (
           (i_eObjectType == CSigContainer::eOBJTYP_BLOCK)
        || (i_eObjectType == CSigContainer::eOBJTYP_MULTIPLE)
        || (i_eObjectType == CSigContainer::eOBJTYP_REGION)
      )
      { // On descend un niveau hiérarchique
        m_psSigObject->nPointIndex = i_nPointNumber; // Nombre d'objets
        m_poSigContainer->HierarchyDown();
      }
      else{}
    }
  }
  else{}

  return m_psSigObject;
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
BOOL CSigParseText::EndObject
( int i_nObjectType
)
{
  switch(i_nObjectType)
  {
    case CSigContainer::eOBJTYP_BLOCK :
    case CSigContainer::eOBJTYP_MULTIPLE :
    case CSigContainer::eOBJTYP_REGION :
      m_poSigContainer->HierarchyUp();
      return TRUE;
      break;
    case CSigContainer::eOBJTYP_ROOT :
    case CSigContainer::eOBJTYP_POINT :
    case CSigContainer::eOBJTYP_LINE :
    case CSigContainer::eOBJTYP_POLYLINE :
    case CSigContainer::eOBJTYP_ARC :
    case CSigContainer::eOBJTYP_TEXT :
    case CSigContainer::eOBJTYP_RECTANGLE :
    case CSigContainer::eOBJTYP_ROUNDRECT :
    case CSigContainer::eOBJTYP_ELLIPSE :
    default :
      return FALSE;
      break;
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
int CSigParseText::AddPoint
( const char* i_panLonX
, const char* i_panLatY
, const char* i_panAltZ // = NULL
)
{
  if(m_poSigContainer != NULL)
  {
    return m_poSigContainer->AddPoint
    ( i_panLonX
    , i_panLatY
    , i_panAltZ
    );
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
int CSigParseText::AddRow
( XStringArray& i_paoStrLineElements
)
{
  int     l_nStringLoop;
  int     l_nStringIndex;
  int     l_nStringReturn = -1;
  XString l_oStrTempo;

  if(m_poSigContainer != NULL)
  {
    if(i_paoStrLineElements.GetSize() > 0)
    {
      for
      ( l_nStringLoop  = 0
      ; l_nStringLoop <  i_paoStrLineElements.GetSize()
      ; l_nStringLoop += 1
      )
      {
        l_oStrTempo = i_paoStrLineElements.GetAt(l_nStringLoop);

        l_oStrTempo.TrimLeft();
        l_oStrTempo.TrimRight();

        l_nStringIndex = m_poSigContainer->AddColumnString(l_oStrTempo, l_nStringLoop);
        
        if(l_nStringReturn == -1)
        {
          l_nStringReturn = l_nStringIndex;
        }
        else{}
      }

      if(m_psSigObject != NULL)
      {
        m_psSigObject->nRowDataIndex = l_nStringReturn;
      }
      else{}

      return l_nStringReturn;
    }
    else
    {
      return (-1);
    }
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
int CSigParseText::AddString
( const char* i_panText
)
{
  if(m_poSigContainer != NULL)
  {
    return m_poSigContainer->AddString(i_panText);
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
void CSigParseText::SetObjectCenter
( double i_nLonX
, double i_nLatY
, double i_nAltZ // = 0.0
)
{
  if(m_psSigObject != NULL)
  {
    m_psSigObject->sCenter.nLonX = i_nLonX;
    m_psSigObject->sCenter.nLatY = i_nLatY;
    m_psSigObject->sCenter.nAltZ = i_nAltZ;
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
BOOL CSigParseText::FileSelect
( char* i_panFileName
)
{
  return m_oPathSplitter.Split(i_panFileName);
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
BOOL CSigParseText::FileOpen
( char* i_panFileName
)
{
  FileSelect(i_panFileName);

  return FileOpen();
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
BOOL CSigParseText::FileOpen
(
)
{
  BOOL l_bResult = TRUE;
//  int  l_nLoop;

  //

  FileClose();

  if(*m_oPathSplitter.GetPath() != '\0')
  {
    m_poSigFile[CSigContainer::eSigFileId_OBJECTS]  = new CFileIO(m_oPathSplitter.GetPath(CPathSplit::ePS_FN, m_oStrFileExtObjects).GetBuffer(0));

    if(m_oStrFileExtDataBase.IsEmpty() == FALSE)
    { // Si il y a une base
      m_poSigFile[CSigContainer::eSigFileId_DATABASE] = new CFileIO(m_oPathSplitter.GetPath(CPathSplit::ePS_FN, m_oStrFileExtDataBase).GetBuffer(0));
    }
    else
    {
      m_poSigFile[CSigContainer::eSigFileId_DATABASE] = NULL;
    }

/*
    for
    ( l_nLoop  = 0
    ; l_nLoop <  CSigContainer::eSigFileId__END
    ; l_nLoop += 1
    )
    { // On vérifie que tout s'est bien passé jusque là
      if(m_poSigFile[l_nLoop] == NULL)
      {
        l_bResult = FALSE;
      }
      else{}
    }
*/

    if(l_bResult == FALSE)
    {
      FileClose();
    }
    else
    {
#ifdef _DEBUG
      if(m_poSigFile[CSigContainer::eSigFileId_OBJECTS] != NULL)
      {
        m_poSigFile[CSigContainer::eSigFileId_OBJECTS]->SetClassName(mp_oStrObjectName+"::m_poSigFile[eSigFileId_OBJECTS]");
      }
      else{}

      if(m_poSigFile[CSigContainer::eSigFileId_DATABASE] != NULL)
      {
        m_poSigFile[CSigContainer::eSigFileId_DATABASE]->SetClassName(mp_oStrObjectName+"::m_poSigFile[eSigFileId_DATABASE]");
      }
      else{}
#endif // _DEBUG
    }
  }
  else{}

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
BOOL CSigParseText::FileCreate
( char* i_panFileName
)
{
  BOOL l_bResult = TRUE;
//  int  l_nLoop;

  //

  FileClose();

  if(*m_oPathSplitter.GetPath() != '\0')
  {
    m_poSigFile[CSigContainer::eSigFileId_OBJECTS]  = new CFileIO();

    if(m_oStrFileExtDataBase.IsEmpty() == FALSE)
    { // Si il y a une base
      m_poSigFile[CSigContainer::eSigFileId_DATABASE] = new CFileIO();
    }
    else
    {
      m_poSigFile[CSigContainer::eSigFileId_DATABASE] = NULL;
    }

/*
    for
    ( l_nLoop  = 0
    ; l_nLoop <  CSigContainer::eSigFileId__END
    ; l_nLoop += 1
    )
    { // On vérifie que tout s'est bien passé jusque là
      if(m_poSigFile[l_nLoop] == NULL)
      {
        l_bResult = FALSE;
      }
      else{}
    }
*/

    if(l_bResult == FALSE)
    {
      FileClose();
    }
    else
    {
      if(m_poSigFile[CSigContainer::eSigFileId_OBJECTS] != NULL)
      {
#ifdef _DEBUG
        m_poSigFile[CSigContainer::eSigFileId_OBJECTS]->SetClassName(mp_oStrObjectName+"::m_poSigFile[eSigFileId_OBJECTS]");
#endif // _DEBUG
        m_poSigFile[CSigContainer::eSigFileId_OBJECTS]->FileCreate(m_oPathSplitter.GetPath(CPathSplit::ePS_FN, m_oStrFileExtObjects).GetBuffer(0));
      }
      else{}

      if(m_poSigFile[CSigContainer::eSigFileId_DATABASE] != NULL)
      {
#ifdef _DEBUG
        m_poSigFile[CSigContainer::eSigFileId_DATABASE]->SetClassName(mp_oStrObjectName+"::m_poSigFile[eSigFileId_DATABASE]");
#endif // _DEBUG
        m_poSigFile[CSigContainer::eSigFileId_DATABASE]->FileCreate(m_oPathSplitter.GetPath(CPathSplit::ePS_FN, m_oStrFileExtDataBase).GetBuffer(0));
      }
      else{}

    }
  }
  else{}

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
BOOL CSigParseText::FileFlush
(
)
{
  BOOL l_bResult = TRUE;
  int  l_nLoop;

  //

  for
  ( l_nLoop  = 0
  ; l_nLoop <  CSigContainer::eSigFileId__END
  ; l_nLoop += 1
  )
  {
    if(m_poSigFile[l_nLoop] != NULL)
    {
      m_poSigFile[l_nLoop]->FileFlush();
    }
    else
    {
      l_bResult = FALSE;
    }
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
BOOL CSigParseText::FileClose
(
)
{
  BOOL l_bResult = TRUE;
  int  l_nLoop;

  //

  for
  ( l_nLoop  = 0
  ; l_nLoop <  CSigContainer::eSigFileId__END
  ; l_nLoop += 1
  )
  {
    if(m_poSigFile[l_nLoop] != NULL)
    {
      m_poSigFile[l_nLoop]->FileClose();

      delete m_poSigFile[l_nLoop];

      m_poSigFile[l_nLoop] = NULL;
    }
    else
    {
      l_bResult = FALSE;
    }
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
BOOL CSigParseText::LoadNextLine
( int  i_nFileId
, BOOL i_bAllowEmptyLine
)
{
  if(m_bStop == FALSE)
  {
    return m_poSigFile[i_nFileId]->LoadNextLine(m_oStrLineData, i_bAllowEmptyLine);
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
BOOL CSigParseText::LoadNextLineParsed
( int  i_nFileId
, BOOL i_bRefreshHash    // = FALSE
, char i_nDelimiter      // = ' '
, BOOL i_bTrimed         // = TRUE
, BOOL i_bAllowEmptyLine // = FALSE
)
{
  int     l_nLoop;
  XString l_oStrTempo;

  //

  if(LoadNextLine(i_nFileId, i_bAllowEmptyLine) == TRUE)
  {
#ifdef DEBUGSTUFF // SigParseText.h
    // Ben oui, dans le cadre d'un fichier MIFMID,
    // la ligne ne 'devrait' pas dépasser 1024 octets
    // (repère les bugs de lecture de ligne)
//    ASSERT(m_oStrLineData.GetLength() < 1024);
#endif // DEBUGSTUFF

    if(i_bTrimed == TRUE)
    {
      m_oStrLineData.TrimLeft();
      m_oStrLineData.TrimRight();
      while(m_oStrLineData.Replace("  ", " "));
    }
    else{}

    m_aoStrLineElements.RemoveAll();

    if(m_oStrLineData.IsEmpty() == FALSE)
    {
      l_nLoop = 0;

#ifdef _DEBUG
      if
      (
           (m_oStrLineData[ 0] == 'R')
        && (m_oStrLineData[ 1] == 'O')
        && (m_oStrLineData[ 2] == 'U')
        && (m_oStrLineData[ 3] == 'F')
        && (m_oStrLineData[ 4] == 'F')
        && (m_oStrLineData[ 5] == 'I')
        && (m_oStrLineData[ 6] == 'G')
        && (m_oStrLineData[ 7] == 'N')
        && (m_oStrLineData[ 8] == 'A')
        && (m_oStrLineData[ 9] == 'C')
        && (m_oStrLineData[10] == '-')
        && (m_oStrLineData[11] == 'S')
      )
      { // Mettre un point d'arret ici pour vérifier l'insertion de "ROUFFIGNAC-"
        l_nLoop = l_nLoop;
      }
#endif // _DEBUG

      while
      (
        MyAfxExtractSubString
        ( l_oStrTempo
        , m_oStrLineData.GetBuffer(0)
        , l_nLoop
        , i_nDelimiter
        )
        == TRUE
      )
      {
        l_oStrTempo.TrimLeft();
        l_oStrTempo.TrimRight();
        l_oStrTempo.Remove('"'); // Pas besoin des guillemets
  
        m_aoStrLineElements.Add(l_oStrTempo);

        l_nLoop +=1;
      }

      if(i_bRefreshHash == TRUE)
      { // Pour une rapidité de parsing, on HASH juste le premier paramètre
        m_nHashed = SHASH(m_aoStrLineElements.GetAt(0));
      }
      else{}
    }
    else
    {
      m_nHashed = 0;
    }

    return (l_nLoop != 0);
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
BOOL CSigParseText::WriteLine
( int         i_nFileId
, const char* i_panBuffer
)
{
  if(m_bStop == FALSE)
  {
    return m_poSigFile[i_nFileId]->WriteLine(i_panBuffer);
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
XString CSigParseText::GetElement
( int i_nElementIndex
)
{
/*
  if(i_nElementIndex > m_aoStrLineElements.GetUpperBound())
  {
    i_nElementIndex = m_aoStrLineElements.GetUpperBound();
  }
  else{}

  if(i_nElementIndex < 0)
  {
    i_nElementIndex = 0;
  }
  else{}
*/
/*
  BOUND_MINMAX
  ( i_nElementIndex
  , 0
  , m_aoStrLineElements.GetUpperBound()
  );
*/
  if
  (
       (i_nElementIndex <= m_aoStrLineElements.GetUpperBound())
    && (i_nElementIndex >= 0)
  )
  {
    return m_aoStrLineElements.GetAt(i_nElementIndex);
  }
  else
  { // Retourne vide en dehors des limites
    return "";
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
BOOL CSigParseText::StepToPos
( int            i_nFileId
, CSkinProgress* i_poSkinProgress
)
{
  if(i_poSkinProgress != NULL)
  {
    i_poSkinProgress->SetPos(GetPos(i_nFileId));

    PeekAndPump(); // Release message pressure

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
int CSigParseText::GetPos
( int i_nFileId
)
{
  if
  (
       (i_nFileId >= CSigContainer::eSigFileId_OBJECTS)
    && (i_nFileId <  CSigContainer::eSigFileId__END)
  )
  {
    return m_poSigFile[i_nFileId]->GetPos();
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
void CSigParseText::Stop
(
)
{
  m_bStop = TRUE;
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
BOOL CSigParseText::ParseFunctionArguments
( const char* i_panParse // = NULL
)
{
  int     l_nTempo;
  XString l_oStrTempo;
  XString l_oStrLoop;

  //

  m_aoStrLineElements.RemoveAll();

  if(i_panParse != NULL)
  {
    m_oStrLineData = i_panParse;
  }
  else{}

  l_nTempo = m_oStrLineData.Find('(');
  if(l_nTempo < 0)
  {
    l_nTempo = m_oStrLineData.Find(' ');
  }
  else{}

  if(l_nTempo < 0)
  {
    m_aoStrLineElements.Add(m_oStrLineData);
  }
  else
  {
    l_oStrTempo = m_oStrLineData.Left(l_nTempo);
    l_oStrTempo.TrimLeft();
    l_oStrTempo.TrimRight();

    m_aoStrLineElements.Add(l_oStrTempo);

    l_oStrTempo = m_oStrLineData.Mid(l_nTempo + 1);

    // SUPER IMPORTANT !!!
    l_oStrTempo.Remove(')');
    l_oStrTempo.Remove(' ');
    l_oStrTempo.Replace('(', ','); // Dans Bounds, remplace le '(' central
    l_oStrTempo.TrimLeft();
    l_oStrTempo.TrimRight();
    // SUPER IMPORTANT !!!

    l_nTempo = 0;

    while
    ( MyAfxExtractSubString
      ( l_oStrLoop
      , l_oStrTempo.GetBuffer(0)
      , l_nTempo
      , ','
      ) == TRUE
    )
    {
      l_oStrLoop.TrimLeft();
      l_oStrLoop.TrimRight();
      l_oStrLoop.Remove('"'); // Pas besoin des guillemets
    
      m_aoStrLineElements.Add(l_oStrLoop);

      l_nTempo +=1;
    }
  }

  // Pour une rapidité de parsing, on HASH juste le premier paramètre
  m_nHashed = SHASH(m_aoStrLineElements.GetAt(0));

  return (m_aoStrLineElements.GetSize() != 1);
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
int CSigParseText::CopyString
( char* o_panBuffer
, char* i_panBuffer
)
{
  int   l_nLoop;
  int   l_nTempo;

  //

  l_nLoop  = strlen(i_panBuffer);

  if(l_nLoop > STRING_SIZE)
  {
    l_nLoop = STRING_SIZE;
  }
  else{}

  l_nTempo = l_nLoop;

  while(l_nLoop != 0)
  {
    *o_panBuffer = *i_panBuffer;

    o_panBuffer += 1;
    i_panBuffer += 1;
    l_nLoop     -= 1;
  }

  return l_nTempo;
}
