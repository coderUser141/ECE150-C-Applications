#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

unsigned int add_checksum(unsigned int n);
void add_checksum(unsigned int (&array)[], std::size_t capacity);
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);
void remove_checksum(unsigned int (&array)[], std::size_t capacity);

unsigned int checksum_calculation(unsigned int in);

unsigned int add_checksum(unsigned int n) {
	if (n <= 99999999) {
		unsigned int temp = n * 10;
		return temp + checksum_calculation(n);
	} else {
		return UINT_MAX;
	}
}

void add_checksum(unsigned int (&array)[], std::size_t capacity) {
	for (int i = 0; i < capacity; ++i) {
		array[i] = add_checksum(array[i]);
	}
}

bool verify_checksum(unsigned int n) {
	int d = n % 10;
	if (n > 999999999 || d != checksum_calculation(n)) {
		return false;
	} else {
		return true;
	}
}

unsigned int remove_checksum(unsigned int n) {
	int d = n % 10;
	if (n > 999999999 || d != checksum_calculation(n)) {
		return UINT_MAX;
	} else {
		return n / 10;
	}
}

void remove_checksum(unsigned int (&array)[], std::size_t capacity) {
	for (int i = 0; i < capacity; ++i) {
		array[i] = remove_checksum(array[i]);
	}
}



unsigned int checksum_calculation(unsigned int in) {
	//return value is 9 digits, input is 8 digits
	unsigned int a[8];
	unsigned int b = in;
	unsigned int c[8] = { 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 };
	unsigned int d{ 0 };
	for (int i = 0; i < 8; ++i) {
		a[7 - i] = b / c[i];
		b = b - a[7 - i] * c[i];
	} //setting array value backwards for easier computation

	for (int j = 0; j < 8; ++j) { //performing the algorithm
		if ((j % 2) == 0) {
			if ((a[j] * 2) > 9) {
				int temp = a[j] * 2;
				int temp_tens = temp / 10;
				int temp_ones = temp - (temp_tens * 10);
				temp = temp_tens + temp_ones;
				a[j] = temp;
			} else {
				a[j] *= 2;
			}
		}
		d += a[j];
	}
	d *= 9;
	d %= 10;

	return d;
}

#ifndef MARMOSET_TESTING
int main() {
	unsigned int value_to_protect{ 21352411 };
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;

	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	} else {
		std::cout << "The checksum is invalid." << std::endl;
	}
	const std::size_t QTY_VALUES{ 3 };
	unsigned int value_series[QTY_VALUES]{ 20201122, 20209913, 20224012 };

	add_checksum(value_series, QTY_VALUES);

	std::cout << "Series with checksums added: ";
	for (std::size_t series_index{ 0 };
		 series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

	std::cout << std::endl;
	return 0;
}
#endif