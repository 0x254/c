keyobj:=dump.o name.o printsadbmsg.o

cc+=gcc
cflags+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib

key: $(keyobj)
	$(cc) $(cflags) -o key $(keyobj) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -c -o $@ $<

clean:
	rm -f *.o key
