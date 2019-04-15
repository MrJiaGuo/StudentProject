project:main.o manager.o teacher.o student.o
	gcc main.o manager.o teacher.o student.o -o project
main.o:main.c
	gcc -c main.c
manager.o:manager.c
	gcc -c manager.c
teacher.o:teacher.c
	gcc -c teacher.c
student.o:student.c
	gcc -c student.c

clean:
	rm -r *.o project
