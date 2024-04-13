#pragma once

#include "veins_inet/veins_inet.h"

#include "veins_inet/VeinsInetApplicationBase.h"

class VEINS_INET_API VeinsInetSampleApplication : public veins::VeinsInetApplicationBase {
protected:
    bool haveForwarded = false;
    int paquetesRecibidos = 0;
    int paquetesEnviados = 0;
    simtime_t totalDelay;
    double totalBitsRecibidos = 0;
    simtime_t tiempoInicio;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;
    virtual void finish() override;

public:
    VeinsInetSampleApplication();
    ~VeinsInetSampleApplication();
};
