/* GToy Example 03
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

#include                                <gtoy.h>
#include                                "dog.h"
#include                                "bulldog.h"
#include                                "cat.h"

int                             
main                                    (int argc, 
                                         char **argv)
{
        Dog *dog = gtoy_object_new (DOG_TYPE, Dog);
        Cat *cat = gtoy_object_new (CAT_TYPE, Cat);
        Bulldog *bulldog = gtoy_object_new (BULLDOG_TYPE, Bulldog);

        g_printf ("Dog can act as Cat? %d \n", gtoy_object_as (dog, CAT_TYPE));
        g_printf ("Cat can act as Dog? %d \n", gtoy_object_as (cat, DOG_TYPE));
        g_printf ("Dog can act as Bulldog? %d \n", gtoy_object_as (dog, BULLDOG_TYPE));
        g_printf ("Cat can act as Bulldog? %d \n", gtoy_object_as (cat, BULLDOG_TYPE));
        g_printf ("Bulldog can act as dog? %d \n", gtoy_object_as (bulldog, DOG_TYPE));
        g_printf ("Bulldog can act as cat? %d \n", gtoy_object_as (bulldog, CAT_TYPE));

        gtoy_object_unref (bulldog);
        gtoy_object_unref (dog);
        gtoy_object_unref (cat);

        return 0;
}
