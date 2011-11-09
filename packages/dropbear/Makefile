include naspkg/info
include ../../build/make.rules

SRC = dropbear-0.53.1

$(STAGING)/bin/dropbear:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(SRC)/dropbear $(STAGING)/bin
	install -m0755 $(SRC)/dropbearkey $(STAGING)/bin
	install -m0755 $(SRC)/scp $(STAGING)/bin

$(SRC)/dropbear:
	cd $(SRC) && ./configure --host=i686-pc-linux-gnu --disable-syslog \
		--disable-lastlog --disable-wtmp --disable-wtmpx
	$(MAKE) -C $(SRC)
	$(MAKE) -C $(SRC) scp

$(NAME)-install: $(STAGING)/bin/dropbear

$(NAME)-source: $(SRC)/dropbear

$(NAME)-clean:
	$(MAKE) -C $(SRC) distclean

