################################################################################
#
# libuwsc
#
################################################################################

LIBUWSC_VERSION = 3.3.5
LIBUWSC_SITE = https://github.com/zhaojh329/libuwsc/releases/download/v$(LIBUWSC_VERSION)
LIBUWSC_LICENSE = MIT
LIBUWSC_LICENSE_FILES = LICENSE
LIBUWSC_INSTALL_STAGING = YES
LIBUWSC_DEPENDENCIES = libev

ifeq ($(LINGMO_PACKAGE_OPENSSL),y)
LIBUWSC_DEPENDENCIES += openssl
LIBUWSC_CONF_OPTS += \
	-DUWSC_SSL_SUPPORT=ON \
	-DUWSC_USE_MBEDTLS=OFF \
	-DUWSC_USE_OPENSSL=ON \
	-DUWSC_USE_WOLFSSL=OFF
else ifeq ($(LINGMO_PACKAGE_WOLFSSL_ALL),y)
LIBUWSC_DEPENDENCIES += wolfssl
LIBUWSC_CONF_OPTS += \
	-DUWSC_SSL_SUPPORT=ON \
	-DUWSC_USE_MBEDTLS=OFF \
	-DUWSC_USE_OPENSSL=OFF \
	-DUWSC_USE_WOLFSSL=ON
else ifeq ($(LINGMO_PACKAGE_MBEDTLS),y)
LIBUWSC_DEPENDENCIES += mbedtls
LIBUWSC_CONF_OPTS += \
	-DUWSC_SSL_SUPPORT=ON \
	-DUWSC_USE_MBEDTLS=ON \
	-DUWSC_USE_OPENSSL=OFF \
	-DUWSC_USE_WOLFSSL=OFF
else
LIBUWSC_CONF_OPTS += -DUWSC_SSL_SUPPORT=OFF
endif

ifeq ($(LINGMO_PACKAGE_LUA):$(LINGMO_STATIC_LIBS),y:)
LIBUWSC_DEPENDENCIES += lua
LIBUWSC_CONF_OPTS += -DUWSC_LUA_SUPPORT=ON
else
LIBUWSC_CONF_OPTS += -DUWSC_LUA_SUPPORT=OFF
endif

# BUILD_SHARED_LIBS is handled in pkg-cmake.mk as it is a generic cmake variable
ifeq ($(LINGMO_SHARED_STATIC_LIBS),y)
LIBUWSC_CONF_OPTS += -DBUILD_STATIC_LIBS=ON
else ifeq ($(LINGMO_SHARED_LIBS),y)
LIBUWSC_CONF_OPTS += -DBUILD_STATIC_LIBS=OFF
endif

$(eval $(cmake-package))
