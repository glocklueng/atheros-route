#
# Makefile for Atheros tools.
#

ifeq ($(obj),)
obj := .
endif

DEPTH := ../../..

ifeq ($(BINDIR),)
BINDIR=/usr/local/bin
endif

include $(obj)/${DEPTH}/os/linux/Makefile.inc

ALL=  80211stats athstats athstatsclr athkey athchans athctrl athdebug wlanconfig \
      athcwm athampdutrc atrc pktlogconf pktlogdump

ATH_TOOLS= 80211stats athstats athstatsclr pktlogconf pktlogdump

ifeq ($(DEBUG_TOOLS), 1)
ATH_TOOLS += dumpregs reg
endif

ifneq ($(strip ${ATH_SUPPORT_IBSS_PRIVATE_SECURITY}),0)
ALL += athadhoc
ATH_TOOLS += athadhoc
endif

ifneq ($(BOARD_TYPE),ap91-2MB)
ifneq ($(strip ${ATH_SUPPORT_DFS}),0)
#ifneq ($(ATH_SUPPORT_HTC),1)
ALL+= radartool
ATH_TOOLS+= radartool
#endif
endif

ifneq ($(strip ${ATH_SUPPORT_AOW}),0)
ALL+= athplay
ATH_TOOLS+= athplay
endif

ifneq ($(strip ${ATH_SUPPORT_AOW}),0)
ALL+= mplay
ATH_TOOLS+= mplay
ALL+= aowstatlog
ATH_TOOLS+= aowstatlog
endif

ifneq ($(strip ${ATH_SUPPORT_SPECTRAL}),0)
ALL+= spectraltool 
ATH_TOOLS+= spectraltool
endif

ifneq ($(strip ${UMAC_SUPPORT_RPTPLACEMENT}),0)
ALL+= rpttool 
ATH_TOOLS+= rpttool
ifeq ($(KERNELVER),2.6.31)
IWDIR=$(TOPDIR)/apps/wireless_tools.29
else 
IWDIR=$(TOPDIR)/apps/wireless_tools.28
endif
endif

ifeq ($(ATH_SUPPORT_TX99),1)
ALL+= tx99tool
ATH_TOOLS+= tx99tool
INCS += -I$(TX99)
endif
endif

all:	${ALL}

ifdef ATHEROSPATH
INCS+= -I$(ATHEROSPATH)
endif
INCS+= -I${HAL} -I${HAL}/${OS} -I${ATH_HAL} -I${obj}/${DEPTH} -I${COMMON} -I${ATH_RATE} -I${ATH} -I${WLAN} 
CFLAGS=	${INCS} ${COPTS}

ifeq (${BUILD_STATIC}, y)
LDFLAGS= -static
endif

ifeq (${BUILD_DEBUG}, y)
CFLAGS += -g
endif

ifeq ($(ATH_CONFIG_NVRAM), 1)
CFLAGS += -DCONFIG_NVRAM=1
endif

ifneq ($(ATH_CARR_DIR), )
ifndef __EXPORTED_HEADERS__
CFLAGS += -D__EXPORTED_HEADERS__
endif
CFLAGS += -DCONFIG_LOCALPC=1 -DCONFIG_DATA_AT_ROOT=1
endif

ifeq ($(BUILD_OPTIMIZED),y)
ifeq ($(KERNELARCH),mips)
CFLAGS += -Os -pipe -mips32r2 -mtune=mips32r2 -funit-at-a-time
else
CFLAGS += -Os -pipe -funit-at-a-time
endif
endif

ifndef BUILD_HOSTAPD_071
export BUILD_HOSTAPD_071=0
endif

ifneq ($(strip ${BUILD_HOSTAPD_071}),0)
COPTS+= -DCFG_HOSTAPD_071=1
endif

ifndef BUILD_HOSTAPD_072
export BUILD_HOSTAPD_072=0
endif

ifneq ($(strip ${BUILD_HOSTAPD_072}),0)
COPTS+= -DCFG_HOSTAPD_072=1
endif

all:	${ALL}

ath_tools: ${ATH_TOOLS}
ifneq ($(BOARD_TYPE),ap91-2MB)
	cp athstats $(INSTALL_ROOT)/sbin;\
	cp 80211stats $(INSTALL_ROOT)/sbin;\
	cp athstatsclr $(INSTALL_ROOT)/sbin;\
	cp pktlogconf $(INSTALL_ROOT)/sbin;
ifneq ($(strip ${ATH_SUPPORT_DFS}),0)
	cp radartool $(INSTALL_ROOT)/sbin;
endif
ifneq ($(strip ${ATH_SUPPORT_SPECTRAL}),0)
	cp spectraltool $(INSTALL_ROOT)/sbin;
endif
	cp pktlogdump $(INSTALL_ROOT)/sbin;
ifneq ($(strip ${ATH_SUPPORT_IBSS_PRIVATE_SECURITY}),0)	
	cp athadhoc $(INSTALL_ROOT)/sbin;
