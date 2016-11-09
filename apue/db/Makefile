test:= test.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/cAPI
libs+= -ldynamic -lgdbm_compat  -L/home/canux/myCode/cAPI -Wl,-rpath=/home/canux/myCode/cAPI

test: $(test)
	$(cc) $(cflag) -o test $(test) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o test
