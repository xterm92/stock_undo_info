#ifndef __EXTURE_PLUS_INTERNET_ELW_H__
#define __EXTURE_PLUS_INTERNET_ELW_H__

/*
 12345678901234567890123456789012345678901234567890123456789012345678901234567890
 */

#pragma pack(1)

#if(1)
// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 5    ��������ELW �򰡱Ⱓ �� �����ڻ������  M5011   ��������ELW �򰡱Ⱓ �� �����ڻ������  92  "������������(15:00~16:00)���� 2ȸ ����"   ��������ELWü��ȣ������
// ���� ������ �������� �����
class ExturePlusElwHighLowPriceOfUnderlyingAssetForEarlyClosedELWDuringEvaluationPeriod
{
    public:
        char data_category[2];                          // 1    DATA����  X   2
        char information_category[2];                   // 2    ��������    X   2
        char market_category[1];                        // 3    ���屸��    X   1
        char issue_code[12];                            // 4    �����ڵ�    X   12
        char issue_seq_number[8];                       // 5    �Ϸù�ȣ    9   8
        char data_transmitted_date[8];                  // 6    ��������    X   8
        char trading_date_of_underlying_asset[8];       // 7    �����ڻ�Ÿ�����    X   8
        char ko_occurred_date[8];                       // 8    KO�߻�����  X   8
        char am_pm_category_code[1];                    // 9    �������ı����ڵ�    X   1
        char issue_code_of_elw_underlying_asset[12];    // 10   ���������ڵ�  X   12
        char market_type_that_elw_included[1];          // 11   ELW�����Ҽӽ��屸���ڵ�   X   1
        char index_industry_code[3];                    // 12   ���������ڵ�  X   3
        char high_price[11];                            // 13   ��  X   11
        char low_price[11];                             // 14   ����  X   11
        char filler[1];                                 // 15   FILLER  X   1
        char ff[1];                                     // 16   FF  X   1
        char cr[1];                                     // 17   CR  X   1
        char lf[1];                                     // 18   LF  X   1
};
const int EXTURE_PLUS_ELW_HIGH_LOW_PRICE_OF_UNDERLYING_ASSET_FOR_EARLY_CLOSED_ELW_DURING_EVALUATION_PERIOD_SIZE = sizeof(ExturePlusElwHighLowPriceOfUnderlyingAssetForEarlyClosedELWDuringEvaluationPeriod);

// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 7    ELW �������    O6021   ELW �������    32  �ǽð� ��������ELWü��ȣ������
// ���� ������ �������� �����
class ExturePlusElwELWQuantityAllocation
{
    public:
        char data_category[2];                                  // 1    DATA����  X   2
        char information_category[2];                           // 2    "��������"  X   2
        char market_category[1];                                // 3    "���屸��"  X   1
        char issue_code[12];                                    // 4    "�����ڵ�"  X   12
        char data_category_other_than_regular_session[1];       // 5    "���Խð��ܱ����ڵ�" X   1
        char allocation_start_end[1];                           // 6    "������뱸���ڵ�"  X   1
        char allocation_type_code[1];                           // 7    "���ó�������ڵ�"  X   1
        char time_for_allocation_end[6];                        // 8    "��������ð�"    X   6
        char filler[3];                                         // 9    "FILLER"    X   3
        char ff[1];                                             // 10   "FF"    X   1
        char cr[1];                                             // 11   "CR"    X   1
        char lf[1];                                             // 12   "LF"    X   1
};
const int EXTURE_PLUS_ELW_ELW_QUANTITY_ALLOCATION_SIZE = sizeof(ExturePlusElwELWQuantityAllocation);

// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 8    ELW_�����ں�    C0021   ELW �����ں�    88  �ǽð�
// ���� ������ �������� �����
class ExturePlusElwELWTradingActivityPerInvestor
{
    public:
        char data_category[2];              // 1    DATA����  X   2
        char information_category[2];       // 2    ��������    X   2
        char market_category[1];            // 3    ���屸��    X   1
        char calculation_time[6];           // 4    ����ð�    X   6
        char investor_code[4];              // 5    �������ڵ�   X   4
        char industry_code[3];              // 6    �����ڵ�    X   3
        char ask_trading_volume[12];        // 7    �ŵ�ü�����  9   12
        char ask_trading_value[18];         // 8    �ŵ��ŷ����  9   18
        char bid_trading_volume[12];        // 9    �ż�ü�����  9   12
        char bid_trading_value[18];         // 10   �ż��ŷ����  9   18
        char filler[7];                     // 11   FILLER  X   7
        char ff[1];                         // 12   FF  X   1
        char cr[1];                         // 13   CR  X   1
        char lf[1];                         // 14   LF  X   1
};
const int EXTURE_PLUS_ELW_ELW_TRADING_ACTIVITY_PER_INVESTOR_SIZE = sizeof(ExturePlusElwELWTradingActivityPerInvestor);

// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 15  ELW ���� RECOVERY B1021   ELW_�ü�����    292 �ǽð�
// ���� ������ �������� �����
class ExturePlusElwELW_EOD
{
    public:
        char data_category[2];                                                                              // 1    DATA����  X   2
        char information_category[2];                                                                       // 2    ��������    X   2
        char market_category[1];                                                                            // 3    ���屸��    X   1
        char issue_code[12];                                                                                // 4    �����ڵ�    X   12
        char issue_seq_no[5];                                                                               // 5    �����Ϸù�ȣ  9   5
        char fluctuation_type[1];                                                                           // 6    �������    X   1
        char price_change_against_previous_day[9];                                                          // 7    ���ϴ��    9   9
        char current_price_[9];                                                                             // 8    ���簡 9   9
        char market_price[9];                                                                               // 9    �ð�  9   9
        char highest_limit_price[9];                                                                        // 10   ��  9   9
        char lowest_limit_price[9];                                                                         // 11   ����  9   9
        char trading_ask[9];                                                                                // 12   �ŵ�ȣ��    9   9
        char trading_bid[9];                                                                                // 13   �ż�ȣ��    9   9
        char accumulated_total_trading_volume[12];                                                          // 14   ����ü�����  9   12
        char accumulated_total_trading_value[18];                                                           // 15   �����ŷ����  9   18
        char regular_closing_price_biased_quotation_new_closing_price_without_trades_price[1];              // 16   �Ǽ�/�⼼ ����    X   1
        char board_event_id[3];                                                                             // 17   �����̺�ƮID X   3
        char board_id[2];                                                                                   // 18   ����ID    X   2
        char trading_halt[1];                                                                               // 19   �ŷ���������  X   1
        char closing_price_trading_volume_of_pre_opening_market[12];                                        // 20   "�尳�����ð�������ü�����" 9   12
        char closing_price_trading_value_of_pre_opening_market[18];                                         // 21   "�尳�����ð��������ŷ����" 9   18
        char trading_volume_of_regular_session[12];                                                         // 22   ������ü����� 9   12
        char trading_value_of_regular_session[18];                                                          // 23   ������ŷ���� 9   18
        char closing_price_trading_volume_of_after_hour_market[12];                                         // 24   "�������Ľð�������ü�����" 9   12
        char closing_price_trading_value_of_after_hour_market[18];                                          // 25   "�������Ľð��������ŷ����" 9   18
        char early_closed_elw_status[1];                                                                    // 26   ELW�������Ῡ��   X   1
        char early_closed_elw_time[6];                                                                      // 27   ELW��������ð�   9   6
        char a_blox_[1];                                                                                    // 28   ����뷮 ���ⱸ��   9   1
        char regular_buy_in_trading_volume[12];                                                             // 29   �Ϲ� Buy-in ü�����  9   12
        char regular_buy_in_trading_value[18];                                                              // 30   �Ϲ� Buy-in �ŷ����  9   18
        char same_day_buy_in_trading_volume[12];                                                            // 31   ���� Buy-in ü�����  9   12
        char same_day_buy_in_trading_value[18];                                                             // 32   ���� Buy-in �ŷ����  9   18
        char filler[8];                                                                                     // 33   FILLER  X   8
        char ff[1];                                                                                         // 34   FF  X   1
        char cr[1];                                                                                         // 35   CR  X   1
        char lf[1];                                                                                         // 36   LF  X   1
};
const int EXTURE_PLUS_ELW_ELW_EOD_SIZE = sizeof(ExturePlusElwELW_EOD);

// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 16  ELW �ü� RECOVERY B2021   ELW_�ü�RECOVERY  292 �ǽð�
// ���� ������ �������� �����
class ExturePlusElwELWMarketDataRecovery
{
    public:
        char data_category[2];                                                                              // 1    DATA����  X   2
        char information_category[2];                                                                       // 2    ��������    X   2
        char market_category[1];                                                                            // 3    ���屸��    X   1
        char issue_code[12];                                                                                // 4    �����ڵ�    X   12
        char issue_seq_no[5];                                                                               // 5    �����Ϸù�ȣ  9   5
        char fluctuation_type[1];                                                                           // 6    �������    X   1
        char price_change_against_previous_day[9];                                                          // 7    ���ϴ��    9   9
        char current_price_[9];                                                                             // 8    ���簡 9   9
        char market_price[9];                                                                               // 9    �ð�  9   9
        char highest_limit_price[9];                                                                        // 10   ��  9   9
        char lowest_limit_price[9];                                                                         // 11   ����  9   9
        char trading_ask[9];                                                                                // 12   �ŵ�ȣ��    9   9
        char trading_bid[9];                                                                                // 13   �ż�ȣ��    9   9
        char accumulated_total_trading_volume[12];                                                          // 14   ����ü�����  9   12
        char accumulated_total_trading_value[18];                                                           // 15   �����ŷ����  9   18
        char regular_closing_price_biased_quotation_new_closing_price_without_trades_price[1];              // 16   �Ǽ�/�⼼ ����    X   1
        char board_event_id[3];                                                                             // 17   �����̺�ƮID X   3
        char board_id[2];                                                                                   // 18   ����ID    X   2
        char trading_halt[1];                                                                               // 19   �ŷ���������  X   1
        char closing_price_trading_volume_of_pre_opening_market[12];                                        // 20   "�尳�����ð�������ü�����" 9   12
        char closing_price_trading_value_of_pre_opening_market[18];                                         // 21   "�尳�����ð��������ŷ����" 9   18
        char trading_volume_of_regular_session[12];                                                         // 22   ������ü����� 9   12
        char trading_value_of_regular_session[18];                                                          // 23   ������ŷ���� 9   18
        char closing_price_trading_volume_of_after_hour_market[12];                                         // 24   "�������Ľð�������ü�����" 9   12
        char closing_price_trading_value_of_after_hour_market[18];                                          // 25   "�������Ľð��������ŷ����" 9   18
        char early_closed_elw_status[1];                                                                    // 26   ELW�������Ῡ��   X   1
        char early_closed_elw_time[6];                                                                      // 27   ELW��������ð�   9   6
        char a_blox_[1];                                                                                    // 28   ����뷮 ���ⱸ��   9   1
        char regular_buy_in_trading_volume[12];                                                             // 29   �Ϲ� Buy-in ü�����  9   12
        char regular_buy_in_trading_value[18];                                                              // 30   �Ϲ� Buy-in �ŷ����  9   18
        char same_day_buy_in_trading_volume[12];                                                            // 31   ���� Buy-in ü�����  9   12
        char same_day_buy_in_trading_value[18];                                                             // 32   ���� Buy-in �ŷ����  9   18
        char filler[8];                                                                                     // 33   FILLER  X   8
        char ff[1];                                                                                         // 34   FF  X   1
        char cr[1];                                                                                         // 35   CR  X   1
        char lf[1];                                                                                         // 36   LF  X   1
};
const int EXTURE_PLUS_ELW_ELW_MARKET_DATA_RECOVERY_SIZE = sizeof(ExturePlusElwELWMarketDataRecovery);

// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 19  HEADER  HE  HEADER  13  ��Ŀ������û�� ����
// ���� ������ �������� �����

// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 20  FOOTER  FO  FOOTER  13  ��Ŀ������û�� ����
// ���� ������ �������� �����

// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 21  LINK    LK  LINK    13  1�а������͹̹߻�������
// ���� ������ �������� �����

class ExturePlusKoscomLineLKInfo_ELW
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
const int EXTURE_PLUS_KOSCOM_LINE_LK_INFO_ELW_SIZE = sizeof(ExturePlusKoscomLineLKInfo_ELW);

// ELW_�ǽð�_���ͳ�(KOSCOM)_20140523_2014052301.xls
// 3   ELW ������ǥ �ΰ���    C7021   ELW ������ǥ �ΰ���    112 �ǽð� ��������ELW������ǥ����
// ���� ������ �������� �����
class ExturePlusElwEquityLinkedWarrantsInvestment
{
    public:
        char data_category[2];              // 1    DATA����  X   2
        char information_category[2];       // 2    ��������    X   2
        char market_category[1];            // 3    ���屸��    X   1
        char issue_code[12];                // 4    �����ڵ�    X   12
        char time[6];                       // 5    ����ð�    X   6
        char theoretical_price[10];         // 6    �̷а� 9   10
        char sensitivity_delta_sign[1];     // 7    �ΰ��� - ��Ÿ��ȣ  X   1
        char sensitivity_delta[7];          // 8    �ΰ��� - ��Ÿ    9   7
        char sensitivity_gamma_sign[1];     // 9    �ΰ��� - ������ȣ  X   1
        char sensitivity_gamma[7];          // 10   �ΰ��� - ����    9   7
        char sensitivity_theta_sign[1];     // 11   �ΰ��� - ��Ÿ��ȣ  X   1
        char sensitivity_theta_[12];        // 12   �ΰ��� - ��Ÿ    9   12
        char sensitivity_vega_sign[1];      // 13   �ΰ��� - ������ȣ  X   1
        char sensitivity_vega[12];          // 14   �ΰ��� - ����    9   12
        char sensitivity_rho_sign[1];       // 15   �ΰ��� - �κ�ȣ   X   1
        char sensitivity_rho[12];           // 16   �ΰ��� - �� 9   12
        char intrinsic_volatility[5];       // 17   ���纯����   9   5
        char prerequisite_cost[10];         // 18   ���ݺ��    9   10
        char filler[6];                     // 19   FILLER  X   6
        char ff[1];                         // 20   FF  X   1
        char cr[1];                         // 21   CR  X   1
        char lf[1];                         // 22   LF  X   1
};
const int EXTURE_PLUS_ELW_EQUITY_LINKED_WARRANTS_INVESTMENT_SIZE = sizeof(ExturePlusElwEquityLinkedWarrantsInvestment);

// ELW_�ǽð�_���ͳ�(KOSCOM)_20140523_2014052301.xls
// 4   ELW LPȣ�� ���纯����  N3021   ELW LPȣ�� ���纯����  872 �ǽð� ��������ELW������ǥ����
// ���� ������ �������� �����
class ExturePlusElwImpliedVolatilityOfELW_LP_Quotes
{
    public:
        char data_category[2];                  // 1    DATA����  X   2
        char information_category[2];           // 2    ��������    X   2
        char market_category[1];                // 3    ���屸��    X   1
        char time[6];                           // 4    ����ð�    9   6
        char issue_code_00[12];                 // 6    �����ڵ�    X   0
        char implied_volatility_00[5];          // 7    ���纯����   9   0
        char issue_code_01[12];                 //
        char implied_volatility_01[5];          //
        char issue_code_02[12];                 //
        char implied_volatility_02[5];          //
        char issue_code_03[12];                 //
        char implied_volatility_03[5];          //
        char issue_code_04[12];                 //
        char implied_volatility_04[5];          //
        char issue_code_05[12];                 //
        char implied_volatility_05[5];          //
        char issue_code_06[12];                 //
        char implied_volatility_06[5];          //
        char issue_code_07[12];                 //
        char implied_volatility_07[5];          //
        char issue_code_08[12];                 //
        char implied_volatility_08[5];          //
        char issue_code_09[12];                 //
        char implied_volatility_09[5];          //
        char issue_code_10[12];                 //
        char implied_volatility_10[5];          //
        char issue_code_11[12];                 //
        char implied_volatility_11[5];          //
        char issue_code_12[12];                 //
        char implied_volatility_12[5];          //
        char issue_code_13[12];                 //
        char implied_volatility_13[5];          //
        char issue_code_14[12];                 //
        char implied_volatility_14[5];          //
        char issue_code_15[12];                 //
        char implied_volatility_15[5];          //
        char issue_code_16[12];                 //
        char implied_volatility_16[5];          //
        char issue_code_17[12];                 //
        char implied_volatility_17[5];          //
        char issue_code_18[12];                 //
        char implied_volatility_18[5];          //
        char issue_code_19[12];                 //
        char implied_volatility_19[5];          //
        char issue_code_20[12];                 //
        char implied_volatility_20[5];          //
        char issue_code_21[12];                 //
        char implied_volatility_21[5];          //
        char issue_code_22[12];                 //
        char implied_volatility_22[5];          //
        char issue_code_23[12];                 //
        char implied_volatility_23[5];          //
        char issue_code_24[12];                 //
        char implied_volatility_24[5];          //
        char issue_code_25[12];                 //
        char implied_volatility_25[5];          //
        char issue_code_26[12];                 //
        char implied_volatility_26[5];          //
        char issue_code_27[12];                 //
        char implied_volatility_27[5];          //
        char issue_code_28[12];                 //
        char implied_volatility_28[5];          //
        char issue_code_29[12];                 //
        char implied_volatility_29[5];          //
        char issue_code_30[12];                 //
        char implied_volatility_30[5];          //
        char issue_code_31[12];                 //
        char implied_volatility_31[5];          //
        char issue_code_32[12];                 //
        char implied_volatility_32[5];          //
        char issue_code_33[12];                 //
        char implied_volatility_33[5];          //
        char issue_code_34[12];                 //
        char implied_volatility_34[5];          //
        char issue_code_35[12];                 //
        char implied_volatility_35[5];          //
        char issue_code_36[12];                 //
        char implied_volatility_36[5];          //
        char issue_code_37[12];                 //
        char implied_volatility_37[5];          //
        char issue_code_38[12];                 //
        char implied_volatility_38[5];          //
        char issue_code_39[12];                 //
        char implied_volatility_39[5];          //
        char issue_code_40[12];                 //
        char implied_volatility_40[5];          //
        char issue_code_41[12];                 //
        char implied_volatility_41[5];          //
        char issue_code_42[12];                 //
        char implied_volatility_42[5];          //
        char issue_code_43[12];                 //
        char implied_volatility_43[5];          //
        char issue_code_44[12];                 //
        char implied_volatility_44[5];          //
        char issue_code_45[12];                 //
        char implied_volatility_45[5];          //
        char issue_code_46[12];                 //
        char implied_volatility_46[5];          //
        char issue_code_47[12];                 //
        char implied_volatility_47[5];          //
        char issue_code_48[12];                 //
        char implied_volatility_48[5];          //
        char issue_code_49[12];                 //
        char implied_volatility_49[5];          //
        char filler[8];                         // 8    FILLER  X   8
        char ff[1];                             // 9    FF  X   1
        char cr[1];                             // 10   CR  X   1
        char lf[1];                             // 11   LF  X   1
};
const int EXTURE_PLUS_ELW_IMPLIED_VOLATILITY_OF_ELW_LP_QUOTES_SIZE = sizeof(ExturePlusElwImpliedVolatilityOfELW_LP_Quotes);
#endif

