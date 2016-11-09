incr:= incr.o
incr1:= incr1.o
incr2:= incr2.o
incranon:= incranon.o
incrzero:= incrzero.o
test:= test.o
test1:= test1.o
create:= create.o
unlink:= unlink.o
write:= write.o
read:= read.o
test2:= test2.o
client:= client.o
server:= server.o
client1:= client1.o
server1:= server1.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/myClib
libs+= -L/home/canux/myCode/myClib -ldynamic -Wl,-rpath=/home/canux/myCode/myClib -lpthread -lrt

incr: $(incr)
	$(cc) $(cflag) -o incr $(incr) $(libs)

incr1: $(incr1)
	$(cc) $(cflag) -o incr1 $(incr1) $(libs)

incr2: $(incr2)
	$(cc) $(cflag) -o incr2 $(incr2) $(libs)

incranon: $(incranon)
	$(cc) $(cflag) -o incranon $(incranon) $(libs)

incrzero: $(incrzero)
	$(cc) $(cflag) -o incrzero $(incrzero) $(libs)

test: $(test)
	$(cc) $(cflag) -o test $(test) $(libs)

test1: $(test1)
	$(cc) $(cflag) -o test1 $(test1) $(libs)

create: $(create)
	$(cc) $(cflag) -o create $(create) $(libs)

unlink: $(unlink)
	$(cc) $(cflag) -o unlink $(unlink) $(libs)

write: $(write)
	$(cc) $(cflag) -o write $(write) $(libs)

read: $(read)
	$(cc) $(cflag) -o read $(read) $(libs)

test2: $(test2)
	$(cc) $(cflag) -o test2 $(test2) $(libs)

client: $(client)
	$(cc) $(cflag) -o client $(client) $(libs)

server: $(server)
	$(cc) $(cflag) -o server $(server) $(libs)

client1: $(client1)
	$(cc) $(cflag) -o client1 $(client1) $(libs)

server1: $(server1)
	$(cc) $(cflag) -o server1 $(server1) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o incr incr1 incr2 incranon incrzero test test1 create unlink read write test2 client server server1 client1
