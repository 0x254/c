client:= client.o

iterate:= iterate.o web_child.o
concurrent:=concurrent.o web_child.o sig_int.o
thread:= thread.o web_child.o sig_int.o

cc+=gcc
cflags+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib

cli: $(client)
	$(cc) $(cflags) -o cli $(client) $(libs)

ite: $(iterate)
	$(cc) $(cflags) -o ite $(iterate) $(libs)
con: $(concurrent)
	$(cc) $(cflags) -o con $(concurrent) $(libs)
thr: $(thread)
	$(cc) $(cflags) -o thr $(thread) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -c -o $@ $< 

clean:
	rm -f *.o cli ite con thr
