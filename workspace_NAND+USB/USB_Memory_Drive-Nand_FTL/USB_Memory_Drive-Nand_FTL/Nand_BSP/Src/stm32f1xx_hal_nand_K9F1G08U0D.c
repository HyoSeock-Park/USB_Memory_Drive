/**
  ******************************************************************************
  * @file    stm32f1xx_hal_nand_K9F1G08U0D.c
  * @author  Park hyoseock
  * @brief   NAND HAL module driver for K9F1G08U0D.
  *          This code modified from stm32f1xx_hal_nand.c of STMicroelectronics.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_nand_K9F1G08U0D.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

#ifdef HAL_NAND_MODULE_ENABLED

/** @defgroup NAND NAND
  * @brief NAND HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private Constants ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup NAND_Exported_Functions NAND Exported Functions
  * @{
  */

/** @defgroup NAND_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### NAND Initialization and de-initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to initialize/de-initialize
    the NAND memory

@endverbatim
  * @{
  */

/**
  * @brief  Perform NAND memory Initialization sequence
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  ComSpace_Timing pointer to Common space timing structure
  * @param  AttSpace_Timing pointer to Attribute space timing structure
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_K9_Init(NAND_HandleTypeDef *hnand, FSMC_NAND_PCC_TimingTypeDef *ComSpace_Timing,
                                 FSMC_NAND_PCC_TimingTypeDef *AttSpace_Timing)
{
	return HAL_NAND_Init(hnand, ComSpace_Timing, AttSpace_Timing);
}

/**
  * @brief  Perform NAND memory De-Initialization sequence
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_K9_DeInit(NAND_HandleTypeDef *hnand)
{
	return HAL_NAND_DeInit(hnand);
}

/**
  * @}
  */

/** @defgroup NAND_Exported_Functions_Group2 Input and Output functions
  * @brief    Input Output and memory control functions
  *
  @verbatim
  ==============================================================================
                    ##### NAND Input and Output functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to use and control the NAND
    memory

@endverbatim
  * @{
  */

/**
  * @brief  Read the NAND memory electronic signature
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pNAND_ID NAND ID structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_K9_Read_ID(NAND_HandleTypeDef *hnand, NAND_IDTypeDef *pNAND_ID)
{
	return HAL_NAND_Read_ID(hnand, pNAND_ID);
}

/**
  * @brief  NAND memory reset
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_K9_Reset(NAND_HandleTypeDef *hnand)
{
	return HAL_NAND_Reset(hnand);
}


/**
  * @brief  Read Page(s) from NAND memory block (8-bits addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  NumPageToRead  number of pages to read from block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_K9_Read_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                        uint32_t NumPageToRead)
{
	  uint32_t deviceaddress;
	  uint32_t nandaddress;

	  uint32_t index;
	  uint32_t tickstart;

	  //uint32_t numpagesread = 0U;

	  /* Check the NAND controller state */
	  if (hnand->State == HAL_NAND_STATE_BUSY)
	  {
	    return HAL_BUSY;
	  }
	  else if (hnand->State == HAL_NAND_STATE_READY)
	  {
	    /* Process Locked */
	    __HAL_LOCK(hnand);

	    /* Update the NAND controller state */
	    hnand->State = HAL_NAND_STATE_BUSY;

	    /* Identify the device address */
	    if (hnand->Init.NandBank == FSMC_NAND_BANK2)
	    {
	      deviceaddress = NAND_DEVICE1;
	    }
	    else
	    {
	      deviceaddress = NAND_DEVICE2;
	    }

	    /* NAND row address calculation */
	    nandaddress = ARRAY_ADDRESS(pAddress, hnand);

	    /* Page(s) read loop */
	    while ((NumPageToRead != 0U) && (nandaddress < ((hnand->Config.BlockSize) * (hnand->Config.BlockNbr))))
	    {

	      /* Send read page command sequence */
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | CMD_AREA)) = NAND_CMD_AREA_A;
	      __DSB();

	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = 0x00U; // offsetinpage
	      __DSB();
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = 0x00U; // offsetinpage
	      __DSB();
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddress); // row_addr = page_number
	      __DSB();
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddress); // row_addr = page_number
	      __DSB();

	      *(__IO uint8_t *)((uint32_t)(deviceaddress | CMD_AREA))  = NAND_CMD_AREA_TRUE1;
	      __DSB();


	      if (hnand->Config.ExtraCommandEnable == ENABLE)
	      {
	        /* Get tick */
	        tickstart = HAL_GetTick();

	        /* Read status until NAND is ready */
	        while (HAL_NAND_Read_Status(hnand) != NAND_READY)
	        {
	          if ((HAL_GetTick() - tickstart) > NAND_WRITE_TIMEOUT)
	          {
	            /* Update the NAND controller state */
	            hnand->State = HAL_NAND_STATE_ERROR;

	            /* Process unlocked */
	            __HAL_UNLOCK(hnand);

	            return HAL_TIMEOUT;
	          }
	        }

	        /* Go back to read mode */
	        *(__IO uint8_t *)((uint32_t)(deviceaddress | CMD_AREA)) = ((uint8_t)0x00);
	        __DSB();
	      }


	      /* Get Data into Buffer */
	      for (index = 0U; index < hnand->Config.PageSize; index++)
	      {
	        *pBuffer = *(uint8_t *)deviceaddress;
	        pBuffer++;
	      }

	      /* Increment read pages number */
	      //numpagesread++;

	      /* Decrement pages to read */
	      NumPageToRead--;

	      /* Increment the NAND address */
	      nandaddress = (uint32_t)(nandaddress + 1U);
	    }

	    /* Update the NAND controller state */
	    hnand->State = HAL_NAND_STATE_READY;

	    /* Process unlocked */
	    __HAL_UNLOCK(hnand);
	  }
	  else
	  {
	    return HAL_ERROR;
	  }

	  return HAL_OK;
}


