

#include  <stdint.h> 
#include  <stdbool.h> 
#include  "ble.h" 
#include  "ble_srv_common.h"

#define cus_BASE_UUID            {{0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x00, 0x00, 0x40, 0x6E}} /**< Used vendor specific UUID. */



#define BLE_UUID_CUS_SERVICE 0x0002 /**< The UUID of the Nordic UART Service. */
#define CUSTOM_TEMP_UUID            0x0006
#define CUSTOM_PRES_UUID            0x0007
#define CUSTOM_HEIGHT_UUID            0x0008 
#define CUSTOM_HEIGHT_Rel_UUID         0x0009 
#define CUSTOM_ACCEL_X_UUID            0x000A 
#define CUSTOM_ACCEL_Y_UUID            0x000B  
#define CUSTOM_ACCEL_Z_UUID            0x000C  
#define CUSTOM_GYRO_X_UUID            0x000D 
#define CUSTOM_GYRO_Y_UUID            0x000E  
#define CUSTOM_GYRO_Z_UUID            0x000F  

typedef struct ble_cus_s ble_cus_t;


#define BLE_CUS_DEF(_name)                                                                          \
static ble_cus_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                     \
                     ble_cus_on_ble_evt, &_name) 


typedef struct
{   
                       /**< Event handler to be called for handling events in the Custom Service. */
    uint8_t                       initial_custom_value;           /**< Initial custom value */
    ble_srv_cccd_security_mode_t  custom_value_char_attr_md;     /**< Initial security level for Custom characteristics attribute */
} ble_cus_init_t;

struct ble_cus_s
{
                      /**< Event handler to be called for handling events in the Custom Service. */
    uint16_t                      service_handle;                 /**< Handle of Custom Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t      pres_custom_value_handles; 
    ble_gatts_char_handles_t      temp_custom_value_handles;
    ble_gatts_char_handles_t      height_custom_value_handles;
    ble_gatts_char_handles_t      height_rel_custom_value_handles;
    ble_gatts_char_handles_t      accel_x_custom_value_handles;
    ble_gatts_char_handles_t      accel_y_custom_value_handles;
    ble_gatts_char_handles_t      accel_z_custom_value_handles;
    ble_gatts_char_handles_t      gyro_x_custom_value_handles;
    ble_gatts_char_handles_t      gyro_y_custom_value_handles;
    ble_gatts_char_handles_t      gyro_z_custom_value_handles;/**< Handles related to the Custom Value characteristic. */
    uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                       uuid_type; 
};

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context);

/**@brief Custom Service event handler type. */


/**@brief Function for initializing the Custom Service.
 *
 * @param[out]  p_cus       Custom Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_cus_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);

