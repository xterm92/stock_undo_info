#include <sstream>
#include <utility>

#include "InvestorCodeConverter.h"
#include "InternetElwChannelProcessor.h"

#include "PaxfeedDefine.h"
#include "PaxfeedPacket.h"
#include "PaxfeedPacketELW.h"
#include "ace/Log_Msg.h"
#include "MMapAllocator.h"
#include "PaxfeedStatus.h"
#include "PaxfeedStringUtil.h"
#include "TickFilter.h"
#include "MasterElwProcessor.h"
#include "SimpleStringUtil.h"
#include <exception>
#include <boost/algorithm/string.hpp>

using namespace paxfeed;

InternetElwChannelProcessor::InternetElwChannelProcessor(const ACE_CString &channelName)
        : InternetChannelProcessor(channelName)
{
    initTradeTypeList();
}

InternetElwChannelProcessor::~InternetElwChannelProcessor()
{

}

int InternetElwChannelProcessor::reset()
{
    InternetChannelProcessor::reset();
    return 0;
}

const std::vector<ACE_CString>& InternetElwChannelProcessor::getTradeTypeList()
{
    return tradeTypeList_;
}

void InternetElwChannelProcessor::initTradeTypeList()
{
    /*
     * mysql> SELECT DISTINCT BOARD_ID, BOARD_DESC FROM TBFC_KRX_CODE_BOARD_EVENT ORDER BY BOARD_ID ASC;
     +----------+------------------------+
     | BOARD_ID | BOARD_DESC             |
     +----------+------------------------+
     | B1       | 대량정규장             |
     | B2       | 대량장개시전시간외     |
     | B3       | 대량장종료후시간외     |
     | E1       | EFP                    |
     | F1       | FLEX정규장             |
     | F1       | 정규장 FLEX            |
     | G1       | 정규장                 |
     | G2       | 장개시전시간외종가     |
     | G3       | 장종료후시간외종가     |
     | G4       | 장종료후시간외단일가   |
     | G5       | 경매매장개시전시간외   |
     | G7       | 일반Buy-In             |
     | G8       | 당일Buy-In             |
     | I1       | 경쟁대량정규장         |
     | I2       | 경쟁대량장개시전시간외 |
     | K1       | 바스켓정규장           |
     | K2       | 바스켓장개시전시간외   |
     | K3       | 바스켓장종료후시간외   |
     | N1       | 협의대량정규장         |
     | R1       | RFQ                    |
     | S1       | 일반신고매매           |
     | SA       | 국채금융신고매매       |
     | SB       | 정부REPO신고매매       |
     | U2       | 장개시전협의거래       |
     +----------+------------------------+
     24 rows in set (0.00 sec)

     mysql>
     *
     */
    tradeTypeList_.clear();
    tradeTypeList_.push_back("B1");
    tradeTypeList_.push_back("B2");
    tradeTypeList_.push_back("B3");
    tradeTypeList_.push_back("E1");
    tradeTypeList_.push_back("F1");
    tradeTypeList_.push_back("G1");
    tradeTypeList_.push_back("G2");
    tradeTypeList_.push_back("G3");
    tradeTypeList_.push_back("G4");
    tradeTypeList_.push_back("G5");
    tradeTypeList_.push_back("G7");
    tradeTypeList_.push_back("G8");
    tradeTypeList_.push_back("I1");
    tradeTypeList_.push_back("I2");
    tradeTypeList_.push_back("K1");
    tradeTypeList_.push_back("K2");
    tradeTypeList_.push_back("K3");
    tradeTypeList_.push_back("N1");
    tradeTypeList_.push_back("R1");
    tradeTypeList_.push_back("S1");
    tradeTypeList_.push_back("SA");
    tradeTypeList_.push_back("SB");
    tradeTypeList_.push_back("U2");
    tradeTypeList_.push_back("ZZ");


#if(1)
	sscanf("4080", "%x", &main_qkey);
	sscanf("4081", "%x", &standby_qkey);

    g_msg_id_main = msgget(main_qkey, IPC_CREAT | 0666 );

    if(g_msg_id_main == -1)
    {
		//ERROR
    }
    if(msgctl(g_msg_id_main, IPC_STAT, &msqstat) == -1)
    {
		//ERROR
    }
    if(msqstat.msg_qnum > 0)
    {
        if(msgctl(g_msg_id_main, IPC_RMID, 0) == -1)
        {
			//ERROR
        }  
    }
#endif	

#if(1)
	g_msg_id_standby = msgget(standby_qkey, IPC_CREAT | 0666 );

    if(g_msg_id_standby == -1)
    {
		//ERROR
    }
    if(msgctl(g_msg_id_standby, IPC_STAT, &msqstat_standby) == -1)
    {
		//ERROR
    }
    if(msqstat_standby.msg_qnum > 0)
    {
        if(msgctl(g_msg_id_standby, IPC_RMID, 0) == -1)
        {
			//ERROR
        }  
    }
#endif
    return;
}

#if(1)
int InternetElwChannelProcessor::processPacket(const ACE_CString &packet)
{
    ACE_CString dataType(packet.substr(0, 5));

    if ( dataType == "A003S" ) //(증권C) STK : A002S, A003S, A004S
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.masterGroupCProc(packet);
    }
	else if ( dataType == "A004S" ) //(증권C) STK : A002S, A003S, A004S
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.masterGroupCProc(packet);
    }
	else if ( dataType == "X304S" ) //(증권C) STK : X304S
    {
        handleETNEarlyRedemptionCriteria(packet);
    }
	else if(dataType=="X804S")//(증권C) STK : X804S
	{
		handleETNProfitStructureDetails(packet);
	}
	else if(dataType=="V600S")//(증권C) STK : V600S
	{
		handleETP_Constituents(packet);
	}
	else if (dataType == "A104S" ) //(증권C) STK : A104S
    {
        handleETNInformationBatch(packet);
    }
	else if(dataType=="A703S")
	{
		handleMarketOperationTS(packet);
	}
	else if(dataType=="A704S")
	{
		handleMarketOperationTS(packet);
	}
	else if(dataType=="A303S")
	{
		handleTrade(packet);
	}
	else if(dataType=="A304S")
	{
		handleTrade(packet);
	}
	else if(dataType=="B903S")
    {
        handleSecuritiesTrade(packet);
    }
	else if(dataType=="B904S")
    {
        handleSecuritiesTrade(packet);
    }
	else if(dataType=="M403S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
	else if(dataType=="M404S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
	else if(dataType=="I603S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
	else if(dataType=="I604S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
	else if ( dataType == "B703S" ) //(증권C) STK : B702S, B703S, B704S
    {
        handleQuote10(packet);
    }
	else if ( dataType == "B704S" ) //(증권C) STK : B702S, B703S, B704S
    {
        handleQuote10(packet);
    }
	else if ( dataType == "B203S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleRecoveryTotalTrade(packet);
    }
	else if ( dataType == "B204S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleRecoveryTotalTrade(packet);
    }
#if(1)
	else if ( dataType == "A002S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "A102S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "B202S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "B902S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "A802S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "A302S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "A602S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "A702S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "B702S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "I602S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "I702S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
	else if ( dataType == "C602S" )
	{
	    handleElwDataToQueueProcedure(packet);;
	}
#endif
	else
	{
		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket] skip...... dataType:[%s]\tpacket:[%s]\tlength:[%d]\n" , getCurrentTimestamp().c_str() , dataType.c_str() , packet.c_str() , packet.length() ));
    }
    return ( 0 );
}
#endif


#if(1)
int InternetElwChannelProcessor::handleElwDataToQueueProcedure(const ACE_CString &packet)
{
	int ff=0;

#if(0)
	msg_buf.mtype = 1;
	memcpy(&msg_buf.mtext[0], packet.c_str(), packet.length());

	if(memcmp(&msg_buf.mtext[0],"A002S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"A102S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"B202S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"B902S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"A802S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"A302S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"A602S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"A702S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"B702S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"I602S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"I702S",5)==0) ff=100;
	else if(memcmp(&msg_buf.mtext[0],"C602S",5)==0) ff=100;

	if(ff == 100)
	{
		if(msgsnd(g_msg_id_main, (struct queue_message_buffer *)&msg_buf, packet.length(), 0) < 0)
		{
			//
		}
		else
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket] msgsnd(1) succ:TR[%.*s]\n" , getCurrentTimestamp().c_str(), 5, &msg_buf.mtext[0]));
		}

		if(msgsnd(g_msg_id_standby, (struct queue_message_buffer *)&msg_buf, packet.length(), 0) < 0)
		{
			//
		}
		else
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket] msgsnd(2) succ:TR[%.*s]\n" , getCurrentTimestamp().c_str(), 5, &msg_buf.mtext[0]));
		}
	}
#endif

#if(1)
	msg_buf.mtype = 1;
	memcpy(&msg_buf.mtext[0], packet.c_str(), packet.length());

	if(msgsnd(g_msg_id_main, (struct queue_message_buffer *)&msg_buf, packet.length(), 0) < 0)
	{
		//
	}
	else
	{
		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket] msgsnd(1) succ:TR[%.*s]\n" , getCurrentTimestamp().c_str(), 5, &msg_buf.mtext[0]));
	}

	if(msgsnd(g_msg_id_standby, (struct queue_message_buffer *)&msg_buf, packet.length(), 0) < 0)
	{
		//
	}
	else
	{
		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket] msgsnd(2) succ:TR[%.*s]\n" , getCurrentTimestamp().c_str(), 5, &msg_buf.mtext[0]));
	}
#endif

    return ( 0 );
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETNProfitStructureDetails(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] Skip : %s, %d : EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwETNProfitStructureDetails rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString data_category(rawRec.data_category, sizeof ( rawRec.data_category ));
    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString etn_profit_structure_details(rawRec.etn_profit_structure_details, sizeof ( rawRec.etn_profit_structure_details ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] etn_profit_structure_details:[%s]\n" , getCurrentTimestamp().c_str() , etn_profit_structure_details.c_str() ));

    if ( issue_code == "999999999999" )
    {
        ACE_DEBUG( ( LM_INFO , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] - Skip dummy data(%s)\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
        return ( 0 );
    }

    int result = 0;
    return ( result );
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETNInformationBatch(const ACE_CString &packet)
{
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket],packet:[%d]\tlength:[%d]\n" , getCurrentTimestamp().c_str() , EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE , packet.length() ));

    if ( EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] Skip : %s, %d : EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE , packet.length() , packet.c_str() ), -1);
    }

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket],packet:[%d]\tlength:[%d]\n" , getCurrentTimestamp().c_str() , EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE , packet.length() ));

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwETNInformationBatch rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString dataSeqNumber(rawRec.dataSeqNumber, sizeof ( rawRec.dataSeqNumber ));
    ACE_CString etnIssueMarketParticipantKoreanName(rawRec.etnIssueMarketParticipantKoreanName, sizeof ( rawRec.etnIssueMarketParticipantKoreanName ));
    ACE_CString etnIssueMarketParticipantEnglishName(rawRec.etnIssueMarketParticipantEnglishName, sizeof ( rawRec.etnIssueMarketParticipantEnglishName ));
    ACE_CString etnIssueMarketParticipantNo(rawRec.etnIssueMarketParticipantNo, sizeof ( rawRec.etnIssueMarketParticipantNo ));
    ACE_CString etnFinalSettlementMethodCode(rawRec.etnFinalSettlementMethodCode, sizeof ( rawRec.etnFinalSettlementMethodCode ));
    ACE_CString etnLastTradingDate(rawRec.etnLastTradingDate, sizeof ( rawRec.etnLastTradingDate ));
    ACE_CString etnPaymentDate(rawRec.etnPaymentDate, sizeof ( rawRec.etnPaymentDate ));
    ACE_CString etnLPHoldingQuantity(rawRec.etnLPHoldingQuantity, sizeof ( rawRec.etnLPHoldingQuantity ));

    ACE_CString lossProtectionEtnProfitStructureCode(rawRec.lossProtectionEtnProfitStructureCode, sizeof ( rawRec.lossProtectionEtnProfitStructureCode ));
    ACE_CString etnMaximumRedemptionPrice(rawRec.etnMaximumRedemptionPrice, sizeof ( rawRec.etnMaximumRedemptionPrice ));
    ACE_CString etnMinimumRedemptionPrice(rawRec.etnMinimumRedemptionPrice, sizeof ( rawRec.etnMinimumRedemptionPrice ));
    ACE_CString etnEarlyRedemptionPossibility(rawRec.etnEarlyRedemptionPossibility, sizeof ( rawRec.etnEarlyRedemptionPossibility ));
    ACE_CString etnEarlyRedemptionPeriodCode(rawRec.etnEarlyRedemptionPeriodCode, sizeof ( rawRec.etnEarlyRedemptionPeriodCode ));
    ACE_CString appraisedPriceCalculationInstitutionCode1(rawRec.appraisedPriceCalculationInstitutionCode1, sizeof ( rawRec.appraisedPriceCalculationInstitutionCode1 ));
    ACE_CString appraisedPriceCalculationInstitutionCode2(rawRec.appraisedPriceCalculationInstitutionCode2, sizeof ( rawRec.appraisedPriceCalculationInstitutionCode2 ));

    /*
     * 2017.03.22
     * 현재 ETNInformationBatch 를 사용하는 곳이 없다.
     * 모의투자에서도 미사용중
     * 시세DB 적재도 하지 않음
     */

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        return 0;
    }

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] dataSeqNumber:[%s]\n" , getCurrentTimestamp().c_str() , dataSeqNumber.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnIssueMarketParticipantKoreanName:[%s]\n" , getCurrentTimestamp().c_str() , etnIssueMarketParticipantKoreanName.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnIssueMarketParticipantEnglishName:[%s]\n" , getCurrentTimestamp().c_str() , etnIssueMarketParticipantEnglishName.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnIssueMarketParticipantNo:[%s]\n" , getCurrentTimestamp().c_str() , etnIssueMarketParticipantNo.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnFinalSettlementMethodCode:[%s]\n" , getCurrentTimestamp().c_str() , etnFinalSettlementMethodCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnLastTradingDate:[%s]\n" , getCurrentTimestamp().c_str() , etnLastTradingDate.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnPaymentDate:[%s]\n" , getCurrentTimestamp().c_str() , etnPaymentDate.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnLPHoldingQuantity:[%s]\n" , getCurrentTimestamp().c_str() , etnLPHoldingQuantity.c_str() ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] lossProtectionEtnProfitStructureCode:[%s]\n" , getCurrentTimestamp().c_str() , lossProtectionEtnProfitStructureCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnMaximumRedemptionPrice:[%s]\n" , getCurrentTimestamp().c_str() , etnMaximumRedemptionPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnMinimumRedemptionPrice:[%s]\n" , getCurrentTimestamp().c_str() , etnMinimumRedemptionPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnEarlyRedemptionPossibility:[%s]\n" , getCurrentTimestamp().c_str() , etnEarlyRedemptionPossibility.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnEarlyRedemptionPeriodCode:[%s]\n" , getCurrentTimestamp().c_str() , etnEarlyRedemptionPeriodCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] appraisedPriceCalculationInstitutionCode1:[%s]\n" , getCurrentTimestamp().c_str() , appraisedPriceCalculationInstitutionCode1.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] appraisedPriceCalculationInstitutionCode2:[%s]\n" , getCurrentTimestamp().c_str() , appraisedPriceCalculationInstitutionCode2.c_str() ));

    ETNInformationBatch batch;
    ::memset(&batch, 0, sizeof(ETNInformationBatch));
    ::memcpy(& ( batch.symbol ), issueCode.c_str(), issueCode.length());
    batch.registerDt = (int) ( ::time(0) );
    ::memcpy(& ( batch.etnIssueMarketParticipantKoreanName ), etnIssueMarketParticipantKoreanName.c_str(), etnIssueMarketParticipantKoreanName.length());
    ::memcpy(& ( batch.etnIssueMarketParticipantEnglishName ), etnIssueMarketParticipantEnglishName.c_str(), etnIssueMarketParticipantEnglishName.length());
    ::memcpy(& ( batch.etnIssueMarketParticipantNo ), etnIssueMarketParticipantNo.c_str(), etnIssueMarketParticipantNo.length());
    ::memcpy(& ( batch.etnFinalSettlementMethodCode ), etnFinalSettlementMethodCode.c_str(), etnFinalSettlementMethodCode.length());
    ::memcpy(& ( batch.etnLastTradingDate ), etnLastTradingDate.c_str(), etnLastTradingDate.length());
    ::memcpy(& ( batch.etnPaymentDate ), etnPaymentDate.c_str(), etnPaymentDate.length());
    batch.etnLPHoldingQuantity = ::atof(etnLPHoldingQuantity.c_str());
    ::memcpy(& ( batch.lossProtectionEtnProfitStructureCode ), lossProtectionEtnProfitStructureCode.c_str(), lossProtectionEtnProfitStructureCode.length());
    batch.etnMaximumRedemptionPrice = ::atof(etnMaximumRedemptionPrice.c_str());
    batch.etnMinimumRedemptionPrice = ::atof(etnMinimumRedemptionPrice.c_str());
    ::memcpy(& ( batch.etnEarlyRedemptionPossibility ), etnEarlyRedemptionPossibility.c_str(), etnEarlyRedemptionPossibility.length());
    ::memcpy(& ( batch.etnEarlyRedemptionPeriodCode ), etnEarlyRedemptionPeriodCode.c_str(), etnEarlyRedemptionPeriodCode.length());
    ::memcpy(& ( batch.appraisedPriceCalculationInstitutionCode1 ), appraisedPriceCalculationInstitutionCode1.c_str(), appraisedPriceCalculationInstitutionCode1.length());
    ::memcpy(& ( batch.appraisedPriceCalculationInstitutionCode2 ), appraisedPriceCalculationInstitutionCode2.c_str(), appraisedPriceCalculationInstitutionCode2.length());

    printPacketETNInformationBatch(batch);

    char buf[ETN_INFORMATION_BATCH_SIZE];
    ::memset(&buf, 0, ETN_INFORMATION_BATCH_SIZE);
    ::memcpy(&buf, &batch, ETN_INFORMATION_BATCH_SIZE);
    int resultBatch = sendPacket(ACE_CString(buf, ETN_INFORMATION_BATCH_SIZE), PACKET_ETN_INFORMATION_BATCH, EXCHANGE_KSE);
    return resultBatch;
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETP_Constituents(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_ETP_TOTAL_CONSTITUENTS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] Skip : %s, %d : EXTURE_PLUS_KOSPI_ETP_CONSTITUENTS_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_ETP_CONSTITUENTS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwKOSPI_ETP_ToTalConstituents totalrawRec;
    ACE_OS::memcpy(&totalrawRec, packet.c_str(), packet.length());

    ExturePlusElwKOSPI_ETP_Constituents rawRec;

    ::memcpy(rawRec.index_calculation_institution_code, totalrawRec.index_calculation_institution_code, sizeof(rawRec.index_calculation_institution_code));
    ::memcpy(rawRec.index_market_classification_id, totalrawRec.index_market_classification_id, sizeof(rawRec.index_market_classification_id));
    ::memcpy(rawRec.index_seq_number, totalrawRec.index_seq_number, sizeof(rawRec.index_seq_number));
    ::memcpy(rawRec.index_leverage_inverse_type_code, totalrawRec.index_leverage_inverse_type_code, sizeof(rawRec.index_leverage_inverse_type_code));
    ::memcpy(rawRec.index_name, totalrawRec.index_name, sizeof(rawRec.index_name));
    ::memcpy(rawRec.index_name_english, totalrawRec.index_name_english, sizeof(rawRec.index_name_english));
    ::memcpy(rawRec.index_asset_classification_id_1, totalrawRec.index_asset_classification_id_1, sizeof(rawRec.index_asset_classification_id_1));
    ::memcpy(rawRec.index_asset_classification_id_2, totalrawRec.index_asset_classification_id_2, sizeof(rawRec.index_asset_classification_id_2));

    ACE_CString data_category(rawRec.data_category, sizeof ( rawRec.data_category ));
    ACE_CString index_calculation_institution_code(rawRec.index_calculation_institution_code, sizeof ( rawRec.index_calculation_institution_code ));
    ACE_CString index_market_classification_id(rawRec.index_market_classification_id, sizeof ( rawRec.index_market_classification_id ));
    ACE_CString index_seq_number(rawRec.index_seq_number, sizeof ( rawRec.index_seq_number ));
    ACE_CString index_leverage_inverse_type_code(rawRec.index_leverage_inverse_type_code, sizeof ( rawRec.index_leverage_inverse_type_code ));
    ACE_CString index_name(rawRec.index_name, sizeof ( rawRec.index_name ));
    ACE_CString index_name_english(rawRec.index_name_english, sizeof ( rawRec.index_name_english ));
    ACE_CString index_asset_classification_id_1(rawRec.index_asset_classification_id_1, sizeof ( rawRec.index_asset_classification_id_1 ));
    ACE_CString index_asset_classification_id_2(rawRec.index_asset_classification_id_2, sizeof ( rawRec.index_asset_classification_id_2 ));
#if(0)
    ACE_CString index_associated_market_type_code(rawRec.index_associated_market_type_code, sizeof ( rawRec.index_associated_market_type_code ));
    ACE_CString industry_index_code(rawRec.industry_index_code, sizeof ( rawRec.industry_index_code ));
#endif
#if(1)
    ACE_CString jisuid(totalrawRec.jisuID, sizeof ( totalrawRec.jisuID ));
    ACE_CString index_associated_market_type_code = getSymbolMarketTypeCode(jisuid);
    if(index_associated_market_type_code == "0") index_associated_market_type_code = " ";
    ACE_CString industry_index_code = getSymbolUpCode(jisuid);
    if(industry_index_code == "000") industry_index_code = "   ";
