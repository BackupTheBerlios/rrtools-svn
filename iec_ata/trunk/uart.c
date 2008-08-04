/* USART-Init beim ATmegaXX */


#include <avr/io.h>
#include <stdlib.h>



#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define UDR UDR0
#define UBRRH UBRR0H
#define UBRRL UBRR0L
#define URSEL UMSEL0
#define TXEN TXEN0
#define UMSEL UMSEL0
#define UCSZ0 UCSZ00
#define RXEN RXEN0
#define UCSRA UCSR0A
#define UDRE UDRE0
#define RXC RXC0


#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_CPU)/((UART_BAUD_RATE)*16L)-1)

#define UART_BAUD_RATE 19200


void uart_init() {
	PORTD |= 0x01;				//Pullup an RXD an

	UCSRB |= (1<<TXEN);			//UART TX einschalten
	UCSRC |= (1<<URSEL)|(3<<UCSZ0);		//Asynchron 8N1

	UCSRB |= (1<<RXEN);			//Uart RX einschalten

	UBRRH=(uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_CPU)>>8);
	UBRRL=(uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_CPU));
}

void uart_putc(char c) {
	while (!(UCSRA & (1<<UDRE))); /* warten bis Senden moeglich                   */
	UDR = c;                      /* schreibt das Zeichen x auf die Schnittstelle */
}

void uart_putstr(char *str) {
	while(*str) {
		uart_putc(*str++);
	}
}

void uart_putstr_P(PGM_P str) {
	char tmp;
	while((tmp = pgm_read_byte(str))) {
		uart_putc(tmp);
		str++;
	}
}

void uart_hexdump(char *buf, int len)
{
	unsigned char x=0, sbuf[3];

	while(len--){
		itoa(*buf++, sbuf, 16);
		if (sbuf[1] == 0) uart_putc(' ');
		uart_putstr(sbuf);
		uart_putc(' ');
		if(++x == 16) {
			uart_putstr_P(PSTR("\r\n"));
			x = 0;
		}
	}
}

char uart_getc()
{
	while (!(UCSRA & (1<<RXC)));	// warten bis Zeichen verfuegbar
	return UDR;			// Zeichen aus UDR zurueckgeben
}

// returns 1 on success
char uart_getc_nb(char *c)
{
	if (UCSRA & (1<<RXC)) {		// Zeichen verfuegbar
		*c = UDR;
		return 1;
	}

	return 0;
}
