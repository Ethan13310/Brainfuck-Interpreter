#include <fstream>
#include <iostream>
#include <string>

#include "BFParser.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 3)
	{
		std::cout << "Usage: ./brainfck <file_path> [<memory_size> | --dump]" << std::endl;
		return 1;
	}

	// load file
	std::ifstream ifs{argv[1]};
	if (!ifs.is_open())
	{
		std::cerr << "[ err  ] The specified file cannot be opened" << std::endl;
		return 1;
	}

	std::string const code{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
	std::size_t mem_size{4096}; // default size = 4 Kio

	if (argc == 3 && std::string{argv[2]} != "--dump")
	{
		// use custom memory size
		try
		{
			int const size{std::stoi(argv[2])};

			if (size < 2 || size > 512 * 1024 * 1024) // max 512 Mio
				throw std::invalid_argument("Invalid memory size");

			mem_size = size;
		}
		catch (std::exception const& /*e*/)
		{
			std::cout << "[ warn ] Specified memory size is invalid" << std::endl;
			std::cout << "[ info ] Default memory size will be used (" << mem_size << " bytes)" << std::endl;
			std::cout << std::endl;
		}
	}

	try
	{
		BFParser parser{code};

		if (argc == 3 && std::string{argv[2]} == "--dump")
			parser.dump();
		else
			parser.exec(mem_size);
	}
	catch (std::runtime_error const& e)
	{
		std::cerr << std::endl;
		std::cerr << "[ err  ] " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
