/*
 * SimpleStringUtil.h
 *
 *  Created on: 2012. 4. 4.
 *      Author: colaman
 */

#ifndef SIMPLESTRINGUTIL_H_
#define SIMPLESTRINGUTIL_H_

#include <iostream>
#include <ace/SString.h>

std::string trim(std::string rawStr);
ACE_CString trim_ACE(ACE_CString rawStr);
std::vector<std::string> tokenize(std::string strRaw, std::string strDelimiter);
std::string getTimestamp();
std::string getTimestamp(time_t utc);
time_t changeTimestampToUTC(std::string strTimestamp);

ACE_CString getDoubleString(ACE_CString raw, double multiple, double defaultValueIfNull);

double parseDouble(ACE_CString raw, double defaultValue);
int parseInt(ACE_CString raw, int defaultValue);

#endif /* SIMPLESTRINGUTIL_H_ */
