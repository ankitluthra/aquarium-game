/**
* \file Aquarium.cpp
*
* \author Ankit Luthra
*/

#include "stdafx.h"
#include <memory>

#include "Aquarium.h"
#include "resource.h"
#include "FishBeta.h"

using namespace std;
using namespace Gdiplus;

/// Defines TrashCanWidth as a constant
const int TrashCanWidth = 51;

/// Defines TrashCanHeight as a constant
const int TrashCanHeight = 70;

/// Mrgin to right and below trash can.
const int TrashCanMargin = 50;

/**
 * Constructor
 */
CAquarium::CAquarium()
{
	// gets the background image from the file
	mBackground = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/background1.png"));
	if (mBackground->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/background1.png");
	}

	// gets the trashcan image from the file
	mTrashcan = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/trashcan.png"));
	if (mTrashcan->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/trashcan.png");
	}

	// trashcan status: false
	mTrashcanActive = false;

}

/**
 * Destructor
 */
CAquarium::~CAquarium()
{
}

/** Draw the aquarium
 * \param graphics The GDI+ graphics context to draw on
 */
void CAquarium::OnDraw(Gdiplus::Graphics *graphics)
{
	graphics->DrawImage(mBackground.get(), 0, 0,
		mBackground->GetWidth(), mBackground->GetHeight());

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	SolidBrush green(Color(0, 64, 0));
	graphics->DrawString(L"Under the Sea!", -1, &font, PointF(2, 2), &green);

	// for loop to draw the items
	for (auto item : mItems)
	{
		item->Draw(graphics);
	}

	// calculating the X and Y location and drawing the trashcan at its position.
	if (mTrashcanActive)
	{
		mTrashcanX = mBackground->GetWidth() - mTrashcan->GetWidth() - TrashCanMargin;
		mTrashcanY = mBackground->GetHeight() - mTrashcan->GetHeight() - TrashCanMargin;
		graphics->DrawImage(mTrashcan.get(), mTrashcanX, mTrashcanY, mTrashcan->GetWidth(), mTrashcan->GetHeight());
	}
}

/**
 * Add an item to the aquarium
 * \param item New item to add
 */
void CAquarium::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/** Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * \param x X location
 * \param y Y location
 * \returns Pointer to item we clicked on or nullptr if none.
 */
shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}

/**
 * Send item to the back after move
 * \param item item to be sent
 */
void CAquarium::moveItemBack(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}

/**
 * Checks if the mouse is over trashcan
 *
 * \param x Mouse position X
 * \param y Mouse position Y
 *
 * \returns True if mouse is over trashcan
 */
bool CAquarium::IsOverTrashcan(int x, int y)
{
	if (!mTrashcanActive)
	{
		return false;
	}

	return x >= mTrashcanX && x < mTrashcanX + (int)mTrashcan->GetWidth() &&
		y >= mTrashcanY && y < mTrashcanY + (int)mTrashcan->GetHeight();
}

/**
 * Set status to member mTrashcanActive
 *
 * \param status to be set for mTrashcanActive
 */
void CAquarium::SetTrashcanActive(bool status){
	mTrashcanActive = status;
}

/**
 * Get the status to member mTrashcanActive
 *
 * \returns true or false in mTrashcanActive
 */
bool CAquarium::GetTrashcanActive(){
	return mTrashcanActive;
}

/**
 * Deletes an Item from the aquarium
 *
 * \param item to be deleted
 */
void CAquarium::DeleteItem(std::shared_ptr<CItem> item){
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
	}
}