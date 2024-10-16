#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <iterator>
#include <memory>

template <typename T>
class CustomVector {
private:
    std::unique_ptr<T[]> data_;
    std::size_t size_;
    std::size_t capacity_;
    void reallocation(std::size_t);
public:
    CustomVector();
    CustomVector(std::size_t);
    CustomVector(std::size_t, const T&);

    CustomVector(const CustomVector&); // копирование
    CustomVector(std::initializer_list<T>);
    CustomVector& operator=(const CustomVector&); // Присваивание копированием

    CustomVector(CustomVector&& object); // Конструктор перемещения 

    CustomVector& operator=(CustomVector&&); // Присваивание с перемещением

    CustomVector& operator=(std::initializer_list<T>);

    void assign(std::size_t count, const T& value);
    void assign(std::initializer_list<T> ilist);

    std::size_t size() const;
    bool empty() const;
    std::size_t capacity() const;
    void reserve(std::size_t new_cap);
    void shrink_to_fit();

    void push_back(const T&);

    void pop_back();

    // Метод для доступа к элементу по индексу

    T& operator[](std::size_t);
    const T& operator[](std::size_t) const;

    T& at(std::size_t);
    const T& at(std::size_t) const;

    T& front();
    const T& front() const;


    T& back();
    const T& back() const;

    T* data();
    const T* data() const;


    class ConstIterator;
    class Iterator {
    private:
        T* ptr;
    public:
        using difference_type = std::ptrdiff_t; 
        explicit Iterator(T* p):ptr(p) {}; // чтобы не дать случайно преобразовать из T* в Iterator
        T& operator*() const {
            if (ptr == nullptr) {
                throw std::runtime_error("Try dereference nullptr");
            }
            return *ptr;
        }
        T* operator->() const {return ptr;}
        Iterator& operator++() {++ptr; return *this;}
        Iterator operator++(int) { Iterator temp = *this; ++ptr; return temp; }
        Iterator& operator--() { --ptr; return *this; }
        Iterator operator--(int) { Iterator temp = *this; --ptr; return temp; }
        Iterator& operator+=(difference_type n) { ptr += n; return *this; }
        Iterator& operator-=(difference_type n) { ptr -= n; return *this; }
        Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
        Iterator operator-(difference_type n) const { return Iterator(ptr - n); }
        difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator<(const Iterator& other) const { return ptr < other.ptr; }
        bool operator>(const Iterator& other) const { return ptr > other.ptr; }
        bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }
        friend ConstIterator;
    };


    Iterator begin() {
        if (data_ == nullptr) {
            throw std::runtime_error("Try take  operator from nullptr structure");
        }
        return Iterator(data_.get());
    }
    Iterator end() {
        if (data_ == nullptr) {
            throw std::runtime_error("Try take  operator from nullptr structure");
        }
        return Iterator(data_.get() + size_);
    }

    class ConstIterator {
    private:
        const T* ptr;
    public:
        using difference_type = std::ptrdiff_t; 
        explicit ConstIterator(const T* p):ptr(p) {}; // чтобы не дать случайно преобразовать из T* в ConstIterator
        const T& operator*() const {
            if (ptr == nullptr) {
                throw std::runtime_error("Try dereference nullptr");
            }
            return *ptr;
        }
        ConstIterator(const Iterator& it): ptr(it.ptr) {}
        const T* operator->() const {return ptr;}
        ConstIterator& operator++() {++ptr; return *this;}
        ConstIterator operator++(int) { ConstIterator temp = *this; ++ptr; return temp; }
        ConstIterator& operator--() { --ptr; return *this; }
        ConstIterator operator--(int) { ConstIterator temp = *this; --ptr; return temp; }
        ConstIterator& operator+=(difference_type n) { ptr += n; return *this; }
        ConstIterator& operator-=(difference_type n) { ptr -= n; return *this; }
        ConstIterator operator+(difference_type n) const { return ConstIterator(ptr + n); }
        ConstIterator operator-(difference_type n) const { return ConstIterator(ptr - n); }
        difference_type operator-(const ConstIterator& other) const { return ptr - other.ptr; }
        bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
        bool operator<(const ConstIterator& other) const { return ptr < other.ptr; }
        bool operator>(const ConstIterator& other) const { return ptr > other.ptr; }
        bool operator<=(const ConstIterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const ConstIterator& other) const { return ptr >= other.ptr; }
    };


    ConstIterator begin() const {
        return Iterator(data_.get());
    }
    ConstIterator end() const {
        return Iterator(data_.get() + size_);
    }
    Iterator insert(ConstIterator, const T&);
    Iterator erase(Iterator pos);

    template <typename... Args>
    Iterator emplace(ConstIterator, Args&&...);

    template <typename... Args>
    T& emplace_back(Args&&...);


    void resize(std::size_t);
    void resize(std::size_t, const T&);

    void clear();
    void swap(CustomVector&);
};

