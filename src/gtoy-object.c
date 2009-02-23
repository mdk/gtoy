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

#include                                "gtoy-object.h"
#include                                "gtoy-magic.h"
#include                                "gtoy-errors.h"

/* Static decls */

static void                            
run_dispose                             (GToyObject *object);

static void                            
free_object                             (GToyObject *object);

static gboolean                          
run_init                                (GToyObject *object);

static gpointer                       
run_inits_backwards                     (GToyObject *object, 
                                         GToyObjectType **first, 
                                         GToyObjectType **last);

static void                            
run_disposes_forwards                   (GToyObject *object, 
                                         GToyObjectType **first, 
                                         GToyObjectType **last);

/* Static impl */

static gpointer                       
run_inits_backwards                     (GToyObject *object, 
                                         GToyObjectType **first, 
                                         GToyObjectType **last)
{
        // FIXME Pedantic test -- first != NULL

        GToyObjectType **current = last;

        while (current >= first) {

                GToyObjectType *type = *current;
                // FIXME Pedantic test for NULL

                if (type->init_func != NULL &&
                    type->init_func (object) == FALSE) 
                        return current;

                // We move backwards
                current -= 1;
        }

        return NULL;
}

static void                            
run_dispose                             (GToyObject *object)
{
        // FIXME Pedantic check if is object
        // FIXME Pedantic check if disposed == FALSE

        object->disposed = TRUE;

        // Now run the dispose function on all types of this obj
        GToyObjectType *type = object->type;
        while (type != NULL) {
                if (type->dispose_func != NULL)
                        type->dispose_func (object);
                type = type->parent;
        }

        // Free all the object structure
        free_object (object);
}

static void                            
run_disposes_forwards                   (GToyObject *object, 
                                         GToyObjectType **first, 
                                         GToyObjectType **last)
{
        // FIXME Pedantic test for disposed
        // FIXME Pedantic test for object

        object->disposed = TRUE;
        GToyObjectType **current = first;

        // Run using the list
        while (current <= last) {
                GToyObjectType *type = *current;
                if (type->dispose_func != NULL)
                        type->dispose_func (object);
                current += 1;
        }

        // Free all the object structure
        free_object (object);
}

static gboolean
run_init                                (GToyObject *object)
{
        // FIXME Pedantic test is object
        // FIXME Pedantic test for object familly/parent
        // FIXME Remove the printf!
        
        // Run for all the objects in the familly
        if (object->type->familly_size > 0) {
                GToyObjectType **first = object->type->familly;
                GToyObjectType **last = object->type->familly + 
                                        object->type->familly_size - 1;

                GToyObjectType **dispose_from = run_inits_backwards (object, first, last);
                if (dispose_from != NULL) {
                        run_disposes_forwards (object, dispose_from, last);
                        return FALSE;
                }
        }

        // And now actually try to run the init function for THIS 
        // object...
        if (object->type->init_func != NULL && 
            object->type->init_func (object) == FALSE) {
                run_dispose (object);
                return FALSE;
        }

        return TRUE;
}

static void                            
free_object                             (GToyObject *object)
{
        g_assert (object != NULL);
        g_assert (object->magic == GTOY_OBJECT_MAGIC);
        g_assert (object->disposed == TRUE);

        object->magic = 0;
        object->type = NULL;

        g_free (object);
}

/* Public */

gpointer                       
gtoy_object_new_with_size               (GToyObjectType *type, gsize size)
{
        gtoy_return_val_if_fail (gtoy_object_type_is (type), NULL, 
                                 GTOY_ERROR_INVALID_OBJECT_TYPE);
        gtoy_return_val_if_fail (size > 0, NULL, 
                                 GTOY_ERROR_NULL_OBJECT_SIZE);

        GToyObject *object = g_malloc (size);

        object->magic = GTOY_OBJECT_MAGIC;
        object->type = type;
        object->ref_count = 1;
        object->disposed = FALSE;

        // Try running the init...
        if (run_init (object))
                return object;
        else
                return NULL;
}

gpointer                       
gtoy_object_ref                         (gpointer object)
{
        gtoy_return_val_if_fail (gtoy_object_is (object), NULL, 
                                 GTOY_ERROR_INVALID_OBJECT);

        GToyObject *obj = (GToyObject *) object;
        obj->ref_count++;

        return  object;
}

