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

#include                                <gtoy.h>
#include                                "tv.h"
#include                                "dispatcher.h"

void
on_channel_changed                      (Tv *tv, 
                                         guint channel)
{
        g_printf ("Channel changed to %d\n", channel);
}

int                             
main                                    (int argc, 
                                         char **argv)
{
        Tv *tv = gtoy_object_new (TV_TYPE, Tv);

        dispatcher_add (tv_channel_changed_dispatcher (tv), on_channel_changed);

        g_printf ("About to change channel...\n");
        tv_set_channel (tv, 10);

        gtoy_object_unref (tv);

        return 0;
}