#if(1)
//ETN ��������
//(����C) STK : A104S
class ExturePlusElwETNInformationBatch
{
    public:
	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char distributeStockIndex[8];                                     //�����й��Ϸù�ȣ
	char issueCode[12];                                     //�����ڵ�
	char dataSeqNumber[6];                                     //�����й������ε���
	char etnIssueMarketParticipantKoreanName[80];                                     //������������ڸ�
	char etnIssueMarketParticipantEnglishName[80];                                     //������������ڿ�����
	char etnIssueMarketParticipantNo[5];                                     //������������ڹ�ȣ
	char etnFinalSettlementMethodCode[1];                                     //������������ڵ�
	char etnLastTradingDate[8];                                     //�����ŷ�����
	char etnPaymentDate[8];                                     //ETN��������
	char etnLPHoldingQuantity[15];                                     //ETN_LP��������
	char lossProtectionEtnProfitStructureCode[2];                                     //�ս�����ETN���ͱ����ڵ�
	char etnMaximumRedemptionPrice[11];                                     //ETN�ִ��ȯ����
	char etnMinimumRedemptionPrice[11];                                     //ETN�ּһ�ȯ����
	char etnEarlyRedemptionPossibility[1];                                     //ETN�����ȯ���ɿ���
	char etnEarlyRedemptionPeriodCode[2];                                     //ETN�����ȯ�ֱ��ڵ�
	char appraisedPriceCalculationInstitutionCode1[2];                                     //�򰡰��ݻ������ڵ�1
	char appraisedPriceCalculationInstitutionCode2[2];                                     //�򰡰��ݻ������ڵ�2
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE = sizeof(ExturePlusElwETNInformationBatch);
#endif

#if(1)
//ELW ��������//LW ���� Ưȭ����
//(����C) STK : A102S
class ExturePlusElwELWBatchData
{
    public:
	char data_category[2];                                   //�����ͱ��а�
	char infoMarketClass[3];                                 //�������а�
	char distributeStockIndex[8];                            //�����й��Ϸù�ȣ
	char issue_code[12];                                     //�����ڵ�
	char data_seq_number[6];                                     //�����й������ε���
	char elw_issue_market_candidate_korean_name[80];                                     //������������ڸ�
	char elw_issue_market_candidate_english_name[80];                                     //������������ڿ�����
	char elw_issue_market_candidate_number[5];                                     //������������ڹ�ȣ
	char elw_composition_issue_market_id_1[3];                                     //�����������ID1
	char elw_composition_issue_market_id_2[3];                                     //�����������ID2
	char elw_composition_issue_market_id_3[3];                                     //�����������ID3
	char elw_composition_issue_market_id_4[3];                                     //�����������ID4
	char elw_composition_issue_market_id_5[3];                                     //�����������ID5
	char elw_underlying_asset_1[12];                                     //�����ڻ������ڵ�1
	char elw_underlying_asset_2[12];                                     //�����ڻ������ڵ�2
	char elw_underlying_asset_3[12];                                     //�����ڻ������ڵ�3
	char elw_underlying_asset_4[12];                                     //�����ڻ������ڵ�4
	char elw_underlying_asset_5[12];                                     //�����ڻ������ڵ�5
	char elw_underlying_asset_composite_rate_1[13];                                     //�����ڻ걸������1
	char elw_underlying_asset_composite_rate_2[13];                                     //�����ڻ걸������2
	char elw_underlying_asset_composite_rate_3[13];                                     //�����ڻ걸������3
	char elw_underlying_asset_composite_rate_4[13];                                     //�����ڻ걸������4
	char elw_underlying_asset_composite_rate_5[13];                                     //�����ڻ걸������5
	char elw_index_industry_code[6];                                     //����ID
	char elw_rights_type_0[1];                                     //�Ǹ������ڵ�
	char elw_rights_execution_type[1];                                     //�Ǹ���������ڵ�
	char elw_payment_method[1];                                     //������������ڵ�
	char elw_last_traded_date[8];                                     //�����ŷ�����
	char elw_payment_date[8];                                     //ELW��������
	char base_price_of_elw_underlying_asset[13];                                     //�����ڻ���ʰ���
	char elw_rights_content[200];                                     //�Ǹ���系��
	char elw_conversion_rate[13];                                     //ELW��ȯ����
	char elw_price_rise_participation_rate[10];                                     //ELW���ݻ��������
	char elw_minimum_compensation_rate[10];                                     //ELW����� //ELW������->ELW�ּ����޺���
	char elw_fixed_payment[22];                                     //ELWȮ�����޾�
	char elw_payment_agent[80];                                     //ELW���޴븮�θ�
	char price_evaluation_method_use_at_elw_maturity[200];                                     //�����򰡰��ݹ��
	char elw_rights_type_1[1];                                     //ELW�Ǹ����������ڵ�
	char elw_lp_holding_quantity[15];                                     //ELW_LP��������
	char filler[4];                                     //�ʷ���4
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_ELW_BATCH_DATA_SIZE = sizeof(ExturePlusElwELWBatchData);
#endif

#if(1)
//���� ��������
//(����A) STK : A001S
//(����C) STK :  A002S, A003S, A004S
//(����B) KSQ : A001Q
//(����B) KNX : A001X
//(�ֽ��Ļ�) STK : A001S
//(�ֽ��Ļ�) KSQ : A001Q
class ExturePlusElwMaster
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
const int EXTURE_PLUS_ELW_MASTER_SIZE = sizeof(ExturePlusElwMaster);
#endif

#if(1)
// (����A) STK : A701S
// (����C) STK :  A702S, A703S, A704S
// (����B) KSQ : A701Q
// (����B) KNX : A701X
// (�Ļ�A) DRV : A701F, A702F, A703F, A704F, A705F, A706F, A707F, A708F, A709F, A710F, A711F, A712F, A713F, A715F, A716F
class ExturePlusElwELWMarketOperationTS
{
    public:
		char  data_category[2]; //       �����ͱ��а�   
		char  infoMarketClass[3]; //       �������а�    
		char  distributeStockIndex[8]; //       �����й��Ϸù�ȣ     
		char  board_id[2]; //       ����ID     
		char  session_id[2]; //       ����ID     
		char  issue_code[12]; //       �����ڵ�     
		char  price_evaluation_method_when_elw_close_early[6]; //       �����й������ε���    
		char  trading_processing_time[12]; //       �Ÿ�ó���ð�   
		char  board_event_id[3]; //       �����̺�ƮID  
		char  start_time_of_board_event[9]; //       �����̺�Ʈ���۽ð�    
		char  board_event_group_code[5]; //       �����̺�Ʈ���뱺�ڵ�   
		char  trading_suspension_cause_code[3]; //       �ŷ����������ڵ�     
		char  end_text[1]; //       �����й�޼�������Ű����  
};
const int EXTURE_PLUS_ELW_ELW_MARKET_OPERATION_TS_SIZE = sizeof(ExturePlusElwELWMarketOperationTS);
#endif

#if(1)
// ELW �������� ����
// (����C) STK : M602S
class ExturePlusElwEarlyClosedELWBatchData
{
    public:
		char  data_category[2]; //       �����ͱ��а�   
		char  infoMarketClass[3]; //       �������а�    
		char  distributeStockIndex[8]; //       �����й��Ϸù�ȣ     
		char  issue_code[12]; //       �����ڵ�     
		char  base_price_for_occurrence_of_elw_early_closing[13]; //       ELW��������߻����ذ���    
		char  contents_of_elw_early_closing_right[200]; //       ELW��������Ǹ���系��    
		char  price_evaluation_method_when_elw_close_early[300]; //       ELW���������򰡹��  
		char  end_text[1]; //       �����й�޼�������Ű���� 
};
const int EXTURE_PLUS_ELW_EARLY_CLOSED_ELW_BATCH_DATA_SIZE = sizeof(ExturePlusElwEarlyClosedELWBatchData);
#endif

#if(1)
// ���� �켱ȣ�� (MM/LPȣ�� ����)
// (����C) STK : B702S, B703S, B704S XXXXX
class ExturePlusElwELWQuoteRecord
{
    public:
		char  askQuote[11]; //       �ŵ�n�ܰ�켱ȣ������  
		char  bidQuote[11]; //       �ż�n�ܰ�켱ȣ������  
		char  askQuoteVolume[12]; //       �ŵ�n�ܰ�켱ȣ���ܷ�  
		char  bidQuoteVolume[12]; //       �ż�n�ܰ�켱ȣ���ܷ�  
		char  askQuoteVolumeLP[12]; //       �ŵ�n�ܰ�LP�켱ȣ���ܷ�    
		char  bidQuoteVolumeLP[12]; //       �ż�n�ܰ�LP�켱ȣ���ܷ�
};
const int EXTURE_PLUS_ELW_ELW_QUOTE_RECORD_SIZE = sizeof(ExturePlusElwELWQuoteRecord);

class ExturePlusElwELWRemainingVolumeOnQuotesLPQuotesIncluded
{
    public:
		char  data_category[2]; //       �����ͱ��а�   
		char  infoMarketClass[3]; //       �������а�    
		char  distributeStockIndex[8]; //       �����й��Ϸù�ȣ     
		char  board_id[2]; //       ����ID     
		char  session_id[2]; //       ����ID     
		char  issue_code[12]; //       �����ڵ�     
		char  issue_seq_no[6]; //       �����й������ε���    
		char  trading_processing_time[12]; //       �Ÿ�ó���ð�   
		ExturePlusElwELWQuoteRecord rec[10];	// �ŵ�(��) �켱ȣ�� ����
		char  total_ask_order_remaining_after_market_closed[12]; //       �ŵ�ȣ�������ܰ��ܷ��հ�
		char  total_bid_order_remaining_after_market_closed[12]; //       �ż�ȣ�������ܰ��ܷ��հ� 
		char  estimated_trading_price[11]; //       ����ü�ᰡ
		char  estimated_trading_quantity[12]; //       ����ü�����   
		char  end_text[1]; //       �����й�޼�������Ű����  

};
const int EXTURE_PLUS_ELW_ELW_REMAINING_VOLUME_ON_QUOTES_LP_QUOTES_INCLUDED_SIZE = sizeof(ExturePlusElwELWRemainingVolumeOnQuotesLPQuotesIncluded);
#endif

#if(0)
//���� Snapshot (MM/LPȣ�� ����)
//���� ���庰 snapshot �� �������¸� ������������ ���� (MM/LPȣ�� ����)
//�ǽð� [�Ǵ� 0.2��/������ ������ 30�� sleep] * �ֱ⺯�� ����
//(����C) STK : B202S, B203S, B204S
class ExturePlusElwRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// �ŵ�n�ܰ�켱ȣ������
	char bidQuote[11];				// �ż�n�ܰ�켱ȣ������
	char askQuoteVolume[12];		// �ŵ�n�ܰ�켱ȣ���ܷ�
	char bidQuoteVolume[12];		// �ż�n�ܰ�켱ȣ���ܷ�
	char askQuoteVolumeLP[12];      // LP �ŵ�ȣ�� �ܷ�
	char bidQuoteVolumeLP[12];      // LP �ż�ȣ�� �ܷ�
};
const int EXTURE_PLUS_ELW_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExturePlusElwRecoveryTotalTradeRecord);

//���� Snapshot (MM/LPȣ�� ����)
//���� ���庰 snapshot �� �������¸� ������������ ���� (MM/LPȣ�� ����)
//�ǽð� [�Ǵ� 0.2��/������ ������ 30�� sleep] * �ֱ⺯�� ����
//(����C) STK : B202S, B203S, B204S
class ExturePlusElwRecoveryTotalTrade
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
	ExturePlusElwRecoveryTotalTradeRecord rec[10];  // �ŵ�(��) n�ܰ� �켱ȣ�� ����
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
	char earlyClosedELWStatus[1];                   // ELW �������Ῡ��
	char earlyClosedELWTime[9];                     // ELW ��������ð�
    char endText[1];     							// �����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExturePlusElwRecoveryTotalTrade);

class ExturePlusElwRecoveryTrade
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
        char lf[1];                                                                                        // 36   LF  X   1
};
const int EXTURE_PLUS_ELW_RECOVERY_TRADE_SIZE = sizeof(ExturePlusElwRecoveryTrade);
#endif

