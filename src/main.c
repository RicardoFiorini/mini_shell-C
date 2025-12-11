/**
 * @file main.c
 * @brief Ponto de entrada do Mini-Shell.
 *
 * Este arquivo contém apenas a função principal (main),
 * que inicia o shell interativo e, ao final, libera recursos usados.
 */

#include "shell.h"
#include "history.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Boas-vindas
    printf("=== Mini-Shell Interativo ===\n");
    printf("Digite 'exit' para sair.\n\n");

    // Inicia o shell interativo
    start_shell();

    // Libera recursos do histórico antes de sair
    free_history();

    printf("\nShell finalizado com sucesso.\n");
    return EXIT_SUCCESS;
}
