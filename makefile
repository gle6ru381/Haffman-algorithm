.PHONY: clean
FLAGS=-Wall -Werror -g3
bin/compress: $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))
	gcc $^ $(FLAGS) -o $@ 

build/%.o: src/%.c
	gcc -o $@ $(FLAGS) -c -MD $<

clean:
	rm build/*.o
	rm build/*.d

include $(wildcard build/*.d)