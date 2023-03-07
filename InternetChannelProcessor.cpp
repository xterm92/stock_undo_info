// InternetChannelProcessor.cpp: implementation of the InternetChannelProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "ace/SStringfwd.h"
#include "ace/String_Base.h"

#include "PaxfeedDefine.h"
#include "PaxfeedPacket.h"
#include "PaxfeedPacketELW.h"
#include "PaxfeedStatus.h"

#include "ace/Log_Msg.h"
#include "MMapAllocator.h"

#include "InternetChannelProcessor.h"
#include "DataDispatcher.h"

#include "Xmitter.h"
#include <exception>

//#include "ExturePlusInternetKse.h"
//#include "ExturePlusInternetKosdaq.h"
//#include "ExturePlusInternetElw.h"

using namespace std;
using namespace paxfeed;

InternetChannelProcessor::InternetChannelProcessor()
{
}

InternetChannelProcessor::InternetChannelProcessor(const ACE_CString &channelName)
        : ChannelProcessor(channelName), 
		accmVolumeMap_(allocHashMap<AccmSizeMap>( ( ACE_CString("TP_ACCMVOL_MAP_") + channelName ).c_str(), *ALLOCATOR::instance())), 
		accmAmountMap_(allocHashMap<AccmSizeMap>( ( ACE_CString("TP_ACCMAMT_MAP_") + channelName ).c_str(), *ALLOCATOR::instance())), 
		totalAccmVolumeMap_(allocHashMap<AccmSizeMap>( ( ACE_CString("TP_TOTAL_ACCMVOL_MAP_") + channelName ).c_str(), *ALLOCATOR::instance())), totalAccmAmountMap_(allocHashMap<AccmSizeMap>( ( ACE_CString("TP_TOTAL_ACCMAMT_MAP_") + channelName ).c_str(), *ALLOCATOR::instance())), tradeMap_(allocHashMap<TradeMap>( ( ACE_CString("TP_TRADEMAP_") + channelName ).c_str(), *ALLOCATOR::instance())), elwTradeMap_(allocHashMap<ELWTradeMap>( ( ACE_CString("TP_ELW_TRADEMAP_") + channelName ).c_str(), *ALLOCATOR::instance())), 
		programTradeMapKse_(allocHashMap<ProgramTradeMapPublicKse>( ( ACE_CString("TP_PROGRAM_TRADE_MAP_KSE_") + channelName ).c_str(), *ALLOCATOR::instance())), 
		programTradeMapKosdaq_(allocHashMap<ProgramTradeMapPublicKosdaq>( ( ACE_CString("TP_PROGRAM_TRADE_MAP_KOSDAQ_") + channelName ).c_str(), *ALLOCATOR::instance())), 
		masterMapKse_(allocHashMap<ExturePlusMasterMapKse>( ( ACE_CString("TP_PROGRAM_MASTER_MAP_KSE_") + channelName ).c_str(), *ALLOCATOR::instance())), 
		masterMapKosdaq_(allocHashMap<ExturePlusMasterMapKosdaq>( ( ACE_CString("TP_PROGRAM_MASTER_MAP_KOSDAQ_") + channelName ).c_str(), *ALLOCATOR::instance())), 
		tradeFixedMapKse_(allocHashMap<ExturePlusKseRecoveryTradeFixedMap>( ( ACE_CString("TP_TRADE_FIXED_RECOVERY_MAP_KSE_") + channelName ).c_str(), *ALLOCATOR::instance())), tradeFixedMapKosdaq_(allocHashMap<ExturePlusKosdaqRecoveryTradeFixedMap>( ( ACE_CString("TP_TRADE_FIXED_RECOVERY_MAP_KOSDAQ_") + channelName ).c_str(), *ALLOCATOR::instance()))
{
}

InternetChannelProcessor::~InternetChannelProcessor()
{
}

int InternetChannelProcessor::reset()
{
    ACE_DEBUG( ( LM_INFO , "%s::reset\n" , typeid(*this).name() ));
    ChannelProcessor::reset();
    accmVolumeMap_->unbind_all();
    accmAmountMap_->unbind_all();
    totalAccmVolumeMap_->unbind_all();
    totalAccmAmountMap_->unbind_all();
    tradeMap_->unbind_all();
    elwTradeMap_->unbind_all();
    programTradeMapKse_->unbind_all();
    programTradeMapKosdaq_->unbind_all();
    tradeFixedMapKse_->unbind_all();

#if(1)
	masterMapKse_->unbind_all();
	masterMapKosdaq_->unbind_all();
#endif
    return 0;
}

void InternetChannelProcessor::updateAccmVolume(const ACE_CString &symbol)
{
    double accmVolume = 0.0;
    const std::vector<ACE_CString> &tradeTypeList = getTradeTypeList();

    for ( vector<ACE_CString>::const_iterator it = tradeTypeList.begin() ; it != tradeTypeList.end() ; ++it )
    {
        accmVolume += getAccmVolume(symbol, *it);
    }
    setTotalAccmVolume(symbol, std::max(accmVolume, getTotalAccmVolume(symbol)));
}

void InternetChannelProcessor::updateAccmAmount(const ACE_CString &symbol)
{
    double accmAmount = 0.0;
    const std::vector<ACE_CString> &tradeTypeList = getTradeTypeList();

    for ( vector<ACE_CString>::const_iterator it = tradeTypeList.begin() ; it != tradeTypeList.end() ; ++it )
    {
        accmAmount += getAccmAmount(symbol, *it);
    }
    setTotalAccmAmount(symbol, std::max(accmAmount, getTotalAccmAmount(symbol)));
}

void InternetChannelProcessor::setAccmAmount(const ACE_CString& symbol, double amount, const ACE_CString &tradePriceType)
{
    ACE_CString key(symbol + tradePriceType);
    double previousAmount = getAccmAmount(symbol, tradePriceType);

    double result = 0;
    int hasValue = accmAmountMap_->find(key, result, ALLOCATOR::instance());

    if ( hasValue != -1 )
    {
        if ( previousAmount < amount )
        {
            ACE_CString oldKey;
            double oldVal;
            accmAmountMap_->rebind(ACE_CString(key.c_str(), ALLOCATOR::instance()), amount, oldKey, oldVal, ALLOCATOR::instance());
        }
    }
    else
    {
        accmAmountMap_->bind(ACE_CString(key.c_str(), ALLOCATOR::instance()), amount, ALLOCATOR::instance());
    }
    updateAccmAmount(symbol);

    // double accmAmount = getAccmAmount(symbol,tradePriceType) ;
    // ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::setAccmAmount] symbol:[%s]\ttradePriceType:[%s]\taccmAmount:[%f]\n", getCurrentTimestamp().c_str(), symbol.c_str(), tradePriceType.c_str(), accmAmount));

}

