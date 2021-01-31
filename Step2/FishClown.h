/**
* \file FishClown.h
*
* \author Ankit Luthra
*
* Class the implements a Clown fish
*
* This is the class that draws and implements the clown fish.
*/

#pragma once

#include <memory>

#include "Item.h"


/**
* Implements a Clown fish
*/
class CFishClown : public CItem
{
public:
	/** CFishClown Constructor */
	CFishClown(CAquarium *aquarium);

	/// Default constructor (disabled)
	CFishClown() = delete;

	/// Copy constructor (disabled)
	CFishClown(const CFishClown &) = delete;

	/** Performs hit test to check where mouse is clicked
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on 
	*/
	bool HitTest(int x, int y);

	/** Draws an item */
	virtual void Draw(Gdiplus::Graphics *graphics);

	/** clown fish destructor */
	~CFishClown();

private:
	/// uique pointer pointing to the fish image
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};
