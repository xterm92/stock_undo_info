#include <errno.h>
#include <sstream> 
#include "ace/OS_NS_errno.h"
#include "ace/OS_NS_sys_time.h"
#include "ace/os_include/os_netdb.h"
#include "ace/Log_Msg.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Reactor.h"
#include "ace/Acceptor.h"

#include "ace/Get_Opt.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Containers_T.h"
#include "ace/SStringfwd.h"
#include "ace/OS_Memory.h"
#include "ace/FILE_Addr.h"
#include "ace/FILE_Connector.h"
#include "ace/FILE_IO.h"

#include "ExturePlusInternetKse.h"
#include "ExturePlusInternetKosdaq.h"
#include "ExturePlusInternetKospi200Future.h"
#include "ExturePlusInternetKospi200Option.h"
#include "ExturePlusInternetElw.h"
#include "ClientChannel.h"
#include "DataDispatcher.h"
#include "HandleInternet.h"

using namespace paxfeed;

typedef ACE_Acceptor<ClientChannel, ACE_SOCK_ACCEPTOR> ClientAcceptor;

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class ACE_Acceptor<ClientChannel, ACE_SOCK_ACCEPTOR>;
template class ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate ACE_Acceptor<ClientChannel, ACE_SOCK_ACCEPTOR>
#pragma instantiate \
   ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

const int TR_ID_SIZE = 5;
/*
 현재 시간 문자열을 출력한다.
 YYYYMMDD_HHMMSS
 */
ACE_CString ClientChannel::getCurrentTimestamp()
{
    ACE_CString strTimestamp = getCurrentTimestamp("%Y%m%d_%H%M%S");
    return strTimestamp;
}

ACE_CString ClientChannel::getCurrentTimestamp(ACE_CString format)
{
    char buffer[32];
    ::memset(&buffer, 0, sizeof ( buffer ));
    struct tm stTm;
    ::memset(&stTm, 0, sizeof(struct tm));
    time_t currentTime = time(NULL);
    ::localtime_r(&currentTime, &stTm);
    ::strftime(buffer, sizeof ( buffer ), format.c_str(), &stTm);
    ACE_CString strCurrentTime(buffer);
    return strCurrentTime;
}

/*
 ClientChannel::ClientChannel(HandleInternet* parent, int channelId, ChannelProcInfo::IDType channelType) :
 parent_(parent), channelId_(channelId), channelType_(channelType)
 */
ClientChannel::ClientChannel(HandleInternet* parent, int channelId, int market)
        : parent_(parent), channelId_(channelId), channelType_(market)
{
    if ( parent == 0 )
    {
        ACE_DEBUG( ( LM_DEBUG , ACE_TEXT("[ClientChannel::ClientChannel] channelId_:[%d] Parent NULL\n") , channelId_ ));
    }
}

int ClientChannel::open(void *p)
{
    if ( super::open(p) == -1 )
    {
        ACE_DEBUG( ( LM_DEBUG , ACE_TEXT("[ClientChannel::open] open ERROR[%d][%s]\n") , errno , strerror(errno) ));
        return -1;
    }

    buffer_ = "";
    datalen_ = 0;
    ACE_TCHAR peer_name[MAXHOSTNAMELEN];
    ACE_INET_Addr peer_addr;
    if ( this->peer().get_remote_addr(peer_addr) == 0 && peer_addr.addr_to_string(peer_name, MAXHOSTNAMELEN) == 0 )
    {
        //ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("[ClientChannel::open] Connection from %s\n"), peer_name));
    }

//    if ( this->reactor()->register_handler(this, ACE_Event_Handler::READ_MASK) == -1 )
//    {
//        ACE_DEBUG( ( LM_DEBUG , ACE_TEXT("[ClientChannel::open] registering service READ_MASK ERROR[%d][%s]\n") , errno , strerror(errno) ));
//        return -1;
//    }

	parent_->registerChannel(this);

    return 0;

}