void InternetChannelProcessor::setTotalAccmAmount(const ACE_CString& symbol, double amount)
{
    ACE_CString key(symbol);
    double previousAmount = getTotalAccmAmount(symbol);

    double result = 0;
    int hasValue = totalAccmAmountMap_->find(key, result, ALLOCATOR::instance());

    if ( hasValue != -1 )
    {
        if ( previousAmount < amount )
        {
            ACE_CString oldKey;
            double oldVal;
            totalAccmAmountMap_->rebind(ACE_CString(key.c_str(), ALLOCATOR::instance()), amount, oldKey, oldVal, ALLOCATOR::instance());
        }
    }
    else
    {
        totalAccmAmountMap_->bind(ACE_CString(key.c_str(), ALLOCATOR::instance()), amount, ALLOCATOR::instance());
    }

    // double totalAccmAmount = getTotalAccmAmount(symbol);
    // ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::setTotalAccmAmount] symbol:[%s]\ttotalAccmAmount:[%f]\n", getCurrentTimestamp().c_str(), symbol.c_str(), totalAccmAmount));
}

void InternetChannelProcessor::setAccmVolume(const ACE_CString &symbol, double volume, const ACE_CString &tradePriceType)
{
    ACE_CString key = symbol + tradePriceType;
    double previousVolume = getAccmVolume(symbol, tradePriceType);

    double result = 0;
    int hasValue = accmVolumeMap_->find(key, result, ALLOCATOR::instance());

    if ( hasValue != -1 )
    {
        if ( previousVolume < volume )
        {
            ACE_CString oldKey;
            double oldVal;
            accmVolumeMap_->rebind(ACE_CString(key.c_str(), ALLOCATOR::instance()), volume, oldKey, oldVal, ALLOCATOR::instance());
        }
    }
    else
    {
        accmVolumeMap_->bind(ACE_CString(key.c_str(), ALLOCATOR::instance()), volume, ALLOCATOR::instance());
    }
    updateAccmVolume(symbol);

    // double accmVolume = getAccmVolume(symbol,tradePriceType) ;
    // ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::setAccmVolume] symbol:[%s]\ttradePriceType:[%s]\taccmVolume:[%f]\n", getCurrentTimestamp().c_str(), symbol.c_str(), tradePriceType.c_str(), accmVolume));
}

void InternetChannelProcessor::setTotalAccmVolume(const ACE_CString &symbol, double volume)
{
    ACE_CString key = symbol;
    double previousVolume = getTotalAccmVolume(symbol);

    double result = 0;
    int hasValue = totalAccmVolumeMap_->find(key, result, ALLOCATOR::instance());

    if ( hasValue != -1 )
    {
        if ( previousVolume < volume )
        {
            ACE_CString oldKey;
            double oldVal;
            totalAccmVolumeMap_->rebind(ACE_CString(key.c_str(), ALLOCATOR::instance()), volume, oldKey, oldVal, ALLOCATOR::instance());
        }
    }
    else
    {
        totalAccmVolumeMap_->bind(ACE_CString(key.c_str(), ALLOCATOR::instance()), volume, ALLOCATOR::instance());
    }

    // double totalAccmVolume = getTotalAccmVolume(symbol);
    // ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::setTotalAccmVolume] symbol:[%s]\ttotalAccmVolume:[%f]\n", getCurrentTimestamp().c_str(), symbol.c_str(), totalAccmVolume));
}

double InternetChannelProcessor::getAccmVolume(const ACE_CString &symbol, const ACE_CString &tradePriceType)
{
    ACE_CString key = symbol + tradePriceType;
    double result = 0;
    int hasValue = accmVolumeMap_->find(key, result, ALLOCATOR::instance());
    if ( hasValue == -1 )
    {
        result = 0;
    }

    return result;
}

double InternetChannelProcessor::getTotalAccmVolume(const ACE_CString &symbol)
{
    ACE_CString key = symbol;
    double result = 0;
    int hasValue = totalAccmVolumeMap_->find(key, result, ALLOCATOR::instance());
    if ( hasValue == -1 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetChannelProcessor::getTotalAccmVolume] symbol:[%s] hasValue:[%d]\n" , getCurrentTimestamp().c_str() , symbol.c_str() , hasValue ), 0);
    }
    return result;
}

double InternetChannelProcessor::getAccmAmount(const ACE_CString &symbol, const ACE_CString &tradePriceType)
{
    ACE_CString key = symbol + tradePriceType;
    double amount = 0;
    int hasValue = accmAmountMap_->find(key, amount, ALLOCATOR::instance());
    if ( hasValue == -1 )
    {
        return 0;
    }
    return amount;
}

double InternetChannelProcessor::getTotalAccmAmount(const ACE_CString &symbol)
{
    ACE_CString key = symbol;
    double amount = 0;
    int hasValue = totalAccmAmountMap_->find(key, amount, ALLOCATOR::instance());
    if ( hasValue == -1 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetChannelProcessor::getTotalAccmAmount] symbol:[%s] hasValue:[%d]\n" , getCurrentTimestamp().c_str() , symbol.c_str() , hasValue ), 0);
    }
    return amount;
}

void InternetChannelProcessor::printPacketTrade(const Trade trade)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketTrade] subtype:[%d]\texchange:[%d]\tsymbolType:[%d]\tdecimalPoint:[%d]\tsymbol[12]:[%s]\ttradeTime:[%d]\tmarket:[%d]\tupDown:[%d]\topen:[%d]\thigh:[%d]\tlow:[%d]\tclose:[%d]\tydayClose:[%d]\ttradeVolume:[%f]\taccmVolume:[%f]\tamount:[%f]\topenInterest:[%d]\topenMin:[%d]\thighMin:[%d]\tlowMin:[%d]\tvolumeMin:[%f]\n" , getCurrentTimestamp().c_str() , trade.subtype , trade.exchange , trade.symbolType , trade.decimalPoint , ACE_CString(trade.symbol, sizeof ( trade.symbol )).c_str() , trade.tradeTime , trade.market , trade.upDown , trade.open , trade.high , trade.low , trade.close , trade.ydayClose , trade.tradeVolume , trade.accmVolume , trade.amount , trade.openInterest , trade.openMin , trade.highMin , trade.lowMin , trade.volumeMin ));
}

