SRC := src/

all:
	$(MAKE) -C $(SRC)
	$(MAKE) -C $(SRC) install

clean:
	$(MAKE) -C $(SRC) clean
