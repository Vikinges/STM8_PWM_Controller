/**
  ******************************************************************************
  * @author  Vladimir Linartas
  * @version V1
  * @date    2-August-2022
  * @brief   This file making Software PWM and can Change speed real time 
  ******************************************************************************

  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/**
  * @addtogroup GPIO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */

// #difine LED_PIN     (GPIO_PIN_3 )
#define PWM_GPIO_PINS  (GPIO_PIN_3 | GPIO_PIN_4 )
#define BUT_UP_PIN     (GPIO_PIN_7)
#define BUT_DOWN_PIN   (GPIO_PIN_6)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t Button_tik=10; //speed PWM button or + or - 
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount); // simple delay 
void PWM_PINC3(uint16_t speed_100_67_10000_99 ); // function to make PWM 
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);
  GPIO_DeInit(GPIOA);
  /* Initialize I/Os in Output Mode */
  GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)PWM_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST); //pin software PWM PC-3-4
  GPIO_Init(GPIOC, BUT_UP_PIN,GPIO_MODE_IN_PU_IT);         // pin button UP PC7
  GPIO_Init(GPIOC, BUT_DOWN_PIN,GPIO_MODE_IN_PU_IT);       // pin button down PC6
  GPIO_Init(GPIOD, GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW);  // Led pin PD3 toogle pin in board 
  GPIO_Init(GPIOA, GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW);  // Led pin PA3 toogle pin white led  
  GPIO_Init(GPIOA, GPIO_PIN_2,GPIO_MODE_OUT_PP_LOW_SLOW);  // Led pin PA2 toogle pin Green Led 
  GPIO_Init(GPIOA, GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);  // Led pin PA1 toogle pin Yellow Led 
  GPIO_Init(GPIOD, GPIO_PIN_6,GPIO_MODE_OUT_PP_LOW_SLOW);  // Led pin PD6 toogle pin Red Led  
  

  while (1)
  {
  
    if (GPIO_ReadInputPin(GPIOC,BUT_UP_PIN) == 0 && Button_tik <1000) // // interupt button UP
    {
      Button_tik++;
      GPIO_WriteReverse(GPIOD, GPIO_PIN_3);      // show manipulations with button  -+
    Delay(5000);
    }
   
        if (GPIO_ReadInputPin(GPIOC,BUT_DOWN_PIN) == 0 && Button_tik >10)  // interupt button down
        {
          Button_tik--;
         GPIO_WriteReverse(GPIOD, GPIO_PIN_3);   // show manipulations with button  -+
        Delay(5000);
        }

 

  /** Switsh Leds show how much duty have PWM 
    * White > 15% green > 35% yellow > 60% red > 90% 
    */

         switch( Button_tik ) 
         {
          case  10 :
          GPIO_WriteHigh(GPIOA,GPIO_PIN_3);
          GPIO_WriteLow(GPIOA,GPIO_PIN_2);
          GPIO_WriteLow(GPIOA,GPIO_PIN_1);
          GPIO_WriteLow(GPIOD,GPIO_PIN_6);
          break;
          case 150 :
          GPIO_WriteLow(GPIOA,GPIO_PIN_3);
          GPIO_WriteHigh(GPIOA,GPIO_PIN_2);
          GPIO_WriteLow(GPIOA,GPIO_PIN_1);
          GPIO_WriteLow(GPIOD,GPIO_PIN_6);
          break;
          case 350 :
          GPIO_WriteLow(GPIOA,GPIO_PIN_3);
          GPIO_WriteLow(GPIOA,GPIO_PIN_2);
          GPIO_WriteHigh(GPIOA,GPIO_PIN_1);
          GPIO_WriteLow(GPIOD,GPIO_PIN_6);
          break;
          case 600 :
          GPIO_WriteLow(GPIOA,GPIO_PIN_3);
          GPIO_WriteLow(GPIOA,GPIO_PIN_2);
          GPIO_WriteHigh(GPIOA,GPIO_PIN_1);
          GPIO_WriteLow(GPIOD,GPIO_PIN_6);
          break; 
          case 900 :
          GPIO_WriteLow(GPIOA,GPIO_PIN_3);
          GPIO_WriteLow(GPIOA,GPIO_PIN_2);
          GPIO_WriteLow(GPIOA,GPIO_PIN_1);
          GPIO_WriteHigh(GPIOD,GPIO_PIN_6);
          break;
         }
  PWM_PINC3(Button_tik); //  duty cycle PWM
  }
}

/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void PWM_PINC3(uint16_t speed_100_67_10000_99 )
{
  uint16_t speed = speed_100_67_10000_99*2;
 GPIO_WriteLow(GPIOC, (GPIO_Pin_TypeDef)PWM_GPIO_PINS);
Delay(100);    
/* Toggles LEDs */
  GPIO_WriteHigh(GPIOC, (GPIO_Pin_TypeDef)PWM_GPIO_PINS);
    //  GPIO_WriteReverse(GPIOC, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
Delay(speed);   // second delay change Value duty PWM    
 
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
