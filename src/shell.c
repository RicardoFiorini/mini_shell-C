/**
 * @file shell.c
 * @brief Implementação do núcleo do Mini-Shell.
 *
 * Contém o loop principal de execução, tratamento de comandos internos,
 * criação de processos com fork/execvp, e suporte a redirecionamento básico (<, >).
 */

#include "shell.h"
#include "utils.h"
#include "history.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * @brief Inicia o shell interativo.
 *
 * Lê comandos do usuário em um loop contínuo até que 'exit' seja digitado.
 */
void start_shell(void) {
    char input[MAX_CMD_LEN];

    while (1) {
        printf("mini-shell> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            printf("\n"); // Captura Ctrl+D com elegância
            break;
        }

        // Remove o newline do final
        input[strcspn(input, "\n")] = '\0';

        // Ignora entradas vazias
        if (strlen(input) == 0) continue;

        add_history(input);

        // Verifica saída
        if (strcmp(input, "exit") == 0) break;

        execute_command(input);
    }
}

/**
 * @brief Executa comandos digitados, tratando internos ou externos.
 *
 * @param input String com o comando e argumentos.
 */
void execute_command(char *input) {
    char **args = parse_input(input);
    if (!args || !args[0]) {
        free_args(args);
        return;
    }

    // Comando interno: cd, history, etc.
    if (is_builtin_command(args)) {
        free_args(args);
        return;
    }

    // Comando externo: fork + execvp
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
    } else if (pid == 0) {
        handle_redirection(args); // Aplica redirecionamento se houver
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }

    free_args(args);
}

/**
 * @brief Executa comandos internos diretamente no shell.
 *
 * Comandos: cd, history.
 *
 * @param args Argumentos do comando.
 * @return true se o comando foi interno e executado, false caso contrário.
 */
bool is_builtin_command(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        if (args[1]) {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        } else {
            fprintf(stderr, "cd: caminho não especificado.\n");
        }
        return true;
    }

    if (strcmp(args[0], "history") == 0) {
        show_history();
        return true;
    }

    return false;
}

/**
 * @brief Verifica e aplica redirecionamento de entrada/saída.
 *
 * Modifica os descritores de arquivo se encontrar '<' ou '>'.
 *
 * @param args Vetor de argumentos. Os redirecionadores e seus caminhos são substituídos por NULL.
 */
void handle_redirection(char **args) {
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], ">") == 0 && args[i + 1]) {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open (output redirection)");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }

        if (strcmp(args[i], "<") == 0 && args[i + 1]) {
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("open (input redirection)");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
}
