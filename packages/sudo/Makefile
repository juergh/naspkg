SUDO := sudo-1.6.8p12

SRC := $(SUDO)

include ../../build/make.rules

BDIR := $(BUILD)/$(SUDO)

$(INSTALL)/bin/sudo:
	install -d -m0755 $(INSTALL)/bin
	install -m0755 $(STAGING)/usr/bin/sudo $(INSTALL)/bin

$(BDIR)/sudo:
	cd $(BDIR) && \
		./configure --host=i686-pc-linux-gnu --prefix=/usr \
			--disable-shared
	$(MAKE) -C $(BDIR)
	$(MAKE) -C $(BDIR) DESTDIR=$(STAGING) install

$(SUDO)-install: $(INSTALL)/bin/sudo

$(SUDO)-build: $(BDIR)/sudo
