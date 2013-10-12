// demo.cpp : Defines the class behaviors for the application.

#include "stdafx.h"
#include "demo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "demoDoc.h"
#include "demoView.h"
#include "xTargetButton.h"
#include "DlgURL.h"

#include "ximage.h"
#include "ximagif.h"
#include "ximatif.h"
#include "xfile.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

DocType doctypes[CMAX_IMAGE_FORMATS] =
{
	{ -1, TRUE, TRUE, "Supported files", "*.bmp;*.gif;*.jpg;*.jpeg;*.png;*.ico;*.tif;*.tiff;*.tga;*.pcx;*.wbmp;*.wmf;*.emf;*.j2k;*.jp2;*.jbg;*.j2c;*.jpc;*.pgx;*.pnm;*.pgm;*.ppm;*.ras" },
#if CXIMAGE_SUPPORT_BMP
	{ CXIMAGE_FORMAT_BMP, TRUE, TRUE, "BMP files", "*.bmp" },
#endif
#if CXIMAGE_SUPPORT_GIF
	{ CXIMAGE_FORMAT_GIF, TRUE, TRUE, "GIF files", "*.gif" },
#endif
#if CXIMAGE_SUPPORT_JPG
	{ CXIMAGE_FORMAT_JPG, TRUE, TRUE, "JPG files", "*.jpg;*.jpeg" },
#endif
#if CXIMAGE_SUPPORT_PNG
	{ CXIMAGE_FORMAT_PNG, TRUE, TRUE, "PNG files", "*.png" },
#endif
#if CXIMAGE_SUPPORT_MNG
	{ CXIMAGE_FORMAT_MNG, TRUE, TRUE, "MNG files", "*.mng;*.jng;*.png" },
#endif
#if CXIMAGE_SUPPORT_ICO
	{ CXIMAGE_FORMAT_ICO, TRUE, TRUE, "ICO CUR files", "*.ico;*.cur" },
#endif
#if CXIMAGE_SUPPORT_TIF
	{ CXIMAGE_FORMAT_TIF, TRUE, TRUE, "TIF files", "*.tif;*.tiff" },
#endif
#if CXIMAGE_SUPPORT_TGA
	{ CXIMAGE_FORMAT_TGA, TRUE, TRUE, "TGA files", "*.tga" },
#endif
#if CXIMAGE_SUPPORT_PCX
	{ CXIMAGE_FORMAT_PCX, TRUE, TRUE, "PCX files", "*.pcx" },
#endif
#if CXIMAGE_SUPPORT_WBMP
	{ CXIMAGE_FORMAT_WBMP, TRUE, TRUE, "WBMP files", "*.wbmp" },
#endif
#if CXIMAGE_SUPPORT_WMF
	{ CXIMAGE_FORMAT_WMF, TRUE, FALSE, "WMF EMF files", "*.wmf;*.emf" },
#endif
#if CXIMAGE_SUPPORT_J2K
	{ CXIMAGE_FORMAT_J2K, TRUE, TRUE, "J2K files", "*.j2k;*.jp2" },
#endif
#if CXIMAGE_SUPPORT_JBG
	{ CXIMAGE_FORMAT_JBG, TRUE, TRUE, "JBG files", "*.jbg" },
#endif
#if CXIMAGE_SUPPORT_JP2
	{ CXIMAGE_FORMAT_JP2, TRUE, TRUE, "JP2 files", "*.j2k;*.jp2" },
#endif
#if CXIMAGE_SUPPORT_JPC
	{ CXIMAGE_FORMAT_JPC, TRUE, TRUE, "JPC files", "*.j2c;*.jpc" },
#endif
#if CXIMAGE_SUPPORT_PGX
	{ CXIMAGE_FORMAT_PGX, TRUE, TRUE, "PGX files", "*.pgx" },
#endif
#if CXIMAGE_SUPPORT_RAS
	{ CXIMAGE_FORMAT_RAS, TRUE, TRUE, "RAS files", "*.ras" },
#endif
#if CXIMAGE_SUPPORT_PNM
	{ CXIMAGE_FORMAT_PNM, TRUE, TRUE, "PNM files", "*.pnm;*.pgm;*.ppm" }
#endif
};

