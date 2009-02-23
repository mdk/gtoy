/* GToy Example 01
 *
 * LGPL license, Copyright (C) 2006 by:
 *
 * Authors:
 *      Michael Dominic Kostrzewa <mdk@mdk.am>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef                                 ___PIZZA_H___
#define                                 ___PIZZA_H___

#include                                <gtoy.h>

struct                                  _Pizza
{
        GToyObject parent;
} typedef                               Pizza;

enum
{
        PIZZA_VIRTUAL_EAT
};

#define                                 PIZZA_TYPE pizza_get_type ()

typedef                                 void (*PizzaEatFunc) (Pizza *pizza);

GToyObjectType*                   
pizza_get_type                          (void);

void                            
pizza_eat                               (Pizza *pizza);

#endif                                  /* ___PIZZA_H___ */
