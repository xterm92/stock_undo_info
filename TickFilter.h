#ifndef _TICKFILTER_H_20040705_

class TickFilter
{
public:
  virtual bool mustFilterByCurrPrice(int currPrice);
};

#endif // _TICKFILTER_H_20040705_

