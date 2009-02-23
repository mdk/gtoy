/* GToy Example 02
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

#include                                "pizza.h"

static void
eat                                     (Pizza *pizza)
{
        g_printf ("Mhmmm... tastes good!\n");
}

static void
add_salt                                (Pizza *pizza, gint salt)
{
        g_printf ("Adding %d grams of salt!\n", salt);
}


GToyObjectType*                   
pizza_get_type                           (void)
{
        static GToyObjectType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_object_type_new ();

                gtoy_object_type_set_name (type, "Pizza");
                gtoy_object_type_add_virtual (type, PIZZA_VIRTUAL_EAT, eat);
                gtoy_object_type_add_virtual (type, PIZZA_VIRTUAL_ADD_SALT, add_salt);
        }
        
        return type;
}

void                            
pizza_eat                               (Pizza *pizza)
{
        PizzaEatFunc func = gtoy_object_get_top_method (pizza, PIZZA_TYPE, PIZZA_VIRTUAL_EAT);
        g_return_if_fail (func != NULL);
        func (pizza);
}

void                            
pizza_add_salt                          (Pizza *pizza, gint salt)
{
        PizzaAddSaltFunc func = gtoy_object_get_top_method (pizza, PIZZA_TYPE, PIZZA_VIRTUAL_ADD_SALT);
        g_return_if_fail (func != NULL);
        func (pizza, salt);
}
