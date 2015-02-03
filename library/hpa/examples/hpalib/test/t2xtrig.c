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
    Test:  xsin  xcos  xtan

    Uses:  atox  xpr_print
    
    Input file:  data/xtrig.dat
*/

#include <stdio.h>
#include <stdlib.h>
#include "xpre.h"

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

#define DECD 30

int
main (int na, char **av)
{
  struct xpr x;
  char num[1024];
  FILE *fp;

  if (na != 2)
    {
      printf ("para: input_file\n");
      exit (-1);
    }
  fp = fopen (*++av, "r");
  printf ("    Test of the trigonometric functions\n\n");
  while (get_line (num, 1024, fp) != -1)
    {
      printf ("*string in : \"%s\"\n", num);
      x = atox (num);
      printf (" x =  \t\t");
      xpr_print (stdout, x, 1, 1, DECD);
      printf ("\n xsin(x) = \t");
      xpr_print (stdout, xsin (x), 1, 1, DECD);
      printf ("\n xcos(x) = \t");
      xpr_print (stdout, xcos (x), 1, 1, DECD);
      printf ("\n xtan(x) = \t");
      xpr_print (stdout, xtan (x), 1, 1, DECD);
      printf ("\n\n");
    }
  fclose (fp);
  return 0;
}

/*  Test output

    Test of the trigonometric functions

*string in : "8.76523e23"
 x =  		+8.765230000000000000000000000000e+23
 xsin(x) = 	+9.452220038871091361022629340676e-1
 xcos(x) = 	-3.264281902159153919182910603288e-1
 xtan(x) = 	-2.895650658302193782211295090873e+0

*string in : "2.1098734e22"
 x =  		+2.109873400000000000000000000000e+22
 xsin(x) = 	+7.542500786390265084476484292297e-1
 xcos(x) = 	-6.565872515309921305708382582096e-1
 xtan(x) = 	-1.148743105931937991818069166570e+0

*string in : "4.123e10"
 x =  		+4.123000000000000000000000000000e+10
 xsin(x) = 	-9.017125073694837327923321933919e-1
 xcos(x) = 	-4.323361586236325258860031537062e-1
 xtan(x) = 	+2.085674513647293103970289801326e+0

*string in : "41230000001.5708"
 x =  		+4.123000000157080000000000000000e+10
 xsin(x) = 	-4.323328464457320475602839062405e-1
 xcos(x) = 	+9.017140954227848125587335687270e-1
 xtan(x) = 	-4.794566799391386301909614346229e-1

*string in : "41230000003.1416"
 x =  		+4.123000000314160000000000000000e+10
 xsin(x) = 	+9.017156834639195728444701772422e-1
 xcos(x) = 	+4.323295342619983460892775131205e-1
 xtan(x) = 	+2.085713817824590263035036758472e+0

*string in : "41230000004.7124"
 x =  		+4.123000000471240000000000000000e+10
 xsin(x) = 	+4.323262220724314661624124291222e-1
 xcos(x) = 	-9.017172714928879922229979678716e-1
 xtan(x) = 	-4.794476447774698097714490790286e-1

*string in : "3.141592653589793238462643383280"
 x =  		+3.141592653589793238462643383280e+0
 xsin(x) = 	-4.914973218076225896998855709477e-31
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	+4.914973218076225896998855709477e-31

*string in : "3.141592653589793238462643383278"
 x =  		+3.141592653589793238462643383278e+0
 xsin(x) = 	+1.508388332444083120113441924633e-30
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	-1.508388332444083120113441924633e-30

*string in : "3.141592653589793238462643383281"
 x =  		+3.141592653589793238462643383281e+0
 xsin(x) = 	-1.492210520911230338947771709915e-30
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	+1.492210520911230338947771709915e-30

*string in : "3.1415926535897932384626433832"
 x =  		+3.141592653589793238462643383200e+0
 xsin(x) = 	+7.950778070814938027453932620815e-29
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	-7.950778070814938027453932620815e-29

*string in : "3.1415926535897932384626433833"
 x =  		+3.141592653589793238462643383300e+0
 xsin(x) = 	-2.049189460828018947651560530910e-29
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	+2.049189460828018947651560530910e-29

*string in : "3.1415926535897932"
 x =  		+3.141592653589793200000000000000e+0
 xsin(x) = 	+3.846264338327950579059638888044e-17
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	-3.846264338327950579059638888044e-17

*string in : "3.1415926535897933"
 x =  		+3.141592653589793300000000000000e+0
 xsin(x) = 	-6.153735661672049443029821678770e-17
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	+6.153735661672049443029821678770e-17

*string in : "1.570796326794896619231321691640"
 x =  		+1.570796326794896619231321691640e+0
 xsin(x) = 	+1.000000000000000000000000000000e+0
 xcos(x) = 	-2.289930703876423429283557773734e-31
 xtan(x) = 	-4.385385860249009821394000278057e+30

*string in : "1.570796326794896619231321691638"
 x =  		+1.570796326794896619231321691638e+0
 xsin(x) = 	+1.000000000000000000000000000000e+0
 xcos(x) = 	+1.772625920814011879152722098358e-30
 xtan(x) = 	+5.643800933190030031011409053500e+29

*string in : "1.570796326794896619231321691642"
 x =  		+1.570796326794896619231321691642e+0
 xsin(x) = 	+1.000000000000000000000000000000e+0
 xcos(x) = 	-2.228686131644909329156377675164e-30
 xtan(x) = 	-4.488500050600646290223458099257e+29

*string in : "1.5707963267948966192313216917"
 x =  		+1.570796326794896619231321691700e+0
 xsin(x) = 	+1.000000000000000000000000000000e+0
 xcos(x) = 	-6.023076270878865917413143178885e-29
 xtan(x) = 	-1.660302386239600561672772958706e+28

*string in : "1.5707963267948966192313216916"
 x =  		+1.570796326794896619231321691600e+0
 xsin(x) = 	+1.000000000000000000000000000000e+0
 xcos(x) = 	+3.977103113057973653636186130934e-29
 xtan(x) = 	+2.514453824509112741300398226239e+28

*string in : "1.5707963267948965"
 x =  		+1.570796326794896500000000000000e+0
 xsin(x) = 	+1.000000000000000000000000000000e+0
 xcos(x) = 	+1.192313216916397627100690059143e-16
 xtan(x) = 	+8.387057912401870157857964529862e+15

*string in : "1.5707963267948967"
 x =  		+1.570796326794896700000000000000e+0
 xsin(x) = 	+1.000000000000000000000000000000e+0
 xcos(x) = 	-8.076867830836023901951523512559e-17
 xtan(x) = 	-1.238103706714353381250453594951e+16

*string in : "0"
 x =  		+0.000000000000000000000000000000e+0
 xsin(x) = 	+0.000000000000000000000000000000e+0
 xcos(x) = 	+1.000000000000000000000000000000e+0
 xtan(x) = 	+0.000000000000000000000000000000e+0

*string in : "1.045e-27"
 x =  		+1.045000000000000000000000000000e-27
 xsin(x) = 	+1.045000000000000000000000000000e-27
 xcos(x) = 	+1.000000000000000000000000000000e+0
 xtan(x) = 	+1.045000000000000000000000000000e-27

*string in : "-1.045e-27"
 x =  		-1.045000000000000000000000000000e-27
 xsin(x) = 	-1.045000000000000000000000000000e-27
 xcos(x) = 	+1.000000000000000000000000000000e+0
 xtan(x) = 	-1.045000000000000000000000000000e-27

*string in : "4.32e-19"
 x =  		+4.320000000000000000000000000000e-19
 xsin(x) = 	+4.320000000000000000000000000000e-19
 xcos(x) = 	+1.000000000000000000000000000000e+0
 xtan(x) = 	+4.320000000000000000000000000000e-19

*string in : "-4.32e-19"
 x =  		-4.320000000000000000000000000000e-19
 xsin(x) = 	-4.320000000000000000000000000000e-19
 xcos(x) = 	+1.000000000000000000000000000000e+0
 xtan(x) = 	-4.320000000000000000000000000000e-19

*string in : "3.889e-16"
 x =  		+3.889000000000000000000000000000e-16
 xsin(x) = 	+3.889000000000000000000000000000e-16
 xcos(x) = 	+9.999999999999999999999999999999e-1
 xtan(x) = 	+3.889000000000000000000000000000e-16

*string in : "-3.889e-16"
 x =  		-3.889000000000000000000000000000e-16
 xsin(x) = 	-3.889000000000000000000000000000e-16
 xcos(x) = 	+9.999999999999999999999999999999e-1
 xtan(x) = 	-3.889000000000000000000000000000e-16

*string in : "-1.570796326794896619231321691640"
 x =  		-1.570796326794896619231321691640e+0
 xsin(x) = 	-1.000000000000000000000000000000e+0
 xcos(x) = 	-2.289930703876423429283557773734e-31
 xtan(x) = 	+4.385385860249009821394000278057e+30

*string in : "-1.570796326794896619231321691638"
 x =  		-1.570796326794896619231321691638e+0
 xsin(x) = 	-1.000000000000000000000000000000e+0
 xcos(x) = 	+1.772625920814011879152722098358e-30
 xtan(x) = 	-5.643800933190030031011409053500e+29

*string in : "-1.570796326794896619231321691642"
 x =  		-1.570796326794896619231321691642e+0
 xsin(x) = 	-1.000000000000000000000000000000e+0
 xcos(x) = 	-2.228686131644909329156377675164e-30
 xtan(x) = 	+4.488500050600646290223458099257e+29

*string in : "-1.5707963267948966192313216917"
 x =  		-1.570796326794896619231321691700e+0
 xsin(x) = 	-1.000000000000000000000000000000e+0
 xcos(x) = 	-6.023076270878865917413143178885e-29
 xtan(x) = 	+1.660302386239600561672772958706e+28

*string in : "-1.5707963267948966192313216916"
 x =  		-1.570796326794896619231321691600e+0
 xsin(x) = 	-1.000000000000000000000000000000e+0
 xcos(x) = 	+3.977103113057973653636186130934e-29
 xtan(x) = 	-2.514453824509112741300398226239e+28

*string in : "-1.5707963267948965"
 x =  		-1.570796326794896500000000000000e+0
 xsin(x) = 	-1.000000000000000000000000000000e+0
 xcos(x) = 	+1.192313216916397627100690059143e-16
 xtan(x) = 	-8.387057912401870157857964529862e+15

*string in : "-1.5707963267948967"
 x =  		-1.570796326794896700000000000000e+0
 xsin(x) = 	-1.000000000000000000000000000000e+0
 xcos(x) = 	-8.076867830836023901951523512559e-17
 xtan(x) = 	+1.238103706714353381250453594951e+16

*string in : "-3.141592653589793238462643383280"
 x =  		-3.141592653589793238462643383280e+0
 xsin(x) = 	+4.914973218076225896998855709477e-31
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	-4.914973218076225896998855709477e-31

*string in : "-3.141592653589793238462643383278"
 x =  		-3.141592653589793238462643383278e+0
 xsin(x) = 	-1.508388332444083120113441924633e-30
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	+1.508388332444083120113441924633e-30

*string in : "-3.141592653589793238462643383281"
 x =  		-3.141592653589793238462643383281e+0
 xsin(x) = 	+1.492210520911230338947771709915e-30
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	-1.492210520911230338947771709915e-30

*string in : "-3.1415926535897932384626433832"
 x =  		-3.141592653589793238462643383200e+0
 xsin(x) = 	-7.950778070814938027453932620815e-29
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	+7.950778070814938027453932620815e-29

*string in : "-3.1415926535897932384626433833"
 x =  		-3.141592653589793238462643383300e+0
 xsin(x) = 	+2.049189460828018947651560530910e-29
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	-2.049189460828018947651560530910e-29

*string in : "-3.1415926535897932"
 x =  		-3.141592653589793200000000000000e+0
 xsin(x) = 	-3.846264338327950579059638888044e-17
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	+3.846264338327950579059638888044e-17

*string in : "-3.1415926535897933"
 x =  		-3.141592653589793300000000000000e+0
 xsin(x) = 	+6.153735661672049443029821678770e-17
 xcos(x) = 	-1.000000000000000000000000000000e+0
 xtan(x) = 	-6.153735661672049443029821678770e-17

*string in : "-8.76523e23"
 x =  		-8.765230000000000000000000000000e+23
 xsin(x) = 	-9.452220038871091361022629340676e-1
 xcos(x) = 	-3.264281902159153919182910603288e-1
 xtan(x) = 	+2.895650658302193782211295090873e+0

*string in : "-2.1098734e22"
 x =  		-2.109873400000000000000000000000e+22
 xsin(x) = 	-7.542500786390265084476484292297e-1
 xcos(x) = 	-6.565872515309921305708382582096e-1
 xtan(x) = 	+1.148743105931937991818069166570e+0

*string in : "0.785398163397448309615660845820"
 x =  		+7.853981633974483096156608458200e-1
 xsin(x) = 	+7.071067811865475244008443621049e-1
 xcos(x) = 	+7.071067811865475244008443621048e-1
 xtan(x) = 	+1.000000000000000000000000000000e+0

*string in : "2.356194490192344928846982537460"
 x =  		+2.356194490192344928846982537460e+0
 xsin(x) = 	+7.071067811865475244008443621046e-1
 xcos(x) = 	-7.071067811865475244008443621051e-1
 xtan(x) = 	-9.999999999999999999999999999993e-1

*string in : "3.926990816987241548078304229099"
 x =  		+3.926990816987241548078304229099e+0
 xsin(x) = 	-7.071067811865475244008443621046e-1
 xcos(x) = 	-7.071067811865475244008443621051e-1
 xtan(x) = 	+9.999999999999999999999999999992e-1

*string in : "5.497787143782138167309625920739"
 x =  		+5.497787143782138167309625920739e+0
 xsin(x) = 	-7.071067811865475244008443621050e-1
 xcos(x) = 	+7.071067811865475244008443621047e-1
 xtan(x) = 	-1.000000000000000000000000000000e+0

*string in : "7.068583470577034786540947612379"
 x =  		+7.068583470577034786540947612379e+0
 xsin(x) = 	+7.071067811865475244008443621049e-1
 xcos(x) = 	+7.071067811865475244008443621048e-1
 xtan(x) = 	+1.000000000000000000000000000000e+0

*string in : "-13.351768777756621263466234378938"
 x =  		-1.335176877775662126346623437894e+1
 xsin(x) = 	-7.071067811865475244008443621049e-1
 xcos(x) = 	+7.071067811865475244008443621048e-1
 xtan(x) = 	-1.000000000000000000000000000000e+0

*string in : "0.523598775598298873077107230547"
 x =  		+5.235987755982988730771072305470e-1
 xsin(x) = 	+5.000000000000000000000000000003e-1
 xcos(x) = 	+8.660254037844386467637231707527e-1
 xtan(x) = 	+5.773502691896257645091487805025e-1

*string in : "75.921822461753336596180548429255"
 x =  		+7.592182246175333659618054842925e+1
 xsin(x) = 	+5.000000000000000000000000000003e-1
 xcos(x) = 	+8.660254037844386467637231707528e-1
 xtan(x) = 	+5.773502691896257645091487805024e-1

*string in : "-0.523598775598298873077107230547"
 x =  		-5.235987755982988730771072305470e-1
 xsin(x) = 	-5.000000000000000000000000000003e-1
 xcos(x) = 	+8.660254037844386467637231707527e-1
 xtan(x) = 	-5.773502691896257645091487805025e-1

*string in : "-77.492618788548233215411870120894"
 x =  		-7.749261878854823321541187012089e+1
 xsin(x) = 	-8.660254037844386467637231707532e-1
 xcos(x) = 	-4.999999999999999999999999999996e-1
 xtan(x) = 	+1.732050807568877293527446341508e+0

*string in : "1.047197551196597746154214461093"
 x =  		+1.047197551196597746154214461093e+0
 xsin(x) = 	+8.660254037844386467637231707529e-1
 xcos(x) = 	+5.000000000000000000000000000001e-1
 xtan(x) = 	+1.732050807568877293527446341505e+0

*string in : "787.230759112042355671430721126789"
 x =  		+7.872307591120423556714307211268e+2
 xsin(x) = 	+9.659258262890682867497431997288e-1
 xcos(x) = 	-2.588190451025207623488988376243e-1
 xtan(x) = 	-3.732050807568877293527446341502e+0

*string in : "-1.047197551196597746154214461093"
 x =  		-1.047197551196597746154214461093e+0
 xsin(x) = 	-8.660254037844386467637231707529e-1
 xcos(x) = 	+5.000000000000000000000000000001e-1
 xtan(x) = 	-1.732050807568877293527446341505e+0

*string in : "-788.801555438837252290662042818429"
 x =  		-7.888015554388372522906620428184e+2
 xsin(x) = 	+2.588190451025207623488988376245e-1
 xcos(x) = 	-9.659258262890682867497431997288e-1
 xtan(x) = 	-2.679491924311227064725536584947e-1

*string in : "876523000000000000000003.141592653589793238462643383280"
 x =  		+8.765230000000000000000031415926e+23
 xsin(x) = 	-9.452220038871091361022629340676e-1
 xcos(x) = 	+3.264281902159153919182910603288e-1
 xtan(x) = 	-2.895650658302193782211295090873e+0

*string in : "-21098734000000000000003.141592653589793238462643383280"
 x =  		-2.109873400000000000000314159265e+22
 xsin(x) = 	+7.542500786438038094597811548554e-1
 xcos(x) = 	+6.565872515255042389681488058061e-1
 xtan(x) = 	+1.148743105948815381123264293771e+0

*/
