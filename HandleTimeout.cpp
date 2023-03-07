#include <new>

#include "HandleTimeout.h"

#include "ace/Service_Config.h"
#include "ace/Get_Opt.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_string.h"
#include "ace/Service_Repository.h"

#include "PaxfeedStatus.h"
#include "Xmitter.h"
#include "ChannelProcInfo.h"
#include "DataDispatcher.h"
#include "HandleInternet.h"

#if defined (SunOS4)
extern "C" 
{
  int init (void);
  int fini (void);
  void __sti__HandleTimeout_C_init_();
  void __std__HandleTimeout_C_init_();
}

int 
init (void)
{
  __sti__HandleTimeout_C_init_();
  return 0;
}

int 
fini (void)
{
  __std__HandleTimeout_C_init_();
  return 0;
}
#endif /* SunOS4 */

HandleTimeout timer_1;
ACE_Service_Object_Type t1 (&timer_1, "Timer_1");

HandleTimeout::HandleTimeout (void): count (0)
{
  time_t timeCurr = ::time(0);
  tmLast_ = *::localtime(&timeCurr);
}

int HandleTimeout::info (char **strp, size_t length) const
{
  char buf[BUFSIZ];

  ACE_OS::sprintf (buf, "%s", "# tests timeout facility\n");

  if (*strp == 0 && (*strp = ACE_OS::strdup (buf)) == 0)
    return -1;
  else
    ACE_OS::strncpy (*strp, buf, length);
  return ACE_OS::strlen (buf);
}

int HandleTimeout::init (int argc, char *argv[])
{
  ACE_Time_Value delta (10);
  ACE_Time_Value interval (1);
  ACE_Get_Opt    get_opt (argc, argv, "a:d:i:", 0);
  int        arg = 0;

  for (int c; (c = get_opt ()) != -1; )
     switch (c)
       {
       case 'd':
         delta.sec (ACE_OS::atoi (get_opt.opt_arg ()));
         break;
       case 'i':
         interval.sec (ACE_OS::atoi (get_opt.opt_arg ()));
         break;
       case 'a':
         arg = ACE_OS::atoi (get_opt.opt_arg ());
         break;
       default:
         break;
       }

  if (ACE_Reactor::instance()->schedule_timer(
      this, reinterpret_cast<void *> (arg), delta, interval) == -1)
    return -1;
  else
    return 0;
}

int HandleTimeout::fini (void)
{
  return 0;
}

ACE_HANDLE HandleTimeout::get_handle (void) const
{
  return ACE_INVALID_HANDLE;
}

int HandleTimeout::handle_timeout (const ACE_Time_Value &tv, const void *arg)
{
  // For Packet Compress 
  ACE_Message_Block* mblk = makeMsgHeartbeat();
  if (mblk != 0) {
    if (DataDispatcher::instance().put(mblk) == -1) {
      mblk->release ();
    }
  }

  paxfeed::STATUS::instance()->setMode(XMITTER::instance()->isActive() ? "ACTIVE" : "STANDBY");
  paxfeed::STATUS::instance()->sendStatus();

  time_t timeCurr = ::time(0);
  struct tm tmCurr = *::localtime(&timeCurr);

  if (tmCurr.tm_yday  != tmLast_.tm_yday)
//  if (tmCurr.tm_min != tmLast_.tm_min)
  {
    prepareNewDay();
  }

  if (tmCurr.tm_min != tmLast_.tm_min) {
    paxfeed::STATUS::instance()->sendTimeSync();
  }

  tmLast_ = tmCurr;

  // Cast arg to a long, first, because a pointer is the same
  // size as a long on all current ACE platforms.
  ACE_DEBUG ((LM_INFO, "time for this(%u) expired at (%d, %d) with arg = %d\n",
             this, tv.sec (), tv.usec (), (int) (long) arg));
  return 0;
}

//----------------------------------------------------------------------------//
// 날짜가 바뀌면,
// 1. 체결이나 마스터데이터 등 전일 상태 데이터 삭제
// 2. rawLogFile의 이름 변경
// 3. STATUS 초기화
int HandleTimeout::prepareNewDay()
{
  ACE_DEBUG ((LM_DEBUG, "HandleTimeout::prepareNewDay ..... \n")) ;

  ACE_Message_Block* mblk = makeMsgNewDay();
  if (mblk != 0) {
    if (DataDispatcher::instance().put(mblk) == -1) {
      mblk->release ();
    }
  }

  ACE_Service_Repository_Iterator itRepo(*ACE_Service_Repository::instance());
  const ACE_Service_Type* serviceType;
  while(itRepo.next(serviceType) != 0)
  {
    const ACE_Service_Type_Impl* svcTypeImpl = serviceType->type();
    ACE_DEBUG ((LM_DEBUG, "prepareNewDay name(%s)..... \n", svcTypeImpl->name())) ;
    HandleInternet* handleInternet = dynamic_cast<HandleInternet*> (
                  static_cast<ACE_Service_Object*> (svcTypeImpl->object()));
    if (handleInternet != 0)
    {
      ACE_DEBUG ((LM_DEBUG, "reset HandleInternet \n")) ;
//      handleUdp->reset();
      handleInternet->prepareLogFile();
    }

    itRepo.advance();
  }

  paxfeed::STATUS::instance()->clear();

  return 0;
}

ACE_Message_Block* HandleTimeout::makeMsgNewDay() const
{
  ACE_Message_Block* mblk = 0;
  const char frameId_NewDay[] = {'N', 'D'};

  try {
    ChannelProcInfo::IDType channelId = ChannelProcInfo::ID_TIMER;
    mblk = new ACE_Message_Block(
      sizeof channelId + sizeof frameId_NewDay) ;

    ::memcpy(mblk->wr_ptr(), &channelId, sizeof channelId);
    mblk->wr_ptr(sizeof channelId);
    ::memcpy(mblk->wr_ptr(), frameId_NewDay, sizeof frameId_NewDay);
    mblk->wr_ptr(sizeof frameId_NewDay);
  }
  catch(std::bad_alloc& e) {
    ACE_DEBUG((LM_ERROR, "cannot allocate ACE_Message_Block " \
      "in HandleTimeout::makeMsg_NewDay (%s)\n", e.what()));
  }

  return mblk;
}

ACE_Message_Block* HandleTimeout::makeMsgHeartbeat() const
{
  ACE_Message_Block* mblk = 0;
  const char frameId[] = {'H', 'B'};

  try {
    ChannelProcInfo::IDType channelId = ChannelProcInfo::ID_ALL;

    mblk = new ACE_Message_Block(
      sizeof channelId + sizeof frameId) ;

    ::memcpy(mblk->wr_ptr(), &channelId, sizeof channelId);
    mblk->wr_ptr(sizeof channelId);
    ::memcpy(mblk->wr_ptr(), frameId, sizeof frameId);
    mblk->wr_ptr(sizeof frameId);
  }
  catch(std::bad_alloc& e) {
    ACE_DEBUG((LM_ERROR, "cannot allocate ACE_Message_Block " \
      "in HandleTimeout::makeMsgHeartbeat (%s)\n", e.what()));
  }

  return mblk;
}
