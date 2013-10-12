// demoDoc.cpp : implementation of the CDemoDoc class
//

#include "stdafx.h"
#include "demo.h"

#include "MainFrm.h"
#include "demoDoc.h"
#include "demoView.h"
#include "DlgRotate.h"
#include "DlgResample.h"
#include "DlgDecBpp.h"
#include "DlgIncBpp.h"
#include "DlgOptions.h"
#include "DlgDither.h"
#include "DlgThreshold.h"
#include "DlgColorize.h"
#include "Quantize.h"
#include "DlgOpacity.h"
#include "DlgGamma.h"
#include "DlgPalette.h"
#include "DlgCombine.h"
#include "DlgFFT.h"
#include "DlgRepair.h"
#include "DlgText.h"
#include "DlgMix.h"

#include "ximage.h"
#include <math.h>
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_STRETCH_MODE, OnStretchMode)
	ON_UPDATE_COMMAND_UI(ID_STRETCH_MODE, OnUpdateStretchMode)
	ON_COMMAND(ID_TRANSFORM_ELLIPSE, OnTransformEllipse)
	ON_COMMAND(ID_WINDOW_DUPLICATE, OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_CXIMAGE_FLIP, OnCximageFlip)
	ON_COMMAND(ID_CXIMAGE_MIRROR, OnCximageMirror)
	ON_COMMAND(ID_CXIMAGE_NEGATIVE, OnCximageNegative)
	ON_COMMAND(ID_CXIMAGE_GRAYSCALE, OnCximageGrayscale)
	ON_COMMAND(ID_CXIMAGE_ROTATE, OnCximageRotate)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomout)
	ON_COMMAND(ID_VIEW_NORMALVIEWING11, OnViewNormalviewing11)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMALVIEWING11, OnUpdateViewNormalviewing11)
	ON_COMMAND(ID_CXIMAGE_SETTRANSPARENCY, OnCximageSettransparency)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SETTRANSPARENCY, OnUpdateCximageSettransparency)
	ON_COMMAND(ID_CXIMAGE_REMOVETRANSPARENCY, OnCximageRemovetransparency)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REMOVETRANSPARENCY, OnUpdateCximageRemovetransparency)
	ON_COMMAND(ID_CXIMAGE_RESAMPLE, OnCximageResample)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_FLIP, OnUpdateCximageFlip)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GRAYSCALE, OnUpdateCximageGrayscale)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_MIRROR, OnUpdateCximageMirror)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_NEGATIVE, OnUpdateCximageNegative)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_RESAMPLE, OnUpdateCximageResample)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ROTATE, OnUpdateCximageRotate)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORM_ELLIPSE, OnUpdateTransformEllipse)
	ON_COMMAND(ID_CXIMAGE_DECREASEBPP, OnCximageDecreasebpp)
	ON_COMMAND(ID_CXIMAGE_INCREASEBPP, OnCximageIncreasebpp)
	ON_COMMAND(ID_CXIMAGE_OPTIONS, OnCximageOptions)
	ON_COMMAND(ID_CXIMAGE_DITHER, OnCximageDither)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DITHER, OnUpdateCximageDither)
	ON_COMMAND(ID_CXIMAGE_THRESHOLD, OnCximageThreshold)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_THRESHOLD, OnUpdateCximageThreshold)
	ON_COMMAND(ID_CXIMAGE_SPLITRGB, OnCximageSplitrgb)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITRGB, OnUpdateCximageSplitrgb)
	ON_COMMAND(ID_CXIMAGE_SPLITYUV, OnCximageSplityuv)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITYUV, OnUpdateCximageSplityuv)
	ON_COMMAND(ID_CXIMAGE_SPLITHSL, OnCximageSplithsl)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITHSL, OnUpdateCximageSplithsl)
	ON_COMMAND(ID_CXIMAGE_PSEUDOCOLORS, OnCximagePseudocolors)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_PSEUDOCOLORS, OnUpdateCximagePseudocolors)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_COLORIZE, OnUpdateCximageFiltersColorize)
	ON_COMMAND(ID_CXIMAGE_COLORIZE, OnCximageFiltersColorize)
	ON_COMMAND(ID_CXIMAGE_DARKEN, OnCximageDarken)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DARKEN, OnUpdateCximageDarken)
	ON_COMMAND(ID_CXIMAGE_LIGHTEN, OnCximageLighten)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_LIGHTEN, OnUpdateCximageLighten)
	ON_COMMAND(ID_CXIMAGE_CONTRAST, OnCximageContrast)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CONTRAST, OnUpdateCximageContrast)
	ON_COMMAND(ID_CXIMAGE_EMBOSS, OnCximageEmboss)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_EMBOSS, OnUpdateCximageEmboss)
	ON_COMMAND(ID_CXIMAGE_BLUR, OnCximageBlur)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_BLUR, OnUpdateCximageBlur)
	ON_COMMAND(ID_CXIMAGE_DILATE, OnCximageDilate)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DILATE, OnUpdateCximageDilate)
	ON_COMMAND(ID_CXIMAGE_EDGE, OnCximageEdge)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_EDGE, OnUpdateCximageEdge)
	ON_COMMAND(ID_CXIMAGE_ERODE, OnCximageErode)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ERODE, OnUpdateCximageErode)
	ON_COMMAND(ID_CXIMAGE_SHARPEN, OnCximageSharpen)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SHARPEN, OnUpdateCximageSharpen)
	ON_COMMAND(ID_CXIMAGE_SOFTEN, OnCximageSoften)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SOFTEN, OnUpdateCximageSoften)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CROP, OnUpdateCximageCrop)
	ON_COMMAND(ID_CXIMAGE_CROP, OnCximageCrop)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REMOVEALPHACHANNEL, OnUpdateCximageRemovealphachannel)
	ON_COMMAND(ID_CXIMAGE_REMOVEALPHACHANNEL, OnCximageRemovealphachannel)
	ON_COMMAND(ID_CXIMAGE_OPACITY, OnCximageOpacity)
	ON_COMMAND(ID_CXIMAGE_INVETALPHA, OnCximageInvetalpha)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_INVETALPHA, OnUpdateCximageInvetalpha)
	ON_COMMAND(ID_CXIMAGE_ALPHAPALETTETOGGLE, OnCximageAlphapalettetoggle)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ALPHAPALETTETOGGLE, OnUpdateCximageAlphapalettetoggle)
	ON_COMMAND(ID_CXIMAGE_ALPHASTRIP, OnCximageAlphastrip)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ALPHASTRIP, OnUpdateCximageAlphastrip)
	ON_COMMAND(ID_CXIMAGE_ROTATEL, OnCximageRotatel)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ROTATEL, OnUpdateCximageRotatel)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ROTATER, OnUpdateCximageRotater)
	ON_COMMAND(ID_CXIMAGE_ROTATER, OnCximageRotater)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GAMMA, OnUpdateCximageGamma)
	ON_COMMAND(ID_CXIMAGE_GAMMA, OnCximageGamma)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_MEDIAN, OnUpdateCximageMedian)
	ON_COMMAND(ID_CXIMAGE_MEDIAN, OnCximageMedian)
	ON_COMMAND(ID_CXIMAGE_ADDNOISE, OnCximageAddnoise)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ADDNOISE, OnUpdateCximageAddnoise)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_MOVE, OnUpdateViewToolsMove)
	ON_COMMAND(ID_VIEW_TOOLS_MOVE, OnViewToolsMove)
	ON_COMMAND(ID_VIEW_TOOLS_SELECT, OnViewToolsSelect)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_SELECT, OnUpdateViewToolsSelect)
	ON_COMMAND(ID_VIEW_TOOLS_ZOOM, OnViewToolsZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_ZOOM, OnUpdateViewToolsZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALETTE, OnUpdateViewPalette)
	ON_COMMAND(ID_VIEW_PALETTE, OnViewPalette)
	ON_COMMAND(ID_CXIMAGE_COMBINE, OnCximageCombine)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_COMBINE, OnUpdateCximageCombine)
	ON_COMMAND(ID_CXIMAGE_FFT, OnCximageFft)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_FFT, OnUpdateCximageFft)
	ON_COMMAND(ID_CXIMAGE_SPLITYIQ, OnCximageSplityiq)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITYIQ, OnUpdateCximageSplityiq)
	ON_COMMAND(ID_CXIMAGE_SPLITXYZ, OnCximageSplitxyz)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITXYZ, OnUpdateCximageSplitxyz)
	ON_COMMAND(ID_CXIMAGE_REPAIR, OnCximageRepair)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REPAIR, OnUpdateCximageRepair)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ALPHACHANNEL_SPLIT, OnUpdateCximageAlphachannelSplit)
	ON_COMMAND(ID_CXIMAGE_ALPHACHANNEL_SPLIT, OnCximageAlphachannelSplit)
	ON_COMMAND(ID_VIEW_TOOLS_TEXT, OnViewToolsText)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_TEXT, OnUpdateViewToolsText)
	ON_COMMAND(ID_CXIMAGE_SPLITCMYK, OnCximageSplitcmyk)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITCMYK, OnUpdateCximageSplitcmyk)
	ON_COMMAND(ID_CXIMAGE_ALPHACREATE, OnCximageAlphaCreate)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_LOG, OnCximageFiltersLog)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_LOG, OnUpdateCximageFiltersLog)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_ROOT, OnCximageFiltersRoot)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_ROOT, OnUpdateCximageFiltersRoot)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_EQUALIZE, OnCximageHistogramEqualize)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_EQUALIZE, OnUpdateCximageHistogramEqualize)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_NORMALIZE, OnCximageHistogramNormalize)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_NORMALIZE, OnUpdateCximageHistogramNormalize)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCH, OnCximageHistogramStretch)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCH, OnUpdateCximageHistogramStretch)
	ON_COMMAND(ID_CXIMAGE_GAUSSIAN3X3, OnCximageGaussian3x3)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GAUSSIAN3X3, OnUpdateCximageGaussian3x3)
	ON_COMMAND(ID_CXIMAGE_GAUSSIAN5X5, OnCximageGaussian5x5)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GAUSSIAN5X5, OnUpdateCximageGaussian5x5)
	ON_COMMAND(ID_CXIMAGE_CONTOUR, OnCximageContour)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CONTOUR, OnUpdateCximageContour)
	ON_COMMAND(ID_CXIMAGE_LESSCONTRAST, OnCximageLesscontrast)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_LESSCONTRAST, OnUpdateCximageLesscontrast)
	ON_COMMAND(ID_CXIMAGE_JITTER, OnCximageJitter)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_JITTER, OnUpdateCximageJitter)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_DUPLICATE, OnUpdateWindowDuplicate)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_MIX, OnUpdateFiltersMix)
	ON_COMMAND(ID_FILTERS_MIX, OnFiltersMix)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER, OnCximageCircletransformCylinder)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER, OnUpdateCximageCircletransformCylinder)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_PINCH, OnCximageCircletransformPinch)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_PINCH, OnUpdateCximageCircletransformPinch)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_PUNCH, OnCximageCircletransformPunch)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_PUNCH, OnUpdateCximageCircletransformPunch)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_SWIRL, OnCximageCircletransformSwirl)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_SWIRL, OnUpdateCximageCircletransformSwirl)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM, OnCximageCircletransformBathroom)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM, OnUpdateCximageCircletransformBathroom)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCH1, OnCximageHistogramStretch1)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCH2, OnCximageHistogramStretch2)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCH1, OnUpdateCximageHistogramStretch1)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCH2, OnUpdateCximageHistogramStretch2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CDemoDoc construction/destruction
