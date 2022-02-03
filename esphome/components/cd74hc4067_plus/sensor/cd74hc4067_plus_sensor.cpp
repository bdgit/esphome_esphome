#include "cd74hc4067_plus_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace cd74hc4067_plus {

static const char *const TAG = "cd74hc4067_plus";

void CD74HC4067PlusSensor::setup() {}

float CD74HC4067PlusSensor::sample() {
  this->mux_->activate_pin(this->pin_);
  return this->mux_->sample();
}

void CD74HC4067PlusSensor::update() {
  float value_v = this->sample();
  this->publish_state(value_v);
}

void CD74HC4067PlusSensor::dump_config() {
  LOG_SENSOR(TAG, "CD74HC4067_PLUS Sensor", this);
  // ESP_LOGCONFIG(TAG, "  Sensor has mux ID %u", this->mux_);
  ESP_LOGCONFIG(TAG, "  Pin: %u", this->pin_);
  LOG_UPDATE_INTERVAL(this);
}

// float CD74HC4067PlusSensor::get_setup_priority() const { return this->mux_->get_setup_priority() - 1.0f; }

}  // namespace cd74hc4067_plus
}  // namespace esphome
