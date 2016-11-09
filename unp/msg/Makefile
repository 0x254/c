ctl:=msgctl.o
create:=msgcreate.o
snd:=msgsnd.o
rcv:=msgrcv.o
rcvid:=msgrcvid.o
rmid:=msgrmid.o
server:=servermain.o msg.o server.o
client:=clientmain.o msg.o client.o
ser:=servermain2.o msg.o server2.o
cli:=clientmain2.o msg.o client2.o
ser3:=servermain3.o msg.o server3.o
cli3:=clientmain3.o msg.o client3.o

cc+=gcc
cflag+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib

ctl: $(ctl)
	$(cc) $(cflag) -o ctl $(ctl) $(libs)

create: $(create)
	$(cc) $(cflag) -o create $(create) $(libs)

snd: $(snd)
	$(cc) $(cflag) -o snd $(snd) $(libs)

rcv: $(rcv)
	$(cc) $(cflag) -o rcv $(rcv) $(libs)

rcvid: $(rcvid)
	$(cc) $(cflag) -o rcvid $(rcvid) $(libs)

rmid: $(rmid)
	$(cc) $(cflag) -o rmid $(rmid) $(libs)

server: $(server)
	$(cc) $(cflag) -o server $(server) $(libs)

client: $(client)
	$(cc) $(cflag) -o client $(client) $(libs)

ser: $(ser)
	$(cc) $(cflag) -o ser $(ser) $(libs)

cli: $(cli)
	$(cc) $(cflag) -o cli $(cli) $(libs)

ser3: $(ser3)
	$(cc) $(cflag) -o ser3 $(ser3) $(libs)

cli3: $(cli3)
	$(cc) $(cflag) -o cli3 $(cli3) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o ctl create snd rcv rcvid rmid client server cli ser cli3 ser3
