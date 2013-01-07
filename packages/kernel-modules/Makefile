KERNEL := linux-2.6.12.6-arm1

SRC := $(KERNEL)

MODULES = \
	sound/core/oss/snd-mixer-oss.ko \
	sound/core/oss/snd-pcm-oss.ko \
	sound/core/snd-page-alloc.ko \
	sound/core/snd-pcm.ko \
	sound/core/snd-rawmidi.ko \
	sound/core/snd-timer.ko \
	sound/core/snd.ko \
	sound/soundcore.ko \
	sound/usb/snd-usb-audio.ko \
	sound/usb/snd-usb-lib.ko \

include ../../build/make.rules

BDIR := $(BUILD)/$(KERNEL)

menuconfig:
	cd $(BDIR) && $(MAKE) ARCH=arm menuconfig
	cp $(BDIR)/.config config

$(INSTALL)/kernel/sound/core/oss/snd-mixer-oss.ko:
	for mod in $(MODULES) ; do \
		dir=$$(dirname $$mod) ; \
		install -d -m0755 $(INSTALL)/kernel/$$dir ; \
		install -m0644 $(BDIR)/$$mod $(INSTALL)/kernel/$$dir ; \
	done

$(BDIR)/sound/core/oss/snd-mixer-oss.ko:
	cp -f config $(BDIR)/.config
	cd $(BDIR) && $(MAKE) ARCH=arm CROSS_COMPILE=arm-linux-uclibc- modules

$(KERNEL)-install: $(INSTALL)/kernel/sound/core/oss/snd-mixer-oss.ko
$(KERNEL)-build: $(BDIR)/sound/core/oss/snd-mixer-oss.ko