#endif

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_calculation_institution_code:[%s]\n" , getCurrentTimestamp().c_str() , index_calculation_institution_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_market_classification_id:[%s]\n" , getCurrentTimestamp().c_str() , index_market_classification_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_seq_number:[%s]\n" , getCurrentTimestamp().c_str() , index_seq_number.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_leverage_inverse_type_code:[%s]\n" , getCurrentTimestamp().c_str() , index_leverage_inverse_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_name:[%s]\n" , getCurrentTimestamp().c_str() , index_name.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_name_english:[%s]\n" , getCurrentTimestamp().c_str() , index_name_english.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_asset_classification_id_1:[%s]\n" , getCurrentTimestamp().c_str() , index_asset_classification_id_1.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_asset_classification_id_2:[%s]\n" , getCurrentTimestamp().c_str() , index_asset_classification_id_2.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_associated_market_type_code:[%s]\n" , getCurrentTimestamp().c_str() , index_associated_market_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] industry_index_code:[%s]\n" , getCurrentTimestamp().c_str() , industry_index_code.c_str() ));

    int result = 0;
    return ( result );
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] Skip : %s, %d : EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwETNEarlyRedemptionCriteria rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString data_category(rawRec.data_category, sizeof ( rawRec.data_category ));
    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString etn_early_redemption_period_code(rawRec.etn_early_redemption_period_code, sizeof ( rawRec.etn_early_redemption_period_code ));
    ACE_CString early_redemption_appraisal_date(rawRec.early_redemption_appraisal_date, sizeof ( rawRec.early_redemption_appraisal_date ));
    ACE_CString early_redemption_criteria_relation_code(rawRec.early_redemption_criteria_relation_code, sizeof ( rawRec.early_redemption_criteria_relation_code ));
    ACE_CString early_redemption_base_index_1(rawRec.early_redemption_base_index_1, sizeof ( rawRec.early_redemption_base_index_1 ));
    ACE_CString early_redemption_base_index_2(rawRec.early_redemption_base_index_2, sizeof ( rawRec.early_redemption_base_index_2 ));
    ACE_CString early_redemption_price_before_expenses(rawRec.early_redemption_price_before_expenses, sizeof ( rawRec.early_redemption_price_before_expenses ));
    ACE_CString early_redemption_payment_date(rawRec.early_redemption_payment_date, sizeof ( rawRec.early_redemption_payment_date ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] etn_early_redemption_period_code:[%s]\n" , getCurrentTimestamp().c_str() , etn_early_redemption_period_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_appraisal_date:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_appraisal_date.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_criteria_relation_code:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_criteria_relation_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_base_index_1:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_base_index_1.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_base_index_2:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_base_index_2.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_price_before_expenses:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_price_before_expenses.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_payment_date:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_payment_date.c_str() ));

    if ( issue_code == "999999999999" )
    {
        ACE_DEBUG( ( LM_INFO , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] - Skip dummy data(%s)\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
        return ( 0 );
    }

    int result = 0;
    return ( result );
}
#endif

#if(0)
else if(dataType=="A703S") handleMarketOperationTS(packet);
else if(dataType=="A704S") handleMarketOperationTS(packet);
#endif
int InternetElwChannelProcessor::handleMarketOperationTS(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationTS] BEGIN\n" , getCurrentTimestamp().c_str() ));
    if ( EXTURE_GROUP_C_MARKET_OPERATION_TS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleMarketOperationTS] Skip : %s, %d : EXTURE_GROUP_C_MARKET_OPERATION_TS_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_GROUP_C_MARKET_OPERATION_TS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExtureGroupCMarketOperationTS rawRec;
    ::memset(&rawRec, 0, sizeof(ExtureGroupCMarketOperationTS));
    ::memcpy(&rawRec, packet.c_str(), sizeof(ExtureGroupCMarketOperationTS));

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

    std::string issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    boost::trim(issueCode);

    if ( issueCode == std::string("") )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationTS] invalid issueCode:[%s][%d] skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , issueCode.length() ));
        return 0;
    }

    ACE_CString symbol(issueCode.c_str());

    ::memcpy(&marketRec.symbol, symbol.c_str(), symbol.length());
    marketRec.recvTime = (int) ( ::time(0) );
    ::memcpy(&marketRec.boardId, rawRec.boardID, sizeof ( rawRec.boardID ));
    ::memcpy(&marketRec.boardEventId, rawRec.boardEventID, sizeof ( rawRec.boardEventID ));
    ::memcpy(&marketRec.beginTime, rawRec.boardEventBeginTime, sizeof ( rawRec.boardEventBeginTime ));
    ::memcpy(&marketRec.tradingHaltReason, rawRec.tradingHaltReasonCode, sizeof ( rawRec.tradingHaltReasonCode ));

    printPacketMarketOperation(marketRec);

    char buf[MARKET_OPERATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &marketRec, sizeof(MarketOperation));
    int result = sendPacket(ACE_CString(buf, MARKET_OPERATION_SIZE), PACKET_MARKET_OPERATION, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationTS] result:[%d]\n" , getCurrentTimestamp().c_str() , result ));
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationTS] END\n" , getCurrentTimestamp().c_str() ));
    return result;
}
#if(0)
else if(dataType=="A303S") handleTrade(packet);
else if(dataType=="A304S") handleTrade(packet);
#endif
int InternetElwChannelProcessor::handleTradeFixed(const ExtureGroupCTrade &elwRawData)
{
    Trade trade;
    ACE_CString stockCode(elwRawData.stockCode, sizeof elwRawData.stockCode);

    TickFilter filter;

    ACE_CString upDown(elwRawData.upDown, sizeof elwRawData.upDown);

    trade.market = MARKET_IN;
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(elwRawData.openPrice, sizeof elwRawData.openPrice).c_str());
    trade.high = atoi(ACE_CString(elwRawData.highPrice, sizeof elwRawData.highPrice).c_str());
    trade.low = atoi(ACE_CString(elwRawData.lowPrice, sizeof elwRawData.lowPrice).c_str());
    trade.close = atoi(ACE_CString(elwRawData.tradePrice, sizeof elwRawData.tradePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(elwRawData.gap, sizeof elwRawData.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(elwRawData.accmTradeVolume, sizeof elwRawData.accmTradeVolume).c_str());
    double accmAmount = ::atof(ACE_CString(elwRawData.accmTradeAmount, sizeof elwRawData.accmTradeAmount).c_str());
    trade.accmVolume = accmVolume;
    trade.amount = accmAmount;

    trade.subtype = TRADESUBTYPE_TRADE;
    trade.tradeVolume = 0;
    trade.exchange = EXCHANGE_KSE;
    trade.symbolType = SYMBOL_STOCK;
    trade.decimalPoint = DECIMAL_0;
    trade.tradeTime = time(0);
    ACE_OS::memcpy(&trade.symbol, &elwRawData.stockCode, sizeof elwRawData.stockCode);

    trade.openMin = 0;
    trade.highMin = 0;
    trade.lowMin = 0;
    trade.volumeMin = 0;

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE_FIXED, EXCHANGE_KSE);

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTradeFixed] stockCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , result ));

#if(1)
    printPacketTrade(trade);
#endif

    return result;
}
int InternetElwChannelProcessor::handleTrade(const ACE_CString &packet)
{
    if ( EXTURE_GROUP_C_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleTrade] Skip : %s,%d : EXTURE_GROUP_C_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_GROUP_C_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());
	ACE_CString dataType(packet.substr(0, 5));

    ACE_CString frameId = "A3";

    ExtureGroupCTrade rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());
    ACE_CString stockCode(rawRec.stockCode, sizeof rawRec.stockCode);
    ACE_CString isNormalstockCode(rawRec.stockCode, ( sizeof rawRec.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.


	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] stockCode  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.stockCode),rawRec.stockCode ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] boardID    :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.boardID),rawRec.boardID ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] sessionID  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.sessionID),rawRec.sessionID ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] transactionProcessingTime:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.transactionProcessingTime),rawRec.transactionProcessingTime ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] upDown     :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.upDown),rawRec.upDown ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] gap        :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.gap),rawRec.gap ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] tradePrice :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.tradePrice),rawRec.tradePrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] tradeVolume:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.tradeVolume),rawRec.tradeVolume ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] openPrice  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.openPrice),rawRec.openPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] highPrice  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.highPrice),rawRec.highPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] lowPrice   :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.lowPrice),rawRec.lowPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] accmTradeVolume:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.accmTradeVolume),rawRec.accmTradeVolume ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTrade] accmTradeAmount:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.accmTradeAmount),rawRec.accmTradeAmount ));

    ACE_CString boardID(rawRec.boardID, sizeof ( rawRec.boardID ));
    ACE_CString sessionID(rawRec.sessionID, sizeof ( rawRec.sessionID ));

    if ( ( boardID == "G7" ) || ( boardID == "G8" ) )
    {
        return 0;
    }
    if ( sessionID == "25" )
    {
        return 0;
    }

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));
    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

#if(0)
    // 정규시간외구분코드 : 장종료후시간외단일가(4) , 체결유형코드 : 시간외단일가(70)
    // 4    장종료후시간외단일가  G4  유가/코스닥
    if ( ( boardID == "G4" ) || ( sessionID == "70" ) )
    {
        return handleTradeFixed(rawRec); //시간외단일가
    }
#endif
#if(1)
    // 정규시간외구분코드 : 장종료후시간외단일가(4) , 체결유형코드 : 시간외단일가(70)
    // 4    장종료후시간외단일가  G4  유가/코스닥
    if ( ( boardID == "G4" ) )
    {
        return handleTradeFixed(rawRec); //시간외단일가
    }
#endif

    ACE_CString upDown(rawRec.upDown, sizeof rawRec.upDown);
    trade.market = getMarketInTrade(boardID);
    trade.upDown = getUpDownInTrade(upDown);

    // 장개시전시간외거래인 경우 시가, 고가, 저가는 0으로 셋팅하고 종가는 체결가로 셋팅한다.
    if ( ( boardID == "G2" ) || ( sessionID == "50" ) )
    {
        trade.open = 0;
        trade.high = 0;
        trade.low = 0;
        trade.close = atoi(ACE_CString(rawRec.tradePrice, sizeof rawRec.tradePrice).c_str());
    }
    //장종료후시간외종가거래인 경우 시가, 고가, 저가, 종가는 그대로 두고, 체결량만 변경한다.
    else if ( boardID == "G3" || sessionID == "65" )  //
    {
        //가격을 셋팅하지 않는다.
        if ( hasValue == -1 )
        {
            return 0;
        }
    }
    else
    {
        trade.open = atoi(ACE_CString(rawRec.openPrice, sizeof rawRec.openPrice).c_str());
        trade.high = atoi(ACE_CString(rawRec.highPrice, sizeof rawRec.highPrice).c_str());
        trade.low = atoi(ACE_CString(rawRec.lowPrice, sizeof rawRec.lowPrice).c_str());
        trade.close = atoi(ACE_CString(rawRec.tradePrice, sizeof rawRec.tradePrice).c_str());
    }

    ACE_CString tradePrice(rawRec.tradePrice, sizeof ( rawRec.tradePrice ));
    ACE_CString openPrice(rawRec.openPrice, sizeof ( rawRec.openPrice ));
    ACE_CString highPrice(rawRec.highPrice, sizeof ( rawRec.highPrice ));
    ACE_CString lowPrice(rawRec.lowPrice, sizeof ( rawRec.lowPrice ));

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(rawRec.gap, sizeof rawRec.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(rawRec.accmTradeVolume, sizeof rawRec.accmTradeVolume).c_str());
    double accmAmount = ::atof(ACE_CString(rawRec.accmTradeAmount, sizeof rawRec.accmTradeAmount).c_str());

	//차세대 시스템(체결가격이 존재하므로 값을 직접 입력)
    trade.tradeVolume = ::atof(ACE_CString(rawRec.tradeVolume, sizeof rawRec.tradeVolume).c_str());

    if ( trade.tradeVolume < 0 )
    {
        /*
         * APP 재기동후 간혹 오류가 나는 경우가 있다.
         * 해당 boardID 의 accmVolume 을 현재것으로 처리하고 다음 리커버리를 기다린다.
         */
        setAccmVolume(stockCode, accmVolume, boardID);
        setAccmAmount(stockCode, accmAmount, boardID);
        trade.tradeVolume = 0;
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleTrade] Skip : %s,%d : net volume error stockCode:[%s] trade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , trade.tradeVolume ), -1);
    }

    setAccmVolume(stockCode, accmVolume, boardID);
    setAccmAmount(stockCode, accmAmount, boardID);

    trade.accmVolume = getTotalAccmVolume(stockCode);

    if ( trade.accmVolume == -1 )
    {
        trade.accmVolume = 0;   //accmVolume ;
    }

    int tradeTime = getTickTime(ACE_CString(rawRec.transactionProcessingTime, sizeof rawRec.transactionProcessingTime), frameId);

    trade.amount = getTotalAccmAmount(stockCode);
    if ( trade.amount == -1 )
    {
        trade.amount = 0;   //amount ;
    }

    if ( hasValue == -1 )
    {
        trade.subtype = TRADESUBTYPE_TRADE;
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = getModTime(tradeTime);
        memcpy(&trade.symbol, &rawRec.stockCode, sizeof rawRec.stockCode);

        trade.openMin = trade.close;
        trade.highMin = trade.close;
        trade.lowMin = trade.close;
        trade.volumeMin = trade.tradeVolume;

        tradeMap_->bind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, ALLOCATOR::instance());
    }
    else
    {
        int previousTime = trade.tradeTime;
        trade.tradeTime = getModTime(tradeTime);
        if ( ( trade.tradeTime / 60 == previousTime / 60 ) && ( trade.volumeMin != 0 ) )
        {
            trade.volumeMin += trade.tradeVolume;

            if ( trade.close > trade.highMin )
            {
                trade.highMin = trade.close;
            }

            if ( trade.close < trade.lowMin )
            {
                trade.lowMin = trade.close;
            }
        }
        else
        {
            trade.volumeMin = trade.tradeVolume;
            trade.openMin = trade.close;
            trade.highMin = trade.close;
            trade.lowMin = trade.close;
        }
        ACE_CString oldKey;
        Trade oldVal;
        tradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());
    }

#if(1)
printPacketTrade(trade);
#endif

    char buf[TRADE_SIZE];
    ::memset(buf, 0, sizeof ( buf ));
    memcpy(buf, &trade, TRADE_SIZE);
	int result = 0;
    result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleTradeFixed] stockCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , result ));

    return 0;
}

#if(0)
else if(dataType=="B903S") handleSecuritiesTrade(packet);
else if(dataType=="B904S") handleSecuritiesTrade(packet);
#endif

int InternetElwChannelProcessor::handleSecuritiesTrade(const ACE_CString &packet)
{
    if ( EXTURE_GROUP_C_SECURITIES_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleSecuritiesTrade] Skip : %s, %d : EXTURE_GROUP_C_SECURITIES_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_GROUP_C_SECURITIES_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExtureGroupCSecuritiesTrade rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), EXTURE_GROUP_C_SECURITIES_TRADE_SIZE);

    SecuritiesTrade2 sec;
    ::memset(&sec, 0, sizeof(SecuritiesTrade2));
    sec.subtype = SECURITIESTRADESUBTYPE_TRADE;
    sec.exchange = EXCHANGE_KSE;
    sec.symbolType = SYMBOL_STOCK;
    ACE_CString stockCode(rawRec.stockCode, sizeof rawRec.stockCode);

    memcpy(sec.symbol, stockCode.c_str(), sizeof rawRec.stockCode);
    ACE_OS::memcpy(sec.rec1.seller, rawRec.rec[0].askSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[0].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec1.buyer, rawRec.rec[0].bidSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[0].bidSecuritiesTradeNumber ) - 2);
    sec.rec1.askVolume = atof(ACE_CString(rawRec.rec[0].askTradeVolume, sizeof rawRec.rec[0].askTradeVolume).c_str());
    sec.rec1.bidVolume = atof(ACE_CString(rawRec.rec[0].bidTradeVolume, sizeof rawRec.rec[0].bidTradeVolume).c_str());
    sec.rec1.askAmount = atof(ACE_CString(rawRec.rec[0].askTradeAmount, sizeof rawRec.rec[0].askTradeAmount).c_str());
    sec.rec1.bidAmount = atof(ACE_CString(rawRec.rec[0].bidTradeAmount, sizeof rawRec.rec[0].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec2.seller, rawRec.rec[1].askSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[1].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec2.buyer, rawRec.rec[1].bidSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[1].bidSecuritiesTradeNumber ) - 2);
    sec.rec2.askVolume = atof(ACE_CString(rawRec.rec[1].askTradeVolume, sizeof rawRec.rec[1].askTradeVolume).c_str());
    sec.rec2.bidVolume = atof(ACE_CString(rawRec.rec[1].bidTradeVolume, sizeof rawRec.rec[1].bidTradeVolume).c_str());
    sec.rec2.askAmount = atof(ACE_CString(rawRec.rec[1].askTradeAmount, sizeof rawRec.rec[1].askTradeAmount).c_str());
    sec.rec2.bidAmount = atof(ACE_CString(rawRec.rec[1].bidTradeAmount, sizeof rawRec.rec[1].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec3.seller, rawRec.rec[2].askSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[2].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec3.buyer, rawRec.rec[2].bidSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[2].bidSecuritiesTradeNumber ) - 2);
    sec.rec3.askVolume = atof(ACE_CString(rawRec.rec[2].askTradeVolume, sizeof rawRec.rec[2].askTradeVolume).c_str());
    sec.rec3.bidVolume = atof(ACE_CString(rawRec.rec[2].bidTradeVolume, sizeof rawRec.rec[2].bidTradeVolume).c_str());
    sec.rec3.askAmount = atof(ACE_CString(rawRec.rec[2].askTradeAmount, sizeof rawRec.rec[2].askTradeAmount).c_str());
    sec.rec3.bidAmount = atof(ACE_CString(rawRec.rec[2].bidTradeAmount, sizeof rawRec.rec[2].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec4.seller, rawRec.rec[3].askSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[3].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec4.buyer, rawRec.rec[3].bidSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[3].bidSecuritiesTradeNumber ) - 2);
    sec.rec4.askVolume = atof(ACE_CString(rawRec.rec[3].askTradeVolume, sizeof rawRec.rec[3].askTradeVolume).c_str());
    sec.rec4.bidVolume = atof(ACE_CString(rawRec.rec[3].bidTradeVolume, sizeof rawRec.rec[3].bidTradeVolume).c_str());
    sec.rec4.askAmount = atof(ACE_CString(rawRec.rec[3].askTradeAmount, sizeof rawRec.rec[3].askTradeAmount).c_str());
    sec.rec4.bidAmount = atof(ACE_CString(rawRec.rec[3].bidTradeAmount, sizeof rawRec.rec[3].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec5.seller, rawRec.rec[4].askSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[4].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec5.buyer, rawRec.rec[4].bidSecuritiesTradeNumber + 2, ( sizeof rawRec.rec[4].bidSecuritiesTradeNumber ) - 2);
    sec.rec5.askVolume = atof(ACE_CString(rawRec.rec[4].askTradeVolume, sizeof rawRec.rec[4].askTradeVolume).c_str());
    sec.rec5.bidVolume = atof(ACE_CString(rawRec.rec[4].bidTradeVolume, sizeof rawRec.rec[4].bidTradeVolume).c_str());
    sec.rec5.askAmount = atof(ACE_CString(rawRec.rec[4].askTradeAmount, sizeof rawRec.rec[4].askTradeAmount).c_str());
    sec.rec5.bidAmount = atof(ACE_CString(rawRec.rec[4].bidTradeAmount, sizeof rawRec.rec[4].bidTradeAmount).c_str());

    char buf[SECURITIES_TRADE2_SIZE];
    memcpy(buf, &sec, SECURITIES_TRADE2_SIZE);

    ACE_CString isNormalstockCode(rawRec.stockCode, ( sizeof rawRec.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    int result = 0;

    result = sendPacket(ACE_CString(buf, SECURITIES_TRADE2_SIZE), PACKET_SECURITIES_TRADE, EXCHANGE_KSE);

#if(0)
	if ( isNormalstockCode == "KRA" )
    {
        result = sendPacket(ACE_CString(buf, SECURITIES_TRADE2_SIZE), PACKET_SECURITIES_TRADE_ELW, EXCHANGE_KSE);
    }
#endif

#if(0)
printPacketSecuritiesTrade2(sec);
#endif

    return result;
}

#if(0)
else if(dataType=="M403S") handleMarketOperationScheduleDisclosure(packet);
else if(dataType=="M404S") handleMarketOperationScheduleDisclosure(packet);
#endif

#if(1)
int InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] BEGIN\n" , getCurrentTimestamp().c_str() ));
    if ( EXTURE_GROUP_C_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] Skip : %s, %d : EXTURE_GROUP_C_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_GROUP_C_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExtureGroupCMarketOperationScheduleDisclosure rawRec;
    ::memset(&rawRec, 0, sizeof(ExtureGroupCMarketOperationScheduleDisclosure));
    ::memcpy(&rawRec, packet.c_str(), sizeof(ExtureGroupCMarketOperationScheduleDisclosure));

    {
        ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
        ACE_CString marketCategory(rawRec.marketCategory, sizeof ( rawRec.marketCategory ));
        ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
        ACE_CString boardID(rawRec.boardID, sizeof ( rawRec.boardID ));
        ACE_CString boardEventID(rawRec.boardEventID, sizeof ( rawRec.boardEventID ));
        ACE_CString boardEventBeginTime(rawRec.boardEventBeginTime, sizeof ( rawRec.boardEventBeginTime ));
        ACE_CString boardEventApplyCode(rawRec.boardEventApplyCode, sizeof ( rawRec.boardEventApplyCode ));
        ACE_CString sessionBeginEndCode(rawRec.sessionBeginEndCode, sizeof ( rawRec.sessionBeginEndCode ));
        ACE_CString sessionID(rawRec.sessionID, sizeof ( rawRec.sessionID ));
        ACE_CString listedIssueCode(rawRec.listedIssueCode, sizeof ( rawRec.listedIssueCode ));
        ACE_CString tradingHaltReasonCode(rawRec.tradingHaltReasonCode, sizeof ( rawRec.tradingHaltReasonCode ));
        ACE_CString tradingHaltOccurenceTypeCode(rawRec.tradingHaltOccurenceTypeCode, sizeof ( rawRec.tradingHaltOccurenceTypeCode ));
        ACE_CString stepApplied(rawRec.stepApplied, sizeof ( rawRec.stepApplied ));

        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] dataCategory                  :[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] marketCategory                :[%s]\n" , getCurrentTimestamp().c_str() , marketCategory.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] issueCode                     :[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] boardID                       :[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] boardEventID                  :[%s]\n" , getCurrentTimestamp().c_str() , boardEventID.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] boardEventBeginTime           :[%s]\n" , getCurrentTimestamp().c_str() , boardEventBeginTime.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] boardEventApplyCode           :[%s]\n" , getCurrentTimestamp().c_str() , boardEventApplyCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] sessionBeginEndCode           :[%s]\n" , getCurrentTimestamp().c_str() , sessionBeginEndCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] sessionID                     :[%s]\n" , getCurrentTimestamp().c_str() , sessionID.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] listedIssueCode               :[%s]\n" , getCurrentTimestamp().c_str() , listedIssueCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] tradingHaltReasonCode         :[%s]\n" , getCurrentTimestamp().c_str() , tradingHaltReasonCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] tradingHaltOccurenceTypeCode  :[%s]\n" , getCurrentTimestamp().c_str() , tradingHaltOccurenceTypeCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] stepApplied                   :[%s]\n" , getCurrentTimestamp().c_str() , stepApplied.c_str() ));
    }

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

    std::string issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    boost::trim(issueCode);

    std::string listedIssueCode(rawRec.listedIssueCode, sizeof ( rawRec.listedIssueCode ));
    boost::trim(listedIssueCode);

    ACE_CString symbol;

    if ( ( issueCode == std::string("") ) || ( listedIssueCode == std::string("") ) )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] issueCode:[%s][%d]\tlistedIssueCode:[%s][%d]\t\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , issueCode.length() , listedIssueCode.c_str() , listedIssueCode.length() ));

        // 종목코드없을 경우 시장공통으로 설정
        symbol = "KRI001000000";
    }
    else
    {
        ACE_CString symbolTemp(issueCode.c_str());
        symbol = symbolTemp;
    }

    ::memcpy(&marketRec.symbol, symbol.c_str(), symbol.length());
    marketRec.recvTime = (int) ( ::time(0) );
    ::memcpy(&marketRec.boardId, rawRec.boardID, sizeof ( rawRec.boardID ));
    ::memcpy(&marketRec.boardEventId, rawRec.boardEventID, sizeof ( rawRec.boardEventID ));
    ::memcpy(&marketRec.beginTime, rawRec.boardEventBeginTime, sizeof ( rawRec.boardEventBeginTime ));
    ::memcpy(&marketRec.tradingHaltReason, rawRec.tradingHaltReasonCode, sizeof ( rawRec.tradingHaltReasonCode ));

    printPacketMarketOperation(marketRec);

    char buf[MARKET_OPERATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &marketRec, sizeof(MarketOperation));
    int result = sendPacket(ACE_CString(buf, MARKET_OPERATION_SIZE), PACKET_MARKET_OPERATION, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] result:[%d]\n" , getCurrentTimestamp().c_str() , result ));
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleMarketOperationScheduleDisclosure] END\n" , getCurrentTimestamp().c_str() ));
    return result;
}
#endif
#if(0)
	else if(dataType=="I603S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
	else if(dataType=="I604S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
#endif
#if(1)
int InternetElwChannelProcessor::handleKOSPIIssueEventInformation(const ACE_CString &packet)
{
    if ( EXTURE_GROUP_C_KOSPI_ISSUE_EVENT_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleKOSPIIssueEventInformation] Skip : %s, %d : EXTURE_GROUP_C_KOSPI_ISSUE_EVENT_INFORMATION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_GROUP_C_KOSPI_ISSUE_EVENT_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExtureGroupCKOSPIIssueEventInformation rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString eventTypeCode(rawRec.eventTypeCode, sizeof ( rawRec.eventTypeCode ));
    ACE_CString eventOccurrenceCauseCode(rawRec.eventOccurrenceCauseCode, sizeof ( rawRec.eventOccurrenceCauseCode ));
    ACE_CString startDate(rawRec.startDate, sizeof ( rawRec.startDate ));
    ACE_CString expirationDate(rawRec.expirationDate, sizeof ( rawRec.expirationDate ));

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleKOSPIIssueEventInformation] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        return 0;
    }

    KOSPI_KOSDAQ_IssueEventInformation infoRec;
    ::memset(&infoRec, 0, sizeof(KOSPI_KOSDAQ_IssueEventInformation));

    ::memcpy(&infoRec.symbol, issueCode.c_str(), issueCode.length());
    infoRec.registerDt = (int) ( ::time(0) );
    ::memcpy(&infoRec.eventTypeCode, eventTypeCode.c_str(), eventTypeCode.length());
    ::memcpy(&infoRec.eventOccurrenceCauseCode, eventOccurrenceCauseCode.c_str(), eventOccurrenceCauseCode.length());
    ::memcpy(&infoRec.startDate, startDate.c_str(), startDate.length());
    ::memcpy(&infoRec.expirationDate, expirationDate.c_str(), expirationDate.length());

    printPacketKOSPI_KOSDAQ_IssueEventInformation(infoRec);

    char buf[KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE];
    ::memset(&buf, 0, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);
    ::memcpy(&buf, &infoRec, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);

    int result = sendPacket(ACE_CString(buf, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE), PACKET_KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION, EXCHANGE_KSE);
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleKOSPIIssueEventInformation] issueCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , result ));
    return result;
}
#endif

