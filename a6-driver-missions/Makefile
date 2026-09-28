CPP_EXEC = g++
CPP_FLAGS = --std=c++11

CPP = $(CPP_EXEC) $(CPP_FLAGS)

SRC_DIR = src
BUILD_DIR = build

all: main

main: $(BUILD_DIR)/main.o $(BUILD_DIR)/input_handler.o $(BUILD_DIR)/manager.o $(BUILD_DIR)/mission.o $(BUILD_DIR)/count_mission.o $(BUILD_DIR)/time_mission.o $(BUILD_DIR)/distance_mission.o $(BUILD_DIR)/driver.o $(BUILD_DIR)/ride.o $(BUILD_DIR)/timestamp.o
	$(CPP) $(BUILD_DIR)/main.o $(BUILD_DIR)/input_handler.o $(BUILD_DIR)/manager.o $(BUILD_DIR)/mission.o $(BUILD_DIR)/count_mission.o $(BUILD_DIR)/time_mission.o $(BUILD_DIR)/distance_mission.o $(BUILD_DIR)/driver.o $(BUILD_DIR)/ride.o $(BUILD_DIR)/timestamp.o -o ./main

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/input_handler.hpp $(SRC_DIR)/manager.hpp $(SRC_DIR)/driver.hpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp
	$(CPP) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/input_handler.o: $(SRC_DIR)/input_handler.cpp $(SRC_DIR)/input_handler.hpp $(SRC_DIR)/manager.hpp $(SRC_DIR)/driver.hpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp $(SRC_DIR)/const.hpp
	$(CPP) -c $(SRC_DIR)/input_handler.cpp -o $(BUILD_DIR)/input_handler.o

$(BUILD_DIR)/manager.o: $(SRC_DIR)/manager.cpp $(SRC_DIR)/manager.hpp $(SRC_DIR)/time_mission.hpp $(SRC_DIR)/distance_mission.hpp $(SRC_DIR)/count_mission.hpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp $(SRC_DIR)/exception.hpp $(SRC_DIR)/const.hpp
	$(CPP) -c $(SRC_DIR)/manager.cpp -o $(BUILD_DIR)/manager.o

$(BUILD_DIR)/mission.o: $(SRC_DIR)/mission.cpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp $(SRC_DIR)/const.hpp
	$(CPP) -c $(SRC_DIR)/mission.cpp -o $(BUILD_DIR)/mission.o 

$(BUILD_DIR)/count_mission.o: $(SRC_DIR)/count_mission.cpp $(SRC_DIR)/count_mission.hpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp $(SRC_DIR)/const.hpp
	$(CPP) -c $(SRC_DIR)/count_mission.cpp -o $(BUILD_DIR)/count_mission.o

$(BUILD_DIR)/time_mission.o: $(SRC_DIR)/time_mission.cpp $(SRC_DIR)/time_mission.hpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp $(SRC_DIR)/const.hpp
	$(CPP) -c $(SRC_DIR)/time_mission.cpp -o $(BUILD_DIR)/time_mission.o

$(BUILD_DIR)/distance_mission.o: $(SRC_DIR)/distance_mission.cpp $(SRC_DIR)/distance_mission.hpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp $(SRC_DIR)/const.hpp
	$(CPP) -c $(SRC_DIR)/distance_mission.cpp -o $(BUILD_DIR)/distance_mission.o

$(BUILD_DIR)/driver.o: $(SRC_DIR)/driver.cpp $(SRC_DIR)/driver.hpp $(SRC_DIR)/mission.hpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp $(SRC_DIR)/const.hpp $(SRC_DIR)/exception.hpp
	$(CPP) -c $(SRC_DIR)/driver.cpp -o $(BUILD_DIR)/driver.o

$(BUILD_DIR)/ride.o: $(SRC_DIR)/ride.cpp $(SRC_DIR)/ride.hpp $(SRC_DIR)/timestamp.hpp
	$(CPP) -c $(SRC_DIR)/ride.cpp -o $(BUILD_DIR)/ride.o

$(BUILD_DIR)/timestamp.o: $(SRC_DIR)/timestamp.cpp $(SRC_DIR)/time_mission.hpp $(SRC_DIR)/const.hpp
	$(CPP) -c $(SRC_DIR)/timestamp.cpp -o $(BUILD_DIR)/timestamp.o

run: main
	./main

clean: 
	rm -rf build/ && mkdir -p build