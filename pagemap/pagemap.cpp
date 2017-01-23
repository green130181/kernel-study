#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

// http://blog.csdn.net/crazycoder8848/article/details/38958075
// https://www.kernel.org/doc/Documentation/vm/pagemap.txt
#define    page_map_file     "/proc/self/pagemap"
#define    PFN_MASK          ((((uint64_t)1)<<55)-1)
#define    PFN_PRESENT_FLAG  (((uint64_t)1)<<63)

int mem_addr_vir2phy(unsigned long vir, unsigned long *phy)
{
    int fd;
    int page_size=getpagesize();
    unsigned long vir_page_idx = vir/page_size;
    unsigned long pfn_item_offset = vir_page_idx*sizeof(uint64_t);
    uint64_t pfn_item;
    
    fd = open(page_map_file, O_RDONLY);
    if (fd<0)
    {
        fprintf(stderr, "open %s failed", page_map_file);
        return -1;
    }

    if ((off_t)-1 == lseek(fd, pfn_item_offset, SEEK_SET))
    {
        fprintf(stderr, "lseek %s failed", page_map_file);
        return -1;
    }

    if (sizeof(uint64_t) != read(fd, &pfn_item, sizeof(uint64_t)))
    {
        fprintf(stderr, "read %s failed", page_map_file);
        return -1;
    }

    if (0==(pfn_item & PFN_PRESENT_FLAG))
    {
        fprintf(stderr, "page is not present");
        return -1;
    }

    *phy = (pfn_item & PFN_MASK)*page_size + vir % page_size;
    return 0;
}

int main(int argc, char* argv[]) {
    unsigned long a = 0xffbbccaa;
    unsigned long vir = reinterpret_cast<unsigned long>(&a);
    unsigned long phy = 0;

    fprintf(stderr, "sizeof(unsigned long):%lu, sizeof(unsigned long*):%lu\n", sizeof(unsigned long), sizeof(unsigned long*));
    mem_addr_vir2phy(vir, &phy);
    fprintf(stderr, "1 vir:0x%lx, phy: 0x%lx getchar to continue\n", vir, phy);
    getchar();
    a = 0x11111111;
    fprintf(stderr, "2 vir:0x%lx, phy: 0x%lx getchar to continue\n", vir, phy);
    getchar();
    fprintf(stderr, "3 vir:0x%lx, phy: 0x%lx a:0x%lx\n", vir, phy, a);
}
