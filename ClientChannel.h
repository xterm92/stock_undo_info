#ifndef CLIENT_CHANNEL_H
#define CLIENT_CHANNEL_H

#include "ace/SOCK_Stream.h"
#include "ace/Svc_Handler.h"
#include "ace/SStringfwd.h"
#include "Tickerplant.h"
#include "ChannelProcInfo.h"
//#include "HandleInternet.h"

class HandleInternet;

class ClientChannel: public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
        typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super;

    public:
        //ClientChannel(HandleInternet* parent=0, int channelId=0, ChannelProcInfo::IDType channelType) ;
        ClientChannel(HandleInternet* parent = 0, int channelId = 0, int market = 0);
        int open(void * = 0);
        virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
        virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);
        virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
        int checkValid();
        int dataFormat();
        int isAuth;
        ACE_CString getCurrentTimestamp();
        ACE_CString getCurrentTimestamp(ACE_CString format);

    protected:
        ACE_CString buffer_;
        HandleInternet* parent_;
        char	data_[8192];
        int datalen_;
        int lastHeartbeatTime_;
        int channelId_;


    private:
        ChannelProcInfo::IDType channelType_;
};

#include /**/ "ace/post.h"
#endif /* CLIENT_CHANNEL_H */
