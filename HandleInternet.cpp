#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <sys/errno.h>

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

#include "DataDispatcher.h"
#include "ChannelProcInfo.h"
#include "HandleInternet.h"
#include "PaxfeedStringUtil.h"
#include "PaxfeedStatus.h"
//#include "FrameId.h"

using namespace paxfeed;

//-----------------------------------------------------------------------------
// register service objects
// �ʿ��ϸ� �߰��ؼ� ��밡��

//KSE
HandleInternet internetKse_001("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_001(&internetKse_001, "InternetKse_001");
HandleInternet internetKse_002("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_002(&internetKse_002, "InternetKse_002");
HandleInternet internetKse_003("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_003(&internetKse_003, "InternetKse_003");
HandleInternet internetKse_004("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_004(&internetKse_004, "InternetKse_004");
HandleInternet internetKse_005("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_005(&internetKse_005, "InternetKse_005");
HandleInternet internetKse_006("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_006(&internetKse_006, "InternetKse_006");
HandleInternet internetKse_007("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_007(&internetKse_007, "InternetKse_007");
HandleInternet internetKse_008("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_008(&internetKse_008, "InternetKse_008");
HandleInternet internetKse_009("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_009(&internetKse_009, "InternetKse_009");
HandleInternet internetKse_010("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_010(&internetKse_010, "InternetKse_010");
HandleInternet internetKse_011("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_011(&internetKse_011, "InternetKse_011");
HandleInternet internetKse_012("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_012(&internetKse_012, "InternetKse_012");
HandleInternet internetKse_013("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_013(&internetKse_013, "InternetKse_013");
HandleInternet internetKse_014("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_014(&internetKse_014, "InternetKse_014");
HandleInternet internetKse_015("Kse", ChannelProcInfo::ID_KOSPI);
ACE_Service_Object_Type ksehandler_015(&internetKse_015, "InternetKse_015");

//KOSDAQ
HandleInternet internetKosdaq_001("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_001(&internetKosdaq_001, "InternetKosdaq_001");
HandleInternet internetKosdaq_002("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_002(&internetKosdaq_002, "InternetKosdaq_002");
HandleInternet internetKosdaq_003("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_003(&internetKosdaq_003, "InternetKosdaq_003");
HandleInternet internetKosdaq_004("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_004(&internetKosdaq_004, "InternetKosdaq_004");
HandleInternet internetKosdaq_005("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_005(&internetKosdaq_005, "InternetKosdaq_005");
HandleInternet internetKosdaq_006("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_006(&internetKosdaq_006, "InternetKosdaq_006");
HandleInternet internetKosdaq_007("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_007(&internetKosdaq_007, "InternetKosdaq_007");
HandleInternet internetKosdaq_008("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_008(&internetKosdaq_008, "InternetKosdaq_008");
HandleInternet internetKosdaq_009("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_009(&internetKosdaq_009, "InternetKosdaq_009");
HandleInternet internetKosdaq_010("Kosdaq", ChannelProcInfo::ID_KOSDAQ);
ACE_Service_Object_Type kosdaqhandler_010(&internetKosdaq_010, "InternetKosdaq_010");

//��������
HandleInternet internetFutureIndex_001("FutureIndex", ChannelProcInfo::ID_FUTURE);
ACE_Service_Object_Type futureIndexhandler_001(&internetFutureIndex_001, "InternetFutureIndex_001");
HandleInternet internetFutureIndex_002("FutureIndex", ChannelProcInfo::ID_FUTURE);
ACE_Service_Object_Type futureIndexhandler_002(&internetFutureIndex_002, "InternetFutureIndex_002");
HandleInternet internetFutureIndex_003("FutureIndex", ChannelProcInfo::ID_FUTURE);
ACE_Service_Object_Type futureIndexhandler_003(&internetFutureIndex_003, "InternetFutureIndex_003");
HandleInternet internetFutureIndex_004("FutureIndex", ChannelProcInfo::ID_FUTURE);
ACE_Service_Object_Type futureIndexhandler_004(&internetFutureIndex_004, "InternetFutureIndex_004");
HandleInternet internetFutureIndex_005("FutureIndex", ChannelProcInfo::ID_FUTURE);
ACE_Service_Object_Type futureIndexhandler_005(&internetFutureIndex_005, "InternetFutureIndex_005");

//�����ɼ�
HandleInternet internetOptionIndex_001("OptionIndex", ChannelProcInfo::ID_OPTION);
ACE_Service_Object_Type optionIndexhandler_001(&internetOptionIndex_001, "InternetOptionIndex_001");
HandleInternet internetOptionIndex_002("OptionIndex", ChannelProcInfo::ID_OPTION);
ACE_Service_Object_Type optionIndexhandler_002(&internetOptionIndex_002, "InternetOptionIndex_002");
HandleInternet internetOptionIndex_003("OptionIndex", ChannelProcInfo::ID_OPTION);
ACE_Service_Object_Type optionIndexhandler_003(&internetOptionIndex_003, "InternetOptionIndex_003");
HandleInternet internetOptionIndex_004("OptionIndex", ChannelProcInfo::ID_OPTION);
ACE_Service_Object_Type optionIndexhandler_004(&internetOptionIndex_004, "InternetOptionIndex_004");
HandleInternet internetOptionIndex_005("OptionIndex", ChannelProcInfo::ID_OPTION);
ACE_Service_Object_Type optionIndexhandler_005(&internetOptionIndex_005, "InternetOptionIndex_005");

// ELW
HandleInternet internetElw_001("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_001(&internetElw_001, "InternetElw_001");
HandleInternet internetElw_002("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_002(&internetElw_002, "InternetElw_002");
HandleInternet internetElw_003("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_003(&internetElw_003, "InternetElw_003");
HandleInternet internetElw_004("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_004(&internetElw_004, "InternetElw_004");
HandleInternet internetElw_005("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_005(&internetElw_005, "InternetElw_005");
HandleInternet internetElw_006("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_006(&internetElw_006, "InternetElw_006");
HandleInternet internetElw_007("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_007(&internetElw_007, "InternetElw_007");
HandleInternet internetElw_008("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_008(&internetElw_008, "InternetElw_008");
HandleInternet internetElw_009("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_009(&internetElw_009, "InternetElw_009");
HandleInternet internetElw_010("Elw", ChannelProcInfo::ID_ELW);
ACE_Service_Object_Type elwhandler_010(&internetElw_010, "InternetElw_010");
//-----------------------------------------------------------------------------

/*
 ���� �ð� ���ڿ��� ����Ѵ�.
 YYYYMMDD_HHMMSS
 */
ACE_CString HandleInternet::getCurrentTimestamp()
{
    char buffer[32];
    ::memset(&buffer, 0, sizeof ( buffer ));
    struct tm stTm;
    ::memset(&stTm, 0, sizeof(struct tm));
    time_t currentTime = time(NULL);
    ::localtime_r(&currentTime, &stTm);
    ::strftime(buffer, sizeof ( buffer ), "%Y%m%d_%H%M%S", &stTm);
    ACE_CString strCurrentTime(buffer);
    return strCurrentTime;
}

HandleInternet::HandleInternet(const ACE_CString& logFileSuffix, int channelType)
        : logFileSuffix_(logFileSuffix), channelType_(channelType)
{
//  ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::HandleInternet] BEGIN\n", getCurrentTimestamp().c_str() ));
//  ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::HandleInternet] logFileSuffix_:[%s]\tchannelType_:[%d]\n", getCurrentTimestamp().c_str(), logFileSuffix_.c_str(), channelType_));
//  ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::HandleInternet] END\n", getCurrentTimestamp().c_str()));
}

int HandleInternet::info(char **, size_t) const
{
//  ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::info] BEGIN\n", getCurrentTimestamp().c_str() ));
//  ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::info] END\n", getCurrentTimestamp().c_str() ));
    return 0;
}

int HandleInternet::open(const ACE_INET_Addr &sia)
{
//  ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::open] BEGIN\n", getCurrentTimestamp().c_str()));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::open] sia.get_host_addr():[%s]\tsia.get_port_number:[%d]\n" , getCurrentTimestamp().c_str() , sia.get_host_addr() , sia.get_port_number() ));
    if ( this->acceptor_.open(sia, 1) == -1 )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::open] this->acceptor_.open ERROR\n" , getCurrentTimestamp().c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::open] APP shutdown executed.\n" , getCurrentTimestamp().c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::open] ACE_OS::exit(-1);\n" , getCurrentTimestamp().c_str() ));
        ACE_OS::exit(-1);
        return -1;
    }
//    ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::open] END\n", getCurrentTimestamp().c_str()));
    return 0;
}

int HandleInternet::init(int argc, char *argv[])
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::init] BEGIN\n" , getCurrentTimestamp().c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::init] argc:[%d]\n" , getCurrentTimestamp().c_str() , argc ));

    time_t curtime = ::time(0);
    struct tm* tmCurr = ::localtime(&curtime);
    currentHour_ = tmCurr->tm_hour;

    ACE_CString ports;
    int mcastPort = 0;
    ACE_CString mcastGroup;
    ACE_CString dirRawLog;

    ACE_Get_Opt get_opt(argc, argv, "p:x:a:l:m:", 0);
    for ( int c ; ( c = get_opt() ) != -1 ; )
    {
        switch ( c )
        {
            case 'p' :
                ports = ACE_CString(get_opt.opt_arg());
                break;

            case 'x' :
                mcastPort = ACE_OS::atoi(get_opt.opt_arg());
                break;

            case 'a' :
                mcastGroup = get_opt.opt_arg();
                break;

            case 'l' :
                dirRawLog_ = get_opt.opt_arg();
                break;

            case 'm' :
                dirMasterFile_ = get_opt.opt_arg();
                break;

            default :
                break;
        }
    }

    port_ = ports;
    setFrameIdLength();
    prepareLogFile();

    ACE_DLList < ACE_CString > portList = splitString(ports, ",");
    ACE_DLList_Iterator < ACE_CString > iter(portList);

    while ( !iter.done() )
    {
        ACE_CString* item = iter.next();
        iter++;
        int port = ACE_OS::atoi(item->c_str());
        delete item;
        ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::init] port:[%d]\n" , getCurrentTimestamp().c_str() , port ));

        if ( port <= 0 )
        {
            continue;
        }

        ACE_INET_Addr local_addr(port);
        if ( ( this->open(local_addr) == -1 ) || ( this->get_handle() == ACE_INVALID_HANDLE ) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , ACE_TEXT("%p\n") , ACE_TEXT("open") ), -1);
        }
        if ( ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK) == -1 )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , ACE_TEXT("registering service with ACE_Reactor\n") ), -1);
        }

        ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::init] local_addr.get_host_addr():[%s]\tlocal_addr.get_port_number():[%d]\n" , getCurrentTimestamp().c_str() , local_addr.get_host_addr() , local_addr.get_port_number() ));
    }

    ACE_INET_Addr mcastAddr(mcastPort, mcastGroup.c_str());
    //by hsy; 2016.02.23 mcast sender�� open���� �ν��Ͻ� ���� (join�� mcast receiver���� ���)
    if ( -1 == XMITTER::instance()->open(mcastAddr) )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::init] mcast group : maybe already open ... \n" , getCurrentTimestamp().c_str() ));
    }
    else
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::init] mcastGroup:[%s]\tmcastPort:[%d] XMITTER::instance()->open() OK\n" , getCurrentTimestamp().c_str() , mcastGroup.c_str() , mcastPort ));
    }
    XMITTER::instance()->setActive(true);
    ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::init] END\n" , getCurrentTimestamp().c_str() ));

    return 0;
}

int HandleInternet::fini(void)
{
    int retv = 0;
    if ( this->get_handle() != ACE_INVALID_HANDLE )
    {
        retv = ACE_Reactor::instance()->remove_handler(this, ACE_Event_Handler::ACCEPT_MASK | ACE_Event_Handler::DONT_CALL);
        this->handle_close(ACE_INVALID_HANDLE, ACE_Event_Handler::NULL_MASK);
    }
    return ( retv );
}

int HandleInternet::handle_signal(int, siginfo_t *, ucontext_t *)
{
    return ( 0 );
}

ACE_HANDLE HandleInternet::get_handle(void) const
{
    return ( this->acceptor_.get_handle() );
}

int HandleInternet::prepareLogFile()
{
    ACE_TRACE(ACE_TEXT("prepareLogFile"));

    if ( dirRawLog_.length() != 0 )
    {
        // close opened file
        rawLogFile_.close();

        // prepare filename
        time_t curtime = time(0);
        struct tm* tmCurr = ::localtime(&curtime);
        std::ostringstream os;
        os << dirRawLog_ << "/" << std::setfill('0') << std::setw(4) << tmCurr->tm_year + 1900 << std::setfill('0') << std::setw(2) << tmCurr->tm_mon + 1 << std::setfill('0') << std::setw(2) << tmCurr->tm_mday << "_" << std::setfill('0') << std::setw(2) << tmCurr->tm_hour << "_internet_" << logFileSuffix_.c_str() << "_" << port_.c_str() << ".log";

        // open new file
        ACE_FILE_Connector connector;
        return connector.connect(rawLogFile_, ACE_FILE_Addr(os.str().c_str()), 0, // No timeout.
                ACE_Addr::sap_any, // Ignored.
                0, // Don't try to reuse the addr.
                O_RDWR | O_CREAT | O_APPEND, ACE_DEFAULT_FILE_PERMS);
    }
    else
    {
        return 0;
    }
}

void HandleInternet::setFrameIdLength()
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::setFrameIdLength] BEGIN\n" , getCurrentTimestamp().c_str() ));

    setFrameIdLength_KSE_KRX();
    setFrameIdLength_KSE_KOSCOM();
    setFrameIdLength_KSE_ETC();
    setFrameIdLength_KOSDAQ_KRX();
    setFrameIdLength_KOSDAQ_KOSCOM();
    setFrameIdLength_KOSDAQ_ETC();
    setFrameIdLength_KOSPI200_FUTURE();
    setFrameIdLength_KOSPI200_OPTION();
    setFrameIdLength_ELW_KRX();
    setFrameIdLength_ELW_KOSCOM();
    setFrameIdLength_ELW_ETC();

    ACE_DEBUG( ( LM_DEBUG , "[%s] [HandleInternet::setFrameIdLength] END\n" , getCurrentTimestamp().c_str() ));
}

void HandleInternet::setFrameIdLength_KSE_KRX()
{
#if(0)
    kseFrameIdMap.bind("A0011", 802);      // 1    �ڽ��������ġ A0011   �����ġ    802
    kseFrameIdMap.bind("A1041", 302);      // 2    ETN �����ġ    A1041   ETN �����ġ    302
    kseFrameIdMap.bind("I6011", 52);      // 3    �ڽ��� ���� �̺�Ʈ ����   I6011   �ŷ�����,�������������� �����̺�Ʈ���� ���� 52
    kseFrameIdMap.bind("I5011", 32);      // 4    �ڽ��� ����� ����  I5011   ����� ����  32
    kseFrameIdMap.bind("A3011", 162);      // 5    �ڽ���ü��   A3011   �ڽ���_ü��  162
    kseFrameIdMap.bind("A4011", 62);      // 6    �ڽ��Ǳ��ذ�����    A4011   �ڽ���_���ذ�����   62
    kseFrameIdMap.bind("A5011", 32);      // 7    �ڽ����������� A5011   �ڽ���_��������    32
    kseFrameIdMap.bind("A6011", 92);      // 8    �ڽ������񸶰� A6011   �ڽ���_���񸶰�    92
    kseFrameIdMap.bind("A7011", 52);      // 9    �ڽ�����TS    A7011   �ڽ���_��TS   52
    kseFrameIdMap.bind("O6011", 42);      // 10   �ڽ��� �������    O6011   �ڽ���_�������    42
    kseFrameIdMap.bind("I7011", 252);      // 29    �ڽ��� LP ����   I7011   LP ����   252
    kseFrameIdMap.bind("C4011", 112);      // 12   �ڽ��Ǵ뷮ü�� C4011   �ڽ���_�뷮ü��    112
    kseFrameIdMap.bind("A8011", 122);      // 13   �ڽ����ֽ������������� A8011   �ڽ���_�������� -> �ڽ���_�ֽ�������������    122
    kseFrameIdMap.bind("R3011", 52);      // 14   �ڽ��� ȸ��������������    R3011   �ڽ���_ȸ��������������    52
    kseFrameIdMap.bind("M4011", 72);      // 15   14    �ڽ����������ٰ��� M4011   �ڽ���_������ -> �ڽ���_�������ٰ���   72  �ǽð� ���������ֽ�ü������
    kseFrameIdMap.bind("B1011", 292);      // 16   �ڽ��� ���� RECOVERY B1011   �ڽ���_�ü�����    292
    kseFrameIdMap.bind("B2011", 292);      // 17   �ڽ��� �ü� RECOVERY B2011   �ڽ���_�ü�RECOVERY  292
    kseFrameIdMap.bind("B4011", 172);      // 18   �ڽ��� �ð��ܴ��ϰ� RECOVERY B4011   �ڽ���_�ð��ܴ��ϰ�_�ü�   172
    kseFrameIdMap.bind("B3011", 172);      // 19   �ڽ��� �ð��ܴ��ϰ� ����   B3011   �ڽ���_�ð��ܴ��ϰ�_����   172
    kseFrameIdMap.bind("B5011", 62);      // 20   �ڽ��� ������    B5011   ����,���,����,����,�϶������ ���� ���� 62
    kseFrameIdMap.bind("B6011", 562);      // 21   �ڽ��� ȣ���ܷ�_LPȣ��_����    B6011   �ڽ���_ȣ���ܷ�_LPȣ��_����    562
    kseFrameIdMap.bind("B7011", 802);      // 22   �ڽ��� ȣ���ܷ�_LPȣ��_����    B7011   �ڽ���_ȣ���ܷ�_LPȣ��_����    802
    kseFrameIdMap.bind("B8011", 62);      // 23   �ڽ��� �尳���� ȣ���ܷ�   B8011   �ڽ���_�尳����_ȣ���ܷ�   62
    kseFrameIdMap.bind("C0011", 88);      // 24   �ڽ��� �����������ں� C0011   �����������ں� 88
    kseFrameIdMap.bind("C2011", 382);      // 25   �ڽ��� ���α׷��Ÿ��Ϻ����Ͱŷ��ܰ�  C2011   ���α׷��Ÿ� �Ϻ����Ͱŷ��ܰ� 382
    kseFrameIdMap.bind("J1011", 132);      // 26   �ڽ��� ���α׷��Ÿ����Ͱŷ��ܰ� �ּ� J1011   ���α׷��Ÿ� ���Ͱŷ��ܰ��ּ� 132
    kseFrameIdMap.bind("C3011", 462);      // 27   �ڽ��� ���α׷��Ÿ� ȣ��   C3011   ���α׷��Ÿ� ȣ��   462
    kseFrameIdMap.bind("J0011", 442);      // 28   �ڽ��� ���α׷��Ÿ� ��ü���� J0011   ���α׷��Ÿ� ��ü���� 442
    kseFrameIdMap.bind("C5011", 102);      // 29   �ڽ��� ���α׷��Ÿ� �������� C5011   ���α׷��Ÿ� �������� 102
    kseFrameIdMap.bind("F0011", 1372);      // 30   �ڽ��� ���ýǽð�   F0011   ����REAL  1372
    kseFrameIdMap.bind("E9011", 1372);      // 31   �ڽ��� ���ù�ġ    E9011   ���ù�ġ    1372
    kseFrameIdMap.bind("O4011", 62);      // 32   �ڽ��� Buy-in�������  O4011   Buy-in�������  62
    kseFrameIdMap.bind("P2011", 18);      // 33   �ڽ��� ������ �����ͷ�   P2011   �ڽ��� ������ �����ͷ�   18
    kseFrameIdMap.bind("B9011", 382);      // 34   �ڽ��� �ŷ��� B9011   �ŷ��� 382
    kseFrameIdMap.bind("M9011", 212);      // 35   ȸ���� ����  M9011   ȸ��������   212
    kseFrameIdMap.bind("C0031", 88);      // 36   ETF_�����ں�    C0031   ETF �����ں�    88

    kseFrameIdMap.bind("C8011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  krx100(����)(��Ī:��������)
    kseFrameIdMap.bind("C9011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  krx100��������
    kseFrameIdMap.bind("D0011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ�������
    kseFrameIdMap.bind("D1011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ǿ�������
    kseFrameIdMap.bind("D2011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ���200����
    kseFrameIdMap.bind("D3011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ���200��������
    kseFrameIdMap.bind("D4011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ���100/50����
    kseFrameIdMap.bind("D6011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ǹ������(��Ī:�������)
    kseFrameIdMap.bind("D7011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ǹ�翹������
    kseFrameIdMap.bind("D8011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  "�ڽ��Ǳ�����豸������(��Ī:������豸������)(2012.09.14)"
    kseFrameIdMap.bind("K2011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  ��������kospi200����
    kseFrameIdMap.bind("E0011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  ��������
    kseFrameIdMap.bind("E1011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  ���Ϳ�������
    kseFrameIdMap.bind("L0011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  "krx sri����(2012.09.14)"
    kseFrameIdMap.bind("L1011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  krx sri��������(2012.09.14)
    kseFrameIdMap.bind("E4011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ�������
    kseFrameIdMap.bind("E5011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ڿ�������
    kseFrameIdMap.bind("E6011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ڽ�Ÿ����(��Ī:��Ÿ����)
    kseFrameIdMap.bind("E7011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ڽ�Ÿ��������
    kseFrameIdMap.bind("L2011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  kosdaq�����̾�����
    kseFrameIdMap.bind("L3011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  kosdaq�����̾������
    kseFrameIdMap.bind("N1011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  krx ����������
    kseFrameIdMap.bind("N2011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  krx ��������������
    kseFrameIdMap.bind("N5011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  kospi200 ��������
    kseFrameIdMap.bind("N6011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  kospi200 ���Ϳ�������
    kseFrameIdMap.bind("N9011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  ���ϰ�������
    kseFrameIdMap.bind("O1011", 52);      // 37   �ڽ��� ����_�������� ����/�������� 52  ���ϰ��߿�������

    kseFrameIdMap.bind("F0012", 1372);      // 38   �ڽ��� ���ø���    F0012   ����REAL  1372
    kseFrameIdMap.bind("E9012", 1372);      // 39   �ڽ��� ���ù�ġ    E9012   ���ù�ġ    1372
    kseFrameIdMap.bind("F0018", 1372);      // 40   �ڳؽ� ���ø���    F0018   ����REAL  1372
    kseFrameIdMap.bind("E9018", 1372);      // 41   �ڳؽ� ���ù�ġ    E9018   ���ù�ġ    1372
    kseFrameIdMap.bind("P0011", 138);      // 42   �ڽ��� ���α׷��Ÿ� �����ں� �Ÿ���Ȳ    P0011   �ڽ��� ���α׷��Ÿ� �����ں� �Ÿ���Ȳ    138
    kseFrameIdMap.bind("O4012", 62);      // 43   �ڽ��� Buy-in�������  O4012   Buy-in�������  62
    kseFrameIdMap.bind("O4018", 62);      // 44   �ڳؽ�_Buy-in_������� O4018   �ڳؽ�_Buy-in_������� 62
    kseFrameIdMap.bind("R8011", 102);      // 46    �ڽ���_�����������(VI)  R8011   �ڽ���_�����������(VI)  102 �ǽð�
    kseFrameIdMap.bind("C0041", 88);      // 47   ETN_�����ں�    C0041   ETN �����ں�    88
    kseFrameIdMap.bind("T7011", 52);      // 48   KTOP30����  T7011   "�ѱ� ���� �� ���ø� ��ǥ�ϴ� �Ҽ��� �ʿ췮 �������� ������ ��ǥ����"   52  2���ֱ�
    kseFrameIdMap.bind("T8011", 52);      // 49   KTOP30��������    T8011   "�ѱ� ���� �� ���ø� ��ǥ�ϴ� �Ҽ��� �ʿ췮 �������� ������ ��ǥ����"   52  2���ֱ�

    kseFrameIdMap.bind("V6011", 201);      // 51 ETP�������� V6011   ETP�������� 201 ���� 05:30, 06:10, 06:50 ��3ȸ ����(��, A0011[KOSPI��������]���� �Ϸ� �� ����
#endif
}
void HandleInternet::setFrameIdLength_KSE_KOSCOM()
{
#if(0)
    kseFrameIdMap.bind("F1011", 82);              // 1    �ڽ��� �ܱ��� �������� ���� Ȯ��ġ    F1011   �ܱ��� ������������(Ȯ��ġ)    82
    kseFrameIdMap.bind("F1012", 82);              // 1    �ڽ��� �ܱ��� �������� ���� Ȯ��ġ    F1011   �ܱ��� ������������(Ȯ��ġ)    82
    kseFrameIdMap.bind("F4011", 62);              // 2    �ڽ��� �ܱ��� Ȯ��ġ������������   F4011   �ܱ��������������� ������ ���������� ��������   62
    kseFrameIdMap.bind("F4012", 62);              // 2    �ڽ��� �ܱ��� Ȯ��ġ������������   F4011   �ܱ��������������� ������ ���������� ��������   62
    kseFrameIdMap.bind("N8011", 252);              // 3    ETF�繫��Ź��ġ   N8011   ETF �����ġ    252
    kseFrameIdMap.bind("F7011", 72);              // 4    ETF NAV F7011   ETF NAV 72
    kseFrameIdMap.bind("I3011", 52);              // 5    ETF ����NAV   I3011   ETF ����NAV   52
    kseFrameIdMap.bind("F8011", 162);              // 6    ETF PDF F8011   ETF PDF 162
    kseFrameIdMap.bind("M8011", 132);              // 7    ETF�������    M8011   ETF�������    132
    kseFrameIdMap.bind("P6011", 62);              // 8    ETF ����������   P6011   ETF ����������   62
    kseFrameIdMap.bind("Q4011", 202);              // 9    �ռ�ETF ���� �ŷ����� �����򰡾� ���� Q4011   �ռ�ETF ���� �ŷ����� �����򰡾� ���� 202
    kseFrameIdMap.bind("Q5011", 202);              // 10   �ռ�ETF �������� �������� Q5011   �ռ�ETF �������� �������� 202
    kseFrameIdMap.bind("S1011", 132);              // 11   ETN �繫��Ź����  S1011   ETN �繫��Ź����  132
    kseFrameIdMap.bind("S2011", 202);              // 12   ETN �������� ��������   S2011   ETN �������� ��������   202
    kseFrameIdMap.bind("S3011", 72);              // 13   ETN IIV S3011   ETN �ǽð���ǥ��ġ(IIV)    72
#endif
}

void HandleInternet::setFrameIdLength_KSE_ETC()
{
#if(0)
    kseFrameIdMap.bind("LK000", 13);              // 49   LINK    LK  LINK    13  1�а������͹̹߻�������
    kseFrameIdMap.bind("DT000", 108);              // ���� �����ں� ����(FTP)
    kseFrameIdMap.bind("ZZ011", 162);              // ���νü���Ŀ����(ü����������)
#endif
}

void HandleInternet::setFrameIdLength_KOSDAQ_KRX()
{
#if(0)
    kosdaqFrameIdMap.bind("A0012", 802);       // 1    �ڽ��������ġ A0012   �����ġ    802
    kosdaqFrameIdMap.bind("I5012", 32);       // 2    �ڽ��� ����� ����  I5012   ����� ����  32
    kosdaqFrameIdMap.bind("I6012", 52);       // 3    �ڽ��� ���� �̺�Ʈ ����   I6012   �ŷ�����,�������������� �����̺�Ʈ���� ���� 52
    kosdaqFrameIdMap.bind("I7012", 252);       // 4 �ڽ��� LP ����   I7012   LP ����   252
    kosdaqFrameIdMap.bind("A3012", 162);       // 5    �ڽ���ü��   A3012   �ڽ���_ü��  162
    kosdaqFrameIdMap.bind("A4012", 62);       // 6    �ڽ��ڱ��ذ�����    A4012   �ڽ���_���ذ�����   62
    kosdaqFrameIdMap.bind("A5012", 32);       // 7    �ڽ����������� A5012   �ڽ���_��������    32
    kosdaqFrameIdMap.bind("A6012", 92);       // 8    �ڽ������񸶰� A6012   �ڽ���_���񸶰�    92
    kosdaqFrameIdMap.bind("A7012", 52);       // 9    �ڽ�����TS    A7012   �ڽ���_��TS   52
    kosdaqFrameIdMap.bind("O6012", 42);       // 10   �ڽ��� �������    O6012   �ڽ���_�������    42
    kosdaqFrameIdMap.bind("C4012", 112);       // 11   �ڽ��ڴ뷮ü�� C4012   KOSDAQ_�뷮ü�� 112
    kosdaqFrameIdMap.bind("A8012", 122);       // 12   �ڽ����ֽ������������� A8012   �ڽ���_�������� -> �ڽ���_�ֽ�������������    122
    kosdaqFrameIdMap.bind("R3012", 52);       // 13   �ڽ���ȸ�������������� R3012   �ڽ���_ȸ��������������    52
    kosdaqFrameIdMap.bind("M4012", 72);       // 13 �ڽ����������ٰ��� M4012   �ڽ���_������ -> �ڽ���_�������� ����  72  �ǽð� �ڽ����ֽ�ü������
    kosdaqFrameIdMap.bind("B1012", 292);       // 15   �ڽ��� ���� RECOVERY B1012   �ڽ���_�ü�����    292
    kosdaqFrameIdMap.bind("B2012", 292);       // 16   �ڽ��� �ü� RECOVERY B2012   �ڽ���_�ü�RECOVERY  292
    kosdaqFrameIdMap.bind("B3012", 172);       // 17   �ڽ��� �ð��ܴ��ϰ� ����   B3012   �ڽ���_�ð��ܴ��ϰ�_����   172
    kosdaqFrameIdMap.bind("B4012", 172);       // 18   �ڽ��� �ð��ܴ��ϰ� RECOVERY B4012   �ڽ���_�ð��ܴ��ϰ�_�ü�   172
    kosdaqFrameIdMap.bind("B5012", 62);       // 19   �ڽ��� ������    B5012   ������    62
    kosdaqFrameIdMap.bind("B6012", 562);       // 20   �ڽ��� ȣ���ܷ�_LPȣ��_����    B6012   �ڽ���_ȣ���ܷ�_LPȣ��_����    562
    kosdaqFrameIdMap.bind("B7012", 792);       // 21   �ڽ��� ȣ���ܷ�_LPȣ��_����    B7012   ȣ���ܷ�_LPȣ��_���� (ETF)  792
    kosdaqFrameIdMap.bind("B8012", 62);       // 22   �ڽ��� �尳���� ȣ���ܷ�   B8012   �ڽ���_�尳����_ȣ���ܷ�   62
    kosdaqFrameIdMap.bind("C0012", 88);       // 23   �ڽ��� �����������ں� C0012   �����������ں� 88
    kosdaqFrameIdMap.bind("C2012", 382);       // 24   �ڽ��� ���α׷��Ÿ��Ϻ����Ͱŷ��ܰ�  C2012   ���α׷��Ÿ� �Ϻ����Ͱŷ��ܰ� 382
    kosdaqFrameIdMap.bind("J1012", 132);       // 25   �ڽ��� ���α׷��Ÿ����Ͱŷ��ܰ��ּ�  J1012   ���α׷��Ÿ� ���Ͱŷ��ܰ��ּ� 132
    kosdaqFrameIdMap.bind("C3012", 462);       // 26   �ڽ��� ���α׷��Ÿ� ȣ��   C3012   ���α׷��Ÿ� ȣ��   462
    kosdaqFrameIdMap.bind("J0012", 442);       // 27   �ڽ��� ���α׷��Ÿ� ��ü���� J0012   ���α׷��Ÿ� ��ü���� 442
    kosdaqFrameIdMap.bind("C5012", 102);       // 28   �ڽ��� ���α׷��Ÿ� �������� C5012   ���α׷��Ÿ� �������İ���   102
    kosdaqFrameIdMap.bind("P0012", 138);       // 29   �ڽ��� ���α׷��Ÿ� �����ں� �Ÿ���Ȳ    P0012   �ڽ��� ���α׷��Ÿ� �����ں� �Ÿ���Ȳ    138
    kosdaqFrameIdMap.bind("P2012", 18);       // 30   �ڽ��� ������ �����ͷ�   P2012   �ڽ��� ������ �����ͷ�   18
    kosdaqFrameIdMap.bind("B9012", 382);       // 31   �ڽ��� �ŷ��� B9012   �ŷ��� 382

    kosdaqFrameIdMap.bind("C8012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  krx100(����)(��Ī:��������)
    kosdaqFrameIdMap.bind("C9012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  krx100��������
    kosdaqFrameIdMap.bind("D0012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ�������
    kosdaqFrameIdMap.bind("D1012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ǿ�������
    kosdaqFrameIdMap.bind("D2012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ���200����
    kosdaqFrameIdMap.bind("D3012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ���200��������
    kosdaqFrameIdMap.bind("D4012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ���100/50����
    kosdaqFrameIdMap.bind("D6012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ǹ������(��Ī:�������)
    kosdaqFrameIdMap.bind("D7012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ǹ�翹������
    kosdaqFrameIdMap.bind("D8012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  "�ڽ��Ǳ�����豸������(��Ī:������豸������)(2012.09.14)"
    kosdaqFrameIdMap.bind("K2012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  ��������kospi200����
    kosdaqFrameIdMap.bind("E0012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  ��������
    kosdaqFrameIdMap.bind("E1012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  ���Ϳ�������
    kosdaqFrameIdMap.bind("L0012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  krx sri����(2012.09.14)
    kosdaqFrameIdMap.bind("L1012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  krx sri��������(2012.09.14)
    kosdaqFrameIdMap.bind("E4012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ�������
    kosdaqFrameIdMap.bind("E5012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ڿ�������
    kosdaqFrameIdMap.bind("E6012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ڽ�Ÿ����(��Ī:��Ÿ����)
    kosdaqFrameIdMap.bind("E7012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  �ڽ��ڽ�Ÿ��������
    kosdaqFrameIdMap.bind("L2012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  kosdaq�����̾�����
    kosdaqFrameIdMap.bind("L3012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  kosdaq�����̾������
    kosdaqFrameIdMap.bind("N1012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  krx ����������
    kosdaqFrameIdMap.bind("N2012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  krx ��������������
    kosdaqFrameIdMap.bind("N5012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  kospi200 ��������
    kosdaqFrameIdMap.bind("N6012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  kospi200 ���Ϳ�������
    kosdaqFrameIdMap.bind("N9012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  ���ϰ�������
    kosdaqFrameIdMap.bind("O1012", 52);       // 32   �ڽ��� ����_�������� ����/�������� 52  ���ϰ��߿�������
    kosdaqFrameIdMap.bind("R8012", 102);       // 32    �ڽ���_�����������(VI)  R8012   �ڽ���_�����������(VI)  102 �ǽð�
#endif
}
void HandleInternet::setFrameIdLength_KOSDAQ_KOSCOM()
{
#if(0)
    // �ڽ����ֽ�_�ǽð�_���ͳ�(KOSCOM)_20130809_2013082601.xls
    kosdaqFrameIdMap.bind("F1011", 82);           // 1    �ڽ��� �ܱ��� �������� ���� Ȯ��ġ    F1012   �ܱ��� ������������(Ȯ��ġ)    82
    kosdaqFrameIdMap.bind("F1012", 82);           // 1    �ڽ��� �ܱ��� �������� ���� Ȯ��ġ    F1012   �ܱ��� ������������(Ȯ��ġ)    82
    kosdaqFrameIdMap.bind("F4011", 62);           // 2    �ڽ��� �ܱ��� Ȯ��ġ������������   F4012   �ܱ��������������� ������ ���������� ��������   62
    kosdaqFrameIdMap.bind("F4012", 62);           // 2    �ڽ��� �ܱ��� Ȯ��ġ������������   F4012   �ܱ��������������� ������ ���������� ��������   62
#endif
}

void HandleInternet::setFrameIdLength_KOSDAQ_ETC()
{
#if(0)
    kosdaqFrameIdMap.bind("LK000", 13);              // 47  LINK    LK  LINK    13  1�а������͹̹߻�������
    kosdaqFrameIdMap.bind("DT000", 108);              // ���� �����ں� ����(FTP)
    kosdaqFrameIdMap.bind("ZZ012", 162);              // ���νü���Ŀ����(ü����������)
#endif
}

void HandleInternet::setFrameIdLength_KOSPI200_FUTURE()
{
#if(0)
    // KOSPI200��������_�ǽð�_���ͳ�(KRX)_20140901_2014073001.xls
    futureFrameIdMap.bind("A0014", 1202);        // 1   KOSPI200�������� �������� ������   A0014   ���� �ŷ������ �Ǵ� ���� ���� ���� �ڷ� ���� 1202
    futureFrameIdMap.bind("B6014", 222);        // 2   KOSPI200�������� �켱ȣ��   B6014   ������ �߻��ø��� �ǽð� ����    222
    futureFrameIdMap.bind("A3014", 119);        // 3   KOSPI200�������� ü�� A3014   ������ �߻��ø��� �ǽð� ����    119
    futureFrameIdMap.bind("G7014", 301);        // 4   KOSPI200�������� ü��_�켱ȣ��    G7014   ������ �߻��ø��� �ǽð� ����    301
    futureFrameIdMap.bind("A6014", 239);        // 5   KOSPI200�������� ���񸶰�   A6014   ���񸶰��ÿ� ���񺰷� ����  239
    futureFrameIdMap.bind("A7014", 248);        // 6   KOSPI200��������_��TS  A7014   �� �̺�Ʈ �߻��� ����  248
    futureFrameIdMap.bind("H0014", 8);        // 7   KOSPI200�������� ���� H0014   ���� �ü�(B6,A3,G7,A6)������ ���� �˸�������  8
    futureFrameIdMap.bind("O6014", 34);        // 8   KOSPI200�������� �������   O6014   ���ϰ�ü��� ��/���Ѱ��� �����Ǵ� ��� ��/���Ѱ� �ż�, �ŵ��ֹ��� ���� �������� ������ ���������� ����Ͽ� ü���Ű�� ��� ����    34
    futureFrameIdMap.bind("H1014", 147);        // 9   KOSPI200�������� ������ ������    H1014   "����Ȯ��ġ:�尳����, ����:30�ʰ���, ����Ȯ��ġ:�������� ����"   147
    futureFrameIdMap.bind("H2014", 41);        // 10  KOSPI200�������� �̰����������� ������    H2014   ������ �̰����������� ������ 41
    futureFrameIdMap.bind("H3014", 56);        // 11  KOSPI200�������� ���갡�� ������   H3014   �������갡   56
    futureFrameIdMap.bind("M4014", 70);        // 12    KOSPI200�������� �������ٰ���   M4014   K200����_�������ٰ����� ���� 70  �ǽð� �ڽ���200��������ü��ȣ������
    futureFrameIdMap.bind("V1014", 59);        // 12    KOSPI200�������� �������ٰ���   M4014   K200����_�������ٰ����� ���� 70  �ǽð� �ڽ���200��������ü��ȣ������
    futureFrameIdMap.bind("B2014", 299);        // 13  KOSPI200���������ü�Recovery ������  B2014   "�ֱ� ���� �ü��� ��������(����� �� ����)���� ����"    299
    futureFrameIdMap.bind("Q2014", 45);        // 14  K200����_�ǽð������Ѱ� ���������    Q2014   �ǽð������Ѱ� ���� �� ������ ���� 45
    futureFrameIdMap.bind("LK000", 13);        // 17  LINK    LK  LINK    13  1�а������͹̹߻�������
#endif
}
void HandleInternet::setFrameIdLength_KOSPI200_OPTION()
{
#if(0)
    // KOSPI200�����ɼ�_�ǽð�_���ͳ�(KRX)_20140901_2014073001.xls
    optionFrameIdMap.bind("A0034", 1202);            // 1   KOSPI200�����ɼ� �������� ������   A0034   ���� �ŷ������ �Ǵ� ���� ���� ���� �ڷ� ���� 1202
    optionFrameIdMap.bind("B6034", 224);            // 2   KOSPI200�����ɼ� �켱ȣ��   B6034   ������ �߻��ø��� �ǽð� ����    224
    optionFrameIdMap.bind("A3034", 105);            // 3   KOSPI200�����ɼ� ü�� A3034   ������ �߻��ø��� �ǽð� ����    105
    optionFrameIdMap.bind("G7034", 289);            // 4   KOSPI200�����ɼ� ü��_�켱ȣ��    G7034   ������ �߻��ø��� �ǽð� ����    289
    optionFrameIdMap.bind("A6034", 242);            // 5   KOSPI200�����ɼ� ���񸶰�   A6034   ���񸶰��ÿ� ���񺰷� ����  242
    optionFrameIdMap.bind("A7034", 249);            // 6   KOSPI200�����ɼ� ��TS  A7034   �� �̺�Ʈ �߻��� ����  249
    optionFrameIdMap.bind("H0034", 8);            // 7   KOSPI200�����ɼ� ���� H0034   ���� �ü�(B6,A3,G7,A6)������ ���� �˸�������  8
    optionFrameIdMap.bind("O6034", 35);            // 8   KOSPI200�����ɼ� �������   O6034   ���ϰ�ü��� ��/���Ѱ��� �����Ǵ� ��� ��/���Ѱ� �ż�,�ŵ��ֹ��� ���� �������� ������ ���������� ����Ͽ� ü���Ű�� ��� ���� 35
    optionFrameIdMap.bind("H1034", 94);            // 9   KOSPI200�����ɼ� ������ ������    H1034   "����Ȯ��ġ:�尳����, ����:30�ʰ���, ����Ȯ��ġ:�������� ����"   94
    optionFrameIdMap.bind("H2034", 42);            // 10  KOSPI200�����ɼ� �̰����������� ������    H2034   ������ �̰����������� ������ 42
    optionFrameIdMap.bind("H3034", 57);            // 11  KOSPI200�����ɼ� �Ÿ����űݱ��ذ� ������   H3034   ���ϸŸ����ű� ���ذ� 57
    optionFrameIdMap.bind("B2034", 286);            // 12  KOSPI200�����ɼǽü�Recovery ������  B2034   "�ֱ� ���� �ü��� ��������(����� �� ����)���� ����"    286
    optionFrameIdMap.bind("M7034", 52);            // 13  K200�ɼ�_�尳�������ǰŷ� M7034   Eurex���� �ڽ���200�ɼ� �尳���� ���ǰŷ�  52
    optionFrameIdMap.bind("M4034", 70);            // KOSPI200�����ɼ� �������ٰ��� KOSPI200�����ɼ� �������ٰ���   2015.06.15  2015.06.15  70  ������ �̺�Ʈ �߻��� ����
    optionFrameIdMap.bind("V1034", 58);            // 15    K200�ɼ�_����������Ȯ��ߵ�    V1034   K200�ɼ�_����������Ȯ�� �ߵ��� ����   58  ���Ǹ�����
    optionFrameIdMap.bind("P1034", 48);            // 15  KOSPI200�ɼ� ���纯����        P1034   KOSPI200�ɼ� ���纯����                48
    optionFrameIdMap.bind("N7034", 142);            // 16  KOSPI200�����ɼ� �ΰ���    N7034   �ɼ� ���� �ΰ��� ����   142
    optionFrameIdMap.bind("Q2034", 44);            // 17  K200�ɼ�_�ǽð������Ѱ� ���������    Q2034   �ǽð������Ѱ� ���� �� ������ ���� 44
    optionFrameIdMap.bind("LK000", 13);            // 20  LINK    LK  LINK    13  1�а������͹̹߻�������
#endif
}

void HandleInternet::setFrameIdLength_ELW_KRX()
{
#if(0)
    elwFrameIdMap.bind("A0011", 802);       // 1    �ڽ��������ġ A0011
    elwFrameIdMap.bind("A1011", 912);       // 2    ELW �����ġ    A1011
    elwFrameIdMap.bind("I6011", 52);       // 3    �ڽ��� ���� �̺�Ʈ ����   I6011
    elwFrameIdMap.bind("M6011", 542);       // 4    ��������ELW �����ġ    M6011
    elwFrameIdMap.bind("M5011", 92);       // 5    ��������ELW �򰡱Ⱓ �� �����ڻ������  M5011
    elwFrameIdMap.bind("C6021", 82);       // 6    ELW ������ǥ    C6021
    elwFrameIdMap.bind("O6021", 32);       // 7    ELW �������    O6021
    elwFrameIdMap.bind("C0021", 88);       // 8    ELW_�����ں�    C0021
    elwFrameIdMap.bind("M4011", 72);       // 9    �ڽ����������ٰ��� M4011
    elwFrameIdMap.bind("A8011", 122);       // 10   �ڽ����ֽ������������� A8011
    elwFrameIdMap.bind("A3021", 162);       // 11   ELW ü��  A3021
    elwFrameIdMap.bind("A6021", 90);       // 12   ELW ���񸶰�    A6021
    elwFrameIdMap.bind("A7021", 52);       // 13   ELW ��TS   A7021
    elwFrameIdMap.bind("B7021", 802);       // 14   ȣ���ܷ�_ELW    B7021
    elwFrameIdMap.bind("B1021", 292);       // 15   ELW ���� RECOVERY B1021
    elwFrameIdMap.bind("B2021", 292);       // 16   ELW �ü� RECOVERY B2021
    elwFrameIdMap.bind("B9021", 382);       // 17   ELW �ŷ��� B9021
    elwFrameIdMap.bind("I7011", 252);       // 18   �ڽ��� LP ����   I7011   LP ����   252
#endif
}
void HandleInternet::setFrameIdLength_ELW_KOSCOM()
{
#if(0)
    elwFrameIdMap.bind("F1011", 82);       // 1    �ڽ��� �ܱ��� �������� ���� Ȯ��ġ    F1011
    elwFrameIdMap.bind("F4011", 62);       // 2    �ڽ��� �ܱ��� Ȯ��ġ������������   F4011
    elwFrameIdMap.bind("C7021", 112);       // 3    ELW ������ǥ �ΰ���    C7021
    elwFrameIdMap.bind("N3021", 872);       // 4    ELW LPȣ�� ���纯����  N3021
#endif
}

void HandleInternet::setFrameIdLength_ELW_ETC()
{
#if(0)
    elwFrameIdMap.bind("LK000", 13);        // 21  LINK    LK  LINK    13  1�а������͹̹߻�������
#endif
}

int HandleInternet::handle_input(ACE_HANDLE fd)
{
//  ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::handle_input] BEGIN\n", getCurrentTimestamp().c_str() ));

    channelCount_++;
//    ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::handle_input] channelCount_:[%d]\n", getCurrentTimestamp().c_str(), channelCount_ ));

    ClientChannel *channel;

    ACE_NEW_RETURN(channel, ClientChannel(this, channelCount_, channelType_), -1);

    auto_ptr<ClientChannel> p(channel);

    ACE_Time_Value timeout(1);
    ACE_INET_Addr client_addr_;

    if (this->acceptor_.accept (channel->peer(), &client_addr_, &timeout) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                    ACE_TEXT ("(%P|%t) %p\n"),
                    ACE_TEXT ("Failed to accept ")
                    ACE_TEXT ("client connection")),
            -1);

    channel->peer().enable(ACE_NONBLOCK);
    //ACE_DEBUG((LM_DEBUG, "[%s] [HandleInternet::handle_input] channelCount_:[%d] accept [%s:%d] OK\n",
    //					getCurrentTimestamp().c_str(), channelCount_, client_addr_.get_host_addr() , client_addr_.get_port_number() ));
    p.release();
    channel->reactor(this->reactor());
    if ( channel->open() == -1 ) channel->handle_close(ACE_INVALID_HANDLE, 0);

    return 0;
}

int HandleInternet::handle_close(ACE_HANDLE, ACE_Reactor_Mask)
{
    ACE_DEBUG( ( LM_DEBUG , ACE_TEXT("ConnectionManager::handle_close ERROR\n") ));
    return this->acceptor_.close();
}

void HandleInternet::logRcvData(const char* buf, ssize_t len, time_t time, ACE_CString recvAddr)
{
    time_t curtime = ::time(0);
    struct tm* tmCurr = ::localtime(&curtime);

    if ( tmCurr->tm_hour != currentHour_ )
    {
        prepareLogFile();
        currentHour_ = tmCurr->tm_hour;
    }

    if ( dirRawLog_.length() != 0 )
    {
        struct tm* tmTemp = ::localtime(&time);
        struct tm tmRecv;
        if ( tmTemp != 0 )
        {
            tmRecv = *tmTemp;
        }

        std::ostringstream os;
//    os << "[" << std::setw(2) << std::setfill('0') << tmRecv.tm_hour
//      << std::setw(2) << std::setfill('0') << tmRecv.tm_min
//      << std::setw(2) << std::setfill('0') << tmRecv.tm_sec << "]";

        os << "[" << std::setw(2) << std::setfill('0') << tmRecv.tm_hour << std::setw(2) << std::setfill('0') << tmRecv.tm_min << std::setw(2) << std::setfill('0') << tmRecv.tm_sec << "]" << "[" << recvAddr.c_str() << "]";

        std::string loggingTime(os.str());
        rawLogFile_.send(loggingTime.c_str(), loggingTime.length());
        rawLogFile_.send(buf, len - 1); // skip last FF in case of UDP
        rawLogFile_.send("\n", 1);
    }
}

int HandleInternet::registerChannel(ClientChannel* channel)
{
    channels_.insert(channel);

    return 0;
}

int HandleInternet::unregisterChannel(ClientChannel* channel)
{
    channels_.remove(channel);

    return 0;
}

