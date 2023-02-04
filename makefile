all: towers

debug: core_game.cpp main.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp game.cpp
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -D PLATFORM_LINUX core_game.cpp main.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp game.cpp -o towers -g

towers: core_game.cpp main.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp game.cpp
	g++ -std=c++17 -D PLATFORM_LINUX core_game.cpp main.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp game.cpp -o towers

win-64-debug: core_game.cpp main.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp game.cpp
	x86_64-w64-mingw32-g++ -std=c++17 -D PLATFORM_WINDOWS core_game.cpp main.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp game.cpp -o towers -g

clean:
	rm -f towers
	rm -f towers.exe