int ClientChannel::dataFormat()
{
    ACE_Time_Value timeout(1);
    time_t timeRecv = ::time(0);
    int trLength = 0;

    ACE_INET_Addr addrLocal;
    ACE_INET_Addr addrRemote;
//    int resultLocal = this->peer().get_local_addr(addrLocal);
//    int resultremote = this->peer().get_remote_addr(addrRemote);

//    ACE_DEBUG (( LM_DEBUG, "[%s][ClientChannel::handle_input] resultLocal:[%d]\tportNumber:[%d]\tget_host_addr:[%s]\n", getCurrentTimestamp().c_str(), resultLocal, addrLocal.get_port_number(), addrLocal.get_host_addr() ));
//    ACE_DEBUG (( LM_DEBUG, "[%s][ClientChannel::handle_input] addrRemote:[%d]\tportNumber:[%d]\tget_host_addr:[%s]\n", getCurrentTimestamp().c_str(), resultLocal, addrRemote.get_port_number(), addrRemote.get_host_addr() ));

    char strRecvAddrBuf[128];
    ::memset(&strRecvAddrBuf, 0, sizeof ( strRecvAddrBuf ));
    ::sprintf(strRecvAddrBuf, "%s:%d", addrLocal.get_host_addr(), addrLocal.get_port_number());
    ACE_CString strRecvAddr(strRecvAddrBuf);

//    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("[%s][ClientChannel::dataProcess] strRecvAddr:[%s] datalen_(%d)[%.*s]\n"),
//    		getCurrentTimestamp().c_str(), strRecvAddr.c_str(), datalen_, datalen_, data_));

    ACE_CString key(data_, TR_ID_SIZE);
    ACE_CString dataCategory(data_, 2);
    trLength = datalen_;
    bool isValidFormat = false;


#if(0)
    if ( ( key[0] >= 'A' ) && ( key[0] <= 'Z' ) )
    {
        if ( ( key[1] >= '0' ) && ( key[1] <= '9' ) )
        {
            isValidFormat = true;
        }
        else
        {
            isValidFormat = false;
        }
    }
    else
    {
        isValidFormat = false;
    }
#endif

#if(1)
    if ( ( key[0] >= 'A' ) && ( key[0] <= 'Z' ) )
    {
        isValidFormat = true;
    }
    else
    {
        isValidFormat = false;
    }
#endif

    // 종목별 투자자별 종가가 DT 라서 추가함
    if ( dataCategory == "LK" )
    {
        isValidFormat = true;
    }
    else if ( dataCategory == "DT" )
    {
        isValidFormat = true;
    }
    else if ( dataCategory == "ZZ" )
    {
        isValidFormat = true;
    }

    if ( isValidFormat == false )
    {
        return 0;
    }

    ACE_Message_Block* mblk = new ACE_Message_Block(PAXFEED_MAX_PACKET_SIZE);
    ::memcpy(mblk->wr_ptr(), &channelType_, sizeof ( channelType_ ));
    mblk->wr_ptr(sizeof ( channelType_ ));

    /*
     * LK 데이터인 경우 LK 데이터를 별도로 만들어 넣자.
     */
    if ( key == "LK000" )
    {
        parent_->logRcvData(data_, datalen_, timeRecv, strRecvAddr);

        if ( channelType_ == ChannelProcInfo::ID_KOSPI )
        {
            ExturePlusKoscomLineLKInfo_KSE lkInfo;
            ::memset(&lkInfo, 0, sizeof(ExturePlusKoscomLineLKInfo_KSE));
            ::memcpy(& ( lkInfo.dataCategory ), "I2", sizeof ( lkInfo.dataCategory ));
            ::memcpy(& ( lkInfo.informationCategory ), "00", sizeof ( lkInfo.informationCategory ));
            ::memcpy(& ( lkInfo.marketCategory ), "0", sizeof ( lkInfo.marketCategory ));
            ::memcpy(& ( lkInfo.time ), getCurrentTimestamp("%H%M").c_str(), sizeof ( lkInfo.time ));
            ::memcpy(& ( lkInfo.recvAddr ), strRecvAddr.c_str(), strRecvAddr.length());
            ::memcpy(mblk->wr_ptr(), &lkInfo, sizeof ( lkInfo ));
            mblk->wr_ptr(sizeof ( lkInfo ));
        }
        if ( channelType_ == ChannelProcInfo::ID_KOSDAQ )
        {
            ExturePlusKoscomLineLKInfo_KOSDAQ lkInfo;
            ::memset(&lkInfo, 0, sizeof(ExturePlusKoscomLineLKInfo_KOSDAQ));
            ::memcpy(& ( lkInfo.dataCategory ), "I2", sizeof ( lkInfo.dataCategory ));
            ::memcpy(& ( lkInfo.informationCategory ), "00", sizeof ( lkInfo.informationCategory ));
            ::memcpy(& ( lkInfo.marketCategory ), "0", sizeof ( lkInfo.marketCategory ));
            ::memcpy(& ( lkInfo.time ), getCurrentTimestamp("%H%M").c_str(), sizeof ( lkInfo.time ));
            ::memcpy(& ( lkInfo.recvAddr ), strRecvAddr.c_str(), strRecvAddr.length());
            ::memcpy(mblk->wr_ptr(), &lkInfo, sizeof ( lkInfo ));
            mblk->wr_ptr(sizeof ( lkInfo ));
        }
        if ( channelType_ == ChannelProcInfo::ID_FUTURE )
        {
            ExturePlusKoscomLineLKInfo_KOSPI200_FUTURE lkInfo;
            ::memset(&lkInfo, 0, sizeof(ExturePlusKoscomLineLKInfo_KSE));
            ::memcpy(& ( lkInfo.dataCategory ), "I2", sizeof ( lkInfo.dataCategory ));
            ::memcpy(& ( lkInfo.informationCategory ), "00", sizeof ( lkInfo.informationCategory ));
            ::memcpy(& ( lkInfo.marketCategory ), "0", sizeof ( lkInfo.marketCategory ));
            ::memcpy(& ( lkInfo.time ), getCurrentTimestamp("%H%M").c_str(), sizeof ( lkInfo.time ));
            ::memcpy(& ( lkInfo.mainBackupType ), "00", sizeof ( lkInfo.marketCategory ));
            ::memcpy(& ( lkInfo.recvAddr ), strRecvAddr.c_str(), strRecvAddr.length());
            ::memcpy(mblk->wr_ptr(), &lkInfo, sizeof ( lkInfo ));
            mblk->wr_ptr(sizeof ( lkInfo ));
        }
        if ( channelType_ == ChannelProcInfo::ID_OPTION )
        {
            ExturePlusKoscomLineLKInfo_KOSPI200_OPTION lkInfo;
            ::memset(&lkInfo, 0, sizeof(ExturePlusKoscomLineLKInfo_KSE));
            ::memcpy(& ( lkInfo.dataCategory ), "I2", sizeof ( lkInfo.dataCategory ));
            ::memcpy(& ( lkInfo.informationCategory ), "00", sizeof ( lkInfo.informationCategory ));
            ::memcpy(& ( lkInfo.marketCategory ), "0", sizeof ( lkInfo.marketCategory ));
            ::memcpy(& ( lkInfo.time ), getCurrentTimestamp("%H%M").c_str(), sizeof ( lkInfo.time ));
            ::memcpy(& ( lkInfo.mainBackupType ), "00", sizeof ( lkInfo.marketCategory ));
            ::memcpy(& ( lkInfo.recvAddr ), strRecvAddr.c_str(), strRecvAddr.length());
            ::memcpy(mblk->wr_ptr(), &lkInfo, sizeof ( lkInfo ));
            mblk->wr_ptr(sizeof ( lkInfo ));
        }
        if ( channelType_ == ChannelProcInfo::ID_ELW )
        {
            ExturePlusKoscomLineLKInfo_ELW lkInfo;
            ::memset(&lkInfo, 0, sizeof(ExturePlusKoscomLineLKInfo_ELW));
            ::memcpy(& ( lkInfo.dataCategory ), "I2", sizeof ( lkInfo.dataCategory ));
            ::memcpy(& ( lkInfo.informationCategory ), "00", sizeof ( lkInfo.informationCategory ));
            ::memcpy(& ( lkInfo.marketCategory ), "0", sizeof ( lkInfo.marketCategory ));
            ::memcpy(& ( lkInfo.time ), getCurrentTimestamp("%H%M").c_str(), sizeof ( lkInfo.time ));
            ::memcpy(& ( lkInfo.recvAddr ), strRecvAddr.c_str(), strRecvAddr.length());
            ::memcpy(mblk->wr_ptr(), &lkInfo, sizeof ( lkInfo ));
            mblk->wr_ptr(sizeof ( lkInfo ));
        }
    }
    else
    {
        ::memcpy(mblk->wr_ptr(), data_, datalen_);
        mblk->wr_ptr(datalen_);
    }

    // log raw data
    if ( ( channelType_ == ChannelProcInfo::ID_KOSPI ) || ( channelType_ == ChannelProcInfo::ID_KOSDAQ ) || ( channelType_ == ChannelProcInfo::ID_FUTURE ) || ( channelType_ == ChannelProcInfo::ID_OPTION ) || ( channelType_ == ChannelProcInfo::ID_ELW ) )
    {
        parent_->logRcvData(mblk->rd_ptr() + sizeof channelType_, mblk->length() - sizeof channelType_, timeRecv, strRecvAddr);
    }


    // queuing
    if ( DataDispatcher::instance().put(mblk) == -1 )
    {
        mblk->release();
    }

    return 0;
}

