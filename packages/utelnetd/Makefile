include naspkg/info
include ../../build/make.rules

SRC = utelnetd-0.1.9

$(STAGING)/bin/utelnetd:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(SRC)/utelnetd $(STAGING)/bin

$(SRC)/utelnetd:
	$(MAKE) -C $(SRC)

$(NAME)-install: $(STAGING)/bin/utelnetd

$(NAME)-source: $(SRC)/utelnetd

$(NAME)-clean:
	@make -C $(SRC) clean
