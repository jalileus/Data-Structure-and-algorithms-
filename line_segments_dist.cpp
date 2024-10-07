/*
Time limit	1 second
Memory limit	64.0 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem :
Ivan fall asleep and he dreamed of the planet Pandora, where 2 river flows. These rivers are quite unusual for earth: they flow strictly from one point to another point directly in space 
(since in Ivan’s dream the planet is not round at all).Ivan decided that he wanted to dig a tunnel between the rivers. Since he is lazy, 
he doesn’t want to dig much. Help Ivan find out how much he will have to dig.

Input format
Four lines specify the integer coordinates of the beginning and end of the rivers. Modulo coordinates do not exceed 1000.

Output format
Print a value with 6 decimal places of accuracy

Sample
Input	       Output
0 0 0        0.408248
1 1 1
0 0 1
0 1 0

*/


#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

struct Point {
  double x, y, z;
};

Point subtract(const Point& p1, const Point& p2) {
  return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

Point cross(const Point& p1, const Point& p2) {
  return {p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z,
          p1.x * p2.y - p1.y * p2.x};
}

double dot(const Point& p1, const Point& p2) {
  return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

double length(const Point& p) { return std::sqrt(dot(p, p)); }

double distancePointToSegment(const Point& point, const Point& segmentStart,
                              const Point& segmentEnd) {
  Point segmentVector = subtract(segmentEnd, segmentStart);
  Point pointVector = subtract(point, segmentStart);
  double t =
      dot(pointVector, segmentVector) / dot(segmentVector, segmentVector);
  t = std::max(0.0, std::min(1.0, t));
  Point closestPoint = {segmentStart.x + t * segmentVector.x,
                        segmentStart.y + t * segmentVector.y,
                        segmentStart.z + t * segmentVector.z};
  return length(subtract(point, closestPoint));
}

double segmentToSegmentDistance(const Point& seg1Start, const Point& seg1End,
                                const Point& seg2Start, const Point& seg2End) {
  Point vector_1 = subtract(seg1End, seg1Start);
  Point vector_2 = subtract(seg2End, seg2Start);
  Point vector_3 = subtract(seg1Start, seg2Start);

  double a = dot(vector_1, vector_1);
  double b = dot(vector_1, vector_2);
  double c = dot(vector_2, vector_2);
  double d = dot(vector_1, vector_3);
  double e = dot(vector_2, vector_3);
  double determinant = a * c - b * b;

  double parameter_s, s_num, s_denom = determinant;
  double parameter_c, t_num, t_denom = determinant;

  if (determinant < 1e-8) {
    s_num = 0.0;
    s_denom = 1.0;
    t_num = e;
    t_denom = c;
  } else {
    s_num = (b * e - c * d);
    t_num = (a * e - b * d);

    if (s_num < 0.0) {
      s_num = 0.0;
      t_num = e;
      t_denom = c;
    } else if (s_num > s_denom) {
      s_num = s_denom;
      t_num = e + b;
      t_denom = c;
    }
  }

  if (t_num < 0.0) {
    t_num = 0.0;
    if (-d < 0.0)
      s_num = 0.0;
    else if (-d > a)
      s_num = s_denom;
    else {
      s_num = -d;
      s_denom = a;
    }
  } else if (t_num > t_denom) {
    t_num = t_denom;
    if ((-d + b) < 0.0)
      s_num = 0.0;
    else if ((-d + b) > a)
      s_num = s_denom;
    else {
      s_num = (-d + b);
      s_denom = a;
    }
  }

  parameter_s = (std::abs(s_num) < 1e-8 ? 0.0 : s_num / s_denom);
  parameter_c = (std::abs(t_num) < 1e-8 ? 0.0 : t_num / t_denom);

  Point difference = {
      vector_3.x + (parameter_s * vector_1.x) - (parameter_c * vector_2.x),
      vector_3.y + (parameter_s * vector_1.y) - (parameter_c * vector_2.y),
      vector_3.z + (parameter_s * vector_1.z) - (parameter_c * vector_2.z)};

  return length(difference);
}

int main() {
  Point first_segment_start, first_segment_end, second_segment_start,
      second_segment_end;

  std::cin >> first_segment_start.x >> first_segment_start.y >>
      first_segment_start.z;
  std::cin >> first_segment_end.x >> first_segment_end.y >> first_segment_end.z;
  std::cin >> second_segment_start.x >> second_segment_start.y >>
      second_segment_start.z;
  std::cin >> second_segment_end.x >> second_segment_end.y >>
      second_segment_end.z;

  double result =
      segmentToSegmentDistance(first_segment_start, first_segment_end,
                               second_segment_start, second_segment_end);

  std::cout << std::fixed << std::setprecision(6) << result << std::endl;

  return 0;
}
