#include "ace/Get_Opt.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_unistd.h"
#include "ace/INET_Addr.h"
#include "ace/Containers_T.h"
#include "ace/SStringfwd.h"
#include "ace/OS_Memory.h"
#include "ace/FILE_Addr.h"
#include "ace/FILE_Connector.h"
#include "ace/FILE_IO.h"

#include "HandleStatus.h"
#include "PaxfeedStringUtil.h"
#include "PaxfeedStatusDefine.h"
#include "Xmitter.h"
#include "PaxfeedStatus.h"
#include "PaxfeedPacketParser.h"

HandleStatus status;
ACE_Service_Object_Type statushandler(&status, "Status");

using namespace paxfeed ;

HandleStatus::HandleStatus (void)
{
  ACE_TRACE(ACE_TEXT ("HandleStatus"));
}

int HandleStatus::info (char **, size_t) const
{
  ACE_TRACE(ACE_TEXT ("info"));
  return 0;
}

int HandleStatus::init (int argc, char *argv[])
{
  ACE_DEBUG((LM_TRACE, "%IHandleStatus start\n"));

  int mcastPort = 0;
  ACE_CString mcastGroup ;
  ACE_CString procName;
  ACE_CString ipAddr;

  ACE_Get_Opt	get_opt (argc, argv, "p:a:n:i:", 0);
  for (int c; (c = get_opt ()) != -1; ) {
     switch (c)
       {
       case 'p': 
         mcastPort = ACE_OS::atoi (get_opt.opt_arg ());
         break;

       case 'a': 
         mcastGroup = ACE_CString(get_opt.opt_arg()) ;
         break;

       case 'n': 
         procName = ACE_CString(get_opt.opt_arg()) ;
         break;

       case 'i': 
         ipAddr = ACE_CString(get_opt.opt_arg()) ;
         break;

       default:
         break;
       }
  }

  // 전송 주소 체크 
  // ACE_OS::exit(0) 이 정상적으로 실행되지 않음
  // 주의 필요함 
  if ( (mcastPort == 0) || ( mcastGroup == "" ) )
  {
    ACE_DEBUG((LM_DEBUG, "[ERROR] HandleStatus::init():mcastGroup:mcastPort:%s:%d\n", 
              mcastGroup.c_str(), mcastPort));
    ACE_ERROR_RETURN ((LM_ERROR, "[ERROR] HandleStatus::init(): mcastGroup:mcastPort config error occurred......\n"), -1);
  }

  svrInfo_.set(STATUS_SERVICE_TICKERPLANT, procName, ipAddr);
  STATUS::instance()->initialize(svrInfo_.service(), svrInfo_.name(), svrInfo_.ipAddr(),
    mcastGroup, mcastPort);

  ACE_INET_Addr mcastAddr(mcastPort,mcastGroup.c_str()) ;
  recvSock_.join(mcastAddr) ;

  int isRegistered = ACE_Reactor::instance()->register_handler(
                     recvSock_.get_handle(),this,ACE_Event_Handler::ACCEPT_MASK);

  if(-1 == isRegistered) {
    ACE_ERROR_RETURN ((LM_ERROR, "Error : registering service with ACE_Reactor\n"), -1);
  }

  return 0;
}

int HandleStatus::fini (void) 
{
  ACE_TRACE(ACE_TEXT ("fini"));

  return ACE_Reactor::instance ()->remove_handler 
    (this, ACE_Event_Handler::ACCEPT_MASK);
}

int HandleStatus::handle_input (ACE_HANDLE fd)
{
  int result = 0;

  ACE_INET_Addr sa;
  char buf[PAXFEED_MAX_BUF_SIZE];
  recvSock_.set_handle(fd);
  ssize_t recvSize = recvSock_.recv (buf, sizeof buf, sa);

  if (recvSize == -1) {
    ACE_ERROR_RETURN ((LM_ERROR, "recv error\n"), -1); 
	// TODO : 에러 리턴시에 데이터처리를 진행하지 못한다. 
  }

  try {
    paxfeed::PacketParser packetParser(buf, buf + recvSize);
    if (packetParser.head().packetType == paxfeed::PACKET_COTROLCOMMAND) {
      //ACE_CString strControl(buf, recvSize);
      ACE_CString strControl(
        packetParser.body().first, packetParser.body().second - packetParser.body().first);
      ControlCmdParser parser(strControl);
    // by magi 20040626     
      ACE_DEBUG((LM_TRACE, "-----------------------------------\n"));
      ACE_DEBUG((LM_TRACE, "Data:%s\n", strControl.c_str()));
      ACE_DEBUG((LM_TRACE, "ControlCommad: Command - %s\n", parser.command().command().c_str()));
      ACE_DEBUG((LM_TRACE, "ControlCommad: Target - service - %s\n", parser.target().service().c_str()));
      ACE_DEBUG((LM_TRACE, "ControlCommad: Target - name - %s\n", parser.target().name().c_str()));
      ACE_DEBUG((LM_TRACE, "ControlCommad: Target - ipaddr - %s\n", parser.target().service().c_str()));
      ACE_DEBUG((LM_TRACE, "ControlCommad: Target - service - %s\n", parser.target().ipAddr().c_str()));
      ACE_DEBUG((LM_TRACE, "ControlCommad: param - %s\n", parser.command().param().c_str()));
      ACE_DEBUG((LM_TRACE, "-----------------------------------\n"));
    // by magi 20040626  
      if (parser.target() == svrInfo_)
      {
        dispatchCommand(parser.command());        
      }
    }
  }
  catch(std::exception& e) {
    ACE_DEBUG((LM_ERROR, "error in HandleStatus::handle_input - %s\n", e.what()));
  }
  return result; 
}

int HandleStatus::handle_close (ACE_HANDLE, ACE_Reactor_Mask)
{
  return 0;
}

void HandleStatus::dispatchCommand(const ControlCmdParser::Command& cmd)
{
  if (cmd.command() == CMD_CHANGE_MODE)
  {
    XMITTER::instance()->setActive(!XMITTER::instance()->isActive()); // toggle active state
  }
}