endif	
ifneq ($(strip ${ATH_SUPPORT_AOW}),0)
	cp mplay $(INSTALL_ROOT)/sbin;
	cp aowstatlog $(INSTALL_ROOT)/sbin;
endif    
ifneq ($(strip ${UMAC_SUPPORT_RPTPLACEMENT}),0)
	cp rpttool $(INSTALL_ROOT)/sbin;
endif
ifeq ($(ATH_SUPPORT_TX99),1)
	cp tx99tool $(INSTALL_ROOT)/sbin;
endif
else
	@echo Athtools done....
endif
ifeq ($(DEBUG_TOOLS), 1)
	cp dumpregs $(INSTALL_ROOT)/sbin;
	cp reg $(INSTALL_ROOT)/sbin;
endif

#- athampdutrc athcwm atrc pktlogconf pktlogdump radartool

dumpregs: hal_diag/dumpregs.o hal_diag/dumpregs_5212.o hal_diag/dumpregs_5416.o hal_diag/dumpregs_9300.o
	${CC} -o dumpregs ${CFLAGS} ${LDFLAGS} hal_diag/dumpregs.o \
		hal_diag/dumpregs_5212.o hal_diag/dumpregs_5416.o hal_diag/dumpregs_9300.o

reg: hal_diag/reg.c
	${CC} -o reg ${CFLAGS} ${LDFLAGS} hal_diag/reg.c

athstats: athstats.c
	${CC} -o athstats ${CFLAGS} -I../ath ${LDFLAGS} athstats.c

athstatsclr: athstatsclr.c
	${CC} -o athstatsclr ${CFLAGS} -I../ath ${LDFLAGS} athstatsclr.c

athctrl: athctrl.c
	${CC} -o athctrl ${CFLAGS} ${LDFLAGS} athctrl.c

athampdutrc: athampdutrc.c
	${CC} -o athampdutrc ${CFLAGS} -I../ath ${LDFLAGS} athampdutrc.c

80211stats: 80211stats.c
	${CC} -o 80211stats ${CFLAGS} ${LDFLAGS} 80211stats.c
athkey: athkey.c
	${CC} -o athkey ${CFLAGS} ${LDFLAGS} athkey.c

ifeq ($(ATH_SINGLE_CFG),1)

CFLAGS += -DATH_SINGLE_CFG=1 -DKERNELVER='"$(KERNELVER)"'

ifeq ($(KERNELVER),2.6.31)
IWDIR=$(TOPDIR)/apps/wireless_tools.29
else
IWDIR=$(TOPDIR)/apps/wireless_tools.28
endif
cgiMain: cgiMain.c wlancfg.c
	${CC} -o cgiMain ${CFLAGS} ${LDFLAGS} cgiMain.c wlancfg.c $(IWDIR)/iwlib.c -I $(IWDIR) -lm
	cp cgiMain $(INSTALL_ROOT)/usr/www/cgi-bin
else	
cgiMain: cgiMain.c
	${CC} -o cgiMain ${CFLAGS} ${LDFLAGS} cgiMain.c
	cp cgiMain $(INSTALL_ROOT)/usr/www/cgi-bin
endif

##add for upload
upload.cgi: upload.cgi.c
	${CC} -o upload.cgi ${CFLAGS} ${LDFLAGS} upload.cgi.c
	cp upload.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o download.cgi ${CFLAGS} ${LDFLAGS} download.cgi.c
	cp download.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o cfgupload.cgi ${CFLAGS} ${LDFLAGS} cfgupload.cgi.c
	cp cfgupload.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o search.cgi ${CFLAGS} ${LDFLAGS} search.cgi.c
	cp search.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o wan_check.cgi ${CFLAGS} ${LDFLAGS} wan_check.cgi.c
	cp wan_check.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o log_download.cgi ${CFLAGS} ${LDFLAGS} log_download.cgi.c
	cp log_download.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o network_diagnostics.cgi ${CFLAGS} ${LDFLAGS} network_diagnostics.cgi.c
	cp network_diagnostics.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o tcpdump.cgi ${CFLAGS} ${LDFLAGS} tcpdump.cgi.c
	cp tcpdump.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o tcp_download.cgi ${CFLAGS} ${LDFLAGS} tcp_download.cgi.c
	cp tcp_download.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o reboot.cgi ${CFLAGS} ${LDFLAGS} reboot.cgi.c
	cp reboot.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o upgrade.cgi ${CFLAGS} ${LDFLAGS} upgrade.cgi.c
	cp upgrade.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o ota.cgi ${CFLAGS} ${LDFLAGS} ota.cgi.c
	cp ota.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o ping.cgi ${CFLAGS} ${LDFLAGS} ping.cgi.c
	cp ping.cgi $(INSTALL_ROOT)/usr/www/cgi-bin

	${CC} -o localinfo.cgi ${CFLAGS} ${LDFLAGS} localinfo.cgi.c
	cp localinfo.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o logconsle.cgi ${CFLAGS} ${LDFLAGS} logconsle.cgi.c
	cp logconsle.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o log_down.cgi ${CFLAGS} ${LDFLAGS} log_down.cgi.c
	cp log_down.cgi $(INSTALL_ROOT)/usr/www/cgi-bin
	${CC} -o log_play.cgi ${CFLAGS} ${LDFLAGS} log_play.cgi.c
	cp log_play.cgi $(INSTALL_ROOT)/usr/www/cgi-bin

