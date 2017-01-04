// SigEngine.h : main header file for the SIGENGINE DLL
//

#if !defined(AFX_SIGENGINE_H__5A10A200_00CD_4EE9_80BF_7B851E6F554A__INCLUDED_)
#define AFX_SIGENGINE_H__5A10A200_00CD_4EE9_80BF_7B851E6F554A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#if !defined _SIGENGINE
	#if defined _SIGENGINEDLL
		//------------------------------------------
		// SigEngine en Dll
		//------------------------------------------
		#ifdef _DEBUG
			#pragma comment(lib,"SigEngineD.lib") 
			#pragma message("Link automatique avec SigEngineD.dll")
		#else
			#pragma comment(lib,"SigEngine.lib") 
			#pragma message("Link automatique avec SigEngine.dll") 
		#endif

		#define EXPSIGENGINE  __declspec(dllimport)
		#define EXPSIGENGINEC extern "C" EXPSIGENGINE

	#elif defined _SIGENGINELIB
		//--------------------------------------------------
		// SigEngine en Lib
		//--------------------------------------------------
		#ifdef _DEBUG
			#pragma comment(lib,"SigEngineD.lib") 
			#pragma message("Link automatique avec SigEngineD.lib") 
		#else
			#pragma comment(lib,"SigEngine.lib") 
			#pragma message("Link automatique avec SigEngine.lib") 
		#endif

		#define EXPSIGENGINE
		#define EXPSIGENGINEC

	#endif
#else
	#if defined _SIGENGINEDLL
		#define EXPSIGENGINE  __declspec(dllexport)
		#define EXPSIGENGINEC extern "C" EXPSIGENGINE
	#elif defined _SIGENGINELIB 
		#define EXPSIGENGINE
		#define EXPSIGENGINEC
	#endif
#endif


#include "ComboTree.h"  // -> ComboTreeEdit.h
                        // -> ComboTreeButton.h
                        // -> ComboTreeHook.h     -> subclass.h
                        // -> ComboTreeDropList.h -> ComboTreeTip.h -> subclass.h
                        //                                          -> puptext.h

#include "CPathSplit.h"

#include "SigMapInfo.h" // -> SigParseText.h -> SigContainer.h -> Memory.h -> SigUtils.h
                        //                   -> CPathSplit.h
                        //                   -> SkinProgress.h

#include "SigAutoCad.h" // -> SigParseText.h -> SigContainer.h -> Memory.h -> SigUtils.h
                        //                   -> CPathSplit.h
                        //                   -> SkinProgress.h

#include "SigGeoProj.h"

#include "SkinProgress.h"

#define TIXML_USE_STL
#include "tinyxml.h"

#include "TurboDLL.h"   // -> TreeListColumnInfo.h
                        // -> TreeListItem.h
                        // -> TreeListHeaderCtrl.h
                        // -> TreeListTipCtrl.h
                        // -> TreeListStaticCtrl.h
                        // -> TreeListEditCtrl.h
                        // -> TreeListComboCtrl.h
                        // -> TreeListCtrl.h

#endif // !defined(AFX_SIGENGINE_H__5A10A200_00CD_4EE9_80BF_7B851E6F554A__INCLUDED_)