#if(1)
//MM/LP ����
//���� MM/LP ����
//05:30, 06:10, 06:50 3ȸ ����
//(����A) STK : I701S
//(����C) STK : I702S, I703S, I704S
//(����B) KSQ : I701Q
//(����B) KNX : I701X"
class ExturePlusElwKOSPI_LP_Information
{
	public:
	char  data_category[2];                     //�����ͱ��а�
	char  infoMarketClass[3];                     //�������а�
	char  distributeStockIndex[8];                     //�����й��Ϸù�ȣ
	char  issue_code[12];                     //�����ڵ�
	char  market_participant_number[5];                     //���������ڹ�ȣ
	char  lp_starting_date[8];                     //LP��������
	char  lp_expiration_date[8];                     //LP��������
	char  minimum_order_volume_multiple[11];                     //�ּ�ȣ���������
	char  maximum_order_volume_multiple[11];                     //�ִ�ȣ���������
	char  order_spread_unit_code[1];                     //ȣ��������������ڵ�
	char  order_spread_value[22];                     //ȣ������������Ѱ�
	char  market_close_for_holiday_order_spread_multiple[11];                     //����ȣ������������
	char  duty_order_submit_time_interval[6];                     //�ǹ�ȣ������ð�����
	char  bid_minumum_order_price[22];                     //�ŵ��ּ�ȣ���ݾ�
	char  ask_minimum_order_price[22];                     //�ż��ּ�ȣ���ݾ�
	char  minimum_order_price[22];                     //�ּ�ȣ���ݾ�
	char  maximum_order_price[22];                     //�ִ�ȣ���ݾ�
	char  endText[1];                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_KOSPI_LP_INFORMATION_SIZE = sizeof(ExturePlusElwKOSPI_LP_Information);
#endif

#if(1)
//ETN �����ȯ���� ����
//ETN �����ȯ���� ����
//05:30, 06:10, 06:50 3ȸ ����
//(����C) STK : X304S
class ExturePlusElwETNEarlyRedemptionCriteria
{
	public:
	char data_category[2];                        //�����ͱ��а�
	char infoMarketClass[3];                        //�������а�
	char distributeStockIndex[8];                        //�����й��Ϸù�ȣ
	char issue_code[12];                        //�����ڵ�
	char etn_early_redemption_period_code[2];                        //ETN�����ȯ�ֱ��ڵ�
	char early_redemption_appraisal_date[8];                        //�����ȯ������
	char early_redemption_criteria_relation_code[1];                        //�����ȯ���ǰ����ڵ�
	char early_redemption_base_index_1[10];                        //�����ȯ����1����
	char early_redemption_base_index_2[10];                        //�����ȯ����2����
	char early_redemption_price_before_expenses[23];                        //�����ȯ����
	char early_redemption_payment_date[8];                        //�����ȯ��������
	char endOfText[1];                        //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE = sizeof(ExturePlusElwETNEarlyRedemptionCriteria);
#endif

#if(1)
// ���� ü��
// (����A) STK : A301S
// (����C) STK : A302S, A303S, A304S
// (����B) KSQ : A301Q
// (����B) KNX : A301X
class ExturePlusElwELWOrderFilled
{
    public:
     char dataClass[2];                        //       �����ͱ��а�  
     char infoMarketClass[3];                        //       �������а�   
     char distributeStockIndex[8];                         //       �����й��Ϸù�ȣ    
     char board_id[2];                          //       ����ID    
     char session_id[2];                        //       ����ID    
     char issue_code[12];                       //       �����ڵ�    
     char issue_seq_no[6];                         //       �����й������ε���   
     char trading_time[12];   	   //       �Ÿ�ó���ð�  
     char price_change_against_previous_day_code[1];                           //       ���ϴ�񱸺��ڵ�    
     char price_change_against_previous_day[11];                              //       ���ϴ�񰡰�  
     char current_price[11];                       //       ü�ᰡ��    
     char trading_volume[10];                     //       �ŷ��� 
     char opening_price[11];                        //       �ð�  
     char high_price[11];                        //       ��  
     char low_price[11];                         //       ����  
     char accumulated_volume[12];                 //       �����ŷ���   
     char accumulated_traded_value[22];                 //       �����ŷ����  
     char final_bid_ask_category[1];              //       �����ŵ��ż������ڵ�  
     char lp_holding_quantity[15];                 //       LP��������  
     char ask_1_order[11];                      //       �ŵ��ֿ켱ȣ������   
     char bid_1_order[11];                      //       �ż��ֿ켱ȣ������   
     char endText[1];                          //       �����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_ELW_ORDER_FILLED_SIZE = sizeof(ExturePlusElwELWOrderFilled);
#endif

#if(1)
//�ŷ����� 5�� ȸ�� ���(B901S)
//(����A) STK : B901S
//(����C) STK : B902S, B903S, B904S
//(����B) KSQ : B901Q
//(����B) KNX : B901X
class ExturePlusElwELWTop5AskBidTradersActivityInformation
{
    public:
        char data_category[2];                  //DATA����  X   2
        char infoMarketClass[3];
        char issue_code[12];                    //�����ڵ�    X   12
        char issue_seq_no[6];                   //�Ϸù�ȣ    9   8
        char ask_member_number1[5];             //�ŵ��ŷ�����ȣ1    9   5
        char ask_trading_volume1[12];           //�ŵ�ü�����1 9   12
        char ask_trading_value1[22];            //�ŵ��ŷ����1 9   22
        char bid_member_number1[5];             //�ż��ŷ�����ȣ1    9   5
        char bid_trading_volume1[12];           //�ż�ü�����1 9   12
        char bid_trading_value1[22];            //�ż��ŷ����1 9   22
        char ask_member_number2[5];             //�ŵ��ŷ�����ȣ2    9   5
        char ask_trading_volume2[12];           //�ŵ�ü�����2 9   12
        char ask_trading_value2[22];            //�ŵ��ŷ����2 9   22
        char bid_member_number2[5];             //�ż��ŷ�����ȣ2    9   5
        char bid_trading_volume2[12];           //�ż�ü�����2 9   12
        char bid_trading_value2[22];            //�ż��ŷ����2 9   22
        char ask_member_number3[5];             //�ŵ��ŷ�����ȣ3    9   5
        char ask_trading_volume3[12];           //�ŵ�ü�����3 9   12
        char ask_trading_value3[22];            //�ŵ��ŷ����3 9   22
        char bid_member_number3[5];             //�ż��ŷ�����ȣ3    9   5
        char bid_trading_volume3[12];           //�ż�ü�����3 9   12
        char bid_trading_value3[22];            //�ż��ŷ����3 9   22
        char ask_member_number4[5];             //�ŵ��ŷ�����ȣ4    9   5
        char ask_trading_volume4[12];           //�ŵ�ü�����4 9   12
        char ask_trading_value4[22];            //�ŵ��ŷ����4 9   22
        char bid_member_number4[5];             //�ż��ŷ�����ȣ4    9   5
        char bid_trading_volume4[12];           //�ż�ü�����4 9   12
        char bid_trading_value4[22];            //�ż��ŷ����4 9   22
        char ask_member_number5[5];             //�ŵ��ŷ�����ȣ5    9   5
        char ask_trading_volume5[12];           //�ŵ�ü�����5 9   12
        char ask_trading_value5[22];            //�ŵ��ŷ����5 9   22
        char bid_member_number5[5];             //�ż��ŷ�����ȣ5    9   5
        char bid_trading_volume5[12];           //�ż�ü�����5 9   12
        char bid_trading_value5[22];            //�ż��ŷ����5 9   22
        char endOfText[1];                      //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_ELW_TOP_5_ASK_BID_TRADERS_ACTIVITY_INFORMATION_SIZE = sizeof(ExturePlusElwELWTop5AskBidTradersActivityInformation);
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
class ExturePlusElwKOSPIMarketOperationScheduleDisclosure
{
	public:
	char dataCategory[2];                               //�����ͱ��а�                             
	char infoMarketClass[3];                               //�������а�                            
	char marketCategory[3];                               //����ǰ�׷�ID                       
	char boardID[2];                               //����ID                                        
	char boardEventID[3];                               //�����̺�ƮID                             
	char boardEventBeginTime[9];                               //�����̺�Ʈ���۽ð�                
	char boardEventApplyCode[5];                               //�����̺�Ʈ���뱺�ڵ�              
	char sessionBeginEndCode[2];                               //���ǰ��������ڵ�                  
	char sessionID[2];                               //����ID                                      
	char issueCode[12];                               //�����ڵ�                                   
	char listedIssueCode[12];                               //����������ڵ�                       
	char productID[11];                               //��ǰID                                     
	char tradingHaltReasonCode[3];                               //�ŷ����������ڵ�                
	char tradingHaltOccurenceTypeCode[1];                               //�ŷ������߻������ڵ�     
	char stepApplied[2];                               //����ܰ�                                  
	char stepAppliedOccuredCode[1];                               //�������񰡰�����Ȯ��߻��ڵ�   
	char stepAppliedScheduleTime[9];                               //��������Ȯ�뿹���ð�          
	char endOfText[1];                               //�����й�޼�������Ű����                    
};
const int EXTURE_PLUS_ELW_KOSPI_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE = sizeof(ExturePlusElwKOSPIMarketOperationScheduleDisclosure);
#endif

#if(1)
//�����̺�Ʈ ����
//(����A) STK : I601S
//(����C) STK : I602S, I603S, I604S
//(����B) KSQ : I601Q
//(����B) KNX : I601X
//�ֽ�/ä�� ������ �ŷ�����, ��������, �����Ÿ� ���� �̺�Ʈ ����
//����ȸ���� (STK, KSQ) ���� �� �����ڻ� �ش����� ���͸� "
class ExturePlusElwKOSPIIssueEventInformation
{
    public:
	char data_category[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char distributeStockIndex[8];                                     //�����й��Ϸù�ȣ
	char issue_code[12];                                     //�����ڵ�
	char event_type_code[2];                                     //�̺�Ʈ�����ڵ�
	char event_occurrence_cause_code[4];                                     //�̺�Ʈ�߻������ڵ�
	char start_date_opening_date_application_date[8];                                     //�̺�Ʈ��������
	char expiration_date_ending_date[8];                                     //�̺�Ʈ��������
	char endOfText[1];                                     //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_KOSPI_ISSUE_EVENT_INFORMATION_SIZE = sizeof(ExturePlusElwKOSPIIssueEventInformation);
#endif

#if(1)
//ETN ���ͱ������� ����
//ETN ���ͱ������� ����
//05:30, 06:10, 06:50 3ȸ ����
//(����C) STK : X804S
class ExturePlusElwETNProfitStructureDetails
{
	public:
	char data_category[2];                        //�����ͱ��а�
	char infoMarketClass[3];                        //�������а�
	char distributeStockIndex[8];                        //�����й��Ϸù�ȣ
	char issue_code[12];                        //�����ڵ�
	char etn_profit_structure_details[2000];                        //ETN���ͱ�������
	char endOfText[1];                        //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE = sizeof(ExturePlusElwETNProfitStructureDetails);
#endif

#if(1)
// ETP��������  ETP�������� 2021.03.15  2021.03.15  202 ETP��������
class ExturePlusElwKOSPI_ETP_Constituents
{
    public:
        char data_category[2];                              // 1    DATA����
        char information_category[2];                       // 2    ��������
        char market_category[1];                            // 3    ���屸��
        char index_calculation_institution_code[2];         // 4    �����������ڵ�
        char index_market_classification_id[6];             // 5    ��������з�ID
        char index_seq_number[3];                           // 6    �����Ϸù�ȣ
        char index_leverage_inverse_type_code[2];           // 7    �������������ι��������ڵ�
        char index_name[80];                                // 8    ������
        char index_name_english[80];                        // 9    ����������
        char index_asset_classification_id_1[6];            // 10   �����ڻ�з�ID1
        char index_asset_classification_id_2[6];            // 11   �����ڻ�з�ID2
        char index_associated_market_type_code[1];          // 12   �����Ҽӽ��屸���ڵ�
        char industry_index_code[8];                        // 13   ���������ڵ�
        char endOfText[1];                                  // 14   FF
        char cr[1];                                         // 15   CR
        char lf[1];                                         // 16   LF
};
const int EXTURE_PLUS_KOSPI_ETP_CONSTITUENTS_SIZE = sizeof(ExturePlusElwKOSPI_ETP_Constituents);
#endif

#if(1)
class ExturePlusElwKOSPI_ETP_ToTalConstituents
{
	public:
	char data_category[2];                                 //�����ͱ��а�
	char infoMarketClass[3];                                 //�������а�
	char distributeStockIndex[8];                                 //�����й��Ϸù�ȣ
	char index_calculation_institution_code[2];                                 //�����������ڵ�
	char index_market_classification_id[6];                                 //��������з�ID
	char index_seq_number[3];                                 //�����Ϸù�ȣ
	char index_leverage_inverse_type_code[2];                                 //�������������ι��������ڵ�
	char index_name[80];                                 //������
	char index_name_english[80];                                 //����������
	char index_asset_classification_id_1[6];                                 //�����ڻ�з�ID1
	char index_asset_classification_id_2[6];                                 //�����ڻ�з�ID2
	char jisuID[6];                                 //����ID
	char filler[4];                                 //�ʷ���4
	char endOfText[1];                                 //�����й�޼�������Ű����
};
const int EXTURE_PLUS_KOSPI_ETP_TOTAL_CONSTITUENTS_SIZE = sizeof(ExturePlusElwKOSPI_ETP_ToTalConstituents);
#endif

#if(1)
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� ������������(Ȯ��ġ)	F101S
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� ������������(Ȯ��ġ)	F101Q
class ExturePlusElwKospiForeignerInvestmentInformationForEachIssueConfirmedData
{
	public:
	char data_category[2];                                       //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char issue_code[12];                                         //�����ڵ�
	char serialNo[8];                                            //�Ϸù�ȣ
	char trading_date[8];                                        //�Ÿ�����
	char issue_limit_ratio[5];                                   //�����ѵ�����
	char individual_limit_ratio[5];                              //�����ѵ�����
	char number_of_listed_stock[15];                             //�����ֽļ�
	char available_quantity_for_order[15];                       //�ֹ����ɼ���
	char limit_exhaustion_type[1];                               //�ѵ���������
	char filler[5];                                              //FILLER
	char endText[1];                                             //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_KOSPI_FOREIGNER_INVESTMENT_INFORMATION_FOR_EACH_ISSUE_CONFIRMED_DATA_SIZE = sizeof(ExturePlusElwKospiForeignerInvestmentInformationForEachIssueConfirmedData);
#endif

#if(1)
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� Ȯ��ġ������������	F401S
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� Ȯ��ġ������������	F401Q
class ExturePlusElwKospiForeignerConfirmedDataRetransmission
{
	public:
	char data_category[2];                                       //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char issue_code[12];                                         //�����ڵ�
	char issue_limit_ratio[5];                                   //�����ѵ�����
	char individual_limit_ratio[5];                              //�����ѵ�����
	char number_of_listed_stock[15];                             //�����ֽļ�
	char available_quantity_for_order[15];                       //�ֹ����ɼ���
	char limit_exhaustion_type[1];                               //�ѵ���������
	char filler[1];                                              //FILLER
	char endText[1];                                             //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_KOSPI_FOREIGNER_CONFIRMED_DATA_RETRANSMISSION_SIZE = sizeof(ExturePlusElwKospiForeignerConfirmedDataRetransmission);
#endif

#if(1)
//���񸶰�	���庰 ���񸶰��� ����
//�ǽð�	
//(����A) STK : A601S
//(����C) STK : A602S, A603S, A604S
//(����B) KSQ : A601Q
//(����B) KNX : A601X
class ExturePlusElwELWIssueClosing
{
	public:
	char data_category[2];                 //DATA����
	char infoMarketClass[3];               //�������а�
	char distributeStockIndex[8];          //�����й��Ϸù�ȣ
	char board_id[2];          //����ID
	char issue_code[12];          //�����ڵ�
	char closing_price[11];          //���񸶰�����
	char closing_price_type_code[1];          //���������ڵ�
	char maximum_limit_price_for_the_single_price_trades[11];          //���񸶰��ð��ܴ��ϰ����Ѱ�
	char minimum_limit_price_for_the_single_price_trades[11];          //���񸶰��ð��ܴ��ϰ����Ѱ�
	char weighted_average_price[11];          //���񸶰���հ����ְ�
	char buy_in_base_price[11];          //���񸶰������ε����ذ���
	char buy_in_upper_limit[11];          //���񸶰������ε����Ѱ�
	char buy_in_lower_limit[11];          //���񸶰������ε����Ѱ�
	char endOfText[1];          //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_ELW_ISSUE_CLOSING_SIZE = sizeof(ExturePlusElwELWIssueClosing);
#endif

#if(0)
// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 12  ELW ���񸶰�    A6021   ELW_���񸶰�    90  �ǽð�
// ���� ������ �������� �����
class ExturePlusElwELWIssueClosing
{
    public:
        char data_category[2];                                       // 1   DATA����  X   2
        char information_category[2];                                // 2   ��������    X   2
        char market_category[1];                                     // 3   ���屸��    X   1
        char issue_code[12];                                         // 4   �����ڵ�    X   12
        char issue_seq_no[5];                                        // 5   �����Ϸù�ȣ  9   5
        char board_id[2];                                            // 6   ����ID    X   2
        char closing_price[9];                                       // 7   ���񸶰�����  9   9
        char closing_price_type_code[1];                             // 8   ���񸶰����ݱ����ڵ�  X   1
        char maximum_limit_price_for_the_single_price_trades[9];     // 9   ���񸶰��ð��ܴ��ϰ����Ѱ� 9   9
        char minimum_limit_price_for_the_single_price_trades[9];     // 10  ���񸶰��ð��ܴ��ϰ����Ѱ� 9   9
        char weighted_average_price[9];                              // 11  ���񸶰���հ����ְ�  9   9
        char buy_in_base_price[9];                                   // 12  �����ε����ذ���    9   9
        char buy_in_upper_limit[9];                                  // 13  �����ε����Ѱ� 9   9
        char buy_in_lower_limit[9];                                  // 14  �����ε����Ѱ� 9   9
        char filler[1];                                              // 15  FILLER  X   1
        char ff[1];                                                  // 16  FF  X   1
        char cr[1];                                                  // 17  CR
        char lf[1];                                                  // 18  LF

};
const int EXTURE_PLUS_ELW_ELW_ISSUE_CLOSING_SIZE = sizeof(ExturePlusElwELWIssueClosing);
#endif

#if(0)
// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 10   �ڽ����ֽ������������� A8011   �ڽ���_�������� -> �ڽ���_�ֽ�������������    122 �ǽð� ���������ֽ�ü������
// ���� ������ �������� �����
class ExturePlusElwKOSPIIssueInformationDisclosure
{
    public:
        char data_category[2];                                                              // 1    DATA����  X   2
        char information_category[2];                                                       // 2    ��������    X   2
        char market_category[1];                                                            // 3    ���屸��    X   1
        char issue_code_[12];                                                               // 4    �����ڵ�    X   12
        char issue_seq_no[5];                                                               // 5    �����Ϸù�ȣ  9   5
        char disclosure_data_type_code[3];                                                  // 6    �������������ڵ�    X   3
        char board_id[2];                                                                   // 7    ����ID    X   2
        char basis_price[9];                                                                // 8    ���ذ���    9   9
        char upper_limit_price[9];                                                          // 9    ���Ѱ� 9   9
        char lower_limit_price[9];                                                          // 10   ���Ѱ� 9   9
        char evaluation_price[9];                                                           // 11   �򰡰���    9   9
        char highest_order_price[9];                                                        // 12   �ְ�ȣ������  9   9
        char lowest_order_price[9];                                                         // 13   ����ȣ������  9   9
        char opening_price_becomes_basis_price_type[1];                                     // 14   �ð����ذ��ݿ���    X   1
        char back_door_listing[2];                                                          // 15   �������ڵ�   X   2
        char par_value_change_type_code[2];                                                 // 16   �׸鰡���汸���ڵ�   X   2
        char lot_size[11];                                                                  // 17   �Ÿż�������  9   11
        char number_of_listed_stocks[16];                                                   // 18   �����ֽļ�   9   16
        char liquidation_of_trades_designation_administrative_issue_designation[1];         // 19   �����Ÿ�/�������� ��������    X   1
        char closing_price_possibility_in_pre_off_hours_session[1];                         // 20   �尳�����ð������� ���ɿ���    X   1
        char filler[4];                                                                     // 21   FILLER  X   4
        char ff[1];                                                                         // 22   FF  X   1
        char cr[1];                                                                         // 23   CR  X   1
        char lf[1];                                                                         // 24   LF  X   1
};
const int EXTURE_PLUS_ELW_KOSPI_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExturePlusElwKOSPIIssueInformationDisclosure);
#endif

#if(1)
//�ֽ�������������
//�ֽ� ���� ���� �������� ��ġ�� �߻������� ����
//�������������ڵ� : �����й�� ������ �ʿ�
//�ǽð�
//(����A) STK : A801S
//(����C) STK : A802S, A803S, A804S
//(����B) KSQ : A801Q
//(����B) KNX : A801X
class ExturePlusElwKOSPIIssueInformationDisclosure
{
    public:
	char data_category[2];                   //DATA����
	char infoMarketClass[3];                 //��������
	char issue_code_[12];                    //�����ڵ�
	char issue_seq_no[6];                    //�����й������ε���
	char disclosure_data_type_code[3];       //�������������ڵ尪
	char board_id[2];                        //����ID
	char basis_price[11];                    //���ذ���
	char upper_limit_price[11];              //���Ѱ�
	char lower_limit_price[11];              //���Ѱ�
	char evaluation_price[11];               //�򰡰���
	char highest_order_price[11];            //�ְ�ȣ������
	char lowest_order_price[11];             //����ȣ������
	char opening_price_becomes_basis_price_type[1];                   //�ð����ذ��ݿ���
	char back_door_listing[2];                                        //�������ڵ�
	char par_value_change_type_code[2];                               //�׸鰡���汸���ڵ�
	char lot_size[11];                                                //��������
	char number_of_listed_stocks[16];                                 //�����ֽļ�
	char liquidation_of_trades_designation_administrative_issue_designation[1];                   //��������
	char closing_price_possibility_in_pre_off_hours_session[1];                                   //�尳�����ð����������ɿ���
	char endText[1];                                                                              //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_KOSPI_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExturePlusElwKOSPIIssueInformationDisclosure);
#endif

#if(0)
// ELW_�ǽð�_���ͳ�(KRX)_20141117_2014092901.xls
// 6    ELW ������ǥ    C6021   ELW ������ǥ    82  �ǽð� ��������ELW������ǥ����
// ���� ������ �������� �����
class ExturePlusElwELWInvestmentIndicatorInformation
{
    public:
        char data_category[2];                  // 1    DATA����  X   2
        char information_category[2];           // 2    ��������    X   2
        char market_category[1];                // 3    ���屸��    X   1
        char elw_issue_code[12];                // 4    �����ڵ�    X   12
        char issue_seq_no[8];                   // 5    �Ϸù�ȣ    9   8
        char calculate_time[6];                 // 6    �� �ð�    X   6
        char parity[8];                         // 7    �и�Ƽ 9   8
        char gearing_ratio[8];                  // 8    ������   9   8
        char break_even_ratio_code[1];          // 9    ���ͺб��� ��ȣ    X   1
        char break_even_ratio[7];               // 10   ���ͺб���   9   7
        char capital_support_point_sign[1];     // 11   �ں������� ��ȣ    X   1
        char capital_support_point[7];          // 12   �ں�������   9   7
        char basket_stock_price[11];            // 13   �ٽ����ְ�   9   11
        char filler[5];                         // 14   FILLER  X   5
        char ff[1];                             // 15   FF  X   1
        char cr[1];                             // 16   CR  X   1
        char lf[1];                             // 17   LF  X   1

};
const int EXTURE_PLUS_ELW_ELW_INVESTMENT_INDICATOR_INFORMATION_SIZE = sizeof(ExturePlusElwELWInvestmentIndicatorInformation);
#endif

#if(1)
//ELW������ǥ
//����� ELW������ǥ �۽�
//�ǽð�����
//C602S
class ExturePlusElwELWInvestmentIndicatorInformation
{
	public:
	char data_category[2];                  //�����ͱ��а�
	char infoMarketClass[3];                //�������а�
	char elw_issue_code[12];                //�����ڵ�
	char issue_seq_no[8];                   //�Ϸù�ȣ
	char calculate_time[6];                 //��������ð�
	char parity[9];                         //�и�Ƽ��
	char gearing_ratio[9];                  //������
	char break_even_ratio_code[1];          //���ͺб�����ȣ
	char break_even_ratio[8];               //���ͺб���
	char capital_support_point_sign[1];     //�ں���������ȣ
	char capital_support_point[8];          //�ں�������
	char basket_stock_price[12];            //�ٽ����ְ�
	char endOfText[1];                      //�����й�޼�������Ű����
};
const int EXTURE_PLUS_ELW_ELW_INVESTMENT_INDICATOR_INFORMATION_SIZE = sizeof(ExturePlusElwELWInvestmentIndicatorInformation);
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

#if(1)
//���� ��������
//(����A) STK : A001S
//(����C) STK :  A002S, A003S, A004S
//(����B) KSQ : A001Q
//(����B) KNX : A001X
//(�ֽ��Ļ�) STK : A001S
//(�ֽ��Ļ�) KSQ : A001Q
class ExtureGroupCMaster
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
const int EXTURE_GROUP_C_MASTER_SIZE = sizeof(ExtureGroupCMaster);

//���� ���� �� ������ǥ
//(����A) STK : CA01S
//(����B) KSQ : CA01Q
//(�ֽ��Ļ�) STK : CA01S
//(�ֽ��Ļ�) KSQ : CA01Q
class ExtureGroupCJisuMaster
{
    public:
	char dataClass[2];                  //�����й� �����͸� �ĺ��ϴ� ���� �ڵ尪
	char infoMarketClass[3];            //�����й迡�� �й��ϴ� ������ ���� �ڵ尪
	char distributeStockIndex[8];		//�����й迡�� �ο��ϴ� �Ϸù�ȣ
										//�ü� : ���� ���庰 �ο� (�� ��뷮 ���񽺿��� ����)
										//�������� :  �������а��� �ο�
										//��Ÿ : �����ͱ��а��� �ο�
	char stockCode[12];         //�����ڵ�
	char stockSeq[6];           //�Ϸù�ȣ
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
const int EXTURE_GROUP_C_JISU_MASTER_SIZE = sizeof(ExtureGroupCJisuMaster);
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
class ExtureGroupCMarketOperationTS
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
const int EXTURE_GROUP_C_MARKET_OPERATION_TS_SIZE = sizeof(ExtureGroupCMarketOperationTS);
#endif

#if(1)
//��������������/��ġ/FTP
//��������������/��ġ/FTP
class ExtureGroupCInvestorStock
{
    public:
        char dataClass[2];                                              // 001 DATA����
        char infoClass[2];                                              // 002 ��������
        char marketClass[1];                                            // 003 ���屸��
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
const int EXTURE_GROUP_C_INVESTOR_STOCK_SIZE = sizeof(ExtureGroupCInvestorStock);
#endif

#if(1)
//���ڰ���
//(����A) STK  : F000S, E900S
//(����A) KSQ  : F000Q, E900Q
//(����A) KNX  : F000X, E900X
//(����A) OTHERS : F0909, E9909
//���ڰ��� (�¶���)    : F0
//���� ���ڰ��� (��ġ) : E9
class ExtureGroupCPublicNews
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
const int EXTURE_GROUP_C_PUBLIC_NEWS_SIZE = sizeof(ExtureGroupCPublicNews);
#endif

#if(1)
//�����̺�Ʈ ����
//(����A) STK : I601S
//(����C) STK : I602S, I603S, I604S
//(����B) KSQ : I601Q
//(����B) KNX : I601X
//�ֽ�/ä�� ������ �ŷ�����, ��������, �����Ÿ� ���� �̺�Ʈ ����
//����ȸ���� (STK, KSQ) ���� �� �����ڻ� �ش����� ���͸� "
class ExtureGroupCKOSPIIssueEventInformation
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
const int EXTURE_GROUP_C_KOSPI_ISSUE_EVENT_INFORMATION_SIZE = sizeof(ExtureGroupCKOSPIIssueEventInformation);
#endif

#if(1)
//���ŵ�����
//(����A) STK : I801S
//(����C) STK : I802S, I803S, I804S
//(����B) KSQ : I801Q
//(����B) KNX : I801X
class ExtureGroupCShortSellingInformation
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
const int EXTURE_GROUP_C_SHORT_SELLING_INFORMATION_SIZE = sizeof(ExtureGroupCShortSellingInformation);
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
class ExtureGroupCMarketOperationScheduleDisclosure
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
const int EXTURE_GROUP_C_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE = sizeof(ExtureGroupCMarketOperationScheduleDisclosure);
#endif

#if(1)
//�ڽ���_�����������(VI)
//VI �ߵ�/���� ����
//(����A) STK : R801S
//(����C) STK : R803S, R804S
//(����B) KSQ : R801Q
//VI (Volatility Interruption) �ߵ�/���� ����
class ExtureGroupCKOSPIVolatilityInterruptionPerInstrument
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
const int EXTURE_GROUP_C_KOSPI_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE = sizeof(ExtureGroupCKOSPIVolatilityInterruptionPerInstrument);
#endif

#if(1)
//�ڽ��� �尳���� ȣ���ܷ�//�ֽ� �������ϰ��Ÿ� ȣ���ܷ�(B801S)
//(����A) STK : B801S
//(����C) STK : B802S, B803S, B804S
//(����B) KSQ : B801Q
//(����B) KNX : B801X
class ExtureGroupCQuoteBefore
{
    public:

	char dataClass[2];                        //�����ͱ��а�
	char infoMarketClass[3];                        //�������а�
	char distributeStockIndex[8];                        //�����й��Ϸù�ȣ
	char boardID[2];                        //����ID
							 //��ǰ�� �ŷ��Ǵ� ����� ���带 �ĺ��ϱ� ���� ID. 
						 //���� ��ǰ�̶� ���� ���忡�� �������� �޸��ϰ� 
						 //�������� �ŸŽ������ �Ÿű�Ģ�Ͽ� ������ �������� �ŷ��� �� ������ 
						 //������(���κ���), 
						 //����/�� �ð�������, 
						 //�ð��ܴ��ϰ�, 
						 //����/��/�� �뷮�Ÿ� ���� ���忡 �ش���
	char stockCode[12];                        //�����ڵ�
	char serialNo[6];                        //�����й������ε���
	char tradeTime[12];                        //�Ÿ�ó���ð�
	char accmTradeVolume[12];                        //�����ŷ���
	char totalAskQouteVolume[12];                        //�ŵ�ȣ�����ܷ�
	char totalBidQuoteVolume[12];                        //�ż�ȣ�����ܷ�
	char endOfText[1];                        //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_QUOTE_BEFORE_SIZE = sizeof(ExtureGroupCQuoteBefore);
#endif

#if(1)
//������ �����ں� ���//������ �����ں� ���
//09:00~18:00 [90�� �ֱ�]
//(����A) STK : C001S
//(����B) KSQ : C001Q
//(����B) KNX : C001X
class ExtureGroupCTotalInvestorIndex
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
const int EXTURE_GROUP_C_TOTAL_INVESTOR_INDEX_SIZE = sizeof(ExtureGroupCTotalInvestorIndex);
#endif

#if(1)
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� ������������(Ȯ��ġ)	F101S
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� ������������(Ȯ��ġ)	F101Q
class ExtureGroupCForeignerMaster
{
	public:
	char dataClass[2];                                       //�����ͱ��а�
	char infoMarketClass[3];                                 //�������а�
	char stockCode[12];                                      //�����ڵ�
	char serialNo[8];                                        //�Ϸù�ȣ
	char tradeDate[8];                                       //�Ÿ�����
	char stockLimitRate[5];                                  //�����ѵ�����
	char individualLimitRate[5];                             //�����ѵ�����
	char listingStockSize[15];                               //�����ֽļ�
	char orderPossibilityVolume[15];                         //�ֹ����ɼ���
	char limitExhaustClass[1];                               //�ѵ���������
	char filler[5];                                          //FILLER
	char endText[1];                                         //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_FOREIGNER_MASTER_SIZE = sizeof(ExtureGroupCForeignerMaster);
#endif

#if(1)
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� Ȯ��ġ������������	F401S
//�ڽ��� ����	�ܱ��� ��������	�ڽ��� �ܱ��� Ȯ��ġ������������	F401Q
class ExtureGroupCForeignerMasterUpdate
{
	public:
	char dataClass[2];                                       //�����ͱ��а�
	char infoMarketClass[3];                                 //�������а�
	char stockCode[12];                                      //�����ڵ�
	char stockLimitRate[5];                                  //�����ѵ�����
	char individualLimitRate[5];                             //�����ѵ�����
	char listingStockSize[15];                               //�����ֽļ�
	char orderPossibilityVolume[15];                         //�ֹ����ɼ���
	char limitExhaustClass[1];                               //�ѵ���������
	char filler[1];                                          //FILLER
	char endText[1];                                         //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_FOREIGNER_MASTER_UPDATE_SIZE = sizeof(ExtureGroupCForeignerMasterUpdate);
#endif

#if(1)
//�ڽ��� ����	ETP����
//ETN �繫��Ź����	
//S104S
class ExtureGroupCETNTransferAgentBatchData
{
	public:
	char dataCategory[2];                                        //�����ͱ��а�
	char infoMarketClass[3];                                     //�������а�
	char issueCode[12];                                          //�����ڵ�
	char seqNumber[8];                                           //�Ϸù�ȣ
	char finalIndexValue[9];                                     //������ǥ��ġ
	char indexValueInSumOfMoney[15];                             //��ǥ��ġ�ݾ�
	char previousDayTaxableBasicPrice[9];                        //���ϰ�ǥ���ذ���
	char previousDayTaxableBasicPriceBeforeDividend[9];          //���Ϲ������ǥ���ذ���
	char previousDayCashDividendPrice[12];                       //�������ݹ��ݾ�
	char aDayBeforePreviousDayTaxableBasicPrice[9];              //�����ϰ��ݰ�ǥ���ذ���
	char volatilityFuturesType[2];                               //��������������
	char minimumQuantityOfCall[10];                              //�ߵ���ȯû���ּҼ���
	char interestRateOfCall[10];                                 //�ߵ���ȯ��������
	char expenses[9];                                            //�����
	char filler[10];                                             //FILLER
	char endText[1];                                             //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_ETN_TRANSFER_AGENT_BATCH_DATA_SIZE = sizeof(ExtureGroupCETNTransferAgentBatchData);
#endif

#if(1)
//�ڽ��� ����,ETP����,ETN �������� ��������	S204S
class ExtureGroupCETNIndexCompositionConstituents
{
	public:
	char dataCategory[2];                                     //�����ͱ��а�
	char infoMarketClass[3];                                  //�������а�
	char ETNIssueCode[12];                                    //�����ڵ�
	char dataSeqNumber[8];                                    //������ �Ϸù�ȣ
	char date[8];                                             //����
	char officeConsignmentCompanyRegistrationNumber[3];       //�繫��Źȸ���ȣ
	char numberOfCompositionConstituents[4];                  //���������
	char compositionConstituentsCode[12];                     //���������ڵ�
	char nameOfCompositionConstituents[80];                   //���������
	char compositionRate[7];                                  //������
	char filler[60];                        //FILLER
	char endText[1];                        //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE = sizeof(ExtureGroupCETNIndexCompositionConstituents);
#endif

#if(1)
//�ڽ��� ����,ETP����,ETN IIV,S304S
class ExtureGroupCETN_IIV
{
	public:
	char dataCategory[2];                 //�����ͱ��а�
	char infoMarketClass[3];              //�������а�
	char ETNIssueCode[12];                //�����ڵ�
	char hours[6];                        //�ð�
	char previousDayIV[9];                //���� IV
	char duringMarketHoursFinalIV[9];     //����/���� IV
	char filler[28];                      //FILLER
	char endText[1];                      //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_ETN_IIV_SIZE = sizeof(ExtureGroupCETN_IIV);
#endif

#if(1)
//�ڽ��� ����,ETP����,ETF �繫��Ź��ġ,N803S
class ExtureGroupCETFWorkEntrustmentBatch
{
	public:
	char dataClass[2];                                          //�����ͱ��а�
	char infoMarketClass[3];                                    //�������а�
	char stockCode[12];                                         //�����ڵ�
	char seiralNo[8];                                           //�Ϸù�ȣ
	char ETFCurrencyStockSize[10];                              //ETF�����ֽļ�
	char ETFCunrencyNetAssetsTotalAmount[15];                                  //ETF������ڻ��Ѿ�
	char ETFNetAssetsTotalAmount[15];                                          //ETF���ڻ��Ѿ�
	char ETFLastNetAssetsValue[9];                                             //ETF�������ڻ갡ġ
	char ETFForeignMoneyCurrencyNetConAssetsTotalAmount[15];                               //ETF��ȭ������ڻ��Ѿ�
	char ETFForeignMoneyNetAssetsTotalAmount[15];                                          //ETF��ȭ���ڻ��Ѿ�
	char ETFForeignMoneyLastNetAssetsValue[9];                                            //ETF��ȭ�������ڻ갡ġ
	char ETFCreationUnit[8];                                          //ETF CU����
	char prevDayScorecardStandardPrice[9];                            //���ϰ�ǥ���ذ���
	char prevPrevDayDividendScorecardStandardPrice[9];                //���Ϲ������ǥ���ذ���
	char prevDayCashDividend[12];                                     //�������ݹ��ݾ�
	char prevPrevDayScorecardStandardPrice[9];                        //�����ϰ�ǥ���ذ���
	char gStockprevDayScorecardStandardPrice[9];                      //�ؿ��ֽ����Ϻ������ǥ���ذ�
	char gStockprevDayDividendScorecardStandardPrice[9];              //�ؿ��ֽ����Ϻ�����������ǥ���ذ�
	char gStockprePrevDayScorecardStandardPrice[9];                   //�ؿ��ֽĺ���������ϰ�ǥ���ذ�
	char filler[62];                                          //FILLER
	char endText[1];                                          //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_ETF_WORK_ENTRUSTMENT_BATCH_SIZE = sizeof(ExtureGroupCETFWorkEntrustmentBatch);
#endif

#if(1)
//�ڽ��� ����,ETP����,ETF PDF,F803S
class ExtureGroupCETF_PDF
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
const int EXTURE_GROUP_C_ETF_PDF_SIZE = sizeof(ExtureGroupCETF_PDF);
#endif

#if(1)
// ������
//(����A) STK : B501S
//(����B) KSQ : B501Q
//(����B) KNX : B501X 
class ExtureGroupCUpDown
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
const int EXTURE_GROUP_C_UPDOWN_SIZE = sizeof(ExtureGroupCUpDown);
#endif

#if(1)
//�������� ����
//IA000(����������)
//IB000(��������)
class ExtureGroupCTotalElwIndex
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
const int EXTURE_GROUP_C_TOTAL_ELW_INDEX_SIZE = sizeof(ExtureGroupCTotalElwIndex);
#endif

#if(1)
//���ǰŷ� ���(TO-BE)//�ڽ��Ǵ뷮ü��(C4011)(AS-IS)
//���ǰŷ� ���//���� ���庰 ���ǰŷ� ����(�����ŷ�����)
//������ �� 2ȸ	
//(����A) STK : C401S
//(����C) STK : C402S, C403S, C404S
//(����B) KSQ : C401Q
//(����B) KNX : C401X
class ExtureGroupCTotalBulkTrade
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
const int EXTURE_GROUP_C_TOTAL_BULK_TRADE_SIZE = sizeof(ExtureGroupCTotalBulkTrade);
#endif

#if(1)
// ���� ü��
// (����A) STK : A301S
// (����C) STK : A302S, A303S, A304S
// (����B) KSQ : A301Q
// (����B) KNX : A301X
class ExtureGroupCTrade
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
const int EXTURE_GROUP_C_TRADE_SIZE = sizeof(ExtureGroupCTrade);
#endif

#if(1)
//���ذ�����
//(����A) STK : A401S
//(����C) STK : A402S, A403S, A404S
//(����B) KSQ : A401Q
//(����B) KNX : A401X
//�򰡰��� ��� ������ ���ذ������� ����
class ExtureGroupCKOSPIDeterminedBasePrice
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
const int EXTURE_GROUP_C_KOSPI_DETERMINED_BASE_PRICE_SIZE = sizeof(ExtureGroupCKOSPIDeterminedBasePrice);
#endif

#if(1)
// ���� �켱ȣ�� (MM/LPȣ�� ����)
// (����A) STK : B601S
// (����B) KSQ : B601Q
// (����B) KNX : B601X
class ExtureGroupCQuoteRecord
{
    public:
	char askQuote[11];	                // �ŵ�n�ܰ�켱ȣ������
	char bidQuote[11];                  // �ż�n�ܰ�켱ȣ������
	char askQuoteVolume[12];            // �ŵ�n�ܰ�켱ȣ���ܷ�
	char bidQuoteVolume[12];            // �ż�n�ܰ�켱ȣ���ܷ�
};
const int EXTURE_GROUP_C_QUOTE_RECORD_SIZE = sizeof(ExtureGroupCQuoteRecord);

class ExtureGroupCQuote10
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
     ExtureGroupCQuoteRecord rec[10];			// �ŵ�(��) n�ܰ� �켱ȣ�� ���� 
     char totalAskQuoteRemainder[12];     //       �ŵ�ȣ�������ܰ��ܷ��հ�    
     char totalBidQuoteRemainder[12];     //       �ż�ȣ�������ܰ��ܷ��հ�    
     char estimatedTradePrice[11];    //       ����ü�ᰡ   
      char estimatedTradeVolume[12];      //       ����ü�����  
     char endText[1];     //       �����й�޼�������Ű����    
};
const int EXTURE_GROUP_C_QUOTE10_SIZE = sizeof(ExtureGroupCQuote10);
#endif

#if(1)
//�ڽ��� �ŷ���//�ŷ����� 5�� ȸ�� ���(B901S)
//(����A) STK : B901S
//(����C) STK : B902S, B903S, B904S
//(����B) KSQ : B901Q
//(����B) KNX : B901X
class ExtureGroupCSecuritiesTradeRecord
{
    public:
        char askSecuritiesTradeNumber[5];                             // 006-1 �ŵ��ŷ�����ȣ
        char askTradeVolume[12];                                      // 006-2 �ŵ�ü�����
        char askTradeAmount[22];                                      // 006-3 �ŵ��ŷ����
        char bidSecuritiesTradeNumber[5];                             // 006-4 �ż��ŷ�����ȣ
        char bidTradeVolume[12];                                      // 006-5 �ż�ü�����
        char bidTradeAmount[22];                                      // 006-6 �ż��ŷ����
};
const int EXTURE_GROUP_C_SECURITIES_TRADE_RECORD_SIZE = sizeof(ExtureGroupCSecuritiesTradeRecord);

class ExtureGroupCSecuritiesTrade
{
    public:
        char dataClass[2];                                            //�����ͱ��а�
        char infoMarketClass[3];                                            //�������а�
        char stockCode[12];                                           //�����ڵ�
		char serialNo[6];                                             //�����й������ε���
        ExtureGroupCSecuritiesTradeRecord rec[5];                   //�ŷ������� OCCURS 5
        char endOfText[1];                                               //�����й�޼�������Ű����
};
const int EXTURE_GROUP_C_SECURITIES_TRADE_SIZE = sizeof(ExtureGroupCSecuritiesTrade);
#endif

#if(1)
//�ֽ�������������
//(����A) STK : A801S
//(����C) STK : A802S, A803S, A804S
//(����B) KSQ : A801Q
//(����B) KNX : A801X
class ExtureGroupCIssueInformationDisclosure
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
const int EXTURE_GROUP_C_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExtureGroupCIssueInformationDisclosure);
#endif

#if(1)
//���α׷��Ÿ� ��ü����
//(����A) STK : J001S
//(����B) KSQ : J001Q
//���α׷��Ÿ� ��ü����
//�������� : �������� �������
//���������� : K200 or Q150 or KRX300 �������"
class ExtureGroupCProgramTradeTotal
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
const int EXTURE_GROUP_C_PROGRAM_TRADE_TOTAL_SIZE = sizeof(ExtureGroupCProgramTradeTotal);
#endif

#if(1)
//���α׷��Ÿ� ȣ��//���α׷��Ÿ� ��������
//(����A) STK : C301S
//(����B) KSQ : C301Q
//���α׷��Ÿ� ��������
//�������� : �������� �������
//���������� : K200 or Q150 or KRX300 �������
class ExtureGroupCProgramTrade
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
const int EXTURE_GROUP_C_PROGRAM_TRADE_SIZE = sizeof(ExtureGroupCProgramTrade);
#endif

#if(1)
//�������	
//(����A) STK : O601S
//(����C) STK : O602S, O603S, O604S
//(����B) KSQ : O601Q
//(����B) KNX : O601X
//(�Ļ�A) DRV : O601F, O603F
//���ϰ�ü���� ��/���Ѱ��� �����Ǵ� ��� ��/���Ѱ� �ż�, �ŵ��ֹ��� ���� �������� ������ ���������� ����Ͽ� ü���Ű�� ���
class ExtureGroupCQuantityAllocation
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
const int EXTURE_GROUP_C_QUANTITY_ALLOCATION_SIZE = sizeof(ExtureGroupCQuantityAllocation);
#endif
#if(1)
//���� Snapshot (MM/LPȣ�� ����)
//���� ���庰 snapshot �� �������¸� ������������ ���� (MM/LPȣ�� ����)
//�ǽð� [�Ǵ� 0.2��/������ ������ 30�� sleep] * �ֱ⺯�� ����
//(����C) STK : B202S, B203S, B204S
class ExtureGroupCRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// �ŵ�n�ܰ�켱ȣ������
	char bidQuote[11];				// �ż�n�ܰ�켱ȣ������
	char askQuoteVolume[12];		// �ŵ�n�ܰ�켱ȣ���ܷ�
	char bidQuoteVolume[12];		// �ż�n�ܰ�켱ȣ���ܷ�
	char askQuoteVolumeLP[12];      // LP �ŵ�ȣ�� �ܷ�
	char bidQuoteVolumeLP[12];      // LP �ż�ȣ�� �ܷ�
};
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExtureGroupCRecoveryTotalTradeRecord);

//���� Snapshot (MM/LPȣ�� ����)
//���� ���庰 snapshot �� �������¸� ������������ ���� (MM/LPȣ�� ����)
//�ǽð� [�Ǵ� 0.2��/������ ������ 30�� sleep] * �ֱ⺯�� ����
//(����C) STK : B202S, B203S, B204S
class ExtureGroupCRecoveryTotalTrade
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
	ExtureGroupCRecoveryTotalTradeRecord rec[10];  // �ŵ�(��) n�ܰ� �켱ȣ�� ����
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
	char earlyClosedELWStatus[1];                   // ELW �������Ῡ��
	char earlyClosedELWTime[9];                     // ELW ��������ð�
    char endText[1];     							// �����й�޼�������Ű����
};
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTotalTrade);

class ExtureGroupCRecoveryTrade
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
        char lf[1];                                                                                        // 36   LF  X   1
};
const int EXTURE_GROUP_C_RECOVERY_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTrade);
#endif
#if(1)





#if(0)
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
class ExtureGroupCRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// �ŵ�n�ܰ�켱ȣ������
	char bidQuote[11];				// �ż�n�ܰ�켱ȣ������
	char askQuoteVolume[12];		// �ŵ�n�ܰ�켱ȣ���ܷ�
	char bidQuoteVolume[12];		// �ż�n�ܰ�켱ȣ���ܷ�
};
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExtureGroupCRecoveryTotalTradeRecord);

class ExtureGroupCRecoveryTotalTrade
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
	ExtureGroupCRecoveryTotalTradeRecord rec[10];  // �ŵ�(��) n�ܰ� �켱ȣ�� ����
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
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTotalTrade);

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

class ExtureGroupCRecoveryTrade
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
const int EXTURE_GROUP_C_RECOVERY_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTrade);
#endif

// ��������_UDP_�����й�_20140203_4���ȳ�.xlsb
//18  �ڽ���_�ð��ܴ��ϰ�_����   �ڽ���_�ð��ܴ��ϰ�_����   B3011   �ڽ���_�ð��ܴ��ϰ�_����   170 170 �ǽð�
//19  �ڽ���_�ð��ܴ��ϰ�_�ü�   �ڽ���_�ð��ܴ��ϰ�_�ü�   B4011   �ڽ���_�ð��ܴ��ϰ�_�ü�   170 170 �ǽð�
class ExtureGroupCRecoveryTradeFixed
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
const int EXTURE_GROUP_C_RECOVERY_TRADE_FIXED_SIZE = sizeof(ExtureGroupCRecoveryTradeFixed);
#endif

#if(1)
//18  KRX100����    �������    C8011   KRX100����    50  -   �ǽð�
//19  KRX100��������  �������    C9011   KRX100��������  50  -   �ǽð�
//20  KOSPI���� �������    D0011   KOSPI���� 50  -   �ǽð�
//21  KOSPI��������   �������    D1011   KOSPI��������   50  -   �ǽð�
//22  KOSPI200����  �������    D2011   KOSPI200����  50  -   �ǽð�
//23  KOSPI200��������    �������    D3011   KOSPI200��������    50  -   �ǽð�
//24  KOSPI100/50����   �������    D4011   KOSPI100/50����   50  -   �ǽð�
//25  KODI(���)����  �������    D6011   KODI(���)����  50  -   �ǽð�
//26  KODI��������    �������    D7011   KODI��������    50  -   �ǽð�
//27  "��������KOSPI200����" �������    K2011   ��������KOSPI200����  50  -   �ǽð�
//28  ��������    �������    E0011   ��������    50  -   �ǽð�
//29  ���Ϳ�������  �������    E1011   ���Ϳ�������  50  -   �ǽð�
//30  KRX SRI����   �������    L0011   KRX SRI����(2009.09.14)   50  -   �ǽð�
//31  KRX SRI�������� �������    L1011   KRX SRI��������(2009.09.14) 50  -   �ǽð�

class ExtureGroupCIndex
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
const int EXTURE_GROUP_C_INDEX_SIZE = sizeof(ExtureGroupCIndex);
#endif

#if(1)
class ExtureGroupCInvestorIndex
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
const int EXTURE_GROUP_C_INVESTOR_INDEX_SIZE = sizeof(ExtureGroupCInvestorIndex);
#endif

#if(1)
class ExtureGroupCKoscomLineLKInfo_ELW
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
const int EXTURE_GROUP_C_KOSCOM_LINE_LK_INFO_ELW_SIZE = sizeof(ExtureGroupCKoscomLineLKInfo_ELW);
#endif

#if(1)
// ���� ��Ŀ������ ���� ���ڵ�
// ü�� ������ ������ ä���.
// DATA ������ ZZ �� �ӽ÷� ������
class PaxfeedElwCustomIndexRecoveryRec
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
const int PAXFEED_ELW_CUSTOM_INDEX_RECOVERY_REC = sizeof(PaxfeedElwCustomIndexRecoveryRec);
#endif

#if(1)
// ��������_UDP_�ڽ��������й�_20140203_1���ȳ�.xlsb
// 2    �ڽ��� �ܱ��� �ֹ����ɼ���  �������    F2011   �ڽ��� �ܱ��� �ֹ����ɼ���  40  -   �ǽð�
class ExtureGroupCForeigner
{
    public:
        char dataClass[2];                                            // 001 DATA����
        char infoClass[2];                                            // 002 ��������
        char marketClass[1];                                          // 003 ���屸��
        char stockCode[12];                                           // 004 �����ڵ�
        char orderPossibilityVolume[15];                              // 005 �ֹ����� ����
        char dataType[2];                                             // 006 ����������(������ Type�Ƿ� ��. ���� DATA���а� �̸��� ���⶧��)
        char filler[5];                                               // 007 FILLER
        char ff[1];                                                   // 008 END OF TEXT
        char cr[1];
        char lf[1];
};
const int EXTURE_GROUP_C_FOREIGNER_SIZE = sizeof(ExtureGroupCForeigner);

// ��������_UDP_�������_20140203_4���ȳ�.xlsb
// 16   �ڽ���_���α׷��Ÿ� �������� �ڽ���_���α׷��Ÿ� �������� C5011   ���α׷��Ÿ� �������� 100 100 �ǽð�
class ExtureGroupCProgramTradePublic
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
const int EXTURE_GROUP_C_PROGRAM_TRADE_PUBLIC_SIZE = sizeof(ExtureGroupCProgramTradePublic);

// ��������_UDP_�������_20140203_4���ȳ�.xlsb
// 12  �ڽ���_���α׷��Ÿ� �Ϻ����Ͱŷ��ܰ� �������    C2011   ���α׷��Ÿ� �Ϻ����Ͱŷ��ܰ� 380 -   "���� 05:30, 06:10, 06:50 �� 3ȸ ����(��, A0011[KOSPI��������] ���� �Ϸ� �� ����)"
class ExtureGroupCProgramTradeBatch
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
const int EXTURE_GROUP_C_PROGRAM_TRADE_BATCH_SIZE = sizeof(ExtureGroupCProgramTradeBatch);
#endif

#if(1)
class ExtureGroupCBulkTrade
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
const int EXTURE_GROUP_C_BULK_TRADE_SIZE = sizeof(ExtureGroupCBulkTrade);
#endif

#if(1)
class ExturePlusElwQuoteRecord
{
    public:
	char askQuote[11];	                // �ŵ�n�ܰ�켱ȣ������
	char bidQuote[11];                  // �ż�n�ܰ�켱ȣ������
	char askQuoteVolume[12];            // �ŵ�n�ܰ�켱ȣ���ܷ�
	char bidQuoteVolume[12];            // �ż�n�ܰ�켱ȣ���ܷ�
	char askQuoteVolumeLP[12]; //       �ŵ�n�ܰ�LP�켱ȣ���ܷ�    
	char bidQuoteVolumeLP[12]; //       �ż�n�ܰ�LP�켱ȣ���ܷ�
};
const int EXTURE_PLUS_ELW_QUOTE_RECORD_SIZE = sizeof(ExturePlusElwQuoteRecord);

class ExturePlusElwQuote10
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
	ExturePlusElwQuoteRecord rec[10];	// �ŵ�(��) �켱ȣ�� ����
	char totalAskQuoteRemainder[12];     //       �ŵ�ȣ�������ܰ��ܷ��հ�    
	char totalBidQuoteRemainder[12];     //       �ż�ȣ�������ܰ��ܷ��հ�    
	char estimatedTradePrice[11];    //       ����ü�ᰡ   
	char estimatedTradeVolume[12];      //       ����ü�����  
	char endText[1];     //       �����й�޼�������Ű����    
};
const int EXTURE_PLUS_ELW_QUOTE10_SIZE = sizeof(ExturePlusElwQuote10);
#endif

#pragma pack()

#endif // __EXTURE_PLUS_INTERNET_ELW_H__