athdebug: athdebug.c
	${CC} -o athdebug ${CFLAGS} ${LDFLAGS} athdebug.c
wlanconfig: wlanconfig.c
	${CC} -o wlanconfig ${CFLAGS} ${LDFLAGS} wlanconfig.c
80211debug: 80211debug.c
	${CC} -o 80211debug ${CFLAGS} ${LDFLAGS} 80211debug.c
athcwm: athcwm.c
	${CC} -o athcwm ${CFLAGS} -I../ath ${LDFLAGS} athcwm.c
atrc: atrc.c
	${CC} -o atrc ${CFLAGS} -I../atrc ${LDFLAGS} atrc.c
pktlogdump: pktlogdump.c
	${CC} -o pktlogdump ${CFLAGS} -I$(COMMON)/ath_pktlog ${LDFLAGS} pktlogdump.c -lm
athadhoc: athadhoc.c
	${CC} -o athadhoc ${CFLAGS} -I$(COMMON)/athadhoc ${LDFLAGS} athadhoc.c -lm	
pktlogconf: pktlogconf.c
	${CC} -o pktlogconf ${CFLAGS} -I$(COMMON)/ath_pktlog ${LDFLAGS} pktlogconf.c
radartool: radartool.c
	${CC} -o radartool ${CFLAGS} -I$(COMMON)/dfs -I../ath ${LDFLAGS} radartool.c
spectraltool: spectraltool.c
	${CC} -o spectraltool ${CFLAGS} -I../ath -I$(COMMON)/dfs -I$(COMMON)/spectral ${LDFLAGS} spectraltool.c
mplay: mplay.c
	${CC} -o mplay ${CFLAGS} -I../ath ${LDFLAGS} mplay.c
aowstatlog: aowstatlog.c
	${CC} -o aowstatlog ${CFLAGS} -I../ath ${LDFLAGS} aowstatlog.c
rpttool: rpttool.c rptsm.c
	${CC} -o rpttool ${CFLAGS} ${LDFLAGS} rpttool.c rptsm.c $(IWDIR)/iwlib.c -I $(IWDIR) -lm
ifeq ($(ATH_SUPPORT_TX99),1)
tx99tool: tx99tool.c
	${CC} -o tx99tool ${CFLAGS} ${LDFLAGS} tx99tool.c
endif
install: ${ALL}
	cp athstats ${DESTDIR}${BINDIR}
	cp 80211stats ${DESTDIR}${BINDIR}
	cp athstatsclr ${DESTDIR}${BINDIR}
	cp athampdutrc ${DESTDIR}${BINDIR}
	cp athcwm ${DESTDIR}${BINDIR}
	cp athdebug ${DESTDIR}${BINDIR}
	cp atrc ${DESTDIR}${BINDIR}
	cp pktlogconf ${DESTDIR}${BINDIR}
	cp pktlogdump ${DESTDIR}${BINDIR}
	-rm ${DESTDIR}/${BINDIR}/wlanstats
	ln ${DESTDIR}/${BINDIR}/80211stats ${DESTDIR}/${BINDIR}/wlanstats
	cp 80211debug ${DESTDIR}${BINDIR}
	-rm ${DESTDIR}/${BINDIR}/wlandebug
	ln ${DESTDIR}/${BINDIR}/80211debug ${DESTDIR}/${BINDIR}/wlandebug
	cp wlanconfig ${DESTDIR}${BINDIR}
	cp radartool ${DESTDIR}${BINDIR}/radartool
	cp spectraltool ${DESTDIR}${BINDIR}/spectraltool
ifneq ($(strip ${ATH_SUPPORT_AOW}),0)
	cp mplay ${DESTDIR}${BINDIR}/mplay
	cp aowstatlog ${DESTDIR}${BINDIR}/aowstatlog
endif    
	cp rpttool ${DESTDIR}${BINDIR}/rpttool 
ifeq ($(ATH_SUPPORT_TX99),1)
	cp tx99tool ${DESTDIR}${BINDIR}
endif

ath_tools_clean:
	@rm -f athstats 80211stats athstatsclr pktlogdump pktlogconf radartool spectraltool rpttool tx99tool
ifeq ($(DEBUG_TOOLS), 1)
	@rm -f dumpregs reg && rm -f hal_diag/*.o
endif

clean: ath_tools_clean
	rm -f ${ALL} core a.out *.o
