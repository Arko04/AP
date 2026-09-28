# Advanced Programming (C++)

My projects for **Advanced Programming** at the University of Tehran, Faculty of Electrical and Computer Engineering (Spring 2023). The course moves from structured C++ to top-down design, object-oriented design, event-driven programming and polymorphism.

| Project | Description | Concepts |
|---------|-------------|----------|
| [A0 – Warm-up](a0-warm-up/) | Two introductory judge problems | C++ basics |
| [A1 – Diary sentiment](a1-diary-sentiment/) | A command-line diary: store dated entries, search them, and score each entry against a list of positive words | Strings, STL containers |
| [A2 – Text processing](a2-text-processing/) | Four recursive string and text-processing problems | Recursion |
| [A3 – Course scheduler](a3-course-scheduler/) | Assigns teachers to courses based on their free days, read from standard input | Top-down design |
| [A4 – Employee management](a4-employee-management-oop/) | A CLI over CSV data (employees, teams, working hours, salary configs) that computes salaries and team reports | Object-oriented design |
| [A5 – Turtix](a5-turtix-sfml-game/) | A 2-D platformer inspired by *Turtix*, with sprite animation, collision detection, platforms and maps loaded from text files | **SFML**, event-driven programming |
| [A6 – Driver missions](a6-driver-missions/) | A ride-hailing mission system: drivers complete time-, distance- and count-based missions, with a class hierarchy for mission types | Inheritance, polymorphism, multi-file builds |
| [A7 – Fantasy football](a7-fantasy-football/) *(team)* | A fantasy-football league with users, fantasy teams, real teams, weekly matches and scoring, driven by a command-line interface | OOD, polymorphism, exceptions |
| [Bonus – Tourist planner](bonus-tourist-planner/) | Plans a sightseeing route through Tehran's attractions (opening hours and ranks, from CSV) | Top-down design |
| [Quiz maker](quiz-maker/) | A quiz engine with single-answer, multiple-answer and short-answer questions | Class hierarchies, Makefile project |

## Building

Single-file projects: `g++ -std=c++20 main.cpp -o main`. Multi-file projects have a `Makefile` (`make`). A5 needs **SFML**: `brew install sfml` / `sudo apt install libsfml-dev`.