//////////////////////////////////////////////////////////////////////////////
// CDemoApp
BEGIN_MESSAGE_MAP(CDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_IMAGE_FROM_BITMAP, OnImageFromBitmap)
	ON_COMMAND(ID_CXIMAGE_LOADJPEGRESOURCE, OnCximageLoadjpegresource)
	ON_COMMAND(ID_CXIMAGE_LOADICONRESOURCE, OnCximageLoadiconresource)
	ON_COMMAND(ID_CXIMAGE_LOADGIFRESOURCE, OnCximageLoadgifresource)
	ON_COMMAND(ID_CXIMAGE_LOADPNGRESOURCE, OnCximageLoadpngresource)
	ON_COMMAND(ID_CXIMAGE_LOADTIFRESOURCE, OnCximageLoadtifresource)
	ON_COMMAND(ID_WINDOW_CLOSEALL, OnWindowCloseall)
	ON_COMMAND(ID_CXIMAGE_DEMOSAVEMULTIPAGETIFF, OnCximageDemosavemultipagetiff)
	ON_COMMAND(ID_CXIMAGE_DEMOSAVEANIMATEDGIF, OnCximageDemosaveanimatedgif)
	ON_COMMAND(ID_CXIMAGE_DOWNLOADFROMURL, OnCximageDownloadfromurl)
	ON_COMMAND(ID_CXIMAGE_DEMOCREATEFROMARRAY, OnCximageDemocreatefromarray)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CDemoApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CDemoApp construction
CDemoApp::CDemoApp()
{
	m_nDocCount=1; //counter for documents

}
//////////////////////////////////////////////////////////////////////////////
// The one and only CDemoApp object
CDemoApp theApp;

//////////////////////////////////////////////////////////////////////////////
// CDemoApp initialization
BOOL CDemoApp::InitInstance()
{
	// <dave> dump memory leaks
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	// Standard initialization
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings(9);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DEMOTYPE,
		RUNTIME_CLASS(CDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDemoView));
	demoTemplate = pDocTemplate;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME)) return FALSE;
	m_pMainWnd = pMainFrame;

	// This code replaces the MFC created menus with 
	// the Ownerdrawn versions 
	pDocTemplate->m_hMenuShared=pMainFrame->NewMenu();
	pMainFrame->m_hMenuDefault=pMainFrame->NewDefaultMenu();
	// This simulates a window being opened if you don't have
	// a default window displayed at startup
	pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
    // Alter behaviour to not open window immediately
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)) return FALSE;

#ifdef VATI_EXTENSIONS
    // init m_text by a temporary CxImage 
	CxImage *ima = new CxImage;
	ima->InitTextInfo( &m_text );
	delete ima;
    
	//recall last used font data for Text tool
    sprintf( m_text.lfont.lfFaceName, GetProfileString ( "TextTool", "lfFaceName", "Arial") );
	m_text.lfont.lfCharSet   = GetProfileInt ( "TextTool", "lfCharSet", EASTEUROPE_CHARSET ) ;
    m_text.lfont.lfWeight    = GetProfileInt ( "TextTool", "lfWeight", 0 );
    m_text.lfont.lfItalic    = GetProfileInt ( "TextTool", "lfItalic", 0 ); 
    m_text.lfont.lfUnderline = GetProfileInt ( "TextTool", "lfUnderline", 0 ); 
    m_text.fcolor = GetProfileInt ( "TextTool", "fcolor", RGB( 255,255,160 ));
    m_text.bcolor = GetProfileInt ( "TextTool", "bcolor", RGB( 32, 96, 0 ));
    m_text.opaque = GetProfileInt ( "TextTool", "opaque", 1);
    m_text.b_opacity = (float)(GetProfileInt( "TextTool", "opacity", 0 ))/(float)100.;  
    m_text.b_round   = GetProfileInt ( "TextTool", "roundradius", 25 );

	m_optJpegQuality = GetProfileInt("Options","JpegQuality",90);

	// recall if main window was maximized on last exit
    if ( GetProfileInt ( "Screen", "maximized", 0 ))
        m_nCmdShow|=SW_MAXIMIZE;
