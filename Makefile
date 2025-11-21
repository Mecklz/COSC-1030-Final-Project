BIN = .\bin
SRC = .\src
TEST = .\tests
DOC = .\doc

main: main_cpp
	.\$(BIN)\main.exe

main_cpp:
	cl $(SRC)\main.cpp /Fe:$(BIN)\main.exe

dice: dice_cpp
	.\$(BIN)\dice.exe

dice_cpp: 
	cl $(SRC)\dice.cpp /Fe:$(BIN)\dice.exe

test: test_cpp
	.\$(BIN)\test.exe

test_cpp: clean
	cl $(TEST)\test.cpp /Fe:$(BIN)\test.exe

clean:
	del $(BIN)\*