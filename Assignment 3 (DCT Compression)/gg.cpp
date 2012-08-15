// KINGPCX.cpp: implementation of the KINGPCX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kingimage.h"
#include "KINGPCX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KINGPCX::KINGPCX()
{
	color=0;
}

KINGPCX::~KINGPCX()
{
	delete color;

}

int KINGPCX::getpicture(CFile *fp)
{
	int num;
	fp->SeekToBegin();
	num=fp->Read(&pcxhead,sizeof(pcxhead));
	width=pcxhead.xmax-pcxhead.xmin+1;
	height=pcxhead.ymax-pcxhead.ymin+1;
	usedbyte=width*height;
	bitsperpixel=pcxhead.bitperpixel;
	linebytes=pcxhead.bytes_per_line;
	usedcolor=1;
	usedcolor<<=bitsperpixel;
	bitsperpixel*=pcxhead.color_planes;
	point=new BYTE[linebytes*height*pcxhead.color_planes];
//	pixel=new BYTE[2];
	num=fp->GetPosition();
	int length=fp->GetLength()-num;
	if (bitsperpixel==8)
		length-=256*3;
	pixel=new BYTE[length];
	fp->Read(pixel,length);
	decodepcx(pixel);
	num=fp->GetPosition();
	if (bitsperpixel==8){
		color=new GIFCOLOR[256];
		num=fp->Read(&color[0].red,256*3);
		num=fp->GetPosition();
	}
	else
		color=new GIFCOLOR[2];
	initbmp();
	return 0;
}

int KINGPCX::savepicture(CFile *fp)
{
	return 0;
}

int KINGPCX::decodepcx(BYTE *fp)
{
	int place=0;
	if (bitsperpixel!=24)
	for (int i=0;i<height;i++){
		int readnum=0;
		while (readnum<linebytes){
//			BYTE now;
//			fp->Read(&now,1);
			if (*fp>0xc0){
				BYTE num;
//				num=now-0xc0;
				num=*(fp++)-0xc0;
//				fp->Read(&now,1);
//				readnum+=num;
				for (BYTE j=0;j<num;j++){
					readnum++;
					if (readnum<width)
						point[place++]=*fp;
			}
			else{
				readnum++;
				if (readnum<width)
					point[place++]=*fp;
			}
			fp++;
		}
	}
	else
	for (int i=0;i<height;i++)
		for (int k=0;k<3;k++){
		int readnum=0;
		place=i*3*width+k;
		while (readnum<linebytes){
//			BYTE now;
//			fp->Read(&now,1);
			if (*fp>0xc0){
				BYTE num;
//				num=now-0xc0;
				num=*(fp++)-0xc0;
//				fp->Read(&now,1);
//				readnum+=num;
				for (BYTE j=0;j<num;j++){
					readnum++;
					if (readnum<width)
						point[place]=*fp;
					place+=3;
				}
			}
			else{
				readnum++;
				if (readnum<width)
					point[place]=*fp;
				place+=3;
			}
			fp++;
		}
		}
	return 0;
}

int KINGPCX::initbmp()
{
	bmpinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth=width;
	bmpinfo.bmiHeader.biHeight=height;
	bmpinfo.bmiHeader.biPlanes=1;//pcxhead.color_planes;
	bmpinfo.bmiHeader.biBitCount=bitsperpixel;
	bmpinfo.bmiHeader.biCompression=0;
	bmpinfo.bmiHeader.biSizeImage=0;
	bmpinfo.bmiHeader.biXPelsPerMeter=0;
	bmpinfo.bmiHeader.biYPelsPerMeter=0;
	bmpinfo.bmiHeader.biClrUsed=0;
	bmpinfo.bmiHeader.biClrImportant=0;
	if (pcxhead.color_planes==1)
		for (int i=0;i<usedcolor;i++){
			bmpinfo.bmiColors[i].rgbBlue=color[i].blue;
			bmpinfo.bmiColors[i].rgbGreen=color[i].green;
			bmpinfo.bmiColors[i].rgbRed=color[i].red;
			bmpinfo.bmiColors[i].rgbBlue=0;
		}
	return 0;
}

int KINGPCX::draw(CDC *pdc)
{
	
	int ret=::SetDIBitsToDevice(pdc->m_hDC,0,0,width,height,0,0,0,height,point,&bmpinfo,DIB_RGB_COLORS);
	ret++;
/*
	int place=0;
	if (pcxhead.color_planes!=1)
	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++)
			pdc->SetPixel(j,i,RGB(point[place++],point[place++],point[place++]));
	else
	if (bitsperpixel==8)
	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++){
			BYTE num=point[place++];
			pdc->SetPixel(j,i,RGB(color[num].red,color[num].green,color[num].blue));
		}
	else
	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++){
			BYTE num=point[place++];
			pdc->SetPixel(j,i,RGB(pcxhead.palette[num*3],pcxhead.palette[num*3+1],pcxhead.palette[num*3+2]));
		}
*/	
	return 0;
}
