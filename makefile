all: towers

debug: main.cpp screen.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp syntax_parser.cpp
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -D PLATFORM_LINUX main.cpp screen.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp syntax_parser.cpp -o towers -g

towers: main.cpp screen.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp syntax_parser.cpp
	g++ -std=c++17 -D PLATFORM_LINUX main.cpp screen.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp syntax_parser.cpp -o towers

win-64-debug: main.cpp screen.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp syntax_parser.cpp
	x86_64-w64-mingw32-g++ -std=c++17 -D PLATFORM_WINDOWS main.cpp screen.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp syntax_parser.cpp -o towers -g

clean:
	rm -f towers
	rm -f towers.exe
