SRC = utelnetd-0.1.9

include ../../build/make.rules

$(STAGING)/bin/utelnetd:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(BUILD)/utelnetd $(STAGING)/bin

$(BUILD)/utelnetd:
	$(MAKE) -C $(BUILD)

$(NAME)-install: $(STAGING)/bin/utelnetd

$(NAME)-source: $(BUILD)/utelnetd

$(NAME)-clean:
