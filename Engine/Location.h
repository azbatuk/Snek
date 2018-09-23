#pragma once

class Location
{
public:
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}
	// Overload == operator to be able to compare two locations
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};