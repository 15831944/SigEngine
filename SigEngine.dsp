# Microsoft Developer Studio Project File - Name="SigEngine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SigEngine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SigEngine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SigEngine.mak" CFG="SigEngine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SigEngine - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SigEngine - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SigEngine - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_TURBODLL" /D "_SIGENGINE" /D "_SIGENGINEDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /def:"SigEngine.def"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\SigEngine.dll ..\Commun	copy Release\SigEngine.lib ..\Commun	copy Release\SigEngine.dll %systemroot%\System32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SigEngine - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_TURBODLL" /D "_SIGENGINE" /D "_SIGENGINEDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /def:"SigEngineD.def" /out:"Debug/SigEngineD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\SigEngineD.dll ..\Commun	copy Debug\SigEngineD.lib ..\Commun	copy Debug\SigEngineD.dll %systemroot%\System32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "SigEngine - Win32 Release"
# Name "SigEngine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Source SigObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SigPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\SigPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\SigPolygonPool.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Source SigParser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SigAutoCad.cpp
# End Source File
# Begin Source File

SOURCE=.\SigContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\SigGeoProj.cpp
# End Source File
# Begin Source File

SOURCE=.\SigMapInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SigParseText.cpp
# End Source File
# End Group
# Begin Group "Source Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryArray.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryPool.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryString.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryStringArray.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryStringContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryStringPool.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryStringTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryTreeAvl.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryTreeRedBlack.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryTreeSplay.cpp
# End Source File
# End Group
# Begin Group "Source Helper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CPathSplit.cpp
# End Source File
# Begin Source File

SOURCE=.\secdesc.cpp
# End Source File
# Begin Source File

SOURCE=.\SigUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinProgress.cpp
# End Source File
# End Group
# Begin Group "Source TurboDLL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TLCDragWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TLCDropWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TLHDragWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TLHDropWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListColumnInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListComboCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListDC.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListResource.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListStaticCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListTipCtrl.cpp
# End Source File
# End Group
# Begin Group "Source TinyXML"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tinystr.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\tinyxml.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\tinyxmlerror.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\tinyxmlparser.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Source ComboTree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ComboTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboTreeButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboTreeDropList.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboTreeEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboTreeHook.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboTreeTip.cpp
# End Source File
# Begin Source File

SOURCE=.\PupText.cpp
# End Source File
# Begin Source File

SOURCE=.\Subclass.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\SigEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Header SigObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SigPoint.h
# End Source File
# Begin Source File

SOURCE=.\SigPolygon.h
# End Source File
# Begin Source File

SOURCE=.\SigPolygonPool.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header SigParser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SigAutoCad.h
# End Source File
# Begin Source File

SOURCE=.\SigContainer.h
# End Source File
# Begin Source File

SOURCE=.\SigGeoProj.h
# End Source File
# Begin Source File

SOURCE=.\SigMapInfo.h
# End Source File
# Begin Source File

SOURCE=.\SigParseText.h
# End Source File
# End Group
# Begin Group "Header Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Memory.h
# End Source File
# Begin Source File

SOURCE=.\MemoryArray.h
# End Source File
# Begin Source File

SOURCE=.\MemoryContainer.h
# End Source File
# Begin Source File

SOURCE=.\MemoryPool.h
# End Source File
# Begin Source File

SOURCE=.\MemoryString.h
# End Source File
# Begin Source File

SOURCE=.\MemoryStringArray.h
# End Source File
# Begin Source File

SOURCE=.\MemoryStringContainer.h
# End Source File
# Begin Source File

SOURCE=.\MemoryStringPool.h
# End Source File
# Begin Source File

SOURCE=.\MemoryStringTree.h
# End Source File
# Begin Source File

SOURCE=.\MemoryTree.h
# End Source File
# Begin Source File

SOURCE=.\MemoryTreeAvl.h
# End Source File
# Begin Source File

SOURCE=.\MemoryTreeRedBlack.h
# End Source File
# Begin Source File

SOURCE=.\MemoryTreeSplay.h
# End Source File
# End Group
# Begin Group "Header Helper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CPathSplit.h
# End Source File
# Begin Source File

SOURCE=.\FixedCoSin.h
# End Source File
# Begin Source File

SOURCE=.\secdesc.h
# End Source File
# Begin Source File

SOURCE=.\SigUtils.h
# End Source File
# Begin Source File

SOURCE=.\SkinProgress.h
# End Source File
# End Group
# Begin Group "Header TurboDLL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TLCDragWnd.h
# End Source File
# Begin Source File

SOURCE=.\TLCDropWnd.h
# End Source File
# Begin Source File

SOURCE=.\TLHDragWnd.h
# End Source File
# Begin Source File

SOURCE=.\TLHDropWnd.h
# End Source File
# Begin Source File

SOURCE=.\TreeListColumnInfo.h
# End Source File
# Begin Source File

SOURCE=.\TreeListComboCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListDC.h
# End Source File
# Begin Source File

SOURCE=.\TreeListEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListItem.h
# End Source File
# Begin Source File

SOURCE=.\TreeListResource.h
# End Source File
# Begin Source File

SOURCE=.\TreeListStaticCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TurboDLL.h
# End Source File
# End Group
# Begin Group "Header TinyXML"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tinystr.h
# End Source File
# Begin Source File

SOURCE=.\tinyxml.h
# End Source File
# End Group
# Begin Group "Header ComboTree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ComboTree.h
# End Source File
# Begin Source File

SOURCE=.\ComboTreeButton.h
# End Source File
# Begin Source File

SOURCE=.\ComboTreeDropList.h
# End Source File
# Begin Source File

SOURCE=.\ComboTreeEdit.h
# End Source File
# Begin Source File

SOURCE=.\ComboTreeHook.h
# End Source File
# Begin Source File

SOURCE=.\ComboTreeTip.h
# End Source File
# Begin Source File

SOURCE=.\PupText.h
# End Source File
# Begin Source File

SOURCE=.\Subclass.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\SigEngine.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BM_BKGND.BMP
# End Source File
# Begin Source File

SOURCE=.\res\bm_bkgnd2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_checkbox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_def_head.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_def_sort.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_def_tree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_lockbox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ComboTreeCheckboxes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur_button.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_checkbox.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_cross.cur
# End Source File
# Begin Source File

SOURCE=.\res\CUR_DROP.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CUR_HORZ.CUR
# End Source File
# Begin Source File

SOURCE=.\res\cur_lockbox.cur
# End Source File
# Begin Source File

SOURCE=.\res\CUR_SIZE.CUR
# End Source File
# Begin Source File

SOURCE=.\res\cur_split.cur
# End Source File
# Begin Source File

SOURCE=.\res\CUR_STOP.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CUR_VERT.CUR
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\SigEngine.rc
# End Source File
# Begin Source File

SOURCE=.\res\SigEngine.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