void InternetChannelProcessor::printPacketQuote10(const Quote10 quote)
{

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketQuote10] exchange:[%d]\tsymbolType:[%d]\tdecimalPoint:[%d]\tsymbol:[%s]\tmarket:[%d]\tconcurrent:[%d]\tquoteTime:[%d]\ttotalAskVolume:[%f]\ttotalBidVolume:[%f]\texpectedPrice:[%d]\texpectedVolume:[%f]\n" , getCurrentTimestamp().c_str() , quote.exchange , quote.symbolType , quote.decimalPoint , ACE_CString(quote.symbol, sizeof ( quote.symbol )).c_str() , quote.market , quote.concurrent , quote.quoteTime , quote.totalAskVolume , quote.totalBidVolume , quote.expectedPrice , quote.expectedVolume ));

    for ( int i = 0 ; i < 10 ; ++i )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketQuote10] QuoteRecord.rec[%d]\task:[%d]\taskVolume:[%f]\tbid:[%d]\tbidVolume:[%f]\n" , getCurrentTimestamp().c_str() , i , quote.rec[i].ask , quote.rec[i].askVolume , quote.rec[i].bid , quote.rec[i].bidVolume ));
    }
}

void InternetChannelProcessor::printPacketUpDown(const UpDown updown)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketUpDown] exchange:[%d]\tsymbolType:[%d]\tsymbol:[%s]\tregisterDt:[%d]\tmarket:[%d]\ttotalCount:[%d]\ttradeCount:[%d]\tupCount:[%d]\tupLimitCount:[%d]\tdownCount:[%d]\tdownLimitCount:[%d]\tstationaryCount:[%d]\tquotationCount:[%d]\tquotationUpCount:[%d]\tquotationDownCount:[%d]\taccmVolume:[%f]\taccmAmount:[%f]\n" , getCurrentTimestamp().c_str() , updown.exchange , updown.symbolType , ACE_CString(updown.symbol, sizeof ( updown.symbol )).c_str() , updown.registerDt , updown.market , updown.totalCount , updown.tradeCount , updown.upCount , updown.upLimitCount , updown.downCount , updown.downLimitCount , updown.stationaryCount , updown.quotationCount , updown.quotationUpCount , updown.quotationDownCount , updown.accmVolume , updown.accmAmount ));

}

void InternetChannelProcessor::printPacketForeignerMaster(const ForeignerMaster master)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketForeignerMaster] exchange:[%d]\tsymbolType:[%d]\tsymbol:[%s]\tserial:[%d]\tsymbolLimitRate:[%d]\tindividualLimitRate:[%d]\tlimitVolume:[%f]\texhaust:[%d]\torderLimitSign:[%d]\torderLimitVolume:[%f]\tlistSize:[%f]\n" , getCurrentTimestamp().c_str() , master.exchange , master.symbolType , ACE_CString(master.symbol, sizeof ( master.symbol )).c_str() , master.serial , master.symbolLimitRate , master.individualLimitRate , master.limitVolume , master.exhaust , master.orderLimitSign , master.orderLimitVolume , master.listSize ));

}

void InternetChannelProcessor::printPacketForeigner(const Foreigner foreigner)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketForeignerMaster] subtype:[%d]\tdecimalPoint:[%d]\tsymbol:[%s]\torderLimitSign:[%d]\torderLimitVolume:[%f]\n" , getCurrentTimestamp().c_str() , foreigner.subtype , foreigner.decimalPoint , ACE_CString(foreigner.symbol, sizeof ( foreigner.symbol )).c_str() , foreigner.orderLimitSign , foreigner.orderLimitVolume ));
}

void InternetChannelProcessor::printPacketQuoteVolume(const QuoteVolume quote)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketQuoteVolume] exchange:[%d]\tsymbolType:[%d]\tsymbol:[%s]\tmarket:[%d]\tquoteTime:[%d]\ttotalAskVolume:[%f]\ttotalBidVolume:[%f]\n" , getCurrentTimestamp().c_str() , quote.exchange , quote.symbolType , ACE_CString(quote.symbol, sizeof ( quote.symbol )).c_str() , quote.market , quote.quoteTime , quote.totalAskVolume , quote.totalBidVolume ));
}

void InternetChannelProcessor::printPacketSecuritiesTrade2(const SecuritiesTrade2 sec)
{

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketSecuritiesTrade2] subtype:[%d]\texchange:[%d]\tsymbolType:[%d]\tsymbol:[%s]\n" , getCurrentTimestamp().c_str() , sec.subtype , sec.exchange , sec.symbolType , ACE_CString(sec.symbol, sizeof ( sec.symbol )).c_str() ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketSecuritiesTrade2] SecuritiesTradeRecord.rec1\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec1.seller, sizeof ( sec.rec1.seller )).c_str() , ACE_CString(sec.rec1.buyer, sizeof ( sec.rec1.buyer )).c_str() , sec.rec1.askVolume , sec.rec1.bidVolume , sec.rec1.askAmount , sec.rec1.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketSecuritiesTrade2] SecuritiesTradeRecord.rec2\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec2.seller, sizeof ( sec.rec2.seller )).c_str() , ACE_CString(sec.rec2.buyer, sizeof ( sec.rec2.buyer )).c_str() , sec.rec2.askVolume , sec.rec2.bidVolume , sec.rec2.askAmount , sec.rec2.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketSecuritiesTrade2] SecuritiesTradeRecord.rec3\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec3.seller, sizeof ( sec.rec3.seller )).c_str() , ACE_CString(sec.rec3.buyer, sizeof ( sec.rec3.buyer )).c_str() , sec.rec3.askVolume , sec.rec3.bidVolume , sec.rec3.askAmount , sec.rec3.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketSecuritiesTrade2] SecuritiesTradeRecord.rec4\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec4.seller, sizeof ( sec.rec4.seller )).c_str() , ACE_CString(sec.rec4.buyer, sizeof ( sec.rec4.buyer )).c_str() , sec.rec4.askVolume , sec.rec4.bidVolume , sec.rec4.askAmount , sec.rec4.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketSecuritiesTrade2] SecuritiesTradeRecord.rec5\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec5.seller, sizeof ( sec.rec5.seller )).c_str() , ACE_CString(sec.rec5.buyer, sizeof ( sec.rec5.buyer )).c_str() , sec.rec5.askVolume , sec.rec5.bidVolume , sec.rec5.askAmount , sec.rec5.bidAmount ));
}

void InternetChannelProcessor::printPacketInvestor(const Investor investor)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketInvestor] subtype:[%d]\texchange:[%d]\tsymbolType:[%d]\tsymbol:[%s]\tinvestor:[%s]\taskVolume:[%f]\taskAmount:[%f]\tbidVolume:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , investor.subtype , investor.exchange , investor.symbolType , ACE_CString(investor.symbol, sizeof ( investor.symbol )).c_str() , ACE_CString(investor.investor, sizeof ( investor.investor )).c_str() , investor.askVolume , investor.askAmount , investor.bidVolume , investor.bidAmount ));
}

