#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>



#define DEVICE	"/dev/input/event0"
int main(int argc, char **argv)
{
	int fd, version;
	struct input_id dev_info;

	fd = open(DEVICE, O_RDWR);
	if( 0 > fd) {
		perror("opening "DEVICE" failed");
	}

	printf("%s opened succesfully\n", DEVICE);

	ioctl(fd, EVIOCGVERSION, &version);

	printf("evdev driver version is : %d.%d.%d\n", \
	       (version >> 16) & 0xff , (version >> 8 ) & 0xff, version & 0xff);

	if( ioctl(fd, EVIOCGID, &dev_info) ) {
		perror("dev_info");
	}
	printf("Bus ID %04x, Vendor ID: %04x, Product ID: %04x, Verison: %04x\n",
	       dev_info.bustype, dev_info.vendor, dev_info.product, dev_info.version);
	
	
	
  exit:
	close(fd);
	
	return 0;
}
