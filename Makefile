CFLAGS=-Wall -lpthread

libext2fsal:  e2fs.o ext2fsal.o ext2fsal_cp.o ext2fsal_rm.o ext2fsal_ln_hl.o ext2fsal_ln_sl.o ext2fsal_mkdir.o
	gcc $(CFLAGS) -o libext2fsal.o $^

%.o : %.c header.h
	gcc $(CFLAGS) -g -c $<

clean : 
	rm -f *.o libext2fsal.so *~
