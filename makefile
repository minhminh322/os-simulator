pr1.out: driver.o partition.o process.o listADTgen.o queue.h
	     gcc -o pr1.out driver.o partition.o process.o listADTgen.o queue.h

driver.o: driver.c partition.h process.h listADTgen.h queue.h
	  gcc -c driver.c

partition.o: partition.c partition.h
	     gcc -c partition.c

process.o: process.c process.h
	   gcc -c process.c

listADT.o: listADTgen.c listADTgen.h
	   gcc -c listADTgen.c



