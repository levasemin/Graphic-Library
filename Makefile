CC = g++ --std=c++17

BuildF = obj/

event_handler: clean $(BuildF)Window.o $(BuildF)functions.o $(BuildF)main.o $(BuildF)Color.o
	$(CC) 			 $(BuildF)Window.o $(BuildF)functions.o $(BuildF)main.o $(BuildF)Color.o -o event_handler -lsfml-graphics -lsfml-window -lsfml-system

$(BuildF)main.o:
	$(CC) -c main.cpp -o $(BuildF)main.o

$(BuildF)Window.o:
	$(CC) -c Window.cpp -o $(BuildF)Window.o

$(BuildF)functions.o:
	$(CC) -c functions.cpp -o $(BuildF)functions.o

$(BuildF)Color.o:
	$(CC) -c Color.cpp -o $(BuildF)Color.o

clean:
	rm -rf $(BuildF)/*.o