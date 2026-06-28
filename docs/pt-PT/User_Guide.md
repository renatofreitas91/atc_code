# Guia de Utilizador do Advanced Trigonometry Calculator

Este guia resume a utilizacao do Advanced Trigonometry Calculator (ATC). Nao
substitui o guia completo, mas oferece uma entrada rapida para os fluxos
principais.

Para detalhe completo, consultar:

- [Guia Completo de Utilizador](User_Guide_Full.md)
- [Cookbook do ATC](ATC_Cookbook.md)
- [Boas Praticas](Best_Practices.md)
- [Testes](Testing.md)

## O que e o ATC

O ATC e uma aplicacao matematica gratuita, open-source e de linha de comandos
para Windows. O utilizador introduz expressoes ou comandos documentados e o ATC
devolve resultados na consola.

## O que o ATC nao e

O ATC foca-se deliberadamente em computacao matematica pratica orientada por
comandos, em vez de tentar ser um CAS universal.

- O ATC nao e um CAS geral completo como Mathematica, Maple, SageMath ou
  SymPy.
- O ATC nao foi desenhado para provar teoremas matematicos arbitrarios.
- O ATC nao substitui ferramentas profissionais de validacao especificas de
  engenharia.
- Existe comportamento simbolico apenas onde esta explicitamente suportado e
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

Notas rapidas:

- `_` e o marcador documentado de negativo em varias formas e outputs do ATC;
- `#0`, `#1` e seguintes referem resultados anteriores;
- expressoes diretas calculam imediatamente;
- comandos iniciam workflows nomeados;
- modulos guiados abrem menus interativos.

## Expressoes basicas

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

- `Tab` para completar comandos, funcoes matematicas e funcoes do utilizador;
- `Tab` repetido para alternar entre varias sugestoes;
- setas `Up` e `Down` para reutilizar expressoes anteriores;
- edicao normal com `Left`, `Right`, `Home`, `End`, `Delete` e `Backspace`.

## Modos de angulo e precisao

O modo angular e configurado com:

```text
mode
```

Modos disponiveis:

```text
radian -> 1
degree -> 2
gradian -> 3
```

A precisao persistente pode alternar entre `double` e Boost `mp_float`:

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

O ATC suporta workflows de ficheiros TXT para processar varios comandos:

```text
predefine txt
solve txt
eliminate strings
```

Usar estes fluxos para calculos em lote e exemplos reprodutiveis.

## Verbose resolution

```text
verbose resolution(1)
verbose resolution(0)
```

O modo verbose ajuda a depurar o processamento de expressoes. Para calculo
normal, deve geralmente estar desligado.

## Boas praticas

- Comecar com expressoes pequenas.
- Validar parenteses.
- Confirmar o modo angular.
- Usar `solve equation(...)` para equacoes suportadas.
- Usar `solver(...)` para pesquisa numerica de raizes.
- Guardar exemplos reprodutiveis ao reportar problemas.
- Nao usar o ATC como substituto de validacao profissional critica.
