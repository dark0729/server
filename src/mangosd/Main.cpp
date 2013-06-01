/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/// \addtogroup mangosd Mangos Daemon
/// @{
/// \file


#include "SystemConfig.h"



#include <ace/Get_Opt.h>


#include <iostream>

/// Launch the mangos server
extern int main(int argc, char** argv)
{
    ///- Command line parsing
    char const* cfg_file = _MANGOSD_CONFIG;

    char const* options = ":a:c:s:";

	ACE_Get_Opt cmd_opts(argc, argv, options);

	std::cout << "MANGOS_ENDIAN: " << MANGOS_ENDIAN << " _ENDIAN_STRING:" << _ENDIAN_STRING << std::endl;
	std::cout << "ARCHITECTURE: " << ARCHITECTURE << std::endl;
	std::cout << "_ENDIAN_PLATFORM: " << _ENDIAN_PLATFORM << std::endl;
}




/// @}
