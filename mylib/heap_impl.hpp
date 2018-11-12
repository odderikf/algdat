
template <typename T>
Heap<T>::Heap(std::vector<T> &vec, bool m, std::function<bool(const T&, const T&)> f)
 : v(vec), size(vec.size()), max_or_min(m), lessthan(f) {
    if (size>1){
        for(int64_t i = (size-2)/2; i >= 0; i--){
            fix(i);
        }
    }
}

template<typename T>
Heap<T>::Heap(std::vector<T> &vec) : v(vec), size(vec.size()), max_or_min(MAX_HEAP) {
    lessthan = [](const T &t1, const T &t2){
        return t1 < t2;
    };
    if (size>1) {
        for (int64_t i = (size - 2) / 2; i >= 0; i--) {
            fix(i);
        }
    }
}
template<typename T>
Heap<T>::Heap(std::vector<T> &vec, bool m) : v(vec), size(vec.size()), max_or_min(m) {
    lessthan = [](const T &t1, const T &t2){
        return t1 < t2;
    };
    if (size>1){
        for(int64_t i = (size-2)/2; i >= 0; i--){
            fix(i);
        }
    }
}

template <typename T>
Heap<T>::Heap(bool m) : v(std::vector<T>(0)), size(v.size()), max_or_min(m){
    lessthan = [](const T &t1, const T &t2){
        return t1 < t2;
    };
}

template <typename T>
Heap<T>::Heap(bool m,  std::function<bool(const T&, const T&)> f)
: v(std::vector<T>(0)), size(v.size()), max_or_min(m), lessthan(f){}

template <typename T>
Heap<T>::Heap() : v(std::vector<T>(0)), size(v.size()), max_or_min(MAX_HEAP){
    lessthan = [](const T &t1, const T &t2){
        return t1 < t2;
    };
}

template<typename T>
void Heap<T>::fix(u_int64_t n) {
    if (n >= size) return;
    if (max_or_min == MAX_HEAP) {
        u_int64_t max = n, l = left(n), r = right(n);
        if (l < size) {
            if (lessthan(v[max], v[l])) max = l;

            if (r < size) {
                if (lessthan(v[max], v[r])) max = r;
            }
            if (max != n) {
                std::swap(v[max], v[n]);
                return fix(max);
            }
        }
    } else {
        u_int64_t min = n, l = left(n), r = right(n);
        if (l < size) {
            if (lessthan(v[l], v[min])) min = l;

            if (r < size) {
                if (lessthan(v[r], v[min])) min = r;
            }
            if (min != n) {
                std::swap(v[min], v[n]);
                return fix(min);
            }
        }
    }

}

template<typename T>
u_int64_t Heap<T>::left(const u_int64_t &i) const {
    return 2 * i + 1;
}

template<typename T>
u_int64_t Heap<T>::right(const u_int64_t &i) const {
    return 2 * i + 2;
}

template <typename T>
u_int64_t Heap<T>::parent(const u_int64_t &i) const {
    if (i > 0)
    return (i-1)/2;
    else return UINT64_MAX;
}
template<typename T>
T Heap<T>::pop_max() {
    assert(max_or_min == MAX_HEAP);
    return pop();
}

template <typename T>
T Heap<T>::pop_min() {
    assert(max_or_min == MIN_HEAP);
    return pop();
}

template <typename T>
T Heap<T>::pop() {
    --size;
    if(size > 0)
        std::swap(v[size], v[0]); // for sorting reasons
    T val = v[size];
    fix(0);
    return val;
}

template <typename T>
bool Heap<T>::empty() {
    return size <= 0;
}
template<typename T>
bool Heap<T>::isleaf(const u_int64_t &i) const {
    return 2*i + 1 > size;
}

template <typename T>
void Heap<T>::emplace(T t){
    if (size < v.size() and size > 0) {
        v.emplace_back(t);
        std::swap(v[size], v[v.size()-1]);
    } else if (size < v.size()) {
        v.insert(v.begin(), t);
    } else {
        v.emplace_back(t);
    }
    size++;
    u_int64_t n = size-1;
    u_int64_t p = parent(n);
    if (max_or_min == MAX_HEAP){
        while (p != UINT64_MAX and lessthan(v[p], v[n])){
            std::swap(v[n], v[p]);
            n = p;
            p = parent(n);
        }
    } else {
        while (p != UINT64_MAX and p < n and lessthan(v[n], v[p])){
            std::swap(v[n], v[p]);
            n = p;
            p = parent(n);
        }
    }
}

template <typename T>
void Heap<T>::shrink_to_fit() {
    while (v.size() > size){
        v.pop_back();
    }
    v.shrink_to_fit();
}

template <typename T>
void Heap<T>::reserve(u_int64_t s){
    v.reserve(s);
}