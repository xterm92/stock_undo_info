#include <sstream>
#include <utility>

#include "InvestorCodeConverter.h"
#include "InternetKospi200OptionChannelProcessor.h"

#include "PaxfeedDefine.h"
#include "PaxfeedPacket.h"
#include "ace/Log_Msg.h"
#include "MMapAllocator.h"
#include "PaxfeedStatus.h"
#include "PaxfeedStringUtil.h"
#include "TickFilter.h"
#include "SimpleStringUtil.h"
#include <exception>
#include "ExturePlusInternetKospi200Option.h"

using namespace paxfeed;

const ACE_CString ERROR_SYMBOL_NOT_FOUND = "ERROR_SYMBOL_NOT_FOUND";

InternetKospi200OptionChannelProcessor::InternetKospi200OptionChannelProcessor(const ACE_CString &channelName)
        : InternetChannelProcessor(channelName), masterMap_(allocHashMap<MasterMap>("TP_OPTION_MASTER", *ALLOCATOR::instance()))
{
    optionMasterMap_.unbind_all();

    MasterMap::iterator iterInfo = masterMap_->begin();
    for ( ; iterInfo != masterMap_->end() ; ++iterInfo )
    {
        ACE_Hash_Map_Entry<ACE_CString, ExturePlusKospi200OptionStockInfoRecord>& entry = *iterInfo;
        ExturePlusKospi200OptionStockInfoRecord tempInfoRec;
        ::memcpy(&tempInfoRec, &entry.int_id_, sizeof(ExturePlusKospi200OptionStockInfoRecord));
        ACE_CString stockCode(tempInfoRec.stockCode, sizeof ( tempInfoRec.stockCode ));
        optionMasterMap_.rebind(stockCode, tempInfoRec);
        ACE_DEBUG( ( LM_DEBUG , "loading Option Master from MMAP stockCode:%s\n" , stockCode.c_str() ));
    }
}

InternetKospi200OptionChannelProcessor::~InternetKospi200OptionChannelProcessor()
{

}

int InternetKospi200OptionChannelProcessor::reset()
{
    InternetChannelProcessor::reset();
    masterMap_->unbind_all();
    optionMasterMap_.unbind_all();
    tradeMap_.unbind_all();
    openInterestMap_.unbind_all();
    return 0;
}

int InternetKospi200OptionChannelProcessor::processPacket(const ACE_CString &packet)
{
    ACE_CString dataClass(packet.substr(0, 2));
    ACE_CString trID(packet.substr(0, 5));
	ACE_CString dataType(packet.substr(0, 5));

	if(dataType == "A003F")
	{
		handleMaster(packet);
	}
	else if(dataType == "A303F")
	{
		handleTrade(packet);
	}
	else if(dataType == "A603F")
	{
		handleStockClose(packet);
	}
	else if(dataType == "A703F")
	{
		handleMarketOperation(packet);
	}
	else if(dataType == "B203F")
	{
		handleRecovery(packet);
	}
	else if(dataType == "B603F")
	{
		handleQuote(packet);
	}
	else if(dataType == "G703F")
	{
		handleTradeAndQuote(packet);
	}
	else if(dataType == "H103F")
	{
		handleInvestor(packet);
	}
	else if(dataType == "H203F")
	{
		handleOpenInterestVolume(packet);
	}
	else if(dataType == "ID03F")
	{
		handleTradeMarginStandardPrice(packet);
	}
	else if(dataType == "M403F")
	{
		handleMarketOperationScheduleDisclosureRecord(packet);
	}
	else if(dataType == "M703F")
	{
		handlePreMarketNegotiatedTrade(packet);
	}
	else if(dataType == "N703F")
	{
		handleSensitivity(packet);
	}
	else if(dataType == "O603F")
	{
		handleQuantityAllocation(packet);
	}
	else if(dataType == "Q203F")
	{
		handleRealTimeUpperLowerLimitPrice(packet);
	}
	else if(dataType == "V103F")
	{
		handlePriceLimitRangeExpansionTriggerRecord(packet);
	}
#if(0)
//(����A) STK : A701S, (�Ļ�A) DRV : A701F, A703F
#endif
	else if(dataType == "A703F")
	{
		handleMarketOperation(packet);
    }
	else
	{
		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::processPacket] trID:[%s]\n" , getCurrentTimestamp().c_str() , trID.c_str() ));
    }
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleTradeAndQuote(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_TRADE_PRIORITY_QUOTE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTradeAndQuote] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_TRADE_PRIORITY_QUOTE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_TRADE_PRIORITY_QUOTE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionTradePriorityQuoteRecord rawTradeQuoteRec;
    ::memset(&rawTradeQuoteRec, 0, sizeof(ExturePlusKospi200OptionTradePriorityQuoteRecord));
    ::memcpy(&rawTradeQuoteRec, packet.c_str(), packet.length());
    ACE_CString stockCode(rawTradeQuoteRec.stockCode, sizeof ( rawTradeQuoteRec.stockCode ));

    ACE_CString sessionID(rawTradeQuoteRec.sessionID, sizeof ( rawTradeQuoteRec.sessionID ));
    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleTradeAndQuote] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        Quote10 quote;
        ::memset(&quote, 0, sizeof(Quote10));
        quote.exchange = EXCHANGE_KSE;
        quote.symbolType = SYMBOL_OPTION;
        quote.decimalPoint = 0;
        ::memcpy(quote.symbol, stockCode.c_str(), stockCode.length());

        quote.market = getMarketInTrade(sessionID);
        quote.quoteTime = getCurrentTimeUTC(sessionID);

        ACE_CString strAskTotalVolume(rawTradeQuoteRec.askTotalQuoteVolume, sizeof ( rawTradeQuoteRec.askTotalQuoteVolume ));
        ACE_CString strBidTotalVolume(rawTradeQuoteRec.bidTotalQuoteVolume, sizeof ( rawTradeQuoteRec.bidTotalQuoteVolume ));

        quote.totalAskVolume = ::atof(strAskTotalVolume.c_str());
        quote.totalBidVolume = ::atof(strBidTotalVolume.c_str());
        quote.expectedPrice = 0;
        quote.expectedVolume = 0;

        quote.concurrent = CONCURRENT_NA;

        ACE_CString strAsk0(rawTradeQuoteRec.askPricePriority1, sizeof ( rawTradeQuoteRec.askPricePriority1 ));
        ACE_CString strAskVolume0(rawTradeQuoteRec.askVolumePriority1, sizeof ( rawTradeQuoteRec.askVolumePriority1 ));
        ACE_CString strBid0(rawTradeQuoteRec.bidPricePriority1, sizeof ( rawTradeQuoteRec.bidPricePriority1 ));
        ACE_CString strBidVolume0(rawTradeQuoteRec.bidVolumePriority1, sizeof ( rawTradeQuoteRec.bidVolumePriority1 ));

        ACE_CString strAsk1(rawTradeQuoteRec.askPricePriority2, sizeof ( rawTradeQuoteRec.askPricePriority2 ));
        ACE_CString strAskVolume1(rawTradeQuoteRec.askVolumePriority2, sizeof ( rawTradeQuoteRec.askVolumePriority2 ));
        ACE_CString strBid1(rawTradeQuoteRec.bidPricePriority2, sizeof ( rawTradeQuoteRec.bidPricePriority2 ));
        ACE_CString strBidVolume1(rawTradeQuoteRec.bidVolumePriority2, sizeof ( rawTradeQuoteRec.bidVolumePriority2 ));

        ACE_CString strAsk2(rawTradeQuoteRec.askPricePriority3, sizeof ( rawTradeQuoteRec.askPricePriority3 ));
        ACE_CString strAskVolume2(rawTradeQuoteRec.askVolumePriority3, sizeof ( rawTradeQuoteRec.askVolumePriority3 ));
        ACE_CString strBid2(rawTradeQuoteRec.bidPricePriority3, sizeof ( rawTradeQuoteRec.bidPricePriority3 ));
        ACE_CString strBidVolume2(rawTradeQuoteRec.bidVolumePriority3, sizeof ( rawTradeQuoteRec.bidVolumePriority3 ));

        ACE_CString strAsk3(rawTradeQuoteRec.askPricePriority4, sizeof ( rawTradeQuoteRec.askPricePriority4 ));
        ACE_CString strAskVolume3(rawTradeQuoteRec.askVolumePriority4, sizeof ( rawTradeQuoteRec.askVolumePriority4 ));
        ACE_CString strBid3(rawTradeQuoteRec.bidPricePriority4, sizeof ( rawTradeQuoteRec.bidPricePriority4 ));
        ACE_CString strBidVolume3(rawTradeQuoteRec.bidVolumePriority4, sizeof ( rawTradeQuoteRec.bidVolumePriority4 ));

        ACE_CString strAsk4(rawTradeQuoteRec.askPricePriority5, sizeof ( rawTradeQuoteRec.askPricePriority5 ));
        ACE_CString strAskVolume4(rawTradeQuoteRec.askVolumePriority5, sizeof ( rawTradeQuoteRec.askVolumePriority5 ));
        ACE_CString strBid4(rawTradeQuoteRec.bidPricePriority5, sizeof ( rawTradeQuoteRec.bidPricePriority5 ));
        ACE_CString strBidVolume4(rawTradeQuoteRec.bidVolumePriority5, sizeof ( rawTradeQuoteRec.bidVolumePriority5 ));

        quote.rec[0].ask = ::atoi(strAsk0.c_str());
        quote.rec[0].askVolume = ::atof(strAskVolume0.c_str());
        quote.rec[0].bid = ::atoi(strBid0.c_str());
        quote.rec[0].bidVolume = ::atof(strBidVolume0.c_str());

        quote.rec[1].ask = ::atoi(strAsk1.c_str());
        quote.rec[1].askVolume = ::atof(strAskVolume1.c_str());
        quote.rec[1].bid = ::atoi(strBid1.c_str());
        quote.rec[1].bidVolume = ::atof(strBidVolume1.c_str());

        quote.rec[2].ask = ::atoi(strAsk2.c_str());
        quote.rec[2].askVolume = ::atof(strAskVolume2.c_str());
        quote.rec[2].bid = ::atoi(strBid2.c_str());
        quote.rec[2].bidVolume = ::atof(strBidVolume2.c_str());

        quote.rec[3].ask = ::atoi(strAsk3.c_str());
        quote.rec[3].askVolume = ::atof(strAskVolume3.c_str());
        quote.rec[3].bid = ::atoi(strBid3.c_str());
        quote.rec[3].bidVolume = ::atof(strBidVolume3.c_str());

        quote.rec[4].ask = ::atoi(strAsk4.c_str());
        quote.rec[4].askVolume = ::atof(strAskVolume4.c_str());
        quote.rec[4].bid = ::atoi(strBid4.c_str());
        quote.rec[4].bidVolume = ::atof(strBidVolume4.c_str());

#if(1)
quote.expectedPrice = quote.expectedPrice * 100;
quote.rec[0].ask = quote.rec[0].ask * 100;
quote.rec[0].bid = quote.rec[0].bid * 100;
quote.rec[1].ask = quote.rec[1].ask * 100;
quote.rec[1].bid = quote.rec[1].bid * 100;
quote.rec[2].ask = quote.rec[2].ask * 100;
quote.rec[2].bid = quote.rec[2].bid * 100;
quote.rec[3].ask = quote.rec[3].ask * 100;
quote.rec[3].bid = quote.rec[3].bid * 100;
quote.rec[4].ask = quote.rec[4].ask * 100;
quote.rec[4].bid = quote.rec[4].bid * 100;
#endif

        sendQuote10(quote);

