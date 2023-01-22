all: towers

towers: Disk.cpp main.cpp Tower.cpp TowerDrawer.cpp
	g++ -std=c++17 Disk.cpp main.cpp Tower.cpp TowerDrawer.cpp -o towers -g

clean:
	rm towers