#if(0)
else if ( dataType == "B703S" ) handleQuote10(packet);
else if ( dataType == "B704S" ) handleQuote10(packet);
#endif
#if(0)
else if ( dataType == "B203S" ) handleElwRecoveryTotalTrade(packet);
else if ( dataType == "B204S" ) handleElwRecoveryTotalTrade(packet);
#endif

#if(1)
int InternetElwChannelProcessor::handleRecoveryTotalTrade(const ACE_CString &packet)
{
    if ( EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] Skip : %s,%d : EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }
	int other_else=0;

    ACE_CString frameId(packet.substr(0, 2));
	ACE_CString dataType(packet.substr(0, 5));

    // log frame count status
    LogFrameCount(frameId);

   	ExtureGroupCRecoveryTotalTrade totalrawRec;
	ACE_OS::memcpy(&totalrawRec, packet.c_str(), packet.length());

    ExtureGroupCRecoveryTrade rawRec;
	::memset(&rawRec, 0x30, sizeof(rawRec));

	memcpy(rawRec.stockCode,totalrawRec.stockCode,sizeof(rawRec.stockCode));
	memcpy(rawRec.boardID,totalrawRec.boardID,sizeof(rawRec.boardID));
	memcpy(rawRec.upDown,totalrawRec.upDown,sizeof(rawRec.upDown));
	memcpy(rawRec.gap,totalrawRec.gap,sizeof(rawRec.gap));
	memcpy(rawRec.closePrice,totalrawRec.closePrice,sizeof(rawRec.closePrice));
	memcpy(rawRec.openPrice,totalrawRec.openPrice,sizeof(rawRec.openPrice));
	memcpy(rawRec.highPrice,totalrawRec.highPrice,sizeof(rawRec.highPrice));
	memcpy(rawRec.lowPrice,totalrawRec.lowPrice,sizeof(rawRec.lowPrice));
	memcpy(rawRec.realRateQuotationClass,totalrawRec.realRateQuotationClass,sizeof(rawRec.realRateQuotationClass));

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] stockCode:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.stockCode),rawRec.stockCode ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] boardID  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.boardID),rawRec.boardID ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] upDown   :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.upDown),rawRec.upDown ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] gap      :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.gap),rawRec.gap ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] closePrice:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.closePrice),rawRec.closePrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] openPrice :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.openPrice),rawRec.openPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] highPrice :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.highPrice),rawRec.highPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] lowPrice  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.lowPrice),rawRec.lowPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] realRateQuotationClass:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(rawRec.realRateQuotationClass),rawRec.realRateQuotationClass ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] accmTradeVolume       :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(totalrawRec.accmTradeVolume),totalrawRec.accmTradeVolume ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] accmTradeAmount       :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(totalrawRec.accmTradeAmount),totalrawRec.accmTradeAmount ));

	ACE_CString boardID(totalrawRec.boardID, sizeof(totalrawRec.boardID ));
    ACE_CString sessionID(totalrawRec.sessionID, sizeof ( totalrawRec.sessionID ));

	ACE_CString stockCode(rawRec.stockCode, sizeof rawRec.stockCode);
    ACE_CString isNormalstockCode(rawRec.stockCode, ( sizeof rawRec.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

	/*
	G2	장개시전종가
	*/
	if(boardID == "G2")
	{
		memcpy(rawRec.beforeMarketOverTimeClosePriceTradeVolume,totalrawRec.accmTradeVolume,sizeof(rawRec.beforeMarketOverTimeClosePriceTradeVolume));
		memcpy(rawRec.beforeMarketOverTimeClosePriceTradeAmount,totalrawRec.accmTradeAmount,sizeof(rawRec.beforeMarketOverTimeClosePriceTradeAmount));

		other_else=100;
	}
	/*
	G1	정규장
	*/
	if(boardID == "G1")
	{
		memcpy(rawRec.regularMarketTradeVolume,totalrawRec.accmTradeVolume,sizeof(rawRec.regularMarketTradeVolume));
		memcpy(rawRec.regularMarketTradeAmount,totalrawRec.accmTradeAmount,sizeof(rawRec.regularMarketTradeAmount));

		other_else=100;
	}
	/*
	G3	장종료후종가
	*/
	if(boardID == "G3")
	{
		memcpy(rawRec.afterMarketOvertimeClosePriceTradeVolume,totalrawRec.accmTradeVolume,sizeof(rawRec.afterMarketOvertimeClosePriceTradeVolume));
		memcpy(rawRec.afterMarketOvertimeClosePriceTradeAmount,totalrawRec.accmTradeAmount,sizeof(rawRec.afterMarketOvertimeClosePriceTradeAmount));

		other_else=100;
	}

	//G7	일반Buy-In	20	단일가	일반 Buy-In 체결수량       
	//G7	일반Buy-In	20	단일가	일반 Buy-In 거래대금       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 체결수량       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 거래대금  

	if(boardID == "G7")
	{
		memcpy(rawRec.regularBuyInTradingVolume,totalrawRec.accmTradeVolume,sizeof(rawRec.regularBuyInTradingVolume));
		memcpy(rawRec.regularBuyInTradingValue,totalrawRec.accmTradeAmount,sizeof(rawRec.regularBuyInTradingValue));

		other_else=100;
	}
	if(boardID == "G8")
	{
		memcpy(rawRec.sameDayBuyInTradingVolume,totalrawRec.accmTradeVolume,sizeof(rawRec.sameDayBuyInTradingVolume));
		memcpy(rawRec.sameDayBuyInTradingValue,totalrawRec.accmTradeAmount,sizeof(rawRec.sameDayBuyInTradingValue));

		other_else=100;
	}

    //G4 시간외단일가누적 체결수량/시간외단일가누적 거래대금(DANIL)
	if(boardID=="G4")
	{
		memcpy(rawRec.overTimeMarketFixedAccmVolume,totalrawRec.accmTradeVolume,sizeof(rawRec.overTimeMarketFixedAccmVolume));
		memcpy(rawRec.overTimeMarketFixedAccmAmount,totalrawRec.accmTradeVolume,sizeof(rawRec.overTimeMarketFixedAccmAmount));

		other_else=100;
	}

	//7.B2	장개시전대량 manyBulkTradeVolume/manyBulkTradeAmount/
    //7.K2	장개시전대량바스켓
    //7.I2	장개시전경쟁대량
    //7.B1	장중대량
    //7.K1	장중대량바스켓
    //7.I1	장중경쟁대량
    //7.B3	장종료후대량
    //7.K3	장종료후대량바스켓
	if(other_else==0)
	{
		memcpy(rawRec.manyBulkTradeVolume,totalrawRec.accmTradeVolume,sizeof(rawRec.manyBulkTradeVolume));
		memcpy(rawRec.manyBulkTradeAmount,totalrawRec.accmTradeVolume,sizeof(rawRec.manyBulkTradeAmount));

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] stockCode:[%s],boardID:[%s],sessionID:[%s],manyBulkTradeVolume:[%.*s],manyBulkTradeAmount:[%.*s]\n" ,getCurrentTimestamp().c_str() , stockCode.c_str() , boardID.c_str(), sessionID.c_str(), sizeof(rawRec.manyBulkTradeVolume), rawRec.manyBulkTradeVolume, sizeof(rawRec.manyBulkTradeAmount), rawRec.manyBulkTradeAmount));
	}

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));

    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(rawRec.upDown, sizeof rawRec.upDown);
	ACE_CString boardEventID(rawRec.boardEventID, sizeof ( rawRec.boardEventID ));

    trade.market = getMarketInRecoveryTrade(boardID, boardEventID);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(rawRec.openPrice, sizeof rawRec.openPrice).c_str());
    trade.high = atoi(ACE_CString(rawRec.highPrice, sizeof rawRec.highPrice).c_str());
    trade.low = atoi(ACE_CString(rawRec.lowPrice, sizeof rawRec.lowPrice).c_str());
    trade.close = atoi(ACE_CString(rawRec.closePrice, sizeof rawRec.closePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(rawRec.gap, sizeof rawRec.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    /*
     * 버그 존재함
     * 정규장때 재기동을 한 경우 장개시전시간외 종가와 장개시후시간외 종가는 당일 거래량으로 포함되어야 하는데,
     * B2 의 누적거래량은 바이인을 제외한 전체 거래량을 담으므로, B2 처리시 전체 거래량은 맞게 되지만,
     * 다음 A3 전문 도착시에는 해당 보드 ID 만이 더해지고, 다른 보드 ID 값은 0 이므로, 거래량이 일부 빠지는 상황이 발생할 수 있다.
     *
     * ==> 로직변경
     * B2 수신시
     * 정규장 거래량을 G1 으로 해서 강제로 업데이트 한다.
     * 장개시전 시간외 거래량을 G2 로 해서 강제로 업데이트하고
     * 장개시후 시간외 거래량을 G3 로 해서 강제로 업데이트해야한다.
     */

    /*
     * 아래 값들을 강제로 세팅해야 한다.
     */

    const ACE_CString BOARD_ID_MARKET_IN("G1");
    const ACE_CString BOARD_ID_MARKET_BEFORE_TRADE("G2");
    const ACE_CString BOARD_ID_MARKET_AFTER_TRADE("G3");
	const ACE_CString BOARD_ID_MARKET_DANIL_TRADE("G4");
	const ACE_CString BOARD_ID_MARKET_REGULARBUYIN_TRADE("G7");
	const ACE_CString BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE("G8");
	const ACE_CString BOARD_ID_BULK_TRADE_TODAY("ZZ");


	double beforeMarketOverTimeClosePriceTradeVolume = ::atof(ACE_CString(rawRec.beforeMarketOverTimeClosePriceTradeVolume, sizeof ( rawRec.beforeMarketOverTimeClosePriceTradeVolume )).c_str());
    double beforeMarketOverTimeClosePriceTradeAmount = ::atof(ACE_CString(rawRec.beforeMarketOverTimeClosePriceTradeAmount, sizeof ( rawRec.beforeMarketOverTimeClosePriceTradeAmount )).c_str());

    if(beforeMarketOverTimeClosePriceTradeVolume == 0) beforeMarketOverTimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);
    if(beforeMarketOverTimeClosePriceTradeAmount == 0) beforeMarketOverTimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);

    double regularMarketTradeVolume = ::atof(ACE_CString(rawRec.regularMarketTradeVolume, sizeof ( rawRec.regularMarketTradeVolume )).c_str());
    double regularMarketTradeAmount = ::atof(ACE_CString(rawRec.regularMarketTradeAmount, sizeof ( rawRec.regularMarketTradeAmount )).c_str());

    if(regularMarketTradeVolume == 0) regularMarketTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_IN);
    if(regularMarketTradeAmount == 0) regularMarketTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_IN);

    double afterMarketOvertimeClosePriceTradeVolume = ::atof(ACE_CString(rawRec.afterMarketOvertimeClosePriceTradeVolume, sizeof ( rawRec.afterMarketOvertimeClosePriceTradeVolume )).c_str());
    double afterMarketOvertimeClosePriceTradeAmount = ::atof(ACE_CString(rawRec.afterMarketOvertimeClosePriceTradeAmount, sizeof ( rawRec.afterMarketOvertimeClosePriceTradeAmount )).c_str());

    if(afterMarketOvertimeClosePriceTradeVolume == 0) afterMarketOvertimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE);
    if(afterMarketOvertimeClosePriceTradeAmount == 0) afterMarketOvertimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE);

	double regularBuyInTradingVolume = ::atof(ACE_CString(rawRec.regularBuyInTradingVolume, sizeof ( rawRec.regularBuyInTradingVolume )).c_str());
	double regularBuyInTradingValue = ::atof(ACE_CString(rawRec.regularBuyInTradingValue, sizeof ( rawRec.regularBuyInTradingValue )).c_str());

	if(regularBuyInTradingVolume == 0) regularBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    if(regularBuyInTradingValue == 0) regularBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);

	double sameDayBuyInTradingVolume = ::atof(ACE_CString(rawRec.sameDayBuyInTradingVolume, sizeof ( rawRec.sameDayBuyInTradingVolume )).c_str());
	double sameDayBuyInTradingValue = ::atof(ACE_CString(rawRec.sameDayBuyInTradingValue, sizeof ( rawRec.sameDayBuyInTradingValue )).c_str());

	if(sameDayBuyInTradingVolume == 0) sameDayBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    if(sameDayBuyInTradingValue == 0) sameDayBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);

	double overTimeMarketFixedAccmVolume = ::atof(ACE_CString(rawRec.overTimeMarketFixedAccmAmount, sizeof ( rawRec.overTimeMarketFixedAccmAmount )).c_str());
	double overTimeMarketFixedAccmAmount = ::atof(ACE_CString(rawRec.overTimeMarketFixedAccmAmount, sizeof ( rawRec.overTimeMarketFixedAccmAmount )).c_str());

	if(overTimeMarketFixedAccmVolume == 0) overTimeMarketFixedAccmVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE);
    if(overTimeMarketFixedAccmAmount == 0) overTimeMarketFixedAccmAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE);

	double manyBulkTradeVolume = ::atof(ACE_CString(rawRec.manyBulkTradeVolume, sizeof ( rawRec.manyBulkTradeVolume )).c_str());
	double manyBulkTradeAmount = ::atof(ACE_CString(rawRec.manyBulkTradeAmount, sizeof ( rawRec.manyBulkTradeAmount )).c_str());

	if(manyBulkTradeVolume == 0) manyBulkTradeVolume = getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY);
    if(manyBulkTradeAmount == 0) manyBulkTradeAmount = getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY);


	//1.장개시전시간외종가 체결수량 : beforeMarketOverTimeClosePriceTradeVolume
    //2.정규장체결수량              : regularMarketTradeVolume
    //3.장종료후시간외종가 체결수량 : afterMarketOvertimeClosePriceTradeVolume
    //4.일반 Buy-in 체결수량        : regularBuyInTradingVolume
    //5.당일 Buy-in 체결수량        : sameDayBuyInTradingVolume
    //6.시간외단일가누적 체결수량   : overTimeMarketFixedAccmVolume
	//7.대량 체결수량               : manyBulkTradeVolume
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] 1.(G2)장개시전시간외종가 체결수량:[%f]\n" ,getCurrentTimestamp().c_str() , beforeMarketOverTimeClosePriceTradeVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] 2.(G1)정규장체결수량             :[%f]\n" ,getCurrentTimestamp().c_str() , regularMarketTradeVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] 3.(G3)장종료후시간외종가 체결수량:[%f]\n" ,getCurrentTimestamp().c_str() , afterMarketOvertimeClosePriceTradeVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] 4.(G7)일반 Buy-in 체결수량       :[%f]\n" ,getCurrentTimestamp().c_str() , regularBuyInTradingVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] 5.(G8)당일 Buy-in 체결수량       :[%f]\n" ,getCurrentTimestamp().c_str() , sameDayBuyInTradingVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] 6.(G4)시간외단일가누적 체결수량  :[%f]\n" ,getCurrentTimestamp().c_str() , overTimeMarketFixedAccmVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] 7.(B2)(K2)(I2)(B1)(K1)(I1)(B3)(K3)대량 체결수량:[%f]\n" ,getCurrentTimestamp().c_str() , manyBulkTradeVolume));

    // 장개시전 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, beforeMarketOverTimeClosePriceTradeVolume, BOARD_ID_MARKET_BEFORE_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, beforeMarketOverTimeClosePriceTradeAmount, BOARD_ID_MARKET_BEFORE_TRADE);
    }

    // 정규장 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeVolume )
    {
        setAccmVolume(stockCode, regularMarketTradeVolume, BOARD_ID_MARKET_IN);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeAmount )
    {
        setAccmAmount(stockCode, regularMarketTradeAmount, BOARD_ID_MARKET_IN);
    }

    // 장마감후 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, afterMarketOvertimeClosePriceTradeVolume, BOARD_ID_MARKET_AFTER_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, afterMarketOvertimeClosePriceTradeAmount, BOARD_ID_MARKET_AFTER_TRADE);
    }

	// 일반 Buy-In
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE) < regularBuyInTradingVolume )
    {
        setAccmVolume(stockCode, regularBuyInTradingVolume, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE) < regularBuyInTradingValue )
    {
        setAccmAmount(stockCode, regularBuyInTradingValue, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    }

	// 당일 Buy-In
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE) < sameDayBuyInTradingVolume )
    {
        setAccmVolume(stockCode, sameDayBuyInTradingVolume, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE) < sameDayBuyInTradingValue )
    {
        setAccmAmount(stockCode, sameDayBuyInTradingValue, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    }

	// DANIL
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE) < overTimeMarketFixedAccmVolume )
    {
        setAccmVolume(stockCode, overTimeMarketFixedAccmVolume, BOARD_ID_MARKET_DANIL_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE) < overTimeMarketFixedAccmAmount )
    {
        setAccmAmount(stockCode, overTimeMarketFixedAccmAmount, BOARD_ID_MARKET_DANIL_TRADE);
    }

	// MANY
	if ( getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY) < manyBulkTradeVolume )
    {
        setAccmVolume(stockCode, manyBulkTradeVolume, BOARD_ID_BULK_TRADE_TODAY);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY) < manyBulkTradeAmount )
    {
        setAccmAmount(stockCode, manyBulkTradeAmount, BOARD_ID_BULK_TRADE_TODAY);
    }

	//1.장개시전시간외종가 체결수량 : beforeMarketOverTimeClosePriceTradeVolume
    //2.정규장체결수량              : regularMarketTradeVolume
    //3.장종료후시간외종가 체결수량 : afterMarketOvertimeClosePriceTradeVolume
    //4.일반 Buy-in 체결수량        : regularBuyInTradingVolume
    //5.당일 Buy-in 체결수량        : sameDayBuyInTradingVolume
    //6.시간외단일가누적 체결수량   : overTimeMarketFixedAccmVolume
	//7.대량 체결수량               : manyBulkTradeVolume

    //1.장개시전시간외종가 거래대금 : beforeMarketOverTimeClosePriceTradeAmount
    //2.정규장거래대금              : regularMarketTradeAmount
    //3.장종료후시간외종가 거래대금 : afterMarketOvertimeClosePriceTradeAmount
    //4.일반 Buy-in 거래대금        : regularBuyInTradingValue
    //5.당일 Buy-in 거래대금        : sameDayBuyInTradingValue
    //6.시간외단일가누적 거래대금   : overTimeMarketFixedAccmAmount
	//7.대량 거래대금               : manyBulkTradeAmount

    //-------------------------------------------------------------
    //7.B2	장개시전대량
    //7.K2	장개시전대량바스켓
    //7.I2	장개시전경쟁대량
    //7.B1	장중대량
    //7.K1	장중대량바스켓
    //7.I1	장중경쟁대량
    //7.B3	장종료후대량
    //7.K3	장종료후대량바스켓
	//--------------------------------------------------------------

    double accmVolume = 0;
    double accmAmount = 0;

	accmVolume = accmVolume + beforeMarketOverTimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularMarketTradeVolume;
	accmVolume = accmVolume + afterMarketOvertimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularBuyInTradingVolume;
	accmVolume = accmVolume + sameDayBuyInTradingVolume;
	accmVolume = accmVolume + overTimeMarketFixedAccmVolume;
	accmVolume = accmVolume + manyBulkTradeVolume;

	accmAmount = accmAmount + beforeMarketOverTimeClosePriceTradeAmount;
	accmAmount = accmAmount + regularMarketTradeAmount;
	accmAmount = accmAmount + regularBuyInTradingValue;
	accmAmount = accmAmount + sameDayBuyInTradingValue;
	accmAmount = accmAmount + overTimeMarketFixedAccmAmount;
	accmAmount = accmAmount + manyBulkTradeAmount;

	double gettotalaccmvolume = getTotalAccmVolume(stockCode);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] Check>> accmVolume:[%f],getTotalAccmVolume():[%f]\n" ,getCurrentTimestamp().c_str() , accmVolume, gettotalaccmvolume));

    //if ( accmVolume < getTotalAccmVolume(stockCode) )
	if ( accmVolume < gettotalaccmvolume )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] Skip : %s,%d : net volume error stockCode:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , accmVolume , getTotalAccmVolume(stockCode) ), -1);
    }

    if ( accmVolume > 0 )
    {
        setTotalAccmVolume(stockCode, accmVolume);
    }
    trade.accmVolume = getTotalAccmVolume(stockCode);

    if ( accmAmount > 0 )
    {
        setTotalAccmAmount(stockCode, accmAmount);
    }
    trade.amount = getTotalAccmAmount(stockCode);

    ACE_CString quotation(rawRec.realRateQuotationClass, sizeof rawRec.realRateQuotationClass);

    if ( quotation == "2" )
    {
        trade.subtype = TRADESUBTYPE_QUOTATION;
    }
    else
    {
        trade.subtype = TRADESUBTYPE_RECOVERY;
    }

    trade.tradeVolume = 0;

    if ( hasValue == -1 )
    {
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = time(0);
        ACE_OS::memcpy(&trade.symbol, &rawRec.stockCode, sizeof rawRec.stockCode);

        trade.openMin = 0;
        trade.highMin = 0;
        trade.lowMin = 0;
        trade.volumeMin = 0;
    }

    trade.market = getMarketBasedCurrentTime();

    ACE_CString oldKey;
    Trade oldVal;
    tradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());

#if(1)
printPacketTrade(trade);
#endif

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] stockCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , result ));

    return result;
}
#endif

