#if !defined(_INTERNET_KOSPI_200_OPTION_CHANNEL_PROCESSOR_H_20040325_)
#define _INTERNET_KOSPI_200_OPTION_CHANNEL_PROCESSOR_H_20040325_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "PaxfeedAceHelper.h"
#include "InternetChannelProcessor.h"
#include "PaxfeedPacket.h"
#include "ExturePlusInternetKospi200Option.h"

class UDPKospi200OptionMasterRecord;
class UDPKospi200OptionOpenInterestVolumeRecord;

class InternetKospi200OptionChannelProcessor: public InternetChannelProcessor
{
    public:
        InternetKospi200OptionChannelProcessor(const ACE_CString &channelName);
        ~InternetKospi200OptionChannelProcessor();

        int reset();

    private:
        int processPacket(const ACE_CString &packet);

        //handler
        int handleQuote(const ACE_CString &packet);
        int handleTrade(const ACE_CString &packet);
        int handleInvestor(const ACE_CString &packet);
        int handleOpenInterestVolume(const ACE_CString &packet);

        int handleMaster(const ACE_CString &packet);
        int handleRecovery(const ACE_CString &packet);
        int handleTradeMarginStandardPrice(const ACE_CString &packet);

        int handleMarketOperation(const ACE_CString &packet);
        int handleStockClose(const ACE_CString &packet);
        int handleTradeAndQuote(const ACE_CString &packet);

        int handlePreMarketNegotiatedTrade(const ACE_CString &packet);
        int handleSensitivity(const ACE_CString &packet);

        int handleQuantityAllocation(const ACE_CString &packet);

        int handleRealTimeUpperLowerLimitPrice(const ACE_CString &packet);

        int handleMarketOperationScheduleDisclosureRecord(const ACE_CString &packet);
        int handlePriceLimitRangeExpansionTriggerRecord(const ACE_CString &packet);

        ACE_CString getOptionType(const ACE_CString &raw);
        ACE_CString getExerciseType(const ACE_CString& raw);
        ACE_CString getYdayCloseType(const ACE_CString& raw);

        int getTradeUnit();
        int getSubstitutePrice();
        ACE_CString getAbbrSymbol(const ACE_CString& symbol);

        BYTE getMarketInTrade(const ACE_CString &sessionID);
//        int getTickTime(const ACE_CString &sessionID);
        int getUpDownInTrade(int prevValue, int currValue);
        ACE_CString getSymbol(const ACE_CString& raw);
        int handleKoscomLineLKInfo(const ACE_CString &packet);

        ACE_CString getSuspensionType(const ACE_CString& raw);
        ACE_CString getATMCode(const ACE_CString& raw);
        ACE_CString getSign(const ACE_CString& raw);

        int getCurrentTimeUTC(const ACE_CString &sessionID);
        int getTickTimeUTCByTimestamp(const ACE_CString &timeStr, const ACE_CString &sessionID);

    protected:
        const std::vector<ACE_CString> &getTradeTypeList();
        void initTradeTypeList();

    protected:
        std::vector<ACE_CString> tradeTypeList_;

        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKospi200OptionStockInfoRecord> MasterMap;
        typedef ACE_Hash_Map_Manager<ACE_CString, paxfeed::Trade, ACE_Null_Mutex> TradeMap;
        typedef ACE_Hash_Map_Manager<ACE_CString, ExturePlusKospi200OptionOpenInterestVolumeRecord, ACE_Null_Mutex> OpenInterestMap;
        typedef ACE_Hash_Map_Manager<ACE_CString, ExturePlusKospi200OptionStockInfoRecord, ACE_Null_Mutex> OptionMasterMap;

        MasterMap* masterMap_;
        OptionMasterMap optionMasterMap_;
        TradeMap tradeMap_;
        OpenInterestMap openInterestMap_;
};

#endif
