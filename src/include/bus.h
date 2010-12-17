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
#ifndef WV_M_BUS_H_
#  define WV_M_BUS_H_

/**
 * @file
 *
 * Bus specifics.
 */

/**
 * A bus thread routine.
 *
 * @v bus       The bus to be used in the thread routine.
 *
 * If you implement your own bus thread routine, you should call
 * bus__process_work_items() within its loop.
 */
typedef void STDCALL WV_F_BUS_THREAD(IN WV_SP_BUS_T);
typedef WV_F_BUS_THREAD * WV_FP_BUS_THREAD;

/* The bus type. */
typedef struct WV_BUS_T {
    struct device__type * device;
    PDEVICE_OBJECT LowerDeviceObject;
    PDEVICE_OBJECT PhysicalDeviceObject;
    winvblock__uint32 Children;
    struct device__type * first_child;
    KSPIN_LOCK SpinLock;
    LIST_ENTRY tracking;
    winvblock__any_ptr ext;
    device__free_func * prev_free;
    UNICODE_STRING dev_name;
    UNICODE_STRING dos_dev_name;
    winvblock__bool named;
    LIST_ENTRY work_items;
    KSPIN_LOCK work_items_lock;
    KEVENT work_signal;
    WV_FP_BUS_THREAD thread;
    winvblock__bool Stop;
    struct {
        LIST_ENTRY Nodes;
        USHORT NodeCount;
      } BusPrivate_;
  } WV_S_BUS_T, * WV_SP_BUS_T;

/* A child PDO node on a bus.  Treat this as an opaque type. */
typedef struct WV_BUS_NODE {
    struct {
        LIST_ENTRY Link;
        PDEVICE_OBJECT Pdo;
        WV_SP_BUS_T Bus;
      } BusPrivate_;
  } WV_S_BUS_NODE, * WV_SP_BUS_NODE;

/* Exports. */
extern NTSTATUS STDCALL WvBusGetDevCapabilities(
    IN PDEVICE_OBJECT,
    IN PDEVICE_CAPABILITIES
  );
extern winvblock__lib_func void WvBusInit(WV_SP_BUS_T);
extern winvblock__lib_func WV_SP_BUS_T bus__create(void);
extern winvblock__lib_func winvblock__bool STDCALL bus__add_child(
    IN OUT WV_SP_BUS_T,
    IN struct device__type *
  );
extern winvblock__lib_func WV_SP_BUS_T bus__get(struct device__type *);
extern winvblock__lib_func void bus__process_work_items(WV_SP_BUS_T);
extern winvblock__lib_func NTSTATUS bus__start_thread(WV_SP_BUS_T);
extern winvblock__lib_func winvblock__bool STDCALL WvBusInitNode(
    OUT WV_SP_BUS_NODE,
    IN PDEVICE_OBJECT
  );
extern winvblock__lib_func NTSTATUS STDCALL WvBusAddNode(
    WV_SP_BUS_T,
    WV_SP_BUS_NODE
  );
extern winvblock__lib_func NTSTATUS STDCALL WvBusRemoveNode(WV_SP_BUS_NODE);

#endif  /* WV_M_BUS_H_ */
