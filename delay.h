#include <stdint.h>
static long sys_time=0;

uint32_t milis(void)
{
		float ms;
		ms = sys_time;
		return ms;
}

void _delay_ms(uint32_t ms)
{
    uint32_t now = milis();
    while (milis() - now < ms);
}
