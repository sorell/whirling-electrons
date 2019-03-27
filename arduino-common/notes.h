#ifndef SS_NOTES_H
#define SS_NOTES_H

#define TEMPO(x) (60000 / (x))

#define NLx2(tempo) ((tempo) * 8)
#define NLx2dot(tempo) ((tempo) * 12)
#define NLx1(tempo) ((tempo) * 4)
#define NLx1dot(tempo) ((tempo) * 6)
#define NL_2(tempo) ((tempo) * 2)
#define NL_2dot(tempo) ((tempo) * 3)
#define NL_4(tempo) (tempo)
#define NL_4dot(tempo) ((tempo) * 3 / 2)
#define NL_8(tempo) ((tempo) / 2)
#define NL_8dot(tempo) ((tempo) * 3 / 4)
#define NL_16(tempo) ((tempo) / 4)
#define NL_16dot(tempo) ((tempo) * 3 / 8)

#define C2 65
#define D2 73
#define E2 82
#define F2 87
#define G2 98
#define Gs2 104
#define A2 110
#define B2 123
#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define Gs3 208
#define A3 220
#define As3 233
#define B3 247
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define Gs4 415
#define A4 440
#define As4 466
#define B4 494
#define C5 523
#define Cs5 554
#define D5 587
#define Ds5 622
#define E5 659
#define F5 698
#define Fs5 740
#define G5 784
#define Gs5 830
#define A5 880
#define B5 988
#define C6 1047
#define D6 1175
#define E6 1319
#define F6 1397
#define G6 1568

#endif  // SS_NOTES_H
