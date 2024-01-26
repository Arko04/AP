CPP_EXEC = g++
CPP_FLAGS = --std=c++11

CPP = $(CPP_EXEC) $(CPP_FLAGS)

BUILD_DIR = build
INC_DIR = inc
SRC_DIR = src

all: quizMaker

quizMaker: $(BUILD_DIR)/main.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/MultiAnswer.o $(BUILD_DIR)/Query.o $(BUILD_DIR)/QueryParser.o  $(BUILD_DIR)/QuizInterface.o $(BUILD_DIR)/ShortAnswer.o $(BUILD_DIR)/SingleAnswer.o $(BUILD_DIR)/Submit.o $(BUILD_DIR)/Utility.o $(BUILD_DIR)/quizMaker.o
	$(CPP) $(BUILD_DIR)/main.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/MultiAnswer.o $(BUILD_DIR)/Query.o $(BUILD_DIR)/QueryParser.o  $(BUILD_DIR)/QuizInterface.o $(BUILD_DIR)/ShortAnswer.o $(BUILD_DIR)/SingleAnswer.o $(BUILD_DIR)/Submit.o $(BUILD_DIR)/Utility.o $(BUILD_DIR)/quizMaker.o -o ./quizMaker

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/QuizInterface.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/QueryParser.hpp $(INC_DIR)/quizMaker.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Query.hpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/ShortAnswer.hpp $(INC_DIR)/SingleAnswer.hpp
	$(CPP) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/QuizInterface.o: $(SRC_DIR)/QuizInterface.cpp $(INC_DIR)/QuizInterface.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp $(INC_DIR)/QuizInterface.hpp $(INC_DIR)/Query.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/ShortAnswer.hpp $(INC_DIR)/SingleAnswer.hpp
	$(CPP) -c $(SRC_DIR)/QuizInterface.cpp -o $(BUILD_DIR)/QuizInterface.o

$(BUILD_DIR)/QueryParser.o: $(SRC_DIR)/QueryParser.cpp $(INC_DIR)/QueryParser.hpp $(INC_DIR)/Query.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/ShortAnswer.hpp $(INC_DIR)/SingleAnswer.hpp
	$(CPP) -c $(SRC_DIR)/QueryParser.cpp -o $(BUILD_DIR)/QueryParser.o

$(BUILD_DIR)/quizMaker.o: $(SRC_DIR)/quizMaker.cpp $(INC_DIR)/quizMaker.hpp $(INC_DIR)/QueryParser.hpp $(INC_DIR)/Query.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/ShortAnswer.hpp $(INC_DIR)/SingleAnswer.hpp
	$(CPP) -c $(SRC_DIR)/quizMaker.cpp -o $(BUILD_DIR)/quizMaker.o 

$(BUILD_DIR)/Query.o: $(SRC_DIR)/Query.cpp $(INC_DIR)/Query.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/ShortAnswer.hpp $(INC_DIR)/SingleAnswer.hpp
	$(CPP) -c $(SRC_DIR)/Query.cpp -o $(BUILD_DIR)/Query.o

$(BUILD_DIR)/MultiAnswer.o: $(SRC_DIR)/MultiAnswer.cpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/Query.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp $(INC_DIR)/ShortAnswer.hpp $(INC_DIR)/SingleAnswer.hpp
	$(CPP) -c $(SRC_DIR)/MultiAnswer.cpp -o $(BUILD_DIR)/MultiAnswer.o 

$(BUILD_DIR)/ShortAnswer.o: $(SRC_DIR)/ShortAnswer.cpp $(INC_DIR)/ShortAnswer.hpp $(INC_DIR)/Query.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/SingleAnswer.hpp
	$(CPP) -c $(SRC_DIR)/ShortAnswer.cpp -o $(BUILD_DIR)/ShortAnswer.o

$(BUILD_DIR)/SingleAnswer.o: $(SRC_DIR)/SingleAnswer.cpp $(INC_DIR)/SingleAnswer.hpp $(INC_DIR)/Query.hpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp $(INC_DIR)/MultiAnswer.hpp $(INC_DIR)/ShortAnswer.hpp
	$(CPP) -c $(SRC_DIR)/SingleAnswer.cpp -o $(BUILD_DIR)/SingleAnswer.o

$(BUILD_DIR)/Submit.o: $(SRC_DIR)/Submit.cpp $(INC_DIR)/Submit.hpp $(INC_DIR)/Const.hpp $(INC_DIR)/Exception.hpp
	$(CPP) -c $(SRC_DIR)/Submit.cpp -o $(BUILD_DIR)/Submit.o 
	
$(BUILD_DIR)/Utility.o: $(SRC_DIR)/Utility.cpp $(INC_DIR)/Utility.hpp $(INC_DIR)/Const.hpp
	$(CPP) -c $(SRC_DIR)/Utility.cpp -o $(BUILD_DIR)/Utility.o 

$(BUILD_DIR)/Exception.o: $(SRC_DIR)/Exception.cpp $(INC_DIR)/Exception.hpp
	$(CPP) -c $(SRC_DIR)/Exception.cpp -o $(BUILD_DIR)/Exception.o

clean: 
	rm -rf build/ && mkdir -p build