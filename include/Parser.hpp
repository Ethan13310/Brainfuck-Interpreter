#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "Memory.hpp"

namespace bf
{
    class Parser
    {
    public:
        Parser() = default;
        ~Parser() = default;

        Parser(Parser const&) = delete;
        Parser(Parser&&) = default;

        Parser& operator=(Parser const&) = delete;
        Parser& operator=(Parser&&) = default;

        void loadFromFile(std::string const& filepath);
        void loadFromMemory(std::vector<Memory::byte_t> const& code);

        void execute() const;
        void dump() const;

        bool isValidCode() const;

    private:
        std::vector<Memory::byte_t> m_instructions{};
    };
}

#endif // PARSER_HPP
