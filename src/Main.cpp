#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>

#include "Arguments.hpp"
#include "Parser.hpp"

int main(int argc, char* argv[])
{
    bf::Arguments args{argc, argv};

    if (args.hasLong("help") || args.count() == 0 || args.count() > 2)
    {
        std::cout << "Usage: ./brainfck <file_path> [--dump | --time]" << std::endl;
        return 1;
    }

    try
    {
        bf::Parser parser{};
        parser.loadFromFile(args.get(0));
        if (args.hasLong("dump"))
            parser.dump();
        else
        {
            parser.execute();
            if (args.hasLong("time"))
            {
                std::cout << "\nProgram terminated" << std::fixed << std::setprecision(3);
                double const exec_time = parser.lastExecutionTime().count() / 1000000000.0;
                std::cout << "\nExecution time: " << exec_time << "s" << std::endl;
            }
        }
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
