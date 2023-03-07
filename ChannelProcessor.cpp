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

    // 바이트 오더 변환부 시작
    Header changedHeader = headerWrapper_.getPacket(headerBuf, HEADER_SIZE);
    ::memcpy(packetBuf_, &changedHeader, HEADER_SIZE);


#if(0)
ACE_DEBUG( ( LM_INFO , "[PAX_DEBUG]>>[%d]:[%s]\n" , body.length(), body.c_str() ));
#endif

    if ( packetType == PACKET_MASTER )
    {
        // 문자열 그대로 전송하므로 바이트 오더 변경할 필요 없음
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_TRADE )
    {
        // 바이트 오더 변경 필요함
        Trade changedRec = tradeWrapper_.getPacket(body.c_str(), TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, TRADE_SIZE);
    }
    else if ( packetType == PACKET_TRADE_FIXED )
    {
        // 바이트 오더 변경 필요함
        // Trade 와 동일처리
        Trade changedRec = tradeWrapper_.getPacket(body.c_str(), TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, TRADE_SIZE);
    }
    else if ( packetType == PACKET_QUOTE10 )
    {
        // 바이트 오더 변경 필요함
        Quote10 changedRec = quote10Wrapper_.getPacket(body.c_str(), QUOTE10_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE10_SIZE);
    }
    else if ( packetType == PACKET_QUOTE_PRICE )
    {
        // 바이트 오더 변경 필요함
        QuotePrice changedRec = quotePriceWrapper_.getPacket(body.c_str(), QUOTE_PRICE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE_PRICE_SIZE);
    }
    else if ( packetType == PACKET_QUOTE_VOLUME )
    {
        // 바이트 오더 변경 필요함
        QuoteVolume changedRec = quoteVolumeWrapper_.getPacket(body.c_str(), QUOTE_VOLUME_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE_VOLUME_SIZE);
    }
    else if ( packetType == PACKET_QUOTE10_FIXED )
    {
        // 바이트 오더 변경 필요함
        // Quote10 과 동일 처리
        Quote10 changedRec = quote10Wrapper_.getPacket(body.c_str(), QUOTE10_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, QUOTE10_SIZE);
    }
    else if ( packetType == PACKET_MARKET )
    {
        // 바이트 오더 변경 필요 없음
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), MARKET_SIZE);
    }
    else if ( packetType == PACKET_UPDOWN )
    {
        // 바이트 오더 변경 필요함
        UpDown changedRec = upDownWrapper_.getPacket(body.c_str(), UPDOWN_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, UPDOWN_SIZE);
    }
    else if ( packetType == PACKET_FOREIGNER )
    {
        // 바이트 오더 변경 필요함
        Foreigner changedRec = forignerWrapper_.getPacket(body.c_str(), FOREIGNER_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, FOREIGNER_SIZE);
    }
    else if ( packetType == PACKET_FOREIGNER_MASTER )
    {
        // 바이트 오더 변경 필요함
        ForeignerMaster changedRec = foreignerMasterWrapper_.getPacket(body.c_str(), FOREIGNER_MASTER_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, FOREIGNER_MASTER_SIZE);
    }
    else if ( packetType == PACKET_SECURITIES_TRADE )
    {
        // 바이트 오더 변경 필요함
        SecuritiesTrade changedRec = securitiesTradeWrapper_.getPacket(body.c_str(), SECURITIES_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, SECURITIES_TRADE_SIZE);
    }
    else if ( packetType == PACKET_INVESTOR )
    {
        // 바이트 오더 변경 필요함
        Investor changedRec = investorWrapper_.getPacket(body.c_str(), INVESTOR_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, INVESTOR_SIZE);
    }
    else if ( packetType == PACKET_PROGRAM_TOTAL )
    {
        // 바이트 오더 변경 필요함
        ProgramTradeTotal changedRec = programTradeTotalWrapper_.getPacket(body.c_str(), PROGRAM_TRADE_TOTAL_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PROGRAM_TRADE_TOTAL_SIZE);
    }
    else if ( packetType == PACKET_PROGRAM )
    {
        // 바이트 오더 변경 필요함
        ProgramTrade changedRec = programTradeWrapper_.getPacket(body.c_str(), PROGRAM_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PROGRAM_TRADE_SIZE);
    }
    else if ( packetType == PACKET_PROGRAM_BATCH )
    {
        // 바이트 오더 변경 필요함
        ProgramTradeBatch changedRec = programTradeBatchWrapper_.getPacket(body.c_str(), PROGRAM_TRADE_BATCH_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PROGRAM_TRADE_BATCH_SIZE);
    }
    else if ( packetType == PACKET_PUBLIC_NEWS )
    {
        // 공시는 코스콤 전문을 그대로 전파함
        // 바이트 오더 변경 필요 없음
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_SIGNAL )
    {
        // PACKET_SIGNAL 는 Tickerplant 에서 발생시키지 않음
        // 혹시 처리 필요하면 그대로 전파
        // 바이트 오더 변경 안함
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_SECURITIES_TRADE_ELW )
    {
        // 바이트 오더 변경 필요함
        SecuritiesTrade2 changedRec = securitiesTrade2Wrapper_.getPacket(body.c_str(), SECURITIES_TRADE2_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, SECURITIES_TRADE2_SIZE);
    }
    else if ( packetType == PACKET_SHORT_SELLING_INFO )
    {
        // 바이트 오더 변경 필요함
        ShortSellingInfo changedRec = shortSellingInfoWrapper_.getPacket(body.c_str(), SHORT_SELLING_INFO_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, SHORT_SELLING_INFO_SIZE);
    }
    else if ( packetType == PACKET_KOSCOM_LINE_LK_INFO )
    {
        // 바이트 오더 변경 필요함
        KoscomLineLKInfo changedRec = koscomLineLKInfoWrapper_.getPacket(body.c_str(), KOSCOM_LINE_LK_INFO_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, KOSCOM_LINE_LK_INFO_SIZE);
    }
    else if ( packetType == PACKET_MARKET_OPERATION )
    {
        // 바이트 오더 변경 필요함
        MarketOperation changedRec = marketOperationWrapper_.getPacket(body.c_str(), MARKET_OPERATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, MARKET_OPERATION_SIZE);
    }
    else if ( packetType == PACKET_BLOCK_TRADE )
    {
        // 바이트 오더 변경 필요함
        BlockTrade changedRec = blockTradeWrapper_.getPacket(body.c_str(), BLOCK_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, BLOCK_TRADE_SIZE);
    }
    else if ( packetType == PACKET_REAL_TIME_LIMIT_PRICE )
    {
        // 바이트 오더 변경 필요함
        RealTimeLimitPrice changedRec = realTimeLimitPriceWrapper_.getPacket(body.c_str(), REAL_TIME_LIMIT_PRICE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, REAL_TIME_LIMIT_PRICE_SIZE);
    }
    else if ( packetType == PACKET_VOLATILITY_INTERRUPTION_PER_INSTRUMENT )
    {
        // 바이트 오더 변경 필요함
        VolatilityInterruptionPerInstrument changedRec = volatilityInterruptionPerInstrumentWrapper_.getPacket(body.c_str(), VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE);
    }
    else if ( packetType == PACKET_VOLATILITY_INTERRUPTION_PER_INSTRUMENT2 )
    {
        // 바이트 오더 변경 필요함
        VolatilityInterruptionPerInstrument2 changedRec = volatilityInterruptionPerInstrument2Wrapper_.getPacket(body.c_str(), VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE);
    }
    else if ( packetType == PACKET_ETN_TRANSFER_AGENT_BATCH_DATA )
    {
        // 바이트 오더 변경 필요함
        ETNTransferAgentBatchData changedRec = etnTransferAgentBatchDataWrapper_.getPacket(body.c_str(), ETN_TRANSFER_AGENT_BATCH_DATA_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_TRANSFER_AGENT_BATCH_DATA_SIZE);
    }
    else if ( packetType == PACKET_ETN_INDEX_COMPOSITION_CONSTITUENTS )
    {
        // 바이트 오더 변경 필요함
        ETNIndexCompositionConstituents changedRec = etnIndexCompositionConstituentsWrapper_.getPacket(body.c_str(), ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE);
    }
    else if ( packetType == PACKET_ETN_IIV )
    {
        // 바이트 오더 변경 필요함
        ETN_IIV changedRec = etnIIVWrapper_.getPacket(body.c_str(), ETN_IIV_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_IIV_SIZE);
    }
    else if ( packetType == PACKET_ETN_INFORMATION_BATCH )
    {
        // 바이트 오더 변경 필요함
        ETNInformationBatch changedRec = etnInformationBatchWrapper_.getPacket(body.c_str(), ETN_INFORMATION_BATCH_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ETN_INFORMATION_BATCH_SIZE);
    }
    else if ( packetType == PACKET_KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA )
    {
        // 바이트 오더 변경 필요함
        KOSPI200IndexFutureSettledPriceData changedRec = kospi200IndexFutureSettledPriceDataWrapper_.getPacket(body.c_str(), KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, KOSPI200_INDEX_FUTURE_SETTLED_PRICE_DATA_SIZE);
    }
    else if ( packetType == PACKET_KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION )
    {
        // 바이트 오더 변경 필요함
        KOSPI_KOSDAQ_IssueEventInformation changedRec = kospiKosdaqIssueEventInformationWrapper_.getPacket(body.c_str(), KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);
    }
    else if ( packetType == PACKET_ELW_QUOTE10_LP_INCLUDED )
    {
        // 바이트 오더 변경 필요함
        ELWQuote10LPIncluded changedRec = elwQuote10LPIncludedWrapper_.getPacket(body.c_str(), ELW_QUOTE10_LP_INCLUDED_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_QUOTE10_LP_INCLUDED_SIZE);
    }
    else if ( packetType == PACKET_ELW_TRADE )
    {
        // 바이트 오더 변경 필요함
        ELWTrade changedRec = elwTradeWrapper_.getPacket(body.c_str(), ELW_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_TRADE_SIZE);
    }
    else if ( packetType == PACKET_ELW_EARLY_CLOSED_ELW_BATCH )
    {
        // 바이트 오더 변경 필요함
        ELWEarlyClosedELWBatch changedRec = elwEarlyClosedELWBatchWrapper_.getPacket(body.c_str(), ELW_EARLY_CLOSED_ELW_BATCH_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_EARLY_CLOSED_ELW_BATCH_SIZE);
    }
    else if ( packetType == PACKET_ELW_SECURITIES_TRADE )
    {
        // 바이트 오더 변경 필요함
        ELWSecuritiesTrade changedRec = elwSecuritiesTradeWrapper_.getPacket(body.c_str(), ELW_SECURITIES_TRADE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_SECURITIES_TRADE_SIZE);
    }
    else if ( packetType == PACKET_ELW_MARKET_OPERATION )
    {
        // 바이트 오더 변경 필요함
        ELWMarketOperation changedRec = elwMarketOperationWrapper_.getPacket(body.c_str(), ELW_MARKET_OPERATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_MARKET_OPERATION_SIZE);
    }
    else if ( packetType == PACKET_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER )
    {
        // 바이트 오더 변경 필요함
        PriceLimitRangeExpansionTrigger changedRec = priceLimitRangeExpansionTriggerWrapper_.getPacket(body.c_str(), PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_SIZE);
    }
    else if ( packetType == PACKET_ELW_LP_INFORMATION )
    {
        // 바이트 오더 변경 필요함
        ELW_LP_Information changedRec = elwLPInformationWrapper_.getPacket(body.c_str(), ELW_LP_INFORMATION_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, ELW_LP_INFORMATION_SIZE);
    }
    else if ( packetType == PACKET_DETERMINED_BASIS_PRICE )
    {
        // 바이트 오더 변경 필요함
        DeterminedBasisPrice changedRec = determinedBasisPriceWrapper_.getPacket(body.c_str(), DETERMINED_BASIC_PRICE_SIZE);
        ::memcpy(packetBuf_ + HEADER_SIZE, &changedRec, DETERMINED_BASIC_PRICE_SIZE);
    }
    else if ( packetType == PACKET_STATUS )
    {
        // 처리 정책 수립 필요함
        // PaxfeedStatus 에서 처리
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_STATUS_SERVER )
    {
        // 처리 정책 수립 필요함
        // PaxfeedStatus 에서 처리
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_SQL_COMMAND )
    {
        // 처리 정책 수립 필요함
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else if ( packetType == PACKET_TIMESYNC )
    {
        // 처리 정책 수립 필요함
        // PaxfeedStatus 에서 처리
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    else
    {
        // 처리 정책 수립 필요함
        ::memcpy(packetBuf_ + HEADER_SIZE, body.c_str(), bodySize);
    }
    // 바이트 오더 변환부 끝

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
        //  직전 체결과 현재가가 같을 경우
        if ( trade.close == prevTrade.close )
        {
            int timeGap = trade.tradeTime - prevTrade.tradeTime;

            // 같은 분 이면서, 압축 시간 이내인 경우
            if ( ( timeGap < COMPRESS_EXPIRE_TIME ) && ( isSameMinute(trade.tradeTime, prevTrade.tradeTime) == true ) )
            {
                // 체결 압축
                prevTrade.tradeVolume += trade.tradeVolume;
                prevTrade.accmVolume = trade.accmVolume;
                prevTrade.amount = trade.amount;
                prevTrade.volumeMin = trade.volumeMin;
                compressedTradeMap_.rebind(ACE_CString(trade.symbol, 12), prevTrade);
            }
            else
            {
                // 압축시간 이내라도 분이 바뀐 경우 혹은 같은 분이라도 압축시간을 초과할 경우에는 데이터를 전송
                // 이때 현재 데이터를 반영해서 send 한다.
                Trade tempTrade;
                ::memset(&tempTrade, 0, sizeof(Trade));
                ::memcpy(&tempTrade, &trade, sizeof(Trade));

                // 거래량은 기존 것 합산
                tempTrade.tradeVolume = tempTrade.tradeVolume + prevTrade.tradeVolume;

                char bufferTrade[TRADE_SIZE];
                ::memset(bufferTrade, 0, sizeof ( bufferTrade ));
                memcpy(bufferTrade, &tempTrade, sizeof ( bufferTrade ));
                sendPacket(ACE_CString(bufferTrade, TRADE_SIZE), PACKET_TRADE, tempTrade.exchange);

                // 압축을 위한 거래량은 압축을 위해 초기화후 등록한다.
                trade.tradeVolume = 0;
                compressedTradeMap_.rebind(symbol, trade);
            }
        }
        else
        {
            // 데이터 전송
            // 압축시간 이내라도 분이 바뀐 경우 혹은 같은 분이라도 압축시간을 초과할 경우에는 데이터를 전송
            // 이때 현재 데이터를 반영해서 send 한다.
            Trade tempTrade;
            ::memset(&tempTrade, 0, sizeof(Trade));
            ::memcpy(&tempTrade, &trade, sizeof(Trade));

            // 거래량은 기존 것 합산
            tempTrade.tradeVolume = tempTrade.tradeVolume + prevTrade.tradeVolume;

            char bufferTrade[TRADE_SIZE];
            ::memset(bufferTrade, 0, sizeof ( bufferTrade ));
            memcpy(bufferTrade, &tempTrade, sizeof ( bufferTrade ));
            sendPacket(ACE_CString(bufferTrade, TRADE_SIZE), PACKET_TRADE, tempTrade.exchange);

            // 압축을 위한 거래량은 압축을 위해 초기화후 등록한다.
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
 현재 시간 문자열을 출력한다.
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

