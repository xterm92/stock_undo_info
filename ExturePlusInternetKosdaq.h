#ifndef __EXTURE_PLUS_KOSDAQ_H__
#define __EXTURE_PLUS_KOSDAQ_H__

/*
 12345678901234567890123456789012345678901234567890123456789012345678901234567890
 */

#pragma pack(1)

#if(1)
//���� ��������
//(����A) STK : A001S
//(����C) STK :  A002S, A003S, A004S
//(����B) KSQ : A001Q
//(����B) KNX : A001X
//(�ֽ��Ļ�) STK : A001S
//(�ֽ��Ļ�) KSQ : A001Q
class ExturePlusKosdaqMaster
{
    public:
	char dataClass[2];                  //�����й� �����͸� �ĺ��ϴ� ���� �ڵ尪
	char infoMarketClass[3];            //�����й迡�� �й��ϴ� ������ ���� �ڵ尪
	char distributeStockIndex[8];		//�����й迡�� �ο��ϴ� �Ϸù�ȣ
										//�ü� : ���� ���庰 �ο� (�� ��뷮 ���񽺿��� ����)
										//�������� :  �������а��� �ο�
										//��Ÿ : �����ͱ��а��� �ο�
	char distributeTotalStockIndex[6];         //�����й��������ε���
	char sendDate[8];         //��������
	char stockCode[12];         //�����ڵ�
	char stockSeq[6];         //�����й������ε���
	char abbrStockCode[9];         //��������ڵ�
	char abbrStockNameKor[40];         //������
	char abbrStockNameEng[40];         //���񿵹����
	char infoDivisionGroupNo[5];         //�����й�׷��ȣ
	char MarketProductGroupID[3];         //����ǰ�׷�ID
	char stockGroupID[2];         //���Ǳ׷�ID
	char isUnitTrade[1];         //�����Ÿ�ü�Ῡ��
	char exClassCode[2];         //�������ڵ�
	char faceValueChangeClassCode[2];         //�׸鰡���汸���ڵ�
	char isOpenPriceBecomeStdPrice[1];         //�ð����ذ������񿩺�
	char isRevaluationStockReason[2];         //������������ڵ�
	char isStandardPriceChangeStock[1];         //���ذ��ݺ������񿩺�
	char randomEndTriggerConditionCode[1];         //��������ߵ������ڵ�
	char isMarketAlarmDangerNotice[1];         //����溸���迹����
	char marketAlarmClassCode[2];         //����溸�����ڵ�
	char isCorporateGovernanceFine[1];         //���豸���췮����
	char isManagementStock[1];         //�������񿩺�
	char isInsincerityPublicNewsAppoint[1];         //�Ҽ��ǰ��ÿ���
	char isBackDoorListing[1];         //��ȸ���忩��
	char isTradeStop[1];         //�ŷ���������
	char standardIndustryCode[10];         //����ID
	char SmallMediumEnterprisesIs[1];         //�߼ұ������
	char isCorporateGovernanceIndexStock[1];         //�ҼӺα����ڵ�
	char investOrganClassCode[1];         //���ڱⱸ�����ڵ�
	char standardPrice[11];         //���ذ���
	char ydayClosePriceClassCode[1];         //�������������ڵ�
	char ydayClosePrice[11];         //��������
	char ydayAccmVolume[12];         //���ϴ����ŷ���
	char ydayAccmAmount[22];         //���ϴ����ŷ����
	char upLimitPrice[11];         //���Ѱ�
	char downLimitPrice[11];         //���Ѱ�
	char substitutePrice[11];         //��밡��
	char faceValue[11];         //�׸鰡
	char issuePrice[11];         //���డ��
	char listingDate[8];         //��������
	char listingSize[16];         //�����ֽļ�
	char isClearanceTrade[1];         //�����Ÿſ���
	char listingStartDate[8];         //������������
	char listingEndDAte[8];         //������������
	char excercisePeriodBeginDate[8];         //���Ⱓ��������
	char excercisePeriodEndDate[8];         //�Ǹ����Ⱓ��������
	char ELWBWExcercisePrice[13];         //ELW�����μ���������簡��
	char capital[22];         //�ں���
	char CreditOrderPossibleIs[1];         //�ſ��ֹ����ɿ���
	char LimitQuotePriceConditionClassCode[5];         //������ȣ����������ڵ�
	char MarketQuotePriceConditionClassCode[5];         //���尡ȣ����������ڵ�
	char ConditionalLimitQuotePriceConditionClassCode[5];         //���Ǻ�������ȣ����������ڵ�
	char BestLimitQuotePriceConditionClassCode[5];         //������������ȣ����������ڵ�
	char topPriorityQuotePriceConditionClassCode[5];         //�ֿ켱������ȣ����������ڵ�
	char capitalIncreaseClassCode[2];         //���ڱ����ڵ�
	char preferredStockClassCode[1];         //�����ֱǱ����ڵ�
	char isNationalStock[1];         //�����ֿ���
	char evaluatePrice[11];         //�򰡰���
	char lowestQuotePrice[11];         //����ȣ������
	char highestQuotePrice[11];         //�ְ�ȣ������
	char MainBaordVolumeUnit[11];         //���κ����������
	char JangAfterOvertimeVolumeUnit[11];         //�������Ľð��ܼ�������
	char REITsClassCode[1];         //���������ڵ�
	char objectSovereign[12];         //�����ֱ������ڵ�
	char CurrencyISOCode[3];         //��ȭISO�ڵ�
	char NationalCode[3];         //�����ڵ�
	char BelfastPossibleIs[1];         //�����������ɿ���
	char OvertimeTradePossibleIs[1];         //�ð��ܸŸŰ��ɿ���
	char isBeforeMarketOvertimeMarketClosePrice[1];         //�尳�����ð����������ɿ���
	char isBeforeMarketOvertimeMarketBlockTradingPossibility[1];         //�尳�����ð��ܴ뷮�ŸŰ��ɿ���
	char isBeforeMarketOvertimeMarketBasketPossibility[1];         //�尳�����ð��ܹٽ��ϰ��ɿ���
	char isEstimatedTradePriceOpen[1];         //����ü�ᰡ��������
	char isShortStockSellingPossibility[1];         //���ŵ����ɿ���
	char ETFFollowingEarningRateMultiple[13];         //�������ͷ����
	char REGSIS[1];         //REGS����
	char SPACIS[1];         //SPAC����
	char taxImportedTypeCode[1];         //���������ڵ�
	char rateSubstitutePriceCalcurated[13];         //��밡�ݻ�������
	char isStockInvestmentWarningAttention[1];         //��������ȯ�����񿩺�
	char delistingDate[8];         //������������
	char shortTermFeverishInstrumentTypeCode[1];         //�ܱ�������񱸺��ڵ�
	char ETFReplicationMethodTypeCode[1];         //ETF������������ڵ�
	char expirationDate[8];         //��������
	char distributeTypeCode[2];         //�й�������ڵ�
	char expirationRedemptionPriceDecisionStartDate[8];         //�����ȯ���ݰ�����������
	char expirationRedemptionPriceDecisionEndDate[8];         //�����ȯ���ݰ�����������
	char etpProductTypeCode[1];         //ETP��ǰ�����ڵ�
	char indexCalculationInstitution_code[2];         //�����������ڵ�
	char indexMarket_classification_id[6];         //��������з�ID
	char indexSeqNumber[3];         //�����Ϸù�ȣ
	char trackingIndexLeverageInverseTypeCode[2];         //�����������������ι��������ڵ�
	char referenceIndexLeverageInverseTypeCode[2];         //�����������������ι��������ڵ�
	char indexAssetClassificationId1[6];         //�����ڻ�з�ID1
	char indexAssetClassificationId2[6];         //�����ڻ�з�ID2
	char RecommendTestimonialNo[5];         //�����ּ���ȸ����ȣ
	char lpOrderPossibility[1];         //LP�ֹ����ɿ���
	char lowLiquidity[1];         //������������
	char abnormalRise[1];         //�̻�޵��
	char upperLimitQuantity[23];         //���Ѽ���
	char isInvestmentPrecautionIssue[1];         //�����������񿩺�
	char TradingVolumeInsufficientIs[1];         //�����ֽļ��������񿩺�
	char isSPAC_merger[1];         //SPAC�Ҹ��պ�����
	char segment_code[1];         //���׸�Ʈ�����ڵ�
	char endOfText[1];         //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_MASTER_SIZE = sizeof(ExturePlusKosdaqMaster);

//���� ���� �� ������ǥ
//(����A) STK : CA01S
//(����B) KSQ : CA01Q
//(�ֽ��Ļ�) STK : CA01S
//(�ֽ��Ļ�) KSQ : CA01Q
class ExturePlusKosdaqJisuMaster
{
    public:
	char dataClass[2];                  //�����й� �����͸� �ĺ��ϴ� ���� �ڵ尪
	char infoMarketClass[3];            //�����й迡�� �й��ϴ� ������ ���� �ڵ尪
	char distributeStockIndex[8];		//�����й迡�� �ο��ϴ� �Ϸù�ȣ
										//�ü� : ���� ���庰 �ο� (�� ��뷮 ���񽺿��� ����)
										//�������� :  �������а��� �ο�
										//��Ÿ : �����ͱ��а��� �ο�
	char stockCode[12];         //�����ڵ�
	char stockSeq[6];         //�Ϸù�ȣ
	char stockGroupID[2];         //���Ǳ׷�ID
	char isEPSCalcExclusion[1];         //�ִ�����ͻ������ܿ���
	char EPS[22];         //�ִ������
	char isloss[1];         //��տ���
	char PER[13];         //�ְ�������
	char isBPSCalcExclusion[1];         //�ִ���ڻ갡ġ�������ܿ���
	char BPS[22];         //�ִ���ڻ갡ġ
	char PBR[13];         //�ִ���ڻ����
	char isDividendPriceExclusion[1];         //�ִ���ݻ������ܿ���
	char dividendPrice[22];         //�ִ���ݾ�
	char dividendEarningRate[13];         //��������
	char listPriceSizeCode[1];         //�ð��ѾױԸ��ڵ�
	char isManufactureIndustry[1];         //����������
	char indexBusinessTypeLarge[6];         //����������з��ڵ�
	char indexBusinessTypeMedium[6];         //���������ߺз��ڵ�
	char indexBusinessTypeSmall[6];         //���������Һз��ڵ�
	char businessTypeKOSPI200[1];         //KOSPI200���;���
	char businessTypeKOSPI200_2[1];         //KOSPI200Ŀ�´����̼Ǽ��񽺼��� �ߺ�����
	char isKOSPI[1];         //KOSPI�������񿩺�
	char investOrganClassCode[1];         //KOSDAQ�������񿩺�
	char isKOSPI100[1];         //KOSPI100����
	char isKOSPI50[1];         //KOSPI50����
	char kosdaq150IndexIssue[1];         //KOSDAQ150�������񿩺�
	char isKRX100Stock[1];         //KRX100���񿩺�
	char krx300[1];         //KRX300��������
	char KOSPI200LowVolatilityHighDividendIndex[1];         //KOSPI200������������
	char isKRX_BBIG_K_NewDealIndex[1];         //KRXBBIGK������������
	char isKRX_secondaryBattery_K_NewDealIndex[1];         //KRX2������K������������
	char isKRX_bio_K_NewDealIndex[1];         //KRX���̿�K������������
	char filler[9];         //
	char endOfText[1];         //
};
const int EXTURE_PLUS_KOSDAQ_JISU_MASTER_SIZE = sizeof(ExturePlusKosdaqJisuMaster);
#endif

#if(1)
//�ڽ��� ���� RECOVERY	B1011�� ���� Snapshot (MM/LPȣ�� ����) �� ����
//�ڽ��� �ü� RECOVERY	B2011�� ���� Snapshot (MM/LPȣ�� ����) �� ����
//�ڽ��� �ð��ܴ��ϰ� ����	B3011�� ���� Snapshot (MM/LPȣ�� ����) �� ����
//�ڽ��� �ð��ܴ��ϰ� RECOVERY	B4011�� ���� Snapshot (MM/LPȣ�� ����) �� ����
//���� Snapshot (MM/LPȣ�� ����)	���� ���庰 snapshot �� �������¸� ������������ ���� (MM/LPȣ�� ����)	
//�ǽð�[�Ǵ� 0.2��/������ ������ 30�� sleep]
//�ֱ⺯�� ����
//(����A) STK : B201S
//(����B) KSQ : B201Q
//(����B) KNX : B201X
class ExturePlusKosdaqRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// �ŵ�n�ܰ�켱ȣ������
	char bidQuote[11];				// �ż�n�ܰ�켱ȣ������
	char askQuoteVolume[12];		// �ŵ�n�ܰ�켱ȣ���ܷ�
	char bidQuoteVolume[12];		// �ż�n�ܰ�켱ȣ���ܷ�
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExturePlusKosdaqRecoveryTotalTradeRecord);

