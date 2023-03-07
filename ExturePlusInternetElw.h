#ifndef __EXTURE_PLUS_INTERNET_ELW_H__
#define __EXTURE_PLUS_INTERNET_ELW_H__

/*
 12345678901234567890123456789012345678901234567890123456789012345678901234567890
 */

#pragma pack(1)

#if(1)
// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 5    조기종료ELW 평가기간 중 기초자산고저가  M5011   조기종료ELW 평가기간 중 기초자산고저가  92  "정규장종료후(15:00~16:00)일일 2회 전송"   유가증권ELW체결호가정보
// 영문 스펙을 기준으로 명명함
class ExturePlusElwHighLowPriceOfUnderlyingAssetForEarlyClosedELWDuringEvaluationPeriod
{
    public:
        char data_category[2];                          // 1    DATA구분  X   2
        char information_category[2];                   // 2    정보구분    X   2
        char market_category[1];                        // 3    시장구분    X   1
        char issue_code[12];                            // 4    종목코드    X   12
        char issue_seq_number[8];                       // 5    일련번호    9   8
        char data_transmitted_date[8];                  // 6    전송일자    X   8
        char trading_date_of_underlying_asset[8];       // 7    기초자산매매일자    X   8
        char ko_occurred_date[8];                       // 8    KO발생일자  X   8
        char am_pm_category_code[1];                    // 9    오전오후구분코드    X   1
        char issue_code_of_elw_underlying_asset[12];    // 10   구성종목코드  X   12
        char market_type_that_elw_included[1];          // 11   ELW지수소속시장구분코드   X   1
        char index_industry_code[3];                    // 12   지수업종코드  X   3
        char high_price[11];                            // 13   고가  X   11
        char low_price[11];                             // 14   저가  X   11
        char filler[1];                                 // 15   FILLER  X   1
        char ff[1];                                     // 16   FF  X   1
        char cr[1];                                     // 17   CR  X   1
        char lf[1];                                     // 18   LF  X   1
};
const int EXTURE_PLUS_ELW_HIGH_LOW_PRICE_OF_UNDERLYING_ASSET_FOR_EARLY_CLOSED_ELW_DURING_EVALUATION_PERIOD_SIZE = sizeof(ExturePlusElwHighLowPriceOfUnderlyingAssetForEarlyClosedELWDuringEvaluationPeriod);

// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 7    ELW 배분정보    O6021   ELW 배분정보    32  실시간 유가증권ELW체결호가정보
// 영문 스펙을 기준으로 명명함
class ExturePlusElwELWQuantityAllocation
{
    public:
        char data_category[2];                                  // 1    DATA구분  X   2
        char information_category[2];                           // 2    "정보구분"  X   2
        char market_category[1];                                // 3    "시장구분"  X   1
        char issue_code[12];                                    // 4    "종목코드"  X   12
        char data_category_other_than_regular_session[1];       // 5    "정규시간외구분코드" X   1
        char allocation_start_end[1];                           // 6    "배분적용구분코드"  X   1
        char allocation_type_code[1];                           // 7    "배분처리구분코드"  X   1
        char time_for_allocation_end[6];                        // 8    "배분해제시각"    X   6
        char filler[3];                                         // 9    "FILLER"    X   3
        char ff[1];                                             // 10   "FF"    X   1
        char cr[1];                                             // 11   "CR"    X   1
        char lf[1];                                             // 12   "LF"    X   1
};
const int EXTURE_PLUS_ELW_ELW_QUANTITY_ALLOCATION_SIZE = sizeof(ExturePlusElwELWQuantityAllocation);

// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 8    ELW_투자자별    C0021   ELW 투자자별    88  실시간
// 영문 스펙을 기준으로 명명함
class ExturePlusElwELWTradingActivityPerInvestor
{
    public:
        char data_category[2];              // 1    DATA구분  X   2
        char information_category[2];       // 2    정보구분    X   2
        char market_category[1];            // 3    시장구분    X   1
        char calculation_time[6];           // 4    산출시각    X   6
        char investor_code[4];              // 5    투자자코드   X   4
        char industry_code[3];              // 6    업종코드    X   3
        char ask_trading_volume[12];        // 7    매도체결수량  9   12
        char ask_trading_value[18];         // 8    매도거래대금  9   18
        char bid_trading_volume[12];        // 9    매수체결수량  9   12
        char bid_trading_value[18];         // 10   매수거래대금  9   18
        char filler[7];                     // 11   FILLER  X   7
        char ff[1];                         // 12   FF  X   1
        char cr[1];                         // 13   CR  X   1
        char lf[1];                         // 14   LF  X   1
};
const int EXTURE_PLUS_ELW_ELW_TRADING_ACTIVITY_PER_INVESTOR_SIZE = sizeof(ExturePlusElwELWTradingActivityPerInvestor);

// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 15  ELW 종가 RECOVERY B1021   ELW_시세종가    292 실시간
// 영문 스펙을 기준으로 명명함
class ExturePlusElwELW_EOD
{
    public:
        char data_category[2];                                                                              // 1    DATA구분  X   2
        char information_category[2];                                                                       // 2    정보구분    X   2
        char market_category[1];                                                                            // 3    시장구분    X   1
        char issue_code[12];                                                                                // 4    종목코드    X   12
        char issue_seq_no[5];                                                                               // 5    종목일련번호  9   5
        char fluctuation_type[1];                                                                           // 6    등락구분    X   1
        char price_change_against_previous_day[9];                                                          // 7    전일대비    9   9
        char current_price_[9];                                                                             // 8    현재가 9   9
        char market_price[9];                                                                               // 9    시가  9   9
        char highest_limit_price[9];                                                                        // 10   고가  9   9
        char lowest_limit_price[9];                                                                         // 11   저가  9   9
        char trading_ask[9];                                                                                // 12   매도호가    9   9
        char trading_bid[9];                                                                                // 13   매수호가    9   9
        char accumulated_total_trading_volume[12];                                                          // 14   누적체결수량  9   12
        char accumulated_total_trading_value[18];                                                           // 15   누적거래대금  9   18
        char regular_closing_price_biased_quotation_new_closing_price_without_trades_price[1];              // 16   실세/기세 구분    X   1
        char board_event_id[3];                                                                             // 17   보드이벤트ID X   3
        char board_id[2];                                                                                   // 18   보드ID    X   2
        char trading_halt[1];                                                                               // 19   거래정지여부  X   1
        char closing_price_trading_volume_of_pre_opening_market[12];                                        // 20   "장개시전시간외종가체결수량" 9   12
        char closing_price_trading_value_of_pre_opening_market[18];                                         // 21   "장개시전시간외종가거래대금" 9   18
        char trading_volume_of_regular_session[12];                                                         // 22   정규장체결수량 9   12
        char trading_value_of_regular_session[18];                                                          // 23   정규장거래대금 9   18
        char closing_price_trading_volume_of_after_hour_market[12];                                         // 24   "장종료후시간외종가체결수량" 9   12
        char closing_price_trading_value_of_after_hour_market[18];                                          // 25   "장종료후시간외종가거래대금" 9   18
        char early_closed_elw_status[1];                                                                    // 26   ELW조기종료여부   X   1
        char early_closed_elw_time[6];                                                                      // 27   ELW조기종료시간   9   6
        char a_blox_[1];                                                                                    // 28   경쟁대량 방향구분   9   1
        char regular_buy_in_trading_volume[12];                                                             // 29   일반 Buy-in 체결수량  9   12
        char regular_buy_in_trading_value[18];                                                              // 30   일반 Buy-in 거래대금  9   18
        char same_day_buy_in_trading_volume[12];                                                            // 31   당일 Buy-in 체결수량  9   12
        char same_day_buy_in_trading_value[18];                                                             // 32   당일 Buy-in 거래대금  9   18
        char filler[8];                                                                                     // 33   FILLER  X   8
        char ff[1];                                                                                         // 34   FF  X   1
        char cr[1];                                                                                         // 35   CR  X   1
        char lf[1];                                                                                         // 36   LF  X   1
};
const int EXTURE_PLUS_ELW_ELW_EOD_SIZE = sizeof(ExturePlusElwELW_EOD);

// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 16  ELW 시세 RECOVERY B2021   ELW_시세RECOVERY  292 실시간
// 영문 스펙을 기준으로 명명함
class ExturePlusElwELWMarketDataRecovery
{
    public:
        char data_category[2];                                                                              // 1    DATA구분  X   2
        char information_category[2];                                                                       // 2    정보구분    X   2
        char market_category[1];                                                                            // 3    시장구분    X   1
        char issue_code[12];                                                                                // 4    종목코드    X   12
        char issue_seq_no[5];                                                                               // 5    종목일련번호  9   5
        char fluctuation_type[1];                                                                           // 6    등락구분    X   1
        char price_change_against_previous_day[9];                                                          // 7    전일대비    9   9
        char current_price_[9];                                                                             // 8    현재가 9   9
        char market_price[9];                                                                               // 9    시가  9   9
        char highest_limit_price[9];                                                                        // 10   고가  9   9
        char lowest_limit_price[9];                                                                         // 11   저가  9   9
        char trading_ask[9];                                                                                // 12   매도호가    9   9
        char trading_bid[9];                                                                                // 13   매수호가    9   9
        char accumulated_total_trading_volume[12];                                                          // 14   누적체결수량  9   12
        char accumulated_total_trading_value[18];                                                           // 15   누적거래대금  9   18
        char regular_closing_price_biased_quotation_new_closing_price_without_trades_price[1];              // 16   실세/기세 구분    X   1
        char board_event_id[3];                                                                             // 17   보드이벤트ID X   3
        char board_id[2];                                                                                   // 18   보드ID    X   2
        char trading_halt[1];                                                                               // 19   거래정지여부  X   1
        char closing_price_trading_volume_of_pre_opening_market[12];                                        // 20   "장개시전시간외종가체결수량" 9   12
        char closing_price_trading_value_of_pre_opening_market[18];                                         // 21   "장개시전시간외종가거래대금" 9   18
        char trading_volume_of_regular_session[12];                                                         // 22   정규장체결수량 9   12
        char trading_value_of_regular_session[18];                                                          // 23   정규장거래대금 9   18
        char closing_price_trading_volume_of_after_hour_market[12];                                         // 24   "장종료후시간외종가체결수량" 9   12
        char closing_price_trading_value_of_after_hour_market[18];                                          // 25   "장종료후시간외종가거래대금" 9   18
        char early_closed_elw_status[1];                                                                    // 26   ELW조기종료여부   X   1
        char early_closed_elw_time[6];                                                                      // 27   ELW조기종료시간   9   6
        char a_blox_[1];                                                                                    // 28   경쟁대량 방향구분   9   1
        char regular_buy_in_trading_volume[12];                                                             // 29   일반 Buy-in 체결수량  9   12
        char regular_buy_in_trading_value[18];                                                              // 30   일반 Buy-in 거래대금  9   18
        char same_day_buy_in_trading_volume[12];                                                            // 31   당일 Buy-in 체결수량  9   12
        char same_day_buy_in_trading_value[18];                                                             // 32   당일 Buy-in 거래대금  9   18
        char filler[8];                                                                                     // 33   FILLER  X   8
        char ff[1];                                                                                         // 34   FF  X   1
        char cr[1];                                                                                         // 35   CR  X   1
        char lf[1];                                                                                         // 36   LF  X   1
};
const int EXTURE_PLUS_ELW_ELW_MARKET_DATA_RECOVERY_SIZE = sizeof(ExturePlusElwELWMarketDataRecovery);

// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 19  HEADER  HE  HEADER  13  리커버리요청시 전송
// 영문 스펙을 기준으로 명명함

// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 20  FOOTER  FO  FOOTER  13  리커버리요청시 전송
// 영문 스펙을 기준으로 명명함

// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 21  LINK    LK  LINK    13  1분간데이터미발생시전송
// 영문 스펙을 기준으로 명명함

class ExturePlusKoscomLineLKInfo_ELW
{
    public:
        // 001 ~ 010
        char dataCategory[2];                                   // 001 DATA 구분
        char informationCategory[2];                            // 002 정보구분
        char marketCategory[1];                                 // 003 시장구분
        char time[4];                                           // 004 시간
        char ff[1];                                             // 005 FF
        char recvAddr[32];                                      // 수신주소정보(전문에는 없는 것)
};
const int EXTURE_PLUS_KOSCOM_LINE_LK_INFO_ELW_SIZE = sizeof(ExturePlusKoscomLineLKInfo_ELW);

// ELW_실시간_인터넷(KOSCOM)_20140523_2014052301.xls
// 3   ELW 투자지표 민감도    C7021   ELW 투자지표 민감도    112 실시간 유가증권ELW투자지표정보
// 영문 스펙을 기준으로 명명함
class ExturePlusElwEquityLinkedWarrantsInvestment
{
    public:
        char data_category[2];              // 1    DATA구분  X   2
        char information_category[2];       // 2    정보구분    X   2
        char market_category[1];            // 3    시장구분    X   1
        char issue_code[12];                // 4    종목코드    X   12
        char time[6];                       // 5    산출시간    X   6
        char theoretical_price[10];         // 6    이론가 9   10
        char sensitivity_delta_sign[1];     // 7    민감도 - 델타부호  X   1
        char sensitivity_delta[7];          // 8    민감도 - 델타    9   7
        char sensitivity_gamma_sign[1];     // 9    민감도 - 감마부호  X   1
        char sensitivity_gamma[7];          // 10   민감도 - 감마    9   7
        char sensitivity_theta_sign[1];     // 11   민감도 - 세타부호  X   1
        char sensitivity_theta_[12];        // 12   민감도 - 세타    9   12
        char sensitivity_vega_sign[1];      // 13   민감도 - 베가부호  X   1
        char sensitivity_vega[12];          // 14   민감도 - 베가    9   12
        char sensitivity_rho_sign[1];       // 15   민감도 - 로부호   X   1
        char sensitivity_rho[12];           // 16   민감도 - 로 9   12
        char intrinsic_volatility[5];       // 17   내재변동성   9   5
        char prerequisite_cost[10];         // 18   제반비용    9   10
        char filler[6];                     // 19   FILLER  X   6
        char ff[1];                         // 20   FF  X   1
        char cr[1];                         // 21   CR  X   1
        char lf[1];                         // 22   LF  X   1
};
const int EXTURE_PLUS_ELW_EQUITY_LINKED_WARRANTS_INVESTMENT_SIZE = sizeof(ExturePlusElwEquityLinkedWarrantsInvestment);

