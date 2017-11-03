#pragma once
#pragma once

#include "MemPool.h"
#include <iostream>
#include <memory>

template<class _Ty>
class Allocator_base2
{
public:
	typedef _Ty value_type;
};

template<class _Ty>
class Allocator_base2<const _Ty>
{
public:
	typedef _Ty value_type;
};

template<class _Ty>
class Allocator2 : public Allocator_base2<_Ty>
{
public:
	typedef typename std::size_t size_type; // typename: std::size_t is a type, not a value
	typedef typename std::ptrdiff_t difference_type;
	typedef _Ty* pointer;
	typedef const _Ty* const_pointer;
	typedef _Ty& reference;
	typedef const _Ty& const_reference;
	typedef Allocator_base2<_Ty> _Mybase;
	typedef typename _Mybase::value_type value_type;

	template<class _U>
	class rebind2
	{
	public:
		typedef Allocator2<_U> other;
	};

	Allocator2() throw() { }
	Allocator2(const Allocator2 &) throw() { }
	template<class _otherAll>
	Allocator2(const Allocator2<_otherAll> &) throw() { }
	~Allocator2() throw() { }

	pointer allocate(size_type num)
	{
		return (pointer) (operator new(num * sizeof(value_type)));
	}
	void deallocate(pointer p, size_type size)
	{
		operator delete(p);
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
