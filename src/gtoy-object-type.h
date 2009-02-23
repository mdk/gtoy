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

#ifndef                                 ___CLAY_OBJECT_TYPE_H___
#define                                 ___CLAY_OBJECT_TYPE_H___

#include                                <glib.h>
#include                                "gtoy-types.h"
#include                                "gtoy-interface-type.h"
#include                                "gtoy-macros.h"
#include                                <string.h>

G_BEGIN_DECLS

GToyObjectType*                 
gtoy_object_type_new                    (void);

void                            
gtoy_object_type_set_name               (GToyObjectType *type, 
                                         const gchar *name);

void                            
gtoy_object_type_set_dispose            (GToyObjectType *type, 
                                         GToyObjectDisposeFunc func);

void                            
gtoy_object_type_set_init               (GToyObjectType *type, 
                                         GToyObjectInitFunc func);

void                            
gtoy_object_type_set_parent             (GToyObjectType *type, 
                                         GToyObjectType *parent);

guint16                         
gtoy_object_type_familly_size           (GToyObjectType *type);

gboolean                        
gtoy_object_type_as                     (GToyObjectType *type, 
                                         GToyObjectType *other);

gboolean                        
gtoy_object_type_is                     (GToyObjectType *type);

gboolean
gtoy_object_type_implements             (GToyObjectType *type, 
                                         GToyInterfaceType *interface);

void                            
gtoy_object_type_add_virtual            (GToyObjectType *type, 
                                         guint16 pos, 
                                         gpointer func);

void                            
gtoy_object_type_add_abstract           (GToyObjectType *type, 
                                         guint16 pos);

void                            
gtoy_object_type_add_interface          (GToyObjectType *type, 
                                         GToyInterfaceType *interface);

void                            
gtoy_object_type_override               (GToyObjectType *type, 
                                         GToyObjectType *base_type, 
                                         guint16 pos, 
                                         gpointer func);

void                            
gtoy_object_type_implement              (GToyObjectType *type, 
                                         GToyInterfaceType *interface, 
                                         guint16 pos, 
                                         gpointer func);

G_END_DECLS

#endif                                  /* ___GTOY_OBJECT_TYPE_H___ */
