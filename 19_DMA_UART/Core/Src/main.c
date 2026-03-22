/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s3;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
char msg[] = "t0.txt=\"Hello STM32\"";
uint8_t end[] = {0xFF,0xFF,0xFF};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S3_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
void Custom_UART_DMA_Init(void);
void Custom_GPIO_Clock_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_USB_HOST_Init();
  //MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  // 1. INITIALIZE OUR CUSTOM HARDWARE SETTINGS
  // 1. KENDİ YAZDIĞIMIZ DONANIM AYARLARINI BAŞLATALIM
  Custom_GPIO_Clock_Init();
  Custom_UART_DMA_Init();
  // ---------------- BİRİNCİ PAKET: METNİ GÖNDER ----------------
  // 2. ARM THE DMA (PREPARE FOR SHOOTING)
  // 2. DMA'YI KUR (ATEŞLEMEYE HAZIRLA)
  // Kaynak: msg dizisi. Hedef: USART2'nin Data Register'ı (DR). Boyut: Mesajın uzunluğu.
  //  F407 dökümanına göre DR kullanıyoruz!
  HAL_DMA_Start(&hdma_usart2_tx,(uint32_t )msg,(uint32_t )&huart2.Instance->DR,strlen(msg));
  // ENABLE UART DMA TRANSMIT REQUEST
  //  UART DMA İLETİM İSTEĞİNİ AKTİF ET
  // UART'ın CR3 (Control Register 3) içindeki DMAT (DMA Transmit) bitini "1" yapıyoruz.
  // Bu komut verildiği an, UART DMA'dan harfleri çekmeye başlar. Veri akışı başlar!
  huart2.Instance->CR3 |= USART_CR3_DMAT;
  // 4. WAIT FOR COMPLETION (POLLING MODE)
  // 4. İŞLEMİN BİTMESİNİ BEKLE (SORGULAMA MODU)
  // İşlemci burada nöbet tutar. DMA son harfi gönderip "Full Transfer" (Tam Transfer)
  // bayrağını kaldırana kadar alt satıra geçmez.
  HAL_DMA_PollForTransfer(&hdma_usart2_tx,HAL_DMA_FULL_TRANSFER,HAL_MAX_DELAY);
  // 5. CLEANUP: DISABLE UART DMA TRANSMIT REQUEST
  // 5. TEMİZLİK: UART DMA İLETİM İSTEĞİNİ KAPAT
  huart2.Instance->CR3 &= ~USART_CR3_DMAT;
  // ---------------- İKİNCİ PAKET: 0xFF BİTİŞ KODLARINI GÖNDER ----------------
  // 1. DMA'yı 'end' dizisi için kur (Boyut olarak sadece 3 yazıyoruz!)
  // 1. Set up DMA for the 'end' array (We only use size 3!)
  HAL_DMA_Start(&hdma_usart2_tx,(uint32_t)end,(uint32_t)&huart2.Instance->DR,3);
  //2.(0xFF baytları gitmeye başlar)
  //2.(0xFF bytes start being sent)
  huart2.Instance->CR3 |= USART_CR3_DMAT;
  // 3. Bitiş kodlarının tamamen gönderilmesini bekle
  HAL_DMA_PollForTransfer(&hdma_usart2_tx, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
  // 4. DMA isteğini kapat (Temizlik)
  huart2.Instance->CR3 &= ~USART_CR3_DMAT;
  // 6. SUCCESS SIGNAL: TURN ON THE GREEN LED (LD4) ON DISCOVERY BOARD
  // 6. BAŞARI SİNYALİ: DISCOVERY KARTINDAKİ YEŞİL LED'İ (LD4) YAK
  // F407 Discovery kartında Yeşil LED, PD12 (GPIOD) pinine bağlıdır.
  HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_96K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* * STEP 1: INITIALIZATION OF PERIPHERAL CLOCKS & GPIO PINS
 * ADIM 1: ÇEVRE BİRİMİ SAATLERİ (CLOCK) VE PİN (GPIO) AYARLARI
 */
void Custom_GPIO_Clock_Init(void){
	/* --- ENABLING PERIPHERAL CLOCKS / ÇEVRE BİRİMİ SAAT SİNYALLERİNİ AÇMA --- */
	// We need PA2 pin, so we enable GPIOA clock.
	// PA2 pinini kullanacağımız için GPIOA portuna enerji (clock) veriyoruz.
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// We are going to use USART2, so we enable its clock.
	// İletişim için USART2 kullanacağız, birimi uyandırıyoruz.
	__HAL_RCC_USART2_CLK_ENABLE();
	// According to RM0090 Table 43, USART2_TX request is on DMA1.
	// RM0090 Tablo 43'e göre USART2_TX isteği DMA1'e bağlıdır, DMA1'i uyandırıyoruz.
	__HAL_RCC_DMA1_CLK_ENABLE();
	/* --- GPIO PIN CONFIGURATION / PİN YAPILANDIRMASI --- */
	GPIO_InitTypeDef GPIO_InitStruct = {0};// Initialize struct with zeros / Yapıyı sıfırla
	// Pin Selection: We selected PA2 according to Datasheet pinout table.
	// Pin Seçimi: Datasheet'teki pinout tablosuna bakarak PA2'yi seçtik.
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	// Mode: Alternate Function Push-Pull. We delegate the pin control to the peripheral (USART).
	// Mod: Alternatif Fonksiyon (Push-Pull). Pinin kontrolünü işlemciden alıp donanıma (USART) veriyoruz.
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	// Pull-up/down: No internal resistor is needed for USART TX line.
	// Direnç: USART TX hattı kendi voltajını sürdüğü için dâhili dirence gerek yoktur.
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	// Speed: Very High Speed to ensure fast signal transitions for serial data.
	// Hız: Seri verinin düzgün iletilmesi için pinin tepki hızını en yükseğe ayarlıyoruz.
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	// Alternate Function: According to Datasheet Table 9, PA2 maps to USART2_TX via AF7.
	// Alternatif Fonksiyon: Datasheet Tablo 9'a göre, PA2 pini USART2_TX hattına AF7 üzerinden bağlanır.
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	// Apply all configurations to GPIOA port.
	// Tüm bu ayarları fiziksel olarak GPIOA portuna (PA2 pini) uygula.
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
/* * STEP 2: UART AND DMA CONFIGURATION
 * ADIM 2: UART VE DMA YAPILANDIRMASI
 */
void Custom_UART_DMA_Init(void){
	/* --- UART2 CONFIGURATION / UART2 YAPILANDIRMASI --- */
	// Select the peripheral instance / Kullanılacak donanım birimi
	huart2.Instance = USART2;
	// Communication parameters (Standard 115200 8N1)
	// İletişim parametreleri (Standart 115200 Baud, 8 Veri biti, Parite Yok, 1 Durdurma biti)
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	// Apply UART configurations / UART ayarlarını uygula
	HAL_UART_Init(&huart2);
	/* --- DMA1 STREAM 6 CONFIGURATION (FOR USART2_TX) --- */

	// Select the correct Stream and Channel based on RM0090 Table 43
	// RM0090 Tablo 43'e göre doğru Akış (Stream) ve Kanalı (Channel) seçiyoruz.
	// F407 uses Stream/Channel architecture! / F407'de Akış/Kanal mimarisi kullanılır!
	hdma_usart2_tx.Instance = DMA1_Stream6;
	hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
	// Transfer direction: Memory to Peripheral
	// Veri yönü: Bellekten (SRAM'deki mesajımız) Çevre Birimine (UART)
	hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	// Peripheral address must remain constant
	// Peripheral address must remain constant
	hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	// Memory address must increment to read the string character by character
	// Mesajı harf harf okumak için bellek adresi her gönderimde otomatik artmalı
	hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
	// Data alignment: 1 Byte (8-bit) for both Memory and Peripheral
	// Veri boyutu: Hem bellek hem donanım için 8-bit (1 Bayt) paketler
	hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	// Normal Mode: Stop after sending the message once
	// Normal Mod: Mesajı bir kere gönderip durur (Circular seçilirse sürekli baştan başlar)
	hdma_usart2_tx.Init.Mode=DMA_NORMAL;
	// Priority level of this DMA stream / Bu DMA akışının öncelik seviyesi
	hdma_usart2_tx.Init.Priority=DMA_PRIORITY_LOW;
	// Disable FIFO mode for simplicity (Direct mode used)
	// Basitlik için FIFO modunu kapatıyoruz (Doğrudan mod kullanılır)
	hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	// Apply DMA configurations / DMA ayarlarını uygula
	HAL_DMA_Init(&hdma_usart2_tx);
}
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
#ifdef USE_FULL_ASSERT
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
