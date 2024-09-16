void user_printf(const char* format) {
    asm volatile ("int $0x80" : : "a"(1), "b"(format));
}

void main()
{
	user_printf("Hello, world, from a PROGRAM!\n");
	return;
}
