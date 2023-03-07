#ifndef _HANDLEUDP_H
#define _HANDLEUDP_H

#include "ace/Service_Config.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Service_Types.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Dgram.h"
#include "ace/SOCK_Dgram_Mcast.h"
#include "ace/Log_Msg.h"
#include "ace/svc_export.h"
#include "ace/Containers.h"
#include "ace/Reactor.h"
#include "ace/Map_Manager.h"
#include "ace/Synch.h"
#include "ace/Singleton.h"
#include "Tickerplant.h"

#include "ace/FILE_IO.h"
#include "ControlCmdParser.h"

class ACE_Svc_Export HandleStatus : public ACE_Service_Object
{
public:
  HandleStatus (void);
  virtual int init (int argc, char *argv[]);
  virtual int info (char **, size_t) const;
  virtual int fini (void);

protected:
  virtual int handle_input (ACE_HANDLE fd);
  virtual int handle_close (ACE_HANDLE fd, ACE_Reactor_Mask);
  void dispatchCommand(const ControlCmdParser::Command& cmd);

  // For Data Recv
  ControlCmdParser::Target svrInfo_;
  ACE_SOCK_Dgram_Mcast recvSock_ ;
};



#endif /* _HANDLEUDP_H */

