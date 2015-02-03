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
    Test:  xtanh  xsinh  xcosh

    Uses:  atox  xprcmp  xadd  xtodbl  xprxpr

*/
#include <stdio.h>
#include "xpre.h"

int decd = 30;

int
main (void)
{
  struct xpr z, w, f, u;
  int k;
  char cf[3];

  cf[0] = 's';
  cf[1] = 'c';
  cf[2] = 't';
  for (k = 0; k < 3; ++k)
    {
      switch (cf[k])
	{
	case 't':
	  printf ("     Test of Tanh Function\n");
	  break;
	case 's':
	  printf ("     Test of Sinh Function\n");
	  break;
	case 'c':
	  printf ("     Test of Cosh Function\n");
	  break;
	}
      z = xZero;
      w = atox ("0.2");
      u = atox ("3.01");
      for (; xprcmp (&z, &u) < 0; z = xadd (z, w, 0))
	{
	  /* compute selected extended precision hyperbolic function */
	  switch (cf[k])
	    {
	    case 't':
	      f = xtanh (z);
	      break;
	    case 's':
	      f = xsinh (z);
	      break;
	    case 'c':
	      f = xcosh (z);
	      break;
	    }
	  printf (" %8.4f  ", xtodbl (z));
	  xprxpr (f, decd);
	  putchar ('\n');
	}
    }
  return 0;
}

/*  Test output

     Test of Sinh Function
   0.0000  0.000000000000000000000000000000e+0
   0.2000  2.013360025410939876255682430103e-1
   0.4000  4.107523258028155085402100138447e-1
   0.6000  6.366535821482412711234543754651e-1
   0.8000  8.881059821876230065747175731898e-1
   1.0000  1.175201193643801456882381850596e+0
   1.2000  1.509461355412172696442894911259e+0
   1.4000  1.904301501451534055142123827697e+0
   1.6000  2.375567953200229697584553544390e+0
   1.8000  2.942174288095679772717109616298e+0
   2.0000  3.626860407847018767668213982801e+0
   2.2000  4.457105170535893521568816370519e+0
   2.4000  5.466229213676094574431383774794e+0
   2.6000  6.694732228393678258661307381207e+0
   2.8000  8.191918354235915953251197311370e+0
   3.0000  1.001787492740990189897459361947e+1
     Test of Cosh Function
   0.0000  1.000000000000000000000000000000e+0
   0.2000  1.020066755619075846295503751629e+0
   0.4000  1.081072371838454809284642938993e+0
   0.6000  1.185465218242267703751913292698e+0
   0.8000  1.337434946304844598004819958205e+0
   1.0000  1.543080634815243778477905620757e+0
   1.2000  1.810655567324374793087872518342e+0
   1.4000  2.150898465393140532081985067531e+0
   1.6000  2.577464471194885106069732812034e+0
   1.8000  3.107473176317266311013914336730e+0
   2.0000  3.762195691083631459562213477774e+0
   2.2000  4.567908328898227404902960796369e+0
   2.4000  5.556947166965507077806555994874e+0
   2.6000  6.769005806608012139089517951377e+0
   2.8000  8.252728416861133918246818699554e+0
   3.0000  1.006766199577776584195393603512e+1
     Test of Tanh Function
   0.0000  0.000000000000000000000000000000e+0
   0.2000  1.973753202249040007381573188110e-1
   0.4000  3.799489622552248852677481238969e-1
   0.6000  5.370495669980352858618253049269e-1
   0.8000  6.640367702678489636848446564011e-1
   1.0000  7.615941559557648881194582828631e-1
   1.2000  8.336546070121552586740951218123e-1
   1.4000  8.853516482022625075834176520256e-1
   1.6000  9.216685544064712826832642230893e-1
   1.8000  9.468060128462682896463983148048e-1
   2.0000  9.640275800758168839464137241878e-1
   2.2000  9.757431300314515204143066680301e-1
   2.4000  9.836748576936802096397291499339e-1
   2.6000  9.890274022010991893409624367582e-1
   2.8000  9.926315202011280244806136325760e-1
   3.0000  9.950547536867304513318801852555e-1
*/
