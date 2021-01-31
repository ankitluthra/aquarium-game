/**
* \file FishNemo.h
*
* \author Ankit Luthra
*
* Class the implements a Nemo fish
*
* This is the class that draws and implements the beta fish.
*/

#pragma once

#include <memory>

#include "Item.h"


/**
* Implements a Nemo fish
*/
class CFishNemo : public CItem
{
public:
	/** CFishNemo Constructor */
	CFishNemo(CAquarium *aquarium);

	/// Default constructor (disabled)
	CFishNemo() = delete;

	/// Copy constructor (disabled)
	CFishNemo(const CFishNemo &) = delete;

	/** Performs hit test to check where mouse is clicked
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on 
	*/
	bool HitTest(int x, int y);

	/** Draws an item */
	virtual void Draw(Gdiplus::Graphics *graphics);

	/** Nemo fish destructor */
	~CFishNemo();

private:
	/// uique pointer pointing to the fish image
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};
