# Projeto SuperComp 

## Maratona de Filmes
Você quer passar um final de semana assistindo ao máximo de filmes possível, mas há restrições quanto aos horários disponíveis e ao número de títulos que podem ser vistos em cada categoria (comédia, drama, ação, etc).

Entrada: Um inteiro N representando o número de filmes disponíveis para assistir e N trios de inteiros (H[i], F[i], C[i]), representando a hora de início, a hora de fim e a categoria do i-ésimo filme. Além disso, um inteiro M representando o número de categorias e uma lista de M inteiros representando o número máximo de filmes que podem ser assistidos em cada categoria.

Saída: Um inteiro representando o número máximo de filmes que podem ser assistidos de acordo com as restrições de horários e número máximo por categoria.

## Heurística Gulosa
A primeira implementação da heurística para nosso projeto consiste em uma implementação gulosa (Greedy).

Implemente uma versão gulosa que ordena os filmes por hora de fim crescente e escolhe aqueles que começam primeiro e não conflitam com os filmes já escolhidos, além de verificar se há vagas disponíveis na categoria do filme.

## Aleatoriedade
Como vimos em aula, aleatoriedade é uma estratégia bastante comum para construção de algoritmos de busca local, podendo ser usada de forma isolada ou de forma complementar a outra estratégia de varredura de um espaço de soluções.

Essa implementação consiste na adaptação da heurística gulosa de nosso projeto. A proposta é que você modifique a sua heurística gulosa de modo que ao longo da seleção de um filme você tenha 25% de chance de pegar outro filme qualquer que respeite o horário. Isso fará com que sua heurística tenha um pouco mais de exploration e possamos ter alguns resultados melhores.

## Paralelismo com OpenMP
Até agora experimentamos heurísticas que buscaram resolver o nosso problema em um tempo razoável, sem garantias de otimalidade. É chegado o momento de incorporar o paralelismo de tarefas em nossas alternativas de resolução.

Para isso, você deve modificar a versão exaustiva de sua implementação. Você pode fazer uso da diretiva #pragma omp parallel for para distribuir as iterações de um loop entre as threads disponíveis. Dentro do loop, você pode fazer a verificação de cada filme e, caso ele esteja dentro das restrições de horário e categoria, incrementar uma variável compartilhada count. Observe que por ser uma variável compartilhada, você precisa preservar essa região crítica entre as threads.

Vale ressaltar que o uso do OpenMP não necessariamente irá garantir um desempenho melhor, pois a paralelização tem um overhead que pode acabar diminuindo a performance do programa em alguns casos. É importante fazer testes para verificar se a utilização do OpenMP é realmente benéfica para o problema em questão.

## Paralelismo com GPU
Esta etapa do projeto consiste em resolver nosso problema por meio da biblioteca Thrust. Sua tarefa é realizar essa implementação em C++ com a Thrust e comparar o desempenho frente as demais implementações.

[Relatório](report.ipynb)
