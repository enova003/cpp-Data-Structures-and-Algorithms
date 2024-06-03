#include "starField.h"
#include <algorithm>

using namespace std;

const int StarField::MAX_COORD; // x & y values are limited to 0..MAX_COORD

StarField::StarField()
{
}

/**
 * @brief Toggle a point from dark to light or vice versa.
 *
 * @param p a point with 0 <= x,y <= MAX_COORD
 */
void StarField::toggle(const Point &p)
{
    //*** Your code here
    if(points.find(p) != points.end()){
        points.erase(p);
    }
    else
    {
        points.insert(p);
    }
}

/**
 * @brief Check to see if a point is lit.
 *
 * @param p a point with 0 <= x,y <= MAX_COORD
 * @return true iff the point is currently light
 */
bool StarField::isLight(const Point &p) const
{
    //*** Your code here
    if(points.find(p) != points.end()){
        return true;
    }
    return false;
}

/**
 * @brief Generate a report describing the lit points.
 *
 * @return Stats
 */
StarField::Statistics StarField::report() const
{
    Statistics stats;
    stats.nLitPoints = 0;
    stats.xMax = 0;
    stats.xMin = MAX_COORD;
    stats.yMax = 0;
    stats.yMin = MAX_COORD;
    stats.nLitPoints = points.size();

    for (const auto &point : points) {
        /* if (isLight(point)) {
            stats.nLitPoints++;
        }

        if (point.x < stats.xMin) {
            stats.xMin = point.x;
        }

        if (point.x > stats.xMax) {
            stats.xMax = point.x;
        }

        if (point.y < stats.yMin) {
            stats.yMin = point.y;
        }

        if (point.y > stats.yMax) {
            stats.yMax = point.y;
        } */

        stats.xMin = min(stats.xMin, point.x);
        stats.xMax = max(stats.xMax, point.x);
        stats.yMin = min(stats.yMin, point.y);
        stats.yMax = max(stats.yMax, point.y);
    }

    return stats;
}

std::ostream& operator<< (std::ostream& out, const StarField& sf)
{
    out << "{";
    bool first = true;
    for (const Point& p: sf.points) {
        if (!first)
            out << ", ";
        first = false;
        out << p;
    }
    out << "}";
    return out;
}

std::ostream& operator<< (std::ostream& out, const StarField::Statistics& stats)
{
    out << "#: " << stats.nLitPoints << "\n";
    out << stats.xMin << " <= x <= " << stats.xMax << "\n";
    out << stats.yMin << " <= y <= " << stats.yMax << "\n";
    return out;
}
