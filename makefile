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




all: main stack cell
	make clear;
	$(BUILD) $(cell) $(stack) ./obj/main.o -o $(BIN)/solver ;
	$(BIN)/solver



main:
	$(FLAGS) $(SRC)/main.cpp -o ./obj/main.o


t_posconv: posconv
	make clear;
	$(BUILD) $(cell) $(stack) ./obj/posfixa.o -o $(BIN)/t_posconv ;
	$(BIN)/t_posconv



posconv: stack cell
	$(FLAGS) $(TST)/posfixa_conversion.cpp -o ./obj/posfixa.o


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


t_pos_v: pos_validity stack cell
	make clear;
	$(BUILD) $(cell) $(stack) ./obj/pos_validity.o -o $(BIN)/t_pos_v ;
	$(BIN)/t_pos_v


pos_validity:
	$(FLAGS) $(TST)/posfixa_validity.cpp -o ./obj/pos_validity.o


infixa: stack
	$(FLAGS) $(TST)/infixa_validity.cpp -o $(infixa)

stack: cell
	$(FLAGS) $(SRC)/stack_dynamic.cpp -o $(stack)

cell:
	$(FLAGS) $(SRC)/cell.cpp -o $(cell)

clear:
	rm -rf ./bin/*

clean:
	rm -rf ./bin/* ./obj/*