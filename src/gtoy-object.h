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

#ifndef                                 ___GTOY_OBJECT_H___
#define                                 ___GTOY_OBJECT_H___

#include                                <glib.h>
#include                                "gtoy-types.h"
#include                                "gtoy-object-type.h"
#include                                "gtoy-macros.h"

G_BEGIN_DECLS

#define                                 gtoy_object_new(type,str) \
                                        gtoy_object_new_with_size (type, sizeof(str))

gpointer                       
gtoy_object_new_with_size               (GToyObjectType *type, gsize size);

gpointer                        
gtoy_object_get_top_method              (gpointer object, 
                                         GToyObjectType *type, 
                                         guint16 pos);

gpointer                        
gtoy_object_get_base_method             (gpointer object, 
                                         GToyObjectType *type,
                                         GToyObjectType *current_type,
                                         guint16 pos);
gpointer
gtoy_object_get_interface_method        (gpointer object, 
                                         GToyInterfaceType *type, 
                                         guint16 pos);

gpointer                        
gtoy_object_ref                         (gpointer object);

void                            
gtoy_object_unref                       (gpointer object);

gboolean
gtoy_object_is                          (gpointer object);

gboolean
gtoy_object_as                          (gpointer object, 
                                         GToyObjectType *type);

gboolean
gtoy_object_implements                  (gpointer object,
                                         GToyInterfaceType *type);

G_END_DECLS

#endif                                  /* ___GTOY_OBJECT_H___ */
