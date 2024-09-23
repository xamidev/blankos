void user_syscall(int syscall_no) {
	asm volatile ("mov %0, %%eax" : : "r"(syscall_no));
	asm volatile ("int $0x80"); 
}

void main()
{
	user_syscall(1);
	return;
}
