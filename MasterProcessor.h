// MasterProcessor.h: interface for the MasterProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASTERPROCESSOR_H__E53BC721_750E_4383_B9E2_EB3D3994D5C9__INCLUDED_)
#define AFX_MASTERPROCESSOR_H__E53BC721_750E_4383_B9E2_EB3D3994D5C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <ace/Map_Manager.h>
#include "DataProcessor.h"

class MasterProcessor: public DataProcessor, public ACE_Map_Manager<ACE_CString, ACE_CString, ACE_Null_Mutex>
{
    public:
        MasterProcessor(int serial);
        ~MasterProcessor();

        ACE_CString makeMaster() const;

        int sendPacket(); // override
        void setPacketType(BYTE packetType);

    protected:
        BYTE getPacketType(); // override

    private:
        BYTE packetType_;
};

#endif // !defined(AFX_MASTERPROCESSOR_H__E53BC721_750E_4383_B9E2_EB3D3994D5C9__INCLUDED_)
