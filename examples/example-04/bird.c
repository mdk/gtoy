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

#include                                "bird.h"

static void
sing                                    (Bird *bird)
{
        g_printf ("La la la...\n");
}

static void
fly                                     (Bird *bird)
{
        g_printf ("Flap flap flap... off I go!\n");
}

GToyObjectType*                   
bird_get_type                           (void)
{
        static GToyObjectType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_object_type_new ();

                gtoy_object_type_set_name (type, "Bird");
                gtoy_object_type_add_virtual (type, BIRD_VIRTUAL_SING, sing);
                gtoy_object_type_add_interface (type, FLYING_TYPE);
                gtoy_object_type_implement (type, FLYING_TYPE, FLYING_INTERFACE_FLY, fly); 
        }
        
        return type;
}

void                            
bird_sing                               (Bird *bird)
{
        BirdSingFunc func = gtoy_object_get_top_method (bird, BIRD_TYPE, BIRD_VIRTUAL_SING);
        g_return_if_fail (func != NULL);
        func (bird);
}
