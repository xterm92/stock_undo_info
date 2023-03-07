#if !defined(_MMapAllocator_H_20040507_)
#define _MMapAllocator_H_20040507_

#include "ace/MMAP_Memory_Pool.h" 

typedef ACE_Allocator_Adapter<ACE_Malloc_T<ACE_MMAP_MEMORY_POOL,
//                                            ACE_SYNCH_MUTEX,
        ACE_Null_Mutex, ACE_Control_Block>
//                                            ACE_PI_Control_Block>
> MMAP_ALLOCATOR;

class Mmap_Allocatior: public MMAP_ALLOCATOR
{
    public:
        Mmap_Allocatior()
                : MMAP_ALLOCATOR("Tickerplant.mem", "Tickerplant.mem",
                //Mmap_Allocatior(const char* filename)
                //  : MMAP_ALLOCATOR(filename, filename,
//        &ACE_MMAP_Memory_Pool_Options(ACE_DEFAULT_BASE_ADDR, ACE_MMAP_Memory_Pool_Options::FIRSTCALL_FIXED))
//        &ACE_MMAP_Memory_Pool_Options(ACE_DEFAULT_BASE_ADDR, ACE_MMAP_Memory_Pool_Options::NEVER_FIXED))
                        &ACE_MMAP_Memory_Pool_Options(ACE_DEFAULT_BASE_ADDR, ACE_MMAP_Memory_Pool_Options::ALWAYS_FIXED))
        {
            ;
        }
};

template<typename HashMap>
HashMap* allocHashMap(const char* mapName, ACE_Allocator& allocator)    // throw(std::runtime_error)
{
    void* hash_map = 0;

    // 이미 맵이 존재할경우, 찾아서 리턴
    if ( allocator.find(mapName, hash_map) == 0 )
    {
        return reinterpret_cast<HashMap*>(hash_map);
    }

    // 존재하지 않을 경우, 신규 생성
    hash_map = allocator.malloc(sizeof(HashMap));
    if ( hash_map == 0 ) return 0;

//    new (hash_map) HashMap(sizeof(HashMap), &allocator);
//    new (hash_map) HashMap(2000, &allocator);
    new (hash_map) HashMap(&allocator);
    if ( allocator.bind(mapName, hash_map) == -1 )
    {
        ACE_ERROR( ( LM_ERROR , ACE_TEXT("%p\n") , ACE_TEXT("allocate_map") ));
        allocator.remove();
        return 0;
    }

    return reinterpret_cast<HashMap*>(hash_map);
}

typedef ACE_Singleton<Mmap_Allocatior, ACE_Null_Mutex> ALLOCATOR;

#endif // _MMapAllocator_H_20040507_
//test2
