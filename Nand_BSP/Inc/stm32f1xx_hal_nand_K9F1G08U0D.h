/**
  ******************************************************************************
  * @file    stm32f1xx_hal_nand_K9F1G08U0D.h
  * @author  Park hyoseock
  * @brief   Header file of NAND HAL module for K9F1G08U0D.
  *          This code modified from stm32f1xx_hal_nand.h of STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32F1xx_HAL_NAND_K9F1G08U0D_H
#define STM32F1xx_HAL_NAND_K9F1G08U0D_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef  HAL_NAND_K9_Init(NAND_HandleTypeDef *hnand, FSMC_NAND_PCC_TimingTypeDef *ComSpace_Timing,
                                 FSMC_NAND_PCC_TimingTypeDef *AttSpace_Timing);
HAL_StatusTypeDef  HAL_NAND_K9_DeInit(NAND_HandleTypeDef *hnand);

HAL_StatusTypeDef  HAL_NAND_K9_Read_ID(NAND_HandleTypeDef *hnand, NAND_IDTypeDef *pNAND_ID);

/* IO operation functions  ****************************************************/
HAL_StatusTypeDef  HAL_NAND_K9_Reset(NAND_HandleTypeDef *hnand);

HAL_StatusTypeDef  HAL_NAND_K9_Read_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                         uint32_t NumPageToRead);
HAL_StatusTypeDef  HAL_NAND_K9_Write_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                          uint32_t NumPageToWrite);
HAL_StatusTypeDef HAL_NAND_K9_Read_SpareArea(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                             uint32_t NumSpareAreaToRead);
HAL_StatusTypeDef HAL_NAND_K9_Write_SpareArea(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                              uint8_t *pBuffer, uint32_t NumSpareAreaTowrite);
HAL_StatusTypeDef  HAL_NAND_K9_Erase_Block(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress);

uint32_t           HAL_NAND_K9_Address_Inc(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress);

/* NAND State functions *******************************************************/
HAL_NAND_StateTypeDef HAL_NAND_K9_GetState(NAND_HandleTypeDef *hnand);
uint32_t              HAL_NAND_K9_Read_Status(NAND_HandleTypeDef *hnand);

#ifdef __cplusplus
}
#endif

#endif /* STM32F1xx_HAL_NAND_K9F1G08U0D_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
