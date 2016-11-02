CC = gcc
CFLAGS = -Wall
#RM = rm -f
VALGRIND = -g
OBJ_PATH = ./obj
BIN_PATH = ./bin

#NOMBRE
TARGET = $(BIN_PATH)/Final
TARGET_TEST = $(TARGET)-test
TARGET_VALGRIND = $(TARGET)-valgrind
#TARGET_RK = $(BIN_PATH)/RungeKutta

SUBMENU-RK = $(OBJ_PATH)/submenu-rungeKutta.o
LISTA = $(OBJ_PATH)/lista.o
MENU = $(OBJ_PATH)/menumgr.o $(OBJ_PATH)/screen.o
SHUNTING-YARD = $(OBJ_PATH)/shunting-yard.o $(OBJ_PATH)/stack.o
EXTRA-STRING = $(OBJ_PATH)/string_extra.o

ALL = $(OBJ_PATH)/main.o \
			$(SUBMENU-RK) \
			$(MENU) $(LISTA) $(SHUNTING-YARD) $(EXTRA-STRING) \
			$(OBJ_PATH)/rungeKutta4.o

TEST = $(OBJ_PATH)/test.o \
			$(MENU) $(LISTA) $(SHUNTING-YARD) $(EXTRA-STRING) \
			$(OBJ_PATH)/rungeKutta4.o

.PHONY : clean

all: rungekutta valgrind test

rungekutta: directorios $(ALL)
	$(CC) $(CFLAGS) $(ALL) -o $(TARGET) -lm

test: directorios $(TEST)
	$(CC) $(CFLAGS) $(TEST) -o $(TARGET_TEST) -lm

valgrind: directorios $(ALL)
	$(CC) $(CFLAGS) $(VALGRIND) $(ALL) -o $(TARGET_VALGRIND) -lm

#===========================
directorios: obj bin
obj:
	@mkdir -p $(OBJ_PATH)/
bin:
	@mkdir -p $(BIN_PATH)/
#===========================
#MAIN
$(OBJ_PATH)/main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/test.o: funciones/runge-kutta/test-RK.c
	$(CC) $(CFLAGS) -c funciones/runge-kutta/test-RK.c -o $(OBJ_PATH)/test.o

#MENU
$(OBJ_PATH)/menumgr.o: menu/menumgr.c menu/screen.h menu/menumgr.h menu/mydefs.h
	$(CC) $(CFLAGS) -c menu/menumgr.c -o $(OBJ_PATH)/menumgr.o

$(OBJ_PATH)/screen.o: menu/screen.c menu/screen.h
	$(CC) $(CFLAGS) -c menu/screen.c -o $(OBJ_PATH)/screen.o

#SUBMENU
$(OBJ_PATH)/submenu-rungeKutta.o: \
	funciones/runge-kutta/submenu-rungeKutta.c funciones/runge-kutta/submenu-rungeKutta.h \
	funciones/runge-kutta/rungeKutta4.h \
	menu/menumgr.h menu/mydefs.h\
	lista/lista.h extras/string_extra.h
	$(CC) $(CFLAGS) -c funciones/runge-kutta/submenu-rungeKutta.c -o $(OBJ_PATH)/submenu-rungeKutta.o

#FUNCIONES
$(OBJ_PATH)/rungeKutta4.o: \
	funciones/runge-kutta/rungeKutta4.c funciones/runge-kutta/rungeKutta4.h \
	lista/lista.h \
	extras/string_extra.h \
	shunting-yard/shunting-yard.h
	$(CC) $(CFLAGS) -c funciones/runge-kutta/rungeKutta4.c -o $(OBJ_PATH)/rungeKutta4.o

#LISTA
$(OBJ_PATH)/lista.o: lista/lista.c lista/lista.h
	$(CC) $(CFLAGS) -c lista/lista.c -o $(OBJ_PATH)/lista.o

#SHUTING-YARD
$(OBJ_PATH)/shunting-yard.o: shunting-yard/shunting-yard.c shunting-yard/shunting-yard.h shunting-yard/stack.h
		$(CC) $(CFLAGS) -c shunting-yard/shunting-yard.c -lm -o $(OBJ_PATH)/shunting-yard.o

$(OBJ_PATH)/stack.o: shunting-yard/stack.c shunting-yard/stack.h
	$(CC) $(CFLAGS) -c shunting-yard/stack.c -o $(OBJ_PATH)/stack.o

#STRING-EXTRA
$(OBJ_PATH)/string_extra.o: extras/string_extra.c extras/string_extra.h
	$(CC) $(CFLAGS) -c extras/string_extra.c -o $(OBJ_PATH)/string_extra.o

#===========================
borrar:
	$(RM) $(BIN_PATH)/ -R
	$(RM) $(OBJ_PATH)/ -R

clean:
	$(RM) $(TARGET)
	$(RM) $(OBJ_PATH)/*.o
#===========================
#install:
