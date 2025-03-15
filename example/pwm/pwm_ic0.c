uint32_t capture_value[3];    /*定义数组变量，存放捕获到的值*/
uint32_t diff_value1;    /*计数差值*/
uint32_t diff_value2;    /*计数差值*/

uint8_t capture_state=0;    /*捕获状态：0表示未开始捕获；1表示完成一次捕获；2表示完成两次捕获*/
uint8_t capture_flag=0;    /*捕获标志位：0表示未完成，1表示已完成*/
int main(){
   HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
  while (1)
  {
     if (capture_flag==1)    /* 捕获完成 */
    {
      printf("\n******capture start******\n");
      if (capture_value[2] >= capture_value[0])    /* 计时没有溢出 */
      {
        diff_value1=capture_value[2]-capture_value[0];    /* 取差值 */
      }
      else    /* 计时有溢出 */
      {
        diff_value1=(0xffffffff+1)+capture_value[2]-capture_value[0];    /* 取差值 */
      }
      // HAL_UART_Transmit(&huart1, &diff_value1, sizeof(diff_value1), HAL_MAX_DELAY);
      // HAL_UART_Transmit(&huart1, a, sizeof(a)/sizeof(a[0]), HAL_MAX_DELAY);
      printf("周期：%.2fms\n",diff_value1/72000.0);    /*周期=差值*单次计数时间*/
      printf("频率：%.2fKHz\n",72000.0/diff_value1);

      if (capture_value[1] >= capture_value[0])    /* 计时没有溢出 */
      {
        diff_value2=capture_value[1]-capture_value[0];    /* 取差值 */
      }
      else    /* 计时有溢出 */
      {
        diff_value2=(0xffffffff+1)+capture_value[1]-capture_value[0];    /* 取差值 */
      }
      printf("高电平：%.2fms\n",diff_value2/72000.0);    /*高电平时间=差值*单次计数时间*/
      printf("占空比：%d%%\n",diff_value2*100/diff_value1);

      printf("******capture over******\n");

      capture_flag=0;    /*清除标志位，准备下一轮捕获*/
      HAL_Delay(1000);
      HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);    /*开启下一轮捕获*/
    }
}

//回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if (htim==&htim1)
  {
    switch (capture_state)
    {
    case 0:
      {
        capture_value[0]=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);    /*读取捕获开始时间*/
        __HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);    /*切换为下降沿捕获*/
        capture_state=1;    /*标志完成第一次捕获*/
      }
      break;

    case 1:
    {
      capture_value[1]=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);    /*读取第二次捕获时间*/
      __HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);    /*切换为上升沿捕获*/
      capture_state=2;    /*标志完成第二次捕获*/
    }
    break;

    case 2:
    {
      capture_value[2]=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);    /*读取捕获结束时间*/
      HAL_TIM_IC_Stop_IT(htim,TIM_CHANNEL_1);    /*停止捕获*/
      capture_state=0;    /*标志完成第三次捕获，重新置0，准备下一轮捕获*/
      capture_flag=1;    /*标志捕获完成*/
    }
    break;
    
    default:
      printf("running error!\n");
      break;
    }
  }
  
}
