## exti of key
### callback function
note:
xSemaphoreGiveFromISR(keySemphrHandle, NULL)
```c 
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_0){

        if(xSemaphoreGiveFromISR(keySemphrHandle, NULL) == pdPASS) 
        {
            my_printf("key is pressed\n");
        }
    }
}

```



## Binary Semaphore 
### function
3.1 创建二值信号量
/********************动态创建二值信号量**********************************************/
SemaphoreHandle_t xSemaphoreCreateBinary(void);
/********************静态创建二值信号量**********************************************/
SemaphoreHandle_t xSemaphoreCreateBinaryStatic(StaticSemaphore_t *pxSemaphoreBuffer);
参数：pxSemaphoreBuffer指向一个StaticSemaphore_t类型的变量，用来保存信号量结构体
/***********************************************************************************/
返回值：创建成功返回二值信号量句柄；失败返回NULL
二值信号量创建函数是一个宏，最终是通过xQueueGenericCreate()函数来完成，其源码如下：
/*其实就是创建了一个长度为1、队列项长度为0、类型为二值信号量的队列*/

3.2 释放信号量
/********************任务级信号量释放**********************************************/
BaseType_t xSemaphoreGive(SemaphoreHandle_t  xSemaphore)
/********************中断级信号量释放**********************************************/
BaseType_t xSemaphoreGiveFromISR( SemaphoreHandle_t xSemaphore,//要释放的信号量句柄
                         BaseType_t *pxHigherPriorityTaskWoken)//标记退出后是否切换任务
/***********************************************************************************/
返回值：释放成功返回pdPASS;释放失败返回errQUEUE_FULL
二值信号量释放函数xSemaphoreGive()是一个宏，其实就是向队列发送消息，其源码如下：
/*其实就是没有具体消息、阻塞时间为0、后向入队的入队过程*/

3.3 获取信号量
/********************任务级信号量获取**********************************************/
BaseType_t xSemaphoreTake(SemaphoreHandle_t  xSemaphore//要获取的信号量句柄
                          TickType_t xBlockTime)//阻塞时间
/********************中断级信号量获取**********************************************/
BaseType_t xSemaphoreTakeFromISR(SemaphoreHandle_t xSemaphore,//要获取的信号量句柄
                         BaseType_t *pxHigherPriorityTaskWoken)//标记退出后是否切换任务
/***********************************************************************************/
返回值：获取成功返回pdPASS;释放失败返回pdFALSE
获取信号量函数也是一个宏，其实就是读取队列的过程，其源码如下

### Example
xSemaphoreGiveFromISR(BinarySemHandle,NULL); //This is important 'NULL'
