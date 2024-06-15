# Benchmark-Arvores-Balanceadas
 Projeto de Benchmark para analisar o desempenho das árvores de pesquisa AVL e Rubro-Negra

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

## Complexidade de rebalanceamento por rotação
 - AVl
  Caso Médio: O(1)
  Pior Caso: O(log(n))

 - ARB
  Caso Médio: O(1)
  Pior Caso: O(1)
  * Contudo ela pode ter log(n) troca de cores.