1、为啥proc.h中没有声明函数，sysproc.c在导入了proc.h头文件之后，仍然可以调用proc.c中的函数呢

答：包含在声明defs.h中


2、关闭qemu
killall qemu-system-riscv64