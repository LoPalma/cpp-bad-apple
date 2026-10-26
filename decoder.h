#ifndef DECODER_H
#define DECODER_H

#define REP_1(c) c
#define REP_2(c) c c
#define REP_3(c) c c c
#define REP_4(c) c c c c

#define REP_5(c) c c c c c

#define REP_10(c) REP_5(c) REP_5(c)
#define REP_20(c) REP_10(c) REP_10(c)
#define REP_30(c) REP_20(c) REP_10(c)
#define REP_40(c) REP_20(c) REP_20(c)
#define REP_50(c) REP_30(c) REP_20(c)
#define REP_60(c) REP_30(c) REP_30(c)

#define REP_6(c)  REP_5(c) REP_1(c)
#define REP_7(c)  REP_5(c) REP_2(c)
#define REP_8(c)  REP_5(c) REP_3(c)
#define REP_9(c)  REP_5(c) REP_4(c)

#define REP_11(c) REP_10(c) REP_1(c)
#define REP_12(c) REP_10(c) REP_2(c)
#define REP_13(c) REP_10(c) REP_3(c)
#define REP_14(c) REP_10(c) REP_4(c)
#define REP_15(c) REP_10(c) REP_5(c)
#define REP_16(c) REP_10(c) REP_6(c)
#define REP_17(c) REP_10(c) REP_7(c)
#define REP_18(c) REP_10(c) REP_8(c)
#define REP_19(c) REP_10(c) REP_9(c)

#define REP_21(c) REP_20(c) REP_1(c)
#define REP_22(c) REP_20(c) REP_2(c)
#define REP_23(c) REP_20(c) REP_3(c)
#define REP_24(c) REP_20(c) REP_4(c)
#define REP_25(c) REP_20(c) REP_5(c)
#define REP_26(c) REP_20(c) REP_6(c)
#define REP_27(c) REP_20(c) REP_7(c)
#define REP_28(c) REP_20(c) REP_8(c)
#define REP_29(c) REP_20(c) REP_9(c)

#define REP_31(c) REP_30(c) REP_1(c)
#define REP_32(c) REP_30(c) REP_2(c)
#define REP_33(c) REP_30(c) REP_3(c)
#define REP_34(c) REP_30(c) REP_4(c)
#define REP_35(c) REP_30(c) REP_5(c)
#define REP_36(c) REP_30(c) REP_6(c)
#define REP_37(c) REP_30(c) REP_7(c)
#define REP_38(c) REP_30(c) REP_8(c)
#define REP_39(c) REP_30(c) REP_9(c)

#define REP_41(c) REP_40(c) REP_1(c)
#define REP_42(c) REP_40(c) REP_2(c)
#define REP_43(c) REP_40(c) REP_3(c)
#define REP_44(c) REP_40(c) REP_4(c)
#define REP_45(c) REP_40(c) REP_5(c)
#define REP_46(c) REP_40(c) REP_6(c)
#define REP_47(c) REP_40(c) REP_7(c)
#define REP_48(c) REP_40(c) REP_8(c)
#define REP_49(c) REP_40(c) REP_9(c)

#define REP_51(c) REP_50(c) REP_1(c)
#define REP_52(c) REP_50(c) REP_2(c)
#define REP_53(c) REP_50(c) REP_3(c)
#define REP_54(c) REP_50(c) REP_4(c)
#define REP_55(c) REP_50(c) REP_5(c)
#define REP_56(c) REP_50(c) REP_6(c)
#define REP_57(c) REP_50(c) REP_7(c)
#define REP_58(c) REP_50(c) REP_8(c)
#define REP_59(c) REP_50(c) REP_9(c)

#define REP_61(c) REP_60(c) REP_1(c)
#define REP_62(c) REP_60(c) REP_2(c)
#define REP_63(c) REP_60(c) REP_3(c)
#define REP_64(c) REP_60(c) REP_4(c)

#define GLUE(a, b) a ## b
#define EXPAND_THEN_REP(num, c) GLUE(REP_, num)(c)

#define B(num) EXPAND_THEN_REP(num, .)
#define W(num) EXPAND_THEN_REP(num, █)

#endif // DECODER_H
