//
//  main.cpp
//  Quickhull
//
//  Created by Dave Dorzback on 4/9/17.
//  Copyright © 2017 Dave Dorzback. All rights reserved.
//

#include "quickhull.hpp"
#include <iostream>


int main(int argc, const char * argv[]) {
#if 1   /* Hardcoded points */
    
    // Points in set
    std::vector<std::pair<int,int>> points({{1, 0}, {0, 0}, {1, 2}, {4, 2}, {1, 1}, {2, 2}, {4, 3}, {3, 3}, {4, 4}});
    
    // Get convex hull
    quickhull qh(points);
    qh.get_convex_hull();
    
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
    quickhull qh(points);
    qh.get_convex_hull();
    
#endif
    
    // Print convex hull
    qh.print_convex_hull();
    return 0;
}
