test:= test.o
test1:= test1.o
isatty:= isatty.o
ttyname:= ttyname.o
ctermid:= ctermid.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/cAPI
libs+= -ldynamic -L/home/canux/myCode/cAPI -Wl,-rpath=/home/canux/myCode/cAPI

test: $(test)
	$(cc) $(cflag) -o test $(test) $(libs)

test1: $(test1)
	$(cc) $(cflag) -o test1 $(test1) $(libs)

isatty: $(isatty)
	$(cc) $(cflag) -o isatty $(isatty) $(libs)

ttyname: $(ttyname)
	$(cc) $(cflag) -o ttyname $(ttyname) $(libs)

ctermid: $(ctermid)
	$(cc) $(cflag) -o ctermid $(ctermid) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o test test1 isatty ttyname ctermid ctermid ctermid ctermid
