create:= create.o
unlink:= unlink.o
getvalue:= getvalue.o
wait:= wait.o
post:= post.o
pc:= prodcons.o
pc1:= prodcons1.o
pc2:= prodcons2.o
pc3:= prodcons3.o
buffer:= buffer.o

cc+=gcc
cflag+=-g
include+=-I/home/canux/myCode/myClib
libs+=-L/home/canux/myCode/myClib -ldynamic -Wl,-rpath=/home/canux/myCode/myClib

create: $(create)
	$(cc) $(cflag) -o create $(create) $(libs)

unlink: $(unlink)
	$(cc) $(cflag) -o unlink $(unlink) $(libs)

getvalue: $(getvalue)
	$(cc) $(cflag) -o getvalue $(getvalue) $(libs)

wait: $(wait)
	$(cc) $(cflag) -o wait $(wait) $(libs)

post: $(post)
	$(cc) $(cflag) -o post $(post) $(libs)

pc: $(pc)
	$(cc) $(cflag) -o pc $(pc) $(libs)

pc1: $(pc1)
	$(cc) $(cflag) -o pc1 $(pc1) $(libs)

pc2: $(pc2)
	$(cc) $(cflag) -o pc2 $(pc2) $(libs)

pc3: $(pc3)
	$(cc) $(cflag) -o pc3 $(pc3) $(libs)

buffer: $(buffer)
	$(cc) $(cflag) -o buffer $(buffer) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o create unlink getvalue wait post pc pc1 pc2 pc3 buffer
