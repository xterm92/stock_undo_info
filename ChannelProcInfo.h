#ifndef _ChannelProcInfo_H_20041006_
#define _ChannelProcInfo_H_20041006_

class ChannelProcInfo
{
    public:
        typedef int IDType;

    public:
        static const IDType ID_KOSPI = 1;
        static const IDType ID_KOSDAQ = 2;

        static const IDType ID_FUTURE = 4;
        static const IDType ID_OPTION = 5;
        static const IDType ID_ELW = 6;
        static const IDType ID_TIMER = 100;
        static const IDType ID_ALL = 999;
};

#endif // _ChannelProcInfo_H_20041006_
