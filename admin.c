#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\Program Files\MySQL\MySQL Server 8.0\include\mysql.h"

// Função para limpar a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para conectar ao banco de dados
MYSQL* conectarBanco() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "1234", "livraria", 3306, NULL, 0)) {
        printf("Erro ao conectar ao MySQL: %s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

// Função para listar livros
void listarLivros(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM livros")) {
        printf("Erro ao buscar livros: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    printf("\n--- Lista de Livros ---\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("ID: %s | Nome: %s | Autor: %s | Gênero: %s | Edição: %s | Editora: %s\n",
               row[0], row[1], row[2], row[3], row[4], row[5]);
    }
    mysql_free_result(res);
}

// Função para listar clientes
void listarClientes(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM clientes")) {
        printf("Erro ao buscar clientes: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    printf("\n--- Lista de Clientes ---\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("ID: %s | Nome: %s | CPF: %s | Telefone: %s | Email: %s\n",
               row[0], row[1], row[2], row[3], row[4]);
    }
    mysql_free_result(res);
}

// Função para listar empréstimos
void listarEmprestimos(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM emprestimos")) {
        printf("Erro ao buscar empréstimos: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    printf("\n--- Lista de Empréstimos ---\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("ID: %s | Livro ID: %s | Cliente ID: %s | Data de Empréstimo: %s | Data de Devolução: %s\n",
               row[0], row[1], row[2], row[3], row[4]);
    }
    mysql_free_result(res);
}

// Função para adicionar um empréstimo
void adicionarEmprestimo(MYSQL *conn) {
    int livro_id, cliente_id;
    char data_emprestimo[20], data_devolucao[20];
    char query[500];

    printf("\n--- Adicionar Empréstimo ---\n");
    printf("ID do Livro: ");
    scanf("%d", &livro_id);
    printf("ID do Cliente: ");
    scanf("%d", &cliente_id);
    printf("Data de Empréstimo (YYYY-MM-DD): ");
    scanf(" %[^\n]", data_emprestimo);
    printf("Data de Devolução (YYYY-MM-DD): ");
    scanf(" %[^\n]", data_devolucao);

    snprintf(query, sizeof(query),
             "INSERT INTO emprestimos (livro_id, cliente_id, data_emprestimo, data_devolucao) "
             "VALUES (%d, %d, '%s', '%s')",
             livro_id, cliente_id, data_emprestimo, data_devolucao);

    if (mysql_query(conn, query)) {
        printf("Erro ao adicionar empréstimo: %s\n", mysql_error(conn));
    } else {
        printf("Empréstimo adicionado com sucesso!\n");
    }
}

// Função para excluir um empréstimo
void excluirEmprestimo(MYSQL *conn) {
    int id;
    char query[200];

    printf("\n--- Excluir Empréstimo ---\n");
    printf("ID do Empréstimo a excluir: ");
    scanf("%d", &id);

    snprintf(query, sizeof(query), "DELETE FROM emprestimos WHERE id=%d", id);

    if (mysql_query(conn, query)) {
        printf("Erro ao excluir empréstimo: %s\n", mysql_error(conn));
    } else {
        printf("Empréstimo excluído com sucesso!\n");
    }
}

// Função para adicionar um livro
void adicionarLivro(MYSQL *conn) {
    char nome[100], autor[100], genero[50], edicao[10], editora[100];
    char query[500];

    printf("\n--- Adicionar Livro ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Autor: ");
    scanf(" %[^\n]", autor);
    printf("Gênero: ");
    scanf(" %[^\n]", genero);
    printf("Edição: ");
    scanf(" %[^\n]", edicao);
    printf("Editora: ");
    scanf(" %[^\n]", editora);

    snprintf(query, sizeof(query),
             "INSERT INTO livros (nome, autor, genero, edicao, editora) VALUES ('%s', '%s', '%s', '%s', '%s')",
             nome, autor, genero, edicao, editora);

    if (mysql_query(conn, query)) {
        printf("Erro ao adicionar livro: %s\n", mysql_error(conn));
    } else {
        printf("Livro adicionado com sucesso!\n");
    }
}

// Função para editar um livro
void editarLivro(MYSQL *conn) {
    int id;
    char nome[100], autor[100], genero[50], edicao[10], editora[100];
    char query[500];

    printf("\n--- Editar Livro ---\n");
    printf("ID do Livro a editar: ");
    scanf("%d", &id);

    printf("Novo Nome: ");
    scanf(" %[^\n]", nome);
    printf("Novo Autor: ");
    scanf(" %[^\n]", autor);
    printf("Novo Gênero: ");
    scanf(" %[^\n]", genero);
    printf("Nova Edição: ");
    scanf(" %[^\n]", edicao);
    printf("Nova Editora: ");
    scanf(" %[^\n]", editora);

    snprintf(query, sizeof(query),
             "UPDATE livros SET nome='%s', autor='%s', genero='%s', edicao='%s', editora='%s' WHERE id=%d",
             nome, autor, genero, edicao, editora, id);

    if (mysql_query(conn, query)) {
        printf("Erro ao editar livro: %s\n", mysql_error(conn));
    } else {
        printf("Livro atualizado com sucesso!\n");
    }
}

// Função para excluir um livro
void excluirLivro(MYSQL *conn) {
    int id;
    char query[200];

    printf("\n--- Excluir Livro ---\n");
    printf("ID do Livro a excluir: ");
    scanf("%d", &id);

    snprintf(query, sizeof(query), "DELETE FROM livros WHERE id=%d", id);

    if (mysql_query(conn, query)) {
        printf("Erro ao excluir livro: %s\n", mysql_error(conn));
    } else {
        printf("Livro excluído com sucesso!\n");
    }
}

// Função para excluir os empréstimos relacionados ao cliente
void excluirEmprestimosCliente(MYSQL *conn, int id_cliente) {
    char query[500];
    snprintf(query, sizeof(query), "DELETE FROM emprestimos WHERE cliente_id = %d", id_cliente);
    if (mysql_query(conn, query)) {
        printf("Erro ao excluir empréstimos do cliente: %s\n", mysql_error(conn));
    } else {
        printf("Empréstimos relacionados ao cliente excluídos com sucesso!\n");
    }
}

// Função para adicionar um cliente
void adicionarCliente(MYSQL *conn) {
    char nome[100], cpf[15], telefone[20], email[100];
    char query[500];

    printf("\n--- Adicionar Cliente ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("CPF: ");
    scanf(" %[^\n]", cpf);
    printf("Telefone: ");
    scanf(" %[^\n]", telefone);
    printf("Email: ");
    scanf(" %[^\n]", email);

    snprintf(query, sizeof(query),
             "INSERT INTO clientes (nome, cpf, telefone, email) VALUES ('%s', '%s', '%s', '%s')",
             nome, cpf, telefone, email);

    if (mysql_query(conn, query)) {
        printf("Erro ao adicionar cliente: %s\n", mysql_error(conn));
    } else {
        printf("Cliente adicionado com sucesso!\n");
    }
}

// Função para excluir um cliente
void excluirCliente(MYSQL *conn) {
    int id;
    char query[200];

    printf("\n--- Excluir Cliente ---\n");
    printf("ID do Cliente a excluir: ");
    scanf("%d", &id);

    // Excluir os empréstimos relacionados ao cliente antes de excluir o cliente
    excluirEmprestimosCliente(conn, id);

    // Excluir o cliente
    snprintf(query, sizeof(query), "DELETE FROM clientes WHERE id=%d", id);

    if (mysql_query(conn, query)) {
        printf("Erro ao excluir cliente: %s\n", mysql_error(conn));
    } else {
        printf("Cliente excluído com sucesso!\n");
    }
}

// Função para mostrar o menu do administrador
void menuAdmin(MYSQL *conn) {
    int opcao;
    do {
        limparTela();
        printf("\n--- Sistema de Administração ---\n");
        
        // Separação de seções no menu
        printf("\n--- Livros ---\n");
        printf("1. Listar Livros\n");
        printf("2. Adicionar Livro\n");
        printf("3. Editar Livro\n");
        printf("4. Excluir Livro\n");

        printf("\n--- Clientes ---\n");
        printf("5. Listar Clientes\n");
        printf("6. Adicionar Cliente\n");
        printf("7. Excluir Cliente\n");

        printf("\n--- Empréstimos ---\n");
        printf("8. Listar Empréstimos\n");
        printf("9. Adicionar Empréstimo\n");
        printf("10. Excluir Empréstimo\n");

        printf("\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarLivros(conn);
                break;
            case 2:
                adicionarLivro(conn);
                break;
            case 3:
                editarLivro(conn);
                break;
            case 4:
                excluirLivro(conn);
                break;
            case 5:
                listarClientes(conn);
                break;
            case 6:
                adicionarCliente(conn);
                break;
            case 7:
                excluirCliente(conn);
                break;
            case 8:
                listarEmprestimos(conn);
                break;
            case 9:
                adicionarEmprestimo(conn);
                break;
            case 10:
                excluirEmprestimo(conn);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar(); getchar(); // Aguarda Enter
        }
    } while (opcao != 0);
}

int main() {
    MYSQL *conn = conectarBanco();
    menuAdmin(conn);
    mysql_close(conn);
    return 0;
}
