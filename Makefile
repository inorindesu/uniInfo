
all: out/uniInfo

out/uniInfo: main.c out/mark
	gcc `pkg-config glib-2.0 --libs --cflags` main.c -o out/uniInfo -std=c99

out/mark:
	mkdir -p out
	touch out/mark

.PHONY: clean
clean:
	rm -rf out
