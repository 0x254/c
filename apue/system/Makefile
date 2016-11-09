pw:= pw.o
pwent:= pwent.o
sp:= sp.o
spent:= spent.o
gr:= gr.o
grent:= grent.o
name:= name.o
time:= time.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/myClib
libs+= -L/home/canux/myCode/myClib -ldynamic -Wl,-rpath=/home/canux/myCode/myClib

pw: $(pw)
	$(cc) $(cflag) -o pw $(pw) $(libs)

pwent: $(pwent)
	$(cc) $(cflag) -o pwent $(pwent) $(libs)

sp: $(sp)
	$(cc) $(cflag) -o sp $(sp) $(libs)

spent: $(spent)
	$(cc) $(cflag) -o spent $(spent) $(libs)

gr: $(gr)
	$(cc) $(cflag) -o gr $(gr) $(libs)

grent: $(grent)
	$(cc) $(cflag) -o grent $(grent) $(libs)

name: $(name)
	$(cc) $(cflag) -o name $(name) $(libs)

time: $(time)
	$(cc) $(cflag) -o time $(time) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o pw pwent sp spent gr grent name time
