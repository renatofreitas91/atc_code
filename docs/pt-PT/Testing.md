# Testes do Advanced Trigonometry Calculator

Este documento resume a infraestrutura de testes do ATC 2.1.7.

## Suite principal

Executar apos compilar o ATC:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

Resultado validado atual em Release x64 e Release x86:

```text
Summary: 360 passed, 0 failed
```

Cobertura isolada atual:

```text
Summary: 68 passed, 0 failed
```

Validacao atual do package SourceForge:

```text
Summary: 44 passed, 0 failed
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

O watcher `auto solve txt` tem agora fixture runtime deterministica: usa um
ficheiro TXT real com `SOLVE_NOW`, valida que a flag e consumida, confirma o
ficheiro `_answers.txt` e regista a abertura do ficheiro por mock. `roots to
polynomial` dentro de `solve txt` ainda deve ser tratado separadamente antes de
entrar na regressao padrao.

## Stress de memoria

Para comandos sensiveis a memoria:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-memory-stress.ps1 -Iterations 10
```

## Limites

Comandos que desligam/reiniciam o PC, abrem janelas externas ou esperam tempo
real longo devem continuar fora da suite automatica padrao ate existirem mocks
seguros.

## Validacao do package SourceForge

O runner de validacao do package e:

```text
tests\run-atc-package-validation.ps1
```

Valida a estrutura preparada para SourceForge sem reconstruir o ZIP. A cobertura
inclui ficheiros raiz, executaveis e launchers x64/x86, PDFs de documentacao,
ausencia de pastas `Source code` duplicadas, ausencia de ficheiros `_answers.txt`
gerados, referencias GitHub/source e consistencia SHA256 de todos os ficheiros
empacotados.

Exemplo:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-package-validation.ps1
```

## Ligacao entre documentacao e testes

Comportamento documentado deve ter cobertura automatica sempre que for
deterministico e seguro com input redirecionado.

Regras ao atualizar documentacao:

- exemplos estaveis devem ser adicionados a suite de regressao quando
  praticavel;
- modulos interativos devem ter pelo menos smoke test seguro ou nota explicita
  de validacao manual;
- comandos que abrem janelas, ficheiros, browsers ou acoes de PC devem usar
  mocks, checks source-level ou notas manuais;
- nao atualizar a contagem documentada de testes sem executar a suite;
- atualizar `tests\ATC_USER_GUIDE_COVERAGE.md` quando uma area documentada
  ganha ou perde cobertura.

O Cookbook e as Boas Praticas devem usar comandos ja documentados. Se uma
receita nao puder ser testada com seguranca, deve indicar isso nas notas ou
limitacoes.
