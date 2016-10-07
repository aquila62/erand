/* erand.h - erand random number generator header file Version 1.0.0 */
/* Copyright (C) 2016 aquila62 at github.com */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

/* The subroutines below are called billions of times     */
/* in a single run.                                       */
/* Parameters to the subroutines must be validated by     */
/* the calling program, to maximize efficiency            */
/* and minimize redundant editing.                        */

typedef struct erandstruct {
   int states;               /* number of states = 1024 */
   unsigned int x;           /* erand state or seed */
   unsigned int a;           /* erand state or seed */
   unsigned int c;           /* erand state or seed */
   unsigned int m;           /* erand state or seed */
   unsigned int ofst;        /* offset into state array */
   unsigned int out;         /* erand output */
   unsigned int prev;        /* prev output state */
   unsigned int pprev;       /* prev prev output state */
   unsigned int *state;      /* state array of 1024 members */
   } erfmt;

#define AYY (214013)

#define CEE (2531011)

#define RAND (er->x = (((er->x * er->a) + er->c) & 0x7fffffff))

#define MAXINTGR 2147483648.0

erfmt *erandinit(void);                 /* initialization routine */
/* the output from erand is 31 bits */
unsigned int erand(erfmt *er);          /* random uint generator */
int erandbit(erfmt *er);                /* random bit generator */
double erandunif(erfmt *er);            /* random uniform number 0-1 */
/* The limit in erandint is 2 - 32767 inclusive */
int erandint(erfmt *er, int limit);     /* random integer 0 up to limit */
unsigned int erandpwr(erfmt *er, int bits); /* random # 1-32 bits */
