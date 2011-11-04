include naspkg/info

SRC = busybox-1.00-pre1

all: $(NAME)

include ../../build/make.build

$(NAME): $(SRC) links _builddir
	install -m0755 $(SRC)/busybox $(BUILDDIR)/bin
	install -m0644 $(SRC)/busybox.links.diff $(BUILDDIR)/busybox.links
	$(MAKE) _package

$(SRC):
	cp $(SRC)/.config.naspkg $(SRC)/.config
	$(MAKE) -C $(SRC)

links:
	diff $(SRC)/busybox.links $(SRC)/busybox.links.dns-323 | \
		awk '/^</ { print $$2 }' > $(SRC)/busybox.links.diff

clean: _clean

install: _install
