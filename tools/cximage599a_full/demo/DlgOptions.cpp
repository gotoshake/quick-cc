// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgOptions.h"

#include "ximajpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgOptions dialog


DlgOptions::DlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(DlgOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgOptions)
	m_quality = 0;
	m_xres = 0;
	m_yres = 0;
	//}}AFX_DATA_INIT
}


void DlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgOptions)
	DDX_Control(pDX, IDEXIF, m_info);
	DDX_Control(pDX, IDC_RADIO7, m_rEnc7);
	DDX_Control(pDX, IDC_RADIO6, m_rEnc5);
	DDX_Control(pDX, IDC_RADIO5, m_rEnc4);
	DDX_Control(pDX, IDC_RADIO4, m_rEnc3);
	DDX_Control(pDX, IDC_RADIO3, m_rEnc2);
	DDX_Control(pDX, IDC_RADIO2, m_rEnc1);
	DDX_Control(pDX, IDC_RADIO1, m_rEnc0);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_canc);
	DDX_Text(pDX, IDC_EDIT1, m_quality);
	DDV_MinMaxByte(pDX, m_quality, 1, 255);
	DDX_Text(pDX, IDC_EDIT2, m_xres);
	DDV_MinMaxLong(pDX, m_xres, 0, 10000);
	DDX_Text(pDX, IDC_EDIT3, m_yres);
	DDV_MinMaxDWord(pDX, m_yres, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgOptions, CDialog)
	//{{AFX_MSG_MAP(DlgOptions)
	ON_BN_CLICKED(IDEXIF, OnExif)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgOptions message handlers