#if(0)
printPacketQuote10(quote);
#endif
    }

    ExturePlusKospi200OptionStockInfoRecord infoRec;
    int hasMasterRec = optionMasterMap_.find(stockCode, infoRec);

    if ( hasMasterRec != -1 )
    {
        ACE_CString strOpenPrice(rawTradeQuoteRec.openPrice, sizeof ( rawTradeQuoteRec.openPrice ));
        ACE_CString strHighPrice(rawTradeQuoteRec.highPrice, sizeof ( rawTradeQuoteRec.highPrice ));
        ACE_CString strLowPrice(rawTradeQuoteRec.lowPrice, sizeof ( rawTradeQuoteRec.lowPrice ));
        ACE_CString strClosePrice(rawTradeQuoteRec.currentPrice, sizeof ( rawTradeQuoteRec.currentPrice ));
        ACE_CString strAccmTradeVolume(rawTradeQuoteRec.accmTradeVolume, sizeof ( rawTradeQuoteRec.accmTradeVolume ));
        int openPrice = ::atoi(strOpenPrice.c_str());
        int highPrice = ::atoi(strHighPrice.c_str());
        int lowPrice = ::atoi(strLowPrice.c_str());
        int closePrice = ::atoi(strClosePrice.c_str());
        double accmTradeVolume = ::atof(strAccmTradeVolume.c_str());

        if ( ( openPrice == 0 ) || ( highPrice == 0 ) || ( lowPrice == 0 ) || ( closePrice == 0 ) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTradeAndQuote] Skip : %s,%d stockCode:[%s] price is zero (%d, %d, %d, %d)\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , openPrice , highPrice , lowPrice , closePrice ), -1);
        }

        Trade trade;
        ::memset(&trade, 0, sizeof(Trade));

        int hasTradePrev = tradeMap_.find(stockCode, trade);
        double netVolume = accmTradeVolume - ( hasTradePrev != -1 ? trade.accmVolume : 0 );

        ACE_CString strTickTimeMillis = ACE_CString(rawTradeQuoteRec.tradeTime, sizeof ( rawTradeQuoteRec.tradeTime ));
        int tickTime = getTickTimeUTCByTimestamp(strTickTimeMillis, sessionID);

        ACE_CString strTradeVolume(rawTradeQuoteRec.tradeVolume, sizeof ( rawTradeQuoteRec.tradeVolume ));
        int tradeVolume = ::atoi(strTradeVolume.c_str());

        if ( netVolume > 0 )
        {
            trade.subtype = TRADESUBTYPE_TRADE;
            trade.exchange = EXCHANGE_KSE;
            trade.symbolType = SYMBOL_OPTION;
            trade.decimalPoint = DECIMAL_2;

            int prevTime = trade.tradeTime;
            trade.tradeTime = tickTime;
            trade.market = getMarketInTrade(sessionID);

            ACE_CString strYdayClose(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
            int ydayClose = ::atoi(strYdayClose.c_str());

            trade.upDown = getUpDownInTrade(ydayClose, closePrice);

            trade.open = openPrice;
            trade.high = highPrice;
            trade.low = lowPrice;
            trade.close = closePrice;
            trade.ydayClose = ydayClose;
            trade.tradeVolume = tradeVolume;
            trade.accmVolume = accmTradeVolume;

            ACE_CString strAmount(rawTradeQuoteRec.accmTradeAmount, sizeof ( rawTradeQuoteRec.accmTradeAmount ));
            trade.amount = ::atof(strAmount.c_str());
            trade.amount = trade.amount * 1000;

            ExturePlusKospi200OptionOpenInterestVolumeRecord oiRec;
            ::memset(&oiRec, 0, sizeof(ExturePlusKospi200OptionOpenInterestVolumeRecord));
            int hasOi = openInterestMap_.find(stockCode, oiRec);
            if ( hasOi != -1 )
            {
                ACE_CString strOpenInterest(oiRec.openInterestVolume, sizeof ( oiRec.openInterestVolume ));
                trade.openInterest = ::atoi(strOpenInterest.c_str());
            }
            else
            {
                trade.openInterest = 0;
            }

            if ( hasTradePrev == -1 )
            {
                trade.subtype = TRADESUBTYPE_TRADE;
                trade.exchange = EXCHANGE_KSE;
                trade.symbolType = SYMBOL_OPTION;
                trade.decimalPoint = DECIMAL_2;

                memcpy(&trade.symbol, stockCode.c_str(), stockCode.length());

                trade.openMin = openPrice;
                trade.highMin = highPrice;
                trade.lowMin = lowPrice;
                trade.volumeMin = trade.tradeVolume;

                tradeMap_.rebind(stockCode, trade);
            } // if (hasTradePrev == -1)
            else
            {
                if ( ( trade.tradeTime / 60 ) == ( prevTime / 60 ) )
                {
                    trade.highMin = trade.highMin > trade.close ? trade.highMin : trade.close;
                    trade.lowMin = trade.lowMin < trade.close ? trade.lowMin : trade.close;
                    trade.volumeMin += trade.tradeVolume;
                }
                else
                {
                    trade.openMin = trade.close;
                    trade.highMin = trade.close;
                    trade.lowMin = trade.close;
                    trade.volumeMin = trade.tradeVolume;
                }
                tradeMap_.rebind(stockCode, trade);
            }

#if(1)
trade.upDown = trade.upDown * 100;
trade.open = trade.open * 100;
trade.high = trade.high * 100;
trade.low = trade.low * 100;
trade.close = trade.close * 100;
trade.ydayClose = trade.ydayClose * 100;
trade.openMin = trade.openMin * 100;
trade.highMin = trade.highMin * 100;
trade.lowMin = trade.lowMin * 100;
#endif

            char buf[TRADE_SIZE];
            memcpy(buf, &trade, TRADE_SIZE);
            sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

#if(0)
printPacketTrade(trade);
#endif

            ACE_CString strRealTimeUpperLimitPrice(rawTradeQuoteRec.realTimeUpperLimitPrice, sizeof ( rawTradeQuoteRec.realTimeUpperLimitPrice ));
            ACE_CString strRealTimeLowerLimitPrice(rawTradeQuoteRec.realTimeLowerLimitPrice, sizeof ( rawTradeQuoteRec.realTimeLowerLimitPrice ));
            double realTimeUpperLimitPrice = ::atof(strRealTimeUpperLimitPrice.c_str());
            double realTimeLowerLimitPrice = ::atof(strRealTimeLowerLimitPrice.c_str());

            RealTimeLimitPrice limitRec;
            ::memset(&limitRec, 0, sizeof(RealTimeLimitPrice));
            ::memcpy(&limitRec.symbol, trade.symbol, sizeof ( trade.symbol ));
            limitRec.registerDt = trade.tradeTime;
            limitRec.realTimeUpperLimitPrice = realTimeUpperLimitPrice;
            limitRec.realTimeLowerLimitPrice = realTimeLowerLimitPrice;

#if(1)
limitRec.realTimeUpperLimitPrice = limitRec.realTimeUpperLimitPrice * 100;
limitRec.realTimeLowerLimitPrice = limitRec.realTimeLowerLimitPrice * 100;
#endif

#if(0)
printPacketRealTimeLimitPrice(limitRec);
#endif

            char bufSendPacket[REAL_TIME_LIMIT_PRICE_SIZE];
            ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
            ::memcpy(&bufSendPacket, &limitRec, sizeof(RealTimeLimitPrice));
            sendPacket(ACE_CString(bufSendPacket, REAL_TIME_LIMIT_PRICE_SIZE), PACKET_REAL_TIME_LIMIT_PRICE, EXCHANGE_KSE);
        }
        else
        {
            if ( netVolume < 0 )
            {
                ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTradeAndQuote] Skip : %s,%d : net volume is below zero stockCode:[%s] netVolume:[%d]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , netVolume ), -1);
            }
        } // if (netVolume > 0)
    } // if (hasMasterRec != -1)  
    else
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTradeAndQuote] Skip : %s,%d : cannot find matching master data stockCode:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() ), -1);
    }
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleRecovery(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_STOCK_RECOVERY_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleRecovery] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_STOCK_RECOVERY_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_STOCK_RECOVERY_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionRecoveryRecord rawRecoveryRec;
    ::memset(&rawRecoveryRec, 0, sizeof(ExturePlusKospi200OptionRecoveryRecord));
    ::memcpy(&rawRecoveryRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawRecoveryRec.stockCode, sizeof ( rawRecoveryRec.stockCode ));
    ACE_CString sessionID(rawRecoveryRec.sessionID, sizeof ( rawRecoveryRec.sessionID ));

    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleRecovery] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        Quote10 quote;
        ::memset(&quote, 0, sizeof(Quote10));
        ::memcpy(quote.symbol, stockCode.c_str(), stockCode.length());
        quote.exchange = EXCHANGE_KSE;
        quote.symbolType = SYMBOL_OPTION;
        quote.decimalPoint = 0;

        quote.market = getMarketInTrade(sessionID);
        quote.quoteTime = getCurrentTimeUTC(sessionID);

        ACE_CString strAskTotalVolume(rawRecoveryRec.askTotalVolume, sizeof ( rawRecoveryRec.askTotalVolume ));
        ACE_CString strBidTotalVolume(rawRecoveryRec.bidTotalVolume, sizeof ( rawRecoveryRec.bidTotalVolume ));

        quote.totalAskVolume = ::atof(strAskTotalVolume.c_str());
        quote.totalBidVolume = ::atof(strBidTotalVolume.c_str());
        quote.expectedPrice = 0;
        quote.expectedVolume = 0;

        quote.concurrent = CONCURRENT_NA;

        for ( int i = 0 ; i < 5 ; ++i )
        {
            ACE_CString strAskPrice(rawRecoveryRec.quoteRecord[i].askPrice, sizeof ( rawRecoveryRec.quoteRecord[i].askPrice ));
            ACE_CString strAskVolume(rawRecoveryRec.quoteRecord[i].askVolume, sizeof ( rawRecoveryRec.quoteRecord[i].askVolume ));
            ACE_CString strBidPrice(rawRecoveryRec.quoteRecord[i].bidPrice, sizeof ( rawRecoveryRec.quoteRecord[i].bidPrice ));
            ACE_CString strBidVolume(rawRecoveryRec.quoteRecord[i].bidVolume, sizeof ( rawRecoveryRec.quoteRecord[i].bidVolume ));

            quote.rec[i].ask = ::atoi(strAskPrice.c_str());
            quote.rec[i].askVolume = ::atof(strAskVolume.c_str());
            quote.rec[i].bid = ::atoi(strBidPrice.c_str());
            quote.rec[i].bidVolume = ::atof(strBidVolume.c_str());
        }

        if ( ( sessionID == "10" ) || ( sessionID == "20" ) || ( sessionID == "30" ) || ( sessionID == "80" ) )
        {
            ACE_CString estimatedTradingPrice(rawRecoveryRec.estimatedTradingPrice, sizeof ( rawRecoveryRec.estimatedTradingPrice ));
            int expectedPrice = ::atoi(estimatedTradingPrice.c_str());
            quote.expectedPrice = expectedPrice;
        }

#if(1)
quote.expectedPrice = quote.expectedPrice * 100;
quote.rec[0].ask = quote.rec[0].ask * 100;
quote.rec[0].bid = quote.rec[0].bid * 100;
quote.rec[1].ask = quote.rec[1].ask * 100;
quote.rec[1].bid = quote.rec[1].bid * 100;
quote.rec[2].ask = quote.rec[2].ask * 100;
quote.rec[2].bid = quote.rec[2].bid * 100;
quote.rec[3].ask = quote.rec[3].ask * 100;
quote.rec[3].bid = quote.rec[3].bid * 100;
quote.rec[4].ask = quote.rec[4].ask * 100;
quote.rec[4].bid = quote.rec[4].bid * 100;
#endif

        char quoteBuf[QUOTE10_SIZE];
        memcpy(quoteBuf, &quote, QUOTE10_SIZE);
        sendPacket(ACE_CString(quoteBuf, QUOTE10_SIZE), PACKET_QUOTE10, EXCHANGE_KSE);

