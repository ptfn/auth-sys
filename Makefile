# Executables
RDB = rdb
IMC = imc
IPC = ipc
IPU = ipu

# Compile
CC = gcc
FLAGS = -Wall -Werror -std=gnu11
SQLITE = -lpthread -ldl -lm

# Folder
SRC = src
BIN = bin
LIB = libs

.PHONY: all clean 

all: $(RDB) $(IMC) $(IPC) $(IPU)

clean:
	rm -rf $(BIN)/*.o $(BIN)/$(RDB) $(BIN)/$(IMC) $(BIN)/$(IPC)

astp.o: astp.c
	$(CC) -c -o $(BIN)/astp.o $(SRC)/astp.c

sqlite3.o: $(LIB)/sqlite3.c
	$(CC) -c -o $(BIN)/sqlite3.o $(LIB)/sqlite3.c

shell.o: $(LIB)/shell.c
	$(CC) -c -o $(BIN)/shell.o $(LIB)/shell.c

totp.o: $(SRC)/totp.c
	$(CC) -c -o $(BIN)/totp.o $(SRC)/totp.c

rdb.o: rdb.c
	$(CC) -c -o $(BIN)/rdb.o $(SRC)/rdb.c

imc.o: imc.c
	$(CC) -c -o $(BIN)/imc.o $(SRC)/imc.c

ipc.o: ipc.c
	$(CC) -c -o $(BIN)/ipc.o $(SRC)/ipc.c

$(RDB): astp.o sqlite.o rdb.o
	$(CC) $(FLAGS) $(SQLITE) -o $(BIN)/$(RDB) $(BIN)/astp.o $(BIN)/sqlite.o $(BIN)/rdb.o 

$(IMC): astp.o imc.o
	$(CC) $(FLAGS) -o $(BIN)/$(IMC) $(BIN/)astp.o $(BIN)/imc.o 

$(IPC): astp.o ipc.o
	$(CC) $(FLAGS) -o $(BIN)/$(IPC) $(BIN)/astp.o $(BIN)/ipc.o 

desktop:
	gcc -Wall -Werror -std=gnu11 src/desktop.c `pkg-config --static --cflags --libs gtk4`

package:
	apt install gir1.2-gtk-4.0 gtk-4-examples gtk-4-tests libgtk-4-1 libgtk-4-bin libgtk-4-bin libgtk-4-common libgtk-4-dev libgtk-4-doc libgtk-4-media-gstreamer