#endif;

	// The main window has been initialized, so show and update it.
    pMainFrame -> ShowWindow ( m_nCmdShow ) ;
	pMainFrame->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable open from command line
	if (*m_lpCmdLine != 0)
		OpenDocumentFile(m_lpCmdLine);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CxTargetButton	m_ok;
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////////
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}
//////////////////////////////////////////////////////////////////////////////
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCapture)
	DDX_Control(pDX, IDOK, m_ok);
	//}}AFX_DATA_MAP
}
//////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////////
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ok.SetIcon(IDI_G,BS_LEFT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////////
// App command to run the dialog
void CDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnFileOpen() 
{
	// prompt the user (with all document templates)
	CString newName;
	int nDocType = -1;
	if (!PromptForFileName(newName, AFX_IDS_OPENFILE,
	  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, &nDocType))
		return; // open cancelled
	
	OpenDocumentFile(newName);

}
//////////////////////////////////////////////////////////////////////////////
// prompt for file name - used for open and save as
// static function called from app
BOOL CDemoApp::PromptForFileName(CString& fileName, UINT nIDSTitle, 
	DWORD dwFlags, BOOL bOpenFileDialog, int* pType)
{
	CFileDialog dlgFile(bOpenFileDialog);
	CString title;
	if (bOpenFileDialog) title="Open image file"; else title="Save image file";

	dlgFile.m_ofn.Flags |= dwFlags;

	int nDocType = (pType != NULL) ? *pType : CXIMAGE_FORMAT_BMP;
	if (nDocType==0) nDocType=1;

	int nIndex = GetIndexFromType(nDocType, bOpenFileDialog);
	if (nIndex == -1) nIndex = 0;

	dlgFile.m_ofn.nFilterIndex = nIndex +1;
	// strDefExt is necessary to hold onto the memory from GetExtFromType
	CString strDefExt = GetExtFromType(nDocType).Mid(2,3);
	dlgFile.m_ofn.lpstrDefExt = strDefExt;
		
	CString strFilter = GetFileTypes(bOpenFileDialog);
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	BOOL bRet = (dlgFile.DoModal() == IDOK) ? TRUE : FALSE;
	fileName.ReleaseBuffer();
	if (bRet){
		if (pType != NULL){
			int nIndex = (int)dlgFile.m_ofn.nFilterIndex - 1;
			ASSERT(nIndex >= 0);
			*pType = GetTypeFromIndex(nIndex, bOpenFileDialog);
		}
	}
	return bRet;
}
//////////////////////////////////////////////////////////////////////////////
int CDemoApp::GetIndexFromType(int nDocType, BOOL bOpenFileDialog)
{
	int nCnt = 0;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog ? doctypes[i].bRead : doctypes[i].bWrite){
			if (doctypes[i].nID == nDocType) return nCnt;
			nCnt++;
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////////
int CDemoApp::GetTypeFromIndex(int nIndex, BOOL bOpenFileDialog)
{
	int nCnt = 0;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog ? doctypes[i].bRead : doctypes[i].bWrite){
			if (nCnt == nIndex)
//              return i; // PJO - Buglet ?
                return doctypes[i].nID;
			nCnt++;
		}
	}
	ASSERT(FALSE);
	return -1;
}
//////////////////////////////////////////////////////////////////////////////
CString CDemoApp::GetExtFromType(int nDocType)
{
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].ext;
	}
	return CString("");
}
//////////////////////////////////////////////////////////////////////////////
CString CDemoApp::GetDescFromType(int nDocType)
{
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].description;
	}
	return CString("");
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoApp::GetWritableType(int nDocType){
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].bWrite;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////
CString CDemoApp::GetFileTypes(BOOL bOpenFileDialog)
{
	CString str;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog && doctypes[i].bRead){
			str += doctypes[i].description;
			str += (TCHAR)NULL;
			str += doctypes[i].ext;
			str += (TCHAR)NULL;
		} else if (!bOpenFileDialog && doctypes[i].bWrite) {
			str += doctypes[i].description;
			str += (TCHAR)NULL;
			str += doctypes[i].ext;
			str += (TCHAR)NULL;
		}
	}
	return str;
}