int ClientChannel::handle_input(ACE_HANDLE)
{
    ACE_Time_Value timeout(1);

#if(1)
    char buffer[8192 * 20];
	int RECEIVE_MAX_SZ = sizeof(buffer);
#endif

    ssize_t recvSize = 0;

    recvSize = this->peer().recv(buffer, RECEIVE_MAX_SZ, &timeout);
    if ( recvSize == -1 )
    {
        ACE_DEBUG( ( LM_DEBUG , ACE_TEXT("[%s][ClientChannel::handle_input] 1.Channel Close\trecvSize:[%d] ERROR\n") , getCurrentTimestamp().c_str() , recvSize ));
        return -1;
    }

    if ( recvSize < 1 )
    {
        //ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("[%s][ClientChannel::handle_input] 2.Channel Close\trecvSize:[%d] ERROR\n"), getCurrentTimestamp().c_str(), recvSize));
        return -1;
    }

#if(0)
    int grid_cnt=0;
    for(int ii=0; ii < recvSize; ii++)
    {
    	if(datalen_ >=  (int)sizeof(data_))
    	{
    		ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("[%s][ClientChannel::handle_input]data end flag ERROR!!  ii[%d]data_ (%d)[%.*s] \n"),
    		    	    		getCurrentTimestamp().c_str(),  ii, datalen_, datalen_, data_));
    		datalen_ = 0;
    	}

    	data_[datalen_++] = buffer[ii];
    	/* TR data의 끝: CR(0x0D), LF(0x0A)로 구분 */
    	if(datalen_ > 2 && data_[datalen_-1] == 0x0a && data_[datalen_-2] == 0x0d &&  (unsigned char)(data_[datalen_-3]) == 0xff)
    	{
    	    //ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("[%s][ClientChannel::handle_input] channelId_[%d]recvSize[%d]ii[%d]data_ [%.5s][%d] \n"),
    	    //		getCurrentTimestamp().c_str(), channelId_, recvSize, ii, data_, datalen_));

    		dataFormat();
    		datalen_ = 0;
    		memset(data_, 0x00, sizeof(data_));

    		if(ii < recvSize-1);
    		{
    			grid_cnt++;
    			//ACE_DEBUG( ( LM_DEBUG , ACE_TEXT("[%s][ClientChannel::handle_input] recvSize[%d] ii[%d] data grid_cnt[%d]\n") ,
    			//					getCurrentTimestamp().c_str() , recvSize, ii, grid_cnt ));
    			continue;
    		}
    	}
    }
