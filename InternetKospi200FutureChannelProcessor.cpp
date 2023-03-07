#include <sstream>
#include <utility>

#include "InvestorCodeConverter.h"
#include "InternetKospi200FutureChannelProcessor.h"

#include "PaxfeedDefine.h"
#include "PaxfeedPacket.h"
#include "ace/Log_Msg.h"
#include "MMapAllocator.h"
#include "PaxfeedStatus.h"
#include "PaxfeedStringUtil.h"
#include "TickFilter.h"
#include "SimpleStringUtil.h"
#include <exception>

using namespace paxfeed;

const ACE_CString ERROR_SYMBOL_NOT_FOUND = "ERROR_SYMBOL_NOT_FOUND";

const int KOSCOM_CODE_NEAREST_FUTURE = 1;

InternetKospi200FutureChannelProcessor::InternetKospi200FutureChannelProcessor(const ACE_CString &channelName)
        : InternetChannelProcessor(channelName), masterMap_(allocHashMap<MasterMap>("TP_FUTURE_MASTER", *ALLOCATOR::instance()))
{
    futureMasterMap_.unbind_all();

    MasterMap::iterator iterMaster = masterMap_->begin();
    for ( ; iterMaster != masterMap_->end() ; ++iterMaster )
    {
        ACE_Hash_Map_Entry<ACE_CString, ExturePlusKospi200FutureStockInfoRecord>& entry = *iterMaster;
        ExturePlusKospi200FutureStockInfoRecord tempMasterRec;
        ::memcpy(&tempMasterRec, &entry.int_id_, sizeof(ExturePlusKospi200FutureStockInfoRecord));
        ACE_CString stockCode(tempMasterRec.stockCode, sizeof ( tempMasterRec.stockCode ));
        futureMasterMap_.rebind(stockCode, tempMasterRec);
        ACE_DEBUG( ( LM_DEBUG , "loading Future Master from MMAP stockCode:%s\n" , stockCode.c_str() ));
    }
}

InternetKospi200FutureChannelProcessor::~InternetKospi200FutureChannelProcessor()
{

}

int InternetKospi200FutureChannelProcessor::reset()
{
    InternetChannelProcessor::reset();
    masterMap_->unbind_all();
    futureMasterMap_.unbind_all();
    tradeMap_.unbind_all();
    openInterestMap_.unbind_all();
    return 0;
}

int InternetKospi200FutureChannelProcessor::processPacket(const ACE_CString &packet)
{
    ACE_CString dataClass(packet.substr(0, 2));
    ACE_CString trID(packet.substr(0, 5));
	ACE_CString dataType(packet.substr(0, 5));

	if(dataType == "A001F")
	{
		handleMaster(packet);
    }
	else if(dataType == "A301F")
	{
		handleTrade(packet);
    }
	else if(dataType == "A601F")
	{
		handleStockClose(packet);
    }
	else if(dataType == "A701F")
	{
		handleMarketOperation(packet);
    }
	else if(dataType == "B201F")
	{
		handleRecovery(packet);
    }
	else if(dataType == "B601F")
	{
		handleQuote(packet);
    }
	else if(dataType == "G701F")
	{
		handleTradeAndQuote(packet);
    }
	else if(dataType == "H101F")
	{
		handleInvestor(packet);
    }
	else if(dataType == "H201F")
	{
		handleOpenInterestVolume(packet);
    }
	else if(dataType == "H301F")
	{
		handleAdjustedPrice(packet);
    }
	else if(dataType == "M401F")
	{
		handleMarketOperationScheduleDisclosureRecord(packet);
    }
	else if(dataType == "M701F")
	{
		handlePreMarketNegotiatedTradeDataRecord(packet);
    }
	else if(dataType == "O601F")
	{
		handleQuantityAllocation(packet);
    }
	else if(dataType == "Q201F")
	{
		handleRealTimeUpperLowerLimitPrice(packet);
    }
	else if(dataType == "V101F")
	{
		handlePriceLimitRangeExpansionTriggerRecord(packet);
    }
#if(0)
//(Áõ±ÇA) STK : A701S, (ÆÄ»ýA) DRV : A701F, A703F
#endif
	else if(dataType == "A701F")
	{
		handleMarketOperation(packet);
    }
    else
	{
		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::processPacket] trID:[%s]\n" , getCurrentTimestamp().c_str() , trID.c_str() ));
    }
    return 0;
}

bool InternetKospi200FutureChannelProcessor::isNearestFuture(const ACE_CString& stockCode)
{
    bool isNearest = false;
    ExturePlusKospi200FutureStockInfoRecord infoRec;
    ::memset(&infoRec, 0, sizeof(ExturePlusKospi200FutureStockInfoRecord));
    int hasMasterRec = futureMasterMap_.find(stockCode, infoRec);
    if ( hasMasterRec != -1 )
    {
        ACE_CString strMonthProductClassCode(infoRec.monthProductClassCode, sizeof ( infoRec.monthProductClassCode ));
        int monthProductClassCode = ::atoi(strMonthProductClassCode.c_str());
        if ( monthProductClassCode == KOSCOM_CODE_NEAREST_FUTURE )
        {
            isNearest = true;
        }
        else
        {
            isNearest = false;
        }
    }
    else
    {
        isNearest = false;
    }
    return isNearest;
}

int InternetKospi200FutureChannelProcessor::handleRecovery(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_RECOVERY_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleRecovery] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_RECOVERY_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_RECOVERY_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureRecoveryRecord rawRecoveryRec;
    ::memset(&rawRecoveryRec, 0, sizeof(ExturePlusKospi200FutureRecoveryRecord));
    ::memcpy(&rawRecoveryRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawRecoveryRec.stockCode, sizeof ( rawRecoveryRec.stockCode ));
    ACE_CString sessionID(rawRecoveryRec.sessionID, sizeof ( rawRecoveryRec.sessionID ));

    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleRecovery] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        Quote10 quote;
        ::memset(&quote, 0, sizeof(Quote10));
        ::memcpy(quote.symbol, stockCode.c_str(), stockCode.length());
        quote.exchange = EXCHANGE_KSE;
        quote.symbolType = SYMBOL_FUTURE;
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
#if(0)
            ACE_CString estimatedTradingPriceSign(rawRecoveryRec.estimatedTradingPriceSign, sizeof ( rawRecoveryRec.estimatedTradingPriceSign ));
#endif

#if(1)
            ACE_CString estimatedTradingPriceSign;

			if(rawRecoveryRec.estimatedTradingPrice[0]=='0') estimatedTradingPriceSign = "+";
			else estimatedTradingPriceSign = "-";
