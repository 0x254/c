obj:= myio.o mysocket.o mysignal.o myipc.o wrap_inet.o wrap_daemon.o wrap_error.o wrap_signal.o wrap_socket.o wrap_unix.o wrap_libc.o wrap_sctp.o wrap_ipc.o wrap_pthread.o

cc+= gcc
cflags+= -g
include+= -I/home/canux/myCode/myClib
libs+= -lsctp -lpthread -lrt -lgdbm -lgdbm_compat

######static library
#libstatic.a: $(obj)
#	ar -crv libstatic.a $(obj)

#%.o: %.c
#	gcc -static -c -o $@ $<

######dynamic library
libdynamic.so: $(obj)
	$(cc) $(cflags) -fPIC -shared -o libdynamic.so $(obj) $(libs)

%.o: %.c
	$(cc) $(cflags) -c -o $@ $<

clean:
	rm -f *.o *.a *.so
