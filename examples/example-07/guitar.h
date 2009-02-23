/* GToy Example 07
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

#ifndef                                 ___GUITAR_H___
#define                                 ___GUITAR_H___

#include                                <gtoy.h>
#include                                "instrument.h"

struct                                  _Guitar
{
        Instrument parent;
} typedef                               Guitar;

enum 
{
        GUITAR_VIRTUAL_CHANGE_STRINGS
};

#define                                 GUITAR_TYPE guitar_get_type ()

typedef                                 void (*GuitarChangeStringsFunc) (Guitar *guitar);

GToyObjectType*                   
guitar_get_type                         (void);

void                                    
guitar_change_strings                   (Guitar *guitar);

#endif                                  /* ___GUITAR_H___ */
