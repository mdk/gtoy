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

#include                                "monster.h"

struct                                  _MonsterPrivate
{
        guint heads_count;
};

static gboolean
init                                    (Monster *monster)
{
        g_printf ("Creating monster...\n");
        monster->priv = g_malloc (sizeof (MonsterPrivate));
        monster->priv->heads_count = 2;

        return TRUE;
}

static void
dispose                                 (Monster *monster)
{
        g_printf ("Destroying monster...\n");
        if (monster->priv == NULL)
                return;

        g_free (monster->priv);
}

static void
set_heads_count                         (Monster *monster,
                                         guint count)
{
        monster->priv->heads_count = count;
}

static guint
get_heads_count                         (Monster *monster)
{
        return monster->priv->heads_count;
}

static void
describe                                (Monster *monster)
{
        g_printf ("I'm a monster with %d heads\n", monster->priv->heads_count);
}

GToyObjectType*                   
monster_get_type                        (void)
{
        static GToyObjectType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_object_type_new ();

                gtoy_object_type_set_name (type, "Monster");
                gtoy_object_type_set_init (type, (GToyObjectInitFunc) init);
                gtoy_object_type_set_dispose (type, (GToyObjectDisposeFunc) dispose);
                gtoy_object_type_add_virtual (type, MONSTER_VIRTUAL_SET_HEADS_COUNT, set_heads_count);
                gtoy_object_type_add_virtual (type, MONSTER_VIRTUAL_GET_HEADS_COUNT, get_heads_count);
                gtoy_object_type_add_virtual (type, MONSTER_VIRTUAL_DESCRIBE, describe);
        }
        
        return type;
}

void
monster_set_heads_count                 (Monster *monster, 
                                         guint count)
{
        MonsterSetHeadsCountFunc func = gtoy_object_get_top_method (monster, MONSTER_TYPE, 
                                                                    MONSTER_VIRTUAL_SET_HEADS_COUNT);
        g_return_if_fail (func != NULL);
        func (monster, count);
}

guint
monster_get_heads_count                 (Monster *monster)
{
        MonsterGetHeadsCountFunc func = gtoy_object_get_top_method (monster, MONSTER_TYPE, 
                                                                    MONSTER_VIRTUAL_GET_HEADS_COUNT);
        g_return_if_fail (func != NULL);
        return func (monster);
}


void
monster_describe                        (Monster *monster)
{
        MonsterDescribeFunc func = gtoy_object_get_top_method (monster, MONSTER_TYPE, \
                                                               MONSTER_VIRTUAL_DESCRIBE);
        g_return_if_fail (func != NULL);
        func (monster);
}

