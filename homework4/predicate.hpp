template<class TInputIterator, class TPredicat>
bool allOf(TInputIterator begin, TInputIterator end, TPredicat pred) {
    for (; begin != end; begin++) {
        if (!pred(*begin)) {
            return 0;
        }
    }
    return 1;
}

template<class TInputIterator, class TPredicat>
bool anyOf(TInputIterator begin, TInputIterator end, TPredicat pred) {
    for (; begin != end; begin++) {
        if (pred(*begin)) {
            return 1;
        }
    }
    return 0;
}

template<class TInputIterator, class TPredicat>
bool noneOf(TInputIterator begin, TInputIterator end, TPredicat pred) {
    for (; begin != end; begin++) {
        if (pred(*begin)) {
            return 0;
        }
    }
    return 1;
}

template<class TInputIterator, class TPredicat>
bool oneOf(TInputIterator begin, TInputIterator end, TPredicat pred) {
    int cnt = 0;
    for (; begin != end; begin++) {
        if (pred(*begin)) {
            cnt++;
        }
    }
    return cnt == 1;
}

//todo default template argument std::less
template<class TInputIterator, class TPredicat>
bool isSorted(TInputIterator begin, TInputIterator end, TPredicat pred) {
    TInputIterator prev = begin;
    begin++;
    for (; begin != end; begin++) {
        if (!pred(*prev, *begin)) {
            return 0;
        }
        prev = begin;
    }
    return 1;
}

template<class TInputIterator>
bool isSorted(TInputIterator begin, TInputIterator end) {
    TInputIterator prev = begin;
    begin++;
    for (; begin != end; begin++) {
        if ((*prev) > (*begin)) {
            return 0;
        }
        prev = begin;
    }
    return 1;
}


template<class TInputIterator, class TPredicat>
bool isPartitioned(TInputIterator begin, TInputIterator end, TPredicat pred) {
    int chng = 0;
    bool cur = pred(*begin);
    begin++;
    for (; begin != end; begin++) {
        if (pred(*begin) != cur) {
            chng++;
        }
        cur = pred(*begin);
    }
    return chng == 1;
}

template<class TInputIterator, class T>
TInputIterator findNot(TInputIterator begin, TInputIterator end, const T &value) {
    for (; begin != end; begin++) {
        if (*begin != value) {
            return begin;
        }
    }
    return begin;
}

template<class TInputIterator, class T>
TInputIterator findBackward(TInputIterator begin, TInputIterator end, const T &value) {
    TInputIterator res = end;
    for (; begin != end; begin++) {
        if (*begin == value) {
            res = begin;
        }
    }
    return res;
}

template<class TInputIterator, class TPredicat>
bool isPalindrome(TInputIterator begin, TInputIterator end, TPredicat pred) {
    end--;
    for (; begin != end; begin++) {
        if (!pred(*begin, *end)) {
            return 0;
        }
        end--;
        if (begin == end) {
            break;
        }
    }
    return 1;
}
