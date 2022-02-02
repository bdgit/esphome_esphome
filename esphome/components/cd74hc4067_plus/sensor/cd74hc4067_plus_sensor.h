#pragma once

#include "esphome/core/component.h"
#include "esphome/components/cd74hc4067_plus/cd74hc4067_plus.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"

#include "esphome/core/helpers.h"
#include <cstring>

namespace esphome {
namespace cd74hc4067_plus {

class CD74HC4067PlusSensor : public sensor::Sensor, public PollingComponent, public voltage_sampler::VoltageSampler {
 public:
  void setup() override;
  float sample() override;
  void update() override;

  void dump_config() override;
  float get_setup_priority() const override { return this->mux_->get_setup_priority() - 1.0f; }

  void set_mux(CD74HC4067PlusComponent *mux) { this->mux_ = mux; }
  void set_pin(uint8_t pin) { this->pin_ = pin; }

 protected:
  CD74HC4067PlusComponent *mux_;
  uint8_t pin_;
};
}  // namespace cd74hc4067_plus
}  // namespace esphome
