/* GToy Example 09
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

#include                                "dispatcher.h"

struct                                  _DispatcherPrivate
{
        GList *func_list;
        GList *iterator;
};

static gboolean
init                                    (Dispatcher *dispatcher)
{
        dispatcher->priv = g_malloc (sizeof (DispatcherPrivate));
        dispatcher->priv->func_list = NULL;
        dispatcher->priv->iterator = NULL;

        return TRUE;
}

static void
dispose                                 (Dispatcher *dispatcher)
{
        if (dispatcher->priv->func_list == NULL)
                return;

        if (dispatcher->priv->func_list != NULL)
                g_list_free (dispatcher->priv->func_list);

        
        g_free (dispatcher->priv);
        dispatcher->priv = NULL;
}

GToyObjectType*                   
dispatcher_get_type                     (void)
{
        static GToyObjectType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_object_type_new ();

                gtoy_object_type_set_name (type, "Dispatcher");
                gtoy_object_type_set_init (type, (GToyObjectInitFunc) init);
                gtoy_object_type_set_dispose (type, (GToyObjectDisposeFunc) dispose);
        }
        
        return type;
}

void
dispatcher_add                          (Dispatcher *dispatcher, 
                                         gpointer func)
{
        g_return_if_fail (gtoy_object_as (dispatcher, DISPATCHER_TYPE));

        dispatcher->priv->func_list = g_list_append (dispatcher->priv->func_list, func);
        dispatcher->priv->iterator = dispatcher->priv->func_list;
}

void
dispatcher_remove                       (Dispatcher *dispatcher, 
                                         gpointer func)
{
        g_return_if_fail (gtoy_object_as (dispatcher, DISPATCHER_TYPE));

        dispatcher->priv->func_list = g_list_remove (dispatcher->priv->func_list, func);
        dispatcher->priv->iterator = dispatcher->priv->func_list;
}

gpointer
dispatcher_iterator_reset               (Dispatcher *dispatcher)
{
        g_return_val_if_fail (gtoy_object_as (dispatcher, DISPATCHER_TYPE), NULL);
        dispatcher->priv->iterator = dispatcher->priv->func_list;
        if (dispatcher->priv->iterator == NULL)
                return NULL;
        else
                return dispatcher->priv->iterator->data;
}

gpointer
dispatcher_iterator_next                (Dispatcher *dispatcher)
{
        g_return_val_if_fail (gtoy_object_as (dispatcher, DISPATCHER_TYPE), NULL);
        if (dispatcher->priv->iterator == NULL)
                return NULL;

        dispatcher->priv->iterator = g_list_next (dispatcher->priv->iterator);
        if (dispatcher->priv->iterator == NULL)
                return NULL;
        else
                return dispatcher->priv->iterator->data;
}