#endif

            ACE_CString estimatedTradingPrice(rawRecoveryRec.estimatedTradingPrice, sizeof ( rawRecoveryRec.estimatedTradingPrice ));

            estimatedTradingPrice = estimatedTradingPriceSign + estimatedTradingPrice;
            estimatedTradingPrice = trim(estimatedTradingPrice);

            int expectedPrice = ::atoi(estimatedTradingPrice.c_str());
            quote.expectedPrice = expectedPrice;

        }

        char quoteBuf[QUOTE10_SIZE];
        memcpy(quoteBuf, &quote, QUOTE10_SIZE);
        sendPacket(ACE_CString(quoteBuf, QUOTE10_SIZE), PACKET_QUOTE10, EXCHANGE_KSE);
    }

    ExturePlusKospi200FutureStockInfoRecord infoRec;
    int hasMasterRec = futureMasterMap_.find(stockCode, infoRec);
    if ( hasMasterRec != -1 )
    {
#if(0)
        ACE_CString openPriceSign(rawRecoveryRec.openPriceSign, sizeof ( rawRecoveryRec.openPriceSign ));
        ACE_CString highPriceSign(rawRecoveryRec.highPriceSign, sizeof ( rawRecoveryRec.highPriceSign ));
        ACE_CString lowPriceSign(rawRecoveryRec.lowPriceSign, sizeof ( rawRecoveryRec.lowPriceSign ));
        ACE_CString currentPriceSign(rawRecoveryRec.currentPriceSign, sizeof ( rawRecoveryRec.currentPriceSign ));
#endif

#if(1)
        ACE_CString openPriceSign;
        ACE_CString highPriceSign;
        ACE_CString lowPriceSign;
        ACE_CString currentPriceSign;

		if(rawRecoveryRec.openPrice[0]=='0') openPriceSign = "+";
		else openPriceSign = "-";

		if(rawRecoveryRec.highPrice[0]=='0') highPriceSign = "+";
		else highPriceSign = "-";

		if(rawRecoveryRec.lowPrice[0]=='0') lowPriceSign = "+";
		else lowPriceSign = "-";

		if(rawRecoveryRec.currentPrice[0]=='0') currentPriceSign = "+";
		else currentPriceSign = "-";
#endif

        ACE_CString strOpenPrice(rawRecoveryRec.openPrice, sizeof ( rawRecoveryRec.openPrice ));
        ACE_CString strHighPrice(rawRecoveryRec.highPrice, sizeof ( rawRecoveryRec.highPrice ));
        ACE_CString strLowPrice(rawRecoveryRec.lowPrice, sizeof ( rawRecoveryRec.lowPrice ));
        ACE_CString strClosePrice(rawRecoveryRec.currentPrice, sizeof ( rawRecoveryRec.currentPrice ));
        ACE_CString strAccmTradeVolume(rawRecoveryRec.accmTradeVolume, sizeof ( rawRecoveryRec.accmTradeVolume ));

        strOpenPrice = openPriceSign + strOpenPrice;
        strOpenPrice = trim(strOpenPrice);

        strHighPrice = highPriceSign + strHighPrice;
        strHighPrice = trim(strHighPrice);

        strLowPrice = lowPriceSign + strLowPrice;
        strLowPrice = trim(strLowPrice);

        strClosePrice = currentPriceSign + strClosePrice;
        strClosePrice = trim(strClosePrice);

        int openPrice = ::atoi(strOpenPrice.c_str());
        int highPrice = ::atoi(strHighPrice.c_str());
        int lowPrice = ::atoi(strLowPrice.c_str());
        int closePrice = ::atoi(strClosePrice.c_str());
        double accmTradeVolume = ::atof(strAccmTradeVolume.c_str());

        if ( ( openPrice == 0 ) || ( highPrice == 0 ) || ( lowPrice == 0 ) || ( closePrice == 0 ) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleRecovery] Skip : %s,%d stockCode:[%s] price is zero (%d, %d, %d, %d)\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , openPrice , highPrice , lowPrice , closePrice ), -1);
        }

        Trade trade;
        ::memset(&trade, 0, sizeof(Trade));
        int hasTradePrev = tradeMap_.find(stockCode, trade);

        double netVolume = accmTradeVolume - ( hasTradePrev != -1 ? trade.accmVolume : 0 );

        if ( netVolume > 0 )
        {
            int prevTime = trade.tradeTime;

            trade.tradeTime = getCurrentTimeUTC(sessionID);
            trade.market = getMarketInTrade(sessionID);

            ACE_CString strYdayClosePrice(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
            ACE_CString strStdPrice(infoRec.standardPrice, sizeof ( infoRec.standardPrice ));
            int ydayClosePrice = ::atoi(strYdayClosePrice.c_str());
            int stdPrice = ::atoi(strStdPrice.c_str());
            trade.upDown = getUpDownInTrade(ydayClosePrice, stdPrice, closePrice);

            trade.open = openPrice;
            trade.high = highPrice;
            trade.low = lowPrice;
            trade.close = closePrice;
            trade.ydayClose = ydayClosePrice;
			trade.tradeVolume = 0;
            trade.accmVolume = accmTradeVolume;

            ACE_CString strAmount(rawRecoveryRec.accmTradeAmount, sizeof ( rawRecoveryRec.accmTradeAmount ));
            trade.amount = ::atof(strAmount.c_str());
            trade.amount = trade.amount * 1000;

            ExturePlusKospi200FutureOpenInterestVolumeRecord oiRec;
            ::memset(&oiRec, 0, sizeof(ExturePlusKospi200FutureOpenInterestVolumeRecord));
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
                trade.symbolType = SYMBOL_FUTURE;
                trade.decimalPoint = DECIMAL_2;

                memcpy(&trade.symbol, stockCode.c_str(), stockCode.length());

                trade.openMin = openPrice;
                trade.highMin = highPrice;
                trade.lowMin = lowPrice;
                trade.volumeMin = trade.tradeVolume;
                tradeMap_.rebind(stockCode, trade);
            }
            else
            {
                if ( trade.tradeTime / 60 == prevTime / 60 )
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
            ACE_CString strSignForRealTimeUpperLimitPrice(rawRecoveryRec.signForRealTimeUpperLimitPrice, sizeof ( rawRecoveryRec.signForRealTimeUpperLimitPrice ));
#endif
#if(1)
            ACE_CString strSignForRealTimeUpperLimitPrice;
			if(rawRecoveryRec.realTimeUpperLimitPrice[0]=='0') strSignForRealTimeUpperLimitPrice = "+";
			else strSignForRealTimeUpperLimitPrice = "-";
#endif
            ACE_CString strRealTimeUpperLimitPrice(rawRecoveryRec.realTimeUpperLimitPrice, sizeof ( rawRecoveryRec.realTimeUpperLimitPrice ));

#if(0)
            ACE_CString strSignForRealTimeLowerLimitPrice(rawRecoveryRec.signForRealTimeLowerLimitPrice, sizeof ( rawRecoveryRec.signForRealTimeLowerLimitPrice ));
#endif
#if(1)
            ACE_CString strSignForRealTimeLowerLimitPrice;
			if(rawRecoveryRec.realTimeLowerLimitPrice[0]=='0') strSignForRealTimeLowerLimitPrice = "+";
			else strSignForRealTimeLowerLimitPrice = "-";
#endif
            ACE_CString strRealTimeLowerLimitPrice(rawRecoveryRec.realTimeLowerLimitPrice, sizeof ( rawRecoveryRec.realTimeLowerLimitPrice ));

            ACE_CString strUpperLimitPriceSigned;
            strUpperLimitPriceSigned = strSignForRealTimeUpperLimitPrice + strRealTimeUpperLimitPrice;
            double realTimeUpperLimitPrice = ::atof(strUpperLimitPriceSigned.c_str());

            ACE_CString strLowerLimitPriceSigned;
            strLowerLimitPriceSigned = strSignForRealTimeLowerLimitPrice + strRealTimeLowerLimitPrice;
            double realTimeLowerLimitPrice = ::atof(strLowerLimitPriceSigned.c_str());

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

            if ( isNearestFuture(stockCode) == true )
            {
                if ( isSpread(stockCode) == false )
                {
                    sendByNearestFuture(trade, limitRec);
                }
            }
        }
        else
        {
            if ( netVolume < 0 )
            {
                ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleRecovery] Skip : %s,%d : net volume is below zero stockCode:[%s] netVolume:[%d]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , netVolume ), -1);
            }
        }
    }
    else
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleRecovery] Skip : %s,%d : cannot find matching master data stockCode:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() ), -1);
    }
    return 0;
}

bool InternetKospi200FutureChannelProcessor::isSpread(const ACE_CString &symbol)
{
    return symbol[3] == '4';
}

