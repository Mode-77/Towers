all: hanoi

hanoi: Disk.cpp main.cpp Tower.cpp TowerDrawer.cpp
	g++ -std=c++17 Disk.cpp main.cpp Tower.cpp TowerDrawer.cpp -o hanoi

clean:
	rm hanoi
