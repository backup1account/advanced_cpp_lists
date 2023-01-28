#ifndef CPP_VECTOR_HPP
#define CPP_VECTOR_HPP

#include <cstddef>
#include <iostream>

namespace cpplab {
    template<typename T>
    class vector;
};

template<typename T>
class cpplab::vector {
    private:
    using value_type = T;

    size_t max_size = 100;
    value_type* buffer = nullptr;
    int index = -1;

    private:
    value_type* allocate(size_t memory) {
        if (memory > max_size) {
            buffer = new value_type[max_size * 2];
        } else if (!buffer) {
            buffer = new value_type[max_size];
        }
        return buffer;
    }

    public:
    vector() noexcept = default;

    vector(size_t size) {
        allocate(size);

        for (int i=0; i < size; ++i) {
            buffer[++index] = i;
        }
    }

    vector(const vector& l_obj) {
        buffer = allocate(l_obj.max_size);
        index = l_obj.index;
        max_size = l_obj.max_size;

        for (size_t i=0; i < max_size; ++i) {
            buffer[i] = l_obj.buffer[i];
        }
    }

    vector& operator=(const vector<T>& l_obj) {
        if (&l_obj != this) {
            delete[] buffer;
            buffer = allocate(l_obj.max_size);
            index = l_obj.index;
            max_size = l_obj.max_size;

            for (size_t i=0; i < max_size; ++i) {
                buffer[i] = l_obj.buffer[i];
            }
        }
        return *this;
    }

    vector(vector&& r_obj) noexcept {
        buffer = r_obj.buffer;
        index = r_obj.index;
        max_size = r_obj.max_size;

        r_obj.buffer = nullptr;
        r_obj.index = -1;
    }

    vector& operator=(vector&& r_obj) noexcept {
        if (&r_obj != this) {
            delete[] buffer;
            
            buffer = r_obj.buffer;
            index = r_obj.index;
            max_size = r_obj.max_size;

            r_obj.buffer = nullptr;
            r_obj.index = -1;
        }
        return *this;
    }

    ~vector() {
        if (buffer) { 
            delete[] buffer;
            buffer = nullptr;
        }
    }   

    bool isEmpty() { return (index < 0); }
    bool isFull() { return (index >= max_size-1); }

    int size() { return index+1; } // return number of elements in vector
    
    value_type& operator[](const int& i) {
        return buffer[i];
    }

    friend std::ostream& operator<<(std::ostream& out, const vector& obj) {
        out << obj << std::endl;
        return out;
    }

    void push(T value) {
        if (isFull()) {
            std::cout << "Buffer overflow. Element not added.\n";
        } else {
            index++;
            allocate(index);
            buffer[index] = value;
        }
    }

    void pop() {
        if (isEmpty()) {
            std::cout << "Buffer underflow. Element not deleted.\n";
        } else {
            auto resized = (size() * sizeof(T)) - sizeof(buffer[index]);
            value_type* resized_buffer = new T[resized];
            index--;

            for (size_t i=0; i < size(); ++i) {
                resized_buffer[i] = buffer[i];
            }

            delete[] buffer;
            buffer = resized_buffer; // pointing to the same location of memory
        }
    }

    template<typename... Args>
    T& emplace_back(Args&&... args) {
        if (index >= max_size) {
            allocate(index);
        }

        this->buffer[index] = T(std::forward<Args>(args)...);
        return buffer[index++];
    }
    
};


template<typename T, typename T2>
auto operator*(cpplab::vector<T>& obj, T2& obj2) {
    auto result = 0;

    try {
        if (obj.size() != obj2.size()) { throw "Vectors should have the same size."; }

        for (size_t i=0; i < obj.size(); ++i) {
            result += (obj[i] * obj2[i]);
        }
    } catch(const char* error) {
        std::cout << error << '\n';
    }

    return result;
}

#endif