#endif

#if(1)
    int grid_cnt=0;
    for(int ii=0; ii < recvSize; ii++)
    {
    	if(datalen_ >=  (int)sizeof(data_))
    	{
    		ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("[%s][ClientChannel::handle_input]data end flag ERROR!!  ii[%d]data_ (%d)[%.*s] \n"),
    		    	    		getCurrentTimestamp().c_str(),  ii, datalen_, datalen_, data_));
    		datalen_ = 0;
    	}

    	data_[datalen_++] = buffer[ii];

/* 
 * EXTURE 3.0
 * Packet 구분자 : FF(0xff)+CR(0x0d)+LF(0x0a) → FF(0xff)
 *
 */
    	if(datalen_ > 2 && (unsigned char)(data_[datalen_- 1]) == 0xff)
    	{
    		dataFormat();
    		datalen_ = 0;
    		memset(data_, 0x00, sizeof(data_));

    		if(ii < recvSize-1);
    		{
    			grid_cnt++;
    			continue;
    		}
    	}
    }
#endif

    return 0;
}

int ClientChannel::handle_output(ACE_HANDLE)
{
    ACE_Message_Block *mb;
    ACE_Time_Value nowait(ACE_OS::gettimeofday());
    while ( -1 != this->getq(mb, &nowait) )
    {
        ssize_t send_cnt = this->peer().send(mb->rd_ptr(), mb->length());
        if ( send_cnt == -1 ) ACE_ERROR( ( LM_ERROR , ACE_TEXT("(%P|%t) %p  ERROR\n") , ACE_TEXT("send") ));
        else mb->rd_ptr(static_cast<size_t>(send_cnt));
        if ( mb->length() > 0 )
        {
            this->ungetq(mb);
            break;
        }
        mb->release();
    }
    return ( this->msg_queue()->is_empty() ) ? -1 : 0;
}

int ClientChannel::handle_close(ACE_HANDLE h, ACE_Reactor_Mask mask)
{
    if ( mask == ACE_Event_Handler::WRITE_MASK ) return 0;

    parent_->unregisterChannel(this);

    return super::handle_close(h, mask);
}

int ACE_TMAIN(int, ACE_TCHAR *[])
{
    ACE_INET_Addr port_to_listen("HAStatus");
    ClientAcceptor acceptor;
    if ( acceptor.open(port_to_listen) == -1 ) return 1;
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("[ClientChannel::ACE_TMAIN]\n") ));

    ACE_Reactor::instance()->run_reactor_event_loop();

    return 0;
}

int ClientChannel::checkValid()
{
    int result = 1;
    /**
     if(time(0) - lastHeartbeatTime_ > SESSION_TIMEOUT_INTERVAL) {
     result = handle_close_CheckConn (get_handle(), NULL_MASK);
     }
     **/

    return result;
}

