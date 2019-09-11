#include "std/buffer.h"
#include "std/mem.h"
#include "std/str.h"

size_t test_count = 0;
size_t test_err = 0;

void
test_init(void)
{
	buffer_puts(buffer_1, "Starting the tests...");
	buffer_flush(buffer_1);
}

void
test_lib(char const *s)
{
	buffer_puts(buffer_1, "\n\nsrc/");
	buffer_puts(buffer_1, s);
	buffer_puts(buffer_1, ".t");
	buffer_flush(buffer_1);
}

void
test_fn(char const *s)
{
	buffer_puts(buffer_1, "\n - ");
	buffer_puts(buffer_1, s);
	buffer_pad(buffer_1, s, ' ', 25);
	buffer_flush(buffer_1);
}

void
test(int i, int ok)
{
	test_err += !ok;
	test_count++;

	if (ok) {
		buffer_puts(buffer_1, " ..");
	} else {
		buffer_puts(buffer_1, " !");
		buffer_putn(buffer_1, i);
	}
	buffer_flush(buffer_1);
}

void
test_summary(void)
{
	buffer_puts(buffer_1, "\n\n => ");
	buffer_putn(buffer_1, test_count - test_err);
	buffer_puts(buffer_1, "/");
	buffer_putn(buffer_1, test_count);
	buffer_puts(buffer_1, " tests passed\n\n");
	buffer_flush(buffer_1);
}
