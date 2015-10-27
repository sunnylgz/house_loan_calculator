# Project: house_loan_calculator
# Makefile created by Dev-C++ 5.11

CPP      = g++
CC       = gcc
OBJ      = ./house_loan.o ./main.o
LINKOBJ  = ./house_loan.o ./main.o
LIBS     =
INCS     =
CXXINCS  =
BIN      = house_loan_calculator
CXXFLAGS = $(CXXINCS)
CFLAGS   = $(INCS)
RM       = rm

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

../house_loan.o: ../house_loan.c
	$(CC) -c ../house_loan.c -o ../house_loan.o $(CFLAGS)

../main.o: ../main.c
	$(CC) -c ../main.c -o ../main.o $(CFLAGS)