void InternetChannelProcessor::printPacketProgramTrade(const ProgramTrade trade)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] subtype:[%f]\n" , getCurrentTimestamp().c_str() , trade.subtype ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] exchange:[%f]\n" , getCurrentTimestamp().c_str() , trade.exchange ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] symbolType:[%f]\n" , getCurrentTimestamp().c_str() , trade.symbolType ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(trade.symbol, sizeof ( trade.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] mpSellQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , trade.mpSellQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] mpBuyQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , trade.mpBuyQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] nmpSellQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , trade.nmpSellQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] nmpBuyQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , trade.nmpBuyQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] mpSellQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.mpSellQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] mpBuyQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.mpBuyQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] nmpSellQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.nmpSellQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] nmpBuyQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.nmpBuyQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] sellCommitTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.sellCommitTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] sellSelfTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.sellSelfTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] buyCommitTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.buyCommitTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] buySelfTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.buySelfTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] sellCommitTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , trade.sellCommitTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] sellSelfTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , trade.sellSelfTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] buyCommitTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , trade.buyCommitTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] buySelfTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , trade.buySelfTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] paSellVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.paSellVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTrade] paBuyVolume:[%f]\n" , getCurrentTimestamp().c_str() , trade.paBuyVolume ));
}

void InternetChannelProcessor::printPacketProgramTradeTotal(const ProgramTradeTotal tradeTotal)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] subtype:[%d]\n" , getCurrentTimestamp().c_str() , tradeTotal.subtype ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] exchange:[%d]\n" , getCurrentTimestamp().c_str() , tradeTotal.exchange ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpSellQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpSellQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpBuyQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpBuyQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpSellQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpSellQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpBuyQuoteRemainder:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpBuyQuoteRemainder ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpSellQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpSellQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpBuyQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpBuyQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpSellQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpSellQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpBuyQuoteVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpBuyQuoteVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpSellCommitTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpSellCommitTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpSellSelfTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpSellSelfTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpBuyCommitTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpBuyCommitTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpBuySelfTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpBuySelfTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpSellCommitTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpSellCommitTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpSellSelfTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpSellSelfTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpBuyCommitTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpBuyCommitTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpBuySelfTradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpBuySelfTradeVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpSellCommitTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpSellCommitTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpSellSelfTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpSellSelfTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpBuyCommitTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpBuyCommitTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] mpBuySelfTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.mpBuySelfTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpSellCommitTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpSellCommitTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpSellSelfTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpSellSelfTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpBuyCommitTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpBuyCommitTradeAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeTotal] nmpBuySelfTradeAmount:[%f]\n" , getCurrentTimestamp().c_str() , tradeTotal.nmpBuySelfTradeAmount ));
}

void InternetChannelProcessor::printPacketProgramTradeBatch(const ProgramTradeBatch batch)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] subtype:[%d]\n" , getCurrentTimestamp().c_str() , batch.subtype ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] exchange:[%d]\n" , getCurrentTimestamp().c_str() , batch.exchange ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] serial:[%d]\n" , getCurrentTimestamp().c_str() , batch.serial ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] registerTime:[%d]\n" , getCurrentTimestamp().c_str() , batch.registerTime ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] securities:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.securities, sizeof ( batch.securities )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] stockType:[%d]\n" , getCurrentTimestamp().c_str() , batch.stockType ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] commitType:[%d]\n" , getCurrentTimestamp().c_str() , batch.commitType ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] stockVolume:[%f]\n" , getCurrentTimestamp().c_str() , batch.stockVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] stockAmounte:[%f]\n" , getCurrentTimestamp().c_str() , batch.stockAmounte ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] futureVolume:[%f]\n" , getCurrentTimestamp().c_str() , batch.futureVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] futuAmount:[%f]\n" , getCurrentTimestamp().c_str() , batch.futuAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] nearSymbolType:[%d]\n" , getCurrentTimestamp().c_str() , batch.nearSymbolType ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] callOptionVolume:[%f]\n" , getCurrentTimestamp().c_str() , batch.callOptionVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] callOptionAmount:[%f]\n" , getCurrentTimestamp().c_str() , batch.callOptionAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] putOptionVolume:[%f]\n" , getCurrentTimestamp().c_str() , batch.putOptionVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketProgramTradeBatch] putOptionAmount:[%f]\n" , getCurrentTimestamp().c_str() , batch.putOptionAmount ));
}

void InternetChannelProcessor::printPacketShortSellingInfo(const ShortSellingInfo info)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(info.symbol, sizeof ( info.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] registerTime:[%d]\n" , getCurrentTimestamp().c_str() , info.registerTime ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] shortSellingDebtSecuritiesAskTradingVolume:[%f]\n" , getCurrentTimestamp().c_str() , info.shortSellingDebtSecuritiesAskTradingVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] shortSellingDebtSecuritiesAskTradingAmount:[%f]\n" , getCurrentTimestamp().c_str() , info.shortSellingDebtSecuritiesAskTradingAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] upTickRuleAppliedCoveredShortSellingTradingVolume:[%f]\n" , getCurrentTimestamp().c_str() , info.upTickRuleAppliedCoveredShortSellingTradingVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] upTickRuleAppliedCoveredShortSellingTradingAmount:[%f]\n" , getCurrentTimestamp().c_str() , info.upTickRuleAppliedCoveredShortSellingTradingAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] upTickRuleUnappliedCoveredShortSellingTradingVolume:[%f]\n" , getCurrentTimestamp().c_str() , info.upTickRuleUnappliedCoveredShortSellingTradingVolume ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketShortSellingInfo] upTickRuleUnappliedCoveredShortSellingTradingAmount:[%f]\n" , getCurrentTimestamp().c_str() , info.upTickRuleUnappliedCoveredShortSellingTradingAmount ));
}

void InternetChannelProcessor::printPacketMarketOperation(const MarketOperation market)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketMarketOperation] symbol:[%s]\trecvTime:[%d]\tboardId:[%s]\tboardEventId:[%s]\tbeginTime:[%s]\ttradingHaltReason:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(market.symbol, sizeof ( market.symbol )).c_str() , market.recvTime , ACE_CString(market.boardId, sizeof ( market.boardId )).c_str() , ACE_CString(market.boardEventId, sizeof ( market.boardEventId )).c_str() , ACE_CString(market.beginTime, sizeof ( market.beginTime )).c_str() , ACE_CString(market.tradingHaltReason, sizeof ( market.tradingHaltReason )).c_str() ));
}

