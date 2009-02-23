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

#ifndef                                 ___GTOY_MACROS_H___
#define                                 ___GTOY_MACROS_H___

#include                                <glib.h>

G_BEGIN_DECLS

#ifndef                                 GTOY_CLASSIC_WARNINGS

void 
gtoy_return_if_fail_warning             (const gchar *log_domain,
			                 const gchar *pretty_function,
			                 const gchar *str, 
                                         ...);

#define                                 gtoy_return_if_fail(expr, ...) {                          \
                                        if (G_LIKELY(expr)) { } else {                            \
                                                gtoy_return_if_fail_warning (G_LOG_DOMAIN,        \
                                                                             __PRETTY_FUNCTION__, \
                                                                             __VA_ARGS__);        \
                                                return;                                           \
                                        }                                                         \
                                        }

#define                                 gtoy_return_val_if_fail(expr, val, ...) {                 \
                                        if (G_LIKELY(expr)) { } else {                            \
                                                gtoy_return_if_fail_warning (G_LOG_DOMAIN,        \
                                                                             __PRETTY_FUNCTION__, \
                                                                             __VA_ARGS__);        \
                                                return val;                                       \
                                        }                                                         \
                                        }

#else                                   /* GTOY_CLASSIC_WARNINGS */

#define                                 gtoy_return_if_fail(expr, ...) \
                                        g_return_if_fail(expr)

#define                                 gtoy_return_val_if_fail(expr, val, ...) \
                                        g_return_val_if_fail(expr, val)

#endif                                  /* GTOY_CLASSIC_WARNINGS */

G_END_DECLS

#endif                                  /* ___GTOY_MACROS_H___ */
