DROPBEAR := dropbear-0.53.1

SRC := $(DROPBEAR)

include ../../build/make.rules

BDIR := $(BUILD)/$(DROPBEAR)

$(INSTALL)/bin/dropbear:
	install -d -m0755 $(INSTALL)/bin
	install -m0755 $(STAGING)/usr/sbin/dropbear $(INSTALL)/bin
	install -m0755 $(STAGING)/usr/bin/dropbearkey $(INSTALL)/bin
	install -m0755 $(STAGING)/usr/bin/scp $(INSTALL)/bin

$(BDIR)/dropbear:
	cd $(BDIR) && \
		./configure --host=i686-pc-linux-gnu --prefix=/usr \
			--disable-syslog --disable-lastlog --disable-wtmp \
			--disable-wtmpx
	$(MAKE) -C $(BDIR) PROGRAMS="dropbear dropbearkey scp" \
		DESTDIR=$(STAGING) strip install

$(DROPBEAR)-install: $(INSTALL)/bin/dropbear

$(DROPBEAR)-build: $(BDIR)/dropbear