#if(1)
int InternetElwChannelProcessor::handleQuote10(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_ELW_QUOTE10_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleQuote10] Skip : %s, %d : EXTURE_PLUS_ELW_QUOTE10_SIZE[%d] != packet.length()[%d] packet:[%s] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_QUOTE10_SIZE , packet.length() , packet.c_str() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwQuote10 rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString stockCode(rawRec.stockCode, sizeof rawRec.stockCode);
    ACE_CString isNormalstockCode(rawRec.stockCode, ( sizeof rawRec.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    ACE_CString boardID(rawRec.boardID, sizeof rawRec.boardID);
    ACE_CString sessionID(rawRec.sessionID, sizeof rawRec.sessionID);

    /*
     * 정규시간외구분코드가 7(일반바이인), 8(당일바이인) 인 경우 skip 한다.
     * 코드값모음집(20131010)
     * ==> 일반 바이인(G7)
     * ==> 당일 바이인(G8)
     */

    if ( ( boardID == "G7" ) || ( boardID == "G8" ) )
    {
        return 0;
    }
    // 바이인 세션 ID ==> 25
    if ( sessionID == "25" )
    {
        return 0;
    }

#if(0)
    // 세션ID / 70:시간외단일가
    // 보드ID / 장종료후시간외단일가(G4)
    if ( ( sessionID == "70" ) || ( boardID == "G4" ) )
    {
        return handleQuote10Fixed(packet);
    }
#endif
#if(0)
    // 보드ID / 장종료후시간외단일가(G4)
    if ( ( boardID == "G4" ) )
    {
        return handleQuote10Fixed(packet);
    }
#endif

    Quote10 quote;
    quote.exchange = EXCHANGE_KSE;
    quote.symbolType = SYMBOL_STOCK;
    quote.decimalPoint = 0;

    ACE_OS::memcpy(&quote.symbol, stockCode.c_str(), sizeof quote.symbol);

    quote.concurrent = getConcurrent(boardID, sessionID);

    // 구스펙 장종료후시간외 값을 처리하기 위해 getMarketInQuote10 함수 매개변수 갯수 변경.
    quote.market = getMarketInQuote10(boardID, sessionID);

    quote.quoteTime = time(0);

    quote.totalAskVolume = atof(ACE_CString(rawRec.totalAskQuoteRemainder, sizeof rawRec.totalAskQuoteRemainder).c_str());
    quote.totalBidVolume = atof(ACE_CString(rawRec.totalBidQuoteRemainder, sizeof rawRec.totalBidQuoteRemainder).c_str());

    quote.expectedPrice = atoi(ACE_CString(rawRec.estimatedTradePrice, sizeof rawRec.estimatedTradePrice).c_str());
    quote.expectedVolume = atof(ACE_CString(rawRec.estimatedTradeVolume, sizeof rawRec.estimatedTradeVolume).c_str());

    for ( int i = 0 ; i < 10 ; ++i )
    {
        quote.rec[i].ask = atoi(ACE_CString(rawRec.rec[i].askQuote, sizeof rawRec.rec[i].askQuote).c_str());
        quote.rec[i].askVolume = atoi(ACE_CString(rawRec.rec[i].askQuoteVolume, sizeof rawRec.rec[i].askQuoteVolume).c_str());
        quote.rec[i].bid = atoi(ACE_CString(rawRec.rec[i].bidQuote, sizeof rawRec.rec[i].bidQuote).c_str());
        quote.rec[i].bidVolume = atoi(ACE_CString(rawRec.rec[i].bidQuoteVolume, sizeof rawRec.rec[i].bidQuoteVolume).c_str());
    }

    sendQuote10(quote);
    return 0;
}
#endif

#if(1)
time_t InternetElwChannelProcessor::getModTime(time_t tradeTime)
{
    return tradeTime;
}
#endif

#if(1)
BYTE InternetElwChannelProcessor::getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = CONCURRENT_OFF;
    if ( boardID == "G1" ) //정규시간외구분코드가 1인경우(동시,접속 둘다 가능) 1 정규장 G1  유가/코스닥/파생/코넥스   개별경쟁거래
    {
        if ( sessionID == "10" ) //시가단일가는 ~09:00 까지. (10:시가단일가)
        {
            result = CONCURRENT_ON;
        }
        else if ( ( sessionID == "40" ) || ( sessionID == "11" ) ) //시가단일가연장은 9시 이후까지 진행가능하므로.
        {
            result = CONCURRENT_OFF;
        }
        else //그 외의 경우 접속으로 가정
        {
            result = CONCURRENT_OFF;
        }
    }
    else
    {
        result = CONCURRENT_OFF;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = MARKET_IN;
    // marketStatusClassCode 60: 장종료시간외접수
    /*
     * 60:장종료후시간외접수
     65:장종료후시간외
     */
    if ( ( boardID == "G3" ) || ( sessionID == "65" ) || ( sessionID == "60" ) )
    {
        result = MARKET_AFTER_TRADE;
    }
    else
    {
        result = MARKET_IN;
    }
    return ( result );
}

int InternetElwChannelProcessor::getTickTime(const ACE_CString &timeStr, const ACE_CString &frameId)
{
    int hour = 0;
    int minute = 0;
    int second = 0;

    if ( timeStr.substr(3, 3) == "JJJ" )
    {
        // 장전 예상지수인 경우 09:00 을 끝으로 한다. by dong in 2008.02.01
        if ( frameId == "D1" )
        {
            hour = 9;
        }
        else
        {
            hour = 18;
        }
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
    int tickTime = dayBaseTime + hour * 3600 + minute * 60 + second;
    return ( tickTime );
}

BYTE InternetElwChannelProcessor::getMarketInTrade(const ACE_CString& raw)
{
    BYTE result = MARKET_IN;
    if ( raw == "G2" )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( raw == "G3" )
    {
        result = MARKET_AFTER_TRADE;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getUpDownInTrade(const ACE_CString& raw)
{
    BYTE result = UPDOWN_STATIONARY;
    if ( raw == "1" )
    {
        result = UPDOWN_UP_LIMIT;
    }
    else if ( raw == "2" )
    {
        result = UPDOWN_UP;
    }
    else if ( raw == "4" )
    {
        result = UPDOWN_DOWN_LIMIT;
    }
    else if ( raw == "5" )
    {
        result = UPDOWN_DOWN;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID)
{
    BYTE result = MARKET_IN;

    if ( boardID == "G2" )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( boardID == "G3" )
    {
        result = MARKET_AFTER_TRADE;
    }
    else if ( boardID == "G4" )
    {
        result = MARKET_END;
    }
    else
    {
        result = MARKET_IN;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getExchange(char rawSymbolType)
{
    return ( rawSymbolType == 'Q' ? EXCHANGE_KOSDAQ : EXCHANGE_KSE );
}

BYTE InternetElwChannelProcessor::getExhaustInForeigner(const ACE_CString& raw)
{
    BYTE result = static_cast<BYTE>(atoi(raw.c_str()));
    return ( result );
}
#endif

#if(1)
	ACE_CString indexConstEtnMap1[599] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","KGD04P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","K2D01T","K2D02T","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGG03P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","CGD01P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","K2G07N","K2G07T","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG02P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","GGS01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","110043","110046","110043","110004","110007","110012","110014","110020","110021","110023","110037","110038","110039","110040","110041","110042","110044","110045","110049","110051","110052","110053","110056","110057","110058","110059","110060","110061","110062","110065","110066","110067","110068","110069","110070","110071","110072","110073","110074","110077","110078","110079","110080","110081","110082","110083","110084","110086","110087","110088","110089","110090","110091","110092","110093","110094","110095","110096","110097","110098","110099","110100","110101","110102","110103","110104","110105","110106","110107","110108","110109","110110","110111","110112","2P8802","2P8803","2P9259","2P9269","2P9258","2P9284","2P9206","2P9271","2P9234","2P9272","2P9263","2P9256","2P9239","2P9246","2P9247","2P9248","2P9260","2P9255","2P9265","2P9267","2P9266","2P9276","2P9277","2P9278","2P9279","2P9280","2P9281","2P9282","2P9283","2P9231","2P9235","2P9240","2P9275","2P9211","2P9242","2P9243","2P9274","2P9245","2P9262","2P9236","2P9251","2P9238","2P9264","2P9268","2P9229","2P9252","2P9233","2P9253","2P9221","2P9244","2P9222","2P9257","2P9241","2P9273","2P9207","2P9250","2P9237","2P9249","2P9210","2P9232","2P9254","2PB003","2PB101","2PB201","2PB211","2PB221","2PB226","2PB231","2PB232","2PB237","2PB238","2PB239","2PB241","2PB242","2PB243","2PB305","2PB306","2PB307","2PC007","2PC006","2PM128","2PM126","2PM127","2PM119","2PM121","2PM102","2PM104","2PM107","2PM109","2PM112","2PM114","2PM115","2PM116","2PM117","2PM118","2PM122","2PM123","2PM131","2PM124","2PM132","2PM125","2PM120","2PM129","2PM130","2PM134","2PM133","2PM001","2PR001","2PR101","120001","120002","120003","120004","120005","2PW006","120007","120008","120009","120010","120011","120012","120013","120014","120015","120016","120017","120018","120019","120020","120021","120901"};
	ACE_CString indexConstEtnMap2[599] = 
	{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","187","188","165","132","133","134","142","136","141","411","412","413","414","415","351","352","353","354","355","356","357","358","105","600","167","203","212","213","214","215","216","217","218","331","204","175","176","169","174","301","302","303","304","801","802","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","004","013","707","731","708","821","312","313","009","010","005","006","007","008","717","003","709","011","012","304","306","307","308","305","822","732","051","052","100","101","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","050","053","054","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","055","056","057","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","601","602","601","004","007","012","014","020","021","023","037","038","039","040","041","042","044","045","049","051","052","053","056","057","058","059","060","061","062","065","066","067","068","069","070","071","072","073","074","077","078","079","080","081","082","083","084","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","802","803","259","269","258","284","206","271","234","272","263","256","239","246","247","248","260","255","265","267","266","276","277","278","279","280","281","282","283","231","235","240","275","211","242","243","274","245","262","236","251","238","264","268","229","252","233","253","221","244","222","257","241","273","207","250","237","249","210","232","254","003","101","201","211","221","226","231","232","237","238","239","241","242","243","305","306","307","007","006","128","126","127","119","121","102","104","107","109","112","114","115","116","117","118","122","123","131","124","132","125","120","129","130","134","133","001","001","101","001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","901"};
	ACE_CString indexConstEtnMap3[599] = 
	{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","5","5","5","5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","6","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","1","2","2","2","2","2","2","2","2","2","2","1","1","1","1","B","B","B","B","C","C","C","1","1","1","1","1","1","D","D","D","D","D","D","D","D","D","G","G","D","D","1","1","C","C","C","C","C","C","C","C","C","C","C","C","2","2","1","1","1","1","1","1","1","3","D","D","2","2","2","2","2","1","D","D","D","D","B","B","1","1","1","1","C","C","E","E","1","1","1","D","D","D","E","E","E","E","E","E","D","G","1","E","E","3","3","3","3","3","D","1","E","E","E","E","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","D","E","E","E","1","2","3","2","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","E","E","E","D","D","B","B","3","3","3","3","D","D","D","D","D","C","E","E","G","3","3","D","D","3","3","1","1","1","1","2","2","3","3","3","3","3","3","3","3","3","3","3","3","1","1","3","3","3","3","2","2","2","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","C","C","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","R","R","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"};
#endif

#if(1)
ACE_CString InternetElwChannelProcessor::getSymbolUpCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<599; kk++)
	{
		if(raw == indexConstEtnMap1[kk])
		{
			ii=kk;
			ff=100;
			break;
		}
	}

	if(ff==0)
	{
		std::ostringstream os;
		os << "000";
		return os.str().c_str();
	}
	else
	{
		return(indexConstEtnMap2[ii]);
	}
}

ACE_CString InternetElwChannelProcessor::getSymbolMarketTypeCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<599; kk++)
	{
		if(raw == indexConstEtnMap1[kk])
		{
			ii=kk;
			ff=100;
			break;
		}
	}

	if(ff==0)
	{
		std::ostringstream os;
		os << "0";
		return os.str().c_str();
	}
	else
	{
		return(indexConstEtnMap3[ii]);
	}
}
#endif


























#if(0)
/*CHANGE-------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------*/
#endif

#if(0)
/*CHANGE-------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------*/
#endif

#if(0)
/*CHANGE-------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------*/
#endif





























































#if(0)
#if(0)
int InternetElwChannelProcessor::processPacket(const ACE_CString &packet)
{
    ACE_CString dataType(packet.substr(0, 5));

#if(1)
	if (dataType == "A104S" ) //(증권C) STK : A104S
    {
        handleETNInformationBatch(packet);
    }
	else if ( dataType == "X304S" ) //(증권C) STK : X304S
    {
        handleETNEarlyRedemptionCriteria(packet);
    }
	else if(dataType=="X804S")//(증권C) STK : X804S
	{
		handleETNProfitStructureDetails(packet);
	}
	else if(dataType=="V600S")//(증권C) STK : V600S
	{
		handleETP_Constituents(packet);
	}
#endif
#if(1)
	else if ( dataType == "A003S" ) //(증권C) STK : A002S, A003S, A004S
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.processPacket_KRX_A002S(packet);
    }
	else if ( dataType == "A004S" ) //(증권C) STK : A002S, A003S, A004S
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.processPacket_KRX_A002S(packet);
    }
#endif
#if(1)
#if(1)
	else if(dataType=="A703S")
	{
		handleMarketOperationTS(packet);
	}
	else if(dataType=="A704S")
	{
		handleMarketOperationTS(packet);
	}
#endif
#if(1)
	else if(dataType=="A303S")
	{
		handleTrade(packet);
	}
	else if(dataType=="A304S")
	{
		handleTrade(packet);
	}
#endif
#if(1)
	else if(dataType=="B903S")
    {
        handleSecuritiesTrade(packet);
    }
	else if(dataType=="B904S")
    {
        handleSecuritiesTrade(packet);
    }
#endif
#if(1)
	else if(dataType=="M403S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
	else if(dataType=="M404S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
#endif
#if(1)
	else if(dataType=="I603S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
	else if(dataType=="I604S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
#endif
#if(1)
	else if ( dataType == "B703S" ) //(증권C) STK : B702S, B703S, B704S
    {
        handleQuote10(packet);
    }
	else if ( dataType == "B704S" ) //(증권C) STK : B702S, B703S, B704S
    {
        handleQuote10(packet);
    }
#endif
#if(1)
	else if ( dataType == "B203S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleElwRecoveryTotalTrade(packet);
    }
	else if ( dataType == "B204S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleElwRecoveryTotalTrade(packet);
    }
#endif
#endif
#if(0)
	if ( dataType == "A104S" ) //(증권C) STK : A104S
    {
        handleETNInformationBatch(packet);
    }
#endif
#if(0)
	else if ( dataType == "A102S" ) //(증권C) STK : A102S-ELW
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.processPacket_KRX_A102S(packet);
    }
	else if ( dataType == "A002S" ) //(증권C) STK : A002S, A003S, A004S-ELW
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.processPacket_KRX_A002S(packet);
    }
	else if ( dataType == "A702S" ) //(증권C) STK : A702S, A703S, A704S-ELW
    {
        processPacket_KRX_A702S(packet);
    }
	else if ( dataType == "B702S" ) //(증권C) STK : B702S, B703S, B704S-ELW
    {
        processPacket_KRX_B702S(packet);
    }
	else if ( dataType == "M602S" ) //(증권C) STK : M602S-ELW
    {
        processPacket_KRX_M602S(packet);
    }
	else if ( dataType == "B202S" ) //(증권C) STK : B202S, B203S, B204S-ELW
    {
        handleRecoveryTotalTrade(packet);
    }
	else if ( dataType == "I702S" ) //(증권C) STK : I702S, I703S, I704S-ELW
    {
        processPacket_KRX_I702S(packet);
    }
	else if ( dataType == "A302S" ) //(증권C) STK : A302S, A303S, A304S-ELW
    {
        processPacket_KRX_A302S(packet);
    }
	else if ( dataType == "B902S" ) //(증권C) STK : B902S, B903S, B904S-ELW
    {
        processPacket_KRX_B902S(packet);
    }
	else if ( dataType == "M402S" ) //(증권C) STK : M402S, M403S, M404S-ELW
    {
        processPacket_KRX_M402S(packet);
    }
	else if ( dataType == "I602S" ) //(증권C) STK : I602S, I603S, I604S-ELW
    {
        processPacket_KRX_I602S(packet);
    }
#endif
#if(0)
	else if ( dataType == "A003S" ) //(증권C) STK : A002S, A003S, A004S
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.processPacket_KRX_A002S(packet);
    }
	else if ( dataType == "A004S" ) //(증권C) STK : A002S, A003S, A004S
    {
        MasterElwProcessor masterProc(getSerial());
        masterProc.processPacket_KRX_A002S(packet);
    }
	else if ( dataType == "A703S" ) //(증권C) STK : A702S, A703S, A704S
    {
        processPacket_KRX_A702S(packet);
    }
	else if ( dataType == "A704S" ) //(증권C) STK : A702S, A703S, A704S
    {
        processPacket_KRX_A702S(packet);
    }
	else if ( dataType == "B703S" ) //(증권C) STK : B702S, B703S, B704S
    {
        processPacket_KRX_B702S(packet);
    }
	else if ( dataType == "B704S" ) //(증권C) STK : B702S, B703S, B704S
    {
        processPacket_KRX_B702S(packet);
    }
	else if ( dataType == "B203S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleRecoveryTotalTrade(packet);
    }
	else if ( dataType == "B204S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleRecoveryTotalTrade(packet);
    }
	else if ( dataType == "I703S" ) //(증권C) STK : I702S, I703S, I704S
    {
        processPacket_KRX_I702S(packet);
    }
	else if ( dataType == "I704S" ) //(증권C) STK : I702S, I703S, I704S
    {
        processPacket_KRX_I702S(packet);
    }
	else if ( dataType == "X304S" ) //(증권C) STK : X304S
    {
        handleETNEarlyRedemptionCriteria(packet);
    }
	else if ( dataType == "A303S" ) //(증권C) STK : A302S, A303S, A304S
    {
        processPacket_KRX_A302S(packet);
    }
	else if ( dataType == "A304S" ) //(증권C) STK : A302S, A303S, A304S
    {
        processPacket_KRX_A302S(packet);
    }
	else if ( dataType == "B903S" ) //(증권C) STK : B902S, B903S, B904S
    {
        processPacket_KRX_B902S(packet);
    }
	else if ( dataType == "B904S" ) //(증권C) STK : B902S, B903S, B904S
    {
        processPacket_KRX_B902S(packet);
    }
	else if ( dataType == "M403S" ) //(증권C) STK : M402S, M403S, M404S
    {
        processPacket_KRX_M402S(packet);
    }
	else if ( dataType == "M404S" ) //(증권C) STK : M402S, M403S, M404S
    {
        processPacket_KRX_M402S(packet);
    }
	else if ( dataType == "I603S" ) //(증권C) STK : I602S, I603S, I604S
    {
        processPacket_KRX_I602S(packet);
    }
	else if ( dataType == "I604S" ) //(증권C) STK : I602S, I603S, I604S
    {
        processPacket_KRX_I602S(packet);
    }
	else if(dataType=="X804S")//(증권C) STK : X804S
	{
		handleETNProfitStructureDetails(packet);
	}
	else if(dataType=="V600S")//(증권C) STK : V600S
	{
		handleETP_Constituents(packet);
	}
#if(0)
//코스콤 정보	외국인 투자정보	코스피 외국인 종목별투자정보(확정치)	F101S
//코스콤 정보	외국인 투자정보	코스닥 외국인 종목별투자정보(확정치)	F101Q
//코스콤 정보	외국인 투자정보	코스피 외국인 확정치데이터재전송	F401S
//코스콤 정보	외국인 투자정보	코스닥 외국인 확정치데이터재전송	F401Q
#endif
	else if(dataType=="F101S")
	{
		processPacket_KOSCOM_F1011(packet);
	}
	else if(dataType=="F101Q")
	{
		processPacket_KOSCOM_F1011(packet);
	}
	else if(dataType=="F401S")
	{
		processPacket_KOSCOM_F4011(packet);
	}
	else if(dataType=="F401Q")
	{
		processPacket_KOSCOM_F4011(packet);
	}
#endif
	else
	{
		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket] skip...... dataType:[%s]\tpacket:[%s]\tlength:[%d]\n" , getCurrentTimestamp().c_str() , dataType.c_str() , packet.c_str() , packet.length() ));
    }
    return ( 0 );
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETP_Constituents(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSPI_ETP_TOTAL_CONSTITUENTS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] Skip : %s, %d : EXTURE_PLUS_KOSPI_ETP_CONSTITUENTS_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSPI_ETP_CONSTITUENTS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwKOSPI_ETP_ToTalConstituents totalrawRec;
    ACE_OS::memcpy(&totalrawRec, packet.c_str(), packet.length());

    ExturePlusElwKOSPI_ETP_Constituents rawRec;

    ::memcpy(rawRec.index_calculation_institution_code, totalrawRec.index_calculation_institution_code, sizeof(rawRec.index_calculation_institution_code));
    ::memcpy(rawRec.index_market_classification_id, totalrawRec.index_market_classification_id, sizeof(rawRec.index_market_classification_id));
    ::memcpy(rawRec.index_seq_number, totalrawRec.index_seq_number, sizeof(rawRec.index_seq_number));
    ::memcpy(rawRec.index_leverage_inverse_type_code, totalrawRec.index_leverage_inverse_type_code, sizeof(rawRec.index_leverage_inverse_type_code));
    ::memcpy(rawRec.index_name, totalrawRec.index_name, sizeof(rawRec.index_name));
    ::memcpy(rawRec.index_name_english, totalrawRec.index_name_english, sizeof(rawRec.index_name_english));
    ::memcpy(rawRec.index_asset_classification_id_1, totalrawRec.index_asset_classification_id_1, sizeof(rawRec.index_asset_classification_id_1));
    ::memcpy(rawRec.index_asset_classification_id_2, totalrawRec.index_asset_classification_id_2, sizeof(rawRec.index_asset_classification_id_2));

    ACE_CString data_category(rawRec.data_category, sizeof ( rawRec.data_category ));
    ACE_CString index_calculation_institution_code(rawRec.index_calculation_institution_code, sizeof ( rawRec.index_calculation_institution_code ));
    ACE_CString index_market_classification_id(rawRec.index_market_classification_id, sizeof ( rawRec.index_market_classification_id ));
    ACE_CString index_seq_number(rawRec.index_seq_number, sizeof ( rawRec.index_seq_number ));
    ACE_CString index_leverage_inverse_type_code(rawRec.index_leverage_inverse_type_code, sizeof ( rawRec.index_leverage_inverse_type_code ));
    ACE_CString index_name(rawRec.index_name, sizeof ( rawRec.index_name ));
    ACE_CString index_name_english(rawRec.index_name_english, sizeof ( rawRec.index_name_english ));
    ACE_CString index_asset_classification_id_1(rawRec.index_asset_classification_id_1, sizeof ( rawRec.index_asset_classification_id_1 ));
    ACE_CString index_asset_classification_id_2(rawRec.index_asset_classification_id_2, sizeof ( rawRec.index_asset_classification_id_2 ));
#if(0)
    ACE_CString index_associated_market_type_code(rawRec.index_associated_market_type_code, sizeof ( rawRec.index_associated_market_type_code ));
    ACE_CString industry_index_code(rawRec.industry_index_code, sizeof ( rawRec.industry_index_code ));
#endif
#if(1)
    ACE_CString jisuid(totalrawRec.jisuID, sizeof ( totalrawRec.jisuID ));
    ACE_CString index_associated_market_type_code = getSymbolMarketTypeCode(jisuid);
    if(index_associated_market_type_code == "0") index_associated_market_type_code = " ";
    ACE_CString industry_index_code = getSymbolUpCode(jisuid);
    if(industry_index_code == "000") industry_index_code = "   ";
#endif

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_calculation_institution_code:[%s]\n" , getCurrentTimestamp().c_str() , index_calculation_institution_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_market_classification_id:[%s]\n" , getCurrentTimestamp().c_str() , index_market_classification_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_seq_number:[%s]\n" , getCurrentTimestamp().c_str() , index_seq_number.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_leverage_inverse_type_code:[%s]\n" , getCurrentTimestamp().c_str() , index_leverage_inverse_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_name:[%s]\n" , getCurrentTimestamp().c_str() , index_name.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_name_english:[%s]\n" , getCurrentTimestamp().c_str() , index_name_english.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_asset_classification_id_1:[%s]\n" , getCurrentTimestamp().c_str() , index_asset_classification_id_1.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_asset_classification_id_2:[%s]\n" , getCurrentTimestamp().c_str() , index_asset_classification_id_2.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] index_associated_market_type_code:[%s]\n" , getCurrentTimestamp().c_str() , index_associated_market_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETP_Constituents] industry_index_code:[%s]\n" , getCurrentTimestamp().c_str() , industry_index_code.c_str() ));

    int result = 0;
    return ( result );
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETNProfitStructureDetails(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] Skip : %s, %d : EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwETNProfitStructureDetails rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString data_category(rawRec.data_category, sizeof ( rawRec.data_category ));
    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString etn_profit_structure_details(rawRec.etn_profit_structure_details, sizeof ( rawRec.etn_profit_structure_details ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] etn_profit_structure_details:[%s]\n" , getCurrentTimestamp().c_str() , etn_profit_structure_details.c_str() ));

    if ( issue_code == "999999999999" )
    {
        ACE_DEBUG( ( LM_INFO , "[%s] [InternetElwChannelProcessor::handleETNProfitStructureDetails] - Skip dummy data(%s)\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
        return ( 0 );
    }

    int result = 0;
    return ( result );
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] Skip : %s, %d : EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwETNEarlyRedemptionCriteria rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString data_category(rawRec.data_category, sizeof ( rawRec.data_category ));
    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString etn_early_redemption_period_code(rawRec.etn_early_redemption_period_code, sizeof ( rawRec.etn_early_redemption_period_code ));
    ACE_CString early_redemption_appraisal_date(rawRec.early_redemption_appraisal_date, sizeof ( rawRec.early_redemption_appraisal_date ));
    ACE_CString early_redemption_criteria_relation_code(rawRec.early_redemption_criteria_relation_code, sizeof ( rawRec.early_redemption_criteria_relation_code ));
    ACE_CString early_redemption_base_index_1(rawRec.early_redemption_base_index_1, sizeof ( rawRec.early_redemption_base_index_1 ));
    ACE_CString early_redemption_base_index_2(rawRec.early_redemption_base_index_2, sizeof ( rawRec.early_redemption_base_index_2 ));
    ACE_CString early_redemption_price_before_expenses(rawRec.early_redemption_price_before_expenses, sizeof ( rawRec.early_redemption_price_before_expenses ));
    ACE_CString early_redemption_payment_date(rawRec.early_redemption_payment_date, sizeof ( rawRec.early_redemption_payment_date ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] etn_early_redemption_period_code:[%s]\n" , getCurrentTimestamp().c_str() , etn_early_redemption_period_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_appraisal_date:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_appraisal_date.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_criteria_relation_code:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_criteria_relation_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_base_index_1:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_base_index_1.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_base_index_2:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_base_index_2.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_price_before_expenses:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_price_before_expenses.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] early_redemption_payment_date:[%s]\n" , getCurrentTimestamp().c_str() , early_redemption_payment_date.c_str() ));

    if ( issue_code == "999999999999" )
    {
        ACE_DEBUG( ( LM_INFO , "[%s] [InternetElwChannelProcessor::handleETNEarlyRedemptionCriteria] - Skip dummy data(%s)\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
        return ( 0 );
    }

    int result = 0;
    return ( result );
}
#endif

#if(0)
int InternetElwChannelProcessor::handleRecoveryTotalTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_ELW_RECOVERY_TOTAL_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleRecoveryTrade] Skip : %s,%d : EXTURE_PLUS_ELW_RECOVERY_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_RECOVERY_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }
	int other_else=0;

    ACE_CString frameId(packet.substr(0, 2));

    // log frame count status
    LogFrameCount(frameId);

   	ExturePlusElwRecoveryTotalTrade totalrawPacket;
	ACE_OS::memcpy(&totalrawPacket, packet.c_str(), packet.length());

    ExturePlusElwRecoveryTrade rawPacket;
	::memset(&rawPacket, 0x30, sizeof(rawPacket));

	memcpy(rawPacket.stockCode,totalrawPacket.stockCode,sizeof(rawPacket.stockCode));
	memcpy(rawPacket.boardID,totalrawPacket.boardID,sizeof(rawPacket.boardID));
	memcpy(rawPacket.upDown,totalrawPacket.upDown,sizeof(rawPacket.upDown));
	memcpy(rawPacket.gap,totalrawPacket.gap,sizeof(rawPacket.gap));
	memcpy(rawPacket.closePrice,totalrawPacket.closePrice,sizeof(rawPacket.closePrice));
	memcpy(rawPacket.openPrice,totalrawPacket.openPrice,sizeof(rawPacket.openPrice));
	memcpy(rawPacket.highPrice,totalrawPacket.highPrice,sizeof(rawPacket.highPrice));
	memcpy(rawPacket.lowPrice,totalrawPacket.lowPrice,sizeof(rawPacket.lowPrice));
	memcpy(rawPacket.realRateQuotationClass,totalrawPacket.realRateQuotationClass,sizeof(rawPacket.realRateQuotationClass));

	ACE_CString boardID(totalrawPacket.boardID, sizeof(totalrawPacket.boardID ));
    ACE_CString sessionID(totalrawPacket.sessionID, sizeof ( totalrawPacket.sessionID ));

	ACE_CString stockCode(rawPacket.stockCode, sizeof rawPacket.stockCode);
    ACE_CString isNormalstockCode(rawPacket.stockCode, ( sizeof rawPacket.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

	/*
	G2	장개시전종가	40
	G2	장개시전종가	40
	*/
	if(boardID == "G2")
	{
		memcpy(rawPacket.beforeMarketOverTimeClosePriceTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.beforeMarketOverTimeClosePriceTradeVolume));
		memcpy(rawPacket.beforeMarketOverTimeClosePriceTradeAmount,totalrawPacket.accmTradeAmount,sizeof(rawPacket.beforeMarketOverTimeClosePriceTradeAmount));

		other_else=100;
	}
	/*
	G1	정규장	10
	G1	정규장	52
	G1	정규장	11
	G1	정규장	53
	G1	정규장	20
	G1	정규장	21
	G1	정규장	30
	G1	정규장	54
	G1	정규장	40
	G1	정규장	50
	G1	정규장	51
	G1	정규장	80
	*/
	if(boardID == "G1")
	{
		memcpy(rawPacket.regularMarketTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.regularMarketTradeVolume));
		memcpy(rawPacket.regularMarketTradeAmount,totalrawPacket.accmTradeAmount,sizeof(rawPacket.regularMarketTradeAmount));

		other_else=100;
	}
	/*
	G3	장종료후종가	60
	G3	장종료후종가	40
	*/
	if(boardID == "G3")
	{
		memcpy(rawPacket.afterMarketOvertimeClosePriceTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.afterMarketOvertimeClosePriceTradeVolume));
		memcpy(rawPacket.afterMarketOvertimeClosePriceTradeAmount,totalrawPacket.accmTradeAmount,sizeof(rawPacket.afterMarketOvertimeClosePriceTradeAmount));

		other_else=100;
	}

	//G7	일반Buy-In	20	단일가	일반 Buy-In 체결수량       
	//G7	일반Buy-In	20	단일가	일반 Buy-In 거래대금       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 체결수량       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 거래대금  

	if(boardID == "G7")
	{
		memcpy(rawPacket.regularBuyInTradingVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.regularBuyInTradingVolume));
		memcpy(rawPacket.regularBuyInTradingValue,totalrawPacket.accmTradeAmount,sizeof(rawPacket.regularBuyInTradingValue));

		other_else=100;
	}
	if(boardID == "G8")
	{
		memcpy(rawPacket.sameDayBuyInTradingVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.sameDayBuyInTradingVolume));
		memcpy(rawPacket.sameDayBuyInTradingValue,totalrawPacket.accmTradeAmount,sizeof(rawPacket.sameDayBuyInTradingValue));

		other_else=100;
	}

    //G4 시간외단일가누적 체결수량/시간외단일가누적 거래대금
	if(boardID=="G4")
	{
		memcpy(rawPacket.overTimeMarketFixedAccmVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.overTimeMarketFixedAccmVolume));
		memcpy(rawPacket.overTimeMarketFixedAccmAmount,totalrawPacket.accmTradeVolume,sizeof(rawPacket.overTimeMarketFixedAccmAmount));

		other_else=100;
	}

	//7.B2	장개시전대량 manyBulkTradeVolume/manyBulkTradeAmount/
    //7.K2	장개시전대량바스켓
    //7.I2	장개시전경쟁대량
    //7.B1	장중대량
    //7.K1	장중대량바스켓
    //7.I1	장중경쟁대량
    //7.B3	장종료후대량
    //7.K3	장종료후대량바스켓
	if(other_else==0)
	{
		memcpy(rawPacket.manyBulkTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.manyBulkTradeVolume));
		memcpy(rawPacket.manyBulkTradeAmount,totalrawPacket.accmTradeVolume,sizeof(rawPacket.manyBulkTradeAmount));

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] stockCode:[%s],boardID:[%s],sessionID:[%s],manyBulkTradeVolume:[%.*s],manyBulkTradeAmount:[%.*s]\n" ,getCurrentTimestamp().c_str() , stockCode.c_str() , boardID.c_str(), sessionID.c_str(), sizeof(rawPacket.manyBulkTradeVolume), rawPacket.manyBulkTradeVolume, sizeof(rawPacket.manyBulkTradeAmount), rawPacket.manyBulkTradeAmount));
	}

    ELWTrade trade;
    ::memset(&trade, 0, sizeof(ELWTrade));

    TickFilter filter;

    int hasValue = elwTradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(rawPacket.upDown, sizeof rawPacket.upDown);
	ACE_CString boardEventID(rawPacket.boardEventID, sizeof ( rawPacket.boardEventID ));

    trade.market = getMarketInRecoveryTrade(boardID, boardEventID);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(rawPacket.openPrice, sizeof rawPacket.openPrice).c_str());
    trade.high = atoi(ACE_CString(rawPacket.highPrice, sizeof rawPacket.highPrice).c_str());
    trade.low = atoi(ACE_CString(rawPacket.lowPrice, sizeof rawPacket.lowPrice).c_str());
    trade.close = atoi(ACE_CString(rawPacket.closePrice, sizeof rawPacket.closePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(rawPacket.gap, sizeof rawPacket.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    /*
     * 버그 존재함
     * 정규장때 재기동을 한 경우 장개시전시간외 종가와 장개시후시간외 종가는 당일 거래량으로 포함되어야 하는데,
     * B2 의 누적거래량은 바이인을 제외한 전체 거래량을 담으므로, B2 처리시 전체 거래량은 맞게 되지만,
     * 다음 A3 전문 도착시에는 해당 보드 ID 만이 더해지고, 다른 보드 ID 값은 0 이므로, 거래량이 일부 빠지는 상황이 발생할 수 있다.
     *
     * ==> 로직변경
     * B2 수신시
     * 정규장 거래량을 G1 으로 해서 강제로 업데이트 한다.
     * 장개시전 시간외 거래량을 G2 로 해서 강제로 업데이트하고
     * 장개시후 시간외 거래량을 G3 로 해서 강제로 업데이트해야한다.
     */

    /*
     * 아래 값들을 강제로 세팅해야 한다.
     */

    const ACE_CString BOARD_ID_MARKET_IN("G1");
    const ACE_CString BOARD_ID_MARKET_BEFORE_TRADE("G2");
    const ACE_CString BOARD_ID_MARKET_AFTER_TRADE("G3");
	const ACE_CString BOARD_ID_MARKET_DANIL_TRADE("G4");
	const ACE_CString BOARD_ID_MARKET_REGULARBUYIN_TRADE("G7");
	const ACE_CString BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE("G8");
	const ACE_CString BOARD_ID_BULK_TRADE_TODAY("ZZ");


	double beforeMarketOverTimeClosePriceTradeVolume = ::atof(ACE_CString(rawPacket.beforeMarketOverTimeClosePriceTradeVolume, sizeof ( rawPacket.beforeMarketOverTimeClosePriceTradeVolume )).c_str());
    double beforeMarketOverTimeClosePriceTradeAmount = ::atof(ACE_CString(rawPacket.beforeMarketOverTimeClosePriceTradeAmount, sizeof ( rawPacket.beforeMarketOverTimeClosePriceTradeAmount )).c_str());

    if(beforeMarketOverTimeClosePriceTradeVolume == 0) beforeMarketOverTimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);
    if(beforeMarketOverTimeClosePriceTradeAmount == 0) beforeMarketOverTimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);

    double regularMarketTradeVolume = ::atof(ACE_CString(rawPacket.regularMarketTradeVolume, sizeof ( rawPacket.regularMarketTradeVolume )).c_str());
    double regularMarketTradeAmount = ::atof(ACE_CString(rawPacket.regularMarketTradeAmount, sizeof ( rawPacket.regularMarketTradeAmount )).c_str());

    if(regularMarketTradeVolume == 0) regularMarketTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_IN);
    if(regularMarketTradeAmount == 0) regularMarketTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_IN);

    double afterMarketOvertimeClosePriceTradeVolume = ::atof(ACE_CString(rawPacket.afterMarketOvertimeClosePriceTradeVolume, sizeof ( rawPacket.afterMarketOvertimeClosePriceTradeVolume )).c_str());
    double afterMarketOvertimeClosePriceTradeAmount = ::atof(ACE_CString(rawPacket.afterMarketOvertimeClosePriceTradeAmount, sizeof ( rawPacket.afterMarketOvertimeClosePriceTradeAmount )).c_str());

    if(afterMarketOvertimeClosePriceTradeVolume == 0) afterMarketOvertimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE);
    if(afterMarketOvertimeClosePriceTradeAmount == 0) afterMarketOvertimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE);

	double regularBuyInTradingVolume = ::atof(ACE_CString(rawPacket.regularBuyInTradingVolume, sizeof ( rawPacket.regularBuyInTradingVolume )).c_str());
	double regularBuyInTradingValue = ::atof(ACE_CString(rawPacket.regularBuyInTradingValue, sizeof ( rawPacket.regularBuyInTradingValue )).c_str());

	if(regularBuyInTradingVolume == 0) regularBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    if(regularBuyInTradingValue == 0) regularBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);

	double sameDayBuyInTradingVolume = ::atof(ACE_CString(rawPacket.sameDayBuyInTradingVolume, sizeof ( rawPacket.sameDayBuyInTradingVolume )).c_str());
	double sameDayBuyInTradingValue = ::atof(ACE_CString(rawPacket.sameDayBuyInTradingValue, sizeof ( rawPacket.sameDayBuyInTradingValue )).c_str());

	if(sameDayBuyInTradingVolume == 0) sameDayBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    if(sameDayBuyInTradingValue == 0) sameDayBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);

	double overTimeMarketFixedAccmVolume = ::atof(ACE_CString(rawPacket.overTimeMarketFixedAccmAmount, sizeof ( rawPacket.overTimeMarketFixedAccmAmount )).c_str());
	double overTimeMarketFixedAccmAmount = ::atof(ACE_CString(rawPacket.overTimeMarketFixedAccmAmount, sizeof ( rawPacket.overTimeMarketFixedAccmAmount )).c_str());

	if(overTimeMarketFixedAccmVolume == 0) overTimeMarketFixedAccmVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE);
    if(overTimeMarketFixedAccmAmount == 0) overTimeMarketFixedAccmAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE);

	double manyBulkTradeVolume = ::atof(ACE_CString(rawPacket.manyBulkTradeVolume, sizeof ( rawPacket.manyBulkTradeVolume )).c_str());
	double manyBulkTradeAmount = ::atof(ACE_CString(rawPacket.manyBulkTradeAmount, sizeof ( rawPacket.manyBulkTradeAmount )).c_str());

	if(manyBulkTradeVolume == 0) manyBulkTradeVolume = getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY);
    if(manyBulkTradeAmount == 0) manyBulkTradeAmount = getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY);

    // 장개시전 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, beforeMarketOverTimeClosePriceTradeVolume, BOARD_ID_MARKET_BEFORE_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, beforeMarketOverTimeClosePriceTradeAmount, BOARD_ID_MARKET_BEFORE_TRADE);
    }

    // 정규장 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeVolume )
    {
        setAccmVolume(stockCode, regularMarketTradeVolume, BOARD_ID_MARKET_IN);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeAmount )
    {
        setAccmAmount(stockCode, regularMarketTradeAmount, BOARD_ID_MARKET_IN);
    }

    // 장마감후 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, afterMarketOvertimeClosePriceTradeVolume, BOARD_ID_MARKET_AFTER_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, afterMarketOvertimeClosePriceTradeAmount, BOARD_ID_MARKET_AFTER_TRADE);
    }

	// 일반 Buy-In
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE) < regularBuyInTradingVolume )
    {
        setAccmVolume(stockCode, regularBuyInTradingVolume, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE) < regularBuyInTradingValue )
    {
        setAccmAmount(stockCode, regularBuyInTradingValue, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    }

	// 당일 Buy-In
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE) < sameDayBuyInTradingVolume )
    {
        setAccmVolume(stockCode, sameDayBuyInTradingVolume, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE) < sameDayBuyInTradingValue )
    {
        setAccmAmount(stockCode, sameDayBuyInTradingValue, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    }

	// DANIL
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE) < overTimeMarketFixedAccmVolume )
    {
        setAccmVolume(stockCode, overTimeMarketFixedAccmVolume, BOARD_ID_MARKET_DANIL_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE) < overTimeMarketFixedAccmAmount )
    {
        setAccmAmount(stockCode, overTimeMarketFixedAccmAmount, BOARD_ID_MARKET_DANIL_TRADE);
    }

	// MANY
	if ( getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY) < manyBulkTradeVolume )
    {
        setAccmVolume(stockCode, manyBulkTradeVolume, BOARD_ID_BULK_TRADE_TODAY);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY) < manyBulkTradeAmount )
    {
        setAccmAmount(stockCode, manyBulkTradeAmount, BOARD_ID_BULK_TRADE_TODAY);
    }

	//1.장개시전시간외종가 체결수량 : beforeMarketOverTimeClosePriceTradeVolume
    //2.정규장체결수량              : regularMarketTradeVolume
    //3.장종료후시간외종가 체결수량 : afterMarketOvertimeClosePriceTradeVolume
    //4.일반 Buy-in 체결수량        : regularBuyInTradingVolume
    //5.당일 Buy-in 체결수량        : sameDayBuyInTradingVolume
    //6.시간외단일가누적 체결수량   : overTimeMarketFixedAccmVolume
	//7.대량 체결수량               : manyBulkTradeVolume

    //1.장개시전시간외종가 거래대금 : beforeMarketOverTimeClosePriceTradeAmount
    //2.정규장거래대금              : regularMarketTradeAmount
    //3.장종료후시간외종가 거래대금 : afterMarketOvertimeClosePriceTradeAmount
    //4.일반 Buy-in 거래대금        : regularBuyInTradingValue
    //5.당일 Buy-in 거래대금        : sameDayBuyInTradingValue
    //6.시간외단일가누적 거래대금   : overTimeMarketFixedAccmAmount
	//7.대량 거래대금               : manyBulkTradeAmount

    //-------------------------------------------------------------
    //7.B2	장개시전대량
    //7.K2	장개시전대량바스켓
    //7.I2	장개시전경쟁대량
    //7.B1	장중대량
    //7.K1	장중대량바스켓
    //7.I1	장중경쟁대량
    //7.B3	장종료후대량
    //7.K3	장종료후대량바스켓
	//--------------------------------------------------------------

    double accmVolume = 0;
    double accmAmount = 0;

	accmVolume = accmVolume + beforeMarketOverTimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularMarketTradeVolume;
	accmVolume = accmVolume + afterMarketOvertimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularBuyInTradingVolume;
	accmVolume = accmVolume + sameDayBuyInTradingVolume;
	accmVolume = accmVolume + overTimeMarketFixedAccmVolume;
	accmVolume = accmVolume + manyBulkTradeVolume;

	accmAmount = accmAmount + beforeMarketOverTimeClosePriceTradeAmount;
	accmAmount = accmAmount + regularMarketTradeAmount;
	accmAmount = accmAmount + regularBuyInTradingValue;
	accmAmount = accmAmount + sameDayBuyInTradingValue;
	accmAmount = accmAmount + overTimeMarketFixedAccmAmount;
	accmAmount = accmAmount + manyBulkTradeAmount;

    if ( accmVolume < getTotalAccmVolume(stockCode) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleRecoveryTrade] Skip : %s,%d : net volume error stockCode:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , accmVolume , getTotalAccmVolume(stockCode) ), -1);
    }

    if ( accmVolume > 0 )
    {
        setTotalAccmVolume(stockCode, accmVolume);
    }
    trade.accmVolume = getTotalAccmVolume(stockCode);

    if ( accmAmount > 0 )
    {
        setTotalAccmAmount(stockCode, accmAmount);
    }
    trade.amount = getTotalAccmAmount(stockCode);

    ACE_CString quotation(rawPacket.realRateQuotationClass, sizeof rawPacket.realRateQuotationClass);

    if ( quotation == "2" )
    {
        trade.subtype = TRADESUBTYPE_QUOTATION;
    }
    else
    {
        trade.subtype = TRADESUBTYPE_RECOVERY;
    }

    trade.tradeVolume = 0;

    if ( hasValue == -1 )
    {
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = time(0);
        ACE_OS::memcpy(&trade.symbol, &rawPacket.stockCode, sizeof rawPacket.stockCode);

        trade.openMin = 0;
        trade.highMin = 0;
        trade.lowMin = 0;
        trade.volumeMin = 0;
    }

    trade.market = getMarketBasedCurrentTime();

    ACE_CString oldKey;
    ELWTrade oldVal;
	::memset(&oldVal, 0x00, sizeof(ELWTrade));
    elwTradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());

    char bufferForPacket[ELW_TRADE_SIZE];
    ::memset(&bufferForPacket, 0, sizeof ( bufferForPacket ));
    ::memcpy(&bufferForPacket, &trade, ELW_TRADE_SIZE);
    int result = sendPacket(ACE_CString(bufferForPacket, ELW_TRADE_SIZE), PACKET_ELW_TRADE, EXCHANGE_KSE);
    return ( result );

    return result;
}
#endif

