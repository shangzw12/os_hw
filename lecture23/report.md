
###键盘输入
>尚智伟 2012011366

>执行过程

	trap_dispatch(){case IRQ_OFFSET + IRQ_KBD}判断中断类型并响应=>
	cons_getc()返回终端输入的字符=>
	kbd_instr()尝试从键盘读取字符=>
	cons_intr(kbd_proc_data),其中kbd_proc_data为真正的从键盘读取字符函数
	
		