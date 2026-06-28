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

## Melhorias de documentacao

A documentacao do ATC 2.1.7 foi expandida para tornar o projeto mais facil de
aprender, testar e desenvolver:

- Quick Start de uma pagina no inicio dos guias;
- Cookbook do ATC com workflows praticos e exemplos seguros;
- Boas Praticas para uso fiavel e reports reprodutiveis;
- Architecture Overview expandida com diagramas de modulo e fluxo;
- Developer Reference com checklists de contribuicao;
- reorganizacao do guia completo por curva natural de aprendizagem;
- ligacao mais clara entre documentacao, cobertura e regressao;
- documentacao bilingue Markdown/PDF e guias completos DOCX.

## Estado de testes

Resultado validado:

```text
Summary: 374 passed, 0 failed
```

Cobertura isolada:

```text
Summary: 68 passed, 0 failed
```

Validacao do package SourceForge:

```text
Summary: 44 passed, 0 failed
```

## Limites

O ATC nao e um CAS geral completo. Funcionalidade simbolica existe apenas onde
esta documentada, implementada e testada.
