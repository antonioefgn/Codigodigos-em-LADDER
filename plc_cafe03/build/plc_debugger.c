/*
 * DEBUGGER code
 * 
 * On "publish", when buffer is free, debugger stores arbitrary variables 
 * content into, and mark this buffer as filled
 * 
 * 
 * Buffer content is read asynchronously, (from non real time part), 
 * and then buffer marked free again.
 *  
 * 
 * */
#ifdef TARGET_DEBUG_AND_RETAIN_DISABLE

void __init_debug    (void){}
void __cleanup_debug (void){}
void __retrieve_debug(void){}
void __publish_debug (void){}

#else

#include "iec_types_all.h"
#include "POUS.h"
/*for memcpy*/
#include <string.h>
#include <stdio.h>

typedef unsigned int dbgvardsc_index_t;
typedef unsigned short trace_buf_offset_t;

#define BUFFER_EMPTY 0
#define BUFFER_FULL 1

#ifndef TARGET_ONLINE_DEBUG_DISABLE

#define TRACE_BUFFER_SIZE 4096
#define TRACE_LIST_SIZE 1024

/* Atomically accessed variable for buffer state */
static long trace_buffer_state = BUFFER_EMPTY;

typedef struct trace_item_s {
    dbgvardsc_index_t dbgvardsc_index;
} trace_item_t;

trace_item_t trace_list[TRACE_LIST_SIZE];
char trace_buffer[TRACE_BUFFER_SIZE];

/* Trace's cursor*/
static trace_item_t *trace_list_collect_cursor = trace_list;
static trace_item_t *trace_list_addvar_cursor = trace_list;
static const trace_item_t *trace_list_end = 
    &trace_list[TRACE_LIST_SIZE-1];
static char *trace_buffer_cursor = trace_buffer;
static const char *trace_buffer_end = trace_buffer + TRACE_BUFFER_SIZE;



#define FORCE_BUFFER_SIZE 1024
#define FORCE_LIST_SIZE 256

typedef struct force_item_s {
    dbgvardsc_index_t dbgvardsc_index;
    void *value_pointer_backup;
} force_item_t;

force_item_t force_list[FORCE_LIST_SIZE];
char force_buffer[FORCE_BUFFER_SIZE];

/* Force's cursor*/
static force_item_t *force_list_apply_cursor = force_list;
static force_item_t *force_list_addvar_cursor = force_list;
static const force_item_t *force_list_end = 
    &force_list[FORCE_LIST_SIZE-1];
static char *force_buffer_cursor = force_buffer;
static const char *force_buffer_end = force_buffer + FORCE_BUFFER_SIZE;


#endif

/***
 * Declare programs 
 **/
extern PROGRAM0 RES0__INSTANCE0;

/***
 * Declare global variables from resources and conf 
 **/
extern       PROGRAM0   RES0__INSTANCE0;

typedef const struct {
    void *ptr;
    __IEC_types_enum type;
} dbgvardsc_t;

