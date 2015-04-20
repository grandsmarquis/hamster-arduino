
#ifndef	__H_LIGHT__
#define	__H_LIGHT__

class Light {

private:
  int pin;
  
public:

  Light(int pin);
  void low();
  void high();
};

#endif
