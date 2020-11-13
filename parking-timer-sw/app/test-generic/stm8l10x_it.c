/**
  ******************************************************************************
  * @file     Project/STM8L10x_StdPeriph_Templates/stm8l10x_it.c
  * @author   MCD Application Team
  * @version  V1.2.1
  * @date     30-September-2014
  * @brief    This file contains all the interrupt routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x_it.h"

/** @addtogroup STM8L10x_StdPeriph_Templates
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief  Dummy interrupt routine
  * @param  None
  * @retval None
*/
void NonHandledInterrupt(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif

/**
  * @brief  TRAP interrupt routine
  * @param  None
  * @retval None
*/
void TRAP(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
void FLASH_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  Auto Wake Up Interrupt routine.
  * @param  None
  * @retval None
  */
void AWU_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PORTB Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTIB_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PORTD Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTID_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI5_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI6_IRQHandler(void)

{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
void EXTI7_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
void COMP_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  Timer2 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
void TIM2_UPD_OVF_TRG_BRK_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  Timer2 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
void TIM2_CAP_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}


/**
  * @brief  Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
void TIM3_UPD_OVF_TRG_BRK_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief  Timer3 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
void TIM3_CAP_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief  Timer4 Update/Overflow Interrupt routine.
  * @param  None
  * @retval None
  */
void TIM4_UPD_OVF_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  SPI Interrupt routine.
  * @param  None
  * @retval None
  */
void SPI_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief  USART TX Interrupt routine.
  * @param  None
  * @retval None
  */
void USART_TX_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief  USART RX Interrupt routine.
  * @param  None
  * @retval None
  */
void USART_RX_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}


/**
  * @brief  I2C Interrupt routine.
  * @param  None
  * @retval None
  */
void I2C_IRQHandler(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

