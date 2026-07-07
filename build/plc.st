TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM program0
  VAR
    cancelar AT %IX1.0 : BOOL;
    botao_ligar AT %IX1.1 : BOOL;
    cafe_puro AT %IX1.2 : BOOL;
    cafe_acucar AT %IX1.3 : BOOL;
    cafe_leite_puro AT %IX1.4 : BOOL;
    cafe_leite_acucar AT %IX1.5 : BOOL;
    LED_cancelar AT %QX1.0 : BOOL;
    LED_ligar AT %QX1.1 : BOOL;
  END_VAR
  VAR
    M_start : BOOL;
  END_VAR
  VAR
    sel_cafe_puro AT %QX1.2 : BOOL;
    sel_cafe_acucar AT %QX1.3 : BOOL;
    sel_cafe_leite_puro AT %QX1.4 : BOOL;
    sel_cafe_leite_acucar AT %QX1.5 : BOOL;
    S_nivel_agua AT %IX2.0 : BOOL;
    S_nivel_cafe AT %IX2.1 : BOOL;
    S_nivel_acucar AT %IX2.2 : BOOL;
    S_nivel_leite AT %IX2.3 : BOOL;
    S_xicara AT %IX2.4 : BOOL;
    Valvula_leite AT %QX2.0 : BOOL;
    Valvula_agua AT %QX2.1 : BOOL;
    Valvula_saida AT %QX2.2 : BOOL;
    Dosador_cafe AT %QX2.3 : BOOL;
    Dosador_acucar AT %QX2.4 : BOOL;
  END_VAR
  VAR
    ingredientes_ok : BOOL;
    T_ingredientes : TON;
    T_mistura : TON;
    T_saida : TON;
    Motor_misturador : BOOL;
  END_VAR
  VAR
    Aquecedor AT %QX1.7 : BOOL;
    Buzzer AT %QX1.6 : BOOL;
  END_VAR
  VAR
    R_TRIG1 : R_TRIG;
    R_TRIG2 : R_TRIG;
    R_TRIG3 : R_TRIG;
    R_TRIG4 : R_TRIG;
    R_TRIG5 : R_TRIG;
    R_TRIG6 : R_TRIG;
    R_TRIG7 : R_TRIG;
    R_TRIG8 : R_TRIG;
    R_TRIG9 : R_TRIG;
    R_TRIG10 : R_TRIG;
    R_TRIG11 : R_TRIG;
    R_TRIG12 : R_TRIG;
    R_TRIG13 : R_TRIG;
    R_TRIG14 : R_TRIG;
    R_TRIG15 : R_TRIG;
    R_TRIG16 : R_TRIG;
    R_TRIG17 : R_TRIG;
    R_TRIG18 : R_TRIG;
    R_TRIG19 : R_TRIG;
    R_TRIG20 : R_TRIG;
    R_TRIG21 : R_TRIG;
    R_TRIG22 : R_TRIG;
    R_TRIG23 : R_TRIG;
    R_TRIG24 : R_TRIG;
  END_VAR

  IF cancelar THEN
    sel_cafe_puro := FALSE; (*reset*)
  END_IF;
  IF cancelar THEN
    sel_cafe_leite_puro := FALSE; (*reset*)
  END_IF;
  IF cancelar THEN
    sel_cafe_leite_acucar := FALSE; (*reset*)
  END_IF;
  IF cancelar THEN
    sel_cafe_acucar := FALSE; (*reset*)
  END_IF;
  IF cancelar THEN
    M_start := FALSE; (*reset*)
  END_IF;
  R_TRIG1(CLK := cafe_puro);
  IF R_TRIG1.Q AND NOT(M_start) THEN
    sel_cafe_puro := TRUE; (*set*)
  END_IF;
  R_TRIG2(CLK := cafe_puro);
  IF R_TRIG2.Q AND NOT(M_start) THEN
    sel_cafe_acucar := FALSE; (*reset*)
  END_IF;
  R_TRIG3(CLK := cafe_puro);
  IF R_TRIG3.Q AND NOT(M_start) THEN
    sel_cafe_leite_acucar := FALSE; (*reset*)
  END_IF;
  R_TRIG4(CLK := cafe_puro);
  IF R_TRIG4.Q AND NOT(M_start) THEN
    sel_cafe_leite_puro := FALSE; (*reset*)
  END_IF;
  R_TRIG5(CLK := cafe_acucar);
  IF R_TRIG5.Q AND NOT(M_start) THEN
    sel_cafe_puro := FALSE; (*reset*)
  END_IF;
  R_TRIG6(CLK := cafe_acucar);
  IF R_TRIG6.Q AND NOT(M_start) THEN
    sel_cafe_acucar := TRUE; (*set*)
  END_IF;
  R_TRIG7(CLK := cafe_acucar);
  IF R_TRIG7.Q AND NOT(M_start) THEN
    sel_cafe_leite_acucar := FALSE; (*reset*)
  END_IF;
  R_TRIG8(CLK := cafe_acucar);
  IF R_TRIG8.Q AND NOT(M_start) THEN
    sel_cafe_leite_puro := FALSE; (*reset*)
  END_IF;
  R_TRIG9(CLK := cafe_leite_acucar);
  IF R_TRIG9.Q AND NOT(M_start) THEN
    sel_cafe_puro := FALSE; (*reset*)
  END_IF;
  R_TRIG10(CLK := cafe_leite_acucar);
  IF R_TRIG10.Q AND NOT(M_start) THEN
    sel_cafe_acucar := FALSE; (*reset*)
  END_IF;
  R_TRIG11(CLK := cafe_leite_acucar);
  IF R_TRIG11.Q AND NOT(M_start) THEN
    sel_cafe_leite_acucar := TRUE; (*set*)
  END_IF;
  R_TRIG12(CLK := cafe_leite_acucar);
  IF R_TRIG12.Q AND NOT(M_start) THEN
    sel_cafe_leite_puro := FALSE; (*reset*)
  END_IF;
  R_TRIG13(CLK := cafe_leite_puro);
  IF R_TRIG13.Q AND NOT(M_start) THEN
    sel_cafe_puro := FALSE; (*reset*)
  END_IF;
  R_TRIG14(CLK := cafe_leite_puro);
  IF R_TRIG14.Q AND NOT(M_start) THEN
    sel_cafe_acucar := FALSE; (*reset*)
  END_IF;
  R_TRIG15(CLK := cafe_leite_puro);
  IF R_TRIG15.Q AND NOT(M_start) THEN
    sel_cafe_leite_acucar := FALSE; (*reset*)
  END_IF;
  R_TRIG16(CLK := cafe_leite_puro);
  IF R_TRIG16.Q AND NOT(M_start) THEN
    sel_cafe_leite_puro := TRUE; (*set*)
  END_IF;
  R_TRIG17(CLK := botao_ligar);
  R_TRIG18(CLK := botao_ligar);
  R_TRIG19(CLK := botao_ligar);
  R_TRIG20(CLK := botao_ligar);
  IF cafe_acucar AND R_TRIG17.Q OR cafe_leite_acucar AND R_TRIG20.Q OR cafe_leite_puro AND R_TRIG19.Q OR cafe_puro AND R_TRIG18.Q THEN
    M_start := TRUE; (*set*)
  END_IF;
  ingredientes_ok := S_nivel_acucar AND S_nivel_cafe AND S_nivel_agua AND sel_cafe_acucar OR S_nivel_cafe AND S_nivel_agua AND sel_cafe_puro OR S_nivel_leite AND S_nivel_acucar AND S_nivel_cafe AND S_nivel_agua AND sel_cafe_leite_acucar OR S_nivel_leite AND S_nivel_cafe AND S_nivel_agua AND sel_cafe_leite_puro;
  Valvula_agua := NOT(T_ingredientes.Q) AND M_start;
  Dosador_cafe := NOT(T_ingredientes.Q) AND M_start;
  Dosador_acucar := (sel_cafe_acucar OR sel_cafe_leite_acucar) AND NOT(T_ingredientes.Q) AND M_start;
  Valvula_leite := (sel_cafe_leite_acucar OR sel_cafe_leite_puro) AND NOT(T_ingredientes.Q) AND M_start;
  Motor_misturador := NOT(T_mistura.Q) AND T_ingredientes.Q AND M_start;
  Aquecedor := NOT(T_mistura.Q) AND T_ingredientes.Q AND M_start;
  Valvula_saida := S_xicara AND NOT(T_saida.Q) AND T_mistura.Q AND M_start;
  IF NOT(Valvula_saida) AND T_saida.Q THEN
    sel_cafe_acucar := FALSE; (*reset*)
  END_IF;
  IF NOT(Valvula_saida) AND T_saida.Q THEN
    sel_cafe_leite_acucar := FALSE; (*reset*)
  END_IF;
  IF NOT(Valvula_saida) AND T_saida.Q THEN
    sel_cafe_leite_puro := FALSE; (*reset*)
  END_IF;
  IF NOT(Valvula_saida) AND T_saida.Q THEN
    sel_cafe_puro := FALSE; (*reset*)
  END_IF;
  LED_cancelar := cancelar OR cancelar OR cancelar OR cancelar OR cancelar;
  R_TRIG21(CLK := botao_ligar);
  R_TRIG22(CLK := botao_ligar);
  R_TRIG23(CLK := botao_ligar);
  R_TRIG24(CLK := botao_ligar);
  LED_ligar := cafe_acucar AND R_TRIG24.Q OR cafe_leite_acucar AND R_TRIG23.Q OR cafe_leite_puro AND R_TRIG22.Q OR cafe_puro AND R_TRIG21.Q;
  Buzzer := S_xicara AND NOT(T_saida.Q) AND T_mistura.Q AND M_start;
  IF NOT(Valvula_saida) AND T_saida.Q THEN
    M_start := FALSE; (*reset*)
  END_IF;
  T_ingredientes(IN := M_start, PT := T#10s);
  T_mistura(IN := T_ingredientes.Q, PT := T#30s);
  T_saida(IN := S_xicara AND T_mistura.Q, PT := T#10s);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
