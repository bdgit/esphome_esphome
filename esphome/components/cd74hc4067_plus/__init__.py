import esphome.codegen as cg
from esphome import pins
from esphome.components import voltage_sampler
import esphome.config_validation as cv
from esphome.const import (
    CONF_DELAY,
    CONF_ID,
)

AUTO_LOAD = ["sensor", "voltage_sampler"]
CODEOWNERS = ["@bdgit"]

cd74hc4067_plus_ns = cg.esphome_ns.namespace("cd74hc4067_plus")
CD74HC4067PlusComponent = cd74hc4067_plus_ns.class_(
    "CD74HC4067PlusComponent",
    cg.Component,
)

CONF_PIN_S0 = "pin_s0"
CONF_PIN_S1 = "pin_s1"
CONF_PIN_S2 = "pin_s2"
CONF_PIN_S3 = "pin_s3"
CONF_SENSOR_SIGNAL = "sensor_signal"

DEFAULT_DELAY = "2ms"

MULTI_CONF = True
CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(CD74HC4067PlusComponent),
        cv.Required(CONF_PIN_S0): pins.internal_gpio_output_pin_schema,
        cv.Required(CONF_PIN_S1): pins.internal_gpio_output_pin_schema,
        cv.Required(CONF_PIN_S2): pins.internal_gpio_output_pin_schema,
        cv.Required(CONF_PIN_S3): pins.internal_gpio_output_pin_schema,
        cv.Required(CONF_SENSOR_SIGNAL): cv.use_id(voltage_sampler.VoltageSampler),
        cv.Optional(
            CONF_DELAY, default=DEFAULT_DELAY
        ): cv.positive_time_period_milliseconds,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # rhs = CD74HC4067PlusComponent(template_)

    pin_s0 = await cg.gpio_pin_expression(config[CONF_PIN_S0])
    cg.add(var.set_pin_s0(pin_s0))

    pin_s1 = await cg.gpio_pin_expression(config[CONF_PIN_S1])
    cg.add(var.set_pin_s1(pin_s1))

    pin_s2 = await cg.gpio_pin_expression(config[CONF_PIN_S2])
    cg.add(var.set_pin_s2(pin_s2))

    pin_s3 = await cg.gpio_pin_expression(config[CONF_PIN_S3])
    cg.add(var.set_pin_s3(pin_s3))

    sensor_signal_id = await cg.get_variable(config[CONF_SENSOR_SIGNAL])
    cg.add(var.set_sensor_signal_id(sensor_signal_id))

    cg.add(var.set_switch_delay(config[CONF_DELAY]))
