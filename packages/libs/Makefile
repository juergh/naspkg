SQLITE    := sqlite-3.7.3
JPEG      := jpeg-6b1
LIBEXIF   := libexif-0.6.19
LIBID3TAG := libid3tag-0.15.1b
LIBOGG    := libogg-1.3.0
LIBVORBIS := libvorbis-1.3.3
FLAC      := flac-1.1.2
LIBAV     := libav-0.5.9

SRC := $(SQLITE) $(JPEG) $(LIBEXIF) $(LIBID3TAG) $(LIBOGG) $(LIBVORBIS) \
	$(FLAC) $(LIBAV)

include ../../build/make.rules

#
# libsqlite3
#

$(INSTALL)/lib/libsqlite3.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libsqlite3.so*) | \
		(cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(SQLITE)/.libs/libsqlite3.so:
	cd $(BUILD)/$(SQLITE) && \
		./configure --host=i686-pc-linux-gnu --prefix=/usr
	$(MAKE) -C $(BUILD)/$(SQLITE)
	$(MAKE) -C $(BUILD)/$(SQLITE) DESTDIR=$(STAGING) install

$(SQLITE)-install: $(INSTALL)/lib/libsqlite3.so
$(SQLITE)-build: $(BUILD)/$(SQLITE)/.libs/libsqlite3.so

#
# libjpeg
#

$(INSTALL)/lib/libjpeg.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libjpeg.so*) | \
		(cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(JPEG)/.libs/libjpeg.so:
	cd $(BUILD)/$(JPEG) && \
		./configure --host=i686-pc-linux-gnu --prefix=/usr
	$(MAKE) -C $(BUILD)/$(JPEG)
	$(MAKE) -C $(BUILD)/$(JPEG) DESTDIR=$(STAGING) install

$(JPEG)-install: $(INSTALL)/lib/libjpeg.so
$(JPEG)-build: $(BUILD)/$(JPEG)/.libs/libjpeg.so

#
# libexif
#

$(INSTALL)/lib/libexif.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libexif.so*) | \
		(cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(LIBEXIF)/libexif/.libs/libexif.so:
	cd $(BUILD)/$(LIBEXIF) && \
		./configure --host=i686-pc-linux-gnu --prefix=/usr
	$(MAKE) -C $(BUILD)/$(LIBEXIF)
	$(MAKE) -C $(BUILD)/$(LIBEXIF) DESTDIR=$(STAGING) install

$(LIBEXIF)-install: $(INSTALL)/lib/libexif.so
$(LIBEXIF)-build: $(BUILD)/$(LIBEXIF)/libexif/.libs/libexif.so

#
# libid3tag
#

$(INSTALL)/lib/libid3tag.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libid3tag.so*) | \
		(cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(LIBID3TAG)/.libs/libid3tag.so:
	cd $(BUILD)/$(LIBID3TAG) && \
		./configure --host=i686-pc-linux-gnu --prefix=/usr
	$(MAKE) -C $(BUILD)/$(LIBID3TAG)
	$(MAKE) -C $(BUILD)/$(LIBID3TAG) DESTDIR=$(STAGING) install

$(LIBID3TAG)-install: $(INSTALL)/lib/libid3tag.so
$(LIBID3TAG)-build: $(BUILD)/$(LIBID3TAG)/.libs/libid3tag.so

#
# libogg
#

$(INSTALL)/lib/libogg.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libogg.so*) | \
		(cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(LIBOGG)/src/.libs/libogg.so:
	cd $(BUILD)/$(LIBOGG) && \
		./configure --host=i686-pc-linux-gnu --prefix=/usr
	$(MAKE) -C $(BUILD)/$(LIBOGG)
	$(MAKE) -C $(BUILD)/$(LIBOGG) DESTDIR=$(STAGING) install

$(LIBOGG)-install: $(INSTALL)/lib/libogg.so
$(LIBOGG)-build: $(BUILD)/$(LIBOGG)/src/.libs/libogg.so

#
# libvorbis
#

$(INSTALL)/lib/libvorbis.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libvorbis.so*) | \
		(cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(LIBVORBIS)/lib/.libs/libvorbis.so:
	cd $(BUILD)/$(LIBVORBIS) && \
		CPPFLAGS=$(CPPFLAGS) \
		LDFLAGS=$(LDFLAGS) \
		PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) \
		 ./configure --host=i686-pc-linux-gnu --prefix=/usr
	$(MAKE) -C $(BUILD)/$(LIBVORBIS)
	$(MAKE) -C $(BUILD)/$(LIBVORBIS) DESTDIR=$(STAGING) install

$(LIBVORBIS)-install: $(INSTALL)/lib/libvorbis.so
$(LIBVORBIS)-build: $(BUILD)/$(LIBVORBIS)/lib/.libs/libvorbis.so

#
# libFLAC
#

$(INSTALL)/lib/libFLAC.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libFLAC.so*) | \
		(cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(FLAC)/src/libFLAC/.libs/libFLAC.so:
	cd $(BUILD)/$(FLAC) && \
		CPPFLAGS=$(CPPFLAGS) \
		LDFLAGS=$(LDFLAGS) \
		PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) \
		 ./configure --host=i686-pc-linux-gnu --prefix=/usr \
			--with-ogg-includes=$(STAGING) \
			--with-ogg-libraries=$(STAGING)
	$(MAKE) -C $(BUILD)/$(FLAC)
	$(MAKE) -C $(BUILD)/$(FLAC) DESTDIR=$(STAGING) install

$(FLAC)-install: $(INSTALL)/lib/libFLAC.so
$(FLAC)-build: $(BUILD)/$(FLAC)/src/libFLAC/.libs/libFLAC.so

#
# libav
#

$(INSTALL)/lib/libavutil.so:
	install -d -m0755 $(INSTALL)/lib
	(cd $(STAGING)/usr/lib && tar -cv libavutil.so* libavformat.so* \
		libavcodec.so*) | (cd $(INSTALL)/lib && tar -x)

$(BUILD)/$(LIBAV)/libavutil/libavutil.so:
	cd $(BUILD)/$(LIBAV) && \
		./configure --prefix=/usr --arch=armv5te \
			--cross-prefix=arm-linux-uclibc- \
			--enable-shared \
			--disable-static \
			--disable-ffmpeg \
			--disable-ffplay \
			--disable-ffserver \
			--disable-devices
	$(MAKE) -C $(BUILD)/$(LIBAV)
	$(MAKE) -C $(BUILD)/$(LIBAV) DESTDIR=$(STAGING) install

$(LIBAV)-install: $(INSTALL)/lib/libavutil.so
$(LIBAV)-build: $(BUILD)/$(LIBAV)/libavutil/libavutil.so
