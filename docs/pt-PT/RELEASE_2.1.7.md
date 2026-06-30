# Notas de Release do Advanced Trigonometry Calculator 2.1.7

Data: 2026-06-09

## Destaques

- Suporte persistente para alternar entre `double` e Boost `mp_float`.
- Correcao de output com 50 casas decimais para constantes como `pi` e `e`.
- Correcao de `solve equation(...)` para polinómios textuais suportados.
- Correcao de `simplify polynomial(...)` para formas textuais e produtos
  simples suportados.
- Suite automática baseada no guia de utilizador.
- Melhorias no comportamento da consola no Windows 11.
- Melhorias de memória dinâmica e reducao de alocacoes desnecessarias em
  caminhos comuns.
- Melhorias no processamento de scripts: `print("...", ...)` pode ser tratado
  diretamente em memória quando é seguro, evitando o caminho temporário por TXT.
- Redução adicional de memória em scripts através da libertação de arrays
  temporários e da alocação preguiçosa de buffers matriciais no
  `initialProcessor()`.
- Cobertura de `min`, `max` e `avg` com listas e variáveis matriz.
- Autocomplete com `Tab`, ciclo de sugestões e histórico com setas.
- Melhorias em `verbose resolution`.
- Cobertura de solver/equation solver com cancelamento racional, `pi`, `e` e
  `pii`.

## Politica de documentação

O inglês é o idioma de referência para documentos open-source e comunidade. O
português é mantido para apoiar a comunidade lusófona.

## Melhorias de documentação

A documentação do ATC 2.1.7 foi expandida para tornar o projeto mais fácil de
aprender, testar e desenvolver:

- Quick Start de uma pagina no inicio dos guias;
- Cookbook do ATC com workflows praticos e exemplos seguros;
- Boas Práticas para uso fiavel e reports reprodutíveis;
- Architecture Overview expandida com diagramas de módulo e fluxo;
- Developer Reference com checklists de contribuicao;
- reorganizacao do guia completo por curva natural de aprendizagem;
- ligação mais clara entre documentação, cobertura e regressão;
- documentação bilingue Markdown/PDF e guias completos DOCX.

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

O ATC não é um CAS geral completo. Funcionalidade simbólica existe apenas onde
esta documentada, implementada e testada.
