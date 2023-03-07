// TimerChannelProcessor.h: interface for the TimerChannelProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMERCHANNELPROCESSOR_H__898325EA_499C_49F8_9F03_43036B616A7B__INCLUDED_)
#define AFX_TIMERCHANNELPROCESSOR_H__898325EA_499C_49F8_9F03_43036B616A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChannelProcessor.h"

class TimerChannelProcessor : public ChannelProcessor  
{
public:
  TimerChannelProcessor(const ACE_CString &channelName);
  virtual ~TimerChannelProcessor();

  virtual int processPacket (const ACE_CString &packet);

protected:
  void handleNewDay();
};

#endif // !defined(AFX_TIMERCHANNELPROCESSOR_H__898325EA_499C_49F8_9F03_43036B616A7B__INCLUDED_)
