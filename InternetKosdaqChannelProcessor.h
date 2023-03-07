#ifndef _INTERNET_KOSDAQ_CHANNEL_PROCESSOR_H
#define _INTERNET_KOSDAQ_CHANNEL_PROCESSOR_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "PaxfeedAceHelper.h"
#include "ExturePlusInternetKosdaq.h"
#include "InternetChannelProcessor.h"
#include "PaxfeedPacket.h"

class InternetKosdaqChannelProcessor: public InternetChannelProcessor
{
    public:
        InternetKosdaqChannelProcessor(const ACE_CString &channelName);
        ~InternetKosdaqChannelProcessor();
        int reset();

    private:
        int processPacket(const ACE_CString &packet);

        //handler
        bool isValidSymbol(const ACE_CString& symbol);

        int handleTrade(const ACE_CString &packet);
        int handleBulkTrade(const ACE_CString &packet);
        int handleMarket(const ACE_CString &packet);
        int handleRecoveryTrade(const ACE_CString &packet);
        int handleIndexWIthCode(const ACE_CString &packet);
        int handleIndex(const ACE_CString &packet);
        int handleQuote10(const ACE_CString &packet);
        int handleQuote10Fixed(const ACE_CString &packet);
        int handleSecuritiesTrade(const ACE_CString &packet);
        int handleInvestorIndex(const ACE_CString &packet);
        int handleProgramTrade(const ACE_CString &packet);
        int handleProgramTradePublic(const ACE_CString &packet);
        int handleProgramTradeTotal(const ACE_CString &packet);
        int handleProgramTradeBatch(const ACE_CString &packet);
        int handlePublicNews(const ACE_CString &packet);

        int handleRecoveryTradeFixed(const ACE_CString &packet);
        int handleTradeFixed(const ExturePlusKosdaqTrade &kosdaq);
        int handleInvestorStock(const ACE_CString &packet);
        int handleUpDown(const ACE_CString &packet);

        int handleIndexForecast(const ACE_CString &packet);

        int handleMarketOperationScheduleDisclosure(const ACE_CString &packet);
        int handleMarketOperationTS(const ACE_CString &packet);

        int handleShortSellingInfo(const ACE_CString &packet);

        int handleQuantityAllocation(const ACE_CString &packet);
        int handleETF_PDF(const ACE_CString &packet);

        int handleKOSDAQVolatilityInterruptionPerInstrument(const ACE_CString &packet);

        int handleKoscomLineLKInfo(const ACE_CString &packet);

        int handleKOSDAQIssueEventInformation(const ACE_CString &packet);

        int handleCustomIndexRecovery(const ACE_CString &packet);

        int handleDeterminedBasePrice(const ACE_CString &packet);
        int handleIssueInformationDisclosure(const ACE_CString &packet);
		
#if(1)
	    int handleRecoveryTotalTrade(const ACE_CString &packet);
#endif		

        ACE_CString getIndexSymbol(int code, const ACE_CString &frameId = "");
        BYTE getMarketInTrade(const ACE_CString& raw);
        BYTE getMarketStepInIndex(const ACE_CString& time);
        BYTE getUpDownInTrade(const ACE_CString& raw);
        BYTE getUpDownInIndex(const ACE_CString& raw);
        BYTE getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID);
        BYTE getCommitType(const ACE_CString& raw);
        BYTE getNearSymbolType(const ACE_CString& raw);

        ACE_CString getEx(const ACE_CString& rawEx);
        ACE_CString getCapitalReduction(const ACE_CString& rawEx);
        ACE_CString getSplitMerge(const ACE_CString& rawEx);
        ACE_CString getManagementType(const ACE_CString& raw);
        ACE_CString getSuspensionType(const ACE_CString& raw);
        ACE_CString getVenture(const ACE_CString& raw);
        ACE_CString getTotalMarketPriceType(const ACE_CString& raw);
        ACE_CString getKogiType(const ACE_CString& raw);
        ACE_CString getCautionType(const ACE_CString& rawAlarm);
        ACE_CString getTradeUnit(const ACE_CString& raw);
        ACE_CString getIsDividendIndexStock(const ACE_CString& raw);
        int getTickTime(const ACE_CString &timeStr, const ACE_CString &frameId);
        BYTE getMarketStatusInMarket(const ACE_CString& raw);
		
#if(1)
	ACE_CString getSymbolFrameId(const ACE_CString& raw);
	ACE_CString getSymbolUpCode(const ACE_CString& raw);
#endif		

        BYTE getMarketInRecoveryTrade(const ACE_CString& frameId, const ACE_CString& boardID, const ACE_CString& boardEventID);
		BYTE getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID);

        BYTE getMarketInRecoveryTradeFixed(const ACE_CString& market);
        ACE_CString getIndustryClassCode(const ACE_CString& industryClassMid, const ACE_CString& industryClassSmall);

        static ACE_CString getEpsSign(const ACE_CString& raw);
        static BYTE getSubType(const ACE_CString& frameId, const ACE_CString& quotation);

        const std::vector<ACE_CString> &getTradeTypeList();
        void initTradeTypeList();
        BYTE getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID);
        int getRegisterDt();

    private:
        std::vector<ACE_CString> tradeTypeList_;
};

#endif

