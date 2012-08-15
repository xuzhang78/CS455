// kingimageView.cpp : implementation of the CKingimageView class
//

#include "stdafx.h"
#include "kingimage.h"
#include "math.h"
#include "kingimageDoc.h"
#include "kingimageView.h"
#define PI 3.1415926535
#define inv16 0.0625

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static double intense[1000][1000];
static double dct[8][8];
static double cosine[8][8];

/////////////////////////////////////////////////////////////////////////////
// CKingimageView

IMPLEMENT_DYNCREATE(CKingimageView, CScrollView)

BEGIN_MESSAGE_MAP(CKingimageView, CScrollView)
	//{{AFX_MSG_MAP(CKingimageView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_ASSIGNMENT3_HSI, &CKingimageView::OnAssignment3Hsi)
	ON_COMMAND(ID_ASSIGNMENT3_8, &CKingimageView::OnAssignment38)
	ON_COMMAND(ID_ASSIGNMENT3_9, &CKingimageView::OnAssignment39)
	ON_COMMAND(ID_ASSIGNMENT3_10, &CKingimageView::OnAssignment310)
	ON_COMMAND(ID_ASSIGNMENT3_TEST, &CKingimageView::OnAssignment3Test)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKingimageView construction/destruction

CKingimageView::CKingimageView()
{
	// TODO: add construction code here

}

CKingimageView::~CKingimageView()
{
}

BOOL CKingimageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView drawing
void CKingimageView::OnDraw(CDC* pDC)
{
	CKingimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDC->SetStretchBltMode(COLORONCOLOR);
//	int x,y,bytes;
	if (pDoc->imagetype==PCX)
		(pDoc->_pcx)->draw(pDC);
	if (pDoc->imagetype==BMP)
		(pDoc->_bmp)->draw(pDC);
	if (pDoc->imagetype==GIF)
		(pDoc->_gif)->draw(pDC);
	if (pDoc->imagetype==JPG)
		(pDoc->_jpg)->draw(pDC);
/*	if (pDoc->imagetype==BMP)
	{
	
	x=((KINGBMP*)(pDoc->_ppicture))->bmpinfo.bmiHeader.biWidth;
	y=((KINGBMP*)(pDoc->_ppicture))->bmpinfo.bmiHeader.biHeight;
	bytes=(pDoc->_ppicture)->needbyte;
	int place=0;
	for (int j=0;j<y;j++)
		for (int i=0;i<x;i++){
//			int color= (pDoc->_bmp)->point[place++] ;
			pDC->SetPixel(i,j,RGB( (pDoc->_picture)->pixel[place+2], (pDoc->_picture)->pixel[place+1] ,(pDoc->_picture)->pixel[place]));
			place+=3;
		}

  /*	if ( (pDoc->_bmp)->bitsperpixel!=24 ){
		CPalette *palette=new CPalette();
		LOGPALETTE palet;
		palet.palVersion=0x300;
		palet.palNumEntries=(pDoc->_bmp)->usedcolor;
		for (int i=0;i<palet.palNumEntries;i++){
			palet.palPalEntry[i].peRed=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbRed;
			palet.palPalEntry[i].peBlue=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbBlue;
			palet.palPalEntry[i].peGreen=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbGreen;
			palet.palPalEntry[i].peFlags=0;//( (pDoc->_bmp) -> bmpinfo) .bmiColors[0].rgbRed;
		}
		BOOL re=palette->CreatePalette(&palet);
		CPalette *pp;
		pp=pDC->SelectPalette(palette,TRUE);
	}
*/
//	::SetDIBitsToDevice(pDC->m_hDC,0,0,x,y,0,0,0,y,(pDoc->_ppicture)->point,&(((KINGBMP*)(pDoc->_ppicture))->bmpinfo),DIB_RGB_COLORS);
	
//	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView printing
BOOL CKingimageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKingimageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKingimageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView diagnostics

#ifdef _DEBUG
void CKingimageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKingimageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

static double alpha(int i){
	if (i==0) return 1.0/sqrt(8.0);
	return 0.5;
}

static void cosineCalc(){
	for (int i=0; i<8; ++i)
	for (int j=0; j<8; ++j)	cosine[i][j] = cos(PI*i*(2.0*j + 1)*inv16);
}

CKingimageDoc* CKingimageView::GetDocument() // non-debug version is inline
{
	cosineCalc();
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKingimageDoc)));
	return (CKingimageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKingimageView message handlers



void CKingimageView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize totalSize=CSize(::GetSystemMetrics(SM_CXSCREEN),
		                  ::GetSystemMetrics(SM_CYSCREEN));
	CSize pageSize=CSize(totalSize.cx/2,totalSize.cy/2);
	CSize lineSize=CSize(totalSize.cx/10,totalSize.cy/10);

	SetScrollSizes(MM_TEXT,totalSize,pageSize,lineSize);
}

void CKingimageView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CScrollView::OnMouseMove(nFlags, point);
}

