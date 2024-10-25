################################################################################
#
# open62541
#
################################################################################

OPEN62541_VERSION = v1.3.9
OPEN62541_SITE_METHOD = git
OPEN62541_SITE = https://github.com/open62541/open62541.git
OPEN62541_GIT_SUBMODULES = YES
OPEN62541_INSTALL_STAGING = YES
OPEN62541_LICENSE = MPL-2.0
OPEN62541_LICENSE_FILES = LICENSE
OPEN62541_CPE_ID_VENDOR = open62541

# Force Release build to remove -Werror.
# Don't use git describe to get the version number.
# Disable hardening options to let Buildroot handle it.
OPEN62541_CONF_OPTS = \
	-DCMAKE_BUILD_TYPE=Release \
	-DGIT_EXECUTABLE=NO \
	-DOPEN62541_VERSION=$(OPEN62541_VERSION) \
	-DUA_ENABLE_HARDENING=OFF \
	-DUA_FORCE_WERROR=OFF

ifeq ($(LINGMO_PACKAGE_OPEN62541_ENCRYPTION_MBEDTLS),y)
OPEN62541_DEPENDENCIES += mbedtls
OPEN62541_CONF_OPTS += -DUA_ENABLE_ENCRYPTION=MBEDTLS
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_ENCRYPTION_OPENSSL),y)
OPEN62541_DEPENDENCIES += openssl
OPEN62541_CONF_OPTS += -DUA_ENABLE_ENCRYPTION=OPENSSL
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_UA_NAMESPACE_ZERO_MINIMAL),y)
OPEN62541_CONF_OPTS += -DUA_NAMESPACE_ZERO=MINIMAL -DUA_ENABLE_SUBSCRIPTIONS_EVENTS=OFF
else ifeq ($(LINGMO_PACKAGE_OPEN62541_UA_NAMESPACE_ZERO_REDUCED),y)
OPEN62541_CONF_OPTS += -DUA_NAMESPACE_ZERO=REDUCED
else ifeq ($(LINGMO_PACKAGE_OPEN62541_UA_NAMESPACE_ZERO_FULL),y)
OPEN62541_CONF_OPTS += -DUA_NAMESPACE_ZERO=FULL
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_HISTORIZING),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_HISTORIZING=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_HISTORIZING=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_DISCOVERY),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_DISCOVERY=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_DISCOVERY=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_JSON_ENCODING),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_JSON_ENCODING=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_JSON_ENCODING=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_PUBSUB),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_PUBSUB_DELTAFRAMES),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_DELTAFRAMES=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_DELTAFRAMES=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_PUBSUB_INFORMATIONMODEL),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_INFORMATIONMODEL=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_INFORMATIONMODEL=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_PUBSUB_INFORMATIONMODEL_METHODS),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_INFORMATIONMODEL_METHODS=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_INFORMATIONMODEL_METHODS=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPEN62541_PUBSUB_ETH_UADP),y)
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_ETH_UADP=ON
else
OPEN62541_CONF_OPTS += -DUA_ENABLE_PUBSUB_ETH_UADP=OFF
endif

# Remove unneeded files
define OPEN62541_REMOVE_UNNEEDED_FILES
	$(RM) -r $(TARGET_DIR)/usr/share/open62541
endef

OPEN62541_POST_INSTALL_TARGET_HOOKS += OPEN62541_REMOVE_UNNEEDED_FILES

$(eval $(cmake-package))
