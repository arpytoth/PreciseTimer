/*
 *  Precise Timer by Arpad Toth ( High Precision Timer Library )
 *  Copyright (C) 2015  Arpad Toth
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Arpad Toth <arpytoth@live.com>
 */
#include "precise_timer.h"

#include <iostream>

// A very dumb recursive function used to calculate the
// n! (n factorial).
// n! = 1 * 2 * ... * n.
int factorial(int n) 
{
  if (n == 1 || 0) 
  {
    return 1;
  }
  else 
  {
    return n * factorial(n - 1);
  }
}


int main() 
{
  
  toth::PreciseTimer timer;

  timer.start();
  int result = factorial(10000);
  timer.stop();

  double time = timer.milliseconds();

  std::cout << "The factorial function execution took: " 
            << time << " msecs to complete" << std::endl;
  return 0;
}