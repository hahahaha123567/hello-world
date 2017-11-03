
#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

class CMemPool
{
private:
	struct _Unit							//The type of the node of linkedlist.
	{
		struct _Unit *pPrev, *pNext;
	};

	void*			m_pMemBlock;			//The address of memory pool.

	//Manage all unit with two linkedlist.
    struct _Unit*	m_pAllocatedMemBlock;	//Head pointer to Allocated linkedlist.
	struct _Unit*	m_pFreeMemBlock;		//Head pointer to Free linkedlist.

    unsigned long	m_ulUnitSize;			//Memory unit size. There are many units in memory pool.
    unsigned long	m_ulBlockSize;			//Memory pool size. Memory pool is make of memory unit.

public:
	CMemPool(unsigned long lUnitNum = 1000, unsigned long lUnitSize = 256); //Here, we fix the UnitNum and UnitSize
	~CMemPool();
	
    void*           Alloc(unsigned long ulSize, bool bUseMemPool = true);	//Allocate memory unit (from OS)
    void            Free( void* p );										//Free memory unit (back to OS)
};

#endif //__MEMPOOL_H__
