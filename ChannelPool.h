// hannelPool.h: interface for the ChannelPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANNELPOOL_H__E05258B6_A4EC_4CB0_B9F1_AE1715B20B3E__INCLUDED_)
#define AFX_HANNELPOOL_H__E05258B6_A4EC_4CB0_B9F1_AE1715B20B3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ace/Hash_Map_Manager_T.h"

class ChannelPool: public ACE_Hash_Map_Manager<ChannelProcInfo::IDType, ChannelProcessor*, ACE_Null_Mutex>
{
    public:
        ChannelPool(); // throw(ESource)
        virtual ~ChannelPool();

        ChannelProcessor* getChannelProcessor(ChannelProcInfo::IDType id);

};

#endif // !defined(AFX_HANNELPOOL_H__E05258B6_A4EC_4CB0_B9F1_AE1715B20B3E__INCLUDED_)
