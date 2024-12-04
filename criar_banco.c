//PROJETO M3 BANCO DE DADOS
//ALUNO: CAUÃ DOMINGOS

#include <stdio.h>  // Inclusão da biblioteca de entrada e saída padrão
#include <stdlib.h> // Inclusão da biblioteca de funções utilitárias, como exit()
#include <string.h> // Inclusão da biblioteca de manipulação de strings
#include "C:\Program Files\MySQL\MySQL Server 8.0\include\mysql.h"  // Inclusão da biblioteca MySQL para usar suas funções

// Função para conectar ao banco de dados
MYSQL* conectarBanco() {
    // Inicializa a conexão com o banco de dados
    MYSQL *conn = mysql_init(NULL);  // Inicializa a estrutura MYSQL

    // Conecta ao banco de dados MySQL no localhost com usuário 'root' e senha '1234'
    // O 'NULL' no lugar do nome do banco de dados significa que o banco de dados não é especificado ainda
    if (!mysql_real_connect(conn, "localhost", "root", "1234", NULL, 3306, NULL, 0)) {
        // Se a conexão falhar, imprime o erro e sai do programa
        printf("Erro ao conectar ao MySQL: %s\n", mysql_error(conn));
        exit(1);  // Encerra o programa com um erro
    }
    
    // Retorna a conexão com o banco de dados
    return conn;
}

// Função para criar o banco de dados e as tabelas
void criarBanco(MYSQL *conn) {
    // Cria o banco de dados 'livraria', se não existir
    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS livraria")) {
        // Se falhar, imprime o erro e retorna
        printf("Erro ao criar banco de dados: %s\n", mysql_error(conn));
        return;
    }
    
    // Seleciona o banco de dados 'livraria' para uso
    if (mysql_query(conn, "USE livraria")) {
        // Se falhar, imprime o erro e retorna
        printf("Erro ao usar o banco de dados: %s\n", mysql_error(conn));
        return;
    }

    // Cria a tabela de livros, se não existir, com campos para id, nome, autor, gênero, edição e editora
    const char *sql_livros = "CREATE TABLE IF NOT EXISTS livros ("
                             "id INT AUTO_INCREMENT PRIMARY KEY, " // Campo 'id' como chave primária e auto-incrementada
                             "nome VARCHAR(100), "  // Campo 'nome' para o nome do livro
                             "autor VARCHAR(100), "  // Campo 'autor' para o autor do livro
                             "genero VARCHAR(50), "  // Campo 'genero' para o gênero do livro
                             "edicao VARCHAR(10), "  // Campo 'edicao' para a edição do livro
                             "editora VARCHAR(100))"; // Campo 'editora' para a editora do livro
    if (mysql_query(conn, sql_livros)) {
        // Se falhar ao criar a tabela de livros, imprime o erro e retorna
        printf("Erro ao criar tabela de livros: %s\n", mysql_error(conn));
        return;
    }

    // Cria a tabela de clientes, se não existir, com campos para id, nome, cpf, telefone e email
    const char *sql_clientes = "CREATE TABLE IF NOT EXISTS clientes ("
                               "id INT AUTO_INCREMENT PRIMARY KEY, " // Campo 'id' como chave primária e auto-incrementada
                               "nome VARCHAR(100), "  // Campo 'nome' para o nome do cliente
                               "cpf VARCHAR(15), "  // Campo 'cpf' para o CPF do cliente
                               "telefone VARCHAR(20), "  // Campo 'telefone' para o telefone do cliente
                               "email VARCHAR(100))"; // Campo 'email' para o email do cliente
    if (mysql_query(conn, sql_clientes)) {
        // Se falhar ao criar a tabela de clientes, imprime o erro e retorna
        printf("Erro ao criar tabela de clientes: %s\n", mysql_error(conn));
        return;
    }

    // Cria a tabela de empréstimos, se não existir, com campos para id, livro_id, cliente_id, data_emprestimo, e data_devolucao
    // Estabelece as chaves estrangeiras (FOREIGN KEY) para as tabelas de livros e clientes
    const char *sql_emprestimos = "CREATE TABLE IF NOT EXISTS emprestimos ("
                                  "id INT AUTO_INCREMENT PRIMARY KEY, "  // Campo 'id' como chave primária e auto-incrementada
                                  "livro_id INT, "  // Campo 'livro_id' para associar o livro ao empréstimo
                                  "cliente_id INT, "  // Campo 'cliente_id' para associar o cliente ao empréstimo
                                  "data_emprestimo DATE, "  // Campo 'data_emprestimo' para registrar a data do empréstimo
                                  "data_devolucao DATE, "  // Campo 'data_devolucao' para registrar a data de devolução
                                  "FOREIGN KEY (livro_id) REFERENCES livros(id), "  // Chave estrangeira para 'livros'
                                  "FOREIGN KEY (cliente_id) REFERENCES clientes(id))";  // Chave estrangeira para 'clientes'
    if (mysql_query(conn, sql_emprestimos)) {
        // Se falhar ao criar a tabela de empréstimos, imprime o erro e retorna
        printf("Erro ao criar tabela de empréstimos: %s\n", mysql_error(conn));
        return;
    }

    // Mensagem de sucesso caso tudo tenha ocorrido corretamente
    printf("Banco de dados e tabelas criados com sucesso!\n");
}

// Função principal onde o programa começa
int main() {
    // Conecta ao banco de dados e obtém o ponteiro de conexão
    MYSQL *conn = conectarBanco();
    
    // Cria o banco de dados e as tabelas
    criarBanco(conn);

    // Fecha a conexão com o banco de dados
    mysql_close(conn);
    
    return 0;  // Retorna 0 para indicar que o programa terminou com sucesso
}
