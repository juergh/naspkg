include naspkg/info

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

all: $(NAME)

include ../../build/make.build

$(NAME): $(SRC) _builddir
	for mod in $(MODULES) ; do \
		dir=$$(dirname $$mod) ; \
		install -d -m0755 $(BUILDDIR)/modules/$$dir ; \
		install -m0644 output/$$mod $(BUILDDIR)/modules/$$dir ; \
	done
	$(MAKE) _package

$(SRC): output
	cd $(SRC) && $(MAKE) ARCH=arm CROSS_COMPILE=arm-linux-uclibc- \
		O=../output modules

output:
	mkdir output
	cp -f config output/.config

menuconfig: output
	cd $(SRC) && $(MAKE) ARCH=arm O=../output menuconfig
	cp output/.config config

clean: _clean
	test -d output && rm -rf output || true

install: _install
