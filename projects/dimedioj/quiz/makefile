testme: testme.c
	gcc -o testme testme.c -coverage
	-testme
	gcov testme.c -b

clean:
	rm -f testme a.out *.0 *~ *.gcov *.gcda *.gcno
