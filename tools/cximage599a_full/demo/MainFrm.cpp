// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "demo.h"

#include "MainFrm.h"
#include "demodoc.h"
#include "DlgCapture.h"

#include "ximage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_FILE_SELECTSOURCE, OnFileSelectsource)
	ON_COMMAND(ID_FILE_ACQUIRE, OnFileAcquire)
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_CAPTURE, OnFileCapture)
	ON_WM_SIZE()
	ON_WM_MEASUREITEM()
	ON_WM_INITMENUPOPUP()
	ON_WM_MENUCHAR()
	ON_COMMAND(ID_VIEW_MENUSTYLE_NORMAL, OnViewMenustyleNormal)
	ON_COMMAND(ID_VIEW_MENUSTYLE_XP, OnViewMenustyleXp)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullscreen)
	ON_COMMAND_EX(ID_VIEW_HISTOGRAM, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HISTOGRAM, OnUpdateControlBarMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR1,
	ID_INDICATOR2,
	ID_INDICATOR3,
	ID_INDICATOR4,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

//////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
CMainFrame::CMainFrame()
{ }
CMainFrame::~CMainFrame()
{ }
//////////////////////////////////////////////////////////////////////////////
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

/*	if (!m_wndProgressBar.Create(WS_CHILD,CRect(200,2,262,18),&m_wndStatusBar,ID_INDICATOR1))
	{
		TRACE0("Failed to create progress bar\n");
		return -1;      // fail to create
	}
	m_wndProgressBar.ShowWindow(SW_SHOW);
	m_wndProgressBar.SetRange(0,100);
*/
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//histogram bar
	m_HistoBar.Create(this, IDD_HISTO, CBRS_TOP, ID_VIEW_HISTOGRAM);
	m_HistoBar.ShowWindow(0);
	m_HistoBar.EnableDocking(0);

	RECT r;
	GetWindowRect(&r);
	FloatControlBar(&m_HistoBar,CPoint(r.right-300,r.top+80),CBRS_ALIGN_TOP);
	
	// <<<TWAIN>>>
	InitTwain(m_hWnd);
//	if(!IsValidDriver()) AfxMessageBox("Unable to load Twain Driver.");

	m_fullscreen=false;

#ifdef VATI_EXTENSIONS
    // load the window size and positions
	CRect rect;
	rect.left   = AfxGetApp()->GetProfileInt ( "Screen", "left",      0 ) ;
	rect.top    = AfxGetApp()->GetProfileInt ( "Screen", "top",       0 ) ;
	rect.right  = AfxGetApp()->GetProfileInt ( "Screen", "right",   850 ) ;
	rect.bottom = AfxGetApp()->GetProfileInt ( "Screen", "bottom",  650 ) ;

	// resize
	if (rect.left && rect.top && rect.right && rect.bottom )
		MoveWindow( & rect,0 );
#endif

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CMDIFrameWnd::PreCreateWindow(cs);
}

