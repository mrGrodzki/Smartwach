

#include "sdk_common.h"
#include "ble_srv_common.h"
#include "ble_cus.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "math.h"
  extern uint8_t steep;

extern int32_t temperature, pressure;

/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
    p_cus->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;
}

static void on_write(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    
    // Check if the handle passed with the event matches the Custom Value Characteristic handle.
    if (p_evt_write->handle == p_cus->height_rel_custom_value_handles.value_handle)
    {
        NRF_LOG_INFO("LED %d",p_evt_write->data ); 
    }  // Put specific task here. 
}

void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_cus_t * p_cus = (ble_cus_t *) p_context;
    
    if (p_cus == NULL || p_ble_evt == NULL)
    {
        return;
    }
    
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
         on_connect(p_cus, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
        on_disconnect(p_cus, p_ble_evt);
            break;
        case BLE_GATTS_EVT_WRITE:
         on_write(p_cus, p_ble_evt);
           break;
        default:
            // No implementation needed.
            break;
    }
}

/**@brief Function for handling the Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.

 */



/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */


/**@brief Function for adding the Custom Value characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
 /*
static uint32_t custom_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

 memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 0; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL; 
    char_md.p_sccd_md         = NULL;
		
    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_cus_init->custom_value_char_attr_md.read_perm;
    attr_md.write_perm = p_cus_init->custom_value_char_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CUSTOM_VALUE_CHAR_UUID;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(uint8_t);

    err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_cus->custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;

}

*/
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)

{

 if (p_cus == NULL || p_cus_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_code_t            err_code;
    ble_uuid_t            ble_uuid;
    ble_uuid128_t         base_uuid = cus_BASE_UUID;
    ble_add_char_params_t add_char_params;
  
    // Initialize service structure
    p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;

     /**@snippet [Adding proprietary Service to the SoftDevice] */
    // Add a custom base UUID.
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_cus->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = BLE_UUID_CUS_SERVICE;

     // Add the service.
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_cus->service_handle);
    /**@snippet [Adding proprietary Service to the SoftDevice] */
    VERIFY_SUCCESS(err_code);
      // Add Custom Value characteristic
  memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_TEMP_UUID;
    add_char_params.max_len           = 2;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->temp_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_PRES_UUID;
    add_char_params.max_len           = 3;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->pres_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

     memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_HEIGHT_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->height_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

        memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_ACCEL_X_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->accel_x_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

        memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_ACCEL_Y_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->accel_y_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

        memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_ACCEL_Z_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->accel_z_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
 


    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_HEIGHT_Rel_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;
    
    add_char_params.char_props.write         = 1;
    add_char_params.char_props.write_wo_resp = 1;

    add_char_params.read_access  = SEC_OPEN;
    add_char_params.write_access = SEC_OPEN;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->height_rel_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    ///////
    
     memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_GYRO_X_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->gyro_z_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    ///////
    
      memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_GYRO_Y_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->gyro_z_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    /////////

     memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid_type         = p_cus->uuid_type;
    add_char_params.uuid              = CUSTOM_GYRO_Z_UUID;
    add_char_params.max_len           = 4;
    add_char_params.is_var_len        = false;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = 1;

    err_code = characteristic_add(p_cus->service_handle, &add_char_params, &p_cus->gyro_z_custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

}

uint32_t ble_cscs_measurement_send(ble_cus_t * p_cus)
{
    uint16_t               len;
    uint16_t               hvx_len;
    uint16_t temp   = 0;
    uint8_t pres_buffer[3]   = {'0'};
    uint8_t temp_buffer[3] ={'0'};
    uint8_t data_axis[24]= {0};
    
   MPU9050_read(&data_axis);
    
    
    if(bme280_read_adc(&temperature, &pressure)==false);
    temp=temperature;
    uint16_encode(temp, &temp_buffer[0]);
     ble_gatts_hvx_params_t hvx_params;

//p_encoded_buffer[0] =0x22;
//p_encoded_buffer[1]=0x0a;
   
    uint24_encode(pressure, &pres_buffer[0]);

  uint8_t height_mass[4]={'0'};
  float H= 70000;
  float r =temp/100;
  //float u=log(10);
  float   height =  (-log(pressure/ H))*(((temp/100)+273)/0.0341593);
  float lsb=0;
  float msb=0;
  uint8_t sign_height=0; // 0 = +  1 = -
  lsb=modff(height, &msb);
  if(height<0) 
  {
    lsb=fabs(lsb);
    msb=fabs(msb);
    sign_height=1;
  }
  else sign_height=0;
  
  uint8_t ui_lsb= (uint8_t) (lsb*100);
  uint16_t ui_msb= (uint16_t) msb;

  height_mass[0]=ui_lsb;
  uint16_encode(ui_msb, &height_mass[1]);
  height_mass[3]=sign_height;




    
    if (p_cus == NULL )
    {
        return NRF_ERROR_NULL;
    }

    uint32_t err_code;

    // Send value if connected and notifying
    if (p_cus->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
       uint8_t   mass[]= {4, 5, 6}; 
       
        
   /////////////////////   
        

        len     = 2;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> temp_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = temp_buffer;

        err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }
///////////////////////////////////////
         len     = 3;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> pres_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = pres_buffer;

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }
/////////////////////////////
        len     = 4;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> height_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = height_mass;

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }
/////////////////////

   len     = 4;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> accel_x_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = data_axis;

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

/////////////////////

   len     = 4;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> accel_y_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = &data_axis[4];

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }


    /////////////////////

   len     = 4;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> accel_z_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = &data_axis[8];

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

     /////////////////////

   len     = 4;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> gyro_x_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = &data_axis[12];

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

     /////////////////////

   len     = 4;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> gyro_y_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = &data_axis[16];

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }


     /////////////////////

   len     = 1;
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_cus-> gyro_z_custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = steep ; //&data_axis[20];

       err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }


    return err_code;
}
