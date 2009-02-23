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

#ifndef                                 ___GTOY_ERRORS_H___
#define                                 ___GTOY_ERRORS_H___

#include                                <glib.h>

G_BEGIN_DECLS

#define                                 GTOY_ERROR_INVALID_OBJECT_TYPE \
                                        "Invalid object type"

#define                                 GTOY_ERROR_INVALID_INTERFACE_TYPE \
                                        "Invalid interface type"

#define                                 GTOY_ERROR_NULL_OBJECT_TYPE_NAME \
                                        "Object type name cannot be NULL"

#define                                 GTOY_ERROR_NULL_INTERFACE_TYPE_NAME \
                                        "Interface type name cannot be NULL"

#define                                 GTOY_ERROR_NULL_VIRTUAL_FUNCTION \
                                        "%s virtual function cannot be null"

#define                                 GTOY_ERROR_NULL_DISPOSE_FUNCTION \
                                        "%s type dispose function cannot be NULL"

#define                                 GTOY_ERROR_NULL_INIT_FUNCTION \
                                        "%s type init function cannot be NULL"

#define                                 GTOY_ERROR_NULL_OVERRIDEN_FUNCTION \
                                        "Cannot override %s method id %d with NULL"

#define                                 GTOY_ERROR_NULL_OBJECT_SIZE \
                                        "Cannot create new object with size 0"

#define                                 GTOY_ERROR_INTEFACE_UNIMPLEMENTED \
                                        "Object type %s doesn't implement interface %s"

#define                                 GTOY_ERROR_INTEFACE_IMPLEMENTED \
                                        "Object type %s already implements interface %s"

#define                                 GTOY_ERROR_INVALID_CAST \
                                        "Object type %s cannot be used as %s"

#define                                 GTOY_ERROR_INVALID_INTERFACE_METHOD \
                                        "%s interface doesn't provide method id %d"

#define                                 GTOY_ERROR_INVALID_OBJECT_TYPE_METHOD \
                                        "%s object type doesn't provide method id %d"

#define                                 GTOY_ERROR_ALREADY_HAS_PARENT \
                                        "%s object type already has parent %s"

#define                                 GTOY_ERROR_INVALID_PARENT_OBJECT_TYPE \
                                        "Invalid parent object type"

#define                                 GTOY_ERROR_INVALID_BASE_OBJECT_TYPE \
                                        "Invalid base object type"

#define                                 GTOY_ERROR_INVALID_OBJECT \
                                        "Invalid object"

G_END_DECLS

#endif                                  /* ___GTOY_ERRORS_H___ */
