
#ifndef __SIGNAL_HANDLING__
#define __SIGNAL_HANDLING__

extern libusb_context *def;
extern libusb_device_handle *usbtinyisp;

void handle_sigint (int p) {
  fprintf (stderr, "\nSIGINT called\n");
  while (1) exit (0);
}

void handle_sigterm (int p) {
  fprintf (stderr, "\nSIGTERM called\n");
  while (1) exit (0);
}

void handle_atexit (void) {
  libusb_control_transfer (usbtinyisp, //*dev_handle
			   0b01000000,       //bmRequestType
			   USBTINY_POWERDOWN, //bRequest
			   0, // wValue
			   0, // reset LOW  //wIndex
			   NULL, // *data
			   0, // wLength
			   USB_TIMEOUT);  // timeout
  libusb_close (usbtinyisp);
  libusb_exit (def);
  fflush (stdout);
}

#endif
