#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief Funções auxiliares para parsing e manipulação de argumentos.
 *
 * Este header define utilitários usados para processar strings de entrada
 * do shell, incluindo parsing de comandos e liberação de memória alocada.
 */

#include <stddef.h>  // Para size_t

#define MAX_ARGS 64  ///< Número máximo de argumentos permitidos

/**
 * @brief Realiza o parsing de uma string de entrada em argumentos.
 *
 * Divide a string recebida em tokens com base em espaços em branco.
 * Aloca dinamicamente um vetor de strings.
 *
 * @param input Linha de comando digitada.
 * @return Um vetor de ponteiros para strings (NULL-terminado).
 *         Deve ser liberado com free_args().
 */
char **parse_input(char *input);

/**
 * @brief Libera os argumentos alocados por parse_input().
 *
 * @param args Vetor de argumentos retornado por parse_input().
 */
void free_args(char **args);

#endif // UTILS_H
