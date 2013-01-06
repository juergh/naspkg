PKGS = $(shell ls -d */ | tr -d '/')

all: TARGET=all
all: pkgs

clean: TARGET=clean
clean: pkgs

deepclean: TARGET=deepclean
deepclean: pkgs

install: TARGET=install
install: pkgs

pkgs:
	for pkg in $(PKGS) ; do \
		$(MAKE) -C $$pkg $(TARGET) ; \
	done

$(PKGS):
	$(MAKE) -C $@

.PHONY: $(PKGS)