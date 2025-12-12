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

//bool isValid(std::pair <Point, Point>& pair, std::vector <Point>& pointList){}
/*
bool isAbove(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point left = (pair.first.x < pair.second.x) ? pair.first : pair.second; 
  Point right = (pair.first.x < pair.second.x) ? pair.second : pair.first; 
  Point up = (pair.first.y < pair.second.y) ? pair.first : pair.second;
  if ( left.x< point.x && point.x < right.x && point.y <= up.y){
     return true;  
  }
  else{
  return false;
  }
}
bool isBelow(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point left = (pair.first.x < pair.second.x) ? pair.first : pair.second; 
  Point right = (pair.first.x < pair.second.x) ? pair.second : pair.first; 
  Point down = (pair.first.y > pair.second.y) ? pair.first : pair.second;
  if ( left.x< point.x && point.x < right.x && point.y >= down.y){
     return true;  
  }
  else{
  return false;
  }
}
bool isLeft(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point top = (pair.first.y < pair.second.y) ? pair.first : pair.second; 
  Point bottom = (pair.first.y < pair.second.y) ? pair.second : pair.first; 
  Point left = (pair.first.x < pair.second.x) ? pair.first : pair.second;
  if ( top.y < point.y && point.y < bottom.y && point.x <= left.x){
    return true;  
  }
  else{
  return false;
  }
}
bool isRight(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point top = (pair.first.y < pair.second.y) ? pair.first : pair.second; 
  Point bottom = (pair.first.y < pair.second.y) ? pair.second : pair.first; 
  Point right = (pair.first.x > pair.second.x) ? pair.first : pair.second;
  if ( top.y< point.y && point.y < bottom.y && point.x >= right.x){
     return true;  
  }
  else{
  return false;
  }
}


bool belowEdge(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point left = (pair.first.x < pair.second.x) ? pair.first : pair.second; 
  Point right = (pair.first.x < pair.second.x) ? pair.second : pair.first; 
  Point down = (pair.first.y < pair.second.y) ? pair.first : pair.second;
  if ( left.x< point.x && point.x < right.x && point.y > down.y){
     return true;  
  }
  else{
  return false;
  }
}
bool aboveEdge(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point left = (pair.first.x < pair.second.x) ? pair.first : pair.second; 
  Point right = (pair.first.x < pair.second.x) ? pair.second : pair.first; 
  Point up = (pair.first.y < pair.second.y) ? pair.first : pair.second;
  if ( left.x< point.x && point.x < right.x && point.y < up.y){
     return true;  
  }
  else{
  return false;
  }
  
}
bool rightOfEdge(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point top = (pair.first.y < pair.second.y) ? pair.first : pair.second; 
  Point bottom = (pair.first.y < pair.second.y) ? pair.second : pair.first; 
  Point left = (pair.first.x < pair.second.x) ? pair.first : pair.second;
  if ( top.y < point.y && point.y < bottom.y && left.x < point.x){
     return true;  
  }
  else{
  return false;
  }
}
bool leftOfEdge(std::pair<Point, Point>& pair, Point point){
  if (point == pair.first || point == pair.second) return false;
  Point top = (pair.first.y < pair.second.y) ? pair.first : pair.second; 
  Point bottom = (pair.first.y < pair.second.y) ? pair.second : pair.first; 
  Point right = (pair.first.x < pair.second.x) ? pair.first : pair.second;
  if ( top.y< point.y && point.y < bottom.y && point.x < right.x){
     return true;  
  }
  else{
  return false;
  }
}


bool checkTop(std::pair<Point, Point>& pair, Point point, const std::vector<Point> pointList){
//  if (pair.first.x == pair.second.x) return false;
  if (isAbove(pair, point)){
//    std::cout << "\n\nTop:\nPoint: " << point << "Pair:\nPoint1: " << pair.first << "Point 2: " << pair.second << "\n\n";
    for (unsigned long int i = 0; i<pointList.size(); i++){
      if (point.x == pointList[i].x && belowEdge(pair, pointList[i])) return false;
    }
  }
  return true;
}
bool checkBottom(std::pair<Point, Point>& pair, Point point, const std::vector<Point> pointList){
//  if (pair.first.x == pair.second.x) return false;
  if (isBelow(pair, point)){
//    std::cout << "\n\nBottom:\nPoint: " << point << "Pair:\nPoint1: " << pair.first << "Point 2: " << pair.second << "\n\n";
    for (unsigned long int i = 0; i<pointList.size(); i++){
      if (point.x == pointList[i].x && aboveEdge(pair, pointList[i])) return false;
    }
  }
  return true;
}
bool checkLeft(std::pair<Point, Point>& pair, Point point, const std::vector<Point> pointList){
//  if (pair.first.x == pair.second.x) return false;
  if (isLeft(pair, point)){
//    std::cout << "\n\nLeft:\nPoint: " << point << "Pair:\nPoint1: " << pair.first << "Point 2: " << pair.second << "\n\n";
    for (unsigned long int i = 0; i<pointList.size(); i++){
      if (point.y == pointList[i].y && rightOfEdge(pair, pointList[i])) return false;
    }
  }
  return true;
}
bool checkRight(std::pair<Point, Point>& pair, Point point, const std::vector<Point> pointList){
//  if (pair.first.x == pair.second.x) return false;
  if (isRight(pair, point)){
//    std::cout << "\n\nRight:\nPoint: " << point << "Pair:\nPoint1: " << pair.first << "Point 2: " << pair.second << "\n\n";
    for (unsigned long int i = 0; i<pointList.size(); i++){
      if (point.y == pointList[i].y && leftOfEdge(pair, pointList[i])) return false;
    }
  }
  return true;
}

bool isValid(std::pair<Point, Point> pair, const std::vector<Point> pointList){
  for (unsigned long int i = 0; i <pointList.size(); i++){
    if(!(checkTop(pair, pointList[i], pointList) && checkBottom(pair, pointList[i], pointList) && checkLeft(pair, pointList[i], pointList) && checkRight(pair, pointList[i], pointList))){
      return false;
    }
  }
  return true;
  if (checkTop(pair, point, pointList)) return false;
  if (checkBottom(pair, point, pointList)) return false;
  if (checkLeft(pair, point, pointList)) return false;
  if (checkRight(pair, point, pointList)) return false;
  return true;
}

bool rightTurn(std::pair <Point, Point>& pair, std::vector <Point>& pointList ){
  unsigned long int i = 0;
  for (; i < pointList.size(); i++){
    if (pair.first ==  pointList[i]){
      break;
    }
  }
  if (pointList[i].x == pointList[i+1].x){
    if (pointList[i].y < pointList[i+1].y){
      if(pointList[i].x < pointList[i+2].x){
        return false;
      } 
      else{
//        std::cout << "\n\nPoint: " << pointList[i] << "\n\n";
        return true;
      } 
    }
    else{ 
      if(pointList[i].x < pointList[i+2].x){
//        std::cout << "\n\nPoint: " << pointList[i] << "\n\n";
        return true;
      } 
      else{
        return false;
      }
    }
  }
  else if(pointList[i].y == pointList[i+1].y){
    if (pointList[i].x < pointList[i+1].x){
      if(pointList[i].y < pointList[i+2].y){
        return false;
      }
      else{
//        std::cout << "\n\nPoint: " << pointList[i] << "\n\n";
        return true;
      }
    }
    else{
      if(pointList[i].y < pointList[i+2].y){
        return false;
      }
      else{
//        std::cout << "\n\nPoint: " << pointList[i] << "\n\n";
        return true;
      }
    }
  } 
}
*/

