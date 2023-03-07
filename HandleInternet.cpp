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
// 필요하면 추가해서 사용가능

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

//지수선물
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

//지수옵션
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
 현재 시간 문자열을 출력한다.
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
    //by hsy; 2016.02.23 mcast sender는 open으로 인스턴스 생성 (join은 mcast receiver에서 사용)
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
    kseFrameIdMap.bind("A0011", 802);      // 1    코스피종목배치 A0011   종목배치    802
    kseFrameIdMap.bind("A1041", 302);      // 2    ETN 종목배치    A1041   ETN 종목배치    302
    kseFrameIdMap.bind("I6011", 52);      // 3    코스피 종목 이벤트 정보   I6011   거래정지,관리종목지정등 종목이벤트정보 제공 52
    kseFrameIdMap.bind("I5011", 32);      // 4    코스피 결산일 정보  I5011   결산일 정보  32
    kseFrameIdMap.bind("A3011", 162);      // 5    코스피체결   A3011   코스피_체결  162
    kseFrameIdMap.bind("A4011", 62);      // 6    코스피기준가결정    A4011   코스피_기준가결정   62
    kseFrameIdMap.bind("A5011", 32);      // 7    코스피임의종료 A5011   코스피_임의종료    32
    kseFrameIdMap.bind("A6011", 92);      // 8    코스피종목마감 A6011   코스피_종목마감    92
    kseFrameIdMap.bind("A7011", 52);      // 9    코스피장운영TS    A7011   코스피_장운영TS   52
    kseFrameIdMap.bind("O6011", 42);      // 10   코스피 배분정보    O6011   코스피_배분정보    42
    kseFrameIdMap.bind("I7011", 252);      // 29    코스피 LP 정보   I7011   LP 정보   252
    kseFrameIdMap.bind("C4011", 112);      // 12   코스피대량체결 C4011   코스피_대량체결    112
    kseFrameIdMap.bind("A8011", 122);      // 13   코스피주식종목정보공개 A8011   코스피_공개정보 -> 코스피_주식종목정보공개    122
    kseFrameIdMap.bind("R3011", 52);      // 14   코스피 회원제제해제공개    R3011   코스피_회원제제해제공개    52
    kseFrameIdMap.bind("M4011", 72);      // 15   14    코스피장운영스케줄공개 M4011   코스피_공개장운영 -> 코스피_장운영스케줄공개   72  실시간 유가증권주식체결정보
    kseFrameIdMap.bind("B1011", 292);      // 16   코스피 종가 RECOVERY B1011   코스피_시세종가    292
    kseFrameIdMap.bind("B2011", 292);      // 17   코스피 시세 RECOVERY B2011   코스피_시세RECOVERY  292
    kseFrameIdMap.bind("B4011", 172);      // 18   코스피 시간외단일가 RECOVERY B4011   코스피_시간외단일가_시세   172
    kseFrameIdMap.bind("B3011", 172);      // 19   코스피 시간외단일가 최종   B3011   코스피_시간외단일가_최종   172
    kseFrameIdMap.bind("B5011", 62);      // 20   코스피 현재등락    B5011   상한,상승,보합,하한,하락종목수 정보 제공 62
    kseFrameIdMap.bind("B6011", 562);      // 21   코스피 호가잔량_LP호가_제외    B6011   코스피_호가잔량_LP호가_제외    562
    kseFrameIdMap.bind("B7011", 802);      // 22   코스피 호가잔량_LP호가_포함    B7011   코스피_호가잔량_LP호가_포함    802
    kseFrameIdMap.bind("B8011", 62);      // 23   코스피 장개시전 호가잔량   B8011   코스피_장개시전_호가잔량   62
    kseFrameIdMap.bind("C0011", 88);      // 24   코스피 업종별투자자별 C0011   업종별투자자별 88
    kseFrameIdMap.bind("C2011", 382);      // 25   코스피 프로그램매매일별차익거래잔고  C2011   프로그램매매 일별차익거래잔고 382
    kseFrameIdMap.bind("J1011", 132);      // 26   코스피 프로그램매매차익거래잔고 주석 J1011   프로그램매매 차익거래잔고주석 132
    kseFrameIdMap.bind("C3011", 462);      // 27   코스피 프로그램매매 호가   C3011   프로그램매매 호가   462
    kseFrameIdMap.bind("J0011", 442);      // 28   코스피 프로그램매매 전체집계 J0011   프로그램매매 전체집계 442
    kseFrameIdMap.bind("C5011", 102);      // 29   코스피 프로그램매매 사전공시 C5011   프로그램매매 사전공시 102
    kseFrameIdMap.bind("F0011", 1372);      // 30   코스피 공시실시간   F0011   공시REAL  1372
    kseFrameIdMap.bind("E9011", 1372);      // 31   코스피 공시배치    E9011   공시배치    1372
    kseFrameIdMap.bind("O4011", 62);      // 32   코스피 Buy-in실행수량  O4011   Buy-in실행수량  62
    kseFrameIdMap.bind("P2011", 18);      // 33   코스피 업종별 배당수익률   P2011   코스피 업종별 배당수익률   18
    kseFrameIdMap.bind("B9011", 382);      // 34   코스피 거래원 B9011   거래원 382
    kseFrameIdMap.bind("M9011", 212);      // 35   회원사 정보  M9011   회원사정보   212
    kseFrameIdMap.bind("C0031", 88);      // 36   ETF_투자자별    C0031   ETF 투자자별    88

    kseFrameIdMap.bind("C8011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  krx100(지수)(약칭:통합지수)
    kseFrameIdMap.bind("C9011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  krx100예상지수
    kseFrameIdMap.bind("D0011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스피지수
    kseFrameIdMap.bind("D1011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스피예상지수
    kseFrameIdMap.bind("D2011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스피200지수
    kseFrameIdMap.bind("D3011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스피200예상지수
    kseFrameIdMap.bind("D4011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스피100/50지수
    kseFrameIdMap.bind("D6011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스피배당지수(약칭:배당지수)
    kseFrameIdMap.bind("D7011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스피배당예상지수
    kseFrameIdMap.bind("D8011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  "코스피기업지배구조지수(약칭:기업지배구조지수)(2012.09.14)"
    kseFrameIdMap.bind("K2011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  레버리지kospi200지수
    kseFrameIdMap.bind("E0011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  섹터지수
    kseFrameIdMap.bind("E1011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  섹터예상지수
    kseFrameIdMap.bind("L0011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  "krx sri지수(2012.09.14)"
    kseFrameIdMap.bind("L1011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  krx sri예상지수(2012.09.14)
    kseFrameIdMap.bind("E4011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스닥지수
    kseFrameIdMap.bind("E5011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스닥예상지수
    kseFrameIdMap.bind("E6011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스닥스타지수(약칭:스타지수)
    kseFrameIdMap.bind("E7011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  코스닥스타예상지수
    kseFrameIdMap.bind("L2011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  kosdaq프리미어지수
    kseFrameIdMap.bind("L3011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  kosdaq프리미어예상지수
    kseFrameIdMap.bind("N1011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  krx 녹색산업지수
    kseFrameIdMap.bind("N2011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  krx 녹색산업예상지수
    kseFrameIdMap.bind("N5011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  kospi200 섹터지수
    kseFrameIdMap.bind("N6011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  kospi200 섹터예상지수
    kseFrameIdMap.bind("N9011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  동일가중지수
    kseFrameIdMap.bind("O1011", 52);      // 37   코스피 지수_예상지수 지수/예상지수 52  동일가중예상지수

    kseFrameIdMap.bind("F0012", 1372);      // 38   코스닥 공시리얼    F0012   공시REAL  1372
    kseFrameIdMap.bind("E9012", 1372);      // 39   코스닥 공시배치    E9012   공시배치    1372
    kseFrameIdMap.bind("F0018", 1372);      // 40   코넥스 공시리얼    F0018   공시REAL  1372
    kseFrameIdMap.bind("E9018", 1372);      // 41   코넥스 공시배치    E9018   공시배치    1372
    kseFrameIdMap.bind("P0011", 138);      // 42   코스피 프로그램매매 투자자별 매매현황    P0011   코스피 프로그램매매 투자자별 매매현황    138
    kseFrameIdMap.bind("O4012", 62);      // 43   코스닥 Buy-in실행수량  O4012   Buy-in실행수량  62
    kseFrameIdMap.bind("O4018", 62);      // 44   코넥스_Buy-in_실행수량 O4018   코넥스_Buy-in_실행수량 62
    kseFrameIdMap.bind("R8011", 102);      // 46    코스피_종목상태정보(VI)  R8011   코스피_종목상태정보(VI)  102 실시간
    kseFrameIdMap.bind("C0041", 88);      // 47   ETN_투자자별    C0041   ETN 투자자별    88
    kseFrameIdMap.bind("T7011", 52);      // 48   KTOP30지수  T7011   "한국 경제 및 증시를 대표하는 소수의 초우량 종목으로 구성된 대표지수"   52  2초주기
    kseFrameIdMap.bind("T8011", 52);      // 49   KTOP30예상지수    T8011   "한국 경제 및 증시를 대표하는 소수의 초우량 종목으로 구성된 대표지수"   52  2초주기

    kseFrameIdMap.bind("V6011", 201);      // 51 ETP지수정보 V6011   ETP지수정보 201 일일 05:30, 06:10, 06:50 총3회 전송(단, A0011[KOSPI종목정보]전송 완료 후 전송
#endif
}
void HandleInternet::setFrameIdLength_KSE_KOSCOM()
{
#if(0)
    kseFrameIdMap.bind("F1011", 82);              // 1    코스피 외국인 종목별투자 정보 확정치    F1011   외국인 종목별투자정보(확정치)    82
    kseFrameIdMap.bind("F1012", 82);              // 1    코스피 외국인 종목별투자 정보 확정치    F1011   외국인 종목별투자정보(확정치)    82
    kseFrameIdMap.bind("F4011", 62);              // 2    코스피 외국인 확정치데이터재전송   F4011   외국인종목별투자정보 오류시 오류보정을 위해전송   62
    kseFrameIdMap.bind("F4012", 62);              // 2    코스피 외국인 확정치데이터재전송   F4011   외국인종목별투자정보 오류시 오류보정을 위해전송   62
    kseFrameIdMap.bind("N8011", 252);              // 3    ETF사무수탁배치   N8011   ETF 종목배치    252
    kseFrameIdMap.bind("F7011", 72);              // 4    ETF NAV F7011   ETF NAV 72
    kseFrameIdMap.bind("I3011", 52);              // 5    ETF 예상NAV   I3011   ETF 예상NAV   52
    kseFrameIdMap.bind("F8011", 162);              // 6    ETF PDF F8011   ETF PDF 162
    kseFrameIdMap.bind("M8011", 132);              // 7    ETF운영사정보    M8011   ETF운영사정보    132
    kseFrameIdMap.bind("P6011", 62);              // 8    ETF 추적오차율   P6011   ETF 추적오차율   62
    kseFrameIdMap.bind("Q4011", 202);              // 9    합성ETF 일일 거래상대방 위험평가액 정보 Q4011   합성ETF 일일 거래상대방 위험평가액 정보 202
    kseFrameIdMap.bind("Q5011", 202);              // 10   합성ETF 기초지수 구성종목 Q5011   합성ETF 기초지수 구성종목 202
    kseFrameIdMap.bind("S1011", 132);              // 11   ETN 사무수탁정보  S1011   ETN 사무수탁정보  132
    kseFrameIdMap.bind("S2011", 202);              // 12   ETN 기초지수 구성종목   S2011   ETN 기초지수 구성종목   202
    kseFrameIdMap.bind("S3011", 72);              // 13   ETN IIV S3011   ETN 실시간지표가치(IIV)    72
#endif
}

void HandleInternet::setFrameIdLength_KSE_ETC()
{
#if(0)
    kseFrameIdMap.bind("LK000", 13);              // 49   LINK    LK  LINK    13  1분간데이터미발생시전송
    kseFrameIdMap.bind("DT000", 108);              // 종목별 투자자별 종가(FTP)
    kseFrameIdMap.bind("ZZ011", 162);              // 내부시세리커버리(체결포맷차용)
#endif
}

void HandleInternet::setFrameIdLength_KOSDAQ_KRX()
{
#if(0)
    kosdaqFrameIdMap.bind("A0012", 802);       // 1    코스닥종목배치 A0012   종목배치    802
    kosdaqFrameIdMap.bind("I5012", 32);       // 2    코스닥 결산일 정보  I5012   결산일 정보  32
    kosdaqFrameIdMap.bind("I6012", 52);       // 3    코스닥 종목 이벤트 정보   I6012   거래정지,관리종목지정등 종목이벤트정보 제공 52
    kosdaqFrameIdMap.bind("I7012", 252);       // 4 코스닥 LP 정보   I7012   LP 정보   252
    kosdaqFrameIdMap.bind("A3012", 162);       // 5    코스닥체결   A3012   코스닥_체결  162
    kosdaqFrameIdMap.bind("A4012", 62);       // 6    코스닥기준가결정    A4012   코스닥_기준가결정   62
    kosdaqFrameIdMap.bind("A5012", 32);       // 7    코스닥임의종료 A5012   코스닥_임의종료    32
    kosdaqFrameIdMap.bind("A6012", 92);       // 8    코스닥종목마감 A6012   코스닥_종목마감    92
    kosdaqFrameIdMap.bind("A7012", 52);       // 9    코스닥장운영TS    A7012   코스닥_장운영TS   52
    kosdaqFrameIdMap.bind("O6012", 42);       // 10   코스닥 배분정보    O6012   코스닥_배분정보    42
    kosdaqFrameIdMap.bind("C4012", 112);       // 11   코스닥대량체결 C4012   KOSDAQ_대량체결 112
    kosdaqFrameIdMap.bind("A8012", 122);       // 12   코스닥주식종목정보공개 A8012   코스닥_공개정보 -> 코스닥_주식종목정보공개    122
    kosdaqFrameIdMap.bind("R3012", 52);       // 13   코스닥회원제재해제공개 R3012   코스닥_회원제재해제공개    52
    kosdaqFrameIdMap.bind("M4012", 72);       // 13 코스닥장운영스케줄공개 M4012   코스닥_공개장운영 -> 코스닥_장운영스케줄 공개  72  실시간 코스닥주식체결정보
    kosdaqFrameIdMap.bind("B1012", 292);       // 15   코스닥 종가 RECOVERY B1012   코스닥_시세종가    292
    kosdaqFrameIdMap.bind("B2012", 292);       // 16   코스닥 시세 RECOVERY B2012   코스닥_시세RECOVERY  292
    kosdaqFrameIdMap.bind("B3012", 172);       // 17   코스닥 시간외단일가 최종   B3012   코스닥_시간외단일가_최종   172
    kosdaqFrameIdMap.bind("B4012", 172);       // 18   코스닥 시간외단일가 RECOVERY B4012   코스닥_시간외단일가_시세   172
    kosdaqFrameIdMap.bind("B5012", 62);       // 19   코스닥 현재등락    B5012   현재등락    62
    kosdaqFrameIdMap.bind("B6012", 562);       // 20   코스닥 호가잔량_LP호가_제외    B6012   코스닥_호가잔량_LP호가_제외    562
    kosdaqFrameIdMap.bind("B7012", 792);       // 21   코스닥 호가잔량_LP호가_포함    B7012   호가잔량_LP호가_포함 (ETF)  792
    kosdaqFrameIdMap.bind("B8012", 62);       // 22   코스닥 장개시전 호가잔량   B8012   코스닥_장개시전_호가잔량   62
    kosdaqFrameIdMap.bind("C0012", 88);       // 23   코스닥 업종별투자자별 C0012   업종별투자자별 88
    kosdaqFrameIdMap.bind("C2012", 382);       // 24   코스닥 프로그램매매일별차익거래잔고  C2012   프로그램매매 일별차익거래잔고 382
    kosdaqFrameIdMap.bind("J1012", 132);       // 25   코스닥 프로그램매매차익거래잔고주석  J1012   프로그램매매 차익거래잔고주석 132
    kosdaqFrameIdMap.bind("C3012", 462);       // 26   코스닥 프로그램매매 호가   C3012   프로그램매매 호가   462
    kosdaqFrameIdMap.bind("J0012", 442);       // 27   코스닥 프로그램매매 전체집계 J0012   프로그램매매 전체집계 442
    kosdaqFrameIdMap.bind("C5012", 102);       // 28   코스닥 프로그램매매 사전공시 C5012   프로그램매매 사전사후공시   102
    kosdaqFrameIdMap.bind("P0012", 138);       // 29   코스닥 프로그램매매 투자자별 매매현황    P0012   코스닥 프로그램매매 투자자별 매매현황    138
    kosdaqFrameIdMap.bind("P2012", 18);       // 30   코스닥 업종별 배당수익률   P2012   코스닥 업종별 배당수익률   18
    kosdaqFrameIdMap.bind("B9012", 382);       // 31   코스닥 거래원 B9012   거래원 382

    kosdaqFrameIdMap.bind("C8012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  krx100(지수)(약칭:통합지수)
    kosdaqFrameIdMap.bind("C9012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  krx100예상지수
    kosdaqFrameIdMap.bind("D0012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스피지수
    kosdaqFrameIdMap.bind("D1012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스피예상지수
    kosdaqFrameIdMap.bind("D2012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스피200지수
    kosdaqFrameIdMap.bind("D3012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스피200예상지수
    kosdaqFrameIdMap.bind("D4012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스피100/50지수
    kosdaqFrameIdMap.bind("D6012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스피배당지수(약칭:배당지수)
    kosdaqFrameIdMap.bind("D7012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스피배당예상지수
    kosdaqFrameIdMap.bind("D8012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  "코스피기업지배구조지수(약칭:기업지배구조지수)(2012.09.14)"
    kosdaqFrameIdMap.bind("K2012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  레버리지kospi200지수
    kosdaqFrameIdMap.bind("E0012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  섹터지수
    kosdaqFrameIdMap.bind("E1012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  섹터예상지수
    kosdaqFrameIdMap.bind("L0012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  krx sri지수(2012.09.14)
    kosdaqFrameIdMap.bind("L1012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  krx sri예상지수(2012.09.14)
    kosdaqFrameIdMap.bind("E4012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스닥지수
    kosdaqFrameIdMap.bind("E5012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스닥예상지수
    kosdaqFrameIdMap.bind("E6012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스닥스타지수(약칭:스타지수)
    kosdaqFrameIdMap.bind("E7012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  코스닥스타예상지수
    kosdaqFrameIdMap.bind("L2012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  kosdaq프리미어지수
    kosdaqFrameIdMap.bind("L3012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  kosdaq프리미어예상지수
    kosdaqFrameIdMap.bind("N1012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  krx 녹색산업지수
    kosdaqFrameIdMap.bind("N2012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  krx 녹색산업예상지수
    kosdaqFrameIdMap.bind("N5012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  kospi200 섹터지수
    kosdaqFrameIdMap.bind("N6012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  kospi200 섹터예상지수
    kosdaqFrameIdMap.bind("N9012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  동일가중지수
    kosdaqFrameIdMap.bind("O1012", 52);       // 32   코스닥 지수_예상지수 지수/예상지수 52  동일가중예상지수
    kosdaqFrameIdMap.bind("R8012", 102);       // 32    코스닥_종목상태정보(VI)  R8012   코스닥_종목상태정보(VI)  102 실시간
#endif
}
void HandleInternet::setFrameIdLength_KOSDAQ_KOSCOM()
{
#if(0)
    // 코스닥주식_실시간_인터넷(KOSCOM)_20130809_2013082601.xls
    kosdaqFrameIdMap.bind("F1011", 82);           // 1    코스닥 외국인 종목별투자 정보 확정치    F1012   외국인 종목별투자정보(확정치)    82
    kosdaqFrameIdMap.bind("F1012", 82);           // 1    코스닥 외국인 종목별투자 정보 확정치    F1012   외국인 종목별투자정보(확정치)    82
    kosdaqFrameIdMap.bind("F4011", 62);           // 2    코스닥 외국인 확정치데이터재전송   F4012   외국인종목별투자정보 오류시 오류보정을 위해전송   62
    kosdaqFrameIdMap.bind("F4012", 62);           // 2    코스닥 외국인 확정치데이터재전송   F4012   외국인종목별투자정보 오류시 오류보정을 위해전송   62
#endif
}

void HandleInternet::setFrameIdLength_KOSDAQ_ETC()
{
#if(0)
    kosdaqFrameIdMap.bind("LK000", 13);              // 47  LINK    LK  LINK    13  1분간데이터미발생시전송
    kosdaqFrameIdMap.bind("DT000", 108);              // 종목별 투자자별 종가(FTP)
    kosdaqFrameIdMap.bind("ZZ012", 162);              // 내부시세리커버리(체결포맷차용)
#endif
}

void HandleInternet::setFrameIdLength_KOSPI200_FUTURE()
{
#if(0)
    // KOSPI200지수선물_실시간_인터넷(KRX)_20140901_2014073001.xls
    futureFrameIdMap.bind("A0014", 1202);        // 1   KOSPI200지수선물 종목정보 데이터   A0014   일일 거래대상이 되는 종목에 대한 기초 자료 제공 1202
    futureFrameIdMap.bind("B6014", 222);        // 2   KOSPI200지수선물 우선호가   B6014   데이터 발생시마다 실시간 제공    222
    futureFrameIdMap.bind("A3014", 119);        // 3   KOSPI200지수선물 체결 A3014   데이터 발생시마다 실시간 제공    119
    futureFrameIdMap.bind("G7014", 301);        // 4   KOSPI200지수선물 체결_우선호가    G7014   데이터 발생시마다 실시간 제공    301
    futureFrameIdMap.bind("A6014", 239);        // 5   KOSPI200지수선물 종목마감   A6014   종목마감시에 종목별로 제공  239
    futureFrameIdMap.bind("A7014", 248);        // 6   KOSPI200지수선물_장운영TS  A7014   장운영 이벤트 발생시 제공  248
    futureFrameIdMap.bind("H0014", 8);        // 7   KOSPI200지수선물 마감 H0014   당일 시세(B6,A3,G7,A6)전송의 끝을 알리는전문  8
    futureFrameIdMap.bind("O6014", 34);        // 8   KOSPI200지수선물 배분정보   O6014   단일가체결시 상/하한가로 결정되는 경우 상/하한가 매수, 매도주문에 대해 일정량의 수량을 순차적으로 배분하여 체결시키는 경우 제공    34
    futureFrameIdMap.bind("H1014", 147);        // 9   KOSPI200지수선물 투자자 데이터    H1014   "전일확정치:장개시전, 장중:30초간격, 당일확정치:장종료후 제공"   147
    futureFrameIdMap.bind("H2014", 41);        // 10  KOSPI200지수선물 미결제약정수량 데이터    H2014   종목의 미결제약정수량 변동시 41
    futureFrameIdMap.bind("H3014", 56);        // 11  KOSPI200지수선물 정산가격 데이터   H3014   당일정산가   56
    futureFrameIdMap.bind("M4014", 70);        // 12    KOSPI200지수선물 장운영스케줄공개   M4014   K200선물_장운영스케줄공개시 제공 70  실시간 코스피200지수선물체결호가정보
    futureFrameIdMap.bind("V1014", 59);        // 12    KOSPI200지수선물 장운영스케줄공개   M4014   K200선물_장운영스케줄공개시 제공 70  실시간 코스피200지수선물체결호가정보
    futureFrameIdMap.bind("B2014", 299);        // 13  KOSPI200지수선물시세Recovery 데이터  B2014   "최근 종목별 시세를 일정간격(변경될 수 있음)으로 제공"    299
    futureFrameIdMap.bind("Q2014", 45);        // 14  K200선물_실시간상하한가 적용및해제    Q2014   실시간상하한가 적용 및 해제시 제공 45
    futureFrameIdMap.bind("LK000", 13);        // 17  LINK    LK  LINK    13  1분간데이터미발생시전송
#endif
}
void HandleInternet::setFrameIdLength_KOSPI200_OPTION()
{
#if(0)
    // KOSPI200지수옵션_실시간_인터넷(KRX)_20140901_2014073001.xls
    optionFrameIdMap.bind("A0034", 1202);            // 1   KOSPI200지수옵션 종목정보 데이터   A0034   일일 거래대상이 되는 종목에 대한 기초 자료 제공 1202
    optionFrameIdMap.bind("B6034", 224);            // 2   KOSPI200지수옵션 우선호가   B6034   데이터 발생시마다 실시간 제공    224
    optionFrameIdMap.bind("A3034", 105);            // 3   KOSPI200지수옵션 체결 A3034   데이터 발생시마다 실시간 제공    105
    optionFrameIdMap.bind("G7034", 289);            // 4   KOSPI200지수옵션 체결_우선호가    G7034   데이터 발생시마다 실시간 제공    289
    optionFrameIdMap.bind("A6034", 242);            // 5   KOSPI200지수옵션 종목마감   A6034   종목마감시에 종목별로 제공  242
    optionFrameIdMap.bind("A7034", 249);            // 6   KOSPI200지수옵션 장운영TS  A7034   장운영 이벤트 발생시 제공  249
    optionFrameIdMap.bind("H0034", 8);            // 7   KOSPI200지수옵션 마감 H0034   당일 시세(B6,A3,G7,A6)전송의 끝을 알리는전문  8
    optionFrameIdMap.bind("O6034", 35);            // 8   KOSPI200지수옵션 배분정보   O6034   단일가체결시 상/하한가로 결정되는 경우 상/하한가 매수,매도주문에 대해 일정량의 수량을 순차적으로 배분하여 체결시키는 경우 제공 35
    optionFrameIdMap.bind("H1034", 94);            // 9   KOSPI200지수옵션 투자자 데이터    H1034   "전일확정치:장개시전, 장중:30초간격, 당일확정치:장종료후 제공"   94
    optionFrameIdMap.bind("H2034", 42);            // 10  KOSPI200지수옵션 미결제약정수량 데이터    H2034   종목의 미결제약정수량 변동시 42
    optionFrameIdMap.bind("H3034", 57);            // 11  KOSPI200지수옵션 매매증거금기준가 데이터   H3034   당일매매증거금 기준가 57
    optionFrameIdMap.bind("B2034", 286);            // 12  KOSPI200지수옵션시세Recovery 데이터  B2034   "최근 종목별 시세를 일정간격(변경될 수 있음)으로 제공"    286
    optionFrameIdMap.bind("M7034", 52);            // 13  K200옵션_장개시전협의거래 M7034   Eurex연계 코스피200옵션 장개시전 협의거래  52
    optionFrameIdMap.bind("M4034", 70);            // KOSPI200지수옵션 장운영스케줄공개 KOSPI200지수옵션 장운영스케줄공개   2015.06.15  2015.06.15  70  공개장운영 이벤트 발생시 제공
    optionFrameIdMap.bind("V1034", 58);            // 15    K200옵션_가격제한폭확대발동    V1034   K200옵션_가격제한폭확대 발동시 제공   58  조건만족시
    optionFrameIdMap.bind("P1034", 48);            // 15  KOSPI200옵션 내재변동성        P1034   KOSPI200옵션 내재변동성                48
    optionFrameIdMap.bind("N7034", 142);            // 16  KOSPI200지수옵션 민감도    N7034   옵션 종목별 민감도 제공   142
    optionFrameIdMap.bind("Q2034", 44);            // 17  K200옵션_실시간상하한가 적용및해제    Q2034   실시간상하한가 적용 및 해제시 제공 44
    optionFrameIdMap.bind("LK000", 13);            // 20  LINK    LK  LINK    13  1분간데이터미발생시전송
#endif
}

void HandleInternet::setFrameIdLength_ELW_KRX()
{
#if(0)
    elwFrameIdMap.bind("A0011", 802);       // 1    코스피종목배치 A0011
    elwFrameIdMap.bind("A1011", 912);       // 2    ELW 종목배치    A1011
    elwFrameIdMap.bind("I6011", 52);       // 3    코스피 종목 이벤트 정보   I6011
    elwFrameIdMap.bind("M6011", 542);       // 4    조기종료ELW 종목배치    M6011
    elwFrameIdMap.bind("M5011", 92);       // 5    조기종료ELW 평가기간 중 기초자산고저가  M5011
    elwFrameIdMap.bind("C6021", 82);       // 6    ELW 투자지표    C6021
    elwFrameIdMap.bind("O6021", 32);       // 7    ELW 배분정보    O6021
    elwFrameIdMap.bind("C0021", 88);       // 8    ELW_투자자별    C0021
    elwFrameIdMap.bind("M4011", 72);       // 9    코스피장운영스케줄공개 M4011
    elwFrameIdMap.bind("A8011", 122);       // 10   코스피주식종목정보공개 A8011
    elwFrameIdMap.bind("A3021", 162);       // 11   ELW 체결  A3021
    elwFrameIdMap.bind("A6021", 90);       // 12   ELW 종목마감    A6021
    elwFrameIdMap.bind("A7021", 52);       // 13   ELW 장운영TS   A7021
    elwFrameIdMap.bind("B7021", 802);       // 14   호가잔량_ELW    B7021
    elwFrameIdMap.bind("B1021", 292);       // 15   ELW 종가 RECOVERY B1021
    elwFrameIdMap.bind("B2021", 292);       // 16   ELW 시세 RECOVERY B2021
    elwFrameIdMap.bind("B9021", 382);       // 17   ELW 거래원 B9021
    elwFrameIdMap.bind("I7011", 252);       // 18   코스피 LP 정보   I7011   LP 정보   252
#endif
}
void HandleInternet::setFrameIdLength_ELW_KOSCOM()
{
#if(0)
    elwFrameIdMap.bind("F1011", 82);       // 1    코스피 외국인 종목별투자 정보 확정치    F1011
    elwFrameIdMap.bind("F4011", 62);       // 2    코스피 외국인 확정치데이터재전송   F4011
    elwFrameIdMap.bind("C7021", 112);       // 3    ELW 투자지표 민감도    C7021
    elwFrameIdMap.bind("N3021", 872);       // 4    ELW LP호가 내재변동성  N3021
#endif
}

void HandleInternet::setFrameIdLength_ELW_ETC()
{
#if(0)
    elwFrameIdMap.bind("LK000", 13);        // 21  LINK    LK  LINK    13  1분간데이터미발생시전송
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

