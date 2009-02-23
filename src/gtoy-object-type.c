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

#include                                "gtoy-object-type.h"
#include                                "gtoy-magic.h"
#include                                "gtoy-errors.h"

/* Static decls */

static void
grow_tables                             (GToyObjectType *type, 
                                         guint16 new_size);

static void                 
add_method                              (GToyObjectType *type, 
                                         guint16 pos, 
                                         gpointer method);

static void                 
grow_interface_tables                   (GToyObjectType *type, 
                                         guint16 new_size);

/* Static impl */

static void
add_method                              (GToyObjectType *type, 
                                         guint16 pos, 
                                         gpointer method)
{
        g_assert (gtoy_object_type_is (type));
        
        if (pos >= type->method_table_size) 
                grow_tables (type, pos + 1);

        type->method_table [pos] = method;
        type->method_jump_table [pos] = type;
}

static void
grow_interface_tables                   (GToyObjectType *type, 
                                         guint16 new_size)
{
        // FIXME Zeroify the new memory?

        g_assert (gtoy_object_type_is (type));
        g_assert (new_size > type->interfaces_size);

        size_t bytes_needed = sizeof (gpointer) * new_size;

        type->interfaces = g_realloc (type->interfaces, bytes_needed);
        type->interfaces_size = new_size;
}

static void
grow_tables                             (GToyObjectType *type, 
                                         guint16 new_size)
{
        // FIXME Zeroify the new memory

        g_assert (gtoy_object_type_is (type));
        g_assert (new_size > type->method_table_size);

        size_t bytes_needed = sizeof (gpointer) * new_size;

        type->method_table = g_realloc (type->method_table, bytes_needed);
        type->method_jump_table = g_realloc (type->method_jump_table, bytes_needed);
        type->method_table_size = new_size;
}

/* Public functions */

GToyObjectType*                 
gtoy_object_type_new                    (void)
{
        GToyObjectType *type = g_new (GToyObjectType, 1);

        type->magic = GTOY_OBJECT_TYPE_MAGIC;
        type->name = "Undefined";
        type->familly = NULL;
        type->parent = NULL;
        type->familly_size = 0;
        type->method_table = 0;
        type->method_jump_table = 0;
        type->method_start = 0;
        type->method_table_size = 0;
        type->dispose_func = NULL;
        type->init_func = NULL;
        type->interfaces_size = 0;
        type->interfaces = NULL;

        return type;
}

void                            
gtoy_object_type_set_name               (GToyObjectType *type, 
                                         const char *name)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (name != NULL, GTOY_ERROR_NULL_OBJECT_TYPE_NAME);

        type->name = name;
}

void                            
gtoy_object_type_set_dispose            (GToyObjectType *type, 
                                         GToyObjectDisposeFunc func)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (func != NULL, 
                             GTOY_ERROR_NULL_DISPOSE_FUNCTION, 
                             type->name);

        type->dispose_func = func;
}

void                            
gtoy_object_type_set_init               (GToyObjectType *type, 
                                         GToyObjectInitFunc func)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (func != NULL, 
                             GTOY_ERROR_NULL_INIT_FUNCTION, 
                             type->name);

        type->init_func = func;
}

void                            
gtoy_object_type_add_interface          (GToyObjectType *type, 
                                         GToyInterfaceType *interface)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (gtoy_interface_type_is (interface), GTOY_ERROR_INVALID_INTERFACE_TYPE);
        gtoy_return_if_fail (! gtoy_object_type_implements (type, interface), 
                             GTOY_ERROR_INTEFACE_IMPLEMENTED, 
                             type->name, interface->name);
        
        // Allocate and fill the info struct
        GToyInterfaceInfo *info = g_new (GToyInterfaceInfo, 1);

        // Fill-in the info struct
        info->interface_type = interface;
        info->methods = g_malloc (sizeof (gpointer) * interface->method_count);

        // Put the info into our table
        grow_interface_tables (type, type->interfaces_size + 1);
        type->interfaces [type->interfaces_size - 1] = info;
}

void                            
gtoy_object_type_implement              (GToyObjectType *type, 
                                         GToyInterfaceType *interface, 
                                         guint16 pos, 
                                         gpointer func)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (gtoy_interface_type_is (interface), GTOY_ERROR_INVALID_INTERFACE_TYPE);
        gtoy_return_if_fail (gtoy_object_type_implements (type, interface), 
                             GTOY_ERROR_INTEFACE_UNIMPLEMENTED, 
                             type->name, interface->name);
        gtoy_return_if_fail (pos < interface->method_count, 
                             GTOY_ERROR_INVALID_INTERFACE_METHOD,
                             interface->name, pos);

        // FIXME Check if interface is not alreay implementing that func
        // FIXME Can run till NULL once we introduce that
        // FIXME Move to one function?
        
        guint16 i;
        for (i = 0; i < type->interfaces_size; i++) 
                if (type->interfaces [i]->interface_type == interface) {
                        type->interfaces [i]->methods [pos] = func;
                        return;
                }
}

