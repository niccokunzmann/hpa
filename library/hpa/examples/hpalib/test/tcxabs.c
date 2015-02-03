/*
   Copyright (C)  2000    Daniel A. Atkinson  <DanAtk@aol.com>
   Copyright (C)  2004    Ivano Primi  <ivprimi@libero.it>    

   This file is part of the HPA Library.

   The HPA Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The HPA Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the HPA Library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
   02110-1301 USA.
*/

/*
    Test:  cxabs  cxarg

    Uses:  cxabs  cxarg  atocx  xpr_print

    Input file:  data/cxgen.dat
*/
#include<stdio.h>
#include<stdlib.h>
#include"cxpre.h"

#define DECD 32

int
get_line (char *buffer, int size, FILE * fp)
{
  if ((fgets (buffer, size, fp)))
    {
      int i;

      for (i = 0; buffer[i] != '\0'; i++);
      if (i > 0 && buffer[i - 1] == '\n')
	buffer[--i] = '\0';
      return i;
    }
  else
    return -1;
}

typedef struct xpr (*pfun) (struct cxpr);
extern int xErrNo;

int
main (int na, char **av)
{
  struct cxpr z;
  struct xpr x;
  FILE *fp;
  char num[1024], *re, *im;
  const char *nlist[] = {
    "cxabs", "cxarg",
    NULL
  };
  pfun flist[] = {
    cxabs, cxarg
  };
  int i;

  if (na != 2)
    {
      printf ("para: input_file\n");
      exit (-1);
    }
  fp = fopen (*++av, "r");
  for (i = 0; nlist[i] != NULL; i++)
    {
      printf ("\nTest of %s\n", nlist[i]);
      while (get_line (num, 1024, fp) != -1)
	{
	  printf ("*string in : \t%s\n", num);
	  /* convert ascii string to extended precision complex */
	  z = atocx (num);
	  re = xpr_asprint (z.re, 1, 0, DECD);
	  im = xpr_asprint (z.im, 1, 0, DECD);
	  printf (" z =  \t\t%s  \t%s\n", re, im);
	  free ((void *) re);
	  free ((void *) im);
	  printf (" %s(z) = \t", nlist[i]);
	  xErrNo = 0;
	  x = (*flist[i]) (z);
	  switch (xErrNo)
	    {
	    case XENONE:
	      xpr_print (stdout, x, 1, 0, DECD);
	      putchar ('\n');
	      break;
	    case XEDIV:
	      printf ("*** Division by zero\n");
	      break;
	    case XEDOM:
	      printf ("*** Out of domain\n");
	      break;
	    case XEBADEXP:
	      printf ("*** Bad exponent\n");
	      break;
	    default:
	      printf ("*** Unknown error\n");
	    }
	}
      rewind (fp);
    }
  fclose (fp);
  return 0;
}

