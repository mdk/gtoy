/* GToy Example 08
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

#ifndef                                 ___MONSTER_H___
#define                                 ___MONSTER_H___

#include                                <gtoy.h>

typedef struct                          _MonsterPrivate MonsterPrivate;

struct                                  _Monster
{
        GToyObject parent;
        MonsterPrivate *priv;
} typedef                               Monster;

enum
{
        MONSTER_VIRTUAL_SET_HEADS_COUNT,
        MONSTER_VIRTUAL_GET_HEADS_COUNT,
        MONSTER_VIRTUAL_DESCRIBE
};

typedef                                 void (*MonsterSetHeadsCountFunc) 
                                        (Monster *monster, guint count);

typedef                                 guint (*MonsterGetHeadsCountFunc) 
                                        (Monster *monster);

typedef                                 void (*MonsterDescribeFunc) 
                                        (Monster *monster);

#define                                 MONSTER_TYPE \
                                        monster_get_type ()

GToyObjectType*                   
monster_get_type                        (void);

void
monster_set_heads_count                 (Monster *monster, 
                                         guint count);

guint
monster_get_heads_count                 (Monster *monster); 

void
monster_describe                        (Monster *monster);

#endif                                  /* ___MONSTER_H___ */