int InternetKospi200FutureChannelProcessor::handleTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_TRADE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTrade] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_TRADE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_TRADE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureTradeRecord rawTradeRec;
    ::memset(&rawTradeRec, 0, sizeof(ExturePlusKospi200FutureTradeRecord));
    ::memcpy(&rawTradeRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawTradeRec.stockCode, sizeof ( rawTradeRec.stockCode ));
    ACE_CString sessionID(rawTradeRec.sessionID, sizeof ( rawTradeRec.sessionID ));

	ExturePlusKospi200FutureStockInfoRecord infoRec;
    int hasMasterRec = futureMasterMap_.find(stockCode, infoRec);

    if ( hasMasterRec != -1 )
    {
#if(0)
        ACE_CString openPriceSign(rawTradeRec.openPriceSign, sizeof ( rawTradeRec.openPriceSign ));
        ACE_CString highPriceSign(rawTradeRec.highPriceSign, sizeof ( rawTradeRec.highPriceSign ));
        ACE_CString lowPriceSign(rawTradeRec.lowPriceSign, sizeof ( rawTradeRec.lowPriceSign ));
        ACE_CString currentPriceSign(rawTradeRec.currentPriceSign, sizeof ( rawTradeRec.currentPriceSign ));
#endif
#if(1)
        ACE_CString openPriceSign;
        ACE_CString highPriceSign;
        ACE_CString lowPriceSign;
        ACE_CString currentPriceSign;

		if(rawTradeRec.openPrice[0]=='0') openPriceSign = "+";
		else openPriceSign = "-";

		if(rawTradeRec.highPrice[0]=='0') highPriceSign = "+";
		else highPriceSign = "-";

		if(rawTradeRec.lowPrice[0]=='0') lowPriceSign = "+";
		else lowPriceSign = "-";

		if(rawTradeRec.currentPrice[0]=='0') currentPriceSign = "+";
		else currentPriceSign = "-";
#endif

        ACE_CString strOpenPrice(rawTradeRec.openPrice, sizeof ( rawTradeRec.openPrice ));
        ACE_CString strHighPrice(rawTradeRec.highPrice, sizeof ( rawTradeRec.highPrice ));
        ACE_CString strLowPrice(rawTradeRec.lowPrice, sizeof ( rawTradeRec.lowPrice ));
        ACE_CString strClosePrice(rawTradeRec.currentPrice, sizeof ( rawTradeRec.currentPrice ));
        ACE_CString strAccmTradeVolume(rawTradeRec.accmTradeVolume, sizeof ( rawTradeRec.accmTradeVolume ));

        strOpenPrice = openPriceSign + strOpenPrice;
        strOpenPrice = trim(strOpenPrice);

        strHighPrice = highPriceSign + strHighPrice;
        strHighPrice = trim(strHighPrice);

        strLowPrice = lowPriceSign + strLowPrice;
        strLowPrice = trim(strLowPrice);

        strClosePrice = currentPriceSign + strClosePrice;
        strClosePrice = trim(strClosePrice);

        int openPrice = ::atoi(strOpenPrice.c_str());
        int highPrice = ::atoi(strHighPrice.c_str());
        int lowPrice = ::atoi(strLowPrice.c_str());
        int closePrice = ::atoi(strClosePrice.c_str());
        double accmTradeVolume = ::atof(strAccmTradeVolume.c_str());

        if ( ( openPrice == 0 ) || ( highPrice == 0 ) || ( lowPrice == 0 ) || ( closePrice == 0 ) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTrade] Skip : %s,%d stockCode:[%s] price is zero (%d, %d, %d, %d)\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , openPrice , highPrice , lowPrice , closePrice ), -1);
        }

        Trade trade;
        ::memset(&trade, 0, sizeof(Trade));

        int hasTradePrev = tradeMap_.find(stockCode, trade);
        double netVolume = accmTradeVolume - ( hasTradePrev != -1 ? trade.accmVolume : 0 );

        ACE_CString strTradeVolume(rawTradeRec.tradeVolume, sizeof ( rawTradeRec.tradeVolume ));
        int tradeVolume = ::atoi(strTradeVolume.c_str());

        ACE_CString strTickTimeMillis = ACE_CString(rawTradeRec.tradeTime, sizeof ( trade.tradeTime ));
        int tickTime = getTickTimeUTCByTimestamp(strTickTimeMillis, sessionID);

        if ( netVolume > 0 )
        {
            int prevTime = trade.tradeTime;
            trade.tradeTime = tickTime;
            trade.market = getMarketInTrade(sessionID);

            ACE_CString strYdayClosePrice(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
            ACE_CString strStdPrice(infoRec.standardPrice, sizeof ( infoRec.standardPrice ));
            int ydayClosePrice = ::atoi(strYdayClosePrice.c_str());
            int stdPrice = ::atoi(strStdPrice.c_str());

            trade.upDown = getUpDownInTrade(ydayClosePrice, stdPrice, closePrice);
            trade.open = openPrice;
            trade.high = highPrice;
            trade.low = lowPrice;
            trade.close = closePrice;
            trade.ydayClose = ydayClosePrice;

            trade.tradeVolume = tradeVolume;

            trade.accmVolume = accmTradeVolume;

            ACE_CString strAmount(rawTradeRec.accmTradeAmount, sizeof ( rawTradeRec.accmTradeAmount ));
            trade.amount = ::atof(strAmount.c_str());
            trade.amount = trade.amount * 1000; // ëˆ„ì ê±°ëž˜ëŒ€ê¸ˆì€ 1000ì› ë‹¨ìœ„ìž„

            ExturePlusKospi200FutureOpenInterestVolumeRecord oiRec;
            ::memset(&oiRec, 0, sizeof(ExturePlusKospi200FutureOpenInterestVolumeRecord));
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
                trade.symbolType = SYMBOL_FUTURE;
                trade.decimalPoint = DECIMAL_2;

                memcpy(&trade.symbol, stockCode.c_str(), stockCode.length());

                trade.openMin = openPrice;
                trade.highMin = highPrice;
                trade.lowMin = lowPrice;
                trade.volumeMin = trade.tradeVolume;

                tradeMap_.rebind(stockCode, trade);
            }
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

#if(1)
printPacketTrade(trade);
#endif

#if(0)
            ACE_CString strSignForRealTimeUpperLimitPrice(rawTradeRec.signForRealTimeUpperLimitPrice, sizeof ( rawTradeRec.signForRealTimeUpperLimitPrice ));
#endif
#if(1)
            ACE_CString strSignForRealTimeUpperLimitPrice;
			if(rawTradeRec.realTimeUpperLimitPrice[0]=='0') strSignForRealTimeUpperLimitPrice = "+";
			else strSignForRealTimeUpperLimitPrice = "-";
#endif
            ACE_CString strRealTimeUpperLimitPrice(rawTradeRec.realTimeUpperLimitPrice, sizeof ( rawTradeRec.realTimeUpperLimitPrice ));

#if(0)
            ACE_CString strSignForRealTimeLowerLimitPrice(rawTradeRec.signForRealTimeLowerLimitPrice, sizeof ( rawTradeRec.signForRealTimeLowerLimitPrice ));
#endif
#if(1)
            ACE_CString strSignForRealTimeLowerLimitPrice;
			if(rawTradeRec.realTimeLowerLimitPrice[0]=='0') strSignForRealTimeLowerLimitPrice = "+";
			else strSignForRealTimeLowerLimitPrice = "-";
#endif
            ACE_CString strRealTimeLowerLimitPrice(rawTradeRec.realTimeLowerLimitPrice, sizeof ( rawTradeRec.realTimeLowerLimitPrice ));

            ACE_CString strUpperLimitPriceSigned;
            strUpperLimitPriceSigned = strSignForRealTimeUpperLimitPrice + strRealTimeUpperLimitPrice;
            double realTimeUpperLimitPrice = ::atof(strUpperLimitPriceSigned.c_str());

            ACE_CString strLowerLimitPriceSigned;
            strLowerLimitPriceSigned = strSignForRealTimeLowerLimitPrice + strRealTimeLowerLimitPrice;
            double realTimeLowerLimitPrice = ::atof(strLowerLimitPriceSigned.c_str());

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

#if(1)
printPacketRealTimeLimitPrice(limitRec);
#endif

            char bufSendPacket[REAL_TIME_LIMIT_PRICE_SIZE];
            ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
            ::memcpy(&bufSendPacket, &limitRec, sizeof(RealTimeLimitPrice));
            sendPacket(ACE_CString(bufSendPacket, REAL_TIME_LIMIT_PRICE_SIZE), PACKET_REAL_TIME_LIMIT_PRICE, EXCHANGE_KSE);

            if ( isNearestFuture(stockCode) == true )
            {
                if ( isSpread(stockCode) == false )
                {
                    sendByNearestFuture(trade, limitRec);
                }
            }
        }
        else
        {
            if ( netVolume < 0 )
            {
                ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTrade] Skip : %s,%d : net volume is below zero stockCode:[%s] netVolume:[%d]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , netVolume ), -1);
            }
        }
    }
    else
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTrade] Skip : %s,%d : cannot find matching master data stockCode:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() ), -1);
    }
    return 0;
}

int InternetKospi200FutureChannelProcessor::handleQuote(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_PRIORITY_QUOTE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleQuote] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_PRIORITY_QUOTE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_PRIORITY_QUOTE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FuturePriorityQuoteRecord rawQuoteRec;
    ::memset(&rawQuoteRec, 0, sizeof(ExturePlusKospi200FuturePriorityQuoteRecord));
    ::memcpy(&rawQuoteRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawQuoteRec.stockCode, sizeof ( rawQuoteRec.stockCode ));

    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleRecovery] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        Quote10 quote;
        ::memset(&quote, 0, sizeof(Quote10));
        quote.exchange = EXCHANGE_KSE;
        quote.symbolType = SYMBOL_FUTURE;
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

        if ( ( sessionID == "10" ) || ( sessionID == "20" ) || ( sessionID == "30" ) || ( sessionID == "80" ) )
        {
#if(0)
            ACE_CString estimatedTradingPriceSign(rawQuoteRec.estimatedTradingPriceSign, sizeof ( rawQuoteRec.estimatedTradingPriceSign ));
#endif
#if(1)
            ACE_CString estimatedTradingPriceSign;
			if(rawQuoteRec.estimatedTradingPrice[0]=='0') estimatedTradingPriceSign = "+";
			else estimatedTradingPriceSign = "-";
#endif
            ACE_CString estimatedTradingPrice(rawQuoteRec.estimatedTradingPrice, sizeof ( rawQuoteRec.estimatedTradingPrice ));
            estimatedTradingPrice = estimatedTradingPriceSign + estimatedTradingPrice;
            estimatedTradingPrice = trim(estimatedTradingPrice);

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

int InternetKospi200FutureChannelProcessor::handleInvestorForNormal(const ExturePlusKospi200FutureInvestorRecord &rawInvestorRec)
{
    ACE_CString dataType(rawInvestorRec.dataType, sizeof ( rawInvestorRec.dataType ));
    if ( ( dataType == "E1" ) || ( dataType == "E2" ) )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleInvestorForNormal] Skip : dataType:[%s]\n" , getCurrentTimestamp().c_str() , dataType.c_str() ));
        return 0;
    }

    Investor investorNormal;
    ::memset(&investorNormal, 0, sizeof(Investor));
    investorNormal.exchange = EXCHANGE_KSE;
    investorNormal.symbolType = SYMBOL_FUTURE;

    ACE_CString normalSymbol("KR4101000000");
    ::memcpy(investorNormal.symbol, normalSymbol.c_str(), normalSymbol.length());

    ACE_CString investorType(rawInvestorRec.investorType, sizeof ( rawInvestorRec.investorType ));
    ::memcpy(investorNormal.investor, investorType.c_str(), investorType.length());

    ACE_CString strAskVolume(rawInvestorRec.askAgreementVolume, sizeof ( rawInvestorRec.askAgreementVolume ));
    ACE_CString strAskAmount(rawInvestorRec.askAgreementAmount, sizeof ( rawInvestorRec.askAgreementAmount ));
    ACE_CString strBidVolume(rawInvestorRec.bidAgreementVolume, sizeof ( rawInvestorRec.bidAgreementVolume ));
    ACE_CString strBidAmount(rawInvestorRec.bidAgreementAmount, sizeof ( rawInvestorRec.bidAgreementAmount ));
    investorNormal.askVolume = ::atof(strAskVolume.c_str());
    investorNormal.askAmount = ::atof(strAskAmount.c_str());
    investorNormal.bidVolume = ::atof(strBidVolume.c_str());
    investorNormal.bidAmount = ::atof(strBidAmount.c_str());

    char buf[INVESTOR_SIZE];
    memcpy(buf, &investorNormal, INVESTOR_SIZE);
    sendPacket(ACE_CString(buf, INVESTOR_SIZE), PACKET_INVESTOR, EXCHANGE_KSE);

#if(0)
printPacketInvestor(investorNormal);
#endif

    return 0;
}

int InternetKospi200FutureChannelProcessor::handleInvestorForSpread(const ExturePlusKospi200FutureInvestorRecord &rawInvestorRec)
{
    ACE_CString dataType(rawInvestorRec.dataType, sizeof ( rawInvestorRec.dataType ));
    if ( ( dataType == "E1" ) || ( dataType == "E2" ) )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleInvestorForSpread] Skip : dataType:[%s]\n" , getCurrentTimestamp().c_str() , dataType.c_str() ));
        return 0;
    }

    Investor investorSpread;
    ::memset(&investorSpread, 0, sizeof(Investor));
    investorSpread.exchange = EXCHANGE_KSE;
    investorSpread.symbolType = SYMBOL_FUTURE;

    ACE_CString spreadSymbol("KR4401000000");
    ::memcpy(investorSpread.symbol, spreadSymbol.c_str(), spreadSymbol.length());

    ACE_CString investorType(rawInvestorRec.investorType, sizeof ( rawInvestorRec.investorType ));
    ::memcpy(investorSpread.investor, investorType.c_str(), investorType.length());

    ACE_CString strAskVolume(rawInvestorRec.askAgreementAmountBySpread, sizeof ( rawInvestorRec.askAgreementVolumeBySpread ));
    ACE_CString strAskAmount(rawInvestorRec.askAgreementAmountBySpread, sizeof ( rawInvestorRec.askAgreementAmountBySpread ));
    ACE_CString strBidVolume(rawInvestorRec.bidAgreementVolumeBySpread, sizeof ( rawInvestorRec.bidAgreementVolumeBySpread ));
    ACE_CString strBidAmount(rawInvestorRec.bidAgreementAmountBySpread, sizeof ( rawInvestorRec.bidAgreementAmountBySpread ));
    investorSpread.askVolume = ::atof(strAskVolume.c_str());
    investorSpread.askAmount = ::atof(strAskAmount.c_str());
    investorSpread.bidVolume = ::atof(strBidVolume.c_str());
    investorSpread.bidAmount = ::atof(strBidAmount.c_str());

    char buf[INVESTOR_SIZE];
    memcpy(buf, &investorSpread, INVESTOR_SIZE);
    sendPacket(ACE_CString(buf, INVESTOR_SIZE), PACKET_INVESTOR, EXCHANGE_KSE);

    return 0;
}

