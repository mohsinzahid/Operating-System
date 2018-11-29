all: output_A.out output_C.out

output_A.out: problem_A.o function.o
	gcc problem_A.o function.o -o output_A.out

output_C.out: problem_C.o function.o
	gcc problem_C.o function.o -o output_C.out

problem_A.o: problem_A.c
	gcc -c problem_A.c -Wall -Werror -pedantic

problem_C.o: problem_A.c
	gcc -c problem_C.c -Wall -Werror -pedantic

function.o:
	gcc -c function.c -Wall -Werror -pedantic

clean:
	rm -rfv *.o *.out
