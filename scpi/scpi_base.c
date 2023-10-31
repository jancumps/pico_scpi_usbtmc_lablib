#include "scpi/scpi_base.h"

#include "scpi-def.h"
#include "usb/usbtmc_app.h"
#include "pico/unique_id.h"

/**
 * Reimplement IEEE488.2 *TST?
 *
 * Result should be 0 if everything is ok
 * Result should be 1 if something goes wrong
 *
 * Return SCPI_RES_OK
 */
scpi_result_t My_CoreTstQ(scpi_t * context) {

    SCPI_ResultInt32(context, 0);

    return SCPI_RES_OK;
}

void triggerHandler() {
    // this function is the handler for SCPI and usbtmc trigger requests.
    // current firmware ignores triggers
    // if there is a use for it, move this to the dedicated module
    return;
}

/**
 * *TRG - This command asserts trigger. 
 *        https://www.ni.com/docs/en-US/bundle/labview-api-ref/page/functions/visa-assert-trigger.html
 *        throw SCPI error, because not implemented
 * @param context
 * @return 
 */
scpi_result_t SCPI_VisaTrg(scpi_t * context) {
    triggerHandler();
    SCPI_ErrorPush(context, SCPI_ERROR_UNDEFINED_HEADER); // TODO: remove when trigger implemented
    return SCPI_RES_ERR; // TODO: return OK when trigger implemented
}
void doTrigger() {
    triggerHandler();
}


scpi_t scpi_context;

scpi_bool_t scpi_instrument_input(const char * data, int len) {
    return SCPI_Input(&scpi_context, data, len);
}

scpi_interface_t scpi_interface = {
    .error = NULL,            // haven't implemented an error logger
    .write = SCPI_Write,
    .control = SCPI_Control,
    .flush = NULL,            // don't need flush for SCI / USB
    .reset = SCPI_Reset,
};

char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];


// init helper for this instrument
void scpi_instrument_init() {
    // buffer to hold flash ID
    static char serial[2 * PICO_UNIQUE_BOARD_ID_SIZE_BYTES + 1];
    static bool unique_initialised = false;
    if (! unique_initialised) {
        pico_get_unique_board_id_string(serial, sizeof(serial));
        unique_initialised = true;
    }

    initInstrument(); // if you prefer no dependency on the gpio_utils in main,
              // you could move this call into the scpi_instrument_init() body.
              // like I did here

    
     SCPI_Init(&scpi_context,
             scpi_commands,
             &scpi_interface,
             scpi_units_def,
             SCPI_IDN1, SCPI_IDN2, serial, SCPI_IDN4,
             scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
             scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

}



/*
 * The SCPI lib calls this function to write data back over the SCI2 interface
 * visual clue: dim user LED B after delivering the reply
 */
size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
    (void) context;

  setReply(data, len);

    return len;
}

scpi_result_t SCPI_Reset(scpi_t * context) {
    (void) context;
    initInstrument();
    return SCPI_RES_OK;   
}

scpi_result_t SCPI_Control(scpi_t* context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val)
{
    (void)context;
    (void) val;

    if (SCPI_CTRL_SRQ == ctrl) {
        setControlReply();
    }
    return SCPI_RES_OK;
}

uint8_t getSTB() {
    return (uint8_t) SCPI_RegGet(&scpi_context, SCPI_REG_STB);
}

void setSTB(uint8_t stb) {
    SCPI_RegSet(&scpi_context, SCPI_REG_STB, (scpi_reg_val_t) stb);    
}

scpi_t * getScpiContext() {
    return &scpi_context;
}

scpi_result_t SCPI_WriteReg(scpi_t * context, scpi_reg_name_t name) {
    int32_t new_OPERE;
    if (SCPI_ParamInt32(context, &new_OPERE, TRUE)) {
        SCPI_RegSet(context, name, (scpi_reg_val_t) new_OPERE);
    }
    return SCPI_RES_OK;
}

scpi_result_t SCPI_ReadReg(scpi_t * context, scpi_reg_name_t name) {
    /* return value */
    SCPI_ResultInt32(context, SCPI_RegGet(context, name));

    /* clear register */
    SCPI_RegSet(context, name, 0);

    return SCPI_RES_OK;
}
