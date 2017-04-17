//
//  Grahams.cpp
//  COT4521 - Homework 3
//
//  Created by Dave Dorzback
//  Copyright © 2017 Dave Dorzback. All rights reserved.
//

#include "Grahams.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

/*
 * Utility Macros - distance squared and orientation test
 */
#define distance_sq(x, y) pow(x.first - y.first, 2) + pow(x.second - y.second, 2)

#define orientation(p, q, r) ({                                                                             \
    int ret  {(q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second)};   \
    ret == 0 ? ret : ret < 0 ? 2 : 1;                                                                       \
})

/*
 * Static Members - first point
 */
point Grahams::p0 {0, 0};


/*
 * Friend function - Qsort Comparator
 */
int cmp(const void *x, const void *y) {
    
    point *a = const_cast<point *>(reinterpret_cast<const point *>(x));
    point *b = const_cast<point *>(reinterpret_cast<const point *>(y));
    
    int orien {orientation(Grahams::p0, point(*a), point(*b))};
    
    return !orien ? (distance_sq(Grahams::p0, point(*b)) >= distance_sq(Grahams::p0, point(*a)) ? -1 : 1)
            : orien != 1 ? -1 : 1;
}

/*
 * Constructors
 */
Grahams::Grahams(std::vector<point> init) {
    points = new point[n=init.size()];
    std::copy(init.begin(), init.end(), points);
}

Grahams::Grahams(point *init, size_t n) {
    points = new point[this->n=n];
    std::copy(init, init + n, points);
}

/*
 * Destructor
 */
Grahams::~Grahams() {
    delete [] points;
}

/*
 * second_to_top - Get the point second to the top of stack
 */
point Grahams::second_to_top() {
    if (s.size() < 2) {
        return {INT_MAX, INT_MAX};
    }
    point tmp {s.top()};
    s.pop();
    point ret {s.top()};
    s.push(tmp);
    return ret;
}

/*
 * print_convex_hull - Uses incremental approach to find the convex hull and prints it to stdout
 */
void Grahams::print_convex_hull() {
    
    // Get lowest point
    ssize_t min {0};
    
    for (auto i {1}; i < n; ++i) {
        if (points[i].second < points[0].second || (points[0].second == points[i].second && points[i].first < points[min].first)) {
            points[0].second = points[i].second;
            min = i;
        }
    }
    
    // Move to position 0
    std::swap(points[0], points[min]);
    
    // Sort with respect to position 0
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(point), cmp);
    
    // Remove points
    size_t m_idx {1};
    for (auto i {1}; i < n; ++i) {
        while (i < n-1 && orientation(p0, points[i], points[i + 1]) == 0) {
            ++i;
        }
        points[m_idx] = points[i];
        ++m_idx;
    }
    
    // Verify enough points for CH
    if (m_idx < 3) {
        return;
    }
    
    // Push the first 3 points onto stack
    for (auto i {0}; i < 3; ++i) {
        s.push(points[i]);
    }
    
    // Process the remaining points to find CH
    for (auto i {3}; i < m_idx; ++i) {
        while (orientation(second_to_top(), s.top(), points[i]) != 2) {
            s.pop();
        }
        s.push(points[i]);
    }
    
    // Print the CH to stdout
    std::cout << "{ ";
    while (true) {
        point tmp {s.top()};
    
        std::cout << "{" << tmp.first << ", " << tmp.second << "}";
        
        s.pop();
        
        if (s.empty()) {
            std::cout << " }\n";
            break;
        } else std::cout << ", ";
    }
}
