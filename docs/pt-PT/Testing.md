# Testes do Advanced Trigonometry Calculator

Este documento resume a infraestrutura de testes do ATC 2.1.7.

## Suite principal

Executar apos compilar o ATC:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

Resultado validado atual em Release x64 e Release x86:

```text
Summary: 359 passed, 0 failed
```

## Cobertura automatizada

A suite cobre, entre outros:

- aritmetica;
- trigonometria e funcoes hiperbolicas;
- logaritmos;
- numeros complexos;
- matrizes;
- estatistica, DSP e probabilidade;
- simplificacao polinomial;
- solver e equation solver;
- function study;
- graph smoke tests;
- settings persistentes;
- autocomplete e historico;
- TXT processing com mocks seguros;
- modulos interativos com caminhos smoke seguros.

## Fluxo TXT

O fluxo direto `predefine txt` -> `solve txt` usa fixtures temporarias. A suite
cobre aritmetica, `solver`, `solve equation`, `simplify polynomial`, recuperacao
apos linha invalida e abertura mockada do ficheiro de respostas.

O watcher vivo de `auto solve txt` ainda requer fixture multi-processo
deterministica. `roots to polynomial` dentro de `solve txt` tambem deve ser
tratado separadamente antes de entrar na regressao padrao.

## Stress de memoria

Para comandos sensiveis a memoria:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-memory-stress.ps1 -Iterations 10
```

## Limites

Comandos que desligam/reiniciam o PC, abrem janelas externas ou esperam tempo
real longo devem continuar fora da suite automatica padrao ate existirem mocks
seguros.
