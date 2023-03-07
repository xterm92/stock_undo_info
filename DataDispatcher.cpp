// DataDispatcher.cpp: implementation of the DataDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#include "ace/SStringfwd.h"
#include "ace/String_Base.h"

#include "ChannelProcessor.h"
#include "ChannelProcInfo.h"
#include "ChannelPool.h"
#include "DataDispatcher.h"

// define global object
DataDispatcher DataDispatcher::inst_;

DataDispatcher::DataDispatcher()
        : pool_(new ChannelPool)
{
    msg_queue()->high_water_mark(MAX_QUEUE_SIZE);
    open();
}

DataDispatcher::~DataDispatcher()
{
}

DataDispatcher& DataDispatcher::instance()
{
    return inst_;
}

int DataDispatcher::open(void *)
{
    return activate(THR_NEW_LWP, MAX_THREADS);
}

int DataDispatcher::put(ACE_Message_Block *mblk, ACE_Time_Value *timeout)
{
    return putq(mblk, timeout);
}

int DataDispatcher::svc()
{

    int prevCommitUTC = 0;
    int currentUTC = 0;
    prevCommitUTC = (int) ( ::time(0) );
    ACE_Message_Block *mblk = 0;
    while ( getq(mblk) != -1 )
    {
        if ( mblk->length() > 0 )
        {
            ChannelProcInfo::IDType channelId = *reinterpret_cast<ChannelProcInfo::IDType*>(mblk->rd_ptr());
            mblk->rd_ptr(sizeof(ChannelProcInfo::IDType));

            if ( channelId == ChannelProcInfo::ID_ALL )
            {
                // 현재 프로세스가 모두 분리되어 있으므로 아래 코드는 동작하지 않는다. 주석처리함
                //ACE_Hash_Map_Manager<ChannelProcInfo::IDType, ChannelProcessor*, ACE_Null_Mutex>::iterator it = pool_->begin();
                //
                //for ( ; it != pool_->end(); ++it )
                //{
                //  ChannelProcessor* cProc = (*it).int_id_  ;
                //  cProc->flushPacket() ;   // it->flushPacket()
                //}
            }
            else
            {
                ChannelProcessor* proc = pool_->getChannelProcessor(channelId);
                if ( proc != 0 )
                {

                    currentUTC = (int) ( ::time(0) );
                    int timeGap = currentUTC - prevCommitUTC;
                    if ( timeGap > 5 )
                    {
                        proc->flushPacket();
                        prevCommitUTC = currentUTC;
                    }
                    ACE_CString packet(mblk->rd_ptr(), mblk->length());
                    proc->processPacket(packet);
                }
            }

            mblk->release();
        }
    }

    return 0;
}

