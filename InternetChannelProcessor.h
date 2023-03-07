// channelProcessor.h: interface for the InternetChannelProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERNETCHANNELPROCESSOR_H__8882EDD1_C5BE_4301_A011_DA4D286BD871__INCLUDED_)
#define AFX_INTERNETCHANNELPROCESSOR_H__8882EDD1_C5BE_4301_A011_DA4D286BD871__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "ChannelProcessor.h"
#include "InvestorCodeConverter.h"

#include "ExturePlusInternetKse.h"
#include "ExturePlusInternetKosdaq.h"
#include "ExturePlusInternetElw.h"

class InternetChannelProcessor: public ChannelProcessor
{
    public:
        InternetChannelProcessor();
        InternetChannelProcessor(const ACE_CString &channelName);
        virtual ~InternetChannelProcessor();
        int reset();

        virtual void printPacketTrade(const Trade trade);
        virtual void printPacketQuote10(const Quote10 quote);
        virtual void printPacketUpDown(const UpDown updown);
        virtual void printPacketForeignerMaster(const ForeignerMaster master);
        virtual void printPacketForeigner(const Foreigner foreigner);
        virtual void printPacketQuoteVolume(const QuoteVolume quote);
        virtual void printPacketSecuritiesTrade2(const SecuritiesTrade2 sec);
        virtual void printPacketInvestor(const Investor investor);
        virtual void printPacketProgramTrade(const ProgramTrade trade);
        virtual void printPacketProgramTradeTotal(const ProgramTradeTotal tradeTotal);
        virtual void printPacketProgramTradeBatch(const ProgramTradeBatch batch);
        virtual void printPacketShortSellingInfo(const ShortSellingInfo info);
        virtual void printPacketMarketOperation(const MarketOperation market);
        virtual void printPacketBlockTrade(const BlockTrade blockRec);

        virtual void printPacketRealTimeLimitPrice(const RealTimeLimitPrice limitRec);

        virtual void printPacketVolatilityInterruptionPerInstrument(const VolatilityInterruptionPerInstrument viRec);
        virtual void printPacketVolatilityInterruptionPerInstrument2(const VolatilityInterruptionPerInstrument2 viRec);

        virtual void printPacketETNTransferAgentBatchData(const ETNTransferAgentBatchData batchData);
        virtual void printPacketETNIndexCompositionConstituents(const ETNIndexCompositionConstituents constituent);
        virtual void printPacketETN_IIV(const ETN_IIV iiv);

        virtual void printPacketETNInformationBatch(const ETNInformationBatch batch);

        virtual int getMarketBasedCurrentTime();

        virtual void printPacketKOSPI200IndexFutureSettledPriceData(const KOSPI200IndexFutureSettledPriceData priceData);

        virtual void printPacketKOSPI_KOSDAQ_IssueEventInformation(const KOSPI_KOSDAQ_IssueEventInformation infoRec);

        virtual void printPacketELWQuote10LPIncluded(const ELWQuote10LPIncluded elwQuote);
        virtual void printPacketELWTrade(const ELWTrade elwTrade);

        virtual void printPacketELWEarlyClosedELWBatch(const ELWEarlyClosedELWBatch elwBatch);

        virtual void printPacketELWSecuritiesTrade(const ELWSecuritiesTrade sec);
        virtual void printPacketELWMarketOperation(const ELWMarketOperation market);

        virtual void printPacketPriceLimitRangeExpansionTrigger(const PriceLimitRangeExpansionTrigger triggerRec);

        virtual void printPacketELW_LP_Information(const ELW_LP_Information infoRec);

        virtual void printPacketDeterminedBasisPrice(const DeterminedBasisPrice priceRec);

    protected:
        double getAccmVolume(const ACE_CString &symbol, const ACE_CString &tradePriceType);
        void setAccmVolume(const ACE_CString &symbol, double volume, const ACE_CString &tradePriceType);

        double getTotalAccmVolume(const ACE_CString &symbol);
        void setTotalAccmVolume(const ACE_CString &symbol, double volume);

        double getAccmAmount(const ACE_CString &symbol, const ACE_CString &tradePriceType);
        void setAccmAmount(const ACE_CString &symbol, double amount, const ACE_CString &tradePriceType);

        double getTotalAccmAmount(const ACE_CString &symbol);
        void setTotalAccmAmount(const ACE_CString &symbol, double amount);

        void updateAccmVolume(const ACE_CString &symbol);
        void updateAccmAmount(const ACE_CString &symbol);

        virtual const std::vector<ACE_CString> &getTradeTypeList() = 0;

    protected:
        typedef ACE_Hash_Map_With_Allocator<ACE_CString, double> AccmSizeMap;
        AccmSizeMap* accmVolumeMap_;
        AccmSizeMap* accmAmountMap_;

        // 거래량 데이터를 map에 저장시에 오류가 발생하여 전체 누적을 별도 메모리로 분리함.
        AccmSizeMap* totalAccmVolumeMap_;
        AccmSizeMap* totalAccmAmountMap_;

        typedef ACE_Hash_Map_With_Allocator<ACE_CString, paxfeed::Trade> TradeMap;
        typedef ACE_Hash_Map_With_Allocator<ACE_CString, paxfeed::ELWTrade> ELWTradeMap;

        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKseProgramTradePublic> ProgramTradeMapPublicKse;
        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKosdaqProgramTradePublic> ProgramTradeMapPublicKosdaq;

        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKseRecoveryTradeFixed> ExturePlusKseRecoveryTradeFixedMap;
        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKosdaqRecoveryTradeFixed> ExturePlusKosdaqRecoveryTradeFixedMap;

        TradeMap* tradeMap_;
        ELWTradeMap* elwTradeMap_;
        ProgramTradeMapPublicKse* programTradeMapKse_;
        ProgramTradeMapPublicKosdaq* programTradeMapKosdaq_;

#if(1)
        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKseMaster> ExturePlusMasterMapKse;
        typedef ACE_Hash_Map_With_Allocator<ACE_CString, ExturePlusKosdaqMaster> ExturePlusMasterMapKosdaq;

		ExturePlusMasterMapKse* masterMapKse_;
		ExturePlusMasterMapKosdaq* masterMapKosdaq_;
#endif

        InvestorCodeConverter invConv_;

        ExturePlusKseRecoveryTradeFixedMap* tradeFixedMapKse_;
        ExturePlusKosdaqRecoveryTradeFixedMap* tradeFixedMapKosdaq_;

};

#endif