void                            
gtoy_object_type_set_parent             (GToyObjectType *type, 
                                         GToyObjectType *parent)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (gtoy_object_type_is (parent), GTOY_ERROR_INVALID_PARENT_OBJECT_TYPE);
        gtoy_return_if_fail (type->parent == NULL, 
                             GTOY_ERROR_ALREADY_HAS_PARENT, 
                             type->name, type->parent->name);

        // FIXME Check if method tables are not touched yet
        // FIXME Check tables (if not added yet)
        // FIXME Check if nothing added to interface tables
        // FIXME Terminate interfaces with NULL

        // Allocate enough memory. We add +1 as we're NULL-terminated
        size_t size = sizeof (gpointer) * (parent->familly_size + 1); 
        
        type->familly = g_malloc (size + sizeof (gpointer)); 
        type->familly [0] = parent;
        
        // Fill-in the familly field
        if (parent->familly == NULL) 
                type->familly [1] = NULL;
        else 
                g_memmove (type->familly + 1, 
                           parent->familly, size);

        // Other fields
        type->parent = parent;
        type->familly_size = parent->familly_size + 1;

        if (parent->method_table_size > type->method_table_size)
                grow_tables (type, parent->method_table_size);

        if (parent->method_table_size > 0) {
                g_memmove (type->method_table, parent->method_table, 
                           sizeof (gpointer) * parent->method_table_size);
                g_memmove (type->method_jump_table, parent->method_jump_table, 
                           sizeof (gpointer) * parent->method_table_size);
        }

        type->method_table_size = parent->method_table_size;
        type->method_start = parent->method_table_size;

        // Copy the interfaces table
        if (parent->interfaces_size > 0) {
                grow_interface_tables (type, parent->interfaces_size);

                g_memmove (type->interfaces, parent->interfaces, 
                           parent->interfaces_size * sizeof (gpointer));

                type->interfaces_size = parent->interfaces_size;
        }

}

guint16                         
gtoy_object_type_familly_size           (GToyObjectType *type)
{
        gtoy_return_val_if_fail (gtoy_object_type_is (type), 0, GTOY_ERROR_INVALID_OBJECT_TYPE);

        return type->familly_size;
}

GToyObjectType*                 
gtoy_object_type_get_parent             (GToyObjectType *type)
{
        gtoy_return_val_if_fail (gtoy_object_type_is (type), NULL, GTOY_ERROR_INVALID_OBJECT_TYPE);

        return type->parent;
}

gboolean                        
gtoy_object_type_as                     (GToyObjectType *type, 
                                         GToyObjectType *other)
{
        gtoy_return_val_if_fail (gtoy_object_type_is (type), FALSE, 
                                 GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_val_if_fail (gtoy_object_type_is (other), FALSE, 
                                 GTOY_ERROR_INVALID_OBJECT_TYPE);

        if (type == other)
                return TRUE;
        else if (type->familly_size == 0)
                return FALSE;
        else if (type->parent == other)
                return TRUE;
        else {
                g_assert (type->familly);

                GToyObjectType **pnt = type->familly;
                while (*pnt != NULL) {
                        if (*pnt == other)
                                return TRUE;
                        pnt += sizeof (GToyObjectType*);
                }
        }

        return FALSE;
}

void                            
gtoy_object_type_add_virtual            (GToyObjectType *type, 
                                         guint16 pos, 
                                         gpointer func)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (func != NULL, 
                             GTOY_ERROR_NULL_VIRTUAL_FUNCTION, 
                             type->name);
 
        add_method (type, pos + type->method_start, func);
}

void                            
gtoy_object_type_add_abstract           (GToyObjectType *type, 
                                         guint16 pos)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);

        add_method (type, pos + type->method_start, NULL);
}

void                            
gtoy_object_type_override               (GToyObjectType *type, 
                                         GToyObjectType *base_type, 
                                         guint16 pos, 
                                         gpointer func)
{
        gtoy_return_if_fail (gtoy_object_type_is (type), GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_if_fail (gtoy_object_type_is (base_type), GTOY_ERROR_INVALID_BASE_OBJECT_TYPE);
        gtoy_return_if_fail (func != NULL, 
                             GTOY_ERROR_NULL_OVERRIDEN_FUNCTION, 
                             type->name, pos);
        gtoy_return_if_fail (pos < type->method_table_size, 
                             GTOY_ERROR_INVALID_OBJECT_TYPE_METHOD, 
                             type->name, pos);

        // FIXME Prevent the method from being overriden for the 
        // second time
        
        add_method (type, base_type->method_start + pos, func);
}

gboolean                        
gtoy_object_type_is                     (GToyObjectType *type)
{
        if (type != NULL &&
            type->magic == GTOY_OBJECT_TYPE_MAGIC)
                return TRUE;
        else
                return FALSE;
}


gboolean
gtoy_object_type_implements             (GToyObjectType *type, 
                                         GToyInterfaceType *interface)
{
        gtoy_return_val_if_fail (gtoy_object_type_is (type), FALSE, 
                                 GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_val_if_fail (gtoy_interface_type_is (interface), FALSE, 
                                 GTOY_ERROR_INVALID_INTERFACE_TYPE);

        if (type->interfaces_size == 0)
                return FALSE;

        // FIXME Can run till NULL once we introduce that
        guint16 i;
        for (i = 0; i < type->interfaces_size; i++) 
                if (type->interfaces [i]->interface_type == interface)
                        return TRUE;

        return FALSE;
}

