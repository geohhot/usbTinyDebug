
LIBUSB=`pkg-config --libs --cflags libusb-1.0`
PRG=term_0
LIBS_PATH=../libs/
#PRG=term
all:
	gcc -o $(PRG) -I$(LIBS_PATH) $(PRG).c $(LIBUSB) 

stuff: all
	./$(PRG)

clean:
	rm *~ *.o -rf
