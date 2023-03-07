// TimerChannelProcessor.cpp: implementation of the TimerChannelProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "TimerChannelProcessor.h"
#include "ChannelProcInfo.h"
#include "ChannelPool.h"
#include "DataDispatcher.h"

TimerChannelProcessor::TimerChannelProcessor(const ACE_CString &channelName)
{
}

TimerChannelProcessor::~TimerChannelProcessor()
{
}

int TimerChannelProcessor::processPacket(const ACE_CString &packet)
{
  ACE_CString frameId(packet.substr(0, 2)) ;

  if (frameId == "ND") {
    handleNewDay();
  }

  return 0;
}

void TimerChannelProcessor::handleNewDay()
{
  ChannelPool* pool = DataDispatcher::instance().getChannelPool();
  if (pool != 0) {
    ChannelPool::ITERATOR it(*pool);
    while(!it.done())
    {
      (*it).int_id_->reset();
      ++it;
    }
  }
}
