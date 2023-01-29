all: towers

debug: main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp
	g++ -std=c++17 main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp -o towers -g

towers: main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp
	g++ -std=c++17 main.cpp parse.cpp move_parser.cpp help.cpp Disk.cpp Tower.cpp TowerDrawer.cpp -o towers

clean:
	rm towers
