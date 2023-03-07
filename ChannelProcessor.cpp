// hannelProcessor.cpp: implementation of the ChannelProcessor class.
//
//////////////////////////////////////////////////////////////////////
#include <exception>
#include <vector>
#include <time.h>

#include "ace/SStringfwd.h"
#include "ace/String_Base.h"
#include "ace/Log_Msg.h"

#include "PaxfeedDefine.h"
#include "PaxfeedStatus.h"
#include "MMapAllocator.h"
#include "ChannelProcInfo.h"
#include "ChannelProcessor.h"
#include "Xmitter.h"

using namespace paxfeed;

ChannelProcessor::ChannelProcessor()
        : seq_(0)
{
}

ChannelProcessor::ChannelProcessor(const ACE_CString &channelName)
        : channelName_(channelName), seq_(0)
{
}

ChannelProcessor::~ChannelProcessor()
{
}

int ChannelProcessor::xmit(const char* buf, int bufSize)
{
    size_t sendSize = XMITTER::instance()->send(buf, bufSize);

    return static_cast<int>(sendSize);
}

int ChannelProcessor::getSerial()
{
    return ++seq_;
}

int ChannelProcessor::reset()
{
    ACE_DEBUG( ( LM_INFO , "%s::reset\n" , typeid(*this).name() ));
    seq_ = 0;
    return 0;
}

