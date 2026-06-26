#include "safe_chararray.h"
#include <cstring>
#include <algorithm>

void RegisterDynamicArray(void* variable, std::size_t elements);
void UnregisterDynamicArray(void* variable);

SafeCharArray SafeCharArray::create(std::size_t cap) {
    if (cap == 0) cap = 1;
    char* buf = new char[cap];
    std::memset(buf, '\0', cap);
    RegisterDynamicArray(buf, cap);
    return SafeCharArray(buf, cap, 0);
}

SafeCharArray::SafeCharArray() : buffer_(nullptr), capacity_(0), length_(0) {}

SafeCharArray::SafeCharArray(char* buf, std::size_t cap, std::size_t len)
    : buffer_(buf), capacity_(cap), length_(len) {}

SafeCharArray::SafeCharArray(SafeCharArray&& other) noexcept
    : buffer_(other.buffer_), capacity_(other.capacity_), length_(other.length_) {
    other.buffer_ = nullptr;
    other.capacity_ = 0;
    other.length_ = 0;
}

SafeCharArray& SafeCharArray::operator=(SafeCharArray&& other) noexcept {
    if (this != &other) {
        if (buffer_ != nullptr) {
            std::memset(buffer_, '\0', capacity_);
            UnregisterDynamicArray(buffer_);
        }
        delete[] buffer_;
        buffer_ = other.buffer_;
        capacity_ = other.capacity_;
        length_ = other.length_;
        other.buffer_ = nullptr;
        other.capacity_ = 0;
        other.length_ = 0;
    }
    return *this;
}

SafeCharArray::~SafeCharArray() {
    if (buffer_ != nullptr) {
        std::memset(buffer_, '\0', capacity_);
        UnregisterDynamicArray(buffer_);
    }
    delete[] buffer_;
}

void SafeCharArray::append_char(char c) {
    if (capacity_ == 0) return;
    if (length_ + 1 >= capacity_) {
        // trunca: apenas garante terminação
        buffer_[capacity_ - 1] = '\0';
        return;
    }
    buffer_[length_++] = c;
    buffer_[length_] = '\0';
}

void SafeCharArray::append_cstr(const char* s) {
    if (!s || capacity_ == 0) return;
    std::size_t sLen = std::strlen(s);
    std::size_t space = (capacity_ - 1) - length_;
    std::size_t toCopy = std::min(sLen, space);
    if (toCopy > 0) {
        std::memcpy(buffer_ + length_, s, toCopy);
        length_ += toCopy;
    }
    buffer_[length_] = '\0';
}

void SafeCharArray::set_cstr(const char* s) {
    if (!s || capacity_ == 0) {
        if (capacity_ > 0) buffer_[0] = '\0';
        length_ = 0;
        return;
    }
    std::size_t sLen = std::strlen(s);
    std::size_t toCopy = std::min(sLen, capacity_ - 1);
    if (toCopy > 0) {
        std::memcpy(buffer_, s, toCopy);
    }
    buffer_[toCopy] = '\0';
    length_ = toCopy;
}

const char* SafeCharArray::c_str() const {
    return buffer_ ? buffer_ : "";
}

std::size_t SafeCharArray::capacity() const { return capacity_; }
std::size_t SafeCharArray::size() const { return length_; }
