a.out: main.o input_handler.o manager.o mission.o time_mission.o distance_mission.o count_mission.o timestamp.o driver.o ride.o
	g++ --std=c++11 main.o input_handler.o manager.o mission.o time_mission.o distance_mission.o count_mission.o timestamp.o driver.o ride.o

main.o : main.cpp input_handler.hpp
	g++ --std=c++11 -c main.cpp

input_handler.o : input_handler.cpp input_handler.hpp const.hpp
	g++ --std=c++11 -c input_handler.cpp


const.hpp count_mission.hpp time_mission.hpp distance_mission.hpp mission.hpp driver.hpp exception.hpp input_handler.hpp timestamp.hpp ride.hpp manager.hpp