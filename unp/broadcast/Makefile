cliobj:= udpcli01.o dg_cli03.o
servobj:=udpserv01.o dg_echo.o

cc+=gcc
cflags+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib

cli: $(cliobj)
	$(cc) $(cflags) -o cli $(cliobj) $(libs)

serv: $(servobj)
	$(cc) $(cflags) -o serv $(servobj) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -c -o $@ $<

clean:
	rm -f *.o cli serv
