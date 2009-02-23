/* GToy Example 06
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

#include                                "box.h"

struct                                  _BoxPrivate
{
        guint a;
        guint b;
        guint c;
};

static gboolean
init                                    (Box *box)
{
        g_printf ("Initializing box...\n");
        box->priv = g_malloc (sizeof (BoxPrivate));
        box->priv->a = 1;
        box->priv->b = 2;
        box->priv->c = 3;

        return TRUE;
}

static void
dispose                                 (Box *box)
{
        g_printf ("Deallocating box...\n");
        if (box->priv == NULL)
                return;

        g_free (box->priv);
}

GToyObjectType*                   
box_get_type                            (void)
{
        static GToyObjectType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_object_type_new ();

                gtoy_object_type_set_name (type, "Box");
                gtoy_object_type_set_init (type, (GToyObjectInitFunc) init);
                gtoy_object_type_set_dispose (type, (GToyObjectDisposeFunc) dispose);
        }
        
        return type;
}

