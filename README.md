# WMMA 2025

## Sumário
  * [Introdução](#introdução)
  * [Metodologia](#metodologia)
  * [Resultados](#resultados)
  * [Visualização dos Resultados](#visualização-dos-resultados)
  * [Discussão e Conclusão](#discussão-e-conclusão)
  * [Membros](#membros)

## Introdução

Esta análise é uma comparação entre os métodos de interpolação de Newton, Lagrange e Cubic Spline, focando em critérios de precisão, desempenho computacional e estabilidade. O objetivo é fornecer um guia prático sobre a adequação de cada algoritmo para diferentes cenários de aplicação. Para esta avaliação, os métodos foram submetidos a um conjunto diversificado de funções, incluindo polinomiais, trigonométricas, exponenciais, logarítmicas, a clássica função de Runge e uma função degrau para simular mudanças súbitas.

## Metodologia

A metodologia experimental foi executada no intervalo de [-1, 1], com o número de pontos de amostragem (N) variando de 10 a 100, com incrementos de 10. Para cada configuração, a análise quantificou três métricas distintas: o custo de pré-processamento; o tempo médio de avaliação sobre 10.000 iterações com pontos aleatórios; e a precisão mensurada através do erro absoluto médio.

## Resultados

Os resultados empíricos revelam comportamentos fundamentalmente distintos entre os métodos avaliados. O método Cubic Spline demonstrou uma convergência estável, na qual o erro absoluto médio diminuiu consistentemente com o aumento do número de pontos (N) para todas as funções contínuas testadas. Em contrapartida, os métodos baseados em um único polinômio de alto grau, Newton e Lagrange, exibiram severa instabilidade numérica. Para a maioria das funções, observa-se uma clara divergência no erro a partir de N≈70 (Lagrange) e N≈80 (Newton), onde os valores de erro crescem de forma exponencial. Esta instabilidade manifestou-se ainda mais cedo em cenários específicos: para a função de Runge, a divergência iniciou-se em N≈30, e para a função degrau, que viola a premissa de continuidade, em N≈40.

## Visualização dos gráficos

### Gráficos de Erro por Método

**Método de Newton**
![Método de Newton](/plots/error_Newton.png)

**Método de Lagrange**
![Método de Lagrange](/plots/error_Lagrange.png)

**Método Cubic Spline**
![Método de Cubic Spline](/plots/error_Cubic_Spline.png)

### Gráfico de complexidade de tempo


## Discussão e Conclusão

Do ponto de vista computacional, a análise de complexidade corrobora os tempos medidos. Embora numericamente instáveis para N elevado, a interpolação de Newton apresenta uma vantagem de desempenho sobre a de Lagrange quando múltiplas avaliações são necessárias. Seu custo de pré-processamento para a construção da tabela de diferenças divididas é de O(n²), mas cada avaliação subsequente possui um custo de apenas O(n). O método de Lagrange, por sua vez, não possui etapa de pré-processamento, mas incorre num custo de O(n²) para cada ponto interpolado. O método Cubic Spline, embora apresente um erro inicial ligeiramente superior para valores muito baixos de N, prova ser a abordagem mais robusta após certa quantidade de número de pontos.

## Membros
  * Vinícius Piotto
  * Maicon Mian
  * Pedro Botelho
  * Ângela Moreno