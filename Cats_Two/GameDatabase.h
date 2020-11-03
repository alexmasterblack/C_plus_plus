#include <vector>
#include <functional>
#include <map>
#include <utility>
#include <unordered_map>
#include <string>
#include <set>

bool operator>(const GameObject& a, const GameObject& b) {
  return a.id > b.id;
}

template <class Tp, template <class> class Compare>
class DereferenceCompare {
  Compare<Tp> comp;

 public:
  bool operator()(const Tp* const a, const Tp* const b) const {
    return comp(*a, *b);
  }
};

class GameDatabase {
 public:
  GameDatabase() = default;
  void Insert(ObjectId id, string name, size_t x, size_t y) {
    if (identifier.find(id) != identifier.end()) {
      Remove(id);
    }
    GameObject object;
    object.id = id;
    object.name = name;
    object.x = x;
    object.y = y;
    identifier[id] = object;
    positions[make_pair(x, y)].insert(&identifier[id]);
    names[name].insert(&identifier[id]);
  }
  void Remove(ObjectId id) {
    if (identifier.find(id) != identifier.end()) {
      positions[make_pair(identifier[id].x, identifier[id].y)].erase(
          &identifier[id]);
      names[identifier[id].name].erase(&identifier[id]);
      identifier.erase(id);
    }
  }
  vector<GameObject> DataByName(string name) const {
    vector<GameObject> result;
    if (names.count(name) != 0) {
      for (auto i = names.find(name)->second.begin();
           i != names.find(name)->second.end(); i++) {
        result.push_back(**i);
      }
    }
    return result;
  }
  vector<GameObject> DataByPosition(size_t x, size_t y) const {
    vector<GameObject> result;
    if (positions.count(std::make_pair(x, y)) != 0) {
      for (auto i = positions.find(make_pair(x, y))->second.begin();
           i != positions.find(make_pair(x, y))->second.end(); i++) {
        result.push_back(**i);
      }
    }
    return result;
  }
  vector<GameObject> Data() const {
    vector<GameObject> result;
    for (auto i = identifier.begin(); i != identifier.end(); i++) {
      result.push_back(i->second);
    }
    return result;
  }

 private:
  std::map<ObjectId, GameObject, std::greater<ObjectId>> identifier;
  std::map<std::pair<size_t, size_t>,
           std::set<GameObject*, DereferenceCompare<GameObject, std::greater>>>
      positions;
  std::unordered_map<
      string,
      std::set<GameObject*, DereferenceCompare<GameObject, std::greater>>>
      names;
};
