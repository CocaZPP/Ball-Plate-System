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
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	KEY_Init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ 115200
 	usmart_dev.init(72);		//��ʼ��USMART		
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   		//��ʼ��LCD  
  //Init_Keyboard_Interrupt();
	//TIM3_Int_Init(9999,7199);
	PID_Init(-14.28,2.61,78,79);
 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	LCD_ShowString(30,70,200,16,16,"OV7670 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/18");  
  LCD_ShowString(30,50,200,16,16,"OV7670 Init...");	 
	while(OV7670_Init())//��ʼ��OV7670
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
	TIM6_Int_Init(100,7199);			//10Khz����Ƶ��,1�����ж�									  
	EXTI8_Init();						//ʹ�ܶ�ʱ������
	OV7670_Window_Set(12,176,160,160);	//���ô���	
  OV7670_CS=0;			
	LCD_Clear(BLACK);
	
	
	
 	while(1)
	{	
		
     key=KEY_Scan(0);	//�õ���ֵ
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//���Ʒ�����
		         mode1_flag=1;mode2_flag=0;mode3_flag=0;mode4_flag=0;
					break; 
				case KEY1_PRES:	//����LED1��ת	 
					LED1=!LED1;
			   	mode1_flag=0;mode2_flag=1;mode3_flag=0;mode4_flag=0;
					break;
				case KEY0_PRES:	//ͬʱ����LED0,LED1��ת 
					mode1_flag=0;mode2_flag=0;mode3_flag=1;mode4_flag=0;
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}else delay_ms(10); 
	}
}