//////////////////////////////////////////////////////////////////////////////
// CDemoApp commands
void CDemoApp::OnImageFromBitmap() 
{
/*	HBITMAP bitmap;
	if (!(bitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1)))){
		AfxMessageBox("Could not load bitmap from resource");
		return;
	}*/

	CxImage* newImage = new CxImage();
	if (!newImage->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDB_BITMAP1),RT_BITMAP),CXIMAGE_FORMAT_BMP)){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
		return;
	}

	CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
	if (doc){
		doc->image = newImage;
		CString s;
		s.Format("BITMAP Resource Image %d",m_nDocCount++);
		doc->SetTitle(s);
		doc->UpdateAllViews(0);
		doc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageLoadjpegresource() 
{
	CxImage* newImage = new CxImage();
	if (!newImage->LoadResource(FindResource(NULL,"IDR_JPG2","JPG"),CXIMAGE_FORMAT_JPG)){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
		return;
	}
	CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
	if (doc){
		doc->image = newImage;
		CString s;
		s.Format("JPEG Resource Image %d",m_nDocCount++);
		doc->SetTitle(s);
		doc->UpdateAllViews(0);
		doc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageLoadiconresource() 
{
	CxImage* newImage = new CxImage();
	if (!newImage->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_ICO1),"ICO"),CXIMAGE_FORMAT_ICO)){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
		return;
	}

//	HICON my_Icon = (HICON)::LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_G),IMAGE_ICON,0, 0, 0);
//	CxImage my_image;
//	my_image.CreateFromHICON(my_Icon);
//	DestroyIcon(my_Icon);

	CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
	if (doc){
		doc->image = newImage;
		CString s;
		s.Format("Icon Resource Image %d",m_nDocCount++);
		doc->SetTitle(s);
		doc->UpdateAllViews(0);
		doc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageLoadgifresource() 
{
	CxImage* newImage = new CxImage();
	if (!newImage->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_GIF1),"GIF"),CXIMAGE_FORMAT_GIF)){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
		return;
	}
	CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
	if (doc){
		doc->image = newImage;

		CString s;
		s.Format("GIF Resource Image %d",m_nDocCount++);
		doc->SetTitle(s);
		doc->UpdateAllViews(0);
		doc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageLoadpngresource() 
{
	CxImage* newImage = new CxImage();
	if (!newImage->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_PNG1),"PNG"),CXIMAGE_FORMAT_PNG)){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
		return;
	}

	CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
	if (doc){
		doc->image = newImage;

		CString s;
		s.Format("PNG Resource Image %d",m_nDocCount++);
		doc->SetTitle(s);
		doc->UpdateAllViews(0);
		doc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageLoadtifresource() 
{
	CxImage* newImage = new CxImage();
	if (!newImage->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_TIF1),"TIF"),CXIMAGE_FORMAT_TIF)){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
		return;
	}
	CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
	if (doc){
		doc->image = newImage;

		CString s;
		s.Format("TIF Resource Image %d",m_nDocCount++);
		doc->SetTitle(s);
		doc->UpdateAllViews(0);
		doc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnWindowCloseall() 
{
	POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition(); 
    while(pos) { 
        CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate(pos); 
        POSITION pos2 = pTemplate->GetFirstDocPosition(); 
        while(pos2) { 
            CDocument* pDocument; 
			if ((pDocument=pTemplate->GetNextDoc(pos2)) != NULL) 
				pDocument->OnCloseDocument();  
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageDemosavemultipagetiff() 
{
	CxImage* newImage1 = new CxImage();
	if (!newImage1->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_TIF1),"TIF"),CXIMAGE_FORMAT_TIF)){
		AfxMessageBox(newImage1->GetLastError());
		delete newImage1;
		newImage1 =NULL;
	}
	CxImage* newImage2 = new CxImage();
	if (!newImage2->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_GIF1),"GIF"),CXIMAGE_FORMAT_GIF)){
		AfxMessageBox(newImage2->GetLastError());
		delete newImage2;
		newImage2 =NULL;
	}
	CxImage* newImage3 = new CxImage();
	if (!newImage3->LoadResource(FindResource(NULL,"IDR_JPG2","JPG"),CXIMAGE_FORMAT_JPG)){
		AfxMessageBox(newImage3->GetLastError());
		delete newImage3;
		newImage3 =NULL;
	}
	newImage3->DecreaseBpp(8,true);

	CxImage *pimage[3];
	pimage[0]=newImage1;
	pimage[1]=newImage2;
	pimage[2]=newImage3;

	FILE* hFile;
	hFile = fopen("multipage.tif","w+b");

	CxImage multiimage;
	multiimage.Encode(hFile,pimage,3,CXIMAGE_FORMAT_TIF);

	fclose(hFile);

	delete newImage1;
	delete newImage2;
	delete newImage3;

	/*{
	FILE* hFile;
	hFile = fopen("c:\\multi.tif","w+b");

	CxImageTIF image;
	image.Load("c:\\1.tif",CXIMAGE_FORMAT_TIF);
	image.Encode(hFile,true);
	image.Load("c:\\2.bmp",CXIMAGE_FORMAT_BMP);
	image.Encode(hFile,true);
	image.Load("c:\\3.png",CXIMAGE_FORMAT_PNG);
	image.Encode(hFile);

	fclose(hFile);
	}*/

	AfxMessageBox("file ""mulipage.tif"" saved to disk",MB_OK);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageDemosaveanimatedgif() 
{
	CxImage* newImage = new CxImage();
	if (!newImage->LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_GIF1),"GIF"),CXIMAGE_FORMAT_GIF)){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
	}
	
	newImage->IncreaseBpp(24);

	CxImage ima1,ima2,ima3;
	ima1.Copy(*newImage);
	ima1.Light(22);
	ima2.Copy(*newImage);
	ima2.Light(44);
	ima3.Copy(*newImage);
	ima3.Light(66);

	newImage->DecreaseBpp(8,0,0);
	ima1.DecreaseBpp(8,0,0);
	ima2.DecreaseBpp(8,0,0);
	ima3.DecreaseBpp(8,0,0);

	newImage->SetTransIndex(newImage->GetPixelIndex(0,0));
	ima1.SetTransIndex(ima1.GetPixelIndex(0,0));
	ima2.SetTransIndex(ima2.GetPixelIndex(0,0));
	ima3.SetTransIndex(ima3.GetPixelIndex(0,0));

	newImage->SetFrameDelay(22);
	ima1.SetFrameDelay(22);
	ima2.SetFrameDelay(22);
	ima3.SetFrameDelay(44);

	CxImage *pimage[7];
	pimage[0]=newImage;
	pimage[1]=&ima1;
	pimage[2]=&ima2;
	pimage[3]=&ima3;
	pimage[4]=&ima2;
	pimage[5]=&ima1;
	pimage[6]=newImage;

	FILE* hFile;
	hFile = fopen("ani.gif","wb");

	CxImageGIF multiimage;
	multiimage.SetComment("CxImage demo");
	multiimage.SetLoops(3);
	multiimage.SetDisposalMethod(2);
	multiimage.Encode(hFile,pimage,7);

	fclose(hFile);

	delete newImage;

	AfxMessageBox("file ""ani.gif"" saved to disk",MB_OK);

}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageDownloadfromurl() 
{
	DlgURL dlg;
	if (dlg.DoModal()==IDOK){
		long size = dlg.m_size;
		if (size){
			CxMemFile memfile((BYTE*)dlg.m_data.GetBuffer(0),size);

			CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
			if (doc){
				CString ext(doc->FindExtension(dlg.m_url));
				ext.MakeLower();
				if (ext == "") return;

				int type = doc->FindType(ext);

				CxImage* ima = new CxImage();
				ima->Decode(&memfile,type);

				doc->image = ima;
				doc->SetTitle(dlg.m_url);
				doc->UpdateAllViews(0);
				doc->UpdateStatusBar();




				if (ima->GetNumFrames()>1){
					CString s;
					s.Format("File with %d images. Read all?",ima->GetNumFrames());
					if (AfxMessageBox(s,MB_OKCANCEL)==IDOK){
						
						int j; // points to the document name
						for(j=strlen(dlg.m_url)-1;j>=0;j--){
							if (dlg.m_url[j]=='\\'){	j++; break;	}
						}
						// create the documents for the other images
						for(int i=1;i<ima->GetNumFrames();i++){
							CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL);
							if (NewDoc)	{
								CxImage *newImage = new CxImage();
								newImage->SetFrame(i);
								memfile.Seek(0,SEEK_SET);
								newImage->Decode(&memfile,type);
								NewDoc->image = newImage;
								CString s;
								s.Format("%s (%d)",dlg.m_url.Mid(j),i+1);
								NewDoc->SetTitle(s);
								NewDoc->UpdateAllViews(NULL,WM_USER_NEWIMAGE);
							}
						}
					}
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoApp::OnCximageDemocreatefromarray() 
{
	CxImage* newImage = new CxImage();

	long w = 256;
	long h = 256;
	BYTE c = 4;

	BYTE* pArray = (BYTE*)malloc(w*h*c);

	int n,d,e;
	int a=w/2;
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			n=c*(j+w*i);
			d=(BYTE)((a*i)/h+(a*(w-j))/w);
			e=(BYTE)((a*(h-i))/h+(a*(w-j))/w);
			if (c==4) pArray[n+3]=(BYTE)(d);
			pArray[n+2]=(BYTE)(e);
			pArray[n+1]=(BYTE)(255-d);
			pArray[n]=(BYTE)(255-e);
		}
	}

	newImage->CreateFromArray(pArray,w,h,8*c,c*w,0);
	free(pArray);

	if (!newImage->IsValid()){
		AfxMessageBox(newImage->GetLastError());
		delete newImage;
		newImage =NULL;
		return;
	}

	CDemoDoc *doc = (CDemoDoc *)demoTemplate->OpenDocumentFile(NULL);
	if (doc){
		doc->image = newImage;

		CString s;
		s.Format("CreateFromArray Image %d",m_nDocCount++);
		doc->SetTitle(s);
		doc->UpdateAllViews(0);
		doc->UpdateStatusBar();
	}
}
//////////////////////////////////////////////////////////////////////////////
