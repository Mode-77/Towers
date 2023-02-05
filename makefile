all: linux-debug win-64-debug

linux-debug: towers-de

towers-de: main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -D PLATFORM_LINUX main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp -o towers-de -g

win-64-debug: towers-de-win-x86-64.exe

towers-de-win-x86-64.exe: main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp
	x86_64-w64-mingw32-g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -D PLATFORM_WINDOWS main.cpp game.cpp screen.cpp parse.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp game_parser.cpp -o towers-de-win-x86-64 -g

clean:
	rm -f towers-de
	rm -f towers-de-win-x86-64.exe
