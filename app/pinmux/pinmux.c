#define DT_ALIAS_PD1_GPIOS_PIN 33
#define DT_ALIAS_PD0_GPIOS_PIN 32
#define DT_ALIAS_PB3_GPIOS_PIN 3

#define SDA_PIN DT_ALIAS_PD1_GPIOS_PIN
#define SCL_PIN DT_ALIAS_PD0_GPIOS_PIN
#define CS_PIN DT_ALIAS_PB3_GPIOS_PIN

// Define Nice!View display GPIO flags
#define DISPLAY_GPIO_FLAGS (GPIO_OUTPUT | OUTPUT_ACTIVE_LOW | DISPLAY_GPIO_PIN_CONFIG)

const struct gpio_dt_spec gpio[] = {
    {DT_ALIAS(CS_PIN), GPIO_ACTIVE_HIGH},
};

static int niceview_init(const struct device *dev) {
    ARG_UNUSED(dev);

    // Configure I2C pins
    int ret = gpio_pin_configure(device_get_binding(DT_LABEL(DT_NODELABEL(i2c1))), SDA_PIN, GPIO_PULL_UP | GPIO_INPUT |  GPIO_DIR_OUT);
    if (ret &lt; 0) {
        return ret;
    }

    ret = gpio_pin_configure(device_get_binding(DT_LABEL(DT_NODELABEL(i2c1))), SCL_PIN, GPIO_PULL_UP | GPIO_INPUT |  GPIO_DIR_OUT);
    if (ret &lt; 0) {
        return ret;
    }

    ret = gpio_pin_configure_dt(&amp;gpio[0], GPIO_OUTPUT);
    if (ret &lt; 0) {
        return ret;
    }

    return 0;
}

SYS_INIT(niceview_init, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);