// SigParseText.h: interface for the CSig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGPARSETEXT_H__F8865F70_9493_46D1_9185_1BADA2CFD898__INCLUDED_)
#define AFX_SIGPARSETEXT_H__F8865F70_9493_46D1_9185_1BADA2CFD898__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#include "CPathSplit.h"
#include "SkinProgress.h"

#include "SigContainer.h"

// Explications sur la topologie des objets CSigMachin
// Il y a trois couches, chacune ayant un role distinct :
//
// Programmeur en détresse 
//  |
//  +-> CSigMapInfo : le moteur de parsing
//  |   |
//  |   '-> CSigParseText : la classe des outils de lecture/écriture (pour l'instant limité au format texte)
//  |        |
//  '--------+-> CSigContainer : le conteneur des données
//
// Le programmeur (en détresse, donc) va avoir à gèrer deux types
// d'objets, le CSigMapInfo (la couche d'abstration de format de fichier)
// et le CSigContainer (les données du fichier dans un format 'exploitable').
//
// Pour charger un fichier, soit le programmeur (s.o.s, help, ...) gère ses
// propres conteneurs (CSigContainer) à la main et les charge/sauve en les
// interfacant avec un CSigMapInfo, soit il utilise le CSigContainer
// crée automatiquement par le CSigParseText. Il n'a alors à travailler
// qu'avec un CSigMapInfo (super pratique pour une gestion ponctuelle).
//
// Philosophie 1 : Routine de chargement 'one-shot' pour lire un fichier MapInfo
//
//   Le programmeur (qui sue du front) va réserver un objet CSigMapInfo et
//   demander de charger un fichier MapInfo (format MIF/MID). Le conteneur
//   est réservé automatiquement et s'utilise de façon transparente pour
//   le programmeur. Il faudra juste récupérer le pointeur sur le container
//   interne qui est m_poSigContainer (public).
//
// Philosophie 2 : Gestion de plusieures couches, avec un CSigContainer par couche
//
//   Dans le cas d'un traitement plus lourd, il n'est pas judicieux de
//   travailler directement avec des objets CSigMapInfo. En effet, on est
//   limité à l'interface avec des fichiers au format MapInfo, et le poid
//   de la classe CSigMapInfo de chaque couche n'est pas nécessaire.
//
//   Il est alors conseillé de n'avoir qu'un seul objet CSigMapInfo et
//   de l'utiliser comme interface d'accès aux données des différentes
//   couches stockées dans des objets CSigContainer.
//
//   Tu vois, c'est limpide, il suffisait de demander...

// ---

class EXPSIGENGINE CSigParseText : public ClassUtils
{
  public:
    CSigParseText(const char* i_panStringName = "CSigParseText");
    virtual ~CSigParseText(void);

    //

    BOOL        CreateContainer(void);
    BOOL        AttachContainer(CSigContainer* i_poSigContainer, BOOL i_bRename = TRUE);
    void        DetachContainer(void);

    BOOL        AddColumn(const char* i_panColName, int i_nColType, int i_nColSize = 0);
// MODIF_KOCH 070328
// DK 070328 (LWPOLYLINE) : Support des couches logiques
    CSigContainer::sSigObject* AddObject(CSigContainer::eSigObjectType i_eObjectType, int i_nPointNumber = 0, const char* i_panStrObjectName = NULL, const char* i_panStrLayerName = NULL);
// MODIF_KOCH 070328
    BOOL        EndObject(int i_nObjectType);

    int         AddPoint(const char* i_panLonX, const char* i_panLatY, const char* i_panAltZ = NULL);
    int         AddRow(XStringArray& i_paoStrLineElements);
    int         AddString(const char* i_panText);

    void        SetObjectCenter(double i_nLonX, double i_nLatY, double i_nAltZ = 0.0);

    BOOL        FileSelect(char* i_panFileName);
    BOOL        FileOpen(char* i_panFileName);
    BOOL        FileOpen(void);
    BOOL        FileCreate(char* i_panFileName);
    BOOL        FileFlush(void);
    BOOL        FileClose(void);

    BOOL        LoadNextLine(int i_nFileId, BOOL i_bAllowEmptyLine = FALSE);
    BOOL        LoadNextLineParsed(int i_nFileId, BOOL i_bRefreshHash = FALSE, char i_nDelimiter = ' ', BOOL i_bTrimed = TRUE, BOOL i_bAllowEmptyLine = FALSE);

    BOOL        WriteLine(int i_nFileId, const char* i_panBuffer);

    XString     GetElement(int i_nElementIndex);
    BOOL        StepToPos(int i_nFileId, CSkinProgress* i_poSkinProgress);
    int         GetPos(int i_nFileId);
    void        Stop(void);
    
    BOOL        ParseFunctionArguments(const char* i_panParse = NULL);

    int         CopyString(char* o_panBuffer, char* i_panBuffer);

  public:
    CPathSplit                 m_oPathSplitter;
    CSigContainer*             m_poSigContainer;

    CFileIO*                   m_poSigFile[CSigContainer::eSigFileId__END];
    CSigContainer::sSigObject* m_psSigObject;
    
    XString                    m_oStrFileExtObjects;
    XString                    m_oStrFileExtDataBase;

    char                       m_oStrDataDelimiter;
    int                        m_nHashed;

    BOOL                       m_bBlockMode; // false=Container, true=Block

    XString                    m_oStrLineData;
    XStringArray               m_aoStrLineElements;

    XString                    m_oStrLastError;
    BOOL                       m_bStop;
};

#endif // !defined(AFX_SIGPARSETEXT_H__F8865F70_9493_46D1_9185_1BADA2CFD898__INCLUDED_)
