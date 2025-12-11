/**
 * @file history.c
 * @brief Implementação das funções de histórico de comandos do Mini-Shell.
 */

#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Vetor de ponteiros que armazena o histórico dos comandos
static char *history[MAX_HISTORY];

/// Contador de comandos armazenados
static int history_count = 0;

/**
 * @brief Adiciona um comando ao histórico interno.
 *
 * Armazena uma cópia do comando usando strdup(). Comandos nulos são ignorados.
 * Se atingir o limite MAX_HISTORY, comandos adicionais são descartados.
 *
 * @param cmd Comando de entrada a ser salvo.
 */
void add_history(const char *cmd) {
    if (!cmd || strlen(cmd) == 0) return;

    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(cmd);
        if (!history[history_count - 1]) {
            perror("strdup (add_history)");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "[AVISO] Histórico cheio. Comando não adicionado.\n");
        // Alternativa futura: sobrescrever o mais antigo (FIFO)
    }
}

/**
 * @brief Exibe todos os comandos armazenados no histórico.
 */
void show_history(void) {
    for (int i = 0; i < history_count; i++) {
        printf("%d  %s\n", i + 1, history[i]);
    }
}

/**
 * @brief Libera toda a memória alocada para o histórico.
 *
 * Essa função deve ser chamada ao encerrar o shell para evitar vazamentos.
 */
void free_history(void) {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
        history[i] = NULL;
    }
    history_count = 0;
}