void InternetChannelProcessor::printPacketBlockTrade(const BlockTrade blockRec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketBlockTrade] symbol:[%s]\trecvTime:[%d]\ttradeVolumePreMarket:[%f]\ttradeVolumeRegularMarket:[%f]\ttradeVolumePostMarket:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(blockRec.symbol, sizeof ( blockRec.symbol )).c_str() , blockRec.recvTime , blockRec.tradeVolumePreMarket , blockRec.tradeVolumeRegularMarket , blockRec.tradeVolumePostMarket ));
}

void InternetChannelProcessor::printPacketRealTimeLimitPrice(const RealTimeLimitPrice limitRec)
{

//    ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::printPacketRealTimeLimitPrice] symbol:[%s]\n"          , getCurrentTimestamp().c_str() , ACE_CString(limitRec.symbol, sizeof(limitRec.symbol)).c_str() ));
//    ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::printPacketRealTimeLimitPrice] registerDt:[%d]\n"         , getCurrentTimestamp().c_str() , limitRec.registerDt ));
//    ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::printPacketRealTimeLimitPrice] realTimeUpperLimitPrice:[%f]\n"        , getCurrentTimestamp().c_str() , limitRec.realTimeUpperLimitPrice ));
//    ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::printPacketRealTimeLimitPrice] realTimeLowerLimitPrice:[%f]\n"       , getCurrentTimestamp().c_str() , limitRec.realTimeLowerLimitPrice  ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketRealTimeLimitPrice] symbol:[%s]\tregisterDt:[%d]\tregisterDt:[%c]\trealTimeUpperLimitPrice:[%f]\trealTimeLowerLimitPrice:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(limitRec.symbol, sizeof ( limitRec.symbol )).c_str() , limitRec.registerDt , limitRec.isRealTimePriceLimit , limitRec.realTimeUpperLimitPrice , limitRec.realTimeLowerLimitPrice ));

}

void InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument(const VolatilityInterruptionPerInstrument viRec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(viRec.symbol, sizeof ( viRec.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , viRec.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] boardID:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(viRec.boardID, sizeof ( viRec.boardID )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] tradeExecutionProcessingTime:[%d]\n" , getCurrentTimestamp().c_str() , viRec.tradeExecutionProcessingTime ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] removalTimeOfVI:[%d]\n" , getCurrentTimestamp().c_str() , viRec.removalTimeOfVI ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] VIApplicationCategoryCode:[%c]\n" , getCurrentTimestamp().c_str() , viRec.VIApplicationCategoryCode ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] basePriceToTriggerVI:[%d]\n" , getCurrentTimestamp().c_str() , viRec.basePriceToTriggerVI ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] VITriggeringPrice:[%d]\n" , getCurrentTimestamp().c_str() , viRec.VITriggeringPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument] disparateRatio:[%f]\n" , getCurrentTimestamp().c_str() , viRec.disparateRatio ));
}

void InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2(const VolatilityInterruptionPerInstrument2 viRec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(viRec.symbol, sizeof ( viRec.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , viRec.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] boardID:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(viRec.boardID, sizeof ( viRec.boardID )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] tradeExecutionProcessingTime:[%d]\n" , getCurrentTimestamp().c_str() , viRec.tradeExecutionProcessingTime ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] removalTimeOfVI:[%d]\n" , getCurrentTimestamp().c_str() , viRec.removalTimeOfVI ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] VIApplicationCategoryCode:[%c]\n" , getCurrentTimestamp().c_str() , viRec.VIApplicationCategoryCode ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] VITypeCode:[%d]\n" , getCurrentTimestamp().c_str() , viRec.VITypeCode ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] basePriceToTriggerStaticVI:[%d]\n" , getCurrentTimestamp().c_str() , viRec.basePriceToTriggerStaticVI ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] basePriceToTriggerDynamicVI:[%d]\n" , getCurrentTimestamp().c_str() , viRec.basePriceToTriggerDynamicVI ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] VITriggeringPrice:[%d]\n" , getCurrentTimestamp().c_str() , viRec.VITriggeringPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] disparateRatioStaticVI:[%f]\n" , getCurrentTimestamp().c_str() , viRec.disparateRatioStaticVI ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketVolatilityInterruptionPerInstrument2] disparateRatioDynamicVI:[%f]\n" , getCurrentTimestamp().c_str() , viRec.disparateRatioDynamicVI ));

}

void InternetChannelProcessor::printPacketETNTransferAgentBatchData(const ETNTransferAgentBatchData batchData)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batchData.symbol, sizeof ( batchData.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , batchData.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] finalIndexValue:[%f]\n" , getCurrentTimestamp().c_str() , batchData.finalIndexValue ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] indexValueInSumOfMoney:[%f]\n" , getCurrentTimestamp().c_str() , batchData.indexValueInSumOfMoney ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] previousDayTaxableBasicPrice:[%f]\n" , getCurrentTimestamp().c_str() , batchData.previousDayTaxableBasicPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] previousDayTaxableBasicPriceBeforeDividend:[%f]\n" , getCurrentTimestamp().c_str() , batchData.previousDayTaxableBasicPriceBeforeDividend ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] previousDayCashDividendPrice:[%f]\n" , getCurrentTimestamp().c_str() , batchData.previousDayCashDividendPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] aDayBeforePreviousDayTaxableBasicPrice:[%f]\n" , getCurrentTimestamp().c_str() , batchData.aDayBeforePreviousDayTaxableBasicPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] volatilityFuturesType:[%d]\n" , getCurrentTimestamp().c_str() , batchData.volatilityFuturesType ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] minimumQuantityOfCall:[%d]\n" , getCurrentTimestamp().c_str() , batchData.minimumQuantityOfCall ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] interestRateOfCall:[%f]\n" , getCurrentTimestamp().c_str() , batchData.interestRateOfCall ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNTransferAgentBatchData] expenses:[%f]\n" , getCurrentTimestamp().c_str() , batchData.expenses ));
}

void InternetChannelProcessor::printPacketETNIndexCompositionConstituents(const ETNIndexCompositionConstituents constituent)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(constituent.symbol, sizeof ( constituent.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , constituent.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] date:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(constituent.date, sizeof ( constituent.date )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] officeConsignmentCompanyRegistrationNumber:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(constituent.officeConsignmentCompanyRegistrationNumber, sizeof ( constituent.officeConsignmentCompanyRegistrationNumber )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] numberOfCompositionConstituents:[%d]\n" , getCurrentTimestamp().c_str() , constituent.numberOfCompositionConstituents ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] compositionConstituentsCode:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(constituent.compositionConstituentsCode, sizeof ( constituent.compositionConstituentsCode )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] nameOfCompositionConstituents:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(constituent.nameOfCompositionConstituents, sizeof ( constituent.nameOfCompositionConstituents )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNIndexCompositionConstituents] compositionRate:[%f]\n" , getCurrentTimestamp().c_str() , constituent.compositionRate ));
}