/*  Test output


Test of cxabs
*string in : 	0
 z =  		0.00000000000000000000000000000000e+0  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	0.00000000000000000000000000000000e+0
*string in : 	+2.3106e-1571
 z =  		2.31059999999999999999999999999571e-1571  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	2.31059999999999999999999999999571e-1571
*string in : 	+8.7792e-20  +9.7732e-20i
 z =  		8.77919999999999999999999999999979e-20  	9.77319999999999999999999999999977e-20
 cxabs(z) = 	1.31373433722347380836939312524523e-19
*string in : 	+2.3298e-1571i
 z =  		0.00000000000000000000000000000000e+0  	2.32979999999999999999999999999567e-1571
 cxabs(z) = 	2.32979999999999999999999999999567e-1571
*string in : 	-4.5592e-19  +8.2219e-18i
 z =  		-4.55919999999999999999999999999990e-19  	8.22189999999999999999999999999983e-18
 cxabs(z) = 	8.23453111333001157906312305396723e-18
*string in : 	-3.8932e-1624i
 z =  		0.00000000000000000000000000000000e+0  	-3.89319999999999999999999999999252e-1624
 cxabs(z) = 	3.89319999999999999999999999999252e-1624
*string in : 	-1.2291e-17  -7.3342e-18i
 z =  		-1.22909999999999999999999999999998e-17  	-7.33419999999999999999999999999984e-18
 cxabs(z) = 	1.43129022437799106208983746855387e-17
*string in : 	-4.0987e-1617i
 z =  		0.00000000000000000000000000000000e+0  	-4.09869999999999999999999999999216e-1617
 cxabs(z) = 	4.09869999999999999999999999999216e-1617
*string in : 	+3.9917e-19  -8.2215e-19i
 z =  		3.99169999999999999999999999999991e-19  	-8.22149999999999999999999999999982e-19
 cxabs(z) = 	9.13929598710972923044843494989334e-19
*string in : 	+1.0
 z =  		1.00000000000000000000000000000000e+0  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	+1.0000000000000000000986
 z =  		1.00000000000000000009860000000000e+0  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000009860000000000e+0
*string in : 	+1.0000000000000000004567 +2.43e-18i
 z =  		1.00000000000000000045670000000000e+0  	2.42999999999999999999999999999995e-18
 cxabs(z) = 	1.00000000000000000045670000000000e+0
*string in : 	+1.0  +3.4506e-1298i
 z =  		1.00000000000000000000000000000000e+0  	3.45059999999999999999999999999470e-1298
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	+0.999999999999999998736  +4.6677e-1297i
 z =  		9.99999999999999998735999999999976e-1  	4.66769999999999999999999999999284e-1297
 cxabs(z) = 	9.99999999999999998735999999999976e-1
*string in : 	+0.999999999999999999754
 z =  		9.99999999999999999753999999999976e-1  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	9.99999999999999999753999999999976e-1
*string in : 	+0.999999999999999999338  -5.0783e-1145i
 z =  		9.99999999999999999337999999999976e-1  	-5.07829999999999999999999999999312e-1145
 cxabs(z) = 	9.99999999999999999337999999999976e-1
*string in : 	+1.0000000000000000000    -6.7002e-1301i
 z =  		1.00000000000000000000000000000000e+0  	-6.70019999999999999999999999998969e-1301
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	+1.0000000000000007423    -5.3321e-1344i
 z =  		1.00000000000000074230000000000000e+0  	-5.33209999999999999999999999999153e-1344
 cxabs(z) = 	1.00000000000000074230000000000000e+0
*string in : 	-1.0
 z =  		-1.00000000000000000000000000000000e+0  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	-0.99999999999999999998811
 z =  		-9.99999999999999999988109999999973e-1  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	9.99999999999999999988109999999973e-1
*string in : 	-0.99999999999999999976632 +2.3344e-15i
 z =  		-9.99999999999999999766319999999974e-1  	2.33439999999999999999999999999996e-15
 cxabs(z) = 	9.99999999999999999766320000002698e-1
*string in : 	-1.0  +4.5601e-997i
 z =  		-1.00000000000000000000000000000000e+0  	4.56009999999999999999999999999462e-997
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	-1.00000000000000000000654 +7.4332e-1532i
 z =  		-1.00000000000000000000654000000000e+0  	7.43319999999999999999999999998655e-1532
 cxabs(z) = 	1.00000000000000000000654000000000e+0
*string in : 	-1.00000000000000000000743
 z =  		-1.00000000000000000000743000000000e+0  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000743000000000e+0
*string in : 	-1.00000000000000000085023 -6.9983e-18i
 z =  		-1.00000000000000000085023000000000e+0  	-6.99829999999999999999999999999985e-18
 cxabs(z) = 	1.00000000000000000085023000000000e+0
*string in : 	-1.0  -5.00098e-1023i
 z =  		-1.00000000000000000000000000000000e+0  	-5.00097999999999999999999999999395e-1023
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	-0.9999999999999999997643  -6.7321e-16i
 z =  		-9.99999999999999999764299999999974e-1  	-6.73209999999999999999999999999987e-16
 cxabs(z) = 	9.99999999999999999764300000000201e-1
*string in : 	+1.0i
 z =  		0.00000000000000000000000000000000e+0  	1.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	+5.6098e-2198 +1.0i
 z =  		5.60979999999999999999999999998542e-2198  	1.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	+4.9987e-18   +1.0000000000000000005421i
 z =  		4.99869999999999999999999999999989e-18  	1.00000000000000000054210000000000e+0
 cxabs(z) = 	1.00000000000000000054210000000000e+0
*string in : 	+1.000000000000000000003201i
 z =  		0.00000000000000000000000000000000e+0  	1.00000000000000000000320100000000e+0
 cxabs(z) = 	1.00000000000000000000320100000000e+0
*string in : 	-6.5541e-20   +1.0000000000000000080981i
 z =  		-6.55409999999999999999999999999984e-20  	1.00000000000000000809810000000000e+0
 cxabs(z) = 	1.00000000000000000809810000000000e+0
*string in : 	-7.0998e-2200 +1.0i
 z =  		-7.09979999999999999999999999998153e-2200  	1.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	-6.8432e-17   +0.9999999999999999999864i
 z =  		-6.84319999999999999999999999999986e-17  	9.99999999999999999986399999999974e-1
 cxabs(z) = 	9.99999999999999999986399999999977e-1
*string in : 	+0.99999999999999989098732i
 z =  		0.00000000000000000000000000000000e+0  	9.99999999999999890987319999999974e-1
 cxabs(z) = 	9.99999999999999890987319999999974e-1
*string in : 	+4.3329e-16   +0.9999999999999999997877i
 z =  		4.33289999999999999999999999999992e-16  	9.99999999999999999787699999999974e-1
 cxabs(z) = 	9.99999999999999999787700000000068e-1
*string in : 	-1.0i
 z =  		0.00000000000000000000000000000000e+0  	-1.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	+2.7762e-2111 -1.0i
 z =  		2.77619999999999999999999999999307e-2111  	-1.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	+3.3321e-17   -0.9999999999999999996555i
 z =  		3.33209999999999999999999999999993e-17  	-9.99999999999999999655499999999974e-1
 cxabs(z) = 	9.99999999999999999655499999999975e-1
*string in : 	-0.999999999999999999996999972013i
 z =  		0.00000000000000000000000000000000e+0  	-9.99999999999999999996999972012965e-1
 cxabs(z) = 	9.99999999999999999996999972012965e-1
*string in : 	-7.5541e-17   -0.999999999999999999987231i
 z =  		-7.55409999999999999999999999999985e-17  	-9.99999999999999999987230999999972e-1
 cxabs(z) = 	9.99999999999999999987230999999975e-1
*string in : 	-2.1156e-2203 -1.0i
 z =  		-2.11559999999999999999999999999449e-2203  	-1.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000000000000000000000000000000e+0
*string in : 	-5.9923e-16   -1.00000000000000000089321i
 z =  		-5.99229999999999999999999999999988e-16  	-1.00000000000000000089321000000000e+0
 cxabs(z) = 	1.00000000000000000089321000000018e+0
*string in : 	-1.000000000000000000007161i
 z =  		0.00000000000000000000000000000000e+0  	-1.00000000000000000000716100000000e+0
 cxabs(z) = 	1.00000000000000000000716100000000e+0
*string in : 	+8.6631e-19   -1.00000000000000000008765i
 z =  		8.66309999999999999999999999999981e-19  	-1.00000000000000000008765000000000e+0
 cxabs(z) = 	1.00000000000000000008765000000000e+0
*string in : 	+1.5876e1876
 z =  		1.58759999999999999999999999999648e+1876  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.58759999999999999999999999999648e+1876
*string in : 	-6.4391e1965
 z =  		-6.43909999999999999999999999998503e+1965  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	6.43909999999999999999999999998503e+1965
*string in : 	+3.4210e2015i
 z =  		0.00000000000000000000000000000000e+0  	3.42099999999999999999999999999185e+2015
 cxabs(z) = 	3.42099999999999999999999999999185e+2015
*string in : 	-4.5522e2011i
 z =  		0.00000000000000000000000000000000e+0  	-4.55219999999999999999999999998917e+2011
 cxabs(z) = 	4.55219999999999999999999999998917e+2011
*string in : 	+2.1907e1854  +9.8765e1872i
 z =  		2.19069999999999999999999999999520e+1854  	9.87649999999999999999999999997812e+1872
 cxabs(z) = 	9.87649999999999999999999999997812e+1872
*string in : 	-3.2966e1946  +7.5721e1834i
 z =  		-3.29659999999999999999999999999241e+1946  	7.57209999999999999999999999998357e+1834
 cxabs(z) = 	3.29659999999999999999999999999241e+1946
*string in : 	-6.0987e2310  -5.4411e2198i
 z =  		-6.09869999999999999999999999998333e+2310  	-5.44109999999999999999999999998585e+2198
 cxabs(z) = 	6.09869999999999999999999999998333e+2310
*string in : 	+7.8895e1854  -3.8699e1943i
 z =  		7.88949999999999999999999999998271e+1854  	-3.86989999999999999999999999999111e+1943
 cxabs(z) = 	3.86989999999999999999999999999111e+1943
*string in : 	+10.009876543100091234
 z =  		1.00098765431000912340000000000000e+1  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00098765431000912340000000000000e+1
*string in : 	+9.8980000000006542009 +6.11002230065009876i
 z =  		9.89800000000065420089999999999997e+0  	6.11002230065009876000000000000000e+0
 cxabs(z) = 	1.16319721678851379722038607417472e+1
*string in : 	+17.9998888123400000076i
 z =  		0.00000000000000000000000000000000e+0  	1.79998888123400000076000000000000e+1
 cxabs(z) = 	1.79998888123400000076000000000000e+1
*string in : 	-12.9822227      +20.87777220192i
 z =  		-1.29822227000000000000000000000000e+1  	2.08777722019200000000000000000000e+1
 cxabs(z) = 	2.45849441396082650373582045429663e+1
*string in : 	-17.9877771265
 z =  		-1.79877771265000000000000000000000e+1  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.79877771265000000000000000000000e+1
*string in : 	-19.09872210981  -32.9800000654i
 z =  		-1.90987221098100000000000000000000e+1  	-3.29800000653999999999999999999999e+1
 cxabs(z) = 	3.81109116991647070985013773072333e+1
*string in : 	-43.987600182345i
 z =  		0.00000000000000000000000000000000e+0  	-4.39876001823449999999999999999999e+1
 cxabs(z) = 	4.39876001823449999999999999999999e+1
*string in : 	+15.982201192361 -43.2189031229i
 z =  		1.59822011923610000000000000000000e+1  	-4.32189031228999999999999999999999e+1
 cxabs(z) = 	4.60793266237661153457951801141377e+1
*string in : 	+1000.009876543100091234
 z =  		1.00000987654310009123400000000000e+3  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.00000987654310009123400000000000e+3
*string in : 	+989.80000000006542009 +611.002230065009876i
 z =  		9.89800000000065420089999999999996e+2  	6.11002230065009875999999999999998e+2
 cxabs(z) = 	1.16319721678851379722038607417472e+3
*string in : 	+179.998888123400000076i
 z =  		0.00000000000000000000000000000000e+0  	1.79998888123400000076000000000000e+2
 cxabs(z) = 	1.79998888123400000076000000000000e+2
*string in : 	-1298.22227  +208.7777220192i
 z =  		-1.29822227000000000000000000000000e+3  	2.08777722019199999999999999999999e+2
 cxabs(z) = 	1.31490273386873724627449847917207e+3
*string in : 	-1798.777712650981
 z =  		-1.79877771265098099999999999999999e+3  	0.00000000000000000000000000000000e+0
 cxabs(z) = 	1.79877771265098099999999999999999e+3
*string in : 	-190.9872210981   -329.800700654i
 z =  		-1.90987221098100000000000000000000e+2  	-3.29800700653999999999999999999999e+2
 cxabs(z) = 	3.81109722750081318097308504558962e+2
*string in : 	+1598.2201192361  -4321.89031229i
 z =  		1.59822011923609999999999999999999e+3  	-4.32189031228999999999999999999998e+3
 cxabs(z) = 	4.60793266237661153457951801141376e+3

Test of cxarg
*string in : 	0
 z =  		0.00000000000000000000000000000000e+0  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	*** Out of domain
*string in : 	+2.3106e-1571
 z =  		2.31059999999999999999999999999571e-1571  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	0.00000000000000000000000000000000e+0
*string in : 	+8.7792e-20  +9.7732e-20i
 z =  		8.77919999999999999999999999999979e-20  	9.77319999999999999999999999999977e-20
 cxarg(z) = 	8.38924958292089629849736401676606e-1
*string in : 	+2.3298e-1571i
 z =  		0.00000000000000000000000000000000e+0  	2.32979999999999999999999999999567e-1571
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	-4.5592e-19  +8.2219e-18i
 z =  		-4.55919999999999999999999999999990e-19  	8.22189999999999999999999999999983e-18
 cxarg(z) = 	1.62619149766846609737886543279789e+0
*string in : 	-3.8932e-1624i
 z =  		0.00000000000000000000000000000000e+0  	-3.89319999999999999999999999999252e-1624
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	-1.2291e-17  -7.3342e-18i
 z =  		-1.22909999999999999999999999999998e-17  	-7.33419999999999999999999999999984e-18
 cxarg(z) = 	-2.60359353930614271172250071199188e+0
*string in : 	-4.0987e-1617i
 z =  		0.00000000000000000000000000000000e+0  	-4.09869999999999999999999999999216e-1617
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	+3.9917e-19  -8.2215e-19i
 z =  		3.99169999999999999999999999999991e-19  	-8.22149999999999999999999999999982e-19
 cxarg(z) = 	-1.11879993977436025825292922558941e+0
*string in : 	+1.0
 z =  		1.00000000000000000000000000000000e+0  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	0.00000000000000000000000000000000e+0
*string in : 	+1.0000000000000000000986
 z =  		1.00000000000000000009860000000000e+0  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	0.00000000000000000000000000000000e+0
*string in : 	+1.0000000000000000004567 +2.43e-18i
 z =  		1.00000000000000000045670000000000e+0  	2.42999999999999999999999999999995e-18
 cxarg(z) = 	2.42999999999999999889021899999995e-18
*string in : 	+1.0  +3.4506e-1298i
 z =  		1.00000000000000000000000000000000e+0  	3.45059999999999999999999999999470e-1298
 cxarg(z) = 	3.45059999999999999999999999999470e-1298
*string in : 	+0.999999999999999998736  +4.6677e-1297i
 z =  		9.99999999999999998735999999999976e-1  	4.66769999999999999999999999999284e-1297
 cxarg(z) = 	4.66770000000000000589997279999295e-1297
*string in : 	+0.999999999999999999754
 z =  		9.99999999999999999753999999999976e-1  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	0.00000000000000000000000000000000e+0
*string in : 	+0.999999999999999999338  -5.0783e-1145i
 z =  		9.99999999999999999337999999999976e-1  	-5.07829999999999999999999999999312e-1145
 cxarg(z) = 	-5.07830000000000000336183459999325e-1145
*string in : 	+1.0000000000000000000    -6.7002e-1301i
 z =  		1.00000000000000000000000000000000e+0  	-6.70019999999999999999999999998969e-1301
 cxarg(z) = 	-6.70019999999999999999999999998969e-1301
*string in : 	+1.0000000000000007423    -5.3321e-1344i
 z =  		1.00000000000000074230000000000000e+0  	-5.33209999999999999999999999999153e-1344
 cxarg(z) = 	-5.33209999999999604198216999999447e-1344
*string in : 	-1.0
 z =  		-1.00000000000000000000000000000000e+0  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-0.99999999999999999998811
 z =  		-9.99999999999999999988109999999973e-1  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-0.99999999999999999976632 +2.3344e-15i
 z =  		-9.99999999999999999766319999999974e-1  	2.33439999999999999999999999999996e-15
 cxarg(z) = 	3.14159265358979090406264338327950e+0
*string in : 	-1.0  +4.5601e-997i
 z =  		-1.00000000000000000000000000000000e+0  	4.56009999999999999999999999999462e-997
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-1.00000000000000000000654 +7.4332e-1532i
 z =  		-1.00000000000000000000654000000000e+0  	7.43319999999999999999999999998655e-1532
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-1.00000000000000000000743
 z =  		-1.00000000000000000000743000000000e+0  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-1.00000000000000000085023 -6.9983e-18i
 z =  		-1.00000000000000000085023000000000e+0  	-6.99829999999999999999999999999985e-18
 cxarg(z) = 	-3.14159265358979323146434338327950e+0
*string in : 	-1.0  -5.00098e-1023i
 z =  		-1.00000000000000000000000000000000e+0  	-5.00097999999999999999999999999395e-1023
 cxarg(z) = 	-3.14159265358979323846264338327950e+0
*string in : 	-0.9999999999999999997643  -6.7321e-16i
 z =  		-9.99999999999999999764299999999974e-1  	-6.73209999999999999999999999999987e-16
 cxarg(z) = 	-3.14159265358979256525264338327950e+0
*string in : 	+1.0i
 z =  		0.00000000000000000000000000000000e+0  	1.00000000000000000000000000000000e+0
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	+5.6098e-2198 +1.0i
 z =  		5.60979999999999999999999999998542e-2198  	1.00000000000000000000000000000000e+0
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	+4.9987e-18   +1.0000000000000000005421i
 z =  		4.99869999999999999999999999999989e-18  	1.00000000000000000054210000000000e+0
 cxarg(z) = 	1.57079632679489661423262169163975e+0
*string in : 	+1.000000000000000000003201i
 z =  		0.00000000000000000000000000000000e+0  	1.00000000000000000000320100000000e+0
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	-6.5541e-20   +1.0000000000000000080981i
 z =  		-6.55409999999999999999999999999984e-20  	1.00000000000000000809810000000000e+0
 cxarg(z) = 	1.57079632679489661929686269163975e+0
*string in : 	-7.0998e-2200 +1.0i
 z =  		-7.09979999999999999999999999998153e-2200  	1.00000000000000000000000000000000e+0
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	-6.8432e-17   +0.9999999999999999999864i
 z =  		-6.84319999999999999999999999999986e-17  	9.99999999999999999986399999999974e-1
 cxarg(z) = 	1.57079632679489668766332169163975e+0
*string in : 	+0.99999999999999989098732i
 z =  		0.00000000000000000000000000000000e+0  	9.99999999999999890987319999999974e-1
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	+4.3329e-16   +0.9999999999999999997877i
 z =  		4.33289999999999999999999999999992e-16  	9.99999999999999999787699999999974e-1
 cxarg(z) = 	1.57079632679489618594132169163975e+0
*string in : 	-1.0i
 z =  		0.00000000000000000000000000000000e+0  	-1.00000000000000000000000000000000e+0
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	+2.7762e-2111 -1.0i
 z =  		2.77619999999999999999999999999307e-2111  	-1.00000000000000000000000000000000e+0
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	+3.3321e-17   -0.9999999999999999996555i
 z =  		3.33209999999999999999999999999993e-17  	-9.99999999999999999655499999999974e-1
 cxarg(z) = 	-1.57079632679489658591032169163975e+0
*string in : 	-0.999999999999999999996999972013i
 z =  		0.00000000000000000000000000000000e+0  	-9.99999999999999999996999972012965e-1
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	-7.5541e-17   -0.999999999999999999987231i
 z =  		-7.55409999999999999999999999999985e-17  	-9.99999999999999999987230999999972e-1
 cxarg(z) = 	-1.57079632679489669477232169163975e+0
*string in : 	-2.1156e-2203 -1.0i
 z =  		-2.11559999999999999999999999999449e-2203  	-1.00000000000000000000000000000000e+0
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	-5.9923e-16   -1.00000000000000000089321i
 z =  		-5.99229999999999999999999999999988e-16  	-1.00000000000000000089321000000000e+0
 cxarg(z) = 	-1.57079632679489721846132169163975e+0
*string in : 	-1.000000000000000000007161i
 z =  		0.00000000000000000000000000000000e+0  	-1.00000000000000000000716100000000e+0
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	+8.6631e-19   -1.00000000000000000008765i
 z =  		8.66309999999999999999999999999981e-19  	-1.00000000000000000008765000000000e+0
 cxarg(z) = 	-1.57079632679489661836501169163975e+0
*string in : 	+1.5876e1876
 z =  		1.58759999999999999999999999999648e+1876  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	0.00000000000000000000000000000000e+0
*string in : 	-6.4391e1965
 z =  		-6.43909999999999999999999999998503e+1965  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	+3.4210e2015i
 z =  		0.00000000000000000000000000000000e+0  	3.42099999999999999999999999999185e+2015
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	-4.5522e2011i
 z =  		0.00000000000000000000000000000000e+0  	-4.55219999999999999999999999998917e+2011
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	+2.1907e1854  +9.8765e1872i
 z =  		2.19069999999999999999999999999520e+1854  	9.87649999999999999999999999997812e+1872
 cxarg(z) = 	1.57079632679489661900951234622387e+0
*string in : 	-3.2966e1946  +7.5721e1834i
 z =  		-3.29659999999999999999999999999241e+1946  	7.57209999999999999999999999998357e+1834
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-6.0987e2310  -5.4411e2198i
 z =  		-6.09869999999999999999999999998333e+2310  	-5.44109999999999999999999999998585e+2198
 cxarg(z) = 	-3.14159265358979323846264338327950e+0
*string in : 	+7.8895e1854  -3.8699e1943i
 z =  		7.88949999999999999999999999998271e+1854  	-3.86989999999999999999999999999111e+1943
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	+10.009876543100091234
 z =  		1.00098765431000912340000000000000e+1  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	0.00000000000000000000000000000000e+0
*string in : 	+9.8980000000006542009 +6.11002230065009876i
 z =  		9.89800000000065420089999999999997e+0  	6.11002230065009876000000000000000e+0
 cxarg(z) = 	5.53042107025953173852302384116297e-1
*string in : 	+17.9998888123400000076i
 z =  		0.00000000000000000000000000000000e+0  	1.79998888123400000076000000000000e+1
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	-12.9822227      +20.87777220192i
 z =  		-1.29822227000000000000000000000000e+1  	2.08777722019200000000000000000000e+1
 cxarg(z) = 	2.12710585235075047160057027232326e+0
*string in : 	-17.9877771265
 z =  		-1.79877771265000000000000000000000e+1  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-19.09872210981  -32.9800000654i
 z =  		-1.90987221098100000000000000000000e+1  	-3.29800000653999999999999999999999e+1
 cxarg(z) = 	-2.09570649869183772096177981258929e+0
*string in : 	-43.987600182345i
 z =  		0.00000000000000000000000000000000e+0  	-4.39876001823449999999999999999999e+1
 cxarg(z) = 	-1.57079632679489661923132169163975e+0
*string in : 	+15.982201192361 -43.2189031229i
 z =  		1.59822011923610000000000000000000e+1  	-4.32189031228999999999999999999999e+1
 cxarg(z) = 	-1.21659537262678903716220661644215e+0
*string in : 	+1000.009876543100091234
 z =  		1.00000987654310009123400000000000e+3  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	0.00000000000000000000000000000000e+0
*string in : 	+989.80000000006542009 +611.002230065009876i
 z =  		9.89800000000065420089999999999996e+2  	6.11002230065009875999999999999998e+2
 cxarg(z) = 	5.53042107025953173852302384116296e-1
*string in : 	+179.998888123400000076i
 z =  		0.00000000000000000000000000000000e+0  	1.79998888123400000076000000000000e+2
 cxarg(z) = 	1.57079632679489661923132169163975e+0
*string in : 	-1298.22227  +208.7777220192i
 z =  		-1.29822227000000000000000000000000e+3  	2.08777722019199999999999999999999e+2
 cxarg(z) = 	2.98213975150210743249550554091572e+0
*string in : 	-1798.777712650981
 z =  		-1.79877771265098099999999999999999e+3  	0.00000000000000000000000000000000e+0
 cxarg(z) = 	3.14159265358979323846264338327950e+0
*string in : 	-190.9872210981   -329.800700654i
 z =  		-1.90987221098100000000000000000000e+2  	-3.29800700653999999999999999999999e+2
 cxarg(z) = 	-2.09570557823594370914996234699252e+0
*string in : 	+1598.2201192361  -4321.89031229i
 z =  		1.59822011923609999999999999999999e+3  	-4.32189031228999999999999999999998e+3
 cxarg(z) = 	-1.21659537262678903716220661644215e+0
*/
