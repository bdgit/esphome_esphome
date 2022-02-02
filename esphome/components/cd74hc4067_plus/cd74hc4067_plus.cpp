#include "cd74hc4067_plus.h"
#include "esphome/core/log.h"

namespace esphome {
namespace cd74hc4067_plus {

static const char *const TAG = "cd74hc4067_plus";

void CD74HC4067PlusComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up CD74HC4067_PLUS...");

  this->pin_s0_->setup();
  this->pin_s1_->setup();
  this->pin_s2_->setup();
  this->pin_s3_->setup();
  // this->sensor_signal_->setup(); // this is the sensor.adc so setup here is probably wrong

  // set other pin, so that activate_pin will really switch
  this->active_pin_ = 1;
  this->activate_pin(0);
}

void CD74HC4067PlusComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "CD74HC4067_PLUS Multiplexer:");
  LOG_PIN("  S0 Pin: ", this->pin_s0_);
  LOG_PIN("  S1 Pin: ", this->pin_s1_);
  LOG_PIN("  S2 Pin: ", this->pin_s2_);
  LOG_PIN("  S3 Pin: ", this->pin_s3_);
  ESP_LOGCONFIG(TAG, "switch delay: %d", this->switch_delay_);
  // ESP_LOGCONFIG(TAG, "sensor signal: %d", this->sensor_signal_);
}

float CD74HC4067PlusComponent::sample() { return this->sensor_signal_->sample(); }

void CD74HC4067PlusComponent::activate_pin(uint8_t pin) {
  if (this->active_pin_ != pin) {
    ESP_LOGD(TAG, "switch to input %d", pin);

    static int mux_channel[16][4] = {
        {0, 0, 0, 0},  // channel 0
        {1, 0, 0, 0},  // channel 1
        {0, 1, 0, 0},  // channel 2
        {1, 1, 0, 0},  // channel 3
        {0, 0, 1, 0},  // channel 4
        {1, 0, 1, 0},  // channel 5
        {0, 1, 1, 0},  // channel 6
        {1, 1, 1, 0},  // channel 7
        {0, 0, 0, 1},  // channel 8
        {1, 0, 0, 1},  // channel 9
        {0, 1, 0, 1},  // channel 10
        {1, 1, 0, 1},  // channel 11
        {0, 0, 1, 1},  // channel 12
        {1, 0, 1, 1},  // channel 13
        {0, 1, 1, 1},  // channel 14
        {1, 1, 1, 1}   // channel 15
    };
    this->pin_s0_->digital_write(mux_channel[pin][0]);
    this->pin_s1_->digital_write(mux_channel[pin][1]);
    this->pin_s2_->digital_write(mux_channel[pin][2]);
    this->pin_s3_->digital_write(mux_channel[pin][3]);
    // small delay is needed to let the multiplexer switch
    delay(this->switch_delay_);
    this->active_pin_ = pin;
  }
}

}  // namespace cd74hc4067_plus
}  // namespace esphome
