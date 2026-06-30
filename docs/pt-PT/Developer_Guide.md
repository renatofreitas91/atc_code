# Guia de Developer do Advanced Trigonometry Calculator

Este guia da uma visão técnica de alto nivel do código do ATC. O código-fonte
continua a ser a referência final para comportamento exato.

Para receitas de contribuicao, checklists e notas práticas de "como adicionar",
ver `docs/pt-PT/Developer_Reference.md`.

## Objetivo do projeto

O ATC é uma aplicação matemática C++ de linha de comandos para Windows. Avalia
expressões textuais e comandos documentados em ambiente de consola.

O projeto suporta fluxos numéricos com aritmética, trigonometria, numeros
complexos, matrizes, estatística, ferramentas polinomiais, resolucao de
equacoes, variáveis e precisão configuravel.

O ATC não deve ser descrito como um CAS geral completo.

## Estrutura de código

Diretorio principal:

```text
Advanced Trigonometry Calculator/
```

Ficheiros importantes:

- `main.cpp`: arranque, settings e escolha entre `double` e Boost `mp_float`;
- `auto_complete.cpp`: edição interativa, autocomplete e histórico;
- `main_aux_processor.cpp` e `main_processor.cpp`: routing de comandos e
  expressões;
- `processing_core.cpp`: processamento de expressões;
- `commands.cpp`: comandos visiveis ao utilizador;
- `equation_solver.cpp`, `equations_system_solver.cpp` e `solver.cpp`:
  caminhos de solver;
- `polynomial_arithmetic.cpp`: simplificacao polinomial;
- `dynamic_allocations.cpp`: helpers de memória dinâmica.

## Fluxo de processamento

Para uma visão visual, consultar `docs/Architecture.md`.

1. `main.cpp` inicializa paths e settings.
2. O runtime tipado e escolhido para `double` ou Boost `mp_float`.
3. O comando entra no fluxo principal.
4. `main_core<T>()` e `main_sub_core<T>()` coordenam comandos, variáveis,
   output e expressões.
5. As expressões passam por `initialProcessor<T>()`, `arithSolver<T>()` e
   `functionProcessor<T>()` quando aplicável.

## Precisao

O modo persistente e guardado em:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\higherPrecision.txt
```

Valores:

- `0`: `double`
- `1`: Boost `mp_float`

## Memoria

Ao alterar código sensível a memória:

- usar helpers existentes quando apropriado;
- garantir terminacao `\0` em arrays de char;
- libertar arrays temporarios em todos os caminhos;
- correr testes de regressão e stress quando praticavel.

## Testes

Scripts principais:

- `tests/run-atc-regression.ps1`
- `tests/run-atc-memory-stress.ps1`
- `tests/run-atc-script-benchmark.ps1`
- `tests/run-atc-isolated-coverage.ps1`

Resultado validado atual:

```text
Summary: 377 passed, 0 failed
```

## Referência prática de developer

A Referência de Developer cobre:

- como adicionar um novo comando;
- como adicionar uma função matemática;
- como adicionar um módulo guiado;
- como adicionar testes de regressão;
- expectativas de documentação;
- riscos de regressão no parser e solver;
- cuidados de compatibilidade Windows;
- regras de estabilidade de output;
- checklist antes de commit/release.

Usar em conjunto com este guia e com a visão de arquitetura antes de alterar
parser, solver, consola ou persistência.
