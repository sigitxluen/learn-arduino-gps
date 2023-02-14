#include "gps.h"

gps::gps (/* args */) {}

void gps::gps_init (void) {
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        // .source_clk = 4,
    };
    // We won't use a buffer for sending data.
    uart_driver_install (UART_NUM_2, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config (UART_NUM_2, &uart_config);
    uart_set_pin (UART_NUM_2, 16, 17, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void gps::gps_get_raw () {
    // uint8_t* data = (uint8_t*)malloc (RX_BUF_SIZE + 1);
    // const int rxBytes =
    // uart_read_bytes (UART_NUM_2, data, RX_BUF_SIZE, 1000 /
    // portTICK_PERIOD_MS); if (rxBytes > 0) {
    //     data[rxBytes] = 0;
    //     ESP_LOGI (RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
    //     free (data);
    // }
}
