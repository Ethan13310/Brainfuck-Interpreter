#ifndef PARSER_HPP
#define PARSER_HPP

#include <chrono>
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

        void execute();
        void dump() const;

        bool isValidCode() const;

        std::chrono::nanoseconds lastExecutionTime() const;

    private:
        std::vector<Memory::byte_t> m_instructions{};
        std::chrono::nanoseconds m_exec_time{};
    };
}

#endif // PARSER_HPP
