# lpm
LPM_SITE = file://$(TOPDIR)/core
LPM_INSTALL_TARGET = yes
LPM_TARBALL = lpm.tar.xz
LPM_INSTALL_STAGING = YES
LPM_INSTALL_TARGET = YES
LPM_SOURCE = ${LPM_TARBALL}
LPM_LICENSE = GPL-2.0
LPM_CPE_ID_VENDOR = lpm
$(eval $(meson-package))