void InternetChannelProcessor::printPacketETN_IIV(const ETN_IIV iiv)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETN_IIV] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(iiv.symbol, sizeof ( iiv.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETN_IIV] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , iiv.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETN_IIV] previousDayIV:[%f]\n" , getCurrentTimestamp().c_str() , iiv.previousDayIV ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETN_IIV] duringMarketHoursFinalIV:[%f]\n" , getCurrentTimestamp().c_str() , iiv.duringMarketHoursFinalIV ));
}

void InternetChannelProcessor::printPacketETNInformationBatch(const ETNInformationBatch batch)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.symbol, sizeof ( batch.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , batch.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnIssueMarketParticipantKoreanName:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnIssueMarketParticipantKoreanName, sizeof ( batch.etnIssueMarketParticipantKoreanName )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnIssueMarketParticipantEnglishName:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnIssueMarketParticipantEnglishName, sizeof ( batch.etnIssueMarketParticipantEnglishName )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnIssueMarketParticipantNo:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnIssueMarketParticipantNo, sizeof ( batch.etnIssueMarketParticipantNo )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnFinalSettlementMethodCode:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnFinalSettlementMethodCode, sizeof ( batch.etnFinalSettlementMethodCode )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnLastTradingDate:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnLastTradingDate, sizeof ( batch.etnLastTradingDate )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnPaymentDate:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnPaymentDate, sizeof ( batch.etnPaymentDate )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnLPHoldingQuantity:[%f]\n" , getCurrentTimestamp().c_str() , batch.etnLPHoldingQuantity ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] lossProtectionEtnProfitStructureCode:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.lossProtectionEtnProfitStructureCode, sizeof ( batch.lossProtectionEtnProfitStructureCode )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnMaximumRedemptionPrice:[%f]\n" , getCurrentTimestamp().c_str() , batch.etnMaximumRedemptionPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnMinimumRedemptionPrice:[%f]\n" , getCurrentTimestamp().c_str() , batch.etnMinimumRedemptionPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnEarlyRedemptionPossibility:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnEarlyRedemptionPossibility, sizeof ( batch.etnEarlyRedemptionPossibility )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] etnEarlyRedemptionPeriodCode:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.etnEarlyRedemptionPeriodCode, sizeof ( batch.etnEarlyRedemptionPeriodCode )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] appraisedPriceCalculationInstitutionCode1:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.appraisedPriceCalculationInstitutionCode1, sizeof ( batch.appraisedPriceCalculationInstitutionCode1 )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketETNInformationBatch] appraisedPriceCalculationInstitutionCode2:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(batch.appraisedPriceCalculationInstitutionCode2, sizeof ( batch.appraisedPriceCalculationInstitutionCode2 )).c_str() ));
}

void InternetChannelProcessor::printPacketKOSPI200IndexFutureSettledPriceData(const KOSPI200IndexFutureSettledPriceData priceData)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI200IndexFutureSettledPriceData] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(priceData.symbol, sizeof ( priceData.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI200IndexFutureSettledPriceData] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , priceData.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI200IndexFutureSettledPriceData] settlementPrice:[%f]\n" , getCurrentTimestamp().c_str() , priceData.settlementPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI200IndexFutureSettledPriceData] settlementPriceType:[%d]\n" , getCurrentTimestamp().c_str() , priceData.settlementPriceType ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI200IndexFutureSettledPriceData] lastSettlementPrice:[%f]\n" , getCurrentTimestamp().c_str() , priceData.lastSettlementPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI200IndexFutureSettledPriceData] lastSettlementPriceType:[%d]\n" , getCurrentTimestamp().c_str() , priceData.lastSettlementPriceType ));
}

void InternetChannelProcessor::printPacketKOSPI_KOSDAQ_IssueEventInformation(const KOSPI_KOSDAQ_IssueEventInformation infoRec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI_KOSDAQ_IssueEventInformation] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.symbol, sizeof ( infoRec.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI_KOSDAQ_IssueEventInformation] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , infoRec.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI_KOSDAQ_IssueEventInformation] eventTypeCode:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.eventTypeCode, sizeof ( infoRec.eventTypeCode )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI_KOSDAQ_IssueEventInformation] eventOccurrenceCauseCode:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.eventOccurrenceCauseCode, sizeof ( infoRec.eventOccurrenceCauseCode )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI_KOSDAQ_IssueEventInformation] startDate:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.startDate, sizeof ( infoRec.startDate )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketKOSPI_KOSDAQ_IssueEventInformation] expirationDate:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.expirationDate, sizeof ( infoRec.expirationDate )).c_str() ));
}

int InternetChannelProcessor::getMarketBasedCurrentTime()
{
    ACE_CString marketBegin(DataDispatcher::instance().marketBegin_);
    ACE_CString marketEnd(DataDispatcher::instance().marketEnd_);

    if ( marketBegin.length() != 6 )
    {
        marketBegin = "090000";
    }
    if ( marketEnd.length() != 6 )
    {
        marketEnd = "153000";
    }

    ACE_CString marketBeginHour = marketBegin.substr(0, 2);
    ACE_CString marketEndHour = marketEnd.substr(0, 2);
    ACE_CString marketBeginMin = marketBegin.substr(2, 2);
    ACE_CString marketEndMin = marketEnd.substr(2, 2);
    ACE_CString marketBeginSec = marketBegin.substr(4, 2);
    ACE_CString marketEndSec = marketEnd.substr(4, 2);

#if(0)
    int beginHour = ::atoi(marketBeginHour.c_str());
    int endHour = ::atoi(marketEndHour.c_str());
    int beginMin = ::atoi(marketBeginMin.c_str());
    int endMin = ::atoi(marketEndMin.c_str());
    int beginSec = ::atoi(marketBeginSec.c_str());
    int endSec = ::atoi(marketBeginSec.c_str());
#endif

    struct tm stTm;
    ::memset(&stTm, 0, sizeof(struct tm));
    time_t currentTime = time(NULL);
    ::localtime_r(&currentTime, &stTm);

    int market = MARKET_IN;

#if	0
    if ( ( stTm.tm_hour >= 0 ) && ( stTm.tm_hour < beginHour ) )
    {
        market = MARKET_BEFORE_TRADE;
    }
    else if ( ( stTm.tm_hour >= beginHour ) && ( stTm.tm_hour < endHour ) )
    {
        market = MARKET_IN;
    }
    else if ( ( stTm.tm_hour >= endHour ) && ( stTm.tm_hour < 24 ) )
    {
        market = MARKET_AFTER_TRADE;
    }
    else
    {
        market = MARKET_IN;
    }

#else /* by hsy; 2016.08.02 장운영 시간대변경*/

    if ( stTm.tm_hour * 100 + stTm.tm_min < 900 )
    {
        market = MARKET_BEFORE_TRADE;
    }
    else if ( ( stTm.tm_hour * 100 + stTm.tm_min >= 900 ) && ( stTm.tm_hour * 100 + stTm.tm_min < 1530 ) )
    {
        market = MARKET_IN;
    }
    else if ( ( stTm.tm_hour * 100 + stTm.tm_min >= 1530 ) && ( stTm.tm_hour < 24 ) )
    {
        market = MARKET_AFTER_TRADE;
    }
    else
    {
        market = MARKET_IN;
    }

#endif

//    ACE_DEBUG((LM_DEBUG, "[%s] [InternetChannelProcessor::getMarketBasedCurrentTime] marketBegin:[%s]\tmarketEnd[%s]\tmarket:[%d]\n"
//            , getCurrentTimestamp().c_str()
//            , marketBegin.c_str()
//            , marketEnd.c_str()
//            , market));

    return market;

}

