#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <list>

template<typename T, typename Iterator, typename other_iterator_tag>
Iterator find(const T& value, Iterator first, Iterator last, other_iterator_tag) {
    for (auto i = first; i != last; i++) {
        if (*i == value) {
            return i;
        }
    }
    return last;
}

template<typename T, typename Iterator>
Iterator find(const T& value, Iterator first, Iterator last, std::random_access_iterator_tag) {
    Iterator middle;
    Iterator end = last, begin = first;
    while (1) {
        middle = begin + (end - begin) / 2;
        if (value < *middle) {
            end = middle;
        } else {
            if (middle != begin) {
                begin = middle;
            }
            else if (middle == begin) {
                begin = middle + 1;
            }
        }
        if (begin == end) {
            if (*middle == value) {
                return middle;
            } else {
                break;
            }
        }
    }
    return last;
}

template<typename T, typename Iterator>
Iterator Find(const T& value, Iterator first, Iterator last) {
    return find(value, first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

struct Test {
    int a;
    explicit Test(int a) : a(a) {}
    static int cnt;
    static void Init() {
        cnt = 0;
    }

    bool operator<(const Test& rhs) const {
        ++cnt;
        return a < rhs.a;
    }
    bool operator==(const Test& rhs) const {
        ++cnt;
        return a == rhs.a;
    }
};

int Test::cnt = 0;

int main() {
    srand(123);

    {
        const int bound = 100000;
        std::vector<int> v(bound);
        for (auto& el : v) el = rand() % bound;
        std::sort(v.begin(), v.end());
        for (int i = 0; i < 100; ++i) {
            int val = rand() % bound;
            auto my_res = Find(val, v.begin(), v.end());
            auto ok_res = std::lower_bound(v.begin(), v.end(), val);
            if (ok_res == v.end() || *ok_res != val) {
                assert(my_res == v.end());
            }
            else {
                assert(my_res != v.end());
                assert(*my_res == *ok_res);
            }
        }
    }

    {
        std::vector<Test> tests;
        for (int i = 0; i < 1000; ++i) {
            tests.emplace_back(i * 3);
        }
        for (int i = 0; i < 1000; ++i) {
            Test res(i * 3);
            Test::Init();
            auto my_res = Find(res, tests.begin(), tests.end());
            assert(my_res != tests.end());
            assert(my_res->a == res.a);
            assert(Test::cnt < 15);
        }
    }

    {
        const int bound = 100;
        std::list<int> ll;
        for (int i = 0; i < bound; ++i) {
            ll.emplace_back(rand() % bound);
        }
        ll.sort();
        for (int i = 0; i < 100; ++i) {
            int val = rand() % bound;
            auto my_res = Find(val, ll.begin(), ll.end());
            auto ok_res = std::lower_bound(ll.begin(), ll.end(), val);
            if (ok_res == ll.end() || *ok_res != val) {
                assert(my_res == ll.end());
            }
            else {
                assert(my_res != ll.end());
                assert(*my_res == *ok_res);
            }
        }
    }
    {
        std::list<Test> tests;
        for (int i = 0; i < 1000; ++i) {
            tests.emplace_back(i * 3);
        }
        for (int i = 0; i < 1000; ++i) {
            Test res(i * 3);
            Test::Init();
            auto my_res = Find(res, tests.begin(), tests.end());
            assert(my_res != tests.end());
            assert(my_res->a == res.a);
            assert(abs(Test::cnt - i) < 5);
        }
    }
    std::cout << 1;
}
