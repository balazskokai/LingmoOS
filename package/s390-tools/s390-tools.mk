################################################################################
#
# s390-tools
#
################################################################################

S390_TOOLS_VERSION = 2.30.0
S390_TOOLS_SITE = $(call github,ibm-s390-linux,s390-tools,v$(S390_TOOLS_VERSION))
S390_TOOLS_LICENSE = MIT
S390_TOOLS_LICENSE_FILES = LICENSE
S390_TOOLS_DEPENDENCIES = zlib

S390_TOOLS_MAKE_OPTS = \
	ARCH=$(LINGMO_ARCH) \
	CFLAGS="$(TARGET_CFLAGS) -D_GNU_SOURCE" \
	HAVE_CARGO=0

ifeq ($(LINGMO_PACKAGE_LIBCURL_OPENSSL),y)
S390_TOOLS_DEPENDENCIES += libcurl
S390_TOOLS_MAKE_OPTS += \
	CURL_CONFIG=$(STAGING_DIR)/usr/bin/curl-config \
	HAVE_CURL=1 \
	HAVE_LIBCURL=1
else
S390_TOOLS_MAKE_OPTS += \
	HAVE_CURL=0 \
	HAVE_LIBCURL=0
endif

ifeq ($(LINGMO_PACKAGE_JSON_C),y)
S390_TOOLS_DEPENDENCIES += json-c
S390_TOOLS_MAKE_OPTS += HAVE_JSONC=1
else
S390_TOOLS_MAKE_OPTS += HAVE_JSONC=0
endif

ifeq ($(LINGMO_PACKAGE_OPENSSL),y)
S390_TOOLS_DEPENDENCIES += openssl
S390_TOOLS_MAKE_OPTS += HAVE_OPENSSL=1
else
S390_TOOLS_MAKE_OPTS += HAVE_OPENSSL=0
endif

ifeq ($(LINGMO_PACKAGE_CRYPTSETUP),y)
S390_TOOLS_DEPENDENCIES += cryptsetup
S390_TOOLS_MAKE_OPTS += HAVE_CRYPTSETUP2=1
else
S390_TOOLS_MAKE_OPTS += HAVE_CRYPTSETUP2=0
endif

ifeq ($(LINGMO_PACKAGE_LIBGLIB2),y)
S390_TOOLS_DEPENDENCIES += libglib2
S390_TOOLS_MAKE_OPTS += HAVE_GLIB2=1
else
S390_TOOLS_MAKE_OPTS += HAVE_GLIB2=0
endif

ifeq ($(LINGMO_PACKAGE_LIBXML2),y)
S390_TOOLS_DEPENDENCIES += libxml2
S390_TOOLS_MAKE_OPTS += \
	HAVE_LIBXML2=1 \
	XML2_CONFIG=$(STAGING_DIR)/usr/bin/xml2-config
else
S390_TOOLS_MAKE_OPTS += HAVE_LIBXML2=0
endif

ifeq ($(LINGMO_PACKAGE_NCURSES),y)
S390_TOOLS_DEPENDENCIES += ncurses
S390_TOOLS_MAKE_OPTS += HAVE_NCURSES=1
else
S390_TOOLS_MAKE_OPTS += HAVE_NCURSES=0
endif

ifeq ($(LINGMO_PACKAGE_LIBPFM4),y)
S390_TOOLS_DEPENDENCIES += libpfm4
S390_TOOLS_MAKE_OPTS += HAVE_PFM=1
else
S390_TOOLS_MAKE_OPTS += HAVE_PFM=0
endif

ifeq ($(LINGMO_PACKAGE_LIBFUSE3),y)
S390_TOOLS_DEPENDENCIES += libfuse3
S390_TOOLS_MAKE_OPTS += HAVE_FUSE=1
else
S390_TOOLS_MAKE_OPTS += HAVE_FUSE=0
endif

ifeq ($(LINGMO_PACKAGE_NETSNMP),y)
S390_TOOLS_DEPENDENCIES += netsnmp
S390_TOOLS_MAKE_OPTS += \
	NET_SNMP_CONFIG=$(STAGING_DIR)/usr/bin/net-snmp-config \
	HAVE_SNMP=1
else
S390_TOOLS_MAKE_OPTS += HAVE_SNMP=0
endif

ifeq ($(LINGMO_PACKAGE_LIBLOCKFILE),y)
S390_TOOLS_DEPENDENCIES += liblockfile
S390_TOOLS_MAKE_OPTS += HAVE_LOCKFILE=1
else
S390_TOOLS_MAKE_OPTS += HAVE_LOCKFILE=0
endif

ifeq ($(LINGMO_PACKAGE_HAS_UDEV),y)
S390_TOOLS_DEPENDENCIES += udev
S390_TOOLS_MAKE_OPTS += HAVE_LIBUDEV=1
else
S390_TOOLS_MAKE_OPTS += HAVE_LIBUDEV=0
endif

define S390_TOOLS_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D) \
		$(S390_TOOLS_MAKE_OPTS)
endef

define S390_TOOLS_INSTALL_TARGET_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D) install \
		$(S390_TOOLS_MAKE_OPTS) DESTDIR="$(TARGET_DIR)"
endef

$(eval $(generic-package))
