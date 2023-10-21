#include "usb/usb_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 0 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 0,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

//--------------------------------------------------------------------+
// BLINKING TASK + Indicator pulse
//--------------------------------------------------------------------+


volatile uint8_t doPulse = false;
// called from USB context
void led_indicator_pulse(void) {
	doPulse = true;
}

void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;
  if(blink_interval_ms == BLINK_MOUNTED) // Mounted
  {
    if(doPulse)
    {
      led_state = true;
      board_led_write(true);
      start_ms = board_millis();
      doPulse = false;
    }
    else if (led_state == true)
    {
      if ( board_millis() - start_ms < 750) //Spec says blink must be between 500 and 1000 ms.
      {
        return; // not enough time
      }
      led_state = false;
      board_led_write(false);
    }
  }
  else
  {
    // Blink every interval ms
    if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
    start_ms += blink_interval_ms;

    board_led_write(led_state);
    led_state = 1 - led_state; // toggle
  }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

