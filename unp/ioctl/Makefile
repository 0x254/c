ifiobj:= printinfo.o get_ifi_info.o
arpobj:=printarp.o get_ifi_info.o

cc+=gcc
cflags+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib

ifi: $(ifiobj)
	$(cc) $(cflags) -o ifi $(ifiobj) $(libs)

arp: $(arpobj)
	$(cc) $(cflags) -o arp $(arpobj) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -c -o $@ $<

clean:
	rm -f *.o ifi arp