CDemoDoc::CDemoDoc()
{
	image = NULL;
	m_WaitingClick = stretchMode = FALSE;
	for (int i=0;i<MAX_UNDO_LEVELS;i++) imageUndo[i]=NULL;
	m_UndoLevel=0;
	m_ZoomFactor=1;
	QueryPerformanceFrequency(&m_swFreq);
	m_etime = 0.0;
	hThread=hProgress=0;
	m_NumSel=0;
	m_tool=0;
	m_hmax=0;
#ifndef VATI_EXTENSIONS
	memset(&m_font,0,sizeof(m_font));
	m_color=0;
	m_text="text";
#endif
}
//////////////////////////////////////////////////////////////////////////////
CDemoDoc::~CDemoDoc()
{
	// stop the elaborations
	if (image) image->SetEscape(1);
	// stop the progress bar
	if (hProgress){
		ResumeThread(hProgress); //wake up!
		WaitForSingleObject(hProgress,INFINITE);
		CloseHandle(hProgress);
	}
	if (hThread){
		WaitForSingleObject(hThread,INFINITE);
		CloseHandle(hThread);
	}
	// free objects
	delete image;
	for (int i=0;i<MAX_UNDO_LEVELS;i++) delete imageUndo[i];
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	image = NULL;

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////
// CDemoDoc serialization
void CDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())	{ } 
	else { }
}
//////////////////////////////////////////////////////////////////////////////
// CDemoDoc diagnostics
#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
//////////////////////////////////////////////////////////////////////////////
// CDemoDoc commands
CString CDemoDoc::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString("");
}
//////////////////////////////////////////////////////////////////////////////
int CDemoDoc::FindType(const CString& ext)
{
	int type = 0;
	if (ext == "bmp")					type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (ext=="jpg"||ext=="jpeg")	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (ext == "gif")				type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (ext == "png")				type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (ext=="mng"||ext=="jng")	type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (ext == "ico")				type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (ext=="tiff"||ext=="tif")	type = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (ext=="tga")				type = CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (ext=="pcx")				type = CXIMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (ext=="wbmp")				type = CXIMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (ext=="wmf"||ext=="emf")	type = CXIMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_J2K
	else if (ext=="j2k"||ext=="jp2")	type = CXIMAGE_FORMAT_J2K;
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (ext=="jbg")				type = CXIMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (ext=="jp2"||ext=="j2k")	type = CXIMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (ext=="jpc"||ext=="j2c")	type = CXIMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (ext=="pgx")				type = CXIMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (ext=="ras")				type = CXIMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (ext=="pnm"||ext=="pgm"||ext=="ppm") type = CXIMAGE_FORMAT_PNM;
#endif
	else type = CXIMAGE_FORMAT_UNKNOWN;

	return type;
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	ext.MakeLower();
	if (ext == "") return FALSE;

	int type = FindType(ext);

	/*CxImage canvas;
	canvas.SetEscape(-1);
	CxIOFile file;
	file.Open(filename,"rb");
	canvas.Decode(&file, type);*/

	Stopwatch(0);
	image = new CxImage(filename, type);
	Stopwatch(1);

	if (!image->IsValid()){
		AfxMessageBox(image->GetLastError());
		delete image;
		image = NULL;
		return FALSE;
	}

	UpdateStatusBar();
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);

	//multiple images (TIFF/ICO)
	if (image->GetNumFrames()>1){
		CString s;
		s.Format("File with %d images. Read all?",image->GetNumFrames());
		if (AfxMessageBox(s,MB_OKCANCEL)==IDOK){
			
			int j; // points to the document name
			for(j=strlen(filename)-1;j>=0;j--){
				if (filename[j]=='\\'){	j++; break;	}
			}
			// create the documents for the other images
			for(int i=1;i<image->GetNumFrames();i++){
				CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL);
				if (NewDoc)	{
					CxImage *newImage = new CxImage();
					newImage->SetFrame(i);
					newImage->Load(filename,type);
					NewDoc->image = newImage;
					CString s;
					s.Format("%s (%d)",filename.Mid(j),i+1);
					NewDoc->SetTitle(s);
					NewDoc->UpdateAllViews(NULL,WM_USER_NEWIMAGE);
				}
			}
		}
	}

	// EXIF jpegs
	if (image->GetType() == CXIMAGE_FORMAT_JPG){
		FILE* hfile = fopen(filename,"rb");
		m_exif.DecodeExif(hfile);
		fclose(hfile);
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	ext.MakeLower();
	if (ext == "") return FALSE;

	int type = FindType(ext);
	if (type == CXIMAGE_FORMAT_UNKNOWN) return FALSE;

	bool retval;
	Stopwatch(0);
	retval = image->Save(filename, type);
	Stopwatch(1);
	UpdateStatusBar();
	if (retval) return TRUE;
	AfxMessageBox(image->GetLastError());

	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::DoSave(LPCTSTR pszPathName, BOOL bReplace /*=TRUE*/)
{
	if (!image)	return FALSE;

	CString newName = pszPathName;
	BOOL bModified = IsModified();

	BOOL bSaveAs = FALSE;
	if (newName.IsEmpty()) bSaveAs = TRUE;
	else if (!theApp.GetWritableType(image->GetType()))	bSaveAs = TRUE;

	if (bSaveAs){
		newName = m_strPathName;
		if (bReplace && newName.IsEmpty()){
			newName = m_strTitle;
			int iBad = newName.FindOneOf(_T("#%;/\\"));    // dubious filename
			if (iBad != -1)	//newName.ReleaseBuffer(iBad);
				newName = "UntitledImage";

			// append the default suffix if there is one
			if (image->GetType()) newName += theApp.GetExtFromType(image->GetType()).Mid(1,4);
		}

		int nDocType = image->GetType();
		if (!theApp.PromptForFileName(newName, 
			bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, &nDocType))
		{
			return FALSE;       // don't even try to save
		}
	}

	BeginWaitCursor();
	if (!OnSaveDocument(newName)){
		if (pszPathName == NULL){
			// be sure to delete the file
			TRY 
			{
				CFile::Remove(newName);
			}
			CATCH_ALL(e)
			{
				TRACE0("Warning: failed to delete file after failed SaveAs\n");
			}
			END_CATCH_ALL
		}
		EndWaitCursor();
		return FALSE;
	}

	EndWaitCursor();
	if (bReplace) {
		// Reset the title and change the document name
		SetPathName(newName, TRUE);
		ASSERT(m_strPathName == newName); // must be set
	}
	else // SaveCopyAs
	{
		SetModifiedFlag(bModified);
	}
	return TRUE;        // success
}
//////////////////////////////////////////////////////////////////////////////
#define EPSILON (0.0000001)

int CDemoDoc::ComputePixel(float x, float y, float &x1, float &y1)
{
  double r, nn;

  if (x==0 && y==0) {
	 x1 = x;
	 y1 = y;
	 return 1;
  }

  nn = sqrt(x*x + y*y);
  r =  (fabs(x) > fabs(y)) ? fabs(nn/x): fabs(nn/y);

  x1 = (float)(r*x);
  y1 = (float)(r*y);

  return 1;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(image==0 || hThread));
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(0);
//	pCmdUI->Enable((image != NULL)); //&& theApp.GetWritableType(image->GetType()));
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnStretchMode() 
{
	stretchMode = !stretchMode;
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateStretchMode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(stretchMode);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateCximageFlip(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGrayscale(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageMirror(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageNegative(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageResample(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRotate(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRotater(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRotatel(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDither(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageThreshold(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplityuv(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplitrgb(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplithsl(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplityiq(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplitxyz(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplitcmyk(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximagePseudocolors(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFiltersColorize(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageLighten(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDarken(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageContrast(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageEmboss(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageBlur(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDilate(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageEdge(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageErode(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSharpen(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSoften(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCrop(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->SelectionIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRemovealphachannel(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageInvetalpha(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAlphapalettetoggle(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaPaletteIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAlphastrip(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || (!image->AlphaIsValid() && !image->AlphaPaletteIsValid())) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRemovetransparency(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || image->GetTransIndex()<0) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGamma(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageMedian(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAddnoise(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCombine(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFft(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRepair(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAlphachannelSplit(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFiltersLog(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFiltersRoot(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramEqualize(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramNormalize(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretch(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGaussian3x3(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGaussian5x5(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageContour(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageLesscontrast(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageJitter(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateWindowDuplicate(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateFiltersMix(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformCylinder(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformPinch(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformPunch(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformSwirl(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformBathroom(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretch1(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretch2(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}

//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateTransformEllipse(CCmdUI* pCmdUI) 
{
	if (image==NULL) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnTransformEllipse() 
{
	SubmitUndo();
	DWORD x, y, x1, y1;
	float fx, fy, xmid, ymid, ar;
	CxImage *image2 = new CxImage(*image,false,false,true);

	xmid = (float) (image->GetWidth()/2.0);
	ymid = (float) (image->GetHeight()/2.0);
	ar = (float)(image->GetHeight())/(float)(image->GetWidth());
	for (y=0; y<image->GetHeight(); y++) {
		for (x=0; x<image->GetWidth(); x++) {
			ComputePixel(ar*(x-xmid), y-ymid, fx, fy);
			x1 = (int)(xmid+fx/ar);
			y1 = (int)(ymid+fy);
			image2->SetPixelColor(x, y, image->GetPixelColor(x1, y1));
		}
	}
	delete image;
	image = image2;
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnWindowDuplicate() 
{
	CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 

	if (NewDoc)	{
		CxImage *newImage = new CxImage(*image);

		NewDoc->image = newImage;

		CString s;
		s.Format("Copy %d of %s",((CDemoApp*)AfxGetApp())->m_nDocCount++,GetTitle());
		NewDoc->SetTitle(s);
		NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	if (image==NULL) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnEditCopy() 
{
	HANDLE hDIB=image->CopyToHandle();

	if (::OpenClipboard(AfxGetApp()->m_pMainWnd->GetSafeHwnd())) {
		if(::EmptyClipboard()) {
			if (::SetClipboardData(CF_DIB,hDIB) == NULL ) {
				AfxMessageBox( "Unable to set Clipboard data" );
			}
		}
	}
	CloseClipboard();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread) pCmdUI->Enable(0);
	else pCmdUI->Enable(m_UndoLevel>0);

	CString s;
	s.Format("Undo (%d)\tCtrl+Z",m_UndoLevel);
	pCmdUI->SetText(s);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread) pCmdUI->Enable(0);
	else pCmdUI->Enable((m_UndoLevel<(MAX_UNDO_LEVELS))&&
				   (imageUndo[m_UndoLevel]!=0));
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnEditUndo() 
{
	m_UndoLevel--;
	CxImage* tmp = image;
	image=imageUndo[m_UndoLevel];
	imageUndo[m_UndoLevel]=tmp;

	UpdateAllViews(0,WM_USER_NEWIMAGE);
	UpdateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnEditRedo() 
{
	CxImage* tmp = image;
	image=imageUndo[m_UndoLevel];
	imageUndo[m_UndoLevel]=tmp;
	m_UndoLevel++;

	UpdateAllViews(0,WM_USER_NEWIMAGE);
	UpdateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::SubmitUndo()
{
	if (m_UndoLevel>=MAX_UNDO_LEVELS){	// Max Undo reached
		delete imageUndo[0];			// discard the early undo
		for(int i=1;i<MAX_UNDO_LEVELS;i++){
			imageUndo[i-1]=imageUndo[i]; //shift the history
		}
		imageUndo[MAX_UNDO_LEVELS-1]=0;	// clear the undo slot
		m_UndoLevel=MAX_UNDO_LEVELS-1;  // reposition at last level
	}
	// we must clear the "redo" history when a new action is performed
	for (int i=m_UndoLevel;i<MAX_UNDO_LEVELS;i++){
		if (imageUndo[i]){
			delete imageUndo[i];
			imageUndo[i]=0;
		}
	}
	// save the actual image in the undo history
	if (image->IsValid()){
		imageUndo[m_UndoLevel] = new CxImage();
		imageUndo[m_UndoLevel]->Copy(*image);
		m_UndoLevel++;
	}
}
//////////////////////////////////////////////////////////////////////////////
void /*unsigned long _stdcall*/ RunProgressThread(void *lpParam)
{
	CDemoDoc *pDoc = (CDemoDoc *)lpParam;
	long n;
	POSITION pos;
	CView *pView;
	while((n=pDoc->image->GetProgress())<100){
		Sleep(333);
		if(pDoc->image->GetEscape()) break;
		pos = pDoc->GetFirstViewPosition();
		pView = pDoc->GetNextView(pos);
		if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,n,0);
	}
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,100,0);
	Sleep(111);
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_NEWIMAGE,0,0);
	pDoc->hProgress = 0;
	_endthread();
	return;
}
//////////////////////////////////////////////////////////////////////////////
void /*unsigned long _stdcall*/ RunCxImageThread(void *lpParam)
{
	CDemoDoc *pDoc = (CDemoDoc *)lpParam;
	if (pDoc==NULL) return;
	if (pDoc->image==NULL) return;

	 //prepare for elaboration
	pDoc->image->SetProgress(0);
	pDoc->image->SetEscape(0);

	pDoc->SubmitUndo();
	
	// auxilary thread for progress bar
	pDoc->hProgress = (HANDLE)_beginthread(RunProgressThread,0,pDoc);

	pDoc->Stopwatch(0);

	switch (pDoc->m_MenuCommand)
	{
//	case ID_FILE_OPEN:
//		pDoc->image->ReadFile(*(CString*)pDoc->m_fp[0],(int)pDoc->m_fp[1]);
//		break;
	case ID_CXIMAGE_FLIP:
		pDoc->image->Flip();
		break;
	case ID_CXIMAGE_MIRROR:
		pDoc->image->Mirror();
		break;
	case ID_CXIMAGE_NEGATIVE:
		pDoc->image->Negative();
		break;
	case ID_CXIMAGE_GRAYSCALE:
		pDoc->image->GrayScale();
		break;
	case ID_CXIMAGE_DITHER:
		pDoc->image->Dither((long)pDoc->m_fp[0]);
		break;
	case ID_CXIMAGE_THRESHOLD:
		pDoc->image->Threshold((BYTE)pDoc->m_fp[0]);
		break;
	case ID_CXIMAGE_COLORIZE:
		if ((BYTE)pDoc->m_fp[0]){
			pDoc->image->Colorize((BYTE)pDoc->m_fp[1],(BYTE)pDoc->m_fp[2]);
		} else {
			pDoc->image->ShiftRGB((BYTE)pDoc->m_fp[1],(BYTE)pDoc->m_fp[2],(BYTE)pDoc->m_fp[3]);
		}
		break;
	case ID_CXIMAGE_LIGHTEN:
		pDoc->image->Light(20);
		break;
	case ID_CXIMAGE_DARKEN:
		pDoc->image->Light(-20);
		break;
	case ID_CXIMAGE_CONTRAST:
		pDoc->image->Light((long)pDoc->m_fp[0],25);
		break;
	case ID_CXIMAGE_LESSCONTRAST:
		pDoc->image->Light((long)pDoc->m_fp[0],-25);
		break;
	case ID_CXIMAGE_DILATE:
		pDoc->image->Dilate();
		break;
	case ID_CXIMAGE_ERODE:
		pDoc->image->Erode();
		break;
	case ID_CXIMAGE_CONTOUR:
		pDoc->image->Contour();
		break;
	case ID_CXIMAGE_ADDNOISE:
		pDoc->image->Noise(50);
		break;
	case ID_CXIMAGE_JITTER:
		pDoc->image->Jitter();
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER:
		pDoc->image->CircleTransform(3,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_PINCH:
		pDoc->image->CircleTransform(1,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_PUNCH:
		pDoc->image->CircleTransform(0,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_SWIRL:
		pDoc->image->CircleTransform(2,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM:
		pDoc->image->CircleTransform(4);
		break;
	case ID_CXIMAGE_EMBOSS:
		{
			long kernel[]={0,0,-1,0,0,0,1,0,0};
		pDoc->image->Filter(kernel,3,0,127);
		break;
		}
	case ID_CXIMAGE_BLUR:
		{
			long kernel[]={1,1,1,1,1,1,1,1,1};
		pDoc->image->Filter(kernel,3,9,0);
		break;
		}
	case ID_CXIMAGE_GAUSSIAN3X3:
		{
			long kernel[]={1,2,1,2,4,2,1,2,1};
		pDoc->image->Filter(kernel,3,16,0);
		break;
		}
	case ID_CXIMAGE_GAUSSIAN5X5:
		{
			long kernel[]={0,1,2,1,0,1,3,4,3,1,2,4,8,4,2,1,3,4,3,1,0,1,2,1,0};
		pDoc->image->Filter(kernel,5,52,0);
		break;
		}
	case ID_CXIMAGE_SOFTEN:
		{
			long kernel[]={1,1,1,1,8,1,1,1,1};
		pDoc->image->Filter(kernel,3,16,0);
		break;
		}
	case ID_CXIMAGE_SHARPEN:
		{
			long kernel[]={-1,-1,-1,-1,15,-1,-1,-1,-1};
		pDoc->image->Filter(kernel,3,7,0);
		break;
		}
	case ID_CXIMAGE_EDGE:
		{
			long kernel[]={-1,-1,-1,-1,8,-1,-1,-1,-1};
		pDoc->image->Filter(kernel,3,-1,255);
		break;
		}
	case ID_CXIMAGE_MEDIAN:
		pDoc->image->Median(3);
		break;
	case ID_CXIMAGE_GAMMA:
		pDoc->image->Gamma((float)(long)pDoc->m_fp[0]/1000);
		break;
	case ID_CXIMAGE_HISTOGRAM_LOG:
		pDoc->image->HistogramLog();
		break;
	case ID_CXIMAGE_HISTOGRAM_ROOT:
		pDoc->image->HistogramRoot();
		break; 
	case ID_CXIMAGE_HISTOGRAM_EQUALIZE:
		pDoc->image->HistogramEqualize();
		break;
	case ID_CXIMAGE_HISTOGRAM_NORMALIZE:
		pDoc->image->HistogramNormalize();
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCH:
		pDoc->image->HistogramStretch();
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCH1:
		pDoc->image->HistogramStretch(1);
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCH2:
		pDoc->image->HistogramStretch(2);
		break;
	case ID_CXIMAGE_ROTATE:
		pDoc->image->Rotate((float)(long)pDoc->m_fp[0]/1000);
		break;
	case ID_CXIMAGE_ROTATEL:
		pDoc->image->RotateLeft();
		break;
	case ID_CXIMAGE_ROTATER:
		pDoc->image->RotateRight();
		break;
	case ID_CXIMAGE_RESAMPLE:
		pDoc->image->Resample((long)pDoc->m_fp[0],(long)pDoc->m_fp[1],(long)pDoc->m_fp[2]);
		break;
	case ID_CXIMAGE_INCREASEBPP:
		pDoc->image->IncreaseBpp((long)pDoc->m_fp[0]);
		break;
	case ID_CXIMAGE_DECREASEBPP:
		{
			long bit=(long)pDoc->m_fp[0];
			long method=(long)pDoc->m_fp[1];
			bool errordiffusion=((long)pDoc->m_fp[2])!=0;
			long colors=(long)pDoc->m_fp[3];

			//pDoc->image->IncreaseBpp(24);

			RGBQUAD* ppal = NULL;
			if (method==1){
				switch (bit){
				/*case 1:
					{
						CQuantizer q(2,8);
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(2*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
						break;
					}*/
				case 4:
					{
						CQuantizer q(colors,8);
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(16*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
						break;
					}
				case 8:
					{
						CQuantizer q(colors,(colors>16?7:8));
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(256*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
					}
				}
				pDoc->image->DecreaseBpp(bit,errordiffusion,ppal,colors);
			} else pDoc->image->DecreaseBpp(bit,errordiffusion,0);

			if (!pDoc->image->AlphaPaletteIsValid()) pDoc->image->AlphaPaletteEnable(0);

			if (ppal) free(ppal);
			break;
		}
	}

	pDoc->Stopwatch(1);

	pDoc->image->SetProgress(100);

	pDoc->hThread=0;
	_endthread();
	return ;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFlip() 
{
	m_MenuCommand=ID_CXIMAGE_FLIP;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageMirror() 
{
	m_MenuCommand=ID_CXIMAGE_MIRROR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageNegative() 
{
	m_MenuCommand=ID_CXIMAGE_NEGATIVE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGrayscale() 
{
	m_MenuCommand=ID_CXIMAGE_GRAYSCALE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDecreasebpp() 
{
	if (image==NULL) return;
	DlgDecBpp dlg;
	dlg.m_bit=4;
	dlg.m_maxcolors = 256;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_DECREASEBPP;
		m_fp[0]=(void *)dlg.m_bit;
		m_fp[1]=(void *)dlg.m_method;
		m_fp[2]=(void *)dlg.m_errordiffusion;
		m_fp[3]=(void *)dlg.m_maxcolors;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageIncreasebpp() 
{
	if (image==NULL) return;
	DlgIncBpp dlg;
	dlg.m_bit=24;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_INCREASEBPP;
		m_fp[0]=(void *)dlg.m_bit;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRotatel() 
{
	m_MenuCommand=ID_CXIMAGE_ROTATEL;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRotater() 
{
	m_MenuCommand=ID_CXIMAGE_ROTATER;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRotate() 
{
	if (image==NULL) return;
	DlgRotate dlg;
	dlg.m_angle=(float)12.345;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_ROTATE;
		m_fp[0]=(void *)(long)(dlg.m_angle*1000);
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageResample() 
{
	if (image==NULL) return;
	
	DlgResample dlg;
	dlg.m_factor=(float)2;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_RESAMPLE;
		m_fp[0]=(void *)(long)(image->GetWidth() * dlg.m_factor);
		m_fp[1]=(void *)(long)(image->GetHeight() * dlg.m_factor);
		m_fp[2]=(void *)(long)dlg.m_mode;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::UpdateStatusBar()
{
	if (image){
		CStatusBar& statusBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetStatusBar();
		CString s,t;
		t = theApp.GetDescFromType(image->GetType());
		s.Format("(%dx%dx%d)",image->GetWidth(),image->GetHeight(),image->GetBpp());
		statusBar.SetPaneText(4, s);
		statusBar.SetPaneText(3,t.Mid(0,3));
		s.Format("Time (s): %.3f",m_etime);
		statusBar.SetPaneText(2, s);

//		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetProgressBar().SetPos(0);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewZoomin() 
{
	if (m_ZoomFactor>=16) return;
	m_ZoomFactor*=2;
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewZoomout() 
{
	if (m_ZoomFactor<=0.0625) return;
	m_ZoomFactor/=2;
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewZoomin(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor>=16) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewZoomout(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor<=0.125) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewNormalviewing11() 
{
	m_ZoomFactor=1;
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewNormalviewing11(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor==1) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateCximageSettransparency(CCmdUI* pCmdUI) 
{
	if (image && hThread==0) pCmdUI->Enable(1);
	else pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRemovetransparency() 
{
	SubmitUndo();
	if (image) image->SetTransIndex(-1);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSettransparency() 
{
	m_WaitingClick=TRUE;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::Stopwatch(int start0stop1)
{
	if (start0stop1==0)	QueryPerformanceCounter(&m_swStart);
	else {
		QueryPerformanceCounter(&m_swStop);
		if (m_swFreq.LowPart==0 && m_swFreq.HighPart==0) m_etime = -1;
		else {
			m_etime = (float)(m_swStop.LowPart - m_swStart.LowPart);
			if (m_etime < 0) m_etime += 2^32;
			m_etime /= (m_swFreq.LowPart+m_swFreq.HighPart * 2^32);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageOptions() 
{
	if (image==NULL) return;
	
	DlgOptions dlg;
	dlg.m_quality = image->GetJpegQuality();
	dlg.m_xres = image->GetXDPI();
	dlg.m_yres = image->GetYDPI();
	dlg.m_EncodeOption = image->GetCodecOption();
	dlg.m_exif = &m_exif;
	if (dlg.DoModal()==IDOK){
		image->SetJpegQuality(dlg.m_quality);
		image->SetXDPI(dlg.m_xres);
		image->SetYDPI(dlg.m_yres);
		image->SetCodecOption(dlg.m_EncodeOption);
#ifdef VATI_EXTENSIONS
		theApp.m_optJpegQuality = dlg.m_quality;
#endif
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDither() 
{
	if (image==NULL) return;
	
	DlgDither dlg;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_DITHER;
		m_fp[0]=(void*)dlg.m_method;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageThreshold() 
{
	if (image==NULL) return;
	DlgThreshold dlg;
	dlg.m_level=(BYTE)image->Mean();
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_THRESHOLD;
		m_fp[0]=(void *)(BYTE)(dlg.m_level);
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplitrgb() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);
	
	image->SplitRGB(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format("Red Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format("Green Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format("Blue Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplityuv() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);

	image->SplitYUV(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format("Y Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format("U Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format("V Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplithsl() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);

	image->SplitHSL(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();
	
	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format("Hue Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format("Saturation Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format("Lightness Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplitcmyk() 
{
	if (image==NULL) return;

	CxImage *newc = new CxImage();
	CxImage *newm = new CxImage();
	CxImage *newy = new CxImage();
	CxImage *newk = new CxImage();

	Stopwatch(0);
	
	image->SplitCMYK(newc,newm,newy,newk);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newc;
		CString s;
		s.Format("C Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newm;
		CString s;
		s.Format("M Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newy;
		CString s;
		s.Format("Y Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDock=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDock)	{
		NewDock->image = newk;
		CString s;
		s.Format("K Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDock->SetTitle(s);
		NewDock->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximagePseudocolors() 
{
	if (image==NULL) return;
	
	SubmitUndo();

	if (!image->IsGrayScale()) image->GrayScale();
	image->HuePalette();

/*	POSITION pos = GetFirstViewPosition();
	CDemoView* pView = (CDemoView*)GetNextView(pos);
	HDC srcDC = ::GetDC(pView->GetSafeHwnd());
	HDC memDC = ::CreateCompatibleDC(srcDC);
	// copy the screen to the bitmap
	CSize sz(image->GetWidth(), image->GetHeight());
	int xshift = 0, yshift = 0;
	HBITMAP bm =::CreateCompatibleBitmap(srcDC, sz.cx, sz.cy);
	HBITMAP oldbm = (HBITMAP)::SelectObject(memDC,bm);
	::BitBlt(memDC, 0, 0, sz.cx, sz.cy, srcDC, xshift, yshift, SRCCOPY);
//	image->SetTransIndex(-1);
//	image->Draw(memDC);
	::TextOut(memDC,10,10,"test",4);
	
	CxImage newima;
	newima.CreateFromHBITMAP(bm);
	image->Transfer(newima);
	// free objects
	SelectObject(memDC,oldbm);    
	DeleteObject(memDC);*/

	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFiltersColorize() 
{
	if (image==NULL) return;
	DlgColorize dlg;
	dlg.m_sat=50;
	dlg.m_hue=12;
	dlg.m_r=50;
	dlg.m_g=0;
	dlg.m_b=-50;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_COLORIZE;
		if (dlg.m_bHSL){
			m_fp[0]=(void *)(BYTE)(dlg.m_bHSL);
			m_fp[1]=(void *)(BYTE)(dlg.m_hue);
			m_fp[2]=(void *)(BYTE)(dlg.m_sat);
		} else {
			m_fp[0]=(void *)(BYTE)(dlg.m_bHSL);
			m_fp[1]=(void *)(BYTE)(dlg.m_r);
			m_fp[2]=(void *)(BYTE)(dlg.m_g);
			m_fp[3]=(void *)(BYTE)(dlg.m_b);
		}
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDarken() 
{
	m_MenuCommand=ID_CXIMAGE_DARKEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageLighten() 
{
	m_MenuCommand=ID_CXIMAGE_LIGHTEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageContrast() 
{
	m_MenuCommand=ID_CXIMAGE_CONTRAST;
//	m_fp[0]=(void *)(long)((128-image->Mean())/4);
	m_fp[0]=(void *)(long)(0);
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageEmboss() 
{
	m_MenuCommand=ID_CXIMAGE_EMBOSS;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageBlur() 
{
	m_MenuCommand=ID_CXIMAGE_BLUR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDilate() 
{
	m_MenuCommand=ID_CXIMAGE_DILATE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageEdge() 
{
	m_MenuCommand=ID_CXIMAGE_EDGE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageErode() 
{
	m_MenuCommand=ID_CXIMAGE_ERODE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSharpen() 
{
	m_MenuCommand=ID_CXIMAGE_SHARPEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSoften() 
{
	m_MenuCommand=ID_CXIMAGE_SOFTEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCrop() 
{
	SubmitUndo();
	RECT r;
	
#ifdef VATI_EXTENSIONS
	// if there is a valid rectangle selection, then call the CropRotatedRectangle instead original Crop
	if (m_isRectSel && m_NumSel==5 )
	{
		CPoint top;
		long height, width;
		float angle;
		int topcorner = -1;

		// get upperleft corner
		top.x = 999999;
		top.y = 999999;
		for(int i=0; i<4; i++)
		{
			if ( top.y >= m_Sel[i].y )
			{
				if ( top.y == m_Sel[i].y && top.x < m_Sel[i].x )
					continue;
				top.x = m_Sel[i].x;
				top.y = m_Sel[i].y;
				topcorner = i;
			}
		}
		// get side lengths (-1st and +1st indexes points to 2 sides)
		if ( topcorner > 0 && topcorner < 4 )
			height = (long)LEN2D( top.x - m_Sel[topcorner-1].x, top.y - m_Sel[topcorner-1].y );
		else if ( topcorner == 0 )
			height = (long)LEN2D( top.x - m_Sel[3].x, top.y - m_Sel[3].y );
		else
			return;	// fatal prog error

		width  = (long)LEN2D( top.x - m_Sel[topcorner+1].x, top.y - m_Sel[topcorner+1].y );
		angle = (float)atan2( (float)(m_Sel[topcorner+1].y - top.y), (float)(m_Sel[topcorner+1].x - top.x) );

		image->CropRotatedRectangle( top.x, top.y, width, height, angle );
	}
		
	else // freehand selection
	{
		image->SelectionGetBox(r);
		r.bottom = image->GetHeight() - 1 -r.bottom; 
		r.top = image->GetHeight() - 1 -r.top; 
		image->Crop(r);
	}
#else
	image->SelectionGetBox(r);
	r.bottom = image->GetHeight() - 1 -r.bottom; 
	r.top = image->GetHeight() - 1 -r.top; 
	image->Crop(r);
#endif	
	UpdateStatusBar(); // VAti - to refresh image size in the status bar
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}

//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRemovealphachannel() 
{
	SubmitUndo();
	image->AlphaDelete();
	image->AlphaSetMax(255);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageOpacity() 
{
	if (image==NULL) return;
	DlgOpacity dlg;
	dlg.m_level=image->AlphaGetMax();
	if (dlg.DoModal()==IDOK){
		SubmitUndo();
		if (!image->AlphaIsValid()){
			image->AlphaCreate();
		}
		image->AlphaSetMax(dlg.m_level);
	}
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageInvetalpha() 
{
	SubmitUndo();
	image->AlphaInvert();
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphapalettetoggle() 
{
	SubmitUndo();
	image->AlphaPaletteEnable(!image->AlphaPaletteIsEnabled());
	UpdateAllViews(NULL);	
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphastrip() 
{
	SubmitUndo();
	RGBQUAD c={255,255,255,0};
	image->SetTransColor(c);
	image->AlphaStrip();
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);	
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGamma() 
{
	if (image==NULL) return;
	DlgGamma dlg;
	dlg.m_gamma=(float)1.23;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_GAMMA;
		m_fp[0]=(void *)(long)(dlg.m_gamma*1000);
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageMedian() 
{
	m_MenuCommand=ID_CXIMAGE_MEDIAN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAddnoise() 
{
	m_MenuCommand=ID_CXIMAGE_ADDNOISE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsMove() 
{
	m_tool=0;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsMove(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsSelect() 
{
	m_tool=1;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==1);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsZoom() 
{
	m_tool=2;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsZoom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==2);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsText() 
{
	if (image==NULL) return;
	DlgText dlg;

#ifndef VATI_EXTENSIONS
	memcpy(&(dlg.m_font),&m_font,sizeof(m_font));
	dlg.m_text=m_text;
	dlg.m_color=m_color;
	if (dlg.DoModal()==IDOK){
		m_text=dlg.m_text;
		m_color=dlg.m_color;
		memcpy(&m_font,&(dlg.m_font),sizeof(m_font));
		m_tool=3;
	}
#else
    //pass all data about text
    memcpy( &(dlg.m_textdata), &theApp.m_text, sizeof(CXTEXTINFO) );
    if (dlg.DoModal()==IDOK)
    {
        //retrieve all data about text
		memcpy( &theApp.m_text, &(dlg.m_textdata), sizeof(CXTEXTINFO) );
		m_tool=3;
	}
#endif
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsText(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==3);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewPalette(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread || image->GetNumColors()==0) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewPalette() 
{
	if (image==NULL) return;
	DlgPalette dlg;
	dlg.m_numcolors=image->GetNumColors();
	memcpy(dlg.m_pal,image->GetPalette(),dlg.m_numcolors*sizeof(RGBQUAD));
	if (dlg.DoModal()==IDOK){
		if (dlg.m_changed){
			SubmitUndo();
			switch (dlg.m_replace){
			case 1:
				{
					image->SetPalette(dlg.m_pal,dlg.m_numcolors);
					break;
				}
			case 2:
				{
					int bpp=image->GetBpp();
					image->IncreaseBpp(24);
					image->DecreaseBpp(bpp,false,dlg.m_pal);
					break;
				}
			case 3:
				{
					int bpp=image->GetBpp();
					image->IncreaseBpp(24);
					image->DecreaseBpp(bpp,true,dlg.m_pal);
					break;
				}
			}

			UpdateAllViews(NULL,WM_USER_NEWIMAGE);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCombine() 
{
	if (image==NULL) return;
	DlgCombine dlg;
	if (dlg.DoModal()==IDOK){
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);
		CxImage *newr,*newg,*newb,*newa;
		newr=newg=newb=newa=NULL;

		newr = new CxImage();
		switch(dlg.pChR){
		case 0:
			newr->Copy(*(dlg.pDocR->GetImage()),1,0,0);
			newr->GrayScale();
			break;
		case 1:
			dlg.pDocR->GetImage()->SplitRGB(newr,0,0);
			break;
		case 2:
			dlg.pDocR->GetImage()->SplitRGB(0,newr,0);
			break;
		case 3:
			dlg.pDocR->GetImage()->SplitRGB(0,0,newr);
			break;
		}

		newg = new CxImage();
		switch(dlg.pChG){
		case 0:
			newg->Copy(*(dlg.pDocG->GetImage()),1,0,0);
			newg->GrayScale();
			break;
		case 1:
			dlg.pDocG->GetImage()->SplitRGB(newg,0,0);
			break;
		case 2:
			dlg.pDocG->GetImage()->SplitRGB(0,newg,0);
			break;
		case 3:
			dlg.pDocG->GetImage()->SplitRGB(0,0,newg);
			break;
		}

		newb = new CxImage();
		switch(dlg.pChB){
		case 0:
			newb->Copy(*(dlg.pDocB->GetImage()),1,0,0);
			newb->GrayScale();
			break;
		case 1:
			dlg.pDocB->GetImage()->SplitRGB(newb,0,0);
			break;
		case 2:
			dlg.pDocB->GetImage()->SplitRGB(0,newb,0);
			break;
		case 3:
			dlg.pDocB->GetImage()->SplitRGB(0,0,newb);
			break;
		}

		if (dlg.pDocA){
			newa = new CxImage();
			switch(dlg.pChA){
			case 0:
				newa->Copy(*(dlg.pDocA->GetImage()),1,0,0);
				newa->GrayScale();
				break;
			case 1:
				dlg.pDocA->GetImage()->SplitRGB(newa,0,0);
				break;
			case 2:
				dlg.pDocA->GetImage()->SplitRGB(0,newa,0);
				break;
			case 3:
				dlg.pDocA->GetImage()->SplitRGB(0,0,newa);
				break;
			}
		}

		CxImage *mix = new CxImage();
		mix->Combine(newr,newg,newb,newa,dlg.pChS);
		
		CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDocr)	{
			NewDocr->image = mix;
			CString s;
			s.Format("NewImage%d",((CDemoApp*)AfxGetApp())->m_nDocCount++);
			NewDocr->SetTitle(s);
			NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}

		delete newr;
		delete newg;
		delete newb;
		delete newa;
		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFft() 
{
	if (image==NULL) return;
	DlgFFT dlg;
	if (dlg.DoModal()==IDOK){
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		CxImage *srcr,*srci,*dstr,*dsti,tmp;

		srcr = (dlg.pDocReal) ? dlg.pDocReal->GetImage() : 0;
		srci = (dlg.pDocImag) ? dlg.pDocImag->GetImage() : 0;

		if (srcr==0 && srci==0) return;

		if (srcr) dstr = new CxImage(*srcr,true,false,false); else dstr=0;
		if (srci) dsti = new CxImage(*srci,true,false,false); else dsti=0;

		if (dstr==0){
			dstr = new CxImage(dsti->GetWidth(),dsti->GetHeight(),8);
			dstr->Clear(0);
			dstr->SetGrayPalette();
		}
		if (dsti==0){
			dsti = new CxImage(dstr->GetWidth(),dstr->GetHeight(),8);
			dsti->Clear(0);
			dsti->SetGrayPalette();
		}

		tmp.FFT2(dstr,dsti,0,0,dlg.bInverse,dlg.bForceFFT!=0,dlg.bMagnitude!=0);

		((CDemoApp*)AfxGetApp())->m_nDocCount++;
		CDemoDoc *NewDoci=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDoci)	{
			NewDoci->image = dsti;
			CString s;
			if (dlg.bMagnitude){
				s.Format("FFT Phase %d",((CDemoApp*)AfxGetApp())->m_nDocCount);
			} else {
				s.Format("FFT Imag %d",((CDemoApp*)AfxGetApp())->m_nDocCount);
			}
			NewDoci->SetTitle(s);
			NewDoci->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}
		CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDocr)	{
			NewDocr->image = dstr;
			CString s;
			if (dlg.bMagnitude){
				s.Format("FFT Magnitude %d",((CDemoApp*)AfxGetApp())->m_nDocCount);
			} else {
				s.Format("FFT Real %d",((CDemoApp*)AfxGetApp())->m_nDocCount);
			}
			NewDocr->SetTitle(s);
			NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}

		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplityiq() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);

	image->SplitYIQ(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format("Y Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format("I Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format("Q Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplitxyz() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);
	
	image->SplitXYZ(newr,newg,newb);
	
	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format("X Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format("Y Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format("Z Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRepair() 
{
	if (image==NULL) return;
	
	DlgRepair dlg;
	dlg.m_iterations = 2;
	dlg.m_radius = (float)0.25;
	if (dlg.DoModal()==IDOK){
		SubmitUndo();
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		image->Repair(dlg.m_radius,dlg.m_iterations,dlg.m_ncs);

		Stopwatch(1);
		UpdateAllViews(NULL);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphachannelSplit() 
{
	if (image==NULL) return;

	CxImage *newa = new CxImage();

	Stopwatch(0);
	
	image->AlphaSplit(newa);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newa;
		CString s;
		s.Format("Alpha Channel %d from %s",((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphaCreate() 
{
	if (image==NULL) return;
	CxImage gray(*image,true,false,false);
	gray.IncreaseBpp(8);
	gray.Negative();
	gray.GrayScale();
	image->AlphaSet(gray);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFiltersLog() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_LOG;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFiltersRoot() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_ROOT;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramEqualize() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_EQUALIZE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramNormalize() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_NORMALIZE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretch() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCH;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGaussian3x3() 
{
	m_MenuCommand=ID_CXIMAGE_GAUSSIAN3X3;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGaussian5x5() 
{
	m_MenuCommand=ID_CXIMAGE_GAUSSIAN5X5;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageContour() 
{
	m_MenuCommand=ID_CXIMAGE_CONTOUR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageLesscontrast() 
{
	m_MenuCommand=ID_CXIMAGE_LESSCONTRAST;
	m_fp[0]=(void *)(long)(0);
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageJitter() 
{
	m_MenuCommand=ID_CXIMAGE_JITTER;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnFiltersMix() 
{
	if (image==NULL) return;
	DlgMix dlg;
	if (dlg.DoModal()==IDOK){
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		CxImage *src, *dst, *tmp;

		src = (dlg.pDocSrc) ? dlg.pDocSrc->GetImage() : 0;
		dst = (dlg.pDocDst) ? dlg.pDocDst->GetImage() : 0;

		if (src==0 && dst==0) return;

		tmp = new CxImage(*dst);
		tmp->Mix(*src,(CxImage::ImageOpType)dlg.OpType,dlg.m_xoffset,dlg.m_yoffset);

		((CDemoApp*)AfxGetApp())->m_nDocCount++;
		CDemoDoc *NewDoci=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDoci)	{
			NewDoci->image = tmp;
			CString s;
			s.Format("Mix %d",((CDemoApp*)AfxGetApp())->m_nDocCount);
			NewDoci->SetTitle(s);
			NewDoci->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}

		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformCylinder() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformPinch() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_PINCH;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformPunch() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_PUNCH;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformSwirl() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_SWIRL;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformBathroom() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretch1() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCH1;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretch2() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCH2;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
