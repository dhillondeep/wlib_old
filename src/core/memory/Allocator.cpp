#include "Allocator.h"
#include <assert.h>
#include <string.h>

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Allocator::Allocator(size_t size, UINT objects, CHAR* memory, const CHAR* name) :
    m_blockSize(size < sizeof(long*) ? sizeof(long*):size),
    m_objectSize(size),
    m_maxObjects(objects),
    m_pHead(nullptr),
    m_poolIndex(0),
    m_blockCnt(0),
    m_blocksInUse(0),
    m_allocations(0),
    m_deallocations(0),
    m_name(name)
{
    // If using a fixed memory pool 
	if (m_maxObjects)
	{
		// If caller provided an external memory pool
		if (memory)
		{
			m_pPool = memory;
			m_allocatorMode = STATIC_POOL;
		}
		else 
		{
			m_pPool = (CHAR*)new CHAR[m_blockSize * m_maxObjects];
			m_allocatorMode = HEAP_POOL;
		}
	}
	else
		m_allocatorMode = HEAP_BLOCKS;
}

//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
Allocator::~Allocator()
{
	// If using pool then destroy it, otherwise traverse free-list and 
	// destroy each individual block
	if (m_allocatorMode == HEAP_POOL)
		delete [] m_pPool;
	else if (m_allocatorMode == HEAP_BLOCKS)
	{
		while(m_pHead)
			delete [] (CHAR*)pop();
	}
}

//------------------------------------------------------------------------------
// Allocate
//------------------------------------------------------------------------------
void* Allocator::allocate(size_t size)
{
    assert(size <= m_objectSize);
	
    // If can't obtain existing block then get a new one
    void* pBlock = pop();
    if (!pBlock)
    {
        // If using a pool method then get block from pool,
        // otherwise using dynamic so get block from heap
        if (m_maxObjects)
        {
            // If we have not exceeded the pool maximum
            if(m_poolIndex < m_maxObjects)
            {
                pBlock = (void*)(m_pPool + (m_poolIndex++ * m_blockSize));
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
        	m_blockCnt++;
            pBlock = (void*)new CHAR[m_blockSize];
        }
    }

    m_blocksInUse++;
    m_allocations++;
	
    return pBlock;
}

//------------------------------------------------------------------------------
// Deallocate
//------------------------------------------------------------------------------
void Allocator::deallocate(void* pBlock)
{
    push(pBlock);
	m_blocksInUse--;
	m_deallocations++;
}


//------------------------------------------------------------------------------
// Reallocate
//------------------------------------------------------------------------------
void *Allocator::reallocate(void* pBlock, size_t oldSize, size_t newSize)
{
    if (newSize == oldSize)
        return pBlock;

    void* newBlock = allocate(newSize);

    if (newSize < oldSize)
        memcpy(newBlock, pBlock, newSize);
    else
        memcpy(newBlock, pBlock, oldSize);

    deallocate(pBlock);

    return newBlock;
}

//------------------------------------------------------------------------------
// Push
//------------------------------------------------------------------------------
void Allocator::push(void* pMemory)
{
    auto * pBlock = (Block*)pMemory;
    pBlock->pNext = m_pHead;
    m_pHead = pBlock;
}

//------------------------------------------------------------------------------
// Pop
//------------------------------------------------------------------------------
void* Allocator::pop()
{
    Block* pBlock = nullptr;

    if (m_pHead)
    {
        pBlock = m_pHead;
        m_pHead = m_pHead->pNext;
    }

    return (void*)pBlock;
}