#if(0)
printPacketQuote10(quote);
#endif
    }

    ExturePlusKospi200OptionStockInfoRecord infoRec;
    int hasMasterRec = optionMasterMap_.find(stockCode, infoRec);

    if ( hasMasterRec != -1 )
    {
        ACE_CString strOpenPrice(rawRecoveryRec.openPrice, sizeof ( rawRecoveryRec.openPrice ));
        ACE_CString strHighPrice(rawRecoveryRec.highPrice, sizeof ( rawRecoveryRec.highPrice ));
        ACE_CString strLowPrice(rawRecoveryRec.lowPrice, sizeof ( rawRecoveryRec.lowPrice ));
        ACE_CString strClosePrice(rawRecoveryRec.currentPrice, sizeof ( rawRecoveryRec.currentPrice ));
        ACE_CString strAccmTradeVolume(rawRecoveryRec.accmTradeVolume, sizeof ( rawRecoveryRec.accmTradeVolume ));
        int openPrice = ::atoi(strOpenPrice.c_str());
        int highPrice = ::atoi(strHighPrice.c_str());
        int lowPrice = ::atoi(strLowPrice.c_str());
        int closePrice = ::atoi(strClosePrice.c_str());
        double accmTradeVolume = ::atof(strAccmTradeVolume.c_str());

        if ( ( openPrice == 0 ) || ( highPrice == 0 ) || ( lowPrice == 0 ) || ( closePrice == 0 ) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleRecovery] Skip : %s,%d stockCode:[%s] price is zero (%d, %d, %d, %d)\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , openPrice , highPrice , lowPrice , closePrice ), -1);
        }

        Trade trade;
        ::memset(&trade, 0, sizeof(Trade));

        int hasTradePrev = tradeMap_.find(stockCode, trade);
        double netVolume = accmTradeVolume - ( hasTradePrev != -1 ? trade.accmVolume : 0 );

        if ( netVolume > 0 )
        {
            trade.subtype = TRADESUBTYPE_TRADE;
            trade.exchange = EXCHANGE_KSE;
            trade.symbolType = SYMBOL_OPTION;
            trade.decimalPoint = DECIMAL_2;

            int prevTime = trade.tradeTime;

            trade.tradeTime = getCurrentTimeUTC(sessionID);
            trade.market = getMarketInTrade(sessionID);

            ACE_CString strYdayClose(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
            int ydayClose = ::atoi(strYdayClose.c_str());

            trade.upDown = getUpDownInTrade(ydayClose, closePrice);
            trade.open = openPrice;
            trade.high = highPrice;
            trade.low = lowPrice;
            trade.close = closePrice;
            trade.ydayClose = ydayClose;

            trade.tradeVolume = 0;
            trade.accmVolume = accmTradeVolume;

            ACE_CString strAmount(rawRecoveryRec.accmTradeAmount, sizeof ( rawRecoveryRec.accmTradeAmount ));
            trade.amount = ::atof(strAmount.c_str());
            trade.amount = trade.amount * 1000;

            ExturePlusKospi200OptionOpenInterestVolumeRecord oiRec;
            ::memset(&oiRec, 0, sizeof(ExturePlusKospi200OptionOpenInterestVolumeRecord));
            int hasOi = openInterestMap_.find(stockCode, oiRec);
            if ( hasOi != -1 )
            {
                ACE_CString strOpenInterest(oiRec.openInterestVolume, sizeof ( oiRec.openInterestVolume ));
                trade.openInterest = ::atoi(strOpenInterest.c_str());
            }
            else
            {
                trade.openInterest = 0;
            }

            if ( hasTradePrev == -1 )
            {
                trade.subtype = TRADESUBTYPE_TRADE;
                trade.exchange = EXCHANGE_KSE;
                trade.symbolType = SYMBOL_OPTION;
                trade.decimalPoint = DECIMAL_2;

                memcpy(&trade.symbol, stockCode.c_str(), stockCode.length());

                trade.openMin = openPrice;
                trade.highMin = highPrice;
                trade.lowMin = lowPrice;
                trade.volumeMin = trade.tradeVolume;

                tradeMap_.rebind(stockCode, trade);
            } // if (hasTradePrev == -1)
            else
            {
                if ( ( trade.tradeTime / 60 ) == ( prevTime / 60 ) )
                {
                    trade.highMin = trade.highMin > trade.close ? trade.highMin : trade.close;
                    trade.lowMin = trade.lowMin < trade.close ? trade.lowMin : trade.close;
                    trade.volumeMin += trade.tradeVolume;
                }
                else
                {
                    trade.openMin = trade.close;
                    trade.highMin = trade.close;
                    trade.lowMin = trade.close;
                    trade.volumeMin = trade.tradeVolume;
                }
                tradeMap_.rebind(stockCode, trade);
            }

#if(1)
trade.upDown = trade.upDown * 100;
trade.open = trade.open * 100;
trade.high = trade.high * 100;
trade.low = trade.low * 100;
trade.close = trade.close * 100;
trade.ydayClose = trade.ydayClose * 100;
trade.openMin = trade.openMin * 100;
trade.highMin = trade.highMin * 100;
trade.lowMin = trade.lowMin * 100;
#endif

            char tradeBuf[TRADE_SIZE];
            memcpy(tradeBuf, &trade, TRADE_SIZE);
            sendPacket(ACE_CString(tradeBuf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

#if(0)
printPacketTrade(trade);
#endif

            // 실시간 상한가 하한가 정보 처리
            ACE_CString strRealTimeUpperLimitPrice(rawRecoveryRec.realTimeUpperLimitPrice, sizeof ( rawRecoveryRec.realTimeUpperLimitPrice ));
            ACE_CString strRealTimeLowerLimitPrice(rawRecoveryRec.realTimeLowerLimitPrice, sizeof ( rawRecoveryRec.realTimeLowerLimitPrice ));
            double realTimeUpperLimitPrice = ::atof(strRealTimeUpperLimitPrice.c_str());
            double realTimeLowerLimitPrice = ::atof(strRealTimeLowerLimitPrice.c_str());

            RealTimeLimitPrice limitRec;
            ::memset(&limitRec, 0, sizeof(RealTimeLimitPrice));
            ::memcpy(&limitRec.symbol, trade.symbol, sizeof ( trade.symbol ));
            limitRec.registerDt = trade.tradeTime;
            limitRec.realTimeUpperLimitPrice = realTimeUpperLimitPrice;
            limitRec.realTimeLowerLimitPrice = realTimeLowerLimitPrice;


#if(1)
limitRec.realTimeUpperLimitPrice = limitRec.realTimeUpperLimitPrice * 100;
limitRec.realTimeLowerLimitPrice = limitRec.realTimeLowerLimitPrice * 100;
#endif

#if(0)
printPacketRealTimeLimitPrice(limitRec);
#endif

            char bufSendPacket[REAL_TIME_LIMIT_PRICE_SIZE];
            ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
            ::memcpy(&bufSendPacket, &limitRec, sizeof(RealTimeLimitPrice));
            sendPacket(ACE_CString(bufSendPacket, REAL_TIME_LIMIT_PRICE_SIZE), PACKET_REAL_TIME_LIMIT_PRICE, EXCHANGE_KSE);
        }
        else
        {
            if ( netVolume < 0 )
            {
                ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleRecovery] Skip : %s,%d : net volume is below zero stockCode:[%s] netVolume:[%d]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , netVolume ), -1);
            }
        } // if (netVolume > 0)
    } // if (hasMasterRec != -1)  
    else
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleRecovery] Skip : %s,%d : cannot find matching master data stockCode:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() ), -1);
    }
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_TRADE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTrade] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_TRADE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_TRADE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionTradeRecord rawTradeRec;
    ::memset(&rawTradeRec, 0, sizeof(ExturePlusKospi200OptionTradeRecord));
    ::memcpy(&rawTradeRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawTradeRec.stockCode, sizeof ( rawTradeRec.stockCode ));
    ACE_CString sessionID(rawTradeRec.sessionID, sizeof ( rawTradeRec.sessionID ));

    ExturePlusKospi200OptionStockInfoRecord infoRec;
    int hasMasterRec = optionMasterMap_.find(stockCode, infoRec);

    if ( hasMasterRec != -1 )
    {
        ACE_CString strOpenPrice(rawTradeRec.openPrice, sizeof ( rawTradeRec.openPrice ));
        ACE_CString strHighPrice(rawTradeRec.highPrice, sizeof ( rawTradeRec.highPrice ));
        ACE_CString strLowPrice(rawTradeRec.lowPrice, sizeof ( rawTradeRec.lowPrice ));
        ACE_CString strClosePrice(rawTradeRec.currentPrice, sizeof ( rawTradeRec.currentPrice ));
        ACE_CString strAccmTradeVolume(rawTradeRec.accmTradeVolume, sizeof ( rawTradeRec.accmTradeVolume ));
        int openPrice = ::atoi(strOpenPrice.c_str());
        int highPrice = ::atoi(strHighPrice.c_str());
        int lowPrice = ::atoi(strLowPrice.c_str());
        int closePrice = ::atoi(strClosePrice.c_str());
        double accmTradeVolume = ::atof(strAccmTradeVolume.c_str());

        if ( ( openPrice == 0 ) || ( highPrice == 0 ) || ( lowPrice == 0 ) || ( closePrice == 0 ) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTrade] Skip : %s,%d stockCode:[%s] price is zero (%d, %d, %d, %d)\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , openPrice , highPrice , lowPrice , closePrice ), -1);
        }

        Trade trade;
        ::memset(&trade, 0, sizeof(Trade));

        int hasTradePrev = tradeMap_.find(stockCode, trade);
        double netVolume = accmTradeVolume - ( hasTradePrev != -1 ? trade.accmVolume : 0 );

        ACE_CString strTickTimeMillis = ACE_CString(rawTradeRec.tradeTime, sizeof ( rawTradeRec.tradeTime ));
        int tickTime = getTickTimeUTCByTimestamp(strTickTimeMillis, sessionID);

        ACE_CString strTradeVolume(rawTradeRec.tradeVolume, sizeof ( rawTradeRec.tradeVolume ));
        int tradeVolume = ::atoi(strTradeVolume.c_str());

        if ( netVolume > 0 )
        {
            trade.subtype = TRADESUBTYPE_TRADE;
            trade.exchange = EXCHANGE_KSE;
            trade.symbolType = SYMBOL_OPTION;
            trade.decimalPoint = DECIMAL_2;

            int prevTime = trade.tradeTime;
            trade.tradeTime = tickTime;
            trade.market = getMarketInTrade(sessionID);

            ACE_CString strYdayClose(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
            int ydayClose = ::atoi(strYdayClose.c_str());

            trade.upDown = getUpDownInTrade(ydayClose, closePrice);
            trade.open = openPrice;
            trade.high = highPrice;
            trade.low = lowPrice;
            trade.close = closePrice;
            trade.ydayClose = ydayClose;
            trade.tradeVolume = tradeVolume;
            trade.accmVolume = accmTradeVolume;

            ACE_CString strAmount(rawTradeRec.accmTradeAmount, sizeof ( rawTradeRec.accmTradeAmount ));
            trade.amount = ::atof(strAmount.c_str());
            trade.amount = trade.amount * 1000;

            ExturePlusKospi200OptionOpenInterestVolumeRecord oiRec;
            ::memset(&oiRec, 0, sizeof(ExturePlusKospi200OptionOpenInterestVolumeRecord));
            int hasOi = openInterestMap_.find(stockCode, oiRec);
            if ( hasOi != -1 )
            {
                ACE_CString strOpenInterest(oiRec.openInterestVolume, sizeof ( oiRec.openInterestVolume ));
                trade.openInterest = ::atoi(strOpenInterest.c_str());
            }
            else
            {
                trade.openInterest = 0;
            }

            if ( hasTradePrev == -1 )
            {
                trade.subtype = TRADESUBTYPE_TRADE;
                trade.exchange = EXCHANGE_KSE;
                trade.symbolType = SYMBOL_OPTION;
                trade.decimalPoint = DECIMAL_2;

                memcpy(&trade.symbol, stockCode.c_str(), stockCode.length());

                trade.openMin = openPrice;
                trade.highMin = highPrice;
                trade.lowMin = lowPrice;
                trade.volumeMin = trade.tradeVolume;

                tradeMap_.rebind(stockCode, trade);
            } // if (hasTradePrev == -1)
            else
            {
                if ( ( trade.tradeTime / 60 ) == ( prevTime / 60 ) )
                {
                    trade.highMin = trade.highMin > trade.close ? trade.highMin : trade.close;
                    trade.lowMin = trade.lowMin < trade.close ? trade.lowMin : trade.close;
                    trade.volumeMin += trade.tradeVolume;
                }
                else
                {
                    trade.openMin = trade.close;
                    trade.highMin = trade.close;
                    trade.lowMin = trade.close;
                    trade.volumeMin = trade.tradeVolume;
                }
                tradeMap_.rebind(stockCode, trade);
            }

#if(1)
trade.upDown = trade.upDown * 100;
trade.open = trade.open * 100;
trade.high = trade.high * 100;
trade.low = trade.low * 100;
trade.close = trade.close * 100;
trade.ydayClose = trade.ydayClose * 100;
trade.openMin = trade.openMin * 100;
trade.highMin = trade.highMin * 100;
trade.lowMin = trade.lowMin * 100;
#endif

            char buf[TRADE_SIZE];
            memcpy(buf, &trade, TRADE_SIZE);
            sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

#if(0)
printPacketTrade(trade);
#endif

            ACE_CString strRealTimeUpperLimitPrice(rawTradeRec.realTimeUpperLimitPrice, sizeof ( rawTradeRec.realTimeUpperLimitPrice ));
            ACE_CString strRealTimeLowerLimitPrice(rawTradeRec.realTimeLowerLimitPrice, sizeof ( rawTradeRec.realTimeLowerLimitPrice ));
            double realTimeUpperLimitPrice = ::atof(strRealTimeUpperLimitPrice.c_str());
            double realTimeLowerLimitPrice = ::atof(strRealTimeLowerLimitPrice.c_str());

            RealTimeLimitPrice limitRec;
            ::memset(&limitRec, 0, sizeof(RealTimeLimitPrice));
            ::memcpy(&limitRec.symbol, trade.symbol, sizeof ( trade.symbol ));
            limitRec.registerDt = trade.tradeTime;
            limitRec.realTimeUpperLimitPrice = realTimeUpperLimitPrice;
            limitRec.realTimeLowerLimitPrice = realTimeLowerLimitPrice;


#if(1)
limitRec.realTimeUpperLimitPrice = limitRec.realTimeUpperLimitPrice * 100;
limitRec.realTimeLowerLimitPrice = limitRec.realTimeLowerLimitPrice * 100;
#endif

#if(0)
printPacketRealTimeLimitPrice(limitRec);
#endif

            char bufSendPacket[REAL_TIME_LIMIT_PRICE_SIZE];
            ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
            ::memcpy(&bufSendPacket, &limitRec, sizeof(RealTimeLimitPrice));
            sendPacket(ACE_CString(bufSendPacket, REAL_TIME_LIMIT_PRICE_SIZE), PACKET_REAL_TIME_LIMIT_PRICE, EXCHANGE_KSE);
        }
        else
        {
            if ( netVolume < 0 )
            {
                ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTrade] Skip : %s,%d : net volume is below zero stockCode:[%s] netVolume:[%d]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , netVolume ), -1);
            }
        } // if (netVolume > 0)
    } // if (hasMasterRec != -1)  
    else
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTrade] Skip : %s,%d : cannot find matching master data stockCode:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() ), -1);
    }
    return 0;
}

#if(1)
int InternetKospi200OptionChannelProcessor::handleMarketOperation(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationTS] BEGIN\n" , getCurrentTimestamp().c_str() ));
    if ( EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperation] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_MARKET_OPERATION_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } 

    ExturePlusKospi200OptionMarketOperationRecord rawOperationRec;
    ::memset(&rawOperationRec, 0, sizeof(ExturePlusKospi200OptionMarketOperationRecord));
    ::memcpy(&rawOperationRec, packet.c_str(), packet.length());

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

    ACE_CString stockCode(rawOperationRec.stockCode, sizeof ( rawOperationRec.stockCode ));
    if ( stockCode == "" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationTS] invalid issueCode:[%s][%d] skip......\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , stockCode.length() ));
        return 0;
    }

    ACE_CString symbol(stockCode.c_str());

    ::memcpy(&marketRec.symbol, symbol.c_str(), symbol.length());
    marketRec.recvTime = (int) ( ::time(0) );
    ::memcpy(&marketRec.boardId, rawOperationRec.boardID, sizeof ( rawOperationRec.boardID ));
    ::memcpy(&marketRec.boardEventId, rawOperationRec.boardEventID, sizeof ( rawOperationRec.boardEventID ));
    ::memcpy(&marketRec.beginTime, rawOperationRec.boardEventBeginTime, sizeof ( rawOperationRec.boardEventBeginTime ));
    ::memcpy(&marketRec.tradingHaltReason, rawOperationRec.tradingHaltReasonCode, sizeof ( rawOperationRec.tradingHaltReasonCode ));

#if(1)
printPacketMarketOperation(marketRec);
#endif

    char buf[MARKET_OPERATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &marketRec, sizeof(MarketOperation));
    int result = sendPacket(ACE_CString(buf, MARKET_OPERATION_SIZE), PACKET_MARKET_OPERATION, EXCHANGE_KSE);
    return result;
}
#endif

#if(1)
int InternetKospi200OptionChannelProcessor::handleStockClose(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_STOCK_CLOSE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleStockClose] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_STOCK_CLOSE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_STOCK_CLOSE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionStockCloseRecord rawCloseRec;
    ::memset(&rawCloseRec, 0, sizeof(ExturePlusKospi200OptionStockCloseRecord));
    ::memcpy(&rawCloseRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawCloseRec.stockCode, sizeof ( rawCloseRec.stockCode ));
    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleStockClose] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));
    int hasTradePrev = tradeMap_.find(stockCode, trade);
    if ( hasTradePrev != -1 )
    {
        int closePrice = ::atoi(ACE_CString(rawCloseRec.closePrice, sizeof rawCloseRec.closePrice).c_str());
        double accmTradeVolume = ::atof(ACE_CString(rawCloseRec.accmTradeVolume, sizeof rawCloseRec.accmTradeVolume).c_str());
        double accmTradeAmount = ::atof(ACE_CString(rawCloseRec.accmTradeAmount, sizeof rawCloseRec.accmTradeAmount).c_str());

        accmTradeAmount = accmTradeAmount * 1000;

        trade.close = closePrice;
        trade.tradeVolume = 0;
        trade.accmVolume = accmTradeVolume;
        trade.amount = accmTradeAmount;



#if(1)
trade.upDown = trade.upDown * 100;
trade.open = trade.open * 100;
trade.high = trade.high * 100;
trade.low = trade.low * 100;
trade.close = trade.close * 100;
trade.ydayClose = trade.ydayClose * 100;
trade.openMin = trade.openMin * 100;
trade.highMin = trade.highMin * 100;
trade.lowMin = trade.lowMin * 100;
#endif


        char buf[TRADE_SIZE];
        memcpy(buf, &trade, TRADE_SIZE);
        sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

#if(1)
printPacketTrade(trade);
#endif

        tradeMap_.rebind(stockCode, trade);
    }
    return 0;
}
#endif

