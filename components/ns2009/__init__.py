import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ['i2c']
AUTO_LOAD = ['sensor']

ns2009_ns = cg.esphome_ns.namespace('ns2009')
NS2009Component = ns2009_ns.class_('NS2009Component', cg.Component, i2c.I2CDevice)

CONF_FAST_READS = 'fast_reads'

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(NS2009Component),
        cv.Optional(CONF_FAST_READS, default=False): cv.boolean,
    })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x48))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    
    if CONF_FAST_READS in config:
        cg.add(var.set_fast_reads(config[CONF_FAST_READS]))
