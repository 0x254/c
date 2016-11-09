cli=sctpcli01.o sctp_strcli.o sctp_strcliecho.o

serv=sctpserv01.o sctp_get_no_strms.o sctp_addr_to_associd.o

cc+=gcc
libs+=-lstatic -L../Mylib -lsctp
cflags+=-g
include+=-I../Mylib

cli: $(cli)
	$(cc) $(cflags) -o cli $(cli) $(libs)

serv: $(serv)
	$(cc) $(cflags) -o serv $(serv) $(libs)

%.o: %.c
	$(cc) $(cflags) $(include) -o $@ $< -c $(libs)

clean:
	rm -f *.o cli serv
