#include <exception>
#include <iostream>

#include "Arguments.hpp"
#include "Parser.hpp"

int main(int argc, char* argv[])
{
    bf::Arguments args{argc, argv};

    if (args.hasLong("help") || args.count() == 0 || args.count() > 2)
    {
        std::cout << "Usage: ./brainfck <file_path> [--dump]" << std::endl;
        return 1;
    }

    try
    {
        bf::Parser parser{};
        parser.loadFromFile(args.get(0));
        if (args.hasLong("dump"))
            parser.dump();
        else
            parser.execute();
        return 0;
    }
    catch (std::runtime_error const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (std::bad_alloc const& /*e*/)
    {
        std::cerr << "Error: Insufficient memory" << std::endl;
    }
    return 1;
}
