// kingimageView.cpp : implementation of the CKingimageView class
//

#include "stdafx.h"
#include "kingimage.h"
#include "kingimageDoc.h"
#include "kingimageView.h"
#include <string.h>
#define UNICODE
#include <windows.h>
#include <iostream>

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
	ON_COMMAND(ID_Adjustments, &CKingimageView::OnAdjustments)
	ON_COMMAND(ID_CCL, &CKingimageView::OnCcl)
	ON_COMMAND(ID_THRESHOLD, &CKingimageView::OnThreshold)
	ON_COMMAND(ID_ADJUSTMENTS_MOREBRIGHTNESS, &CKingimageView::OnAdjustmentsMorebrightness)
	ON_COMMAND(ID_ADJUSTMENTS_LESSBRIGHTNESS, &CKingimageView::OnAdjustmentsLessbrightness)
	ON_COMMAND(ID_ADJUSTMENTS_MORECONTRAST, &CKingimageView::OnAdjustmentsMorecontrast)
	ON_COMMAND(ID_ADJUSTMENTS_LESSCONTRAS, &CKingimageView::OnAdjustmentsLesscontras)
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
	double picture[256];
	double pic2[256];
	int size;
	int sum;
void CKingimageView::OnProcess()
{
    CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);
	size = iWidth * iHeight;
	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		for (int i=0; i<256; i++) { picture[i] = 0; pic2[i] = 0; }

		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)	picture[pImg[i*iWidth+j]]++;
		}
		
		for (int i=0;i<256;i++) pic2[i] = picture[i]/(double)size;

		picture[0] = pic2[0];

		for(int i=1; i<256; i++) picture[i] = picture[i-1] + pic2[i];

		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)
			{
				if (255*picture[pImg[i*iWidth+j]] > 255) pImg[i*iWidth+j] = 255;
				else if (255*picture[pImg[i*iWidth+j]] < 0) pImg[i*iWidth+j] = 0;
				else {
					pImg[i*iWidth+j] = (255*picture[pImg[i*iWidth+j]]);	 
				}
			}
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


void CKingimageView::OnAdjustments(){}
	int labels[1000][1000];
void CKingimageView::OnCcl()
{
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if (iWidth%4 != 0) iWidth = iWidth + (iWidth%4);

	int counter = 1;

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		OnThreshold();

		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)
			{
				if (pImg[i*iWidth+j] == 255)
				{
					if(pImg[i*iWidth+j-1] == 255) labels[i][j] = labels[i][j-1];
					else if (pImg[i*iWidth+j-1] == pImg[(i-1)*iWidth+j] && labels[i][j-1] != labels[i-1][j])
					{
						labels[i][j] = min(labels[i][j-1], labels[i-1][j]);
						labels[i][j-1] = labels[i][j];
						labels[i-1][j] = labels[i][j];
					}
					else if (pImg[i*iWidth+j-1] != 255 && pImg[(i-1)*iWidth+j] == 255) labels[i][j] = labels[i-1][j];
					else if (pImg[i*iWidth+j-1] != pImg[(i-1)*iWidth+j]) { counter++; labels[i][j] = counter; }
				}
			}
		}
		int keeper = 255/counter;
		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)
			{
				if (labels[i][j] > 0)
				{
					if (labels[i][j]*keeper > 20 && labels[i][j]*keeper < 255)
						pImg[i*iWidth+j] = labels[i][j]*keeper;
					else
						pImg[i*iWidth+j] = labels[i][j]*100;
				}
			}
		}
	}

	////redraw the screen
	OnDraw(GetDC());
}

void CKingimageView::Onany(){}
void CKingimageView::OnThreshold()
{
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	size = iWidth * iHeight;

	for(int i=0; i<iHeight; i++)
	{
		for(int j=0; j<iWidth; j++)
		{
			sum += pImg[i*iWidth+j];
		}
	}

	int average = sum/size;
	if (average > 255) average = 255;

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)
			{
				if (pImg[i*iWidth+j] < average) {
					pImg[i*iWidth+j] = 0;
				}
				else {
					pImg[i*iWidth+j] = 255;
					labels[i][j] = 1;
				}
			}
		}
	}
	CString str;
	str.Format(_T("%d"), average);
	MessageBox(str, "Threshold T value", MB_OK);
	////redraw the screen
	OnDraw(GetDC());
}

void CKingimageView::OnAdjustmentsMorebrightness()
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{

		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)
			{
				if ((pImg[i*iWidth+j]+10) > 255) pImg[i*iWidth+j] = 255;
				else if ((pImg[i*iWidth+j] + 10) < 0) pImg[i*iWidth+j] = 0;
				else {
					pImg[i*iWidth+j] = pImg[i*iWidth+j] + 10; 
				}
			}
		}
		int contrast = 10;
		int factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
		
		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)
			{
				if ((factor * (pImg[i*iWidth+j] - 128) + 128) > 255) pImg[i*iWidth+j] = 255;
				else if ((factor * (pImg[i*iWidth+j] - 128) + 128) < 0) pImg[i*iWidth+j] = 0;
				else {
					pImg[i*iWidth+j] = (factor * (pImg[i*iWidth+j] - 128) + 128);
				}
			}
		}
	}
	

	////redraw the screen
	OnDraw(GetDC());
}


void CKingimageView::OnAdjustmentsLessbrightness()
{
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
    int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
    BYTE *pImg = pDoc->_bmp->point;

	if(iBitPerPixel == 8)  ////Grey scale 8 bits image
	{

		for(int i=0; i<iHeight; i++)
		{
			for(int j=0; j<iWidth; j++)
			{
				if ((pImg[i*iWidth+j]-10) > 255) pImg[i*iWidth+j] = 255;
				else if ((pImg[i*iWidth+j] - 10) < 0) pImg[i*iWidth+j] = 0;
				else {
					pImg[i*iWidth+j] = pImg[i*iWidth+j] - 10; 
				}
			}
		}
		
	}
	////redraw the screen
	OnDraw(GetDC());
}
void CKingimageView::OnAdjustmentsLesscontras(){}
void CKingimageView::OnAdjustmentsMorecontrast(){}