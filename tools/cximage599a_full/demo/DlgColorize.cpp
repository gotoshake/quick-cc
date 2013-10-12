// DlgColorize.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgColorize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgColorize dialog


DlgColorize::DlgColorize(CWnd* pParent /*=NULL*/)
	: CDialog(DlgColorize::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgColorize)
	m_hue = 0;
	m_sat = 0;
	m_r = 0;
	m_g = 0;
	m_b = 0;
	//}}AFX_DATA_INIT
}


void DlgColorize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgColorize)
	DDX_Control(pDX, IDC_RADIO3, m_rbHSL);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_canc);
	DDX_Text(pDX, IDC_EDIT1, m_hue);
	DDX_Text(pDX, IDC_EDIT2, m_sat);
	DDX_Text(pDX, IDC_EDIT3, m_r);
	DDX_Text(pDX, IDC_EDIT4, m_g);
	DDX_Text(pDX, IDC_EDIT5, m_b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgColorize, CDialog)
	//{{AFX_MSG_MAP(DlgColorize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgColorize message handlers

BOOL DlgColorize::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ok.SetIcon(IDI_G,BS_LEFT);
	m_canc.SetIcon(IDI_R,BS_LEFT);
	
	m_rbHSL.SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgColorize::OnOK() 
{
	m_bHSL = m_rbHSL.GetCheck();
	
	CDialog::OnOK();
}
