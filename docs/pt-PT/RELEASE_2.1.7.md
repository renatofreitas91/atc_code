# Notas de Release do Advanced Trigonometry Calculator 2.1.7

Data: 2026-06-09

## Destaques

- Suporte persistente para alternar entre `double` e Boost `mp_float`.
- Correcao de output com 50 casas decimais para constantes como `pi` e `e`.
- Correcao de `solve equation(...)` para polinomios textuais suportados.
- Correcao de `simplify polynomial(...)` para formas textuais e produtos
  simples suportados.
- Suite automatica baseada no guia de utilizador.
- Melhorias no comportamento da consola no Windows 11.
- Melhorias de memoria dinamica e reducao de alocacoes desnecessarias em
  caminhos comuns.
- Cobertura de `min`, `max` e `avg` com listas e variaveis matriz.
- Autocomplete com `Tab`, ciclo de sugestoes e historico com setas.
- Melhorias em `verbose resolution`.
- Cobertura de solver/equation solver com cancelamento racional, `pi`, `e` e
  `pii`.

## Politica de documentacao

O ingles e o idioma de referencia para documentos open-source e comunidade. O
portugues e mantido para apoiar a comunidade lusofona.

## Estado de testes

Resultado validado:

```text
Summary: 359 passed, 0 failed
```

## Limites

O ATC nao e um CAS geral completo. Funcionalidade simbolica existe apenas onde
esta documentada, implementada e testada.
