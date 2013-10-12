# Microsoft Developer Studio Project File - Name="demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=demo - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "demo.mak" CFG="demo - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "demo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\cximage" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "VATI_EXTENSIONS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL" /d "VATI_EXTENSIONS"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wininet.lib ../png/Release/png.lib ../jpeg/Release/jpeg.lib ../zlib/Release/zlib.lib ../tiff/Release/tiff.lib ../j2k/Release/j2k.lib ../jbig/Release/jbig.lib ../jasper/Release/jasper.lib ../cximage/Release/cximage.lib /nologo /subsystem:windows /machine:I386 /out:"../bin/demo.exe"

!ELSEIF  "$(CFG)" == "demo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\cximage" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "VATI_EXTENSIONS" /FD /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL" /d "VATI_EXTENSIONS"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 wininet.lib ../png/Debug/png.lib ../jpeg/Debug/jpeg.lib ../zlib/Debug/zlib.lib ../tiff/Debug/tiff.lib ../j2k/Debug/j2k.lib ../jbig/Debug/jbig.lib ../jasper/Debug/jasper.lib ../cximage/Debug/cximage.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../bin/demod.exe"

!ENDIF 

# Begin Target

# Name "demo - Win32 Release"
# Name "demo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\demo.cpp
# End Source File
# Begin Source File

SOURCE=.\demo.rc
# End Source File
# Begin Source File

SOURCE=.\demoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\demoView.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCapture.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgColorize.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCombine.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecBpp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDither.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFFT.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGamma.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHisto.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIncBpp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMix.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOpacity.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPalette.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRepair.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgResample.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRotate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgText.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThreshold.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgURL.cpp
# End Source File
# Begin Source File

SOURCE=.\logomdi.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Quantize.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TwainCpp.cpp
# End Source File
# Begin Source File

SOURCE=.\xTargetButton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\demo.h
# End Source File
# Begin Source File

SOURCE=.\demoDoc.h
# End Source File
# Begin Source File

SOURCE=.\demoView.h
# End Source File
# Begin Source File

SOURCE=.\DlgCapture.h
# End Source File
# Begin Source File

SOURCE=.\DlgColorize.h
# End Source File
# Begin Source File

SOURCE=.\DlgCombine.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecBpp.h
# End Source File
# Begin Source File

SOURCE=.\DlgDither.h
# End Source File
# Begin Source File

SOURCE=.\DlgFFT.h
# End Source File
# Begin Source File

SOURCE=.\DlgGamma.h
# End Source File
# Begin Source File

SOURCE=.\DlgHisto.h
# End Source File
# Begin Source File

SOURCE=.\DlgIncBpp.h
# End Source File
# Begin Source File

SOURCE=.\DlgMix.h
# End Source File
# Begin Source File

SOURCE=.\DlgOpacity.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgPalette.h
# End Source File
# Begin Source File

SOURCE=.\DlgRepair.h
# End Source File
# Begin Source File

SOURCE=.\DlgResample.h
# End Source File
# Begin Source File

SOURCE=.\DlgRotate.h
# End Source File
# Begin Source File

SOURCE=.\DlgText.h
# End Source File
# Begin Source File

SOURCE=.\DlgThreshold.h
# End Source File
# Begin Source File

SOURCE=.\DlgURL.h
# End Source File
# Begin Source File

SOURCE=.\logomdi.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Quantize.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TwainCpp.h
# End Source File
# Begin Source File

SOURCE=.\xTargetButton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\b1.ico
# End Source File
# Begin Source File

SOURCE=.\res\bg.BMP
# End Source File
# Begin Source File

SOURCE=.\res\bg.gif
# End Source File
# Begin Source File

SOURCE=.\res\bg.jpg
# End Source File
# Begin Source File

SOURCE=.\res\bg2.jpg
# End Source File
# Begin Source File

SOURCE=.\res\canc.ico
# End Source File
# Begin Source File

SOURCE=.\res\demo.ico
# End Source File
# Begin Source File

SOURCE=.\res\demo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\demoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Explorer.ico
# End Source File
# Begin Source File

SOURCE=.\res\gray.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico2.bin
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\no1.ico
# End Source File
# Begin Source File

SOURCE=.\res\ok.ico
# End Source File
# Begin Source File

SOURCE=.\res\r1.ico
# End Source File
# Begin Source File

SOURCE=.\res\testbmp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\bg.tif
# End Source File
# Begin Source File

SOURCE=.\res\us.png
# End Source File
# End Target
# End Project
