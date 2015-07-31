#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
 
#include <libusb-1.0/libusb.h>

#define USB_TIMEOUT 500L
#define SCK_PERIOD 1

#include "usbtinyisp.h"
#include "signal_handling.h"

#define USBTINY_VENDOR  0x1781
#define USBTINY_PRODUCT 0x0C9F

libusb_context *def = NULL;
libusb_device_handle *usbtinyisp;

void init (void) {
  atexit (handle_atexit);
  signal (SIGINT, handle_sigint);
  signal (SIGTERM, handle_sigterm);
}

// PB3 - connected to SS

int main (void) {
  init ();
  
  int result = libusb_init (&def);
  if (result != 0) {
    fprintf (stderr, \
	     "Got LIBUSB_ERROR (%d) on libusb_init ..\n", result);
    exit (EXIT_FAILURE);
  }

  usbtinyisp = libusb_open_device_with_vid_pid (def,
						USBTINY_VENDOR,
						USBTINY_PRODUCT);

  if (usbtinyisp == NULL) {
    fprintf (stderr, \
	     "Couldn't find the usbtinyisp, make sure its connected\n");
    exit (EXIT_FAILURE);
  }
  puts ("Found the deivce!");

  char ret[4];
  
  libusb_control_transfer (usbtinyisp, //*dev_handle
  			   0b11000000,       //bmRequestType
  			   USBTINY_SPI, //bRequest
  			   0, // wValue
  			   0, // reset High  //wIndex
  			   ret, // *data
  			   4, // wLength
  			   USB_TIMEOUT);  // timeout

  libusb_control_transfer (usbtinyisp, //*dev_handle
			   0b01000000,       //bmRequestType
			   USBTINY_POWERUP, //bRequest
			   SCK_PERIOD, // wValue
			   0, // reset LOW  //wIndex
			   ret, // *data
			   0, // wLength
			   USB_TIMEOUT); // timeout
  usleep (200000L);
  libusb_control_transfer (usbtinyisp, //*dev_handle
			   0b01000000,       //bmRequestType
			   USBTINY_POWERUP, //bRequest
			   SCK_PERIOD, // wValue
			   1, // reset High  //wIndex
			   ret, // *data
			   4, // wLength
			   USB_TIMEOUT);  // timeout
  // usleep (1);

  usleep (10000L);
  
  while (1) {
    libusb_control_transfer (usbtinyisp, //*dev_handle
			     0b11000000,       //bmRequestType
			     USBTINY_SPI, //bRequest
			     0, // wValue
			     0, // reset High  //wIndex
			     ret, // *data
			     4, // wLength
			     USB_TIMEOUT);  // timeout

    //printf ("%s", ret);

    for (uint8_t j=0; j<4; ++j)
      if (ret[j] != 0x00 && ret[j] != 0x01)
    	printf ("%c", ret[j]);
    fflush (stdout);
  }  

  // atexit
  return EXIT_SUCCESS;
}
