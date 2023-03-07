#ifndef __EXTURE_PLUS_KOSPI_200_OPTION_H__
#define __EXTURE_PLUS_KOSPI_200_OPTION_H__

/*
 12345678901234567890123456789012345678901234567890123456789012345678901234567890
 */

#pragma pack(1)

#if(1)
// KOSPI200�����ɼ�_�ǽð�_UDP(8M)_20140901_2014072501.xls
// 19   K200�ɼ�_Polling ������  I2034   ��� ��Ʈ Ȯ�ο����� �۽� 1�а������� ����    20  1�а���    �ڽ���200�����ɼ�ü��ȣ������
class ExturePlusKoscomLineLKInfo_KOSPI200_OPTION
{
    public:
        // 001 ~ 010
        char dataCategory[2];                                   // 001 DATA ����
        char informationCategory[2];                            // 002 ��������
        char marketCategory[1];                                 // 003 ���屸��
        char time[4];                                           // 004 �ð�
        char mainBackupType[2];                                 // 005 MainBackup ����
        char filler[8];                                         // 006 Filler
        char endOfText[1];                                      // 007 FF
        char recvAddr[32];                                      // �����ּ�����(�������� ���� ��)
};
const int EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_OPTION_SIZE = sizeof(ExturePlusKoscomLineLKInfo_KOSPI200_OPTION);
#endif

