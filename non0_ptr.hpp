#ifndef CPP_NON_PTR_HPP
#define CPP_NON_PTR_HPP

namespace cpplab {
    template <typename T>
    class non0_ptr;
}

template <typename T>
class cpplab::non0_ptr {
    public:
    explicit non0_ptr(T* ptr) : ptr_{ptr} {
        if (!ptr_) {
        throw std::runtime_error("null pointer value");
        }
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }

    private:
    T* ptr_;
};

#endif