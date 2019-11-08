CC=g++

HEADER_PATH = include
SRC_PATH = src
BIN_PATH = bin

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
HPP_FILES = $(wildcard $(HEADER_PATH)/*.hpp)

DIRECTIVES = -std=c++1z -Wall -Wextra -Wno-unused-result -c -I$(HEADER_PATH) #-O2

EXEC = pseudo-so.out



# Regra default:
all: $(EXEC)
# Regra de criação do executável final:
$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)
#chama all e depois roda
run: clear all
	./$(EXEC)

run-%: clear all
	./$(EXEC) $*

# Regra de inferência para criação dos objetos de compilação:
$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp $(HPP_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -c -o $@ $< $(DIRECTIVES)

# Regra para limpar/deletar todos os arquivos e diretórios criados pelo make
clean:
	rm -r -f $(BIN_PATH)
	rm -f $(EXEC)

clear:
	clear && clear
remake: clear clean all