void InternetChannelProcessor::printPacketELWQuote10LPIncluded(const ELWQuote10LPIncluded elwQuote)
{

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWQuote10LPIncluded] exchange:[%d]\tsymbolType:[%d]\tdecimalPoint:[%d]\tsymbol:[%s]\tmarket:[%d]\tconcurrent:[%d]\tquoteTime:[%d]\ttotalAskVolume:[%f]\ttotalBidVolume:[%f]\texpectedPrice:[%d]\texpectedVolume:[%f]\tboardID:[%s]\tsessionID:[%s]\n" , getCurrentTimestamp().c_str() , elwQuote.exchange , elwQuote.symbolType , elwQuote.decimalPoint , ACE_CString(elwQuote.symbol, sizeof ( elwQuote.symbol )).c_str() , elwQuote.market , elwQuote.concurrent , elwQuote.quoteTime , elwQuote.totalAskVolume , elwQuote.totalBidVolume , elwQuote.expectedPrice , elwQuote.expectedVolume , ACE_CString(elwQuote.boardID, sizeof ( elwQuote.boardID )).c_str() , ACE_CString(elwQuote.sessionID, sizeof ( elwQuote.sessionID )).c_str() ));

    for ( int i = 0 ; i < 10 ; ++i )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWQuote10LPIncluded] ELWQuoteLPIncluded.rec[%d]\task:[%d]\taskVolume:[%f]\taskVolumeLP:[%f]\tbid:[%d]\tbidVolume:[%f]\tbidVolumeLP:[%f]\n" , getCurrentTimestamp().c_str() , i , elwQuote.rec[i].ask , elwQuote.rec[i].askVolume , elwQuote.rec[i].askVolumeLP , elwQuote.rec[i].bid , elwQuote.rec[i].bidVolume , elwQuote.rec[i].bidVolumeLP ));
    }
}

void InternetChannelProcessor::printPacketELWTrade(const ELWTrade elwTrade)
{
    ACE_DEBUG(
            ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWTrade] subtype:[%d]\texchange:[%d]\tsymbolType:[%d]\tdecimalPoint:[%d]\tsymbol[12]:[%s]\ttradeTime:[%d]\tmarket:[%d]\tupDown:[%d]\topen:[%d]\thigh:[%d]\tlow:[%d]\tclose:[%d]\tydayClose:[%d]\ttradeVolume:[%f]\taccmVolume:[%f]\tamount:[%f]\topenInterest:[%d]\topenMin:[%d]\thighMin:[%d]\tlowMin:[%d]\tvolumeMin:[%f]\tboardID:[%s]\tsessionID:[%s]\tlpHoldingVolume:[%f]\tisFialTypeAskOrBidFromLast:[%c]\tisEqualCloseAndQuotePrice1:[%c]\n" , getCurrentTimestamp().c_str() , elwTrade.subtype , elwTrade.exchange , elwTrade.symbolType , elwTrade.decimalPoint , ACE_CString(elwTrade.symbol, sizeof ( elwTrade.symbol )).c_str() , elwTrade.tradeTime , elwTrade.market , elwTrade.upDown , elwTrade.open , elwTrade.high , elwTrade.low , elwTrade.close , elwTrade.ydayClose , elwTrade.tradeVolume , elwTrade.accmVolume , elwTrade.amount , elwTrade.openInterest , elwTrade.openMin , elwTrade.highMin , elwTrade.lowMin , elwTrade.volumeMin , ACE_CString(
                    elwTrade.boardID, sizeof ( elwTrade.boardID )).c_str() , ACE_CString(elwTrade.sessionID, sizeof ( elwTrade.sessionID )).c_str() , elwTrade.lpHoldingVolume , elwTrade.isFialTypeAskOrBidFromLast , elwTrade.isEqualCloseAndQuotePrice1 ));
}

void InternetChannelProcessor::printPacketELWEarlyClosedELWBatch(const ELWEarlyClosedELWBatch elwBatch)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWEarlyClosedELWBatch] exchange:[%d]\n" , getCurrentTimestamp().c_str() , elwBatch.exchange ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWEarlyClosedELWBatch] symbolType:[%d]\n" , getCurrentTimestamp().c_str() , elwBatch.symbolType ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWEarlyClosedELWBatch] recvTime:[%d]\n" , getCurrentTimestamp().c_str() , elwBatch.recvTime ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWEarlyClosedELWBatch] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(elwBatch.symbol, sizeof ( elwBatch.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWEarlyClosedELWBatch] base_price_for_occurrence_of_elw_early_closing:[%f]\n" , getCurrentTimestamp().c_str() , elwBatch.base_price_for_occurrence_of_elw_early_closing ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWEarlyClosedELWBatch] contents_of_elw_early_closing_right:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(elwBatch.contents_of_elw_early_closing_right, sizeof ( elwBatch.contents_of_elw_early_closing_right )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWEarlyClosedELWBatch] price_evaluation_method_when_elw_close_early:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(elwBatch.price_evaluation_method_when_elw_close_early, sizeof ( elwBatch.price_evaluation_method_when_elw_close_early )).c_str() ));
}

