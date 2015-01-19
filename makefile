all: juby

juby:
	gcc src/*.c -o juby -Wno-missing-braces
