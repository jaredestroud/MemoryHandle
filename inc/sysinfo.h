//
// Created by dllcoolj on 8/12/20.
//

#ifndef MEMFD_SYSINFO_H
#define MEMFD_SYSINFO_H

#include <string>
#include <sys/utsname.h>
#include <unistd.h>

class sysinfo {
    public:
        sysinfo();
        ~sysinfo();
        struct getinfo {
            int pid;
            int uid;
            int euid;
            struct utsname kernel_info;
        };
        void id_system(getinfo &currprogram_struct);
};


#endif //MEMFD_SYSINFO_H
