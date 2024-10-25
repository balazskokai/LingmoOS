################################################################################
#
# mediastreamer
#
################################################################################

MEDIASTREAMER_VERSION = 4.4.8
MEDIASTREAMER_SITE = \
	https://gitlab.linphone.org/BC/public/mediastreamer2/-/archive/$(MEDIASTREAMER_VERSION)
MEDIASTREAMER_LICENSE = GPL-3.0+
MEDIASTREAMER_LICENSE_FILES = LICENSE.txt
MEDIASTREAMER_INSTALL_STAGING = YES
MEDIASTREAMER_DEPENDENCIES = ortp
MEDIASTREAMER_CONF_OPTS = \
	-DENABLE_DOC=OFF \
	-DENABLE_GL=OFF \
	-DENABLE_GLX=OFF \
	-DENABLE_MKV=OFF \
	-DENABLE_SOUND=OFF \
	-DENABLE_STRICT=OFF \
	-DENABLE_TOOLS=OFF \
	-DENABLE_UNIT_TESTS=OFF \
	-DENABLE_ZRTP=OFF

ifeq ($(LINGMO_PACKAGE_ALSA_LIB),y)
MEDIASTREAMER_CONF_OPTS += \
	-DENABLE_ALSA=ON \
	-DENABLE_SOUND=ON
MEDIASTREAMER_DEPENDENCIES += alsa-lib
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_ALSA=OFF
endif

ifeq ($(LINGMO_PACKAGE_BCG729),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_G729=ON
MEDIASTREAMER_DEPENDENCIES += bcg729
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_G729=OFF
endif

ifeq ($(LINGMO_PACKAGE_JPEG_TURBO),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_JPEG=ON
MEDIASTREAMER_DEPENDENCIES += jpeg
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_JPEG=OFF
endif

ifeq ($(LINGMO_PACKAGE_LIBGSM),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_GSM=ON
MEDIASTREAMER_DEPENDENCIES += libgsm
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_GSM=OFF
endif

ifeq ($(LINGMO_PACKAGE_LIBPCAP),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_PCAP=ON
MEDIASTREAMER_DEPENDENCIES += libpcap
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_PCAP=OFF
endif

ifeq ($(LINGMO_PACKAGE_LIBSRTP),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_SRTP=ON
MEDIASTREAMER_DEPENDENCIES += libsrtp
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_SRTP=OFF
endif

ifeq ($(LINGMO_PACKAGE_LIBVPX),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_VPX=ON
MEDIASTREAMER_DEPENDENCIES += libvpx
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_VPX=OFF
endif

ifeq ($(LINGMO_PACKAGE_OPUS),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_OPUS=ON
MEDIASTREAMER_DEPENDENCIES += opus
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_OPUS=OFF
endif

# portaudio backend needs speexdsp as well
ifeq ($(LINGMO_PACKAGE_PORTAUDIO)$(LINGMO_PACKAGE_SPEEXDSP),yy)
MEDIASTREAMER_CONF_OPTS += \
	-DENABLE_PORTAUDIO=ON \
	-DENABLE_SOUND=ON
MEDIASTREAMER_DEPENDENCIES += portaudio
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_PORTAUDIO=OFF
endif

ifeq ($(LINGMO_PACKAGE_PULSEAUDIO),y)
MEDIASTREAMER_CONF_OPTS += \
	-DENABLE_PULSEAUDIO=ON \
	-DENABLE_SOUND=ON
MEDIASTREAMER_DEPENDENCIES += pulseaudio
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_PULSEAUDIO=OFF
endif

ifeq ($(LINGMO_PACKAGE_SPEEX),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_SPEEX_CODEC=ON
MEDIASTREAMER_DEPENDENCIES += speex
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_SPEEX_CODEC=OFF
endif

ifeq ($(LINGMO_PACKAGE_SPEEXDSP),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_SPEEX_DSP=ON
MEDIASTREAMER_DEPENDENCIES += speexdsp
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_SPEEX_DSP=OFF
endif

ifeq ($(LINGMO_PACKAGE_SPEEX)$(LINGMO_PACKAGE_SPEEXDSP),yy)
MEDIASTREAMER_CONF_OPTS += -DENABLE_RESAMPLE=ON
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_RESAMPLE=OFF
endif

ifeq ($(LINGMO_PACKAGE_FFMPEG_SWSCALE),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_FFMPEG=ON
MEDIASTREAMER_DEPENDENCIES += ffmpeg
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_FFMPEG=OFF
endif

ifeq ($(LINGMO_PACKAGE_SDL),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_SDL=ON
MEDIASTREAMER_DEPENDENCIES += sdl
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_SDL=OFF
endif

ifeq ($(LINGMO_PACKAGE_XLIB_LIBX11),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_X11=ON
MEDIASTREAMER_DEPENDENCIES += xlib_libX11
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_X11=OFF
endif

ifeq ($(LINGMO_PACKAGE_XLIB_LIBXV),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_XV=ON
MEDIASTREAMER_DEPENDENCIES += xlib_libXv
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_XV=OFF
endif

ifeq ($(LINGMO_PACKAGE_LIBTHEORA),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_THEORA=ON
MEDIASTREAMER_DEPENDENCIES += libtheora
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_THEORA=OFF
endif

ifeq ($(LINGMO_PACKAGE_LIBV4L),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_V4L=ON
MEDIASTREAMER_DEPENDENCIES += libv4l
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_V4L=OFF
endif

ifeq ($(LINGMO_PACKAGE_ZXING_CPP),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_QRCODE=ON
MEDIASTREAMER_DEPENDENCIES += zxing-cpp
else
MEDIASTREAMER_CONF_OPTS += -DENABLE_QRCODE=OFF
endif

ifeq ($(LINGMO_STATIC_LIBS),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_SHARED=OFF -DENABLE_STATIC=ON
else ifeq ($(LINGMO_SHARED_STATIC_LIBS),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_SHARED=ON -DENABLE_STATIC=ON
else ifeq ($(LINGMO_SHARED_LIBS),y)
MEDIASTREAMER_CONF_OPTS += -DENABLE_SHARED=ON -DENABLE_STATIC=OFF
endif

$(eval $(cmake-package))