int InternetKospi200FutureChannelProcessor::handleInvestor(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_INVESTOR_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleInvestor] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_INVESTOR_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_INVESTOR_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureInvestorRecord investorRec;
    ::memset(&investorRec, 0, sizeof(ExturePlusKospi200FutureInvestorRecord));
    ::memcpy(&investorRec, packet.c_str(), packet.length());

    ACE_CString dataType(investorRec.dataType, sizeof ( investorRec.dataType ));
    if ( dataType == "99" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleInvestor] Skip : dataType:[%s]\n" , getCurrentTimestamp().c_str() , dataType.c_str() ));
        return 0;
    }
    handleInvestorForNormal(investorRec);
    handleInvestorForSpread(investorRec);
    return 0;
}

int InternetKospi200FutureChannelProcessor::handleOpenInterestVolume(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_OPEN_INTEREST_VOLUME_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleOpenInterestVolume] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_OPEN_INTEREST_VOLUME_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_OPEN_INTEREST_VOLUME_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureOpenInterestVolumeRecord oiRec;
    ::memset(&oiRec, 0, sizeof(ExturePlusKospi200FutureOpenInterestVolumeRecord));
    ::memcpy(&oiRec, packet.c_str(), packet.length());

    ACE_CString stockCode(oiRec.stockCode, sizeof ( oiRec.stockCode ));
    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleOpenInterestVolume] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        openInterestMap_.rebind(stockCode, oiRec);
    }
    return 0;
}

int InternetKospi200FutureChannelProcessor::handleAdjustedPrice(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_ADJUSTED_PRICE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleAdjustedPrice] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_ADJUSTED_PRICE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_ADJUSTED_PRICE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureAdjustedPriceRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200FutureAdjustedPriceRecord));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString symbol(rawRec.stockCode, sizeof ( rawRec.stockCode ));
    if ( symbol == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleAdjustedPrice] Skip : symbol:[%s]\n" , getCurrentTimestamp().c_str() , symbol.c_str() ));
        return 0;
    }

    int registerDt = ::time(0);
    ACE_CString strSettlementPrice(rawRec.adjustedPrice, sizeof ( rawRec.adjustedPrice ));
    double settlementPrice = ::atof(strSettlementPrice.c_str());
    settlementPrice = settlementPrice / 100000000.0;

    ACE_CString strSettlementPriceType(rawRec.adjustedPriceClass, sizeof ( rawRec.adjustedPriceClass ));

    ACE_CString strLastSettlementPrice(rawRec.lastSettlementPrice, sizeof ( rawRec.lastSettlementPrice ));
    double lastSettlementPrice = ::atof(strLastSettlementPrice.c_str());
    lastSettlementPrice = lastSettlementPrice / 100000000.0;

    ACE_CString strLastSettlementPriceType(rawRec.lastSettlementPriceClass, sizeof ( rawRec.lastSettlementPriceClass ));

    KOSPI200IndexFutureSettledPriceData priceData;
    ::memset(&priceData, 0, sizeof(KOSPI200IndexFutureSettledPriceData));
    ::memcpy(& ( priceData.symbol ), symbol.c_str(), symbol.length());
    priceData.registerDt = registerDt;
    priceData.settlementPrice = settlementPrice;
    priceData.settlementPriceType = getSettlementType(strSettlementPriceType);
    priceData.lastSettlementPrice = lastSettlementPrice;
    priceData.lastSettlementPriceType = getLastSettlementType(strLastSettlementPriceType);

#if(1)
priceData.settlementPrice = priceData.settlementPrice * 100;
priceData.lastSettlementPrice = priceData.lastSettlementPrice * 100;
#endif

#if(1)
printPacketKOSPI200IndexFutureSettledPriceData(priceData);
#endif

    char buf[KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA_SIZE];
    memcpy(buf, &priceData, KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA_SIZE);
    int result = sendPacket(ACE_CString(buf, KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA_SIZE), PACKET_KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA, EXCHANGE_KSE);

    return ( result );
}

int InternetKospi200FutureChannelProcessor::getSettlementType(const ACE_CString rawSettlementType)
{
    int settlementType = KOSPI200_FUTURE_INDEX_SETTLEMENT_PRICE_TYPE_UNDEFINED;

    if ( rawSettlementType == "0" )
    {
        settlementType = KOSPI200_FUTURE_INDEX_SETTLEMENT_PRICE_TYPE_NO_SETTLEMENT_PRICE;
    }
    else if ( rawSettlementType == "1" )
    {
        settlementType = KOSPI200_FUTURE_INDEX_SETTLEMENT_PRICE_TYPE_TODAY_CLOSING_PRICE_REAL_PRICE;
    }
    else if ( rawSettlementType == "4" )
    {
        settlementType = KOSPI200_FUTURE_INDEX_SETTLEMENT_PRICE_TYPE_TODAY_THEORETICAL_VALUE;
    }
    else if ( rawSettlementType == "7" )
    {
        settlementType = KOSPI200_FUTURE_INDEX_SETTLEMENT_PRICE_TYPE_UNDERLYING_ASSET_CLOSING_PRICE;
    }
    else if ( rawSettlementType == "8" )
    {
        settlementType = KOSPI200_FUTURE_INDEX_SETTLEMENT_PRICE_TYPE_BASE_PRICE_FOR_SETTLEMENT;
    }
    else
    {
        settlementType = KOSPI200_FUTURE_INDEX_SETTLEMENT_PRICE_TYPE_UNDEFINED;
    }
    return settlementType;

}

int InternetKospi200FutureChannelProcessor::getLastSettlementType(const ACE_CString rawLastSettlementType)
{
    int lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_UNDEFINED;

    if ( rawLastSettlementType == "1" )
    {
        lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_UNDERLYING_ASSET_CLOSING_PRICE;
    }
    else if ( rawLastSettlementType == "2" )
    {
        lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_PRICE_BY_CALCULATION_FORMULA;
    }
    else if ( rawLastSettlementType == "3" )
    {
        lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_NO_VAULE_OF_THE_LAST_SETTLEMENT_PRICE;
    }
    else if ( rawLastSettlementType == "4" )
    {
        lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_SPECIAL_SETTLEMENT_INDEX;
    }
    else if ( rawLastSettlementType == "5" )
    {
        lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_THE_LATEST_UNDERLYING_ASSET_CLOSING_PRICE;
    }
    else if ( rawLastSettlementType == "6" )
    {
        lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_THE_LATEST_ADJUSTED_UNDERLYING_ASSET_CLOSING_PRICE;
    }
    else
    {
        lastSettlementType = KOSPI200_FUTURE_INDEX_LAST_SETTLEMENT_TYPE_UNDEFINED;
    }
    return lastSettlementType;
}

