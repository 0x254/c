#cliobj:=tcpcli01.o str_clinob.o
#cliobj:=tcpcli01.o str_clifork.o
#servobj:=tcpservselect.o str_echo01.o

#cliobj:=timecli.o
#servobj:=timeserv.o

webobj:=web.o write_get_cmd.o home_page.o start_connect.o

cc+=gcc
cflags+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib
#libs+=-L/home/canux/myCode/Mylib -lstatic

cli:$(cliobj)
	$(cc) $(cflags) $(include) -o cli $(cliobj) $(libs)

serv:$(servobj)
	$(cc) $(cflags) $(include) -o serv $(servobj) $(libs)

web: $(webobj)
	$(cc) $(cflags) -o web $(webobj) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -c -o $@ $<

clean:
	rm -f serv cli *.o web
