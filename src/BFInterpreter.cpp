#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "BFParser.hpp"
#include "BFInterpreter.hpp"

BFInterpreter::BFInterpreter(int argc, char* argv[]) :
	m_file{},
	m_code{},
	m_mem_size{4096},
	m_dump{false}
{
	// load args
	std::vector<std::string> args{};
	for (int i{1}; i < argc; ++i)
		args.push_back(argv[i]);

	// file path
	if (args.size() >= 1)
		m_file = args[0];

	// memory size or --dump option
	if (args.size() >= 2)
	{
		if (args[1] == "--dump")
			m_dump = true;
		else
		{
			try
			{
				int const size{std::stoi(args[1])};
				if (size > 0)
					m_mem_size = size;
			}
			catch (std::exception const& /*e*/)
			{}
		}
	}
}

bool BFInterpreter::load()
{
	// load file
	std::ifstream ifs{m_file};
	if (!ifs.is_open())
		throw std::runtime_error("The specified file cannot be opened");

	m_code = std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
	return true;
}

bool BFInterpreter::exec() const
{
	BFParser parser{m_code};

	if (m_dump)
		return parser.dump();
	else
		return parser.exec(m_mem_size);
}
