# === Variáveis de Configuração ===
CC       := gcc
CFLAGS   := -Wall -Wextra -pedantic -std=c99 -g
LDFLAGS  := 
BIN_DIR  := bin
SRC_DIR  := src
TARGET   := $(BIN_DIR)/mini_shell

# === Arquivos fonte e objetos ===
SOURCES  := $(wildcard $(SRC_DIR)/*.c)
OBJECTS  := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCES))

# === Regra principal ===
all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build finalizado: $(TARGET)"

# === Compilação dos .c para .o ===
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

# === Limpeza dos binários e objetos ===
clean:
	@rm -rf $(BIN_DIR)/*
	@echo "Limpeza concluída."

# === Rebuild completo ===
rebuild: clean all

# === Execução direta ===
run: all
	@echo "Executando o shell:"
	@$(TARGET)

# === Ajuda ===
help:
	@echo "Comandos disponíveis:"
	@echo "  make           - Compila o projeto"
	@echo "  make run       - Compila e executa"
	@echo "  make clean     - Remove arquivos de build"
	@echo "  make rebuild   - Limpa e recompila"
	@echo "  make help      - Exibe este menu"
