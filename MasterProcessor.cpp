// MasterProcessor.cpp: implementation of the MasterProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include <sstream>
#include "PaxfeedPacketDefine.h"
#include "MasterProcessor.h"

MasterProcessor::MasterProcessor(int serial)
        : DataProcessor(serial)
{
    packetType_ = paxfeed::PACKET_MASTER;
}

MasterProcessor::~MasterProcessor()
{
}

ACE_CString MasterProcessor::makeMaster() const
{
    ACE_CString result;

    std::ostringstream os;

    const_iterator it(*this);
    while ( !it.done() )
    {
        os << ( *it ).ext_id_.c_str() << '|' << ( *it ).int_id_.c_str() << '\n';
        ++it;
    }

    // ACE_DEBUG((LM_DEBUG, "MasterProcessor::makeMaster():%s\n", os.str().c_str()));

    return ( os.str().c_str() );
}

int MasterProcessor::sendPacket()
{
//  return DataProcessor::sendPacket(makeMaster());
    ACE_CString strMasterPacket = makeMaster();
    ACE_DEBUG( ( LM_DEBUG , "[%s] [MasterProcessor::sendPacket]:[%s]\n" , getCurrentTimestamp().c_str() , strMasterPacket.c_str() ));
    return ( DataProcessor::sendPacket(strMasterPacket) );
}

void MasterProcessor::setPacketType(BYTE packetType)
{
    packetType_ = packetType;
}

BYTE MasterProcessor::getPacketType()
{
    return ( packetType_ );
}
