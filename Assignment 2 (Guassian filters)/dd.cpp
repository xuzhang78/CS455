// KINGGIF.cpp: implementation of the KINGGIF class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kingimage.h"
#include "KINGGIF.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KINGGIF::KINGGIF()
{
	existglobe=0;
	existlocal=0;
	usedcolor=0;
	index=0;
	leftbits=8;
	place=0;
	usedmask[0]=1;
	for (int i=1;i<8;i++)
		usedmask[i]=usedmask[i-1]<<1;
}

KINGGIF::~KINGGIF()
{
	delete globe_gifcolor;
	delete local_gifcolor;
}

int KINGGIF::getpicture(CFile *fp)
{
	int num;
	fp->SeekToBegin();
	num=fp->Read(&gifhead,GIFHEADLENGTH);
	if ( (gifhead.copyright[0]!='G') || (gifhead.copyright[1]!='I') || (gifhead.copyright[2]!='F') )
		return -1;
	bitsperpixel=(gifhead.globe_flag&0x07)+1;
	if (gifhead.globe_flag&0x80){
		existglobe=1;
		usedcolor=1;
		usedcolor<<=bitsperpixel;
		_init=usedcolor;
		_end=usedcolor+1;
		globe_gifcolor=new GIFCOLOR[usedcolor];
		fp->Seek(GIFHEADLENGTH,CFile::begin);
		num=fp->Read(&globe_gifcolor[0].red,sizeof(GIFCOLOR)*usedcolor);
		num=fp-> GetPosition();
	}
	else
		globe_gifcolor=new GIFCOLOR[2];

	int offset=fp->Seek(GIFHEADLENGTH+usedcolor*sizeof(GIFCOLOR),CFile::begin);
	BYTE next;
	fp->Read(&next,1);
	num=fp-> GetPosition();
	int end=0;
	while (end==0)
		switch	(next)
	{
		case ';':
			end=1;break;
		case ',':
			fp->Read(&gifdatahead,GIFLOCALHEADLENGTH);
			offset+=GIFLOCALHEADLENGTH;
			width=(gifdatahead.width+3)/4*4;
			height=gifdatahead.height;
			usedbyte=width*height;
			needbyte=width*height;
			pixel=new BYTE[needbyte];
			point=new BYTE[usedbyte];
			if (gifdatahead.local_flag&0x80){
				existlocal=1;
				usedcolor=1;
				usedcolor<<=bitsperpixel;
				_init=usedcolor;
				_end=usedcolor+1;
				local_gifcolor=new GIFCOLOR[usedcolor];
				fp->Seek(offset,CFile::begin);
				num=fp->Read(&local_gifcolor[0].red,sizeof(GIFCOLOR)*usedcolor);
				offset=offset+sizeof(GIFCOLOR)*usedcolor;
			}
			else
				local_gifcolor=new GIFCOLOR[2];
			num=fp->GetLength()-fp->GetPosition();
			fp->Seek(offset,CFile::begin);
			fp->Read(pixel,num);
			temp=num;
			decodelzw(pixel);
			end=1;
			break;
		case '!':
			break;
		default: 
			exit(-2);
	}
	return 0;
}

int KINGGIF::savepicture(CFile *fp)
{
	fp->SeekToBegin();
	fp->Write(&gifhead,GIFHEADLENGTH);
	if (existglobe==1){
		fp->Write(&globe_gifcolor[0].red,sizeof(GIFCOLOR)*usedcolor);
	}
	BYTE next=',';
	fp->Write(&next,1);
	fp->Write(&gifdatahead,GIFLOCALHEADLENGTH);
	if (existlocal==1)
		fp->Write(&local_gifcolor[0].red,sizeof(GIFCOLOR)*usedcolor);
	BYTE *code=new BYTE[usedbyte*2];
	int reallen=0;
	codelzw(code,&reallen);
	fp->Write(code,reallen);
	delete code;
	return 0;
}

