#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "USART.h"
#include "LiquidCrystal_I2C.h"
char *strrev(char *str) 
	{
	char *p1, *p2;

	if (!str || !*str)
		return str;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
}

char *itoa(int n, char *s, int b) 
	{
	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i=0, sign;

	if ((sign = n) < 0)
		n = -n;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	return strrev(s);
}
void displayKeyCodes(void) 
	{
  uint8_t i = 0;
		int j;
		char buf[10];
  while (1) 
		{
    LCDI2C_clear();
    LCDI2C_setCursor(2,2);
    LCDI2C_write_String("Hello MGTOW!");
    LCDI2C_setCursor(0, 0);
	
	itoa(i, buf, 10);
    LCDI2C_write_String("Codes 0x"); LCDI2C_write_String(buf);
	itoa(i+19, buf, 10);
    LCDI2C_write_String("-0x"); LCDI2C_write_String(buf);
    LCDI2C_setCursor(0, 1);
    
    for (j=0; j<20; j++) 
			{
      LCDI2C_write(i+j);
    }
    i+=16;
    if (i<15) break;
    Delay(2000);
  }
}
