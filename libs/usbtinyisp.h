enum
{
	// Generic requests
	USBTINY_ECHO,		// echo test
	USBTINY_READ,		// read byte
	USBTINY_WRITE,		// write byte
	USBTINY_CLR,		// clear bit 
	USBTINY_SET,		// set bit
	// Programming requests
	USBTINY_POWERUP,	// apply power (wValue:SCK-period, wIndex:RESET)
	USBTINY_POWERDOWN,	// remove power from chip
	USBTINY_SPI,		// issue SPI command (wValue:c1c0, wIndex:c3c2)
	USBTINY_POLL_BYTES,	// set poll bytes for write (wValue:p1p2)
	USBTINY_FLASH_READ,	// read flash (wIndex:address)
	USBTINY_FLASH_WRITE,	// write flash (wIndex:address, wValue:timeout)
	USBTINY_EEPROM_READ,	// read eeprom (wIndex:address)
	USBTINY_EEPROM_WRITE,	// write eeprom (wIndex:address, wValue:timeout)
	USBTINY_DDRWRITE,        // set port direction
	USBTINY_SPI1            // a single SPI command
};