static const dbgvardsc_t dbgvardsc[] = {
{&(RES0__INSTANCE0.CANCELAR), BOOL_P_ENUM},
{&(RES0__INSTANCE0.BOTAO_LIGAR), BOOL_P_ENUM},
{&(RES0__INSTANCE0.CAFE_PURO), BOOL_P_ENUM},
{&(RES0__INSTANCE0.CAFE_ACUCAR), BOOL_P_ENUM},
{&(RES0__INSTANCE0.CAFE_LEITE_PURO), BOOL_P_ENUM},
{&(RES0__INSTANCE0.CAFE_LEITE_ACUCAR), BOOL_P_ENUM},
{&(RES0__INSTANCE0.LED_CANCELAR), BOOL_O_ENUM},
{&(RES0__INSTANCE0.LED_LIGAR), BOOL_O_ENUM},
{&(RES0__INSTANCE0.M_START), BOOL_ENUM},
{&(RES0__INSTANCE0.SEL_CAFE_PURO), BOOL_O_ENUM},
{&(RES0__INSTANCE0.SEL_CAFE_ACUCAR), BOOL_O_ENUM},
{&(RES0__INSTANCE0.SEL_CAFE_LEITE_PURO), BOOL_O_ENUM},
{&(RES0__INSTANCE0.SEL_CAFE_LEITE_ACUCAR), BOOL_O_ENUM},
{&(RES0__INSTANCE0.S_NIVEL_AGUA), BOOL_P_ENUM},
{&(RES0__INSTANCE0.S_NIVEL_CAFE), BOOL_P_ENUM},
{&(RES0__INSTANCE0.S_NIVEL_ACUCAR), BOOL_P_ENUM},
{&(RES0__INSTANCE0.S_NIVEL_LEITE), BOOL_P_ENUM},
{&(RES0__INSTANCE0.S_XICARA), BOOL_P_ENUM},
{&(RES0__INSTANCE0.VALVULA_LEITE), BOOL_O_ENUM},
{&(RES0__INSTANCE0.VALVULA_AGUA), BOOL_O_ENUM},
{&(RES0__INSTANCE0.VALVULA_SAIDA), BOOL_O_ENUM},
{&(RES0__INSTANCE0.DOSADOR_CAFE), BOOL_O_ENUM},
{&(RES0__INSTANCE0.DOSADOR_ACUCAR), BOOL_O_ENUM},
{&(RES0__INSTANCE0.INGREDIENTES_OK), BOOL_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.PT), TIME_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.ET), TIME_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.T_INGREDIENTES.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.PT), TIME_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.ET), TIME_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.T_MISTURA.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.PT), TIME_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.ET), TIME_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.T_SAIDA.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.MOTOR_MISTURADOR), BOOL_ENUM},
{&(RES0__INSTANCE0.AQUECEDOR), BOOL_O_ENUM},
{&(RES0__INSTANCE0.BUZZER), BOOL_O_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG8.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG8.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG8.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG8.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG8.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG9.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG9.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG9.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG9.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG9.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG10.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG10.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG10.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG10.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG10.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG11.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG11.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG11.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG11.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG11.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG12.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG12.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG12.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG12.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG12.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG13.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG13.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG13.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG13.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG13.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG14.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG14.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG14.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG14.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG14.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG15.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG15.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG15.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG15.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG15.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG16.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG16.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG16.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG16.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG16.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG17.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG17.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG17.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG17.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG17.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG18.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG18.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG18.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG18.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG18.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG19.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG19.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG19.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG19.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG19.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG20.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG20.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG20.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG20.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG20.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG21.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG21.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG21.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG21.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG21.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG22.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG22.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG22.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG22.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG22.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG23.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG23.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG23.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG23.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG23.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG24.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG24.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG24.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG24.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG24.M), BOOL_ENUM}
};

static const dbgvardsc_index_t retain_list[] = {

};
static unsigned int retain_list_collect_cursor = 0;
static const unsigned int retain_list_size = sizeof(retain_list)/sizeof(dbgvardsc_index_t);

typedef void(*__for_each_variable_do_fp)(dbgvardsc_t*);
void __for_each_variable_do(__for_each_variable_do_fp fp)
{
    unsigned int i;
    for(i = 0; i < sizeof(dbgvardsc)/sizeof(dbgvardsc_t); i++){
        dbgvardsc_t *dsc = &dbgvardsc[i];
        if(dsc->type != UNKNOWN_ENUM) 
            (*fp)(dsc);
    }
}

#define __Unpack_desc_type dbgvardsc_t


