
#include <freewpc.h>
#include "system/platform.h"
#include "native/gpio.h"

/* RTTX(name=triac_rtt   freq=1) */
/* RTTX(name=pinio_active_led_toggle   freq=64) */
/* RTTX(name=sound_write_rtt   freq=2) */


#ifndef CONFIG_SIM
void writeb (IOPTR ptr, U8 val)
{
	switch (ptr)
	{
		case IO_LAMP:
			gpio_write_led (0, val & 1);
			gpio_write_led (1, val & 2);
			gpio_write_led (2, val & 4);
			gpio_write_led (3, val & 8);
			break;
	}
}

U8 readb (IOPTR ptr)
{
	U8 val = 0;
	//printf ("readb(%X) -> %X\n", ptr, val);
	return val;
}
#endif

/* RTT(name=switch_rtt freq=2) */
void switch_rtt (void)
{
	platform_switch_input (0, readb (IO_SWITCH));
	platform_switch_debounce (0);
}

/* RTT(name=lamp_rtt freq=16) */
void lamp_rtt (void)
{
	writeb (IO_LAMP, platform_lamp_compute (0));
}

/* RTT(name=sol_update_rtt_0 freq=1) */
void sol_update_rtt_0 (void)
{
	pinio_write_solenoid_set (0, *sol_get_read_reg (0));
}

void sol_update_rtt_1 (void)
{
}

void platform_init (void)
{
	/* Request GPIOs */
}

