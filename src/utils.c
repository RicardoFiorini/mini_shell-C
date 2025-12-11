/**
 * @file utils.c
 * @brief Implementações das funções auxiliares de parsing e manipulação de argumentos.
 */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Divide a entrada em argumentos separados por espaço.
 *
 * Aloca dinamicamente um vetor de strings com os tokens encontrados.
 * Considera até MAX_ARGS argumentos. Desconsidera múltiplos espaços consecutivos.
 *
 * @param input String original de entrada.
 * @return Vetor de ponteiros para strings (char **), NULL-terminado.
 */
char **parse_input(char *input) {
    if (input == NULL) {
        return NULL;
    }

    char **args = malloc(sizeof(char *) * MAX_ARGS);
    if (!args) {
        perror("malloc (args)");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char *token = strtok(input, " \t");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = strdup(token);  // Aloca cópia do token
        if (!args[i]) {
            perror("strdup (parse_input)");
            exit(EXIT_FAILURE);
        }

        i++;
        token = strtok(NULL, " \t");
    }

    args[i] = NULL;  // Termina com NULL como exige execvp

    return args;
}

/**
 * @brief Libera memória alocada por parse_input().
 *
 * Libera cada string individualmente e depois o vetor principal.
 *
 * @param args Vetor retornado por parse_input.
 */
void free_args(char **args) {
    if (!args) return;

    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }

    free(args);
}
