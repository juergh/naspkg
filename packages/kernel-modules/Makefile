SRC = linux-2.6.12.6-arm1

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

menuconfig:
	cd $(BUILD) && $(MAKE) ARCH=arm menuconfig
	cp $(BUILD)/.config config

$(STAGING)/kernel/sound/core/oss/snd-mixer-oss.ko:
	for mod in $(MODULES) ; do \
		dir=$$(dirname $$mod) ; \
		install -d -m0755 $(STAGING)/kernel/$$dir ; \
		install -m0644 $(BUILD)/$$mod $(STAGING)/kernel/$$dir ; \
	done

$(BUILD)/sound/core/oss/snd-mixer-oss.ko:
	cp -f config $(BUILD)/.config
	cd $(BUILD) && $(MAKE) ARCH=arm CROSS_COMPILE=arm-linux-uclibc- modules

$(NAME)-install: $(STAGING)/kernel/sound/core/oss/snd-mixer-oss.ko

$(NAME)-source: $(BUILD)/sound/core/oss/snd-mixer-oss.ko

$(NAME)-clean:
