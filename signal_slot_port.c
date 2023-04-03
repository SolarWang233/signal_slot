#include <stdarg.h>
#include "signal_slot_port.h"
#define LOG_TAG "signal_slot"
#include "elog.h"
#include "FreeRTOS.h"
#include "semphr.h"
static SemaphoreHandle_t registry_mutex; // 信号注册表互斥量
// 初始化信号槽框架
void signal_slot_init(void) {
    // 申请一个互斥量，ss_lock,ss_unlock需要用到
    registry_mutex = xSemaphoreCreateMutex();
}

void ss_lock(void)
{
    xSemaphoreTake(registry_mutex, portMAX_DELAY);
}

void ss_unlock(void)
{
    xSemaphoreGive(registry_mutex);
}