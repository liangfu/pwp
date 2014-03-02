; compvis.nsi

!define /date DATE "%Y-%m-%d"
!define /date REVISION "%y%m%d"
!define VERSION 0.1
!define MUI_ICON appicon.ico

!define MUI_FILE "compvis-demo"
!define MUI_PRODUCT "CompVis"

;--------------------------------
;Include Modern UI

!include "MUI2.nsh"

; The name of the installer
Name "CompVis"

; The file to write
OutFile "CompVisSetup-v${VERSION}.${REVISION}.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\CompVis"

;Get installation folder from registry if available
InstallDirRegKey HKCU "Software\CompVis" ""

; The text to prompt the user to enter a directory
DirText "Choose a folder in which to install the CompVis!"

; Show details
ShowInstDetails show

;Request application privileges for Windows Vista
RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  
;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\LICENSE.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  
;--------------------------------
;Installer Sections

Section "CompVis full version"
  ; Set output path to the installation directory
  SetOutPath $INSTDIR

  ; List of files
  File /r "Microsoft.VC90.CRT"
  File "compvis-demo.exe" "compvis-demo.exe.manifest" "cxcore.dll" "cv.dll" "highgui.dll" "compvis.dll" "QtCore4.dll" "QtGui4.dll" "vcredist_x86_vs2008sp1.exe" "RELEASE_NOTES.txt"
  ExecWait "$INSTDIR\vcredist_x86_vs2008sp1.exe"

  ;Create desktop shortcut
  CreateShortCut "$DESKTOP\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_FILE}.exe" ""

  ;Create start-menu items
  CreateDirectory "$SMPROGRAMS\${MUI_PRODUCT}"
  CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\Uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_FILE}.exe" "" "$INSTDIR\${MUI_FILE}.exe" 0
  
  ;Store installation folder
  WriteRegStr HKCU "Software\${MUI_FILE}" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;Delete Files 
  RMDir /r "$INSTDIR\*.*"    
 
  ;Remove the installation directory
  RMDir "$INSTDIR"

  ;Delete Start Menu Shortcuts
  Delete "$DESKTOP\${MUI_PRODUCT}.lnk"
  Delete "$SMPROGRAMS\${MUI_PRODUCT}\*.*"
  RmDir  "$SMPROGRAMS\${MUI_PRODUCT}"

  ;Delete "$INSTDIR\Uninstall.exe"
  ;RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\CompVis"

SectionEnd