#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <vector>

#include <cstdint>
#include <cassert>

// GrowableStack is a stack that grows (allocates more memory through std::vector), but never shrinks
// this is PROBABLY how std::stack behaves, too, in our situation, but we have our own here
// for more performance certainty
template <typename T>
class GrowableStack
{
public:
	GrowableStack() : m_data(1), m_size(0) {}

	void Push(const T &x)
	{
		if (m_size == m_data.size())
		{
			m_data.resize(m_data.size() * 2);
		}

		m_data[m_size] = x;
		++m_size;
	}

	T Pop()
	{
#ifdef DEBUG
		assert(m_size > 0);
#endif
		--m_size;
		return m_data[m_size];
	}

	T &Top()
	{
#ifdef DEBUG
		assert(m_size > 0);
#endif
		return m_data[m_size - 1];
	}

	void Clear()
	{
		m_size = 0;
	}

	size_t GetSize() const { return m_size; }

	T &operator[](size_t i)
	{
#ifdef DEBUG
		assert(i < m_size);
#endif
		return m_data[i];
	}

	const T &operator[](size_t i) const
	{
#ifdef DEBUG
		assert(i < m_size);
#endif
		return m_data[i];
	}

	// make sure there is enough space for another element
	// increment size, and return reference to that element (the element needs to be constructed by the caller)
	T &PrePush()
	{
		if (m_size == m_data.size())
		{
			m_data.resize(m_data.size() * 2);
		}

		return m_data[m_size++];
	}

private:
	std::vector<T> m_data;
	size_t m_size;
};

// these are fast fixed-size containers that don't use the heap

template <typename T, uint32_t MAX_SIZE>
class FixedStack
{
public:
	FixedStack() : m_size(0) {}

	void Push(const T &x)
	{
#ifdef DEBUG
		assert(m_size < MAX_SIZE);
#endif
		m_data[m_size] = x;
		++m_size;
	}

	T Pop()
	{
#ifdef DEBUG
		assert(m_size > 0);
#endif
		--m_size;
		return m_data[m_size];
	}

	T &Top()
	{
#ifdef DEBUG
		assert(m_size > 0);
#endif
		return m_data[m_size - 1];
	}

	void Clear()
	{
		m_size = 0;
	}

	size_t GetSize() { return m_size; }

private:
	T m_data[MAX_SIZE];
	size_t m_size;
};

template <typename T, uint32_t MAX_SIZE>
class FixedVector
{
public:
	FixedVector(size_t size) : m_size(size) {}
	FixedVector() : FixedVector(0) {}

	void PushBack(const T &x)
	{
#ifdef DEBUG
		assert(m_size < MAX_SIZE);
#endif
		m_data[m_size] = x;
		++m_size;
	}

	T &operator[](size_t i)
	{
#ifdef DEBUG
		assert(i < MAX_SIZE); // we do intentionally violate (i < m_size) in SEE
#endif
		return m_data[i];
	}

	void Clear()
	{
		m_size = 0;
	}

	size_t GetSize() { return m_size; }

private:
	T m_data[MAX_SIZE];
	size_t m_size;
};

#endif // CONTAINERS_H
