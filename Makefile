main:
	gcc src/main.c -Wall -std=c99 -o uwulang

test:
	./uwulang test/hellOwOrld.uwu