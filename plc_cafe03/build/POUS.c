void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX1_0,data__->CANCELAR,retain)
  __INIT_LOCATED_VALUE(data__->CANCELAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX1_1,data__->BOTAO_LIGAR,retain)
  __INIT_LOCATED_VALUE(data__->BOTAO_LIGAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX1_2,data__->CAFE_PURO,retain)
  __INIT_LOCATED_VALUE(data__->CAFE_PURO,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX1_3,data__->CAFE_ACUCAR,retain)
  __INIT_LOCATED_VALUE(data__->CAFE_ACUCAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX1_4,data__->CAFE_LEITE_PURO,retain)
  __INIT_LOCATED_VALUE(data__->CAFE_LEITE_PURO,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX1_5,data__->CAFE_LEITE_ACUCAR,retain)
  __INIT_LOCATED_VALUE(data__->CAFE_LEITE_ACUCAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX1_0,data__->LED_CANCELAR,retain)
  __INIT_LOCATED_VALUE(data__->LED_CANCELAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX1_1,data__->LED_LIGAR,retain)
  __INIT_LOCATED_VALUE(data__->LED_LIGAR,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->M_START,__BOOL_LITERAL(FALSE),retain)
  __INIT_LOCATED(BOOL,__QX1_2,data__->SEL_CAFE_PURO,retain)
  __INIT_LOCATED_VALUE(data__->SEL_CAFE_PURO,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX1_3,data__->SEL_CAFE_ACUCAR,retain)
  __INIT_LOCATED_VALUE(data__->SEL_CAFE_ACUCAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX1_4,data__->SEL_CAFE_LEITE_PURO,retain)
  __INIT_LOCATED_VALUE(data__->SEL_CAFE_LEITE_PURO,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX1_5,data__->SEL_CAFE_LEITE_ACUCAR,retain)
  __INIT_LOCATED_VALUE(data__->SEL_CAFE_LEITE_ACUCAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX2_0,data__->S_NIVEL_AGUA,retain)
  __INIT_LOCATED_VALUE(data__->S_NIVEL_AGUA,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX2_1,data__->S_NIVEL_CAFE,retain)
  __INIT_LOCATED_VALUE(data__->S_NIVEL_CAFE,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX2_2,data__->S_NIVEL_ACUCAR,retain)
  __INIT_LOCATED_VALUE(data__->S_NIVEL_ACUCAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX2_3,data__->S_NIVEL_LEITE,retain)
  __INIT_LOCATED_VALUE(data__->S_NIVEL_LEITE,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX2_4,data__->S_XICARA,retain)
  __INIT_LOCATED_VALUE(data__->S_XICARA,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX2_0,data__->VALVULA_LEITE,retain)
  __INIT_LOCATED_VALUE(data__->VALVULA_LEITE,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX2_1,data__->VALVULA_AGUA,retain)
  __INIT_LOCATED_VALUE(data__->VALVULA_AGUA,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX2_2,data__->VALVULA_SAIDA,retain)
  __INIT_LOCATED_VALUE(data__->VALVULA_SAIDA,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX2_3,data__->DOSADOR_CAFE,retain)
  __INIT_LOCATED_VALUE(data__->DOSADOR_CAFE,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX2_4,data__->DOSADOR_ACUCAR,retain)
  __INIT_LOCATED_VALUE(data__->DOSADOR_ACUCAR,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->INGREDIENTES_OK,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->T_INGREDIENTES,retain);
  TON_init__(&data__->T_MISTURA,retain);
  TON_init__(&data__->T_SAIDA,retain);
  __INIT_VAR(data__->MOTOR_MISTURADOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_LOCATED(BOOL,__QX1_7,data__->AQUECEDOR,retain)
  __INIT_LOCATED_VALUE(data__->AQUECEDOR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX1_6,data__->BUZZER,retain)
  __INIT_LOCATED_VALUE(data__->BUZZER,__BOOL_LITERAL(FALSE))
  R_TRIG_init__(&data__->R_TRIG1,retain);
  R_TRIG_init__(&data__->R_TRIG2,retain);
  R_TRIG_init__(&data__->R_TRIG3,retain);
  R_TRIG_init__(&data__->R_TRIG4,retain);
  R_TRIG_init__(&data__->R_TRIG5,retain);
  R_TRIG_init__(&data__->R_TRIG6,retain);
  R_TRIG_init__(&data__->R_TRIG7,retain);
  R_TRIG_init__(&data__->R_TRIG8,retain);
  R_TRIG_init__(&data__->R_TRIG9,retain);
  R_TRIG_init__(&data__->R_TRIG10,retain);
  R_TRIG_init__(&data__->R_TRIG11,retain);
  R_TRIG_init__(&data__->R_TRIG12,retain);
  R_TRIG_init__(&data__->R_TRIG13,retain);
  R_TRIG_init__(&data__->R_TRIG14,retain);
  R_TRIG_init__(&data__->R_TRIG15,retain);
  R_TRIG_init__(&data__->R_TRIG16,retain);
  R_TRIG_init__(&data__->R_TRIG17,retain);
  R_TRIG_init__(&data__->R_TRIG18,retain);
  R_TRIG_init__(&data__->R_TRIG19,retain);
  R_TRIG_init__(&data__->R_TRIG20,retain);
  R_TRIG_init__(&data__->R_TRIG21,retain);
  R_TRIG_init__(&data__->R_TRIG22,retain);
  R_TRIG_init__(&data__->R_TRIG23,retain);
  R_TRIG_init__(&data__->R_TRIG24,retain);
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  if (__GET_LOCATED(data__->CANCELAR,)) {
    __SET_LOCATED(data__->,SEL_CAFE_PURO,,__BOOL_LITERAL(FALSE));
  };
  if (__GET_LOCATED(data__->CANCELAR,)) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_PURO,,__BOOL_LITERAL(FALSE));
  };
  if (__GET_LOCATED(data__->CANCELAR,)) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  if (__GET_LOCATED(data__->CANCELAR,)) {
    __SET_LOCATED(data__->,SEL_CAFE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  if (__GET_LOCATED(data__->CANCELAR,)) {
    __SET_VAR(data__->,M_START,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG1.,CLK,,__GET_LOCATED(data__->CAFE_PURO,));
  R_TRIG_body__(&data__->R_TRIG1);
  if ((__GET_VAR(data__->R_TRIG1.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_PURO,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->R_TRIG2.,CLK,,__GET_LOCATED(data__->CAFE_PURO,));
  R_TRIG_body__(&data__->R_TRIG2);
  if ((__GET_VAR(data__->R_TRIG2.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG3.,CLK,,__GET_LOCATED(data__->CAFE_PURO,));
  R_TRIG_body__(&data__->R_TRIG3);
  if ((__GET_VAR(data__->R_TRIG3.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG4.,CLK,,__GET_LOCATED(data__->CAFE_PURO,));
  R_TRIG_body__(&data__->R_TRIG4);
  if ((__GET_VAR(data__->R_TRIG4.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_PURO,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG5.,CLK,,__GET_LOCATED(data__->CAFE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG5);
  if ((__GET_VAR(data__->R_TRIG5.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_PURO,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG6.,CLK,,__GET_LOCATED(data__->CAFE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG6);
  if ((__GET_VAR(data__->R_TRIG6.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_ACUCAR,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->R_TRIG7.,CLK,,__GET_LOCATED(data__->CAFE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG7);
  if ((__GET_VAR(data__->R_TRIG7.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG8.,CLK,,__GET_LOCATED(data__->CAFE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG8);
  if ((__GET_VAR(data__->R_TRIG8.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_PURO,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG9.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG9);
  if ((__GET_VAR(data__->R_TRIG9.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_PURO,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG10.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG10);
  if ((__GET_VAR(data__->R_TRIG10.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG11.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG11);
  if ((__GET_VAR(data__->R_TRIG11.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_ACUCAR,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->R_TRIG12.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_ACUCAR,));
  R_TRIG_body__(&data__->R_TRIG12);
  if ((__GET_VAR(data__->R_TRIG12.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_PURO,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG13.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_PURO,));
  R_TRIG_body__(&data__->R_TRIG13);
  if ((__GET_VAR(data__->R_TRIG13.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_PURO,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG14.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_PURO,));
  R_TRIG_body__(&data__->R_TRIG14);
  if ((__GET_VAR(data__->R_TRIG14.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG15.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_PURO,));
  R_TRIG_body__(&data__->R_TRIG15);
  if ((__GET_VAR(data__->R_TRIG15.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->R_TRIG16.,CLK,,__GET_LOCATED(data__->CAFE_LEITE_PURO,));
  R_TRIG_body__(&data__->R_TRIG16);
  if ((__GET_VAR(data__->R_TRIG16.Q,) && !(__GET_VAR(data__->M_START,)))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_PURO,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->R_TRIG17.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG17);
  __SET_VAR(data__->R_TRIG18.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG18);
  __SET_VAR(data__->R_TRIG19.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG19);
  __SET_VAR(data__->R_TRIG20.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG20);
  if (((((__GET_LOCATED(data__->CAFE_ACUCAR,) && __GET_VAR(data__->R_TRIG17.Q,)) || (__GET_LOCATED(data__->CAFE_LEITE_ACUCAR,) && __GET_VAR(data__->R_TRIG20.Q,))) || (__GET_LOCATED(data__->CAFE_LEITE_PURO,) && __GET_VAR(data__->R_TRIG19.Q,))) || (__GET_LOCATED(data__->CAFE_PURO,) && __GET_VAR(data__->R_TRIG18.Q,)))) {
    __SET_VAR(data__->,M_START,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->,INGREDIENTES_OK,,((((((__GET_LOCATED(data__->S_NIVEL_ACUCAR,) && __GET_LOCATED(data__->S_NIVEL_CAFE,)) && __GET_LOCATED(data__->S_NIVEL_AGUA,)) && __GET_LOCATED(data__->SEL_CAFE_ACUCAR,)) || ((__GET_LOCATED(data__->S_NIVEL_CAFE,) && __GET_LOCATED(data__->S_NIVEL_AGUA,)) && __GET_LOCATED(data__->SEL_CAFE_PURO,))) || ((((__GET_LOCATED(data__->S_NIVEL_LEITE,) && __GET_LOCATED(data__->S_NIVEL_ACUCAR,)) && __GET_LOCATED(data__->S_NIVEL_CAFE,)) && __GET_LOCATED(data__->S_NIVEL_AGUA,)) && __GET_LOCATED(data__->SEL_CAFE_LEITE_ACUCAR,))) || (((__GET_LOCATED(data__->S_NIVEL_LEITE,) && __GET_LOCATED(data__->S_NIVEL_CAFE,)) && __GET_LOCATED(data__->S_NIVEL_AGUA,)) && __GET_LOCATED(data__->SEL_CAFE_LEITE_PURO,))));
  __SET_LOCATED(data__->,VALVULA_AGUA,,(!(__GET_VAR(data__->T_INGREDIENTES.Q,)) && __GET_VAR(data__->M_START,)));
  __SET_LOCATED(data__->,DOSADOR_CAFE,,(!(__GET_VAR(data__->T_INGREDIENTES.Q,)) && __GET_VAR(data__->M_START,)));
  __SET_LOCATED(data__->,DOSADOR_ACUCAR,,(((__GET_LOCATED(data__->SEL_CAFE_ACUCAR,) || __GET_LOCATED(data__->SEL_CAFE_LEITE_ACUCAR,)) && !(__GET_VAR(data__->T_INGREDIENTES.Q,))) && __GET_VAR(data__->M_START,)));
  __SET_LOCATED(data__->,VALVULA_LEITE,,(((__GET_LOCATED(data__->SEL_CAFE_LEITE_ACUCAR,) || __GET_LOCATED(data__->SEL_CAFE_LEITE_PURO,)) && !(__GET_VAR(data__->T_INGREDIENTES.Q,))) && __GET_VAR(data__->M_START,)));
  __SET_VAR(data__->,MOTOR_MISTURADOR,,((!(__GET_VAR(data__->T_MISTURA.Q,)) && __GET_VAR(data__->T_INGREDIENTES.Q,)) && __GET_VAR(data__->M_START,)));
  __SET_LOCATED(data__->,AQUECEDOR,,((!(__GET_VAR(data__->T_MISTURA.Q,)) && __GET_VAR(data__->T_INGREDIENTES.Q,)) && __GET_VAR(data__->M_START,)));
  __SET_LOCATED(data__->,VALVULA_SAIDA,,(((__GET_LOCATED(data__->S_XICARA,) && !(__GET_VAR(data__->T_SAIDA.Q,))) && __GET_VAR(data__->T_MISTURA.Q,)) && __GET_VAR(data__->M_START,)));
  if ((!(__GET_LOCATED(data__->VALVULA_SAIDA,)) && __GET_VAR(data__->T_SAIDA.Q,))) {
    __SET_LOCATED(data__->,SEL_CAFE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  if ((!(__GET_LOCATED(data__->VALVULA_SAIDA,)) && __GET_VAR(data__->T_SAIDA.Q,))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_ACUCAR,,__BOOL_LITERAL(FALSE));
  };
  if ((!(__GET_LOCATED(data__->VALVULA_SAIDA,)) && __GET_VAR(data__->T_SAIDA.Q,))) {
    __SET_LOCATED(data__->,SEL_CAFE_LEITE_PURO,,__BOOL_LITERAL(FALSE));
  };
  if ((!(__GET_LOCATED(data__->VALVULA_SAIDA,)) && __GET_VAR(data__->T_SAIDA.Q,))) {
    __SET_LOCATED(data__->,SEL_CAFE_PURO,,__BOOL_LITERAL(FALSE));
  };
  __SET_LOCATED(data__->,LED_CANCELAR,,((((__GET_LOCATED(data__->CANCELAR,) || __GET_LOCATED(data__->CANCELAR,)) || __GET_LOCATED(data__->CANCELAR,)) || __GET_LOCATED(data__->CANCELAR,)) || __GET_LOCATED(data__->CANCELAR,)));
  __SET_VAR(data__->R_TRIG21.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG21);
  __SET_VAR(data__->R_TRIG22.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG22);
  __SET_VAR(data__->R_TRIG23.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG23);
  __SET_VAR(data__->R_TRIG24.,CLK,,__GET_LOCATED(data__->BOTAO_LIGAR,));
  R_TRIG_body__(&data__->R_TRIG24);
  __SET_LOCATED(data__->,LED_LIGAR,,((((__GET_LOCATED(data__->CAFE_ACUCAR,) && __GET_VAR(data__->R_TRIG24.Q,)) || (__GET_LOCATED(data__->CAFE_LEITE_ACUCAR,) && __GET_VAR(data__->R_TRIG23.Q,))) || (__GET_LOCATED(data__->CAFE_LEITE_PURO,) && __GET_VAR(data__->R_TRIG22.Q,))) || (__GET_LOCATED(data__->CAFE_PURO,) && __GET_VAR(data__->R_TRIG21.Q,))));
  __SET_LOCATED(data__->,BUZZER,,(((__GET_LOCATED(data__->S_XICARA,) && !(__GET_VAR(data__->T_SAIDA.Q,))) && __GET_VAR(data__->T_MISTURA.Q,)) && __GET_VAR(data__->M_START,)));
  if ((!(__GET_LOCATED(data__->VALVULA_SAIDA,)) && __GET_VAR(data__->T_SAIDA.Q,))) {
    __SET_VAR(data__->,M_START,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->T_INGREDIENTES.,IN,,__GET_VAR(data__->M_START,));
  __SET_VAR(data__->T_INGREDIENTES.,PT,,__time_to_timespec(1, 0, 10, 0, 0, 0));
  TON_body__(&data__->T_INGREDIENTES);
  __SET_VAR(data__->T_MISTURA.,IN,,__GET_VAR(data__->T_INGREDIENTES.Q,));
  __SET_VAR(data__->T_MISTURA.,PT,,__time_to_timespec(1, 0, 30, 0, 0, 0));
  TON_body__(&data__->T_MISTURA);
  __SET_VAR(data__->T_SAIDA.,IN,,(__GET_LOCATED(data__->S_XICARA,) && __GET_VAR(data__->T_MISTURA.Q,)));
  __SET_VAR(data__->T_SAIDA.,PT,,__time_to_timespec(1, 0, 10, 0, 0, 0));
  TON_body__(&data__->T_SAIDA);

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