int InternetKospi200OptionChannelProcessor::handleQuote(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_PRIORITY_QUOTE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleQuote] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_PRIORITY_QUOTE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_PRIORITY_QUOTE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionPriorityQuoteRecord rawQuoteRec;
    ::memset(&rawQuoteRec, 0, sizeof(ExturePlusKospi200OptionPriorityQuoteRecord));
    ::memcpy(&rawQuoteRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawQuoteRec.stockCode, sizeof ( rawQuoteRec.stockCode ));
    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleQuote] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        Quote10 quote;
        ::memset(&quote, 0, sizeof(Quote10));
        quote.exchange = EXCHANGE_KSE;
        quote.symbolType = SYMBOL_OPTION;
        quote.decimalPoint = 0;
        ::memcpy(quote.symbol, stockCode.c_str(), stockCode.length());

        ACE_CString sessionID(rawQuoteRec.sessionID, sizeof ( rawQuoteRec.sessionID ));

        quote.market = getMarketInTrade(sessionID);
        quote.quoteTime = getCurrentTimeUTC(sessionID);

        ACE_CString strAskTotalVolume(rawQuoteRec.askTotalQuoteVolume, sizeof ( rawQuoteRec.askTotalQuoteVolume ));
        ACE_CString strBidTotalVolume(rawQuoteRec.bidTotalQuoteVolume, sizeof ( rawQuoteRec.bidTotalQuoteVolume ));

        quote.totalAskVolume = ::atof(strAskTotalVolume.c_str());
        quote.totalBidVolume = ::atof(strBidTotalVolume.c_str());
        quote.expectedPrice = 0;
        quote.expectedVolume = 0;

        quote.concurrent = CONCURRENT_NA;

        ACE_CString strAsk0(rawQuoteRec.askPricePriority1, sizeof ( rawQuoteRec.askPricePriority1 ));
        ACE_CString strAskVolume0(rawQuoteRec.askVolumePriority1, sizeof ( rawQuoteRec.askVolumePriority1 ));
        ACE_CString strBid0(rawQuoteRec.bidPricePriority1, sizeof ( rawQuoteRec.bidPricePriority1 ));
        ACE_CString strBidVolume0(rawQuoteRec.bidVolumePriority1, sizeof ( rawQuoteRec.bidVolumePriority1 ));

        ACE_CString strAsk1(rawQuoteRec.askPricePriority2, sizeof ( rawQuoteRec.askPricePriority2 ));
        ACE_CString strAskVolume1(rawQuoteRec.askVolumePriority2, sizeof ( rawQuoteRec.askVolumePriority2 ));
        ACE_CString strBid1(rawQuoteRec.bidPricePriority2, sizeof ( rawQuoteRec.bidPricePriority2 ));
        ACE_CString strBidVolume1(rawQuoteRec.bidVolumePriority2, sizeof ( rawQuoteRec.bidVolumePriority2 ));

        ACE_CString strAsk2(rawQuoteRec.askPricePriority3, sizeof ( rawQuoteRec.askPricePriority3 ));
        ACE_CString strAskVolume2(rawQuoteRec.askVolumePriority3, sizeof ( rawQuoteRec.askVolumePriority3 ));
        ACE_CString strBid2(rawQuoteRec.bidPricePriority3, sizeof ( rawQuoteRec.bidPricePriority3 ));
        ACE_CString strBidVolume2(rawQuoteRec.bidVolumePriority3, sizeof ( rawQuoteRec.bidVolumePriority3 ));

        ACE_CString strAsk3(rawQuoteRec.askPricePriority4, sizeof ( rawQuoteRec.askPricePriority4 ));
        ACE_CString strAskVolume3(rawQuoteRec.askVolumePriority4, sizeof ( rawQuoteRec.askVolumePriority4 ));
        ACE_CString strBid3(rawQuoteRec.bidPricePriority4, sizeof ( rawQuoteRec.bidPricePriority4 ));
        ACE_CString strBidVolume3(rawQuoteRec.bidVolumePriority4, sizeof ( rawQuoteRec.bidVolumePriority4 ));

        ACE_CString strAsk4(rawQuoteRec.askPricePriority5, sizeof ( rawQuoteRec.askPricePriority5 ));
        ACE_CString strAskVolume4(rawQuoteRec.askVolumePriority5, sizeof ( rawQuoteRec.askVolumePriority5 ));
        ACE_CString strBid4(rawQuoteRec.bidPricePriority5, sizeof ( rawQuoteRec.bidPricePriority5 ));
        ACE_CString strBidVolume4(rawQuoteRec.bidVolumePriority5, sizeof ( rawQuoteRec.bidVolumePriority5 ));

        quote.rec[0].ask = ::atoi(strAsk0.c_str());
        quote.rec[0].askVolume = ::atof(strAskVolume0.c_str());
        quote.rec[0].bid = ::atoi(strBid0.c_str());
        quote.rec[0].bidVolume = ::atof(strBidVolume0.c_str());

        quote.rec[1].ask = ::atoi(strAsk1.c_str());
        quote.rec[1].askVolume = ::atof(strAskVolume1.c_str());
        quote.rec[1].bid = ::atoi(strBid1.c_str());
        quote.rec[1].bidVolume = ::atof(strBidVolume1.c_str());

        quote.rec[2].ask = ::atoi(strAsk2.c_str());
        quote.rec[2].askVolume = ::atof(strAskVolume2.c_str());
        quote.rec[2].bid = ::atoi(strBid2.c_str());
        quote.rec[2].bidVolume = ::atof(strBidVolume2.c_str());

        quote.rec[3].ask = ::atoi(strAsk3.c_str());
        quote.rec[3].askVolume = ::atof(strAskVolume3.c_str());
        quote.rec[3].bid = ::atoi(strBid3.c_str());
        quote.rec[3].bidVolume = ::atof(strBidVolume3.c_str());

        quote.rec[4].ask = ::atoi(strAsk4.c_str());
        quote.rec[4].askVolume = ::atof(strAskVolume4.c_str());
        quote.rec[4].bid = ::atoi(strBid4.c_str());
        quote.rec[4].bidVolume = ::atof(strBidVolume4.c_str());

        // 예상체결가 디버깅용
        if ( ( sessionID == "10" ) || ( sessionID == "20" ) || ( sessionID == "30" ) || ( sessionID == "80" ) )
        {
            ACE_CString estimatedTradingPrice(rawQuoteRec.estimatedTradingPrice, sizeof ( rawQuoteRec.estimatedTradingPrice ));

            int expectedPrice = ::atoi(estimatedTradingPrice.c_str());
            quote.expectedPrice = expectedPrice;
        }