int KINGGIF::decodelzw(BYTE *fp)
{
//	temp=num;
	int place=0;
	BYTE *nowpoint;
	nowpoint=point;
	inittable();
	BYTE *now;
	now=fp;
	readbits=*(now++)+1;
	temp--;
	int pre=-1;
	temp--;
	int end=0;
	while (end==0){
	int next=getcode(&now);
	if (next>top)
		return -1;
	if (next==_init){
		pre=-1;
		inittable();
	}
	else
		if (next==_end)
			end=1;
		else{
			if (next<top){
				if (pre!=-1) 
					inserttable(pre,next);
			}
			else
				inserttable(pre,pre);
		pre=next;
		if (usedcolor!=256)
			for (int i1=0;i1<table[next].GetLength();i1++){
				*(nowpoint++)=table[next].GetAt(i1);
				place++;
				if (place==gifdatahead.width)
					for (int ii=gifdatahead.width;ii<width;ii++)
						*(nowpoint++)=place=0;
			}
		else
			for (int i1=0;i1<table[next].GetLength()/2;i1++){
				*(nowpoint)=table[next].GetAt(i1<<1)<<4;
				(*(nowpoint++))+=table[next].GetAt((i1<<1)+1);
				place++;
				if (place==gifdatahead.width)
					for (int ii=gifdatahead.width;ii<width;ii++)
						*(nowpoint++)=place=0;
			}
		
		}
	}
	initbmp();
	return 0;
}

void KINGGIF::inittable()
{
	nowmax=usedcolor<<1;
	readbits=bitsperpixel+1;
	if (usedcolor<256)
		for (int i=0;i<usedcolor;i++)
			table[i]=i;
	else  
		for (int i=0;i<usedcolor;i++)
			table[i]=CString(i>>4)+CString(i&0x0f);
	for (int i=usedcolor;i<4096;i++)
		table[i]='\0';
	top=usedcolor+2;
}





int KINGGIF::inserttable(int pre, int next)
{
	if (usedcolor==256)
		table[top]=table[pre]+table[next].GetAt(0)+table[next].GetAt(1);
	else
		table[top]=table[pre]+table[next].GetAt(0);
	top++;
	if (top==nowmax){
		readbits++;
		nowmax<<=1;
		int whythis=readbits;
		if (whythis==13)
			readbits--;
	}
	return 0;
}

int KINGGIF::getcode(BYTE **now)
{
	int needbits=readbits;
	int total=0;
	int power=0;
	preleftbits=leftbits;
	while (index==0)	
		index=*((*now)++);
	while (needbits>leftbits){//
		int thisterm=0;
		thisterm=(**now)>>(8-leftbits);
		total=total+(thisterm<<power);
		power+=leftbits;
		needbits-=leftbits;
		(*now)++;
		index--;
		while (index==0)
			index=*((*now)++);
		leftbits=8;
	}
	int thisterm=0;
	int mask=0xff;
	mask>>=(leftbits-needbits);
	thisterm=(**now)&mask;
	total=total+(thisterm<<power);
	leftbits=leftbits-needbits;
	if (leftbits==0){
		leftbits=8;
		(*now)++;
		index--;
		while (index==0)
			index=*((*now)++);
	}
	return total;
}

