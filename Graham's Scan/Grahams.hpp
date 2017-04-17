//
//  Grahams.hpp
//  COT4521 - Homework 3
//
//  Created by Dave Dorzback
//  Copyright © 2017 Dave Dorzback. All rights reserved.
//

#ifndef Grahams_hpp
#define Grahams_hpp

#include <stdio.h>
#include <utility>
#include <vector>
#include <stack>

// Defintion of point for 2D coordinate system
typedef std::pair<int, int> point;

/*
 * Convex Hull Finder - Find/prints the convex hull for a given set of 2d points
 */
class Grahams {
    
    friend int cmp(const void *x, const void *y);
    
    public:
        Grahams(std::vector<point> init);
        Grahams(point *init, size_t n);
    
        ~Grahams();
    
        void print_convex_hull(void);
    
    private:
        point second_to_top(void);
    
        point *points;
        std::stack<point> s;
        size_t n;
        static point p0;
};

#endif /* Grahams_hpp */
