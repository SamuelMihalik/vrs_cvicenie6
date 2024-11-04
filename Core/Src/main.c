#include "main.h"

char formated_text[30];

typedef struct {
    float temperature_h;
    float temperature_l;
    uint8_t humidity;
    float pressure;
    float height;
} sensor_data;

sensor_data data;
float initial_pressure;

void SystemClock_Config(void);

int main(void) {
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_DMA_Init();
	MX_I2C1_Init();
	MX_USART2_UART_Init();

	if(!HTS221_Init(i2c_master_read, i2c_master_write))
		return;



	if(!LPS25HB_Init(i2c_master_read, i2c_master_write))
		return;

	initial_pressure = LPS25HB_get_pressure();

	while (1) {
		LL_mDelay(100);

		get_sensor_data();

		memset(formated_text, '\0', sizeof(formated_text));

		sprintf(formated_text, "%.1f,%.1f,%.d,%.2f,%.2f\n\r", data.temperature_l, data.temperature_h, data.humidity, data.pressure, data.height);
		USART2_PutBuffer((uint8_t*)formated_text, strlen(formated_text));
	}

}

void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_SetSystemCoreClock(8000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
}

void get_sensor_data(void) {
	data.temperature_h = HTS221_get_temperature();
	data.temperature_l = LPS25HB_get_temperature();
	data.pressure = LPS25HB_get_pressure();
	data.height = (float)44330.00 * (1 - pow(data.pressure / initial_pressure, 1 / 5.255)); //15, 10, klesa tlak
	data.humidity = HTS221_get_humidity();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
