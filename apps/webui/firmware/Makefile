ifneq ($(strip $(TOOLPREFIX)),)
CROSS:=$(TOOLPREFIX)
endif

CC=$(CROSS)gcc
CFLAGS:=-Wall -Wno-unused -g -I.
RM:=rm -rf

all:clean
	$(CC) $(CFLAGS) -o firmware_check firmware_check.c
	$(CC) $(CFLAGS) -o firmware_check2 firmware_check2.c
clean:
	$(RM) firmware_check *.o

