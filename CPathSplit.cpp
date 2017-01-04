//////////////////////////////////////////////////////////////////////
// CPathSplit.cpp - Kochise 2002-2004
//

#include "stdafx.h"
#include "CPathSplit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinProgress

// g_Global      : g_ = Global
// i_Input       : i_ = Input
// no z...
// m_Member      : m_ = Member
// o_Output      : o_ = Output
// l_Local       : l_ = Local
// ...           : use your imagination

// aArray        : a  = Array    (array)
// bBool         : b  = Boolean  (boolean, true/false)
// cConstant     : c  = Constant (constant, whatever...)
// dDefine       : d  = Define   (simple define or defined value)
// eEnum         : e  = Enum     (enum list element)
// iIterator     : i  = Iterator (STL iterator)
// nNumber       : n  = Number   (char, long, int, whatever...)
// oObject       : o  = Object   (C++ class)
// pPointer      : p  = Pointer  (typicaly a 32 bits ulong address)
// sStruct       : s  = Struct   (structure)
// tTemplate     : t  = Template (template)
// uUnion        : u  = Union    (join two or more values of the same size under a common name)
// vVector       : v  = Vector   (STL vector, mostly like an array)

// poRemoteClass : po = Pointer on Object
// cdConstantDef : cd = Constant Define, typicaly a constant defined value
// usUnionStruct : us = Union of Structures
// ...           : use your imagination

// o_psBitmap    : CBitmap::GetBitmap((BITMAP*) o_psBitmap); // s = BITMAP, p = *, o_ means it's an output

// <Value>
// [Function]

CPathSplit::CPathSplit
(
)
{

  // Init

  ErasePointers();

  // Process
}

CPathSplit::CPathSplit
( const char* i_panStrPath
)
{

  // Init

  ErasePointers();

  // Process

  Split(i_panStrPath);
}

BOOL CPathSplit::Split
( const char* i_panStrPath
)
{
  int l_nLenPath;

  // Init

  ErasePointers(); // Erase pointers

  m_oStrPath = i_panStrPath;
  m_oStrPath.TrimLeft();
  m_oStrPath.TrimRight();

  // Process

  l_nLenPath = m_oStrPath.GetLength();

  if(l_nLenPath > 0)
  { // If the path is not empty
    m_anPathFirst[ePS_DIR] = m_oStrPath.Find('\\');

    if(m_anPathFirst[ePS_DIR] != (-1))
    { // If first directory found
      m_anPathCount[ePS_DRV] = m_anPathFirst[ePS_DIR] - m_anPathFirst[ePS_DRV];

      if(m_oStrPath.Mid(m_anPathFirst[ePS_DIR], 2) == "\\\\")
      { // If Network
        m_anPathFirst[ePS_DIR] += 1;
      }else{}

      m_anPathFirst[ePS_FN] = m_oStrPath.ReverseFind('\\');

      if(m_anPathFirst[ePS_FN] != (-1))
      { // If last directory found (typicaly the file name, but may be empty also)
        m_anPathFirst[ePS_FN] += 1; // Include the trailing '\' in the directory
        m_anPathCount[ePS_DIR] = m_anPathFirst[ePS_FN] - m_anPathFirst[ePS_DIR];

        m_anPathFirst[ePS_EXT] = m_oStrPath.ReverseFind('.');

        if
        (
             (m_anPathFirst[ePS_EXT] != (-1))
          && (m_anPathFirst[ePS_EXT]  > m_anPathFirst[ePS_FN])
        )
        { // If a extension was found AFTER the last directory
          m_anPathCount[ePS_FN]  = m_anPathFirst[ePS_EXT] - m_anPathFirst[ePS_FN];
          m_anPathCount[ePS_EXT] = l_nLenPath - m_anPathFirst[ePS_EXT];
        }
        else
        {
          m_anPathCount[ePS_FN]  = l_nLenPath - m_anPathFirst[ePS_FN];
          m_anPathFirst[ePS_EXT] = 0;
          // m_anPathCount[ePS_EXT] = 0; // Already to 0 from ErasePointers()
        }
      }else{}
    }
    else
    {
      m_anPathCount[ePS_DRV] = l_nLenPath;
    }

    return true;
  }else{}

  return false;
}

CString CPathSplit::GetPath
( int         i_nEnd
, const char* i_panStrQueue
, int         i_nStart
)
{
  CString l_oStrTempo;

  //

  if(i_nEnd < 0)
  { // In case...
    i_nEnd = 0;
  }else{}

  if(i_nStart < 0)
  { // ...of bad values
    i_nStart = 0;
  }else{}

  if(i_nEnd >= ePS__NUM)
  { // Clip to the maximum number of path elements currently supported
    i_nEnd = ePS__NUM - 1;
  }else{}

  if(i_nStart > i_nEnd)
  { // Clip the start
    i_nStart = i_nEnd;
  }else{}

  l_oStrTempo
  = m_oStrPath.Mid
    ( m_anPathFirst[i_nStart] // From...
    ,    (m_anPathFirst[i_nEnd] - m_anPathFirst[i_nStart]) // Size of the Start TO end
       + m_anPathCount[i_nEnd] // Includes size of end
    )
  ;

  if(i_panStrQueue != NULL)
  { // Add a queue of needed
    l_oStrTempo += i_panStrQueue;
  }else{}

  return l_oStrTempo;
}

void CPathSplit::ErasePointers
(
)
{
  int l_nLoop;

  // Init

  for
  ( l_nLoop  = 0
  ; l_nLoop <  ePS__NUM
  ; l_nLoop += 1
  )
  { // Erase pointers
    m_anPathFirst[l_nLoop] = 0;
    m_anPathCount[l_nLoop] = 0;
  }

  // Process
}
