all: towers

towers: main.cpp parse.cpp move_parser.cpp Disk.cpp Tower.cpp TowerDrawer.cpp
	g++ -std=c++17 main.cpp parse.cpp move_parser.cpp Disk.cpp Tower.cpp TowerDrawer.cpp -o towers -g

clean:
	rm towers