#if(1)
int InternetElwChannelProcessor::handleETNInformationBatch(const ACE_CString &packet)
{
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket],packet:[%d]\tlength:[%d]\n" , getCurrentTimestamp().c_str() , EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE , packet.length() ));

    if ( EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] Skip : %s, %d : EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE , packet.length() , packet.c_str() ), -1);
    }

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket],packet:[%d]\tlength:[%d]\n" , getCurrentTimestamp().c_str() , EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE , packet.length() ));

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwETNInformationBatch rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString dataSeqNumber(rawRec.dataSeqNumber, sizeof ( rawRec.dataSeqNumber ));
    ACE_CString etnIssueMarketParticipantKoreanName(rawRec.etnIssueMarketParticipantKoreanName, sizeof ( rawRec.etnIssueMarketParticipantKoreanName ));
    ACE_CString etnIssueMarketParticipantEnglishName(rawRec.etnIssueMarketParticipantEnglishName, sizeof ( rawRec.etnIssueMarketParticipantEnglishName ));
    ACE_CString etnIssueMarketParticipantNo(rawRec.etnIssueMarketParticipantNo, sizeof ( rawRec.etnIssueMarketParticipantNo ));
    ACE_CString etnFinalSettlementMethodCode(rawRec.etnFinalSettlementMethodCode, sizeof ( rawRec.etnFinalSettlementMethodCode ));
    ACE_CString etnLastTradingDate(rawRec.etnLastTradingDate, sizeof ( rawRec.etnLastTradingDate ));
    ACE_CString etnPaymentDate(rawRec.etnPaymentDate, sizeof ( rawRec.etnPaymentDate ));
    ACE_CString etnLPHoldingQuantity(rawRec.etnLPHoldingQuantity, sizeof ( rawRec.etnLPHoldingQuantity ));

    ACE_CString lossProtectionEtnProfitStructureCode(rawRec.lossProtectionEtnProfitStructureCode, sizeof ( rawRec.lossProtectionEtnProfitStructureCode ));
    ACE_CString etnMaximumRedemptionPrice(rawRec.etnMaximumRedemptionPrice, sizeof ( rawRec.etnMaximumRedemptionPrice ));
    ACE_CString etnMinimumRedemptionPrice(rawRec.etnMinimumRedemptionPrice, sizeof ( rawRec.etnMinimumRedemptionPrice ));
    ACE_CString etnEarlyRedemptionPossibility(rawRec.etnEarlyRedemptionPossibility, sizeof ( rawRec.etnEarlyRedemptionPossibility ));
    ACE_CString etnEarlyRedemptionPeriodCode(rawRec.etnEarlyRedemptionPeriodCode, sizeof ( rawRec.etnEarlyRedemptionPeriodCode ));
    ACE_CString appraisedPriceCalculationInstitutionCode1(rawRec.appraisedPriceCalculationInstitutionCode1, sizeof ( rawRec.appraisedPriceCalculationInstitutionCode1 ));
    ACE_CString appraisedPriceCalculationInstitutionCode2(rawRec.appraisedPriceCalculationInstitutionCode2, sizeof ( rawRec.appraisedPriceCalculationInstitutionCode2 ));

    /*
     * 2017.03.22
     * 현재 ETNInformationBatch 를 사용하는 곳이 없다.
     * 모의투자에서도 미사용중
     * 시세DB 적재도 하지 않음
     */

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        return 0;
    }

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] dataSeqNumber:[%s]\n" , getCurrentTimestamp().c_str() , dataSeqNumber.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnIssueMarketParticipantKoreanName:[%s]\n" , getCurrentTimestamp().c_str() , etnIssueMarketParticipantKoreanName.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnIssueMarketParticipantEnglishName:[%s]\n" , getCurrentTimestamp().c_str() , etnIssueMarketParticipantEnglishName.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnIssueMarketParticipantNo:[%s]\n" , getCurrentTimestamp().c_str() , etnIssueMarketParticipantNo.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnFinalSettlementMethodCode:[%s]\n" , getCurrentTimestamp().c_str() , etnFinalSettlementMethodCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnLastTradingDate:[%s]\n" , getCurrentTimestamp().c_str() , etnLastTradingDate.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnPaymentDate:[%s]\n" , getCurrentTimestamp().c_str() , etnPaymentDate.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnLPHoldingQuantity:[%s]\n" , getCurrentTimestamp().c_str() , etnLPHoldingQuantity.c_str() ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] lossProtectionEtnProfitStructureCode:[%s]\n" , getCurrentTimestamp().c_str() , lossProtectionEtnProfitStructureCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnMaximumRedemptionPrice:[%s]\n" , getCurrentTimestamp().c_str() , etnMaximumRedemptionPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnMinimumRedemptionPrice:[%s]\n" , getCurrentTimestamp().c_str() , etnMinimumRedemptionPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnEarlyRedemptionPossibility:[%s]\n" , getCurrentTimestamp().c_str() , etnEarlyRedemptionPossibility.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] etnEarlyRedemptionPeriodCode:[%s]\n" , getCurrentTimestamp().c_str() , etnEarlyRedemptionPeriodCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] appraisedPriceCalculationInstitutionCode1:[%s]\n" , getCurrentTimestamp().c_str() , appraisedPriceCalculationInstitutionCode1.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleETNInformationBatch] appraisedPriceCalculationInstitutionCode2:[%s]\n" , getCurrentTimestamp().c_str() , appraisedPriceCalculationInstitutionCode2.c_str() ));

    ETNInformationBatch batch;
    ::memset(&batch, 0, sizeof(ETNInformationBatch));
    ::memcpy(& ( batch.symbol ), issueCode.c_str(), issueCode.length());
    batch.registerDt = (int) ( ::time(0) );
    ::memcpy(& ( batch.etnIssueMarketParticipantKoreanName ), etnIssueMarketParticipantKoreanName.c_str(), etnIssueMarketParticipantKoreanName.length());
    ::memcpy(& ( batch.etnIssueMarketParticipantEnglishName ), etnIssueMarketParticipantEnglishName.c_str(), etnIssueMarketParticipantEnglishName.length());
    ::memcpy(& ( batch.etnIssueMarketParticipantNo ), etnIssueMarketParticipantNo.c_str(), etnIssueMarketParticipantNo.length());
    ::memcpy(& ( batch.etnFinalSettlementMethodCode ), etnFinalSettlementMethodCode.c_str(), etnFinalSettlementMethodCode.length());
    ::memcpy(& ( batch.etnLastTradingDate ), etnLastTradingDate.c_str(), etnLastTradingDate.length());
    ::memcpy(& ( batch.etnPaymentDate ), etnPaymentDate.c_str(), etnPaymentDate.length());
    batch.etnLPHoldingQuantity = ::atof(etnLPHoldingQuantity.c_str());
    ::memcpy(& ( batch.lossProtectionEtnProfitStructureCode ), lossProtectionEtnProfitStructureCode.c_str(), lossProtectionEtnProfitStructureCode.length());
    batch.etnMaximumRedemptionPrice = ::atof(etnMaximumRedemptionPrice.c_str());
    batch.etnMinimumRedemptionPrice = ::atof(etnMinimumRedemptionPrice.c_str());
    ::memcpy(& ( batch.etnEarlyRedemptionPossibility ), etnEarlyRedemptionPossibility.c_str(), etnEarlyRedemptionPossibility.length());
    ::memcpy(& ( batch.etnEarlyRedemptionPeriodCode ), etnEarlyRedemptionPeriodCode.c_str(), etnEarlyRedemptionPeriodCode.length());
    ::memcpy(& ( batch.appraisedPriceCalculationInstitutionCode1 ), appraisedPriceCalculationInstitutionCode1.c_str(), appraisedPriceCalculationInstitutionCode1.length());
    ::memcpy(& ( batch.appraisedPriceCalculationInstitutionCode2 ), appraisedPriceCalculationInstitutionCode2.c_str(), appraisedPriceCalculationInstitutionCode2.length());

    printPacketETNInformationBatch(batch);

    char buf[ETN_INFORMATION_BATCH_SIZE];
    ::memset(&buf, 0, ETN_INFORMATION_BATCH_SIZE);
    ::memcpy(&buf, &batch, ETN_INFORMATION_BATCH_SIZE);
    int resultBatch = sendPacket(ACE_CString(buf, ETN_INFORMATION_BATCH_SIZE), PACKET_ETN_INFORMATION_BATCH, EXCHANGE_KSE);
    return resultBatch;
}
#endif

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_I602S(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_ELW_KOSPI_ISSUE_EVENT_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_I6011] Skip : %s, %d : EXTURE_PLUS_ELW_KOSPI_ISSUE_EVENT_INFORMATION_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_KOSPI_ISSUE_EVENT_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusElwKOSPIIssueEventInformation rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwKOSPIIssueEventInformation));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ACE_CString issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));
    ACE_CString event_type_code(rawPacket.event_type_code, sizeof ( rawPacket.event_type_code ));
    ACE_CString event_occurrence_cause_code(rawPacket.event_occurrence_cause_code, sizeof ( rawPacket.event_occurrence_cause_code ));
    ACE_CString start_date_opening_date_application_date(rawPacket.start_date_opening_date_application_date, sizeof ( rawPacket.start_date_opening_date_application_date ));
    ACE_CString expiration_date_ending_date(rawPacket.expiration_date_ending_date, sizeof ( rawPacket.expiration_date_ending_date ));

    if ( issue_code == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_I6011] issue_code:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
        return ( 0 );
    }

    KOSPI_KOSDAQ_IssueEventInformation infoRec;
    ::memset(&infoRec, 0, sizeof(KOSPI_KOSDAQ_IssueEventInformation));

    ::memcpy(&infoRec.symbol, issue_code.c_str(), issue_code.length());
    infoRec.registerDt = (int) ( ::time(0) );
    ::memcpy(&infoRec.eventTypeCode, event_type_code.c_str(), event_type_code.length());
    ::memcpy(&infoRec.eventOccurrenceCauseCode, event_occurrence_cause_code.c_str(), event_occurrence_cause_code.length());
    ::memcpy(&infoRec.startDate, start_date_opening_date_application_date.c_str(), start_date_opening_date_application_date.length());
    ::memcpy(&infoRec.expirationDate, expiration_date_ending_date.c_str(), expiration_date_ending_date.length());

    printPacketKOSPI_KOSDAQ_IssueEventInformation(infoRec);

    char buf[KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE];
    ::memset(&buf, 0, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);
    ::memcpy(&buf, &infoRec, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);

    int result = sendPacket(ACE_CString(buf, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE), PACKET_KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION, EXCHANGE_KSE);
    return ( result );

}
#endif

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_M602S(const ACE_CString& packet)
{
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_M602S] BEGIN\n" , getCurrentTimestamp().c_str() ));
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_M602S] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    if ( EXTURE_PLUS_ELW_EARLY_CLOSED_ELW_BATCH_DATA_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_M602S] Skip : %s,%d : EXTURE_PLUS_ELW_EARLY_CLOSED_ELW_BATCH_DATA_SIZE:[%d] != packet.length():[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_EARLY_CLOSED_ELW_BATCH_DATA_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwEarlyClosedELWBatchData rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwEarlyClosedELWBatchData));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ACE_CString issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));
    ACE_CString str_base_price_for_occurrence_of_elw_early_closing(rawPacket.base_price_for_occurrence_of_elw_early_closing, sizeof ( rawPacket.base_price_for_occurrence_of_elw_early_closing ));
    double base_price_for_occurrence_of_elw_early_closing = parseDouble(str_base_price_for_occurrence_of_elw_early_closing, 0);

    ACE_CString contents_of_elw_early_closing_right(rawPacket.contents_of_elw_early_closing_right, sizeof ( rawPacket.contents_of_elw_early_closing_right ));
    contents_of_elw_early_closing_right = trim_ACE(contents_of_elw_early_closing_right);

    ACE_CString price_evaluation_method_when_elw_close_early(rawPacket.price_evaluation_method_when_elw_close_early, sizeof ( rawPacket.price_evaluation_method_when_elw_close_early ));
    price_evaluation_method_when_elw_close_early = trim_ACE(price_evaluation_method_when_elw_close_early);

    ELWEarlyClosedELWBatch elwBatch;
    ::memset(&elwBatch, 0, sizeof(ELWEarlyClosedELWBatch));
    elwBatch.exchange = EXCHANGE_KSE;
    elwBatch.symbolType = SYMBOL_ELW;
    elwBatch.recvTime = (int) ( ::time(0) );     // 전문에 별도 시간이 없음
    ::memcpy(& ( elwBatch.symbol ), issue_code.c_str(), issue_code.length());
    elwBatch.base_price_for_occurrence_of_elw_early_closing = base_price_for_occurrence_of_elw_early_closing;
    ::memcpy(& ( elwBatch.contents_of_elw_early_closing_right ), contents_of_elw_early_closing_right.c_str(), contents_of_elw_early_closing_right.length());
    ::memcpy(& ( elwBatch.price_evaluation_method_when_elw_close_early ), price_evaluation_method_when_elw_close_early.c_str(), price_evaluation_method_when_elw_close_early.length());

    printPacketELWEarlyClosedELWBatch(elwBatch);

    char bufferForPacket[ELW_EARLY_CLOSED_ELW_BATCH_SIZE];
    ::memset(&bufferForPacket, 0, sizeof ( bufferForPacket ));
    ::memcpy(&bufferForPacket, &elwBatch, ELW_EARLY_CLOSED_ELW_BATCH_SIZE);

    int result = sendPacket(ACE_CString(bufferForPacket, ELW_EARLY_CLOSED_ELW_BATCH_SIZE), PACKET_ELW_EARLY_CLOSED_ELW_BATCH, EXCHANGE_KSE);
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_M602S] issue_code:[%s]\t\result:[%d]n" , getCurrentTimestamp().c_str() , issue_code.c_str() , result ));

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_M602S] END\n" , getCurrentTimestamp().c_str() ));

    return ( result );
}
#endif

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_M402S(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_ELW_KOSPI_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_M4011] Skip : %s, %d : EXTURE_PLUS_ELW_KOSPI_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_KOSPI_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExturePlusElwKOSPIMarketOperationScheduleDisclosure rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwKOSPIMarketOperationScheduleDisclosure));
    ::memcpy(&rawPacket, packet.c_str(), sizeof(ExturePlusElwKOSPIMarketOperationScheduleDisclosure));

    {
        ACE_CString dataCategory(rawPacket.dataCategory, sizeof ( rawPacket.dataCategory ));
        ACE_CString marketCategory(rawPacket.marketCategory, sizeof ( rawPacket.marketCategory ));
        ACE_CString issueCode(rawPacket.issueCode, sizeof ( rawPacket.issueCode ));
        ACE_CString boardID(rawPacket.boardID, sizeof ( rawPacket.boardID ));
        ACE_CString boardEventID(rawPacket.boardEventID, sizeof ( rawPacket.boardEventID ));
        ACE_CString boardEventBeginTime(rawPacket.boardEventBeginTime, sizeof ( rawPacket.boardEventBeginTime ));
        ACE_CString boardEventApplyCode(rawPacket.boardEventApplyCode, sizeof ( rawPacket.boardEventApplyCode ));
        ACE_CString sessionBeginEndCode(rawPacket.sessionBeginEndCode, sizeof ( rawPacket.sessionBeginEndCode ));
        ACE_CString sessionID(rawPacket.sessionID, sizeof ( rawPacket.sessionID ));
        ACE_CString listedIssueCode(rawPacket.listedIssueCode, sizeof ( rawPacket.listedIssueCode ));
        ACE_CString tradingHaltReasonCode(rawPacket.tradingHaltReasonCode, sizeof ( rawPacket.tradingHaltReasonCode ));
        ACE_CString tradingHaltOccurenceTypeCode(rawPacket.tradingHaltOccurenceTypeCode, sizeof ( rawPacket.tradingHaltOccurenceTypeCode ));
        ACE_CString stepApplied(rawPacket.stepApplied, sizeof ( rawPacket.stepApplied ));
    }

    ELWMarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(ELWMarketOperation));

    std::string issue_code(rawPacket.issueCode, sizeof ( rawPacket.issueCode ));
    issue_code = trim(issue_code);

    if ( issue_code == std::string("") )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_M4011] invalid issue_code:[%s][%d] skip...... packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , issue_code.length() , packet.c_str() , packet.length() ));
        return ( 0 );
    }

    ::memcpy(& ( marketRec.symbol ), issue_code.c_str(), issue_code.length());
    marketRec.recvTime = (int) ( ::time(0) );
    ::memcpy(& ( marketRec.boardID ), & ( rawPacket.boardID ), sizeof ( rawPacket.boardID ));
    ::memcpy(& ( marketRec.boardEventID ), & ( rawPacket.boardEventID ), sizeof ( rawPacket.boardEventID ));
    ::memcpy(& ( marketRec.beginTime ), & ( rawPacket.boardEventBeginTime ), sizeof ( rawPacket.boardEventBeginTime ));
    ::memcpy(& ( marketRec.boardEventGroupCode ), & ( rawPacket.boardEventApplyCode ), sizeof ( rawPacket.boardEventApplyCode ));
    ::memcpy(& ( marketRec.sessionID ), & ( rawPacket.sessionID ), sizeof ( rawPacket.sessionID ));
    ::memcpy(& ( marketRec.tradingHaltReason ), & ( rawPacket.tradingHaltReasonCode ), sizeof ( rawPacket.tradingHaltReasonCode ));

    printPacketELWMarketOperation(marketRec);

    char buf[ELW_MARKET_OPERATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &marketRec, sizeof(ELWMarketOperation));
    int result = sendPacket(ACE_CString(buf, ELW_MARKET_OPERATION_SIZE), PACKET_ELW_MARKET_OPERATION, EXCHANGE_KSE);
    return ( result );
}
#endif

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_A302S(const ACE_CString& packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A3021] BEGIN\n" , getCurrentTimestamp().c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A3021] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    if ( EXTURE_PLUS_ELW_ELW_ORDER_FILLED_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A3021] Skip : %s,%d : EXTURE_PLUS_ELW_ELW_ORDER_FILLED_SIZE:[%d] != packet.length():[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_ELW_ORDER_FILLED_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwELWOrderFilled rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwELWOrderFilled));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ACE_CString issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));

    ACE_CString board_id(rawPacket.board_id, sizeof ( rawPacket.board_id ));
    ACE_CString session_id(rawPacket.session_id, sizeof ( rawPacket.session_id ));

    ELWTrade elwTrade;
    ::memset(&elwTrade, 0, sizeof(ELWTrade));
    TickFilter filter;

    /*
     * 내부포맷 ELWTrade 와 Trade 가 다르므로, TradeMap 을 따로 간다.
     */
    int hasValue = elwTradeMap_->find(issue_code, elwTrade, ALLOCATOR::instance());

    // 정규시간외구분코드 : 장종료후시간외단일가(4) , 체결유형코드 : 시간외단일가(70)
    // 4    장종료후시간외단일가  G4  유가/코스닥

    if ( ( board_id == "G4" ) || ( session_id == "70" ) )
    {
        // 시간외 단일가는 처리하지 않는다.
        return ( 0 );
    }

    elwTrade.market = getMarketInTrade(board_id);

    ACE_CString upDown(rawPacket.price_change_against_previous_day_code, sizeof ( rawPacket.price_change_against_previous_day_code ));
    elwTrade.upDown = getUpDownInTrade(upDown);

    // 장개시전시간외거래인 경우 시가, 고가, 저가는 0으로 셋팅하고 종가는 체결가로 셋팅한다.
    if ( ( board_id == "G2" ) || ( session_id == "50" ) )
    {
        elwTrade.open = 0;
        elwTrade.high = 0;
        elwTrade.low = 0;
        elwTrade.close = atoi(ACE_CString(rawPacket.current_price, sizeof ( rawPacket.current_price )).c_str());
    }
    //장종료후시간외종가거래인 경우 시가, 고가, 저가, 종가는 그대로 두고, 체결량만 변경한다.
    else if ( ( board_id == "G3" ) || ( session_id == "65" ) )  //
    {
        //가격을 셋팅하지 않는다.
        if ( hasValue == -1 )
        {
            return ( 0 );
        }
    }
    else
    {
        elwTrade.open = ::atoi(ACE_CString(rawPacket.opening_price, sizeof ( rawPacket.opening_price )).c_str());
        elwTrade.high = ::atoi(ACE_CString(rawPacket.high_price, sizeof ( rawPacket.high_price )).c_str());
        elwTrade.low = ::atoi(ACE_CString(rawPacket.low_price, sizeof ( rawPacket.low_price )).c_str());
        elwTrade.close = ::atoi(ACE_CString(rawPacket.current_price, sizeof ( rawPacket.current_price )).c_str());
    }

    ACE_CString tradePrice(rawPacket.current_price, sizeof ( rawPacket.current_price ));
    ACE_CString openPrice(rawPacket.opening_price, sizeof ( rawPacket.opening_price ));
    ACE_CString highPrice(rawPacket.high_price, sizeof ( rawPacket.high_price ));
    ACE_CString lowPrice(rawPacket.low_price, sizeof ( rawPacket.low_price ));

    // 현재가가 0 이면 skip
    if ( filter.mustFilterByCurrPrice(elwTrade.close) )
    {
        return ( -1 );
    }

    int gap = ::atoi(ACE_CString(rawPacket.price_change_against_previous_day, sizeof ( rawPacket.price_change_against_previous_day )).c_str());
    if ( ( elwTrade.upDown == UPDOWN_DOWN ) || ( elwTrade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    elwTrade.ydayClose = elwTrade.close - gap;
    elwTrade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(rawPacket.accumulated_volume, sizeof ( rawPacket.accumulated_volume )).c_str());
    double accmAmount = ::atof(ACE_CString(rawPacket.accumulated_traded_value, sizeof ( rawPacket.accumulated_traded_value )).c_str());

    elwTrade.tradeVolume = ::atof(ACE_CString(rawPacket.trading_volume, sizeof ( rawPacket.trading_volume )).c_str());

    if ( elwTrade.tradeVolume < 0 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A3021] Skip : %s,%d : net volume error issue_code:[%s] elwTrade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , issue_code.c_str() , elwTrade.tradeVolume ), -1);
    }

    setAccmVolume(issue_code, accmVolume, board_id);
    setAccmAmount(issue_code, accmAmount, board_id);

    elwTrade.accmVolume = getTotalAccmVolume(issue_code);

    if ( elwTrade.accmVolume == -1 )
    {
        elwTrade.accmVolume = 0;   //accmVolume ;
    }

    ACE_CString trading_time(rawPacket.trading_time, sizeof ( rawPacket.trading_time ));
    ACE_CString frameID = "A3";
    int tradeTime = getTickTime(trading_time, frameID);

    elwTrade.amount = getTotalAccmAmount(issue_code);
    if ( elwTrade.amount == -1 )
    {
        elwTrade.amount = 0;   //amount ;
    }

    ::memcpy(& ( elwTrade.boardID ), board_id.c_str(), board_id.length());
    ::memcpy(& ( elwTrade.sessionID ), session_id.c_str(), session_id.length());

    ACE_CString str_lp_holding_quantity(rawPacket.lp_holding_quantity, sizeof ( rawPacket.lp_holding_quantity ));
    double lp_holding_quantity = ::atof(str_lp_holding_quantity.c_str());
    elwTrade.lpHoldingVolume = lp_holding_quantity;

	char isequalcloseandquoteprice1;
	ACE_CString bid_1_order(rawPacket.bid_1_order, sizeof ( rawPacket.bid_1_order ));

	if(::atof(bid_1_order.c_str()) == 0) isequalcloseandquoteprice1 = '0';
	else
	{
	    if(tradePrice == bid_1_order) isequalcloseandquoteprice1 = '1';
		else isequalcloseandquoteprice1 = '2';
	}

