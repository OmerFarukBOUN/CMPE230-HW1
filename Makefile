all: deneme hashmap

deneme: deneme.c
	gcc -Wall -o deneme deneme.c

hashmap: hashmap.c
	gcc -Wall -o hashmap hashmap.c

clean:
	rm -f deneme hashmap
