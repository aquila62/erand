/* fcdeal.c - FreeCell deal using Microsoft rand  Version 1.0.0 */
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

/*********************************************************************/
/* This program uses Microsoft's rand() algorithm to deal            */
/* a deck of FreeCell cards.  The output should match the            */
/* same FreeCell deal that comes with the Windows version of         */
/* FreeCell.                                                         */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct fcstruct {
   unsigned int x;           /* erand state or seed */
   unsigned int a;           /* erand state or seed */
   unsigned int c;           /* erand state or seed */
   unsigned int m;           /* erand state or seed */
   unsigned int out;         /* erand output */
   } fcfmt;

#define AYY (214013)

#define CEE (2531011)

#define MAXINT (2147483648.0)

#define RAND (fc->x = (((fc->x * fc->a) + fc->c) & 0x7fffffff))

void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s seed\n", pgm);
   fprintf(stderr,"Where seed is 1 to 1000000\n");
   fprintf(stderr,"Example: %s 617\n", pgm);
   exit(1);
   } /* putstx */

int main(int argc, char **argv)
   {
   int i;
   int indx;
   int last;
   int lmt;
   unsigned int seed;
   char deck[128];
   char suit[128];
   char rank[128];
   char *p,*q;
   fcfmt *fc;
   if (argc != 2) putstx(*argv);
   seed = atoi(*(argv+1));
   if (seed < 1)
      {
      fprintf(stderr,"main: seed %s "
         "is too small\n", *(argv+1));
      putstx(*argv);
      } /* seed too small */
   if (seed > 1000000)
      {
      fprintf(stderr,"main: seed %s "
         "is too large\n", *(argv+1));
      putstx(*argv);
      } /* seed too large */
   fc = (fcfmt *) malloc(sizeof(fcfmt));
   if (fc == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating fc\n");
      exit(1);
      } /* out of memory */
   fc->x = seed;
   fc->a = AYY;
   fc->c = CEE;
   fc->m = MAXINT;
   printf("seed is %d\n", seed);
   /************************/
   p = (char *) deck;
   q = (char *) deck + 52;
   while (p < q) *p++ = '\0';
   /************************/
   p = (char *) suit;
   q = (char *) suit + 52;
   while (p < q) *p++ = '\0';
   /************************/
   p = (char *) rank;
   q = (char *) rank + 52;
   while (p < q) *p++ = '\0';
   /************************/
   i = 0;
   p = (char *) deck;
   q = (char *) deck + 52;
   while (p < q)
      {
      *p++ = i++;
      } /* for each card in deck */
   /************************/
   strcpy(rank,"AAAA222233334444555566667777");
   strcat(rank,"88889999TTTTJJJJQQQQKKKK");
   strcpy(suit,"CDHSCDHSCDHSCDHS");
   strcat(suit,"CDHSCDHSCDHSCDHS");
   strcat(suit,"CDHSCDHSCDHSCDHSCDHS");
   /***************************************************/
   /* In place shuffle of a deck of cards.            */
   /***************************************************/
   last = 51;
   lmt  = 52;
   i = 51;
   while (i--)
      {
      char tmp;
      RAND;          /* Microsoft rand() algorithm */
      /* The modulus is the number of cards remaining */
      /* in the deck */
      indx = (fc->x >> 16) % lmt;
      tmp = deck[last];
      deck[last] = deck[indx];
      deck[indx] = tmp;
      lmt--;
      last--;
      } /* for each card in deck */
   /***************************************************/
   /* print the deal with 8 columns to a row.         */
   /***************************************************/
   i = 0;
   p = (char *) deck + 51;
   q = (char *) deck;
   while (p >= q)
      {
      int indx;
      i++;
      indx = (int) *p--;
      printf("%c%c ", rank[indx], suit[indx]);
      if (i == 8)
	 {
         printf("\n");
	 i = 0;
	 } /* if end of line */
      } /* for each card in deck */
   printf("\n");
   return(0);
   } /* main */
