#pragma once
#include <cstddef>

// Leitura segura: retorna '\0' se 'idx < off' ou ponteiro nulo.
// Uso: safe_get(trigData.array, tD, 6) em vez de trigData.array[tD - 6]
inline char safe_get(const char* arr, std::size_t idx, std::size_t off) {
    if (arr == nullptr) return '\0';
    if (idx < off) return '\0';
    return arr[idx - off];
}