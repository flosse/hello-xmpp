default: client.o
	gcc -o client client.o -Llibstrophe -lstrophe -lssl -lresolv -lexpat

client.o: client.c
	gcc -c -Ilibstrophe client.c

clean:
	rm *.o client