#if(1)
int InternetKospi200FutureChannelProcessor::handleMaster(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_INFO_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_INFO_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_INFO_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureStockInfoRecord infoRec;
    ::memset(&infoRec, 0, sizeof(ExturePlusKospi200FutureStockInfoRecord));
    ::memcpy(&infoRec, packet.c_str(), packet.length());

    ACE_CString stockCode(infoRec.stockCode, sizeof ( infoRec.stockCode ));

    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        ACE_Map_Manager < ACE_CString , ACE_CString , ACE_Null_Mutex > masterMap;

        char tempBuf[128];
        ::memset(tempBuf, 0, sizeof ( tempBuf ));

        // MASTER_SYMBOL
        masterMap.bind(MASTER_SYMBOL, stockCode);

        // MASTER_NAME
        ACE_CString name(infoRec.stockNameKor, sizeof ( infoRec.stockNameKor ));
        masterMap.bind(MASTER_NAME, trim(name));

        // MASTER_EXCHANGE
        ACE_CString exchange(EXCHANGE_KSE_STRING);
        masterMap.bind(MASTER_EXCHANGE, exchange);

        // MASTER_SYMBOL_TYPE
        ACE_CString symbolType(SYMBOL_FUTURE_STRING);
        masterMap.bind(MASTER_SYMBOL_TYPE, SYMBOL_FUTURE_STRING);

        // MASTER_SYMBOL_SUBTYPE
        ACE_CString symbolSubType(SYMBOL_SUBTYPE_INDEXFUTURE);
        masterMap.bind(MASTER_SYMBOL_SUBTYPE, symbolSubType);

        // MASTER_DECIMAL_POINT
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", DECIMAL_2);
        masterMap.bind(MASTER_DECIMAL_POINT, tempBuf);

        ACE_CString registerDate(infoRec.listingDate, sizeof ( infoRec.listingDate ));
        masterMap.bind(MASTER_REGISTER_DATE, registerDate);

        // MASTER_LAST_TRADE_DATE
        ACE_CString lastTradeDate(infoRec.lastTradeDate, sizeof ( infoRec.lastTradeDate ));
        masterMap.bind(MASTER_LAST_TRADE_DATE, lastTradeDate);

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

        // MASTER_YDAY_VOLUME  
        ACE_CString strYdayVolume(infoRec.ydayTradeVolume, sizeof ( infoRec.ydayTradeVolume ));
        int ydayVolume = ::atoi(strYdayVolume.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", ydayVolume);
        masterMap.bind(MASTER_YDAY_VOLUME, tempBuf);

        // MASTER_YDAY_AMOUNT    
        ACE_CString strYdayAmount(infoRec.ydayTradeAmount, sizeof ( infoRec.ydayTradeAmount ));
        double ydayAmount = ::atof(strYdayAmount.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%f", ydayAmount);
        masterMap.bind(MASTER_YDAY_AMOUNT, tempBuf);

#if(1)
		ACE_CString strYdayOpenInterest(infoRec.ydayOpenInterest, sizeof ( infoRec.ydayOpenInterest ));
		double strydayopeninterest = ::atof(strYdayOpenInterest.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydayopeninterest * 100.0);
        masterMap.bind(MASTER_YDAY_OPEN_INTEREST, tempBuf);
#endif



        // MASTER_ABBR_SYMBOL
        ACE_CString abbrSymbol(getAbbrSymbol(stockCode));
        masterMap.bind(MASTER_ABBR_SYMBOL, abbrSymbol);

        // MASTER_SURVIVAL_DAYS
        ACE_CString strSurvivalDays(infoRec.remainDateCount, sizeof ( infoRec.remainDateCount ));
        int survivalDays = ::atoi(strSurvivalDays.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", survivalDays);
        masterMap.bind(MASTER_SURVIVAL_DAYS, tempBuf);

        // MASTER_THEORIC_PRICE_SETTLE
        ACE_CString strTheoricPriceSettle(infoRec.theoreticalPriceSettlement, sizeof ( infoRec.theoreticalPriceSettlement ) - 4);
        int theoricPriceSettle = ::atoi(strTheoricPriceSettle.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", theoricPriceSettle);
        masterMap.bind(MASTER_THEORIC_PRICE_SETTLE, tempBuf);

#if(1)
		ACE_CString strTheoricPriceStand(infoRec.theoreticalPriceStandard, sizeof ( infoRec.theoreticalPriceStandard ) - 4);
		double strtheoricpricestand = ::atof(strTheoricPriceStand.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strtheoricpricestand * 100.0);
        masterMap.bind(MASTER_THEORIC_PRICE_STAND, tempBuf);
#endif


#if(1)
		ACE_CString strCdRate(infoRec.cdRate, sizeof ( infoRec.cdRate ));
		double strcdrate = ::atof(strCdRate.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strcdrate * 1000.0);
        masterMap.bind(MASTER_CD_RATE, tempBuf);
#endif


#if(1)
		ACE_CString strYdaySettlePrice(infoRec.ydaySettlementPrice, sizeof ( infoRec.ydaySettlementPrice ) - 6);
		double strydaysettleprice = ::atof(strYdaySettlePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydaysettleprice * 100.0);
        masterMap.bind(MASTER_YDAY_SETTLE_PRICE, tempBuf);
#endif


#if(1)
		ACE_CString strYdayHighPrice(infoRec.ydayHighPrice, sizeof ( infoRec.ydayHighPrice ));
		double strydayhighprice = ::atof(strYdayHighPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydayhighprice * 100.0);
        masterMap.bind(MASTER_YDAY_HIGH_PRICE, tempBuf);
#endif



#if(1)
		ACE_CString strYdayLowPrice(infoRec.ydayLowPrice, sizeof ( infoRec.ydayLowPrice ));
		double strydaylowprice = ::atof(strYdayLowPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strydaylowprice * 100.0);
        masterMap.bind(MASTER_YDAY_LOW_PRICE, tempBuf);
#endif


		// MASTER_YEAR_HIGHEST_DATE
        ACE_CString yearHighestDate(infoRec.highestPriceDateWithinYear, sizeof ( infoRec.highestPriceDateWithinYear ));
        masterMap.bind(MASTER_YEAR_HIGHEST_DATE, yearHighestDate);

#if(1)
		ACE_CString strYearHighestPrice(infoRec.highestPriceWithinYear, sizeof ( infoRec.highestPriceWithinYear ));
		double stryearhighestprice = ::atof(strYearHighestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", stryearhighestprice * 100.0);
        masterMap.bind(MASTER_YEAR_HIGHEST_PRICE, tempBuf);
#endif

        // MASTER_YEAR_LOWEST_DATE
        ACE_CString yearLowestDate(infoRec.lowestPriceDateWithinYear, sizeof ( infoRec.lowestPriceDateWithinYear ));
        masterMap.bind(MASTER_YEAR_LOWEST_DATE, yearLowestDate);

#if(1)
		ACE_CString strYearLowestPrice(infoRec.lowestPriceWithinYear, sizeof ( infoRec.lowestPriceWithinYear ));
		double stryearlowestprice = ::atof(strYearLowestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", stryearlowestprice * 100.0);
        masterMap.bind(MASTER_YEAR_LOWEST_PRICE, tempBuf);
#endif

        // MASTER_HIGHEST_PRICE_DATE
        ACE_CString highestPriceDate(infoRec.highestPriceDateWithinListing, sizeof ( infoRec.highestPriceDateWithinListing ));
        masterMap.bind(MASTER_HIGHEST_PRICE_DATE, highestPriceDate);

#if(1)
		ACE_CString strHighestPrice(infoRec.highestPriceWithinListing, sizeof ( infoRec.highestPriceWithinListing ));
		double strhighestprice = ::atof(strHighestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strhighestprice * 100.0);
        masterMap.bind(MASTER_HIGHEST_PRICE, tempBuf);
#endif

#if(1)
        // MASTER_LOWEST_PRICE_DATE
        ACE_CString lowestPriceDate(infoRec.lowestPriceDateWithinListing, sizeof ( infoRec.lowestPriceDateWithinListing ));
        masterMap.bind(MASTER_LOWEST_PRICE_DATE, lowestPriceDate);
#endif

#if(1)
		ACE_CString strLowestPrice(infoRec.lowestPriceWithinListing, sizeof ( infoRec.lowestPriceWithinListing ));
		double strlowestprice = ::atof(strLowestPrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", strlowestprice * 100.0);
        masterMap.bind(MASTER_LOWEST_PRICE, tempBuf);
#endif

        // MASTER_SESSION_DATE
        ACE_CString sessionDate(infoRec.hireDate, sizeof ( infoRec.hireDate ));
        masterMap.bind(MASTER_SESSION_DATE, sessionDate);

        // MASTER_SUBSTITUE_PRICE
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", getSubstitutePrice());
        masterMap.bind(MASTER_SUBSTITUE_PRICE, tempBuf);

        ACE_CString abbrSymbolFull(infoRec.abbrStockCode, sizeof ( infoRec.abbrStockCode ));
        masterMap.bind(MASTER_ABBR_SYMBOL_FULL, abbrSymbolFull);

        ACE_CString strMonthProductClassCode(infoRec.monthProductClassCode, sizeof ( infoRec.monthProductClassCode ));
        int monthProductClassCode = ::atoi(strMonthProductClassCode.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", monthProductClassCode);
        masterMap.bind(MASTER_SETTLEMENT_MONTH_NUMBER, tempBuf);

        ACE_CString expireDate(infoRec.expireDate, sizeof ( infoRec.expireDate ));
        masterMap.bind(MASTER_EXPIRE_DATE, expireDate);

        ACE_CString strExercisePrice(infoRec.exercisePrice, 11);
        int exercisePrice = ::atoi(strExercisePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", exercisePrice);
        masterMap.bind(MASTER_EXERCISE_PRICE, tempBuf);

#if(1)
        ACE_CString strTradeUnit(infoRec.tradeUnit, sizeof(infoRec.tradeUnit));
        int tradeUnit = ::atoi(strTradeUnit.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", tradeUnit / 1000);
        masterMap.bind(MASTER_TRADE_UNIT, tempBuf);
#endif

        ACE_CString strTradeMultiplier(infoRec.tradeMultiplier, 13);
        int tradeMultiplier = ::atoi(strTradeMultiplier.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", tradeMultiplier);
        masterMap.bind(MASTER_TRADING_MULTIPLIER, tempBuf);

        ACE_CString isTradeStop(infoRec.isTradeStop, sizeof ( infoRec.isTradeStop ));
        masterMap.bind(MASTER_SUSPENSION, getSuspensionType(isTradeStop));

        ACE_CString ATMClassCode(infoRec.ATMClassCode, sizeof ( infoRec.ATMClassCode ));
        masterMap.bind(MASTER_ATM_TYPE, getATMCode(ATMClassCode));

        ACE_CString isLastTradeDate(infoRec.isLastTradeDate, sizeof ( infoRec.isLastTradeDate ));
        masterMap.bind(MASTER_LAST_TRADING_DATE_CODE, isLastTradeDate);

        // for debug
        ACE_CString strIsHoliday(infoRec.isHoliday, sizeof ( infoRec.isHoliday ));

        ACE_CString isRealTimePriceLimit(infoRec.isRealTimePriceLimit, sizeof ( infoRec.isRealTimePriceLimit ));
        masterMap.bind(MASTER_IS_REAL_TIME_PRICE_LIMIT, isRealTimePriceLimit);

		ACE_CString signRealTimeUpperLimitPriceRange;

		if(infoRec.realTimeUpperLimitPriceRange[0]=='0') signRealTimeUpperLimitPriceRange = "+";
		else signRealTimeUpperLimitPriceRange = "-";

        ACE_CString realTimeUpperLimitPriceRange(infoRec.realTimeUpperLimitPriceRange, sizeof ( infoRec.realTimeUpperLimitPriceRange ));
        ACE_CString strRealTimeUpperLimitPriceRangeSigned;
        strRealTimeUpperLimitPriceRangeSigned = getSign(signRealTimeUpperLimitPriceRange) + realTimeUpperLimitPriceRange;

        int realTimeUpperLimitPriceRangeSigned = ::atoi(strRealTimeUpperLimitPriceRangeSigned.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", realTimeUpperLimitPriceRangeSigned);
        masterMap.bind(MASTER_REAL_TIME_UPPER_LIMIT_PRICE_RANGE, tempBuf);

        ACE_CString signRealTimeLowerLimitPriceRange;
		if(infoRec.realTimeLowerLimitPriceRange[0]=='0') signRealTimeLowerLimitPriceRange = "+";
		else signRealTimeLowerLimitPriceRange = "-";

        ACE_CString realTimeLowerLimitPriceRange(infoRec.realTimeLowerLimitPriceRange, sizeof ( infoRec.realTimeLowerLimitPriceRange ));
        ACE_CString strRealTimeLowerLimitPriceRangeSigned;
        strRealTimeLowerLimitPriceRangeSigned = getSign(signRealTimeLowerLimitPriceRange) + realTimeLowerLimitPriceRange;

        int realTimeLowerLimitPriceRangeSigned = ::atoi(strRealTimeLowerLimitPriceRangeSigned.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", realTimeLowerLimitPriceRangeSigned);
        masterMap.bind(MASTER_REAL_TIME_LOWER_LIMIT_PRICE_RANGE, tempBuf);

        ACE_CString price_limit_expansion_direction_code(infoRec.price_limit_expansion_direction_code, sizeof ( infoRec.price_limit_expansion_direction_code ));
        ACE_CString price_limit_final_step(infoRec.price_limit_final_step, sizeof ( infoRec.price_limit_final_step ));

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

        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_expansion_direction_code:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_expansion_direction_code.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_final_step:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_final_step.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_upper_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_upper_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_upper_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_lower_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_lower_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_1st_lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_1st_lower_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_upper_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_upper_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_upper_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_lower_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_lower_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_2nd_lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_2nd_lower_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_upper_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_upper_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_upper_limit_price.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_lower_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_lower_limit_price_sign.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tprice_limit_3rd_lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , price_limit_3rd_lower_limit_price.c_str() ));

        masterMap.bind(MASTER_PRICE_LIMIT_EXPANSION_TYPE, price_limit_expansion_direction_code);

        int limit_final_step = parseInt(price_limit_final_step, 0);
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%d", limit_final_step);
        masterMap.bind(MASTER_PRICE_LIMIT_FINAL_STEP, tempBuf);

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

        ACE_CString baseAssetStockCode(infoRec.baseAssetStockCode, sizeof ( infoRec.baseAssetStockCode ));
        masterMap.bind(MASTER_BASE_ASSET_SYMBOL, baseAssetStockCode);

#if(1)
        ACE_CString strBaseAssetClosePrice(infoRec.baseAssetClosePrice, sizeof ( infoRec.baseAssetClosePrice ));
		double baseAssetClosePrice = ::atof(strBaseAssetClosePrice.c_str());
        ::memset(tempBuf, 0, sizeof ( tempBuf ));
        ::sprintf(tempBuf, "%.0f", baseAssetClosePrice * 100.0);
        masterMap.bind(MASTER_BASE_ASSET_CLOSE_PRICE, tempBuf);
#endif

        ACE_CString underlyingAssetMarketID(infoRec.underlyingAssetMarketID, sizeof ( infoRec.underlyingAssetMarketID ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tunderlyingAssetMarketID:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , underlyingAssetMarketID.c_str() ));


#if(1)
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


        ACE_CString isSuspendedStocks(infoRec.isSuspendedStocks, sizeof ( infoRec.isSuspendedStocks ));
        masterMap.bind(MASTER_IS_SUSPENDED_STOCKS, isSuspendedStocks);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tisSuspendedStocks:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , isSuspendedStocks.c_str() ));

        ACE_CString designationDateForSuspendedStocks(infoRec.designationDateForSuspendedStocks, sizeof ( infoRec.designationDateForSuspendedStocks ));
        masterMap.bind(MASTER_DESIGNATION_DATE_FOR_SUSPENDED_STOCKS, designationDateForSuspendedStocks);
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tname:[%s]\tdesignationDateForSuspendedStocks:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , name.c_str() , designationDateForSuspendedStocks.c_str() ));


        tradeMap_.unbind(stockCode);
        openInterestMap_.unbind(stockCode);

        ACE_CString oldStockCode;
        ExturePlusKospi200FutureStockInfoRecord oldInfoRec;

        futureMasterMap_.rebind(stockCode, infoRec);
        masterMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), infoRec, oldStockCode, oldInfoRec, ALLOCATOR::instance());

        ACE_CString resultStr(makeMaster (masterMap));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMaster] stockCode:[%s]\tresultStr:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , resultStr.c_str() ));
        int result = sendPacket(makeMaster(masterMap), PACKET_MASTER, EXCHANGE_KSE);
        return result;
    }
}
#endif

#if(1)
int InternetKospi200FutureChannelProcessor::handleMarketOperation(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationTS] BEGIN\n" , getCurrentTimestamp().c_str() ));
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_MARKET_OPERATION_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperation] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_MARKET_OPERATION_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_MARKET_OPERATION_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } 

    ExturePlusKospi200FutureMarketOperationRecord rawOperationRec;
    ::memset(&rawOperationRec, 0, sizeof(ExturePlusKospi200FutureMarketOperationRecord));
    ::memcpy(&rawOperationRec, packet.c_str(), packet.length());

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

    ACE_CString stockCode(rawOperationRec.stockCode, sizeof ( rawOperationRec.stockCode ));
    if ( stockCode == "" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationTS] invalid issueCode:[%s][%d] skip......\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , stockCode.length() ));
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

