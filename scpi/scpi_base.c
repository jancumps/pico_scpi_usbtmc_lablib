#include "scpi/scpi_base.h"

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

scpi_bool_t scpi_instrument_input(const char * data, int len) {
    return SCPI_Input(&scpi_context, data, len);
}