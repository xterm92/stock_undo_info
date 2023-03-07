#ifndef _INTERNET_KSE_CHANNEL_PROCESSOR_H
#define _INTERNET_KSE_CHANNEL_PROCESSOR_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "PaxfeedAceHelper.h"
#include "InternetChannelProcessor.h"
#include "PaxfeedPacket.h"
#include "ExturePlusInternetKse.h"

class InternetKseChannelProcessor: public InternetChannelProcessor
{
    public:
        InternetKseChannelProcessor(const ACE_CString &channelName);
        ~InternetKseChannelProcessor();

        int reset();

    private:

        bool isValidSymbol(const ACE_CString& symbol);

        int processPacket(const ACE_CString &packet);

        //handler
        int handleTrade(const ACE_CString &packet);
        int handleBulkTrade(const ACE_CString &packet);
        int handleMarket(const ACE_CString &packet);
		int handleRecoveryTotalTrade(const ACE_CString &packet);
        int handleRecoveryTrade(const ACE_CString &packet);
        int handleUpDown(const ACE_CString &packet);
        int handleUpDownIndex(const ACE_CString &packet);
        int handleIndex(const ACE_CString &packet);
        int handleEquallyWeightedIndex(const ACE_CString &packet);
        int handleEquallyWeightedIndexForecast(const ACE_CString &packet);
        int handleForeignerMaster(const ACE_CString &packet);
        int handleForeignerMasterUpdate(const ACE_CString &packet);
        int handleForeigner(const ACE_CString &packet);
        int handleQuote10(const ACE_CString &packet);
        int handleQuoteBefore(const ACE_CString &packet);
        int handleQuote10Fixed(const ACE_CString &packet);
        int handleSecuritiesTrade(const ACE_CString &packet);

        int handleInvestorIndex(const ACE_CString &packet);
        int handleProgramTrade(const ACE_CString &packet);
        int handleProgramTradePublic(const ACE_CString &packet);
        int handleProgramTradeTotal(const ACE_CString &packet);
        int handleProgramTradeBatch(const ACE_CString &packet);
        int handlePublicNews(const ACE_CString &packet);
        int handleRecoveryTradeFixed(const ACE_CString &packet);

        int handleTradeFixed(const ExturePlusKseTrade &kse);
        int handleInvestorStock(const ACE_CString &packet);
        int handleIndexForecast(const ACE_CString &packet);
        int handleETFWorkEntrustmentBatch(const ACE_CString &packet);

        int handleMarketOperationScheduleDisclosure(const ACE_CString &packet);
        int handleMarketOperationTS(const ACE_CString &packet);
        int handleShortSellingInfo(const ACE_CString &packet);

        int handleQuantityAllocation(const ACE_CString &packet);
        int handleETF_PDF(const ACE_CString &packet);
        int handleKospi200FutureIndex(const ACE_CString &packet);

        int handleKOSPIVolatilityInterruptionPerInstrument(const ACE_CString &packet);

        int handleKoscomLineLKInfo(const ACE_CString &packet);

        int handleETNTransferAgentBatchData(const ACE_CString &packet);
        int handleETNIndexCompositionConstituents(const ACE_CString &packet);
        int handleETN_IIV(const ACE_CString &packet);

        int handleETNInformationBatch(const ACE_CString &packet);

        int handleKOSPIIssueEventInformation(const ACE_CString &packet);

        int handleCustomIndexRecovery(const ACE_CString &packet);
        int handleDeterminedBasePrice(const ACE_CString &packet);

        int handleETP_Constituents(const ACE_CString &packet);

        int handleETNProfitStructureDetails(const ACE_CString &packet);
        int handleETNEarlyRedemptionCriteria(const ACE_CString &packet);
        int handleIssueInformationDisclosure(const ACE_CString &packet);

        ACE_CString getIndexSymbol(int code, const ACE_CString &frameId = "");
        BYTE getMarketInTrade(const ACE_CString& raw);
        BYTE getMarketStepInIndex(const ACE_CString& time);
        BYTE getUpDownInTrade(const ACE_CString& raw);
        BYTE getUpDownInIndex(const ACE_CString& raw);
        BYTE getExhaustInForeigner(const ACE_CString& raw);
        BYTE getSign(const ACE_CString& raw);
        BYTE getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID);
        ACE_CString getKospi200Type(const ACE_CString& raw);
        int getTickTime(const ACE_CString& timeStr, const ACE_CString &frameId);
        BYTE getMarketStatusInMarket(const ACE_CString& raw);

        BYTE getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID);

        BYTE getStockType(const ACE_CString& raw);
        BYTE getCommitType(const ACE_CString& raw);
        BYTE getNearSymbolType(const ACE_CString& raw);
        BYTE getSymbolType(char rawSymbolType);
        BYTE getExchange(char rawSymbolType);
        BYTE getMarketInTradeFixed(const ACE_CString& raw);
        BYTE getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID);
        const ACE_CString& getInvestorCode(const ACE_CString& raw);
        static time_t getModTime(time_t tradeTime);
        int getRegisterDt();
        int getRegisterDt(const ACE_CString &imsiTime);

#if(1)
	ACE_CString getSymbolFrameId(const ACE_CString& raw);
	ACE_CString getSymbolUpCode(const ACE_CString& raw);

#endif

#if(1)
	int InternetKseChannelProcessor::handleElwRecoveryTotalTrade(const ACE_CString &packet);
#endif

    protected:
        const std::vector<ACE_CString> &getTradeTypeList();
        void initTradeTypeList();

    protected:
        std::vector<ACE_CString> tradeTypeList_;
};

#endif
