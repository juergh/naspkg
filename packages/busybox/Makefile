BUSYBOX := busybox-1.00-pre1

SRC := $(BUSYBOX)

include ../../build/make.rules

BDIR := $(BUILD)/$(BUSYBOX)

menuconfig: $(BDIR)
	cp config $(BDIR)/.config
	cd $(BDIR) && $(MAKE) menuconfig
	cp $(BDIR)/.config config

$(INSTALL)/bin/busybox:
	install -d -m0755 $(INSTALL)/bin
	install -m0755 $(STAGING)/usr/bin/busybox $(INSTALL)/bin
	install -m0644 $(BDIR)/busybox.links.diff $(INSTALL)/busybox.links

$(BDIR)/busybox:
	cp config $(BDIR)/.config
	$(MAKE) -C $(BDIR)
	diff $(BDIR)/busybox.links $(BDIR)/busybox.links.dns-323 | \
		awk '/^</ { print $$2 }' > $(BDIR)/busybox.links.diff
	install -d -m0755 $(STAGING)/usr/bin
	install -m0755 -s --strip-program=$(STRIP) $(BDIR)/busybox \
		$(STAGING)/usr/bin

$(BUSYBOX)-install: $(INSTALL)/bin/busybox

$(BUSYBOX)-build: $(BDIR)/busybox
