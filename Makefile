# Variáveis de compilação
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 -pedantic
LDFLAGS = -lSDL2 -lGL

# Diretórios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXEC = $(BIN_DIR)/main

# Regras de compilação
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra de limpeza
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: clean

