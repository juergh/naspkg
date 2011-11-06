include naspkg/info

SRC = utelnetd-0.1.9

all: $(NAME)

include ../../build/make.build

$(NAME): $(SRC) _builddir
	install -d -m0755 $(BUILDDIR)/bin
	install -m0755 $(SRC)/utelnetd $(BUILDDIR)/bin
	$(MAKE) _package

$(SRC):
	$(MAKE) -C $(SRC)

clean: _clean

install: _install
