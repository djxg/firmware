#include "hw_config.h"
#include "boot_mode.h"
#include "params_hal.h"
#include "ui_hal.h"
#include "flash_map.h"
#include "system_config.h"
#include "boot_debug.h"

#define UPDATE_BLINK_PERIOD 100

extern UART_HandleTypeDef UartHandleCellular;
extern SDK_QUEUE USART_Cellular_Queue;

pFunction JumpToApplication;
uint32_t JumpAddress;

void start_app(void)
{
    if(((*(__IO uint32_t*)CORE_FW_ADDRESS) & APP_START_MASK ) == 0x20000000)
    {
        /* Jump to user application */
        JumpAddress = *(__IO uint32_t*) (CORE_FW_ADDRESS + 4);
        JumpToApplication = (pFunction) JumpAddress;

        /* Initialize user application's Stack Pointer */
        __set_MSP(*(__IO uint32_t*) CORE_FW_ADDRESS);
        JumpToApplication();
    }
}

void USBD_DFU_Init(void)
{
    USBD_Init(&USBD_Device, &DFU_Desc, 0);
    USBD_RegisterClass(&USBD_Device, USBD_DFU_CLASS);
    USBD_DFU_RegisterMedia(&USBD_Device, &USBD_DFU_fops);
    USBD_Start(&USBD_Device);
}

void USBD_CDC_Init(void)
{
    USBD_Init(&USBD_Device, &VCP_Desc, 0);
    USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
    USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
    USBD_Start(&USBD_Device);
}

void USBD_CDC_Process(void)
{
    uint8_t TxBuffer[1024];
    uint32_t len=0;

    len=0;
    while(!sdkIsQueueEmpty(&USART_Cellular_Queue))
    {
        if(len < sizeof(TxBuffer)) {
            sdkGetQueueData(&USART_Cellular_Queue, &TxBuffer[len++]);
        } else {
            break;
        }
    }
    if(len) {
        if (USBD_STATE_CONFIGURED == USBD_Device.dev_state) {
            USBD_CDC_SetTxBuffer(&USBD_Device, TxBuffer, len);
            while(USBD_CDC_TransmitPacket(&USBD_Device) != USBD_OK);
        }
    }

    len=0;
    while(!sdkIsQueueEmpty(&USB_Rx_Queue))
    {
        if(len < sizeof(TxBuffer)) {
            sdkGetQueueData(&USB_Rx_Queue, &TxBuffer[len++]);
        } else {
            break;
        }
    }
    if(len) {
        HAL_UART_Transmit(&UartHandleCellular, TxBuffer, len, 2000);//2000ms
    }
}

bool FLASH_Restore(Firmware_TypeDef FmType)
{
    bool result;
    uint32_t size;

    if(DEFAULT_FIRWARE == FmType) {
        size = HAL_PARAMS_Get_Boot_def_app_size();
        if(0 == size) {
            //size = FIRMWARE_IMAGE_SIZE;
            size = 0x40000; //默认程序没有这么，为了缩短恢复默认程序，大小修改成256k
        }
        result = FLASH_CopyMemory(FLASH_SERIAL, EXTERNAL_FLASH_FAC_ADDRESS, FLASH_INTERNAL, CORE_FW_ADDRESS, size, 0, 0);
    } else {
        size = HAL_PARAMS_Get_Boot_ota_app_size();
        if(0 == size) {
            return true;
        }
        result = FLASH_CopyMemory(FLASH_SERIAL, EXTERNAL_FLASH_OTA_ADDRESS, FLASH_INTERNAL, CORE_FW_ADDRESS, size, 0, 0);
    }
    return result;
}

bool DEFAULT_Flash_Reset(void)
{
    return FLASH_Restore(DEFAULT_FIRWARE);
}

bool OTA_Flash_Reset(void)
{
    return FLASH_Restore(OTA_FIRWARE);
}

void Enter_Default_RESTORE_Mode(void)
{
    HAL_UI_RGB_Blink(RGB_COLOR_YELLOW, UPDATE_BLINK_PERIOD);
    if(DEFAULT_Flash_Reset()) {
        HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_NORMAL);
        HAL_PARAMS_Save_Params();
    } else {
        System_Reset();
    }
}

void Enter_Serail_Com_Mode(void)
{
    HAL_UI_RGB_Color(RGB_COLOR_BLUE);
    HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_NORMAL);
    HAL_PARAMS_Save_Params();
    USBD_CDC_Init();
    while (1)
    {
        USBD_CDC_Process();
    }
}

void Enter_Factory_RESTORE_Mode(void)
{
    HAL_UI_RGB_Blink(RGB_COLOR_YELLOW, UPDATE_BLINK_PERIOD);
    HAL_PARAMS_Set_Boot_initparam_flag(INITPARAM_FLAG_FACTORY_RESET);
    HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_NORMAL);
    HAL_PARAMS_Save_Params();
}

void Enter_OTA_Update_Mode(void)
{
    HAL_UI_RGB_Blink(RGB_COLOR_YELLOW, UPDATE_BLINK_PERIOD);
    if(OTA_Flash_Reset()) {
        HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_NORMAL);
        HAL_PARAMS_Save_Params();
    } else {
        System_Reset();
    }
}

void Enter_DFU_Mode(void)
{
    HAL_UI_RGB_Color(RGB_COLOR_MAGENTA);
    USBD_DFU_Init();
    while(1)
    {}
}

void Enter_Cellular_Update_Mode(void)
{
    HAL_UI_RGB_Color(RGB_COLOR_RED);
    Cellular_Enter_UpdateMode_Pre();
    while (1)
    {
        if (!HAL_UI_Mode_BUTTON_GetState(BUTTON1)) {
            Cellular_Enter_UpdateMode();
        }
    }
}

void Enter_Flash_Test(void)
{
    sFLASH_Init();
    uint32_t success_count = 0, failed_count = 0;
    int result =0;
    while(1) {
        result = sFLASH_SelfTest();
        if(0 == result) {
            success_count ++;
        } else {
            failed_count ++;
        }
        //BOOT_DEBUG("success_count = %d, failed_count = %d\r\n", success_count, failed_count);
        delay(1000);
    }
}

