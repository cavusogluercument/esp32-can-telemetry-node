#pragma once
#include <stdint.h>
#include "esp_err.h"
typedef struct { uint32_t tx_ok, tx_fail, rx_ok, bus_error, bus_off, recovery; } can_diag_t;
esp_err_t can_bus_init(void);
esp_err_t can_bus_send(uint32_t id, const uint8_t *data, uint8_t len);
void can_bus_get_diag(can_diag_t *out);
void can_rx_task(void *arg);
void can_alert_task(void *arg);
