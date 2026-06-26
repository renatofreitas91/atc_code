#pragma once

// Precision and variant types shared across the project
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/variant.hpp>

// High-precision decimal (50 decimal digits)
using mp_float = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<50>>;

using PrecisionDoublePointer = boost::variant<double**, mp_float**>;
using PrecisionPointer = boost::variant<double*, mp_float*>;
using PrecisionValue = boost::variant<double, mp_float>;

template <typename T>
inline T precisionValueTo(const PrecisionValue& value) {
    if (const T* exact = boost::get<T>(&value)) return *exact;
    if (const double* number = boost::get<double>(&value)) return (T)*number;
    if (const mp_float* number = boost::get<mp_float>(&value)) return (T)*number;
    return (T)0;
}

template <typename T>
inline double precisionDisplayDouble(const T& value) {
    return (double)value;
}

inline double precisionDisplayDouble(const PrecisionValue& value) {
    return precisionValueTo<double>(value);
}
inline PrecisionValue operator+(const PrecisionValue& lhs, const PrecisionValue& rhs) {
    return precisionValueTo<mp_float>(lhs) + precisionValueTo<mp_float>(rhs);
}
inline PrecisionValue operator-(const PrecisionValue& lhs, const PrecisionValue& rhs) {
    return precisionValueTo<mp_float>(lhs) - precisionValueTo<mp_float>(rhs);
}
inline PrecisionValue operator*(const PrecisionValue& lhs, const PrecisionValue& rhs) {
    return precisionValueTo<mp_float>(lhs) * precisionValueTo<mp_float>(rhs);
}
inline PrecisionValue operator/(const PrecisionValue& lhs, const PrecisionValue& rhs) {
    return precisionValueTo<mp_float>(lhs) / precisionValueTo<mp_float>(rhs);
}
inline PrecisionValue operator-(const PrecisionValue& value) {
    return -precisionValueTo<mp_float>(value);
}
inline bool operator==(const PrecisionValue& lhs, double rhs) { return precisionValueTo<mp_float>(lhs) == mp_float(rhs); }
inline bool operator!=(const PrecisionValue& lhs, double rhs) { return !(lhs == rhs); }
inline bool operator<(const PrecisionValue& lhs, double rhs) { return precisionValueTo<mp_float>(lhs) < mp_float(rhs); }
inline bool operator>(const PrecisionValue& lhs, double rhs) { return precisionValueTo<mp_float>(lhs) > mp_float(rhs); }
inline bool operator<=(const PrecisionValue& lhs, double rhs) { return !(lhs > rhs); }
inline bool operator>=(const PrecisionValue& lhs, double rhs) { return !(lhs < rhs); }
inline bool operator==(double lhs, const PrecisionValue& rhs) { return rhs == lhs; }
inline bool operator!=(double lhs, const PrecisionValue& rhs) { return !(rhs == lhs); }
inline bool operator<(double lhs, const PrecisionValue& rhs) { return mp_float(lhs) < precisionValueTo<mp_float>(rhs); }
inline bool operator>(double lhs, const PrecisionValue& rhs) { return mp_float(lhs) > precisionValueTo<mp_float>(rhs); }
inline bool operator<=(double lhs, const PrecisionValue& rhs) { return !(lhs > rhs); }
inline bool operator>=(double lhs, const PrecisionValue& rhs) { return !(lhs < rhs); }
inline bool operator==(const PrecisionValue& lhs, int rhs) { return lhs == (double)rhs; }
inline bool operator!=(const PrecisionValue& lhs, int rhs) { return !(lhs == rhs); }
inline bool operator<(const PrecisionValue& lhs, int rhs) { return lhs < (double)rhs; }
inline bool operator>(const PrecisionValue& lhs, int rhs) { return lhs > (double)rhs; }
inline bool operator<=(const PrecisionValue& lhs, int rhs) { return lhs <= (double)rhs; }
inline bool operator>=(const PrecisionValue& lhs, int rhs) { return lhs >= (double)rhs; }
inline bool operator==(int lhs, const PrecisionValue& rhs) { return rhs == lhs; }
inline bool operator!=(int lhs, const PrecisionValue& rhs) { return !(rhs == lhs); }
inline bool operator<(int lhs, const PrecisionValue& rhs) { return (double)lhs < rhs; }
inline bool operator>(int lhs, const PrecisionValue& rhs) { return (double)lhs > rhs; }
inline bool operator<=(int lhs, const PrecisionValue& rhs) { return (double)lhs <= rhs; }
inline bool operator>=(int lhs, const PrecisionValue& rhs) { return (double)lhs >= rhs; }
inline bool operator==(const PrecisionValue& lhs, const mp_float& rhs) { return precisionValueTo<mp_float>(lhs) == rhs; }
inline bool operator!=(const PrecisionValue& lhs, const mp_float& rhs) { return !(lhs == rhs); }
inline bool operator<(const PrecisionValue& lhs, const mp_float& rhs) { return precisionValueTo<mp_float>(lhs) < rhs; }
inline bool operator>(const PrecisionValue& lhs, const mp_float& rhs) { return precisionValueTo<mp_float>(lhs) > rhs; }
inline bool operator<=(const PrecisionValue& lhs, const mp_float& rhs) { return !(lhs > rhs); }
inline bool operator>=(const PrecisionValue& lhs, const mp_float& rhs) { return !(lhs < rhs); }
inline bool operator==(const mp_float& lhs, const PrecisionValue& rhs) { return rhs == lhs; }
inline bool operator!=(const mp_float& lhs, const PrecisionValue& rhs) { return !(rhs == lhs); }
inline bool operator<(const mp_float& lhs, const PrecisionValue& rhs) { return lhs < precisionValueTo<mp_float>(rhs); }
inline bool operator>(const mp_float& lhs, const PrecisionValue& rhs) { return lhs > precisionValueTo<mp_float>(rhs); }
inline bool operator<=(const mp_float& lhs, const PrecisionValue& rhs) { return !(lhs > rhs); }
inline bool operator>=(const mp_float& lhs, const PrecisionValue& rhs) { return !(lhs < rhs); }
