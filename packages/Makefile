PKGS = $(shell ls -d */ | tr -d '/')

TARGETS = all clean install

all: TARGET=all
all: pkgs

clean: TARGET=clean
clean: pkgs
	-rm *~

install: TARGET=install
install: pkgs

pkgs:
	for pkg in $(PKGS) ; do \
		$(MAKE) -C $$pkg $(TARGET) ; \
	done

.PHONY: $(PKGS)