//////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnEditPaste() 
{
	CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 

	if (NewDoc)	{
		HANDLE hBitmap=NULL;
		CBitmap bmpClip;
		if (OpenClipboard()) hBitmap=GetClipboardData(CF_DIB);
		if (hBitmap){
			CxImage *newima = new CxImage();
			newima->CreateFromHANDLE(hBitmap);
			NewDoc->image = newima;
		}
		CloseClipboard();

		CString s;
		s.Format("Clipboard Image %d",((CDemoApp*)AfxGetApp())->m_nDocCount++);
		NewDoc->SetTitle(s);
		NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
		NewDoc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	if(!IsClipboardFormatAvailable(CF_DIB)) pCmdUI->Enable(FALSE);
}
//////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (CMDIFrameWnd::OnCreateClient(lpcs, pContext)){  
		// Subclass the MDIClient to print the logo in the 
		// bottom right corner....See CLogoMdi in logomdi.cpp
        m_LogoMdiClientWnd.SubclassWindow(m_hWndMDIClient) ; 
        return TRUE ;
	} else {
        return FALSE ;
	}
}
//////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if (CTwain::SourceEnabled()) //<<<TWAIN>>>
		return CTwain::ProcessMessage(*pMsg);			//process twain
	else
		return CMDIFrameWnd::PreTranslateMessage(pMsg);	//other message
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFileSelectsource() 
{
	CTwain::SelectSource(); //<<<TWAIN>>>
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFileAcquire() 
{
	CTwain::Acquire(TWCPP_ANYCOUNT); //<<<TWAIN>>>
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnClose() 
{
	CTwain::ReleaseTwain(); //<<<TWAIN>>>

#ifdef VATI_EXTENSIONS
    // get the window & save
    AfxGetApp()->WriteProfileInt ( "Screen", "maximized", IsZoomed()) ;
	if ( !IsZoomed() && !IsIconic() )
	{
		CRect rect;
		GetWindowRect ( & rect ) ;

		int xScreen = GetSystemMetrics(SM_CXSCREEN) - 100;
		int yScreen = GetSystemMetrics(SM_CYSCREEN) - 100;
		if (rect.left > xScreen)
			rect.left = xScreen;
		if (rect.top > yScreen)
			rect.top = yScreen;

		AfxGetApp()->WriteProfileInt ( "Screen", "left",   rect.left ) ;
		AfxGetApp()->WriteProfileInt ( "Screen", "top",    rect.top ) ;
		AfxGetApp()->WriteProfileInt ( "Screen", "right",  rect.right ) ;
		AfxGetApp()->WriteProfileInt ( "Screen", "bottom", rect.bottom ) ;
	}
	// save last used font data for Text tool
    AfxGetApp()->WriteProfileString( "TextTool", "lfFaceName", theApp.m_text.lfont.lfFaceName );
	AfxGetApp()->WriteProfileInt( "TextTool", "lfCharSet", theApp.m_text.lfont.lfCharSet );
	AfxGetApp()->WriteProfileInt( "TextTool", "lfWeight", theApp.m_text.lfont.lfWeight );
	AfxGetApp()->WriteProfileInt( "TextTool", "lfItalic", theApp.m_text.lfont.lfItalic );
	AfxGetApp()->WriteProfileInt( "TextTool", "lfUnderline", theApp.m_text.lfont.lfUnderline );
	AfxGetApp()->WriteProfileInt( "TextTool", "fcolor", theApp.m_text.fcolor );
	AfxGetApp()->WriteProfileInt( "TextTool", "bcolor", theApp.m_text.bcolor );
	AfxGetApp()->WriteProfileInt( "TextTool", "opacity", (int)(100.*theApp.m_text.b_opacity) );
	AfxGetApp()->WriteProfileInt( "TextTool", "r_radius", theApp.m_text.b_round );
	AfxGetApp()->WriteProfileInt( "Options" , "JpegQuality",theApp.m_optJpegQuality);

#endif

	CMDIFrameWnd::OnClose();
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::SetImage(HANDLE hBitmap,TW_IMAGEINFO& info)
{ //<<<TWAIN>>>
	CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDoc)	{
		if (hBitmap){
			CxImage *newima = new CxImage();
			newima->CreateFromHANDLE(hBitmap);
			NewDoc->image = newima;
		}
		CString s;
		s.Format("Acquired Image %d",((CDemoApp*)AfxGetApp())->m_nDocCount++);
		NewDoc->SetTitle(s);
		NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
		NewDoc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFileCapture() 
{
	DlgCapture dlg;
	if (dlg.DoModal()==IDOK){
		// get the desired window from dialog box
		HWND hwnd=dlg.m_SelectedWnd;
		// get window size
		CRect r;
		::GetWindowRect(hwnd,&r);

		int xScreen,yScreen;	//check if the window is out of the screen or maximixed <Qiang>
		int xshift = 0, yshift = 0;
		xScreen = GetSystemMetrics(SM_CXSCREEN);
		yScreen = GetSystemMetrics(SM_CYSCREEN);
		if(r.right > xScreen)
			   r.right = xScreen;
		if(r.bottom > yScreen)
			   r.bottom = yScreen;
		if(r.left < 0){
			   xshift = -r.left;
			   r.left = 0;
		}
		if(r.top < 0){
			   yshift = -r.top;
			   r.top = 0;
		}
		
		CSize sz(r.Width(), r.Height());
		if(sz.cx <= 0 || sz.cy <= 0) return;

		// bring the window at the top most level
		::SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

		// prepare the DCs
		HDC dstDC = ::GetDC(NULL);
        HDC srcDC = ::GetWindowDC(hwnd); //full window (::GetDC(hwnd); = clientarea)
		HDC memDC = ::CreateCompatibleDC(dstDC);
		
		// copy the screen to the bitmap
		HBITMAP bm =::CreateCompatibleBitmap(dstDC, sz.cx, sz.cy);
		HBITMAP oldbm = (HBITMAP)::SelectObject(memDC,bm);
		::BitBlt(memDC, 0, 0, sz.cx, sz.cy, srcDC, xshift, yshift, SRCCOPY);
	
		// restore the position
		::SetWindowPos(hwnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		::SetWindowPos(m_hWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

		// prepare the new document
		CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDoc)	{
			CxImage *newima = new CxImage();
			newima->CreateFromHBITMAP(bm);
			NewDoc->image = newima;
			CString s;
			s.Format("Captured Image %d",((CDemoApp*)AfxGetApp())->m_nDocCount++);
			NewDoc->SetTitle(s);
			NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
			NewDoc->UpdateStatusBar();
		}

		// free objects
		DeleteObject(SelectObject(memDC,oldbm));
		DeleteObject(memDC);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
	
//	m_wndProgressBar.SetWindowPos(0,max(200,cx-370),2,0,0,SWP_NOZORDER|SWP_NOSIZE);
}
//////////////////////////////////////////////////////////////////////////////
HMENU CMainFrame::NewMenu()
{
  static UINT toolbars[]={
    IDR_MAINFRAME,
	IDR_TOOLBAR1
  };

  // Load the menu from the resources
  // ****replace IDR_MENUTYPE with your menu ID****
  m_menu.LoadMenu(IDR_DEMOTYPE);  
  // One method for adding bitmaps to menu options is 
  // through the LoadToolbars member function.This method 
  // allows you to add all the bitmaps in a toolbar object 
  // to menu options (if they exist). The first function 
  // parameter is an array of toolbar id's. The second is 
  // the number of toolbar id's. There is also a function 
  // called LoadToolbar that just takes an id.
  m_menu.LoadToolbars(toolbars,2);

  return(m_menu.Detach());
}
//////////////////////////////////////////////////////////////////////////////
HMENU CMainFrame::NewDefaultMenu()
{
  m_default.LoadMenu(IDR_MAINFRAME);
  m_default.LoadToolbar(IDR_MAINFRAME);
  return(m_default.Detach());
}
//////////////////////////////////////////////////////////////////////////////
//This handler ensure that the popup menu items are 
// drawn correctly
void CMainFrame::OnMeasureItem(int nIDCtl, 
 LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
  BOOL setflag=FALSE;
  if(lpMeasureItemStruct->CtlType==ODT_MENU){
    if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
      CMenu* cmenu = 
       CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);

      if(m_menu.IsMenu(cmenu)||m_default.IsMenu(cmenu)){
        m_menu.MeasureItem(lpMeasureItemStruct);
        setflag=TRUE;
      }
    }
  }

  if(!setflag)CMDIFrameWnd::OnMeasureItem(nIDCtl, 
                                          lpMeasureItemStruct);
}
//////////////////////////////////////////////////////////////////////////////
//This handler ensures that keyboard shortcuts work
LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, 
 CMenu* pMenu) 
{
  LRESULT lresult;
  if(m_menu.IsMenu(pMenu)||m_default.IsMenu(pMenu))
    lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
  else
    lresult=CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
  return(lresult);
}
//////////////////////////////////////////////////////////////////////////////
//This handler updates the menus from time to time
void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, 
 UINT nIndex, BOOL bSysMenu) 
{
  CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
  if(!bSysMenu){
    if(m_menu.IsMenu(pPopupMenu)||m_default.IsMenu(pPopupMenu))
      BCMenu::UpdateMenu(pPopupMenu);
  }
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnViewMenustyleNormal() 
{
	BCMenu::SetMenuDrawMode(BCMENU_DRAWMODE_ORIGINAL);
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnViewMenustyleXp() 
{
	BCMenu::SetMenuDrawMode(BCMENU_DRAWMODE_XP);
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnViewFullscreen() 
{
	if (m_fullscreen)
	{
		ModifyStyle(0,WS_CAPTION|WS_THICKFRAME);			
		ShowWindow(SW_SHOWNORMAL);

		ShowControlBar(&m_wndToolBar, TRUE, FALSE);
		ShowControlBar(&m_wndStatusBar, TRUE, FALSE);
	}
	else
	{
		ModifyStyle(WS_CAPTION|WS_THICKFRAME,0);			
		ShowWindow(SW_MAXIMIZE);

		CFrameWnd* pChild = GetActiveFrame();
		if (pChild)	pChild->ShowWindow(SW_MAXIMIZE);

		ShowControlBar(&m_wndToolBar, FALSE, FALSE);
		ShowControlBar(&m_wndStatusBar, FALSE, FALSE);
	}
	m_fullscreen = !m_fullscreen;
}
//////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateViewFullscreen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_fullscreen);	
}
//////////////////////////////////////////////////////////////////////////////
