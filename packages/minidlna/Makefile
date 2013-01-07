MINIDLNA := minidlna-1.0.25

SRC := $(MINIDLNA)

include ../../build/make.rules

BDIR := $(BUILD)/$(MINIDLNA)

CFLAGS := -Wall -s -Os -mtune=arm9e -march=armv5te \
	-I. \
	-I$(STAGING)/usr/include \
	-I$(STAGING)/usr/include/libavcodec \
	-I$(STAGING)/usr/include/libavformat \
	-I$(STAGING)/usr/include/libavutil

LDFLAGS := -L$(STAGING)/usr/lib

$(INSTALL)/bin/minidlna:
	install -d -m0755 $(INSTALL)/bin
	install -m0755 $(STAGING)/usr/sbin/minidlna $(INSTALL)/bin

$(BDIR)/minidlna:
	$(MAKE) -C $(BDIR) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"
	$(MAKE) -C $(BDIR) DESTDIR=$(STAGING) install

$(MINIDLNA)-install: $(INSTALL)/bin/minidlna
$(MINIDLNA)-build: $(BDIR)/minidlna