//******************************************************
//  Image Processing Sample Program for CS555
//  Image origin: lower-left point
//  Image info:
//		int width;
//		int height;
//		int bitsperpixel;
//		int needbyte;
//		int usedcolor;
//		int usedbyte;
//		BYTE *pixel;	//maybe serval point in one BYTE
//		BYTE *point;
//
//  
//******************************************************
void CKingimageView::OnAssignment3Hsi()
{
	CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;
	double param = 0, intensity=0, hue = 0, saturation = 0;
	int red, blue, green, all;

	if(iWidth%4 != 0) iWidth -= iWidth%4;

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
        for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth+j] = 255;
		}
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
			blue = pImg[i*iWidth*3+j*3];      //B
			green = pImg[i*iWidth*3+j*3+1];      //G
			red = pImg[i*iWidth*3+j*3+2];      //R 
			all = red+green+blue;

			if (all != 0)
			{
			//intensity 
			intensity = all/3;

			//hue
			param = (red-green)*(red-green) + (red-blue)*(green-blue);
			hue = (0.5*(red+red-green-blue))/(sqrt(param));
			if (blue <= green) hue = acos(hue);
			else hue = 2*PI - acos(hue);
			hue = hue*180/PI;

			//saturation
			saturation = 1 - ((min(red,(min(blue,green))))/intensity);

			pImg[i*iWidth*3+j*3] = intensity;      //B
			pImg[i*iWidth*3+j*3+1] = intensity;      //G
			pImg[i*iWidth*3+j*3+2] = intensity;		//R

			/*
			if (hue > 0 && hue < 120) {
				pImg[i*iWidth*3+j*3] = intensity*(1-saturation);			//B
				pImg[i*iWidth*3+j*3+2] = intensity*(1+(
					(saturation*cos(hue))/cos(60-hue)));					//R 
				pImg[i*iWidth*3+j*3+1] = 3*intensity - (red+blue);			//G
			}
			else if (hue >= 120 && hue < 240){
				hue = hue - 120;
				pImg[i*iWidth*3+j*3+2] = intensity*(1-saturation);			//R
				pImg[i*iWidth*3+j*3+1] = intensity*(1+(
					(saturation*cos(hue))/cos(60-hue)));					//G
				pImg[i*iWidth*3+j*3] = 	3*intensity - (red+green);			//B
			}
			else if (hue >= 240){
				hue = hue - 240;
				pImg[i*iWidth*3+j*3+1] = intensity*(1-saturation);			//G			
				pImg[i*iWidth*3+j*3] = intensity*(1+(
					(saturation*cos(hue))/cos(60-hue)));					//B
				pImg[i*iWidth*3+j*3+2] = 3*intensity - (green+blue);		//R 
			}*/
			}
		}
	}
	////redraw the screen
	OnDraw(GetDC());
}

//calculating 8*8 dct on image
void CKingimageView::OnAssignment38()
{
	CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;
	int red, blue, green, all;
	if (iWidth%8 != 0) iWidth = iWidth -iWidth%8;
	if (iHeight%8 != 0) iHeight = iHeight -iHeight%8;

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
        for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth+j] = 255;
		}
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)	
		{
			blue = pImg[i*iWidth*3+j*3];      //B
			green = pImg[i*iWidth*3+j*3+1];      //G
			red = pImg[i*iWidth*3+j*3+2];      //R 
			all = red+green+blue;

			//intensity array
			if (all != 0) intense[i][j] = all/3;
		}

		for(int i=0; i<iHeight-7; i+=8)
		for(int j=0; j<iWidth-7; j+=8)
		{
			for (int x=0; x<8; ++x)
			for (int y=0; y<8; ++y)
			{
				dct[x][y] = 0;
				for (int u=0; u<8; ++u)
				for (int v=0; v<8; ++v)
				{
					dct[x][y] += intense[i+u][j+v]*cosine[x][u]*cosine[y][v];
				}
				dct[x][y] = alpha(x)*alpha(y)*dct[x][y];
			}

			for (int u=0; u<8; ++u)
			for (int v=0; v<8; ++v)
			{
				for (int x=0; x<8; ++x)		
				for (int y=0; y<8; ++y)
				{
			//		if (!(x==0 && y==0))	//uncomment this if statement for the correct color!
					intense[i+u][j+v] += alpha(x)*alpha(y)*dct[x][y]*cosine[x][u]*cosine[y][v];
				}
				if (intense[i+u][j+v] > 255) intense[i+u][j+v] = 255;
				if (intense[i+u][j+v] < 0) intense[i+u][j+v]= 0;
			}
			for(int x=i; x<i+8; ++x)
			for(int y=j; y<j+8; ++y)
			{
				pImg[x*iWidth*3+y*3] = intense[x][y];			//B
				pImg[x*iWidth*3+y*3+1] = intense[x][y];			//G
				pImg[x*iWidth*3+y*3+2] = intense[x][y];			//R 
			}
		}
	}

    ////redraw the screen
	OnDraw(GetDC());

	for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
			intense[i][j] = 0;
}

