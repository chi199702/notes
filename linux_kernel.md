# Linux Kernel Development

> “对内核各个核心子系统有个整体把握，包括它们提供什么样的服务，为什么要提供这样的服务，又是怎样实现的”

## 一、Linux 内核简介

**Linux 是类 Unix 系统，但它不是 Unix。**Linux 借鉴了 Unix 的许多设计并且实现了 Unix 的 API，但 Linux 没有像其他 Unix 变种那样直接使用 Unix 的源代码。必要的时候，Linux 的实现可能和其他各种 Unix 的实现大相径庭，**但它没有抛弃 Unix 的设计目标并且保证了应用程序编程接口的一致。**

Linux 系统的基础是内核、C 库、工具集和系统的基本工具，**通常一个内核由负责响应中断的中断服务程序，负责管理多个进程从而分享处理器时间的调度程序，负责管理进程地址空间的内存管理程序和网络、进程间通信等系统服务程序共同组成。**

## 二、从内核出发

<div style="text-align:center;"><b>内核源码树的根目录描述-Linux 2.6</b></div>

| 目录          | 描述                                 |
| ------------- | ------------------------------------ |
| arch          | 特定体系结构的源码                   |
| block         | 块设备 I/O 层                        |
| crypto        | 加密 API                             |
| Documentation | 内核源码文档                         |
| drivers       | 设备驱动程序                         |
| fireware      | 使用某些驱动程序而需要的设备固件     |
| fs            | VFS 和各种文件系统                   |
| include       | 内核头文件                           |
| init          | 内核引导和初始化                     |
| ipc           | 进程间通信代码                       |
| kernel        | 像调度程序这样的核心子系统           |
| lib           | 通用内核函数                         |
| mm            | 内存管理子系统和 VM                  |
| net           | 网络子系统                           |
| samples       | 示例，示范代码                       |
| scripts       | 编译内核所用的脚本                   |
| security      | Linux 安全模块                       |
| sound         | 语音子系统                           |
| usr           | 早期用户空间代码（所谓的 initramfs） |
| tools         | 在 Linux 开发中有用的工具            |
| virt          | 虚拟化基础结构                       |

内核开发不同于用户空间内应用程序开发的点：

+ 编程时不能访问 C 库，也不能访问标准的 C 头文件
+ 编程时必须使用 GNU C
+ 编程时缺乏像用户空间那样的内存保护机制
+ 编程时难以执行浮点运算
+ 内核给每个进程只有一个很小的定长堆栈
+ 内核支持异步中断、抢占和 SMP，因此必须时刻注意同步和并发
+ 要考虑可移植性的重要性

## 三、进程管理

> 进程是处于执行期的程序以及相关资源的总称

内核通过**双向循环链表**来存储进程描述符，进程描述符**完整**的描述了一个正在执行的程序：它打开的文件、挂起的信号、进程的地址空间、进程状态等。

内核会为每个进程分配一个内核栈，当进程陷入内核时，系统调用函数使用的是内核栈。

![123](https://raw.githubusercontent.com/chi199702/notes/main/image/thread_kernel_stack.png)

```c
union thread_union {
    struct thread_info thread_info;
    unsigned long stack[THREAD_SIZE / sizeof(long)];
}
```

`struct thread_info`位于栈底，和内核栈**共享同一片空间**。

`struct thread_info`

