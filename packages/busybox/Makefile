include ../../build/make.rules

SRC = busybox-1.00-pre1

$(STAGING)/bin/busybox:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(SRC)/busybox $(STAGING)/bin
	install -m0644 $(SRC)/busybox.links.diff $(STAGING)/busybox.links

$(SRC)/busybox:
	cp $(SRC)/.config.naspkg $(SRC)/.config
	$(MAKE) -C $(SRC)
	diff $(SRC)/busybox.links $(SRC)/busybox.links.dns-323 | \
		awk '/^</ { print $$2 }' > $(SRC)/busybox.links.diff

$(NAME)-install: $(STAGING)/bin/busybox

$(NAME)-source: $(SRC)/busybox

$(NAME)-clean:
	@make -C $(SRC) distclean
	@test -e $(SRC)/busybox.links.diff && \
		rm -f $(SRC)/busybox.links.diff || true