// ELW_실시간_인터넷(KOSCOM)_20140523_2014052301.xls
// 4   ELW LP호가 내재변동성  N3021   ELW LP호가 내재변동성  872 실시간 유가증권ELW투자지표정보
// 영문 스펙을 기준으로 명명함
class ExturePlusElwImpliedVolatilityOfELW_LP_Quotes
{
    public:
        char data_category[2];                  // 1    DATA구분  X   2
        char information_category[2];           // 2    정보구분    X   2
        char market_category[1];                // 3    시장구분    X   1
        char time[6];                           // 4    산출시간    9   6
        char issue_code_00[12];                 // 6    종목코드    X   0
        char implied_volatility_00[5];          // 7    내재변동성   9   0
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
//ETN 종목정보
//(증권C) STK : A104S
class ExturePlusElwETNInformationBatch
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char issueCode[12];                                     //종목코드
	char dataSeqNumber[6];                                     //정보분배종목인덱스
	char etnIssueMarketParticipantKoreanName[80];                                     //발행시장참가자명
	char etnIssueMarketParticipantEnglishName[80];                                     //발행시장참가자영문명
	char etnIssueMarketParticipantNo[5];                                     //발행시장참가자번호
	char etnFinalSettlementMethodCode[1];                                     //최종결제방법코드
	char etnLastTradingDate[8];                                     //최종거래일자
	char etnPaymentDate[8];                                     //ETN지급일자
	char etnLPHoldingQuantity[15];                                     //ETN_LP보유수량
	char lossProtectionEtnProfitStructureCode[2];                                     //손실제한ETN수익구조코드
	char etnMaximumRedemptionPrice[11];                                     //ETN최대상환가격
	char etnMinimumRedemptionPrice[11];                                     //ETN최소상환가격
	char etnEarlyRedemptionPossibility[1];                                     //ETN조기상환가능여부
	char etnEarlyRedemptionPeriodCode[2];                                     //ETN조기상환주기코드
	char appraisedPriceCalculationInstitutionCode1[2];                                     //평가가격산출기관코드1
	char appraisedPriceCalculationInstitutionCode2[2];                                     //평가가격산출기관코드2
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ETN_INFORMATION_BATCH_SIZE = sizeof(ExturePlusElwETNInformationBatch);
#endif

#if(1)
//ELW 종목정보//LW 종목 특화정보
//(증권C) STK : A102S
class ExturePlusElwELWBatchData
{
    public:
	char data_category[2];                                   //데이터구분값
	char infoMarketClass[3];                                 //정보구분값
	char distributeStockIndex[8];                            //정보분배일련번호
	char issue_code[12];                                     //종목코드
	char data_seq_number[6];                                     //정보분배종목인덱스
	char elw_issue_market_candidate_korean_name[80];                                     //발행시장참가자명
	char elw_issue_market_candidate_english_name[80];                                     //발행시장참가자영문명
	char elw_issue_market_candidate_number[5];                                     //발행시장참가자번호
	char elw_composition_issue_market_id_1[3];                                     //구성종목시장ID1
	char elw_composition_issue_market_id_2[3];                                     //구성종목시장ID2
	char elw_composition_issue_market_id_3[3];                                     //구성종목시장ID3
	char elw_composition_issue_market_id_4[3];                                     //구성종목시장ID4
	char elw_composition_issue_market_id_5[3];                                     //구성종목시장ID5
	char elw_underlying_asset_1[12];                                     //기초자산종목코드1
	char elw_underlying_asset_2[12];                                     //기초자산종목코드2
	char elw_underlying_asset_3[12];                                     //기초자산종목코드3
	char elw_underlying_asset_4[12];                                     //기초자산종목코드4
	char elw_underlying_asset_5[12];                                     //기초자산종목코드5
	char elw_underlying_asset_composite_rate_1[13];                                     //기초자산구성비율1
	char elw_underlying_asset_composite_rate_2[13];                                     //기초자산구성비율2
	char elw_underlying_asset_composite_rate_3[13];                                     //기초자산구성비율3
	char elw_underlying_asset_composite_rate_4[13];                                     //기초자산구성비율4
	char elw_underlying_asset_composite_rate_5[13];                                     //기초자산구성비율5
	char elw_index_industry_code[6];                                     //지수ID
	char elw_rights_type_0[1];                                     //권리유형코드
	char elw_rights_execution_type[1];                                     //권리행사유형코드
	char elw_payment_method[1];                                     //최종결제방법코드
	char elw_last_traded_date[8];                                     //최종거래일자
	char elw_payment_date[8];                                     //ELW지급일자
	char base_price_of_elw_underlying_asset[13];                                     //기초자산기초가격
	char elw_rights_content[200];                                     //권리행사내용
	char elw_conversion_rate[13];                                     //ELW전환비율
	char elw_price_rise_participation_rate[10];                                     //ELW가격상승참가율
	char elw_minimum_compensation_rate[10];                                     //ELW보상률 //ELW보상율->ELW최소지급비율
	char elw_fixed_payment[22];                                     //ELW확정지급액
	char elw_payment_agent[80];                                     //ELW지급대리인명
	char price_evaluation_method_use_at_elw_maturity[200];                                     //만기평가가격방식
	char elw_rights_type_1[1];                                     //ELW권리형태종류코드
	char elw_lp_holding_quantity[15];                                     //ELW_LP보유수량
	char filler[4];                                     //필러값4
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_ELW_BATCH_DATA_SIZE = sizeof(ExturePlusElwELWBatchData);
#endif

#if(1)
//증권 종목정보
//(증권A) STK : A001S
//(증권C) STK :  A002S, A003S, A004S
//(증권B) KSQ : A001Q
//(증권B) KNX : A001X
//(주식파생) STK : A001S
//(주식파생) KSQ : A001Q
class ExturePlusElwMaster
{
    public:
	char dataClass[2];                  //정보분배 데이터를 식별하는 구분 코드값
	char infoMarketClass[3];            //정보분배에서 분배하는 정보의 구분 코드값
	char distributeStockIndex[8];		//정보분배에서 부여하는 일련번호
										//시세 : 종목별 보드별 부여 (※ 대용량 서비스에서 제공)
										//종목정보 :  정보구분값별 부여
										//기타 : 데이터구분값별 부여
	char distributeTotalStockIndex[6];         //정보분배총종목인덱스
	char sendDate[8];         //영업일자
	char stockCode[12];         //종목코드
	char stockSeq[6];         //정보분배종목인덱스
	char abbrStockCode[9];         //종목단축코드
	char abbrStockNameKor[40];         //종목약명
	char abbrStockNameEng[40];         //종목영문약명
	char infoDivisionGroupNo[5];         //정보분배그룹번호
	char MarketProductGroupID[3];         //장운영상품그룹ID
	char stockGroupID[2];         //증권그룹ID
	char isUnitTrade[1];         //단위매매체결여부
	char exClassCode[2];         //락구분코드
	char faceValueChangeClassCode[2];         //액면가변경구분코드
	char isOpenPriceBecomeStdPrice[1];         //시가기준가격종목여부
	char isRevaluationStockReason[2];         //재평가종목사유코드
	char isStandardPriceChangeStock[1];         //기준가격변경종목여부
	char randomEndTriggerConditionCode[1];         //임의종료발동조건코드
	char isMarketAlarmDangerNotice[1];         //시장경보위험예고여부
	char marketAlarmClassCode[2];         //시장경보구분코드
	char isCorporateGovernanceFine[1];         //지배구조우량여부
	char isManagementStock[1];         //관리종목여부
	char isInsincerityPublicNewsAppoint[1];         //불성실공시여부
	char isBackDoorListing[1];         //우회상장여부
	char isTradeStop[1];         //거래정지여부
	char standardIndustryCode[10];         //업종ID
	char SmallMediumEnterprisesIs[1];         //중소기업여부
	char isCorporateGovernanceIndexStock[1];         //소속부구분코드
	char investOrganClassCode[1];         //투자기구구분코드
	char standardPrice[11];         //기준가격
	char ydayClosePriceClassCode[1];         //전일종가구분코드
	char ydayClosePrice[11];         //전일종가
	char ydayAccmVolume[12];         //전일누적거래량
	char ydayAccmAmount[22];         //전일누적거래대금
	char upLimitPrice[11];         //상한가
	char downLimitPrice[11];         //하한가
	char substitutePrice[11];         //대용가격
	char faceValue[11];         //액면가
	char issuePrice[11];         //발행가격
	char listingDate[8];         //상장일자
	char listingSize[16];         //상장주식수
	char isClearanceTrade[1];         //정리매매여부
	char listingStartDate[8];         //존립개시일자
	char listingEndDAte[8];         //존립종료일자
	char excercisePeriodBeginDate[8];         //행사기간개시일자
	char excercisePeriodEndDate[8];         //권리행사기간만료일자
	char ELWBWExcercisePrice[13];         //ELW신주인수권증권행사가격
	char capital[22];         //자본금
	char CreditOrderPossibleIs[1];         //신용주문가능여부
	char LimitQuotePriceConditionClassCode[5];         //지정가호가취소조건코드
	char MarketQuotePriceConditionClassCode[5];         //시장가호가취소조건코드
	char ConditionalLimitQuotePriceConditionClassCode[5];         //조건부지정가호가취소조건코드
	char BestLimitQuotePriceConditionClassCode[5];         //최유리지정가호가취소조건코드
	char topPriorityQuotePriceConditionClassCode[5];         //최우선지정가호가취소조건코드
	char capitalIncreaseClassCode[2];         //증자구분코드
	char preferredStockClassCode[1];         //종류주권구분코드
	char isNationalStock[1];         //국민주여부
	char evaluatePrice[11];         //평가가격
	char lowestQuotePrice[11];         //최저호가가격
	char highestQuotePrice[11];         //최고호가가격
	char MainBaordVolumeUnit[11];         //메인보드수량단위
	char JangAfterOvertimeVolumeUnit[11];         //장종료후시간외수량단위
	char REITsClassCode[1];         //리츠종류코드
	char objectSovereign[12];         //목적주권종목코드
	char CurrencyISOCode[3];         //통화ISO코드
	char NationalCode[3];         //국가코드
	char BelfastPossibleIs[1];         //시장조성가능여부
	char OvertimeTradePossibleIs[1];         //시간외매매가능여부
	char isBeforeMarketOvertimeMarketClosePrice[1];         //장개시전시간외종가가능여부
	char isBeforeMarketOvertimeMarketBlockTradingPossibility[1];         //장개시전시간외대량매매가능여부
	char isBeforeMarketOvertimeMarketBasketPossibility[1];         //장개시전시간외바스켓가능여부
	char isEstimatedTradePriceOpen[1];         //예상체결가공개여부
	char isShortStockSellingPossibility[1];         //공매도가능여부
	char ETFFollowingEarningRateMultiple[13];         //추적수익률배수
	char REGSIS[1];         //REGS여부
	char SPACIS[1];         //SPAC여부
	char taxImportedTypeCode[1];         //과세유형코드
	char rateSubstitutePriceCalcurated[13];         //대용가격사정비율
	char isStockInvestmentWarningAttention[1];         //투자주의환기종목여부
	char delistingDate[8];         //상장폐지일자
	char shortTermFeverishInstrumentTypeCode[1];         //단기과열종목구분코드
	char ETFReplicationMethodTypeCode[1];         //ETF복제방법구분코드
	char expirationDate[8];         //만기일자
	char distributeTypeCode[2];         //분배금형태코드
	char expirationRedemptionPriceDecisionStartDate[8];         //만기상환가격결정시작일자
	char expirationRedemptionPriceDecisionEndDate[8];         //만기상환가격결정종료일자
	char etpProductTypeCode[1];         //ETP상품구분코드
	char indexCalculationInstitution_code[2];         //지수산출기관코드
	char indexMarket_classification_id[6];         //지수시장분류ID
	char indexSeqNumber[3];         //지수일련번호
	char trackingIndexLeverageInverseTypeCode[2];         //추적지수레버리지인버스구분코드
	char referenceIndexLeverageInverseTypeCode[2];         //참고지수레버리지인버스구분코드
	char indexAssetClassificationId1[6];         //지수자산분류ID1
	char indexAssetClassificationId2[6];         //지수자산분류ID2
	char RecommendTestimonialNo[5];         //상장주선사회원번호
	char lpOrderPossibility[1];         //LP주문가능여부
	char lowLiquidity[1];         //저유동성여부
	char abnormalRise[1];         //이상급등여부
	char upperLimitQuantity[23];         //상한수량
	char isInvestmentPrecautionIssue[1];         //투자유의종목여부
	char TradingVolumeInsufficientIs[1];         //상장주식수부족종목여부
	char isSPAC_merger[1];         //SPAC소멸합병여부
	char segment_code[1];         //세그먼트구분코드
	char endOfText[1];         //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_MASTER_SIZE = sizeof(ExturePlusElwMaster);
#endif

#if(1)
// (증권A) STK : A701S
// (증권C) STK :  A702S, A703S, A704S
// (증권B) KSQ : A701Q
// (증권B) KNX : A701X
// (파생A) DRV : A701F, A702F, A703F, A704F, A705F, A706F, A707F, A708F, A709F, A710F, A711F, A712F, A713F, A715F, A716F
class ExturePlusElwELWMarketOperationTS
{
    public:
		char  data_category[2]; //       데이터구분값   
		char  infoMarketClass[3]; //       정보구분값    
		char  distributeStockIndex[8]; //       정보분배일련번호     
		char  board_id[2]; //       보드ID     
		char  session_id[2]; //       세션ID     
		char  issue_code[12]; //       종목코드     
		char  price_evaluation_method_when_elw_close_early[6]; //       정보분배종목인덱스    
		char  trading_processing_time[12]; //       매매처리시각   
		char  board_event_id[3]; //       보드이벤트ID  
		char  start_time_of_board_event[9]; //       보드이벤트시작시각    
		char  board_event_group_code[5]; //       보드이벤트적용군코드   
		char  trading_suspension_cause_code[3]; //       거래정지사유코드     
		char  end_text[1]; //       정보분배메세지종료키워드  
};
const int EXTURE_PLUS_ELW_ELW_MARKET_OPERATION_TS_SIZE = sizeof(ExturePlusElwELWMarketOperationTS);
#endif

#if(1)
// ELW 조기종료 정보
// (증권C) STK : M602S
class ExturePlusElwEarlyClosedELWBatchData
{
    public:
		char  data_category[2]; //       데이터구분값   
		char  infoMarketClass[3]; //       정보구분값    
		char  distributeStockIndex[8]; //       정보분배일련번호     
		char  issue_code[12]; //       종목코드     
		char  base_price_for_occurrence_of_elw_early_closing[13]; //       ELW조기종료발생기준가격    
		char  contents_of_elw_early_closing_right[200]; //       ELW조기종료권리행사내용    
		char  price_evaluation_method_when_elw_close_early[300]; //       ELW조기종료평가방식  
		char  end_text[1]; //       정보분배메세지종료키워드 
};
const int EXTURE_PLUS_ELW_EARLY_CLOSED_ELW_BATCH_DATA_SIZE = sizeof(ExturePlusElwEarlyClosedELWBatchData);
#endif

#if(1)
// 증권 우선호가 (MM/LP호가 포함)
// (증권C) STK : B702S, B703S, B704S XXXXX
class ExturePlusElwELWQuoteRecord
{
    public:
		char  askQuote[11]; //       매도n단계우선호가가격  
		char  bidQuote[11]; //       매수n단계우선호가가격  
		char  askQuoteVolume[12]; //       매도n단계우선호가잔량  
		char  bidQuoteVolume[12]; //       매수n단계우선호가잔량  
		char  askQuoteVolumeLP[12]; //       매도n단계LP우선호가잔량    
		char  bidQuoteVolumeLP[12]; //       매수n단계LP우선호가잔량
};
const int EXTURE_PLUS_ELW_ELW_QUOTE_RECORD_SIZE = sizeof(ExturePlusElwELWQuoteRecord);

class ExturePlusElwELWRemainingVolumeOnQuotesLPQuotesIncluded
{
    public:
		char  data_category[2]; //       데이터구분값   
		char  infoMarketClass[3]; //       정보구분값    
		char  distributeStockIndex[8]; //       정보분배일련번호     
		char  board_id[2]; //       보드ID     
		char  session_id[2]; //       세션ID     
		char  issue_code[12]; //       종목코드     
		char  issue_seq_no[6]; //       정보분배종목인덱스    
		char  trading_processing_time[12]; //       매매처리시각   
		ExturePlusElwELWQuoteRecord rec[10];	// 매도(수) 우선호가 정보
		char  total_ask_order_remaining_after_market_closed[12]; //       매도호가공개단계잔량합계
		char  total_bid_order_remaining_after_market_closed[12]; //       매수호가공개단계잔량합계 
		char  estimated_trading_price[11]; //       예상체결가
		char  estimated_trading_quantity[12]; //       예상체결수량   
		char  end_text[1]; //       정보분배메세지종료키워드  

};
const int EXTURE_PLUS_ELW_ELW_REMAINING_VOLUME_ON_QUOTES_LP_QUOTES_INCLUDED_SIZE = sizeof(ExturePlusElwELWRemainingVolumeOnQuotesLPQuotesIncluded);
#endif

#if(0)
//증권 Snapshot (MM/LP호가 포함)
//종목별 보드별 snapshot 및 최종상태를 일정간격으로 제공 (MM/LP호가 포함)
//실시간 [건당 0.2초/전종목 전송후 30초 sleep] * 주기변경 가능
//(증권C) STK : B202S, B203S, B204S
class ExturePlusElwRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// 매도n단계우선호가가격
	char bidQuote[11];				// 매수n단계우선호가가격
	char askQuoteVolume[12];		// 매도n단계우선호가잔량
	char bidQuoteVolume[12];		// 매수n단계우선호가잔량
	char askQuoteVolumeLP[12];      // LP 매도호가 잔량
	char bidQuoteVolumeLP[12];      // LP 매수호가 잔량
};
const int EXTURE_PLUS_ELW_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExturePlusElwRecoveryTotalTradeRecord);

//증권 Snapshot (MM/LP호가 포함)
//종목별 보드별 snapshot 및 최종상태를 일정간격으로 제공 (MM/LP호가 포함)
//실시간 [건당 0.2초/전종목 전송후 30초 sleep] * 주기변경 가능
//(증권C) STK : B202S, B203S, B204S
class ExturePlusElwRecoveryTotalTrade
{
	public:
	char dataClass[2];								// 데이터구분값 
	char infoMarketClass[3];						// 정보구분값 
	char boardID[2];								// 보드ID
	char sessionID[2];								// 세션ID
	char stockCode[12];								// 종목코드
	char stockSeq[6];								// 정보분배종목인덱스
	char upDown[1];             					// 전일대비구분코드
	char gap[11];							        // 전일대비가격
	char upLimitPrice[11];      					// 상한가
	char downLimitPrice[11];    					// 하한가 
	char closePrice[11];							// 현재가
    char openPrice[11];         					// 시가  
    char highPrice[11];         					// 고가  
    char lowPrice[11];          					// 저가  
    char accmTradeVolume[12];   					// 누적거래량   
    char accmTradeAmount[22];   					// 누적거래대금  
    char lastAskBidClassCode[1];					// 최종매도매수구분코드 
	ExturePlusElwRecoveryTotalTradeRecord rec[10];  // 매도(수) n단계 우선호가 정보
	char totalRemainingAskPrice[12];     			// 매도호가공개단계잔량합계    
	char totalRemainingBidPrice[12];     			// 매수호가공개단계잔량합계 
	char estimatedTradePrice[11];   				// 예상체결가   
    char estimatedTradeVolume[12];  				// 예상체결수량
	char realRateQuotationClass[1];    				// 전일종가구분코드
													// 1:실세
													// 2:기세
													// 3:거래무
													// 4:시가기준가종목의 기세
	char isTradeStop[1];            				// 거래정지여부
	char earlyClosedELWStatus[1];                   // ELW 조기종료여부
	char earlyClosedELWTime[9];                     // ELW 조기종료시간
    char endText[1];     							// 정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExturePlusElwRecoveryTotalTrade);

class ExturePlusElwRecoveryTrade
{
    public:
        char dataClass[2];                                          // 001 DATA구분
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드(표준코드)
        char serialNo[5];                                           // 005 종목일련번호
        char upDown[1];                                             // 006 등락구분
        char gap[9];                                                // 007 전일대비
        char closePrice[11];                                        // 008 현재가
        char openPrice[11];                                         // 009 시가
        char highPrice[11];                                         // 010 고가
        char lowPrice[11];                                          // 011 저가
        char askQuote[11];                                          // 012 매도호가
        char bidQuote[11];                                          // 013 매수호가
        char accmTradeVolume[12];                                   // 014 누적체결수량
        char accmTradeAmount[22];                                   // 015 누적거래대금
        char realRateQuotationClass[1];                             // 016 실세/기세구분
        char boardEventID[3];                                       // 017 보드이벤트ID
        char boardID[2];                                            // 018 보드ID
        char isTradeStop[1];                                        // 019 거래정지여부
        char beforeMarketOverTimeClosePriceTradeVolume[12];         // 020 장개시전시간외종가체결수량
        char beforeMarketOverTimeClosePriceTradeAmount[22];         // 021 장개시전시간외종가거래대금
        char regularMarketTradeVolume[12];                          // 022 정규장체결수량
        char regularMarketTradeAmount[22];                          // 023 정규장거래대금
        char afterMarketOvertimeClosePriceTradeVolume[12];          // 024 장종료후시간외종가체결수량
        char afterMarketOvertimeClosePriceTradeAmount[22];          // 025 장종료후시간외종가거래대금
	char overTimeMarketFixedAccmVolume[12];          //단일가체결수량
        char overTimeMarketFixedAccmAmount[22];          //단일가거래대금
	char manyBulkTradeVolume[12];          //대량체결수량
        char manyBulkTradeAmount[22];          //대량거래대금
        char earlyClosedELWStatus[1];                               // 026 ELW 조기종료여부
        char earlyClosedELWTime[6];                                 // 027 ELW 조기종료시간
        char aBlox[1];                                              // 028 경쟁대량 방향구분
        char regularBuyInTradingVolume[12];                         // 029 일반 Buy-In 체결수량
        char regularBuyInTradingValue[22];                          // 030 일반 Buy-In 거래대금
        char sameDayBuyInTradingVolume[12];                         // 031 당일 Buy-In 체결수량
        char sameDayBuyInTradingValue[22];                          // 032 당일 Buy-In 거래대금
        char filler[8];                                             // 033 FILLER
        char ff[1];                                                 // 034 FF
        char cr[1];
        char lf[1];                                                                                        // 36   LF  X   1
};
const int EXTURE_PLUS_ELW_RECOVERY_TRADE_SIZE = sizeof(ExturePlusElwRecoveryTrade);
#endif

#if(1)
//MM/LP 정보
//증권 MM/LP 정보
//05:30, 06:10, 06:50 3회 전송
//(증권A) STK : I701S
//(증권C) STK : I702S, I703S, I704S
//(증권B) KSQ : I701Q
//(증권B) KNX : I701X"
class ExturePlusElwKOSPI_LP_Information
{
	public:
	char  data_category[2];                     //데이터구분값
	char  infoMarketClass[3];                     //정보구분값
	char  distributeStockIndex[8];                     //정보분배일련번호
	char  issue_code[12];                     //종목코드
	char  market_participant_number[5];                     //시장참가자번호
	char  lp_starting_date[8];                     //LP개시일자
	char  lp_expiration_date[8];                     //LP종료일자
	char  minimum_order_volume_multiple[11];                     //최소호가수량배수
	char  maximum_order_volume_multiple[11];                     //최대호가수량배수
	char  order_spread_unit_code[1];                     //호가스프레드단위코드
	char  order_spread_value[22];                     //호가스프레드상한값
	char  market_close_for_holiday_order_spread_multiple[11];                     //휴장호가스프레드배수
	char  duty_order_submit_time_interval[6];                     //의무호가제출시간간격
	char  bid_minumum_order_price[22];                     //매도최소호가금액
	char  ask_minimum_order_price[22];                     //매수최소호가금액
	char  minimum_order_price[22];                     //최소호가금액
	char  maximum_order_price[22];                     //최대호가금액
	char  endText[1];                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_KOSPI_LP_INFORMATION_SIZE = sizeof(ExturePlusElwKOSPI_LP_Information);
#endif

#if(1)
//ETN 조기상환조건 정보
//ETN 조기상환조건 정보
//05:30, 06:10, 06:50 3회 전송
//(증권C) STK : X304S
class ExturePlusElwETNEarlyRedemptionCriteria
{
	public:
	char data_category[2];                        //데이터구분값
	char infoMarketClass[3];                        //정보구분값
	char distributeStockIndex[8];                        //정보분배일련번호
	char issue_code[12];                        //종목코드
	char etn_early_redemption_period_code[2];                        //ETN조기상환주기코드
	char early_redemption_appraisal_date[8];                        //조기상환평가일자
	char early_redemption_criteria_relation_code[1];                        //조기상환조건관계코드
	char early_redemption_base_index_1[10];                        //조기상환기준1지수
	char early_redemption_base_index_2[10];                        //조기상환기준2지수
	char early_redemption_price_before_expenses[23];                        //조기상환가격
	char early_redemption_payment_date[8];                        //조기상환지급일자
	char endOfText[1];                        //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_ETN_EARLY_REDEMPTION_CRITERIA_SIZE = sizeof(ExturePlusElwETNEarlyRedemptionCriteria);
#endif

#if(1)
// 증권 체결
// (증권A) STK : A301S
// (증권C) STK : A302S, A303S, A304S
// (증권B) KSQ : A301Q
// (증권B) KNX : A301X
class ExturePlusElwELWOrderFilled
{
    public:
     char dataClass[2];                        //       데이터구분값  
     char infoMarketClass[3];                        //       정보구분값   
     char distributeStockIndex[8];                         //       정보분배일련번호    
     char board_id[2];                          //       보드ID    
     char session_id[2];                        //       세션ID    
     char issue_code[12];                       //       종목코드    
     char issue_seq_no[6];                         //       정보분배종목인덱스   
     char trading_time[12];   	   //       매매처리시각  
     char price_change_against_previous_day_code[1];                           //       전일대비구분코드    
     char price_change_against_previous_day[11];                              //       전일대비가격  
     char current_price[11];                       //       체결가격    
     char trading_volume[10];                     //       거래량 
     char opening_price[11];                        //       시가  
     char high_price[11];                        //       고가  
     char low_price[11];                         //       저가  
     char accumulated_volume[12];                 //       누적거래량   
     char accumulated_traded_value[22];                 //       누적거래대금  
     char final_bid_ask_category[1];              //       최종매도매수구분코드  
     char lp_holding_quantity[15];                 //       LP보유수량  
     char ask_1_order[11];                      //       매도최우선호가가격   
     char bid_1_order[11];                      //       매수최우선호가가격   
     char endText[1];                          //       정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_ELW_ORDER_FILLED_SIZE = sizeof(ExturePlusElwELWOrderFilled);
#endif

#if(1)
//거래상위 5개 회원 통계(B901S)
//(증권A) STK : B901S
//(증권C) STK : B902S, B903S, B904S
//(증권B) KSQ : B901Q
//(증권B) KNX : B901X
class ExturePlusElwELWTop5AskBidTradersActivityInformation
{
    public:
        char data_category[2];                  //DATA구분  X   2
        char infoMarketClass[3];
        char issue_code[12];                    //종목코드    X   12
        char issue_seq_no[6];                   //일련번호    9   8
        char ask_member_number1[5];             //매도거래원번호1    9   5
        char ask_trading_volume1[12];           //매도체결수량1 9   12
        char ask_trading_value1[22];            //매도거래대금1 9   22
        char bid_member_number1[5];             //매수거래원번호1    9   5
        char bid_trading_volume1[12];           //매수체결수량1 9   12
        char bid_trading_value1[22];            //매수거래대금1 9   22
        char ask_member_number2[5];             //매도거래원번호2    9   5
        char ask_trading_volume2[12];           //매도체결수량2 9   12
        char ask_trading_value2[22];            //매도거래대금2 9   22
        char bid_member_number2[5];             //매수거래원번호2    9   5
        char bid_trading_volume2[12];           //매수체결수량2 9   12
        char bid_trading_value2[22];            //매수거래대금2 9   22
        char ask_member_number3[5];             //매도거래원번호3    9   5
        char ask_trading_volume3[12];           //매도체결수량3 9   12
        char ask_trading_value3[22];            //매도거래대금3 9   22
        char bid_member_number3[5];             //매수거래원번호3    9   5
        char bid_trading_volume3[12];           //매수체결수량3 9   12
        char bid_trading_value3[22];            //매수거래대금3 9   22
        char ask_member_number4[5];             //매도거래원번호4    9   5
        char ask_trading_volume4[12];           //매도체결수량4 9   12
        char ask_trading_value4[22];            //매도거래대금4 9   22
        char bid_member_number4[5];             //매수거래원번호4    9   5
        char bid_trading_volume4[12];           //매수체결수량4 9   12
        char bid_trading_value4[22];            //매수거래대금4 9   22
        char ask_member_number5[5];             //매도거래원번호5    9   5
        char ask_trading_volume5[12];           //매도체결수량5 9   12
        char ask_trading_value5[22];            //매도거래대금5 9   22
        char bid_member_number5[5];             //매수거래원번호5    9   5
        char bid_trading_volume5[12];           //매수체결수량5 9   12
        char bid_trading_value5[22];            //매수거래대금5 9   22
        char endOfText[1];                      //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_ELW_TOP_5_ASK_BID_TRADERS_ACTIVITY_INFORMATION_SIZE = sizeof(ExturePlusElwELWTop5AskBidTradersActivityInformation);
#endif

#if(1)
//장운영스케줄공개
//(증권A) STK : M401S
//(증권C) STK : M402S, M403S, M404S
//(증권B) KSQ : M401Q
//(증권B) KNX : M401X
//(채권A) BND : M401B
//(채권A) SMB : M401M
//(채권A) KTS : M401K
//(채권A) RPO : M401R
//(파생A) DRV : M401F, M402F, M403F, M404F, M405F, M406F, M407F, M408F, M409F, M410F, M411F, M412F, M413F, M415F, M416F
//(파생B) DRV : M414F
//(일반A) CMD : M401G
//(일반A) ETS : M401E
//장운영스케줄 이벤트 공개 발생시 제공
class ExturePlusElwKOSPIMarketOperationScheduleDisclosure
{
	public:
	char dataCategory[2];                               //데이터구분값                             
	char infoMarketClass[3];                               //정보구분값                            
	char marketCategory[3];                               //장운영상품그룹ID                       
	char boardID[2];                               //보드ID                                        
	char boardEventID[3];                               //보드이벤트ID                             
	char boardEventBeginTime[9];                               //보드이벤트시작시각                
	char boardEventApplyCode[5];                               //보드이벤트적용군코드              
	char sessionBeginEndCode[2];                               //세션개시종료코드                  
	char sessionID[2];                               //세션ID                                      
	char issueCode[12];                               //종목코드                                   
	char listedIssueCode[12];                               //상장사종목코드                       
	char productID[11];                               //상품ID                                     
	char tradingHaltReasonCode[3];                               //거래정지사유코드                
	char tradingHaltOccurenceTypeCode[1];                               //거래정지발생유형코드     
	char stepApplied[2];                               //적용단계                                  
	char stepAppliedOccuredCode[1];                               //기준종목가격제한확대발생코드   
	char stepAppliedScheduleTime[9];                               //가격제한확대예정시각          
	char endOfText[1];                               //정보분배메세지종료키워드                    
};
const int EXTURE_PLUS_ELW_KOSPI_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE = sizeof(ExturePlusElwKOSPIMarketOperationScheduleDisclosure);
#endif

#if(1)
//종목이벤트 정보
//(증권A) STK : I601S
//(증권C) STK : I602S, I603S, I604S
//(증권B) KSQ : I601Q
//(증권B) KNX : I601X
//주식/채권 종목의 거래정지, 관리종목, 정리매매 등의 이벤트 정보
//선물회선은 (STK, KSQ) 종목 중 기초자산 해당종목만 필터링 "
class ExturePlusElwKOSPIIssueEventInformation
{
    public:
	char data_category[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char issue_code[12];                                     //종목코드
	char event_type_code[2];                                     //이벤트종류코드
	char event_occurrence_cause_code[4];                                     //이벤트발생사유코드
	char start_date_opening_date_application_date[8];                                     //이벤트개시일자
	char expiration_date_ending_date[8];                                     //이벤트종료일자
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_KOSPI_ISSUE_EVENT_INFORMATION_SIZE = sizeof(ExturePlusElwKOSPIIssueEventInformation);
#endif

#if(1)
//ETN 수익구조내용 정보
//ETN 수익구조내용 정보
//05:30, 06:10, 06:50 3회 전송
//(증권C) STK : X804S
class ExturePlusElwETNProfitStructureDetails
{
	public:
	char data_category[2];                        //데이터구분값
	char infoMarketClass[3];                        //정보구분값
	char distributeStockIndex[8];                        //정보분배일련번호
	char issue_code[12];                        //종목코드
	char etn_profit_structure_details[2000];                        //ETN수익구조내용
	char endOfText[1];                        //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ETN_PROFIT_STRUCTURE_DETAILS_SIZE = sizeof(ExturePlusElwETNProfitStructureDetails);
#endif

#if(1)
// ETP지수정보  ETP지수정보 2021.03.15  2021.03.15  202 ETP지수정보
class ExturePlusElwKOSPI_ETP_Constituents
{
    public:
        char data_category[2];                              // 1    DATA구분
        char information_category[2];                       // 2    정보구분
        char market_category[1];                            // 3    시장구분
        char index_calculation_institution_code[2];         // 4    지수산출기관코드
        char index_market_classification_id[6];             // 5    지수시장분류ID
        char index_seq_number[3];                           // 6    지수일련번호
        char index_leverage_inverse_type_code[2];           // 7    지수레버리지인버스구분코드
        char index_name[80];                                // 8    지수명
        char index_name_english[80];                        // 9    지수영문명
        char index_asset_classification_id_1[6];            // 10   지수자산분류ID1
        char index_asset_classification_id_2[6];            // 11   지수자산분류ID2
        char index_associated_market_type_code[1];          // 12   지수소속시장구분코드
        char industry_index_code[8];                        // 13   업종지수코드
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
	char data_category[2];                                 //데이터구분값
	char infoMarketClass[3];                                 //정보구분값
	char distributeStockIndex[8];                                 //정보분배일련번호
	char index_calculation_institution_code[2];                                 //지수산출기관코드
	char index_market_classification_id[6];                                 //지수시장분류ID
	char index_seq_number[3];                                 //지수일련번호
	char index_leverage_inverse_type_code[2];                                 //지수레버리지인버스구분코드
	char index_name[80];                                 //지수명
	char index_name_english[80];                                 //지수영문명
	char index_asset_classification_id_1[6];                                 //지수자산분류ID1
	char index_asset_classification_id_2[6];                                 //지수자산분류ID2
	char jisuID[6];                                 //지수ID
	char filler[4];                                 //필러값4
	char endOfText[1];                                 //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_ETP_TOTAL_CONSTITUENTS_SIZE = sizeof(ExturePlusElwKOSPI_ETP_ToTalConstituents);
#endif

#if(1)
//코스콤 정보	외국인 투자정보	코스피 외국인 종목별투자정보(확정치)	F101S
//코스콤 정보	외국인 투자정보	코스닥 외국인 종목별투자정보(확정치)	F101Q
class ExturePlusElwKospiForeignerInvestmentInformationForEachIssueConfirmedData
{
	public:
	char data_category[2];                                       //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char issue_code[12];                                         //종목코드
	char serialNo[8];                                            //일련번호
	char trading_date[8];                                        //매매일자
	char issue_limit_ratio[5];                                   //종목한도비율
	char individual_limit_ratio[5];                              //개인한도비율
	char number_of_listed_stock[15];                             //상장주식수
	char available_quantity_for_order[15];                       //주문가능수량
	char limit_exhaustion_type[1];                               //한도소진구분
	char filler[5];                                              //FILLER
	char endText[1];                                             //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_KOSPI_FOREIGNER_INVESTMENT_INFORMATION_FOR_EACH_ISSUE_CONFIRMED_DATA_SIZE = sizeof(ExturePlusElwKospiForeignerInvestmentInformationForEachIssueConfirmedData);
#endif

#if(1)
//코스콤 정보	외국인 투자정보	코스피 외국인 확정치데이터재전송	F401S
//코스콤 정보	외국인 투자정보	코스닥 외국인 확정치데이터재전송	F401Q
class ExturePlusElwKospiForeignerConfirmedDataRetransmission
{
	public:
	char data_category[2];                                       //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char issue_code[12];                                         //종목코드
	char issue_limit_ratio[5];                                   //종목한도비율
	char individual_limit_ratio[5];                              //개인한도비율
	char number_of_listed_stock[15];                             //상장주식수
	char available_quantity_for_order[15];                       //주문가능수량
	char limit_exhaustion_type[1];                               //한도소진구분
	char filler[1];                                              //FILLER
	char endText[1];                                             //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_KOSPI_FOREIGNER_CONFIRMED_DATA_RETRANSMISSION_SIZE = sizeof(ExturePlusElwKospiForeignerConfirmedDataRetransmission);
#endif

#if(1)
//종목마감	보드별 종목마감시 제공
//실시간	
//(증권A) STK : A601S
//(증권C) STK : A602S, A603S, A604S
//(증권B) KSQ : A601Q
//(증권B) KNX : A601X
class ExturePlusElwELWIssueClosing
{
	public:
	char data_category[2];                 //DATA구분
	char infoMarketClass[3];               //정보구분값
	char distributeStockIndex[8];          //정보분배일련번호
	char board_id[2];          //보드ID
	char issue_code[12];          //종목코드
	char closing_price[11];          //종목마감종가
	char closing_price_type_code[1];          //종가구분코드
	char maximum_limit_price_for_the_single_price_trades[11];          //종목마감시간외단일가상한가
	char minimum_limit_price_for_the_single_price_trades[11];          //종목마감시간외단일가하한가
	char weighted_average_price[11];          //종목마감평균가중주가
	char buy_in_base_price[11];          //종목마감매입인도기준가격
	char buy_in_upper_limit[11];          //종목마감매입인도상한가
	char buy_in_lower_limit[11];          //종목마감매입인도하한가
	char endOfText[1];          //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_ELW_ISSUE_CLOSING_SIZE = sizeof(ExturePlusElwELWIssueClosing);
#endif

#if(0)
// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 12  ELW 종목마감    A6021   ELW_종목마감    90  실시간
// 영문 스펙을 기준으로 명명함
class ExturePlusElwELWIssueClosing
{
    public:
        char data_category[2];                                       // 1   DATA구분  X   2
        char information_category[2];                                // 2   정보구분    X   2
        char market_category[1];                                     // 3   시장구분    X   1
        char issue_code[12];                                         // 4   종목코드    X   12
        char issue_seq_no[5];                                        // 5   종목일련번호  9   5
        char board_id[2];                                            // 6   보드ID    X   2
        char closing_price[9];                                       // 7   종목마감종가  9   9
        char closing_price_type_code[1];                             // 8   종목마감가격구분코드  X   1
        char maximum_limit_price_for_the_single_price_trades[9];     // 9   종목마감시간외단일가상한가 9   9
        char minimum_limit_price_for_the_single_price_trades[9];     // 10  종목마감시간외단일가하한가 9   9
        char weighted_average_price[9];                              // 11  종목마감평균가중주가  9   9
        char buy_in_base_price[9];                                   // 12  매입인도기준가격    9   9
        char buy_in_upper_limit[9];                                  // 13  매입인도상한가 9   9
        char buy_in_lower_limit[9];                                  // 14  매입인도하한가 9   9
        char filler[1];                                              // 15  FILLER  X   1
        char ff[1];                                                  // 16  FF  X   1
        char cr[1];                                                  // 17  CR
        char lf[1];                                                  // 18  LF

};
const int EXTURE_PLUS_ELW_ELW_ISSUE_CLOSING_SIZE = sizeof(ExturePlusElwELWIssueClosing);
#endif

#if(0)
// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 10   코스피주식종목정보공개 A8011   코스피_공개정보 -> 코스피_주식종목정보공개    122 실시간 유가증권주식체결정보
// 영문 스펙을 기준으로 명명함
class ExturePlusElwKOSPIIssueInformationDisclosure
{
    public:
        char data_category[2];                                                              // 1    DATA구분  X   2
        char information_category[2];                                                       // 2    정보구분    X   2
        char market_category[1];                                                            // 3    시장구분    X   1
        char issue_code_[12];                                                               // 4    종목코드    X   12
        char issue_seq_no[5];                                                               // 5    종목일련번호  9   5
        char disclosure_data_type_code[3];                                                  // 6    공개정보구분코드    X   3
        char board_id[2];                                                                   // 7    보드ID    X   2
        char basis_price[9];                                                                // 8    기준가격    9   9
        char upper_limit_price[9];                                                          // 9    상한가 9   9
        char lower_limit_price[9];                                                          // 10   하한가 9   9
        char evaluation_price[9];                                                           // 11   평가가격    9   9
        char highest_order_price[9];                                                        // 12   최고호가가격  9   9
        char lowest_order_price[9];                                                         // 13   최저호가가격  9   9
        char opening_price_becomes_basis_price_type[1];                                     // 14   시가기준가격여부    X   1
        char back_door_listing[2];                                                          // 15   락구분코드   X   2
        char par_value_change_type_code[2];                                                 // 16   액면가변경구분코드   X   2
        char lot_size[11];                                                                  // 17   매매수량단위  9   11
        char number_of_listed_stocks[16];                                                   // 18   상장주식수   9   16
        char liquidation_of_trades_designation_administrative_issue_designation[1];         // 19   정리매매/관리종목 지정여부    X   1
        char closing_price_possibility_in_pre_off_hours_session[1];                         // 20   장개시전시간외종가 가능여부    X   1
        char filler[4];                                                                     // 21   FILLER  X   4
        char ff[1];                                                                         // 22   FF  X   1
        char cr[1];                                                                         // 23   CR  X   1
        char lf[1];                                                                         // 24   LF  X   1
};
const int EXTURE_PLUS_ELW_KOSPI_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExturePlusElwKOSPIIssueInformationDisclosure);
#endif

#if(1)
//주식종목정보변경
//주식 종목에 대한 정보변경 조치가 발생했을시 제공
//공개정보구분코드 : 정보분배용 재정의 필요
//실시간
//(증권A) STK : A801S
//(증권C) STK : A802S, A803S, A804S
//(증권B) KSQ : A801Q
//(증권B) KNX : A801X
class ExturePlusElwKOSPIIssueInformationDisclosure
{
    public:
	char data_category[2];                   //DATA구분
	char infoMarketClass[3];                 //정보구분
	char issue_code_[12];                    //종목코드
	char issue_seq_no[6];                    //정보분배종목인덱스
	char disclosure_data_type_code[3];       //공개정보구분코드값
	char board_id[2];                        //보드ID
	char basis_price[11];                    //기준가격
	char upper_limit_price[11];              //상한가
	char lower_limit_price[11];              //하한가
	char evaluation_price[11];               //평가가격
	char highest_order_price[11];            //최고호가가격
	char lowest_order_price[11];             //최저호가가격
	char opening_price_becomes_basis_price_type[1];                   //시가기준가격여부
	char back_door_listing[2];                                        //락구분코드
	char par_value_change_type_code[2];                               //액면가변경구분코드
	char lot_size[11];                                                //수량단위
	char number_of_listed_stocks[16];                                 //상장주식수
	char liquidation_of_trades_designation_administrative_issue_designation[1];                   //지정여부
	char closing_price_possibility_in_pre_off_hours_session[1];                                   //장개시전시간외종가가능여부
	char endText[1];                                                                              //정보분배메세지종료키워드
};
const int EXTURE_PLUS_ELW_KOSPI_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExturePlusElwKOSPIIssueInformationDisclosure);
#endif

#if(0)
// ELW_실시간_인터넷(KRX)_20141117_2014092901.xls
// 6    ELW 투자지표    C6021   ELW 투자지표    82  실시간 유가증권ELW투자지표정보
// 영문 스펙을 기준으로 명명함
class ExturePlusElwELWInvestmentIndicatorInformation
{
    public:
        char data_category[2];                  // 1    DATA구분  X   2
        char information_category[2];           // 2    정보구분    X   2
        char market_category[1];                // 3    시장구분    X   1
        char elw_issue_code[12];                // 4    종목코드    X   12
        char issue_seq_no[8];                   // 5    일련번호    9   8
        char calculate_time[6];                 // 6    산 시간    X   6
        char parity[8];                         // 7    패리티 9   8
        char gearing_ratio[8];                  // 8    기어링비율   9   8
        char break_even_ratio_code[1];          // 9    손익분기율 부호    X   1
        char break_even_ratio[7];               // 10   손익분기율   9   7
        char capital_support_point_sign[1];     // 11   자본지지점 부호    X   1
        char capital_support_point[7];          // 12   자본지지점   9   7
        char basket_stock_price[11];            // 13   바스켓주가   9   11
        char filler[5];                         // 14   FILLER  X   5
        char ff[1];                             // 15   FF  X   1
        char cr[1];                             // 16   CR  X   1
        char lf[1];                             // 17   LF  X   1

};
const int EXTURE_PLUS_ELW_ELW_INVESTMENT_INDICATOR_INFORMATION_SIZE = sizeof(ExturePlusElwELWInvestmentIndicatorInformation);
#endif

#if(1)
//ELW투자지표
//산출된 ELW투자지표 송신
//실시간제공
//C602S
class ExturePlusElwELWInvestmentIndicatorInformation
{
	public:
	char data_category[2];                  //데이터구분값
	char infoMarketClass[3];                //정보구분값
	char elw_issue_code[12];                //종목코드
	char issue_seq_no[8];                   //일련번호
	char calculate_time[6];                 //지수산출시각
	char parity[9];                         //패리티값
	char gearing_ratio[9];                  //기어링비율
	char break_even_ratio_code[1];          //손익분기율부호
	char break_even_ratio[8];               //손익분기율
	char capital_support_point_sign[1];     //자본지지점부호
	char capital_support_point[8];          //자본지지점
	char basket_stock_price[12];            //바스켓주가
	char endOfText[1];                      //정보분배메세지종료키워드
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
//증권 종목정보
//(증권A) STK : A001S
//(증권C) STK :  A002S, A003S, A004S
//(증권B) KSQ : A001Q
//(증권B) KNX : A001X
//(주식파생) STK : A001S
//(주식파생) KSQ : A001Q
class ExtureGroupCMaster
{
    public:
	char dataClass[2];                  //정보분배 데이터를 식별하는 구분 코드값
	char infoMarketClass[3];            //정보분배에서 분배하는 정보의 구분 코드값
	char distributeStockIndex[8];		//정보분배에서 부여하는 일련번호
										//시세 : 종목별 보드별 부여 (※ 대용량 서비스에서 제공)
										//종목정보 :  정보구분값별 부여
										//기타 : 데이터구분값별 부여
	char distributeTotalStockIndex[6];         //정보분배총종목인덱스
	char sendDate[8];         //영업일자
	char stockCode[12];         //종목코드
	char stockSeq[6];         //정보분배종목인덱스
	char abbrStockCode[9];         //종목단축코드
	char abbrStockNameKor[40];         //종목약명
	char abbrStockNameEng[40];         //종목영문약명
	char infoDivisionGroupNo[5];         //정보분배그룹번호
	char MarketProductGroupID[3];         //장운영상품그룹ID
	char stockGroupID[2];         //증권그룹ID
	char isUnitTrade[1];         //단위매매체결여부
	char exClassCode[2];         //락구분코드
	char faceValueChangeClassCode[2];         //액면가변경구분코드
	char isOpenPriceBecomeStdPrice[1];         //시가기준가격종목여부
	char isRevaluationStockReason[2];         //재평가종목사유코드
	char isStandardPriceChangeStock[1];         //기준가격변경종목여부
	char randomEndTriggerConditionCode[1];         //임의종료발동조건코드
	char isMarketAlarmDangerNotice[1];         //시장경보위험예고여부
	char marketAlarmClassCode[2];         //시장경보구분코드
	char isCorporateGovernanceFine[1];         //지배구조우량여부
	char isManagementStock[1];         //관리종목여부
	char isInsincerityPublicNewsAppoint[1];         //불성실공시여부
	char isBackDoorListing[1];         //우회상장여부
	char isTradeStop[1];         //거래정지여부
	char standardIndustryCode[10];         //업종ID
	char SmallMediumEnterprisesIs[1];         //중소기업여부
	char isCorporateGovernanceIndexStock[1];         //소속부구분코드
	char investOrganClassCode[1];         //투자기구구분코드
	char standardPrice[11];         //기준가격
	char ydayClosePriceClassCode[1];         //전일종가구분코드
	char ydayClosePrice[11];         //전일종가
	char ydayAccmVolume[12];         //전일누적거래량
	char ydayAccmAmount[22];         //전일누적거래대금
	char upLimitPrice[11];         //상한가
	char downLimitPrice[11];         //하한가
	char substitutePrice[11];         //대용가격
	char faceValue[11];         //액면가
	char issuePrice[11];         //발행가격
	char listingDate[8];         //상장일자
	char listingSize[16];         //상장주식수
	char isClearanceTrade[1];         //정리매매여부
	char listingStartDate[8];         //존립개시일자
	char listingEndDAte[8];         //존립종료일자
	char excercisePeriodBeginDate[8];         //행사기간개시일자
	char excercisePeriodEndDate[8];         //권리행사기간만료일자
	char ELWBWExcercisePrice[13];         //ELW신주인수권증권행사가격
	char capital[22];         //자본금
	char CreditOrderPossibleIs[1];         //신용주문가능여부
	char LimitQuotePriceConditionClassCode[5];         //지정가호가취소조건코드
	char MarketQuotePriceConditionClassCode[5];         //시장가호가취소조건코드
	char ConditionalLimitQuotePriceConditionClassCode[5];         //조건부지정가호가취소조건코드
	char BestLimitQuotePriceConditionClassCode[5];         //최유리지정가호가취소조건코드
	char topPriorityQuotePriceConditionClassCode[5];         //최우선지정가호가취소조건코드
	char capitalIncreaseClassCode[2];         //증자구분코드
	char preferredStockClassCode[1];         //종류주권구분코드
	char isNationalStock[1];         //국민주여부
	char evaluatePrice[11];         //평가가격
	char lowestQuotePrice[11];         //최저호가가격
	char highestQuotePrice[11];         //최고호가가격
	char MainBaordVolumeUnit[11];         //메인보드수량단위
	char JangAfterOvertimeVolumeUnit[11];         //장종료후시간외수량단위
	char REITsClassCode[1];         //리츠종류코드
	char objectSovereign[12];         //목적주권종목코드
	char CurrencyISOCode[3];         //통화ISO코드
	char NationalCode[3];         //국가코드
	char BelfastPossibleIs[1];         //시장조성가능여부
	char OvertimeTradePossibleIs[1];         //시간외매매가능여부
	char isBeforeMarketOvertimeMarketClosePrice[1];         //장개시전시간외종가가능여부
	char isBeforeMarketOvertimeMarketBlockTradingPossibility[1];         //장개시전시간외대량매매가능여부
	char isBeforeMarketOvertimeMarketBasketPossibility[1];         //장개시전시간외바스켓가능여부
	char isEstimatedTradePriceOpen[1];         //예상체결가공개여부
	char isShortStockSellingPossibility[1];         //공매도가능여부
	char ETFFollowingEarningRateMultiple[13];         //추적수익률배수
	char REGSIS[1];         //REGS여부
	char SPACIS[1];         //SPAC여부
	char taxImportedTypeCode[1];         //과세유형코드
	char rateSubstitutePriceCalcurated[13];         //대용가격사정비율
	char isStockInvestmentWarningAttention[1];         //투자주의환기종목여부
	char delistingDate[8];         //상장폐지일자
	char shortTermFeverishInstrumentTypeCode[1];         //단기과열종목구분코드
	char ETFReplicationMethodTypeCode[1];         //ETF복제방법구분코드
	char expirationDate[8];         //만기일자
	char distributeTypeCode[2];         //분배금형태코드
	char expirationRedemptionPriceDecisionStartDate[8];         //만기상환가격결정시작일자
	char expirationRedemptionPriceDecisionEndDate[8];         //만기상환가격결정종료일자
	char etpProductTypeCode[1];         //ETP상품구분코드
	char indexCalculationInstitution_code[2];         //지수산출기관코드
	char indexMarket_classification_id[6];         //지수시장분류ID
	char indexSeqNumber[3];         //지수일련번호
	char trackingIndexLeverageInverseTypeCode[2];         //추적지수레버리지인버스구분코드
	char referenceIndexLeverageInverseTypeCode[2];         //참고지수레버리지인버스구분코드
	char indexAssetClassificationId1[6];         //지수자산분류ID1
	char indexAssetClassificationId2[6];         //지수자산분류ID2
	char RecommendTestimonialNo[5];         //상장주선사회원번호
	char lpOrderPossibility[1];         //LP주문가능여부
	char lowLiquidity[1];         //저유동성여부
	char abnormalRise[1];         //이상급등여부
	char upperLimitQuantity[23];         //상한수량
	char isInvestmentPrecautionIssue[1];         //투자유의종목여부
	char TradingVolumeInsufficientIs[1];         //상장주식수부족종목여부
	char isSPAC_merger[1];         //SPAC소멸합병여부
	char segment_code[1];         //세그먼트구분코드
	char endOfText[1];         //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_MASTER_SIZE = sizeof(ExtureGroupCMaster);

//증권 지수 및 투자지표
//(증권A) STK : CA01S
//(증권B) KSQ : CA01Q
//(주식파생) STK : CA01S
//(주식파생) KSQ : CA01Q
class ExtureGroupCJisuMaster
{
    public:
	char dataClass[2];                  //정보분배 데이터를 식별하는 구분 코드값
	char infoMarketClass[3];            //정보분배에서 분배하는 정보의 구분 코드값
	char distributeStockIndex[8];		//정보분배에서 부여하는 일련번호
										//시세 : 종목별 보드별 부여 (※ 대용량 서비스에서 제공)
										//종목정보 :  정보구분값별 부여
										//기타 : 데이터구분값별 부여
	char stockCode[12];         //종목코드
	char stockSeq[6];           //일련번호
	char stockGroupID[2];         //증권그룹ID
	char isEPSCalcExclusion[1];         //주당순이익산출제외여부
	char EPS[22];         //주당순이익
	char isloss[1];         //결손여부
	char PER[13];         //주가수익율
	char isBPSCalcExclusion[1];         //주당순자산가치산출제외여부
	char BPS[22];         //주당순자산가치
	char PBR[13];         //주당순자산비율
	char isDividendPriceExclusion[1];         //주당배당금산출제외여부
	char dividendPrice[22];         //주당배당금액
	char dividendEarningRate[13];         //배당수익율
	char listPriceSizeCode[1];         //시가총액규모코드
	char isManufactureIndustry[1];         //제조업여부
	char indexBusinessTypeLarge[6];         //지수업종대분류코드
	char indexBusinessTypeMedium[6];         //지수업종중분류코드
	char indexBusinessTypeSmall[6];         //지수업종소분류코드
	char businessTypeKOSPI200[1];         //KOSPI200섹터업종
	char businessTypeKOSPI200_2[1];         //KOSPI200커뮤니케이션서비스섹터 중복여부
	char isKOSPI[1];         //KOSPI지수종목여부
	char investOrganClassCode[1];         //KOSDAQ지수종목여부
	char isKOSPI100[1];         //KOSPI100여부
	char isKOSPI50[1];         //KOSPI50여부
	char kosdaq150IndexIssue[1];         //KOSDAQ150지수종목여부
	char isKRX100Stock[1];         //KRX100종목여부
	char krx300[1];         //KRX300지수여부
	char KOSPI200LowVolatilityHighDividendIndex[1];         //KOSPI200고배당지수여부
	char isKRX_BBIG_K_NewDealIndex[1];         //KRXBBIGK뉴딜지수여부
	char isKRX_secondaryBattery_K_NewDealIndex[1];         //KRX2차전지K뉴딜지수여부
	char isKRX_bio_K_NewDealIndex[1];         //KRX바이오K뉴딜지수여부
	char filler[9];         //
	char endOfText[1];         //
};
const int EXTURE_GROUP_C_JISU_MASTER_SIZE = sizeof(ExtureGroupCJisuMaster);
#endif

#if(1)
//장운영TS
//장운영 Trading Session 이벤트 발생시 종목별 제공
//실시간
//(증권A) STK : A701S
//(증권C) STK : A702S, A703S, A704S
//(증권B) KSQ : A701Q
//(증권B) KNX : A701X
//(파생A) DRV : A701F, A703F
class ExtureGroupCMarketOperationTS
{
    public:
	char dataCategory[2];                                //데이터구분값
	char infoMarketClass[3];                                //정보구분값
	char distributeStockIndex[8];                                //정보분배일련번호
	char boardID[2];                                //보드ID
	char sessionID[2];                                //세션ID
	char issueCode[12];                                //종목코드
	char serialNo[6];                                //정보분배종목인덱스
	char tradeProcessTime[12];                                //매매처리시각
	char boardEventID[3];                                //보드이벤트ID
	char boardEventBeginTime[9];                                //보드이벤트시작시각
	char boardEventApplyCode[5];                                //보드이벤트적용군코드
	char tradingHaltReasonCode[3];                                //거래정지사유코드
	char endOfText[1];                                //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_MARKET_OPERATION_TS_SIZE = sizeof(ExtureGroupCMarketOperationTS);
#endif

#if(1)
//종목별투자자정보/배치/FTP
//종목별투자자정보/배치/FTP
class ExtureGroupCInvestorStock
{
    public:
        char dataClass[2];                                              // 001 DATA구분
        char infoClass[2];                                              // 002 정보구분
        char marketClass[1];                                            // 003 시장구분
        char exchange[2];             // 시장구분
        char date[8];                 // 일자
        char symbol[12];              // 종목코드
        char investor[4];             // 투자자구분
                                      // 1000:기관계 9000:외국인계
        char sellVolume[12];          // 매도거래량 // 단위:주
        char sellAmount[18];          // 매도거래대금 // 단위:원
        char buyVolume[12];           // 매수거래량 // 단위:주
        char buyAmount[18];           // 매수거래대금 // 단위:원
        char filler[14];              // FILLER 14
        char endOfText[1];
};
const int EXTURE_GROUP_C_INVESTOR_STOCK_SIZE = sizeof(ExtureGroupCInvestorStock);
#endif

#if(1)
//전자공시
//(증권A) STK  : F000S, E900S
//(증권A) KSQ  : F000Q, E900Q
//(증권A) KNX  : F000X, E900X
//(증권A) OTHERS : F0909, E9909
//전자공시 (온라인)    : F0
//전일 전자공시 (배치) : E9
class ExtureGroupCPublicNews
{
    public:
	char dataClass[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char stockCode[12];                                     //종목코드
	char publicNewsSerialNumber[6];                                     //공시연단위일련번호
	char perPublicNewsTotalPageSize[5];                                     //공시문서총페이지번호
	char perPulbicNewsPageSerialNumber[5];                                     //공시문서페이지번호
	char publicNewsDate[8];                                     //공시일자
	char sendDate[8];                                     //전송일자
	char publicNewsMarketClass[1];                                     //공시시장구분코드
	char stockName[40];                                     //종목약명
	char processClass[1];                                     //공시문서처리구분값
	char reason[5];                                     //공시사유구분코드값
	char koreanEnglishClass[1];                                     //공시언어구분값
	char publicNewsTitle[264];                                     //공시문서제목
	char publicNewsContents[1000];                                     //공시문서내용
	char isStockExistence[1];                                     //공시문서종목코드포함여부
	char isPulbicNewsContentsStockCode[1];                                     //공시페이지종목코드여부
	char stockCodeCount[2];                                     //공시페이지종목개수
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_PUBLIC_NEWS_SIZE = sizeof(ExtureGroupCPublicNews);
#endif

#if(1)
//종목이벤트 정보
//(증권A) STK : I601S
//(증권C) STK : I602S, I603S, I604S
//(증권B) KSQ : I601Q
//(증권B) KNX : I601X
//주식/채권 종목의 거래정지, 관리종목, 정리매매 등의 이벤트 정보
//선물회선은 (STK, KSQ) 종목 중 기초자산 해당종목만 필터링 "
class ExtureGroupCKOSPIIssueEventInformation
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char issueCode[12];                                     //종목코드
	char eventTypeCode[2];                                     //이벤트종류코드
	char eventOccurrenceCauseCode[4];                                     //이벤트발생사유코드
	char startDate[8];                                     //이벤트개시일자
	char expirationDate[8];                                     //이벤트종료일자
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_KOSPI_ISSUE_EVENT_INFORMATION_SIZE = sizeof(ExtureGroupCKOSPIIssueEventInformation);
#endif

#if(1)
//공매도정보
//(증권A) STK : I801S
//(증권C) STK : I802S, I803S, I804S
//(증권B) KSQ : I801Q
//(증권B) KNX : I801X
class ExtureGroupCShortSellingInformation
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char issueCode[12];                                     //종목코드
	char shortSellingDebtSecuritiesAskTradingVolume[12];                                     //차입공매도체결수량
	char shortSellingDebtSecuritiesAskTradingValue[22];                                     //차입공매도거래대금
	char upTickRuleAppliedCoveredShortSellingTradingVolume[12];                                     //업틱룰적용거래량
	char upTickRuleAppliedCoveredShortSellingTradingValue[22];                                     //업틱룰적용거래대금
	char upTickRuleUnappliedCoveredShortSellingTradingVolume[12];                                     //업틱룰예외거래량
	char upTickRuleUnappliedCoveredShortSellingTradingValue[22];                                     //업틱룰예외거래대금
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_SHORT_SELLING_INFORMATION_SIZE = sizeof(ExtureGroupCShortSellingInformation);
#endif

#if(1)
//장운영스케줄공개
//(증권A) STK : M401S
//(증권C) STK : M402S, M403S, M404S
//(증권B) KSQ : M401Q
//(증권B) KNX : M401X
//(채권A) BND : M401B
//(채권A) SMB : M401M
//(채권A) KTS : M401K
//(채권A) RPO : M401R
//(파생A) DRV : M401F, M402F, M403F, M404F, M405F, M406F, M407F, M408F, M409F, M410F, M411F, M412F, M413F, M415F, M416F
//(파생B) DRV : M414F
//(일반A) CMD : M401G
//(일반A) ETS : M401E
//장운영스케줄 이벤트 공개 발생시 제공
class ExtureGroupCMarketOperationScheduleDisclosure
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char marketCategory[3];                                     //장운영상품그룹ID
	char boardID[2];                                     //보드ID
	char boardEventID[3];                                     //보드이벤트ID
	char boardEventBeginTime[9];                                     //보드이벤트시작시각
	char boardEventApplyCode[5];                                     //보드이벤트적용군코드
	char sessionBeginEndCode[2];                                     //세션개시종료코드
	char sessionID[2];                                     //세션ID
	char issueCode[12];                                     //종목코드
	char listedIssueCode[12];                                     //상장사종목코드
	char productID[11];                                     //상품ID
	char tradingHaltReasonCode[3];                                     //거래정지사유코드
	char tradingHaltOccurenceTypeCode[1];                                     //거래정지발생유형코드
	char stepApplied[2];                                     //적용단계
	char stepAppliedOccuredCode[1];                                     //기준종목가격제한확대발생코드
	char stepAppliedScheduleTime[9];                                     //가격제한확대예정시각
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE = sizeof(ExtureGroupCMarketOperationScheduleDisclosure);
#endif

#if(1)
//코스피_종목상태정보(VI)
//VI 발동/해제 정보
//(증권A) STK : R801S
//(증권C) STK : R803S, R804S
//(증권B) KSQ : R801Q
//VI (Volatility Interruption) 발동/해제 정보
class ExtureGroupCKOSPIVolatilityInterruptionPerInstrument
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char boardID[2];                                     //보드ID
	char issueCode[12];                                     //종목코드
	char issueSeqNo[6];                                     //정보분배종목인덱스
	char tradeExecutionProcessingTime[12];                                     //매매처리시각
	char removalTimeOfVI[9];                                     //VI해제시각
	char VIApplicationCategoryCode[1];                                     //VI적용구분코드
	char VITypeCode[1];                                     //VI종류코드
	char basePriceToTriggerStaticVI[11];                                     //정적VI발동기준가격
	char basePriceToTriggerDynamicVI[11];                                     //동적VI발동기준가격
	char VITriggeringPrice[11];                                     //VI발동가격
	char disparateRatioStaticVI[13];                                     //정적VI발동가격괴리율
	char disparateRatioDynamicVI[13];                                     //동적VI발동가격괴리율
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_KOSPI_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE = sizeof(ExtureGroupCKOSPIVolatilityInterruptionPerInstrument);
#endif

#if(1)
//코스피 장개시전 호가잔량//주식 종가단일가매매 호가잔량(B801S)
//(증권A) STK : B801S
//(증권C) STK : B802S, B803S, B804S
//(증권B) KSQ : B801Q
//(증권B) KNX : B801X
class ExtureGroupCQuoteBefore
{
    public:

	char dataClass[2];                        //데이터구분값
	char infoMarketClass[3];                        //정보구분값
	char distributeStockIndex[8];                        //정보분배일련번호
	char boardID[2];                        //보드ID
							 //상품이 거래되는 장소인 보드를 식별하기 위한 ID. 
						 //동일 상품이라도 여러 보드에서 집계장을 달리하고 
						 //독립적인 매매스케쥴과 매매규칙하에 각각의 가격으로 거래될 수 있으며 
						 //정규장(메인보드), 
						 //장전/후 시간외종가, 
						 //시간외단일가, 
						 //장전/중/후 대량매매 등이 보드에 해당함
	char stockCode[12];                        //종목코드
	char serialNo[6];                        //정보분배종목인덱스
	char tradeTime[12];                        //매매처리시각
	char accmTradeVolume[12];                        //누적거래량
	char totalAskQouteVolume[12];                        //매도호가총잔량
	char totalBidQuoteVolume[12];                        //매수호가총잔량
	char endOfText[1];                        //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_QUOTE_BEFORE_SIZE = sizeof(ExtureGroupCQuoteBefore);
#endif

#if(1)
//업종별 투자자별 통계//업종별 투자자별 통계
//09:00~18:00 [90초 주기]
//(증권A) STK : C001S
//(증권B) KSQ : C001Q
//(증권B) KNX : C001X
class ExtureGroupCTotalInvestorIndex
{
    public:
	char dataClass[2];              //데이터구분값
	char infoMarketClass[3];              //정보구분값
	char calculationTime[6];              //통계산출시각
	char investorCode[4];              //투자자구분코드
	char jisuIdentifiation[6];              //지수ID
	char jisuStandardCode[12];              //표준코드
	char askTradeVolume[12];              //누적매도체결수량
	char askTradeAmount[22];              //누적매도거래대금
	char bidTradeVolume[12];              //누적매수체결수량
	char bidTradeAmount[22];              //누적매수거래대금
	char filler[3];              //필러값3
	char endText[1];              //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_TOTAL_INVESTOR_INDEX_SIZE = sizeof(ExtureGroupCTotalInvestorIndex);
#endif

#if(1)
//코스콤 정보	외국인 투자정보	코스피 외국인 종목별투자정보(확정치)	F101S
//코스콤 정보	외국인 투자정보	코스닥 외국인 종목별투자정보(확정치)	F101Q
class ExtureGroupCForeignerMaster
{
	public:
	char dataClass[2];                                       //데이터구분값
	char infoMarketClass[3];                                 //정보구분값
	char stockCode[12];                                      //종목코드
	char serialNo[8];                                        //일련번호
	char tradeDate[8];                                       //매매일자
	char stockLimitRate[5];                                  //종목한도비율
	char individualLimitRate[5];                             //개인한도비율
	char listingStockSize[15];                               //상장주식수
	char orderPossibilityVolume[15];                         //주문가능수량
	char limitExhaustClass[1];                               //한도소진구분
	char filler[5];                                          //FILLER
	char endText[1];                                         //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_FOREIGNER_MASTER_SIZE = sizeof(ExtureGroupCForeignerMaster);
#endif

#if(1)
//코스콤 정보	외국인 투자정보	코스피 외국인 확정치데이터재전송	F401S
//코스콤 정보	외국인 투자정보	코스닥 외국인 확정치데이터재전송	F401Q
class ExtureGroupCForeignerMasterUpdate
{
	public:
	char dataClass[2];                                       //데이터구분값
	char infoMarketClass[3];                                 //정보구분값
	char stockCode[12];                                      //종목코드
	char stockLimitRate[5];                                  //종목한도비율
	char individualLimitRate[5];                             //개인한도비율
	char listingStockSize[15];                               //상장주식수
	char orderPossibilityVolume[15];                         //주문가능수량
	char limitExhaustClass[1];                               //한도소진구분
	char filler[1];                                          //FILLER
	char endText[1];                                         //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_FOREIGNER_MASTER_UPDATE_SIZE = sizeof(ExtureGroupCForeignerMasterUpdate);
#endif

#if(1)
//코스콤 정보	ETP정보
//ETN 사무수탁정보	
//S104S
class ExtureGroupCETNTransferAgentBatchData
{
	public:
	char dataCategory[2];                                        //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char issueCode[12];                                          //종목코드
	char seqNumber[8];                                           //일련번호
	char finalIndexValue[9];                                     //최종지표가치
	char indexValueInSumOfMoney[15];                             //지표가치금액
	char previousDayTaxableBasicPrice[9];                        //전일과표기준가격
	char previousDayTaxableBasicPriceBeforeDividend[9];          //전일배당전과표기준가격
	char previousDayCashDividendPrice[12];                       //전일현금배당금액
	char aDayBeforePreviousDayTaxableBasicPrice[9];              //전전일가격과표기준가격
	char volatilityFuturesType[2];                               //변동성선물구분
	char minimumQuantityOfCall[10];                              //중도상환청구최소수량
	char interestRateOfCall[10];                                 //중도상환수수료율
	char expenses[9];                                            //제비용
	char filler[10];                                             //FILLER
	char endText[1];                                             //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_ETN_TRANSFER_AGENT_BATCH_DATA_SIZE = sizeof(ExtureGroupCETNTransferAgentBatchData);
#endif

#if(1)
//코스콤 정보,ETP정보,ETN 기초지수 구성종목	S204S
class ExtureGroupCETNIndexCompositionConstituents
{
	public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                  //정보구분값
	char ETNIssueCode[12];                                    //종목코드
	char dataSeqNumber[8];                                    //데이터 일련번호
	char date[8];                                             //일자
	char officeConsignmentCompanyRegistrationNumber[3];       //사무수탁회사번호
	char numberOfCompositionConstituents[4];                  //구성종목수
	char compositionConstituentsCode[12];                     //구성종목코드
	char nameOfCompositionConstituents[80];                   //구성종목명
	char compositionRate[7];                                  //구성비
	char filler[60];                        //FILLER
	char endText[1];                        //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE = sizeof(ExtureGroupCETNIndexCompositionConstituents);
#endif

#if(1)
//코스콤 정보,ETP정보,ETN IIV,S304S
class ExtureGroupCETN_IIV
{
	public:
	char dataCategory[2];                 //데이터구분값
	char infoMarketClass[3];              //정보구분값
	char ETNIssueCode[12];                //종목코드
	char hours[6];                        //시간
	char previousDayIV[9];                //전일 IV
	char duringMarketHoursFinalIV[9];     //장중/최종 IV
	char filler[28];                      //FILLER
	char endText[1];                      //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_ETN_IIV_SIZE = sizeof(ExtureGroupCETN_IIV);
#endif

#if(1)
//코스콤 정보,ETP정보,ETF 사무수탁배치,N803S
class ExtureGroupCETFWorkEntrustmentBatch
{
	public:
	char dataClass[2];                                          //데이터구분값
	char infoMarketClass[3];                                    //정보구분값
	char stockCode[12];                                         //종목코드
	char seiralNo[8];                                           //일련번호
	char ETFCurrencyStockSize[10];                              //ETF유통주식수
	char ETFCunrencyNetAssetsTotalAmount[15];                                  //ETF유통순자산총액
	char ETFNetAssetsTotalAmount[15];                                          //ETF순자산총액
	char ETFLastNetAssetsValue[9];                                             //ETF최종순자산가치
	char ETFForeignMoneyCurrencyNetConAssetsTotalAmount[15];                               //ETF외화유통순자산총액
	char ETFForeignMoneyNetAssetsTotalAmount[15];                                          //ETF외화순자산총액
	char ETFForeignMoneyLastNetAssetsValue[9];                                            //ETF외화최종순자산가치
	char ETFCreationUnit[8];                                          //ETF CU수량
	char prevDayScorecardStandardPrice[9];                            //전일과표기준가격
	char prevPrevDayDividendScorecardStandardPrice[9];                //전일배당전과표기준가격
	char prevDayCashDividend[12];                                     //전일현금배당금액
	char prevPrevDayScorecardStandardPrice[9];                        //전전일과표기준가격
	char gStockprevDayScorecardStandardPrice[9];                      //해외주식전일비과세과표기준가
	char gStockprevDayDividendScorecardStandardPrice[9];              //해외주식전일비과세배당전과표기준가
	char gStockprePrevDayScorecardStandardPrice[9];                   //해외주식비과세전전일과표기준가
	char filler[62];                                          //FILLER
	char endText[1];                                          //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_ETF_WORK_ENTRUSTMENT_BATCH_SIZE = sizeof(ExtureGroupCETFWorkEntrustmentBatch);
#endif

#if(1)
//코스콤 정보,ETP정보,ETF PDF,F803S
class ExtureGroupCETF_PDF
{
	public:
	char dataCategory[2];                            //데이터구분값
	char infoMarketClass[3];                         //정보구분값
	char etfCode[12];                                //종목코드
	char dataSeqNumber[8];                           //데이터 일련번호
	char date[8];                                    //일자
	char transferAgentNumber[3];                     //사무수탁회사번호
	char compositionIssueNumber[4];                  //구성종목수
	char compositionIssueCode[12];                   //구성종목코드
	char oneCUUnitShare[18];                         //1CU단위증권수/계약수/원화현금
	char compositionIssueMarketType[1];              //구성종목시장구분
	char compositionIssueName[40];                   //구성종목명
	char parValueAmount[18];                         //액면금액/설정현금액
	char profitDistributionBasisDate[8];             //이익분배기준일
	char appraisedValue[18];                         //평가금액
	char filler[4];                                  //FILLER
	char endOfText[1];                               //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_ETF_PDF_SIZE = sizeof(ExtureGroupCETF_PDF);
#endif

#if(1)
// 현재등락
//(증권A) STK : B501S
//(증권B) KSQ : B501Q
//(증권B) KNX : B501X 
class ExtureGroupCUpDown
{
    public:
	 char data_category[2];           //       데이터구분값  
	 char infoMarketClass[3];               //       정보구분값   
	 char totalStockSize[5];          //       등락대상종목수
	 char tradeFormationStockSize[5]; //       등락거래형성수    
	 char upLimitStockSize[5];        //       등락상한수 
	 char upStockSize[5];             //       등락상승수  
	 char sattionaryStockSize[5];     //       등락보합수
	 char downLimitStockSize[5];      //       등락하한수
	 char downStockSize[5];           //       등락하락수  
	 char quotationStockSize[5];      //       등락기세수
	 char quotationUpStockSize[5];    //       등락기세상승수
	 char quotationDownStockSize[5];  //       등락기세하락수
	 char endText[1];                 //       정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_UPDOWN_SIZE = sizeof(ExtureGroupCUpDown);
#endif

#if(1)
//지수전문 통합
//IA000(정규장지수)
//IB000(예상지수)
class ExtureGroupCTotalElwIndex
{
	public:
	char dataClass[2];              //데이터구분값
	char infoMarketClass[3];        //정보구분값
	char dataID[6];                 //지수ID
	char standardCode[12];          //표준코드
	char time[6];                   //지수산출시각
	char index[9];                  //지수
	char sign[1];                   //전일대비지수부호
	char gap[9];                    //전일대비지수
	char tradeVolume[12];           //누적거래량
	char tradeAmount[12];           //누적거래대금
	char filler[4];                 //필러값
	char endText[1];                //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_TOTAL_ELW_INDEX_SIZE = sizeof(ExtureGroupCTotalElwIndex);
#endif

#if(1)
//협의거래 결과(TO-BE)//코스피대량체결(C4011)(AS-IS)
//협의거래 결과//종목별 보드별 협의거래 공개(누적거래량만)
//장종료 후 2회	
//(증권A) STK : C401S
//(증권C) STK : C402S, C403S, C404S
//(증권B) KSQ : C401Q
//(증권B) KNX : C401X
class ExtureGroupCTotalBulkTrade
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char boardID[2];                                     //보드ID
	char stockCode[12];                                     //종목코드
	char stockSeq[6];                                     //정보분배종목인덱스
	char accumlatedVolume[12];                                     //누적거래량
	char endText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_TOTAL_BULK_TRADE_SIZE = sizeof(ExtureGroupCTotalBulkTrade);
#endif

#if(1)
// 증권 체결
// (증권A) STK : A301S
// (증권C) STK : A302S, A303S, A304S
// (증권B) KSQ : A301Q
// (증권B) KNX : A301X
class ExtureGroupCTrade
{
    public:
     char dataClass[2];                        //       데이터구분값  
     char infoMarketClass[3];                        //       정보구분값   
     char distributeStockIndex[8];                         //       정보분배일련번호    
     char boardID[2];                          //       보드ID    
     char sessionID[2];                        //       세션ID    
     char stockCode[12];                       //       종목코드    
     char stockSeq[6];                         //       정보분배종목인덱스   
     char transactionProcessingTime[12];   	   //       매매처리시각  
     char upDown[1];                           //       전일대비구분코드    
     char gap[11];                              //       전일대비가격  
     char tradePrice[11];                       //       체결가격    
     char tradeVolume[10];                     //       거래량 
     char openPrice[11];                        //       시가  
     char highPrice[11];                        //       고가  
     char lowPrice[11];                         //       저가  
     char accmTradeVolume[12];                 //       누적거래량   
     char accmTradeAmount[22];                 //       누적거래대금  
     char lastAskBidClassCode[1];              //       최종매도매수구분코드  
     char LPHoldingVolume[15];                 //       LP보유수량  
     char askOneQuote[11];                      //       매도최우선호가가격   
     char bidOneQuote[11];                      //       매수최우선호가가격   
     char endText[1];                          //       정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_TRADE_SIZE = sizeof(ExtureGroupCTrade);
#endif

#if(1)
//기준가결정
//(증권A) STK : A401S
//(증권C) STK : A402S, A403S, A404S
//(증권B) KSQ : A401Q
//(증권B) KNX : A401X
//평가가격 대상 종목의 기준가결정시 제공
class ExtureGroupCKOSPIDeterminedBasePrice
{
	public:
	char dataCategory[2];                      // 데이터구분값
	char infoMarketClass[3];               // 정보구분값
	char distributeStockIndex[8];                        // 정보분배일련번호
	char boardID[2];                           // 보드ID
	char issueCode[12];                        // 종목코드
	char stockSeq[6];                          // 정보분배종목인덱스
	char basisPrice[11];                       // 기준가격
	char upperLimitPriceOfBasisPrice[11];      // 기준가격상한가
	char lowerLimitPriceOfBasisPrice[11];      // 기준가격하한가
	char endText[1];                           // 정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_KOSPI_DETERMINED_BASE_PRICE_SIZE = sizeof(ExtureGroupCKOSPIDeterminedBasePrice);
#endif

#if(1)
// 증권 우선호가 (MM/LP호가 제외)
// (증권A) STK : B601S
// (증권B) KSQ : B601Q
// (증권B) KNX : B601X
class ExtureGroupCQuoteRecord
{
    public:
	char askQuote[11];	                // 매도n단계우선호가가격
	char bidQuote[11];                  // 매수n단계우선호가가격
	char askQuoteVolume[12];            // 매도n단계우선호가잔량
	char bidQuoteVolume[12];            // 매수n단계우선호가잔량
};
const int EXTURE_GROUP_C_QUOTE_RECORD_SIZE = sizeof(ExtureGroupCQuoteRecord);

class ExtureGroupCQuote10
{
    public:
     char dataClass[2];       //       데이터구분값  
     char infoMarketClass[3];     //       정보구분값   
     char distributeStockIndex[8];                    //       정보분배일련번호    
     char boardID[2];     //       보드ID    
     char sessionID[2];   //       세션ID    
     char stockCode[12];      //       종목코드    
     char stockSeq[6];    //       정보분배종목인덱스   
     char tradingProcessingTime[12];  //       매매처리시각 
     ExtureGroupCQuoteRecord rec[10];			// 매도(수) n단계 우선호가 정보 
     char totalAskQuoteRemainder[12];     //       매도호가공개단계잔량합계    
     char totalBidQuoteRemainder[12];     //       매수호가공개단계잔량합계    
     char estimatedTradePrice[11];    //       예상체결가   
      char estimatedTradeVolume[12];      //       예상체결수량  
     char endText[1];     //       정보분배메세지종료키워드    
};
const int EXTURE_GROUP_C_QUOTE10_SIZE = sizeof(ExtureGroupCQuote10);
#endif

#if(1)
//코스피 거래원//거래상위 5개 회원 통계(B901S)
//(증권A) STK : B901S
//(증권C) STK : B902S, B903S, B904S
//(증권B) KSQ : B901Q
//(증권B) KNX : B901X
class ExtureGroupCSecuritiesTradeRecord
{
    public:
        char askSecuritiesTradeNumber[5];                             // 006-1 매도거래원번호
        char askTradeVolume[12];                                      // 006-2 매도체결수량
        char askTradeAmount[22];                                      // 006-3 매도거래대금
        char bidSecuritiesTradeNumber[5];                             // 006-4 매수거래원번호
        char bidTradeVolume[12];                                      // 006-5 매수체결수량
        char bidTradeAmount[22];                                      // 006-6 매수거래대금
};
const int EXTURE_GROUP_C_SECURITIES_TRADE_RECORD_SIZE = sizeof(ExtureGroupCSecuritiesTradeRecord);

class ExtureGroupCSecuritiesTrade
{
    public:
        char dataClass[2];                                            //데이터구분값
        char infoMarketClass[3];                                            //정보구분값
        char stockCode[12];                                           //종목코드
		char serialNo[6];                                             //정보분배종목인덱스
        ExtureGroupCSecuritiesTradeRecord rec[5];                   //거래원정보 OCCURS 5
        char endOfText[1];                                               //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_SECURITIES_TRADE_SIZE = sizeof(ExtureGroupCSecuritiesTrade);
#endif

#if(1)
//주식종목정보변경
//(증권A) STK : A801S
//(증권C) STK : A802S, A803S, A804S
//(증권B) KSQ : A801Q
//(증권B) KNX : A801X
class ExtureGroupCIssueInformationDisclosure
{
	public:
	char data_category[2];                                          //  데이터구분값  
	char infoMarketClass[3];                                   //  정보구분값   
	char board_id[2];                                               //  보드ID    
	char issue_code[12];                                            //  종목코드    
	char issue_seq_no[6];    										 //  정보분배종목인덱스   
	char disclosure_data_type_code[3];                              //  공개정보구분코드값   
	char basis_price[11];                                           //  기준가격    
	char upper_limit_price[11];                                     //  상한가 
	char lower_limit_price[11];                                     //  하한가 
	char evaluation_price[11];                                      //  평가가격    
	char highest_order_price[11];                                   //  최고호가가격  
	char lowest_order_price[11];                                    //  최저호가가격  
	char opening_price_becomes_basis_price_type[1];                 //  시가기준가격여부    
	char back_door_listing[2];                                      //  락구분코드   
	char par_value_change_type_code[2];                             //  액면가변경구분코드   
	char lot_size[11];                                              //  수량단위    
	char number_of_listed_stocks[16];                               //  상장주식수   
	char designation[1];                                            //  지정여부    
	char closing_price_possibility_in_pre_off_hours_session[1];     //  장개시전시간외종가가능여부   
	char endText[1];     										     //  정보분배메세지종료키워드    
};
const int EXTURE_GROUP_C_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExtureGroupCIssueInformationDisclosure);
#endif

#if(1)
//프로그램매매 전체집계
//(증권A) STK : J001S
//(증권B) KSQ : J001Q
//프로그램매매 전체집계
//차익종목 : 종합지수 대상종목
//비차익종목 : K200 or Q150 or KRX300 대상종목"
class ExtureGroupCProgramTradeTotal
{
    public:
	char dataClass[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char indexMarginalProfitAskQuoteRemainder[15];                                     //매도차익거래잔량
	char indexMarginalProfitBidQuoteRemainder[15];                                     //매수차익거래잔량
	char indexNotMarginalProfitAskQuoteRemainder[15];                                     //매도비차익잔량
	char indexNotMarginalProfitBidQuoteRemainder[15];                                     //매수비차익잔량
	char indexMarginalProfitAskQuoteVolume[15];                                     //매도차익수량
	char indexMarginalProfitBidQuoteVolume[15];                                     //매수차익수량
	char indexNotMarginalProfitAskQuoteVolume[15];                                     //매도비차익수량
	char indexNotMarginalProfitBidQuoteVolume[15];                                     //매수비차익수량
	char indexMarginalProfitAskConsignmentTradeVolume[10];                                     //위탁매도차익체결수량
	char indexMarginalProfitAskFloorTradeVolume[10];                                     //자기매도차익체결수량
	char indexMarginalProfitBidConsignmentTradeVolume[10];                                     //위탁매수차익체결수량
	char indexMarginalProfitBidFloorTradeVolume[10];                                     //자기매수차익체결수량
	char indexNotMarginalProfitAskConsignmentTradeVolume[10];                                     //위탁매도비차익체결수량
	char indexNotMarginalProfitAskFloorTradeVolume[10];                                     //자기매도비차익체결수량
	char indexNotMarginalProfitBidConsignmentTradeVolume[10];                                     //위탁매수비차익체결수량
	char indexNotMarginalProfitBidFloorTradeVolume[10];                                     //자기매수비차익체결수량
	char indexMarginalProfitAskConsignmentTradeAmount[22];                                     //위탁매도차익거래대금
	char indexMarginalProfitAskFloorTradeAmount[22];                                     //자기매도차익거래대금
	char indexMarginalProfitBidConsignmentTradeAmount[22];                                     //위탁매수차익거래대금
	char indexMarginalProfitBidFloorTradeAmount[22];                                     //자기매수차익거래대금
	char indexNotMarginalProfitAskConsignmentTradeAmount[22];                                     //위탁매도비차익거래대금
	char indexNotMarginalProfitAskFloorTradeAmount[22];                                     //자기매도비차익거래대금
	char indexNotMarginalProfitBidConsignmentTradeAmount[22];                                     //위탁매수비차익거래대금
	char indexNotMarginalProfitBidFloorTradeAmount[22];                                     //자기매수비차익거래대금
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_PROGRAM_TRADE_TOTAL_SIZE = sizeof(ExtureGroupCProgramTradeTotal);
#endif

#if(1)
//프로그램매매 호가//프로그램매매 종목별집계
//(증권A) STK : C301S
//(증권B) KSQ : C301Q
//프로그램매매 종목별집계
//차익종목 : 종합지수 대상종목
//비차익종목 : K200 or Q150 or KRX300 대상종목
class ExtureGroupCProgramTrade
{
    public:

	char dataClass[2];                        //데이터구분값
	char infoMarketClass[3];                        //정보구분값
	char stockCode[12];                        //종목코드
	char serialNo[6];                        //정보분배종목인덱스
	char indexMarginalProfitAskQuoteRemainder[15];                        //매도차익거래잔량
	char indexMarginalProfitBidQuoteRemainder[15];                        //매수차익거래잔량
	char indexNotMarginalProfitAskQuoteRemainder[15];                        //매도비차익잔량
	char indexNotMarginalProfitBidQuoteRemainder[15];                        //매수비차익잔량
	char indexMarginalProfitAskQuoteVolume[15];                        //매도차익수량
	char indexMarginalProfitBidQuoteVolume[15];                        //매수차익수량
	char indexNotMarginalProfitAskQuoteVolume[15];                        //매도비차익수량
	char indexNotMarginalProfitBidQuoteVolume[15];                        //매수비차익수량
	char indexMarginalProfitAskConsignmentTradeVolume[10];                        //위탁매도차익체결수량
	char indexMarginalProfitAskFloorTradeVolume[10];                        //자기매도차익체결수량
	char indexMarginalProfitBidConsignmentTradeVolume[10];                        //위탁매수차익체결수량
	char indexMarginalProfitBidFloorTradeVolume[10];                        //자기매수차익체결수량
	char indexNotMarginalProfitAskConsignmentTradeVolume[10];                        //위탁매도비차익체결수량
	char indexNotMarginalProfitAskFloorTradeVolume[10];                        //자기매도비차익체결수량
	char indexNotMarginalProfitBidConsignmentTradeVolume[10];                        //위탁매수비차익체결수량
	char indexNotMarginalProfitBidFloorTradeVolume[10];                        //자기매수비차익체결수량
	char indexMarginalProfitAskConsignmentTradeAmount[22];                        //위탁매도차익거래대금
	char indexMarginalProfitAskFloorTradeAmount[22];                        //자기매도차익거래대금
	char indexMarginalProfitBidConsignmentTradeAmount[22];                        //위탁매수차익거래대금
	char indexMarginalProfitBidFloorTradeAmount[22];                        //자기매수차익거래대금
	char indexNotMarginalProfitAskConsignmentTradeAmount[22];                        //위탁매도비차익거래대금
	char indexNotMarginalProfitAskFloorTradeAmount[22];                        //자기매도비차익거래대금
	char indexNotMarginalProfitBidConsignmentTradeAmount[22];                        //위탁매수비차익거래대금
	char indexNotMarginalProfitBidFloorTradeAmount[22];                        //자기매수비차익거래대금
	char endOfText[1];                        //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_PROGRAM_TRADE_SIZE = sizeof(ExtureGroupCProgramTrade);
#endif

#if(1)
//배분정보	
//(증권A) STK : O601S
//(증권C) STK : O602S, O603S, O604S
//(증권B) KSQ : O601Q
//(증권B) KNX : O601X
//(파생A) DRV : O601F, O603F
//단일가체결이 상/하한가로 결정되는 경우 상/하한가 매수, 매도주문에 대해 일정량의 수량을 순차적으로 배분하여 체결시키는 경우
class ExtureGroupCQuantityAllocation
{
    public:

	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char boardID[2];                                     //보드ID
	char issueCode[12];                                     //종목코드
	char serialNo[6];                                     //정보분배종목인덱스
	char allocationStartEnd[1];                                     //배분적용구분코드
	char allocationTypeCode[1];                                     //배분처리구분코드
	char timeForAllocationEnd[9];                                     //배분해제시각
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_QUANTITY_ALLOCATION_SIZE = sizeof(ExtureGroupCQuantityAllocation);
#endif
#if(1)
//증권 Snapshot (MM/LP호가 포함)
//종목별 보드별 snapshot 및 최종상태를 일정간격으로 제공 (MM/LP호가 포함)
//실시간 [건당 0.2초/전종목 전송후 30초 sleep] * 주기변경 가능
//(증권C) STK : B202S, B203S, B204S
class ExtureGroupCRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// 매도n단계우선호가가격
	char bidQuote[11];				// 매수n단계우선호가가격
	char askQuoteVolume[12];		// 매도n단계우선호가잔량
	char bidQuoteVolume[12];		// 매수n단계우선호가잔량
	char askQuoteVolumeLP[12];      // LP 매도호가 잔량
	char bidQuoteVolumeLP[12];      // LP 매수호가 잔량
};
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExtureGroupCRecoveryTotalTradeRecord);

//증권 Snapshot (MM/LP호가 포함)
//종목별 보드별 snapshot 및 최종상태를 일정간격으로 제공 (MM/LP호가 포함)
//실시간 [건당 0.2초/전종목 전송후 30초 sleep] * 주기변경 가능
//(증권C) STK : B202S, B203S, B204S
class ExtureGroupCRecoveryTotalTrade
{
	public:
	char dataClass[2];								// 데이터구분값 
	char infoMarketClass[3];						// 정보구분값 
	char boardID[2];								// 보드ID
	char sessionID[2];								// 세션ID
	char stockCode[12];								// 종목코드
	char stockSeq[6];								// 정보분배종목인덱스
	char upDown[1];             					// 전일대비구분코드
	char gap[11];							        // 전일대비가격
	char upLimitPrice[11];      					// 상한가
	char downLimitPrice[11];    					// 하한가 
	char closePrice[11];							// 현재가
    char openPrice[11];         					// 시가  
    char highPrice[11];         					// 고가  
    char lowPrice[11];          					// 저가  
    char accmTradeVolume[12];   					// 누적거래량   
    char accmTradeAmount[22];   					// 누적거래대금  
    char lastAskBidClassCode[1];					// 최종매도매수구분코드 
	ExtureGroupCRecoveryTotalTradeRecord rec[10];  // 매도(수) n단계 우선호가 정보
	char totalRemainingAskPrice[12];     			// 매도호가공개단계잔량합계    
	char totalRemainingBidPrice[12];     			// 매수호가공개단계잔량합계 
	char estimatedTradePrice[11];   				// 예상체결가   
    char estimatedTradeVolume[12];  				// 예상체결수량
	char realRateQuotationClass[1];    				// 전일종가구분코드
													// 1:실세
													// 2:기세
													// 3:거래무
													// 4:시가기준가종목의 기세
	char isTradeStop[1];            				// 거래정지여부
	char earlyClosedELWStatus[1];                   // ELW 조기종료여부
	char earlyClosedELWTime[9];                     // ELW 조기종료시간
    char endText[1];     							// 정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTotalTrade);

class ExtureGroupCRecoveryTrade
{
    public:
        char dataClass[2];                                          // 001 DATA구분
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드(표준코드)
        char serialNo[5];                                           // 005 종목일련번호
        char upDown[1];                                             // 006 등락구분
        char gap[9];                                                // 007 전일대비
        char closePrice[11];                                        // 008 현재가
        char openPrice[11];                                         // 009 시가
        char highPrice[11];                                         // 010 고가
        char lowPrice[11];                                          // 011 저가
        char askQuote[11];                                          // 012 매도호가
        char bidQuote[11];                                          // 013 매수호가
        char accmTradeVolume[12];                                   // 014 누적체결수량
        char accmTradeAmount[22];                                   // 015 누적거래대금
        char realRateQuotationClass[1];                             // 016 실세/기세구분
        char boardEventID[3];                                       // 017 보드이벤트ID
        char boardID[2];                                            // 018 보드ID
        char isTradeStop[1];                                        // 019 거래정지여부
        char beforeMarketOverTimeClosePriceTradeVolume[12];         // 020 장개시전시간외종가체결수량
        char beforeMarketOverTimeClosePriceTradeAmount[22];         // 021 장개시전시간외종가거래대금
        char regularMarketTradeVolume[12];                          // 022 정규장체결수량
        char regularMarketTradeAmount[22];                          // 023 정규장거래대금
        char afterMarketOvertimeClosePriceTradeVolume[12];          // 024 장종료후시간외종가체결수량
        char afterMarketOvertimeClosePriceTradeAmount[22];          // 025 장종료후시간외종가거래대금
	char overTimeMarketFixedAccmVolume[12];          //단일가체결수량
        char overTimeMarketFixedAccmAmount[22];          //단일가거래대금
	char manyBulkTradeVolume[12];          //대량체결수량
        char manyBulkTradeAmount[22];          //대량거래대금
        char earlyClosedELWStatus[1];                               // 026 ELW 조기종료여부
        char earlyClosedELWTime[6];                                 // 027 ELW 조기종료시간
        char aBlox[1];                                              // 028 경쟁대량 방향구분
        char regularBuyInTradingVolume[12];                         // 029 일반 Buy-In 체결수량
        char regularBuyInTradingValue[22];                          // 030 일반 Buy-In 거래대금
        char sameDayBuyInTradingVolume[12];                         // 031 당일 Buy-In 체결수량
        char sameDayBuyInTradingValue[22];                          // 032 당일 Buy-In 거래대금
        char filler[8];                                             // 033 FILLER
        char ff[1];                                                 // 034 FF
        char cr[1];
        char lf[1];                                                                                        // 36   LF  X   1
};
const int EXTURE_GROUP_C_RECOVERY_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTrade);
#endif
#if(1)





#if(0)
//코스피 종가 RECOVERY	B1011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//코스피 시세 RECOVERY	B2011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//코스피 시간외단일가 최종	B3011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//코스피 시간외단일가 RECOVERY	B4011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//증권 Snapshot (MM/LP호가 제외)	종목별 보드별 snapshot 및 최종상태를 일정간격으로 제공 (MM/LP호가 제외)	
//실시간[건당 0.2초/전종목 전송후 30초 sleep]
//주기변경 가능
//(증권A) STK : B201S
//(증권B) KSQ : B201Q
//(증권B) KNX : B201X
class ExtureGroupCRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// 매도n단계우선호가가격
	char bidQuote[11];				// 매수n단계우선호가가격
	char askQuoteVolume[12];		// 매도n단계우선호가잔량
	char bidQuoteVolume[12];		// 매수n단계우선호가잔량
};
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExtureGroupCRecoveryTotalTradeRecord);

class ExtureGroupCRecoveryTotalTrade
{
	public:
	char dataClass[2];								// 데이터구분값 
	char infoMarketClass[3];						// 정보구분값 
	char boardID[2];								// 보드ID
	char sessionID[2];								// 세션ID
	char stockCode[12];								// 종목코드
	char stockSeq[6];								// 정보분배종목인덱스
	char upDown[1];             					// 전일대비구분코드
	char gap[11];							        // 전일대비가격
	char upLimitPrice[11];      					// 상한가
	char downLimitPrice[11];    					// 하한가 
	char closePrice[11];							// 현재가
    char openPrice[11];         					// 시가  
    char highPrice[11];         					// 고가  
    char lowPrice[11];          					// 저가  
    char accmTradeVolume[12];   					// 누적거래량   
    char accmTradeAmount[22];   					// 누적거래대금  
    char lastAskBidClassCode[1];					// 최종매도매수구분코드 
	ExtureGroupCRecoveryTotalTradeRecord rec[10];  // 매도(수) n단계 우선호가 정보
	char totalRemainingAskPrice[12];     			// 매도호가공개단계잔량합계    
	char totalRemainingBidPrice[12];     			// 매수호가공개단계잔량합계 
	char estimatedTradePrice[11];   				// 예상체결가   
    char estimatedTradeVolume[12];  				// 예상체결수량
	char realRateQuotationClass[1];    				// 전일종가구분코드
													// 1:실세
													// 2:기세
													// 3:거래무
													// 4:시가기준가종목의 기세
	char isTradeStop[1];            				// 거래정지여부
    char endText[1];     							// 정보분배메세지종료키워드
};
const int EXTURE_GROUP_C_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTotalTrade);

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

class ExtureGroupCRecoveryTrade
{
    public:
        char dataClass[2];                                          // 001 DATA구분
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드(표준코드)
        char serialNo[5];                                           // 005 종목일련번호
        char upDown[1];                                             // 006 등락구분
        char gap[9];                                                // 007 전일대비
        char closePrice[11];                                        // 008 현재가
        char openPrice[11];                                         // 009 시가
        char highPrice[11];                                         // 010 고가
        char lowPrice[11];                                          // 011 저가
        char askQuote[11];                                          // 012 매도호가
        char bidQuote[11];                                          // 013 매수호가
        char accmTradeVolume[12];                                   // 014 누적체결수량
        char accmTradeAmount[22];                                   // 015 누적거래대금
        char realRateQuotationClass[1];                             // 016 실세/기세구분
        char boardEventID[3];                                       // 017 보드이벤트ID
        char boardID[2];                                            // 018 보드ID
        char isTradeStop[1];                                        // 019 거래정지여부

        char beforeMarketOverTimeClosePriceTradeVolume[12];         // 020 장개시전시간외종가체결수량
        char beforeMarketOverTimeClosePriceTradeAmount[22];         // 021 장개시전시간외종가거래대금

        char regularMarketTradeVolume[12];                          // 022 정규장체결수량
        char regularMarketTradeAmount[22];                          // 023 정규장거래대금

        char afterMarketOvertimeClosePriceTradeVolume[12];          // 024 장종료후시간외종가체결수량
        char afterMarketOvertimeClosePriceTradeAmount[22];          // 025 장종료후시간외종가거래대금

		char overTimeMarketFixedAccmVolume[12];          //단일가체결수량
        char overTimeMarketFixedAccmAmount[22];          //단일가거래대금

		char manyBulkTradeVolume[12];          //대량체결수량
        char manyBulkTradeAmount[22];          //대량거래대금

        char earlyClosedELWStatus[1];                               // 026 ELW 조기종료여부
        char earlyClosedELWTime[6];                                 // 027 ELW 조기종료시간

        char aBlox[1];                                              // 028 경쟁대량 방향구분
        char regularBuyInTradingVolume[12];                         // 029 일반 Buy-In 체결수량
        char regularBuyInTradingValue[22];                          // 030 일반 Buy-In 거래대금
        char sameDayBuyInTradingVolume[12];                         // 031 당일 Buy-In 체결수량
        char sameDayBuyInTradingValue[22];                          // 032 당일 Buy-In 거래대금
        char filler[8];                                             // 033 FILLER
        char ff[1];                                                 // 034 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_GROUP_C_RECOVERY_TRADE_SIZE = sizeof(ExtureGroupCRecoveryTrade);
#endif

// 유가증권_UDP_정보분배_20140203_4차안내.xlsb
//18  코스피_시간외단일가_최종   코스피_시간외단일가_최종   B3011   코스피_시간외단일가_최종   170 170 실시간
//19  코스피_시간외단일가_시세   코스피_시간외단일가_시세   B4011   코스피_시간외단일가_시세   170 170 실시간
class ExtureGroupCRecoveryTradeFixed
{
    public:
        char dataClass[2];                                          // 001 DATA구분
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드
        char serialNo[5];                                           // 005 종목일련번호
        char upDown[1];                                             // 006 시간외단일가등락구분
        char gap[9];                                                // 007 시간외단일가대비
        char overTimeMarketFixedUpLimitPrice[11];                    // 008 시간외단일가상한가
        char overTimeMarketFixedDownLimitPrice[11];                  // 009 시간외단일가하한가
        char overTimeMarketFixedCurrClosePrice[11];                  // 010 시간외단일가현재가
        char overTimeMarketFixedOpenPrice[11];                       // 011 시간외단일가시가
        char overTimeMarketFixedHighPrice[11];                       // 012 시간외단일가고가
        char overTimeMarketFixedLowPrice[11];                        // 013 시간외단일가저가
        char overTimeMarketFixedAskQuote[11];                        // 014 시간외단일매도호가
        char overTimeMarketFixedBikQuote[11];                        // 015 시간외단일매수호가
        char overTimeMarketFixedAccmVolume[12];                     // 016 시간외단일가누적체결수량
        char overTimeMarketFixedAccmAmount[22];                     // 017 시간외단일가누적거래대금
        char totalAccmVolume[12];                                   // 018 전체 총 누적체결수량
        char totlaAccmAmount[22];                                   // 019 전체 총 누적거래대금
        char overTimeMarketFixedMarketClass[1];                     // 020 시간외단일가장구분
        char isTradeStop[1];                                        // 021 거래정지여부
        char realRateQuotationClass[1];                             // 022 실세/기세 구분
        char filler[2];                                             // 023 FILLER
        char ff[1];                                                 // 024 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_GROUP_C_RECOVERY_TRADE_FIXED_SIZE = sizeof(ExtureGroupCRecoveryTradeFixed);
#endif

#if(1)
//18  KRX100지수    변경없음    C8011   KRX100지수    50  -   실시간
//19  KRX100예상지수  변경없음    C9011   KRX100예상지수  50  -   실시간
//20  KOSPI지수 변경없음    D0011   KOSPI지수 50  -   실시간
//21  KOSPI예상지수   변경없음    D1011   KOSPI예상지수   50  -   실시간
//22  KOSPI200지수  변경없음    D2011   KOSPI200지수  50  -   실시간
//23  KOSPI200예상지수    변경없음    D3011   KOSPI200예상지수    50  -   실시간
//24  KOSPI100/50지수   변경없음    D4011   KOSPI100/50지수   50  -   실시간
//25  KODI(배당)지수  변경없음    D6011   KODI(배당)지수  50  -   실시간
//26  KODI예상지수    변경없음    D7011   KODI예상지수    50  -   실시간
//27  "레버리지KOSPI200지수" 변경없음    K2011   레버리지KOSPI200지수  50  -   실시간
//28  섹터지수    변경없음    E0011   섹터지수    50  -   실시간
//29  섹터예상지수  변경없음    E1011   섹터예상지수  50  -   실시간
//30  KRX SRI지수   변경없음    L0011   KRX SRI지수(2009.09.14)   50  -   실시간
//31  KRX SRI예상지수 변경없음    L1011   KRX SRI예상지수(2009.09.14) 50  -   실시간

class ExtureGroupCIndex
{
    public:
        char dataClass[2];                                            // 001 DATA구분
        char infoClass[2];                                            // 001 정보구분
        char marketClass[1];                                          // 001 시장구분
        char businessTypeCode[3];                                     // 002 업종코드
        char time[6];                                                 // 003 시간
        char index[9];                                                // 004 지수
        char sign[1];                                                 // 005 부호
        char gap[9];                                                  // 006 대비
        char tradeVolume[12];                                          // 007 체결수량
        char tradeAmount[12];                                          // 008 거래대금
};
const int EXTURE_GROUP_C_INDEX_SIZE = sizeof(ExtureGroupCIndex);
#endif

#if(1)
class ExtureGroupCInvestorIndex
{
    public:
        char dataClass[2];                                            // 001 DATA구분
        char infoClass[2];                                            // 002 정보구분
        char marketClass[1];                                          // 003 시장구분
        char calculationTime[6];                                      // 004 산출시각
        char investorCode[4];                                         // 005 투자자코드
        char businessType[3];                                         // 006 업종코드
        char askTradeVolume[12];                                      // 007 매도체결수량
        char askTradeAmount[22];                                      // 008 매도거래대금
        char bidTradeVolume[12];                                      // 009 매수체결수량
        char bidTradeAmount[22];                                      // 010 매수거래대금
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
        char dataCategory[2];                                   // 001 DATA 구분
        char informationCategory[2];                            // 002 정보구분
        char marketCategory[1];                                 // 003 시장구분
        char time[4];                                           // 004 시간
        char ff[1];                                             // 005 FF
        char recvAddr[32];                                      // 수신주소정보(전문에는 없는 것)
};
const int EXTURE_GROUP_C_KOSCOM_LINE_LK_INFO_ELW_SIZE = sizeof(ExtureGroupCKoscomLineLKInfo_ELW);
#endif

#if(1)
// 지수 리커버리용 내부 레코드
// 체결 포맷을 빌려서 채운다.
// DATA 구분은 ZZ 로 임시로 설정함
class PaxfeedElwCustomIndexRecoveryRec
{
    public:
        char dataClass[2];                                          // 001 DATA구분(ZZ)
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드
        char serialNo[5];                                           // 005 종목일련번호(A0001 의 serialNo 와 같은 값이며, 사이즈가 다르지만 실제 유효한 값이 5자리를 안넘으므로 동일한 값임. 일련번호는 매일매일 다를 수 있음)
        char boardID[2];                                            // 006 보드 ID
        char upDown[1];                                             // 007 전일대비(기준가대비)구분
        char gap[9];                                                // 008 전일대비
        char tradePrice[9];                                         // 009 체결가격
        char tradeVolume[10];                                       // 010 체결수량
        char sessionID[2];                                          // 011 세션ID
        char openPrice[9];                                          // 012 시가
        char highPrice[9];                                          // 013 고가
        char lowPrice[9];                                           // 014 저가
        char accmTradeVolume[12];                                   // 015 누적체결수량
        char accmTradeAmount[18];                                   // 016 누적거래대금
        char lastAskBidClassCode[1];                                // 017 최종매도매수구분코드
        char isTradePriceQuotePrice1Equal[1];                       // 018 체결가와1호가일치여부
        char tradeTime[6];                                          // 019 체결시각
        char LPHoldingVolume[15];                                   // 020 LP보유수량
        char askOneQuote[9];                                        // 021 매도1호가
        char bidOneQuote[9];                                        // 022 매수1호가
        char filler[6];                                             // 023 FILLER(2)
        char ff[1];                                                 // 024 FF
        char cr[1];
        char lf[1];
};
const int PAXFEED_ELW_CUSTOM_INDEX_RECOVERY_REC = sizeof(PaxfeedElwCustomIndexRecoveryRec);
#endif

#if(1)
// 유가증권_UDP_코스콤정보분배_20140203_1차안내.xlsb
// 2    코스피 외국인 주문가능수량  변경없음    F2011   코스피 외국인 주문가능수량  40  -   실시간
class ExtureGroupCForeigner
{
    public:
        char dataClass[2];                                            // 001 DATA구분
        char infoClass[2];                                            // 002 정보구분
        char marketClass[1];                                          // 003 시장구분
        char stockCode[12];                                           // 004 종목코드
        char orderPossibilityVolume[15];                              // 005 주문가능 수량
        char dataType[2];                                             // 006 데이터종류(종류를 Type의로 함. 위에 DATA구분과 이름이 같기때문)
        char filler[5];                                               // 007 FILLER
        char ff[1];                                                   // 008 END OF TEXT
        char cr[1];
        char lf[1];
};
const int EXTURE_GROUP_C_FOREIGNER_SIZE = sizeof(ExtureGroupCForeigner);

// 유가증권_UDP_지수통계_20140203_4차안내.xlsb
// 16   코스피_프로그램매매 사전공시 코스피_프로그램매매 사전공시 C5011   프로그램매매 사전공시 100 100 실시간
class ExtureGroupCProgramTradePublic
{
    public:
        char dataClass[2];                                             // 001 데이터구분
        char infoClass[2];                                             // 002 정보구분
        char marketClass[1];                                           // 003 시장구분
        char stockCode[12];                                            // 004 종목코드
        char serialNo[8];                                              // 005 일련번호
        char askPublicAheadPublicPrevRemainder[12];                    // 006 사전공시신규호가매도수량(항목명변경:매도공시사전수량->사전공시신규호가매도수량)
        char bidPublicAheadPublicPrevRemainder[12];                    // 007 사전공시신규호가매수수량(항목명변경:매수공시사전수량->사전공시신규호가매수수량)
        char askPublicAheadPublicPrevCorrectingRemainder[12];          // 008 사전공시기제출호가매도수량(항목명변경:매도공시사전정정수량->사전공시기제출호가매도수량)
        char bidPublicAheadPublicPrevCorrectingRemainder[12];          // 009 사전공시기제출호가매수수량(항목명변경:매수공시사전정정수량->사전공시기제출호가매수수량)
        char postDisclosedProgramTradingSellOrderVolume[12];           // 010 사후공시매도수량(단위 : 주,  신규                2011.05.30)
        char postDisclosedProgramTradingBuyOrderVolume[12];            // 011 사후공시매수수량(단위 : 주,  신규                2011.05.30)
        char filler[2];                                                // 012 FILLER
        char ff[1];                                                    // 013 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_GROUP_C_PROGRAM_TRADE_PUBLIC_SIZE = sizeof(ExtureGroupCProgramTradePublic);

// 유가증권_UDP_지수통계_20140203_4차안내.xlsb
// 12  코스피_프로그램매매 일별차익거래잔고 변경없음    C2011   프로그램매매 일별차익거래잔고 380 -   "일일 05:30, 06:10, 06:50 총 3회 전송(단, A0011[KOSPI종목정보] 전송 완료 후 전송)"
class ExtureGroupCProgramTradeBatch
{
    public:
        char dataClass[2];                                            // 001 data구분
        char infoClass[2];                                            // 002 정보구분
        char marketClass[1];                                          // 003 시장구분
        char serialNo[8];                                             // 004 일련번호
        char ptFirstMonthClassCode[1];                                // 005 PT월물구분코드
        char consignmentFloorTradingClassCode[2];                     // 006 위탁자기구분코드
        char memberNo[5];                                             // 007 회원번호
        char tradeDate[8];                                            // 008 매매일자
        char stockAskVolume[12];                                      // 009 주식매도수량
        char stockAskAmount[22];                                      // 010 주식매도금액
        char stockBidVolume[12];                                      // 011 주식매수수량
        char stockBidAmount[22];                                      // 012 주식매수금액
        char futureAskVolume[12];                                     // 013 선물매도수량
        char futureAskAmount[22];                                     // 014 선물매도금액
        char futureBidVolume[12];                                     // 015 선물매수수량
        char futureBidAmount[22];                                     // 016 선물매수금액
        char callAskVolume[12];                                       // 017 콜매도수량
        char callAskAmount[22];                                       // 018 콜매도금액
        char callBidVolume[12];                                       // 019 콜매수수량
        char callBidAmount[22];                                       // 020 콜매수금액
        char putAskVolume[12];                                        // 021 풋매도수량
        char putAskAmount[22];                                        // 022 풋매도금액
        char putBidVolume[12];                                        // 023 풋매수수량
        char putBidAmount[22];                                        // 024 풋매수금액
        char stockErrorVolume[12];                                    // 025 주식오차수량
        char stockErrorCause[60];                                     // 026 주식오차사유
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
        char dataCategory[2];                                          // 001 DATA구분
        char informationCategory[2];                                   // 002 정보구분
        char marketCategory[1];                                        // 003 시장구분
        char issueCode[12];                                            // 004 종목코드
        char serialNo[5];                                              // 005 종목일련번호
        char seqNumber[8];                                             // 006 일련번호
        char kBloxVolumeInPreMarketTradingHoursSession[12];             // 007 장개시전 시간외 상대대량 체결수량
        char basketTradingVolumeInPreMarketTradingHoursSession[12];     // 008 장개시전 시간외 바스켓 체결수량
        char aBloxVolumeInPreMarketTradingHoursSession[12];             // 009 장개시전 시간외 경쟁대량체결수량
        char kBloxVolumeInRegularTradingHoursSession[12];               // 010 장중상대대량체결수량
        char basketTradingVolumeInRegularTradingHoursSession[12];       // 011 장중바스켓체결수량
        char aBloxVolumeInRegularTradingHoursSession[12];               // 012 장중경쟁대량체결수량
        char kBloxVolumeInPostMarketTradingHoursSession[12];            // 013 장종료후 시간외 상대대량체결수량
        char basketTradingVolumeInPostMarketTradingHoursSession[12];    // 014 장종료후 시간외 바스켓 체결수량
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
	char askQuote[11];	                // 매도n단계우선호가가격
	char bidQuote[11];                  // 매수n단계우선호가가격
	char askQuoteVolume[12];            // 매도n단계우선호가잔량
	char bidQuoteVolume[12];            // 매수n단계우선호가잔량
	char askQuoteVolumeLP[12]; //       매도n단계LP우선호가잔량    
	char bidQuoteVolumeLP[12]; //       매수n단계LP우선호가잔량
};
const int EXTURE_PLUS_ELW_QUOTE_RECORD_SIZE = sizeof(ExturePlusElwQuoteRecord);

class ExturePlusElwQuote10
{
    public:
	char dataClass[2];       //       데이터구분값  
	char infoMarketClass[3];     //       정보구분값   
	char distributeStockIndex[8];                    //       정보분배일련번호    
	char boardID[2];     //       보드ID    
	char sessionID[2];   //       세션ID    
	char stockCode[12];      //       종목코드    
	char stockSeq[6];    //       정보분배종목인덱스   
	char tradingProcessingTime[12];  //       매매처리시각 
	ExturePlusElwQuoteRecord rec[10];	// 매도(수) 우선호가 정보
	char totalAskQuoteRemainder[12];     //       매도호가공개단계잔량합계    
	char totalBidQuoteRemainder[12];     //       매수호가공개단계잔량합계    
	char estimatedTradePrice[11];    //       예상체결가   
	char estimatedTradeVolume[12];      //       예상체결수량  
	char endText[1];     //       정보분배메세지종료키워드    
};
const int EXTURE_PLUS_ELW_QUOTE10_SIZE = sizeof(ExturePlusElwQuote10);
#endif

#pragma pack()

#endif // __EXTURE_PLUS_INTERNET_ELW_H__
