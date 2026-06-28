# Cookbook do Advanced Trigonometry Calculator

Versao: ATC 2.1.7  
Idioma: Portugues de Portugal

Este cookbook junta fluxos praticos de utilizacao do ATC. Nao substitui o guia
completo; serve como ponto de partida rapido para tarefas comuns.

Os exemplos com output estavel mostram o resultado esperado. Os modulos
interativos sao descritos como workflows, porque o texto exato pode depender
das opcoes escolhidas e das settings persistentes.

## Calculo cientifico rapido

**Problema:** avaliar uma expressao curta sem criar variaveis.

**Comando(s):**

```text
2+3*4
sin(pi/2)
log(100)
```

**Output esperado:**

```text
14
1
2
```

**Quando usar:** aritmetica rapida, logaritmos e verificacoes
trigonometricas.

**Notas / limites:** os indices `#0`, `#1` dependem dos comandos anteriores na
sessao atual.

## Trigonometria em radianos e graus

**Problema:** alternar entre fluxos em radianos e em graus.

**Comando(s):**

```text
mode
sin(pi/2)
sin(30)
```

**Output esperado:** `sin(pi/2)` e normalmente usado em modo radiano;
`sin(30)` e normalmente usado em modo grau e devolve `0.5`.

**Quando usar:** trigonometria escolar, engenharia e testes com solver onde as
unidades angulares interessam.

**Notas / limites:** confirmar sempre `mode` antes de comparar resultados
trigonometricos.

## Equacao quadratica

**Problema:** resolver uma equacao polinomial suportada.

**Comando(s):**

```text
solve equation(x^2-5*x+6)
```

**Output esperado:**

```text
x1=3
x2=2
```

**Quando usar:** equacoes polinomiais que o ATC consegue normalizar e enviar
para o equation solver.

**Notas / limites:** o ATC nao e um CAS completo. Formas simbolicas nao
suportadas podem seguir fallback ou ser rejeitadas.

## Solver numerico

**Problema:** encontrar uma raiz numericamente quando o comando polinomial
direto nao e o melhor caminho.

**Comando(s):**

```text
solver(x+2)
solver(sin(x)-0.5)
```

**Output esperado:** `solver(x+2)` devolve `-2`. O resultado trigonometrico
depende do modo angular.

**Quando usar:** pesquisa numerica de raizes em expressoes suportadas.

**Notas / limites:** verificar o modo angular e evitar depender de sintaxe nao
documentada.

## Simplificacao de polinomios

**Problema:** expandir ou simplificar uma expressao polinomial suportada.

**Comando(s):**

```text
simplify polynomial((x-2)*(x-3))
```

**Output esperado:**

```text
(1+0i)x^2+(_5+0i)x^1+(6+0i)
```

**Quando usar:** preparar polinomios antes de resolver ou documentar calculos.

**Notas / limites:** o comportamento simbolico existe onde esta implementado e
testado.

## Raizes para polinomio

**Problema:** construir um polinomio a partir de raizes conhecidas.

**Comando(s):**

```text
roots to polynomial(2\3)
```

**Output esperado:** um polinomio de segundo grau com raizes `2` e `3`.

**Quando usar:** workflows tipo Vieta ou criacao de polinomios para testar o
solver.

**Notas / limites:** raizes complexas sao suportadas nas formas documentadas.

## Matrizes

**Problema:** criar e reutilizar uma matriz.

**Comando(s):**

```text
create matrix(foo\2\2\3)
see variables
```

**Output esperado:** o ATC cria a variavel matriz `foo` e lista variaveis com
`see variables`.

**Quando usar:** calculos matriciais repetidos ou exemplos com matriz nomeada.

**Notas / limites:** alguns comandos de matrizes sao interativos. Validar com
matrizes pequenas primeiro.

## Media, minimo e maximo

**Problema:** calcular estatistica descritiva basica numa lista ou matriz.

**Comando(s):**

```text
avg(2\4\6)
min(2\4\6)
max(2\4\6)
```

**Output esperado:**

```text
4
2
6
```

**Quando usar:** resumos estatisticos rapidos.

**Notas / limites:** o ATC 2.1.7 tambem valida `min`, `max` e `avg` com nomes
de variaveis matriz.

## FFT / IFFT

**Problema:** executar um workflow DSP simples.

**Comando(s):**

```text
fft(1\0\0\0)
ifft(1\1\1\1)
```

**Output esperado:** o ATC devolve dados transformados no formato numerico
documentado.

**Quando usar:** verificacoes simples de processamento de sinal e exemplos
educativos de DSP.

**Notas / limites:** confirmar escala e ordenacao no formato do ATC antes de
usar os resultados noutra ferramenta.

## Workflow TXT

**Problema:** processar varios comandos ATC a partir de um ficheiro de texto.

**Comando(s):**

```text
predefine txt
solve txt
eliminate strings
```

**Output esperado:** o ATC le um ficheiro, processa linhas suportadas e escreve
um ficheiro de resposta.

**Quando usar:** calculos em lote, exemplos reprodutiveis e validacao manual
tipo regressao.

**Notas / limites:** comandos que abrem ficheiros ou janelas devem ser
mockados ou contornados em testes automaticos.

## Verbose resolution para debug

**Problema:** perceber como o ATC processa uma expressao.

**Comando(s):**

```text
verbose resolution(1)
sin(pi/6)
verbose resolution(0)
```

**Output esperado:** o ATC imprime informacao intermedia de processamento
enquanto a setting esta ativa.

**Quando usar:** debug do parser e do processamento de expressoes.

**Notas / limites:** o output verbose e diagnostico. Nao deve ser tratado como
contrato estavel salvo quando estiver coberto explicitamente por regressao.

## Modulos guiados

**Problema:** usar modulos de dominio com menus.

**Comando(s):**

```text
financial calculations
geometry calculations
statistics calculations
physics calculations
unit conversions
microeconomics calculations
triangles rectangles solver
arithmetic matrix solver
```

**Output esperado:** cada comando abre o respetivo workflow guiado.

**Quando usar:** quando o calculo e mais facil de expressar por menu do que
numa expressao de uma linha.

**Notas / limites:** os testes automaticos usam smoke paths seguros nestes
modulos. A validacao completa de cada opcao continua manual ou futura.

