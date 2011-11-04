include naspkg/info

SRC = sudo-1.6.8p12

all: $(NAME)

include ../../build/make.build

$(NAME): $(SRC) _builddir
	install -m0755 $(SRC)/sudo $(BUILDDIR)/bin
	$(MAKE) _package

$(SRC):
	cd $(SRC) && ./configure --host=i686-pc-linux-gnu
	$(MAKE) -C $(SRC)

clean: _clean

install: _install
