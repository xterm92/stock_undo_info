// hannelPool.cpp: implementation of the ChannelPool class.
//
//////////////////////////////////////////////////////////////////////

#include "ChannelProcInfo.h"

#include "InvestorCodeConverter.h"
#include "DataProcessor.h"
#include "ace/Refcounted_Auto_Ptr.h"
#include "ace/CDR_Base.h"
#include "InternetKseChannelProcessor.h"
#include "InternetKosdaqChannelProcessor.h"
#include "InternetKospi200FutureChannelProcessor.h"
#include "InternetKospi200OptionChannelProcessor.h"
#include "InternetElwChannelProcessor.h"
#include "ChannelPool.h"
#include "TimerChannelProcessor.h"
#include "ESource.h"

#include <sstream>

ChannelPool::ChannelPool() // throw(ESource)
{
    try
    {
        if ( bind(ChannelProcInfo::ID_KOSPI, new InternetKseChannelProcessor("KSE")) != 0 ) throw ChannelProcInfo::ID_KOSPI;
        if ( bind(ChannelProcInfo::ID_KOSDAQ, new InternetKosdaqChannelProcessor("KOSDAQ")) != 0 ) throw ChannelProcInfo::ID_KOSDAQ;
        if ( bind(ChannelProcInfo::ID_FUTURE, new InternetKospi200FutureChannelProcessor("FUTURE")) != 0 ) throw ChannelProcInfo::ID_FUTURE;
        if ( bind(ChannelProcInfo::ID_OPTION, new InternetKospi200OptionChannelProcessor("OPTION")) != 0 ) throw ChannelProcInfo::ID_OPTION;
        if ( bind(ChannelProcInfo::ID_ELW, new InternetElwChannelProcessor("ELW")) != 0 ) throw ChannelProcInfo::ID_ELW;
        if ( bind(ChannelProcInfo::ID_TIMER, new TimerChannelProcessor("TIMER")) != 0 ) throw ChannelProcInfo::ID_TIMER;
    }
    catch ( ChannelProcInfo::IDType e )
    {
        std::ostringstream os;
        os << "cannot bind ChannelProcessor(" << e << ")";
        throw paxfeed::ESource(os.str(), __FILE__, __LINE__);
    }
    catch ( ... )
    {
        throw paxfeed::ESource("cannot bind ChannelProcessor", __FILE__, __LINE__);
    }
}

ChannelPool::~ChannelPool()
{
    const_iterator it(*this);
    while ( !it.done() )
    {
        delete ( *it ).int_id_;
    }
}

ChannelProcessor* ChannelPool::getChannelProcessor(ChannelProcInfo::IDType id)
{
    ChannelProcessor* pProc = 0;
    find(id, pProc);
    return pProc;
}
