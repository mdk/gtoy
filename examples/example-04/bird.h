/* GToy Example 04
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

#ifndef                                 ___BIRD_H___
#define                                 ___BIRD_H___

#include                                <gtoy.h>
#include                                "flying.h"

struct                                  _Bird
{
        GToyObject parent;
} typedef                               Bird;

enum
{
        BIRD_VIRTUAL_SING
};

#define                                 BIRD_TYPE bird_get_type ()

typedef                                 void (*BirdSingFunc) (Bird *bird);

GToyObjectType*                   
bird_get_type                           (void);

void                            
bird_sing                               (Bird *bird);

#endif                                  /* ___BIRD_H___ */
