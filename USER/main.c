#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "string.h"
#include "ov7670.h"
#include "timer.h"
#include "exti.h"
#include "usmart.h"
#include "stdio.h"
#include "location.h"
#include "usart3.h"
#include "pid.h"
#include "key_scan.h"
 
extern u8 mode1_flag,mode2_flag,mode3_flag,mode4_flag,mode5_flag;

 int main(void)
 {	 
	
	 u8 key;
	 
	delay_init();	    	 //延时函数初始化	  
	KEY_Init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为 115200
 	usmart_dev.init(72);		//初始化USMART		
 	LED_Init();		  			//初始化与LED连接的硬件接口
	LCD_Init();			   		//初始化LCD  
  //Init_Keyboard_Interrupt();
	//TIM3_Int_Init(9999,7199);
	PID_Init(-14.28,2.61,78,79);
 	POINT_COLOR=RED;			//设置字体为红色 
	LCD_ShowString(30,70,200,16,16,"OV7670 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/18");  
  LCD_ShowString(30,50,200,16,16,"OV7670 Init...");	 
	while(OV7670_Init())//初始化OV7670
	{
		LCD_ShowString(30,70,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	  LCD_Fill(30,210,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(30,700,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 	   
	usart3_init();
	TIM3_PWM_Init(9999,143);
	TIM6_Int_Init(100,7199);			//10Khz计数频率,1秒钟中断									  
	EXTI8_Init();						//使能定时器捕获
	OV7670_Window_Set(12,176,160,160);	//设置窗口	
  OV7670_CS=0;			
	LCD_Clear(BLACK);
	
	
	
 	while(1)
	{	
		
     key=KEY_Scan(0);	//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//控制蜂鸣器
		         mode1_flag=1;mode2_flag=0;mode3_flag=0;mode4_flag=0;
					break; 
				case KEY1_PRES:	//控制LED1翻转	 
					LED1=!LED1;
			   	mode1_flag=0;mode2_flag=1;mode3_flag=0;mode4_flag=0;
					break;
				case KEY0_PRES:	//同时控制LED0,LED1翻转 
					mode1_flag=0;mode2_flag=0;mode3_flag=1;mode4_flag=0;
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}else delay_ms(10); 
	}
}









