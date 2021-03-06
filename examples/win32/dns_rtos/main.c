/**
 * \file            main.c
 * \brief           Main file
 */

/*
 * Copyright (c) 2018 Tilen Majerle
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of ESP-AT.
 *
 * Before you start using WIN32 implementation with USB and VCP,
 * check esp_ll_win32.c implementation and choose your COM port!
 */
#include "stdafx.h"
#include "esp/esp.h"
#include "station_manager.h"

static espr_t esp_callback_func(esp_cb_t* cb);

/**
 * \brief           Program entry point
 */
int
main(void) {
    esp_ip_t ip;
    printf("Starting ESP application!\r\n");

    /*
     * Initialize ESP with default callback function
     */
    esp_init(esp_callback_func, 1);

    /*
     * Connect to access point.
     *
     * Try unlimited time until access point accepts up.
     * Check for station_manager.c to define preferred access points ESP should connect to
     */
    connect_to_preferred_access_point(1);

    /*
     * Use DNS protocol to get IP address of domain name
     */
    if (esp_dns_getbyhostname("example.com", &ip, 1) == espOK) {
        printf("DNS record for example.com: %d.%d.%d.%d\r\n",
            (int)ip.ip[0], (int)ip.ip[1], (int)ip.ip[2], (int)ip.ip[3]);
    } else {
        printf("Error on DNS resolver\r\n");
    }

    return 0;
}

/**
 * \brief           Event callback function for ESP stack
 * \param[in]       cb: Event information with data
 * \return          espOK on success, member of \ref espr_t otherwise
 */
static espr_t
esp_callback_func(esp_cb_t* cb) {
    switch (cb->type) {
        case ESP_CB_INIT_FINISH: {
            printf("Device initialized!\r\n");
            break;
        }
        case ESP_CB_RESET: {
            printf("Device reset!\r\n");
            break;
        }
        default: break;
    }
    return espOK;
}
