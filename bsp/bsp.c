#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include "bsp.h" // Board Support Package

#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/reboot.h>

#include <zephyr/drivers/can.h>
#include <zephyr/drivers/led.h>
#include <zephyr/drivers/led/lp50xx.h>
#include <zephyr/dt-bindings/led/led.h>

#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>

#include "app/drivers/nafe13388.h"
#ifndef CONFIG_VE_SIM
LOG_MODULE_REGISTER(bsp, CONFIG_LOG_DEFAULT_LEVEL);

/*****************************************************************************/
/* GPIO */
#define USB_ID_PIN_MASK 0x100
#define USB_ID_GPIO_NUMBER 0x8

#define BUTTON_INPUTS_COUNT 5
#define DIGITAL_INPUT_LINES_COUNT 8

/*****************************************************************************/
/* Device tree */
#define CANBUS_NODE DT_CHOSEN(zephyr_canbus)
#define NAFE13388 DT_NODELABEL(nafe13388)
#define MODBUS_UART DT_NODELABEL(lpuart10)
#define MODBUS_NODE DT_ALIAS(modbus)
#define I2C_NODE DT_ALIAS(i2c)
#define GPIO_EXPANDER DT_ALIAS(gpio_expander)
#define DIGITAL_IN_PORT DT_ALIAS(digital_in_port)
#define DRV8844 DT_ALIAS(drv8844)

#define LED_RED DT_ALIAS(led_red)
#define LED_GREEN DT_ALIAS(led_green)
#define POWER_TFT_EN DT_ALIAS(power_tft_en)
#define BACKLIGHT_EN DT_ALIAS(backlight_led_en)
#define DISPLAY_RESET DT_ALIAS(display_reset)
#define BUZZER_EN DT_ALIAS(buzzer_en)
#define POWER_5V_EN DT_ALIAS(power_5v_en)
#define VREF_CTRL DT_ALIAS(vref_ctrl)
#define BUTTON_LED_DRIVER DT_ALIAS(button_led_driver)
#define NAFE_PWR_EN DT_ALIAS(nafe_pwr_en)

#define BOARD_BUTTON_0 DT_ALIAS(board_button_0)
#define BOARD_BUTTON_1 DT_ALIAS(board_button_1)
#define BOARD_BUTTON_2 DT_ALIAS(board_button_2)
#define BOARD_BUTTON_3 DT_ALIAS(board_button_3)
#define BOARD_BUTTON_4 DT_ALIAS(board_button_4)

#define DIGITAL_IN_1_HI DT_ALIAS(digital_in_1_hi)
#define DIGITAL_IN_1_LOW DT_ALIAS(digital_in_1_low)
#define DIGITAL_IN_2_HI DT_ALIAS(digital_in_2_hi)
#define DIGITAL_IN_2_LOW DT_ALIAS(digital_in_2_low)
#define DIGITAL_IN_3_HI DT_ALIAS(digital_in_3_hi)
#define DIGITAL_IN_3_LOW DT_ALIAS(digital_in_3_low)
#define DIGITAL_IN_4_HI DT_ALIAS(digital_in_4_hi)
#define DIGITAL_IN_4_LOW DT_ALIAS(digital_in_4_low)

#define USB_ID_INPUT DT_ALIAS(usb_id_input)

/*****************************************************************************/
/* FUSB303 address and registers */
#define FUSB_I2C_ADDR 0x21
#define FUSB_REG_CONTROL1 0x05
#define FUSB_REG_DEVICE_ID 0x01

#define FUSB_REG_CONTROL1_DEFAULT 0x23
#define FUSB_REG_CONTROL1_ENABLE 0x08
#define FUSB_REG_DEVICE_ID_VAL 0x10

