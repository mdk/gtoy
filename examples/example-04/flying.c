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

#include                                "flying.h"

GToyInterfaceType*                
flying_get_type                         (void)
{
        static GToyInterfaceType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_interface_type_new ();
                gtoy_interface_type_add_method (type, FLYING_INTERFACE_FLY);
                gtoy_interface_type_set_name (type, "Flying");
        }
        
        return type;
}

void                            
flying_fly                              (GToyObject *obj)
{
        FlyingFlyFunc func = gtoy_object_get_interface_method (obj, FLYING_TYPE, FLYING_INTERFACE_FLY);
        g_return_if_fail (func != NULL);
        func (obj);
}
