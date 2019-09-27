
// pendrView.cpp: CpendrView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "pendr.h"
#endif

#include "pendrDoc.h"
#include "pendrView.h"
#include "CLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpendrView

IMPLEMENT_DYNCREATE(CpendrView, CView)

BEGIN_MESSAGE_MAP(CpendrView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SEL_COLORSELECTION, &CpendrView::OnSelColorselection)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CpendrView 생성/소멸

CpendrView::CpendrView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CpendrView::~CpendrView()
{
}

BOOL CpendrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CpendrView 그리기
COLORREF col;
void CpendrView::OnDraw(CDC* pDC)
{
	CpendrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int n = pDoc->m_oa.GetSize();
	CLine* p;
	for (int i = 0; i < n; i++) {
		p = (CLine*)pDoc->m_oa[i];
		p->Draw(pDC);
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CpendrView 인쇄

BOOL CpendrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CpendrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CpendrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CpendrView 진단

#ifdef _DEBUG
void CpendrView::AssertValid() const
{
	CView::AssertValid();
}

void CpendrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpendrDoc* CpendrView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpendrDoc)));
	return (CpendrDoc*)m_pDocument;
}
#endif //_DEBUG


// CpendrView 메시지 처리기


void CpendrView::OnSelColorselection()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		col = dlg.GetColor();
	}
		
}

CPoint pnt;
void CpendrView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON) {
		CLine* p = new CLine(pnt, point, col);
		GetDocument()->m_oa.Add(p);
		Invalidate(0);
	}
	pnt = point;

	

	CView::OnMouseMove(nFlags, point);
}
