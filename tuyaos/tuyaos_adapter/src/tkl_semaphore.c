/**
 * @file tkl_semaphore.c
 * @brief this file was auto-generated by tuyaos v&v tools, developer can add implements between BEGIN and END
 * 
 * @warning: changes between user 'BEGIN' and 'END' will be keeped when run tuyaos v&v tools
 *           changes in other place will be overwrited and lost
 *
 * @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
 * 
 */

// --- BEGIN: user defines and implements ---
#include "tkl_semaphore.h"
#include "tuya_error_code.h"
#include "tkl_system.h"

#include "portmacro.h"
#include "projdefs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// #include <semaphore.h>
#include <time.h>
#include "wlan_ui_pub.h"

typedef struct
{
    xSemaphoreHandle sem;
}TKL_SEM_MANAGE,*P_TKL_SEM_MANAGE;
// --- END: user defines and implements ---

/**
* @brief Create semaphore
*
* @param[out] handle: semaphore handle
* @param[in] sem_cnt: semaphore init count
* @param[in] sem_max: semaphore max count
*
* @note This API is used for creating semaphore.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_semaphore_create_init(TKL_SEM_HANDLE *handle, UINT_T sem_cnt, UINT_T sem_max)
{
    // --- BEGIN: user implements ---
    if(!handle) {
        return OPRT_INVALID_PARM;
    }
	
    *handle = (TKL_SEM_HANDLE)xSemaphoreCreateCounting(sem_max, sem_cnt);
    if (NULL == *handle) {
        return OPRT_OS_ADAPTER_SEM_CREAT_FAILED;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Wait semaphore
*
* @param[in] handle: semaphore handle
* @param[in] timeout: wait timeout, bet: ms. SEM_WAIT_FOREVER means wait until get semaphore
*
* @note This API is used for waiting semaphore.
*
* @return OPRT_OK on success.OPRT_OS_ADAPTER_SEM_WAIT_TIMEOUT means timeout. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_semaphore_wait(CONST TKL_SEM_HANDLE handle, UINT_T timeout)
{
    // --- BEGIN: user implements ---
    if(!handle) {
        return OPRT_INVALID_PARM;
    }
    
    BaseType_t ret;
    if (timeout == TKL_SEM_WAIT_FOREVER) {
        ret = xSemaphoreTake(handle, portMAX_DELAY);
    } else {
        UINT_T ticks = timeout / portTICK_RATE_MS;

        if (ticks == 0) {
            ticks = 1;
        }
        ret = xSemaphoreTake(handle, ticks);
    }
    if (pdTRUE != ret) {
        return OPRT_OS_ADAPTER_SEM_WAIT_FAILED;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Post semaphore
*
* @param[in] handle: semaphore handle
*
* @note This API is used for posting semaphore.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_semaphore_post(CONST TKL_SEM_HANDLE handle)
{
    // --- BEGIN: user implements ---
    if(!handle) {
        return OPRT_INVALID_PARM;
    }
    
    P_TKL_SEM_MANAGE sem_manage;
    sem_manage = (P_TKL_SEM_MANAGE)handle;

    BaseType_t ret;
    if (0 == bk_wlan_get_INT_status()) {
        ret = xSemaphoreGive(sem_manage->sem);
    } else {
        signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        ret = xSemaphoreGiveFromISR(sem_manage->sem,
                                    &xHigherPriorityTaskWoken);
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }

    if (pdTRUE != ret) {
        return OPRT_OS_ADAPTER_SEM_POST_FAILED;
    }
    
    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Release semaphore
*
* @param[in] handle: semaphore handle
*
* @note This API is used for releasing semaphore.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_semaphore_release(CONST TKL_SEM_HANDLE handle)
{
    // --- BEGIN: user implements ---
    if(!handle) {
        return OPRT_INVALID_PARM;
    }

    vSemaphoreDelete(handle);
    
    return OPRT_OK;
    // --- END: user implements ---
}

