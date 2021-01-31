/**
* \file ChildView.cpp
*
* \author Ankit Luthra
*/


// ChildView.cpp : implementation of the CChildView class

#include "stdafx.h"
#include "Step2.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishClown.h"
#include "FishNemo.h"
#include "Aquarium.h"

#include "DoubleBufferDC.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace Gdiplus;
using namespace std;


/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/**
* Constructor
*/
CChildView::CChildView()
{
}

/**
* Destructor
*/
CChildView::~CChildView()
{
}

/// \cond
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_COMMAND(ID_ADDFISH_CLOWNFISH, &CChildView::OnAddfishClownfish)
	ON_COMMAND(ID_ADDFISH_NEMO, &CChildView::OnAddfishNemo)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_TRASHCAN, &CChildView::OnViewTrashcan)
END_MESSAGE_MAP()
/// \endcond

// CChildView message handlers

/** This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/** This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint()
{
	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	mAquarium.OnDraw(&graphics);
}


/**
 * Add Fish/Beta menu option handler
 */
void CChildView::OnAddfishBetafish()
{
	auto fish = make_shared<CFishBeta>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
* Add Fish/Clown menu option handler
*/
void CChildView::OnAddfishClownfish()
{
	auto fish = make_shared<CFishClown>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
* Add Fish/Nemo menu option handler
*/

void CChildView::OnAddfishNemo()
{
	auto fish = make_shared<CFishNemo>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/** Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		// We have selected an item
		// Move it to the end of the list of items
		mAquarium.moveItemBack(mGrabbedItem);
	}
}


/** Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}


/** Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x, point.y);
		}
		else
		{
			// When the left button is released, we release the item.
			if (mAquarium.IsOverTrashcan(point.x, point.y))
			{
				mAquarium.DeleteItem(mGrabbedItem);
			}
			
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}

/**
* Erase the background
*
* This is disabled to eliminate flicker
* \param pDC Device context
* \returns FALSE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}



/**
* Handles the visibility of the trash can
*/
void CChildView::OnViewTrashcan()
{
	// TODO: Add your command handler code here
	if (mAquarium.GetTrashcanActive() == true)
	{
		mAquarium.SetTrashcanActive(false);
		Invalidate();
	}
	else
	{
		mAquarium.SetTrashcanActive(true);
		Invalidate();
	}
}