int KINGGIF::initbmp()
{
	bmpused.bmpinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
//	bmpused.bmpinfo.bmiHeader.biWidth=(width+3)/4*4;
	bmpused.bmpinfo.bmiHeader.biWidth=width;
	bmpused.bmpinfo.bmiHeader.biHeight=-height;
	bmpused.bmpinfo.bmiHeader.biPlanes=1;
	bmpused.bmpinfo.bmiHeader.biBitCount=8;//bitsperpixel;
	bmpused.bmpinfo.bmiHeader.biCompression=0;
	bmpused.bmpinfo.bmiHeader.biSizeImage=0;
	bmpused.bmpinfo.bmiHeader.biXPelsPerMeter=0;
	bmpused.bmpinfo.bmiHeader.biYPelsPerMeter=0;
	bmpused.bmpinfo.bmiHeader.biClrUsed=usedcolor;
	bmpused.bmpinfo.bmiHeader.biClrImportant=0;
	if (existlocal==1){
	bmpused.bmpinfo.bmiColors[0].rgbBlue=local_gifcolor[0].blue;
	bmpused.bmpinfo.bmiColors[0].rgbGreen=local_gifcolor[0].green;
	bmpused.bmpinfo.bmiColors[0].rgbRed=local_gifcolor[0].red;
	bmpused.bmpinfo.bmiColors[0].rgbReserved=0;
	for (int i=0;i<usedcolor-1;i++){
		bmpused.color[i].rgbBlue=local_gifcolor[i+1].blue;
		bmpused.color[i].rgbGreen=local_gifcolor[i+1].green;
		bmpused.color[i].rgbRed=local_gifcolor[i+1].red;
		bmpused.color[i].rgbReserved=0;
	}
	}
	else{
		bmpused.bmpinfo.bmiColors[0].rgbBlue=globe_gifcolor[0].blue;
		bmpused.bmpinfo.bmiColors[0].rgbGreen=globe_gifcolor[0].green;
		bmpused.bmpinfo.bmiColors[0].rgbRed=globe_gifcolor[0].red;
		bmpused.bmpinfo.bmiColors[0].rgbReserved=0;
		for (int i=0;i<usedcolor-1;i++){
			bmpused.color[i].rgbBlue=globe_gifcolor[i+1].blue;
			bmpused.color[i].rgbGreen=globe_gifcolor[i+1].green;
			bmpused.color[i].rgbRed=globe_gifcolor[i+1].red;
			bmpused.color[i].rgbReserved=0;
		}
	}
	

	return 0;
}

int KINGGIF::draw(CDC *pdc)
{
//	int ret=::SetDIBitsToDevice(pdc->m_hDC,0,0,bmpused.bmpinfo.bmiHeader.biWidth,height,0,0,0,height,point,&bmpused.bmpinfo,DIB_RGB_COLORS);
	int ret=::SetDIBitsToDevice(pdc->m_hDC,0,0,width,height,0,0,0,height,point,&bmpused.bmpinfo,DIB_RGB_COLORS);
	return 0;
}


int KINGGIF::codelzw(BYTE * fp,int *length)
{
	BYTE *now;
	BYTE *needcode;
	needcode=point;
	CString pre='\0';
	CString next;
	int left=usedbyte;
	now=fp;
//	BYTE skip
	leftbits=8;
	inittable();
//	*now=bitsperpixel;
	writecode(&now,length,bitsperpixel);
//	*now=skip;
	skip=0xfe;
	writecode(&now,length,skip);
//	*now=_init;
	writecode(&now,length,_init);
	int last=-1;
	int here=-1;
	while (usedbyte!=0){
		if (usedcolor==256){
		}
		else
			next=*(needcode++);
		CString temp;
		if (last!=-1)
			temp=pre+next;
		else
			temp=next;
		here=find(temp);
		if ( here>=0 ){
			pre=temp;
			last=here;
		}
		else{
			inserttable( last , *(needcode-1) );
			if (top==0x1000){
				writecode(&now,length,_init);	
				inittable();
				last=-1;
				here=-1;
				pre='\0';
			}
			writecode(&now,length,last);
			last=*(needcode-1);
			pre=next;
		}
	}
//	*now=';';
	writecode(&now,length,_end);
	return 0;
}

int KINGGIF::writecode(BYTE * * fp, int * length,int place)
{
	static remain=0;
	int needbits=readbits;
	while (leftbits<needbits){
		BYTE temp=place&usedmask[leftbits];
		temp<<(8-leftbits);
		remain+=temp;
		*((*fp)++)=remain;
		skip--;
		(*length)++;
		if (skip==0){
			skip=0xfe;
			*((*fp)++)=skip;
			(*length)++;
		}
		remain=0;
		leftbits=8;
	}
	place<<=(8-leftbits);
	remain+=place;
	leftbits=8-leftbits;
	if (leftbits==0){
		*((*fp)++)=remain;
		skip--;
		(*length)++;
		if (skip==0){
			skip=0xfe;
			*((*fp)++)=skip;
			(*length)++;
		}
		leftbits=8;
		remain=0;
	}
	return 0;
}

int KINGGIF::find(CString aim)
{
	if (aim.GetLength()==1)
		return aim.GetAt(0);
	for (int i=usedcolor+2;i<top;i++)
		if (table[i]==aim)
			return i;
	return -1;
}
