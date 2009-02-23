/* GToy
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

#include                                "gtoy-interface-type.h"
#include                                "gtoy-magic.h"
#include                                "gtoy-errors.h"

GToyInterfaceType*                        
gtoy_interface_type_new                 (void)
{
        GToyInterfaceType *type = g_new (GToyInterfaceType, 1);

        type->magic = GTOY_INTERFACE_TYPE_MAGIC;
        type->name = "Undefined";
        type->method_count = 0;

        return type;
}

void                            
gtoy_interface_type_add_method          (GToyInterfaceType *type, guint16 pos)
{
        gtoy_return_if_fail (gtoy_interface_type_is (type), GTOY_ERROR_INVALID_INTERFACE_TYPE);

        type->method_count = MAX (type->method_count, pos + 1);
}

gboolean
gtoy_interface_type_is                  (GToyInterfaceType *type)
{
        if (type != NULL &&
            type->magic == GTOY_INTERFACE_TYPE_MAGIC)
                return TRUE;
        else
                return FALSE;
}

void                            
gtoy_interface_type_set_name            (GToyInterfaceType *type, 
                                         const char *name)
{
        gtoy_return_if_fail (gtoy_interface_type_is (type), GTOY_ERROR_INVALID_INTERFACE_TYPE);
        gtoy_return_if_fail (name != NULL, GTOY_ERROR_NULL_INTERFACE_TYPE_NAME);

        type->name = name;
}


