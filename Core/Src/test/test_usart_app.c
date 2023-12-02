#include <stdint.h>

int test_usart_app_main(void) {
  uint8_t operate_count = 0;

  APP_UART_StartReceive();
  while (1) {
    APP_UART_OutChar('a');
    APP_UART_OutChar('b');
    APP_UART_OutChar('c');
    APP_UART_OutChar('d');
    APP_UART_OutChar(APP_CHAR_LF);
    // // HAL_GPIO_TogglePin(G_GPIO_Port, G_Pin);
    HAL_Delay(100);

    operate_count++;

    if ((operate_count % 20) == 0) {
      APP_UART_OutChar(APP_CHAR_LF);
      APP_UART_FlushFIFO();
      APP_UART_OutChar(APP_CHAR_LF);
      APP_UART_OutString((uint8_t*) "Hello World! I am Iron Man. You are Venom. Hung bi dep trai");
      APP_UART_OutChar(APP_CHAR_LF);
    }

    // if ((operate_count % 100) == 0) {
    //   APP_UART_FlushFIFO();
    // }
  }
}