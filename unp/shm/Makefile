get:= get.o
rmid:= rmid.o
read:= read.o
write:= write.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/myClib
libs+= -L/home/canux/myCode/myClib -ldynamic -Wl,-rpath=/home/canux/myCode/myClib

get: $(get)
	$(cc) $(cflag) -o get $(get) $(libs)

rmid: $(rmid)
	$(cc) $(cflag) -o rmid $(rmid) $(libs)

write: $(write)
	$(cc) $(cflag) -o write $(write) $(libs)

read: $(read) 
	$(cc) $(cflag) -o read $(read) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o get rmid read write
