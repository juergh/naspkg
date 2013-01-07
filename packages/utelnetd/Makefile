UTELNETD := utelnetd-0.1.9

SRC := $(UTELNETD)

include ../../build/make.rules

BDIR := $(BUILD)/$(UTELNETD)

$(INSTALL)/bin/utelnetd:
	install -d -m0755 $(INSTALL)/bin
	install -m0755 $(STAGING)/usr/bin/utelnetd $(INSTALL)/bin

$(BDIR)/utelnetd:
	$(MAKE) -C $(BDIR)
	$(MAKE) -C $(BDIR) DESTDIR=$(STAGING) install

$(UTELNETD)-install: $(INSTALL)/bin/utelnetd

$(UTELNETD)-build: $(BDIR)/utelnetd
