# Cookbook do Advanced Trigonometry Calculator

Versão: ATC 2.1.7
Idioma: Português de Portugal

Este cookbook junta fluxos praticos de utilização do ATC. Não substitui o guia
completo; serve como ponto de partida rápido para tarefas comuns.

Os exemplos com output estavel mostram o resultado esperado. Os módulos
interativos são descritos como workflows, porque o texto exato pode depender
das opções escolhidas e das settings persistentes.

## Calculo cientifico rápido

**Problema:** avaliar uma expressão curta sem criar variáveis.

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

**Quando usar:** aritmética rápida, logaritmos e verificacoes
trigonométricas.

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

**Notas / limites:** o ATC não é um CAS completo. Formas simbólicas não
suportadas podem seguir fallback ou ser rejeitadas.

## Solver numérico

**Problema:** encontrar uma raiz numericamente quando o comando polinomial
direto não é o melhor caminho.

**Comando(s):**

```text
solver(x+2)
solver(sin(x)-0.5)
```

**Output esperado:** `solver(x+2)` devolve `-2`. O resultado trigonometrico
depende do modo angular.

**Quando usar:** pesquisa numérica de raizes em expressões suportadas.

**Notas / limites:** verificar o modo angular e evitar depender de sintaxe não
documentada.

## Simplificacao de polinómios

**Problema:** expandir ou simplificar uma expressão polinomial suportada.

**Comando(s):**

```text
simplify polynomial((x-2)*(x-3))
```

**Output esperado:**

```text
(1+0i)x^2+(_5+0i)x^1+(6+0i)
```

**Quando usar:** preparar polinómios antes de resolver ou documentar cálculos.

**Notas / limites:** o comportamento simbólico existe onde esta implementado e
testado.

## Raizes para polinómio

**Problema:** construir um polinómio a partir de raizes conhecidas.

**Comando(s):**

```text
roots to polynomial(2\3)
```

**Output esperado:** um polinómio de segundo grau com raizes `2` e `3`.

**Quando usar:** workflows tipo Vieta ou criacao de polinómios para testar o
solver.

**Notas / limites:** raizes complexas são suportadas nas formas documentadas.

## Matrizes

**Problema:** criar e reutilizar uma matriz.

**Comando(s):**

```text
create matrix(foo\2\2\3)
see variables
```

**Output esperado:** o ATC cria a variavel matriz `foo` e lista variáveis com
`see variables`.

**Quando usar:** cálculos matriciais repetidos ou exemplos com matriz nomeada.

**Notas / limites:** alguns comandos de matrizes são interativos. Validar com
matrizes pequenas primeiro.

## Media, minimo e maximo

**Problema:** calcular estatística descritiva básica numa lista ou matriz.

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

**Quando usar:** resumos estatisticos rápidos.

**Notas / limites:** o ATC 2.1.7 também valida `min`, `max` e `avg` com nomes
de variáveis matriz.

## FFT / IFFT

**Problema:** executar um workflow DSP simples.

**Comando(s):**

```text
fft(1\0\0\0)
ifft(1\1\1\1)
```

**Output esperado:** o ATC devolve dados transformados no formato numérico
documentado.

**Quando usar:** verificacoes simples de processamento de sinal e exemplos
educativos de DSP.

**Notas / limites:** confirmar escala e ordenacao no formato do ATC antes de
usar os resultados noutra ferramenta.

## Workflow TXT

**Problema:** processar vários comandos ATC a partir de um ficheiro de texto.

**Comando(s):**

```text
predefine txt
solve txt
eliminate strings
```

**Output esperado:** o ATC le um ficheiro, processa linhas suportadas e escreve
um ficheiro de resposta.

**Quando usar:** cálculos em lote, exemplos reprodutíveis e validação manual
tipo regressão.

**Notas / limites:** comandos que abrem ficheiros ou janelas devem ser
mockados ou contornados em testes automáticos.

## Verbose resolution para debug

**Problema:** perceber como o ATC processa uma expressão.

**Comando(s):**

```text
verbose resolution(1)
sin(pi/6)
verbose resolution(0)
```

**Output esperado:** o ATC imprime informação intermedia de processamento
enquanto a setting esta ativa.

**Quando usar:** debug do parser e do processamento de expressões.

**Notas / limites:** o output verbose e diagnostico. Não deve ser tratado como
contrato estavel salvo quando estiver coberto explicitamente por regressão.

## Modulos guiados

**Problema:** usar módulos de dominio com menus.

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

**Quando usar:** quando o cálculo e mais fácil de expressar por menu do que
numa expressão de uma linha.

**Notas / limites:** os testes automáticos usam smoke paths seguros nestes
módulos. A validação completa de cada opção continua manual ou futura.
