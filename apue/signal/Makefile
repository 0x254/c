signal:= signal.o
reentry:= reentry.o
alarm:= alarm.o
aj:= aj.o
sigset:= sigset.o
sigjmp:= sigjmp.o
sigsuspend:= sigsuspend.o
sigsusvar:= sigsusvar.o
system:= system.o
job:= job.o
sigmsg:= sigmsg.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/cAPI
libs+= -L/home/canux/myCode/cAPI -ldynamic -Wl,-rpath=/home/canux/myCode/cAPI

signal: $(signal)
	$(cc) $(cflag) -o signal $(signal) $(libs)

reentry: $(reentry)
	$(cc) $(cflag) -o reentry $(reentry) $(libs)

alarm: $(alarm)
	$(cc) $(cflag) -o alarm $(alarm) $(libs)

aj: $(aj)
	$(cc) $(cflag) -o aj $(aj) $(libs)

sigset: $(sigset)
	$(cc) $(cflag) -o sigset $(sigset) $(libs)

sigjmp: $(sigjmp)
	$(cc) $(cflag) -o sigjmp $(sigjmp) $(libs)

sigsuspend: $(sigsuspend)
	$(cc) $(cflag) -o sigsuspend $(sigsuspend) $(libs)

sigsusvar: $(sigsusvar)
	$(cc) $(cflag) -o sigsusvar $(sigsusvar) $(libs)

system: $(system)
	$(cc) $(cflag) -o system $(system) $(libs)

job: $(job)
	$(cc) $(cflag) -o job $(job) $(libs)

sigmsg: $(sigmsg)
	$(cc) $(cflag) -o sigmsg $(sigmsg) $(libs)
	
%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o signal reentry alarm aj sigset sigjmp sigsuspend sigsusvar system job sigmsg
