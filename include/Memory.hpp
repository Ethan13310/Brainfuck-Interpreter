#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <exception>
#include <vector>

class Memory
{
public:
	using byte_t = unsigned char;

	explicit Memory(std::size_t size = 1024) :
		m_data(size, 0),
		m_ptr{0}
	{}

	~Memory() = default;

	Memory(Memory const&) = default;
	Memory(Memory&&) = default;

	Memory& operator=(Memory const&) = default;
	Memory& operator=(Memory&&) = default;

	void set(byte_t const value)
	{
		if (m_ptr >= size())
			resize(m_ptr + 1);
		m_data[m_ptr] = value;
	}

	byte_t get() const
	{
		if (m_ptr >= size())
			return 0;
		return m_data[m_ptr];
	}

	std::size_t size() const
	{
		return m_data.size();
	}

	void resize(std::size_t const new_size)
	{
		if (new_size > size())
		{
			try
			{
				m_data.resize(new_size, 0);
			}
			catch (std::bad_alloc const& /*e*/)
			{
				throw std::runtime_error("Insufficient memory");
			}
		}
	}

	void increment()
	{
		++m_ptr;
	}

	void decrement()
	{
		if (m_ptr != 0)
			--m_ptr;
	}

private:
	std::vector<byte_t> m_data;
	std::size_t m_ptr;
};

#endif // MEMORY_HPP
