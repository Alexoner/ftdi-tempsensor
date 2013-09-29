CC=clang
CFLAGS=-lftd2xx -lm -L/usr/local/lib -g -Wall

tempsensor.cgi:tempsensor.c tempsensor.cgi.c
	$(CC) -o $@ $^ $(CFLAGS)
test:test.c tempsensor.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o tempsensor tempsensor.cgi test