void InternetChannelProcessor::printPacketELWSecuritiesTrade(const ELWSecuritiesTrade sec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWSecuritiesTrade] subtype:[%d]\texchange:[%d]\tsymbolType:[%d]\tsymbol:[%s]\trecvTime:[%d]\n" , getCurrentTimestamp().c_str() , sec.subtype , sec.exchange , sec.symbolType , ACE_CString(sec.symbol, sizeof ( sec.symbol )).c_str() , sec.recvTime ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWSecuritiesTrade] rec1\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec1.seller, sizeof ( sec.rec1.seller )).c_str() , ACE_CString(sec.rec1.buyer, sizeof ( sec.rec1.buyer )).c_str() , sec.rec1.askVolume , sec.rec1.bidVolume , sec.rec1.askAmount , sec.rec1.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWSecuritiesTrade] rec2\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec2.seller, sizeof ( sec.rec2.seller )).c_str() , ACE_CString(sec.rec2.buyer, sizeof ( sec.rec2.buyer )).c_str() , sec.rec2.askVolume , sec.rec2.bidVolume , sec.rec2.askAmount , sec.rec2.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWSecuritiesTrade] rec3\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec3.seller, sizeof ( sec.rec3.seller )).c_str() , ACE_CString(sec.rec3.buyer, sizeof ( sec.rec3.buyer )).c_str() , sec.rec3.askVolume , sec.rec3.bidVolume , sec.rec3.askAmount , sec.rec3.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWSecuritiesTrade] rec4\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec4.seller, sizeof ( sec.rec4.seller )).c_str() , ACE_CString(sec.rec4.buyer, sizeof ( sec.rec4.buyer )).c_str() , sec.rec4.askVolume , sec.rec4.bidVolume , sec.rec4.askAmount , sec.rec4.bidAmount ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELWSecuritiesTrade] rec5\tseller:[%s]\tbuyer:[%s]\taskVolume:[%f]\tbidVolume:[%f]\taskAmount:[%f]\tbidAmount:[%f]\n" , getCurrentTimestamp().c_str() , ACE_CString(sec.rec5.seller, sizeof ( sec.rec5.seller )).c_str() , ACE_CString(sec.rec5.buyer, sizeof ( sec.rec5.buyer )).c_str() , sec.rec5.askVolume , sec.rec5.bidVolume , sec.rec5.askAmount , sec.rec5.bidAmount ));
}

void InternetChannelProcessor::printPacketELWMarketOperation(const ELWMarketOperation market)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [printPacketELWMarketOperation::printPacketELWMarketOperation] symbol:[%s]\trecvTime:[%d]\tboardID:[%s]\tboardEventID:[%s]\tbeginTime:[%s]\tboardEventGroupCode:[%s]\tsessionID:[%s]\ttradingHaltReason:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(market.symbol, sizeof ( market.symbol )).c_str() , market.recvTime , ACE_CString(market.boardID, sizeof ( market.boardID )).c_str() , ACE_CString(market.boardEventID, sizeof ( market.boardEventID )).c_str() , ACE_CString(market.beginTime, sizeof ( market.beginTime )).c_str() , ACE_CString(market.boardEventGroupCode, sizeof ( market.boardEventGroupCode )).c_str() , ACE_CString(market.sessionID, sizeof ( market.sessionID )).c_str() , ACE_CString(market.tradingHaltReason, sizeof ( market.tradingHaltReason )).c_str() ));
}

void InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger(const PriceLimitRangeExpansionTrigger triggerRec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(triggerRec.symbol, sizeof ( triggerRec.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , triggerRec.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] boardId:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(triggerRec.boardId, sizeof ( triggerRec.boardId )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] priceExpansionTime:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(triggerRec.priceExpansionTime, sizeof ( triggerRec.priceExpansionTime )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] upperStepOfPriceLimitexpansion:[%d]\n" , getCurrentTimestamp().c_str() , triggerRec.upperStepOfPriceLimitexpansion ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] lowerStepOfPriceLimitexpansion:[%d]\n" , getCurrentTimestamp().c_str() , triggerRec.lowerStepOfPriceLimitexpansion ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] upperLimitPrice:[%d]\n" , getCurrentTimestamp().c_str() , triggerRec.upperLimitPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketPriceLimitRangeExpansionTrigger] lowerLimitPrice:[%d]\n" , getCurrentTimestamp().c_str() , triggerRec.lowerLimitPrice ));
}

void InternetChannelProcessor::printPacketELW_LP_Information(const ELW_LP_Information infoRec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.symbol, sizeof ( infoRec.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] recvTime:[%d]\n" , getCurrentTimestamp().c_str() , infoRec.recvTime ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] market_participant_number:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.market_participant_number, sizeof ( infoRec.market_participant_number )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] lp_starting_date:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.lp_starting_date, sizeof ( infoRec.lp_starting_date )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] lp_expiration_date:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.lp_expiration_date, sizeof ( infoRec.lp_expiration_date )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] minimum_order_volume_multiple:[%f]\n" , getCurrentTimestamp().c_str() , infoRec.minimum_order_volume_multiple ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] maximum_order_volume_multiple:[%f]\n" , getCurrentTimestamp().c_str() , infoRec.maximum_order_volume_multiple ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] order_spread_unit_code:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(infoRec.order_spread_unit_code, sizeof ( infoRec.order_spread_unit_code )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] order_spread_value:[%f]\n" , getCurrentTimestamp().c_str() , infoRec.order_spread_value ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] market_close_for_holiday_order_spread_multiple:[%f]\n" , getCurrentTimestamp().c_str() , infoRec.market_close_for_holiday_order_spread_multiple ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] duty_order_submit_time_interval:[%d]\n" , getCurrentTimestamp().c_str() , infoRec.duty_order_submit_time_interval ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] bid_minumum_order_price:[%f]\n" , getCurrentTimestamp().c_str() , infoRec.bid_minumum_order_price ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketELW_LP_Information] ask_minimum_order_price:[%f]\n" , getCurrentTimestamp().c_str() , infoRec.ask_minimum_order_price ));
}

void InternetChannelProcessor::printPacketDeterminedBasisPrice(const DeterminedBasisPrice priceRec)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketDeterminedBasisPrice] symbol:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(priceRec.symbol, sizeof ( priceRec.symbol )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketDeterminedBasisPrice] registerDt:[%d]\n" , getCurrentTimestamp().c_str() , priceRec.registerDt ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketDeterminedBasisPrice] boardId:[%s]\n" , getCurrentTimestamp().c_str() , ACE_CString(priceRec.boardId, sizeof ( priceRec.boardId )).c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketDeterminedBasisPrice] stdPrice:[%d]\n" , getCurrentTimestamp().c_str() , priceRec.stdPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketDeterminedBasisPrice] upperLimitPrice:[%d]\n" , getCurrentTimestamp().c_str() , priceRec.upperLimitPrice ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetChannelProcessor::printPacketDeterminedBasisPrice] lowerLimitPrice:[%d]\n" , getCurrentTimestamp().c_str() , priceRec.lowerLimitPrice ));
}

