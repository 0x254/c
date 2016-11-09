create:= create.o
rmid:= rmid.o
getvalue:= getvalue.o
setvalue:= setvalue.o
op:= op.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/myClib
libs+= -L/home/canux/myCode/myClib -ldynamic -Wl,-rpath=/home/canux/myCode/myClib

create: $(create)
	$(cc) $(cflag) -o create $(create) $(libs)

rm: $(rmid)
	$(cc) $(cflag) -o rm $(rmid) $(libs)

getvalue: $(getvalue)
	$(cc) $(cflag) -o getvalue $(getvalue) $(libs)

setvalue: $(setvalue)
	$(cc) $(cflag) -o setvalue $(setvalue) $(libs)

op: $(op)
	$(cc) $(cfalg) -o op $(op) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o create rm getvalue setvalue op
