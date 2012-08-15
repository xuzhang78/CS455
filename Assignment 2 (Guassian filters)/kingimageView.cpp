// kingimageView.cpp : implementation of the CKingimageView class
//

#include "stdafx.h"
#include "kingimage.h"
#include <cmath>
#include "kingimageDoc.h"
#include "kingimageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKingimageView

IMPLEMENT_DYNCREATE(CKingimageView, CScrollView)

BEGIN_MESSAGE_MAP(CKingimageView, CScrollView)
	//{{AFX_MSG_MAP(CKingimageView)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PROCESS, OnProcess)
	ON_COMMAND(ID_any, Onany)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_ASSIGNMENT2_UNSHARPMASK, &CKingimageView::OnAssignment2Unsharpmask)
	ON_COMMAND(ID_ASSIGNMENT2_SOBEL, &CKingimageView::OnAssignment2Sobel)
	ON_COMMAND(ID_LOGMASKS_MASK17, &CKingimageView::OnLogmasksMask1)
	ON_COMMAND(ID_LOGMASKS_MASK211, &CKingimageView::OnLogmasksMask2)
	ON_COMMAND(ID_ASSIGNMENT2_CANNYEDGE, &CKingimageView::OnAssignment2Cannyedge)
	ON_COMMAND(ID_ASSIGNMENT2_ZERO, &CKingimageView::OnAssignment2Zero)
	ON_COMMAND(ID_ZERO_MASK1, &CKingimageView::OnZeroMask1)
	ON_COMMAND(ID_ZERO_MASK211, &CKingimageView::OnZeroMask211)
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

CKingimageDoc* CKingimageView::GetDocument() // non-debug version is inline
{
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

int labels[1000][1000];
void CKingimageView::OnProcess(){}
void CKingimageView::Onany(){}

void CKingimageView::OnAssignment2Unsharpmask()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	for (int i=0; i<1000;++i)
	for (int j=0; j<10000;++j)
		labels[i][j]=0;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		double filter[3][3] =
		{
			-1, -1, -1,
			-1, 9, -1,
			-1, -1, -1
		};
		double calc, one, two, three, four, five, six, seven, eight, nine;

		for(int i=0; i<iHeight; ++i)
		for(int j=0; j<iWidth; ++j)
		{
			one = pImg[i*iWidth+j]*filter[0][0];
			two = pImg[i*iWidth+j+1]*filter[1][0];
			three = pImg[i*iWidth+j+2]*filter[2][0];
			four = pImg[(i+1)*iWidth+j]*filter[0][1];
			five = pImg[(i+1)*iWidth+j+1]*filter[1][1];
			six = pImg[(i+1)*iWidth+j+2]*filter[2][1];
			seven = pImg[(i+2)*iWidth+j]*filter[0][2];
			eight = pImg[(i+2)*iWidth+j+1]*filter[1][2];
			nine = pImg[(i+2)*iWidth+j+2]*filter[2][2];
			
			calc = one + two + three + four + five + six + seven + eight + nine;
			if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			labels[i+1][j+1] = calc;
	//		pImg[i*iWidth+j] = calc;
		}
		for(int i=1; i<iHeight; ++i)
		for(int j=1; j<iWidth; ++j)
		{
			pImg[i*iWidth+j] = labels[i][j];
		}

	
//		pImg[2*iWidth]=255;pImg[3*iWidth]=255;pImg[4*iWidth]=255;
//		pImg[2*iWidth+1]=255;pImg[3*iWidth+1]=255;pImg[4*iWidth+1]=255;
//		pImg[2*iWidth+2]=255;pImg[3*iWidth+2]=255;pImg[4*iWidth+2]=255;
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth*3+j*3]   = 0;      //B
			pImg[i*iWidth*3+j*3+1] = 0;      //G
			pImg[i*iWidth*3+j*3+2] = 0;      //R 
		}
	}

	    ////redraw the screen
		OnDraw(GetDC());
}

