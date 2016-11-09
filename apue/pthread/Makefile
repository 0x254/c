create:= create.o
join:= join.o
cleanup:= cleanup.o
pfork:= pfork.o
psignal:= psignal.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/cAPI
libs+= -L/home/canux/myCode/cAPI -ldynamic -Wl,-rpath=/home/canux/myCode/cAPI -lpthread

create: $(create)
	$(cc) $(cflag) -o create $(create) $(libs)

join: $(join)
	$(cc) $(cflag) -o join $(join) $(libs)

cleanup: $(cleanup)
	$(cc) $(cflag) -o cleanup $(cleanup) $(libs)

pfork: $(pfork)
	$(cc) $(cflag) -o pfork $(pfork) $(libs)

psignal: $(psignal)
	$(cc) $(cflag) -o psignal $(psignal) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $< 

clean:
	rm -f *.o create join cleanup pfork psignal
