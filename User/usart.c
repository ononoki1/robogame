#include "all.h"

u8 USART1_RX_BUF
    [USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
u16 USART1_RX_STA = 0; //接收状态标记

void uart1Init() {
  // Usart1 NVIC 配置
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //串口1中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // IRQ通道使能
  NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器

  // GPIO端口设置
  USART_InitTypeDef USART_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  // USART1 初始化设置
  USART_InitStructure.USART_BaudRate = 9600; //波特率设置
  USART_InitStructure.USART_WordLength =
      USART_WordLength_8b; //字长为8位数据格式
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
  USART_InitStructure.USART_Parity = USART_Parity_No;    //无奇偶校验位
  USART_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None; //无硬件数据流控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
  USART_Init(USART1, &USART_InitStructure);      //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启相关中断
  USART_Cmd(USART1, ENABLE);                     //使能串口1

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // TX
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode =
      GPIO_Mode_AF_PP; // IO端口工作模式：复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // RX
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode =
      GPIO_Mode_IN_FLOATING; // IO端口工作模式：浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// USART1中断服务函数
void USART1_IRQHandler() {
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
  {
    u8 Res = USART_ReceiveData(USART1); //接收数据，考虑转义字符

    if (Res == COMMU_OPR_BALL && step == WAIT_FETCH)
      finish = 1;

    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
}
