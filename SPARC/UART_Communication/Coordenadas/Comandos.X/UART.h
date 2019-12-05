#ifndef UART_HEADER

#define _XTAL_FREQ 8000000L

void UARTConfi(int Baud);
void UARTWrite(char data);
char UARTRead(void);

#endif //UART_HEADER
