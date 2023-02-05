all: towers

debug: main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -D PLATFORM_LINUX main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp -o towers -g

towers: main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -D PLATFORM_LINUX main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp -o towers

win-64-debug: main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp
	x86_64-w64-mingw32-g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -D PLATFORM_WINDOWS main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp -o towers -g

clean:
	rm -f towers
	rm -f towers.exe
