/* GToy Example 08
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

#include                                "dragon.h"

struct                                  _DragonPrivate
{
        guint tails_count;
};

static gboolean
init                                    (Dragon *dragon)
{
        g_printf ("Creating dragon...\n");
        dragon->priv = g_malloc (sizeof (DragonPrivate));
        dragon->priv->tails_count = 1;

        return TRUE;
}

static void
dispose                                 (Dragon *dragon)
{
        g_printf ("Destroying dragon...\n");
        if (dragon->priv == NULL)
                return;

        g_free (dragon->priv);
}

static void
describe                                (Dragon *dragon)
{
        g_printf ("I'm a dragon with %d heads and %d tails\n", 
                  monster_get_heads_count ((Monster *) dragon), 
                  dragon->priv->tails_count);
}

static void
set_heads_count                         (Dragon *dragon, guint count)
{
        /* Everybody knows, that this is the one and only correct
         * way to calculate dragon tails... */

        dragon->priv->tails_count = MAX (count / 2, 1);

        MonsterSetHeadsCountFunc func = gtoy_object_get_base_method (dragon, 
                                                                     MONSTER_TYPE,
                                                                     DRAGON_TYPE,
                                                                     MONSTER_VIRTUAL_SET_HEADS_COUNT);
        g_return_if_fail (func != NULL);
        func ((Monster *) dragon, count);
}

GToyObjectType*                   
dragon_get_type                         (void)
{
        static GToyObjectType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_object_type_new ();

                gtoy_object_type_set_name (type, "Dragon");
                gtoy_object_type_set_parent (type, MONSTER_TYPE);
                gtoy_object_type_set_init (type, (GToyObjectInitFunc) init);
                gtoy_object_type_set_dispose (type, (GToyObjectDisposeFunc) dispose);
                gtoy_object_type_override (type, MONSTER_TYPE, MONSTER_VIRTUAL_DESCRIBE, describe);
                gtoy_object_type_override (type, MONSTER_TYPE, MONSTER_VIRTUAL_SET_HEADS_COUNT, set_heads_count);
        }
        
        return type;
}
