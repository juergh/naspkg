include naspkg/info

SRC = dropbear-0.53.1

all: $(NAME)

include ../../build/make.build

$(NAME): $(SRC) _builddir
	install -d -m0755 $(BUILDDIR)/bin
	install -m0755 $(SRC)/dropbear $(BUILDDIR)/bin
	install -m0755 $(SRC)/dropbearkey $(BUILDDIR)/bin
	install -m0755 $(SRC)/scp $(BUILDDIR)/bin
	$(MAKE) _package

$(SRC):
	cd $(SRC) && ./configure --host=i686-pc-linux-gnu --disable-syslog \
		--disable-lastlog --disable-wtmp --disable-wtmpx
	$(MAKE) -C $(SRC)
	$(MAKE) -C $(SRC) scp

clean: _clean

install: _install
