/*!  \file     logic_user.c
*    \brief    General logic for user operations
*    Created:  16/02/2019
*    Author:   Mathieu Stephan
*/
#include <string.h>
#include "smartcard_highlevel.h"
#include "logic_user.h"
#include "custom_fs.h"
#include "nodemgmt.h"
#include "defines.h"
#include "rng.h"
// Next CTR value for our AES encryption
uint8_t logic_user_next_ctr_val[MEMBER_SIZE(nodemgmt_profile_main_data_t,current_ctr)];


/*! \fn     logic_user_init_context(uint8_t user_id)
*   \brief  Initialize our user context
*   \param  user_id The user ID
*/
void logic_user_init_context(uint8_t user_id)
{
    nodemgmt_init_context(user_id);
    nodemgmt_read_profile_ctr((void*)logic_user_next_ctr_val);
}

/*! \fn     logic_user_create_new_user(volatile uint16_t* pin_code, BOOL use_provisioned_key, volatile uint8_t* aes_key)
*   \brief  Add a new user with a new smart card
*   \param  pin_code            The new pin code
*   \param  use_provisioned_key BOOL to specify use of provisioned key
*   \param  aes_key             In case of provisioned key, the aes key
*   \return success or not
*/
ret_type_te logic_user_create_new_user(volatile uint16_t* pin_code, BOOL use_provisioned_key, uint8_t* aes_key)
{    
    // When inserting a new user and a new card, we need to setup the following elements
    // - AES encryption key, stored in the smartcard
    // - AES next available CTR, stored in the user profile
    // - AES nonce, stored in the MCU flash along with the user ID
    // - Smartcard CPZ, randomly generated and stored in our MCU flash along with user id & nonce
    uint8_t temp_buffer[AES_KEY_LENGTH/8];
    uint8_t new_user_id;
    
    /* Check if there actually is an available slot */
    if (custom_fs_get_nb_free_cpz_lut_entries(&new_user_id) == 0)
    {
        return RETURN_NOK;
    }
    
    /* Setup user profile in MCU Flash */
    cpz_lut_entry_t user_profile;
    user_profile.user_id = new_user_id;
    
    /* Use provisioned key? */
    if (use_provisioned_key != FALSE)
    {
        user_profile.use_provisioned_key_flag = CUSTOM_FS_PROV_KEY_FLAG;
        // TODO: change below to write encrypted key
        memcpy(user_profile.provisioned_key, aes_key, sizeof(user_profile.provisioned_key));
    }
    else
    {
        user_profile.use_provisioned_key_flag = 0;
        rng_fill_array(user_profile.provisioned_key, sizeof(user_profile.provisioned_key));
    }
    
    /* Nonce & Cards CPZ: random numbers */
    rng_fill_array(user_profile.cards_cpz, sizeof(user_profile.cards_cpz));
    rng_fill_array(user_profile.nonce, sizeof(user_profile.nonce));
    
    /* Reserved field: set to 0 */
    memset(user_profile.reserved, 0, sizeof(user_profile.reserved));
    
    /* Setup user profile in external flash */
    nodemgmt_format_user_profile(new_user_id);
    
    /* Initialize nodemgmt context */
    logic_user_init_context(new_user_id);
    
    /* Write card CPZ */
    smartcard_highlevel_write_protected_zone(user_profile.cards_cpz);
    
    /* Write card random AES key */
    rng_fill_array(temp_buffer, sizeof(temp_buffer));
    if (smartcard_highlevel_write_aes_key(temp_buffer) != RETURN_OK)
    {
        return RETURN_NOK;
    }
    memset(temp_buffer, 0, sizeof(temp_buffer));
    
    // TODO: Initialize encryption handling
    //initEncryptionHandling(temp_buffer, temp_nonce);
    
    // Write new pin code
    smartcard_highlevel_write_security_code(pin_code);
    
    return custom_fs_store_cpz_entry(&user_profile, new_user_id);
}