/* erandinit.c - Extended erand initialization Version 1.0.0          */
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

/* This is the initialization routine for extended erand     */
/* This initialization routine is based on date/time/ticks   */
/* The caller is welcome to override the following:          */
/* the state array                                           */
/* the two previous outputs                                  */
/* the current output                                        */
/* the three states for the erand algorithm                  */
/*                                                           */
/* The period length of erand is estimated to be             */
/* 5.41e+2639.                                               */
/* The period length of GSL taus2 is 3.09e+26.               */
/* The speed of erand is 1/3 faster than the GSL version     */
/* of taus2.                                                 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include "erand.h"

/* size of the state array is 2^10 */
#define STATES 1024

erfmt *erandinit(void)
   {
   int i;                      /* loop counter */
   unsigned int dttk;          /* combined date, time, and #ticks */
   unsigned int *stp,*stq;     /* pointer into state array */
   time_t now;                 /* current date and time */
   clock_t clk;                /* current number of ticks */
   struct tms t;               /* structure used by times() */
   erfmt *er;                  /* erand structure */

   /***************************************************/
   /* allocate memory for erand structure             */
   /***************************************************/
   er = (erfmt *) malloc(sizeof(erfmt));
   if (er == NULL)
      {
      fprintf(stderr,"erandinit: out of memory "
      "allocating erand structure er\n");
      exit(1);
      } /* out of memory */
   er->states = STATES; /* save the number of erand states */

   /***************************************************/
   /* allocate memory for erand state array           */
   /***************************************************/
   er->state = (unsigned int *)
      malloc(sizeof(unsigned int) * STATES);
   if (er->state == NULL)
      {
      fprintf(stderr,"erandinit: out of memory "
      "allocating er->state state array\n");
      exit(1);
      } /* out of memory */

   /***************************************************/
   /* Randomize the seeds and states                  */
   /***************************************************/
   /* get clock ticks since boot                           */
   clk = times(&t);
   /* get date & time                                      */
   time(&now);
   /* combine date, time, and ticks into a single UINT     */
   dttk = (unsigned int) (now ^ clk) | 1;
   /* initialize the erand state to date,time,ticks        */
   /* the initial seed must be an odd number               */
   er->x = dttk;      /* initialize x to combined dttk     */
   er->a = AYY;
   er->c = CEE;

   /***************************************************/
   /* Warm up the erand state.                        */
   /* This loop truncates er->x to 31 bits            */
   /***************************************************/
   i = 128;
   while (i--) RAND;

   /***************************************************/
   /* initialize out, prev, and prev prev             */
   /* to random values                                */
   /***************************************************/
   RAND;
   er->out   = er->x;           /* set to random 31-bit UINT */
   RAND;
   er->prev  = er->x;           /* set to random 31-bit UINT */
   RAND;
   er->pprev = er->x;           /* set to random 31-bit UINT */

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) er->state;
   stq = (unsigned int *) er->state + STATES;
   while (stp < stq)
      {
      RAND;
      *stp++ = er->x;           /* set to random 31-bit UINT */
      } /* for each member in er->state array */

   /***************************************************/
   /* Warm up the erand state table.                  */
   /***************************************************/
   i = 128;
   while (i--) erand(er);

   /***************************************************/
   /* after this subroutine you may initialize the    */
   /* state array to your own values, if you wish     */
   /* to do regression testing.                       */
   /* Use the above 9 instructions as an example of   */
   /* how to initialize the generator                 */
   /***************************************************/
   /* return the erand structure                      */
   /***************************************************/
   return(er);
   } /* erandinit subroutine */
