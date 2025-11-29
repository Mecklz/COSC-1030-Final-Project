BIN = .\bin
SRC = .\src
TEST = .\tests
DOC = .\doc

main: main_cpp
	.\$(BIN)\simulate.exe

main_cpp: clean
	cl $(SRC)\main.cpp $(SRC)\Day.cpp /Fe:$(BIN)\simulate.exe

dice: dice_cpp
	.\$(BIN)\dice.exe

dice_cpp: 
	cl $(SRC)\dice.cpp /Fe:$(BIN)\dice.exe

test: test_cpp
	.\$(BIN)\test.exe

test_cpp: clean
	cl $(TEST)\test.cpp /Fe:$(BIN)\test.exe

clean: refresh_sim
	del $(BIN)\*

refresh_sim:
	del $(DOC)\Sim_Results.txt