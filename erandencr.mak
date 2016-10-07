#  erandencr.mak - Compile erandencr.c Version 1.0.0
#  Copyright (C) 2016 aquila62 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

OBJ=erandencr.o \
	erandinit.o \
	erand.o \
	erandpwr.o \
	erandbit.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=

erandencr:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o erandencr $(LDFLAGS)

erandencr.o:			erandencr.c
		$(CC) $(CFLAGS) erandencr.c

erandinit.o:			erandinit.c
		$(CC) $(CFLAGS) erandinit.c

erand.o:			erand.c
		$(CC) $(CFLAGS) erand.c

erandpwr.o:			erandpwr.c
		$(CC) $(CFLAGS) erandpwr.c

erandbit.o:			erandbit.c
		$(CC) $(CFLAGS) erandbit.c

clean:
		rm -f $(OBJ) erandencr