template <typename T>
CustomVector<T>::CustomVector():size_(0),capacity_(0) {
    data_ = std::make_unique<T[]>(0);
}

template <typename T>
CustomVector<T>::CustomVector(std::size_t first_size):size_(first_size),capacity_(first_size) {
    data_ = std::make_unique<T[]>(first_size);
}

template <typename T>
CustomVector<T>::CustomVector(std::size_t new_size, const T& value) {
    capacity_ = new_size;
    size_ = new_size;
    data_ = std::make_unique<T[]>(new_size);
    for (std::size_t i = 0; i < new_size; ++i) {
        data_[i] = value;
    }
}

template <typename T>
CustomVector<T>::CustomVector(const CustomVector& other): size_(other.size_), capacity_(other.capacity_) {
    data_ = std::make_unique<T[]>(capacity_);
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template <typename T>
CustomVector<T>::CustomVector(std::initializer_list<T>ilist){
    size_ = ilist.size();
    capacity_ = ilist.size();
    data_ = std::make_unique<T[]>(capacity_);
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
        data_[it - ilist.begin()] = *it;
    }
}

template <typename T>
CustomVector<T>& CustomVector<T>::operator=(const CustomVector& other) {
    if (this != &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = std::make_unique<T[]>(capacity_);
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template <typename T>
CustomVector<T>::CustomVector(CustomVector&& object) {
    size_ = object.size_;
    capacity_ = object.capacity_;
    data_ = object.data_;
    object.data_ = nullptr;
}

template<typename T>
CustomVector<T>& CustomVector<T>::operator=(CustomVector&& object) {
    size_ = object.size_;
    capacity_ = object.capacity_;
    data_ = std::move(object.data_);
    object.data_ = nullptr;
    object.size_ = 0;
    object.capacity_ = 0;
    return *this;
}

template<typename T>
CustomVector<T>& CustomVector<T>::operator=(std::initializer_list<T> ilist) {
    size_ = ilist.size();
    capacity_ = ilist.size();
    data_ = std::make_unique<T[]>(capacity_);
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
        data_[it - ilist.begin()] = *it;
    }
    return *this;
}
template <typename T>
void CustomVector<T>::assign(std::size_t count, const T& value) {
    capacity_ = count;
    size_ = count;
    data_ = std::make_unique<T[]>(count);
    for (std::size_t i = 0; i < count; ++i) {
        data_[i] = value;
    }
}

template <typename T>
void CustomVector<T>::assign(std::initializer_list<T> ilist) {
    size_ = ilist.size();
    capacity_ = ilist.size();
    data_ = std::make_unique<T[]>(capacity_);
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
        data_[it - ilist.begin()] = *it;
    }
}

template <typename T>
std::size_t CustomVector<T>::size() const {
    return size_;
}

template <typename T>
bool CustomVector<T>::empty() const {
    return size_ == 0;  
}

template <typename T>
std::size_t CustomVector<T>::capacity() const {
    return capacity_;
} 

template <typename T>
void CustomVector<T>::reserve(std::size_t new_cap) {
    if (new_cap > capacity_) {
        reallocation(new_cap);
    }
}

template <typename T>
void CustomVector<T>::shrink_to_fit() {
    reallocation(size_);
}

