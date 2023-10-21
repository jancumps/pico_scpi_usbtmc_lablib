#ifndef SCPI_SCPI_BASE_H
#define SCPI_SCPI_BASE_H

#include "scpi/scpi.h"

#define SCPI_INPUT_BUFFER_LENGTH 256
#define SCPI_ERROR_QUEUE_SIZE 17

#define SCPI_BASE_COMMANDS \
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */ \
    { .pattern = "*CLS", .callback = SCPI_CoreCls,}, \
    { .pattern = "*ESE", .callback = SCPI_CoreEse,}, \
    { .pattern = "*ESE?", .callback = SCPI_CoreEseQ,}, \
    { .pattern = "*ESR?", .callback = SCPI_CoreEsrQ,}, \
    { .pattern = "*IDN?", .callback = SCPI_CoreIdnQ,}, \
    { .pattern = "*OPC", .callback = SCPI_CoreOpc,}, \
    { .pattern = "*OPC?", .callback = SCPI_CoreOpcQ,}, \
    { .pattern = "*RST", .callback = SCPI_CoreRst,}, \
    { .pattern = "*SRE", .callback = SCPI_CoreSre,}, \
    { .pattern = "*SRE?", .callback = SCPI_CoreSreQ,}, \
    { .pattern = "*STB?", .callback = SCPI_CoreStbQ,}, \
    { .pattern = "*TST?", .callback = My_CoreTstQ,}, \
    { .pattern = "*WAI", .callback = SCPI_CoreWai,}, \
 \
    /* Required SCPI commands (SCPI std V1999.0 4.2.1) */ \
    {.pattern = "SYSTem:ERRor[:NEXT]?", .callback = SCPI_SystemErrorNextQ,}, \
    {.pattern = "SYSTem:ERRor:COUNt?", .callback = SCPI_SystemErrorCountQ,}, \
    {.pattern = "SYSTem:VERSion?", .callback = SCPI_SystemVersionQ,}, \
 \
 \
    {.pattern = "STATus:OPERation:EVENt?", .callback = SCPI_StatusOperationEventQ,}, \
    {.pattern = "STATus:OPERation:CONDition?", .callback = SCPI_StatusOperationConditionQ,}, \
    {.pattern = "STATus:OPERation:ENABle", .callback = SCPI_StatusOperationEnable,}, \
    {.pattern = "STATus:OPERation:ENABle?", .callback = SCPI_StatusOperationEnableQ,}, \
 \
    {.pattern = "STATus:QUEStionable[:EVENt]?", .callback = SCPI_StatusQuestionableEventQ,}, \
    {.pattern = "STATus:QUEStionable:CONDition?", .callback = SCPI_StatusQuestionableConditionQ,}, \
    {.pattern = "STATus:QUEStionable:ENABle", .callback = SCPI_StatusQuestionableEnable,}, \
    {.pattern = "STATus:QUEStionable:ENABle?", .callback = SCPI_StatusQuestionableEnableQ,}, \
 \
    {.pattern = "STATus:PRESet", .callback = SCPI_StatusPreset,}, \
    /* VISA commands */  \
    /* support VISA ASSERT TRIGGER */  \
    /* https://www.ni.com/docs/en-US/bundle/labview-api-ref/page/functions/visa-assert-trigger.html */  \
    { .pattern = "*TRG", .callback = SCPI_VisaTrg,},


scpi_result_t My_CoreTstQ(scpi_t * context);
scpi_result_t SCPI_VisaTrg(scpi_t * context);

void doTrigger();

scpi_bool_t scpi_instrument_input(const char * data, int len);

scpi_t * getScpiContext();

extern scpi_interface_t scpi_interface;
extern char scpi_input_buffer[];
extern scpi_error_t scpi_error_queue_data[];
extern scpi_t scpi_context;

void scpi_instrument_init();
size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);

// helper functions to simplyfy integration of TinyUSB tmcusb and the scpi-lib
uint8_t getSTB();
void setSTB(uint8_t);

scpi_result_t SCPI_WriteReg(scpi_t * context, scpi_reg_name_t name);
scpi_result_t SCPI_ReadReg(scpi_t * context, scpi_reg_name_t name);

#endif // SCPI_SCPI_BASE_H