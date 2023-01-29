all: towers

debug: main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp
	g++ -std=c++17 main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp -o towers -g

towers: main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp
	g++ -std=c++17 main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp -o towers

win-64-debug:
	x86_64-w64-mingw32-g++ -std=c++17 main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp -o towers -g

clean:
	rm towers
