#include "../../shared/controller/input/InputHandler.h"
#include "../../shared/io/uart/uart.h"
#include "../../shared/util.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/wdt.h>
#include <util/delay.h>
extern "C" {
#include "pins.h"
}

InputHandler controller;

size_t controller_index = 0;
bool done = false;
int main() {
  UBRR0 = 6;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(UDRIE0);
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  // Notify the usb processor so that it knows we are about to wait for the
  // config
  while (!bit_is_set(UCSR0A, RXC0)) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = 0xFE;
  }
  for (size_t i = 0; i < sizeof(config_t); i++) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    ((uint8_t *)&config)[i] = UDR0;
  }
  controller.init();
  sei();
  while (true) {
    controller.process();
    if (bit_is_set(UCSR0A, RXC0)) {
      if (UDR0 == 0xEF) {
        wdt_enable(WDTO_120MS);
      }
    }
  }
}
ISR(USART_UDRE_vect) {
  if (controller_index < 2) {
    UDR0 = controller_index == 0 ? 'm' : 'a';
  } else {
    UDR0 = ((uint8_t *)&controller.controller)[controller_index - 2];
  }
  controller_index++;
  if (controller_index >= sizeof(Controller) + 2) {
    controller_index = 0;
  }
}

extern "C" void before_reboot() {}