/**
  * @brief  Write Page(s) to NAND memory block (8-bits addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumPageToWrite   number of pages to write to block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_K9_Write_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                         uint32_t NumPageToWrite)
{
	  uint32_t deviceaddress;
	  uint32_t nandaddress;

	  uint32_t index;
	  uint32_t tickstart;

	  //uint32_t numpageswritten = 0;

	  /* Check the NAND controller state */
	  if (hnand->State == HAL_NAND_STATE_BUSY)
	  {
	    return HAL_BUSY;
	  }
	  else if (hnand->State == HAL_NAND_STATE_READY)
	  {
	    /* Process Locked */
	    __HAL_LOCK(hnand);

	    /* Update the NAND controller state */
	    hnand->State = HAL_NAND_STATE_BUSY;

	    /* Identify the device address */
	    if (hnand->Init.NandBank == FSMC_NAND_BANK2)
	    {
	      deviceaddress = NAND_DEVICE1;
	    }
	    else
	    {
	      deviceaddress = NAND_DEVICE2;
	    }

	    /* NAND row address calculation */
	    nandaddress = ARRAY_ADDRESS(pAddress, hnand);

	    /* Page(s) write loop */
	    while ((NumPageToWrite != 0U) && (nandaddress < ((hnand->Config.BlockSize) * (hnand->Config.BlockNbr))))
	    {

	      /* Send write page command sequence */
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | CMD_AREA)) = NAND_CMD_WRITE0;
	      __DSB();

	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = 0x00U; // offsetinpage
	      __DSB();
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = 0x00U; // offsetinpage
	      __DSB();
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddress); // row_addr = page_number
	      __DSB();
	      *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddress); // row_addr = page_number
	      __DSB();

	      /* Write data to memory */
	      for (index = 0U; index < hnand->Config.PageSize; index++)
	      {
	        *(__IO uint8_t *)deviceaddress = *pBuffer;
	        pBuffer++;
	        __DSB();
	      }

	      *(__IO uint8_t *)((uint32_t)(deviceaddress | CMD_AREA)) = NAND_CMD_WRITE_TRUE1;
	      __DSB();


	      /* Get tick */
	      tickstart = HAL_GetTick();

	      /* Read status until NAND is ready */
	      while (HAL_NAND_Read_Status(hnand) != NAND_READY)
	      {
	        if ((HAL_GetTick() - tickstart) > NAND_WRITE_TIMEOUT)
	        {
	          /* Update the NAND controller state */
	          hnand->State = HAL_NAND_STATE_ERROR;

	          /* Process unlocked */
	          __HAL_UNLOCK(hnand);

	          return HAL_TIMEOUT;
	        }
	      }

	      /* Increment written pages number */
	      //numpageswritten++;

	      /* Decrement pages to write */
	      NumPageToWrite--;

	      /* Increment the NAND address */
	      nandaddress = (uint32_t)(nandaddress + 1U);
	    }

	    /* Update the NAND controller state */
	    hnand->State = HAL_NAND_STATE_READY;

	    /* Process unlocked */
	    __HAL_UNLOCK(hnand);
	  }
	  else
	  {
	    return HAL_ERROR;
	  }

	  return HAL_OK;
}

