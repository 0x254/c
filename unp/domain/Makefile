tcpcli=tcpcli.o str_cli01.o
#tcpserv=tcpserv.o str_echo01.o
tcpserv=tcpserv.o str_echocred.o

mycatobj=mycat.o read_fd.o
openfileobj=openfile.o write_fd.o

udpcli=udpcli.o dg_cli.o
udpserv=udpserv.o dg_echo.o

include=-I$(HOME)/myCode/Mylib
lib=-lstatic -L$(HOME)/myCode/Mylib

udpcli: $(udpcli)
	gcc -o cli $(udpcli) $(lib)

udpserv: $(udpserv)
	gcc -o serv $(udpserv) $(lib)

tcpcli: $(tcpcli)
	gcc -o cli $(tcpcli) $(lib)

tcpserv: $(tcpserv)
	gcc -o serv $(tcpserv) $(lib)

mycat: $(mycatobj)
	gcc -o mycat $(mycatobj) $(lib)

openfile: $(openfileobj)
	gcc -o openfile $(openfileobj) $(lib)

%.o: %.c
	gcc $(include) -o $@ $< -c 

clean:
	rm -f *.o serv cli openfile mycat
