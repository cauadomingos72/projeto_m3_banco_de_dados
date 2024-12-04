# Sistema de Gerenciamento de Livraria com MySQL

Este projeto é um **Sistema de Gerenciamento de Livraria** que utiliza a linguagem C para interação com um banco de dados MySQL. Ele permite o gerenciamento de livros, clientes e empréstimos em uma livraria por meio de um menu interativo.  

---

## **Funcionalidades**

O sistema oferece as seguintes opções:  

### **Livros**
1. **Listar Livros:** Exibe todos os livros cadastrados no banco de dados.  
2. **Adicionar Livro:** Permite cadastrar um novo livro.  
3. **Editar Livro:** Atualiza os dados de um livro existente.  
4. **Excluir Livro:** Remove um livro do banco de dados.  

### **Clientes**
5. **Listar Clientes:** Exibe todos os clientes cadastrados.  
6. **Adicionar Cliente:** Permite cadastrar um novo cliente.  
7. **Excluir Cliente:** Remove um cliente e seus empréstimos associados.  

### **Empréstimos**
8. **Listar Empréstimos:** Exibe todos os empréstimos realizados.  
9. **Adicionar Empréstimo:** Registra um novo empréstimo associando livro, cliente e datas.  
10. **Excluir Empréstimo:** Remove um empréstimo específico.  

### **Geral**
- **Sair:** Encerra o programa.  

---

## **Estrutura do Banco de Dados**

O sistema trabalha com as seguintes tabelas no MySQL:  

### **Tabela `livros`**
| Campo     | Tipo        | Descrição             |
|-----------|-------------|-----------------------|
| `id`      | INT         | ID único do livro     |
| `nome`    | VARCHAR(100)| Nome do livro         |
| `autor`   | VARCHAR(100)| Autor do livro        |
| `genero`  | VARCHAR(50) | Gênero literário      |
| `edicao`  | VARCHAR(10) | Edição do livro       |
| `editora` | VARCHAR(100)| Editora do livro      |

### **Tabela `clientes`**
| Campo     | Tipo        | Descrição            |
|-----------|-------------|----------------------|
| `id`      | INT         | ID único do cliente  |
| `nome`    | VARCHAR(100)| Nome do cliente      |
| `cpf`     | VARCHAR(15) | CPF do cliente       |
| `telefone`| VARCHAR(20) | Telefone do cliente  |
| `email`   | VARCHAR(100)| Email do cliente     |

### **Tabela `emprestimos`**
| Campo             | Tipo        | Descrição                          |
|--------------------|-------------|------------------------------------|
| `id`              | INT         | ID único do empréstimo             |
| `livro_id`        | INT         | ID do livro emprestado             |
| `cliente_id`      | INT         | ID do cliente que fez o empréstimo |
| `data_emprestimo` | DATE        | Data do empréstimo                 |
| `data_devolucao`  | DATE        | Data prevista para devolução        |

---

## **Pré-Requisitos**

1. **MySQL Server** instalado e em execução.
2. Biblioteca **MySQL C API** (inclusa no MySQL Connector C).
3. Ambiente para compilar e executar programas em C, como GCC.

---

## **Configuração e Execução**

1. **Crie o Banco de Dados e as Tabelas**
   Execute o script SQL para criar as tabelas `livros`, `clientes` e `emprestimos` no seu banco de dados MySQL.

```sql
CREATE DATABASE livraria;

USE livraria;

CREATE TABLE livros (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100),
    autor VARCHAR(100),
    genero VARCHAR(50),
    edicao VARCHAR(10),
    editora VARCHAR(100)
);

CREATE TABLE clientes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100),
    cpf VARCHAR(15),
    telefone VARCHAR(20),
    email VARCHAR(100)
);

CREATE TABLE emprestimos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    livro_id INT,
    cliente_id INT,
    data_emprestimo DATE,
    data_devolucao DATE,
    FOREIGN KEY (livro_id) REFERENCES livros(id),
    FOREIGN KEY (cliente_id) REFERENCES clientes(id)
);
```sql

a


