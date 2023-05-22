# Implementação dos algoritmos de teste de equivalência por visão e serialibidade por conflito
Esse projeto foi feito para a disciplina de Bancos de Dados,utilizando a linguagem C e makefile para compilação. 

# Compilação 
Compila a partir do C, utilizando comandos make.  
Para efetuar a compilação, basta e digitar make.
Para excluir todos os arquivos temporários digite make clean,
e para excluir temporários e o executável digite make purge.  
Ao compilar criará um arquivo executável com o nome escalona.

# Execução 
## Entrada
A entrada deve ser feita pela entrada padrão (stdin). O arquivo é formado por uma sequência de linhas, onde cada linha representa uma transação chegando. Cada linha tem 4 campos: o primeiro é o tempo de chegada, o segundo é o identificador da transação, o terceiro é a operação (R=read, W=write, C=commit) e o quarto o atributo que será lido/escrito. Estas linhas estão ordenadas pelo primeiro campo (tempos menores no início indicando a linha do tempo).

Leitura dos comandos por linha separados por quatro campos, _tempo cheagada_,_id da transação_,_operação_,_atributo em que ocorre o comando_, através da entrada padrão (stdin). 

## Saída
![image](https://github.com/Rubens-Zan/Transaction-escalation/assets/80857600/93a3927d-4836-4b12-9cee-48d236ecf3f3)


A saída ocorre através da saída padrão, sendo que cada linha é composta por um escalonamento do agendamento recebido, sendo representado por 4 campos:  
(_identificador do escalonamento_,_lista de transações_,_serialidade do escalonamento_,_equivalência do escalonamento por visão_). 
A saída deve ser feita pela saída padrão (stdout). O arquivo será composto por uma sequência de linhas. Uma linha para cada escalonamento. Cada linha tem 4 campos separados por espaço (um único espaço entre cada par de campos). O primeiro campo é o identificador do escalonamento. O segundo campo é a lista de transações. E o terceiro apresenta o resultado do algoritmo da garantia da seriabilidade, onde SS e NS significam respectivamente serial (SS) ou não serial (NS). O quarto campo é o resultado do algoritmo de teste de equivalência de visão, onde SV e NV significam respectivamente equivalente (SV) ou não equivalente (NV) 


# Algoritmos
![image](https://github.com/Rubens-Zan/Transaction-escalation/assets/80857600/6f355d27-afb7-47bd-8a87-9469bab39897)

## Algoritmo de equivalência por visão
Utiização de função auxiliares, para efetuar as permutações das transações por meio de adaptações no algoritmo de permutação por backtracking. As permutações são traduzidas para apenas aquelas em que não ocorre mudança na order dos comandos em uma mesma transação.

### Condições
Dois agendamentos S e S' são equivalentes por visão, se atenderem as seguintes condições:
O mesmo conjunto de transações e operações participam em S e S'
Para cada r(x) de Ti, se o valor de x lido for escrito por w(x) de Tj, o mesmo deve permanecer para r(x) de Ti em S'
Se o operador w(y) em Tk é a ultima escrita de y em S, então w(y) em Tk deve ser a última escrita em S'

## Algoritmo de seriação de conflito
Utiliza um algoritmo baseado em busca em profundidade sobre um grafo para detectar se existe um ciclo no mesmo. O grafo é construido criando arestas direcionadas (dependências) entre os vertices (transações) de acordo com as operações efetuadas por transações num agendamento. 

### Condições
Crie um nó para cada T do escalonamento S
Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
S é serial se não existe ciclo no grafo

## Autor 
Rubens Zandomenighi Laszlo e Julio L. Martins 