#if(1)
quote.expectedPrice = quote.expectedPrice * 100;
quote.rec[0].ask = quote.rec[0].ask * 100;
quote.rec[0].bid = quote.rec[0].bid * 100;
quote.rec[1].ask = quote.rec[1].ask * 100;
quote.rec[1].bid = quote.rec[1].bid * 100;
quote.rec[2].ask = quote.rec[2].ask * 100;
quote.rec[2].bid = quote.rec[2].bid * 100;
quote.rec[3].ask = quote.rec[3].ask * 100;
quote.rec[3].bid = quote.rec[3].bid * 100;
quote.rec[4].ask = quote.rec[4].ask * 100;
quote.rec[4].bid = quote.rec[4].bid * 100;
#endif

        sendQuote10(quote);
    }
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleInvestor(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INVESTOR_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleInvestor] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INVESTOR_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INVESTOR_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionInvestorRecord rawInvestorRec;
    ::memset(&rawInvestorRec, 0, sizeof(ExturePlusKospi200OptionInvestorRecord));
    ::memcpy(&rawInvestorRec, packet.c_str(), packet.length());

    // 최종 레코드는 99 로 세팅
    ACE_CString dataType(rawInvestorRec.dataType, sizeof ( rawInvestorRec.dataType ));
    if ( dataType == "99" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleInvestor] Skip : dataType:[%s]\n" , getCurrentTimestamp().c_str() , dataType.c_str() ));
        return 0;
    }

    Investor investor;
    ::memset(&investor, 0, sizeof(Investor));
    investor.exchange = EXCHANGE_KSE;
    investor.symbolType = SYMBOL_OPTION;

    ACE_CString optionClass(rawInvestorRec.optionClass, sizeof ( rawInvestorRec.optionClass ));
    ACE_CString changedStockCode = getSymbol(optionClass);

    if ( ( changedStockCode == "" ) || ( changedStockCode == "999999999999" ) )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleInvestor] Skip : changedStockCode:[%s]\n" , getCurrentTimestamp().c_str() , changedStockCode.c_str() ));
        return 0;
    }
    else
    {
        ::memcpy(investor.symbol, changedStockCode.c_str(), changedStockCode.length());

        ACE_CString investorType(rawInvestorRec.investorType, sizeof ( rawInvestorRec.investorType ));
        ::memcpy(investor.investor, investorType.c_str(), investorType.length());

        ACE_CString strAskVolume(rawInvestorRec.askAgreementVolume, sizeof ( rawInvestorRec.askAgreementVolume ));
        ACE_CString strAskAmount(rawInvestorRec.askAgreementAmount, sizeof ( rawInvestorRec.askAgreementAmount ));
        ACE_CString strBidVolume(rawInvestorRec.bidAgreementVolume, sizeof ( rawInvestorRec.bidAgreementVolume ));
        ACE_CString strBidAmount(rawInvestorRec.bidAgreementAmount, sizeof ( rawInvestorRec.bidAgreementAmount ));
        investor.askVolume = ::atof(strAskVolume.c_str());
        investor.askAmount = ::atof(strAskAmount.c_str());
        investor.bidVolume = ::atof(strBidVolume.c_str());
        investor.bidAmount = ::atof(strBidAmount.c_str());

        char buf[INVESTOR_SIZE];
        memcpy(buf, &investor, INVESTOR_SIZE);
        sendPacket(ACE_CString(buf, INVESTOR_SIZE), PACKET_INVESTOR, EXCHANGE_KSE);
//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleInvestor] changedStockCode:[%s]\tinvestorType:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , changedStockCode.c_str() , investorType.c_str() , result ));

    }
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleOpenInterestVolume(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_OPEN_INTEREST_VOLUME_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleOpenInterestVolume] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_OPEN_INTEREST_VOLUME_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_OPEN_INTEREST_VOLUME_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionOpenInterestVolumeRecord oiRec;
    ::memset(&oiRec, 0, sizeof(ExturePlusKospi200OptionOpenInterestVolumeRecord));
    ::memcpy(&oiRec, packet.c_str(), packet.length());

    ACE_CString stockCode(oiRec.stockCode, sizeof ( oiRec.stockCode ));
    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleOpenInterestVolume] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        openInterestMap_.rebind(stockCode, oiRec);
    }
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleMaster(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INFO_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INFO_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INFO_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionStockInfoRecord infoRec;
    ::memset(&infoRec, 0, sizeof(ExturePlusKospi200OptionStockInfoRecord));
    ::memcpy(&infoRec, packet.c_str(), packet.length());

#if(0)
printExturePlusKospi200OptionStockInfoRecord(infoRec);
#endif

    ACE_CString stockCode(infoRec.stockCode, sizeof ( infoRec.stockCode ));

    int result = 0;
    // 마지막 레코드가 999999999999 인 경우에는 처리하지 않는다.
    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return ( result );
    }
    else
    {
        ACE_Map_Manager < ACE_CString , ACE_CString , ACE_Null_Mutex > masterMap;
        char tempBuf[128];
        ::memset(tempBuf, 0, sizeof ( tempBuf ));

        // MASTER_SYMBOL
        masterMap.bind(MASTER_SYMBOL, stockCode);

        // MASTER_ABBR_SYMBOL
        ACE_CString abbrSymbol(getAbbrSymbol(stockCode));
        masterMap.bind(MASTER_ABBR_SYMBOL, abbrSymbol);

        // MASTER_NAME
        ACE_CString name(infoRec.stockNameKor, sizeof ( infoRec.stockNameKor ));
        masterMap.bind(MASTER_NAME, trim(name));

        // MASTER_EXCHANGE
        ACE_CString exchange(EXCHANGE_KSE_STRING);
        masterMap.bind(MASTER_EXCHANGE, exchange);

        // MASTER_SYMBOL_TYPE
        ACE_CString symbolType(SYMBOL_OPTION_STRING);
        masterMap.bind(MASTER_SYMBOL_TYPE, symbolType);

        // MASTER_SYMBOL_SUBTYPE
        // 기존에는 004 옵션종류 라는 독립된 컬럼값으로 구분했으나, 신스펙에는 없음
        // 종목코드를 통해 분류해야 함
        ACE_CString symbolSubType = getOptionType(stockCode);
        masterMap.bind(MASTER_SYMBOL_SUBTYPE, symbolSubType);

        // MASTER_OPTION_TYPE
        // 기존에는 004 옵션종류 라는 독립된 컬럼값으로 구분했으나, 신스펙에는 없음
        // 종목코드를 통해 분류해야 함
        ACE_CString optionType = getOptionType(stockCode);
        masterMap.bind(MASTER_OPTION_TYPE, optionType);

        // MASTER_EXERCISE_TYPE
        ACE_CString exerciseType = getExerciseType(ACE_CString(infoRec.exerciseTypeCode, sizeof ( infoRec.exerciseTypeCode )));
        masterMap.bind(MASTER_OPTION_TYPE, exerciseType);

        // MASTER_EXPIRATION_MONTH
        // 기존 006 만기년월 컬럼이 삭제되고, 신스펙의 028 만기일자 컬럼으로 사용
        // 기존에 연월까지만 전송하므로 6 바이트만 자르고 버림
        ACE_CString expirationMonth(infoRec.expireDate, 6);
        masterMap.bind(MASTER_EXPIRATION_MONTH, expirationMonth);


#if(0)
        ACE_CString strExercisePrice(infoRec.exercisePrice, 11);
        int exercisePrice = ::atoi(strExercisePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", exercisePrice);
        masterMap.bind(MASTER_EXERCISE_PRICE, tempBuf);
#endif

#if(1)
		//
		ACE_CString exercisePrice(infoRec.exercisePrice, sizeof ( infoRec.exercisePrice ));
		double exerciseprice = ::atof(exercisePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", exerciseprice * 100.0);
        masterMap.bind(MASTER_EXERCISE_PRICE, tempBuf);
#endif

        ACE_CString registerDate(infoRec.listingDate, sizeof ( infoRec.listingDate ));
        masterMap.bind(MASTER_REGISTER_DATE, registerDate);

        // MASTER_LAST_TRADE_DATE
        ACE_CString lastTradeDate(infoRec.lastTradeDate, sizeof ( infoRec.lastTradeDate ));
        masterMap.bind(MASTER_LAST_TRADE_DATE, lastTradeDate);

#if(0)
        // MASTER_STD_PRICE(10, 2)
        ACE_CString strStdPrice(infoRec.standardPrice, sizeof ( infoRec.standardPrice ));
        int stdPrice = ::atoi(strStdPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", stdPrice);
        masterMap.bind(MASTER_STD_PRICE, tempBuf);
#endif

#if(0)
        // MASTER_YDAY_CLOSE
        ACE_CString strYdayClose(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
        int ydayClose = ::atoi(strYdayClose.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", ydayClose);
        masterMap.bind(MASTER_YDAY_CLOSE, tempBuf);
#endif

#if(0)
        // MASTER_YDAY_OPEN_INTEREST(10, 0)
        ACE_CString strYdayOpenInterest(infoRec.ydayOpenInterest, sizeof ( infoRec.ydayOpenInterest ));
        int ydayOpenInterest = ::atoi(strYdayOpenInterest.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", ydayOpenInterest);
        masterMap.bind(MASTER_YDAY_OPEN_INTEREST, tempBuf);
#endif

        // MASTER_YDAY_VOLUME(12, 0)
        ACE_CString strYdayVolume(infoRec.ydayTradeVolume, sizeof ( infoRec.ydayTradeVolume ));
        int ydayVolume = ::atoi(strYdayVolume.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", ydayVolume);
        masterMap.bind(MASTER_YDAY_VOLUME, tempBuf);

        // MASTER_YDAY_AMOUNT (전일거래대금 단위 원)
        ACE_CString strYdayAmount(infoRec.ydayTradeAmount, sizeof ( infoRec.ydayTradeAmount ));
        double ydayAmount = ::atof(strYdayAmount.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%f", ydayAmount);
        masterMap.bind(MASTER_YDAY_AMOUNT, tempBuf);

        // MASTER_SESSION_DATE
        ACE_CString sessionDate(infoRec.hireDate, sizeof ( infoRec.hireDate ));
        masterMap.bind(MASTER_SESSION_DATE, sessionDate);

        // MASTER_ENG_NAME
        // DB 컬럼이 30 바이트이므로 30 바이트에서 자름
        ACE_CString engName(infoRec.stockNameEng, 30);
        masterMap.bind(MASTER_ENG_NAME, engName);

        // MASTER_SURVIVAL_DAYS
        // 잔존일수
        ACE_CString strSurvivalDays(infoRec.remainDateCount, sizeof ( infoRec.remainDateCount ));
        int survivalDays = ::atoi(strSurvivalDays.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", survivalDays);
        masterMap.bind(MASTER_SURVIVAL_DAYS, tempBuf);

//        // MASTER_YDAY_CLOSE_TYPE
//        ACE_CString ydayCloseType = getYdayCloseType(ACE_CString(infoRec.ydayClosePriceClassCode, sizeof ( infoRec.ydayClosePriceClassCode )));
//        masterMap.bind(MASTER_YDAY_CLOSE_TYPE, ydayCloseType);

        // MASTER_THEORIC_PRICE_SETTLE    // 이론가(9, 6)
        // 기존에는 x 100 되어 있으므로 소수점 2자리까지만 처리함 9(9)V(6)
        ACE_CString strTheoricPriceSettle(infoRec.theoreticalPriceSettlement, 11);
        int theoricPriceSettle = ::atoi(strTheoricPriceSettle.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", theoricPriceSettle);
        masterMap.bind(MASTER_THEORIC_PRICE_SETTLE, tempBuf);

#if(0)
        // MASTER_YDAY_HIGH_PRICE(10, 2)    
        ACE_CString strYdayHighPrice(infoRec.ydayHighPrice, sizeof ( infoRec.ydayHighPrice ));
        int ydayHighPrice = ::atoi(strYdayHighPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", ydayHighPrice);
        masterMap.bind(MASTER_YDAY_HIGH_PRICE, tempBuf);
#endif

#if(0)
        // MASTER_YDAY_LOW_PRICE(10, 2)
        ACE_CString strYdayLowPrice(infoRec.ydayLowPrice, sizeof ( infoRec.ydayLowPrice ));
        int ydayLowPrice = ::atoi(strYdayLowPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", ydayLowPrice);
        masterMap.bind(MASTER_YDAY_LOW_PRICE, tempBuf);
#endif

#if(0)
        // MASTER_CD_RATE(3, 3)
        ACE_CString strCdRate(infoRec.cdRate, sizeof ( infoRec.cdRate ));
        int cdRate = ::atoi(strCdRate.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", cdRate);
        masterMap.bind(MASTER_CD_RATE, tempBuf);
#endif

        // MASTER_YEAR_HIGHEST_DATE
        ACE_CString yearHighestDate(infoRec.highestPriceDateWithinYear, sizeof ( infoRec.highestPriceDateWithinYear ));
        masterMap.bind(MASTER_YEAR_HIGHEST_DATE, yearHighestDate);

#if(0)
        // MASTER_YEAR_HIGHEST_PRICE(10, 2)
        ACE_CString strYearHighestPrice(infoRec.highestPriceWithinYear, sizeof ( infoRec.highestPriceWithinYear ));
        int yearHighestPrice = ::atoi(strYearHighestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", yearHighestPrice);
        masterMap.bind(MASTER_YEAR_HIGHEST_PRICE, tempBuf);
#endif

        // MASTER_YEAR_LOWEST_DATE
        ACE_CString yearLowestDate(infoRec.lowestPriceDateWithinYear, sizeof ( infoRec.lowestPriceDateWithinYear ));
        masterMap.bind(MASTER_YEAR_LOWEST_DATE, yearLowestDate);

#if(0)
        // MASTER_YEAR_LOWEST_PRICE(10, 2)
        ACE_CString strYearLowestPrice(infoRec.lowestPriceWithinYear, sizeof ( infoRec.lowestPriceWithinYear ));
        int yearLowestPrice = ::atoi(strYearLowestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", yearLowestPrice);
        masterMap.bind(MASTER_YEAR_LOWEST_PRICE, tempBuf);
#endif

        // MASTER_HIGHEST_PRICE_DATE
        ACE_CString highestPriceDate(infoRec.highestPriceDateWithinListing, sizeof ( infoRec.highestPriceDateWithinListing ));
        masterMap.bind(MASTER_HIGHEST_PRICE_DATE, highestPriceDate);
#if(0)
        // MASTER_HIGHEST_PRICE(10, 2)
        ACE_CString strHighestPrice(infoRec.highestPriceWithinListing, sizeof ( infoRec.highestPriceWithinListing ));
        int highestPrice = ::atoi(strHighestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", highestPrice);
        masterMap.bind(MASTER_HIGHEST_PRICE, tempBuf);
#endif

        // MASTER_LOWEST_PRICE_DATE
        ACE_CString lowestPriceDate(infoRec.lowestPriceDateWithinListing, sizeof ( infoRec.lowestPriceDateWithinListing ));
        masterMap.bind(MASTER_LOWEST_PRICE_DATE, lowestPriceDate);

#if(0)
        // MASTER_LOWEST_PRICE(10, 2)
        ACE_CString strLowestPrice(infoRec.lowestPriceWithinListing, sizeof ( infoRec.lowestPriceWithinListing ));
        int lowestPrice = ::atoi(strLowestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", lowestPrice);
        masterMap.bind(MASTER_LOWEST_PRICE, tempBuf);
#endif


#if(0)
        ACE_CString strIv(infoRec.intrinsicVolatility, sizeof ( infoRec.intrinsicVolatility ));
        int iv = ::atoi(strIv.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", iv);
        masterMap.bind(MASTER_IV, tempBuf);
#endif

#if(1)
		//
		ACE_CString intrinsicVolatility(infoRec.intrinsicVolatility, sizeof ( infoRec.intrinsicVolatility ));
		double intrinsicvolatility = ::atof(intrinsicVolatility.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", intrinsicvolatility * 1000.0);
        masterMap.bind(MASTER_IV, tempBuf);
#endif

        // MASTER_SUBSTITUE_PRICE // 대용가 ==> UDP 스펙에 대용가 컬럼이 없음
        int substituePrice = getSubstitutePrice();
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", substituePrice);
        masterMap.bind(MASTER_SUBSTITUE_PRICE, tempBuf);

        // 2014.11.28 모의투자 지원을 위해 추가함
        // 종목단축코드(앞뒤삭제 없는전체)
        ACE_CString abbrSymbolFull(infoRec.abbrStockCode, sizeof ( infoRec.abbrStockCode ));
        masterMap.bind(MASTER_ABBR_SYMBOL_FULL, abbrSymbolFull);

        // 결재월번호
        // 001 -> 1 로 변경한다.
        ACE_CString strMonthProductClassCode(infoRec.monthProductClassCode, sizeof ( infoRec.monthProductClassCode ));
        int monthProductClassCode = ::atoi(strMonthProductClassCode.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", monthProductClassCode);
        masterMap.bind(MASTER_SETTLEMENT_MONTH_NUMBER, tempBuf);

        // 만기일자
        ACE_CString expireDate(infoRec.expireDate, sizeof ( infoRec.expireDate ));
        masterMap.bind(MASTER_EXPIRE_DATE, expireDate);


#if(0)
        ACE_CString strTradeUnit(infoRec.tradeUnit, 9);
        int tradeUnit = ::atoi(strTradeUnit.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", tradeUnit);
        masterMap.bind(MASTER_TRADE_UNIT, tempBuf);
#endif

        // 거래승수
        // 소수점 절삭
        ACE_CString strTradeMultiplier(infoRec.tradeMultiplier, 13);
        int tradeMultiplier = ::atoi(strTradeMultiplier.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", tradeMultiplier);
        masterMap.bind(MASTER_TRADING_MULTIPLIER, tempBuf);

        // 거래정지여부
        ACE_CString isTradeStop(infoRec.isTradeStop, sizeof ( infoRec.isTradeStop ));
        masterMap.bind(MASTER_SUSPENSION, getSuspensionType(isTradeStop));

        // ATM 구분코드
        ACE_CString ATMClassCode(infoRec.ATMClassCode, sizeof ( infoRec.ATMClassCode ));
        masterMap.bind(MASTER_ATM_TYPE, getATMCode(ATMClassCode));

        // 최종거래일여부(Y,N)
        ACE_CString isLastTradeDate(infoRec.isLastTradeDate, sizeof ( infoRec.isLastTradeDate ));
        masterMap.bind(MASTER_LAST_TRADING_DATE_CODE, isLastTradeDate);

        // for debug
        ACE_CString strIsHoliday(infoRec.isHoliday, sizeof ( infoRec.isHoliday ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tstrIsHoliday:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , strIsHoliday.c_str() ));

        ACE_CString isRealTimePriceLimit(infoRec.isRealTimePriceLimit, sizeof ( infoRec.isRealTimePriceLimit ));
        masterMap.bind(MASTER_IS_REAL_TIME_PRICE_LIMIT, isRealTimePriceLimit);


		ACE_CString signRealTimeUpperLimitPriceRange;
		if(infoRec.realTimeUpperLimitPriceRange[0]=='0') signRealTimeUpperLimitPriceRange = "+";
		else signRealTimeUpperLimitPriceRange = "-";

        ACE_CString signRealTimeLowerLimitPriceRange;
		if(infoRec.realTimeLowerLimitPriceRange[0]=='0') signRealTimeLowerLimitPriceRange = "+";
		else signRealTimeLowerLimitPriceRange = "-";

#if(0)
        ACE_CString realTimeUpperLimitPriceRange(infoRec.realTimeUpperLimitPriceRange, sizeof ( infoRec.realTimeUpperLimitPriceRange ));
        ACE_CString strRealTimeUpperLimitPriceRangeSigned;
        strRealTimeUpperLimitPriceRangeSigned = getSign(signRealTimeUpperLimitPriceRange) + realTimeUpperLimitPriceRange;

        int realTimeUpperLimitPriceRangeSigned = ::atoi(strRealTimeUpperLimitPriceRangeSigned.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", realTimeUpperLimitPriceRangeSigned);
        masterMap.bind(MASTER_REAL_TIME_UPPER_LIMIT_PRICE_RANGE, tempBuf);
#endif


#if(1)
		//
		ACE_CString realTimeUpperLimitPriceRange(infoRec.realTimeUpperLimitPriceRange, sizeof ( infoRec.realTimeUpperLimitPriceRange ));
		double realtimeupperlimitpricerange = ::atof(realTimeUpperLimitPriceRange.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", realtimeupperlimitpricerange * 100.0);
        masterMap.bind(MASTER_REAL_TIME_UPPER_LIMIT_PRICE_RANGE, tempBuf);
#endif


#if(0)
        ACE_CString realTimeLowerLimitPriceRange(infoRec.realTimeLowerLimitPriceRange, sizeof ( infoRec.realTimeLowerLimitPriceRange ));
        ACE_CString strRealTimeLowerLimitPriceRangeSigned;
        strRealTimeLowerLimitPriceRangeSigned = getSign(signRealTimeLowerLimitPriceRange) + realTimeLowerLimitPriceRange;

        int realTimeLowerLimitPriceRangeSigned = ::atoi(strRealTimeLowerLimitPriceRangeSigned.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", realTimeLowerLimitPriceRangeSigned);
        masterMap.bind(MASTER_REAL_TIME_LOWER_LIMIT_PRICE_RANGE, tempBuf);
#endif


#if(1)
		//
		ACE_CString realTimeLowerLimitPriceRange(infoRec.realTimeLowerLimitPriceRange, sizeof ( infoRec.realTimeLowerLimitPriceRange ));
		double realtimelowerlimitpricerange = ::atof(realTimeLowerLimitPriceRange.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", realtimelowerlimitpricerange * 100.0);
        masterMap.bind(MASTER_REAL_TIME_LOWER_LIMIT_PRICE_RANGE, tempBuf);
#endif

//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tisRealTimePriceLimit:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , isRealTimePriceLimit.c_str() ));
//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tsignRealTimeUpperLimitPriceRange:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , signRealTimeUpperLimitPriceRange.c_str() ));
//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\trealTimeUpperLimitPriceRange:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , realTimeUpperLimitPriceRange.c_str() ));
//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tsignRealTimeLowerLimitPriceRange:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , signRealTimeLowerLimitPriceRange.c_str() ));
//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\trealTimeLowerLimitPriceRange:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , realTimeLowerLimitPriceRange.c_str() ));

		ACE_CString price_limit_1st_upper_limit_price_sign;
		ACE_CString price_limit_1st_lower_limit_price_sign;
		ACE_CString price_limit_2nd_upper_limit_price_sign;
        ACE_CString price_limit_2nd_lower_limit_price_sign;
		ACE_CString price_limit_3rd_upper_limit_price_sign;
		ACE_CString price_limit_3rd_lower_limit_price_sign;

        ACE_CString price_limit_1st_upper_limit_price(infoRec.price_limit_1st_upper_limit_price, sizeof ( infoRec.price_limit_1st_upper_limit_price ));
        ACE_CString price_limit_1st_lower_limit_price(infoRec.price_limit_1st_lower_limit_price, sizeof ( infoRec.price_limit_1st_lower_limit_price ));
        ACE_CString price_limit_2nd_upper_limit_price(infoRec.price_limit_2nd_upper_limit_price, sizeof ( infoRec.price_limit_2nd_upper_limit_price ));
        ACE_CString price_limit_2nd_lower_limit_price(infoRec.price_limit_2nd_lower_limit_price, sizeof ( infoRec.price_limit_2nd_lower_limit_price ));
        ACE_CString price_limit_3rd_upper_limit_price(infoRec.price_limit_3rd_upper_limit_price, sizeof ( infoRec.price_limit_3rd_upper_limit_price ));
        ACE_CString price_limit_3rd_lower_limit_price(infoRec.price_limit_3rd_lower_limit_price, sizeof ( infoRec.price_limit_3rd_lower_limit_price ));

		if(infoRec.price_limit_1st_upper_limit_price[0]=='0') price_limit_1st_upper_limit_price_sign = "+";
		else price_limit_1st_upper_limit_price_sign = "-";

		if(infoRec.price_limit_1st_lower_limit_price[0]=='0') price_limit_1st_lower_limit_price_sign = "+";
		else price_limit_1st_lower_limit_price_sign = "-";

		if(infoRec.price_limit_2nd_lower_limit_price[0]=='0') price_limit_2nd_lower_limit_price_sign = "+";
		else price_limit_2nd_lower_limit_price_sign = "-";

		if(infoRec.price_limit_2nd_upper_limit_price[0]=='0') price_limit_2nd_upper_limit_price_sign = "+";
		else price_limit_2nd_upper_limit_price_sign = "-";

		if(infoRec.price_limit_3rd_upper_limit_price[0]=='0') price_limit_3rd_upper_limit_price_sign = "+";
		else price_limit_3rd_upper_limit_price_sign = "-";

		if(infoRec.price_limit_3rd_lower_limit_price[0]=='0') price_limit_3rd_lower_limit_price_sign = "+";
		else price_limit_3rd_lower_limit_price_sign = "-";

        ACE_CString price_limit_expansion_direction_code(infoRec.price_limit_expansion_direction_code, sizeof ( infoRec.price_limit_expansion_direction_code ));
        ACE_CString price_limit_final_step(infoRec.price_limit_final_step, sizeof ( infoRec.price_limit_final_step ));

        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_expansion_direction_code:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_expansion_direction_code.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_final_step:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_final_step.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_upper_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_upper_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_upper_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_lower_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_lower_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_lower_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_upper_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_upper_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_upper_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_lower_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_lower_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_lower_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_upper_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_upper_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_upper_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_lower_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_lower_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_lower_limit_price.c_str() ));

        /*
         * 2015.05.19
         * 06.15 가격제한폭 제도 변경에 따라, 지수선물, 지수옵션은 3단계로 변경된다.
         * 기존 시스템 호환을 위해 1단계 상한값은 MASTER_UP_LIMIT 으로 보내고
         * 다시 각 단계별 값을 나눠보낸다.
         */

        masterMap.bind(MASTER_PRICE_LIMIT_EXPANSION_TYPE, price_limit_expansion_direction_code);

        int limit_final_step = parseInt(price_limit_final_step, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", limit_final_step);
        masterMap.bind(MASTER_PRICE_LIMIT_FINAL_STEP, tempBuf);

#if(0)
        price_limit_1st_upper_limit_price = price_limit_1st_upper_limit_price_sign + price_limit_1st_upper_limit_price;
        price_limit_1st_upper_limit_price = trim_ACE(price_limit_1st_upper_limit_price);
        int upLimit1 = parseInt(price_limit_1st_upper_limit_price, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", upLimit1);
        masterMap.bind(MASTER_UP_LIMIT, tempBuf);
        masterMap.bind(MASTER_UP_LIMIT_STEP_1, tempBuf);

        price_limit_2nd_upper_limit_price = price_limit_2nd_upper_limit_price_sign + price_limit_2nd_upper_limit_price;
        price_limit_2nd_upper_limit_price = trim_ACE(price_limit_2nd_upper_limit_price);
        int upLimit2 = parseInt(price_limit_2nd_upper_limit_price, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", upLimit2);
        masterMap.bind(MASTER_UP_LIMIT_STEP_2, tempBuf);

        price_limit_3rd_upper_limit_price = price_limit_3rd_upper_limit_price_sign + price_limit_3rd_upper_limit_price;
        price_limit_3rd_upper_limit_price = trim_ACE(price_limit_3rd_upper_limit_price);
        int upLimit3 = parseInt(price_limit_3rd_upper_limit_price, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", upLimit3);
        masterMap.bind(MASTER_UP_LIMIT_STEP_3, tempBuf);

        price_limit_1st_lower_limit_price = price_limit_1st_lower_limit_price_sign + price_limit_1st_lower_limit_price;
        price_limit_1st_lower_limit_price = trim_ACE(price_limit_1st_lower_limit_price);
        int downLimit1 = parseInt(price_limit_1st_lower_limit_price, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", downLimit1);
        masterMap.bind(MASTER_DOWN_LIMIT, tempBuf);
        masterMap.bind(MASTER_DOWN_LIMIT_STEP_1, tempBuf);

        price_limit_2nd_lower_limit_price = price_limit_2nd_lower_limit_price_sign + price_limit_2nd_lower_limit_price;
        price_limit_2nd_lower_limit_price = trim_ACE(price_limit_2nd_lower_limit_price);
        int downLimit2 = parseInt(price_limit_2nd_lower_limit_price, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", downLimit2);
        masterMap.bind(MASTER_DOWN_LIMIT_STEP_2, tempBuf);

        price_limit_3rd_lower_limit_price = price_limit_3rd_lower_limit_price_sign + price_limit_3rd_lower_limit_price;
        price_limit_3rd_lower_limit_price = trim_ACE(price_limit_3rd_lower_limit_price);
        int downLimit3 = parseInt(price_limit_3rd_lower_limit_price, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", downLimit3);
        masterMap.bind(MASTER_DOWN_LIMIT_STEP_3, tempBuf);
#endif

        /*
         * 2015.11.17 dong
         * 모의투자 시스템 요청으로 기초자산종목코드 추가함
         */
        // 기초자산종목코드
        ACE_CString baseAssetStockCode(infoRec.baseAssetStockCode, sizeof ( infoRec.baseAssetStockCode ));
        masterMap.bind(MASTER_BASE_ASSET_SYMBOL, baseAssetStockCode);

#if(0)
        // 기초자산종가
        ACE_CString strBaseAssetClosePrice(infoRec.baseAssetClosePrice, sizeof ( infoRec.baseAssetClosePrice ));
        int baseAssetClosePrice = ::atoi(strBaseAssetClosePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", baseAssetClosePrice);
        masterMap.bind(MASTER_BASE_ASSET_CLOSE_PRICE, tempBuf);
#endif

        // 2018.11.23
        // 기초자산시장ID(기초자산시장ID는 기초자산이 KRX에 상장된 경우에만 채워짐.)
        // 일단 출력만 하고, 종목정보 MAP 에는 등록하지 않는다. 추후 요청이 있을때 추가
        ACE_CString underlyingAssetMarketID(infoRec.underlyingAssetMarketID, sizeof ( infoRec.underlyingAssetMarketID ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tunderlyingAssetMarketID:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , underlyingAssetMarketID.c_str() ));

#if(0)
        // 상한수량
        ACE_CString upperLimitQuantity(infoRec.upperLimitQuantity, sizeof ( infoRec.upperLimitQuantity ));
        masterMap.bind(MASTER_UPPER_LIMIT_QUANTITY, upperLimitQuantity);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tupperLimitQuantity:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , upperLimitQuantity.c_str() ));
#endif

#if(0)
        // 하한수량
        ACE_CString lowerLimitQuantity(infoRec.lowerLimitQuantity, sizeof ( infoRec.lowerLimitQuantity ));
        masterMap.bind(MASTER_LOWER_LIMIT_QUANTITY, lowerLimitQuantity);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tlowerLimitQuantity:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , lowerLimitQuantity.c_str() ));
#endif

#if(0)
        // 협의대량매매상한수량
        ACE_CString upperLimitQuantityForBlockTrade(infoRec.upperLimitQuantityForBlockTrade, sizeof ( infoRec.upperLimitQuantityForBlockTrade ));
        masterMap.bind(MASTER_UPPER_LIMIT_QUANTITY_FOR_BLOCK_TRADE, upperLimitQuantityForBlockTrade);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tupperLimitQuantityForBlockTrade:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , upperLimitQuantityForBlockTrade.c_str() ));
#endif

#if(0)
        // 협의대량매매하한수량
        ACE_CString lowerLimitQuantityForBlockTrade(infoRec.lowerLimitQuantityForBlockTrade, sizeof ( infoRec.lowerLimitQuantityForBlockTrade ));
        masterMap.bind(MASTER_LOWER_LIMIT_QUANTITY_FOR_BLOCK_TRADE, lowerLimitQuantityForBlockTrade);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tlowerLimitQuantityForBlockTrade:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , lowerLimitQuantityForBlockTrade.c_str() ));
#endif

        // 휴면여부
        ACE_CString isSuspendedStocks(infoRec.isSuspendedStocks, sizeof ( infoRec.isSuspendedStocks ));
        masterMap.bind(MASTER_IS_SUSPENDED_STOCKS, isSuspendedStocks);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tisSuspendedStocks:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , isSuspendedStocks.c_str() ));

        // 휴면지정일자
        ACE_CString designationDateForSuspendedStocks(infoRec.designationDateForSuspendedStocks, sizeof ( infoRec.designationDateForSuspendedStocks ));
        masterMap.bind(MASTER_DESIGNATION_DATE_FOR_SUSPENDED_STOCKS, designationDateForSuspendedStocks);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tdesignationDateForSuspendedStocks:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , designationDateForSuspendedStocks.c_str() ));








#if(1)
		ACE_CString strStdPrice(infoRec.standardPrice, sizeof ( infoRec.standardPrice ));
		double strstdprice = ::atof(strStdPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strstdprice * 100.0);
        masterMap.bind(MASTER_STD_PRICE, tempBuf);
#endif
#if(1)
		ACE_CString strYdayClose(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
		double strydayclose = ::atof(strYdayClose.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydayclose * 100.0);
        masterMap.bind(MASTER_YDAY_CLOSE, tempBuf);
#endif
#if(1)
		//
		ACE_CString strYdayOpenInterest(infoRec.ydayOpenInterest, sizeof ( infoRec.ydayOpenInterest ));
		double strydayopeninterest = ::atof(strYdayOpenInterest.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydayopeninterest * 100.0);
        masterMap.bind(MASTER_YDAY_OPEN_INTEREST, tempBuf);
#endif
#if(0)
		ACE_CString strTheoricPriceStand(infoRec.theoreticalPriceStandard, sizeof ( infoRec.theoreticalPriceStandard ) - 4);
		double strtheoricpricestand = ::atof(strTheoricPriceStand.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strtheoricpricestand * 100.0);
        masterMap.bind(MASTER_THEORIC_PRICE_STAND, tempBuf);
#endif
#if(1)
		//
		ACE_CString strCdRate(infoRec.cdRate, sizeof ( infoRec.cdRate ));
		double strcdrate = ::atof(strCdRate.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strcdrate * 1000.0);
        masterMap.bind(MASTER_CD_RATE, tempBuf);
#endif
#if(0)
		ACE_CString strYdaySettlePrice(infoRec.ydaySettlementPrice, sizeof ( infoRec.ydaySettlementPrice ) - 6);
		double strydaysettleprice = ::atof(strYdaySettlePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydaysettleprice * 100.0);
        masterMap.bind(MASTER_YDAY_SETTLE_PRICE, tempBuf);
#endif
#if(1)
		//
		ACE_CString strYdayHighPrice(infoRec.ydayHighPrice, sizeof ( infoRec.ydayHighPrice ));
		double strydayhighprice = ::atof(strYdayHighPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydayhighprice * 100.0);
        masterMap.bind(MASTER_YDAY_HIGH_PRICE, tempBuf);
#endif
#if(1)
		//
		ACE_CString strYdayLowPrice(infoRec.ydayLowPrice, sizeof ( infoRec.ydayLowPrice ));
		double strydaylowprice = ::atof(strYdayLowPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydaylowprice * 100.0);
        masterMap.bind(MASTER_YDAY_LOW_PRICE, tempBuf);
#endif
#if(1)
		//
		ACE_CString strYearHighestPrice(infoRec.highestPriceWithinYear, sizeof ( infoRec.highestPriceWithinYear ));
		double stryearhighestprice = ::atof(strYearHighestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", stryearhighestprice * 100.0);
        masterMap.bind(MASTER_YEAR_HIGHEST_PRICE, tempBuf);
#endif
#if(1)
		//
		ACE_CString strYearLowestPrice(infoRec.lowestPriceWithinYear, sizeof ( infoRec.lowestPriceWithinYear ));
		double stryearlowestprice = ::atof(strYearLowestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", stryearlowestprice * 100.0);
        masterMap.bind(MASTER_YEAR_LOWEST_PRICE, tempBuf);
#endif
#if(1)
		//
		ACE_CString strHighestPrice(infoRec.highestPriceWithinListing, sizeof ( infoRec.highestPriceWithinListing ));
		double strhighestprice = ::atof(strHighestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strhighestprice * 100.0);
        masterMap.bind(MASTER_HIGHEST_PRICE, tempBuf);
#endif

#if(1)
		//
		ACE_CString strLowestPrice(infoRec.lowestPriceWithinListing, sizeof ( infoRec.lowestPriceWithinListing ));
		double strlowestprice = ::atof(strLowestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strlowestprice * 100.0);
        masterMap.bind(MASTER_LOWEST_PRICE, tempBuf);
#endif
#if(1)
        ACE_CString strTradeUnit(infoRec.tradeUnit, sizeof(infoRec.tradeUnit));
        int tradeUnit = ::atoi(strTradeUnit.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", tradeUnit / 1000);
        masterMap.bind(MASTER_TRADE_UNIT, tempBuf);
#endif
#if(1)
        price_limit_1st_upper_limit_price = price_limit_1st_upper_limit_price_sign + price_limit_1st_upper_limit_price;
        price_limit_1st_upper_limit_price = trim_ACE(price_limit_1st_upper_limit_price);

		double upLimit1 = ::atof(price_limit_1st_upper_limit_price.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", upLimit1 * 100.0);
        masterMap.bind(MASTER_UP_LIMIT, tempBuf);
        masterMap.bind(MASTER_UP_LIMIT_STEP_1, tempBuf);

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\t,MASTER_UP_LIMIT_STEP_1:[%s]\n" , getCurrentTimestamp().c_str() , 
			stockCode.c_str() , tempBuf ));

        price_limit_2nd_upper_limit_price = price_limit_2nd_upper_limit_price_sign + price_limit_2nd_upper_limit_price;
        price_limit_2nd_upper_limit_price = trim_ACE(price_limit_2nd_upper_limit_price);

		double upLimit2 = ::atof(price_limit_2nd_upper_limit_price.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", upLimit2 * 100.0);
        masterMap.bind(MASTER_UP_LIMIT_STEP_2, tempBuf);

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\t,MASTER_UP_LIMIT_STEP_2:[%s]\n" , getCurrentTimestamp().c_str() , 
			stockCode.c_str() , tempBuf ));

        price_limit_3rd_upper_limit_price = price_limit_3rd_upper_limit_price_sign + price_limit_3rd_upper_limit_price;
        price_limit_3rd_upper_limit_price = trim_ACE(price_limit_3rd_upper_limit_price);

		double upLimit3 = ::atof(price_limit_3rd_upper_limit_price.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", upLimit3 * 100.0);
        masterMap.bind(MASTER_UP_LIMIT_STEP_3, tempBuf);

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\t,MASTER_UP_LIMIT_STEP_3:[%s]\n" , getCurrentTimestamp().c_str() , 
			stockCode.c_str() , tempBuf ));

        price_limit_1st_lower_limit_price = price_limit_1st_lower_limit_price_sign + price_limit_1st_lower_limit_price;
        price_limit_1st_lower_limit_price = trim_ACE(price_limit_1st_lower_limit_price);

		double downLimit1 = ::atof(price_limit_1st_lower_limit_price.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", downLimit1 * 100.0);
        masterMap.bind(MASTER_DOWN_LIMIT, tempBuf);
        masterMap.bind(MASTER_DOWN_LIMIT_STEP_1, tempBuf);

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\t,MASTER_DOWN_LIMIT_STEP_1:[%s]\n" , getCurrentTimestamp().c_str() , 
			stockCode.c_str() , tempBuf ));

        price_limit_2nd_lower_limit_price = price_limit_2nd_lower_limit_price_sign + price_limit_2nd_lower_limit_price;
        price_limit_2nd_lower_limit_price = trim_ACE(price_limit_2nd_lower_limit_price);

		double downLimit2 = ::atof(price_limit_2nd_lower_limit_price.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", downLimit2 * 100.0);
        masterMap.bind(MASTER_DOWN_LIMIT_STEP_2, tempBuf);

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\t,MASTER_DOWN_LIMIT_STEP_2:[%s]\n" , getCurrentTimestamp().c_str() , 
			stockCode.c_str() , tempBuf ));

        price_limit_3rd_lower_limit_price = price_limit_3rd_lower_limit_price_sign + price_limit_3rd_lower_limit_price;
        price_limit_3rd_lower_limit_price = trim_ACE(price_limit_3rd_lower_limit_price);

		double downLimit3 = ::atof(price_limit_3rd_lower_limit_price.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", downLimit3 * 100.0);
        masterMap.bind(MASTER_DOWN_LIMIT_STEP_3, tempBuf);

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\t,MASTER_DOWN_LIMIT_STEP_3:[%s]\n" , getCurrentTimestamp().c_str() , 
			stockCode.c_str() , tempBuf ));
#endif
#if(1)
		//
        ACE_CString strBaseAssetClosePrice(infoRec.baseAssetClosePrice, sizeof ( infoRec.baseAssetClosePrice ));
		double baseAssetClosePrice = ::atof(strBaseAssetClosePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", baseAssetClosePrice * 100.0);
        masterMap.bind(MASTER_BASE_ASSET_CLOSE_PRICE, tempBuf);
#endif
#if(1)
		//
	    ACE_CString lowerLimitQuantityForBlockTrade(infoRec.lowerLimitQuantityForBlockTrade, sizeof ( infoRec.lowerLimitQuantityForBlockTrade ));
	    int lowerlimitquantityforblocktrade = parseInt(lowerLimitQuantityForBlockTrade.c_str(), 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", lowerlimitquantityforblocktrade);
        masterMap.bind(MASTER_LOWER_LIMIT_QUANTITY_FOR_BLOCK_TRADE, tempBuf);
#endif


#if(1)
	    ACE_CString upperLimitQuantityForBlockTrade(infoRec.upperLimitQuantityForBlockTrade, sizeof ( infoRec.upperLimitQuantityForBlockTrade ));
	    int upperlimitquantityforblocktrade = parseInt(upperLimitQuantityForBlockTrade.c_str(), 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", upperlimitquantityforblocktrade);
        masterMap.bind(MASTER_UPPER_LIMIT_QUANTITY_FOR_BLOCK_TRADE, tempBuf);
#endif

#if(1)
		ACE_CString lowerLimitQuantity(infoRec.lowerLimitQuantity, sizeof ( infoRec.lowerLimitQuantity ));
		double lowerlimitquantity = ::atof(lowerLimitQuantity.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", lowerlimitquantity * 100.0);
        masterMap.bind(MASTER_LOWER_LIMIT_QUANTITY, tempBuf);
#endif

#if(1)
		ACE_CString upperLimitQuantity(infoRec.upperLimitQuantity, sizeof ( infoRec.upperLimitQuantity ));
		double upperlimitquantity = ::atof(lowerLimitQuantity.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", upperlimitquantity * 100.0);
        masterMap.bind(MASTER_UPPER_LIMIT_QUANTITY, tempBuf);
#endif





        // 체결, 호가등 다른 스펙에서는 8자리 코드로 처리하고 있음
        ACE_CString symbol = stockCode.substr(3, 8);

        // 마스터 재전송시 tradeMap_, openInterestMap_ 초기화
        tradeMap_.unbind(stockCode);
        openInterestMap_.unbind(stockCode);

        Trade tempTrade;
        ::memset(&tempTrade, 0, sizeof(Trade));
        ExturePlusKospi200OptionOpenInterestVolumeRecord tempOiRec;
        ::memset(&tempOiRec, 0, sizeof(ExturePlusKospi200OptionOpenInterestVolumeRecord));

        ACE_CString oldStockCode;
        ExturePlusKospi200OptionStockInfoRecord oldInfoRec;

        int resultBind = optionMasterMap_.rebind(stockCode, infoRec);
        resultBind = masterMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), infoRec, oldStockCode, oldInfoRec, ALLOCATOR::instance());

        ACE_CString resultStr(makeMaster (masterMap));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMaster] stockCode:[%s]\tresultStr:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , resultStr.c_str() ));

        result = sendPacket(makeMaster(masterMap), PACKET_MASTER, EXCHANGE_KSE);
    }
    return ( result );
}

int InternetKospi200OptionChannelProcessor::handleTradeMarginStandardPrice(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_TRADE_MARGIN_STANDARD_PRICE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleTradeMarginStandardPrice] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_TRADE_MARGIN_STANDARD_PRICE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_TRADE_MARGIN_STANDARD_PRICE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionTradeMarginStandardPriceRecord marginRec;
    ::memset(&marginRec, 0, sizeof(ExturePlusKospi200OptionTradeMarginStandardPriceRecord));
    ::memcpy(&marginRec, packet.c_str(), packet.length());
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleQuantityAllocation(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_QUANTITY_ALLOCATION_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleQuantityAllocation] Skip : %s, %d : EXTURE_PLUS_KOSPI_200_OPTION_QUANTITY_ALLOCATION_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_QUANTITY_ALLOCATION_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKospi200OptionQuantityAllocationRecord allocationRec;
    ACE_OS::memcpy(&allocationRec, packet.c_str(), packet.length());

    ACE_CString dataType(allocationRec.dataType, sizeof ( allocationRec.dataType ));
    ACE_CString issueCode(allocationRec.issueCode, sizeof ( allocationRec.issueCode ));
    ACE_CString issueSeqence(allocationRec.issueSeqence, sizeof ( allocationRec.issueSeqence ));
    ACE_CString boardID(allocationRec.boardID, sizeof ( allocationRec.boardID ));
    ACE_CString allocationStartEnd(allocationRec.allocationStartEnd, sizeof ( allocationRec.allocationStartEnd ));
    ACE_CString allocationTypeCode(allocationRec.allocationTypeCode, sizeof ( allocationRec.allocationTypeCode ));
    ACE_CString timeForAllocationEnd(allocationRec.timeForAllocationEnd, sizeof ( allocationRec.timeForAllocationEnd ));

    int result = 0;
    return result;
}

int InternetKospi200OptionChannelProcessor::handleRealTimeUpperLowerLimitPrice(const ACE_CString &packet)
{

    if ( EXTURE_PLUS_KOSPI_200_OPTION_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleRealTimeUpperLowerLimitPrice] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
        return 0;
    }

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleRealTimeUpperLowerLimitPrice] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    ExturePlusKospi200OptionRealTimeUpperLowerLimitPriceRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200OptionRealTimeUpperLowerLimitPriceRecord));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));

    ACE_CString strRealTimeUpperLimitPrice(rawRec.realTimeUpperLimitPrice, sizeof ( rawRec.realTimeUpperLimitPrice ));
    ACE_CString strRealTimeLowerLimitPrice(rawRec.realTimeLowerLimitPrice, sizeof ( rawRec.realTimeLowerLimitPrice ));
    double realTimeUpperLimitPrice = ::atof(strRealTimeUpperLimitPrice.c_str());
    double realTimeLowerLimitPrice = ::atof(strRealTimeLowerLimitPrice.c_str());

    RealTimeLimitPrice limitRec;
    ::memset(&limitRec, 0, sizeof(RealTimeLimitPrice));
    ::memcpy(&limitRec.symbol, issueCode.c_str(), issueCode.length());
    limitRec.registerDt = (int) ( ::time(0) );

    limitRec.isRealTimePriceLimit = rawRec.realTimePriceLimit[0];


    limitRec.realTimeUpperLimitPrice = realTimeUpperLimitPrice;
    limitRec.realTimeLowerLimitPrice = realTimeLowerLimitPrice;

#if(1)
limitRec.realTimeUpperLimitPrice = limitRec.realTimeUpperLimitPrice * 100;
limitRec.realTimeLowerLimitPrice = limitRec.realTimeLowerLimitPrice * 100;
#endif

    printPacketRealTimeLimitPrice(limitRec);

    char bufSendPacket[REAL_TIME_LIMIT_PRICE_SIZE];
    ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
    ::memcpy(&bufSendPacket, &limitRec, sizeof(RealTimeLimitPrice));

    int resultLimitRec = sendPacket(ACE_CString(bufSendPacket, REAL_TIME_LIMIT_PRICE_SIZE), PACKET_REAL_TIME_LIMIT_PRICE, EXCHANGE_KSE);

    return ( resultLimitRec );
}

ACE_CString InternetKospi200OptionChannelProcessor::getOptionType(const ACE_CString& raw)
{
    ACE_CString optionType(raw.substr(3, 1));

    ACE_CString result;
    if ( optionType == "2" )
    {
        result = "CALL";
    }
    else if ( optionType == "3" )
    {
        result = "PUT";
    }
    else
    {
        result = "";
    }
    return result;
}

ACE_CString InternetKospi200OptionChannelProcessor::getExerciseType(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "E" )
    {
        result = "유럽형";
    }
    else if ( raw == "A" )
    {
        result = "미국식";
    }
    else if ( raw == "Z" )
    {
        result = "기타";
    }
    else
    {
        result = "";
    }
    return result;
}

ACE_CString InternetKospi200OptionChannelProcessor::getYdayCloseType(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "1" )
    {
        result = "실세";
    }
    else if ( raw == "2" )
    {
        result = "기세";
    }
    else if ( raw == "3" )
    {
        result = "무거래";
    }
    else
    {
        result = "실세";    // 기존 인터넷 옵션 시세 구현부 참고
    }
    return result;
}

int InternetKospi200OptionChannelProcessor::getTradeUnit()
{
    int defaultTradeUnit = 1;
    return defaultTradeUnit;
}

int InternetKospi200OptionChannelProcessor::getSubstitutePrice()
{
    int defaultSubstitutePrice = 0;
    return defaultSubstitutePrice;
}

ACE_CString InternetKospi200OptionChannelProcessor::getAbbrSymbol(const ACE_CString& symbol)
{
    return symbol.substring(3, 8);
}

BYTE InternetKospi200OptionChannelProcessor::getMarketInTrade(const ACE_CString &sessionID)
{
    BYTE result = MARKET_IN;

    if ( ( sessionID == "00" ) || ( sessionID == "10" ) )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( ( sessionID == "11" ) || ( sessionID == "20" ) || ( sessionID == "21" ) || ( sessionID == "40" ) || ( sessionID == "80" ) )
    {
        result = MARKET_IN;
    }
    else if ( ( sessionID == "30" ) || ( sessionID == "90" ) || ( sessionID == "99" ) )
    {
        result = MARKET_END;
    }
    else
    {
        result = MARKET_IN;
    }
    return result;
}

int InternetKospi200OptionChannelProcessor::getUpDownInTrade(int prevValue, int currValue)
{
    if ( prevValue > currValue )
    {
        return UPDOWN_DOWN; // 하락
    }
    else if ( prevValue < currValue )
    {
        return UPDOWN_UP; // 상승
    }
    else
    {
        return UPDOWN_STATIONARY;  // 보합
    }
}

ACE_CString InternetKospi200OptionChannelProcessor::getSymbol(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "C" )   // 콜옵션
    {
        result = "KR4201000000";
    }
    else if ( raw == "P" )
    {
        result = "KR4301000000";
    }
    else
    {
        result = "";
    }
    return result;
}

const std::vector<ACE_CString>& InternetKospi200OptionChannelProcessor::getTradeTypeList()
{
    return tradeTypeList_;
}

void InternetKospi200OptionChannelProcessor::initTradeTypeList()
{
    return;
}

int InternetKospi200OptionChannelProcessor::handlePreMarketNegotiatedTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_PRE_MARKET_NEGOTIATED_TRADE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handlePreMarketNegotiatedTrade] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_PRE_MARKET_NEGOTIATED_TRADE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_PRE_MARKET_NEGOTIATED_TRADE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionPreMarketNegotiatedTradeRecord preTradeRec;
    ::memset(&preTradeRec, 0, sizeof(ExturePlusKospi200OptionPreMarketNegotiatedTradeRecord));
    ::memcpy(&preTradeRec, packet.c_str(), packet.length());

    ACE_CString stockCode(preTradeRec.stockCode, sizeof ( preTradeRec.stockCode ));
    ACE_CString tradePrice(preTradeRec.tradePrice, sizeof ( preTradeRec.tradePrice ));
    ACE_CString tradeVolume(preTradeRec.tradeVolume, sizeof ( preTradeRec.tradeVolume ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePreMarketNegotiatedTrade] stockCode:[%s]\ttradePrice:[%s]\ttradeVolume:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , tradePrice.c_str() , tradeVolume.c_str() ));
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleSensitivity(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_SENSITIVITY_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleSensitivity] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_SENSITIVITY_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_SENSITIVITY_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200OptionSensitivityRecord sensitivityRec;
    ::memset(&sensitivityRec, 0, sizeof(ExturePlusKospi200OptionSensitivityRecord));
    ::memcpy(&sensitivityRec, packet.c_str(), packet.length());

    ACE_CString dataType(sensitivityRec.dataType, sizeof ( sensitivityRec.dataType ));
    ACE_CString issueCode(sensitivityRec.issueCode, sizeof ( sensitivityRec.issueCode ));
    ACE_CString seq(sensitivityRec.seq, sizeof ( sensitivityRec.seq ));
    ACE_CString producedDate(sensitivityRec.producedDate, sizeof ( sensitivityRec.producedDate ));
    ACE_CString producedTime(sensitivityRec.producedTime, sizeof ( sensitivityRec.producedTime ));
    ACE_CString dataCategory(sensitivityRec.dataCategory, sizeof ( sensitivityRec.dataCategory ));
    ACE_CString underlyingAssetId(sensitivityRec.underlyingAssetId, sizeof ( sensitivityRec.underlyingAssetId ));
#if(0)
    ACE_CString sign00(sensitivityRec.sign00, sizeof ( sensitivityRec.sign00 ));
#endif
#if(1)
    ACE_CString sign00;
	if(sensitivityRec.sensitivityDelta[0]=='0') sign00 = "+";
	else sign00 = "-";
#endif


    ACE_CString sensitivityDelta(sensitivityRec.sensitivityDelta, sizeof ( sensitivityRec.sensitivityDelta ));

#if(0)
    ACE_CString sign01(sensitivityRec.sign01, sizeof ( sensitivityRec.sign01 ));
#endif
#if(1)
    ACE_CString sign01;
	if(sensitivityRec.sensitivityTheta[0]=='0') sign01 = "+";
	else sign01 = "-";
#endif


    ACE_CString sensitivityTheta(sensitivityRec.sensitivityTheta, sizeof ( sensitivityRec.sensitivityTheta ));

#if(0)
    ACE_CString sign02(sensitivityRec.sign02, sizeof ( sensitivityRec.sign02 ));
#endif
#if(1)
    ACE_CString sign02;
	if(sensitivityRec.sensitivityVega[0]=='0') sign02 = "+";
	else sign02 = "-";
#endif


    ACE_CString sensitivityVega(sensitivityRec.sensitivityVega, sizeof ( sensitivityRec.sensitivityVega ));

#if(0)
    ACE_CString sign03(sensitivityRec.sign03, sizeof ( sensitivityRec.sign03 ));
#endif
#if(1)
    ACE_CString sign03;
	if(sensitivityRec.sensitivityGamma[0]=='0') sign03 = "+";
	else sign03 = "-";
#endif


    ACE_CString sensitivityGamma(sensitivityRec.sensitivityGamma, sizeof ( sensitivityRec.sensitivityGamma ));

#if(0)
    ACE_CString sign04(sensitivityRec.sign04, sizeof ( sensitivityRec.sign04 ));
#endif
#if(1)
    ACE_CString sign04;
	if(sensitivityRec.sensitivityRho[0]=='0') sign04 = "+";
	else sign04 = "-";
#endif


    ACE_CString sensitivityRho(sensitivityRec.sensitivityRho, sizeof ( sensitivityRec.sensitivityRho ));
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleKoscomLineLKInfo(const ACE_CString &packet)
{

    if ( EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_OPTION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleKoscomLineLKInfo] Skip : %s,%d : EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_OPTION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_OPTION_SIZE , packet.length() , packet.c_str() ), -1);
        return 0;
    }

    ExturePlusKoscomLineLKInfo_KOSPI200_OPTION rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKoscomLineLKInfo_KOSPI200_OPTION));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_INET_Addr addrLocalhost;
    ACE_CString hostname(addrLocalhost.get_host_name());
    ACE_CString recvAddr(rawRec.recvAddr, sizeof ( rawRec.recvAddr ));
    ACE_CString lkMsgRaw(packet.c_str(), 9);

    KoscomLineLKInfo lkRec;
    ::memset(&lkRec, 0, sizeof(KoscomLineLKInfo));
    ::memcpy(& ( lkRec.hostname_ ), hostname.c_str(), hostname.length());
    ::memcpy(& ( lkRec.addrInfo_ ), recvAddr.c_str(), recvAddr.length());
    lkRec.commType_ = COMM_TYPE_TCP;
    lkRec.recvTime_ = static_cast<int>(::time(0));
    ::memcpy(& ( lkRec.msgRaw_ ), lkMsgRaw.c_str(), lkMsgRaw.length());

    char bufSendPacket[KOSCOM_LINE_LK_INFO_SIZE];
    ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
    ::memcpy(&bufSendPacket, &lkRec, sizeof(KoscomLineLKInfo));
    int result = sendPacket(ACE_CString(bufSendPacket, KOSCOM_LINE_LK_INFO_SIZE), PACKET_KOSCOM_LINE_LK_INFO, EXCHANGE_KSE);

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleKoscomLineLKInfo] result:[%d]\thostname:[%s]\trecvAddr:[%s]\tcommType:[%d]\trecvTime:[%d]\tlkMsgRaw:[%s]\n" , getCurrentTimestamp().c_str() , result , ACE_CString(lkRec.hostname_, sizeof ( lkRec.hostname_ )).c_str() , ACE_CString(lkRec.addrInfo_, sizeof ( lkRec.addrInfo_ )).c_str() , lkRec.commType_ , lkRec.recvTime_ , ACE_CString(lkRec.msgRaw_, sizeof ( lkRec.msgRaw_ )).c_str() ));
    return 0;
}

int InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
        return ( 0 );
    }

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    ExturePlusKospi200OptionMarketOperationScheduleDisclosureRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200OptionMarketOperationScheduleDisclosureRecord));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString market_operation_product_group_id(rawRec.market_operation_product_group_id, sizeof ( rawRec.market_operation_product_group_id ));
    ACE_CString board_id(rawRec.board_id, sizeof ( rawRec.board_id ));
    ACE_CString board_event_id(rawRec.board_event_id, sizeof ( rawRec.board_event_id ));
    ACE_CString board_event_start_time(rawRec.board_event_start_time, sizeof ( rawRec.board_event_start_time ));
    ACE_CString board_event_group_code(rawRec.board_event_group_code, sizeof ( rawRec.board_event_group_code ));
    ACE_CString session_start_end_code(rawRec.session_start_end_code, sizeof ( rawRec.session_start_end_code ));
    ACE_CString session_id(rawRec.session_id, sizeof ( rawRec.session_id ));
    ACE_CString step_applied(rawRec.step_applied, sizeof ( rawRec.step_applied ));
    ACE_CString price_expansion_trigger_code_for_base_issue(rawRec.price_expansion_trigger_code_for_base_issue, sizeof ( rawRec.price_expansion_trigger_code_for_base_issue ));
    ACE_CString price_expansion_expected_time(rawRec.price_expansion_expected_time, sizeof ( rawRec.price_expansion_expected_time ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] market_operation_product_group_id:[%s]\n" , getCurrentTimestamp().c_str() , market_operation_product_group_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_id:[%s]\n" , getCurrentTimestamp().c_str() , board_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_event_id:[%s]\n" , getCurrentTimestamp().c_str() , board_event_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_event_start_time:[%s]\n" , getCurrentTimestamp().c_str() , board_event_start_time.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_event_group_code:[%s]\n" , getCurrentTimestamp().c_str() , board_event_group_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] session_start_end_code:[%s]\n" , getCurrentTimestamp().c_str() , session_start_end_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] session_id:[%s]\n" , getCurrentTimestamp().c_str() , session_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] step_applied:[%s]\n" , getCurrentTimestamp().c_str() , step_applied.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] price_expansion_trigger_code_for_base_issue:[%s]\n" , getCurrentTimestamp().c_str() , price_expansion_trigger_code_for_base_issue.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handleMarketOperationScheduleDisclosureRecord] price_expansion_expected_time:[%s]\n" , getCurrentTimestamp().c_str() , price_expansion_expected_time.c_str() ));

    return ( 0 );
}

int InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI200_OPTION_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] Skip : %s,%d : EXTURE_PLUS_KOSPI200_OPTION_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI200_OPTION_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
        return ( 0 );
    }

    ExturePlusKospi200OptionPriceLimitRangeExpansionTriggerRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200OptionPriceLimitRangeExpansionTriggerRecord));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString board_id(rawRec.board_id, sizeof ( rawRec.board_id ));
    ACE_CString price_expansion_time(rawRec.price_expansion_time, sizeof ( rawRec.price_expansion_time ));
    ACE_CString the_upper_step_of_price_limit_expansion(rawRec.the_upper_step_of_price_limit_expansion, sizeof ( rawRec.the_upper_step_of_price_limit_expansion ));
    ACE_CString the_lower_step_of_price_limit_expansion(rawRec.the_lower_step_of_price_limit_expansion, sizeof ( rawRec.the_lower_step_of_price_limit_expansion ));
    ACE_CString upper_limit_price(rawRec.upper_limit_price, sizeof ( rawRec.upper_limit_price ));
    ACE_CString lower_limit_price(rawRec.lower_limit_price, sizeof ( rawRec.lower_limit_price ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] board_id:[%s]\n" , getCurrentTimestamp().c_str() , board_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] price_expansion_time:[%s]\n" , getCurrentTimestamp().c_str() , price_expansion_time.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] the_upper_step_of_price_limit_expansion:[%s]\n" , getCurrentTimestamp().c_str() , the_upper_step_of_price_limit_expansion.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] the_lower_step_of_price_limit_expansion:[%s]\n" , getCurrentTimestamp().c_str() , the_lower_step_of_price_limit_expansion.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , upper_limit_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200OptionChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , lower_limit_price.c_str() ));

    PriceLimitRangeExpansionTrigger triggerRec;
    ::memset(&triggerRec, 0, sizeof(PriceLimitRangeExpansionTrigger));
    ::memcpy(& ( triggerRec.symbol ), issue_code.c_str(), issue_code.length());
    triggerRec.registerDt = (int) ( ::time(0) );
    ::memcpy(& ( triggerRec.boardId ), board_id.c_str(), board_id.length());
    ::memcpy(& ( triggerRec.priceExpansionTime ), price_expansion_time.c_str(), price_expansion_time.length());

    triggerRec.upperStepOfPriceLimitexpansion = parseInt(the_upper_step_of_price_limit_expansion, 0);
    triggerRec.lowerStepOfPriceLimitexpansion = parseInt(the_lower_step_of_price_limit_expansion, 0);

    triggerRec.upperLimitPrice = parseInt(upper_limit_price, 0);
    triggerRec.lowerLimitPrice = parseInt(lower_limit_price, 0);

