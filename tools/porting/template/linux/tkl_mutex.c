/**
 * @file tkl_mutex.c
 * @brief this file was auto-generated by tuyaos v&v tools, developer can add implements between BEGIN and END
 *
 * @warning: changes between user 'BEGIN' and 'END' will be keeped when run tuyaos v&v tools
 *           changes in other place will be overwrited and lost
 *
 * @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
 *
 */

// --- BEGIN: user defines and implements ---
#include "tkl_mutex.h"
#include "tkl_memory.h"
#include "tuya_error_code.h"
#include <pthread.h>
#include <errno.h>

typedef pthread_mutex_t TKL_THRD_MUTEX;
typedef struct {
    TKL_THRD_MUTEX mutex;
} TKL_MUTEX_MANAGE, *P_TKL_MUTEX_MANAGE;
// --- END: user defines and implements ---

/**
 * @brief Create mutex
 *
 * @param[out] pMutexHandle: mutex handle
 *
 * @note This API is used to create and init mutex.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_mutex_create_init(TKL_MUTEX_HANDLE *pMutexHandle)
{
    // --- BEGIN: user implements ---
    if (!pMutexHandle)
        return OPRT_INVALID_PARM;

    P_TKL_MUTEX_MANAGE mutex_manage;
    mutex_manage = (P_TKL_MUTEX_MANAGE)tkl_system_malloc(sizeof(TKL_MUTEX_MANAGE));
    if (!(mutex_manage))
        return OPRT_MALLOC_FAILED;

    int ret;
    pthread_mutexattr_t attr;

    ret = pthread_mutexattr_init(&attr);
    if (0 != ret) {
        return OPRT_OS_ADAPTER_MUTEX_CREAT_FAILED;
    }

    ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    if (0 != ret) {
        return OPRT_OS_ADAPTER_MUTEX_CREAT_FAILED;
    }

    ret = pthread_mutex_init(&(mutex_manage->mutex), &attr);
    if (0 != ret) {
        return OPRT_OS_ADAPTER_MUTEX_CREAT_FAILED;
    }

    ret = pthread_mutexattr_destroy(&attr);
    if (0 != ret) {
        return OPRT_OS_ADAPTER_MUTEX_RELEASE_FAILED;
    }

    *pMutexHandle = (TKL_MUTEX_HANDLE)mutex_manage;

    return OPRT_OK;
    // --- END: user implements ---
}

/**
 * @brief Lock mutex
 *
 * @param[in] mutexHandle: mutex handle
 *
 * @note This API is used to lock mutex.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_mutex_lock(const TKL_MUTEX_HANDLE mutexHandle)
{
    // --- BEGIN: user implements ---
    if (!mutexHandle) {
        return OPRT_INVALID_PARM;
    }

    P_TKL_MUTEX_MANAGE mutex_manage;
    mutex_manage = (P_TKL_MUTEX_MANAGE)mutexHandle;

    int ret;
    ret = pthread_mutex_lock(&(mutex_manage->mutex));
    if (ret != 0) {
        return OPRT_OS_ADAPTER_MUTEX_LOCK_FAILED;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
 * @brief Try Lock mutex
 *
 * @param[in] mutexHandle: mutex handle
 *
 * @note This API is used to try lock mutex.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_mutex_trylock(const TKL_MUTEX_HANDLE mutexHandle)
{
    // --- BEGIN: user implements ---
    if (!mutexHandle) {
        return OPRT_INVALID_PARM;
    }

    P_TKL_MUTEX_MANAGE mutex_manage;
    mutex_manage = (P_TKL_MUTEX_MANAGE)mutexHandle;

    int ret;
    ret = pthread_mutex_trylock(&(mutex_manage->mutex));
    if (ret != 0) {
        return OPRT_OS_ADAPTER_MUTEX_LOCK_FAILED;
    }

    return OPRT_OK;
}

/**
 * @brief Unlock mutex
 *
 * @param[in] mutexHandle: mutex handle
 *
 * @note This API is used to unlock mutex.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_mutex_unlock(const TKL_MUTEX_HANDLE mutexHandle)
{
    // --- BEGIN: user implements ---
    if (!mutexHandle) {
        return OPRT_INVALID_PARM;
    }

    P_TKL_MUTEX_MANAGE mutex_manage;
    mutex_manage = (P_TKL_MUTEX_MANAGE)mutexHandle;

    int ret;
    ret = pthread_mutex_unlock(&(mutex_manage->mutex));
    if (ret != 0) {
        return OPRT_OS_ADAPTER_MUTEX_UNLOCK_FAILED;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
 * @brief Release mutex
 *
 * @param[in] mutexHandle: mutex handle
 *
 * @note This API is used to release mutex.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_mutex_release(const TKL_MUTEX_HANDLE mutexHandle)
{
    // --- BEGIN: user implements ---
    if (!mutexHandle) {
        return OPRT_INVALID_PARM;
    }

    P_TKL_MUTEX_MANAGE mutex_manage;
    mutex_manage = (P_TKL_MUTEX_MANAGE)mutexHandle;

    int ret;
    ret = pthread_mutex_destroy(&(mutex_manage->mutex));
    if (ret != 0) {
        return OPRT_OS_ADAPTER_MUTEX_RELEASE_FAILED;
    }

    tkl_system_free(mutexHandle);
    return OPRT_OK;
    // --- END: user implements ---
}
