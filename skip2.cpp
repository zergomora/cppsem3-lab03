#include <set>
#include <unordered_set>
#include <iostream>

template <typename T> class SkipList {
private:
    std::set<T> currList;
public:
    SkipList() = default;

    template <typename InputIter>
    SkipList(InputIter first, InputIter last) {
        currList.insert(first, last);
    }
    SkipList(const SkipList& otherList) {
        if(this != &otherList) {
            currList.insert(otherList.begin(), otherList.end());
        }
    }
    SkipList& operator=(const SkipList& otherList) {
        if(this != &otherList) {
            currList.insert(otherList.begin(), otherList.end());
        }
        return *this;
    }
    SkipList(SkipList&& otherList) : currList(std::move(otherList->currList)) { }
    SkipList& operator=(SkipList&& otherList) noexcept {
        if(this != &otherList) {
            currList = std::move(otherList->currList);
        }
        return *this;
    }

    bool empty() {
        return currList.empty();
    }
    size_t size() {
        return currList.size();
    }
    void insert(T elem) {
        currList.insert(elem);
    }

    template <typename InputIter>
    void insert(InputIter first, InputIter last) {
        for (auto iter = first; iter != last; iter++) {
           currList.insert(*iter); 
        }
    }

    using iterator = typename std::set<T>::iterator;
    using const_iterator = typename std::set<T>::const_iterator;

    iterator begin() {
        return currList.begin();
    }

    iterator end() {
        return currList.end();
    }

    const_iterator begin() const {
        return currList.begin();
    }

    const_iterator end() const {
        return currList.end();
    }

    using reverse_iterator = typename std::set<T>::reverse_iterator;
    using const_reverse_iterator = typename std::set<T>::const_reverse_iterator;
    
    reverse_iterator rbegin() {
        return currList.rbegin();
    }

    reverse_iterator rend() {
        return currList.rend();
    }

    const_reverse_iterator rbegin() const {
        return currList.rbegin();
    }

    const_reverse_iterator rend() const {
        return currList.rend();
    }

    iterator find(T value) {
        for(auto it = currList.begin(); it != currList.end(); it++) {
            if(value == *it) return it;
        }
        auto it = currList.end(); it--;
        return it;
    }
    size_t count(T value) {
        size_t count = 0;
        for(auto it = currList.begin(); it != currList.end(); it++) {
            if(value == *it) count++;
        }
        return count;
    }

    iterator lower_bound(T value) {
        for(auto it = currList.begin(); it != currList.end(); it++) {
            if(value <= *it) return it;
        }
        auto it = currList.end(); it--;
        return it;
    }

    iterator upper_bound(T value) {
        for(auto it = currList.begin(); it != currList.end(); it++) {
            if(value < *it) return it;
        }
        auto it = currList.end(); it--;
        return it;
    }
    
    void read() {
        for (const auto& elem : currList) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    void clear() {
        currList.clear();
    }

    void erase(iterator elem) {
        currList.erase(elem);
    }

    template <typename InputIter>
    void erase(InputIter first, InputIter last) {
        for (auto iter = first; iter != last; iter++) {
           currList.erase(iter); 
        }
    }

    SkipList equal_range(iterator elem) {
        SkipList<T> tempList;
        for(auto it = currList.begin(); it != currList.end(); it++) {
            if(elem == *it) {
                tempList.insert(it);
            }
        }
        return tempList; 
    }

};

int main() {

    SkipList<int> test1;
    test1.insert(-10);
    test1.insert(25);

    std::unordered_set<int> test2 = {-41,26,33};
    test1.insert(test2.begin(), test2.end());

    test1.read();

    for (const auto& elem : test1) {
        std::cout << elem << " ";
    }

    std::cout << "Reversed iterator: ";
    for (auto rit = test1.rbegin(); rit != test1.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    auto it = test1.find(27);
    std::cout << *it << std::endl;
    
    auto it2 = test1.upper_bound(26);
    std::cout << *it2 << std::endl;

    return 0;
}
