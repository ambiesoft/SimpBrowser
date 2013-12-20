; CLW ÉtÉ@ÉCÉãÇÕ MFC ClassWizard ÇÃèÓïÒÇä‹ÇÒÇ≈Ç¢Ç‹Ç∑ÅB

[General Info]
Version=1
LastClass=CSimpBrowserView
LastTemplate=CHtmlView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SimpBrowser.h"
LastPage=0

ClassCount=7
Class1=CSimpBrowserApp
Class2=CSimpBrowserDoc
Class3=CSimpBrowserView
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_MAINFRAME
Resource2=IDR_MAINFRAME (âpåÍ (±“ÿ∂))
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX
Class6=CSubDocument
Class7=CSubView
Resource4=IDD_ABOUTBOX (âpåÍ (±“ÿ∂))
Resource5=IDR_MAINFRAME (English (U.S.))
Resource6=IDD_ABOUTBOX (English (U.S.))

[CLS:CSimpBrowserApp]
Type=0
HeaderFile=SimpBrowser.h
ImplementationFile=SimpBrowser.cpp
Filter=N

[CLS:CSimpBrowserDoc]
Type=0
HeaderFile=SimpBrowserDoc.h
ImplementationFile=SimpBrowserDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSimpBrowserView]
Type=0
HeaderFile=SimpBrowserView.h
ImplementationFile=SimpBrowserView.cpp
Filter=C
BaseClass=CHtmlView
VirtualFilter=7VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDM_BROWSER_SILENT




[CLS:CAboutDlg]
Type=0
HeaderFile=SimpBrowser.cpp
ImplementationFile=SimpBrowser.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_REOPEN
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[MNU:IDR_MAINFRAME (âpåÍ (±“ÿ∂))]
Type=1
Class=CMainFrame
Command1=ID_FILE_REOPEN
Command2=ID_ABOUT_BLANK
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_STATUS_BAR
Command14=ID_APP_ABOUT
CommandCount=14

[ACL:IDR_MAINFRAME (âpåÍ (±“ÿ∂))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (âpåÍ (±“ÿ∂))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CSubDocument]
Type=0
HeaderFile=SubDocument.h
ImplementationFile=SubDocument.cpp
BaseClass=CDocument
Filter=N

[CLS:CSubView]
Type=0
HeaderFile=SubView.h
ImplementationFile=SubView.cpp
BaseClass=CHtmlView
Filter=C
VirtualFilter=7VWC

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_OPEN_CLIPBOARD
Command2=ID_FILE_REOPEN
Command3=ID_ABOUT_BLANK
Command4=ID_FILE_NEW
Command5=ID_FILE_OPEN
Command6=ID_FILE_SAVE
Command7=ID_FILE_SAVE_AS
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=IDM_BROWSER_SILENT
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

