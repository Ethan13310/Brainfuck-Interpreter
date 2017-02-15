#ifndef BFINTERPRETER_HPP
#define BFINTERPRETER_HPP

#include <string>

class BFInterpreter
{
public:
	explicit BFInterpreter(int argc, char* argv[]);
	~BFInterpreter() = default;

	BFInterpreter(BFInterpreter const&) = delete;
	BFInterpreter(BFInterpreter&&) = default;

	BFInterpreter& operator=(BFInterpreter const&) = delete;
	BFInterpreter& operator=(BFInterpreter&&) = default;

	bool load();
	bool exec() const;

private:
	std::string m_file;
	std::string m_code;
	std::size_t m_mem_size;
	bool m_dump;
};

#endif // BFINTERPRETER_HPP
