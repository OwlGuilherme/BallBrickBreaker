# Variáveis de compilação
CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS = -lSDL2

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

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: clean

