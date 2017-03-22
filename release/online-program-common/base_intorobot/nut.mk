GCC_ARM_PATH ?= $(PROJECT_ROOT)/tools/xtensa-lx106-elf/bin/
GCC_PREFIX ?= xtensa-lx106-elf-
include common-tools.mk
include common-xtensa-lx106.mk

CFLAGS += -DINTOROBOT_ARCH_XTENSA
CFLAGS += -DPLATFORM_THREADING=0

# FLAGS For nut
CFLAGS += -I nut/inc/hal/
CFLAGS += -I nut/inc/platform/
CFLAGS += -I nut/inc/services/
CFLAGS += -I nut/inc/system/
CFLAGS += -I nut/inc/user/
CFLAGS += -I nut/inc/wiring/
CFLAGS += -I nut/inc/wiring_ex/

LDFLAGS += -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static -Wl,--gc-sections -Wl,-wrap,system_restart_local -Wl,-wrap,register_chipv6_phy

LDFLAGS += -L nut/lib -L nut/lib/esp8266
LIBS += wiring wiring_ex hal system services platform
LIBS += m gcc halhal phy pp net80211 wpa crypto main wps axtls smartconfig airkiss mesh wpa2 lwip_gcc stdc++
LDFLAGS += -Wl,--start-group $(patsubst %,-l%,$(LIBS)) -Wl,--end-group

STARTUP_OBJFILE +=

LDFLAGS += -L nut/linker/
LDFLAGS += -Tlinker_nut_app.ld

USE_PRINTF_FLOAT ?= y
ifeq ("$(USE_PRINTF_FLOAT)","y")
LDFLAGS += -u _printf_float
endif
