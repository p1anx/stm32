# 串口接收中断
1. 启动接收：

- 调用 HAL_UART_Receive_IT(&huartx, RXbuff, sizeof(RXbuff)) 启动接收操作。
- 此函数立即返回HAL_OK，表示接收操作已经启动，但它不会等待所有数据都接收到。

2. 回调函数：
重要：要接收到512个或者1024个字符后，才能触发回调函数。最好是设置BUFFER_SIZE为1时，可以接收任意字符数。如果设置其他固定数量，必须输入同样数量的字符。

- 当接收到一半数据（即512字节）时，UART_RxHalfCpltCallback 回调函数会被调用。
- 当接收到全部数据（即1024字节）时，UART_RxCpltCallback 回调函数会被调用。

## 方式一
```c 
#include "stm32fxxx_hal.h" // 根据您的具体MCU型号替换xxx

#define BUFFER_SIZE 1024

// 定义接收缓冲区
uint8_t RXbuff[BUFFER_SIZE];
volatile uint16_t rx_count = 0; // 用于跟踪接收到的字节数

extern UART_HandleTypeDef huartx;

// 中断回调函数：当接收到一半数据时调用
void UART_RxHalfCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USARTx) { // 根据实际使用的USART外设修改
        printf("Received half of the data (512 bytes).\n");
        // 处理前半部分数据
        // ...
        rx_count += BUFFER_SIZE / 2;
    }
}

// 中断回调函数：当接收到全部数据时调用
void UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USARTx) { // 根据实际使用的USART外设修改
        printf("Received all data (1024 bytes).\n");
        // 处理全部数据
        // ...
        rx_count += BUFFER_SIZE / 2;
        
        // 如果需要继续接收，可以重新启动接收
        HAL_UART_Receive_IT(&huartx, RXbuff, BUFFER_SIZE);
    }
}

// 主函数中启动接收
int main(void) {
    // 初始化HAL库、时钟、GPIO等
    HAL_Init();
    SystemClock_Config(); // 配置系统时钟
    MX_USARTx_UART_Init(); // 初始化串口，根据实际配置修改

    // 启动中断接收
    if (HAL_UART_Receive_IT(&huartx, RXbuff, BUFFER_SIZE) != HAL_OK) {
        // 错误处理
        printf("Failed to start UART receive IT.\n");
    }

    while (1) {
        // 主循环
        // 可以在这里添加其他任务
    }
}
```
## 方式二
add the following the content in `main.c` file 
```c 
  __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
```
```c 
void USART1_IRQHandler(void)
{
  uint8_t ch=0; 
  
	if(__HAL_UART_GET_FLAG( &huart1, UART_FLAG_RXNE ) != RESET)
	{		
    ch=( uint16_t)READ_REG(huart1.Instance->DR);
    WRITE_REG(huart1.Instance->DR,ch); 
 
	}
}
```

# Input capture
Ref: https://blog.csdn.net/weixin_42880082/article/details/131778564