class ExturePlusKosdaqRecoveryTotalTrade
{
	public:
	char dataClass[2];								// �����ͱ��а� 
	char infoMarketClass[3];						// �������а� 
	char boardID[2];								// ����ID
	char sessionID[2];								// ����ID
	char stockCode[12];								// �����ڵ�
	char stockSeq[6];								// �����й������ε���
	char upDown[1];             					// ���ϴ�񱸺��ڵ�
	char gap[11];							        // ���ϴ�񰡰�
	char upLimitPrice[11];      					// ���Ѱ�
	char downLimitPrice[11];    					// ���Ѱ� 
	char closePrice[11];							// ���簡
    char openPrice[11];         					// �ð�  
    char highPrice[11];         					// ��  
    char lowPrice[11];          					// ����  
    char accmTradeVolume[12];   					// �����ŷ���   
    char accmTradeAmount[22];   					// �����ŷ����  
    char lastAskBidClassCode[1];					// �����ŵ��ż������ڵ� 
	ExturePlusKosdaqRecoveryTotalTradeRecord rec[10];  // �ŵ�(��) n�ܰ� �켱ȣ�� ����
	char totalRemainingAskPrice[12];     			// �ŵ�ȣ�������ܰ��ܷ��հ�    
	char totalRemainingBidPrice[12];     			// �ż�ȣ�������ܰ��ܷ��հ� 
	char estimatedTradePrice[11];   				// ����ü�ᰡ   
    char estimatedTradeVolume[12];  				// ����ü�����
	char realRateQuotationClass[1];    				// �������������ڵ�
													// 1:�Ǽ�
													// 2:�⼼
													// 3:�ŷ���
													// 4:�ð����ذ������� �⼼
	char isTradeStop[1];            				// �ŷ���������
    char endText[1];     							// �����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExturePlusKosdaqRecoveryTotalTrade);
#endif

//1.�尳�����ð������� ü����� : beforeMarketOverTimeClosePriceTradeVolume
//2.������ü�����              : regularMarketTradeVolume
//3.�������Ľð������� ü����� : afterMarketOvertimeClosePriceTradeVolume
//4.�Ϲ� Buy-in ü�����        : regularBuyInTradingVolume
//5.���� Buy-in ü�����        : sameDayBuyInTradingVolume
//6.�ð��ܴ��ϰ����� ü�����   : overTimeMarketFixedAccmVolume
//7.�뷮 ü�����               : manyBulkTradeVolume

//1.�尳�����ð������� �ŷ���� : beforeMarketOverTimeClosePriceTradeAmount
//2.������ŷ����              : regularMarketTradeAmount
//3.�������Ľð������� �ŷ���� : afterMarketOvertimeClosePriceTradeAmount
//4.�Ϲ� Buy-in �ŷ����        : regularBuyInTradingValue
//5.���� Buy-in �ŷ����        : sameDayBuyInTradingValue
//6.�ð��ܴ��ϰ����� �ŷ����   : overTimeMarketFixedAccmAmount
//7.�뷮 �ŷ����               : manyBulkTradeAmount

#if(1)
//��������������/��ġ/FTP
//��������������/��ġ/FTP
class ExturePlusKosdaqInvestorStock
{
    public:
        char dataClass[2];            // 001 DATA���� DT
        char infoClass[2];            // 002 �������� 00
        char marketClass[1];          // 003 ���屸�� 0
        char exchange[2];             // ���屸��
        char date[8];                 // ����
        char symbol[12];              // �����ڵ�
        char investor[4];             // �����ڱ���
                                      // 1000:����� 9000:�ܱ��ΰ�
        char sellVolume[12];          // �ŵ��ŷ��� // ����:��
        char sellAmount[18];          // �ŵ��ŷ���� // ����:��
        char buyVolume[12];           // �ż��ŷ��� // ����:��
        char buyAmount[18];           // �ż��ŷ���� // ����:��
        char filler[14];              // FILLER 14
        char endOfText[1];
};
const int EXTURE_PLUS_KOSDAQ_INVESTOR_STOCK_SIZE = sizeof(ExturePlusKosdaqInvestorStock);
#endif

#if(1)
//�������ٰ���
//(����A) STK : M401S
//(����C) STK : M402S, M403S, M404S
//(����B) KSQ : M401Q
//(����B) KNX : M401X
//(ä��A) BND : M401B
//(ä��A) SMB : M401M
//(ä��A) KTS : M401K
//(ä��A) RPO : M401R
//(�Ļ�A) DRV : M401F, M402F, M403F, M404F, M405F, M406F, M407F, M408F, M409F, M410F, M411F, M412F, M413F, M415F, M416F
//(�Ļ�B) DRV : M414F
//(�Ϲ�A) CMD : M401G
//(�Ϲ�A) ETS : M401E
//�������� �̺�Ʈ ���� �߻��� ����
class ExturePlusKosdaqMarketOperationScheduleDisclosure
{
    public:
	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char marketCategory[3];                                     //����ǰ�׷�ID
	char boardID[2];                                     //����ID
	char boardEventID[3];                                     //�����̺�ƮID
	char boardEventBeginTime[9];                                     //�����̺�Ʈ���۽ð�
	char boardEventApplyCode[5];                                     //�����̺�Ʈ���뱺�ڵ�
	char sessionBeginEndCode[2];                                     //���ǰ��������ڵ�
	char sessionID[2];                                     //����ID
	char issueCode[12];                                     //�����ڵ�
	char listedIssueCode[12];                                     //����������ڵ�
	char productID[11];                                     //��ǰID
	char tradingHaltReasonCode[3];                                     //�ŷ����������ڵ�
	char tradingHaltOccurenceTypeCode[1];                                     //�ŷ������߻������ڵ�
	char stepApplied[2];                                     //����ܰ�
	char stepAppliedOccuredCode[1];                                     //�������񰡰�����Ȯ��߻��ڵ�
	char stepAppliedScheduleTime[9];                                     //��������Ȯ�뿹���ð�
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE = sizeof(ExturePlusKosdaqMarketOperationScheduleDisclosure);
#endif

#if(1)
//���ǰŷ� ���(TO-BE)//�ڽ��Ǵ뷮ü��(C4011)(AS-IS)
//���ǰŷ� ���//���� ���庰 ���ǰŷ� ����(�����ŷ�����)
//������ �� 2ȸ	
//(����A) STK : C401S
//(����C) STK : C402S, C403S, C404S
//(����B) KSQ : C401Q
//(����B) KNX : C401X
class ExturePlusKosdaqTotalBulkTrade
{
    public:
	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char boardID[2];                                     //����ID
	char stockCode[12];                                     //�����ڵ�
	char stockSeq[6];                                     //�����й������ε���
	char accumlatedVolume[12];                                     //�����ŷ���
	char endText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_TOTAL_BULK_TRADE_SIZE = sizeof(ExturePlusKosdaqTotalBulkTrade);
#endif

#if(1)
//�������� ����
//IA000(����������)
//IB000(��������)
class ExturePlusTotalKosdaqIndex
{
    public:
	char dataClass[2];              //�����ͱ��а�
	char infoMarketClass[3];        //�������а�
	char dataID[6];                 //����ID
	char standardCode[12];          //ǥ���ڵ�
	char time[6];                   //��������ð�
	char index[9];                  //����
	char sign[1];                   //���ϴ��������ȣ
	char gap[9];                    //���ϴ������
	char tradeVolume[12];           //�����ŷ���
	char tradeAmount[12];           //�����ŷ����
	char filler[4];                 //�ʷ���
	char endText[1];                //�����й�޼�������Ű����
};
const int EXTURE_PLUS_TOTAL_KOSDAQ_INDEX_SIZE = sizeof(ExturePlusTotalKosdaqIndex);

//14  KOSDAQ����    �������    E4012   KOSDAQ����    50  -   �ǽð�
//15  KOSDAQ��������  �������    E5012   KOSDAQ��������  50  -   �ǽð�
//16  KOSTAR����    �������    E6012   KOSTAR����    50  -   �ǽð�
//17  KOSTAR��������  �������    E7012   KOSTAR��������  50  -   �ǽð�
//18  "KOSDAQ�����̾�����" �������    L2012   KOSDAQ�����̾�����    50  -   �ǽð�
//19  "KOSDAQ�����̾������"   �������    L3012   KOSDAQ�����̾������  50  -   �ǽð�
class ExturePlusKosdaqIndex
{
    public:
        char dataClass[2];                                            // 001 DATA����
        char infoClass[2];                                            // 001 ��������
        char marketClass[1];                                          // 001 ���屸��
        char businessTypeCode[3];                                     // 002 �����ڵ�
        char time[6];                                                 // 003 �ð�
        char index[9];                                                // 004 ����
        char sign[1];                                                 // 005 ��ȣ
        char gap[9];                                                  // 006 ���
        char tradeVolume[12];                                          // 007 ü�����
        char tradeAmount[12];                                          // 008 �ŷ����
};
const int EXTURE_PLUS_KOSDAQ_INDEX_SIZE = sizeof(ExturePlusKosdaqIndex);
#endif

#if(1)
//�ڽ���_�����������(VI)
//VI �ߵ�/���� ����
//(����A) STK : R801S
//(����C) STK : R803S, R804S
//(����B) KSQ : R801Q
//VI (Volatility Interruption) �ߵ�/���� ����
class ExturePlusKosdaqKOSDAQVolatilityInterruptionPerInstrument
{
    public:
	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char distributeStockIndex[8];                                     //�����й��Ϸù�ȣ
	char boardID[2];                                     //����ID
	char issueCode[12];                                     //�����ڵ�
	char issueSeqNo[6];                                     //�����й������ε���
	char tradeExecutionProcessingTime[12];                                     //�Ÿ�ó���ð�
	char removalTimeOfVI[9];                                     //VI�����ð�
	char VIApplicationCategoryCode[1];                                     //VI���뱸���ڵ�
	char VITypeCode[1];                                     //VI�����ڵ�
	char basePriceToTriggerStaticVI[11];                                     //����VI�ߵ����ذ���
	char basePriceToTriggerDynamicVI[11];                                     //����VI�ߵ����ذ���
	char VITriggeringPrice[11];                                     //VI�ߵ�����
	char disparateRatioStaticVI[13];                                     //����VI�ߵ����ݱ�����
	char disparateRatioDynamicVI[13];                                     //����VI�ߵ����ݱ�����
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_KOSDAQ_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE = sizeof(ExturePlusKosdaqKOSDAQVolatilityInterruptionPerInstrument);
#endif

#if(1)
//�������	
//(����A) STK : O601S
//(����C) STK : O602S, O603S, O604S
//(����B) KSQ : O601Q
//(����B) KNX : O601X
//(�Ļ�A) DRV : O601F, O603F
//���ϰ�ü���� ��/���Ѱ��� �����Ǵ� ��� ��/���Ѱ� �ż�, �ŵ��ֹ��� ���� �������� ������ ���������� ����Ͽ� ü���Ű�� ���
class ExturePlusKosdaqQuantityAllocation
{
    public:

	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char distributeStockIndex[8];                                     //�����й��Ϸù�ȣ
	char boardID[2];                                     //����ID
	char issueCode[12];                                     //�����ڵ�
	char serialNo[6];                                     //�����й������ε���
	char allocationStartEnd[1];                                     //������뱸���ڵ�
	char allocationTypeCode[1];                                     //���ó�������ڵ�
	char timeForAllocationEnd[9];                                     //��������ð�
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_QUANTITY_ALLOCATION_SIZE = sizeof(ExturePlusKosdaqQuantityAllocation);
#endif

#if(1)
//�����̺�Ʈ ����
//(����A) STK : I601S
//(����C) STK : I602S, I603S, I604S
//(����B) KSQ : I601Q
//(����B) KNX : I601X
//�ֽ�/ä�� ������ �ŷ�����, ��������, �����Ÿ� ���� �̺�Ʈ ����
//����ȸ���� (STK, KSQ) ���� �� �����ڻ� �ش����� ���͸� "
class ExturePlusKosdaqKOSDAQIssueEventInformation
{
    public:
	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char distributeStockIndex[8];                                     //�����й��Ϸù�ȣ
	char issueCode[12];                                     //�����ڵ�
	char eventTypeCode[2];                                     //�̺�Ʈ�����ڵ�
	char eventOccurrenceCauseCode[4];                                     //�̺�Ʈ�߻������ڵ�
	char startDate[8];                                     //�̺�Ʈ��������
	char expirationDate[8];                                     //�̺�Ʈ��������
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE = sizeof(ExturePlusKosdaqKOSDAQIssueEventInformation);
#endif

#if(1)
//���α׷��Ÿ� ȣ��//���α׷��Ÿ� ��������
//(����A) STK : C301S
//(����B) KSQ : C301Q
//���α׷��Ÿ� ��������
//�������� : �������� �������
//���������� : K200 or Q150 or KRX300 �������
class ExturePlusKosdaqProgramTrade
{
    public:

