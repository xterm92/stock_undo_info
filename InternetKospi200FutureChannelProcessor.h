#if !defined(_INTERNET_KOSPI_200_FUTURE_CHANNEL_PROCESSOR_H_20040325_)
#define _INTERNET_KOSPI_200_FUTURE_CHANNEL_PROCESSOR_H_20040325_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "PaxfeedAceHelper.h"
#include "InternetChannelProcessor.h"
#include "PaxfeedPacket.h"
#include "ExturePlusInternetKospi200Future.h"

class UDPKospi200FutureMasterRecord;
class UDPKospi200FutureOpenInterestVolumeRecord;
class UDPKospi200FutureTradeStatusByInvestorRecord;

class InternetKospi200FutureChannelProcessor: public InternetChannelProcessor
{
    public:
        InternetKospi200FutureChannelProcessor(const ACE_CString &channelName);
        ~InternetKospi200FutureChannelProcessor();

        int reset();

    private:
        int processPacket(const ACE_CString &packet);

        //handler
        int handleQuote(const ACE_CString &packet);
        int handleTrade(const ACE_CString &packet);
        int handleInvestor(const ACE_CString &packet);
        int handleOpenInterestVolume(const ACE_CString &packet);
        int handleAdjustedPrice(const ACE_CString &packet);
        int handleMaster(const ACE_CString &packet);
        int handleMarketOperation(const ACE_CString &packet);
        int handleRecovery(const ACE_CString &packet);
        int handleStockClose(const ACE_CString &packet);
        int handleTradeAndQuote(const ACE_CString &packet);

        int handleQuantityAllocation(const ACE_CString &packet);

        int handleRealTimeUpperLowerLimitPrice(const ACE_CString &packet);

        int handleMarketOperationScheduleDisclosureRecord(const ACE_CString &packet);
        int handlePriceLimitRangeExpansionTriggerRecord(const ACE_CString &packet);

        int handlePreMarketNegotiatedTradeDataRecord(const ACE_CString &packet);


        BYTE getMarketStepInIndex(const ACE_CString& time);
        BYTE getUpDownInIndex(const ACE_CString& raw);

        ACE_CString getAbbrSymbol(const ACE_CString& symbol);
        int getTradeUnit();
        int getSubstitutePrice();

        BYTE getMarketInTrade(const ACE_CString &sessionID);
        // int getTickTime(const ACE_CString &sessionID);
        bool isSpread(const ACE_CString &symbol);

        BYTE getUpDownInTrade(int ydayClose, int stdPrice, int currentPrice);
        void sendByNearestFuture(const paxfeed::Trade& trade, const paxfeed::RealTimeLimitPrice& limitRec);
        int handleInvestorForNormal(const ExturePlusKospi200FutureInvestorRecord &rawInvestorRec);
        int handleInvestorForSpread(const ExturePlusKospi200FutureInvestorRecord &rawInvestorRec);
        int getRegisterDt();

        int handleKoscomLineLKInfo(const ACE_CString &packet);

        ACE_CString getSuspensionType(const ACE_CString& raw);
        ACE_CString getATMCode(const ACE_CString& raw);
        ACE_CString getSign(const ACE_CString& raw);

        bool isNearestFuture(const ACE_CString& stockCode);

        int getSettlementType(const ACE_CString rawSettlementType);
        int getLastSettlementType(const ACE_CString rawLastSettlementType);

        int getCurrentTimeUTC(const ACE_CString &sessionID);
        int getTickTimeUTCByTimestamp(const ACE_CString &timeStr, const ACE_CString &sessionID);

    protected:
        const std::vector<ACE_CString> &getTradeTypeList();
        void initTradeTypeList();

    protected:
        std::vector<ACE_CString> tradeTypeList_;
        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKospi200FutureStockInfoRecord> MasterMap;
        typedef ACE_Hash_Map_Manager<ACE_CString, paxfeed::Trade, ACE_Null_Mutex> TradeMap;
        typedef ACE_Hash_Map_Manager<ACE_CString, ExturePlusKospi200FutureOpenInterestVolumeRecord, ACE_Null_Mutex> OpenInterestMap;
        typedef ACE_Hash_Map_Manager<ACE_CString, ExturePlusKospi200FutureStockInfoRecord, ACE_Null_Mutex> FutureMasterMap;

        MasterMap* masterMap_;
        FutureMasterMap futureMasterMap_;
        TradeMap tradeMap_;
        OpenInterestMap openInterestMap_;
};

#endif