/*****************************************************************************/
/* Private objects */
static struct gpio_dt_spec const l_led_red = GPIO_DT_SPEC_GET(LED_RED, gpios);
static struct gpio_dt_spec const l_led_green = GPIO_DT_SPEC_GET(LED_GREEN, gpios);
static struct gpio_dt_spec const power_tft_en = GPIO_DT_SPEC_GET(POWER_TFT_EN, gpios);
static struct gpio_dt_spec const reset_tft = GPIO_DT_SPEC_GET(DISPLAY_RESET, gpios);
static struct gpio_dt_spec const buzzer_en = GPIO_DT_SPEC_GET(BUZZER_EN, gpios);
static struct gpio_dt_spec const power_5v_en = GPIO_DT_SPEC_GET(POWER_5V_EN, gpios);
static struct gpio_dt_spec const vref_ctrl = GPIO_DT_SPEC_GET(VREF_CTRL, gpios);
static struct gpio_dt_spec const nafe_pwr_en = GPIO_DT_SPEC_GET(NAFE_PWR_EN, gpios);

static struct gpio_dt_spec const board_button_0 = GPIO_DT_SPEC_GET(BOARD_BUTTON_0, gpios);
static struct gpio_dt_spec const board_button_1 = GPIO_DT_SPEC_GET(BOARD_BUTTON_1, gpios);
static struct gpio_dt_spec const board_button_2 = GPIO_DT_SPEC_GET(BOARD_BUTTON_2, gpios);
static struct gpio_dt_spec const board_button_3 = GPIO_DT_SPEC_GET(BOARD_BUTTON_3, gpios);
static struct gpio_dt_spec const board_button_4 = GPIO_DT_SPEC_GET(BOARD_BUTTON_4, gpios);

static struct gpio_callback button_cb_data[BUTTON_INPUTS_COUNT];

static struct gpio_dt_spec const digital_in_1_hi = GPIO_DT_SPEC_GET(DIGITAL_IN_1_HI, gpios);
static struct gpio_dt_spec const digital_in_1_low = GPIO_DT_SPEC_GET(DIGITAL_IN_1_LOW, gpios);
static struct gpio_dt_spec const digital_in_2_hi = GPIO_DT_SPEC_GET(DIGITAL_IN_2_HI, gpios);
static struct gpio_dt_spec const digital_in_2_low = GPIO_DT_SPEC_GET(DIGITAL_IN_2_LOW, gpios);
static struct gpio_dt_spec const digital_in_3_hi = GPIO_DT_SPEC_GET(DIGITAL_IN_3_HI, gpios);
static struct gpio_dt_spec const digital_in_3_low = GPIO_DT_SPEC_GET(DIGITAL_IN_3_LOW, gpios);
static struct gpio_dt_spec const digital_in_4_hi = GPIO_DT_SPEC_GET(DIGITAL_IN_4_HI, gpios);
static struct gpio_dt_spec const digital_in_4_low = GPIO_DT_SPEC_GET(DIGITAL_IN_4_LOW, gpios);

static struct gpio_dt_spec const digital_input_lines[DIGITAL_INPUT_LINES_COUNT] = {
    digital_in_1_hi, digital_in_1_low, digital_in_2_hi, digital_in_2_low,
    digital_in_3_hi, digital_in_3_low, digital_in_4_hi, digital_in_4_low,
};

static struct gpio_callback digital_input_cb_data[DIGITAL_INPUT_LINES_COUNT];

static struct gpio_dt_spec const usb_id_input = GPIO_DT_SPEC_GET(USB_ID_INPUT, gpios);
static struct gpio_callback usb_id_input_cb_data;

static const struct device *gpio_expander = DEVICE_DT_GET(GPIO_EXPANDER);
static const struct device *button_led_driver = DEVICE_DT_GET(BUTTON_LED_DRIVER);
static const struct device *modbus_uart = DEVICE_DT_GET(MODBUS_UART);
static const struct device *canfd = DEVICE_DT_GET(CANBUS_NODE);
static const struct device *i2c = DEVICE_DT_GET(I2C_NODE);
static const struct device *digital_in_port = DEVICE_DT_GET(DIGITAL_IN_PORT);
static const struct device *drv8844 = DEVICE_DT_GET(DRV8844);

