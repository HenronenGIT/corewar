#include <stdio.h>
#include <stdint.h>
#define MEM_SIZE 4


//fix with IDX_MOD
void	write_arena(int8_t *arena, int idx, int32_t *reg)
{
	int		i;
	int8_t	*p;

	p = (int8_t *)reg;
	idx = (idx + 3) % MEM_SIZE;
	i = 0;
	while (i++ < 4)
	{
		arena[idx] = *p;
		idx = (idx - 1);
		if (idx < 0)
			idx = MEM_SIZE + idx;
		p++;
	}
}

int32_t	bytes2int(uint8_t *byte_value, int idx,  size_t size)
{
	int		signbit;
	int		n;
	int32_t	decimal;
	int		i;

	decimal = 0;
	signbit = 0;
	if (byte_value[idx] & 0x80)
		signbit = 1;
	printf("signbit: %d\n", signbit);
	n = 0;
	while (size)
	{
		i = (idx + (size - 1)) % MEM_SIZE;
		printf("i: %d\n", i);
		if (signbit)
			decimal += ((byte_value[i] ^ 0xFF) << (n * 8));
		else
			decimal += byte_value[i] << (n * 8);
		n++;
		size--;
	}
	if (signbit)
		decimal = ~(decimal);
	return (decimal);
}

int main ()
{
	int8_t arr[4] = {0xff, 0x01, 0x22, 0x00};
	int32_t val = 0xaabbccdd;

	printf("val: %d\n", bytes2int((uint8_t *)arr, 0, 4));

	for (int i = 0; i < MEM_SIZE; i++)
		printf("%.2x ", (uint8_t)arr[i]);
	printf("\n");
	write_arena(arr, 3, &val);
	for (int i = 0; i < MEM_SIZE; i++)
		printf("%.2x ", (uint8_t)arr[i]);
	printf("\n");

	return (0);
}