BOOL DlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ok.SetIcon(IDI_G,BS_LEFT);
	m_canc.SetIcon(IDI_R,BS_LEFT);
	m_info.SetIcon(IDI_B,BS_LEFT);

	m_info.EnableWindow(m_exif->m_exifinfo.IsExif);

	switch(m_EncodeOption)
	{
	case 1:
		m_rEnc1.SetCheck(1);
		break;
	case 2:
		m_rEnc2.SetCheck(1);
		break;
	case 3:
	case 4:
		m_rEnc3.SetCheck(1);
		break;
	case 32773:
		m_rEnc4.SetCheck(1);
		break;
	case 7:
		m_rEnc5.SetCheck(1);
		break;
	default:
		m_rEnc0.SetCheck(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgOptions::OnOK() 
{
	if (m_rEnc1.GetCheck()) m_EncodeOption = 1;
	if (m_rEnc2.GetCheck()) m_EncodeOption = 2;
	if (m_rEnc3.GetCheck()) m_EncodeOption = 4;
	if (m_rEnc4.GetCheck()) m_EncodeOption = 32773;
	if (m_rEnc5.GetCheck()) m_EncodeOption = 7;
	if (m_rEnc7.GetCheck()) m_EncodeOption = 5;
	if (m_rEnc0.GetCheck()) m_EncodeOption = 0;
	
	CDialog::OnOK();
}

void DlgOptions::OnExif() 
{
	CString s,t;
	s="";

    if (m_exif->m_exifinfo.CameraMake[0]){
        t.Format("Camera make  : %s\n",m_exif->m_exifinfo.CameraMake); s+=t;
        t.Format("Camera model : %s\n",m_exif->m_exifinfo.CameraModel); s+=t;
    }
    if (m_exif->m_exifinfo.DateTime[0]){
        t.Format("Date/Time    : %s\n",m_exif->m_exifinfo.DateTime); s+=t;
    }
    if (m_exif->m_exifinfo.Version[0]){
        t.Format("Exif version : %s\n",m_exif->m_exifinfo.Version); s+=t;
    }

    t.Format("Width x Height   : %d x %d\n",m_exif->m_exifinfo.Width, m_exif->m_exifinfo.Height); s+=t;

	if ((m_exif->m_exifinfo.ResolutionUnit!=0)&&(m_exif->m_exifinfo.Xresolution!=0)){
		t.Format("X resolution (dpi) : %5.1f\n",m_exif->m_exifinfo.Xresolution/m_exif->m_exifinfo.ResolutionUnit); s+=t;
	}
	if ((m_exif->m_exifinfo.ResolutionUnit!=0)&&(m_exif->m_exifinfo.Yresolution!=0)){
		t.Format("Y resolution (dpi) : %5.1f\n",m_exif->m_exifinfo.Yresolution/m_exif->m_exifinfo.ResolutionUnit); s+=t;
	}

    if (m_exif->m_exifinfo.Orientation > 1){
        t.Format("Orientation  : %s\n", m_exif->m_exifinfo.Orientation); s+=t;
    }
    if (m_exif->m_exifinfo.IsColor == 0){
        t.Format("Color/bw     : Black and white\n"); s+=t;
    }
    if (m_exif->m_exifinfo.FlashUsed >= 0){
        t.Format("Flash used   : %s\n",m_exif->m_exifinfo.FlashUsed ? "Yes" :"No"); s+=t;
    }
    if (m_exif->m_exifinfo.FocalLength){
        t.Format("Focal length : %4.1fmm",(double)m_exif->m_exifinfo.FocalLength); s+=t;
        if (m_exif->m_exifinfo.CCDWidth){
            t.Format("  (35mm equivalent: %dmm)",
                        (int)(m_exif->m_exifinfo.FocalLength/m_exif->m_exifinfo.CCDWidth*36 + 0.5)); s+=t;
        }
        t.Format("\n"); s+=t;
    }

    if (m_exif->m_exifinfo.CCDWidth){
        t.Format("CCD width    : %4.2fmm\n",(double)m_exif->m_exifinfo.CCDWidth); s+=t;
    }

    if (m_exif->m_exifinfo.ExposureTime){
        t.Format("Exposure time:%6.3f s ",(double)m_exif->m_exifinfo.ExposureTime); s+=t;
        if (m_exif->m_exifinfo.ExposureTime <= 0.5){
            t.Format(" (1/%d)",(int)(0.5 + 1/m_exif->m_exifinfo.ExposureTime)); s+=t;
        }
        t.Format("\n"); s+=t;
    }
	if (m_exif->m_exifinfo.Brightness){
		t.Format("Brightness : %6.3f\n",m_exif->m_exifinfo.Brightness); s+=t;
	}
    if (m_exif->m_exifinfo.ApertureFNumber){
        t.Format("Aperture     : f/%3.1f\n",(double)m_exif->m_exifinfo.ApertureFNumber); s+=t;
    }
    if (m_exif->m_exifinfo.Distance){
        if (m_exif->m_exifinfo.Distance < 0){
            t.Format("Focus dist.  : Infinite\n"); s+=t;
        }else{
            t.Format("Focus dist.  : %4.2fm\n",(double)m_exif->m_exifinfo.Distance); s+=t;
        }
    }


    if (m_exif->m_exifinfo.ISOequivalent){ // 05-jan-2001 vcs
        t.Format("ISO equiv.   : %2d\n",(int)m_exif->m_exifinfo.ISOequivalent); s+=t;
    }
    if (m_exif->m_exifinfo.ExposureBias){ // 05-jan-2001 vcs
        t.Format("Exposure bias:%4.2f\n",(double)m_exif->m_exifinfo.ExposureBias); s+=t;
    }
        
    if (m_exif->m_exifinfo.Whitebalance){ // 05-jan-2001 vcs
        switch(m_exif->m_exifinfo.Whitebalance) {
        case 1:
            t.Format("Whitebalance : sunny\n"); s+=t;
            break;
        case 2:
            t.Format("Whitebalance : fluorescent\n"); s+=t;
            break;
        case 3:
            t.Format("Whitebalance : incandescent\n"); s+=t;
            break;
        default:
            t.Format("Whitebalance : cloudy\n"); s+=t;
        }
    }
    if (m_exif->m_exifinfo.MeteringMode){ // 05-jan-2001 vcs
        switch(m_exif->m_exifinfo.MeteringMode) {
        case 2:
            t.Format("Metering Mode: center weight\n"); s+=t;
            break;
        case 3:
            t.Format("Metering Mode: spot\n"); s+=t;
            break;
        case 5:
            t.Format("Metering Mode: matrix\n"); s+=t;
            break;
        }
    }
    if (m_exif->m_exifinfo.ExposureProgram){ // 05-jan-2001 vcs
        switch(m_exif->m_exifinfo.ExposureProgram) {
        case 2:
            t.Format("Exposure     : program (auto)\n"); s+=t;
            break;
        case 3:
            t.Format("Exposure     : aperture priority (semi-auto)\n"); s+=t;
            break;
        case 4:
            t.Format("Exposure     : shutter priority (semi-auto)\n"); s+=t;
            break;
        }
    }
    if (m_exif->m_exifinfo.CompressionLevel){ // 05-jan-2001 vcs
        switch(m_exif->m_exifinfo.CompressionLevel) {
        case 1:
            t.Format("Jpeg Quality : basic\n"); s+=t;
            break;
        case 2:
            t.Format("Jpeg Quality : normal\n"); s+=t;
            break;
        case 4:
            t.Format("Jpeg Quality : fine\n"); s+=t;
            break;
       }
    }

    t.Format("Encoding      : "); s+=t;
	switch(m_exif->m_exifinfo.Process){
	case 0xC0: //M_SOF0
		t.Format("Baseline\n"); s+=t;
		break;
	case 0xC1: //M_SOF1
		t.Format("Extended sequential\n"); s+=t;
		break;
	case 0xC2: //M_SOF2
		t.Format("Progressive\n"); s+=t;
		break;
	case 0xC3: //M_SOF3
		t.Format("Lossless\n"); s+=t;
		break;
	case 0xC5: //M_SOF5
		t.Format("Differential sequential\n"); s+=t;
		break;
	case 0xC6: //M_SOF6
		t.Format("Differential progressive\n"); s+=t;
		break;
	case 0xC7: //M_SOF7
		t.Format("Differential lossless\n"); s+=t;
		break;
	case 0xC9: //M_SOF9
		t.Format("Extended sequential, arithmetic coding\n"); s+=t;
		break;
	case 0xCA: //M_SOF10
		t.Format("Progressive, arithmetic coding\n"); s+=t;
		break;
	case 0xCB: //M_SOF11
		t.Format("Lossless, arithmetic coding\n"); s+=t;
		break;
	case 0xCD: //M_SOF13
		t.Format("Differential sequential, arithmetic coding\n"); s+=t;
		break;
	case 0xCE: //M_SOF14
		t.Format("Differential progressive, arithmetic coding\n"); s+=t;
		break;
	case 0xCF: //M_SOF0
		t.Format("Differential lossless, arithmetic coding\n"); s+=t;
		break;
	default:
		t.Format("Unknown\n"); s+=t;
		break;
	}

    // Print the comment. Print 'Comment:' for each new line of comment.
    if (m_exif->m_exifinfo.Comments[0]){
        int a;
        char c;
        t.Format("Comment      : "); s+=t;
        for (a=0;a<MAX_COMMENT;a++){
            c = m_exif->m_exifinfo.Comments[a];
            if (c == '\0') break;
            if (c == '\n'){
                // Do not start a new line if the string ends with a carriage return.
                if (m_exif->m_exifinfo.Comments[a+1] != '\0'){
                    t.Format("\nComment      : "); s+=t;
                }else{
                    t.Format("\n"); s+=t;
                }
            }else{
                s+=c;
            }
        }
    }

    t.Format("\n"); s+=t;
		
	MessageBox(s,"EXIF",MB_OK|MB_ICONQUESTION);
}
