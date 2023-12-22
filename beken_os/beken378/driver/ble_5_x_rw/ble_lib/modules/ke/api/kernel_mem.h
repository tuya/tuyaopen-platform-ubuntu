/**
 ****************************************************************************************
 *
 * @file kernel_mem.h
 *
 * @brief API for the heap management module.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef _KERNEL_MEM_H_
#define _KERNEL_MEM_H_

#include "rwip_config.h"     // IP configuration
#include <stdint.h>          // standard integer
#include <stdbool.h>         // standard includes

/**
 ****************************************************************************************
 * @defgroup MEM Memory
 * @ingroup KERNEL
 * @brief Heap management module.
 *
 * This module implements heap management functions that allow initializing heap,
 * allocating and freeing memory.
 *
 * @{
 ****************************************************************************************
 */

#define KERNEL_MEM_DEBUG 0

#define BK_BLE_ASSERT_MEM_CORRUPT_ERR_POS       1
#define BK_BLE_ASSERT_MEM_NO_SPACE_POS          2

/*
 *BIT 0--------->BK_BLE_ASSERT_MEM_CORRUPT_ERR
 *BIT 1--------->BK_BLE_ASSERT_MEM_NO_SPACE
 *others-------->NONE
*/
uint8_t bk_ble_mem_assert_type_cb(uint8_t clear);



// forward declarations
struct mblock_free;

/**
 ****************************************************************************************
 * @brief Heap initialization.
 *
 * This function performs the following operations:
 * - sanity checks
 * - check memory allocated is at least large enough to hold two block descriptors to hold
 * start and end
 * - initialize the first and last descriptors
 * - save heap into kernel environment variable.
 *
 * @param[in]     type      Memory type.
 * @param[in|out] heap      Heap pointer
 * @param[in]     heap_size Size of the heap
 *
 *
 ****************************************************************************************
 */
void kernel_mem_init(uint8_t type, uint8_t* heap, uint16_t heap_size);

/**
 ****************************************************************************************
 * @brief Allocation of a block of memory.
 *
 * Allocates a memory block whose size is size; if no memory is available return NULL
 *
 * @param[in] size Size of the memory area that need to be allocated.
 * @param[in] type Type of memory block
 *
 * @return A pointer to the allocated memory area.
 *
 ****************************************************************************************
 */
#if KERNEL_MEM_DEBUG
void *kernel_malloc_debug(uint32_t size, uint8_t type,const char *func, uint32_t line);
#define kernel_malloc(size, type) kernel_malloc_debug(size, type, __FUNCTION__, __LINE__)
#else
void *kernel_malloc(uint32_t size, uint8_t type);
#endif

/**
 ****************************************************************************************
 * @brief Check if it's possible to allocate a block of memory with a specific size.
 *
 * @param[in] size Size of the memory area that need to be allocated.
 * @param[in] type Type of memory block
 *
 * @return True if memory block can be allocated, False else.
 *
 ****************************************************************************************
 */
bool kernel_check_malloc(uint32_t size, uint8_t type);

/**
 ****************************************************************************************
 * @brief Freeing of a block of memory.
 *
 * Free the memory area pointed by mem_ptr : mark the block as free and insert it in
 * the pool of free block.
 *
 * @param[in] mem_ptr Pointer to the memory area that need to be freed.
 *
 ****************************************************************************************
 */
void kernel_free(void *mem_ptr);


/**
 ****************************************************************************************
 * @brief Check if current heap is empty or not (not used)
 *
 * @param[in] type Type of memory heap block
 *
 * @return true if heap not used, false else.
 ****************************************************************************************
 */
bool kernel_mem_is_empty(uint8_t type);



/**
 ****************************************************************************************
 * @brief Check if current pointer is free or not
 *
 * @param[in] mem_ptr pointer to a memory block
 *
 * @return true if already free, false else.
 ****************************************************************************************
 */
bool kernel_is_free(void* mem_ptr);

#if (KERNEL_PROFILING)

/**
 ****************************************************************************************
 * @brief Retrieve memory usage of selected heap.
 *
 * @param[in] type Type of memory heap block
 *
 * @return current memory usage of current heap.
 ****************************************************************************************
 */
uint16_t kernel_get_mem_usage(uint8_t type);


/**
 ****************************************************************************************
 * @brief Retrieve max memory usage of all heap.
 * This command also resets max measured value.
 *
 * @return max memory usage of all heap.
 ****************************************************************************************
 */
uint32_t kernel_get_max_mem_usage(void);

#endif // (KERNEL_PROFILING)

///@} MEM

#endif // _KERNEL_MEM_H_

