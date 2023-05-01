FLAGS := g++ -g -std=c++11 -Wall -I ./include -c
BUILD := g++ -g -std=c++11 -Wall

OBJ := ./obj
TST := ./tests
BIN := ./bin
SRC := ./src

infixa := $(OBJ)/infixa.o
cell := $(OBJ)/cell.o
stack := $(OBJ)/stack.o

t_infixa: infixa cell stack
	$(BUILD) $(infixa) $(cell) $(stack) -o $(BIN)/t_infixa ;
	$(BIN)/t_infixa

infixa: stack
	$(FLAGS) $(TST)/infixa_validity.cpp -o $(infixa)

stack: cell
	$(FLAGS) $(SRC)/stack_dynamic.cpp -o $(stack)

cell:
	$(FLAGS) $(SRC)/cell.cpp -o $(cell)
