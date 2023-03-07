// DataProcessor.h: interface for the DataProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAPROCESSOR_H__26A9399E_312B_4481_800E_1D8B949B3A20__INCLUDED_)
#define AFX_DATAPROCESSOR_H__26A9399E_312B_4481_800E_1D8B949B3A20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PaxfeedStatus.h"
#include "PacketWrappers.h"

class DataProcessor
{
    public:
        DataProcessor(int serial);
        virtual ~DataProcessor();

        ACE_INLINE
        void LogFrameCount(const ACE_CString& frameId) const
        {
            paxfeed::STATUS::instance()->increaseLineInfo(frameId);
        }

        virtual int sendPacket() = 0;ACE_INLINE
        int getSerial() const
        {
            return serial_;
        }
        ACE_CString getCurrentTimestamp();

    protected:
        virtual BYTE getExchange() = 0;
        virtual BYTE getPacketType() = 0;

        int sendPacket(const char data[], size_t len); // throws(std::runtime_error)
        int sendPacket(const ACE_CString& data); // throws(std::runtime_error)

        static void CheckSize(int recvsize, int standsize); // throws(std::runtime_error)
        static int xmit(const char* buf, int bufSize); // throws(std::runtime_error)

    private:
        void makeHeader(paxfeed::Header& header, size_t datasize);

    private:
        const int serial_;
        HeaderWrapper headerWrapper_;
};

#endif // !defined(AFX_DATAPROCESSOR_H__26A9399E_312B_4481_800E_1D8B949B3A20__INCLUDED_)
