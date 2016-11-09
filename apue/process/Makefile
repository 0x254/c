atexit:= atexit.o
env:= env.o
limit:= limit.o
jmp:= jmp.o
fork:= fork.o
wait:= wait.o
waitpid:= waitpid.o
compete:= compete.o
nocompete:= nocompete.o
exec:= exec.o
system:= system.o
getlogin:= getlogin.o
times:= times.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/myClib
libs+= -L/home/canux/myCode/myClib -ldynamic -Wl,-rpath=/home/canux/myCode/myClib

atexit: $(atexit)
	$(cc) $(cflag) -o atexit $(atexit) $(libs)

env: $(env)
	$(cc) $(cflag) -o env $(env) $(libs)

limit: $(limit)
	$(cc) $(cflag) -o limit $(limit) $(libs)

jmp: $(jmp)
	$(cc) $(cflag) -o jmp $(jmp) $(libs)

fork: $(fork)
	$(cc) $(cflag) -o fork $(fork) $(libs)

wait: $(wait)
	$(cc) $(cflag) -o wait $(wait) $(libs)

waitpid: $(waitpid)
	$(cc) $(cflag) -o waitpid $(waitpid) $(libs)

compete: $(compete)
	$(cc) $(cflag) -o compete $(compete) $(libs)

nocompete: $(nocompete)
	$(cc) $(cflag) -o nocompete $(nocompete) $(libs)

exec: $(exec)
	$(cc) $(cflag) -o exec $(exec) $(libs)

system: $(system)
	$(cc) $(cflag) -o system $(system) $(libs)

getlogin: $(getlogin)
	$(cc) $(cflag) -o getlogin $(getlogin) $(libs)

times: $(times)
	$(cc) $(cflag) -o times $(times) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o atexit env limit jmp fork wait waitpid compete nocompete exec system getlogin times
