// hannelProcessor.h: interface for the ChannelProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANNELPROCESSOR_H__8882EDD1_C5BE_4301_A011_DA4D286BD871__INCLUDED_)
#define AFX_CHANNELPROCESSOR_H__8882EDD1_C5BE_4301_A011_DA4D286BD871__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PaxfeedDefine.h"
#include "ace/Map_Manager.h"
#include "ace/Hash_Map_Manager.h"
#include "PaxfeedAceHelper.h"
#include "PaxfeedPacket.h"
#include "PaxfeedPacketELW.h"
#include "PacketWrappers.h"
#include "Tickerplant.h"

class ChannelProcessor
{
    public:
        ChannelProcessor();
        ChannelProcessor(const ACE_CString &channelName);
        virtual ~ChannelProcessor();

        virtual int reset();
        virtual int processPacket(const ACE_CString &packet) = 0;

        void LogFrameCount(const ACE_CString& frameId);
        int xmit(const char* buf, int bufSise);
        int sendPacket(const ACE_CString &body, BYTE packetType, BYTE exchange);
        int getSerial();

        time_t getTime(const ACE_CString& date);

        ACE_CString makeMaster(ACE_Map_Manager<ACE_CString, ACE_CString, ACE_Null_Mutex> &map);
        void flushPacket();

        void sendTrade(paxfeed::Trade& trade);
        void sendQuote10(paxfeed::Quote10& quote);
        void sendELWQuote10LPIncluded(paxfeed::ELWQuote10LPIncluded& elwQuote);
        bool isSameMinute(int currentTime, int prevTime);

        ACE_CString getCurrentTimestamp();
    protected:
        ACE_Hash_Map_Manager<ACE_CString, paxfeed::Trade, ACE_Null_Mutex> compressedTradeMap_;
        ACE_Hash_Map_Manager<ACE_CString, paxfeed::Quote10, ACE_Null_Mutex> compressedQuote10Map_;
        ACE_Hash_Map_Manager<ACE_CString, paxfeed::ELWQuote10LPIncluded, ACE_Null_Mutex> compressedELWQuote10LPIncludedMap_;
        ACE_CString channelName_;

    private:
        int seq_;
        char packetBuf_[PAXFEED_MAX_PACKET_SIZE]; //전송할 버퍼를 미리 생성해 둔다.

    private:
        HeaderWrapper headerWrapper_;
        TradeWrapper tradeWrapper_;
        TradeFixedWrapper tradeFixedWrapper_;
        Quote10Wrapper quote10Wrapper_;
        QuotePriceWrapper quotePriceWrapper_;
        QuoteVolumeWrapper quoteVolumeWrapper_;
        MarketWrapper marketWrapper_;
        UpDownWrapper upDownWrapper_;
        ForeignerWrapper forignerWrapper_;
        ForeignerMasterWrapper foreignerMasterWrapper_;
        SecuritiesTradeWrapper securitiesTradeWrapper_;
        InvestorWrapper investorWrapper_;
        ProgramTradeTotalWrapper programTradeTotalWrapper_;
        ProgramTradeWrapper programTradeWrapper_;
        ProgramTradeBatchWrapper programTradeBatchWrapper_;
        SecuritiesTrade2Wrapper securitiesTrade2Wrapper_;
        ShortSellingInfoWrapper shortSellingInfoWrapper_;
        KoscomLineLKInfoWrapper koscomLineLKInfoWrapper_;
        MarketOperationWrapper marketOperationWrapper_;
        BlockTradeWrapper blockTradeWrapper_;
        RealTimeLimitPriceWrapper realTimeLimitPriceWrapper_;
        VolatilityInterruptionPerInstrumentWrapper volatilityInterruptionPerInstrumentWrapper_;
        VolatilityInterruptionPerInstrument2Wrapper volatilityInterruptionPerInstrument2Wrapper_;

        ETNTransferAgentBatchDataWrapper etnTransferAgentBatchDataWrapper_;
        ETNIndexCompositionConstituentsWrapper etnIndexCompositionConstituentsWrapper_;
        ETN_IIVWrapper etnIIVWrapper_;
        ETNInformationBatchWrapper etnInformationBatchWrapper_;

        KOSPI200IndexFutureSettledPriceDataWrapper kospi200IndexFutureSettledPriceDataWrapper_;
        KOSPI_KOSDAQ_IssueEventInformationWrapper kospiKosdaqIssueEventInformationWrapper_;

        ELWQuote10LPIncludedWrapper elwQuote10LPIncludedWrapper_;
        ELWTradeWrapper elwTradeWrapper_;

        ELWEarlyClosedELWBatchWrapper elwEarlyClosedELWBatchWrapper_;

        ELWSecuritiesTradeWrapper elwSecuritiesTradeWrapper_;
        ELWMarketOperationWrapper elwMarketOperationWrapper_;

        PriceLimitRangeExpansionTriggerWrapper priceLimitRangeExpansionTriggerWrapper_;

        ELW_LP_InformationWrapper elwLPInformationWrapper_;

        DeterminedBasisPriceWrapper determinedBasisPriceWrapper_;

};

#endif

