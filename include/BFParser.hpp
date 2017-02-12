#ifndef BFPARSER_HPP
#define BFPARSER_HPP

#include <string>
#include <vector>

#include "Memory.hpp"

class BFParser
{
public:
	explicit BFParser(std::string const& code);
	~BFParser() = default;

	BFParser(BFParser const&) = delete;
	BFParser(BFParser&&) = default;

	BFParser& operator=(BFParser const&) = delete;
	BFParser& operator=(BFParser&&) = default;

	bool exec(std::size_t mem_size = 1024) const;
	bool dump() const;
	bool check() const;

private:
	std::vector<Memory::byte_t> m_instructions;
};

#endif // BFPARSER_HPP
