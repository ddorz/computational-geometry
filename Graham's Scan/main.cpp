//
//  main.cpp
//  COT4521 - Homework 3
//
//  Created by Dave Dorzback
//  Copyright © 2017 Dave Dorzback. All rights reserved.
//

#include "Grahams.hpp"
#include <iostream>
#include <utility>

#define NUM_POINTS 9

int main(int argc, const char * argv[]) {
    
#if 0   /* Hardcoded points */
    // Points in set
    std::pair<int,int> points[] {{1, 0}, {0, 0}, {1, 2}, {4, 2}, {1, 1}, {2, 2}, {4, 3}, {3, 3}, {4, 4}};
    
    // Get convex hull
    Grahams newg(points, NUM_POINTS);
    
#else   /* User entered points */
    
    // Get number of points in set
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;
    
    // Create vector of points
    std::vector<std::pair<int, int>> points(n);
    
    // Input each point from user
    int x, y;
    for (auto i : points) {
        std::cout << "Enter point (x, y): ";
        std::cin >> x >> y;
        points.push_back(std::pair<int, int>({x, y}));
    }
    
    // Get convex hull
    Grahams newg(points);
#endif
    
    // Print convex hull
    newg.print_convex_hull();
}