template <typename T>
void CustomVector<T>::reallocation(std::size_t new_capacity) {
    std::unique_ptr<T[]>new_data_ = std::make_unique<T[]>(new_capacity);
    for (std::size_t i = 0; i < size_; ++i) {
        new_data_[i] = std::move(data_[i]);
    }
    data_ = std::move(new_data_);
    capacity_ = new_capacity;
}
template <typename T>
void CustomVector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reallocation(capacity_ == 0? 1: capacity_ * 2);
    }
    data_[size_] = value;
    ++size_;
}

template <typename T>
void CustomVector<T>::pop_back() {
    data_[size_] = T();
    if (size_ > 0) {
        --size_;
    }
}

template <typename T>
T& CustomVector<T>::operator[](std::size_t index) {
    return data_[index];
}

template <typename T>
const T& CustomVector<T>::operator[](std::size_t index) const {
    return data_[index];
} 

template<typename T>
T& CustomVector<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index is out of range");
    }
    return data_[index];
}

template<typename T>
const T& CustomVector<T>::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index is out of range");
    }
    return data_[index];
}

template<typename T>
T& CustomVector<T>::front() {
    return data_[0];
}

template<typename T>
const T& CustomVector<T>::front() const {
    return data_[0];
}

template<typename T>
T& CustomVector<T>::back() {
    return data_[size_ - 1];
}

template<typename T>
const T& CustomVector<T>::back() const {
    return data_[size_ - 1];
}

template<typename T>
T* CustomVector<T>::data() {
    return data_.get();
}

template<typename T>
const T* CustomVector<T>::data() const {
    return data_.get();
}

template <typename T>
typename CustomVector<T>::Iterator CustomVector<T>::insert(typename CustomVector<T>::ConstIterator pos, const T& value) {
    size_t index = pos - begin();
    if (size_ == capacity_) {
        reallocation(capacity_ == 0 ? 1: capacity_ * 2);
    }
    ++size_;
    for (std::size_t i = size_ - 1; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = value;
    return typename CustomVector<T>::Iterator(data_.get() + index);
}

template <typename T>
typename CustomVector<T>::Iterator CustomVector<T>::erase(typename CustomVector<T>::Iterator pos) {
    size_t index = pos - begin();
    for (std::size_t i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    size_--;
    return typename CustomVector<T>::Iterator(data_.get() + index);
}

template <typename T>
template <typename... Args>
typename CustomVector<T>::Iterator CustomVector<T>::emplace(typename CustomVector<T>::ConstIterator pos, Args&& ... args) {
    size_t index = pos - begin();
    if (size_ == capacity_) {
        reallocation(capacity_ == 0 ? 1: capacity_ * 2);
    }
    for (std::size_t i = size_; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = T(std::forward<Args>(args)...);
    ++size_;
    return typename CustomVector<T>::Iterator(data_.get() + index);
}

template <typename T>
template <typename... Args>
T& CustomVector<T>::emplace_back(Args&& ... args) {
    if (size_ == capacity_) {
        reallocation(capacity_ == 0? 1: capacity_ * 2);
    }
    data_[size_] = T(std::forward<Args>(args)...);
    ++size_;
    return data_[size_];
}

template <typename T>
void CustomVector<T>::resize(std::size_t new_size) {
    if (data_ == nullptr) {
        capacity_ = new_size;
        size_ = new_size;
        data_ = std::make_unique<T[]>(new_size);
        return;
    }
    if (new_size > capacity_) {
        reallocation(new_size);
    }
    size_ = new_size;
}

template <typename T>
void CustomVector<T>::resize(std::size_t new_size, const T&value) {
    if (data_ == nullptr) {
        capacity_ = new_size;
        size_ = new_size;
        data_ = std::make_unique<T[]>(new_size);
        for (std::size_t i = 0; i < new_size; ++i) {
            data_[i] = value;
        }
        return;
    }
    if (new_size > capacity_) {
        reallocation(new_size);
        for (std::size_t i=size_; i < new_size; ++i) {
            data_[i] = value;
        }
    }
    size_ = new_size;
}

template <typename  T>
void CustomVector<T>::clear() {
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = T();
    }
    size_ = 0;
}

template <typename T>
void CustomVector<T>::swap(CustomVector&other) {
    std::swap(capacity_,other.capacity_);
    std::swap(size_,other.size_);
    data_.swap(other.data_);
}
#endif