int ChannelProcessor::sendPacket(const ACE_CString& body, BYTE packetType, BYTE exchange)
{
    int bodySize = body.length();

    Header header;
    header.majorVersion = VERSION_MAJOR;
    header.minorVersion = VERSION_MINOR;

    header.packetType = packetType;
    header.exchange = exchange;
    header.serial = getSerial();
    header.time = ::time(0);
    header.dataSize = bodySize + TAIL_SIZE;

    char headerBuf[HEADER_SIZE];
    ::memcpy(headerBuf, &header, HEADER_SIZE);

    // ����Ʈ ���� ��ȯ�� ����
    Header changedHeader = headerWrapper_.getPacket(headerBuf, HEADER_SIZE);
    ::memcpy(packetBuf_, &changedHeader, HEADER_SIZE);


#if(0)
ACE_DEBUG( ( LM_INFO , "[PAX_DEBUG]>>[%d]:[%s]\n" , body.length(), body.c_str() ));
#endif

    if ( packetType == PACKET_MASTER )
    {
        // ���ڿ� �״�� �����ϹǷ� ����Ʈ ���� ������ �ʿ� ����
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_TRADE )
    {
        // ����Ʈ ���� ���� �ʿ���
        Trade changedRec = tradeWrapper_.getPacket(body.c_str(), TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, TRADE_SIZE);
    }
    else if ( packetType == PACKET_TRADE_FIXED )
    {
        // ����Ʈ ���� ���� �ʿ���
        // Trade �� ����ó��
        Trade changedRec = tradeWrapper_.getPacket(body.c_str(), TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, TRADE_SIZE);
    }
    else if ( packetType == PACKET_QUOTE10 )
    {
        // ����Ʈ ���� ���� �ʿ���
        Quote10 changedRec = quote10Wrapper_.getPacket(body.c_str(), QUOTE10_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE10_SIZE);
    }
    else if ( packetType == PACKET_QUOTE_PRICE )
    {
        // ����Ʈ ���� ���� �ʿ���
        QuotePrice changedRec = quotePriceWrapper_.getPacket(body.c_str(), QUOTE_PRICE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE_PRICE_SIZE);
    }
    else if ( packetType == PACKET_QUOTE_VOLUME )
    {
        // ����Ʈ ���� ���� �ʿ���
        QuoteVolume changedRec = quoteVolumeWrapper_.getPacket(body.c_str(), QUOTE_VOLUME_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE_VOLUME_SIZE);
    }
    else if ( packetType == PACKET_QUOTE10_FIXED )
    {
        // ����Ʈ ���� ���� �ʿ���
        // Quote10 �� ���� ó��
        Quote10 changedRec = quote10Wrapper_.getPacket(body.c_str(), QUOTE10_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE10_SIZE);
    }
    else if ( packetType == PACKET_MARKET )
    {
        // ����Ʈ ���� ���� �ʿ� ����
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), MARKET_SIZE);
    }
    else if ( packetType == PACKET_UPDOWN )
    {
        // ����Ʈ ���� ���� �ʿ���
        UpDown changedRec = upDownWrapper_.getPacket(body.c_str(), UPDOWN_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, UPDOWN_SIZE);
    }
    else if ( packetType == PACKET_FOREIGNER )
    {
        // ����Ʈ ���� ���� �ʿ���
        Foreigner changedRec = forignerWrapper_.getPacket(body.c_str(), FOREIGNER_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, FOREIGNER_SIZE);
    }
    else if ( packetType == PACKET_FOREIGNER_MASTER )
    {
        // ����Ʈ ���� ���� �ʿ���
        ForeignerMaster changedRec = foreignerMasterWrapper_.getPacket(body.c_str(), FOREIGNER_MASTER_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, FOREIGNER_MASTER_SIZE);
    }
    else if ( packetType == PACKET_SECURITIES_TRADE )
    {
        // ����Ʈ ���� ���� �ʿ���
        SecuritiesTrade changedRec = securitiesTradeWrapper_.getPacket(body.c_str(), SECURITIES_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, SECURITIES_TRADE_SIZE);
    }
    else if ( packetType == PACKET_INVESTOR )
    {
        // ����Ʈ ���� ���� �ʿ���
        Investor changedRec = investorWrapper_.getPacket(body.c_str(), INVESTOR_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, INVESTOR_SIZE);
    }
    else if ( packetType == PACKET_PROGRAM_TOTAL )
    {
        // ����Ʈ ���� ���� �ʿ���
        ProgramTradeTotal changedRec = programTradeTotalWrapper_.getPacket(body.c_str(), PROGRAM_TRADE_TOTAL_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PROGRAM_TRADE_TOTAL_SIZE);
    }
    else if ( packetType == PACKET_PROGRAM )
    {
        // ����Ʈ ���� ���� �ʿ���
        ProgramTrade changedRec = programTradeWrapper_.getPacket(body.c_str(), PROGRAM_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PROGRAM_TRADE_SIZE);
    }
    else if ( packetType == PACKET_PROGRAM_BATCH )
    {
        // ����Ʈ ���� ���� �ʿ���
        ProgramTradeBatch changedRec = programTradeBatchWrapper_.getPacket(body.c_str(), PROGRAM_TRADE_BATCH_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PROGRAM_TRADE_BATCH_SIZE);
    }
    else if ( packetType == PACKET_PUBLIC_NEWS )
    {
        // ���ô� �ڽ��� ������ �״�� ������
        // ����Ʈ ���� ���� �ʿ� ����
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_SIGNAL )
    {
        // PACKET_SIGNAL �� Tickerplant ���� �߻���Ű�� ����
        // Ȥ�� ó�� �ʿ��ϸ� �״�� ����
        // ����Ʈ ���� ���� ����
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_SECURITIES_TRADE_ELW )
    {
        // ����Ʈ ���� ���� �ʿ���
        SecuritiesTrade2 changedRec = securitiesTrade2Wrapper_.getPacket(body.c_str(), SECURITIES_TRADE2_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, SECURITIES_TRADE2_SIZE);
    }
    else if ( packetType == PACKET_SHORT_SELLING_INFO )
    {
        // ����Ʈ ���� ���� �ʿ���
        ShortSellingInfo changedRec = shortSellingInfoWrapper_.getPacket(body.c_str(), SHORT_SELLING_INFO_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, SHORT_SELLING_INFO_SIZE);
    }
    else if ( packetType == PACKET_KOSCOM_LINE_LK_INFO )
    {
        // ����Ʈ ���� ���� �ʿ���
        KoscomLineLKInfo changedRec = koscomLineLKInfoWrapper_.getPacket(body.c_str(), KOSCOM_LINE_LK_INFO_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, KOSCOM_LINE_LK_INFO_SIZE);
    }
    else if ( packetType == PACKET_MARKET_OPERATION )
    {
        // ����Ʈ ���� ���� �ʿ���
        MarketOperation changedRec = marketOperationWrapper_.getPacket(body.c_str(), MARKET_OPERATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, MARKET_OPERATION_SIZE);
    }
    else if ( packetType == PACKET_BLOCK_TRADE )
    {
        // ����Ʈ ���� ���� �ʿ���
        BlockTrade changedRec = blockTradeWrapper_.getPacket(body.c_str(), BLOCK_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, BLOCK_TRADE_SIZE);
    }
    else if ( packetType == PACKET_REAL_TIME_LIMIT_PRICE )
    {
        // ����Ʈ ���� ���� �ʿ���
        RealTimeLimitPrice changedRec = realTimeLimitPriceWrapper_.getPacket(body.c_str(), REAL_TIME_LIMIT_PRICE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, REAL_TIME_LIMIT_PRICE_SIZE);
    }
    else if ( packetType == PACKET_VOLATILITY_INTERRUPTION_PER_INSTRUMENT )
    {
        // ����Ʈ ���� ���� �ʿ���
        VolatilityInterruptionPerInstrument changedRec = volatilityInterruptionPerInstrumentWrapper_.getPacket(body.c_str(), VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE);
    }
    else if ( packetType == PACKET_VOLATILITY_INTERRUPTION_PER_INSTRUMENT2 )
    {
        // ����Ʈ ���� ���� �ʿ���
        VolatilityInterruptionPerInstrument2 changedRec = volatilityInterruptionPerInstrument2Wrapper_.getPacket(body.c_str(), VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE);
    }
    else if ( packetType == PACKET_ETN_TRANSFER_AGENT_BATCH_DATA )
    {
        // ����Ʈ ���� ���� �ʿ���
        ETNTransferAgentBatchData changedRec = etnTransferAgentBatchDataWrapper_.getPacket(body.c_str(), ETN_TRANSFER_AGENT_BATCH_DATA_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_TRANSFER_AGENT_BATCH_DATA_SIZE);
    }
    else if ( packetType == PACKET_ETN_INDEX_COMPOSITION_CONSTITUENTS )
    {
        // ����Ʈ ���� ���� �ʿ���
        ETNIndexCompositionConstituents changedRec = etnIndexCompositionConstituentsWrapper_.getPacket(body.c_str(), ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE);
    }
    else if ( packetType == PACKET_ETN_IIV )
    {
        // ����Ʈ ���� ���� �ʿ���
        ETN_IIV changedRec = etnIIVWrapper_.getPacket(body.c_str(), ETN_IIV_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_IIV_SIZE);
    }
    else if ( packetType == PACKET_ETN_INFORMATION_BATCH )
    {
        // ����Ʈ ���� ���� �ʿ���
        ETNInformationBatch changedRec = etnInformationBatchWrapper_.getPacket(body.c_str(), ETN_INFORMATION_BATCH_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_INFORMATION_BATCH_SIZE);
    }
    else if ( packetType == PACKET_KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA )
    {
        // ����Ʈ ���� ���� �ʿ���
        KOSPI200IndexFutureSettledPriceData changedRec = kospi200IndexFutureSettledPriceDataWrapper_.getPacket(body.c_str(), KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA_SIZE);
    }
    else if ( packetType == PACKET_KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION )
    {
        // ����Ʈ ���� ���� �ʿ���
        KOSPI_KOSDAQ_IssueEventInformation changedRec = kospiKosdaqIssueEventInformationWrapper_.getPacket(body.c_str(), KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);
    }
    else if ( packetType == PACKET_ELW_QUOTE10_LP_INCLUDED )
    {
        // ����Ʈ ���� ���� �ʿ���
        ELWQuote10LPIncluded changedRec = elwQuote10LPIncludedWrapper_.getPacket(body.c_str(), ELW_QUOTE10_LP_INCLUDED_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_QUOTE10_LP_INCLUDED_SIZE);
    }
    else if ( packetType == PACKET_ELW_TRADE )
    {
        // ����Ʈ ���� ���� �ʿ���
        ELWTrade changedRec = elwTradeWrapper_.getPacket(body.c_str(), ELW_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_TRADE_SIZE);
    }
    else if ( packetType == PACKET_ELW_EARLY_CLOSED_ELW_BATCH )
    {
        // ����Ʈ ���� ���� �ʿ���
        ELWEarlyClosedELWBatch changedRec = elwEarlyClosedELWBatchWrapper_.getPacket(body.c_str(), ELW_EARLY_CLOSED_ELW_BATCH_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_EARLY_CLOSED_ELW_BATCH_SIZE);
    }
    else if ( packetType == PACKET_ELW_SECURITIES_TRADE )
    {
        // ����Ʈ ���� ���� �ʿ���
        ELWSecuritiesTrade changedRec = elwSecuritiesTradeWrapper_.getPacket(body.c_str(), ELW_SECURITIES_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_SECURITIES_TRADE_SIZE);
    }
    else if ( packetType == PACKET_ELW_MARKET_OPERATION )
    {
        // ����Ʈ ���� ���� �ʿ���
        ELWMarketOperation changedRec = elwMarketOperationWrapper_.getPacket(body.c_str(), ELW_MARKET_OPERATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_MARKET_OPERATION_SIZE);
    }
    else if ( packetType == PACKET_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER )
    {
        // ����Ʈ ���� ���� �ʿ���
        PriceLimitRangeExpansionTrigger changedRec = priceLimitRangeExpansionTriggerWrapper_.getPacket(body.c_str(), PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_SIZE);
    }
    else if ( packetType == PACKET_ELW_LP_INFORMATION )
    {
        // ����Ʈ ���� ���� �ʿ���
        ELW_LP_Information changedRec = elwLPInformationWrapper_.getPacket(body.c_str(), ELW_LP_INFORMATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_LP_INFORMATION_SIZE);
    }
    else if ( packetType == PACKET_DETERMINED_BASIS_PRICE )
    {
        // ����Ʈ ���� ���� �ʿ���
        DeterminedBasisPrice changedRec = determinedBasisPriceWrapper_.getPacket(body.c_str(), DETERMINED_BASIC_PRICE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, DETERMINED_BASIC_PRICE_SIZE);
    }
    else if ( packetType == PACKET_STATUS )
    {
        // ó�� ��å ���� �ʿ���
        // PaxfeedStatus ���� ó��
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_STATUS_SERVER )
    {
        // ó�� ��å ���� �ʿ���
        // PaxfeedStatus ���� ó��
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_SQL_COMMAND )
    {
        // ó�� ��å ���� �ʿ���
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_TIMESYNC )
    {
        // ó�� ��å ���� �ʿ���
        // PaxfeedStatus ���� ó��
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else
    {
        // ó�� ��å ���� �ʿ���
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    // ����Ʈ ���� ��ȯ�� ��

    ::memcpy(packetBuf_ + HEADER_SIZE + bodySize, TAIL.c_str(), TAIL.length());

    int packetSize = HEADER_SIZE + bodySize + TAIL_SIZE;
    int result = xmit(packetBuf_, packetSize);
//  ACE_DEBUG((LM_DEBUG, "result : %d PACKET : %d / %d / %d / %d\n", 
//             result, header.time, header.packetType, header.exchange, header.serial));

    return ( result );
}

void ChannelProcessor::LogFrameCount(const ACE_CString& frameId)
{
    STATUS::instance()->increaseLineInfo(frameId);
}

ACE_CString ChannelProcessor::makeMaster(ACE_Map_Manager<ACE_CString, ACE_CString, ACE_Null_Mutex> &map)
{
    ACE_CString result;

    char buf[PAXFEED_MAX_BUF_SIZE];

    ACE_Map_Manager<ACE_CString, ACE_CString, ACE_Null_Mutex>::iterator iter = map.begin();

    for ( ; iter != map.end() ; iter++ )
    {
        ACE_CString key = ( *iter ).ext_id_;
        ACE_CString value = ( *iter ).int_id_;

        sprintf(buf, "%s|%s\n", key.c_str(), value.c_str());
        result += ACE_CString(buf);
    }
    return ( result );
}

time_t ChannelProcessor::getTime(const ACE_CString& date)
{
    time_t timeResult = 0;

    if ( date.length() >= 8 )
    {
        struct tm tmResult;

        tmResult.tm_year = ::atoi(date.substring(0, 4).c_str()) - 1900;
        tmResult.tm_mon = ::atoi(date.substring(4, 2).c_str()) - 1;
        tmResult.tm_mday = ::atoi(date.substring(6, 2).c_str());
        tmResult.tm_hour = 18;
        tmResult.tm_min = 0;
        tmResult.tm_sec = 0;

        timeResult = ::mktime(&tmResult);
    }

    return ( timeResult );
}

void ChannelProcessor::flushPacket()
{
    time_t currentUTC;
    time(&currentUTC);

    std::vector < ACE_CString > vTradeSymbol;
    char bufferTrade[TRADE_SIZE];
    ACE_Hash_Map_Manager<ACE_CString, paxfeed::Trade, ACE_Null_Mutex>::iterator iterTrade = compressedTradeMap_.begin();

    for ( ; iterTrade != compressedTradeMap_.end() ; ++iterTrade )
    {
        Trade trade = ( *iterTrade ).int_id_;
        if ( ( currentUTC - trade.tradeTime ) > COMPRESS_EXPIRE_TIME )
        {
            ::memset(bufferTrade, 0, sizeof ( bufferTrade ));
            memcpy(bufferTrade, &trade, sizeof ( bufferTrade ));
            sendPacket(ACE_CString(bufferTrade, TRADE_SIZE), PACKET_TRADE, trade.exchange);
            vTradeSymbol.push_back(ACE_CString(trade.symbol, 12));
        }
    }

    std::vector<ACE_CString>::iterator iterTradeSymbol = vTradeSymbol.begin();
    for ( ; iterTradeSymbol != vTradeSymbol.end() ; ++iterTradeSymbol )
    {
        compressedTradeMap_.unbind(*iterTradeSymbol);
    }

    std::vector < ACE_CString > vQuoteSymbol;

    char bufferQuote10[QUOTE10_SIZE];
    ACE_Hash_Map_Manager<ACE_CString, paxfeed::Quote10, ACE_Null_Mutex>::iterator iterQuote = compressedQuote10Map_.begin();
    for ( ; iterQuote != compressedQuote10Map_.end() ; ++iterQuote )
    {
        Quote10 quote = ( *iterQuote ).int_id_;
        if ( ( currentUTC - quote.quoteTime ) > COMPRESS_EXPIRE_TIME )
        {
            ::memset(bufferQuote10, 0, sizeof ( bufferQuote10 ));
            memcpy(bufferQuote10, &quote, sizeof ( bufferQuote10 ));
            sendPacket(ACE_CString(bufferQuote10, QUOTE10_SIZE), PACKET_QUOTE10, quote.exchange);
            vQuoteSymbol.push_back(ACE_CString(quote.symbol, 12));
        }
    }

    std::vector<ACE_CString>::iterator iterQuoteSymbol = vQuoteSymbol.begin();
    for ( ; iterQuoteSymbol != vQuoteSymbol.end() ; ++iterQuoteSymbol )
    {
        compressedQuote10Map_.unbind(*iterQuoteSymbol);
    }
}

void ChannelProcessor::sendTrade(Trade& trade)
{
    ACE_CString symbol(trade.symbol, 12);
    Trade prevTrade;
    int hasValue = compressedTradeMap_.find(symbol, prevTrade);
    if ( hasValue == -1 )
    {

        char bufferTrade[TRADE_SIZE];
        ::memset(bufferTrade, 0, sizeof ( bufferTrade ));
        memcpy(bufferTrade, &trade, sizeof ( bufferTrade ));
        sendPacket(ACE_CString(bufferTrade, TRADE_SIZE), PACKET_TRADE, trade.exchange);
        trade.tradeVolume = 0;
        compressedTradeMap_.bind(symbol, trade);
    }
    else
    {
        //  ���� ü��� ���簡�� ���� ���
        if ( trade.close == prevTrade.close )
        {
            int timeGap = trade.tradeTime - prevTrade.tradeTime;

            // ���� �� �̸鼭, ���� �ð� �̳��� ���
            if ( ( timeGap < COMPRESS_EXPIRE_TIME ) && ( isSameMinute(trade.tradeTime, prevTrade.tradeTime) == true ) )
            {
                // ü�� ����
                prevTrade.tradeVolume += trade.tradeVolume;
                prevTrade.accmVolume = trade.accmVolume;
                prevTrade.amount = trade.amount;
                prevTrade.volumeMin = trade.volumeMin;
                compressedTradeMap_.rebind(ACE_CString(trade.symbol, 12), prevTrade);
            }
            else
            {
                // ����ð� �̳��� ���� �ٲ� ��� Ȥ�� ���� ���̶� ����ð��� �ʰ��� ��쿡�� �����͸� ����
                // �̶� ���� �����͸� �ݿ��ؼ� send �Ѵ�.
                Trade tempTrade;
                ::memset(&tempTrade, 0, sizeof(Trade));
                ::memcpy(&tempTrade, &trade, sizeof(Trade));

                // �ŷ����� ���� �� �ջ�
                tempTrade.tradeVolume = tempTrade.tradeVolume + prevTrade.tradeVolume;

                char bufferTrade[TRADE_SIZE];
                ::memset(bufferTrade, 0, sizeof ( bufferTrade ));
                memcpy(bufferTrade, &tempTrade, sizeof ( bufferTrade ));
                sendPacket(ACE_CString(bufferTrade, TRADE_SIZE), PACKET_TRADE, tempTrade.exchange);

                // ������ ���� �ŷ����� ������ ���� �ʱ�ȭ�� ����Ѵ�.
                trade.tradeVolume = 0;
                compressedTradeMap_.rebind(symbol, trade);
            }
        }
        else
        {
            // ������ ����
            // ����ð� �̳��� ���� �ٲ� ��� Ȥ�� ���� ���̶� ����ð��� �ʰ��� ��쿡�� �����͸� ����
            // �̶� ���� �����͸� �ݿ��ؼ� send �Ѵ�.
            Trade tempTrade;
            ::memset(&tempTrade, 0, sizeof(Trade));
            ::memcpy(&tempTrade, &trade, sizeof(Trade));

            // �ŷ����� ���� �� �ջ�
            tempTrade.tradeVolume = tempTrade.tradeVolume + prevTrade.tradeVolume;

            char bufferTrade[TRADE_SIZE];
            ::memset(bufferTrade, 0, sizeof ( bufferTrade ));
            memcpy(bufferTrade, &tempTrade, sizeof ( bufferTrade ));
            sendPacket(ACE_CString(bufferTrade, TRADE_SIZE), PACKET_TRADE, tempTrade.exchange);

            // ������ ���� �ŷ����� ������ ���� �ʱ�ȭ�� ����Ѵ�.
            trade.tradeVolume = 0;
            compressedTradeMap_.rebind(symbol, trade);
        }
    }
}

bool ChannelProcessor::isSameMinute(int timeUTC1, int timeUTC2)
{
    if ( ( timeUTC1 / 60 ) == ( timeUTC2 / 60 ) )
    {
        return ( true );
    }
    else
    {
        return ( false );
    }
}

void ChannelProcessor::sendQuote10(Quote10& quote)
{
    ACE_CString symbol(quote.symbol, 12);
    Quote10 prevQuote;
    int hasValue = compressedQuote10Map_.find(symbol, prevQuote);

    if ( hasValue == -1 )
    {
        compressedQuote10Map_.bind(symbol, quote);
    }
    else
    {
        if ( ( quote.quoteTime - prevQuote.quoteTime ) < COMPRESS_EXPIRE_TIME )
        {
            quote.quoteTime = prevQuote.quoteTime;
            compressedQuote10Map_.rebind(symbol, quote);
        }
        else
        {
            char bufferQuote10[QUOTE10_SIZE];
            ::memset(bufferQuote10, 0, sizeof ( bufferQuote10 ));
            memcpy(bufferQuote10, &quote, sizeof ( bufferQuote10 ));
            sendPacket(ACE_CString(bufferQuote10, QUOTE10_SIZE), PACKET_QUOTE10, quote.exchange);
            compressedQuote10Map_.unbind(ACE_CString(quote.symbol, 12));
        }
    }
}

void ChannelProcessor::sendELWQuote10LPIncluded(ELWQuote10LPIncluded& elwQuote)
{
    ACE_CString symbol(elwQuote.symbol, 12);
    ELWQuote10LPIncluded elwQuotePrev;
    ::memset(&elwQuotePrev, 0, sizeof(ELWQuote10LPIncluded));
    int hasValue = compressedELWQuote10LPIncludedMap_.find(symbol, elwQuotePrev);

    if ( hasValue == -1 )
    {
        compressedELWQuote10LPIncludedMap_.bind(symbol, elwQuote);
    }
    else
    {
        if ( ( elwQuote.quoteTime - elwQuotePrev.quoteTime ) < COMPRESS_EXPIRE_TIME )
        {
            elwQuote.quoteTime = elwQuotePrev.quoteTime;
            compressedELWQuote10LPIncludedMap_.rebind(symbol, elwQuote);
        }
        else
        {
            char bufferELWQuote10[ELW_QUOTE10_LP_INCLUDED_SIZE];
            ::memset(bufferELWQuote10, 0, sizeof ( bufferELWQuote10 ));
            ::memcpy(bufferELWQuote10, &elwQuote, sizeof ( bufferELWQuote10 ));
            sendPacket(ACE_CString(bufferELWQuote10, ELW_QUOTE10_LP_INCLUDED_SIZE), PACKET_ELW_QUOTE10_LP_INCLUDED, elwQuote.exchange);
            compressedELWQuote10LPIncludedMap_.unbind(ACE_CString(elwQuote.symbol, 12));
        }
    }
}

/*
 ���� �ð� ���ڿ��� ����Ѵ�.
 YYYYMMDD_HHMMSS
 */
ACE_CString ChannelProcessor::getCurrentTimestamp()
{
    char buffer[32];
    ::memset(&buffer, 0, sizeof ( buffer ));
    struct tm stTm;
    ::memset(&stTm, 0, sizeof(struct tm));
    time_t currentTime = time(NULL);
    ::localtime_r(&currentTime, &stTm);
    ::strftime(buffer, sizeof ( buffer ), "%Y%m%d_%H%M%S", &stTm);
    ACE_CString strCurrentTime(buffer);
    return ( strCurrentTime );
}

