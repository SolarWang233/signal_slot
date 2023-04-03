#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "signal_slot.h"
static Signal *signal_registry = NULL;  // 信号注册表

// 创建一个新的信号
Signal *signal_create(const char *name) {
    ss_lock();

    Signal *current = signal_registry;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            ss_logi("Signal '%s' already exists.\r\n", name);
            ss_unlock();
            return current;
        }
        current = current->next;
    }

    Signal *new_signal = (Signal *)ss_malloc(sizeof(Signal));
    strncpy(new_signal->name, name, sizeof(new_signal->name) - 1);
    new_signal->name[sizeof(new_signal->name) - 1] = '\0';
    new_signal->slot_count = 0;
    new_signal->next = NULL;
    if (signal_registry == NULL) {
        signal_registry = new_signal;
    } else {
        Signal *last = signal_registry;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_signal;
    }

    ss_unlock();

    return new_signal;
}

void singal_delete(const char *name) {
    ss_lock();
    Signal *current = signal_registry;
    Signal *previous = NULL;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            ss_logi("find signal '%s and delete it.\r\n", name);
            previous->next = current->next;
            ss_free(current);
            if (current == signal_registry) {
                signal_registry = NULL;
            }
            ss_unlock();
            return;
        }
        previous = current;

        current = current->next;
    }
    ss_loge("delete signal %s error !signal not found \r\n", name);
    ss_unlock();
}

// 将槽函数连接到指定信号
bool signal_connect(const char *name, void (*slot_function)(void *data)) {
    ss_lock();

    Signal *current = signal_registry;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->slot_count <
                sizeof(current->slots) / sizeof(current->slots[0])) {
                current->slots[current->slot_count++] = slot_function;
                ss_unlock();
                return true;
            } else {
                ss_loge("No more slots available for signal '%s'.\r\n", name);
                ss_unlock();
                return false;
            }
        }
        current = current->next;
    }

    ss_loge("connect signal to slot error! Signal '%s' not found.\r\n", name);
    ss_unlock();
    return false;
}

// 发射指定信号
void signal_emit(const char *name) {
    ss_lock();

    Signal *current = signal_registry;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            for (uint8_t i = 0; i < current->slot_count; i++) {
                current->slots[i](NULL);
            }
            ss_unlock();
            return;
        }
        current = current->next;
    }

    ss_loge("emit signal error '%s' is not found.\r\n", name);
    ss_unlock();
}

void signal_emit_with_data(const char *name, void *data) {
    ss_lock();

    Signal *current = signal_registry;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            for (uint8_t i = 0; i < current->slot_count; i++) {
                current->slots[i](data);
            }
            ss_unlock();
            return;
        }
        current = current->next;
    }

    ss_loge("emit signal error '%s' is not found.\r\n", name);
    ss_unlock();
}