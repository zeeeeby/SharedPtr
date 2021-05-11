#pragma once

using ValueType = int;

class SharedPtr {
public:
    SharedPtr();
    explicit SharedPtr(ValueType* ptr);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    SharedPtr& operator=(const SharedPtr& other);

    ~SharedPtr();

    void reset();

    explicit operator bool() const;
    ValueType* get();
    ValueType& operator*() const;

private:
    ValueType* _ptr;
    int* _count;
};