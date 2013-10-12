// bg_trans.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ximage.h"
#include <io.h>
#include <direct.h>
#include <map>
#include <string>

char* unit_move_pics[] = {
	"movedown_01",
	"movedown_02",
	"moveup_01",
	"moveup_02",
	"moveleft_01",
	"moveleft_02",
	NULL,
};

void generate_move_plist()
{
	mkdir("mix_png");
	FILE *fp = fopen("mix_png/mix_png.plist", "w");
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fp, "<plist version=\"1.0\">\n");
	fprintf(fp, "<dict>\n");

	fprintf(fp, "<key>texture</key>\n\
		<dict>\n\
		<key>height</key>\n\
		<integer>528</integer>\n\
		<key>width</key>\n\
		<integer>48</integer>\n\
		</dict>\n");


	fprintf(fp, "<key>frames</key>\n<dict>\n");
	struct _finddata_t finddata;
	int file_Handle = _findfirst("./*.png", &finddata);
	if(file_Handle == -1)
		return;
	do
	{		
		if ( (finddata.attrib &_A_ARCH) )
		{	
			for (int i=0; unit_move_pics[i] != NULL; ++i)
			{
				int j = atoi(finddata.name);
				fprintf(fp, "<key>%d_%s.png</key>\n", j, unit_move_pics[i]);
				fprintf(fp, "<dict>\n");
				fprintf(fp, "<key>height</key>\n");
				fprintf(fp, "<integer>48</integer>\n");
				fprintf(fp, "<key>width</key>\n");
				fprintf(fp, "<integer>48</integer>\n");
				fprintf(fp, "<key>originalHeight</key>\n");
				fprintf(fp, "<integer>48</integer>\n");
				fprintf(fp, "<key>originalWidth</key>\n");
				fprintf(fp, "<integer>48</integer>\n");
				fprintf(fp, "<key>x</key>\n");
				fprintf(fp, "<integer>%d</integer>", j*48);
				fprintf(fp, "<key>y</key>\n");
				fprintf(fp, "<integer>%d</integer>", i*48);
				fprintf(fp, "</dict>\n");
				
			}
		}		

	}while(0 == _findnext(file_Handle, &finddata));


	_findclose(file_Handle);


	fprintf(fp, "</dict>\n");
	fprintf(fp, "</dict>\n</plist>\n");
	fclose(fp);
}

int bg_trans()
{
	struct _finddata_t finddata;
	int file_Handle = _findfirst("./*.png", &finddata);
	if(file_Handle == -1)
		return 0;

	mkdir("bg_trans");

	do
	{		
		if ( (finddata.attrib &_A_ARCH) )
		{			
			char szSave[32] = {0};
			
			CxImage *ima = new CxImage(finddata.name, CXIMAGE_FORMAT_PNG);
			if (ima->IsValid()) 
			{		
				/*
				ima->SetTransIndex(ima->GetPixelIndex(0,ima->GetHeight() - 1));
								ima->SetTransColor(ima->GetPixelColor(0,ima->GetHeight() - 1));*/
				
				ima->SetTransIndex(0);
				RGBQUAD rgb;
				rgb.rgbRed =247;
				rgb.rgbGreen=0;
				rgb.rgbBlue=255;
				rgb.rgbReserved=0;
				ima->SetTransColor(rgb);

				sprintf(szSave, "./bg_trans/%s", finddata.name);
				ima->Save(szSave,CXIMAGE_FORMAT_PNG);
			}
			delete ima;
		}		

	}while(0 == _findnext(file_Handle, &finddata));


	_findclose(file_Handle);
}

