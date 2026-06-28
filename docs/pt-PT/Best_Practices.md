# Boas praticas do ATC

Estas praticas ajudam a obter resultados fiaveis no Advanced Trigonometry
Calculator 2.1.7.

## Comecar pequeno

Construir calculos complexos a partir de expressoes menores. Guardar resultados
intermedios em variaveis ou reutilizar referencias como `#0`, `#1` e seguintes.

## Validar parenteses cedo

Quando uma expressao fica longa, testar primeiro os fatores internos. Isto e
especialmente util em expressoes racionais, produtos polinomiais e inputs do
solver.

## Confirmar o modo angular

Usar:

```text
mode
```

antes de calculos trigonometricos. Os modos grau, radiano e gradiano alteram o
significado de comandos como `sin(30)`.

## Usar a sintaxe documentada para negativos

O ATC imprime frequentemente coeficientes negativos com `_`, por exemplo `_5`.
Usar a sintaxe documentada quando se introduzem listas de coeficientes negativas
ou comandos que esperam esse formato.

## Usar verbose resolution para debug

Ativar output diagnostico apenas quando necessario:

```text
verbose resolution(1)
verbose resolution(0)
```

O verbose e util para investigar comportamento do parser, mas os calculos
normais devem geralmente correr com essa setting desligada.

## Escolher o caminho certo de resolucao

Usar `solve equation(...)` para formas polinomiais e equacoes suportadas. Usar
`solver(...)` para workflows numericos de procura de raizes.

## Usar TXT workflows para repeticao

Para lotes de comandos repetidos, usar o workflow TXT em vez de reescrever
sequencias longas. Durante debug, manter o ficheiro pequeno e reprodutivel.

## Guardar exemplos reprodutiveis

Ao reportar um bug, incluir:

- versao exata do ATC;
- modo de precisao;
- modo angular;
- comandos introduzidos;
- resultado esperado;
- resultado obtido;
- se `verbose resolution` estava ativo.

## Respeitar o ambito do ATC

O ATC nao substitui ferramentas profissionais de validacao especificas de
dominio. Em decisoes criticas de engenharia, financas ou ciencia, comparar
resultados importantes com metodos independentes.

## Evitar comportamento nao documentado

Nao construir workflows dependentes de comportamento que nao esteja descrito no
guia, nas notas de release ou nos testes. Os internos do parser e do solver
podem evoluir mantendo o comportamento documentado.

