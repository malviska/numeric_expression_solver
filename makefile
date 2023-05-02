FLAGS := g++ -g -std=c++11 -Wall -I ./include -c
BUILD := g++ -g -std=c++11 -Wall

OBJ := ./obj
TST := ./tests
BIN := ./bin
SRC := ./src

infixa := $(OBJ)/infixa.o
infconv := $(OBJ)/infconv.o
cell := $(OBJ)/cell.o
stack := $(OBJ)/stack.o

t_infconv: infconv cell stack
	make clear;
	$(BUILD) $(infconv) $(cell) $(stack) -o $(BIN)/t_infconv ;
	$(BIN)/t_infconv

infconv: stack
	$(FLAGS) $(TST)/infixa_conversion.cpp -o $(infconv)

t_infixa: infixa cell stack
	make clear;
	$(BUILD) $(infixa) $(cell) $(stack) -o $(BIN)/t_infixa ;
	$(BIN)/t_infixa

infixa: stack
	$(FLAGS) $(TST)/infixa_validity.cpp -o $(infixa)

stack: cell
	$(FLAGS) $(SRC)/stack_dynamic.cpp -o $(stack)

cell:
	$(FLAGS) $(SRC)/cell.cpp -o $(cell)

clear:
	rm -rf ./bin/*