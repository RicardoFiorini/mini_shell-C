#ifndef HISTORY_H
#define HISTORY_H

/**
 * @file history.h
 * @brief Interface para o gerenciamento de histórico de comandos no Mini-Shell.
 *
 * Este módulo mantém os comandos digitados pelo usuário em uma lista interna
 * e oferece funções para adicionar novos comandos e exibir o histórico completo.
 */

#define MAX_HISTORY 100  ///< Número máximo de comandos salvos no histórico

/**
 * @brief Adiciona um comando ao histórico.
 *
 * Armazena uma cópia do comando recebido até o limite definido por MAX_HISTORY.
 * Se o limite for atingido, novos comandos são ignorados (FIFO opcional futuro).
 *
 * @param cmd Comando digitado pelo usuário.
 */
void add_history(const char *cmd);

/**
 * @brief Exibe todos os comandos armazenados no histórico.
 *
 * Os comandos são listados na ordem em que foram inseridos.
 */
void show_history(void);

/**
 * @brief Libera toda a memória alocada pelo histórico.
 *
 * Deve ser chamada ao encerrar o shell, para evitar vazamento de memória.
 */
void free_history(void);

#endif // HISTORY_H
