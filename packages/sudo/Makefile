SRC = sudo-1.6.8p12

include ../../build/make.rules

$(STAGING)/bin/sudo:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(BUILD)/sudo $(STAGING)/bin

$(BUILD)/sudo:
	cd $(BUILD) && ./configure --host=i686-pc-linux-gnu
	$(MAKE) -C $(BUILD)

$(NAME)-install: $(STAGING)/bin/sudo

$(NAME)-source: $(BUILD)/sudo

$(NAME)-clean:
