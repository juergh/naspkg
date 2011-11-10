include ../../build/make.rules

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

output:
	mkdir output
	cp -f config output/.config

menuconfig: output
	cd $(SRC) && $(MAKE) ARCH=arm O=../output menuconfig
	cp output/.config config

$(STAGING)/modules/sound/core/oss/snd-mixer-oss.ko:
	for mod in $(MODULES) ; do \
		dir=$$(dirname $$mod) ; \
		install -d -m0755 $(STAGING)/modules/$$dir ; \
		install -m0644 output/$$mod $(STAGING)/modules/$$dir ; \
	done

output/sound/core/oss/snd-mixer-oss.ko: output
	cd $(SRC) && $(MAKE) ARCH=arm CROSS_COMPILE=arm-linux-uclibc- \
		O=../output modules

$(NAME)-install: $(STAGING)/modules/sound/core/oss/snd-mixer-oss.ko

$(NAME)-source: output/sound/core/oss/snd-mixer-oss.ko

$(NAME)-clean:
	test -d output && rm -rf output || true
