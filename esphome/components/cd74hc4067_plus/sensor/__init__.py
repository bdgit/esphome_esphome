import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, voltage_sampler
from esphome.const import (
    CONF_ID,
    CONF_NUMBER,
    ICON_FLASH,
    UNIT_VOLT,
    STATE_CLASS_MEASUREMENT,
    DEVICE_CLASS_VOLTAGE,
)
from .. import cd74hc4067_plus_ns, CD74HC4067PlusComponent

CONF_MUX = "mux"

DEPENDENCIES = ["cd74hc4067_plus"]
CODEOWNERS = ["@bdgit"]

CD74HC4067PlusSensor = cd74hc4067_plus_ns.class_(
    "CD74HC4067PlusSensor",
    sensor.Sensor,
    cg.PollingComponent,
    voltage_sampler.VoltageSampler,
)

# CONF_CD74HC4067_PLUS_ID = "cd74hc4067_plus_id"

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_FLASH,
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(CD74HC4067PlusSensor),
            # cv.GenerateID(CONF_CD74HC4067_PLUS_ID): cv.use_id(CD74HC4067PlusComponent),
            cv.Required(CONF_MUX): cv.use_id(CD74HC4067PlusComponent),
            cv.Required(CONF_NUMBER): cv.int_range(0, 15),
        }
    )
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    mux = await cg.get_variable(config[CONF_MUX])
    cg.add(var.set_mux(mux))

    cg.add(var.set_pin(config[CONF_NUMBER]))
