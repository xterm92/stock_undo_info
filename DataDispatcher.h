// DataDispatcher.h: interface for the DataDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATADISPATCHER_H__D975040F_7255_408F_ABAE_7099AF7B4255__INCLUDED_)
#define AFX_DATADISPATCHER_H__D975040F_7255_408F_ABAE_7099AF7B4255__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ace/Singleton.h"
#include "ace/Synch.h"
#include "ace/Task.h"

class ChannelPool;

#include <memory>

class DataDispatcher: public ACE_Task<ACE_MT_SYNCH>
{
    public:
        enum
        {
            MAX_THREADS = 1
        };
        enum
        {
            MAX_QUEUE_SIZE = 10 * 1024 * 1024
        };

    public:
        static DataDispatcher& instance();ACE_INLINE
        ChannelPool* getChannelPool()
        {
            return pool_.get();
        }
        virtual int open(void * = 0);
        virtual int put(ACE_Message_Block *mblk, ACE_Time_Value *timeout = 0);
        virtual int svc(void);

        ACE_CString marketBegin_;
        ACE_CString marketEnd_;

    private:
        DataDispatcher();
        virtual ~DataDispatcher();

    private:
        std::auto_ptr<ChannelPool> pool_;

    private:
        static DataDispatcher inst_;
};

#endif // !defined(AFX_DATADISPATCHER_H__D975040F_7255_408F_ABAE_7099AF7B4255__INCLUDED_)
