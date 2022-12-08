#include <stdio.h>
#include <stdint.h>

int32_t	bytes2int(uint8_t *byte_value, size_t size)
{
	int		signbit;
	int		n;
	int32_t	decimal;

	decimal = 0;
	signbit = 0;
	if (byte_value[0] & 0x80)
		signbit = 1;
	n = 0;
	while (size)
	{
		if (signbit)
			decimal += ((byte_value[size - 1] ^ 0xFF) << (n * 8));
		else
			decimal += byte_value[size - 1] << (n * 8);
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
	int val;

	printf("val: %d\n", bytes2int((uint8_t *)arr + 2, 2));

	return (0);
}
