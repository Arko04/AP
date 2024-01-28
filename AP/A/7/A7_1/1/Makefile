CPP_EXEC = g++
CPP_FLAGS = --std=c++11

CPP = $(CPP_EXEC) $(CPP_FLAGS)

BUILD_DIR = build

all: futballFantasy.out

futballFantasy.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/Manager.o $(BUILD_DIR)/TeamManager.o $(BUILD_DIR)/WeekManager.o $(BUILD_DIR)/Week.o $(BUILD_DIR)/Match.o  $(BUILD_DIR)/RealTeam.o $(BUILD_DIR)/User.o $(BUILD_DIR)/FantasyTeam.o $(BUILD_DIR)/Player.o
	$(CPP) $(BUILD_DIR)/main.o $(BUILD_DIR)/Manager.o $(BUILD_DIR)/TeamManager.o $(BUILD_DIR)/WeekManager.o $(BUILD_DIR)/Week.o $(BUILD_DIR)/Match.o  $(BUILD_DIR)/RealTeam.o $(BUILD_DIR)/User.o $(BUILD_DIR)/FantasyTeam.o $(BUILD_DIR)/Player.o -o ./futballFantasy.out

$(BUILD_DIR)/main.o: main.cpp Manager.hpp Const.hpp User.hpp RealTeam.hpp TeamManager.hpp WeekManager.hpp FantasyTeam.hpp Match.hpp Player.hpp Week.hpp
	$(CPP) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Manager.o: Manager.cpp Manager.hpp Exception.hpp Const.hpp User.hpp RealTeam.hpp TeamManager.hpp WeekManager.hpp FantasyTeam.hpp Match.hpp Player.hpp Week.hpp
	$(CPP) -c Manager.cpp -o $(BUILD_DIR)/Manager.o

$(BUILD_DIR)/TeamManager.o: TeamManager.cpp TeamManager.hpp Const.hpp RealTeam.hpp Player.hpp Match.hpp
	$(CPP) -c TeamManager.cpp -o $(BUILD_DIR)/TeamManager.o

$(BUILD_DIR)/WeekManager.o: WeekManager.cpp WeekManager.hpp Const.hpp Week.hpp RealTeam.hpp Match.hpp Player.hpp
	$(CPP) -c WeekManager.cpp -o $(BUILD_DIR)/WeekManager.o 

$(BUILD_DIR)/Week.o: Week.cpp Week.hpp Const.hpp RealTeam.hpp Match.hpp Player.hpp
	$(CPP) -c Week.cpp -o $(BUILD_DIR)/Week.o

$(BUILD_DIR)/Match.o: Match.cpp Match.hpp Const.hpp 
	$(CPP) -c Match.cpp -o $(BUILD_DIR)/Match.o

$(BUILD_DIR)/RealTeam.o: RealTeam.cpp RealTeam.hpp Const.hpp Match.hpp Player.hpp
	$(CPP) -c RealTeam.cpp -o $(BUILD_DIR)/RealTeam.o

$(BUILD_DIR)/User.o: User.cpp User.hpp Exception.hpp FantasyTeam.hpp Player.hpp
	$(CPP) -c User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/FantasyTeam.o: FantasyTeam.cpp FantasyTeam.hpp Exception.hpp Const.hpp Player.hpp
	$(CPP) -c FantasyTeam.cpp -o $(BUILD_DIR)/FantasyTeam.o

$(BUILD_DIR)/Player.o: Player.cpp Player.hpp Const.hpp
	$(CPP) -c Player.cpp -o $(BUILD_DIR)/Player.o 

clean: 
	rm -rf build/ && mkdir -p build