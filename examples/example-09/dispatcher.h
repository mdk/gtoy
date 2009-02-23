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

#ifndef                                 ___DISPATCHER_H___
#define                                 ___DISPATCHER_H___

#include                                <gtoy.h>

typedef struct                          _DispatcherPrivate DispatcherPrivate;

struct                                  _Dispatcher
{
        GToyObject parent;
        DispatcherPrivate *priv;
} typedef                               Dispatcher;

#define                                 DISPATCHER_TYPE \
                                        dispatcher_get_type ()

GToyObjectType*                   
dispatcher_get_type                     (void);

void
dispatcher_add                          (Dispatcher *dispatcher, 
                                         gpointer func);

void
dispatcher_remove                       (Dispatcher *dispatcher, 
                                         gpointer func);
gpointer
dispatcher_iterator_reset               (Dispatcher *dispatcher);

gpointer
dispatcher_iterator_next                (Dispatcher *dispatcher);

#endif                                  /* ___DISPATCHER_H___ */
