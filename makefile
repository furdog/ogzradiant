#LINUX ONLY
SRC := sauerbraten/src

all:
	$(MAKE) -C $(SRC)
	mkdir -p linux/build
	cp $(SRC)/sauer_client linux/build/native_client

clean:
	$(MAKE) -C $(SRC) clean
