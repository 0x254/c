testopen:= testopen.o
testlseek:= testlseek.o
testwrite:= testwrite.o
rw:= rw.o
fcntl:= fcntl.o
stat:= stat.o
access:= access.o
umask:= umask.o
chmod:= chmod.o
link:= link.o
unlink:= unlink.o
utime:= utime.o
dir:= dir.o
dev:= dev.o
char:= char.o
string:= string.o
fopen:= fopen.o
tempfile:= tempfile.o

cc+= gcc
cflag+= -g
include+= -I/home/canux/myCode/myClib
libs+= -L/home/canux/myCode/myClib -ldynamic -Wl,-rpath=/home/canux/myCode/myClib

testopen: $(testopen)
	$(cc) $(cflag) -o testopen $(testopen) $(libs)

testlseek: $(testlseek)
	$(cc) $(cflag) -o testlseek $(testlseek) $(libs)

testwrite: $(testwrite)
	$(cc) $(cflag) -o testwrite $(testwrite) $(libs)

rw: $(rw)
	$(cc) $(cflag) -o rw $(rw) $(libs)

fcntl: $(fcntl)
	$(cc) $(cflag) -o fcntl $(fcntl) $(libs)

stat: $(stat)
	$(cc) $(cflag) -o stat $(stat) $(libs)

access: $(access)
	$(cc) $(cflag) -o access $(access) $(libs)

umask: $(umask)
	$(cc) $(cflag) -o umask $(umask) $(libs)

chmod: $(chmod)
	$(cc) $(cflag) -o chmod $(chmod) $(libs)

unlink: $(unlink)
	$(cc) $(cflag) -o unlink $(unlink) $(libs)

link: $(link)
	$(cc) $(cflag) -o link $(link) $(libs)

utime: $(utime)
	$(cc) $(cflag) -o utime $(utime) $(libs)

dir: $(dir)
	$(cc) $(cflag) -o dir $(dir) $(libs)

dev: $(dev)
	$(cc) $(cflag) -o dev $(dev) $(libs)

char: $(char)
	$(cc) $(cflag) -o char $(char) $(libs)

string: $(string)
	$(cc) $(cflag) -o string $(string) $(libs)

fopen: $(fopen)
	$(cc) $(cflag) -o fopen $(fopen) $(libs)

tempfile: $(tempfile)
	$(cc) $(cflag) -o tempfile $(tempfile) $(libs)

%.o: %.c
	$(cc) $(cflag) $(include) -c -o $@ $<

clean:
	rm -f *.o testopen testlseek testwrite rw fcntl stat access umask chmod unlink link utime dir dev char string fopen tempfile
