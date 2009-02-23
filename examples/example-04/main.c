/* GToy Example 04
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
#include                                "bird.h"
#include                                "crow.h"
#include                                "flying.h"

int                             
main                                    (int argc, 
                                         char **argv)
{
        Bird *bird = gtoy_object_new (BIRD_TYPE, Bird);
        Bird *crow = gtoy_object_new (CROW_TYPE, Crow);

        g_printf ("Sing, bird!\n");
        bird_sing (bird);
        g_printf ("Fly, bird!\n");
        flying_fly ((GToyObject *) bird);

        g_printf ("Can crow sing?\n");
        bird_sing (crow);
        g_printf ("Can crow fly?\n");
        flying_fly ((GToyObject *) crow);

        gtoy_object_unref (bird);
        gtoy_object_unref (crow);

        return 0;
}
