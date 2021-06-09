#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class CircularBuffer {
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;

        Iterator(T *it, T *bg_, T *ed_, T *s_, T *f_) {
            iterator = it;
            bg = bg_;
            ed = ed_;
            s = s_;
            f = f_;
        }

        T &operator*() const {
            return *iterator;
        }

        T *operator->() const {
            return iterator;
        }

        Iterator &operator++() {
            if(iterator == f){
                iterator = s;
            }else{
                iterator++;
            }
            return *this;
        }

        Iterator &operator--() {
            if(iterator == s){
                iterator = f;
            }else{
                --iterator;
            }
            
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
        T *bg;
        T *ed;
        T *f;
        T *s;
    };

    CircularBuffer(int capacity) {
        bg = 0;
        ed = 0;
        capac = capacity;
        sz = 0;
        buff = new T[capac];
    }
    void pp(){
        Iterator q = begin();
        for(int i = 0;i < 10;i++){
            cout << *q << endl;
            if(q == end()){
                break;
            }
            ++q;
        }
    }
    // void prnt(){
    // }
    //todo O(1) all operations
    void addFirst(T x) {    
        sz++;
        if(bg == ed && bg == 0){
            ed++;
            if(ed == capac){
                ed = 0;
            }
        }
        buff[bg] = x;
        if(bg == 0){
            bg = capac - 1;  
        }else{
            bg--;
        }
    }

    void addLast(T x) {
        sz++;
        if(bg == ed && bg == 0){
            bg--;
            if(bg == -1){
                bg = capac - 1;
            }
        }
        buff[ed] = x;
        if(ed == capac - 1){
            ed = 0;
        }else{
            ed++;
        }
    }

    void delFirst() {
        sz--;
        bg++;
        if(bg == capac){
            bg = 0;
        }
    }

    T first() const {
        return buff[(bg + 1) % capac];
    }

    T last() const {
        if(ed - 1 >= 0){
            return buff[ed - 1];
        }else{
            return buff[capac - 1];
        }
    }

    void changeCapacity(int _sz) {
        T *_buff = new T[_sz];
        int cur = 0;
        for (int i = bg + 1; i < ed; i++) {
            int j = i % (capac);
            _buff[cur] = buff[j];
            cur++;
        }
        delete[] buff;
        capac = _sz;
        buff = _buff;
        ed = cur;
        bg = capac - 1;
    }

    void delLast() {
        sz--;
        ed--;
        if(ed == -1){
            ed = capac - 1;
        }
    }

    //todo information about size and index in exception
    T &operator[](int ind) const {
        if (ind < 0 || ind >= sz) {
            throw out_of_range("out of range");
        }
        return buff[(bg + 1 + ind) % capac];
    }

    Iterator begin() const {
        if(bg == capac - 1){
            return Iterator(buff, buff, buff + ed, buff, buff + sz - 1);
        }else{
            return Iterator(buff + bg + 1, buff + bg + 1, buff + ed, buff, buff + sz - 1);
        }
    }

    Iterator end() const {
        if(bg == capac - 1){
            return Iterator(buff + ed, buff, buff + sz - 1, buff, buff + sz - 1);
        }else{
            return Iterator(buff + ed, buff + bg + 1, buff, buff, buff + sz - 1);
        }
    }

public:
    T *buff;
    int capac, sz;
    int bg,ed;
};