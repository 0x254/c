pc:=prodcons.o
pc2:=prodcons2.o
pc3:=prodcons3.o
tc:=testcancel.o
lock:=lockmain.o

cc+=gcc
cflag+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib

pc: $(pc)
	$(cc) $(cflag) -o pc $(pc) $(libs)

pc2: $(pc2)
	$(cc) $(cflag) -o pc2 $(pc2) $(libs)

pc3: $(pc3)
	$(cc) $(cflag) -o pc3 $(pc3) $(libs)

tc: $(tc)
	$(cc) $(cflag) -o tc $(tc) $(libs)

lock: $(lock)
	$(cc) $(cflag) -o lock $(lock) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o pc pc2 pc3 tc lock
