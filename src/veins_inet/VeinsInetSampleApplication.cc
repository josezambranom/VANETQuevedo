#include "veins_inet/VeinsInetSampleApplication.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

#include "veins_inet/VeinsInetSampleMessage_m.h"

using namespace inet;

Define_Module(VeinsInetSampleApplication);

VeinsInetSampleApplication::VeinsInetSampleApplication() : paquetesEnviados(0), paquetesRecibidos(0), totalDelay(0), totalBitsRecibidos(0), tiempoInicio(simTime()) {
}

/*bool VeinsInetSampleApplication::startApplication() {
    // La lógica inicial, especialmente para el vehículo que detecta el accidente.
    if (getParentModule()->getIndex() == 0) {
            auto callback = [this]() {
                getParentModule()->getDisplayString().setTagArg("i", 1, "red");

                traciVehicle->setSpeed(0);

                tiempoInicio = simTime();

                auto payload = makeShared<VeinsInetSampleMessage>();
                payload->setChunkLength(B(100));
                payload->setRoadId(traciVehicle->getRoadId().c_str());
                timestampPayload(payload);

                auto packet = createPacket("accidente");
                packet->insertAtBack(payload);

                sendPacket(std::move(packet));

                paquetesEnviados++; // Incrementa aquí
                EV_INFO << "Número de paquetes enviados: " << paquetesEnviados << endl;

                // host should continue after 50s
                auto callback = [this]() {
                    traciVehicle->setSpeed(-1);
                };
                timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(70, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(60, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(50, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(40, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(30, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(20, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(10, SIMTIME_S)));
            };
            timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(65, SIMTIME_S)));
            timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(55, SIMTIME_S)));
            timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(45, SIMTIME_S)));
            timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(35, SIMTIME_S)));
            timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(25, SIMTIME_S)));
            timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(15, SIMTIME_S)));
            timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(5, SIMTIME_S)));
        }

        return true;
}*/

bool VeinsInetSampleApplication::startApplication() {

    if (getParentModule()->getIndex() == 0) {
                auto callback = [this]() {
                    getParentModule()->getDisplayString().setTagArg("i", 1, "red");

                    traciVehicle->setSpeed(0);

                    tiempoInicio = simTime();

                    auto payload = makeShared<VeinsInetSampleMessage>();
                    payload->setChunkLength(B(100));
                    payload->setRoadId(traciVehicle->getRoadId().c_str());
                    timestampPayload(payload);

                    auto packet = createPacket("accidente");
                    packet->insertAtBack(payload);

                    sendPacket(std::move(packet));

                    paquetesEnviados++; // Incrementa aquí
                    EV_INFO << "Número de paquetes enviados: " << paquetesEnviados << endl;

                    // host should continue after 50s
                    auto callback = [this]() {
                        traciVehicle->setSpeed(0);
                    };
                    timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(80, SIMTIME_S)));
                    timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(70, SIMTIME_S)));
                    timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(60, SIMTIME_S)));
                    timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(50, SIMTIME_S)));
                    timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(40, SIMTIME_S)));
                    timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(30, SIMTIME_S)));
                    timerManager.create(veins::TimerSpecification(callback).oneshotIn(SimTime(20, SIMTIME_S)));
                };
                timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(75, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(65, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(55, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(45, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(35, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(25, SIMTIME_S)));
                timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(15, SIMTIME_S)));
            }
            return true;
}



bool VeinsInetSampleApplication::stopApplication() {
    return true;
}

VeinsInetSampleApplication::~VeinsInetSampleApplication() {
}

void VeinsInetSampleApplication::processPacket(std::shared_ptr<inet::Packet> pk) {
    paquetesRecibidos++;
    simtime_t receptionTime = simTime();
    simtime_t delay = receptionTime - tiempoInicio;
    totalDelay += delay;

    totalBitsRecibidos += pk->getBitLength();

    auto payload = pk->peekAtFront<VeinsInetSampleMessage>();

    if(strcmp(payload->getRoadId(), traciVehicle->getRoadId().c_str()) != 0) { // Comprobación para evitar cambiar ruta si ya está en la ruta del accidente
        traciVehicle->changeRoute(payload->getRoadId(), simTime().dbl()); // Cambia la ruta para evitar el accidente
    }
}

void VeinsInetSampleApplication::finish() {
    double tiempoSimulacion = (simTime() - tiempoInicio).dbl();
    double throughput = totalBitsRecibidos / tiempoSimulacion; // bits por segundo
    double delayPromedio = paquetesRecibidos > 0 ? totalDelay.dbl() / paquetesRecibidos : 0; // segundos
    double pdr = paquetesEnviados > 0 ? static_cast<double>(paquetesRecibidos) / static_cast<double>(paquetesEnviados) * 100.0 : 0; // porcentaje

    recordScalar("PDR", pdr);
    recordScalar("Delay", delayPromedio);
    recordScalar("Throughput", throughput);
}
