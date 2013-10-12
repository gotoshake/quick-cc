// DlgResample.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgResample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// DlgResample dialog


DlgResample::DlgResample(CWnd* pParent /*=NULL*/)
	: CDialog(DlgResample::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgResample)
	m_factor = 0.0f;
	//}}AFX_DATA_INIT
}


void DlgResample::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgResample)
	DDX_Control(pDX, IDC_RADIO3, m_r3);
	DDX_Control(pDX, IDC_RADIO2, m_r2);
	DDX_Control(pDX, IDC_RADIO1, m_r1);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_canc);
	DDX_Text(pDX, IDC_EDIT1, m_factor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgResample, CDialog)
	//{{AFX_MSG_MAP(DlgResample)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// DlgResample message handlers

BOOL DlgResample::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ok.SetIcon(IDI_G,BS_LEFT);
	m_canc.SetIcon(IDI_R,BS_LEFT);

	m_r1.SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgResample::OnOK() 
{
	if (m_r1.GetCheck()) m_mode=1;
	if (m_r2.GetCheck()) m_mode=0;
	if (m_r3.GetCheck()) m_mode=2;
	
	CDialog::OnOK();
}
