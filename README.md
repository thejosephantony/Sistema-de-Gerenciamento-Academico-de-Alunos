# 📚 Sistema de Gerenciamento de Alunos e Histórico Acadêmico

Este projeto implementa um **sistema de gerenciamento acadêmico em linguagem C**, utilizando **estruturas de dados dinâmicas**, com foco em **listas encadeadas simples e duplamente encadeadas**.  
O sistema permite cadastrar alunos, gerenciar disciplinas cursadas e consultar históricos acadêmicos por meio de um **menu interativo no terminal**.

---

## 🎯 Objetivo do Projeto

Aplicar na prática os principais conceitos da disciplina de **Estrutura de Dados**, tais como:

- Uso de `struct`
- Alocação dinâmica de memória
- Listas simplesmente encadeadas
- Listas duplamente encadeadas
- Manipulação de ponteiros
- Modularização de funções
- Entrada e saída de dados em C

---

## ⚙️ Funcionalidades do Sistema

O sistema oferece as seguintes opções ao usuário:

- **Cadastrar aluno**
- **Cadastrar disciplina de aluno**
- **Exibir lista de alunos**
- **Remover aluno**
- **Exibir histórico de um aluno**
- **Atualizar disciplina de um aluno**
- **Sair do sistema**

---

## 🧱 Estruturas de Dados Utilizadas

### 👤 Aluno
Representa um aluno cadastrado no sistema.

**Campos:**
- Nome
- Matrícula
- Ponteiro para o aluno anterior
- Ponteiro para o próximo aluno
- Ponteiro para o histórico de disciplinas

➡️ Implementado como **lista duplamente encadeada**

---

### 📘 Histórico
Representa o histórico acadêmico de um aluno.

**Campos:**
- Ponteiro para a primeira disciplina
- Ponteiro para a última disciplina

---

### 📕 Disciplina
Representa uma disciplina cursada por um aluno.

**Campos:**
- Nome da disciplina
- Nota final
- Frequência (%)
- Período letivo
- Status da disciplina
- Ponteiro para a próxima disciplina

➡️ Implementado como **lista simplesmente encadeada**

---

## 📌 Regras para Status da Disciplina

O status da disciplina é definido automaticamente conforme os critérios:

- **TR** – Disciplina trancada
- **RF** – Reprovado por falta (presença < 50%)
- **AP** – Aprovado (nota ≥ 5.0)
- **RM** – Reprovado por média (nota < 5.0)

---

