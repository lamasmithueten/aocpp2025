#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <climits>

struct Point{
  long int x,y;
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
};
long int pow( long int base,  long int exponent) {
  long int result = 1;
  for ( long int i = 0; i < exponent; i++)
    result *= base;
  return result;
}

Point findGridSize(std::vector<Point>& tiles){
  Point gridsize = {0,0};
  for (Point pair : tiles){
    if (pair.x>gridsize.x)gridsize.x = pair.x;
    if (pair.y>gridsize.y)gridsize.y = pair.y;
  }
  gridsize.x++;
  gridsize.y++;
  return gridsize;
}

long int rectSize(Point a, Point b){
  return (std::sqrt( pow((a.x - b.x+1), 2) ) * std::sqrt( pow((a.y - b.y+1), 2))) ;
}

 long int findBiggestRectSize(std::vector<std::pair<Point, Point>>& tiles ){
   long int biggest = 0;
  for (unsigned long int i = 0; i<tiles.size(); i++){
    long int current = rectSize(tiles[i].first, tiles[i].second);
    if(current > biggest){ 
      std::cout << "Point 1: X: " << tiles[i].first.x << " Y: " << tiles[i].first.y << "\nPoint 2: X: " << tiles[i].second.x << " Y: " <<tiles[i].second.y << "\n";
      biggest=current;
      std::cout << "Size: " << current <<"\n\n";
    }
  }
  return biggest; 
}

std::pair<Point, Point> getNormalizedPoints(const Point &p1, const Point &p2) {

//    std::cout << "Point 1: X: " << p1.x << " Y: " << p1.y << "\nPoint 2: X: " << p2.x << " Y: " <<p2.y << "\n\n";
    // Determine the top-left and bottom-right corners
    Point topLeft, bottomRight;

    // The top-left corner has the smaller x and y
    topLeft.x = std::min(p1.x, p2.x);
    topLeft.y = std::min(p1.y, p2.y);

    // The bottom-right corner has the larger x and y
    bottomRight.x = std::max(p1.x, p2.x);
    bottomRight.y = std::max(p1.y, p2.y);
//    std::cout << "New Point 1: X: " << topLeft.x << " Y: " << topLeft.y << "\nNew Point 2: X: " << bottomRight.x << " Y: " <<bottomRight.y << "\n\n";

    return {topLeft, bottomRight};
}
/*bool checkPoint(Point a, Point b, Point inBetween, std::vector<Point>& vectorList){
  for (unsigned long int i = 0; i< vectorList.size(); i++){
    for (unsigned long int j = 0 ; j<vectorList.size(); i++){
      if (vectorList[i]== vectorList[j])continue;
      if (vectorList[i].x == vectorList[j].x){
        if(vectorList[i].y<=a.y &&vectorList[j].y<a.y ) return false;
      }
    }
  }
  for (unsigned long int i = 0; i< vectorList.size(); i++){
    for (unsigned long int j = 0; j<vectorList.size(); i++){
      if (vectorList[i]== vectorList[j])continue;
      if (vectorList[i].y == vectorList[j].y){
        if(vectorList[i].x<=a.x &&vectorList[j].x<a.x ) return false;
      }
    }
  }
  return true;
}*/



bool checkHorizontalLines(const std::vector<Point>& points, const Point& a, const Point& b) {
    for (const auto& p : points) {
        if (p == a || p == b) continue; // Skip the corners

        // Check if p is strictly to the left of the left edge and between top and bottom edges
        if (p.x < a.x && p.y >= a.y && p.y <= b.y) {
            for (const auto& q : points) {
                if (q == p || q == a || q == b) continue;
                if (q.y == p.y && q.x > p.x) {
                    return false; // Horizontal line enters from the left
                }
            }
        }
    }
    return true;
}

bool checkVerticalLines(const std::vector<Point>& points, const Point& a, const Point& b) {
    for (const auto& p : points) {
        if (p == a || p == b) continue; // Skip the corners

        // Check if p is strictly above the top edge and between left and right edges
        if (p.y < a.y && p.x >= a.x && p.x <= b.x) {
            for (const auto& q : points) {
                if (q == p || q == a || q == b) continue;
                if (q.x == p.x && q.y > p.y) {
                    return false; // Vertical line enters from the top
                }
            }
        }
    }
    return true;
}

bool checkPoint(const std::vector<Point>& points, const Point& a, const Point& b) {
    bool horizontalClear = checkHorizontalLines(points, a, b);
    bool verticalClear = checkVerticalLines(points, a, b);

    return horizontalClear && verticalClear;
}



/*bool checkPoint(const std::vector<Point>& points, const Point& a, const Point& b) {
    // Check horizontal line between a and b
    for (const auto& p : points) {
        if (p == a || p == b) continue; // Skip the corners

        // Check if p is on the horizontal line between a and b
        if (p.y == a.y && p.x > a.x && p.x < b.x) {
            return false;
        }

        // Check if p is on the vertical line between a and b
        if (p.x == a.x && p.y > a.y && p.y < b.y) {
            return false;
        }

        // Check if p is on the horizontal line between a and b (other side)
        if (p.y == b.y && p.x > a.x && p.x < b.x) {
            return false;
        }

        // Check if p is on the vertical line between a and b (other side)
        if (p.x == b.x && p.y > a.y && p.y < b.y) {
            return false;
        }
    }

    return true;
}*/

bool isValid(Point a, Point b, std::vector<Point> pointList){
  int size = pointList.size();
  std::pair<Point, Point> normalizedPoints = getNormalizedPoints (a, b);
  for (int i = 0; i< size; i++){
    if(checkPoint(pointList, normalizedPoints.first, normalizedPoints.second)){ 
      return false;
//      std::cout << "Point 1: X: " << a.x << " Y: " << a.y << "\nPoint 2: X: " << b.x << " Y: " <<b.y << "\n";
//      std::cout << "Checked Point: X: " << pointList[i].x << " Y: " << pointList[i].y << "\n\n";
    }
  }
  return true;
}







int main(int argc, char **argv){
  std::fstream file (argv[1]);
  std::string line;
  std::vector<Point> tiles;
  
  while (std::getline(file,line)){
        std::istringstream iss(line);
        std::string token;
        std::vector< long int> values;

        while (std::getline(iss, token, ',')) {
            values.push_back(std::stoul(token));
        }

        tiles.push_back({values[0], values[1]});
  }
  std::vector<std::pair<Point,Point>> validSquares;
  for (unsigned long int i= 0; i<tiles.size();i++){
    for (unsigned long int j = i; j<tiles.size(); j++){
      if (tiles[i] == tiles[j]) continue;
      if (isValid(tiles[i], tiles[j], tiles)) validSquares.push_back({tiles[i], tiles[j]});
    }
  }
    

/*  for (std::pair<Point,Point> pair: validSquares){
    std::cout << "Point 1: X: " << pair.first.x << " Y: " << pair.first.y << "\nPoint 2: X: " << pair.second.x << " Y: " <<pair.second.y << "\n\n";
  }*/
  long int biggestRect = findBiggestRectSize(validSquares);
  std::cout << "Biggest: " << biggestRect << '\n';
  
  
  return 0;

}
