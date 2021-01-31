/**
 * \file Aquarium.h
 *
 * \author Ankit Luthra
 *
 * class that contains all the information about aquarium.
 *
 * This class contains all the elements required to build the aquarium.
 */

#pragma once

#include<memory>
#include<vector>

class CItem;

/**
 * Class that represents an aquarium
 *
 * Holds the collection of items in the aquarium.
 */
class CAquarium
{
public:
	CAquarium();
	virtual ~CAquarium();

	/** Draws the aquarium*/
	void OnDraw(Gdiplus::Graphics *graphics);
	
	/**Adds an item in aquarium */
	void Add(std::shared_ptr<CItem> item);
	
	/** Hit test to check where the location of mouse clicked*/
	std::shared_ptr<CItem> HitTest(int x, int y);
	
	/** Move the item to the back*/
	void moveItemBack(std::shared_ptr<CItem> item);
	
	/** Checks if the mouse loation is over trash can */
	bool CAquarium::IsOverTrashcan(int x, int y);
	
	/** Set the trashcan status*/
	void CAquarium::SetTrashcanActive(bool status);
	
	/** Get the trashcan status*/
	bool CAquarium::GetTrashcanActive();
	
	/** Delete an item over trashcan*/
	void DeleteItem(std::shared_ptr<CItem> item);

private:
	/// Background image to use
	std::unique_ptr<Gdiplus::Bitmap> mBackground;

	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Trash can image
	std::unique_ptr<Gdiplus::Bitmap> mTrashcan;

	/// Trashcan Status
	bool mTrashcanActive = false;

	/// Trashcan X location
	int mTrashcanX = 0;

	/// Trashcan Y location
	int mTrashcanY = 0;
};

