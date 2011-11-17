SRC = busybox-1.00-pre1

include ../../build/make.rules

$(STAGING)/bin/busybox:
	install -d -m0755 $(STAGING)/bin
	install -m0755 $(BUILD)/busybox $(STAGING)/bin
	install -m0644 $(BUILD)/busybox.links.diff $(STAGING)/busybox.links

$(BUILD)/busybox:
	cp config $(BUILD)/.config
	$(MAKE) -C $(BUILD)
	diff $(BUILD)/busybox.links $(BUILD)/busybox.links.dns-323 | \
		awk '/^</ { print $$2 }' > $(BUILD)/busybox.links.diff

$(NAME)-install: $(STAGING)/bin/busybox

$(NAME)-source: $(BUILD)/busybox

$(NAME)-clean:
