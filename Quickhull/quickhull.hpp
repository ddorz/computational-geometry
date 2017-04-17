//
//  quickhull.hpp
//  Quickhull
//
//  Created by Dave Dorzback on 4/9/17.
//  Copyright © 2017 Dave Dorzback. All rights reserved.
//

#ifndef quickhull_hpp
#define quickhull_hpp

#include <stdio.h>
#include <vector>
#include <utility>

class quickhull {
    
    // Point defintion std::pair<int, int>
    typedef std::pair<int, int> point;
    
    public:
        // Constructors
        quickhull(point *init, size_t n) {std::copy(init, init + n, points.begin());}
        quickhull(std::vector<point> init): points(init) {}
        quickhull(quickhull const &other_qh): points(other_qh.points), convex_hull(other_qh.convex_hull) {}
    
        // Assignment operator
        quickhull& operator=(quickhull const &other_qh);
    
        // Destructor
        ~quickhull();
    
        // Get convex hull of 'points' vector via quickhull
        void get_convex_hull(void);
    
        // Print the points in convex_hull found using get_convex_hull
        void print_convex_hull(void);
    
    private:
        // Vector of points
        std::vector<point> points;
    
        // Vector of points in convex_hull
        std::vector<point> convex_hull;
    
        // Orientation test
        int orientation(point p, point q, point s);
    
        // Distance
        int distance(point p, point q, point s);
    
        // Find hull utility function, finds points on convex hull from 'set'
        void find_hull(point p, point q, std::vector<point> &set);
};
#endif /* quickhull_hpp */

