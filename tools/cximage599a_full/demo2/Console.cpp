// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ximage.h"

CString FindExtension(const CString& name)
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

int FindFormat(const CString& ext)
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

int main(int argc, char* argv[])
{
	CxImage image;

    if (argc<3) {
        fprintf(stderr, image.GetVersion());
        fprintf(stderr, "\nConsole demo\n");
        fprintf(stderr, "usage: %s input-file output-file\n", argv[0]);
        return 1;
    }

	CString filein(argv[1]);
	CString extin(FindExtension(filein));
	extin.MakeLower();
	int typein = FindFormat(extin);
	if (typein == CXIMAGE_FORMAT_UNKNOWN) {
        fprintf(stderr, "unknown extension for %s\n", argv[1]);
        return 1;
	}

	CString fileout(argv[2]);
	CString extout(FindExtension(fileout));
	extout.MakeLower();
	int typeout = FindFormat(extout);
	if (typeout == CXIMAGE_FORMAT_UNKNOWN) {
        fprintf(stderr, "unknown extension for %s\n", argv[2]);
        return 1;
	}


	if (!image.Load(argv[1],typein)){
        fprintf(stderr, "%s\n", image.GetLastError());
        fprintf(stderr, "error loading %s\n", argv[1]);
        return 1;
	}

	if (!image.Save(argv[2],typeout)){
        fprintf(stderr, "%s\n", image.GetLastError());
        fprintf(stderr, "error saving %s\n", argv[2]);
        return 1;
	}

	printf("Done!\n");
	return 0;
}

