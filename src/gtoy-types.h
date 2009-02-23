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

#ifndef                         ___GTOY_TYPES_H___
#define                         ___GTOY_TYPES_H___

#include                        <glib.h>

G_BEGIN_DECLS

/* Stubs */

typedef struct                  _GToyObjectType GToyObjectType;

typedef struct                  _GToyObject GToyObject;

typedef struct                  _GToyInterfaceType GToyInterfaceType;

typedef struct                  _GToyInterfaceInfo GToyInterfaceInfo;

/* Func decls */

typedef void                    (*GToyObjectDisposeFunc) (GToyObject *object);

typedef gboolean                (*GToyObjectInitFunc) (GToyObject *object);

/* Padding */

#define                         GTOY_PAD_POINTER gpointer

/* Structs */

struct                          _GToyObjectType
{
        guchar magic;
        const gchar *name;
        guint16 familly_size;
        GToyObjectType **familly;
        GToyObjectType *parent;
        gpointer *method_table;
        gpointer *method_jump_table;
        guint16 method_start;
        guint16 method_table_size;
        GToyObjectDisposeFunc dispose_func;
        GToyObjectInitFunc init_func;
        guint16 interfaces_size;
        GToyInterfaceInfo **interfaces;
        GTOY_PAD_POINTER pad1;
        GTOY_PAD_POINTER pad2;
};

struct                          _GToyObject
{
        gchar magic;
        GToyObjectType *type;
        guint16 ref_count;
        gboolean disposed;
        GTOY_PAD_POINTER pad1;
};

struct                          _GToyInterfaceType
{
        gchar magic;
        const gchar *name;
        guint16 method_count;
        GTOY_PAD_POINTER pad1;
};

struct                          _GToyInterfaceInfo
{
        GToyInterfaceType *interface_type;
        gpointer *methods;
};

G_END_DECLS

#endif                          /* ___GTOY_TYPES_H___ */
