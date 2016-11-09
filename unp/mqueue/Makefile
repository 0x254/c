create1:=mqcreate1.o
unlink:=mqunlink.o
getattr:=mqgetattr.o
create2:=mqcreate2.o
send:=mqsend.o
receive:=mqreceive.o
nfs1:=mqnotifysig1.o
nfs2:=mqnotifysig2.o
nfs3:=mqnotifysig3.o
nfs4:=mqnotifysig4.o
nfs5:=mqnotifysig5.o
nft:=mqnotifythr.o
rt:=sigrt.o

cc+=gcc
cflags+=-g
include+=-I/home/canux/myCode/Mylib
libs+=-L/home/canux/myCode/Mylib -ldynamic -Wl,-rpath=/home/canux/myCode/Mylib -lrt

create1: $(create1)
	$(cc) $(cflags) -o create1 $(create1) $(libs)

unlink: $(unlink)
	$(cc) $(cflags) -o unlink $(unlink) $(libs)

getattr: $(getattr)
	$(cc) $(cflags) -o getattr $(getattr) $(libs)

create2: $(create2)
	$(cc) $(cflags) -o create2 $(create2) $(libs)

send: $(send)
	$(cc) $(cflags) -o send $(send) $(libs)

receive: $(receive)
	$(cc) $(cflags) -o receive $(receive) $(libs)

nfs1: $(nfs1)
	$(cc) $(cflags) -o nfs1 $(nfs1) $(libs)

nfs2: $(nfs2)
	$(cc) $(cflags) -o nfs2 $(nfs2) $(libs)

nfs3: $(nfs3)
	$(cc) $(cflags) -o nfs3 $(nfs3) $(libs) 

nfs4: $(nfs4)
	$(cc) $(cflags) -o nfs4 $(nfs4) $(libs)

nfs5: $(nfs5)
	$(cc) $(cflags) -o nfs5 $(nfs5) $(libs)

nft: $(nft)
	$(cc) $(cflags) -o nft $(nft) $(libs)

rt: $(rt)
	$(cc) $(cflags) -o rt $(rt) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -c -o $@ $<

clean:
	rm -f *.o create1 unlink getattr receive send create2 sysconf nfs* rt nft
