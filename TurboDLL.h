#ifndef __TURBO_DLL__
#define __TURBO_DLL__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _AFXDLL
	#pragma message("You *MUST* use MFC as Shared DLL")
	#error No MFC found
#endif

//#include <afxtempl.h>

#include "TreeListColumnInfo.h"
#include "TreeListItem.h"
#include "TreeListHeaderCtrl.h"
#include "TreeListTipCtrl.h"
#include "TreeListStaticCtrl.h"
#include "TreeListEditCtrl.h"
#include "TreeListComboCtrl.h"
#include "TreeListCtrl.h"

#endif  //TURBO_DLL__