#ifndef BSP_H_
#define BSP_H_

#include <stdbool.h>
#include <stdint.h>

#include "app/drivers/drv8844.h"

#define BOARD_DIGITAL_INPUTS_COUNT 4
#define BOARD_DIGITAL_OUTPUTS_COUNT 4

typedef enum {
    DIGITAL_IN_1,
    DIGITAL_IN_2,
    DIGITAL_IN_3,
    DIGITAL_IN_4,
    DIGITAL_IN_MAX
} digital_input_t;

typedef enum {
    DIGITAL_IN_STATE_INVALID = 0,
    DIGITAL_IN_LOGIC_LOW,
    DIGITAL_IN_LOGIC_HIGH,
    DIGITAL_IN_UNDEFINED,
    DIGITAL_IN_STATE_MAX
} digital_input_state_t;

struct digital_inputs {
    digital_input_state_t digital_in_1;
    digital_input_state_t digital_in_2;
    digital_input_state_t digital_in_3;
    digital_input_state_t digital_in_4;
    int err;
};

typedef enum {
    DIGITAL_OUT_1 = OUT1,
    DIGITAL_OUT_2 = OUT2,
    DIGITAL_OUT_3 = OUT3,
    DIGITAL_OUT_4 = OUT4,
    DIGITAL_OUT_MAX
} digital_output_t;

typedef enum {
    DIGITAL_OUT_DISABLED,
    DIGITAL_OUT_ENABLED,
} digital_output_en_t;

typedef enum {
    DIGITAL_OUT_STATE_INVALID,
    DIGITAL_OUT_LOGIC_LOW,
    DIGITAL_OUT_LOGIC_HIGH,
    DIGITAL_OUT_PWM,
    DIGITAL_OUT_STATE_MAX
} digital_output_state_t;

struct digital_output_pin_mode {
    digital_output_en_t enabled;
    digital_output_state_t state;
    uint32_t pulse_width_ns;
};

typedef enum {
    INPUT_BUTTON_0,
    INPUT_BUTTON_1,
    INPUT_BUTTON_2,
    INPUT_BUTTON_3,
    INPUT_BUTTON_4,
    INPUT_BUTTON_MAX
} input_button_t;

/*****************************************************************************/

/// @brief Initializes the BSP. Must be called before using any other periperal-
/// related functions in main
/// @param
int bsp_init(void);

/// @brief Turns on red board LED
/// @param
/// @return 0 on success
int bsp_red_led_on(void);

/// @brief Turns off red board LED
/// @param
/// @return 0 on success
int bsp_red_led_off(void);

/// @brief Turns on green board LED
/// @param
/// @return 0 on success
int bsp_green_led_on(void);

/// @brief Turns off green board LED
/// @param
/// @return 0 on success
int bsp_green_led_off(void);

/// @brief Toggles green board LED
/// @param
/// @return 0 on success
int bsp_green_led_toggle(void);

/// @brief Toggles red board LED
/// @param
/// @return 0 on success
int bsp_red_led_toggle(void);

/// @brief Enables/disables digital inputs ISR
/// @param din
/// @param enable
/// @return 0 on success
int bsp_digital_input_isr_enable(digital_input_t din, bool enable);

/// @brief Enables NAFE power (3.3V and +/- 15V)
/// @param
/// @return 0 on success
int bsp_nafe_power_on(void);

/// @brief Disables NAFE power
/// @param
/// @return 0 on success
int bsp_nafe_power_off(void);

/// @brief Returns a struct digital_inputs with the state of the digital inputs
/// The digital_inputs.err member is set to 0 on success
struct digital_inputs bsp_digital_inputs_get(void);

/// @brief Returns the state of a single digital input
/// @param din
/// @return
digital_input_state_t bsp_digital_input_get(digital_input_t input);

/// @brief Enables a digital output (asserts the Enable DRV8844 line)
/// @param output Digital output to enable
/// @return 0 on success
int bsp_digital_out_enable(digital_output_t output);

/// @brief Disables a digital output (deasserts the Enable DRV8844 line)
/// @param output Digital output to disable
/// @return 0 on success
int bsp_digital_out_disable(digital_output_t output);

/// @brief Sets a digital output to logic 1
/// @param output
/// @return 0 on success
int bsp_digital_out_set(digital_output_t output);

/// @brief Resets a digital output to logic 0
/// @param output
/// @return 0 on success
int bsp_digital_out_reset(digital_output_t output);

/// @brief Starts PWM on a digital output with the specified pulse width.
/// If the pulse width is greater than the PWM peripheral period (as specified in DT),
/// the output will be set to logic 1.
/// @param output
/// @param pulse_width_ns Zephyr's PWM_USEC(x) and PWM_NSEC(x) can be used
/// @return 0 on success
int bsp_digital_out_pwm_set(digital_output_t output, uint32_t pulse_width_ns);

/// @brief Queries the state of an output pin
/// @param output
/// @return a struct with the state of an output pin
struct digital_output_pin_mode bsp_digital_out_mode_get(digital_output_t output);

/// @brief Sets a digital output mode (enable and PWM pulse width). The function
/// provides convenient way to enable/disable and set pulse width with one call.
/// @param output
/// @param pin_mode struct digital_output_pin containing the desired output settings
/// @return 0 on success
int bsp_digital_out_mode_set(digital_output_t output, struct digital_output_pin_mode pin_mode);

/// @brief Returns the state of an input button
/// @param button
/// @return 0 or 1, -1 on error
int bsp_input_button_get(input_button_t button);

/// @brief Button changed callback definition
typedef int (*on_input_button_changed_cb_t)(input_button_t button, int state);

/// @brief Sets a callback invoked when input button change interrupt appears.
/// @param cb
/// @return 0 on success
int bsp_input_button_callback_set(on_input_button_changed_cb_t cb);


void set_button_pressed(uint8_t index);

#endif // BSP_H_