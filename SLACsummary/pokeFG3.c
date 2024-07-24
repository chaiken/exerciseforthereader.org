/*
 * this is a user-space program 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include "menable_ioctl.h"
#include "men_ioctl_codes.h"

#define MAXSTRING 256
/*
 * doesnt appear to be defined for userland include files 
 */
#define BITS_PER_LONG 64
#define CURRBUFFSIZE 4096

int
main()
{

    int             returnlen,
                    dev_file = -1;
    const char      dev_file_name[] = "/dev/menable0";
    unsigned int    cmd;
    char            dir = '\0';
    char            type = 'm';
    unsigned size = 0;
    unsigned        nr = 0;

    struct men_io_range range;
/*
 * struct men_io_range {
 * unsigned long start;
 * unsigned long length;
 * long subnr;
 * unsigned int headnr;
 * } __attribute__ ((packed));
 */

    struct men_io_bufidx num;
/*
 * struct men_io_bufidx {
 * unsigned int headnr;
 * long index;
 * }; 
 */

    if ((dev_file = open(dev_file_name, O_RDWR)) < 0) {
	fprintf(stderr, "ERR:on open(%s):%s \n", dev_file_name,
		strerror(errno));
	exit(EXIT_FAILURE);
    } else
	printf("Opening framegrabber file %s with descriptor %d.\n",
	       dev_file_name, dev_file);

/*
 * if (range.length == 0) return -EFAULT;
 * men_create_userbuf(men, &range);
 get_page_addresses(range->start, range->length, &pages);
 get_page_addresses(unsigned long addr, const size_t length, struct page ***pg)
 
 See Robert Love, _Linux Kernel Development 3rd Edition_, p. 316
 struct vm_area_struct *vma;
 vma = find_vma(current->mm, addr);
 len = DIV_ROUND_UP(length + (addr % PAGE_SIZE), PAGE_SIZE);
 *pg = vmalloc(len * sizeof(*pg));
 
 bh = me_get_bh(men, range->headnr, 0);
 if (range->subnr >= bh->num_sb) goto fail_cnt;
 */

    if ((range.start = (unsigned long) mmap(0,CURRBUFFSIZE,PROT_WRITE,MAP_SHARED,dev_file,0)) == (unsigned long) -1){
	fprintf(stderr, "ERR %d from mmap:%s \n", errno, strerror(errno));
	exit(EXIT_FAILURE);
    }
    printf("range.start is %li.\n", range.start);
    range.length = (unsigned long) CURRBUFFSIZE;
    range.subnr = (long) 1;
    range.headnr = (unsigned int) 1;

/*
 * + 128 due to MEN_IOCTL64(ADD_VIRT_USER_BUFFER, 41) 
 */ ;
    nr = IOCTL_ADD_VIRT_USER_BUFFER + 128;	// assumes BITS_PER_LONG > 32 
    /* size = 28;  // 8 + 8 + 8 + 4 */
    size = sizeof(range);
    cmd = (unsigned int) _IOC(dir, type, nr, size);
    printf("_IOR_NR for ADD_VIRT_USER BUFFER is %d and macro is %#0x.\n", _IOC_NR(cmd), _IOC(dir, type, nr, size));
    if ((returnlen = ioctl(dev_file, cmd, &range)) != 0) {
	fprintf(stderr, "ERR:on ioctl: %s\n", strerror(errno));
	free(&range.start);
	close(dev_file);
	exit(EXIT_FAILURE);
    } else {
	printf("Virtual user buffer added.\n");
    }

    num.headnr = (unsigned int) 1;
    num.index = (long) 0;

/*
 * dh = me_get_bh(men, num.headnr, 0);
 * r = men_free_userbuf(men, dh, num.index); 
 * MEN_IOCTL(DEL_VIRT_USER_BUFFER, 44), ==> no +128 
 */
    nr = IOCTL_DEL_VIRT_USER_BUFFER;
    /* size = 12;  // 4 +8 */
    size = sizeof(num);
    cmd = (unsigned int) _IOC(dir, type, nr, size);
    printf("_IOR_NR for DEL_VIRT_USER BUFFER is %d and macro is %#0x.\n",
	   _IOC_NR(cmd), _IOC(dir, type, nr, size));
    if ((returnlen = ioctl(dev_file, cmd, &num)) != 0) {
	fprintf(stderr, "ERR:on ioctl: %s\n", strerror(errno));
	close(dev_file);
	exit(EXIT_FAILURE);
    } else {
	printf("Virtual user buffer deleted.\n");
    }

    /* clean-up*/
    free(&range.start);
    close(dev_file);
    exit(0);
}
