#include <exception>
#include <iostream>

#include "BFInterpreter.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 3)
	{
		std::cout << "Usage: ./brainfck <file_path> [<memory_size> | --dump]" << std::endl;
		return 1;
	}

	try
	{
		BFInterpreter interpreter{argc, argv};
		interpreter.load();
		interpreter.exec();
		return 0;
	}
	catch (std::bad_alloc const& /*e*/)
	{
		#ifdef __linux__
			std::cerr << "[ \e[1;31merror\e[0m ] Insufficient memory" << std::endl;
		#else
			std::cerr << "[ error ] Insufficient memory" << std::endl;
		#endif
	}
	catch (std::exception const& e)
	{
		#ifdef __linux__
			std::cerr << "[ \e[1;31merror\e[0m ] " << e.what() << std::endl;
		#else
			std::cerr << "[ error ] " << e.what() << std::endl;
		#endif
	}
	return 1;
}