#if(0)
    elwTrade.isEqualCloseAndQuotePrice1 = rawPacket.assurance_on_trading_price_and_first_price[0];
#endif
#if(1)
    elwTrade.isEqualCloseAndQuotePrice1 = isequalcloseandquoteprice1;
#endif

    if ( hasValue == -1 )
    {
        elwTrade.subtype = TRADESUBTYPE_TRADE;
        elwTrade.exchange = EXCHANGE_KSE;
        elwTrade.symbolType = SYMBOL_ELW;
        elwTrade.decimalPoint = DECIMAL_0;
        elwTrade.tradeTime = tradeTime;

        ::memcpy(& ( elwTrade.symbol ), issue_code.c_str(), issue_code.length());

        elwTrade.openMin = elwTrade.close;
        elwTrade.highMin = elwTrade.close;
        elwTrade.lowMin = elwTrade.close;
        elwTrade.volumeMin = elwTrade.tradeVolume;

        elwTradeMap_->bind(ACE_CString(issue_code.c_str(), ALLOCATOR::instance()), elwTrade, ALLOCATOR::instance());
    }
    else
    {
        int tradeTimePrev = elwTrade.tradeTime;
        elwTrade.tradeTime = tradeTime;
        if ( ( ( elwTrade.tradeTime / 60 ) == ( tradeTimePrev / 60 ) ) && ( elwTrade.volumeMin != 0 ) )
        {
            elwTrade.volumeMin = elwTrade.volumeMin + elwTrade.tradeVolume;

            if ( elwTrade.close > elwTrade.highMin )
            {
                elwTrade.highMin = elwTrade.close;
            }

            if ( elwTrade.close < elwTrade.lowMin )
            {
                elwTrade.lowMin = elwTrade.close;
            }
        }
        else
        {
            elwTrade.volumeMin = elwTrade.tradeVolume;
            elwTrade.openMin = elwTrade.close;
            elwTrade.highMin = elwTrade.close;
            elwTrade.lowMin = elwTrade.close;
        }
        ACE_CString oldKey;
        ELWTrade oldVal;
        ::memset(&oldVal, 0, sizeof(ELWTrade));

        elwTradeMap_->rebind(ACE_CString(issue_code.c_str(), ALLOCATOR::instance()), elwTrade, oldKey, oldVal, ALLOCATOR::instance());
    }

    printPacketELWTrade(elwTrade);

    // 체결 전문 압축 발송
    // sendTrade(trade);

    // 체결 전문 압축 해제 발송
    char buf[ELW_TRADE_SIZE];
    ::memset(buf, 0, sizeof ( buf ));
    memcpy(buf, &elwTrade, ELW_TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, ELW_TRADE_SIZE), PACKET_ELW_TRADE, EXCHANGE_KSE);
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A3021] issue_code:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , result ));
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A3021] END\n" , getCurrentTimestamp().c_str() ));
    return ( result );

}
#endif

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_A702S(const ACE_CString& packet)
{
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A702S] BEGIN\n" , getCurrentTimestamp().c_str() ));

    if ( EXTURE_PLUS_ELW_ELW_MARKET_OPERATION_TS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A702S] Skip : %s, %d : EXTURE_PLUS_ELW_ELW_MARKET_OPERATION_TS_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_ELW_MARKET_OPERATION_TS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExturePlusElwELWMarketOperationTS rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwELWMarketOperationTS));
    ::memcpy(&rawPacket, packet.c_str(), sizeof(ExturePlusElwELWMarketOperationTS));

    ELWMarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(ELWMarketOperation));

    std::string issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));
    issue_code = trim(issue_code);

    if ( issue_code == std::string("") )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A702S] invalid issue_code:[%s][%d] skip...... packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , issue_code.length() , packet.c_str() , packet.length() ));
        return ( 0 );
    }

    ::memcpy(& ( marketRec.symbol ), issue_code.c_str(), issue_code.length());
    marketRec.recvTime = (int) ( ::time(0) );
    ::memcpy(& ( marketRec.boardID ), & ( rawPacket.board_id ), sizeof ( rawPacket.board_id ));
    ::memcpy(& ( marketRec.boardEventID ), & ( rawPacket.board_event_id ), sizeof ( rawPacket.board_event_id ));
    ::memcpy(& ( marketRec.beginTime ), & ( rawPacket.start_time_of_board_event ), sizeof ( rawPacket.start_time_of_board_event ));
    ::memcpy(& ( marketRec.boardEventGroupCode ), & ( rawPacket.board_event_group_code ), sizeof ( rawPacket.board_event_group_code ));
    ::memcpy(& ( marketRec.sessionID ), & ( rawPacket.session_id ), sizeof ( rawPacket.session_id ));
    ::memcpy(& ( marketRec.tradingHaltReason ), & ( rawPacket.trading_suspension_cause_code ), sizeof ( rawPacket.trading_suspension_cause_code ));

    printPacketELWMarketOperation(marketRec);

    char buf[ELW_MARKET_OPERATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &marketRec, sizeof(ELWMarketOperation));
    int result = sendPacket(ACE_CString(buf, ELW_MARKET_OPERATION_SIZE), PACKET_ELW_MARKET_OPERATION, EXCHANGE_KSE);
    //   ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_A702S] result:[%d]\n" , getCurrentTimestamp().c_str() , result ));
    return ( result );

}
#endif

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_B702S(const ACE_CString& packet)
{
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B702S] BEGIN\n" , getCurrentTimestamp().c_str() ));
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B702S] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    if ( EXTURE_PLUS_ELW_ELW_REMAINING_VOLUME_ON_QUOTES_LP_QUOTES_INCLUDED_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B702S] Skip : %s, %d : EXTURE_PLUS_ELW_ELW_REMAINING_VOLUME_ON_QUOTES_LP_QUOTES_INCLUDED_SIZE:[%d] != packet.length():[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_ELW_REMAINING_VOLUME_ON_QUOTES_LP_QUOTES_INCLUDED_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwELWRemainingVolumeOnQuotesLPQuotesIncluded rawPacket;
    ACE_OS::memcpy(&rawPacket, packet.c_str(), packet.length());

    ACE_CString issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));

    ACE_CString board_id(rawPacket.board_id, sizeof ( rawPacket.board_id ));
    ACE_CString session_id(rawPacket.session_id, sizeof ( rawPacket.session_id ));

    /*
     * 현물처리에서 board_id 가 바이인 관련인 경우에는 skip 시켰는데,
     * ELW 에서는 아직 정책을 못정했다. 일단 그대로 보낸다.
     * 시간외단일가는 처리하지 않는다.
     */

    // 세션ID / 70:시간외단일가
    // 보드ID / 장종료후시간외단일가(G4)
    if ( ( session_id == "70" ) || ( board_id == "G4" ) )
    {
        return ( 0 );
    }

    ELWQuote10LPIncluded elwQuote10;
    ::memset(&elwQuote10, 0, sizeof(ELWQuote10LPIncluded));

    elwQuote10.exchange = EXCHANGE_KSE;
    elwQuote10.symbolType = SYMBOL_ELW;
    elwQuote10.decimalPoint = 0;

    ::memcpy(& ( elwQuote10.symbol ), issue_code.c_str(), issue_code.length());

    elwQuote10.concurrent = getConcurrent(board_id, session_id);
    elwQuote10.market = getMarketInQuote10(board_id, session_id);

    elwQuote10.quoteTime = ::time(0);
    elwQuote10.totalAskVolume = ::atof(ACE_CString(rawPacket.rec[0].askQuoteVolume, sizeof ( rawPacket.rec[0].askQuoteVolume )).c_str());
    elwQuote10.totalBidVolume = ::atof(ACE_CString(rawPacket.rec[0].bidQuoteVolume, sizeof ( rawPacket.rec[0].bidQuoteVolume )).c_str());

    elwQuote10.expectedPrice = ::atoi(ACE_CString(rawPacket.estimated_trading_price, sizeof ( rawPacket.estimated_trading_price )).c_str());
    elwQuote10.expectedVolume = ::atof(ACE_CString(rawPacket.estimated_trading_quantity, sizeof ( rawPacket.estimated_trading_quantity )).c_str());

    for ( int i = 0 ; i < 10 ; ++i )
    {
        elwQuote10.rec[i].ask = ::atoi(ACE_CString(rawPacket.rec[i].askQuote, sizeof ( rawPacket.rec[i].askQuote )).c_str());
        elwQuote10.rec[i].askVolume = ::atoi(ACE_CString(rawPacket.rec[i].askQuoteVolume, sizeof ( rawPacket.rec[i].askQuoteVolume )).c_str());
        elwQuote10.rec[i].askVolumeLP = ::atoi(ACE_CString(rawPacket.rec[i].askQuoteVolumeLP, sizeof ( rawPacket.rec[i].askQuoteVolumeLP )).c_str());
        elwQuote10.rec[i].bid = ::atoi(ACE_CString(rawPacket.rec[i].bidQuote, sizeof ( rawPacket.rec[i].bidQuote )).c_str());
        elwQuote10.rec[i].bidVolume = ::atoi(ACE_CString(rawPacket.rec[i].bidQuoteVolume, sizeof ( rawPacket.rec[i].bidQuoteVolume )).c_str());
        elwQuote10.rec[i].bidVolumeLP = ::atoi(ACE_CString(rawPacket.rec[i].bidQuoteVolumeLP, sizeof ( rawPacket.rec[i].bidQuoteVolumeLP )).c_str());
    }

    // session_id, board_id 를 필요로 하는 경우가 있다. (모의투자등)
    ::memcpy(& ( elwQuote10.boardID ), & ( rawPacket.board_id ), sizeof ( rawPacket.board_id ));
    ::memcpy(& ( elwQuote10.sessionID ), & ( rawPacket.session_id ), sizeof ( rawPacket.session_id ));