// Input buttons user callback
static on_input_button_changed_cb_t on_input_button_changed_cb = NULL;

struct input_button_changed_work_ {
    struct k_work work;
    input_button_t button;
    int state;
} input_button_changed_work;

// Work function to invoke callback on workqueue thread
static void invoke_user_input_button_cb(struct k_work *item)
{
    struct input_button_changed_work_ *w =
        CONTAINER_OF(item, struct input_button_changed_work_, work);

    if (on_input_button_changed_cb) {
        on_input_button_changed_cb(w->button, w->state);
    }
}

uint8_t pin_index = 6;

uint8_t check_button_pressed(void)
{
    return pin_index;
}

void set_button_pressed(uint8_t index)
{
    if (index < INPUT_BUTTON_MAX) {
        pin_index = index;
    } else {
        LOG_ERR("Invalid button index: %d", index);
    }
}

void reset_button_pressed(void)
{
    pin_index = 6;
}


/*****************************************************************************/
// GPIO Interrupt handler
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    input_button_t button = INPUT_BUTTON_0;

    // Which button has been pressed?
    switch (pins) {
    case 0x04:
        button = INPUT_BUTTON_0;
        pin_index = INPUT_BUTTON_0;
        break;
    case 0x40:
        button = INPUT_BUTTON_1;
        pin_index = INPUT_BUTTON_1;
        break;
    case 0x10:
        button = INPUT_BUTTON_2;
        pin_index = INPUT_BUTTON_2;
        break;
    case 0x20:
        button = INPUT_BUTTON_3;
        pin_index = INPUT_BUTTON_3;
        break;
    case 0x08:
        button = INPUT_BUTTON_4;
        pin_index = INPUT_BUTTON_4;
        break;
    default:
        LOG_ERR("Invalid pin 0x%02X", pins);
        return;
    };

    // Trigger user callback
    gpio_port_value_t port_val;
    int err = gpio_port_get(dev, &port_val);
    int state = (port_val & pins) ? 1 : 0;

    if (err) {
        state = -1;
    }

    input_button_changed_work.button = button;
    input_button_changed_work.state = state;
    k_work_submit(&input_button_changed_work.work);

    // if (on_input_button_changed_cb && err == 0) {
    //     int state = (port_val & pins) ? 1 : 0;
    //     on_input_button_changed_cb(button, state);
    // }
}

/*****************************************************************************/
// USB ID input interrupt handler
void usb_id_input_changed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    switch (pins) {
    case USB_ID_PIN_MASK: {
        int pin_state = gpio_pin_get(dev, USB_ID_GPIO_NUMBER);

        LOG_INF("USB role: %s", pin_state == 1 ? "source" : "sink");
        break;
    }
    default: {
        LOG_WRN("GPIO3 pin %d ISR triggered!", pins);
        break;
    }
    }
}

/*****************************************************************************/
// GPIO Interrupt handler
void digital_in_changed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    gpio_port_value_t port_val;
    gpio_port_get_raw(dev, &port_val);

    uint8_t digital_in_1 = (port_val >> 3) & 0b11; // Digital in 1: GPIO13 3 and 4
    uint8_t digital_in_2 = (port_val >> 5) & 0b11; // Digital in 2: GPIO13 5 and 6
    uint8_t digital_in_3 = (port_val >> 7) & 0b11; // Digital in 3: GPIO13 7 and 8
    uint8_t digital_in_4 = (port_val >> 9) & 0b11; // Digital in 4: GPIO13 9 and 10

    // 0b01 - low
    // 0b10 - high
    // ob11 - undefined
    LOG_INF("DIN1: 0x%02X, DIN2: 0x%02X, DIN3: 0x%02X, DIN4: 0x%02X", digital_in_1, digital_in_2,
            digital_in_3, digital_in_4);
}

/*****************************************************************************/

