# Microsoft Developer Studio Project File - Name="tabs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=tabs - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tabs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tabs.mak" CFG="tabs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tabs - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tabs - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tabs - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release/tabs"
# PROP BASE Intermediate_Dir "Release/tabs"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release/tabs"
# PROP Intermediate_Dir "Release/tabs"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /GX /Os /Ob2 /I "." /I "../.." /I "../../zlib" /I "../../png" /I "../../jpeg" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 fltk.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcd" /out:"../../test/tabs.exe" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "tabs - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug/tabs"
# PROP BASE Intermediate_Dir "Debug/tabs"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug/tabs"
# PROP Intermediate_Dir "Debug/tabs"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /Gm /GX /ZI /Od /I "." /I "../.." /I "../../zlib" /I "../../png" /I "../../jpeg" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 fltkd.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcd" /out:"../../test/tabsd.exe" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /pdb:none /incremental:no

!ENDIF 

# Begin Target

# Name "tabs - Win32 Release"
# Name "tabs - Win32 Debug"
# Begin Source File

SOURCE=..\..\test\tabs.cxx
# End Source File
# Begin Source File

SOURCE=..\..\test\tabs.fl

!IF  "$(CFG)" == "tabs - Win32 Release"

# Begin Custom Build - Create .cxx and .h file with fluid
InputPath=..\..\test\tabs.fl

"..\..\test\tabs.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pushd ..\..\test\ 
	..\fluid\fluid -c tabs.fl
	popd 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "tabs - Win32 Debug"

# Begin Custom Build - Create .cxx and .h file with fluidd
InputPath=..\..\test\tabs.fl

"..\..\test\tabs.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pushd ..\..\test\ 
	..\fluid\fluidd -c tabs.fl 
	popd 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
