#!/usr/bin/make

# erandpat.mak - Compile Program erandpat.c
# Version 0.1.0
# Copyright (C) 2016   aquila62 at github.com

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to:

# 	Free Software Foundation, Inc.
# 	59 Temple Place - Suite 330
# 	Boston, MA  02111-1307, USA.

# Commands when running erandpat:
# r = reset
# q = quit

OBJ=erandpat.o \
	erandinit.o \
	erand.o \
	erandint.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lncurses -lgsl -lgslcblas -lm

erandpat:		$(OBJ)
	$(CC) -Wall -O2 $(OBJ) -o erandpat $(LDFLAGS)

erandpat.o:		erandpat.c
	$(CC) $(CFLAGS) erandpat.c

erandinit.o:		erandinit.c
	$(CC) $(CFLAGS) erandinit.c

erand.o:		erand.c
	$(CC) $(CFLAGS) erand.c

erandint.o:		erandint.c
	$(CC) $(CFLAGS) erandint.c

clean:
	rm -f $(OBJ) erandpat
