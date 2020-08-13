/*
 * MemoryHandle is a toy application to experiment with the MemoryHandle syscalls to make memory backed file descriptors.
 * Refernces:
 *  https://man7.org/linux/man-pages/man2/memfd_create.2.html
 *  https://dvdhrm.wordpress.com/2014/06/10/memfd_create2/ (Author of MemoryHandle)
 *  https://x-c3ll.github.io/posts/fileless-memfd_create/
 *  https://0x00sec.org/t/super-stealthy-droppers/3715
 */

#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include "sysinfo.h"
#include <linux/version.h>

int main() {

    sysinfo sys;
    sysinfo::getinfo info;
    sys.id_system(info);

    // print sys information for debugging/testing on different platform purposes
    std::cout << "[MemoryHandle]\n* Current PID: " << info.pid << std::endl <<
        "\t* UID: "  << info.uid << std::endl <<
        "\t* EUID: " << info.euid << std::endl <<
        "\t* Kernel build: " << info.kernel_info.release << std::endl;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,14,0)
    int fd = memfd_create("",MFD_HUGETLB); // Linux >=  4.14  has support for Huge tables.

#elif (LINUX_VERSION_CODE > KERNEL_VERSION(3 ,17 ,0) ) && (LINUX_VERSION_CODE < KERNEL_VERSION(4 ,14 ,0) )
    // tested on older version of Arch I had laying around...
    #define __NR_memfd_create 319
    int fd = syscall(SYS_memfd_create, "", FD_CLOEXEC);

#else
    std::cout << "[!!!] This kernel version is not supported" << std::endl;
    return 0;
#endif

    if (fd == -1) { // error executing memfd_create
        std::cerr << "[!] Error creating memfd!" << errno << std::endl;
        exit(1);
    }
    std::cout << "[+] Created memfd!\n" << "\t* /proc/" << info.pid << "/fd/" << fd << std::endl;

    pause(); // pause execution so the memfd stays open for use by other applications.
    close(fd);

    return 0;
}