#if(1)
//KOSPI200�������� �������� ������//�Ļ� ��������
//�Ļ� ��������//�Ļ� ��������
//�Ļ� �������� ���� �Ϸ� �� Ÿ ��ġ���� ����
//(�Ļ�A) DRV : A001F, A003F
class ExturePlusKospi200OptionStockInfoRecord
{
    public:
	char dataClass[2];               //�����ͱ��а�
	char infoMarketClass[3];               //�������а�
	char distributeStockIndex[8];               //�����й��Ϸù�ȣ
	char stockCount[6];               //���������������
	char hireDate[8];               //��������
	char stockCode[12];               //�����ڵ�
	char stockSeq[6];               //�����й������ε���
	char futureOptionCode[1];               //�����ɼǱ����ڵ�
	char productId[11];               //��ǰID
	char abbrStockCode[9];               //��������ڵ�
	char stockNameKor[80];               //�����
	char abbrStockNameKor[40];               //������
	char stockNameEng[80];               //���񿵹���
	char abbrStockNameEng[40];               //���񿵹����
	char productGroupID[3];               //����ǰ�׷�ID
	char listingDate[8];               //��������
	char discontinueListingDate[8];               //������������
	char stockClassCodeBasedSpread[1];               //��������������񱸺��ڵ�
	char finalSettlementTypeCode[1];               //������������ڵ�
	char price_limit_expansion_direction_code[1];               //��������Ȯ����������ڵ�
	char price_limit_final_step[3];               //�������������ܰ�
	char price_limit_1st_upper_limit_price[11];               //��������1�ܰ���Ѱ�
	char price_limit_2nd_upper_limit_price[11];               //��������2�ܰ���Ѱ�
	char price_limit_3rd_upper_limit_price[11];               //��������3�ܰ���Ѱ�
	char price_limit_1st_lower_limit_price[11];               //��������1�ܰ����Ѱ�
	char price_limit_2nd_lower_limit_price[11];               //��������2�ܰ����Ѱ�
	char price_limit_3rd_lower_limit_price[11];               //��������3�ܰ����Ѱ�
	char standardPrice[11];               //���ذ���
	char baseAssetId[3];               //�����ڻ�ID
	char exerciseTypeCode[1];               //�Ǹ���������ڵ�
	char spreadTypeCode[2];               //�������屸���ڵ�
	char spreadNdmStockCode[12];               //�������屸�������ڵ�1
	char spreadFdmStockCode[12];               //�������屸�������ڵ�2
	char lastTradeDate[8];               //�����ŷ�����
	char lastSettlementDate[8];               //������������
	char monthProductClassCode[3];               //�������Ϸù�ȣ
	char expireDate[8];               //��������
	char exercisePrice[18];               //��簡��
	char adjustmentClassCode[1];               //���������ڵ�
	char tradeUnit[22];               //�ŷ�����
	char tradeMultiplier[22];               //�ŷ��¼�
	char marketCreationClassCode[1];               //�������������ڵ�
	char listingTypeCode[1];               //���������ڵ�
	char atTheMoney[11];               //���
	char adjustmentReasonCode[2];               //���������ڵ�
	char baseAssetStockCode[12];               //�����ڻ������ڵ�
	char baseAssetClosePrice[11];               //�����ڻ�����
	char remainDateCount[8];               //�����ϼ�
	char adjustedStandardPrice[18];               //�������ذ���
	char standardPriceClassCode[2];               //���ذ��ݱ����ڵ�
	char standardPriceClassCodeForTrade[1];               //�Ÿſ���ذ��ݱ����ڵ�
	char ydayClosePriceAdjusted[18];               //������������
	char isConsultBulkTradeProduct[1];               //���Ǵ뷮�ŸŴ�󿩺�
	char ydayWarrentMoneyStandardPrice[23];               //�������űݱ��ذ���
	char ydayWarrentMoneyStandardPriceClassCode[2];               //���űݱ��ذ��ݱ����ڵ�
	char theoreticalPriceSettlement[16];               //�����̷а���
	char theoreticalPriceStandard[16];               //�����̷а���
	char ydaySettlementPrice[18];               //�������갡��
	char isTradeStop[1];               //�ŷ���������
	char upLimitPriceForOptionCircuitBreakers[11];               //����CIRCUIT_BREAKERS���Ѱ�
	char downLimitPriceForOptionCircuitBreakers[11];               //����CIRCUIT_BREAKERS���Ѱ�
	char exercisePriceForIncuiry[18];               //��ȸ����簡��
	char ATMClassCode[1];               //ATM�����ڵ�
	char isLastTradeDate[1];               //�����ŷ��Ͽ���
	char divValueForSettlementPrice[16];               //�����Ĺ�簡ġ
	char ydayClosePrice[11];               //��������
	char ydayClosePriceClassCode[1];               //�������������ڵ�
	char ydayOpenPrice[11];               //�������ڽð�
	char ydayHighPrice[11];               //�������ڰ�
	char ydayLowPrice[11];               //������������
	char firstTradeDate[8];               //���ʰŷ�����
	char ydayLastTradeTime[9];               //����ü��ð�
	char ydaySettlementPriceClassCode[2];               //���갡�ݱ����ڵ�
	char exactTheoryPriceSeparationRate[13];               //���갡���̷а��ݱ�����
	char ydayOpenInterest[12];               //���Ϲ̰�����������
	char ydayAskPriceQuotePriority1[11];               //���ϸŵ��켱ȣ������
	char ydayBidPriceQuotePriority1[11];               //���ϸż��켱ȣ������
	char intrinsicVolatility[11];               //���纯����
	char highestPriceWithinListing[11];               //�������ְ�
	char lowestPriceWithinListing[11];               //������������
	char highestPriceWithinYear[11];               //�����ְ�
	char lowestPriceWithinYear[11];               //����������
	char highestPriceDateWithinListing[8];               //�������ְ�����
	char lowestPriceDateWithinListing[8];               //����������������
	char highestPriceDateWithinYear[8];               //�����ְ�����
	char lowestPriceDateWithinYear[8];               //��������������
	char standardDayCountYear[8];               //���������ϼ�
	char standardTradeDayCountMonth[8];               //�����ŷ��ϼ�
	char standardTradeDayCountYear[8];               //�����ŷ��ϼ�
	char ydayTradeCount[15];               //����ü��Ǽ�
	char ydayTradeVolume[12];               //���ϴ����ŷ���
	char ydayTradeAmount[22];               //���ϴ����ŷ����
	char ydayConsultBulkTradeVolume[15];               //�����Ѵ����ŷ���
	char ydayConsultBulkTradeAmount[22];               //�����Ѵ����ŷ����
	char cdRate[11];               //CD�ݸ�
	char unsettledLimitContractCount[15];               //�ֽļ����̰����ѵ�����
	char productGroup[4];               //�����ڻ��ǰ��ID
	char productGroupOffsetRate[11];               //���ű�OFFSET����
	char limitPriceQuoteConditionClassCode[5];               //������ȣ����������ڵ�
	char marketPriceQuotePriceConditionClassCode[5];               //���尡ȣ����������ڵ�
	char conditionalLimitPriceQuotePriceConditionClassCode[5];               //���Ǻ�������ȣ����������ڵ�
	char advantageousLimitPriceQuotePriceConditionClassCode[5];               //������������ȣ����������ڵ�
	char EFPTradingItem[1];               //EFP�ŷ���󿩺�
	char FLEXTradingItem[1];               //FLEX�ŷ���󿩺�
	char previousDayEFPTradingVolume[12];               //EFPü�����
	char previousDayEFPTradingPrice[22];               //EFP�ŷ����
	char isHoliday[1];               //���忩��
	char isRealTimePriceLimit[1];               //�����������ѿ���
	char realTimeUpperLimitPriceRange[11];               //�������Ѱ�����
	char realTimeLowerLimitPriceRange[11];               //�������Ѱ�����
	char underlyingAssetMarketID[3];               //�����ڻ����ID
	char upperLimitQuantity[23];               //���Ѽ���
	char lowerLimitQuantity[23];               //���Ѽ���
	char upperLimitQuantityForBlockTrade[23];               //���Ǵ뷮�ŸŻ��Ѽ���
	char lowerLimitQuantityForBlockTrade[23];               //���Ǵ뷮�Ÿ����Ѽ���
	char standardProductID[11];            //���ػ�ǰID
	char subProductID[11];                 //�λ�ǰID  
	char standardProductStockCount[6];     //�λ�ǰID
	char subProductStockCount[6];          //�λ�ǰ�����
	char tradeDefineWeek[2];               //������
	char isSuspendedStocks[1];               //�޸鿩��
	char designationDateForSuspendedStocks[8];               //�޸���������
	char endOfText[1];               //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INFO_RECORD_SIZE = sizeof(ExturePlusKospi200OptionStockInfoRecord);
#endif

#if(1)
//�Ļ� ü��//F1���� : �����ŷ����� ���� (����, �ŷ���� �� ����)//(A301F)
//�Ļ� ü��//�Ļ� ü��
//F1���� : �����ŷ����� ���� (����, �ŷ���� �� ����)
//(�Ļ�A) DRV : A301F, A303F
class ExturePlusKospi200OptionTradeRecord
{
    public:
	char dataClass[2];            //�����ͱ��а�
	char infoMarketClass[3];            //�������а�
	char distributeStockIndex[8];            //�����й��Ϸù�ȣ
	char boardID[2];            //����ID
	char sessionID[2];            //����ID
	char stockCode[12];            //�����ڵ�
	char stockSeq[6];            //�����й������ε���
	char tradeTime[12];            //�Ÿ�ó���ð�
	char currentPrice[9];            //ü�ᰡ��
	char tradeVolume[9];            //�ŷ���
	char ndmInterestPrice[9];            //�ٿ���ü�ᰡ��
	char fdmInterestPrice[9];            //������ü�ᰡ��
	char openPrice[9];            //�ð�
	char highPrice[9];            //��
	char lowPrice[9];            //����
	char lastPrice[9];            //��������
	char accmTradeVolume[12];            //�����ŷ���
	char accmTradeAmount[22];            //�����ŷ����
	char lastQuoteTypeAskBid[1];            //�����ŵ��ż������ڵ�
	char realTimeUpperLimitPrice[9];            //�������Ѱ�
	char realTimeLowerLimitPrice[9];            //�������Ѱ�
	char endOfText[1];            //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_TRADE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionTradeRecord);
#endif

#if(1)
//KOSPI200���������ü�Recovery ������//�Ļ� �ü� Snapshot(�켱ȣ�� 5�ܰ�)
//�Ļ� �ü� Snapshot (�켱ȣ�� 5�ܰ�)
//�Ļ� �ü� Snapshot (�켱ȣ�� 5�ܰ�)
//(�Ļ�A) DRV : B201F, B203F
class ExturePlusKospi200OptionRecoveryQuoteRecord
{
    public:
	char askPrice[9];             //�ŵ� �켱ȣ������
	char bidPrice[9];             //�ż� �켱ȣ������
	char askVolume[9];            //�ŵ� �켱ȣ���ܷ�
	char bidVolume[9];            //�ż� �켱ȣ���ܷ�
	char askCount[5];             //�ŵ� �켱ȣ���ֹ��Ǽ�
	char bidCount[5];             //�ż� �켱ȣ���ֹ��Ǽ�
};
const int EXTURE_PLUS_KOSPI_200_OPTION_RECOVERY_QUOTE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionRecoveryQuoteRecord);

class ExturePlusKospi200OptionRecoveryRecord
{
    public:
	char dataClass[2];           //�����ͱ��а�
	char infoMarketClass[3];           //�������а�
	char boardID[2];           //����ID
	char sessionID[2];           //����ID
	char stockCode[12];           //�����ڵ�
	char stockSeq[6];           //�����й������ε���
	char realTimeUpperLimitPrice[9];           //���Ѱ�
	char realTimeLowerLimitPrice[9];           //���Ѱ�
	char currentPrice[9];           //ü�ᰡ��
	char ndmInterestPrice[9];           //�ٿ���ü�ᰡ��
	char fdmInterestPrice[9];           //������ü�ᰡ��
	char openPrice[9];           //�ð�
	char highPrice[9];           //��
	char lowPrice[9];           //����
	char openInterestVolume[10];           //�̰�����������
	char accmTradeVolume[12];           //�����ŷ���
	char accmTradeAmount[22];           //�����ŷ����
	char lastQuoteTypeAskBid[1];           //�����ŵ��ż������ڵ�
	ExturePlusKospi200OptionRecoveryQuoteRecord quoteRecord[5];
	char askTotalVolume[9];            //�ŵ�ȣ�����ܷ�
	char bidTotalVolume[9];            //�ż�ȣ�����ܷ�
	char askCountValidQuote[5];            //�ŵ�ȣ����ȿ�Ǽ�
	char bidCountValidQuote[5];            //�ż�ȣ����ȿ�Ǽ�
	char estimatedTradingPrice[9];            //����ü�ᰡ
	char endOfText[1];            //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_RECOVERY_RECORD_SIZE = sizeof(ExturePlusKospi200OptionRecoveryRecord);
#endif

#if(1)
//KOSPI200�������� �켱ȣ��//�Ļ� �켱ȣ�� (�켱ȣ�� 5�ܰ�)(B601F)
//�Ļ� �켱ȣ�� (�켱ȣ�� 5�ܰ�)//�Ļ� �켱ȣ�� (�켱ȣ�� 5�ܰ�)
//(�Ļ�A) DRV : B601F, B603F
class ExturePlusKospi200OptionPriorityQuoteRecord
{
    public:
	char dataClass[2];        //�����ͱ��а�
	char infoMarketClass[3];        //�������а�
	char distributeStockIndex[8];        //�����й��Ϸù�ȣ
	char boardID[2];        //����ID
	char sessionID[2];        //����ID
	char stockCode[12];        //�����ڵ�
	char stockSeq[6];        //�����й������ε���
	char quoteAcceptTime[12];        //�Ÿ�ó���ð�
	char askPricePriority1[9];        //�ŵ�1�ܰ�켱ȣ������
	char bidPricePriority1[9];        //�ż�1�ܰ�켱ȣ������
	char askVolumePriority1[9];        //�ŵ�1�ܰ�켱ȣ���ܷ�
	char bidVolumePriority1[9];        //�ż�1�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority1[5];        //�ŵ�1�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority1[5];        //�ż�1�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority2[9];        //�ŵ�2�ܰ�켱ȣ������
	char bidPricePriority2[9];        //�ż�2�ܰ�켱ȣ������
	char askVolumePriority2[9];        //�ŵ�2�ܰ�켱ȣ���ܷ�
	char bidVolumePriority2[9];        //�ż�2�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority2[5];        //�ŵ�2�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority2[5];        //�ż�2�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority3[9];        //�ŵ�3�ܰ�켱ȣ������
	char bidPricePriority3[9];        //�ż�3�ܰ�켱ȣ������
	char askVolumePriority3[9];        //�ŵ�3�ܰ�켱ȣ���ܷ�
	char bidVolumePriority3[9];        //�ż�3�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority3[5];        //�ŵ�3�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority3[5];        //�ż�3�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority4[9];        //�ŵ�4�ܰ�켱ȣ������
	char bidPricePriority4[9];        //�ż�4�ܰ�켱ȣ������
	char askVolumePriority4[9];        //�ŵ�4�ܰ�켱ȣ���ܷ�
	char bidVolumePriority4[9];        //�ż�4�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority4[5];        //�ŵ�4�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority4[5];        //�ż�4�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority5[9];        //�ŵ�5�ܰ�켱ȣ������
	char bidPricePriority5[9];        //�ż�5�ܰ�켱ȣ������
	char askVolumePriority5[9];        //�ŵ�5�ܰ�켱ȣ���ܷ�
	char bidVolumePriority5[9];        //�ż�5�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority5[5];        //�ŵ�5�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority5[5];        //�ż�5�ܰ�켱ȣ���ֹ��Ǽ�
	char askTotalQuoteVolume[9];        //�ŵ�ȣ�����ܷ�
	char bidTotalQuoteVolume[9];        //�ż�ȣ�����ܷ�
	char askCountValidQuote[5];        //�ŵ�ȣ����ȿ�Ǽ�
	char bidCountValidQuote[5];        //�ż�ȣ����ȿ�Ǽ�
	char estimatedTradingPrice[9];        //����ü�ᰡ
	char endOfText[1];        //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_PRIORITY_QUOTE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionPriorityQuoteRecord);
#endif

#if(1)
//KOSPI200�������� ü��_�켱ȣ��	G7014
//�Ļ� ü�� + �켱ȣ�� (�켱ȣ�� 5�ܰ�)
//�Ļ� ü�� + �켱ȣ��(�켱ȣ�� 5�ܰ�)
//(�Ļ�A) DRV : G701F, G703F
class ExturePlusKospi200OptionTradePriorityQuoteRecord
{
    public:
	char dataClass[2];            //�����ͱ��а�
	char infoMarketClass[3];            //�������а�
	char distributeStockIndex[8];            //�����й��Ϸù�ȣ
	char boardID[2];            //����ID
	char sessionID[2];            //����ID
	char stockCode[12];            //�����ڵ�
	char stockSeq[6];            //�����й������ε���
	char tradeTime[12];            //�Ÿ�ó���ð�
	char currentPrice[9];            //ü�ᰡ��
	char tradeVolume[9];            //�ŷ���
	char ndmInterestPrice[9];            //�ٿ���ü�ᰡ��
	char fdmInterestPrice[9];            //������ü�ᰡ��
	char openPrice[9];            //�ð�
	char highPrice[9];            //��
	char lowPrice[9];            //����
	char lastPrice[9];            //��������
	char accmTradeVolume[12];            //�����ŷ���
	char accmTradeAmount[22];            //�����ŷ����
	char lastQuoteTypeAskBid[1];            //�����ŵ��ż������ڵ�
	char realTimeUpperLimitPrice[9];            //�������Ѱ�
	char realTimeLowerLimitPrice[9];            //�������Ѱ�
	char askPricePriority1[9];            //�ŵ�1�ܰ�켱ȣ������
	char bidPricePriority1[9];            //�ż�1�ܰ�켱ȣ������
	char askVolumePriority1[9];            //�ŵ�1�ܰ�켱ȣ���ܷ�
	char bidVolumePriority1[9];            //�ż�1�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority1[5];            //�ŵ�1�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority1[5];            //�ż�1�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority2[9];            //�ŵ�2�ܰ�켱ȣ������
	char bidPricePriority2[9];            //�ż�2�ܰ�켱ȣ������
	char askVolumePriority2[9];            //�ŵ�2�ܰ�켱ȣ���ܷ�
	char bidVolumePriority2[9];            //�ż�2�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority2[5];            //�ŵ�2�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority2[5];            //�ż�2�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority3[9];            //�ŵ�3�ܰ�켱ȣ������
	char bidPricePriority3[9];            //�ż�3�ܰ�켱ȣ������
	char askVolumePriority3[9];            //�ŵ�3�ܰ�켱ȣ���ܷ�
	char bidVolumePriority3[9];            //�ż�3�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority3[5];            //�ŵ�3�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority3[5];            //�ż�3�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority4[9];            //�ŵ�4�ܰ�켱ȣ������
	char bidPricePriority4[9];            //�ż�4�ܰ�켱ȣ������
	char askVolumePriority4[9];            //�ŵ�4�ܰ�켱ȣ���ܷ�
	char bidVolumePriority4[9];            //�ż�4�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority4[5];            //�ŵ�4�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority4[5];            //�ż�4�ܰ�켱ȣ���ֹ��Ǽ�
	char askPricePriority5[9];            //�ŵ�5�ܰ�켱ȣ������
	char bidPricePriority5[9];            //�ż�5�ܰ�켱ȣ������
	char askVolumePriority5[9];            //�ŵ�5�ܰ�켱ȣ���ܷ�
	char bidVolumePriority5[9];            //�ż�5�ܰ�켱ȣ���ܷ�
	char askCountQuotePriority5[5];            //�ŵ�5�ܰ�켱ȣ���ֹ��Ǽ�
	char bidCountQuotePriority5[5];            //�ż�5�ܰ�켱ȣ���ֹ��Ǽ�
	char askTotalQuoteVolume[9];            //�ŵ�ȣ�����ܷ�
	char bidTotalQuoteVolume[9];            //�ż�ȣ�����ܷ�
	char askCountValidQuote[5];            //�ŵ�ȣ����ȿ�Ǽ�
	char bidCountValidQuote[5];            //�ż�ȣ����ȿ�Ǽ�
	char endOfText[1];            //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_TRADE_PRIORITY_QUOTE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionTradePriorityQuoteRecord);
#endif

#if(1)
//KOSPI200�������� ������ ������//�Ļ� ��ǰ�� �����ں� ���
//�Ļ� ��ǰ�� �����ں� ���//�Ļ� ��ǰ�� �����ں� ���
//(���� ���� ���常 ����)
//(�Ļ�A) DRV : H101F, H103F
class ExturePlusKospi200OptionInvestorRecord
{
    public:
	char dataClass[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char createDate[8];                       //��������
	char createTime[6];                       //������ð�
	char dataType[2];                       //�����ڰŷ���Ȳ�۽ŵ����ͱ����ڵ�
	char productId[11];                       //��ǰID
	char optionClass[1];                            //�ɼǱ���
	char investorType[4];                       //�����ڱ����ڵ�
	char bidAgreementVolume[10];                       //�ż��ŷ���
	char askAgreementVolume[10];                       //�ŵ��ŷ���
	char bidAgreementAmount[22];                       //�ż��ŷ����
	char askAgreementAmount[22];                       //�ŵ��ŷ����
	char bidAgreementVolumeBySpread[10];                       //��������ż��ŷ���
	char askAgreementVolumeBySpread[10];                       //��������ŵ��ŷ���
	char bidAgreementAmountBySpread[22];                       //��������ż��ŷ����
	char askAgreementAmountBySpread[22];                       //��������ŵ��ŷ����
	char endOfText[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INVESTOR_RECORD_SIZE = sizeof(ExturePlusKospi200OptionInvestorRecord);
#endif

#if(1)
//KOSPI200�������� �̰����������� ������//�Ļ����� �̰����������� ������
//�Ļ����� �̰����������� ������
//�Ļ����� �̰����������� ������
//����Ȯ��ġ : �尳����
//���� : 10���ֱ�
//����Ȯ��ġ : ��������
//(�Ļ�A) DRV : H201F, H203F
class ExturePlusKospi200OptionOpenInterestVolumeRecord
{
    public:
	char dataClass[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char stockCode[12];                       //�����ڵ�
	char stockSeq[6];                       //�����й������ε���
	char openInterestClass[2];                       //�̰��������۽ŵ����ͱ����ڵ�
	char tradeDate[8];                       //�ŷ�����
	char openInterestVolume[10];                       //�̰�����������
	char endOfText[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_OPEN_INTEREST_VOLUME_RECORD_SIZE = sizeof(ExturePlusKospi200OptionOpenInterestVolumeRecord);
#endif

#if(1)
//KOSPI200�������� ���갡�� ������//�������� ���갡�� ������
//�������� ���갡�� ������	��������
//���갡�� ������	
//��������
//(�Ļ�A) DRV : H301F, H304F
class ExturePlusKospi200OptionAdjustedPriceRecord
{
    public:
	char dataClass[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char stockCode[12];                       //�����ڵ�
	char stockSeq[6];                       //�����й������ε���
	char adjustedPrice[18];                       //���갡��
	char adjustedPriceClass[2];                       //���갡�ݱ����ڵ�
	char lastSettlementPrice[18];                       //������������
	char lastSettlementPriceClass[1];                       //�����������ݱ����ڵ�
	char endOfText[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_ADJUSTED_PRICE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionAdjustedPriceRecord);
#endif

#if(1)
//�ɼ����� �Ÿ����ű� ���ذ� ������
//�ɼ����� �Ÿ����ű� ���ذ� ������
//��������
//(�Ļ�A) DRV : ID03F, ID05F, ID07F, ID12F, ID15F, ID16F
class ExturePlusKospi200OptionTradeMarginStandardPriceRecord
{
    public:

        char dataClass[2];                              //1 	�����ͱ��а�	0	String	2                  
        char infoMarketClass[3];                        //2 	�������а�	0	String	3                      
        char stockCode[12];                             //3 	�����ڵ�	0	String	12                     
        char stockSeq[4];                               //4 	�����й������ε���	0	Int	6                  
        char marginStdPrice[18];                        //5 	���űݱ��ذ���	8	FLOAT128	18             
        char marginStdPriceClass[2];                    //6 	���űݱ��ذ��ݱ����ڵ�	0	String	2          
        char optionExercisePrice[18];                   //7 	�ɼǱǸ�����������	8	FLOAT128	18     
        char optionExercisePriceClass[1];               //8 	�ɼǱǸ����������ݱ����ڵ�	0	String	1  
        char endOfText[1];                              //9 	�����й�޼�������Ű����	0	String	1      
};
const int EXTURE_PLUS_KOSPI_200_OPTION_TRADE_MARGIN_STANDARD_PRICE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionTradeMarginStandardPriceRecord);
#endif

#if(1)
//KOSPI200�������� �������ٰ���//�������ٰ���
//�������ٰ���//�������� �̺�Ʈ ���� �߻��� ����
//�ǽð�
//(����A) STK : M401S
//(����C) STK : M402S, M403S, M404S
//(����B) KSQ : M401Q
//(����B) KNX : M401X
//(ä��A) BND : M401B
//(ä��A) SMB : M401M
//(ä��A) KTS : M401K
//(ä��A) RPO : M401R
//(�Ļ�A) DRV : M401F, M403F
class ExturePlusKospi200OptionMarketOperationScheduleDisclosureRecord
{
    public:
	char data_type[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char market_operation_product_group_id[3];                       //����ǰ�׷�ID
	char board_id[2];                       //����ID
	char board_event_id[3];                       //�����̺�ƮID
	char board_event_start_time[9];                       //�����̺�Ʈ���۽ð�
	char board_event_group_code[5];                       //�����̺�Ʈ���뱺�ڵ�
	char session_start_end_code[2];                       //���ǰ��������ڵ�
	char session_id[2];                       //����ID
	char issue_code[12];                       //�����ڵ�
	char listedCompanyStockCode [12];                       //����������ڵ�
	char derivatives_id[11];                       //��ǰID
	char uspensionTransactionReasonCode [3];                       //�ŷ����������ڵ�
	char uspensionTransactionOccurCode [1];                       //�ŷ������߻������ڵ�
	char step_applied[2];                       //����ܰ�
	char price_expansion_trigger_code_for_base_issue[1];                       //�������񰡰�����Ȯ��߻��ڵ�
	char price_expansion_expected_time[9];                       //��������Ȯ�뿹���ð�
	char end_of_text[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionMarketOperationScheduleDisclosureRecord);
#endif

#if(1)
//KOSPI200�������� �������	KOSPI200�������� �������//�������
//�������
//���ϰ�ü���� ��/���Ѱ��� �����Ǵ� ��� ��/���Ѱ� �ż�, �ŵ��ֹ��� ���� �������� ������ ���������� ����Ͽ� ü���Ű�� ���
//�ǽð�
//(����A) STK : O601S
//(����C) STK : O602S, O603S, O604S
//(����B) KSQ : O601Q
//(����B) KNX : O601X
//(�Ļ�A) DRV : O601F, O603F
class ExturePlusKospi200OptionQuantityAllocationRecord
{
    public:
	char dataType[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char distributeStockIndex[8];                       //�����й��Ϸù�ȣ
	char boardID[2];                       //����ID
	char issueCode[12];                       //�����ڵ�
	char issueSeqence[6];                       //�����й������ε���
	char allocationStartEnd[1];                       //������뱸���ڵ�
	char allocationTypeCode[1];                       //���ó�������ڵ�
	char timeForAllocationEnd[9];                       //��������ð�
	char endOfText[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_QUANTITY_ALLOCATION_RECORD_SIZE = sizeof(ExturePlusKospi200OptionQuantityAllocationRecord);
#endif

#if(1)
//K200����_�ǽð������Ѱ� ���������//�Ļ� ���������Ѱ� ���� �� ����(Q201F)
//�Ļ� ���������Ѱ� ���� �� ����
//�Ļ� ���������Ѱ� ���� �� ����
//�ǽð�
//(�Ļ�A) DRV : Q201F, Q203F
class ExturePlusKospi200OptionRealTimeUpperLowerLimitPriceRecord
{
    public:
	char dataType[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char distributeStockIndex[8];                       //�����й��Ϸù�ȣ
	char boardID[2];                       //����ID
	char issueCode[12];                       //�����ڵ�
	char issueSeqence[6];                       //�����й������ε���
	char processingTime[12];                       //�Ÿ�ó���ð�
	char realTimePriceLimit[1];                       //�����������Ѽ����ڵ�
	char realTimeUpperLimitPrice[9];                       //�������Ѱ�
	char realTimeLowerLimitPrice[9];                       //�������Ѱ�
	char endOfText[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionRealTimeUpperLowerLimitPriceRecord);
#endif

#if(1)
//K200����_����������Ȯ��ߵ�//�Ļ� ����������Ȯ��ߵ�
//�Ļ� ����������Ȯ��ߵ�//����������Ȯ�� �ߵ��� ����
//(�Ļ�A) DRV : V101F, V103F
class ExturePlusKospi200OptionPriceLimitRangeExpansionTriggerRecord
{
    public:
	char data_type[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char distributeStockIndex[8];                       //�����й��Ϸù�ȣ
	char board_id[2];                       //����ID
	char issue_code[12];                       //�����ڵ�
	char issue_seq[6];                       //�����й������ε���
	char price_expansion_time[9];                       //����Ȯ��ð�
	char the_upper_step_of_price_limit_expansion[2];                       //��������Ȯ����Ѵܰ�
	char the_lower_step_of_price_limit_expansion[2];                       //��������Ȯ�����Ѵܰ�
	char upper_limit_price[9];                       //���Ѱ�
	char lower_limit_price[9];                       //���Ѱ�
	char end_of_text[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI200_OPTION_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE = sizeof(ExturePlusKospi200OptionPriceLimitRangeExpansionTriggerRecord);
#endif

#if(1)
// (�Ļ�A) DRV : A601F, A602F, A603F, A604F, A605F, A606F, A607F, A608F, A609F, A610F, A611F, A612F, A613F, A615F, A616F
// �Ļ� ���񸶰�
class ExturePlusKospi200OptionStockCloseRecord
{
    public:
        char dataClass[2];                              // �����ͱ��а�
        char infoMarketClass[3];                        // �������а�
		char distributeStockIndex[8];                   // �����й��Ϸù�ȣ
		char boardID[2];                                // ����ID
        char stockCode[12];                             // �����ڵ�		
		char stockSeq[6];					// �����й������ε���
		char closePrice[9];                             // ���񸶰�����
		char closePriceTypeCode[1];                     // ���������ڵ�
        char accmTradeVolume[12];                       // �����ŷ���
        char accmTradeAmount[22];                       // �����ŷ����
		char endOfText[1];                              // �����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_CLOSE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionStockCloseRecord);
#endif

#if(1)
//�ɼ����� �ΰ��� ������
//�ɼ����� �ΰ��� ������
//���� : 10���ֱ�
//(�Ļ�A) DRV : N703F, N705F, N707F, N712F, N715F, N716F
class ExturePlusKospi200OptionSensitivityRecord
{
	public:
	char  dataType[2];                        //�����ͱ��а�
	char  infoMarketClass[3];                        //�������а�
	char  issueCode[12];                        //�����ڵ�
	char  seq[6];                        //�����й������ε���
	char  producedDate[8];                        //��������
	char  producedTime[9];                        //����ð�
	char  dataCategory[1];                        //���纯�������ⱸ���ڵ�
	char  underlyingAssetId[3];                        //�����ڻ�ID
	char  sensitivityDelta[20];                        //�ΰ�����Ÿ
	char  sensitivityTheta[20];                        //�ΰ�����Ÿ
	char  sensitivityVega[20];                        //�ΰ�������
	char  sensitivityGamma[20];                        //�ΰ�������
	char  sensitivityRho[20];                        //�ΰ�����
	char  endOfText[1];                        //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_SENSITIVITY_RECORD_SIZE = sizeof(ExturePlusKospi200OptionSensitivityRecord);
#endif

#if(1)
//K200����_�尳�������ǰŷ�//Eurex���� �尳���� ���ǰŷ�
//Eurex���� �尳���� ���ǰŷ�
//Eurex���� �尳���� ���ǰŷ�
//09:00 1ȸ	
//(�Ļ�A) DRV : M701F, M703F
class ExturePlusKospi200OptionPreMarketNegotiatedTradeRecord
{
    public:
	char data_type[2];                       //�����ͱ��а�
	char infoMarketClass[3];                       //�������а�
	char stockCode[12];                       //�����ڵ�
	char stockSeq[6];                       //�����й������ε���
	char tradePrice[9];                       //ü�ᰡ��
	char tradeVolume[9];                       //�ŷ���
	char end_of_text[1];                       //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_PRE_MARKET_NEGOTIATED_TRADE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionPreMarketNegotiatedTradeRecord);
#endif

#if(1)
//��TS
//�� Trading Session �̺�Ʈ �߻��� ���� ����
//�ǽð�
//(����A) STK : A701S
//(����C) STK : A702S, A703S, A704S
//(����B) KSQ : A701Q
//(����B) KNX : A701X
//(�Ļ�A) DRV : A701F, A703F
class ExturePlusKospi200OptionMarketOperationRecord
{
    public:
	char dataCategory[2];                           //�����ͱ��а�
	char infoMarketClass[3];                        //�������а�
	char distributeStockIndex[8];                   //�����й��Ϸù�ȣ
	char boardID[2];                                //����ID
	char sessionID[2];                              //����ID
	char stockCode[12];                             //�����ڵ�
	char stockSeq[6];                               //�����й������ε���
	char tradeProcessTime[12];                      //�Ÿ�ó���ð�
	char boardEventID[3];                           //�����̺�ƮID
	char boardEventBeginTime[9];                    //�����̺�Ʈ���۽ð�
	char boardEventApplyCode[5];                    //�����̺�Ʈ���뱺�ڵ�
	char tradingHaltReasonCode[3];                  //�ŷ����������ڵ�
	char endOfText[1];                              //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_RECORD_SIZE = sizeof(ExturePlusKospi200OptionMarketOperationRecord);
#endif

#pragma pack()

#endif // __EXTURE_PLUS_KOSPI_200_OPTION_H__
