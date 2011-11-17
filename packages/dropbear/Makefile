SRC = dropbear-0.53.1

include ../../build/make.rules

$(STAGING)/bin/dropbear:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(BUILD)/dropbear $(STAGING)/bin
	install -m0755 $(BUILD)/dropbearkey $(STAGING)/bin
	install -m0755 $(BUILD)/scp $(STAGING)/bin

$(BUILD)/dropbear:
	cd $(BUILD) && ./configure --host=i686-pc-linux-gnu --disable-syslog \
		--disable-lastlog --disable-wtmp --disable-wtmpx
	$(MAKE) -C $(BUILD)
	$(MAKE) -C $(BUILD) scp

$(NAME)-install: $(STAGING)/bin/dropbear

$(NAME)-source: $(BUILD)/dropbear

$(NAME)-clean:

