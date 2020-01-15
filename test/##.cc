#include <iostream>
#define TEXT(x)  "class"#x"Info"
#define HTP_RELAYER_HOST(idx) "relayer_host"#idx
int main()
{
	std::cout << HTP_RELAYER_HOST(2) << std::endl;
	return 0;
}