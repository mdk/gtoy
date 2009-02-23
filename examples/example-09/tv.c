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

#include                                "tv.h"

struct                                  _TvPrivate
{
        Dispatcher *channel_changed;
        guint channel;
};

static gboolean
init                                    (Tv *tv)
{
        tv->priv = g_malloc (sizeof (TvPrivate));
        tv->priv->channel_changed = gtoy_object_new (DISPATCHER_TYPE, Dispatcher);
        tv->priv->channel = 1;

        return (tv->priv->channel_changed != NULL);
}

static void
dispose                                 (Tv *tv)
{
        if (tv->priv == NULL)
                return;

        if (tv->priv->channel_changed != NULL)
                gtoy_object_unref (tv->priv->channel_changed);

        g_free (tv->priv);
        tv->priv = NULL;
}

GToyObjectType*                   
tv_get_type                             (void)
{
        static GToyObjectType *type = NULL;
        
        if (type == NULL) {
                type = gtoy_object_type_new ();

                gtoy_object_type_set_name (type, "Tv");
                gtoy_object_type_set_init (type, (GToyObjectInitFunc) init);
                gtoy_object_type_set_dispose (type, (GToyObjectDisposeFunc) dispose);
        }
        
        return type;
}

void
tv_set_channel                          (Tv *tv, 
                                         guint channel)
{
        g_return_if_fail (gtoy_object_as (tv, TV_TYPE));
        tv->priv->channel = channel;

        TvChannelChangedFunc func = dispatcher_iterator_reset (tv->priv->channel_changed);
        while (func != NULL) {
                func (tv, channel);
                func = dispatcher_iterator_next (tv->priv->channel_changed);
        }
}

guint
tv_get_channel                          (Tv *tv)
{
        g_return_val_if_fail (gtoy_object_as (tv, TV_TYPE), 0);
        return tv->priv->channel;
}

Dispatcher*
tv_channel_changed_dispatcher           (Tv *tv)
{
        g_return_val_if_fail (gtoy_object_as (tv, TV_TYPE), NULL);
        return tv->priv->channel_changed;
}



