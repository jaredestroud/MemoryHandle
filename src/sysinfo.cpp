//
// Created by dllcoolj on 8/12/20.
//

#include "sysinfo.h"

sysinfo::sysinfo() {}
sysinfo::~sysinfo() {}

/*
 * Populate a struct's attributes about current running processes/system information
 * Return: void
 */
void sysinfo::id_system(getinfo &currprogram_struct) {
    currprogram_struct.euid = geteuid();
    currprogram_struct.uid = getuid();
    currprogram_struct.pid = getpid();
    uname(&currprogram_struct.kernel_info); // populate utsname struct with kernel/build info

}
