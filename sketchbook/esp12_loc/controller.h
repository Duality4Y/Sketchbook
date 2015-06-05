#ifndef CONTROLLER_H
#define CONTROLLER_H

#define STATIC 0

#include "artnet.h"

#define NUM_LEDS 170

class CController
{
  public:
    CController();

    void    Initialize();
    void    Process();
    void    HandlePacket(uint8_t ip[4], uint16_t port, uint8_t* data, uint16_t len);
    void    Transmit(uint8_t* data, uint16_t size, uint16_t sourceport, const uint8_t* destip, uint16_t destport);
    void    OnDmxData(uint8_t* data, uint16_t channels);
    void    OnValidData();

  private:
    void    SetPortAddressFromIp();

    CArtNet  m_artnet;
    uint32_t m_ledshowtime; 
    uint32_t m_validdatatime;
};

#endif //CONTROLLER_H
