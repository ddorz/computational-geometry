//
//  quickhull.cpp
//  Quickhull
//
//  Created by Dave Dorzback on 4/9/17.
//  Copyright © 2017 Dave Dorzback. All rights reserved.
//

#include "quickhull.hpp"
#include <algorithm>
#include <stdlib.h>
#include <iostream>

/*
 * Destructor
 */
quickhull::~quickhull(void) {
    points.clear();
    convex_hull.clear();
}

/*
 * Assignment operator
 */
quickhull& quickhull::operator=(quickhull const &other_qh) {
    points.clear();
    convex_hull.clear();
    std::copy(other_qh.points.begin(), other_qh.points.end(), points.begin());
    std::copy(other_qh.convex_hull.begin(), other_qh.convex_hull.end(), convex_hull.begin());
    return *this;
}

/*
 * orientation - Finds the orientation of point s relative to the line formed by points p & q
 */
int quickhull::orientation(point p, point q, point s) {
    int ret {(q.first - p.first) * (s.second - p.second) - (q.second - p.second) * (s.first - p.first)};
    return ret == 0 ? 0 : ret > 0 ? 1 : -1;
    
}

/*
 * distance - Find the distance of point s from the line formed by points p & q
 */
int quickhull::distance(point p, point q, point s) {
    int ret {(q.first - p.first) * (p.second - s.second) - (q.second - p.second) * (p.first - s.first)};
    return abs(ret);
}

/*
 * find_hull - Finds points on convex hull from the set of points 'set'
 */
void quickhull::find_hull(point p, point q, std::vector<point> &set) {
    
    // Return if set is empty
    if (set.empty()) {
        return;
    }
    
    // Find insertion point in convex hull
    auto insertion_iter {std::find(convex_hull.begin(), convex_hull.end(), q)};
    
    auto max_p    {set.begin()};
    auto max_dist {INT_MIN};
    
    // Find point on side of line with max distance from line
    for (auto it {set.begin()}; it != set.end(); ++it) {
        auto dist {distance(p, q, *it)};
        max_p = dist > max_dist ? it : max_p;
        max_dist  = std::max(dist, max_dist);
    }
    
    // Insert point into convex hull and remove from set
    point s {*max_p};
    convex_hull.insert(insertion_iter, s);
    set.erase(max_p);
    
    std::vector<point> pleft;
    std::vector<point> qleft;
    
    // Determine points to the left of line formed by point p and s and line formed by q and s
    for (const auto &i : set) {
        if (orientation(p, s, i) == 1) {
            pleft.push_back(i);
        }
        if (orientation(s, q, i) == 1) {
            qleft.push_back(i);
        }
    }
    
    // Repeat recursively
    find_hull(p, s, pleft);
    find_hull(s, q, qleft);
}

/*
 * get_convex_hull - Finds the convex hull from the set 'points' of n points
 */
void quickhull::get_convex_hull(void) {
    
    if (points.size() < 3) {
        std::copy(points.begin(), points.end(), convex_hull.begin());
        return;
    }
    
    auto min_iter {points.begin()}, max_iter {points.begin()};
    auto min_x    {INT_MAX},        max_x    {INT_MIN};
    
    // Find points with minimum and maximum x coordinates - always part of convex hull
    for (auto it {points.begin()}; it != points.end(); ++it) {
        min_iter = it->first < min_x ? it : min_iter;
        min_x = std::min(it->first, min_x);
        max_iter = it->first > max_x ? it : max_iter;
        max_x = std::max(it->first, max_x);
    }
    
    point p {*min_iter}, q {*max_iter};
    
    // Add the min/max points to convex hull and remove them from 'points' set
    convex_hull.push_back(p);
    convex_hull.push_back(q);
    points.erase(min_iter);
    points.erase(max_iter);
    
    std::vector<point> left;
    std::vector<point> right;
    
    // Use line formed by p & q to build two subsets of points, left / right points
    for (const auto &i : points) {
        if (orientation(p, q, i) == 1) {
            right.push_back(i);
        } else if (orientation(p, q, i) == -1) {
            left.push_back(i);
        }
    }
    
    // Call find hull with each set of points
    find_hull(p, q, right);
    find_hull(q, p, left);
}

/*
 * print_convex_hull - Prints the convex hull of set of points 'points'
 */
void quickhull::print_convex_hull(void) {
    
    if (convex_hull.empty()) {
        std::cout << "Error: no convex hull to print.\n";
    }
    
    std::cout << "{ ";
    for (const auto &i : convex_hull) {
        std::cout << "{" << i.first << ", " << i.second << "}, ";
    }
    std::cout << " }\n";
}