void                            
gtoy_object_unref                       (gpointer object)
{
        gtoy_return_if_fail (object != NULL, 
                             GTOY_ERROR_INVALID_OBJECT);
        GToyObject *obj = (GToyObject *) object;
        gtoy_return_if_fail (obj->magic == GTOY_OBJECT_MAGIC, 
                             GTOY_ERROR_INVALID_OBJECT);
        // FIXME Why do we use a custom here?

        // Silently exit if already disposed
        if (obj->disposed)
                return;

        if (obj->ref_count > 0)
                obj->ref_count--;

        if (obj->ref_count == 0)
                run_dispose (obj);
}

gpointer                       
gtoy_object_get_top_method              (gpointer object, 
                                         GToyObjectType *type, 
                                         guint16 pos)
{
        gtoy_return_val_if_fail (gtoy_object_is (object), NULL, 
                                 GTOY_ERROR_INVALID_OBJECT);
        gtoy_return_val_if_fail (gtoy_object_type_is (type), NULL, 
                                 GTOY_ERROR_INVALID_OBJECT_TYPE);
      
        GToyObject *obj = (GToyObject *) object;

        gtoy_return_val_if_fail (gtoy_object_type_as (obj->type, type), 
                                 NULL, 
                                 GTOY_ERROR_INVALID_CAST, 
                                 obj->type->name, 
                                 type->name);

        guint16 method = type->method_start + pos;
        GToyObjectType *type_to_use = obj->type->method_jump_table [method];
      
        g_assert (type_to_use->method_table [method]);
        return type_to_use->method_table [method];
}

gpointer                       
gtoy_object_get_interface_method        (gpointer object, 
                                         GToyInterfaceType *type, 
                                         guint16 pos)
{
        GToyObject *obj = (GToyObject *) object;

        gtoy_return_val_if_fail (gtoy_object_is (object), NULL, 
                                 GTOY_ERROR_INVALID_OBJECT);
        gtoy_return_val_if_fail (gtoy_interface_type_is (type), NULL,
                                 GTOY_ERROR_INVALID_INTERFACE_TYPE);
        
        gtoy_return_val_if_fail (gtoy_object_implements (object, type), NULL,
                                 GTOY_ERROR_INVALID_CAST, 
                                 obj->type->name, type->name);
       
        // FIXME Can run till NULL once we introduce that
        // FIXME Move to one function?
        // FIXME What about an situation, when the interface is implemented
        //       but the function is not?
        
        guint16 i;
        for (i = 0; i < obj->type->interfaces_size; i++) 
                if (obj->type->interfaces [i]->interface_type == type)
                        return obj->type->interfaces [i]->methods [pos];

        return NULL;
}

gpointer                       
gtoy_object_get_base_method             (gpointer object, 
                                         GToyObjectType *type, 
                                         GToyObjectType *current_type,
                                         guint16 pos)
{
        gtoy_return_val_if_fail (gtoy_object_is (object), NULL, 
                                 GTOY_ERROR_INVALID_OBJECT);
       
        gtoy_return_val_if_fail (gtoy_object_type_is (type), NULL, 
                                 GTOY_ERROR_INVALID_BASE_OBJECT_TYPE);
        
        // FIXME Check if we have parent
        // FIXME Check if we implement that object actually

        GToyObject *obj = (GToyObject *) object;
        guint16 method = type->method_start + pos;
        GToyObjectType *type_to_use = current_type->parent->method_jump_table [method];
        return type_to_use->method_table [method];
}

gboolean
gtoy_object_is                          (gpointer object)
{
        GToyObject *obj = (GToyObject *) object;
        if (obj != NULL &&
            obj->magic == GTOY_OBJECT_MAGIC && 
            obj->type != NULL &&
            obj->disposed == FALSE)
                return TRUE;
        else
                return FALSE;
}

gboolean
gtoy_object_as                          (gpointer object, 
                                         GToyObjectType *type)
{
        gtoy_return_val_if_fail (gtoy_object_is (object), FALSE, 
                                 GTOY_ERROR_INVALID_OBJECT);

        gtoy_return_val_if_fail (gtoy_object_type_is (type), FALSE, 
                                 GTOY_ERROR_INVALID_OBJECT_TYPE);

        return gtoy_object_type_as (((GToyObject *) object)->type, type);
}

gboolean
gtoy_object_implements                  (gpointer object,
                                         GToyInterfaceType *type)
{
        gtoy_return_val_if_fail (gtoy_object_is (object), FALSE, 
                                 GTOY_ERROR_INVALID_OBJECT);

        gtoy_return_val_if_fail (gtoy_interface_type_is (type), FALSE, 
                                 GTOY_ERROR_INVALID_INTERFACE_TYPE);

        return gtoy_object_type_implements (((GToyObject *) object)->type, type);
}

