#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <cmath>
#include <algorithm>

struct Point{
  long int x,y;
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
  bool operator<(const Point &other) const {
    if(x!=other.x)
      return x<other.x;
    return y<other.y;
  }
};

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "X: " << point.x << " Y: " << point.y <<  '\n';
    return os;
}



long int pow( long int base,  long int exponent) {
  long int result = 1;
  for ( long int i = 0; i < exponent; i++)
    result *= base;
  return result;
}

long int rectSize(Point& a, Point& b){
  Point topLeft = {std::min (a.x, b.x), std::min (a.y, b.y)};
  Point bottomRight = {std::max (a.x, b.x), std::max (a.y, b.y)};
  return std::sqrt(pow((bottomRight.x - topLeft.x+1), 2) ) * std::sqrt( pow((bottomRight.y - topLeft.y+1), 2));
}


 long int findBiggestRectSize(std::vector<std::pair<Point, Point>>& tiles ){
   long int biggest = 0;
  for (unsigned long int i = 0; i<tiles.size(); i++){
    long int current = rectSize(tiles[i].second, tiles[i].first);
    if(current > biggest){ 
      biggest=current;
    }
  }
  return biggest; 
}

bool isPointInRect(const Point& p, const std::pair<Point, Point>& rect) {
    const Point& bl = rect.first;
    const Point& tr = rect.second;
    long int xMin = std::min(bl.x, tr.x);
    long int xMax = std::max(bl.x, tr.x);
    long int yMin = std::min(bl.y, tr.y);
    long int yMax = std::max(bl.y, tr.y);
    return p.x > xMin && p.x < xMax && p.y > yMin && p.y < yMax;
}


bool isValid(
    const std::pair<Point, Point>& rect,
    const std::vector<std::pair<Point, Point>>& allLines) {

    for (size_t i = 0; i<allLines.size(); i++) {
        if (isPointInRect(allLines[i].first, rect) || isPointInRect(allLines[i].second, rect)) {
            return false;
        }
        if (allLines[i].first.x == allLines[i].second.x) {
          Point top = {std::min(allLines[i].first.x, allLines[i].second.x), std::min(allLines[i].first.y, allLines[i].second.y)};
          Point bot = {std::max(allLines[i].first.x, allLines[i].second.x),  std::max(allLines[i].first.y, allLines[i].second.y)};
          long int yMin = std::min(rect.first.y, rect.second.y);
          long int yMax = std::max(rect.first.y, rect.second.y);
          long int xMin = std::min(rect.first.x, rect.second.x);
          long int xMax = std::max(rect.first.x, rect.second.x);
          if (top.y<=yMin && bot.y >=yMax && top.x > xMin && bot.x< xMax){
            return false;
          }
        } else if (allLines[i].first.y == allLines[i].second.y) {
          Point left = {std::min(allLines[i].first.x, allLines[i].second.x), std::min(allLines[i].first.y, allLines[i].second.y)};
          Point right = {std::max(allLines[i].first.x, allLines[i].second.x),  std::max(allLines[i].first.y, allLines[i].second.y)};
          long int yMin = std::min(rect.first.y, rect.second.y);
          long int yMax = std::max(rect.first.y, rect.second.y);
          long int xMin = std::min(rect.first.x, rect.second.x);
          long int xMax = std::max(rect.first.x, rect.second.x);
          if (left.x<=xMin && right.x >=xMax && left.y > yMin && right.y< yMax){
            return false;
          }
        }
    }
    return true;
}

void separateLines(
    const std::vector<Point>& points,
    std::vector<std::pair<Point, Point>>& horizontalLines,
    std::vector<std::pair<Point, Point>>& verticalLines) {

    for (size_t i = 0; i < points.size() ; ++i) {
        const Point& p1 = points[i  % points.size()];
        const Point& p2 = points[(i + 1) % points.size()];

        if (p1.x == p2.x) {
            verticalLines.push_back(std::make_pair(p1, p2));
        } else if (p1.y == p2.y) {
            horizontalLines.push_back(std::make_pair(p1, p2));
        }
    }
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
  std::vector<std::pair<std::pair<Point, Point>, long int>> rects;
  
  for (unsigned long int i = 0; i< tiles.size(); i++){
    for (unsigned long int j = i; j< tiles.size(); j++){
      if (i == j){
        continue;
      }
      long size = rectSize(tiles[i], tiles[j]);
      rects.push_back({{tiles[i], tiles[j]}, size}) ;
    } 
  }


std::sort(rects.begin(), rects.end(),
    [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<std::pair<Point, Point>> horizontalLines;
    std::vector<std::pair<Point, Point>> verticalLines;

    separateLines(tiles, horizontalLines, verticalLines);
    std::vector<std::pair<Point, Point>> allLines = horizontalLines;
allLines.insert(allLines.end(), verticalLines.begin(), verticalLines.end());
    


  for (unsigned long int i = 0; i<rects.size(); i++){
    if (isValid(rects[i].first, allLines)) {
        std::cout << "Biggest: " << rects[i].second << '\n';
        break;
    }

  }
  
  
  return 0;

}
