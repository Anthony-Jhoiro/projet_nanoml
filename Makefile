CXX       := gcc
CXX_FLAGS := -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := nanoml


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

# $^ => all files (nanoml.c & $(SRC)/**/*.c) 
# $@ => target ($(BIN)/$(EXECUTABLE))

$(BIN)/$(EXECUTABLE): nanoml.c $(SRC)/**/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
