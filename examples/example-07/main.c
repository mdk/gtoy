/* GToy Example 07
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
#include                                "instrument.h"
#include                                "flute.h"
#include                                "guitar.h"

int                             
main                                    (int argc, 
                                         char **argv)
{
        Flute *flute = gtoy_object_new (FLUTE_TYPE, Flute);
        Guitar *guitar = gtoy_object_new (GUITAR_TYPE, Flute);

        g_printf ("Changing string in real guitar...\n");
        guitar_change_strings (guitar);

        g_printf ("Try to change strings in flute (bad casting)..\n");
        guitar_change_strings ((Guitar *) flute);

        gtoy_object_unref (flute);
        gtoy_object_unref (guitar);

        g_printf ("Trying to destroy already destroyed flue...\n");
        gtoy_object_unref (flute);
        
        return 0;
}
