#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class CircularBuffer {
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;

        Iterator(T *it) {
            iterator = it;
        }

        T &operator*() const {
            return *iterator;
        }

        T *operator->() const {
            return iterator;
        }

        Iterator &operator++() {
            ++iterator;
            return *this;
        }

        Iterator &operator--() {
            --iterator;
            return *this;
        }

        difference_type operator-(const Iterator &it) const {
            return iterator - it.iterator;
        }

        Iterator operator+(difference_type it) const {
            return Iterator(iterator + it);
        }

        Iterator operator-(difference_type it) const {
            return Iterator(iterator - it);
        }

        bool operator==(const Iterator &other) const {
            return iterator == other.iterator;
        }

        bool operator!=(const Iterator &other) const {
            return iterator != other.iterator;
        }

        bool operator>(const Iterator &other) const {
            return iterator > other.iterator;
        }

        bool operator<(const Iterator &other) const {
            return iterator<other.iterator;
        }

        bool operator>=(const Iterator &other) const {
            return iterator >= other.iterator;
        }

        bool operator<=(const Iterator &other) const {
            return iterator <= other.iterator;
        }

    private:
        T *iterator;
    };

    CircularBuffer(int capacity) {
        capac = capacity;
        sz = 0;
        buff = new T[capac];
    }

    void addFirst(T x) {
        for (int i = min(capac - 1, sz); i > 0; i--) {
            buff[i] = buff[i - 1];
        }

        buff[0] = x;
        if (capac - 1 >= sz) {
            sz++;
        }
    }

    void addLast(T x) {
        buff[sz] = x;
        sz++;
    }
    //todo O(1) all operations
    void delFirst() {
        for (int i = 0; i < sz - 1; i++) {
            buff[i] = buff[i + 1];
        }
        sz--;
    }

    T first() const {
        return buff[0];
    }

    T last() const {
        return buff[sz - 1];
    }

    void changeCapacity(int _sz) {
        T *_buff = new T[_sz];
        for (int i = 0; i < _sz; i++) {
            _buff[i] = buff[i];
        }
        delete[] buff;
        capac = _sz;
        buff = _buff;
    }

    void delLast() {
        sz--;
    }

    //todo information about size and index in exception
    T &operator[](int ind) const {
        if (ind < 0 || ind >= sz) {
            throw out_of_range("out of range");
        }
        return buff[ind];
    }

    Iterator begin() const {
        return Iterator(buff);
    }

    Iterator end() const {
        return Iterator(buff + sz);
    }

private:
    T *buff;
    int capac, sz;
};

