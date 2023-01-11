all: hanoi

hanoi: Disk.cpp main.cpp PerfectHanoi.cpp Tower.cpp TowerDrawer.cpp unit_tests.cpp
	g++ -std=c++17 Disk.cpp main.cpp PerfectHanoi.cpp Tower.cpp TowerDrawer.cpp unit_tests.cpp -o hanoi

clean:
	rm hanoi