void CKingimageView::OnAssignment2Sobel()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);
	for (int i=0; i<1000;++i)
	for (int j=0; j<10000;++j)
		labels[i][j]=0;
	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		/* this is the convolution filter applied for the sobel algorithm
		*/
		double filter[3][3] =
		{
			-1, 0, 1,
			-2, 0, 2,
			-1, 0, 1
		};
		double filtery[3][3] =
		{
			1, 2, 1,
			0, 0, 0,
			-1, -2, -1
		};
		double calc, calcx, one, two, three, four, five, six, seven, eight, nine,
				calcy, oney, twoy, threey, foury, fivey, sixy, seveny, eighty, niney;

		for(int i=0; i<iHeight; ++i)
		for(int j=0; j<iWidth; ++j)
		{
			/* for simplicity i wrote individually every pixel multiplication
			and then applied the formula in the 'calc' double.
			*/
			one = pImg[(i)*iWidth+j]*filter[0][0];
			two = pImg[(i)*iWidth+j+1]*filter[0][1];
			three = pImg[(i)*iWidth+j+2]*filter[0][2];
			four = pImg[(i+1)*iWidth+j]*filter[1][0];
			five = pImg[(i+1)*iWidth+j+1]*filter[1][1];
			six = pImg[(i+1)*iWidth+j+2]*filter[1][2];
			seven = pImg[(i+2)*iWidth+j]*filter[2][0];
			eight = pImg[(i+2)*iWidth+j+1]*filter[2][1];
			nine = pImg[(i+2)*iWidth+j+2]*filter[2][2];
			
			oney = pImg[(i)*iWidth+j]*filtery[0][0];
			twoy = pImg[(i)*iWidth+j+1]*filtery[0][1];
			threey = pImg[(i)*iWidth+j+2]*filtery[0][2];
			foury = pImg[(i+1)*iWidth+j]*filtery[1][0];
			fivey = pImg[(i+1)*iWidth+j+1]*filtery[1][1];
			sixy = pImg[(i+1)*iWidth+j+2]*filtery[1][2];
			seveny = pImg[(i+2)*iWidth+j]*filtery[2][0];
			eighty = pImg[(i+2)*iWidth+j+1]*filtery[2][1];
			niney = pImg[(i+2)*iWidth+j+2]*filtery[2][2];

			calcx = one + two + three + four + five + six + seven + eight + nine;
			calcy = oney + twoy + threey + foury + fivey + sixy + seveny + eighty + niney;

			calc = sqrt((calcx*calcx) + (calcy*calcy));
			if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			labels[i+2][j+1] = calc;			//made sure i added the result to a new array so i doesnt modify the actual pixels
		}
		for(int i=2; i<iHeight; ++i)
		for(int j=1; j<iWidth; ++j)
		{
			pImg[i*iWidth+j] = labels[i][j];
		}
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth*3+j*3]   = 0;      //B
			pImg[i*iWidth*3+j*3+1] = 0;      //G
			pImg[i*iWidth*3+j*3+2] = 0;      //R 
		}
	}

	    ////redraw the screen
		OnDraw(GetDC());
}

