/*
Time limit	1 second
Memory limit	64.0 MB
Input	stdin or input.txt
Output	stdout or output.txt
Ivan fell asleep and dreamed of the planet Pandora, where he was fighting aliens. 
Ivan and some of his allies created a safe zone inside a fortress, its walls forming a strict boundary. Unfortunately, 
Ivan couldn't contact any of his allies, and he wasn't sure if all of them were inside the fortress or not. However, he knew the location of all his allies.

Your task is to check whether all of Ivan's allies are positioned strictly inside the fortress. This means that any ally should be strictly inside the fortress. 
"Strictly" means that an ally cannot lie on the side of the fortress. 
Ivan built the fortress as a strictly convex polygon, and all coordinates of the allies create an arbitrary polygon without any self-intersections or self-touches. 
The coordinates of both figures are given in clockwise order. No three consecutive allies or coordinates of the fortress are located on the same straight line.

Input format
The first line contains the only integer ( n ) - the number of vertices of the fortress. Then ( n ) lines contain pairs of integers - coordinates of each vertex (coordinates can vary from (-10^9) to (10^9)). 
The vertices are given in clockwise order.

The next line contains a single integer ( m ) - the number of allies. Then the following ( m ) lines contain pairs of integers - coordinates of each ally (coordinates can vary from (-10^9) to (10^9)). 
The allies are given in clockwise order.

Output format
Print on the only line the answer to the problem — if all allies are strictly inside fortress, print "YES", otherwise print "NO"

Sample:
Input:
5
1 2
4 2
3 -3
-2 -2
-2 1
4
0 1
1 2
4 1
2 -1
Output:
NO
*/

#include <algorithm>
#include <iostream>
#include <vector>

using Point = std::pair<long long, long long>;

bool PointsCheck(const Point& p1, const Point& p2) {
  if (p1.first == p2.first) {
    return p1.second < p2.second;
  }
  return p1.first < p2.first;
}

bool ClockWise(const Point& p1, const Point& p2, const Point& p3) {
  return (p1.first * (p2.second - p3.second) +
          p2.first * (p3.second - p1.second) +
          p3.first * (p1.second - p2.second)) < 0LL;
}

bool CounterClockWise(const Point& p1, const Point& p2, const Point& p3) {
  return (p1.first * (p2.second - p3.second) +
          p2.first * (p3.second - p1.second) +
          p3.first * (p1.second - p2.second)) > 0LL;
}

std::vector<Point> MonotoneChainAlgo(std::vector<Point>& pts) {
  std::sort(pts.begin(), pts.end(), PointsCheck);
  if (pts.size() <= 3) {
    return pts;
  }
  std::vector<Point> upper_hull, lower_hull;
  Point left = pts.front();
  Point right = pts.back();

  upper_hull.push_back(left);
  lower_hull.push_back(left);

  for (size_t i = 1; i < pts.size(); i++) {
    if (i == pts.size() - 1 || !CounterClockWise(left, pts[i], right)) {
      while (upper_hull.size() > 1 &&
             CounterClockWise(upper_hull[upper_hull.size() - 2],
                              upper_hull.back(), pts[i])) {
        upper_hull.pop_back();
      }
      upper_hull.push_back(pts[i]);
    }
    if (i == pts.size() - 1 || !ClockWise(left, pts[i], right)) {
      while (lower_hull.size() > 1 &&
             ClockWise(lower_hull[lower_hull.size() - 2], lower_hull.back(),
                       pts[i])) {
        lower_hull.pop_back();
      }
      lower_hull.push_back(pts[i]);
    }
  }

  for (size_t i = lower_hull.size() - 2; i > 0; i--) {
    upper_hull.push_back(lower_hull[i]);
  }
  upper_hull.resize(std::unique(upper_hull.begin(), upper_hull.end()) -
                    upper_hull.begin());
  return upper_hull;
}

bool InnerPoint(std::vector<Point> hull, Point p) {
  hull.push_back(p);
  hull = MonotoneChainAlgo(hull);
  for (const auto& point : hull) {
    if (point == p) {
      return false;
    }
  }
  return true;
}

bool PolygonInside(std::vector<Point> hull) {
  long long pts_num;
  std::cin >> pts_num;
  Point pts;
  for (long long i = 0; i < pts_num; ++i) {
    std::cin >> pts.first >> pts.second;
    if (!InnerPoint(hull, pts)) {
      return false;
    }
  }
  return true;
}

std::vector<Point> InitializeVector(long long n) {
  std::vector<Point> vec(n);
  for (long long i = 0; i < n; i++) {
    std::cin >> vec[i].first >> vec[i].second;
  }
  return vec;
}

int main() {
  long long num_pts;
  std::cin >> num_pts;
  std::vector<Point> pts = InitializeVector(num_pts);
  bool res = PolygonInside(pts);
  std::cout << (res ? "YES" : "NO") << std::endl;
  return 0;
}
