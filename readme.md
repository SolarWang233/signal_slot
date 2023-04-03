# Signal-Slot Framework

这是一个基于C语言实现的简单信号槽框架，用于事件驱动编程。本框架支持信号注册表的创建、删除、信号槽连接、信号发射等基本功能。

## 如何移植

1. 将`signal_slot.h`, `signal_slot.c`, `signal_slot_port.h`和`signal_slot_port.c`这四个文件添加到您的项目中。

2. 根据实际情况，修改`signal_slot_port.h`文件中的互斥量实现、内存分配和日志输出宏定义。例如，您可能需要将互斥量实现替换为您所使用RTOS的实现，或将日志输出调整为适合您的硬件平台。

## 如何使用

以下是一个简单的示例，展示了如何使用信号槽框架：

```c
#include <stdio.h>
#include "signal_slot.h"
#include "signal_slot_port.h"

// 定义一个槽函数
void slot_function(void *data)
{
    printf("Slot function called with data: %p\n", data);
}

int main(void)
{
    // 初始化信号槽框架
    signal_slot_init();

    // 创建一个信号
    Signal *test_signal = signal_create("test_signal");

    // 将槽函数连接到信号
    bool connected = signal_connect("test_signal", slot_function);

    if (!connected)
    {
        printf("Failed to connect slot_function to test_signal\n");
        return -1;
    }

    // 发射信号
    signal_emit_with_data("test_signal", (void *)0x12345678);

    return 0;
}
```

# 更多信息 
请参考源代码文件中的注释以获取有关实现细节的更多信息。如果您在使用过程中遇到问题，请随时提交Issue或Pull Request。

# 许可证 
本项目采用MIT许可证，详情请参阅LICENSE文件。