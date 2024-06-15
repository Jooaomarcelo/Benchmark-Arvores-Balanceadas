# Benchmark-Arvores-Balanceadas
 Projeto de Benchmark para analisar o desempenho das árvores de pesquisa AVL e Rubro-Negra
 com a inserção e remoção de 10.000 elementos ordenados, e a operação de pesquisa com 10.000 elementos aleatórios.
 
 Os testes foram feitos em um computador com:
 - Processador: 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz.
 - RAM: 12 GB.
 - Sistema Operacional: Windows 11 Home.

# Organização do Projeto
 ## `/Arvores`: contém todos os arquivos referentes as estruturas de dados do projeto.
   - `arvores.h \ arvores.c`: contém as funções que são semelhantes entre as árvores.
   - `AVL.h \ AVL.c`: contém as funções referentes a AVL.
   - `ARB.h \ ARB.c`: contém as funções referentes a Rubro-Negra.
 ## `/Entrada_Saida`: contém os arquivos que controlam a entrada e saída dos dados.
   - `ES.h \ ES.c`: contém funções como as de criação dos arquivos de análise e dos resultados obtidos.

## Complexidade de tempo
### AVL
| Operação | Caso Médio | Pior Caso |
| --------- | ----------- | --------- |
| **Inserção** | O(log(n)) | O(log(n)) |
| **Pesquisa** | O(log(n)) | O(log(n)) |
| **Remoção** | O(log(n)) | O(log(n)) |


### Rubro-Negra
| Operação | Caso Médio | Pior Caso |
| --------- | ----------- | --------- |
| **Inserção** | O(log(n)) | O(log(n)) |
| **Pesquisa** | O(log(n)) | O(log(n)) |
| **Remoção** | O(log(n)) | O(log(n)) |

## Complexidade de espaço
 Ambas as árvores possuem complexidade de espaço O(N)

## Complexidade de rebalanceamento
 ### AVl
  * **Caso Médio**: O(1)
  * **Pior Caso**: O(log(n))

 ### ARB
  * **Caso Médio**: O(1)
  * **Pior Caso**: O(log(n)) * No caso de ela ter log(n) troca de cores.

## Resultados
| Árvore | Operação | Rotações | Tempo(ms) |
| --------- | --------- | ----------- | --------- |
| AVL | **Inserção** | 9986 | 3,136 |
| AVL | **Pesquisa** | ---- | 2.506 |
| AVL | **Remoção** | 4988 | 1.644 |
| ARB | **Inserção** | 9976 | 2.534 |
| ARB | **Pesquisa** | ---- | 2.606 |
| ARB | **Remoção** | 4989 | 1.294 |
