#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <float.h>

struct Vector {
  double x = 0;
  double y = 0;
  double z = 0;

  bool operator==(const Vector &other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  bool operator!=(const Vector &other) const {
    return x != other.x || y != other.y || z != other.y;
  }

  bool operator<(const Vector &other) const {
    if (x != other.x)
      return x < other.x;
    if (y != other.y)
      return y < other.y;
    return z < other.z;
  }
};

std::ostream &operator<<(std::ostream &os, const Vector &vec) {
  os << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z;
  return os;
}

struct VectorPair {
  Vector vec1;
  Vector vec2;
  double distance;

  bool operator<(const VectorPair &other) const {
    if (vec1 != other.vec1)
      return vec1 < other.vec1;
    return vec2 < other.vec2;
  }
  bool operator==(const VectorPair &other) const {
    return vec1 == other.vec1 && vec2 == other.vec2;
  }
};

void eliminateDuplicatePairs(std::vector<VectorPair> &pairs) {
  for (size_t i = 0; i < pairs.size(); i++) {
    for (size_t j = 1; j < pairs.size(); j++) {
    }
  }
}

VectorPair getDistance(const Vector &v1, const std::vector<Vector> vectorList) {
  double shortestDistance = DBL_MAX;
  int index = 0;
  int currentIndex = 0;
  for (Vector v2: vectorList){
    if (v2 == v1) continue;
    index++;
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    double dz = v2.z - v1.z;
    double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    if (distance < shortestDistance){
      shortestDistance = distance;
      currentIndex = index;
    }
  }
  return {v1, vectorList[currentIndex], shortestDistance} ;
}

bool isConnection(Vector vec, std::vector<Vector> vecArray) {
  if (vecArray.empty())
    return false;
  for (Vector i : vecArray)
    if (vec == i)
      return true;
  return false;
}

VectorPair findPair(Vector vec, std::vector<VectorPair> pairs) {
  for (VectorPair i : pairs) {
    if (vec == i.vec1 || vec == i.vec2)
      return i;
  }
}

/*bool checkIfAllUsed(std::vector<Vector> vectorList, std::vector<std::vector<Vector>> components){
    for (Vector elem : vectorList) {
        bool found = false;
        for (const auto& innerVec : components) {
            if (std::find(innerVec.begin(), innerVec.end(), elem) != innerVec.end()) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}*/

std::vector<std::vector<Vector>>
connectPairs(const std::vector<VectorPair> &pairs, std::vector<Vector> vectors, std::vector <Vector> vectorList) {
  std::vector<std::vector<Vector>> components;
  components.push_back({pairs[0].vec1, pairs[0].vec2});
  int limit = pairs.size();
  for (int i = 1; i < limit; i++) {

    bool changed = false;
    int size = components.size()-1;

    for (int j = 0; j < size; j++) {

      if (isConnection(pairs[i].vec1, components[j]) &&
          isConnection(pairs[i].vec2, components[j])) {
        changed = true;
        break;
      } else if (isConnection(pairs[i].vec1, components[j])) {
        bool found = false;
        for (int k = j; k < size; k++) {
          if (isConnection(pairs[i].vec2, components[k])) {
            
            components[j].insert(components[j].end(), components[k].begin(),
                                 components[k].end());
            components.erase(components.begin() + k);
            found = true;
            break;
          }
        }
        if (!found) {
          components[j].push_back(pairs[i].vec2);
        }

        changed = true;
        break;
      } else if (isConnection(pairs[i].vec2, components[j])) {
        bool found = false;
        for (int k = j; k < size; k++) {
          if (isConnection(pairs[i].vec1, components[k])) {
            components[j].insert(components[j].end(), components[k].begin(),
                                 components[k].end());
            components.erase(components.begin() + k);
            found = true;
            break;
          }
        }

        if (!found) {
          components[j].push_back(pairs[i].vec1);
        }

        changed = true;
      }
    }
    if (changed) {
      continue;
    } else {
      components.push_back({pairs[i].vec1, pairs[i].vec2});
    }
  }

  return components;
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<Vector> vectorList;
  std::vector<VectorPair> pairList;
  std::vector<std::vector<Vector>> circuits;
  while (std::getline(file, line)) {
    std::string value;
    Vector vector;

    double *ptr = &vector.x;

    size_t start = 0;
    size_t end = line.find_first_of(",\n");

    while (end != std::string::npos) {
      *ptr++ = std::stoull(line.substr(start, end - start));
      start = end + 1;
      end = line.find_first_of(",\n", start);
    }
    *ptr = std::stoull(line.substr(start, end - start));

    vectorList.push_back(vector);
  }
  size_t size = vectorList.size();



  size = vectorList.size();
  for (size_t i = 0; i < size; i++) {
//    for (size_t j = i; j < size; j++) {
//      if (vectorList[i] == vectorList[j]) {
//        continue;
//      } else {
        VectorPair pair = getDistance(vectorList[i], vectorList);
        pairList.push_back(pair);
      }
//    }
//  }

  std::sort(pairList.begin(), pairList.end(),
            [](const VectorPair &a, const VectorPair &b) {
              return a.distance < b.distance;
            });


  circuits = connectPairs(pairList, vectorList, vectorList);

  std::sort(circuits.begin(), circuits.end(),
            [](const std::vector<Vector> &a, const std::vector<Vector> &b) {
              return a.size() > b.size();
            });

  unsigned long long sum = 1;
  

  sum *= pairList[pairList.size()-1].vec1.x *pairList[pairList.size()-1].vec2.x;

  std::cout << "Sum: " << sum << '\n';

  return 0;
}
