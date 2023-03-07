// DataProcessor.cpp: implementation of the DataProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "PaxfeedPacket.h"
#include "PaxfeedPacketELW.h"
#include "PaxfeedPacketDefine.h"

#include "DataProcessor.h"
#include "EDataSize.h"
#include "Xmitter.h"

#include <stdexcept>
#include <vector>

DataProcessor::DataProcessor(int serial)
        : serial_(serial)
{
}

DataProcessor::~DataProcessor()
{

}

int DataProcessor::sendPacket(const char data[], size_t len) // throws(std::runtime_error)
{
    size_t packetSize = paxfeed::HEADER_SIZE + len + paxfeed::TAIL_SIZE;

    paxfeed::Header orgHeader;
    makeHeader(orgHeader, len + paxfeed::TAIL_SIZE);

    char bufHeader[HEADER_SIZE];
    ::memset(bufHeader, 0, sizeof ( bufHeader ));
    ::memcpy(bufHeader, &orgHeader, sizeof ( bufHeader ));
    paxfeed::Header header = headerWrapper_.getPacket(bufHeader, HEADER_SIZE);

    std::vector<char> transBuff(packetSize);
    size_t offset = 0;
    ACE_OS::memcpy(&transBuff[offset], &header, paxfeed::HEADER_SIZE);
    offset += paxfeed::HEADER_SIZE;
    ACE_OS::memcpy(&transBuff[offset], data, len);
    offset += len;
    ACE_OS::memcpy(&transBuff[offset], paxfeed::TAIL.c_str(), paxfeed::TAIL.length());
    offset += paxfeed::TAIL.length();

    return xmit(&transBuff[0], packetSize);
}

int DataProcessor::sendPacket(const ACE_CString& data) // throws(std::runtime_error)
{
    // ACE_DEBUG((LM_DEBUG, "DataProcessor::sendPacket:00:data:%s\n", data.c_str()));
    size_t packetSize = paxfeed::HEADER_SIZE + data.length() + paxfeed::TAIL_SIZE;

    paxfeed::Header orgHeader;
    makeHeader(orgHeader, data.length() + paxfeed::TAIL_SIZE);

    char bufHeader[HEADER_SIZE];
    ::memset(bufHeader, 0, sizeof ( bufHeader ));
    ::memcpy(bufHeader, &orgHeader, sizeof ( bufHeader ));
    paxfeed::Header header = headerWrapper_.getPacket(bufHeader, HEADER_SIZE);

    std::vector<char> transBuff(packetSize);
    size_t offset = 0;
    ACE_OS::memcpy(&transBuff[offset], &header, paxfeed::HEADER_SIZE);
    offset += paxfeed::HEADER_SIZE;
    ACE_OS::memcpy(&transBuff[offset], data.c_str(), data.length());
    offset += data.length();
    ACE_OS::memcpy(&transBuff[offset], paxfeed::TAIL.c_str(), paxfeed::TAIL.length());
    offset += paxfeed::TAIL.length();

    // ACE_DEBUG((LM_DEBUG, "DataProcessor::sendPacket:01\n"));

#if(0)
ACE_DEBUG((LM_DEBUG, ">>>>DataProcessor::sendPacket:data:%s\n", data.c_str()));
#endif

    return xmit(&transBuff[0], packetSize);
}

int DataProcessor::xmit(const char* buf, int bufSize) // throws(std::runtime_error)
{
    ssize_t sent = static_cast<int>(XMITTER::instance()->send(buf, bufSize));
    if ( sent == -1 ) throw std::runtime_error("xmit failed");

    return sent;
}

void DataProcessor::CheckSize(int recvsize, int standsize) // throws(std::runtime_error)
{
    if ( recvsize != standsize )
    {
        throw std::runtime_error("received data size is not equal to that of same frameId");
    }
}

void DataProcessor::makeHeader(paxfeed::Header& header, size_t datasize)
{
    header.majorVersion = paxfeed::VERSION_MAJOR;
    header.minorVersion = paxfeed::VERSION_MINOR;
    header.packetType = getPacketType();
    header.exchange = getExchange();
    header.serial = getSerial();
    header.time = ::time(0);
    header.dataSize = datasize;
}

/*
 현재 시간 문자열을 출력한다.
 YYYYMMDD_HHMMSS
 */
ACE_CString DataProcessor::getCurrentTimestamp()
{
    char buffer[32];
    ::memset(&buffer, 0, sizeof ( buffer ));
    struct tm stTm;
    ::memset(&stTm, 0, sizeof(struct tm));
    time_t currentTime = time(NULL);
    ::localtime_r(&currentTime, &stTm);
    ::strftime(buffer, sizeof ( buffer ), "%Y%m%d_%H%M%S", &stTm);
    ACE_CString strCurrentTime(buffer);
    return strCurrentTime;
}