int InternetKospi200FutureChannelProcessor::handleTradeAndQuote(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_TRADE_PRIORITY_QUOTE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTradeAndQuote] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_TRADE_PRIORITY_QUOTE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_TRADE_PRIORITY_QUOTE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    } // if 

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureTradePriorityQuoteRecord rawTradeQuoteRec;
    ::memset(&rawTradeQuoteRec, 0, sizeof(ExturePlusKospi200FutureTradePriorityQuoteRecord));
    ::memcpy(&rawTradeQuoteRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawTradeQuoteRec.stockCode, sizeof ( rawTradeQuoteRec.stockCode ));

    ACE_CString sessionID(rawTradeQuoteRec.sessionID, sizeof ( rawTradeQuoteRec.sessionID ));

    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleTradeAndQuote] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }
    else
    {
        Quote10 quote;
        ::memset(&quote, 0, sizeof(Quote10));
        quote.exchange = EXCHANGE_KSE;
        quote.symbolType = SYMBOL_FUTURE;
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
    }

    ExturePlusKospi200FutureStockInfoRecord infoRec;
    int hasMasterRec = futureMasterMap_.find(stockCode, infoRec);
    if ( hasMasterRec != -1 )
    {
#if(1)
        ACE_CString openPriceSign;
        ACE_CString highPriceSign;
        ACE_CString lowPriceSign;
        ACE_CString currentPriceSign;

		if(rawTradeQuoteRec.openPrice[0]=='0') openPriceSign = "+";
		else openPriceSign = "-";

		if(rawTradeQuoteRec.highPrice[0]=='0') highPriceSign = "+";
		else highPriceSign = "-";

		if(rawTradeQuoteRec.lowPrice[0]=='0') lowPriceSign = "+";
		else lowPriceSign = "-";

		if(rawTradeQuoteRec.currentPrice[0]=='0') currentPriceSign = "+";
		else currentPriceSign = "-";
#endif

        ACE_CString strOpenPrice(rawTradeQuoteRec.openPrice, sizeof ( rawTradeQuoteRec.openPrice ));
        ACE_CString strHighPrice(rawTradeQuoteRec.highPrice, sizeof ( rawTradeQuoteRec.highPrice ));
        ACE_CString strLowPrice(rawTradeQuoteRec.lowPrice, sizeof ( rawTradeQuoteRec.lowPrice ));
        ACE_CString strClosePrice(rawTradeQuoteRec.currentPrice, sizeof ( rawTradeQuoteRec.currentPrice ));
        ACE_CString strAccmTradeVolume(rawTradeQuoteRec.accmTradeVolume, sizeof ( rawTradeQuoteRec.accmTradeVolume ));

        strOpenPrice = openPriceSign + strOpenPrice;
        strOpenPrice = trim(strOpenPrice);

        strHighPrice = highPriceSign + strHighPrice;
        strHighPrice = trim(strHighPrice);

        strLowPrice = lowPriceSign + strLowPrice;
        strLowPrice = trim(strLowPrice);

        strClosePrice = currentPriceSign + strClosePrice;
        strClosePrice = trim(strClosePrice);

        int openPrice = ::atoi(strOpenPrice.c_str());
        int highPrice = ::atoi(strHighPrice.c_str());
        int lowPrice = ::atoi(strLowPrice.c_str());
        int closePrice = ::atoi(strClosePrice.c_str());
        double accmTradeVolume = ::atof(strAccmTradeVolume.c_str());

        if ( ( openPrice == 0 ) || ( highPrice == 0 ) || ( lowPrice == 0 ) || ( closePrice == 0 ) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTradeAndQuote] Skip : %s,%d stockCode:[%s] price is zero (%d, %d, %d, %d)\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , openPrice , highPrice , lowPrice , closePrice ), -1);
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
            int prevTime = trade.tradeTime;
            trade.tradeTime = tickTime;
            trade.market = getMarketInTrade(sessionID);

            ACE_CString strYdayClosePrice(infoRec.ydayClosePrice, sizeof ( infoRec.ydayClosePrice ));
            ACE_CString strStdPrice(infoRec.standardPrice, sizeof ( infoRec.standardPrice ));
            int ydayClosePrice = ::atoi(strYdayClosePrice.c_str());
            int stdPrice = ::atoi(strStdPrice.c_str());

            trade.upDown = getUpDownInTrade(ydayClosePrice, stdPrice, closePrice);
            trade.open = openPrice;
            trade.high = highPrice;
            trade.low = lowPrice;
            trade.close = closePrice;
            trade.ydayClose = ydayClosePrice;
            trade.tradeVolume = tradeVolume;
            trade.accmVolume = accmTradeVolume;

            ACE_CString strAmount(rawTradeQuoteRec.accmTradeAmount, sizeof ( rawTradeQuoteRec.accmTradeAmount ));
            trade.amount = ::atof(strAmount.c_str());
            trade.amount = trade.amount * 1000; // ëˆ„ì ê±°ëž˜ëŒ€ê¸ˆì€ 1000ì› ë‹¨ìœ„ìž„

            ExturePlusKospi200FutureOpenInterestVolumeRecord oiRec;
            ::memset(&oiRec, 0, sizeof(ExturePlusKospi200FutureOpenInterestVolumeRecord));
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
                trade.symbolType = SYMBOL_FUTURE;
                trade.decimalPoint = DECIMAL_2;

                memcpy(&trade.symbol, stockCode.c_str(), stockCode.length());

                trade.openMin = openPrice;
                trade.highMin = highPrice;
                trade.lowMin = lowPrice;
                trade.volumeMin = trade.tradeVolume;

                tradeMap_.rebind(stockCode, trade);
            }
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

