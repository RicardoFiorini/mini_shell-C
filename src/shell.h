#ifndef SHELL_H
#define SHELL_H

/**
 * @file shell.h
 * @brief Interface do módulo principal do Mini-Shell.
 *
 * Este módulo é responsável pelo loop principal do shell, leitura da entrada,
 * execução de comandos externos (via fork/execvp), comandos internos como `cd` e `exit`,
 * e suporte ao redirecionamento de entrada e saída (`<`, `>`).
 */

#include <stdbool.h>  // Para uso de tipo bool

#define MAX_CMD_LEN 1024  ///< Tamanho máximo da linha de comando

/**
 * @brief Inicia o shell interativo.
 *
 * Função principal que exibe o prompt, lê entradas do usuário e executa os comandos.
 * O loop só termina quando o usuário digita `exit`.
 */
void start_shell(void);

/**
 * @brief Executa um comando digitado pelo usuário.
 *
 * Essa função lida com o parsing da entrada, execução de comandos internos
 * (`cd`, `exit`, `history`) e criação de processos para comandos externos.
 *
 * @param input String contendo o comando a ser executado.
 */
void execute_command(char *input);

/**
 * @brief Realiza o redirecionamento de entrada e saída, se especificado.
 *
 * Verifica os tokens `>` e `<` e faz o redirecionamento dos descritores de arquivo
 * antes da execução com `execvp()`.
 *
 * @param args Vetor de argumentos do comando, possivelmente contendo `>` ou `<`.
 */
void handle_redirection(char **args);

/**
 * @brief Verifica se o comando é interno (builtin).
 *
 * Comandos como `cd`, `exit` e `history` são tratados diretamente pelo shell
 * sem o uso de fork/execvp.
 *
 * @param args Vetor de argumentos (argv-like)
 * @return true se for comando interno, false caso contrário
 */
bool is_builtin_command(char **args);

#endif // SHELL_H
