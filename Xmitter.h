#if !defined(_Xmitter_H_20040427_)
#define _Xmitter_H_20040427_

#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/SOCK_Dgram_Mcast.h"

class Xmitter : public ACE_SOCK_Dgram_Mcast
{
public:
  Xmitter(void) : active_(false) {;}
  ~Xmitter(void) {;}

  ACE_INLINE void setActive(bool active)
  { active_ = active;}// paxfeed::STATUS::instance()->setMode(active_ ? "ACTIVE" : "STANDBY"); }
  ACE_INLINE bool isActive() {return active_;}

  ACE_INLINE ssize_t send (const void *buf, size_t n, int flags=0) const
  {
    if (active_)
      return ACE_SOCK_Dgram_Mcast::send(buf, n, flags);

    return 0;
  }

private:
  bool active_;
};

typedef ACE_Singleton<Xmitter, ACE_Null_Mutex> XMITTER;

#endif // _Xmitter_H_20040427_
