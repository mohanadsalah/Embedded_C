#include "uart.h"
unsigned char string_buffer[100]="learn-in-depth:Mohanad_Mohamed";
unsigned char const string_buffer2[100]="learn-in-depth:Mohanad_Mohamed";


void main(void)
{
	Uart_send_string(string_buffer);
}