void CKingimageView::OnLogmasksMask1()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);

	for (int i=0; i<1000;++i)
	for (int j=0; j<10000;++j)
		labels[i][j]=0;
	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		double calc, one, two, three;

		const int k = 7;
		const int k2 = k/2;
		double coeff[k][k];
		double sigma = 1.4;
		const int NORM = 25;

		for (int di=0; di<k; ++di)
		for (int dj=0; dj<k; ++dj)
		{
			one = -(1/(3.14*sigma*sigma*sigma*sigma));
			two = 1-((((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			three = exp(-(((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			coeff[di][dj] = one*two*three*NORM;
		}

		for(int i=k; i<iHeight-k; ++i)
		for(int j=k; j<iWidth-k; ++j)
		{
			for (int di=0; di<k;++di)
			for (int dj=0; dj<k;++dj)
			{
				calc += pImg[(i+di)*iWidth+j+dj]*coeff[dj][di];
			}
			if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			labels[i+1][j+1] = calc;
	//		pImg[i*iWidth+j] = calc;
		}
		for(int i=1; i<iHeight; ++i)
		for(int j=1; j<iWidth; ++j)
		{
			pImg[i*iWidth+j] = labels[i][j];
		}
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth*3+j*3]   = 0;      //B
			pImg[i*iWidth*3+j*3+1] = 0;      //G
			pImg[i*iWidth*3+j*3+2] = 0;      //R 
		}
	}

	////redraw the screen
	OnDraw(GetDC());
}
void CKingimageView::OnLogmasksMask2()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);
	for (int i=0; i<1000;++i)
	for (int j=0; j<10000;++j)
		labels[i][j]=0;
	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		double calc, one, two, three;

		const int k = 11;
		const int k2 = k/2;
		double coeff[k][k];
		double sigma = 5.0;
		const int NORM = 512;

		for (int di=0; di<k; ++di)
		for (int dj=0; dj<k; ++dj)
		{
			one = -(1/(3.14*sigma*sigma*sigma*sigma));
			two = 1-((((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			three = exp(-(((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			if (di == 0 || dj == 0 || di == 10 || dj == 10 || ((di>2 && dj>2 && di<8 && dj<8))) coeff[di][dj] = one*two*three*NORM;
			else coeff[di][dj] = (-1)*one*two*three*NORM;
		}

		for(int i=k; i<iHeight-k; ++i)
		for(int j=k; j<iWidth-k; ++j)
		{
			for (int di=0; di<k;++di)
			for (int dj=0; dj<k;++dj)
			{
				calc += pImg[(i+dj)*iWidth+j+di]*coeff[di][dj];
			}
			if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			labels[i+1][j+1] = calc;
		}
		for(int i=1; i<iHeight; ++i)
		for(int j=1; j<iWidth; ++j)
		{
			pImg[i*iWidth+j] = labels[i][j];
		}
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth*3+j*3]   = 0;      //B
			pImg[i*iWidth*3+j*3+1] = 0;      //G
			pImg[i*iWidth*3+j*3+2] = 0;      //R 
		}
	}

	////redraw the screen
	OnDraw(GetDC());
}

void CKingimageView::OnAssignment2Cannyedge(){}
void CKingimageView::OnAssignment2Zero(){}

void CKingimageView::OnZeroMask1()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);

	for (int i=0; i<1000;++i)
	for (int j=0; j<10000;++j)
		labels[i][j]=0;
	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		double calc, one, two, three, temp = 0;

		const int k = 7;
		const int k2 = k/2;
		double coeff[k][k];
		double sigma = 1.4;
		const int NORM = 3000;

		for (int di=0; di<k; ++di)
		for (int dj=0; dj<k; ++dj)
		{
			one = -(1/(3.14*sigma*sigma*sigma*sigma));
			two = 1-((((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			three = exp(-(((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			coeff[di][dj] = one*two*three*NORM;
		}

		for(int i=k; i<iHeight-k; ++i)
		for(int j=k; j<iWidth-k; ++j)
		{
			for (int di=0; di<k;++di)
			for (int dj=0; dj<k;++dj)
			{
				calc += pImg[(i+di)*iWidth+j+dj]*coeff[dj][di];
			}
			if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			if (calc > 0 && temp < 0) calc = 255;
			else if (calc < 0 && temp > 0) calc = 0;
			else if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			temp = calc;
			labels[i+1][j+1] = calc;
		}
		for(int i=1; i<iHeight; ++i)
		for(int j=1; j<iWidth; ++j)
		{
			pImg[i*iWidth+j] = labels[i][j];
		}
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth*3+j*3]   = 0;      //B
			pImg[i*iWidth*3+j*3+1] = 0;      //G
			pImg[i*iWidth*3+j*3+2] = 0;      //R 
		}
	}

	////redraw the screen
	OnDraw(GetDC());
}

void CKingimageView::OnZeroMask211()
{
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	for (int i=0; i<1000;++i)
	for (int j=0; j<10000;++j)
		labels[i][j]=0;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		double calc, one, two, three, temp = 0;

		const int k = 11;
		const int k2 = k/2;
		double coeff[k][k];
		double sigma = 5.0;
		const int NORM = 100000;

		for (int di=0; di<k; ++di)
		for (int dj=0; dj<k; ++dj)
		{
			one = -(1/(3.14*sigma*sigma*sigma*sigma));
			two = 1-((((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			three = exp(-(((di-k2)*(di-k2))+((dj-k2)*(dj-k2)))/(2*sigma*sigma));
			if (di == 0 || dj == 0 || di == 10 || dj == 10 || ((di>2 && dj>2 && di<8 && dj<8))) coeff[di][dj] = one*two*three*NORM;
			else coeff[di][dj] = (-1)*one*two*three*NORM;
		}
		
		for(int i=k; i<iHeight-k; ++i)
		for(int j=k; j<iWidth-k; ++j)
		{
			for (int di=0; di<k;++di)
			for (int dj=0; dj<k;++dj)
			{
				calc += pImg[(i+di)*iWidth+j+dj]*coeff[di][dj];
			}
			if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			if (calc > 0 && temp < 0) calc = 255;
			else if (calc < 0 && temp > 0) calc = 0;
			else if (calc > 255) calc = 255;
			else if (calc < 0) calc = 0;
			temp = calc;
			labels[i+1][j+1] = calc;
		}
		for(int i=1; i<iHeight; ++i)
		for(int j=1; j<iWidth; ++j)
		{
			pImg[i*iWidth+j] = labels[i][j];
		}
	}

    if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
            pImg[i*iWidth*3+j*3]   = 0;      //B
			pImg[i*iWidth*3+j*3+1] = 0;      //G
			pImg[i*iWidth*3+j*3+2] = 0;      //R 
		}
	}

	////redraw the screen
	OnDraw(GetDC());
}
