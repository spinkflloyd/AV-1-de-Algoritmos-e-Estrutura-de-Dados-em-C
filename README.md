<div align="center">

# 💻 AED I · Atividade Avaliativa I 💻

---

## 📖 Sobre o projeto

Códigos feitos para a primeira avaliação da disciplina de **AED I**. As questões foram disponibilizadas pelo professor com a estrutura principal (`main`) já implementada, sendo necessário complementar as soluções com a implementação dos subprogramas solicitados em cada questão.

## 🎓 Sobre a avaliação

| | |
|---|---|
| 📘 **Disciplina** | Algoritmos e Estruturas de Dados I |
| 🗓️ **Semestre** | 2026.1 |
| 💡 **Linguagem** | C |

<div align="left">

### 📏 Regras da atividade

- O código que já vinha pronto **não podia ser alterado**.
- O código novo só podia ser inserido nos trechos marcados com `\\ SEU CÓDIGO AQUI`.
- Todos os subprogramas com código faltante precisavam ser implementados, mesmo os que não eram usados na solução.

### 1️⃣ Inversão de fila

Implementar `queue_invert(Queue *q)`, que retorna uma **nova** fila com os elementos de `q` em ordem reversa, usando uma pilha como estrutura auxiliar. A fila original não pode ser modificada.

- A pilha é implementada em um **vetor** de tamanho `MAX_STACK_SIZE`, sem um campo `top` explícito: o índice do topo fica guardado na primeira posição do vetor, e os dados, da segunda em diante.
- A fila é uma **lista encadeada simples** alocada na heap.
- O segundo teste usa uma fila de 15 elementos, acima da capacidade da pilha, então a fila invertida tem só 9 elementos (conforme a saída esperada pelo enunciado).

### 2️⃣ Lista palíndromo

Implementar `list_ispalindrome(List *l)`, que verifica se uma lista é lida da mesma forma nos dois sentidos (como `1 → 2 → 2 → 1` e `1 → 2 → 3 → 2 → 1`).

- A verificação usa uma **pilha implementada como lista encadeada simples**.
- A lista deve ser percorrida **apenas uma vez**: dois ponteiros (um lento e um rápido) empilham a primeira metade, que depois é comparada com a segunda metade.
- Funciona para tamanhos par e ímpar, e a lista vazia ou com um elemento conta como palíndromo.

### 3️⃣ Fila de prioridade

Um sistema de atendimento recebe solicitações com prioridade **baixa**, **média** ou **alta**. A fila deve permitir:

1. Adicionar uma solicitação com a prioridade especificada.
2. Remover a próxima solicitação de **maior prioridade** (entre prioridades iguais, a que entrou primeiro).
3. Retornar o número de solicitações na fila.

- A fila é uma **única lista duplamente encadeada**, com os nós alocados dinamicamente.

<div align="center">

## 🛠️ Tecnologias

| Linguagem |
|---|
| ![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black) |
