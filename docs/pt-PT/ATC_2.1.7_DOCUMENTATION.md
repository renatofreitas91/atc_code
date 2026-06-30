# Documentação técnica do Advanced Trigonometry Calculator 2.1.7

Este documento resume o estado técnico do ATC 2.1.7.

## Âmbito

A versão 2.1.7 foca-se em previsibilidade do modo de precisão, correções no
solver e simplificador polinomial, cobertura de regressão, comportamento da
consola Windows 11, memória dinâmica, autocomplete e verbose resolution.


## Memória e scripts

A versão 2.1.7 reduz o consumo de memória em scripts repetitivos. O `processTxt()` liberta arrays temporários de respostas, o `arithSolver()` liberta buffers auxiliares no retorno normal e o `initialProcessor()` só aloca buffers matriciais quando a expressão realmente usa matrizes.

O interpretador de scripts também tem um caminho rápido para `print("...", ...)`: quando a linha é segura, o ATC executa o `print` diretamente em memória e evita o ficheiro temporário usado pelo fluxo TXT tradicional.
## Mapa documental

Usar estes documentos em conjunto:

- `docs/pt-PT/User_Guide_Full.md`: guia completo e Quick Start;
- `docs/pt-PT/ATC_Cookbook.md`: receitas práticas e workflows;
- `docs/pt-PT/Best_Practices.md`: boas práticas de uso e bug reports;
- `docs/pt-PT/Architecture.md`: arquitetura e fluxo de execução;
- `docs/pt-PT/Developer_Guide.md`: visão geral do código;
- `docs/pt-PT/Developer_Reference.md`: checklists e notas práticas;
- `docs/SOFTWARE_REQUIREMENTS_SPECIFICATION.md`: requisitos formais,
  critérios de aceitação e rastreabilidade;
- `docs/pt-PT/Testing.md`: regressão, cobertura isolada e lacunas manuais.

## O que o ATC não é

O ATC foca-se em computação matemática prática por comandos e não pretende ser
um CAS universal.

- Não e substituto de Mathematica, Maple, SageMath ou SymPy.
- Não prova teoremas matemáticos arbitrários.
- Não substitui ferramentas profissionais de validação de engenharia.
- Tem comportamento simbólico apenas onde está explicitamente suportado e
  testado.

## Recipes / Perfis

Engenharia:

```text
solve equation(x^2-5*x+6)
create matrix(foo\2\2\3)
unit conversions
physics calculations
```

Educação:

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

Estatística:

```text
avg(2\4\6)
min(3\_1\2)
max(3\_1\2)
statistics calculations
```

Finanças:

```text
financial calculations
100*15/100
```

Menus interativos devem ser tratados como exemplos guiados; outputs estáveis
devem ser documentados apenas quando confirmados por testes.

## Precisao

`higherprecision(1)` ativa Boost `mp_float` após reinicio. `higherprecision(0)`
volta a `double`. O ficheiro persistente e `higherPrecision.txt`.

## Solver e polinómios

A versão 2.1.7 valida comandos como:

```text
solve equation(x^2-5*x+6)
simplify polynomial((x-2)*(x-3))
solver(sin(x)-0.5)
```

Tambem existem fast paths testados para cancelamento racional e constantes
simbólicas como `pi`, `e` e `pii`.

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
