// demo.h : main header file for the DEMO application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#ifdef VATI_EXTENSIONS
// just for including CXTEXTINFO type declaration:
#include "ximage.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoApp:
// See demo.cpp for the implementation of this class
//

class CDemoApp : public CWinApp
{
public:
	CDemoApp();

	// Attributes
	int m_nDocCount;	//number of documents
	CMultiDocTemplate *demoTemplate;

#ifdef VATI_EXTENSIONS
	int m_optJpegQuality;
    // for text placement
    CXTEXTINFO  m_text;
#endif

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Operations
	BOOL PromptForFileName(CString& fileName, UINT nIDSTitle, 
		DWORD dwFlags, BOOL bOpenFileDialog, int* pType=NULL);
	int GetIndexFromType(int nDocType, BOOL bOpenFileDialog);
	int GetTypeFromIndex(int nIndex, BOOL bOpenFileDialog);
	CString GetExtFromType(int nDocType);
	CString GetDescFromType(int nDocType);
	CString GetFileTypes(BOOL bOpenFileDialog);
	BOOL GetWritableType(int nDocType);

// Implementation

	//{{AFX_MSG(CDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnImageFromBitmap();
	afx_msg void OnCximageLoadjpegresource();
	afx_msg void OnCximageLoadiconresource();
	afx_msg void OnCximageLoadgifresource();
	afx_msg void OnCximageLoadpngresource();
	afx_msg void OnCximageLoadtifresource();
	afx_msg void OnWindowCloseall();
	afx_msg void OnCximageDemosavemultipagetiff();
	afx_msg void OnCximageDemosaveanimatedgif();
	afx_msg void OnCximageDownloadfromurl();
	afx_msg void OnCximageDemocreatefromarray();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CDemoApp theApp;

struct DocType
{
public:
	int nID;
	BOOL bRead;
	BOOL bWrite;
	const char* description;
	const char* ext;
};


/////////////////////////////////////////////////////////////////////////////
