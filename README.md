# Mini Shell em C
Um interpretador de comandos simples e eficiente desenvolvido em **linguagem C** para explorar o funcionamento interno de sistemas operacionais e o gerenciamento de processos.
## Funcionalidades Implementadas

- **Prompt Interativo:** Interface amigável para entrada de comandos.
- **Execução de Comandos externos:** Suporte a comandos do sistema (ls, pwd, mkdir, etc).
- **Parsing de Argumentos:** Capacidade de processar comandos com múltiplos parâmetros.
- **Built-ins:** Comandos internos como `exit` e `cd`.

## Progresso do Projeto
- [x] Loop principal (REPL)
- [x] Criação de processos filhos com fork()
- [x] Substituição de imagem de processo com exec()
- [ ] Implementar redirecionamento de entrada/saída (>, <)
- [ ] Implementar Pipes (|)
## Exemplo da Lógica de Execução
O shell utiliza a técnica de bifurcação de processos para manter o programa principal rodando enquanto executa os comandos solicitados:
```c

pid_t pid = fork();
if (pid == 0) {
// Processo Filho
if (execvp(args[0], args) == -1) {
perror("Erro ao executar comando");
}
exit(EXIT_FAILURE);
} else {
// Processo Pai
wait(NULL);
}

```
## Requisitos de Sistema
> [!TIP]
> Este projeto foi desenvolvido para ambientes baseados em Unix/Linux, pois utiliza chamadas de sistema da biblioteca POSIX.
## Principais Chamadas de Sistema Utilizadas
| Função | Descrição |
| --- | --- |
| fork() | Cria um novo processo quase idêntico ao pai |
| execvp() | Substitui o processo atual por um novo programa |
| wait() | Faz o pai esperar a finalização do processo filho |
| strtok() | Divide a string de entrada em tokens (comando e argumentos) |
