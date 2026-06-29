# Guia de Utilizador do Advanced Trigonometry Calculator

Este guia resume a utilização do Advanced Trigonometry Calculator (ATC). Não
substitui o guia completo, mas oferece uma entrada rápida para os fluxos
principais.

Para detalhe completo, consultar:

- [Guia Completo de Utilizador](User_Guide_Full.md)
- [Cookbook do ATC](ATC_Cookbook.md)
- [Boas Práticas](Best_Practices.md)
- [Testes](Testing.md)

## O que é o ATC

O ATC é uma aplicação matemática gratuita, open-source e de linha de comandos
para Windows. O utilizador introduz expressões ou comandos documentados e o ATC
devolve resultados na consola.

## O que o ATC não é

O ATC foca-se deliberadamente em computação matemática prática orientada por
comandos, em vez de tentar ser um CAS universal.

- O ATC não é um CAS geral completo como Mathematica, Maple, SageMath ou
  SymPy.
- O ATC não foi desenhado para provar teoremas matemáticos arbitrários.
- O ATC não substitui ferramentas profissionais de validação específicas de
  engenharia.
- Existe comportamento simbólico apenas onde está explicitamente suportado e
  testado.

## Quick Start

```text
2+2
sin(pi/2)
mode
solve equation(x^2-5*x+6)
solver(x+2)
create matrix(foo\2\2\3)
see variables
exit
```

Notas rápidas:

- `_` e o marcador documentado de negativo em várias formas e outputs do ATC;
- `#0`, `#1` e seguintes referem resultados anteriores;
- expressões diretas calculam imediatamente;
- comandos iniciam workflows nomeados;
- módulos guiados abrem menus interativos.

## Expressões básicas

```text
2+3*4
sqrt(9)
sin(pi/2)
log(100)
```

Exemplo de output:

```text
#0=14
#1=3
#2=1
#3=2
```

## Prompt interativo

O prompt suporta:

- `Tab` para completar comandos, funções matemáticas e funções do utilizador;
- `Tab` repetido para alternar entre várias sugestões;
- setas `Up` e `Down` para reutilizar expressões anteriores;
- edição normal com `Left`, `Right`, `Home`, `End`, `Delete` e `Backspace`.

## Modos de ângulo e precisão

O modo angular é configurado com:

```text
mode
```

Modos disponíveis:

```text
radian -> 1
degree -> 2
gradian -> 3
```

A precisão persistente pode alternar entre `double` e Boost `mp_float`:

```text
higherprecision(1)
higherprecision(0)
```

## Exemplos importantes

```text
simplify polynomial((x-2)*(x-3))
solve equation(x^2-5*x+6)
roots to polynomial(2\3)
solver(x+2)
avg(2\4\6)
min(2\4\6)
max(2\4\6)
```

## Matrizes

```text
create matrix(foo\2\2\3)
see variables
```

Para exemplos mais completos, consultar o cookbook.

## TXT processing

O ATC suporta workflows de ficheiros TXT para processar vários comandos:

```text
predefine txt
solve txt
eliminate strings
```

Usar estes fluxos para cálculos em lote e exemplos reprodutíveis.

## Verbose resolution

```text
verbose resolution(1)
verbose resolution(0)
```

O modo verbose ajuda a depurar o processamento de expressões. Para cálculo
normal, deve geralmente estar desligado.

## Boas práticas

- Comecar com expressões pequenas.
- Validar parenteses.
- Confirmar o modo angular.
- Usar `solve equation(...)` para equacoes suportadas.
- Usar `solver(...)` para pesquisa numérica de raizes.
- Guardar exemplos reprodutíveis ao reportar problemas.
- Não usar o ATC como substituto de validação profissional crítica.
