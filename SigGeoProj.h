// SigGeoProj.h: interface for the CSigGeoProj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGGEOPROJ_H__86BF38A4_54B2_446C_8349_508B0B7F85DA__INCLUDED_)
#define AFX_SIGGEOPROJ_H__86BF38A4_54B2_446C_8349_508B0B7F85DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EXPSIGENGINE CSigGeoProj  
{
  public:
	  CSigGeoProj();
	  virtual ~CSigGeoProj();

  // Implementation
  public:
    void SelectCurrentSysGeo
         ( CString& o_roStrProjConvers
         , CString& o_roStrCurSysGeo
         , CString& o_roStrCurFamGeo
         , int&     o_rnUnit
         , int&     o_rnMerid
         , CSigContainer::sSigProjection* i_psSigProj = NULL
         );

    CSigContainer::sSigProjection m_sSigProj; // INPUT

  protected:
    void _InitCurrentSysGeo(void);
    void _AddCurrentSysGeo
         ( char*  i_panProjection // Equivalent CONVERS (si on connais)
         , char*  i_panSyntax
         , int    i_nTypeOrTableName
         , int    i_nDatumOrWindowID
         , int    i_nStuffing          = 0 // <- Sert à ne pas prendre en compte un des paramètres
         , double i_nOriginLon         = 0.0
         , double i_nOriginLat         = 0.0
         , double i_nStandartParallel1 = 0.0
         , double i_nStandartParallel2 = 0.0
         , double i_nAzimut            = 0.0
         , double i_nScaleFactor       = 0.0
         , double i_nFalseEasting      = 0.0
         , double i_nFalseNorthing     = 0.0
         , double i_nRange             = 0.0
         );

  // Members
    CMemoryTreeRedBlack           mp_asProjecBuffer;
    CMemoryStringArray            mp_asStringBuffer;
    CMemoryStringArray            mp_asConvBuffer;
    CSigContainer::sSigProjection mp_sSigProjCast; // TEMPO CAST
    int                           mp_nIndexFam;
};

#endif // !defined(AFX_SIGGEOPROJ_H__86BF38A4_54B2_446C_8349_508B0B7F85DA__INCLUDED_)
