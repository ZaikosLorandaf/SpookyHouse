main.exe: main.o init.o display.o print_buffer.o assets.o
	gcc -o $@ -Wall -pedantic-errors -O2 $^

main.o: main.c headers/init.h headers/display.h headers/coord.h headers/assets.h
	gcc -c -o $@ -Wall -pedantic-errors -O2 main.c

init.o: headers/init.h init.c
	gcc -c -o $@ -Wall -pedantic-errors -O2 init.c

display.o: headers/display.h headers/coord.h headers/print_buffer.h display.c
	gcc -c -o $@ -Wall -pedantic-errors -O2 display.c

print_buffer.o: headers/print_buffer.h print_buffer.c
	gcc -c -o $@ -Wall -pedantic-errors -O2 print_buffer.c

assets.o: headers/assets.h headers/print_buffer.h assets.c
	gcc -c -o $@ -Wall -pedantic-errors -O2 assets.c

.PHONY: clean

clean:
	rm -rf *.o
