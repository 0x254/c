obj=mainfifo.o msgclient.o msgserver.o msg.o

include=-I/home/canux/testCode/Mylib/

fifo: $(obj) 
	gcc -o fifo $(obj) -lstatic -L/home/canux/testCode/Mylib/

%.o: %.c 
	gcc $(include) -o $@ $< -c -lstatic -L/home/canux/testCode/Mylib/

clean:
	rm -f *.o fifo client server
