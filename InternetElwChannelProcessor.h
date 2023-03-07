#ifndef _INTERNET_ELW_CHANNEL_PROCESSOR_H
#define _INTERNET_ELW_CHANNEL_PROCESSOR_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include <sys/msg.h>
#include "PaxfeedAceHelper.h"
#include "InternetChannelProcessor.h"
#include "PaxfeedPacket.h"
#include "PaxfeedPacketELW.h"
#include "ExturePlusInternetElw.h"

class InternetElwChannelProcessor: public InternetChannelProcessor
{
    public:
        InternetElwChannelProcessor(const ACE_CString &channelName);
        ~InternetElwChannelProcessor();

        int reset();

    private:

#if(1)
int processPacket(const ACE_CString &packet);
#endif

#if(1)
int handleMarketOperationTS(const ACE_CString &packet);
int handleTradeFixed(const ExtureGroupCTrade &elwRawData);
int handleTrade(const ACE_CString &packet);
int handleSecuritiesTrade(const ACE_CString &packet);
int handleMarketOperationScheduleDisclosure(const ACE_CString &packet);
int handleKOSPIIssueEventInformation(const ACE_CString &packet);
int handleElwRecoveryTotalTrade(const ACE_CString &packet);
int handleRecoveryTotalTrade(const ACE_CString &packet);
int handleRecoveryTrade(const ACE_CString &packet);
int handleQuote10(const ACE_CString &packet);
int handleETNEarlyRedemptionCriteria(const ACE_CString &packet);
int handleETP_Constituents(const ACE_CString &packet);
int handleETNInformationBatch(const ACE_CString &packet);
int handleETNProfitStructureDetails(const ACE_CString &packet);
#endif

#if(1)
static time_t getModTime(time_t tradeTime);
BYTE getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID);
BYTE getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID);
int getTickTime(const ACE_CString &timeStr, const ACE_CString &frameId);
BYTE getMarketInTrade(const ACE_CString& raw);
BYTE getUpDownInTrade(const ACE_CString& raw);
BYTE getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID);
BYTE getExchange(char rawSymbolType);
BYTE getExhaustInForeigner(const ACE_CString& raw);
ACE_CString getSymbolMarketTypeCode(const ACE_CString& raw);
ACE_CString getSymbolUpCode(const ACE_CString& raw);
#endif


#if(0)
int processPacket_KRX_I6011(const ACE_CString& packet);
int processPacket_KRX_M6011(const ACE_CString& packet);
void processPacket_KRX_M5011(const ACE_CString& packet);
void processPacket_KRX_C6021(const ACE_CString& packet);
void processPacket_KRX_O6021(const ACE_CString& packet);
void processPacket_KRX_C0021(const ACE_CString& packet);
int processPacket_KRX_M4011(const ACE_CString& packet);
void processPacket_KRX_A8011(const ACE_CString& packet);
int processPacket_KRX_A3021(const ACE_CString& packet);
void processPacket_KRX_A6021(const ACE_CString& packet);
int processPacket_KRX_A7021(const ACE_CString& packet);
int processPacket_KRX_B7021(const ACE_CString& packet);
int processPacket_KRX_B1021(const ACE_CString& packet);
int processPacket_KRX_B2021(const ACE_CString& packet);
int processPacket_KRX_B9021(const ACE_CString& packet);
int processPacket_KRX_I7011(const ACE_CString& packet);
int processPacket_KOSCOM_F1011(const ACE_CString& packet);
int processPacket_KOSCOM_F4011(const ACE_CString& packet);
void processPacket_KOSCOM_C7021(const ACE_CString& packet);
void processPacket_KOSCOM_N3021(const ACE_CString& packet);
#endif

#if(0)
int handleETNInformationBatch(const ACE_CString &packet);
int processPacket_KRX_A702S(const ACE_CString &packet);
int processPacket_KRX_B702S(const ACE_CString &packet);
int processPacket_KRX_M602S(const ACE_CString &packet);
int processPacket_KRX_I702S(const ACE_CString& packet);
int handleETNEarlyRedemptionCriteria(const ACE_CString &packet);
int processPacket_KRX_A302S(const ACE_CString& packet);
int processPacket_KRX_B902S(const ACE_CString& packet);
int processPacket_KRX_M402S(const ACE_CString& packet);
int processPacket_KRX_I602S(const ACE_CString& packet);
int handleETNProfitStructureDetails(const ACE_CString &packet);
int handleETP_Constituents(const ACE_CString &packet);
#endif

#if(0)
int handleQuote10(const ACE_CString &packet);
int handleTradeFixed(const ExtureGroupCTrade &elwRawData);
int handleMarketOperationTS(const ACE_CString &packet);
int handleTrade(const ACE_CString &packet);
int handleSecuritiesTrade(const ACE_CString &packet);
int handleMarketOperationScheduleDisclosure(const ACE_CString &packet);
int handleKOSPIIssueEventInformation(const ACE_CString &packet);
int handleElwRecoveryTotalTrade(const ACE_CString &packet);
int handleRecoveryTotalTrade(const ACE_CString &packet);
int handleRecoveryTrade(const ACE_CString &packet);
#endif

#if(0)
//handler
BYTE getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID);
BYTE getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID);
int getTickTime(const ACE_CString& timeStr, const ACE_CString &frameId);
BYTE getMarketInTrade(const ACE_CString& raw);
BYTE getUpDownInTrade(const ACE_CString& raw);

BYTE getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID);
BYTE getExchange(char rawSymbolType);
BYTE getExhaustInForeigner(const ACE_CString& raw);
#endif

#if(0)
ACE_CString getSymbolMarketTypeCode(const ACE_CString& raw);
ACE_CString getSymbolUpCode(const ACE_CString& raw);
#endif

#if(1)
int InternetElwChannelProcessor::handleElwDataToQueueProcedure(const ACE_CString &packet);
#endif

#if(1)
public:

int   main_qkey, standby_qkey;
int   g_msg_id_main, g_msg_id_standby;

struct msqid_ds msqstat;
struct msqid_ds msqstat_standby;

struct queue_message_buffer {
	long mtype;
	char mtext[8192];
};
struct queue_message_buffer msg_buf;
#endif

    protected:
        const std::vector<ACE_CString> &getTradeTypeList();
        void initTradeTypeList();

    protected:
        std::vector<ACE_CString> tradeTypeList_;
};

#endif
