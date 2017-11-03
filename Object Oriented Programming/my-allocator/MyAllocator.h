#pragma once

#include "MemPool.h"
#include <iostream>
#include <memory>

template<class _Ty>
class Allocator_base
{
public:
	typedef _Ty value_type;
};

template<class _Ty>
class Allocator_base<const _Ty>
{
public:
	typedef _Ty value_type;
};

template<class _Ty>
class Allocator : public Allocator_base<_Ty>
{
public:
	typedef typename std::size_t size_type; // typename: std::size_t is a type, not a value
	typedef typename std::ptrdiff_t difference_type;
	typedef _Ty* pointer;
	typedef const _Ty* const_pointer;
	typedef _Ty& reference;
	typedef const _Ty& const_reference;
	typedef Allocator_base<_Ty> _Mybase;
	typedef typename _Mybase::value_type value_type;

	template<class _U>
	class rebind
	{
	public:
		typedef Allocator<_U> other;
	};

	// std::shared_ptr<CMemPool> pool;
	static CMemPool * pool;

	Allocator() throw() {
		// pool = std::make_shared<CMemPool>(); 
		if (pool == nullptr) {
			pool = new CMemPool;
			// std::cout << "new pool" << std::endl;
		}
	}
	Allocator(const Allocator & nico) throw() { pool = nico.pool; }
	template<class _otherAll>
	Allocator(const Allocator<_otherAll> & nico) throw() { pool = nico.pool; }
	~Allocator() throw() {}

	pointer allocate(size_type num)
	{
		// std::cout << "MyAllocator::allocate" << std::endl;
		return (pointer)(pool->Alloc(num * sizeof(value_type)));
	}
	void deallocate(pointer p, size_type size)
	{
		pool->Free(p);
	}
	void construct(pointer p, const_reference t)
	{
		new((void*)p) value_type(t);
	}
	void destroy(pointer p)
	{
		p->~_Ty();
	}

	/*A::max_size() {
		return size_type(-1) / sizeof(value_type);
	}

	A::pointer A::address(reference x) {
		return 
	}*/
};

template<class T>
CMemPool * Allocator<T>::pool = nullptr;