#define __Unpack_case_t(TYPENAME)                                           \
        case TYPENAME##_ENUM :                                              \
            if(flags) *flags = ((__IEC_##TYPENAME##_t *)varp)->flags;       \
            if(value_p) *value_p = &((__IEC_##TYPENAME##_t *)varp)->value;  \
		    if(size) *size = sizeof(TYPENAME);                              \
            break;

#define __Unpack_case_p(TYPENAME)                                           \
        case TYPENAME##_O_ENUM :                                            \
        case TYPENAME##_P_ENUM :                                            \
            if(flags) *flags = ((__IEC_##TYPENAME##_p *)varp)->flags;       \
            if(value_p) *value_p = ((__IEC_##TYPENAME##_p *)varp)->value;   \
		    if(size) *size = sizeof(TYPENAME);                              \
            break;

#define __Is_a_string(dsc) (dsc->type == STRING_ENUM)   ||\
                           (dsc->type == STRING_P_ENUM) ||\
                           (dsc->type == STRING_O_ENUM)

static int UnpackVar(__Unpack_desc_type *dsc, void **value_p, char *flags, size_t *size)
{
    void *varp = dsc->ptr;
    /* find data to copy*/
    switch(dsc->type){
        __ANY(__Unpack_case_t)
        __ANY(__Unpack_case_p)
    default:
        return 0; /* should never happen */
    }
    return 1;
}



void Remind(unsigned int offset, unsigned int count, void * p);

extern int CheckRetainBuffer(void);
extern void InitRetain(void);

void __init_debug(void)
{
    /* init local static vars */
#ifndef TARGET_ONLINE_DEBUG_DISABLE
    trace_buffer_cursor = trace_buffer;
    trace_list_addvar_cursor = trace_list;
    trace_list_collect_cursor = trace_list;
    trace_buffer_state = BUFFER_EMPTY;

    force_buffer_cursor = force_buffer;
    force_list_addvar_cursor = force_list;
    force_list_apply_cursor = force_list;
#endif

    InitRetain();
    /* Iterate over all variables to fill debug buffer */
    if(CheckRetainBuffer()){
        unsigned int retain_offset = 0;
        retain_list_collect_cursor = 0;

        /* iterate over retain list */
        while(retain_list_collect_cursor < retain_list_size){
            void *value_p = NULL;
            size_t size;
            char* next_cursor;

            dbgvardsc_t *dsc = &dbgvardsc[
                retain_list[retain_list_collect_cursor]];

            UnpackVar(dsc, &value_p, NULL, &size);

            /* if buffer not full */
            Remind(retain_offset, size, value_p);
            /* increment cursor according size*/
            retain_offset += size;

            retain_list_collect_cursor++;
        }
    }else{
        char mstr[] = "RETAIN memory invalid - defaults used";
        LogMessage(LOG_WARNING, mstr, sizeof(mstr));
    }
}

extern void InitiateDebugTransfer(void);
extern void CleanupRetain(void);

extern unsigned long __tick;

void __cleanup_debug(void)
{
#ifndef TARGET_ONLINE_DEBUG_DISABLE
    trace_buffer_cursor = trace_buffer;
    InitiateDebugTransfer();
#endif    

    CleanupRetain();
}

void __retrieve_debug(void)
{
}

void Retain(unsigned int offset, unsigned int count, void * p);

/* Return size of all retain variables */
unsigned int GetRetainSize(void)
{
    unsigned int retain_size = 0;
    retain_list_collect_cursor = 0;

    /* iterate over retain list */
    while(retain_list_collect_cursor < retain_list_size){
        void *value_p = NULL;
        size_t size;
        char* next_cursor;

        dbgvardsc_t *dsc = &dbgvardsc[
            retain_list[retain_list_collect_cursor]];

        UnpackVar(dsc, &value_p, NULL, &size);

        retain_size += size;
        retain_list_collect_cursor++;
    }

    return retain_size;
}


extern void PLC_GetTime(IEC_TIME*);
extern int TryEnterDebugSection(void);
extern long AtomicCompareExchange(long*, long, long);
extern long long AtomicCompareExchange64(long long* , long long , long long);
extern void LeaveDebugSection(void);
extern void ValidateRetainBuffer(void);
extern void InValidateRetainBuffer(void);

#define __ReForceOutput_case_p(TYPENAME)                                                            \
        case TYPENAME##_P_ENUM :                                                                    \
        case TYPENAME##_O_ENUM :                                                                    \
            {                                                                                       \
                char *next_cursor = force_buffer_cursor + sizeof(TYPENAME);                         \
                if(next_cursor <= force_buffer_end ){                                               \
                    /* outputs real value must be systematically forced */                          \
                    if(vartype == TYPENAME##_O_ENUM)                                                \
                        /* overwrite value pointed by backup */                                     \
                        *((TYPENAME *)force_list_apply_cursor->value_pointer_backup) =  \
                            *((TYPENAME *)force_buffer_cursor);                                     \
                    /* inc force_buffer cursor */                                                   \
                    force_buffer_cursor = next_cursor;                                              \
                }else{                                                                              \
                    stop = 1;                                                                       \
                }                                                                                   \
            }                                                                                       \
            break;
void __publish_debug(void)
{
    InValidateRetainBuffer();
    
#ifndef TARGET_ONLINE_DEBUG_DISABLE 
    /* Check there is no running debugger re-configuration */
    if(TryEnterDebugSection()){
        /* Lock buffer */
        long latest_state = AtomicCompareExchange(
            &trace_buffer_state,
            BUFFER_EMPTY,
            BUFFER_FULL);
            
        /* If buffer was free */
        if(latest_state == BUFFER_EMPTY)
        {
            int stop = 0;
            /* Reset force list cursor */
            force_list_apply_cursor = force_list;

            /* iterate over force list */
            while(!stop && force_list_apply_cursor < force_list_addvar_cursor){
                dbgvardsc_t *dsc = &dbgvardsc[
                    force_list_apply_cursor->dbgvardsc_index];
                void *varp = dsc->ptr;
                __IEC_types_enum vartype = dsc->type;
                switch(vartype){
                    __ANY(__ReForceOutput_case_p)
                default:
                    break;
                }
                force_list_apply_cursor++;
            }

            /* Reset buffer cursor */
            trace_buffer_cursor = trace_buffer;
            /* Reset trace list cursor */
            trace_list_collect_cursor = trace_list;

            /* iterate over trace list */
            while(trace_list_collect_cursor < trace_list_addvar_cursor){
                void *value_p = NULL;
                size_t size;
                char* next_cursor;

                dbgvardsc_t *dsc = &dbgvardsc[
                    trace_list_collect_cursor->dbgvardsc_index];

                UnpackVar(dsc, &value_p, NULL, &size);

                /* copy visible variable to buffer */;
                if(__Is_a_string(dsc)){
                    /* optimization for strings */
                    /* assume NULL terminated strings */
                    size = ((STRING*)value_p)->len + 1;
                }

                /* compute next cursor positon.*/
                next_cursor = trace_buffer_cursor + size;
                /* check for buffer overflow */
                if(next_cursor < trace_buffer_end)
                    /* copy data to the buffer */
                    memcpy(trace_buffer_cursor, value_p, size);
                else
                    /* stop looping in case of overflow */
                    break;
                /* increment cursor according size*/
                trace_buffer_cursor = next_cursor;
                trace_list_collect_cursor++;
            }
            
            /* Leave debug section,
             * Trigger asynchronous transmission 
             * (returns immediately) */
            InitiateDebugTransfer(); /* size */
        }
        LeaveDebugSection();
    }
#endif
    unsigned int retain_offset = 0;
    /* when not debugging, do only retain */
    retain_list_collect_cursor = 0;

    /* iterate over retain list */
    while(retain_list_collect_cursor < retain_list_size){
        void *value_p = NULL;
        size_t size;
        char* next_cursor;

        dbgvardsc_t *dsc = &dbgvardsc[
            retain_list[retain_list_collect_cursor]];

        UnpackVar(dsc, &value_p, NULL, &size);

        /* if buffer not full */
        Retain(retain_offset, size, value_p);
        /* increment cursor according size*/
        retain_offset += size;

        retain_list_collect_cursor++;
    }
    ValidateRetainBuffer();
}

#ifndef TARGET_ONLINE_DEBUG_DISABLE

#define TRACE_LIST_OVERFLOW    1
#define FORCE_LIST_OVERFLOW    2
#define FORCE_BUFFER_OVERFLOW  3

#define __ForceVariable_case_t(TYPENAME)                                                \
        case TYPENAME##_ENUM :                                                          \
            /* add to force_list*/                                                      \
            force_list_addvar_cursor->dbgvardsc_index = idx;                            \
            ((__IEC_##TYPENAME##_t *)varp)->flags |= __IEC_FORCE_FLAG;                  \
            ((__IEC_##TYPENAME##_t *)varp)->value = *((TYPENAME *)force);               \
            break;
#define __ForceVariable_case_p(TYPENAME)                                                \
        case TYPENAME##_P_ENUM :                                                        \
        case TYPENAME##_O_ENUM :                                                        \
            {                                                                           \
                char *next_cursor = force_buffer_cursor + sizeof(TYPENAME);             \
                if(next_cursor <= force_buffer_end ){                                   \
                    /* add to force_list*/                                              \
                    force_list_addvar_cursor->dbgvardsc_index = idx;                    \
                    /* save pointer to backup */                                        \
                    force_list_addvar_cursor->value_pointer_backup =                    \
                        ((__IEC_##TYPENAME##_p *)varp)->value;                          \
                    /* store forced value in force_buffer */                            \
                    *((TYPENAME *)force_buffer_cursor) = *((TYPENAME *)force);          \
                    /* replace pointer with pointer to force_buffer */                  \
                    ((__IEC_##TYPENAME##_p *)varp)->value =                             \
                        (TYPENAME *)force_buffer_cursor;                                \
                    (((__IEC_##TYPENAME##_p *)varp)->fvalue) = *((TYPENAME *)force);    \
                    /* mark variable as forced */                                       \
                    ((__IEC_##TYPENAME##_p *)varp)->flags |= __IEC_FORCE_FLAG;          \
                    /* inc force_buffer cursor */                                       \
                    force_buffer_cursor = next_cursor;                                  \
                    /* outputs real value must be systematically forced */              \
                    if(vartype == TYPENAME##_O_ENUM)                                    \
                        *(((__IEC_##TYPENAME##_p *)varp)->value) = *((TYPENAME *)force);\
                } else {                                                                \
                    error_code = FORCE_BUFFER_OVERFLOW;                                 \
                    goto error_cleanup;                                                 \
                }                                                                       \
            }                                                                           \
            break;


void ResetDebugVariables(void);

int RegisterDebugVariable(dbgvardsc_index_t idx, void* force)
{
    int error_code = 0;
    if(idx < sizeof(dbgvardsc)/sizeof(dbgvardsc_t)){
        /* add to trace_list, inc trace_list_addvar_cursor*/
        if(trace_list_addvar_cursor <= trace_list_end){
            trace_list_addvar_cursor->dbgvardsc_index = idx;
            trace_list_addvar_cursor++;
        } else {
            error_code = TRACE_LIST_OVERFLOW;
            goto error_cleanup;
        }
        if(force){
            if(force_list_addvar_cursor <= force_list_end){
                dbgvardsc_t *dsc = &dbgvardsc[idx];
                void *varp = dsc->ptr;
                __IEC_types_enum vartype = dsc->type;

                switch(vartype){
                    __ANY(__ForceVariable_case_t)
                    __ANY(__ForceVariable_case_p)
                default:
                    break;
                }
                /* inc force_list cursor */
                force_list_addvar_cursor++;
            } else {
                error_code = FORCE_LIST_OVERFLOW;
                goto error_cleanup;
            }
        }
    }
    return 0;

error_cleanup:
    ResetDebugVariables();
    trace_buffer_state = BUFFER_EMPTY;
    return error_code;
    
}

#define ResetForcedVariable_case_t(TYPENAME)                                            \
        case TYPENAME##_ENUM :                                                          \
            ((__IEC_##TYPENAME##_t *)varp)->flags &= ~__IEC_FORCE_FLAG;                 \
            /* for local variable we don't restore original value */                    \
            /* that can be added if needed, but it was like that since ever */          \
            break;

#define ResetForcedVariable_case_p(TYPENAME)                                            \
        case TYPENAME##_P_ENUM :                                                        \
        case TYPENAME##_O_ENUM :                                                        \
            ((__IEC_##TYPENAME##_p *)varp)->flags &= ~__IEC_FORCE_FLAG;                 \
            /* restore backup to pointer */                                             \
            ((__IEC_##TYPENAME##_p *)varp)->value =                                     \
                force_list_apply_cursor->value_pointer_backup;                          \
            break;

void ResetDebugVariables(void)
{
    /* Reset trace list */
    trace_list_addvar_cursor = trace_list;

    force_list_apply_cursor = force_list;
    /* Restore forced variables */
    while(force_list_apply_cursor < force_list_addvar_cursor){
        dbgvardsc_t *dsc = &dbgvardsc[
            force_list_apply_cursor->dbgvardsc_index];
        void *varp = dsc->ptr;
        switch(dsc->type){
            __ANY(ResetForcedVariable_case_t)
            __ANY(ResetForcedVariable_case_p)
        default:
            break;
        }
        /* inc force_list cursor */
        force_list_apply_cursor++;
    } /* else TODO: warn user about failure to force */ 

    /* Reset force list */
    force_list_addvar_cursor = force_list;
    /* Reset force buffer */
    force_buffer_cursor = force_buffer;
}

void FreeDebugData(void)
{
    /* atomically mark buffer as free */
    AtomicCompareExchange(
        &trace_buffer_state,
        BUFFER_FULL,
        BUFFER_EMPTY);
}
int WaitDebugData(unsigned long *tick);
/* Wait until debug data ready and return pointer to it */
int GetDebugData(unsigned long *tick, unsigned long *size, void **buffer){
    int wait_error = WaitDebugData(tick);
    if(!wait_error){
        *size = trace_buffer_cursor - trace_buffer;
        *buffer = trace_buffer;
    }
    return wait_error;
}
#endif
#endif

