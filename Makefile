proj3.exe: main.o menu.o ColorClass.o RowColumnClass.o ColorImageClass.o 
	g++ main.o menu.o ColorClass.o RowColumnClass.o ColorImageClass.o -o proj3.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

menu.o: menu.h menu.cpp
	g++ -c menu.cpp -o menu.o

ColorClass.o: ColorClass.h ColorClass.cpp
	g++ -c ColorClass.cpp -o ColorClass.o

RowColumnClass.o: RowColumnClass.h RowColumnClass.cpp
	g++ -c RowColumnClass.cpp -o RowColumnClass.o

ColorImageClass.o: ColorImageClass.h ColorImageClass.cpp
	g++ -c ColorImageClass.cpp -o ColorImageClass.o

clean:
	rm -rf main.o menu.o ColorImageClass.o ColorClass.o RowColumnClass.o proj3.exe