/* calculates the DCT using only the DC
   part of the image. then projects the result
   onto the screen
*/
void CKingimageView::OnAssignment39()
{
    CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;
	int red, blue, green, all;
	if (iWidth%8 != 0) iWidth = iWidth -iWidth%8;
	if (iHeight%8 != 0) iHeight = iHeight -iHeight%8;

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
        for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++) pImg[i*iWidth+j] = 255;
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)	
		{
			blue = pImg[i*iWidth*3+j*3];      //B
			green = pImg[i*iWidth*3+j*3+1];      //G
			red = pImg[i*iWidth*3+j*3+2];      //R 
			all = red+green+blue;

			//intensity array
			if (all != 0) intense[i][j] = all/3;
		}

		for (int u=0; u<8; ++u)
		for (int v=0; v<8; ++v)	dct[u][v] = 0;

		for(int i=0; i<iHeight-7; i+=8)
		for(int j=0; j<iWidth-7; j+=8)
		{
			for (int x=0; x<1; ++x)
			for (int y=0; y<1; ++y)
			{
				for (int u=0; u<8; ++u)
				for (int v=0; v<8; ++v)
				{
					dct[x][y] += intense[i+u][j+v]*cosine[x][u]*cosine[y][v];
				}
				dct[x][y] = alpha(x)*alpha(y)*dct[x][y];
			}

			for (int u=0; u<8; ++u)
			for (int v=0; v<8; ++v)
			{
				for (int x=0; x<8; ++x)
				for (int y=0; y<8; ++y)
				{
					intense[i+u][j+v] += alpha(x)*alpha(y)*dct[x][y]*cosine[x][u]*cosine[y][v];
				}
				if (intense[i+u][j+v] > 255) intense[i+u][j+v] = 255;
				if (intense[i+u][j+v] < 0) intense[i+u][j+v]= 0;
			}
			for(int x=i; x<i+8; ++x)
			for(int y=j; y<j+8; ++y)
			{
				pImg[x*iWidth*3+y*3] = intense[x][y];			//B
				pImg[x*iWidth*3+y*3+1] = intense[x][y];			//G
				pImg[x*iWidth*3+y*3+2] = intense[x][y];			//R 
			}
		}
	}

    ////redraw the screen
	OnDraw(GetDC());

	for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
			intense[i][j] = 0;
}

/*	calculates DCT 8*8 but this time
	using a the 3*3 values of the matrix as the main frequency
	components, discards all others.
*/
void CKingimageView::OnAssignment310()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;
	int red, blue, green, all;
	if (iWidth%8 != 0) iWidth = iWidth -iWidth%8;
	if (iHeight%8 != 0) iHeight = iHeight -iHeight%8;
	
	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
        for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++) pImg[i*iWidth+j] = 255;
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		//reseting the dct array to 0
		for (int u=0; u<8; ++u)
		for (int v=0; v<8; ++v) dct[u][v] = 0;

		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)	
		{
			blue = pImg[i*iWidth*3+j*3];      //B
			green = pImg[i*iWidth*3+j*3+1];      //G
			red = pImg[i*iWidth*3+j*3+2];      //R 
			all = red+green+blue;

			//intensity array
			if (all != 0) intense[i][j] = all/3;
		}

		for(int i=0; i<iHeight-7; i+=8)
		for(int j=0; j<iWidth-7; j+=8)
		{
			for (int x=0; x<3; ++x)
			for (int y=0; y<3; ++y)
			{
				dct[x][y] = 0;
				for (int u=0; u<8; ++u)
				for (int v=0; v<8; ++v)
				{
					dct[x][y] += intense[i+u][j+v]*cosine[x][u]*cosine[y][v];
				}
				dct[x][y] = alpha(x)*alpha(y)*dct[x][y];
			}

			for (int u=0; u<8; ++u)
			for (int v=0; v<8; ++v)
			{
				for (int x=0; x<8; ++x)
				for (int y=0; y<8; ++y)
				{
					intense[i+u][j+v] += alpha(x)*alpha(y)*dct[x][y]*cosine[x][u]*cosine[y][v];
				}
				if (intense[i+u][j+v] > 255) intense[i+u][j+v] = 255;
				if (intense[i+u][j+v] < 0) intense[i+u][j+v]= 0;
			}
			for(int x=i; x<i+8; ++x)
			for(int y=j; y<j+8; ++y)
			{
				pImg[x*iWidth*3+y*3] = intense[x][y];			//B
				pImg[x*iWidth*3+y*3+1] = intense[x][y];			//G
				pImg[x*iWidth*3+y*3+2] = intense[x][y];			//R 
			}
		}
	}

    ////redraw the screen
	OnDraw(GetDC());

	for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
			intense[i][j] = 0;
}

//practice for part 1
static double beta(int i){
	if (i==0) return sqrt(1./16.);
	return sqrt(2./16.);
}
void CKingimageView::OnAssignment3Test()
{
	double matrix[16] = {10.,11.,12.,11.,12.,13.,12.,11.,10.,-10.,8.,-7.,8.,-8.,7.,-7.};
	double result[16];

	for (int u=0;u<16;u++)
	for (int i=0;i<16;i++)
	{
		result[u] += beta(u)*cos(PI*u*(2*i+1)*inv16)*matrix[i];
	}
	for (int u=0;u<16;u++) result[u] = result[u];
}
