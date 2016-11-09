objcli=tcpcli01.o str_cli03.o 

objserv=tcpservpoll.o str_echo01.o

include=-I/home/canux/myCode/Mylib/

tcpcli: $(objcli) 
	gcc -o tcpcli $(objcli) -lstatic -L/home/canux/myCode/Mylib/

tcpserv: $(objserv) 
	gcc -o tcpserv $(objserv) -lstatic -L/home/canux/myCode/Mylib/

%.o: %.c 
	gcc $(include) -o $@ $< -c -lstatic -L/home/canux/myCode/Mylib/

clean:
	rm -f *.o tcpserv tcpcli
