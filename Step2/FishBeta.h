/**
* \file FishBeta.h
*
* \author Ankit Luthra
*
* Class the implements a Beta fish.
*
* This is the class that draws and implements the beta fish.
*/

#pragma once

#include <memory>
#include "Item.h"

/**
* Implements a Beta fish
*/
class CFishBeta : public CItem
{
public:
	/** CFishBeta Constructor */
	CFishBeta(CAquarium *aquarium);

	/// Default constructor (disabled)
	CFishBeta() = delete;

	/// Copy constructor (disabled)
	CFishBeta(const CFishBeta &) = delete;

	/** Performs hit test to check where mouse is clicked 
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on 
	*/
	bool HitTest(int, int);

	/** Draws an item */
	virtual void Draw(Gdiplus::Graphics *graphics);

	/** Beta fish destructor */
	~CFishBeta();

private:

	/// uique pointer pointing to the fish image
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};
