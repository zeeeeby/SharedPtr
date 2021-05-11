#include <utility>
#include "sharedPtr.h"

SharedPtr::SharedPtr() {
}

SharedPtr::SharedPtr(ValueType* ptr) {
    _count = new int(1);
    _ptr = ptr;
}


SharedPtr::SharedPtr(const SharedPtr& other) {
    _count = other._count;
    ++*_count;
    _ptr = other._ptr;
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept {
    _ptr = std::exchange(other._ptr, nullptr);
    _count = std::exchange(other._count, nullptr);
}

SharedPtr::~SharedPtr() {
    if (_count && _ptr) {
        reset();
    }
}


SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        if (_count) {
            reset();
        }
        _ptr = std::exchange(other._ptr, nullptr);
        _count = std::exchange(other._count, nullptr);
    }
    return *this;
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {
        *this = SharedPtr(other);
    }
    return *this;
}

void SharedPtr::reset() {
    --*_count;
    if (!*_count) {
        delete[] _ptr;
        delete _count;
    }
    _ptr = _count = nullptr;
}

SharedPtr::operator bool() const {
    return _ptr != nullptr;
}

ValueType* SharedPtr::get() {
    return _ptr;
}

ValueType& SharedPtr::operator*() const {
    return *_ptr;
}