//    sendELWQuote10LPIncluded (elwQuote10);

    char buf[ELW_QUOTE10_LP_INCLUDED_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &elwQuote10, ELW_QUOTE10_LP_INCLUDED_SIZE);

    int result = sendPacket(ACE_CString(buf, ELW_QUOTE10_LP_INCLUDED_SIZE), PACKET_ELW_QUOTE10_LP_INCLUDED, EXCHANGE_KSE);

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B702S] issue_code:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , result ));
//    printPacketELWQuote10LPIncluded(elwQuote10);
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B702S] END\n" , getCurrentTimestamp().c_str() ));
    return ( result );
}
#endif

int InternetElwChannelProcessor::processPacket_KRX_B2021(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_ELW_ELW_MARKET_DATA_RECOVERY_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B2021] Skip : %s,%d : EXTURE_PLUS_ELW_ELW_MARKET_DATA_RECOVERY_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_ELW_MARKET_DATA_RECOVERY_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ACE_CString frameId(packet.substr(0, 2));

    // log frame count status
    LogFrameCount(frameId);

    ExturePlusElwELWMarketDataRecovery rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwELWMarketDataRecovery));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ACE_CString issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));

    ACE_CString board_id(rawPacket.board_id, sizeof ( rawPacket.board_id ));
    ACE_CString board_event_id(rawPacket.board_event_id, sizeof ( rawPacket.board_event_id ));

    ELWTrade elwTrade;
    ::memset(&elwTrade, 0, sizeof(ELWTrade));

    TickFilter filter;

    int hasValue = elwTradeMap_->find(issue_code, elwTrade, ALLOCATOR::instance());

    ACE_CString upDown(rawPacket.fluctuation_type, sizeof ( rawPacket.fluctuation_type ));

    elwTrade.market = getMarketInRecoveryTrade(board_id, board_event_id);
    elwTrade.upDown = getUpDownInTrade(upDown);

    elwTrade.open = parseInt(ACE_CString(rawPacket.market_price, sizeof ( rawPacket.market_price )), 0);
    elwTrade.high = parseInt(ACE_CString(rawPacket.highest_limit_price, sizeof ( rawPacket.highest_limit_price )), 0);
    elwTrade.low = parseInt(ACE_CString(rawPacket.lowest_limit_price, sizeof ( rawPacket.lowest_limit_price )), 0);
    elwTrade.close = parseInt(ACE_CString(rawPacket.current_price_, sizeof ( rawPacket.current_price_ )), 0);

    if ( filter.mustFilterByCurrPrice(elwTrade.close) )
    {
        return ( -1 );
    }

    int gap = parseInt(ACE_CString(rawPacket.price_change_against_previous_day, sizeof ( rawPacket.price_change_against_previous_day )), 0);
    if ( ( elwTrade.upDown == UPDOWN_DOWN ) || ( elwTrade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    elwTrade.ydayClose = elwTrade.close - gap;
    elwTrade.openInterest = 0;

    double beforeMarketOverTimeClosePriceTradeVolume = parseDouble(ACE_CString(rawPacket.closing_price_trading_volume_of_pre_opening_market, sizeof ( rawPacket.closing_price_trading_volume_of_pre_opening_market )), 0);
    double beforeMarketOverTimeClosePriceTradeAmount = parseDouble(ACE_CString(rawPacket.closing_price_trading_value_of_pre_opening_market, sizeof ( rawPacket.closing_price_trading_value_of_pre_opening_market )), 0);
    double regularMarketTradeVolume = parseDouble(ACE_CString(rawPacket.trading_volume_of_regular_session, sizeof ( rawPacket.trading_volume_of_regular_session )), 0);
    double regularMarketTradeAmount = parseDouble(ACE_CString(rawPacket.trading_value_of_regular_session, sizeof ( rawPacket.trading_value_of_regular_session )), 0);
    double afterMarketOvertimeClosePriceTradeVolume = parseDouble(ACE_CString(rawPacket.closing_price_trading_volume_of_after_hour_market, sizeof ( rawPacket.closing_price_trading_volume_of_after_hour_market )), 0);
    double afterMarketOvertimeClosePriceTradeAmount = parseDouble(ACE_CString(rawPacket.closing_price_trading_value_of_after_hour_market, sizeof ( rawPacket.closing_price_trading_value_of_after_hour_market )), 0);

    const ACE_CString BOARD_ID_MARKET_IN("G1");
    const ACE_CString BOARD_ID_MARKET_BEFORE_TRADE("G2");
    const ACE_CString BOARD_ID_MARKET_AFTER_TRADE("G3");
    const ACE_CString BOARD_ID_BULK_TRADE_TODAY("ZZ");

    // 장개시전 시간외 거래 값 업데이트
    if ( getAccmVolume(issue_code, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeVolume )
    {
        setAccmVolume(issue_code, beforeMarketOverTimeClosePriceTradeVolume, BOARD_ID_MARKET_BEFORE_TRADE);
    }
    if ( getAccmAmount(issue_code, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeAmount )
    {
        setAccmAmount(issue_code, beforeMarketOverTimeClosePriceTradeAmount, BOARD_ID_MARKET_BEFORE_TRADE);
    }

    // 정규장 값 업데이트
    if ( getAccmVolume(issue_code, BOARD_ID_MARKET_IN) < regularMarketTradeVolume )
    {
        setAccmVolume(issue_code, regularMarketTradeVolume, BOARD_ID_MARKET_IN);
    }
    if ( getAccmAmount(issue_code, BOARD_ID_MARKET_IN) < regularMarketTradeAmount )
    {
        setAccmAmount(issue_code, regularMarketTradeAmount, BOARD_ID_MARKET_IN);
    }

    // 장마감후 시간외 거래 값 업데이트
    if ( getAccmVolume(issue_code, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeVolume )
    {
        setAccmVolume(issue_code, afterMarketOvertimeClosePriceTradeVolume, BOARD_ID_MARKET_AFTER_TRADE);
    }
    if ( getAccmAmount(issue_code, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeAmount )
    {
        setAccmAmount(issue_code, afterMarketOvertimeClosePriceTradeAmount, BOARD_ID_MARKET_AFTER_TRADE);
    }

    double accmVolume = parseDouble(ACE_CString(rawPacket.accumulated_total_trading_volume, sizeof ( rawPacket.accumulated_total_trading_volume )), 0);
    double accmAmount = parseDouble(ACE_CString(rawPacket.accumulated_total_trading_value, sizeof ( rawPacket.accumulated_total_trading_value )), 0);

    // 대량체결거래량
    double bulkTradeVolumeEstimated = accmVolume - ( beforeMarketOverTimeClosePriceTradeVolume + regularMarketTradeVolume + afterMarketOvertimeClosePriceTradeVolume );
    // 대량체결거래대금
    double bulkTradeAmountEstimated = accmAmount - ( beforeMarketOverTimeClosePriceTradeAmount + regularMarketTradeAmount + afterMarketOvertimeClosePriceTradeAmount );

    if ( getAccmVolume(issue_code, BOARD_ID_BULK_TRADE_TODAY) < bulkTradeVolumeEstimated )
    {
        setAccmVolume(issue_code, bulkTradeVolumeEstimated, BOARD_ID_BULK_TRADE_TODAY);
    }
    if ( getAccmAmount(issue_code, BOARD_ID_BULK_TRADE_TODAY) < bulkTradeAmountEstimated )
    {
        setAccmAmount(issue_code, bulkTradeAmountEstimated, BOARD_ID_BULK_TRADE_TODAY);
    }

    if ( accmVolume < getTotalAccmVolume(issue_code) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B2021] Skip : %s,%d : net volume error issue_code:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , issue_code.c_str() , accmVolume , getTotalAccmVolume(issue_code) ), -1);
    }

    if ( accmVolume > 0 )
    {
        setTotalAccmVolume(issue_code, accmVolume);
    }
    elwTrade.accmVolume = getTotalAccmVolume(issue_code);

    if ( accmAmount > 0 )
    {
        setTotalAccmAmount(issue_code, accmAmount);
    }
    elwTrade.amount = getTotalAccmAmount(issue_code);

    if ( frameId == "B1" )
    {
        elwTrade.subtype = TRADESUBTYPE_CLOSE;
    }
    else
    {
        // 실세 기세 구분
        ACE_CString quotation(rawPacket.regular_closing_price_biased_quotation_new_closing_price_without_trades_price, sizeof ( rawPacket.regular_closing_price_biased_quotation_new_closing_price_without_trades_price ));
        if ( quotation == "2" )
        {
            elwTrade.subtype = TRADESUBTYPE_QUOTATION;
        }
        else
        {
            elwTrade.subtype = TRADESUBTYPE_RECOVERY;
        }
    }

    elwTrade.tradeVolume = 0;

    if ( hasValue == -1 )
    {
        elwTrade.exchange = EXCHANGE_KSE;
        elwTrade.symbolType = SYMBOL_ELW;
        elwTrade.decimalPoint = DECIMAL_0;
        elwTrade.tradeTime = ::time(0);
        ::memcpy(& ( elwTrade.symbol ), issue_code.c_str(), issue_code.length());
        elwTrade.openMin = 0;
        elwTrade.highMin = 0;
        elwTrade.lowMin = 0;
        elwTrade.volumeMin = 0;
    }

    elwTrade.market = getMarketBasedCurrentTime();

    ACE_CString oldKey;
    ELWTrade oldVal;
    ::memset(&oldVal, 0, sizeof(ELWTrade));
    elwTradeMap_->rebind(ACE_CString(issue_code.c_str(), ALLOCATOR::instance()), elwTrade, oldKey, oldVal, ALLOCATOR::instance());

    printPacketELWTrade(elwTrade);

    char bufferForPacket[ELW_TRADE_SIZE];
    ::memset(&bufferForPacket, 0, sizeof ( bufferForPacket ));
    ::memcpy(&bufferForPacket, &elwTrade, ELW_TRADE_SIZE);
    int result = sendPacket(ACE_CString(bufferForPacket, ELW_TRADE_SIZE), PACKET_ELW_TRADE, EXCHANGE_KSE);
    //   ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B2021] issue_code:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , result ));
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B2021] END\n" , getCurrentTimestamp().c_str() ));
    return ( result );
}

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_B902S(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_ELW_ELW_TOP_5_ASK_BID_TRADERS_ACTIVITY_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B9021] Skip : %s, %d : EXTURE_PLUS_ELW_ELW_TOP_5_ASK_BID_TRADERS_ACTIVITY_INFORMATION_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_ELW_TOP_5_ASK_BID_TRADERS_ACTIVITY_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwELWTop5AskBidTradersActivityInformation rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwELWTop5AskBidTradersActivityInformation));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ELWSecuritiesTrade sec;
    ::memset(&sec, 0, sizeof(ELWSecuritiesTrade));
    sec.subtype = SECURITIESTRADESUBTYPE_TRADE;
    sec.exchange = EXCHANGE_KSE;
    sec.symbolType = SYMBOL_ELW;
    ACE_CString issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));

    ::memcpy(& ( sec.symbol ), issue_code.c_str(), issue_code.length());
    sec.recvTime = (int) ( ::time(0) );

    ::memcpy(& ( sec.rec1.seller ), & ( rawPacket.ask_member_number1 ), sizeof ( rawPacket.ask_member_number1 ));
    ::memcpy(& ( sec.rec1.buyer ), & ( rawPacket.bid_member_number1 ), sizeof ( rawPacket.bid_member_number1 ));
    sec.rec1.askVolume = parseDouble(ACE_CString(rawPacket.ask_trading_volume1, sizeof ( rawPacket.ask_trading_volume1 )), 0);
    sec.rec1.bidVolume = parseDouble(ACE_CString(rawPacket.bid_trading_volume1, sizeof ( rawPacket.bid_trading_volume1 )), 0);
    sec.rec1.askAmount = parseDouble(ACE_CString(rawPacket.ask_trading_value1, sizeof ( rawPacket.ask_trading_value1 )), 0);
    sec.rec1.bidAmount = parseDouble(ACE_CString(rawPacket.bid_trading_value1, sizeof ( rawPacket.bid_trading_value1 )), 0);

    ::memcpy(& ( sec.rec2.seller ), & ( rawPacket.ask_member_number2 ), sizeof ( rawPacket.ask_member_number2 ));
    ::memcpy(& ( sec.rec2.buyer ), & ( rawPacket.bid_member_number2 ), sizeof ( rawPacket.bid_member_number2 ));
    sec.rec2.askVolume = parseDouble(ACE_CString(rawPacket.ask_trading_volume2, sizeof ( rawPacket.ask_trading_volume2 )), 0);
    sec.rec2.bidVolume = parseDouble(ACE_CString(rawPacket.bid_trading_volume2, sizeof ( rawPacket.bid_trading_volume2 )), 0);
    sec.rec2.askAmount = parseDouble(ACE_CString(rawPacket.ask_trading_value2, sizeof ( rawPacket.ask_trading_value2 )), 0);
    sec.rec2.bidAmount = parseDouble(ACE_CString(rawPacket.bid_trading_value2, sizeof ( rawPacket.bid_trading_value2 )), 0);

    ::memcpy(& ( sec.rec3.seller ), & ( rawPacket.ask_member_number3 ), sizeof ( rawPacket.ask_member_number3 ));
    ::memcpy(& ( sec.rec3.buyer ), & ( rawPacket.bid_member_number3 ), sizeof ( rawPacket.bid_member_number3 ));
    sec.rec3.askVolume = parseDouble(ACE_CString(rawPacket.ask_trading_volume3, sizeof ( rawPacket.ask_trading_volume3 )), 0);
    sec.rec3.bidVolume = parseDouble(ACE_CString(rawPacket.bid_trading_volume3, sizeof ( rawPacket.bid_trading_volume3 )), 0);
    sec.rec3.askAmount = parseDouble(ACE_CString(rawPacket.ask_trading_value3, sizeof ( rawPacket.ask_trading_value3 )), 0);
    sec.rec3.bidAmount = parseDouble(ACE_CString(rawPacket.bid_trading_value3, sizeof ( rawPacket.bid_trading_value3 )), 0);

    ::memcpy(& ( sec.rec4.seller ), & ( rawPacket.ask_member_number4 ), sizeof ( rawPacket.ask_member_number4 ));
    ::memcpy(& ( sec.rec4.buyer ), & ( rawPacket.bid_member_number4 ), sizeof ( rawPacket.bid_member_number4 ));
    sec.rec4.askVolume = parseDouble(ACE_CString(rawPacket.ask_trading_volume4, sizeof ( rawPacket.ask_trading_volume4 )), 0);
    sec.rec4.bidVolume = parseDouble(ACE_CString(rawPacket.bid_trading_volume4, sizeof ( rawPacket.bid_trading_volume4 )), 0);
    sec.rec4.askAmount = parseDouble(ACE_CString(rawPacket.ask_trading_value4, sizeof ( rawPacket.ask_trading_value4 )), 0);
    sec.rec4.bidAmount = parseDouble(ACE_CString(rawPacket.bid_trading_value4, sizeof ( rawPacket.bid_trading_value4 )), 0);

    ::memcpy(& ( sec.rec5.seller ), & ( rawPacket.ask_member_number5 ), sizeof ( rawPacket.ask_member_number5 ));
    ::memcpy(& ( sec.rec5.buyer ), & ( rawPacket.bid_member_number5 ), sizeof ( rawPacket.bid_member_number5 ));
    sec.rec5.askVolume = parseDouble(ACE_CString(rawPacket.ask_trading_volume5, sizeof ( rawPacket.ask_trading_volume5 )), 0);
    sec.rec5.bidVolume = parseDouble(ACE_CString(rawPacket.bid_trading_volume5, sizeof ( rawPacket.bid_trading_volume5 )), 0);
    sec.rec5.askAmount = parseDouble(ACE_CString(rawPacket.ask_trading_value5, sizeof ( rawPacket.ask_trading_value5 )), 0);
    sec.rec5.bidAmount = parseDouble(ACE_CString(rawPacket.bid_trading_value5, sizeof ( rawPacket.bid_trading_value5 )), 0);

    printPacketELWSecuritiesTrade(sec);

    char buf[ELW_SECURITIES_TRADE_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &sec, ELW_SECURITIES_TRADE_SIZE);

    int result = sendPacket(ACE_CString(buf, ELW_SECURITIES_TRADE_SIZE), PACKET_ELW_SECURITIES_TRADE, EXCHANGE_KSE);

    //   ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B9021] issue_code:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , result ));
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KRX_B9021] END\n" , getCurrentTimestamp().c_str() ));
    return ( result );

}
#endif

