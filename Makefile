build:
	gcc -g -O3 Librarie_Muzica.c -o pb1 -Wall
	./pb1 Input Output
	rm pb1
memory:
	gcc -g Librarie_Muzica.c -o pb1 -Wall
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 ./pb1 Input Output
	rm pb1
	rm Input
	mv Output Input
	touch Output