/* erandbit.c - erand random bit generator Version 1.0.0             */
/* Copyright (C) 2016 aquila62 at github.com                         */

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

#include "erand.h"

int erandbit(erfmt *er)
   {
   unsigned int *p;           /* state pointer */
   unsigned int tmp;          /* used for Bays-Durham shuffle */
   /***********************************************************/
   /* back up the previous two states                         */
   /***********************************************************/
   er->ofst  = er->pprev >> 21;      /* offset into state array  */
   er->pprev = er->prev;   /* prev ==> prev prev              */
   er->prev  = er->x;      /* current ==> prev                */
   /***********************************************************/
   /* Calculate the RAND algorithm inline to save a call      */
   /* to erand()                                              */
   /***********************************************************/
   /* The RAND macro is in erand.h                            */
   /* XOR the previous two results with the current output    */
   RAND;
   /***********************************************************/
   /* Bays-Durham shuffle of state array                      */
   /* 1024! = 5.41e+2639 base 10 rounded down                 */
   /* The period length of the state array is very long       */
   /***********************************************************/
   /* point into the state array */
   p = (unsigned int *) er->state + er->ofst;
   /* swap the current output with a member in the state array */
   tmp   = *p;
   *p    = er->x;
   er->x = tmp;

   /* return high order output bit */
   er->out = (er->x ^ er->pprev ^ er->prev);
   return((er->out >> 30) & 1);
   } /* erandbit subroutine */
