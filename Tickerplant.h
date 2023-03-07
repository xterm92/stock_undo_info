#ifndef __TICKERPLANT_H__
#define __TICKERPLANT_H__

//Tickerplant 에서 사용되는 공통 정의
#include "ace/SStringfwd.h"
#include "PaxfeedDefine.h"
#include "PaxfeedPacket.h"
#include "PaxfeedPacketELW.h"
#include "PaxfeedPacketDefine.h"
#include "PaxfeedMasterDefine.h"
#include "PaxfeedMasterELWDefine.h"
#include "PaxfeedAceHelper.h"

const int TICKERPLANT_KSE_MAX_SYMBOL_COUNT = 1500;
const int TICKERPLANT_KOSDAQ_MAX_SYMBOL_COUNT = 1500;
const int TICKERPLANT_ECN_MAX_SYMBOL_COUNT = 3000;
const int TICKERPLANT_KSE_FUTURE_MAX_SYMBOL_COUNT = 20;
const int TICKERPLANT_KSE_OPTION_MAX_SYMBOL_COUNT = 150;
const int TICKERPLANT_BASECODE_KOSPI = 0;
const int TICKERPLANT_BASECODE_KOSPI200 = 200;
const int TICKERPLANT_BASECODE_KOSPI100 = 100;
const int TICKERPLANT_BASECODE_KOSPI50 = 50;
const int TICKERPLANT_BASECODE_KOSPIIT = 300;
const int TICKERPLANT_BASECODE_KODI = 310;
const int TICKERPLANT_BASECODE_KOGI = 320;
const int TICKERPLANT_BASECODE_KOSDAQ = 500;
const int TICKERPLANT_BASECODE_KOSDAQ50 = 750;
const int TICKERPLANT_BASECODE_KOSDAQIT50 = 800;
const int TICKERPLANT_BASECODE_KOSTAR = 810;


const int TICKERPLANT_BASECODE_KTOP30 = 460;

const int COMPRESS_EXPIRE_TIME = 10; // 10에서 5로 수정

typedef HashMap<ACE_CString, paxfeed::Trade> TradeMap;
typedef HashMap<ACE_CString, paxfeed::ELWTrade> ELWTradeMap;
typedef HashMap<ACE_CString, double> AccmSizeMap;

#include <typeinfo>
template<typename T>
class ForLog
{
    public:
        ForLog(T& t, const ACE_CString& msg, unsigned tid)
                : t_(t), msg_(msg), tid_(tid)
        {
            ACE_DEBUG( ( LM_ERROR , "ForLog constructor - %s, %s, %u\n" , typeid(t_).name() , msg_.c_str() , tid_ ));
        }
        ~ForLog()
        {
            ACE_DEBUG( ( LM_ERROR , "ForLog destructor - %s, %s, %u\n" , typeid(t_).name() , msg_.c_str() , tid_ ));
        }

    private:
        T& t_;
        ACE_CString msg_;
        unsigned tid_;
};

#endif
