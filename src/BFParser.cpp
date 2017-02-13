#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Memory.hpp"
#include "BFParser.hpp"

BFParser::BFParser(std::string const& code) :
	m_instructions{}
{
	std::array<Memory::byte_t, 8> const valid_insts{
		'<', '>', '+', '-',
		'.', ',', '[', ']'
	};

	// load valid instructions
	for (auto const inst : code)
	{
		if (std::find(valid_insts.begin(), valid_insts.end(), inst) != valid_insts.end())
			m_instructions.push_back(inst);
	}
}

bool BFParser::exec(std::size_t const mem_size) const
{
	// program memory
	Memory memory{mem_size};

	// loop start addresses stack
	std::stack<std::size_t> loop_stack{};

	for (std::size_t inst_ptr{0}; inst_ptr < m_instructions.size(); ++inst_ptr)
	{
		// inner loop counter (see case '[' and ']')
		std::size_t loop_count{0};

		switch (m_instructions[inst_ptr])
		{
		case '>':
			memory.increment();
			break;

		case '<':
			memory.decrement();
			break;

		case '+':
			memory.set(memory.get() + 1);
			break;

		case '-':
			memory.set(memory.get() - 1);
			break;

		case '.':
			std::cout << memory.get() << std::flush;
			break;

		case ',':
			memory.set(std::cin.get());
			if (memory.get() == '\n') // EOL
				memory.set('\0');
			break;

		case '[':
			if (!memory.get())
			{
				++inst_ptr;

				// jump to ']'
				while (inst_ptr < m_instructions.size() && (m_instructions[inst_ptr] != ']' || loop_count != 0))
				{
					// handle inner loops
					if (m_instructions[inst_ptr] == '[')
						++loop_count;
					else if (m_instructions[inst_ptr] == ']')
						--loop_count;

					++inst_ptr;
				}

				if (inst_ptr == m_instructions.size())
					throw std::runtime_error("Bad-formed loop");
			}
			else
				loop_stack.push(inst_ptr);
			break;

		case ']':
			if (!loop_stack.empty())
			{
				if (memory.get())
					inst_ptr = loop_stack.top();
				else
					loop_stack.pop();
			}
			else
				throw std::runtime_error("Bad-formed loop");
			break;

		default:
			throw std::runtime_error("Illegal instruction");
		}
	}

	return true;
}

bool BFParser::dump() const
{
	if (!check())
		throw std::runtime_error("Bad-formed loop");

	std::size_t indent_level{0};

	auto new_line = [&indent_level]() {
		std::cout << std::endl;
		for (std::size_t i{0}; i < indent_level * 4; ++i)
			std::cout << ' ';
	};

	// printing the code
	for (auto const inst : m_instructions)
	{
		switch (inst)
		{
		case '[':
			new_line();
			std::cout << inst;
			++indent_level;
			new_line();
			break;

		case ']':
			--indent_level;
			new_line();

		case '.':
		case ',':
			std::cout << inst;
			new_line();
			break;

		default:
			std::cout << inst;
		}
	}
	std::cout << std::endl;

	return true;
}

bool BFParser::check() const
{
	std::size_t loop_count{0};

	// checks if loops are well-formed
	for (auto const inst : m_instructions)
	{
		if (inst == '[')
			++loop_count;
		else if (inst == ']')
		{
			if (loop_count == 0)
				return false;
			--loop_count;
		}
	}

	return (loop_count == 0);
}