int mix_png()
{
	struct _finddata_t finddata;
	int file_Handle = _findfirst("./*.png", &finddata);
	if(file_Handle == -1)
		return 0;

	mkdir("mix_png");
	std::map<std::string, CxImage*> fileMap;
	int h = 0;
	int w = 0;

	do
	{		
		if ( (finddata.attrib &_A_ARCH) )
		{
			CxImage *ima = new CxImage(finddata.name, CXIMAGE_FORMAT_PNG);
			if (ima->IsValid()) 
			{
				if (ima->GetHeight() >h)
					h = ima->GetHeight();

				w += ima->GetWidth();
				fileMap[finddata.name] = ima;
			}			
		}		

	}while(0 == _findnext(file_Handle, &finddata));

	_findclose(file_Handle);

	
	std::map<std::string, CxImage*>::iterator it = fileMap.begin();
	CxImage ima_out;
	ima_out.Create(w, h, it->second->GetBpp(), CXIMAGE_FORMAT_PNG);
	ima_out.SetPalette(it->second->GetPalette());

	int w_ins = 0;
	for (; it != fileMap.end(); ++it)
	{
		ima_out.MixFrom(*(it->second), w_ins, 0);
		w_ins += it->second->GetWidth();
	}

	ima_out.Save("./mix_png/mix.png", CXIMAGE_FORMAT_PNG);

}

int seprate_png()
{
	struct _finddata_t finddata;
	int file_Handle = _findfirst("./*.png", &finddata);
	if(file_Handle == -1)
		return 0;

	mkdir("sep_png");
	
	int h = 48;
	int w = 48;

	do
	{		
		if ( (finddata.attrib &_A_ARCH) )
		{
			CxImage  ima;
			ima.Load(finddata.name, CXIMAGE_FORMAT_PNG);
			if (ima.IsValid()) 
			{
				ima.Save("c:/temp.png", CXIMAGE_FORMAT_PNG);
				ima.Load("c:/temp.png", CXIMAGE_FORMAT_PNG);
				for (int i=0; unit_move_pics[i] != NULL; ++i)
				{
					int j = atoi(finddata.name);
					CxImage ima_out;
					ima_out.Create(w, h, ima.GetBpp(), CXIMAGE_FORMAT_PNG);
					ima_out.SetPalette(ima.GetPalette());
					ima_out.SeprateFrom(ima, 0, ima.GetHeight()-(i+1)*48);

					ima_out.SetTransIndex(0);
					RGBQUAD rgb;
					rgb.rgbRed =247;
					rgb.rgbGreen=0;
					rgb.rgbBlue=255;
					rgb.rgbReserved=0;
					ima_out.SetTransColor(rgb);

					char out_name[32] = {0};
					sprintf(out_name, "sep_png/%d_%s.png",j, unit_move_pics[i]);
					ima_out.Save(out_name, CXIMAGE_FORMAT_PNG);
				}
				
			}			
		}		

	}while(0 == _findnext(file_Handle, &finddata));

	_findclose(file_Handle);
}

int rename_png()
{
	struct _finddata_t finddata;
	int file_Handle = _findfirst("./*.png", &finddata);
	if(file_Handle == -1)
		return 0;

	char new_name[64] = {0};
	do
	{		
		if ( (finddata.attrib &_A_ARCH) )
		{
			
			strncpy(new_name, finddata.name, sizeof(new_name));
			char* pos = strchr(new_name, '-');

			if (pos != 0)
			{
				*pos = 0;
				strcat(new_name, ".png");
				rename(finddata.name, new_name);	
			}
					
		}		

	}while(0 == _findnext(file_Handle, &finddata));

	_findclose(file_Handle);
}



void mix_png2()
{
	CxImage img1,img2,img3;
	int h1,w1,h2,w2,h3,w3,bpp;
	img1.Load("F:\\1.png", CXIMAGE_FORMAT_PNG);
	img2.Load("F:\\2.png", CXIMAGE_FORMAT_PNG);
	h1=img1.GetHeight();
	w1=img1.GetWidth();
	h2=img2.GetHeight();
	w2=img2.GetWidth();
	h3=h1;
	w3=w1+w2;
	bpp=img1.GetBpp();
	img3.Create(w3,h3,bpp,CXIMAGE_FORMAT_PNG);
	img3.SetPalette(img1.GetPalette());
	img3.MixFrom(img1,0,0);
	img3.MixFrom(img2,w1,0);

	
	img3.Save("f:\\3.png",CXIMAGE_FORMAT_PNG);
}

int _tmain(int argc, _TCHAR* argv[])
{
	rename_png();
	seprate_png();
	return 0;
}