// Check if a point is inside a rectangle (inclusive of edges)
bool isPointInRect(const Point& p, const std::pair<Point, Point>& rect) {
    const Point& bl = rect.first;
    const Point& tr = rect.second;
    long int xMin = std::min(bl.x, tr.x);
    long int xMax = std::max(bl.x, tr.x);
    long int yMin = std::min(bl.y, tr.y);
    long int yMax = std::max(bl.y, tr.y);
    return p.x > xMin && p.x < xMax && p.y > yMin && p.y < yMax;
}


// Check if any line crosses the rectangle
bool isValid(
    const std::pair<Point, Point>& rect,
    const std::vector<std::pair<Point, Point>>& allLines) {
//    std::cout << "Rect:\n";
//    std::cout << rect.first << rect.second<< '\n';

    for (size_t i = 0; i<allLines.size(); i++) {
        if (isPointInRect(allLines[i].first, rect) || isPointInRect(allLines[i].second, rect)) {
            return false;
        }
            // Vertical line
        if (allLines[i].first.x == allLines[i].second.x) {
//          std::cout << "Vertical\n";
//          std::cout << allLines[i].first << allLines[i].second <<'\n';
          Point top = {std::min(allLines[i].first.x, allLines[i].second.x), std::min(allLines[i].first.y, allLines[i].second.y)};
          Point bot = {std::max(allLines[i].first.x, allLines[i].second.x),  std::max(allLines[i].first.y, allLines[i].second.y)};
          long int yMin = std::min(rect.first.y, rect.second.y);
          long int yMax = std::max(rect.first.y, rect.second.y);
          long int xMin = std::min(rect.first.x, rect.second.x);
          long int xMax = std::max(rect.first.x, rect.second.x);
//          std::cout << yMin<< '\n' << yMax << '\n' << xMin << '\n' << xMax << '\n' << top << '\n' << bot <<  '\n';
          if (top.y<=yMin && bot.y >=yMax && top.x > xMin && bot.x< xMax){
            return false;
          }
            // Horizontal line
        } else if (allLines[i].first.y == allLines[i].second.y) {
//          std::cout << "Horizontal\n";
//          std::cout << allLines[i].first << allLines[i].second <<'\n';
          Point left = {std::min(allLines[i].first.x, allLines[i].second.x), std::min(allLines[i].first.y, allLines[i].second.y)};
          Point right = {std::max(allLines[i].first.x, allLines[i].second.x),  std::max(allLines[i].first.y, allLines[i].second.y)};
          long int yMin = std::min(rect.first.y, rect.second.y);
          long int yMax = std::max(rect.first.y, rect.second.y);
          long int xMin = std::min(rect.first.x, rect.second.x);
          long int xMax = std::max(rect.first.x, rect.second.x);
//          std::cout << yMin<< '\n' << yMax << '\n' << xMin << '\n' << xMax << '\n' <<  left<<'\n' << right <<'\n';
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
            // Vertical line
            verticalLines.push_back(std::make_pair(p1, p2));
        } else if (p1.y == p2.y) {
            // Horizontal line
            horizontalLines.push_back(std::make_pair(p1, p2));
        }
        // Ignore diagonal lines if any
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

/*  std::sort(rects.begin(), rects.begin(),
    [](const std::pair<std::pair<Point, Point>, long int> &a , const std::pair<std::pair<Point,Point>, long int> &b) {
      return a.second < b.second;
    });*/

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
        std::cout << rects[i].first.first << rects[i].first.second;
        break;
    }

/*      if (!checkTop(rects[i].first, tiles[j],tiles)){
        std::cout << "Point:\n" << tiles[j]  <<  "Rect:\nPoint 1: " << rects[i].first.first << "Point 2: "<< rects[i].first.second << "Size: " <<rects[i].second ;
        std::cout << "\ntop\n";
        std::cout << "\n\n";
      }
      if (!checkBottom(rects[i].first, tiles[j],tiles)){
        std::cout << "Point:\n" << tiles[j]  <<  "Rect:\nPoint 1: " << rects[i].first.first << "Point 2: "<< rects[i].first.second << "Size: " <<rects[i].second ;
        std::cout << "\nbottom\n";
        std::cout << "\n\n";
        
      }
      if (!checkLeft(rects[i].first, tiles[j],tiles)){
        std::cout << "Point:\n" << tiles[j]  <<  "Rect:\nPoint 1: " << rects[i].first.first << "Point 2: "<< rects[i].first.second << "Size: " <<rects[i].second ;
        std::cout <<  "\nleft\n";
        std::cout << "\n\n";
      }
      if (!checkRight(rects[i].first, tiles[j],tiles)){
        std::cout << "Point:\n" << tiles[j]  <<  "Rect:\nPoint 1: " << rects[i].first.first << "Point 2: "<< rects[i].first.second << "Size: " <<rects[i].second ;
        std::cout << "\nright\n";
        std::cout << "\n\n";
      }*/
  }
/*  for (unsigned long int i = 0; i< rects.size(); i++){
        std::cout << "Rect:\nPoint 1: " << rects[i].first.first << "Point 2: "<< rects[i].first.second << "Size: " <<rects[i].second << '\n';
  }*/

  
/*  for (std::pair<Point,Point> pair: validRects){
    std::cout << "Pair:\n" <<pair.first  << pair.second <<'\n';
  }*/
  
/*  std::vector<std::pair<Point,Point>> vec;
  for (unsigned long int i = 0; i<validRects.size(); i++){
    if(checkRectValid(validRects[i], tiles)) vec.push_back(validRects[i]);
    else {
      std::cout << "Invalid:\n" << validRects[i].first << validRects[i].second <<'\n';
    }
  }*/
/*    std::cout << "All Lines\n";
  for (auto i: allLines){
    std::cout << i.first << i.second << '\n';
  }*/
  

    

//  long int biggestRect = findBiggestRectSize(validRects);
//  std::cout << "Biggest: " << biggestRect << '\n';
  
  
  return 0;

}