#if(1)
            ACE_CString strSignForRealTimeUpperLimitPrice;
			if(rawTradeQuoteRec.realTimeUpperLimitPrice[0]=='0') strSignForRealTimeUpperLimitPrice = "+";
			else strSignForRealTimeUpperLimitPrice = "-";
#endif
            ACE_CString strRealTimeUpperLimitPrice(rawTradeQuoteRec.realTimeUpperLimitPrice, sizeof ( rawTradeQuoteRec.realTimeUpperLimitPrice ));

#if(1)
            ACE_CString strSignForRealTimeLowerLimitPrice;
			if(rawTradeQuoteRec.realTimeLowerLimitPrice[0]=='0') strSignForRealTimeLowerLimitPrice = "+";
			else strSignForRealTimeLowerLimitPrice = "-";
#endif
            ACE_CString strRealTimeLowerLimitPrice(rawTradeQuoteRec.realTimeLowerLimitPrice, sizeof ( rawTradeQuoteRec.realTimeLowerLimitPrice ));

            ACE_CString strUpperLimitPriceSigned;
            strUpperLimitPriceSigned = strSignForRealTimeUpperLimitPrice + strRealTimeUpperLimitPrice;
            double realTimeUpperLimitPrice = ::atof(strUpperLimitPriceSigned.c_str());

            ACE_CString strLowerLimitPriceSigned;
            strLowerLimitPriceSigned = strSignForRealTimeLowerLimitPrice + strRealTimeLowerLimitPrice;
            double realTimeLowerLimitPrice = ::atof(strLowerLimitPriceSigned.c_str());

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

            if ( isNearestFuture(stockCode) == true )
            {
                if ( isSpread(stockCode) == false )
                {
                    sendByNearestFuture(trade, limitRec);
                }
            }
        }
        else
        {
            if ( netVolume < 0 )
            {
                ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTradeAndQuote] Skip : %s,%d : net volume is below zero stockCode:[%s] netVolume:[%d]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , netVolume ), -1);
            }
        }
    }
    else
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleTradeAndQuote] Skip : %s,%d : cannot find matching master data stockCode:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() ), -1);
    }
    return 0;
}

#if(1)
int InternetKospi200FutureChannelProcessor::handleStockClose(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_CLOSE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleStockClose] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_CLOSE_RECORD_SIZE[%d] != packet.length()[%d] : [%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_STOCK_CLOSE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKospi200FutureStockCloseRecord rawCloseRec;
    ::memset(&rawCloseRec, 0, sizeof(ExturePlusKospi200FutureStockCloseRecord));
    ::memcpy(&rawCloseRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawCloseRec.stockCode, sizeof ( rawCloseRec.stockCode ));

    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleStockClose] skip ...... stockCode:[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
        return 0;
    }

	Trade trade;
    ::memset(&trade, 0, sizeof(Trade));
    int hasTradePrev = tradeMap_.find(stockCode, trade);
    if ( hasTradePrev != -1 )
    {
#if(1)
        ACE_CString closePriceSign;
		if(rawCloseRec.closePrice[0]=='0') closePriceSign = "+";
		else closePriceSign = "-";
#endif
        ACE_CString strClosePrice(rawCloseRec.closePrice, sizeof ( rawCloseRec.closePrice ));
        strClosePrice = closePriceSign + strClosePrice;
        strClosePrice = trim(strClosePrice);

        int closePrice = ::atoi(strClosePrice.c_str());
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
        printPacketTrade(trade);
        tradeMap_.rebind(stockCode, trade);
    }
    return 0;
}
#endif

int InternetKospi200FutureChannelProcessor::handleQuantityAllocation(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_QUANTITY_ALLOCATION_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleQuantityAllocation] Skip : %s, %d : EXTURE_PLUS_KOSPI_200_FUTURE_QUANTITY_ALLOCATION_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_QUANTITY_ALLOCATION_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKospi200FutureQuantityAllocationRecord allocationRec;
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

int InternetKospi200FutureChannelProcessor::handleRealTimeUpperLowerLimitPrice(const ACE_CString &packet)
{

    if ( EXTURE_PLUS_KOSPI_200_FUTURE_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleRealTimeUpperLowerLimitPrice] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
        return 0;
    }

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleRealTimeUpperLowerLimitPrice] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    ExturePlusKospi200FutureRealTimeUpperLowerLimitPriceRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200FutureRealTimeUpperLowerLimitPriceRecord));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));

#if(0)
    ACE_CString strSignForRealTimeUpperLimitPrice(rawRec.signForRealTimeUpperLimitPrice, sizeof ( rawRec.signForRealTimeUpperLimitPrice ));
#endif
#if(1)
    ACE_CString strSignForRealTimeUpperLimitPrice;
	if(rawRec.realTimeUpperLimitPrice[0]=='0') strSignForRealTimeUpperLimitPrice = "+";
	else strSignForRealTimeUpperLimitPrice = "-";
#endif
    ACE_CString strRealTimeUpperLimitPrice(rawRec.realTimeUpperLimitPrice, sizeof ( rawRec.realTimeUpperLimitPrice ));

#if(0)
    ACE_CString strSignForRealTimeLowerLimitPrice(rawRec.signForRealTimeLowerLimitPrice, sizeof ( rawRec.signForRealTimeLowerLimitPrice ));
#endif
#if(1)
    ACE_CString strSignForRealTimeLowerLimitPrice;
	if(rawRec.realTimeLowerLimitPrice[0]=='0') strSignForRealTimeLowerLimitPrice = "+";
	else strSignForRealTimeLowerLimitPrice = "-";
#endif

    ACE_CString strRealTimeLowerLimitPrice(rawRec.realTimeLowerLimitPrice, sizeof ( rawRec.realTimeLowerLimitPrice ));


    ACE_CString strUpperLimitPriceSigned;
    strUpperLimitPriceSigned = strSignForRealTimeUpperLimitPrice + strRealTimeUpperLimitPrice;
    double realTimeUpperLimitPrice = ::atof(strUpperLimitPriceSigned.c_str());

    ACE_CString strLowerLimitPriceSigned;
    strLowerLimitPriceSigned = strSignForRealTimeLowerLimitPrice + strRealTimeLowerLimitPrice;
    double realTimeLowerLimitPrice = ::atof(strLowerLimitPriceSigned.c_str());

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

#if(1)
printPacketRealTimeLimitPrice(limitRec);
#endif

    char bufSendPacket[REAL_TIME_LIMIT_PRICE_SIZE];
    ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
    ::memcpy(&bufSendPacket, &limitRec, sizeof(RealTimeLimitPrice));

	int resultLimitRec = sendPacket(ACE_CString(bufSendPacket, REAL_TIME_LIMIT_PRICE_SIZE), PACKET_REAL_TIME_LIMIT_PRICE, EXCHANGE_KSE);

	return ( resultLimitRec );
}

int InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_200_FUTURE_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] Skip : %s,%d : EXTURE_PLUS_KOSPI_200_FUTURE_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_200_FUTURE_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
        return ( 0 );
    }

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    ExturePlusKospi200FutureMarketOperationScheduleDisclosureRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200FutureMarketOperationScheduleDisclosureRecord));
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
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] market_operation_product_group_id:[%s]\n" , getCurrentTimestamp().c_str() , market_operation_product_group_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_id:[%s]\n" , getCurrentTimestamp().c_str() , board_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_event_id:[%s]\n" , getCurrentTimestamp().c_str() , board_event_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_event_start_time:[%s]\n" , getCurrentTimestamp().c_str() , board_event_start_time.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] board_event_group_code:[%s]\n" , getCurrentTimestamp().c_str() , board_event_group_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] session_start_end_code:[%s]\n" , getCurrentTimestamp().c_str() , session_start_end_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] session_id:[%s]\n" , getCurrentTimestamp().c_str() , session_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] step_applied:[%s]\n" , getCurrentTimestamp().c_str() , step_applied.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] price_expansion_trigger_code_for_base_issue:[%s]\n" , getCurrentTimestamp().c_str() , price_expansion_trigger_code_for_base_issue.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handleMarketOperationScheduleDisclosureRecord] price_expansion_expected_time:[%s]\n" , getCurrentTimestamp().c_str() , price_expansion_expected_time.c_str() ));

    return ( 0 );
}

int InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI200_FUTURE_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] Skip : %s,%d : EXTURE_PLUS_KOSPI200_FUTURE_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI200_FUTURE_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
        return ( 0 );
    }

    ExturePlusKospi200FuturePriceLimitRangeExpansionTriggerRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200FuturePriceLimitRangeExpansionTriggerRecord));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString board_id(rawRec.board_id, sizeof ( rawRec.board_id ));
    ACE_CString price_expansion_time(rawRec.price_expansion_time, sizeof ( rawRec.price_expansion_time ));
    ACE_CString the_upper_step_of_price_limit_expansion(rawRec.the_upper_step_of_price_limit_expansion, sizeof ( rawRec.the_upper_step_of_price_limit_expansion ));
    ACE_CString the_lower_step_of_price_limit_expansion(rawRec.the_lower_step_of_price_limit_expansion, sizeof ( rawRec.the_lower_step_of_price_limit_expansion ));

#if(1)
    ACE_CString upper_limit_price_sign;
	if(rawRec.upper_limit_price[0]=='0') upper_limit_price_sign = "+";
	else upper_limit_price_sign = "-";
#endif

    ACE_CString upper_limit_price(rawRec.upper_limit_price, sizeof ( rawRec.upper_limit_price ));

#if(1)
    ACE_CString lower_limit_price_sign;
	if(rawRec.lower_limit_price[0]=='0') lower_limit_price_sign = "+";
	else lower_limit_price_sign = "-";
#endif

    ACE_CString lower_limit_price(rawRec.lower_limit_price, sizeof ( rawRec.lower_limit_price ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] board_id:[%s]\n" , getCurrentTimestamp().c_str() , board_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] price_expansion_time:[%s]\n" , getCurrentTimestamp().c_str() , price_expansion_time.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] the_upper_step_of_price_limit_expansion:[%s]\n" , getCurrentTimestamp().c_str() , the_upper_step_of_price_limit_expansion.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] the_lower_step_of_price_limit_expansion:[%s]\n" , getCurrentTimestamp().c_str() , the_lower_step_of_price_limit_expansion.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] upper_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , upper_limit_price_sign.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , upper_limit_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] lower_limit_price_sign:[%s]\n" , getCurrentTimestamp().c_str() , lower_limit_price_sign.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePriceLimitRangeExpansionTriggerRecord] lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , lower_limit_price.c_str() ));

    PriceLimitRangeExpansionTrigger triggerRec;
    ::memset(&triggerRec, 0, sizeof(PriceLimitRangeExpansionTrigger));
    ::memcpy(& ( triggerRec.symbol ), issue_code.c_str(), issue_code.length());
    triggerRec.registerDt = (int) ( ::time(0) );
    ::memcpy(& ( triggerRec.boardId ), board_id.c_str(), board_id.length());
    ::memcpy(& ( triggerRec.priceExpansionTime ), price_expansion_time.c_str(), price_expansion_time.length());

    triggerRec.upperStepOfPriceLimitexpansion = parseInt(the_upper_step_of_price_limit_expansion, 0);
    triggerRec.lowerStepOfPriceLimitexpansion = parseInt(the_lower_step_of_price_limit_expansion, 0);

    upper_limit_price = upper_limit_price_sign + upper_limit_price;
    upper_limit_price = trim_ACE(upper_limit_price);

    lower_limit_price = lower_limit_price_sign + lower_limit_price;
    lower_limit_price = trim_ACE(lower_limit_price);

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

int InternetKospi200FutureChannelProcessor::handlePreMarketNegotiatedTradeDataRecord(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI200_FUTURE_PRE_MARKET_NEGOTIATED_TRADE_DATA_RECORD_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handlePreMarketNegotiatedTradeDataRecord] Skip : %s,%d : EXTURE_PLUS_KOSPI200_FUTURE_PRE_MARKET_NEGOTIATED_TRADE_DATA_RECORD_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI200_FUTURE_PRE_MARKET_NEGOTIATED_TRADE_DATA_RECORD_SIZE , packet.length() , packet.c_str() ), -1);
        return ( 0 );
    }

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePreMarketNegotiatedTradeDataRecord] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    ExturePlusKospi200FuturePreMarketNegotiatedTradeDataRecord rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKospi200FuturePreMarketNegotiatedTradeDataRecord));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString trade_value(rawRec.trade_value, sizeof ( rawRec.trade_value ));
    ACE_CString trading_volume_by_tick(rawRec.trading_volume_by_tick, sizeof ( rawRec.trading_volume_by_tick ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePreMarketNegotiatedTradeDataRecord] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePreMarketNegotiatedTradeDataRecord] trade_value:[%s]\n" , getCurrentTimestamp().c_str() , trade_value.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKospi200FutureChannelProcessor::handlePreMarketNegotiatedTradeDataRecord] trading_volume_by_tick:[%s]\n" , getCurrentTimestamp().c_str() , trading_volume_by_tick.c_str() ));

    int result = 0;
    return ( result );

}

BYTE InternetKospi200FutureChannelProcessor::getMarketStepInIndex(const ACE_CString& time)
{
    BYTE result = MARKET_IN;
    if ( time == "JUNJJJ" )
    {
        result = MARKET_END;
    }
    return result;
}

BYTE InternetKospi200FutureChannelProcessor::getUpDownInIndex(const ACE_CString& raw)
{
    BYTE result;
    if ( raw == "+" )
    {
        result = UPDOWN_UP;
    }
    else if ( raw == "-" )
    {
        result = UPDOWN_DOWN;
    }
    else
    {
        result = UPDOWN_STATIONARY;
    }
    return result;
}

ACE_CString InternetKospi200FutureChannelProcessor::getAbbrSymbol(const ACE_CString& symbol)
{
    return symbol.substring(3, 5);
}

int InternetKospi200FutureChannelProcessor::getTradeUnit()
{
    int defaultTradeUnit = 1;
    return defaultTradeUnit;
}

int InternetKospi200FutureChannelProcessor::getSubstitutePrice()
{
    int defaultSubstitutePrice = 0;
    return defaultSubstitutePrice;
}

BYTE InternetKospi200FutureChannelProcessor::getMarketInTrade(const ACE_CString &sessionID)
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

BYTE InternetKospi200FutureChannelProcessor::getUpDownInTrade(int ydayClose, int stdPrice, int currentPrice)
{
    if ( ydayClose != 0 )
    {
        if ( ydayClose > currentPrice )
        {
            return UPDOWN_DOWN;
        }
        else if ( ydayClose < currentPrice )
        {
            return UPDOWN_UP;
        }
        else
        {
            return UPDOWN_STATIONARY;
        }
    }
    else
    {
        if ( stdPrice > currentPrice )
        {
            return UPDOWN_DOWN;
        }
        else if ( stdPrice < currentPrice )
        {
            return UPDOWN_UP;
        }
        else
        {
            return UPDOWN_STATIONARY;
        }
    }
}

void InternetKospi200FutureChannelProcessor::sendByNearestFuture(const paxfeed::Trade& trade, const paxfeed::RealTimeLimitPrice& limitRec)
{
    const ACE_CString& symbol("KR4101000000");
    Trade nearTrade = trade;
    ::memcpy(&nearTrade.symbol, symbol.c_str(), symbol.length());
    char buf[TRADE_SIZE];
    memcpy(buf, &nearTrade, TRADE_SIZE);
    sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

    RealTimeLimitPrice nearLimitRec = limitRec;
    ::memcpy(&nearLimitRec.symbol, symbol.c_str(), symbol.length());

#if(0)
	//assignment of data-member `paxfeed::RealTimeLimitPrice::realTimeUpperLimitPrice' in read-only structure
	//assignment of data-member `paxfeed::RealTimeLimitPrice::realTimeUpperLimitPrice' in read-only structure
	//assignment of data-member `paxfeed::RealTimeLimitPrice::realTimeUpperLimitPrice' in read-only structure

limitRec.realTimeUpperLimitPrice = limitRec.realTimeUpperLimitPrice * 100;
limitRec.realTimeLowerLimitPrice = limitRec.realTimeLowerLimitPrice * 100;
#endif

    char bufSendPacket[REAL_TIME_LIMIT_PRICE_SIZE];
    ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
    ::memcpy(&bufSendPacket, &nearLimitRec, sizeof(RealTimeLimitPrice));
    sendPacket(ACE_CString(bufSendPacket, REAL_TIME_LIMIT_PRICE_SIZE), PACKET_REAL_TIME_LIMIT_PRICE, EXCHANGE_KSE);
}

int InternetKospi200FutureChannelProcessor::handleKoscomLineLKInfo(const ACE_CString &packet)
{

    if ( EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_FUTURE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKospi200FutureChannelProcessor::handleKoscomLineLKInfo] Skip : %s,%d : EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_FUTURE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_FUTURE_SIZE , packet.length() , packet.c_str() ), -1);
        return 0;
    }

    ExturePlusKoscomLineLKInfo_KOSPI200_FUTURE rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKoscomLineLKInfo_KOSPI200_FUTURE));
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

    return ( result );
}

int InternetKospi200FutureChannelProcessor::getRegisterDt()
{
    time_t registerDt = ::time(0);
    struct tm tmRegisterDt = *::localtime(&registerDt);
    registerDt = ::mktime(&tmRegisterDt);
    return ( registerDt );
}

const std::vector<ACE_CString>& InternetKospi200FutureChannelProcessor::getTradeTypeList()
{
    return ( tradeTypeList_ );
}

void InternetKospi200FutureChannelProcessor::initTradeTypeList()
{
    return;
}

ACE_CString InternetKospi200FutureChannelProcessor::getSuspensionType(const ACE_CString& raw)
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

ACE_CString InternetKospi200FutureChannelProcessor::getATMCode(const ACE_CString& raw)
{
    ACE_CString result;

    if ( raw == "0" )
    {
        result = "¼±¹°";
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
        result = "¹ÌÁöÁ¤";
    }
    return result;
}

ACE_CString InternetKospi200FutureChannelProcessor::getSign(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "-" )
    {
        result = "-";
    }
    return result;
}

int InternetKospi200FutureChannelProcessor::getCurrentTimeUTC(const ACE_CString &sessionID)
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

int InternetKospi200FutureChannelProcessor::getTickTimeUTCByTimestamp(const ACE_CString &timeStr, const ACE_CString &sessionID)
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


