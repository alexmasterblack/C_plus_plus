#include <algorithm>
#include <vector>

class Set {
 private:
    std::vector<int64_t> our_set;

 public:
    Set() {}
    explicit Set(const std::vector<int64_t>& set) {
        for (auto elem : set) {
            Add(elem);
        }
    }
    bool Contains(int64_t element) const {
        auto check = find(our_set.begin(), our_set.end(), element);
        if (check == our_set.end()) {
            return false;
        } else {
            return true;
        }
    }
    void Add(int64_t element) {
        if (!Contains(element)) {
            our_set.push_back(element);
            sort(our_set.begin(), our_set.end());
        }
    }
    void Remove(int64_t element) {
        if (Contains(element)) {
            auto del = find(our_set.begin(), our_set.end(), element);
            our_set.erase(del);
        }
    }
    std::vector<int64_t> Data() const {
        return our_set;
    }
    Set Union(const Set& Other) const {
        Set new_set(our_set);
        for (auto elem : Other.our_set) {
            if (!Contains(elem)) {
                new_set.Add(elem);
            }
        }
        return new_set;
    }
    Set Intersection(const Set& Other) const {
        Set new_set;
        for (auto elem : Other.our_set) {
            if (Contains(elem)) {
                new_set.Add(elem);
            }
        }
        return new_set;
    }
    Set Difference(const Set& Other) const {
        Set new_set(our_set);
        for (auto elem : Other.our_set) {
            if (Contains(elem)) {
                new_set.Remove(elem);
            }
        }
        return new_set;
    }
    Set SymmetricDifference(const Set& Other) const {
        Set union_set = Union(Other);
        Set inter_set = Intersection(Other);
        return union_set.Difference(inter_set);
    }
};
