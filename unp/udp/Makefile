objcli=udpcli01.o dg_cli.o

objserv=udpservselect01.o str_echo01.o

include=-I../Mylib/

udpcli: $(objcli) 
	gcc -o udpcli $(objcli) -lstatic -L../Mylib/

udpserv: $(objserv) 
	gcc -o udpserv $(objserv) -lstatic -L../Mylib/

%.o: %.c
	gcc $(include) -o $@ $< -c -lstatic -L../Mylib/

clean:
	rm -f *.o udpcli udpserv
