#include <Interfaces/IActuator.h>

#include <memory>
#include <string>
#include <vector>

#include "Step.h"

class ActuatorERM : public IActuator {
 protected:
  static int nextID;
  const static std::string defaultName;
  int id;
  std::shared_ptr<IActuatorDriver> m_driver;

 public:
  ActuatorERM() = delete;
  std::string m_name;
  // std::list<Device*> deviceList;
  explicit ActuatorERM(std::shared_ptr<IActuatorDriver> driver);
  ActuatorERM(std::shared_ptr<IActuatorDriver> driver, const std::string &name);
  void start();
  void stop();
  // Actuator(ActuatorDriverGPIO driver, std::string name, Device device);
  // addToDevice(Device device);
  // removeFromDevice(Device device);
  void setDriver(std::shared_ptr<IActuatorDriver> driver);
  ~ActuatorERM() = default;
};
