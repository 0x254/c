rtobj:=getrt.o get_rtaddrs.o

cc+=gcc
cflags+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath+=/home/canux/myCode/Mylib

rt: $(rtobj)
	$(cc) $(cflags) -o rt $(rtobj) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -c -o $@ $<

clean:
	rm -f rt *.o