#if(1)
int InternetElwChannelProcessor::processPacket_KRX_I702S(const ACE_CString& packet)
{
    if ( EXTURE_PLUS_ELW_KOSPI_LP_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KRX_I702S] Skip : %s, %d : EXTURE_PLUS_ELW_KOSPI_LP_INFORMATION_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_KOSPI_LP_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwKOSPI_LP_Information rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwKOSPI_LP_Information));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ACE_CString data_category(rawPacket.data_category, sizeof ( rawPacket.data_category ));
    ACE_CString issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));
    ACE_CString market_participant_number(rawPacket.market_participant_number, sizeof ( rawPacket.market_participant_number ));
    ACE_CString lp_starting_date(rawPacket.lp_starting_date, sizeof ( rawPacket.lp_starting_date ));
    ACE_CString lp_expiration_date(rawPacket.lp_expiration_date, sizeof ( rawPacket.lp_expiration_date ));
    ACE_CString str_minimum_order_volume_multiple(rawPacket.minimum_order_volume_multiple, sizeof ( rawPacket.minimum_order_volume_multiple ));
    ACE_CString str_maximum_order_volume_multiple(rawPacket.maximum_order_volume_multiple, sizeof ( rawPacket.maximum_order_volume_multiple ));
    ACE_CString order_spread_unit_code(rawPacket.order_spread_unit_code, sizeof ( rawPacket.order_spread_unit_code ));
    ACE_CString str_order_spread_value(rawPacket.order_spread_value, sizeof ( rawPacket.order_spread_value ));
    ACE_CString str_market_close_for_holiday_order_spread_multiple(rawPacket.market_close_for_holiday_order_spread_multiple, sizeof ( rawPacket.market_close_for_holiday_order_spread_multiple ));
    ACE_CString str_duty_order_submit_time_interval(rawPacket.duty_order_submit_time_interval, sizeof ( rawPacket.duty_order_submit_time_interval ));
    ACE_CString str_bid_minumum_order_price(rawPacket.bid_minumum_order_price, sizeof ( rawPacket.bid_minumum_order_price ));
    ACE_CString str_ask_minimum_order_price(rawPacket.ask_minimum_order_price, sizeof ( rawPacket.ask_minimum_order_price ));

    ELW_LP_Information infoRec;
    ::memset(&infoRec, 0, sizeof(ELW_LP_Information));

    ::memcpy(infoRec.symbol, issue_code.c_str(), issue_code.length());
    infoRec.recvTime = (int) ( ::time(0) );
    ::memcpy(infoRec.market_participant_number, market_participant_number.c_str(), market_participant_number.length());
    ::memcpy(infoRec.lp_starting_date, lp_starting_date.c_str(), lp_starting_date.length());
    ::memcpy(infoRec.lp_expiration_date, lp_expiration_date.c_str(), lp_expiration_date.length());
    double minimum_order_volume_multiple = ::atof(str_minimum_order_volume_multiple.c_str());
    infoRec.minimum_order_volume_multiple = minimum_order_volume_multiple;
    double maximum_order_volume_multiple = ::atof(str_maximum_order_volume_multiple.c_str());
    infoRec.maximum_order_volume_multiple = maximum_order_volume_multiple;
    ::memcpy(infoRec.order_spread_unit_code, order_spread_unit_code.c_str(), order_spread_unit_code.length());
    double order_spread_value = ::atof(str_order_spread_value.c_str());
    infoRec.order_spread_value = order_spread_value;
    double market_close_for_holiday_order_spread_multiple = ::atof(str_market_close_for_holiday_order_spread_multiple.c_str());
    infoRec.market_close_for_holiday_order_spread_multiple = market_close_for_holiday_order_spread_multiple;
    int duty_order_submit_time_interval = ::atoi(str_duty_order_submit_time_interval.c_str());
    infoRec.duty_order_submit_time_interval = duty_order_submit_time_interval;
    double bid_minumum_order_price = ::atof(str_bid_minumum_order_price.c_str());
    infoRec.bid_minumum_order_price = bid_minumum_order_price;
    double ask_minimum_order_price = ::atof(str_ask_minimum_order_price.c_str());
    infoRec.ask_minimum_order_price = ask_minimum_order_price;

    printPacketELW_LP_Information(infoRec);

    char buf[ELW_LP_INFORMATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &infoRec, ELW_LP_INFORMATION_SIZE);

    int result = 0;
    return ( result );

}
#endif

int InternetElwChannelProcessor::processPacket_KOSCOM_F1011(const ACE_CString& packet)
{
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F1011] BEGIN\n" , getCurrentTimestamp().c_str() ));
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F1011] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    if ( EXTURE_PLUS_ELW_KOSPI_FOREIGNER_INVESTMENT_INFORMATION_FOR_EACH_ISSUE_CONFIRMED_DATA_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F1011] Skip : %s, %d : EXTURE_PLUS_ELW_KOSPI_FOREIGNER_INVESTMENT_INFORMATION_FOR_EACH_ISSUE_CONFIRMED_DATA_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_KOSPI_FOREIGNER_INVESTMENT_INFORMATION_FOR_EACH_ISSUE_CONFIRMED_DATA_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwKospiForeignerInvestmentInformationForEachIssueConfirmedData rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwKospiForeignerInvestmentInformationForEachIssueConfirmedData));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ForeignerMaster master;
    ::memset(&master, 0, sizeof(ForeignerMaster));

    master.exchange = getExchange(rawPacket.infoMarketClass[2]);
    master.symbolType = SYMBOL_ELW;

    // 마지막 레코드 스킵.
    std::string issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));
    issue_code = trim(issue_code);
    if ( ( issue_code == "999999999999" ) || ( issue_code == "000000000000" ) || ( issue_code == "" ) )
    {
        return ( 0 );
    }

    ::memcpy(& ( master.symbol ), issue_code.c_str(), issue_code.length());

    master.serial = 0;  // ELW F1 전문에는 없다.
    master.symbolLimitRate = parseInt(ACE_CString(rawPacket.issue_limit_ratio, sizeof ( rawPacket.issue_limit_ratio )).c_str(), 0);
    master.individualLimitRate = parseInt(ACE_CString(rawPacket.individual_limit_ratio, sizeof ( rawPacket.individual_limit_ratio )).c_str(), 0);

    // 한도수량 = 상장주식수 *  종목한도비율 / 10000 (10000으로 나눠진 이유는 종목한도비율값을 백분율값으로 나타내기 위해서 10000으로 나눠준다.)
    // master.limitVolume = atof(ACE_CString(kse.listingStockSize,sizeof kse.listingStockSize).c_str()) * atof(ACE_CString(kse.stockLimitRate,sizeof kse.stockLimitRate).c_str()) / (float)10000;
    // 위의 구문을 아래와 같이 변경함
    double listingStockSize = parseDouble(ACE_CString(rawPacket.number_of_listed_stock, sizeof ( rawPacket.number_of_listed_stock )).c_str(), 0);
    double stockLimitRate = parseDouble(ACE_CString(rawPacket.issue_limit_ratio, sizeof ( rawPacket.issue_limit_ratio )).c_str(), 0);
    double limitVolume = listingStockSize * stockLimitRate / 10000.0;
    master.limitVolume = limitVolume;

    ACE_CString str_limit_exhaustion_type(rawPacket.limit_exhaustion_type, sizeof ( rawPacket.limit_exhaustion_type ));
    master.exhaust = getExhaustInForeigner(str_limit_exhaustion_type);

    // 미사용 컬럼, (EXTURE 이전) KOSCOM 정보분배 시스템에서만 제공되었던 데이터
    master.orderLimitSign = 0;

    master.orderLimitVolume = parseDouble(ACE_CString(rawPacket.available_quantity_for_order, sizeof ( rawPacket.available_quantity_for_order )).c_str(), 0);
    master.listSize = parseDouble(ACE_CString(rawPacket.number_of_listed_stock, sizeof ( rawPacket.number_of_listed_stock )).c_str(), 0);

    printPacketForeignerMaster(master);

    char buf[FOREIGNER_MASTER_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &master, FOREIGNER_MASTER_SIZE);
    int result = sendPacket(ACE_CString(buf, FOREIGNER_MASTER_SIZE), PACKET_FOREIGNER_MASTER, master.exchange);

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F1011] issue_code:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , result ));

    return ( result );

}
int InternetElwChannelProcessor::processPacket_KOSCOM_F4011(const ACE_CString& packet)
{
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F4011] BEGIN\n" , getCurrentTimestamp().c_str() ));
//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F4011] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    if ( EXTURE_PLUS_ELW_KOSPI_FOREIGNER_CONFIRMED_DATA_RETRANSMISSION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F4011] Skip : %s, %d : EXTURE_PLUS_ELW_KOSPI_FOREIGNER_CONFIRMED_DATA_RETRANSMISSION_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_ELW_KOSPI_FOREIGNER_CONFIRMED_DATA_RETRANSMISSION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusElwKospiForeignerConfirmedDataRetransmission rawPacket;
    ::memset(&rawPacket, 0, sizeof(ExturePlusElwKospiForeignerConfirmedDataRetransmission));
    ::memcpy(&rawPacket, packet.c_str(), packet.length());

    ForeignerMaster master;
    ::memset(&master, 0, sizeof(ForeignerMaster));

    master.exchange = getExchange(rawPacket.infoMarketClass[2]);
    master.symbolType = SYMBOL_ELW;

    // 마지막 레코드 스킵.
    std::string issue_code(rawPacket.issue_code, sizeof ( rawPacket.issue_code ));
    issue_code = trim(issue_code);
    if ( ( issue_code == "999999999999" ) || ( issue_code == "000000000000" ) || ( issue_code == "" ) )
    {
        return ( 0 );
    }

    ::memcpy(& ( master.symbol ), issue_code.c_str(), issue_code.length());

    master.serial = 0;  // ELW F1 전문에는 없다.
    master.symbolLimitRate = parseInt(ACE_CString(rawPacket.issue_limit_ratio, sizeof ( rawPacket.issue_limit_ratio )).c_str(), 0);
    master.individualLimitRate = parseInt(ACE_CString(rawPacket.individual_limit_ratio, sizeof ( rawPacket.individual_limit_ratio )).c_str(), 0);

    // 한도수량 = 상장주식수 *  종목한도비율 / 10000 (10000으로 나눠진 이유는 종목한도비율값을 백분율값으로 나타내기 위해서 10000으로 나눠준다.)
    // master.limitVolume = atof(ACE_CString(kse.listingStockSize,sizeof kse.listingStockSize).c_str()) * atof(ACE_CString(kse.stockLimitRate,sizeof kse.stockLimitRate).c_str()) / (float)10000;
    // 위의 구문을 아래와 같이 변경함
    double listingStockSize = parseDouble(ACE_CString(rawPacket.number_of_listed_stock, sizeof ( rawPacket.number_of_listed_stock )).c_str(), 0);
    double stockLimitRate = parseDouble(ACE_CString(rawPacket.issue_limit_ratio, sizeof ( rawPacket.issue_limit_ratio )).c_str(), 0);
    double limitVolume = listingStockSize * stockLimitRate / 10000.0;
    master.limitVolume = limitVolume;

    ACE_CString str_limit_exhaustion_type(rawPacket.limit_exhaustion_type, sizeof ( rawPacket.limit_exhaustion_type ));
    master.exhaust = getExhaustInForeigner(str_limit_exhaustion_type);

    // 미사용 컬럼, (EXTURE 이전) KOSCOM 정보분배 시스템에서만 제공되었던 데이터
    master.orderLimitSign = 0;

    master.orderLimitVolume = parseDouble(ACE_CString(rawPacket.available_quantity_for_order, sizeof ( rawPacket.available_quantity_for_order )).c_str(), 0);
    master.listSize = parseDouble(ACE_CString(rawPacket.number_of_listed_stock, sizeof ( rawPacket.number_of_listed_stock )).c_str(), 0);

    printPacketForeignerMaster(master);

    char buf[FOREIGNER_MASTER_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &master, FOREIGNER_MASTER_SIZE);
    int result = sendPacket(ACE_CString(buf, FOREIGNER_MASTER_SIZE), PACKET_FOREIGNER_MASTER, master.exchange);

    //   ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::processPacket_KOSCOM_F4011] issue_code:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() , result ));
    return ( result );

}

BYTE InternetElwChannelProcessor::getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = CONCURRENT_OFF;
    if ( boardID == "G1" ) //정규시간외구분코드가 1인경우(동시,접속 둘다 가능) 1 정규장 G1  유가/코스닥/파생/코넥스   개별경쟁거래
    {
        if ( sessionID == "10" ) //시가단일가는 ~09:00 까지. (10:시가단일가)
        {
            result = CONCURRENT_ON;
        }
        else if ( ( sessionID == "40" ) || ( sessionID == "11" ) ) //시가단일가연장은 9시 이후까지 진행가능하므로.
        {
            result = CONCURRENT_OFF;
        }
        else //그 외의 경우 접속으로 가정
        {
            result = CONCURRENT_OFF;
        }
    }
    else
    {
        result = CONCURRENT_OFF;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = MARKET_IN;
    // marketStatusClassCode 60: 장종료시간외접수
    /*
     * 60:장종료후시간외접수
     65:장종료후시간외
     */
    if ( ( boardID == "G3" ) || ( sessionID == "65" ) || ( sessionID == "60" ) )
    {
        result = MARKET_AFTER_TRADE;
    }
    else
    {
        result = MARKET_IN;
    }
    return ( result );
}

int InternetElwChannelProcessor::getTickTime(const ACE_CString &timeStr, const ACE_CString &frameId)
{
    int hour = 0;
    int minute = 0;
    int second = 0;

    if ( timeStr.substr(3, 3) == "JJJ" )
    {
        // 장전 예상지수인 경우 09:00 을 끝으로 한다. by dong in 2008.02.01
        if ( frameId == "D1" )
        {
            hour = 9;
        }
        else
        {
            hour = 18;
        }
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
    int tickTime = dayBaseTime + hour * 3600 + minute * 60 + second;
    return ( tickTime );
}

/*
 *
 *
 *
 * 1) 일반호가  -   1   정규장 G1  유가/코스닥/파생/코넥스   개별경쟁거래
 2   장개시전시간외종가   G2  유가/코스닥
 3   장종료후시간외종가   G3  유가/코스닥/코넥스
 4   장종료후시간외단일가  G4  유가/코스닥
 2   장개시전시간외종가   G5  코넥스
 7   일반Buy-In    G7  유가/코스닥/코넥스
 8   당일Buy-In    G8  유가/코스닥/코넥스
 *
 */
BYTE InternetElwChannelProcessor::getMarketInTrade(const ACE_CString& raw)
{
    BYTE result = MARKET_IN;
    if ( raw == "G2" )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( raw == "G3" )
    {
        result = MARKET_AFTER_TRADE;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getUpDownInTrade(const ACE_CString& raw)
{
    BYTE result = UPDOWN_STATIONARY;
    if ( raw == "1" )
    {
        result = UPDOWN_UP_LIMIT;
    }
    else if ( raw == "2" )
    {
        result = UPDOWN_UP;
    }
    else if ( raw == "4" )
    {
        result = UPDOWN_DOWN_LIMIT;
    }
    else if ( raw == "5" )
    {
        result = UPDOWN_DOWN;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID)
{
    BYTE result = MARKET_IN;

    if ( boardID == "G2" )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( boardID == "G3" )
    {
        result = MARKET_AFTER_TRADE;
    }
    else if ( boardID == "G4" )
    {
        result = MARKET_END;
    }
    else
    {
        result = MARKET_IN;
    }
    return ( result );
}

BYTE InternetElwChannelProcessor::getExchange(char rawSymbolType)
{
    return ( rawSymbolType == 'Q' ? EXCHANGE_KOSDAQ : EXCHANGE_KSE );
}

BYTE InternetElwChannelProcessor::getExhaustInForeigner(const ACE_CString& raw)
{
    BYTE result = static_cast<BYTE>(atoi(raw.c_str()));
    return ( result );
}


#if(1)
	ACE_CString indexConstEtnMap1[599] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","KGD04P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","K2D01T","K2D02T","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGG03P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","CGD01P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","K2G07N","K2G07T","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG02P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","GGS01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","110043","110046","110043","110004","110007","110012","110014","110020","110021","110023","110037","110038","110039","110040","110041","110042","110044","110045","110049","110051","110052","110053","110056","110057","110058","110059","110060","110061","110062","110065","110066","110067","110068","110069","110070","110071","110072","110073","110074","110077","110078","110079","110080","110081","110082","110083","110084","110086","110087","110088","110089","110090","110091","110092","110093","110094","110095","110096","110097","110098","110099","110100","110101","110102","110103","110104","110105","110106","110107","110108","110109","110110","110111","110112","2P8802","2P8803","2P9259","2P9269","2P9258","2P9284","2P9206","2P9271","2P9234","2P9272","2P9263","2P9256","2P9239","2P9246","2P9247","2P9248","2P9260","2P9255","2P9265","2P9267","2P9266","2P9276","2P9277","2P9278","2P9279","2P9280","2P9281","2P9282","2P9283","2P9231","2P9235","2P9240","2P9275","2P9211","2P9242","2P9243","2P9274","2P9245","2P9262","2P9236","2P9251","2P9238","2P9264","2P9268","2P9229","2P9252","2P9233","2P9253","2P9221","2P9244","2P9222","2P9257","2P9241","2P9273","2P9207","2P9250","2P9237","2P9249","2P9210","2P9232","2P9254","2PB003","2PB101","2PB201","2PB211","2PB221","2PB226","2PB231","2PB232","2PB237","2PB238","2PB239","2PB241","2PB242","2PB243","2PB305","2PB306","2PB307","2PC007","2PC006","2PM128","2PM126","2PM127","2PM119","2PM121","2PM102","2PM104","2PM107","2PM109","2PM112","2PM114","2PM115","2PM116","2PM117","2PM118","2PM122","2PM123","2PM131","2PM124","2PM132","2PM125","2PM120","2PM129","2PM130","2PM134","2PM133","2PM001","2PR001","2PR101","120001","120002","120003","120004","120005","2PW006","120007","120008","120009","120010","120011","120012","120013","120014","120015","120016","120017","120018","120019","120020","120021","120901"};
	ACE_CString indexConstEtnMap2[599] = 
	{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","187","188","165","132","133","134","142","136","141","411","412","413","414","415","351","352","353","354","355","356","357","358","105","600","167","203","212","213","214","215","216","217","218","331","204","175","176","169","174","301","302","303","304","801","802","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","004","013","707","731","708","821","312","313","009","010","005","006","007","008","717","003","709","011","012","304","306","307","308","305","822","732","051","052","100","101","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","050","053","054","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","055","056","057","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","601","602","601","004","007","012","014","020","021","023","037","038","039","040","041","042","044","045","049","051","052","053","056","057","058","059","060","061","062","065","066","067","068","069","070","071","072","073","074","077","078","079","080","081","082","083","084","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","802","803","259","269","258","284","206","271","234","272","263","256","239","246","247","248","260","255","265","267","266","276","277","278","279","280","281","282","283","231","235","240","275","211","242","243","274","245","262","236","251","238","264","268","229","252","233","253","221","244","222","257","241","273","207","250","237","249","210","232","254","003","101","201","211","221","226","231","232","237","238","239","241","242","243","305","306","307","007","006","128","126","127","119","121","102","104","107","109","112","114","115","116","117","118","122","123","131","124","132","125","120","129","130","134","133","001","001","101","001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","901"};
	ACE_CString indexConstEtnMap3[599] = 
	{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","5","5","5","5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","6","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","1","2","2","2","2","2","2","2","2","2","2","1","1","1","1","B","B","B","B","C","C","C","1","1","1","1","1","1","D","D","D","D","D","D","D","D","D","G","G","D","D","1","1","C","C","C","C","C","C","C","C","C","C","C","C","2","2","1","1","1","1","1","1","1","3","D","D","2","2","2","2","2","1","D","D","D","D","B","B","1","1","1","1","C","C","E","E","1","1","1","D","D","D","E","E","E","E","E","E","D","G","1","E","E","3","3","3","3","3","D","1","E","E","E","E","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","D","E","E","E","1","2","3","2","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","E","E","E","D","D","B","B","3","3","3","3","D","D","D","D","D","C","E","E","G","3","3","D","D","3","3","1","1","1","1","2","2","3","3","3","3","3","3","3","3","3","3","3","3","1","1","3","3","3","3","2","2","2","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","C","C","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","R","R","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"};
#endif

#if(1)
ACE_CString InternetElwChannelProcessor::getSymbolUpCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<599; kk++)
	{
		if(raw == indexConstEtnMap1[kk])
		{
			ii=kk;
			ff=100;
			break;
		}
	}

	if(ff==0)
	{
		std::ostringstream os;
		os << "000";
		return os.str().c_str();
	}
	else
	{
		return(indexConstEtnMap2[ii]);
	}
}

ACE_CString InternetElwChannelProcessor::getSymbolMarketTypeCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<599; kk++)
	{
		if(raw == indexConstEtnMap1[kk])
		{
			ii=kk;
			ff=100;
			break;
		}
	}

	if(ff==0)
	{
		std::ostringstream os;
		os << "0";
		return os.str().c_str();
	}
	else
	{
		return(indexConstEtnMap3[ii]);
	}
}
#endif
#endif



#if(0)
/*CHANGE-------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------*/
#endif

