# Имя выходного файла
TARGET = app

# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -std=c++17

# SFML библиотеки
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Исходники
SRC = include/optimizer2.cpp

# Правило по умолчанию
all: $(TARGET)

# Правило сборки
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)
init:
	sudo apt install libsfml-dev
# Очистка
clean:
	rm -f $(TARGET)
