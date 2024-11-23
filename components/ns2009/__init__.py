import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["sensor"]

ns2009_ns = cg.esphome_ns.namespace("ns2009")
NS2009Component = ns2009_ns.class_("NS2009Component", cg.Component, i2c.I2CDevice)

CONF_FLIP_X = "flip_x"
CONF_FLIP_Y = "flip_y"
CONF_MIN_X = "min_x"
CONF_MAX_X = "max_x"
CONF_MIN_Y = "min_y"
CONF_MAX_Y = "max_y"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(NS2009Component),
            cv.Optional(CONF_FLIP_X, default=False): cv.boolean,
            cv.Optional(CONF_FLIP_Y, default=False): cv.boolean,
            cv.Optional(CONF_MIN_X, default=200): cv.int_,
            cv.Optional(CONF_MAX_X, default=3850): cv.int_,
            cv.Optional(CONF_MIN_Y, default=400): cv.int_,
            cv.Optional(CONF_MAX_Y, default=3920): cv.int_,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x48))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    
    cg.add(var.set_flip_x(config[CONF_FLIP_X]))
    cg.add(var.set_flip_y(config[CONF_FLIP_Y]))
    cg.add(var.calibrate(
        config[CONF_MIN_X],
        config[CONF_MAX_X],
        config[CONF_MIN_Y],
        config[CONF_MAX_Y]
    ))
