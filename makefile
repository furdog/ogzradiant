#LINUX ONLY
SRC := sauerbraten/src

all:
	$(MAKE) -C $(SRC)
	mkdir -p linux/build
	cp $(SRC)/sauer_client linux/build/native_client

test:
	gcc ogzradiant.test.c -std=c89 -pedantic -Wall -Wextra -g

clean:
	$(MAKE) -C $(SRC) clean
	rm -rf linux/build

format:
	clang-format -style=file -i ogzradiant.h
	#clang-format -style=file -i *.c *.h