	char dataClass[2];                        //�����ͱ��а�
	char infoMarketClass[3];                        //�������а�
	char stockCode[12];                        //�����ڵ�
	char serialNo[6];                        //�����й������ε���
	char indexMarginalProfitAskQuoteRemainder[15];                        //�ŵ����Ͱŷ��ܷ�
	char indexMarginalProfitBidQuoteRemainder[15];                        //�ż����Ͱŷ��ܷ�
	char indexNotMarginalProfitAskQuoteRemainder[15];                        //�ŵ��������ܷ�
	char indexNotMarginalProfitBidQuoteRemainder[15];                        //�ż��������ܷ�
	char indexMarginalProfitAskQuoteVolume[15];                        //�ŵ����ͼ���
	char indexMarginalProfitBidQuoteVolume[15];                        //�ż����ͼ���
	char indexNotMarginalProfitAskQuoteVolume[15];                        //�ŵ������ͼ���
	char indexNotMarginalProfitBidQuoteVolume[15];                        //�ż������ͼ���
	char indexMarginalProfitAskConsignmentTradeVolume[10];                        //��Ź�ŵ�����ü�����
	char indexMarginalProfitAskFloorTradeVolume[10];                        //�ڱ�ŵ�����ü�����
	char indexMarginalProfitBidConsignmentTradeVolume[10];                        //��Ź�ż�����ü�����
	char indexMarginalProfitBidFloorTradeVolume[10];                        //�ڱ�ż�����ü�����
	char indexNotMarginalProfitAskConsignmentTradeVolume[10];                        //��Ź�ŵ�������ü�����
	char indexNotMarginalProfitAskFloorTradeVolume[10];                        //�ڱ�ŵ�������ü�����
	char indexNotMarginalProfitBidConsignmentTradeVolume[10];                        //��Ź�ż�������ü�����
	char indexNotMarginalProfitBidFloorTradeVolume[10];                        //�ڱ�ż�������ü�����
	char indexMarginalProfitAskConsignmentTradeAmount[22];                        //��Ź�ŵ����Ͱŷ����
	char indexMarginalProfitAskFloorTradeAmount[22];                        //�ڱ�ŵ����Ͱŷ����
	char indexMarginalProfitBidConsignmentTradeAmount[22];                        //��Ź�ż����Ͱŷ����
	char indexMarginalProfitBidFloorTradeAmount[22];                        //�ڱ�ż����Ͱŷ����
	char indexNotMarginalProfitAskConsignmentTradeAmount[22];                        //��Ź�ŵ������Ͱŷ����
	char indexNotMarginalProfitAskFloorTradeAmount[22];                        //�ڱ�ŵ������Ͱŷ����
	char indexNotMarginalProfitBidConsignmentTradeAmount[22];                        //��Ź�ż������Ͱŷ����
	char indexNotMarginalProfitBidFloorTradeAmount[22];                        //�ڱ�ż������Ͱŷ����
	char endOfText[1];                        //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_SIZE = sizeof(ExturePlusKosdaqProgramTrade);
#endif

#if(1)
//���α׷��Ÿ� ��ü����
//(����A) STK : J001S
//(����B) KSQ : J001Q
//���α׷��Ÿ� ��ü����
//�������� : �������� �������
//���������� : K200 or Q150 or KRX300 �������"
class ExturePlusKosdaqProgramTradeTotal
{
    public:
	char dataClass[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char indexMarginalProfitAskQuoteRemainder[15];                                     //�ŵ����Ͱŷ��ܷ�
	char indexMarginalProfitBidQuoteRemainder[15];                                     //�ż����Ͱŷ��ܷ�
	char indexNotMarginalProfitAskQuoteRemainder[15];                                     //�ŵ��������ܷ�
	char indexNotMarginalProfitBidQuoteRemainder[15];                                     //�ż��������ܷ�
	char indexMarginalProfitAskQuoteVolume[15];                                     //�ŵ����ͼ���
	char indexMarginalProfitBidQuoteVolume[15];                                     //�ż����ͼ���
	char indexNotMarginalProfitAskQuoteVolume[15];                                     //�ŵ������ͼ���
	char indexNotMarginalProfitBidQuoteVolume[15];                                     //�ż������ͼ���
	char indexMarginalProfitAskConsignmentTradeVolume[10];                                     //��Ź�ŵ�����ü�����
	char indexMarginalProfitAskFloorTradeVolume[10];                                     //�ڱ�ŵ�����ü�����
	char indexMarginalProfitBidConsignmentTradeVolume[10];                                     //��Ź�ż�����ü�����
	char indexMarginalProfitBidFloorTradeVolume[10];                                     //�ڱ�ż�����ü�����
	char indexNotMarginalProfitAskConsignmentTradeVolume[10];                                     //��Ź�ŵ�������ü�����
	char indexNotMarginalProfitAskFloorTradeVolume[10];                                     //�ڱ�ŵ�������ü�����
	char indexNotMarginalProfitBidConsignmentTradeVolume[10];                                     //��Ź�ż�������ü�����
	char indexNotMarginalProfitBidFloorTradeVolume[10];                                     //�ڱ�ż�������ü�����
	char indexMarginalProfitAskConsignmentTradeAmount[22];                                     //��Ź�ŵ����Ͱŷ����
	char indexMarginalProfitAskFloorTradeAmount[22];                                     //�ڱ�ŵ����Ͱŷ����
	char indexMarginalProfitBidConsignmentTradeAmount[22];                                     //��Ź�ż����Ͱŷ����
	char indexMarginalProfitBidFloorTradeAmount[22];                                     //�ڱ�ż����Ͱŷ����
	char indexNotMarginalProfitAskConsignmentTradeAmount[22];                                     //��Ź�ŵ������Ͱŷ����
	char indexNotMarginalProfitAskFloorTradeAmount[22];                                     //�ڱ�ŵ������Ͱŷ����
	char indexNotMarginalProfitBidConsignmentTradeAmount[22];                                     //��Ź�ż������Ͱŷ����
	char indexNotMarginalProfitBidFloorTradeAmount[22];                                     //�ڱ�ż������Ͱŷ����
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_TOTAL_SIZE = sizeof(ExturePlusKosdaqProgramTradeTotal);
#endif

#if(1)
//�ڽ��� �ŷ���//�ŷ����� 5�� ȸ�� ���(B901S)
//(����A) STK : B901S
//(����C) STK : B902S, B903S, B904S
//(����B) KSQ : B901Q
//(����B) KNX : B901X
class ExturePlusKosdaqSecuritiesTradeRecord
{
    public:
        char askSecuritiesTradeNumber[5];                             // 006-1 �ŵ��ŷ�����ȣ
        char askTradeVolume[12];                                      // 006-2 �ŵ�ü�����
        char askTradeAmount[22];                                      // 006-3 �ŵ��ŷ����
        char bidSecuritiesTradeNumber[5];                             // 006-4 �ż��ŷ�����ȣ
        char bidTradeVolume[12];                                      // 006-5 �ż�ü�����
        char bidTradeAmount[22];                                      // 006-6 �ż��ŷ����
};
const int EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_RECORD_SIZE = sizeof(ExturePlusKosdaqSecuritiesTradeRecord);

class ExturePlusKosdaqSecuritiesTrade
{
    public:
        char dataClass[2];                                            //�����ͱ��а�
        char infoMarketClass[3];                                            //�������а�
        char stockCode[12];                                           //�����ڵ�
		char serialNo[6];                                             //�����й������ε���
        ExturePlusKosdaqSecuritiesTradeRecord rec[5];                   //�ŷ������� OCCURS 5
        char endOfText[1];                                               //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_SIZE = sizeof(ExturePlusKosdaqSecuritiesTrade);
#endif

#if(1)
// ���� �켱ȣ�� (MM/LPȣ�� ����)
// (����A) STK : B601S
// (����B) KSQ : B601Q
// (����B) KNX : B601X
class ExturePlusKosdaqQuoteRecord
{
    public:
	char askQuote[11];	                // �ŵ�n�ܰ�켱ȣ������
	char bidQuote[11];                  // �ż�n�ܰ�켱ȣ������
	char askQuoteVolume[12];            // �ŵ�n�ܰ�켱ȣ���ܷ�
	char bidQuoteVolume[12];            // �ż�n�ܰ�켱ȣ���ܷ�
};
const int EXTURE_PLUS_KOSDAQ_QUOTE_RECORD_SIZE = sizeof(ExturePlusKosdaqQuoteRecord);

class ExturePlusKosdaqQuote10
{
    public:
     char dataClass[2];       //       �����ͱ��а�  
     char infoMarketClass[3];     //       �������а�   
     char distributeStockIndex[8];                    //       �����й��Ϸù�ȣ    
     char boardID[2];     //       ����ID    
     char sessionID[2];   //       ����ID    
     char stockCode[12];      //       �����ڵ�    
     char stockSeq[6];    //       �����й������ε���   
     char tradingProcessingTime[12];  //       �Ÿ�ó���ð� 
     ExturePlusKosdaqQuoteRecord rec[10];			// �ŵ�(��) n�ܰ� �켱ȣ�� ���� 
     char totalAskQuoteRemainder[12];     //       �ŵ�ȣ�������ܰ��ܷ��հ�    
     char totalBidQuoteRemainder[12];     //       �ż�ȣ�������ܰ��ܷ��հ�    
     char estimatedTradePrice[11];    //       ����ü�ᰡ   
      char estimatedTradeVolume[12];      //       ����ü�����  
     char endText[1];     //       �����й�޼�������Ű����    
};
const int EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE = sizeof(ExturePlusKosdaqQuote10);
#endif

#if(1)
// ������
//(����A) STK : B501S
//(����B) KSQ : B501Q
//(����B) KNX : B501X 
class ExturePlusKosdaqUpDown
{
    public:
	 char data_category[2];           //       �����ͱ��а�  
	 char infoMarketClass[3];               //       �������а�   
	 char totalStockSize[5];          //       �����������
	 char tradeFormationStockSize[5]; //       ����ŷ�������    
	 char upLimitStockSize[5];        //       ������Ѽ� 
	 char upStockSize[5];             //       �����¼�  
	 char sattionaryStockSize[5];     //       ������ռ�
	 char downLimitStockSize[5];      //       ������Ѽ�
	 char downStockSize[5];           //       ����϶���  
	 char quotationStockSize[5];      //       ����⼼��
	 char quotationUpStockSize[5];    //       ����⼼��¼�
	 char quotationDownStockSize[5];  //       ����⼼�϶���
	 char endText[1];                 //       �����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_UPDOWN_SIZE = sizeof(ExturePlusKosdaqUpDown);
#endif

#if(1)
//�ֽ�������������
//(����A) STK : A801S
//(����C) STK : A802S, A803S, A804S
//(����B) KSQ : A801Q
//(����B) KNX : A801X
class ExturePlusKosdaqIssueInformationDisclosure
{
	public:
	char data_category[2];                                          //  �����ͱ��а�  
	char infoMarketClass[3];                                   //  �������а�   
	char board_id[2];                                               //  ����ID    
	char issue_code[12];                                            //  �����ڵ�    
	char issue_seq_no[6];    										 //  �����й������ε���   
	char disclosure_data_type_code[3];                              //  �������������ڵ尪   
	char basis_price[11];                                           //  ���ذ���    
	char upper_limit_price[11];                                     //  ���Ѱ� 
	char lower_limit_price[11];                                     //  ���Ѱ� 
	char evaluation_price[11];                                      //  �򰡰���    
	char highest_order_price[11];                                   //  �ְ�ȣ������  
	char lowest_order_price[11];                                    //  ����ȣ������  
	char opening_price_becomes_basis_price_type[1];                 //  �ð����ذ��ݿ���    
	char back_door_listing[2];                                      //  �������ڵ�   
	char par_value_change_type_code[2];                             //  �׸鰡���汸���ڵ�   
	char lot_size[11];                                              //  ��������    
	char number_of_listed_stocks[16];                               //  �����ֽļ�   
	char designation[1];                                            //  ��������    
	char closing_price_possibility_in_pre_off_hours_session[1];     //  �尳�����ð����������ɿ���   
	char endText[1];     										     //  �����й�޼�������Ű����    
};
const int EXTURE_PLUS_KOSDAQ_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExturePlusKosdaqIssueInformationDisclosure);
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
class ExturePlusKosdaqMarketOperationTS
{
    public:
	char dataCategory[2];                                //�����ͱ��а�
	char infoMarketClass[3];                                //�������а�
	char distributeStockIndex[8];                                //�����й��Ϸù�ȣ
	char boardID[2];                                //����ID
	char sessionID[2];                                //����ID
	char issueCode[12];                                //�����ڵ�
	char serialNo[6];                                //�����й������ε���
	char tradeProcessTime[12];                                //�Ÿ�ó���ð�
	char boardEventID[3];                                //�����̺�ƮID
	char boardEventBeginTime[9];                                //�����̺�Ʈ���۽ð�
	char boardEventApplyCode[5];                                //�����̺�Ʈ���뱺�ڵ�
	char tradingHaltReasonCode[3];                                //�ŷ����������ڵ�
	char endOfText[1];                                //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_TS_SIZE = sizeof(ExturePlusKosdaqMarketOperationTS);
#endif

#if(1)
//���ذ�����
//(����A) STK : A401S
//(����C) STK : A402S, A403S, A404S
//(����B) KSQ : A401Q
//(����B) KNX : A401X
//�򰡰��� ��� ������ ���ذ������� ����
class ExturePlusKosdaqKOSDAQDeterminedBasePrice
{
	public:
	char dataCategory[2];                      // �����ͱ��а�
	char infoMarketClass[3];               // �������а�
	char distributeStockIndex[8];                        // �����й��Ϸù�ȣ
	char boardID[2];                           // ����ID
	char issueCode[12];                        // �����ڵ�
	char stockSeq[6];                          // �����й������ε���
	char basisPrice[11];                       // ���ذ���
	char upperLimitPriceOfBasisPrice[11];      // ���ذ��ݻ��Ѱ�
	char lowerLimitPriceOfBasisPrice[11];      // ���ذ������Ѱ�
	char endText[1];                           // �����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_KOSDAQ_DETERMINED_BASE_PRICE_SIZE = sizeof(ExturePlusKosdaqKOSDAQDeterminedBasePrice);
#endif

#if(1)
// ���� ü��
// (����A) STK : A301S
// (����C) STK : A302S, A303S, A304S
// (����B) KSQ : A301Q
// (����B) KNX : A301X
class ExturePlusKosdaqTrade
{
    public:
     char dataClass[2];                        //       �����ͱ��а�  
     char infoMarketClass[3];                        //       �������а�   
     char distributeStockIndex[8];                         //       �����й��Ϸù�ȣ    
     char boardID[2];                          //       ����ID    
     char sessionID[2];                        //       ����ID    
     char stockCode[12];                       //       �����ڵ�    
     char stockSeq[6];                         //       �����й������ε���   
     char transactionProcessingTime[12];   	   //       �Ÿ�ó���ð�  
     char upDown[1];                           //       ���ϴ�񱸺��ڵ�    
     char gap[11];                              //       ���ϴ�񰡰�  
     char tradePrice[11];                       //       ü�ᰡ��    
     char tradeVolume[10];                     //       �ŷ��� 
     char openPrice[11];                        //       �ð�  
     char highPrice[11];                        //       ��  
     char lowPrice[11];                         //       ����  
     char accmTradeVolume[12];                 //       �����ŷ���   
     char accmTradeAmount[22];                 //       �����ŷ����  
     char lastAskBidClassCode[1];              //       �����ŵ��ż������ڵ�  
     char LPHoldingVolume[15];                 //       LP��������  
     char askOneQuote[11];                      //       �ŵ��ֿ켱ȣ������   
     char bidOneQuote[11];                      //       �ż��ֿ켱ȣ������   
     char endText[1];                          //       �����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_TRADE_SIZE = sizeof(ExturePlusKosdaqTrade);
#endif

#if(1)
//���ŵ�����
//(����A) STK : I801S
//(����C) STK : I802S, I803S, I804S
//(����B) KSQ : I801Q
//(����B) KNX : I801X
class ExturePlusKosdaqShortSellingInformation
{
    public:
	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char issueCode[12];                                     //�����ڵ�
	char shortSellingDebtSecuritiesAskTradingVolume[12];                                     //���԰��ŵ�ü�����
	char shortSellingDebtSecuritiesAskTradingValue[22];                                     //���԰��ŵ��ŷ����
	char upTickRuleAppliedCoveredShortSellingTradingVolume[12];                                     //��ƽ������ŷ���
	char upTickRuleAppliedCoveredShortSellingTradingValue[22];                                     //��ƽ������ŷ����
	char upTickRuleUnappliedCoveredShortSellingTradingVolume[12];                                     //��ƽ�꿹�ܰŷ���
	char upTickRuleUnappliedCoveredShortSellingTradingValue[22];                                     //��ƽ�꿹�ܰŷ����
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_SHORT_SELLING_INFORMATION_SIZE = sizeof(ExturePlusKosdaqShortSellingInformation);
#endif

#if(1)
class ExturePlusKosdaqProgramTradePublic
{
    public:
        char dataClass[2];                                             // 001 �����ͱ���
        char infoClass[2];                                             // 002 ��������
        char marketClass[1];                                           // 003 ���屸��
        char stockCode[12];                                            // 004 �����ڵ�
        char serialNo[8];                                              // 005 �Ϸù�ȣ
        char askPublicAheadPublicPrevRemainder[12];                    // 006 �������ýű�ȣ���ŵ�����(�׸����:�ŵ����û�������->�������ýű�ȣ���ŵ�����)
        char bidPublicAheadPublicPrevRemainder[12];                    // 007 �������ýű�ȣ���ż�����(�׸����:�ż����û�������->�������ýű�ȣ���ż�����)
        char askPublicAheadPublicPrevCorrectingRemainder[12];          // 008 �������ñ�����ȣ���ŵ�����(�׸����:�ŵ����û�����������->�������ñ�����ȣ���ŵ�����)
        char bidPublicAheadPublicPrevCorrectingRemainder[12];          // 009 �������ñ�����ȣ���ż�����(�׸����:�ż����û�����������->�������ñ�����ȣ���ż�����)
        char postDisclosedProgramTradingSellOrderVolume[12];           // 010 ���İ��øŵ�����(���� : ��,  �ű�                2011.05.30)
        char postDisclosedProgramTradingBuyOrderVolume[12];            // 011 ���İ��øż�����(���� : ��,  �ű�                2011.05.30)
        char filler[2];                                                // 012 FILLER
        char ff[1];                                                    // 013 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_PUBLIC_SIZE = sizeof(ExturePlusKosdaqProgramTradePublic);
#endif

#if(1)
class ExturePlusKosdaqProgramTradeBatch
{
    public:
        char dataClass[2];                                            // 001 data����
        char infoClass[2];                                            // 002 ��������
        char marketClass[1];                                          // 003 ���屸��
        char serialNo[8];                                             // 004 �Ϸù�ȣ
        char ptFirstMonthClassCode[1];                                // 005 PT���������ڵ�
        char consignmentFloorTradingClassCode[2];                     // 006 ��Ź�ڱⱸ���ڵ�
        char memberNo[5];                                             // 007 ȸ����ȣ
        char tradeDate[8];                                            // 008 �Ÿ�����
        char stockAskVolume[12];                                      // 009 �ֽĸŵ�����
        char stockAskAmount[22];                                      // 010 �ֽĸŵ��ݾ�
        char stockBidVolume[12];                                      // 011 �ֽĸż�����
        char stockBidAmount[22];                                      // 012 �ֽĸż��ݾ�
        char futureAskVolume[12];                                     // 013 �����ŵ�����
        char futureAskAmount[22];                                     // 014 �����ŵ��ݾ�
        char futureBidVolume[12];                                     // 015 �����ż�����
        char futureBidAmount[22];                                     // 016 �����ż��ݾ�
        char callAskVolume[12];                                       // 017 �ݸŵ�����
        char callAskAmount[22];                                       // 018 �ݸŵ��ݾ�
        char callBidVolume[12];                                       // 019 �ݸż�����
        char callBidAmount[22];                                       // 020 �ݸż��ݾ�
        char putAskVolume[12];                                        // 021 ǲ�ŵ�����
        char putAskAmount[22];                                        // 022 ǲ�ŵ��ݾ�
        char putBidVolume[12];                                        // 023 ǲ�ż�����
        char putBidAmount[22];                                        // 024 ǲ�ż��ݾ�
        char stockErrorVolume[12];                                    // 025 �ֽĿ�������
        char stockErrorCause[60];                                     // 026 �ֽĿ�������
        char filler[6];                                               // 027 FILLER
        char ff[1];                                                   // 028 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_BATCH_SIZE = sizeof(ExturePlusKosdaqProgramTradeBatch);
#endif

#if(1)
//���ڰ���
//(����A) STK  : F000S, E900S
//(����A) KSQ  : F000Q, E900Q
//(����A) KNX  : F000X, E900X
//(����A) OTHERS : F0909, E9909
//���ڰ��� (�¶���)    : F0
//���� ���ڰ��� (��ġ) : E9
class ExturePlusKosdaqPublicNews
{
    public:
	char dataClass[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char stockCode[12];                                     //�����ڵ�
	char publicNewsSerialNumber[6];                                     //���ÿ������Ϸù�ȣ
	char perPublicNewsTotalPageSize[5];                                     //���ù�������������ȣ
	char perPulbicNewsPageSerialNumber[5];                                     //���ù�����������ȣ
	char publicNewsDate[8];                                     //��������
	char sendDate[8];                                     //��������
	char publicNewsMarketClass[1];                                     //���ý��屸���ڵ�
	char stockName[40];                                     //������
	char processClass[1];                                     //���ù���ó�����а�
	char reason[5];                                     //���û��������ڵ尪
	char koreanEnglishClass[1];                                     //���þ��а�
	char publicNewsTitle[264];                                     //���ù�������
	char publicNewsContents[1000];                                     //���ù�������
	char isStockExistence[1];                                     //���ù��������ڵ����Կ���
	char isPulbicNewsContentsStockCode[1];                                     //���������������ڵ忩��
	char stockCodeCount[2];                                     //�������������񰳼�
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_PUBLIC_NEWS_SIZE = sizeof(ExturePlusKosdaqPublicNews);
#endif

#if(0)
class ExturePlusKosdaqPublicNews
{
    public:
        char dataClass[2];                                              // 001 DATA����
        char infoClass[2];                                              // 002 ��������
        char marketClass[1];                                            // 003 ���屸��
        char stockCode[12];                                             // 004 �����ڵ�
        char publicNewsSerialNumber[6];                                 // 005 �����Ϸù�ȣ
        char perPublicNewsTotalPageSize[5];                             // 006 ���ðǴ� �� ������ ��
        char perPulbicNewsPageSerialNumber[5];                          // 007 ���ðǴ� ������ �Ϸù�ȣ
        char publicNewsDate[8];                                         // 008 ��������
        char sendDate[8];                                               // 009 ��������
        char publicNewsMarketClass[1];                                  // 010 ���ÿ���屸��
        char stockName[40];                                             // 011 �����
        char processClass[1];                                           // 012 ó������
        char reason[5];                                                 // 013 ����
        char koreanEnglishClass[1];                                     // 014 ������������
        char publicNewsTitle[264];                                      // 015 ��������
        char publicNewsContents[1000];                                  // 016 ���ó���.
        char isStockExistence[1];                                       // 017 �������翩��.
        char isPulbicNewsContentsStockCode[1];                          // 018 ���ó��� �����ڵ忩��
        char stockCodeCount[2];                                         // 019 �����ڵ尹��
        char filler[8];                                                 // 020 FILLER
        char ff[1];                                                     // 021 END OF TEXT
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_PUBLIC_NEWS_SIZE = sizeof(ExturePlusKosdaqPublicNews);
#endif

#if(0)
// ��������_UDP_�ڽ��������й�_20140203_1���ȳ�.xlsb
// 23   ETF PDF �������    F8011   ETF PDF 160 -   ���� 06:10, 06:50 �� 2ȸ ����
class ExturePlusKosdaqETF_PDF
{
    public:
        // 001 ~ 010
        char dataCategory[2];                                   // 001 DATA ����
        char informationCategory[2];                            // 002 ��������
        char marketCategory[1];                                 // 003 ���屸��
        char etfCode[12];                                       // 004 ETF�ڵ�
        char dataSeqNumber[8];                                  // 005 ������ �Ϸù�ȣ
        char date[8];                                           // 006 ����
        char transferAgentNumber[3];                            // 007 �繫��Źȸ���ȣ
        char compositionIssueNumber[4];                         // 008 ���������
        char compositionIssueCode[12];                          // 009 ���������ڵ�
        char oneCUUnitShare[18];                                // 010 "1CU�������Ǽ�/����/��ȭ����/USD����/��ȭ�򰡾�"
        char compositionIssueMarketType[1];                     // 011 ����������屸��
        char compositionIssueName[40];                          // 012 ���������
        char parValueAmount[18];                                // 013 "�׸�ݾ�/�������ݾ�/��ȭ�򰡱ݾ�"
        char profitDistributionBasisDate[8];                    // 014 ���ͺй������
        char appraisedValue[18];                                // 015 �򰡱ݾ�
        char filler[4];                                         // 016 FILLER
        char endOfText[1];                                      // 017 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_ETF_PDF_SIZE = sizeof(ExturePlusKosdaqETF_PDF);
#endif

#if(1)
//�ڽ��� ����,ETP����,ETF PDF,F803S
class ExturePlusKosdaqETF_PDF
{
	public:
	char dataCategory[2];                            //�����ͱ��а�
	char infoMarketClass[3];                         //�������а�
	char etfCode[12];                                //�����ڵ�
	char dataSeqNumber[8];                           //������ �Ϸù�ȣ
	char date[8];                                    //����
	char transferAgentNumber[3];                     //�繫��Źȸ���ȣ
	char compositionIssueNumber[4];                  //���������
	char compositionIssueCode[12];                   //���������ڵ�
	char oneCUUnitShare[18];                         //1CU�������Ǽ�/����/��ȭ����
	char compositionIssueMarketType[1];              //����������屸��
	char compositionIssueName[40];                   //���������
	char parValueAmount[18];                         //�׸�ݾ�/�������ݾ�
	char profitDistributionBasisDate[8];             //���ͺй������
	char appraisedValue[18];                         //�򰡱ݾ�
	char filler[4];                                  //FILLER
	char endOfText[1];                               //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_ETF_PDF_SIZE = sizeof(ExturePlusKosdaqETF_PDF);
#endif

#if(1)
class ExturePlusKosdaqRecoveryTrade
{
    public:
        char dataClass[2];                                          // 001 DATA����
        char infoClass[2];                                          // 002 ��������
        char marketClass[1];                                        // 003 ���屸��
        char stockCode[12];                                         // 004 �����ڵ�(ǥ���ڵ�)
        char serialNo[5];                                           // 005 �����Ϸù�ȣ
        char upDown[1];                                             // 006 �������
        char gap[9];                                                // 007 ���ϴ��
        char closePrice[11];                                        // 008 ���簡
        char openPrice[11];                                         // 009 �ð�
        char highPrice[11];                                         // 010 ��
        char lowPrice[11];                                          // 011 ����
        char askQuote[11];                                          // 012 �ŵ�ȣ��
        char bidQuote[11];                                          // 013 �ż�ȣ��
        char accmTradeVolume[12];                                   // 014 ����ü�����
        char accmTradeAmount[22];                                   // 015 �����ŷ����
        char realRateQuotationClass[1];                             // 016 �Ǽ�/�⼼����
        char boardEventID[3];                                       // 017 �����̺�ƮID
        char boardID[2];                                            // 018 ����ID
        char isTradeStop[1];                                        // 019 �ŷ���������

        char beforeMarketOverTimeClosePriceTradeVolume[12];         // 020 �尳�����ð�������ü�����
        char beforeMarketOverTimeClosePriceTradeAmount[22];         // 021 �尳�����ð��������ŷ����

        char regularMarketTradeVolume[12];                          // 022 ������ü�����
        char regularMarketTradeAmount[22];                          // 023 ������ŷ����

        char afterMarketOvertimeClosePriceTradeVolume[12];          // 024 �������Ľð�������ü�����
        char afterMarketOvertimeClosePriceTradeAmount[22];          // 025 �������Ľð��������ŷ����

		char overTimeMarketFixedAccmVolume[12];          //���ϰ�ü�����
        char overTimeMarketFixedAccmAmount[22];          //���ϰ��ŷ����

		char manyBulkTradeVolume[12];          //�뷮ü�����
        char manyBulkTradeAmount[22];          //�뷮�ŷ����

        char earlyClosedELWStatus[1];                               // 026 ELW �������Ῡ��
        char earlyClosedELWTime[6];                                 // 027 ELW ��������ð�

        char aBlox[1];                                              // 028 ����뷮 ���ⱸ��
        char regularBuyInTradingVolume[12];                         // 029 �Ϲ� Buy-In ü�����
        char regularBuyInTradingValue[22];                          // 030 �Ϲ� Buy-In �ŷ����
        char sameDayBuyInTradingVolume[12];                         // 031 ���� Buy-In ü�����
        char sameDayBuyInTradingValue[22];                          // 032 ���� Buy-In �ŷ����
        char filler[8];                                             // 033 FILLER
        char ff[1];                                                 // 034 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_SIZE = sizeof(ExturePlusKosdaqRecoveryTrade);
#endif


#if(1)
// ��������_UDP_�����й�_20140203_4���ȳ�.xlsb
//18  �ڽ���_�ð��ܴ��ϰ�_����   �ڽ���_�ð��ܴ��ϰ�_����   B3011   �ڽ���_�ð��ܴ��ϰ�_����   170 170 �ǽð�
//19  �ڽ���_�ð��ܴ��ϰ�_�ü�   �ڽ���_�ð��ܴ��ϰ�_�ü�   B4011   �ڽ���_�ð��ܴ��ϰ�_�ü�   170 170 �ǽð�
class ExturePlusKosdaqRecoveryTradeFixed
{
    public:
        char dataClass[2];                                          // 001 DATA����
        char infoClass[2];                                          // 002 ��������
        char marketClass[1];                                        // 003 ���屸��
        char stockCode[12];                                         // 004 �����ڵ�
        char serialNo[5];                                           // 005 �����Ϸù�ȣ
        char upDown[1];                                             // 006 �ð��ܴ��ϰ��������
        char gap[9];                                                // 007 �ð��ܴ��ϰ����
        char overTimeMarketFixedUpLimitPrice[11];                    // 008 �ð��ܴ��ϰ����Ѱ�
        char overTimeMarketFixedDownLimitPrice[11];                  // 009 �ð��ܴ��ϰ����Ѱ�
        char overTimeMarketFixedCurrClosePrice[11];                  // 010 �ð��ܴ��ϰ����簡
        char overTimeMarketFixedOpenPrice[11];                       // 011 �ð��ܴ��ϰ��ð�
        char overTimeMarketFixedHighPrice[11];                       // 012 �ð��ܴ��ϰ���
        char overTimeMarketFixedLowPrice[11];                        // 013 �ð��ܴ��ϰ�����
        char overTimeMarketFixedAskQuote[11];                        // 014 �ð��ܴ��ϸŵ�ȣ��
        char overTimeMarketFixedBikQuote[11];                        // 015 �ð��ܴ��ϸż�ȣ��
        char overTimeMarketFixedAccmVolume[12];                     // 016 �ð��ܴ��ϰ�����ü�����
        char overTimeMarketFixedAccmAmount[22];                     // 017 �ð��ܴ��ϰ������ŷ����
        char totalAccmVolume[12];                                   // 018 ��ü �� ����ü�����
        char totlaAccmAmount[22];                                   // 019 ��ü �� �����ŷ����
        char overTimeMarketFixedMarketClass[1];                     // 020 �ð��ܴ��ϰ��屸��
        char isTradeStop[1];                                        // 021 �ŷ���������
        char realRateQuotationClass[1];                             // 022 �Ǽ�/�⼼ ����
        char filler[2];                                             // 023 FILLER
        char ff[1];                                                 // 024 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_FIXED_SIZE = sizeof(ExturePlusKosdaqRecoveryTradeFixed);
#endif

#if(1)
//������ �����ں� ���//������ �����ں� ���
//09:00~18:00 [90�� �ֱ�]
//(����A) STK : C001S
//(����B) KSQ : C001Q
//(����B) KNX : C001X
class ExturePlusKosdaqTotalInvestorIndex
{
    public:
	char dataClass[2];              //�����ͱ��а�
	char infoMarketClass[3];              //�������а�
	char calculationTime[6];              //������ð�
	char investorCode[4];              //�����ڱ����ڵ�
	char jisuIdentifiation[6];              //����ID
	char jisuStandardCode[12];              //ǥ���ڵ�
	char askTradeVolume[12];              //�����ŵ�ü�����
	char askTradeAmount[22];              //�����ŵ��ŷ����
	char bidTradeVolume[12];              //�����ż�ü�����
	char bidTradeAmount[22];              //�����ż��ŷ����
	char filler[3];              //�ʷ���3
	char endText[1];              //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSDAQ_TOTAL_INVESTOR_INDEX_SIZE = sizeof(ExturePlusKosdaqTotalInvestorIndex);
#endif

#if(1)
class ExturePlusKosdaqInvestorIndex
{
    public:
        char dataClass[2];                                            // 001 DATA����
        char infoClass[2];                                            // 002 ��������
        char marketClass[1];                                          // 003 ���屸��
        char calculationTime[6];                                      // 004 ����ð�
        char investorCode[4];                                         // 005 �������ڵ�
        char businessType[3];                                         // 006 �����ڵ�
        char askTradeVolume[12];                                      // 007 �ŵ�ü�����
        char askTradeAmount[22];                                      // 008 �ŵ��ŷ����
        char bidTradeVolume[12];                                      // 009 �ż�ü�����
        char bidTradeAmount[22];                                      // 010 �ż��ŷ����
        char filler[7];
        char ff[1];
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_INVESTOR_INDEX_SIZE = sizeof(ExturePlusKosdaqInvestorIndex);
#endif

#if(1)
class ExturePlusKoscomLineLKInfo_KOSDAQ
{
    public:
        // 001 ~ 010
        char dataCategory[2];                                   // 001 DATA ����
        char informationCategory[2];                            // 002 ��������
        char marketCategory[1];                                 // 003 ���屸��
        char time[4];                                           // 004 �ð�
        char ff[1];                                             // 005 FF
        char recvAddr[32];                                      // �����ּ�����(�������� ���� ��)
};
const int EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSDAQ_SIZE = sizeof(ExturePlusKoscomLineLKInfo_KOSDAQ);
#endif

#if(1)
// ���� ��Ŀ������ ���� ���ڵ�
// ü�� ������ ������ ä���.
// DATA ������ ZZ �� �ӽ÷� ������
class PaxfeedKosdaqCustomIndexRecoveryRec
{
    public:
        char dataClass[2];                                          // 001 DATA����(ZZ)
        char infoClass[2];                                          // 002 ��������
        char marketClass[1];                                        // 003 ���屸��
        char stockCode[12];                                         // 004 �����ڵ�
        char serialNo[5];                                           // 005 �����Ϸù�ȣ(A0001 �� serialNo �� ���� ���̸�, ����� �ٸ����� ���� ��ȿ�� ���� 5�ڸ��� �ȳ����Ƿ� ������ ����. �Ϸù�ȣ�� ���ϸ��� �ٸ� �� ����)
        char boardID[2];                                            // 006 ���� ID
        char upDown[1];                                             // 007 ���ϴ��(���ذ����)����
        char gap[9];                                                // 008 ���ϴ��
        char tradePrice[9];                                         // 009 ü�ᰡ��
        char tradeVolume[10];                                       // 010 ü�����
        char sessionID[2];                                          // 011 ����ID
        char openPrice[9];                                          // 012 �ð�
        char highPrice[9];                                          // 013 ��
        char lowPrice[9];                                           // 014 ����
        char accmTradeVolume[12];                                   // 015 ����ü�����
        char accmTradeAmount[18];                                   // 016 �����ŷ����
        char lastAskBidClassCode[1];                                // 017 �����ŵ��ż������ڵ�
        char isTradePriceQuotePrice1Equal[1];                       // 018 ü�ᰡ��1ȣ����ġ����
        char tradeTime[6];                                          // 019 ü��ð�
        char LPHoldingVolume[15];                                   // 020 LP��������
        char askOneQuote[9];                                        // 021 �ŵ�1ȣ��
        char bidOneQuote[9];                                        // 022 �ż�1ȣ��
        char filler[6];                                             // 023 FILLER(2)
        char ff[1];                                                 // 024 FF
        char cr[1];
        char lf[1];
};
const int PAXFEED_KOSDAQ_CUSTOM_INDEX_RECOVERY_REC = sizeof(PaxfeedKosdaqCustomIndexRecoveryRec);
#endif

#if(1)
class ExturePlusKosdaqBulkTrade
{
    public:
        char dataCategory[2];                                          // 001 DATA����
        char informationCategory[2];                                   // 002 ��������
        char marketCategory[1];                                        // 003 ���屸��
        char issueCode[12];                                            // 004 �����ڵ�
        char serialNo[5];                                              // 005 �����Ϸù�ȣ
        char seqNumber[8];                                             // 006 �Ϸù�ȣ
        char kBloxVolumeInPreMarketTradingHoursSession[12];             // 007 �尳���� �ð��� ���뷮 ü�����
        char basketTradingVolumeInPreMarketTradingHoursSession[12];     // 008 �尳���� �ð��� �ٽ��� ü�����
        char aBloxVolumeInPreMarketTradingHoursSession[12];             // 009 �尳���� �ð��� ����뷮ü�����
        char kBloxVolumeInRegularTradingHoursSession[12];               // 010 ���߻��뷮ü�����
        char basketTradingVolumeInRegularTradingHoursSession[12];       // 011 ���߹ٽ���ü�����
        char aBloxVolumeInRegularTradingHoursSession[12];               // 012 ���߰���뷮ü�����
        char kBloxVolumeInPostMarketTradingHoursSession[12];            // 013 �������� �ð��� ���뷮ü�����
        char basketTradingVolumeInPostMarketTradingHoursSession[12];    // 014 �������� �ð��� �ٽ��� ü�����
        char filler[7];                                                // 015 FILLER
        char ff[1];                                                    // 016 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_BULK_TRADE_SIZE = sizeof(ExturePlusKosdaqBulkTrade);
#endif

#pragma pack()

#endif // __EXTURE_PLUS_KOSDAQ_H__