int bsp_init(void)
{
    /**************************************************************************/
    /* GPIOs */
    int ret = gpio_pin_configure_dt(&l_led_red, GPIO_OUTPUT_ACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring l_led_red");

    ret = gpio_pin_configure_dt(&l_led_green, GPIO_OUTPUT_ACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring l_led_green");

    ret = gpio_pin_configure_dt(&power_tft_en, GPIO_OUTPUT_INACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring power_tft_en");
    gpio_pin_set_dt(&power_tft_en, false);

    ret = gpio_pin_configure_dt(&reset_tft, GPIO_OUTPUT_ACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring reset_tft");
    gpio_pin_set_dt(&reset_tft, false);

    ret = gpio_pin_configure_dt(&buzzer_en, GPIO_OUTPUT_INACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring buzzer_en");

    ret = gpio_pin_configure_dt(&power_5v_en, GPIO_OUTPUT_ACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring power_5v_en");

    ret = gpio_pin_configure_dt(&vref_ctrl, GPIO_OUTPUT_ACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring vref_ctrl");

    /* NAFE power pin - configure but do not assert */
    ret = gpio_pin_configure_dt(&nafe_pwr_en, GPIO_OUTPUT_INACTIVE);
    //__ASSERT(ret >= 0, "Failed configuring nafe_pwr_en");

    /**************************************************************************/
    /* Board buttons on GPIO expander */
    //__ASSERT(device_is_ready(gpio_expander), "GPIO expander not ready");

    struct gpio_dt_spec const button_inputs[BUTTON_INPUTS_COUNT] = {
        board_button_0, board_button_1, board_button_2, board_button_3, board_button_4};

    for (int i = 0; i < BUTTON_INPUTS_COUNT; i++) {
        ret = gpio_pin_configure_dt(&button_inputs[i], GPIO_INPUT);
        //__ASSERT(ret >= 0, "Failed configuring button input %d", i);

        ret = gpio_pin_interrupt_configure_dt(&button_inputs[i], GPIO_INT_EDGE_FALLING);
        //__ASSERT(ret >= 0, "Failed configuring button input %d ISR", i);

        gpio_init_callback(&button_cb_data[i], button_pressed, BIT(button_inputs[i].pin));
        ret = gpio_add_callback(button_inputs[i].port, &button_cb_data[i]);
        //__ASSERT(ret >= 0, "Failed adding callback to button input %d", i);
    }

    k_work_init(&input_button_changed_work.work,
                invoke_user_input_button_cb); // Work submitted in buttons ISR

    /**************************************************************************/
    /* Tri-state digital inputs in SNVS domain */

    for (int i = 0; i < DIGITAL_INPUT_LINES_COUNT; i++) {
        ret = gpio_pin_configure_dt(&digital_input_lines[i], GPIO_INPUT);
        //__ASSERT(ret >= 0, "Failed configuring digital input line %d", i);

        // ret = gpio_pin_interrupt_configure_dt(&digital_input_lines[i], GPIO_INT_EDGE_BOTH);
        // //__ASSERT(ret >= 0, "Failed configuring digital input line %d ISR", i);

        // gpio_init_callback(&digital_input_cb_data[i], digital_in_changed,
        //                    BIT(digital_input_lines[i].pin));

        // ret = gpio_add_callback(digital_input_lines[i].port, &digital_input_cb_data[i]);
        // //__ASSERT(ret >= 0, "Failed adding callback to digital input line %d", i);
    }

    /**************************************************************************/
    /* FUSB303 */
    ret = device_is_ready(i2c);
    //__ASSERT(ret != 0, "I2C not ready");

    #ifndef CONFIG_VE_SIM
    /* Read device ID */
    uint8_t fusb_id = 0x0;
    ret = i2c_reg_read_byte(i2c, FUSB_I2C_ADDR, FUSB_REG_DEVICE_ID, &fusb_id);
    if (ret) {
        LOG_ERR("Failed to read FUSB ID (err %i)", ret);
    } else {
        LOG_DBG("FUSB ID 0x%02X", fusb_id);
    }

    if (fusb_id != FUSB_REG_DEVICE_ID_VAL) {
        LOG_ERR("FUSB Device ID not correct, expected 0x%02X", FUSB_REG_DEVICE_ID_VAL);
    }

    /* Set CONTROL1.ENABLE bit */
    ret = i2c_reg_write_byte(i2c, FUSB_I2C_ADDR, FUSB_REG_CONTROL1,
                             (FUSB_REG_CONTROL1_DEFAULT | FUSB_REG_CONTROL1_ENABLE));
    if (ret) {
        LOG_ERR("Failed to set FUSB303's CONTROL1.ENABLE bit!");
    }

    /* Configure USB ID as input */
    ret = gpio_is_ready_dt(&usb_id_input);
    //__ASSERT(ret >= 0, "USB ID input not ready");
    ret = gpio_pin_configure_dt(&usb_id_input, GPIO_INPUT);
    //__ASSERT(ret >= 0, "Failed configuring USB ID input");
    ret = gpio_pin_interrupt_configure_dt(&usb_id_input, GPIO_INT_EDGE_BOTH);
    //__ASSERT(ret >= 0, "Failed configuring USB ID ISR");
    gpio_init_callback(&usb_id_input_cb_data, usb_id_input_changed, BIT(usb_id_input.pin));
    ret = gpio_add_callback(usb_id_input.port, &usb_id_input_cb_data);
    //__ASSERT(ret >= 0, "Failed adding callback to USB ID");
    #endif
    /**************************************************************************/
    /* Button board LED driver */
    //__ASSERT(device_is_ready(button_led_driver), "LED driver not ready");
    for (int i = 0; i < 5; i++) {
        uint8_t color[] = {23, 194, 255};
        led_set_color(button_led_driver, i, 3, color);
        led_on(button_led_driver, i);
        led_set_brightness(button_led_driver, i, 5);
    }

    /**************************************************************************/
    /* CANFD */
    //__ASSERT(device_is_ready(canfd), "CANFD not ready");

    /**************************************************************************/
    /* Modbus UART */
    // //__ASSERT(device_is_ready(modbus_uart), "Modbus UART not ready");

    /**************************************************************************/
    /* Digital outputs */
    //__ASSERT(device_is_ready(drv8844), "DRV8844 not ready");
    return 0;
}

/*****************************************************************************/
int bsp_red_led_on(void)
{
    return gpio_pin_set_dt(&l_led_red, true);
}

/*****************************************************************************/
int bsp_red_led_off(void)
{
    return gpio_pin_set_dt(&l_led_red, false);
}

/*****************************************************************************/
int bsp_green_led_on(void)
{
    return gpio_pin_set_dt(&l_led_green, true);
}

/*****************************************************************************/
int bsp_green_led_off(void)
{
    return gpio_pin_set_dt(&l_led_green, false);
}

/*****************************************************************************/
int bsp_green_led_toggle(void)
{
    return gpio_pin_toggle_dt(&l_led_green);
}

/*****************************************************************************/
int bsp_red_led_toggle(void)
{
    return gpio_pin_toggle_dt(&l_led_red);
}

/*****************************************************************************/
int bsp_digital_input_isr_enable(digital_input_t din, bool enable)
{
    //__ASSERT(din < DIGITAL_IN_MAX, "Invalid pin number");

    int ret = 0;

    // Map digital input to processor input line index in digital_input_lines[] array
    static const uint8_t indices[DIGITAL_IN_MAX][2] = {
        [DIGITAL_IN_1] = {0, 1},
        [DIGITAL_IN_2] = {2, 3},
        [DIGITAL_IN_3] = {4, 5},
        [DIGITAL_IN_4] = {6, 7},
    };

    uint8_t input_line_1 = indices[din][0];
    uint8_t input_line_2 = indices[din][1];
    uint32_t int_flags = enable ? GPIO_INT_EDGE_BOTH : GPIO_INT_DISABLE;

    ret = gpio_pin_interrupt_configure_dt(&digital_input_lines[input_line_1], int_flags);
    //__ASSERT(ret >= 0, "Failed configuring digital input line %d ISR", input_line_1);

    ret = gpio_pin_interrupt_configure_dt(&digital_input_lines[input_line_2], int_flags);
    //__ASSERT(ret >= 0, "Failed configuring digital input line %d ISR", input_line_2);

    if (enable) {
        ret = gpio_add_callback(digital_input_lines[input_line_1].port,
                                &digital_input_cb_data[input_line_1]);
        //__ASSERT(ret >= 0, "Failed adding callback to digital input line %d", input_line_1);

        ret = gpio_add_callback(digital_input_lines[input_line_2].port,
                                &digital_input_cb_data[input_line_2]);
        //__ASSERT(ret >= 0, "Failed adding callback to digital input line %d", input_line_1);
    } else {
        ret = gpio_remove_callback(digital_input_lines[input_line_1].port,
                                   &digital_input_cb_data[input_line_1]);
        //__ASSERT(ret >= 0, "Failed adding callback to digital input line %d", input_line_1);

        ret = gpio_remove_callback(digital_input_lines[input_line_2].port,
                                   &digital_input_cb_data[input_line_2]);
        //__ASSERT(ret >= 0, "Failed adding callback to digital input line %d", input_line_1);
    }

    return ret;
}

/*****************************************************************************/
int bsp_nafe_power_on(void)
{
    return gpio_pin_set_dt(&nafe_pwr_en, true);
}

/*****************************************************************************/
int bsp_nafe_power_off(void)
{
    return gpio_pin_set_dt(&nafe_pwr_en, false);
}

/*****************************************************************************/
struct digital_inputs bsp_digital_inputs_get(void)
{
    struct digital_inputs inputs = {DIGITAL_IN_STATE_INVALID, DIGITAL_IN_STATE_INVALID,
                                    DIGITAL_IN_STATE_INVALID, DIGITAL_IN_STATE_INVALID, .err = 0};

    gpio_port_value_t port_val;
    int ret = gpio_port_get_raw(digital_in_port, &port_val);
    if (ret != 0) {
        inputs.err = ret;
        return inputs;
    }

    inputs.digital_in_1 = (port_val >> 3) & 0b11; // Digital in 1: GPIO13 3 and 4
    inputs.digital_in_2 = (port_val >> 5) & 0b11; // Digital in 2: GPIO13 5 and 6
    inputs.digital_in_3 = (port_val >> 7) & 0b11; // Digital in 3: GPIO13 7 and 8
    inputs.digital_in_4 = (port_val >> 9) & 0b11; // Digital in 4: GPIO13 9 and 10

    // If any of the digital inputs is set to 0b00, flag an error
    if ((inputs.digital_in_1 == 0x0 || inputs.digital_in_2 == 0x0 || inputs.digital_in_3 == 0x0 ||
         inputs.digital_in_4) == 0x0) {
        inputs.err = -2;
    }

    return inputs;
}

/*****************************************************************************/
digital_input_state_t bsp_digital_input_get(digital_input_t input)
{
    //__ASSERT(input >= DIGITAL_IN_1 && input < DIGITAL_IN_MAX, "Invalid input number");

    struct digital_inputs inputs = bsp_digital_inputs_get();

    if (inputs.err) {
        return DIGITAL_IN_STATE_INVALID;
    }

    switch (input) {
    case DIGITAL_IN_1:
        return inputs.digital_in_1;
    case DIGITAL_IN_2:
        return inputs.digital_in_2;
    case DIGITAL_IN_3:
        return inputs.digital_in_3;
    case DIGITAL_IN_4:
        return inputs.digital_in_4;
    default:
        //__ASSERT(0, "Invalid input number");
    }
}

/*****************************************************************************/
int bsp_digital_out_enable(digital_output_t output)
{
    return drv8844_output_enable(drv8844, output, 1);
}

/*****************************************************************************/
int bsp_digital_out_disable(digital_output_t output)
{
    return drv8844_output_enable(drv8844, output, 0);
}

/*****************************************************************************/
int bsp_digital_out_set(digital_output_t output)
{
    return drv8844_pulse_set(drv8844, output, 0xffffffff);
}

/*****************************************************************************/
int bsp_digital_out_reset(digital_output_t output)
{
    return drv8844_pulse_set(drv8844, output, 0x0);
}

/*****************************************************************************/
int bsp_digital_out_pwm_set(digital_output_t output, uint32_t pulse_width_ns)
{
    return drv8844_pulse_set(drv8844, output, pulse_width_ns);
}

/*****************************************************************************/
struct digital_output_pin_mode bsp_digital_out_mode_get(digital_output_t output)
{
    struct digital_output_pin_mode dout = {DIGITAL_OUT_DISABLED, DIGITAL_OUT_STATE_INVALID, 0};

    dout.enabled = drv8844_output_enable_get(drv8844, output);

    uint32_t pulse_width_ns = drv8844_pulse_get(drv8844, output);

    if (pulse_width_ns == 0x0) {
        dout.state = DIGITAL_OUT_LOGIC_LOW;
    } else if (pulse_width_ns == 0xFFFFFFFF) {
        dout.state = DIGITAL_OUT_LOGIC_HIGH;
    } else {
        dout.state = DIGITAL_OUT_PWM;
    }

    dout.pulse_width_ns = pulse_width_ns;

    return dout;
}

/*****************************************************************************/
int bsp_digital_out_mode_set(digital_output_t output, struct digital_output_pin_mode pin_mode)
{
    int err = 0;

    if (pin_mode.enabled) {
        err = bsp_digital_out_enable(output);
    } else {
        err = bsp_digital_out_disable(output);
    }

    if (err) {
        return err;
    }

    // The state member of pin_mode takes precedense over the value of pulse_width_ns
    switch (pin_mode.state) {
    case DIGITAL_OUT_LOGIC_LOW: {
        err = bsp_digital_out_reset(output);
        break;
    }
    case DIGITAL_OUT_LOGIC_HIGH: {
        err = bsp_digital_out_set(output);
        break;
    }
    case DIGITAL_OUT_PWM: {
        err = bsp_digital_out_pwm_set(output, pin_mode.pulse_width_ns);
        break;
    }
    default: {
        //__ASSERT(0, "Invalid digital out state");
    }
    }

    return err;
}

/*****************************************************************************/
int bsp_input_button_get(input_button_t button)
{
    static const struct gpio_dt_spec board_buttons[INPUT_BUTTON_MAX] = {
        board_button_0, board_button_1, board_button_2, board_button_3, board_button_4};

    if (button < INPUT_BUTTON_0 || button > INPUT_BUTTON_MAX) {
        return -1;
    }

    return gpio_pin_get_dt(&board_buttons[button]);
}

/*****************************************************************************/
int bsp_input_button_callback_set(on_input_button_changed_cb_t cb)
{
    if (cb) {
        on_input_button_changed_cb = cb;
        return 0;
    }

    return -1;
}

#ifdef CONFIG_BSP_AUTO_INIT
SYS_INIT(bsp_init, APPLICATION, 32);
#endif /* CONFIG_LV_Z_AUTO_INIT */

#else /* CONFIG_VE_SIM */

int bsp_nafe_power_on(void)
{
    //nuffing
}
int  bsp_nafe_power_off(void){
    //nuffing
}
int  bsp_digital_out_disable(digital_output_t output){
    //nuffing
}
int  bsp_digital_out_enable(digital_output_t output){
    //nuffing
}
int  bsp_digital_out_pwm_set(digital_output_t output, uint32_t pulse_width_ns){
    //nuffing
}
int  bsp_digital_out_mode_set(digital_output_t output, struct digital_output_pin_mode pin_mode){
    //nuffing
}
uint8_t  check_button_pressed(void){
    //nuffing
}
void  reset_button_pressed(void){
    //nuffing
}
#endif