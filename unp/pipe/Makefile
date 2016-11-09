obj=mainpipe.o msgclient.o msgserver.o msg.o

include=-I/home/canux/testCode/Mylib/

pipe: $(obj) 
	gcc -o pipe $(obj) -lstatic -L/home/canux/testCode/Mylib/

%.o: %.c 
	gcc $(include) -o $@ $< -c -lstatic -L/home/canux/testCode/Mylib/

clean:
	rm -f *.o pipe client server
