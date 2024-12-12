#include <iostream>
#include <cstdio>
#include <type_traits>
#include <string>
#include <vector>
#include <list>

template<typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
void print_ip(T n) {
	for (size_t i = 1; i < sizeof(T); i++)
	{
		int f = (n >> (sizeof(T) * 8 - (8 * i))) & 0xFF;
		std::printf("%d.", f);
	}
	int f = (n >> (sizeof(T) * 8 - (8 * sizeof(T)))) & 0xFF;
	std::printf("%d", f);
	std::cout << "\n";
};
template<typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
void operator>>(T& lhs, T& rhs)
{
	lhs >> rhs;
}

template<typename T, typename std::enable_if<std::is_same<T, std::string>::value, bool>::type = true>
void print_ip(T s) {
	std::cout << s.c_str();
	std::cout << "\n";
};

template <typename T, typename = void>
struct has_begin : std::false_type {};

template <typename T>
struct has_begin < T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {};

template<typename T, typename std::enable_if<has_begin<T>::value, int>::type = 0,
	typename std::enable_if<!std::is_same<T, std::string>::value, bool>::type = true>
void print_ip(T x)
{
	auto it = std::begin(x);
	auto end = std::end(x);

	if (it != end) {
		for (; it != std::prev(end); ++it) {
			std::cout << *it << ".";
		}
		std::cout << *it;
	}
	std::cout << "\n";
}

int main() {
	print_ip(int8_t{ -1 });
	print_ip(int16_t{ 0 });
	print_ip(int32_t{ 2130706433 });
	print_ip(int64_t{ 8875824491850138409 });
	print_ip(std::string{ "Hello, world!" });
	print_ip(std::vector<int>{100, 200, 300, 400});
	print_ip(std::list<short>{400, 300, 200, 100});
	return 0;
};