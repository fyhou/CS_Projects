
all: toascii countlines2 towords rpncalc printargs

toascii: toascii.c
	gcc -g -o toascii toascii.c

countlines2: countlines2.c
	gcc -g -o countlines2 countlines2.c

towords: towords.c
	gcc -g -o towords towords.c

rpncalc: rpncalc.c
	gcc -g -o rpncalc rpncalc.c -lm

printargs: printargs.c
	gcc -g -o printargs printargs.c

clean:
	rm -f toascii countlines2 towords printargs rpncalc hello *out
