#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <string>
#include <vector>

namespace bf
{
    class Arguments
    {
    public:
        explicit Arguments(int argc, char* argv[]) :
            m_args{}
        {
            for (int i{1}; i < argc; ++i)
                m_args.push_back(argv[i]);
        }

        ~Arguments() = default;

        Arguments(Arguments const&) = default;
        Arguments(Arguments&&) = default;

        Arguments& operator=(Arguments const&) = default;
        Arguments& operator=(Arguments&&) = default;

        bool hasLong(std::string const& arg_name) const
        {
            std::string const long_arg{"--" + arg_name};
            for (auto const& i : m_args)
            {
                if (i == long_arg)
                    return true;
            }
            return false;
        }

        std::size_t count() const
        {
            return m_args.size();
        }

        std::string get(std::size_t const pos) const
        {
            if (pos < m_args.size())
                return m_args[pos];
            return std::string{};
        }

    private:
        std::vector<std::string> m_args{};
    };
}

#endif // ARGUMENTS_HPP
