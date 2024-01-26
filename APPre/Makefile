CPP_EXEC = g++
CPP_FLAGS = --std=c++11

CPP = $(CPP_EXEC) $(CPP_FLAGS)

BUILD_DIR = build

all: quizMaker

quizMaker: $(BUILD_DIR)/main.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/MultiAnswer.o $(BUILD_DIR)/Query.o $(BUILD_DIR)/QueryParser.o  $(BUILD_DIR)/QuizInterface.o $(BUILD_DIR)/ShortAnswer.o $(BUILD_DIR)/SingleAnswer.o $(BUILD_DIR)/Submit.o $(BUILD_DIR)/Utility.o $(BUILD_DIR)/quizMaker.o
	$(CPP) $(BUILD_DIR)/main.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/MultiAnswer.o $(BUILD_DIR)/Query.o $(BUILD_DIR)/QueryParser.o  $(BUILD_DIR)/QuizInterface.o $(BUILD_DIR)/ShortAnswer.o $(BUILD_DIR)/SingleAnswer.o $(BUILD_DIR)/Submit.o $(BUILD_DIR)/Utility.o $(BUILD_DIR)/quizMaker.o -o ./quizMaker

$(BUILD_DIR)/main.o: main.cpp QuizInterface.hpp Const.hpp Utility.hpp QueryParser.hpp quizMaker.hpp Submit.hpp Query.hpp MultiAnswer.hpp ShortAnswer.hpp SingleAnswer.hpp
	$(CPP) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/QuizInterface.o: QuizInterface.cpp QuizInterface.hpp Utility.hpp Const.hpp Exception.hpp QuizInterface.hpp Query.hpp Submit.hpp MultiAnswer.hpp ShortAnswer.hpp SingleAnswer.hpp
	$(CPP) -c QuizInterface.cpp -o $(BUILD_DIR)/QuizInterface.o

$(BUILD_DIR)/QueryParser.o: QueryParser.cpp QueryParser.hpp Query.hpp Submit.hpp Utility.hpp Const.hpp Exception.hpp MultiAnswer.hpp ShortAnswer.hpp SingleAnswer.hpp
	$(CPP) -c QueryParser.cpp -o $(BUILD_DIR)/QueryParser.o

$(BUILD_DIR)/quizMaker.o: quizMaker.cpp quizMaker.hpp QueryParser.hpp Query.hpp Submit.hpp Utility.hpp Const.hpp Exception.hpp MultiAnswer.hpp ShortAnswer.hpp SingleAnswer.hpp
	$(CPP) -c quizMaker.cpp -o $(BUILD_DIR)/quizMaker.o 

$(BUILD_DIR)/Query.o: Query.cpp Query.hpp Submit.hpp Utility.hpp Const.hpp Exception.hpp MultiAnswer.hpp ShortAnswer.hpp SingleAnswer.hpp
	$(CPP) -c Query.cpp -o $(BUILD_DIR)/Query.o

$(BUILD_DIR)/MultiAnswer.o: MultiAnswer.cpp MultiAnswer.hpp Query.hpp Submit.hpp Utility.hpp Const.hpp Exception.hpp ShortAnswer.hpp SingleAnswer.hpp
	$(CPP) -c MultiAnswer.cpp -o $(BUILD_DIR)/MultiAnswer.o 

$(BUILD_DIR)/ShortAnswer.o: ShortAnswer.cpp ShortAnswer.hpp Query.hpp Submit.hpp Utility.hpp Const.hpp Exception.hpp MultiAnswer.hpp SingleAnswer.hpp
	$(CPP) -c ShortAnswer.cpp -o $(BUILD_DIR)/ShortAnswer.o

$(BUILD_DIR)/SingleAnswer.o: SingleAnswer.cpp SingleAnswer.hpp Query.hpp Submit.hpp Utility.hpp Const.hpp Exception.hpp MultiAnswer.hpp ShortAnswer.hpp
	$(CPP) -c SingleAnswer.cpp -o $(BUILD_DIR)/SingleAnswer.o

$(BUILD_DIR)/Submit.o: Submit.cpp Submit.hpp Const.hpp Exception.hpp
	$(CPP) -c Submit.cpp -o $(BUILD_DIR)/Submit.o 
	
$(BUILD_DIR)/Utility.o: Utility.cpp Utility.hpp Const.hpp
	$(CPP) -c Utility.cpp -o $(BUILD_DIR)/Utility.o 

$(BUILD_DIR)/Exception.o: Exception.cpp Exception.hpp
	$(CPP) -c Exception.cpp -o $(BUILD_DIR)/Exception.o

clean: 
	rm -rf build/ && mkdir -p build