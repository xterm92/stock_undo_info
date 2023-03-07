#ifndef _HANDLEINTERNET_H
#define _HANDLEINTERNET_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Service_Config.h"
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
#include "ace/FILE_IO.h"

#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Service_Object.h"
#include "ace/Vector_T.h"
#include "ace/Containers_T.h"
#include "ace/Reactor_Notification_Strategy.h"

#include "Tickerplant.h"
#include "Xmitter.h"
#include "ChannelProcInfo.h"
#include "PaxfeedAceHelper.h"
#include "ClientChannel.h"

typedef ACE_Unbounded_Set<ClientChannel*> Channels;

#if(0)
typedef HashMap<ACE_CString, int> KseFrameIdMap;
typedef HashMap<ACE_CString, int> KosdaqFrameIdMap;
typedef HashMap<ACE_CString, int> FutureFrameIdMap;
typedef HashMap<ACE_CString, int> OptionFrameIdMap;
typedef HashMap<ACE_CString, int> ElwFrameIdMap;
#endif

class ACE_Svc_Export HandleInternet : public ACE_Service_Object
{
    protected:
    enum
    {   MAX_THREADS_BASE = 1};
    enum
    {   MAX_QUEUE_SIZE = 1024*1024};

    public:
    HandleInternet (const ACE_CString& logFileSuffix, int channelType);
    virtual int init (int argc, char *argv[]);
    virtual int info (char **, size_t) const;
    virtual int fini (void);
    int prepareLogFile(); //const ACE_CString& fileSuffix);
    int registerChannel(ClientChannel* channel);
    int unregisterChannel(ClientChannel* channel);
    virtual void logRcvData(const char* buf, ssize_t len, time_t time, ACE_CString recvAddr);

    void setFrameIdLength();

    void setFrameIdLength_KSE_KRX();
    void setFrameIdLength_KSE_KOSCOM();
    void setFrameIdLength_KSE_ETC();

    void setFrameIdLength_KOSDAQ_KRX();
    void setFrameIdLength_KOSDAQ_KOSCOM();
    void setFrameIdLength_KOSDAQ_ETC();

    void setFrameIdLength_KOSPI200_FUTURE();
    void setFrameIdLength_KOSPI200_OPTION();

    void setFrameIdLength_ELW_KRX();
    void setFrameIdLength_ELW_KOSCOM();
    void setFrameIdLength_ELW_ETC();

#if(0)
    KseFrameIdMap kseFrameIdMap;
    KosdaqFrameIdMap kosdaqFrameIdMap;
    FutureFrameIdMap futureFrameIdMap;
    OptionFrameIdMap optionFrameIdMap;
    ElwFrameIdMap elwFrameIdMap;
#endif

    ACE_CString getCurrentTimestamp();

    protected:
    virtual int handle_input (ACE_HANDLE fd);
    virtual int handle_close (ACE_HANDLE fd, ACE_Reactor_Mask);
    int open (const ACE_INET_Addr &sia);
    virtual ACE_HANDLE get_handle (void) const;
    virtual int handle_signal (int signum, siginfo_t *, ucontext_t *);

    Channels channels_;
    ACE_SOCK_Acceptor acceptor_;
    int channelCount_;

    private:
    ACE_FILE_IO rawLogFile_;
    ACE_CString logFileSuffix_;
    ACE_CString port_;
    ACE_CString dirRawLog_;
    int currentHour_;
    int channelType_;
    ACE_CString dirMasterFile_;

};

#endif /* _HANDLEUDP_H */
