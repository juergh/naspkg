include naspkg/info
include ../../build/make.rules

SRC = sudo-1.6.8p12

$(STAGING)/bin/sudo:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(SRC)/sudo $(STAGING)/bin

$(SRC)/sudo:
	cd $(SRC) && ./configure --host=i686-pc-linux-gnu
	$(MAKE) -C $(SRC)

$(NAME)-install: $(STAGING)/bin/sudo

$(NAME)-source: $(SRC)/sudo

$(NAME)-clean:
	$(MAKE) -C $(SRC) realclean
