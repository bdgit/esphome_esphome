#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"

#include "esphome/core/helpers.h"
#include <cstring>

namespace esphome {
namespace cd74hc4067_plus {

// template<typename T> class CD74HC4067PlusComponent : public Component {
class CD74HC4067PlusComponent : public Component {
 public:
  /// Set up the internal sensor array.
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return esphome::setup_priority::LATE; }

  /// setting pin active by setting the right combination of the four multiplexer input pins
  void activate_pin(uint8_t pin);

  /// set the pin connected to multiplexer control pin 0
  void set_pin_s0(InternalGPIOPin *pin) { this->pin_s0_ = pin; }
  /// set the pin connected to multiplexer control pin 1
  void set_pin_s1(InternalGPIOPin *pin) { this->pin_s1_ = pin; }
  /// set the pin connected to multiplexer control pin 2
  void set_pin_s2(InternalGPIOPin *pin) { this->pin_s2_ = pin; }
  /// set the pin connected to multiplexer control pin 3
  void set_pin_s3(InternalGPIOPin *pin) { this->pin_s3_ = pin; }

  /// set the delay needed after an input switch
  void set_switch_delay(uint32_t switch_delay) { this->switch_delay_ = switch_delay; }

  void set_sensor_signal_id(voltage_sampler::VoltageSampler *sensor_signal) { this->sensor_signal_ = sensor_signal; }

  float sample();

 protected:
 private:
  InternalGPIOPin *pin_s0_;
  InternalGPIOPin *pin_s1_;
  InternalGPIOPin *pin_s2_;
  InternalGPIOPin *pin_s3_;
  /// the currently active pin
  uint8_t active_pin_;
  uint32_t switch_delay_;
  /// The sampling source to read values from.
  voltage_sampler::VoltageSampler *sensor_signal_;
};

}  // namespace cd74hc4067_plus
}  // namespace esphome
