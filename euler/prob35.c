/*
** prob35.c
** Login : <thura@thura-desktop>
** Started on  Mon Dec 14 19:18:30 2009 Thura Hlaing
** $Id$
** 
** Copyright (C) 2009 Thura Hlaing
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char num_str[8];

int circular_prime (long number)
{
  sprintf(num_str, "%ld", number);
  
  int m = 0;
  int n = 0;
  int len = strlen(num_str);

  for(; m < len; m++) {
  }
	

  return 0;
}



int main ()
{
  circular_prime(1000);
  return 0;
}
  
