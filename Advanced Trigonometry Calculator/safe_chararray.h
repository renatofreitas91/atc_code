#pragma once
#include <cstddef>

class SafeCharArray {
public:
    // cria um buffer com capacidade 'cap' (inclui espaço para '\0')
    static SafeCharArray create(std::size_t cap);

    SafeCharArray();
    SafeCharArray(const SafeCharArray&) = delete;
    SafeCharArray& operator=(const SafeCharArray&) = delete;
    SafeCharArray(SafeCharArray&& other) noexcept;
    SafeCharArray& operator=(SafeCharArray&& other) noexcept;
    ~SafeCharArray();

    // insere um caracter (trunca se cheio)
    void append_char(char c);

    // insere uma string NUL-terminated (trunca se necessário)
    void append_cstr(const char* s);

    // define conteúdo (substitui) — copia até capacity-1 e termina com '\0'
    void set_cstr(const char* s);

    // retorna ponteiro NUL-terminated
    const char* c_str() const;

    // capacidade total (inclui espaço para '\0')
    std::size_t capacity() const;

    // tamanho atual (exclui '\0')
    std::size_t size() const;

private:
    SafeCharArray(char* buf, std::size_t cap, std::size_t len);
    char* buffer_;
    std::size_t capacity_;
    std::size_t length_;
};