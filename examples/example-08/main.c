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

#include                                <gtoy.h>
#include                                "monster.h"
#include                                "dragon.h"

int                             
main                                    (int argc, 
                                         char **argv)
{
        Monster *monster = gtoy_object_new (MONSTER_TYPE, Monster);
        monster_set_heads_count (monster, 3);
       
        Monster *dragon = gtoy_object_new (DRAGON_TYPE, Dragon);
        monster_set_heads_count (dragon, 12);
        
        monster_describe (monster);
        monster_describe (dragon);

        gtoy_object_unref (dragon);
        gtoy_object_unref (monster);

        return 0;
}
