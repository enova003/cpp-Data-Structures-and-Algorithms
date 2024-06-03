#ifndef STARFIELD_H
#define STARFIELD_H

#include <unordered_set>
#include "point.h"
#include <set>
#include <functional>

//*** Declare a hash function for Points
class pointHasher{
	public:
		std::size_t operator() (const Point& p) const
		{
			std::hash<int> int_hash;
			return (std::size_t)int_hash(p.x) ^ (std::size_t)int_hash(p.y);
		}
};

/**
 * @brief A photograph of stars against the night sky.
 * 
 * A star field is denoted by a collection of Points that are lit or dark.
 * It is expected that the vast majority of points will be dark.
 * 
 */
class StarField
{
public:
	const static int MAX_COORD = 1000000; // x & y values are limited to 0..MAX_COORD

	struct Statistics {
		int nLitPoints; // number of points that are lit
		int xMin;       // smallest x value of any lit point
		int xMax;       // largest x value of any lit point
		int yMin;       // smallest y value of any lit point
		int yMax;       // largest value of any lit point
	};

	/**
	 * @brief Construct a new Star Field object with everything dark.
	 * 
	 */
	StarField();


	/**
	 * @brief Toggle a point from dark to light or vice versa.
	 * 
	 * @param p a point with 0 <= x,y <= MAX_COORD
	 */
	void toggle (const Point& p);

	/**
	 * @brief Check to see if a point is lit.
	 * 
	 * @param p a point with 0 <= x,y <= MAX_COORD
	 * @return true iff the point is currently light
	 */
	bool isLight (const Point& p) const;

	/**
	 * @brief Generate a report describing the lit points.
	 * 
	 * @return Stats 
	 */
	Statistics report() const;

private:
	std::unordered_set<Point, pointHasher> points;  //*** Declare points as an unordered set
	friend std::ostream& operator<< (std::ostream& out, const StarField& sf);

public:
	void sanityCheck() const;  // instructor only
};

std::ostream& operator<< (std::ostream& out, const StarField& sf);
std::ostream& operator<< (std::ostream& out, const StarField::Statistics& stats);


#endif


