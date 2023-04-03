#ifndef SINGAL_SLOT_PORT_H
#define SINGAL_SLOT_PORT_H
#include <stdint.h>

void signal_slot_init(void) ;

#define TAG "signal_slot"
#define ss_malloc pvPortMalloc
#define ss_free vPortFree
#define ss_logi(...) elog_i(TAG,__VA_ARGS__)
#define ss_loge(...) elog_e(TAG,__VA_ARGS__)
#define ss_logd(...) elog_d(TAG,__VA_ARGS__)
#define ss_logw(...) elog_w(TAG,__VA_ARGS__)

void ss_lock(void);
void ss_unlock(void);

#endif
