# Documentacao tecnica do Advanced Trigonometry Calculator 2.1.7

Este documento resume o estado tecnico do ATC 2.1.7.

## Ambito

A versao 2.1.7 foca-se em previsibilidade do modo de precisao, correcoes no
solver e simplificador polinomial, cobertura de regressao, comportamento da
consola Windows 11, memoria dinamica, autocomplete e verbose resolution.

## Mapa documental

Usar estes documentos em conjunto:

- `docs/pt-PT/User_Guide_Full.md`: guia completo e Quick Start;
- `docs/pt-PT/ATC_Cookbook.md`: receitas praticas e workflows;
- `docs/pt-PT/Best_Practices.md`: boas praticas de uso e bug reports;
- `docs/pt-PT/Architecture.md`: arquitetura e fluxo de execucao;
- `docs/pt-PT/Developer_Guide.md`: visao geral do codigo;
- `docs/pt-PT/Developer_Reference.md`: checklists e notas praticas;
- `docs/SOFTWARE_REQUIREMENTS_SPECIFICATION.md`: requisitos formais,
  criterios de aceitacao e rastreabilidade;
- `docs/pt-PT/Testing.md`: regressao, cobertura isolada e lacunas manuais.

## O que o ATC nao e

O ATC foca-se em computacao matematica pratica por comandos e nao pretende ser
um CAS universal.

- Nao e substituto de Mathematica, Maple, SageMath ou SymPy.
- Nao prova teoremas matematicos arbitrarios.
- Nao substitui ferramentas profissionais de validacao de engenharia.
- Tem comportamento simbolico apenas onde esta explicitamente suportado e
  testado.

## Recipes / Perfis

Engenharia:

```text
solve equation(x^2-5*x+6)
create matrix(foo\2\2\3)
unit conversions
physics calculations
```

Educacao:

```text
2+3*4
sin(pi/2)
geometry calculations
```

DSP:

```text
sinc(0)
fft(1\0\0\0)
```

Estatistica:

```text
avg(2\4\6)
min(3\_1\2)
max(3\_1\2)
statistics calculations
```

Financas:

```text
financial calculations
100*15/100
```

Menus interativos devem ser tratados como exemplos guiados; outputs estaveis
devem ser documentados apenas quando confirmados por testes.

## Precisao

`higherprecision(1)` ativa Boost `mp_float` apos reinicio. `higherprecision(0)`
volta a `double`. O ficheiro persistente e `higherPrecision.txt`.

## Solver e polinomios

A versao 2.1.7 valida comandos como:

```text
solve equation(x^2-5*x+6)
simplify polynomial((x-2)*(x-3))
solver(sin(x)-0.5)
```

Tambem existem fast paths testados para cancelamento racional e constantes
simbolicas como `pi`, `e` e `pii`.

## Testes

Resultado atual:

```text
Summary: 374 passed, 0 failed
```

Cobertura isolada atual:

```text
Summary: 68 passed, 0 failed
```

Validacao atual do package SourceForge:

```text
Summary: 44 passed, 0 failed
```
