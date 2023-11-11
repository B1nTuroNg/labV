#include <iostream>
#include <cassert>

template <typename T>
class Grid final{
public:
    using value_type = T;
    using size_type = unsigned;
    size_type get_y_size() const {return y_size; }
    size_type get_x_size() const {return x_size; }

private:
    T* const data;
    size_type const y_size, x_size;
public:
    // весь код основной

    // деструктор
    ~Grid() {
        delete[] data;
    }
    // copy constructor
    Grid<T>& operator=(Grid<T>& t){
        delete[] *data;
        data(new T[t->x_size*t->y_size]);
        for ( int i = 0; i <= x_size*y_size; i++){
            data[i] = (*t).data[i];
        }
        x_size = t->x_size;
        y_size = t->y_size;
    }
    // move равно
    Grid<T>& operator=(Grid<T>&& t){
        delete[] data;
        data(new T[t->x_size*t->y_size]);
        data = t->data;
        t->data = nullptr;
        x_size = t->x_size;
        y_size = t->y_size;
    }
    // move copy
    Grid(Grid<T>&& t): data(new T[t->x_size*t->y_size]), x_size(t->x_size), y_size(t->y_size){
        data = t->data;
        t->data = nullptr;
    }

    Grid(T *data, size_type y_size, size_type x_size):
    data(data), y_size(y_size), x_size(x_size) {}

    T operator ()(size_type y_idx, size_type x_idx) const{
        return data[y_idx * x_size + x_idx];
    }

    T& operator ()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }
    //copy равно
    Grid<T>& operator=(T const &t){
        for (auto it = data, end = data + x_size * y_size; it != end; ++it)
            *it = t;
        return *this;
    }


    Grid(T const &t): data(new T[1]), y_size(1), x_size(1) {// В скобках - кол-во ячеек
        *data = t;
    }

    Grid(size_type y_size, size_type x_size): data(new T[y_size*x_size]),
                                                                y_size(y_size), x_size(x_size){}

    Grid(size_type y_size, size_type x_size, T const &t): data(new T[y_size*x_size]),
                                                                y_size(y_size), x_size(x_size){
        for (auto it = data, end = data + x_size * y_size; it != end; ++it)
            *it = t;
    }
    /*
    Grid<T>& operator [](size_type y_idx){
        Grid<float> new_g(1, x_size, 0.0f);
        for (int i = 0; i <= x_size; i++){
            new_g(1, i) = data[y_size*y_idx + i];
        }
    }*/
    T* operator[] (size_type idx) {
        return &data[idx * x_size];
    }

};


int main() {

    Grid<float> g(3, 2, 0.0f);
    assert(3==g.get_y_size());
    assert(2==g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);


    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));

    return 0;
}

