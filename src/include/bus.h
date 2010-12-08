/**
 * Copyright (C) 2009-2010, Shao Miller <shao.miller@yrdsb.edu.on.ca>.
 * Copyright 2006-2008, V.
 * For WinAoE contact information, see http://winaoe.org/
 *
 * This file is part of WinVBlock, derived from WinAoE.
 *
 * WinVBlock is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WinVBlock is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WinVBlock.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _BUS_H
#  define _BUS_H

/**
 * @file
 *
 * Bus specifics.
 */

struct bus__type {
    device__type_ptr device;
    PDEVICE_OBJECT LowerDeviceObject;
    PDEVICE_OBJECT PhysicalDeviceObject;
    winvblock__uint32 Children;
    device__type_ptr first_child_ptr;
    KSPIN_LOCK SpinLock;
    LIST_ENTRY tracking;
    winvblock__any_ptr ext;
    device__free_func * prev_free;
    UNICODE_STRING dev_name;
    UNICODE_STRING dos_dev_name;
    winvblock__bool named;
  };

extern NTSTATUS STDCALL bus__get_dev_capabilities(
    IN PDEVICE_OBJECT,
    IN PDEVICE_CAPABILITIES
  );

extern NTSTATUS bus__module_init(void);
extern void bus__module_shutdown(void);

/**
 * Create a new bus.
 *
 * @ret bus_ptr         The address of a new bus, or NULL for failure.
 *
 * This function should not be confused with a PDO creation routine, which is
 * actually implemented for each device type.  This routine will allocate a
 * bus__type, track it in a global list, as well as populate the bus
 * with default values.
 */
extern winvblock__lib_func struct bus__type * bus__create(void);

/**
 * Add a child node to the bus.
 *
 * @v bus_ptr           Points to the bus receiving the child.
 * @v dev_ptr           Points to the child device to add.
 *
 * Returns TRUE for success, FALSE for failure.
 */
extern winvblock__lib_func winvblock__bool STDCALL bus__add_child(
    IN OUT struct bus__type * bus_ptr,
    IN device__type_ptr dev_ptr
  );

/**
 * Get a pointer to the bus device's extension space.
 *
 * @ret         A pointer to the bus device's extension space, or NULL.
 */
extern winvblock__lib_func struct bus__type * bus__boot(void);

extern winvblock__lib_func struct bus__type * bus__get(device__type_ptr dev);

#endif  /* _BUS_H */
