//////////////////////////////////////////////////////////////////////
// CPathSplit.h - Kochise Kochise 2002-2004
//

#ifndef __CPATHSPLIT_H__
#define __CPATHSPLIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class EXPSIGENGINE CPathSplit
{ 
  // Construction
  public: 
    CPathSplit
    (
    );

    CPathSplit
    ( const char* i_panStrPath
    );

    typedef enum ePathElement
    { ePS_DRV = 0
    , ePS_DIR
    , ePS_FN
    , ePS_EXT
    , ePS__NUM
    };

  // Operations
    // Split the path
    BOOL Split
    ( const char* i_panStrPath
    );
    
    inline CString GetPath()     {return m_oStrPath;}

    CString GetPath
    ( int         i_nEnd
    , const char* i_panStrQueue = NULL          // No queue
    , int         i_nStart      = ePS_DRV // From DRIVE
    );

    inline CString GetDrive()    {return GetPath(ePS_DRV, NULL ,ePS_DRV);}
    inline CString GetDirectory(){return GetPath(ePS_DIR, NULL, ePS_DIR);}
    inline CString GetFolder()   {return GetPath(ePS_DIR, NULL, ePS_DRV);}

    inline CString GetFileName() {return GetPath(ePS_FN,  NULL, ePS_FN);}
    inline CString GetExtension(){return GetPath(ePS_EXT, NULL, ePS_EXT);}
    inline CString GetFile()     {return GetPath(ePS_EXT, NULL, ePS_FN);}

  // Attributes
  protected:
    CString m_oStrPath;

    int     m_anPathFirst[ePS__NUM];
    int     m_anPathCount[ePS__NUM];

    void ErasePointers
    (
    );
}; 

#endif // __CPATHSPLIT_H__