/**
  * @brief  NAND memory Block erase
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_K9_Erase_Block(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress)
{
	  uint32_t deviceaddress;
	  uint32_t nandaddress;

	  uint32_t tickstart;

	  /* Check the NAND controller state */
	  if (hnand->State == HAL_NAND_STATE_BUSY)
	  {
	    return HAL_BUSY;
	  }
	  else if (hnand->State == HAL_NAND_STATE_READY)
	  {
	    /* Process Locked */
	    __HAL_LOCK(hnand);

	    /* Update the NAND controller state */
	    hnand->State = HAL_NAND_STATE_BUSY;

	    /* Identify the device address */
	    if (hnand->Init.NandBank == FSMC_NAND_BANK2)
	    {
	      deviceaddress = NAND_DEVICE1;
	    }
	    else
	    {
	      deviceaddress = NAND_DEVICE2;
	    }

	    /* NAND row address calculation */
	    nandaddress = ARRAY_ADDRESS(pAddress, hnand);

	    /* Send Erase block command sequence */
	    *(__IO uint8_t *)((uint32_t)(deviceaddress | CMD_AREA)) = NAND_CMD_ERASE0;
	    __DSB();
	    *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddress);
	    __DSB();
	    *(__IO uint8_t *)((uint32_t)(deviceaddress | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddress);
	    __DSB();
	    *(__IO uint8_t *)((uint32_t)(deviceaddress | CMD_AREA)) = NAND_CMD_ERASE1;
	    __DSB();


	    /* Get tick */
	    tickstart = HAL_GetTick();

	    /* Read status until NAND is ready */
	    while (HAL_NAND_Read_Status(hnand) != NAND_READY)
	    {
	      if ((HAL_GetTick() - tickstart) > NAND_WRITE_TIMEOUT)
	      {
	        /* Update the NAND controller state */
	        hnand->State = HAL_NAND_STATE_ERROR;

	         /* Process unlocked */
	        __HAL_UNLOCK(hnand);

	         return HAL_TIMEOUT;
	      }
	    }

	    /* Update the NAND controller state */
	    hnand->State = HAL_NAND_STATE_READY;

	    /* Process unlocked */
	    __HAL_UNLOCK(hnand);
	  }
	  else
	  {
	    return HAL_ERROR;
	  }

	  return HAL_OK;
}

/**
  * @brief  Increment the NAND memory address
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param pAddress pointer to NAND address structure
  * @retval The new status of the increment address operation. It can be:
  *           - NAND_VALID_ADDRESS: When the new address is valid address
  *           - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t HAL_NAND_K9_Address_Inc(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress)
{
	return HAL_NAND_Address_Inc(hnand, pAddress);
}


/** @defgroup NAND_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions
  *
@verbatim
  ==============================================================================
                         ##### NAND State functions #####
  ==============================================================================
  [..]
    This subsection permits to get in run-time the status of the NAND controller
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  return the NAND state
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL state
  */
HAL_NAND_StateTypeDef HAL_NAND_K9_GetState(NAND_HandleTypeDef *hnand)
{
  return hnand->State;
}

/**
  * @brief  NAND memory read status
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval NAND status
  */
uint32_t HAL_NAND_K9_Read_Status(NAND_HandleTypeDef *hnand)
{
	return HAL_NAND_Read_Status(hnand);
}


#endif /* HAL_NAND_MODULE_ENABLED  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
