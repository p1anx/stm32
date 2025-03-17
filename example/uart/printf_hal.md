## 1 printf in HAL
```c
#include "stdio.h"
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,0xFFFF);//阻塞方式打印,串口1
  return ch;
}

```
## 2 sprintf（alternative solution)
```c
int a = 11;
float b = 2.2
char buff[10];
sprintf(buff, "a = %d b = %f\n", a, b);
```
if in `platformio`, add `build_flags = -Wl,-u,_printf_float` in `platformio.ini` file

