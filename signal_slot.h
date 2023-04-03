#ifndef SIGNAL_SLOT_H
#define SIGNAL_SLOT_H

#include <stdint.h>
#include <stdbool.h>
#include "signal_slot_port.h"

#define NAME_LEN_MAX 32
#define SLOT_NUM_MAX 5

// 信号结构体
typedef struct Signal {
    char name[NAME_LEN_MAX];                  // 信号名
    void (*slots[5])(void *data);             // 槽函数数组
    uint8_t slot_count;                       // 已连接的槽函数数量
    struct Signal *next;                      // 指向下一个信号的指针
} Signal;

// 初始化信号槽框架
void signal_slot_init(void);

// 创建一个新的信号
Signal *signal_create(const char *name);

// 删除一个信号
void singal_delete(const char *name);

// 将槽函数连接到指定信号
bool signal_connect(const char *name, void (*slot_function)(void *data));

// 发射指定信号
void signal_emit(const char *name);

// 发射指定信号,带其他数据
void signal_emit_with_data(const char *name, void *data);

#endif // SIGNAL_SLOT_H