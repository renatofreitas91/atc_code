# Guia de Utilizador do Advanced Trigonometry Calculator

Este guia resume a utilização do Advanced Trigonometry Calculator (ATC). Nao
substitui o guia completo distribuido com a aplicacao, mas oferece uma entrada
rapida para os fluxos principais.

## O que e o ATC

O ATC e uma aplicacao matematica gratuita, open source e de linha de comandos
para Windows. O utilizador introduz expressoes ou comandos documentados e o ATC
devolve resultados na consola.

## O que o ATC nao e

O ATC foca-se deliberadamente em computacao matematica pratica orientada por
comandos, em vez de tentar ser um CAS universal.

- O ATC nao e um CAS geral completo como Mathematica, Maple, SageMath ou
  SymPy.
- O ATC nao foi desenhado para provar simbolicamente teoremas matematicos
  arbitrarios.
- O ATC nao substitui ferramentas profissionais de validacao especificas de
  engenharia.
- O ATC foca-se em calculo numerico, fluxos por comandos, uso educativo,
  funcionalidades hibridas simbolicas/numericas implementadas e execucao local
  rapida.
- Existe algum comportamento simbolico, mas apenas onde esta explicitamente
  suportado e testado.

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

## Matrizes

```text
create matrix(foo\2\2\3)
min(foo)
max(foo)
avg(foo)
```

## Polinomios e equacoes

```text
simplify polynomial((x-2)*(x-3))
roots to polynomial(2\3)
solve equation(x^2-5*x+6)
solve quadratic equation(1\_5\6)
solve equations system(1\1\5;1\_1\1)
```

## Solver

```text
solver(sin(x)-0.5)
solver(x^2-12x-9)
```

O comportamento depende do tipo de expressao, do modo angular configurado e do
caminho de solver disponivel.

## Recipes / Perfis de utilizacao

### Engenharia

Objetivo: resolver uma equacao polinomial suportada.

```text
solve equation(x^2-5*x+6)
```

Output esperado:

```text
x1=3
x2=2
```

Use quando a equacao encaixa nos caminhos documentados do solver.

Objetivo: usar conversoes ou fisica guiada.

```text
unit conversions
physics calculations
```

Output esperado: example placeholder, porque estes fluxos sao menus
interativos.

Objetivo: criar e reutilizar uma matriz.

```text
create matrix(foo\2\2\3)
foo+foo
```

### Educacao

Objetivo: demonstrar precedencia.

```text
2+3*4
```

Output esperado:

```text
#0=14
```

Objetivo: validar trigonometria em radianos.

```text
sin(pi/2)
```

Output esperado:

```text
#0=1
```

Objetivo: usar geometria guiada.

```text
geometry calculations
```

Output esperado: example placeholder.

### DSP

Objetivo: avaliar uma funcao de sinal.

```text
sinc(0)
```

Output esperado:

```text
#0=1
```

Objetivo: executar FFT num vetor curto.

```text
fft(1\0\0\0)
```

### Estatistica

Objetivo: calcular media.

```text
avg(2\4\6)
```

Output esperado:

```text
#0=4
```

Objetivo: minimo e maximo.

```text
min(3\_1\2)
max(3\_1\2)
```

Outputs esperados:

```text
#0=-1
#1=3
```

### Financas

Objetivo: abrir calculos financeiros guiados.

```text
financial calculations
```

Output esperado: example placeholder.

Objetivo: percentagem simples por aritmetica.

```text
100*15/100
```

Output esperado:

```text
#0=15
```

## Mais ajuda

Dentro do ATC:

```text
user guide
current settings
```
