#----- Makefile --------------------------------------------------------------------------------
#
# Makefile,v 1.3 2004/04/02 15:17:01 lefebvre Exp
#
# This source code copyright (c) Hexago Inc. 2002-2004.
#
# This program is free software; you can redistribute it and/or modify it 
# under the terms of the GNU General Public License (GPL) Version 2, 
# June 1991 as published by the Free  Software Foundation.
#
# This program is distributed in the hope that it will be useful, 
# but WITHOUT ANY WARRANTY;  without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program; see the file GPL_LICENSE.txt. If not, write 
# to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
# MA 02111-1307 USA
#

include ../../Mk/mk-$(target).mk

OBJDIR=../../objs
OBJ=$(OBJDIR)/tsp_local.o 
OBJLINK=$(OBJDIR)/*.o
BIN=../../bin
TSPC=tspc

CFLAGS=-lsocket -lnsl -g -Wall -I../../include -I../../platform/$(target)
CC=gcc

all: $(OBJ) $(OBJLINK) $(BIN)/$(TSPC)

$(OBJDIR)/tsp_local.o:tsp_local.c
	$(CC) $(CFLAGS) -c tsp_local.c -o $(OBJDIR)/tsp_local.o $(DEFINES)
$(OBJDIR)/tsp_tun.o:tsp_tun.c
	$(CC) $(CFLAGS) -c tsp_tun.c -o $(OBJDIR)/tsp_tun.o $(DEFINES)

$(BIN)/$(TSPC): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN)/$(TSPC) $(OBJLINK)

clean:
	rm -f $(OBJDIR)/*.o $(BIN)/$(TSPC)

install: all