#if(1)
printPacketPriceLimitRangeExpansionTrigger(triggerRec);
#endif

    char bufSendPacket[PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_SIZE];
    ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
    ::memcpy(&bufSendPacket, &triggerRec, sizeof(PriceLimitRangeExpansionTrigger));

    int result = sendPacket(ACE_CString(bufSendPacket, PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_SIZE), PACKET_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER, EXCHANGE_KSE);

    return ( result );

}

ACE_CString InternetKospi200OptionChannelProcessor::getSuspensionType(const ACE_CString& raw)
{
    ACE_CString result;

    if ( raw == "Y" )
    {
        result = MASTER_SUSPENSION_VALUE_SUSPENDED;
    }
    else
    {
        result = MASTER_SUSPENSION_VALUE_NORMAL;
    }
    return result;
}

ACE_CString InternetKospi200OptionChannelProcessor::getATMCode(const ACE_CString& raw)
{
    ACE_CString result;

    if ( raw == "0" )
    {
        result = "선물";
    }
    else if ( raw == "1" )
    {
        result = "ATM";
    }
    else if ( raw == "2" )
    {
        result = "ITM";
    }
    else if ( raw == "3" )
    {
        result = "OTM";
    }
    else
    {
        result = "미지정";
    }
    return result;
}

ACE_CString InternetKospi200OptionChannelProcessor::getSign(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "-" )
    {
        result = "-";
    }
    return result;
}

int InternetKospi200OptionChannelProcessor::getCurrentTimeUTC(const ACE_CString &sessionID)
{
    time_t currentTime = 0;

    if ( getMarketInTrade(sessionID) == MARKET_END )
    {
        time_t timeCurr = ::time(0);
        struct tm tmCurr = *::localtime(&timeCurr);
        tmCurr.tm_hour = 18;
        tmCurr.tm_min = 0;
        tmCurr.tm_sec = 0;
        currentTime = ::mktime(&tmCurr);
    }
    else
    {
        currentTime = ::time(0);
    }
    return currentTime;
}

int InternetKospi200OptionChannelProcessor::getTickTimeUTCByTimestamp(const ACE_CString &timeStr, const ACE_CString &sessionID)
{
    int tickTime = 0;

    if ( getMarketInTrade(sessionID) == MARKET_END )
    {
        time_t currentTime = 0;
        time_t timeCurr = ::time(0);
        struct tm tmCurr = *::localtime(&timeCurr);
        tmCurr.tm_hour = 18;
        tmCurr.tm_min = 0;
        tmCurr.tm_sec = 0;
        currentTime = ::mktime(&tmCurr);
        tickTime = (int) ( currentTime );
    }
    else
    {
        int hour = 0;
        int minute = 0;
        int second = 0;

        if ( timeStr.substr(3, 3) == "JJJ" )
        {
            hour = 18;
            minute = 0;
            second = 0;
        }
        else
        {
            hour = atoi(timeStr.substr(0, 2).c_str());
            minute = atoi(timeStr.substr(2, 2).c_str());
            second = atoi(timeStr.substr(4, 2).c_str());
        }
        int currentTime = ::time(0);
        int timezone = -9 * 3600;
        int dayBaseTime = ( currentTime - timezone ) - ( ( currentTime - timezone ) % ( 3600 * 24 ) ) + timezone;
        tickTime = dayBaseTime + hour * 3600 + minute * 60 + second;
    }
    return tickTime;
}

