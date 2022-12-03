CC = g+++

BuildF = obj/

event_handler: clean $(BuildF)Window.o $(BuildF)functions.o $(BuildF)main.o $(BuildF)Color.o $(BuildF)Vector2d.o $(BuildF)Event.o $(BuildF)plugin_func.o $(BuildF)ToolButton.o $(BuildF)Button.o $(BuildF)Font.o $(BuildF)ToolEraser.o
	$(CC) 			 $(BuildF)Window.o $(BuildF)functions.o $(BuildF)main.o $(BuildF)Color.o $(BuildF)Vector2d.o $(BuildF)Event.o $(BuildF)plugin_func.o $(BuildF)ToolButton.o $(BuildF)Button.o $(BuildF)Font.o $(BuildF)ToolEraser.o -o event_handler -lsfml-graphics -lsfml-window -lsfml-system -ldl -export-dynamic

$(BuildF)main.o:
	$(CC) -c main.cpp -o $(BuildF)main.o

$(BuildF)Window.o:
	$(CC) -c Window.cpp -o $(BuildF)Window.o

$(BuildF)functions.o:
	$(CC) -fPIC -c functions.cpp -o $(BuildF)functions.o 

$(BuildF)Color.o:
	$(CC) -fPIC -c Color.cpp -o $(BuildF)Color.o

$(BuildF)Vector2d.o:
	$(CC) -c Vector2d.cpp -o $(BuildF)Vector2d.o

$(BuildF)Event.o:
	$(CC) -c Event.cpp -o $(BuildF)Event.o

$(BuildF)plugin_func.o:
	$(CC) -c plugin_func.cpp -o $(BuildF)plugin_func.o

$(BuildF)ToolButton.o:
	$(CC) -c ToolButton.cpp -o $(BuildF)ToolButton.o

$(BuildF)Button.o:
	$(CC) -c Button.cpp -o $(BuildF)Button.o

$(BuildF)Font.o:
	$(CC) -c Font.cpp -o $(BuildF)Font.o

$(BuildF)ToolEraser.o:
	$(CC) -fPIC -c ToolEraser.cpp -o $(BuildF)ToolEraser.o

clean:
	rm -rf $(BuildF)/*.o


# $(PLUGINS_SRC)/%.cpp $(SRC)/kernel/tools.hpp
# $(CXX) $(CFLAGS) -shared -Wall -Wextra -o $@ -fPIC $<