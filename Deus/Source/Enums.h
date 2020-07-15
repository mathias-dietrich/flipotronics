//
//  Enums.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Enums_h
#define Enums_h


enum E_Master {mEdit, mLibrary, mPerform, mArp, mSetup, mDebug};

enum E_ViewMode { vPlot=1, vSpectrum, vADSR1, vADSR2, vADSR3, vADSR4, vLFO1, vLFO2, vLFO3, vLFO4, vWave, vCurve, vDebug, vTable, vNone };

enum E_WaveType { wSin, wSaw, wTriangle, wSquare, wShark, wWhite, wPink, wBrown, wTable };

enum E_UnitType { uFloat, uDouble, uInt, uBool, uTertiar, uString, uHZ, uDb, uColorCode, uWaveType, uTimeMsec, uPhase, uCurve, uMidiNote, uDevision, uProcent, uChordMode, uArpMode, uFilterType, uUnknown};

enum E_ParamType { pVol, pBalance, pFreq, pDelay, pTime, pTimeSpan, pMidiNote, pAngle, pText, pImageUrl, pUrl, pLocation, pSize, pColo, pControl, pSysex };

enum E_FileType { fWav,fAiff, fCaf, fMP3, fBank, fPatch, fSettings, fImage, fRaw, fMidi };

enum E_NoteType { nWHOLE, nHALF, nHALFD, qQuarter, qQuarterD, nEIGHT, nEIGHTD, nSIXTEEN, nSIXTEEND, nThirtyTwo, nThirtyTwoD, nSixtyFour};

enum MultiModeLadderFilterTypes
{
    OFF=0,
    LPF1,
    LPF2,
    LPF3,
    LPF4,
    HPF1,
    HPF2,
    HPF3,
    HPF4,
    BPF2,
    BPF4,
    NF2,
    NF4,
    PF2,
    PF4,
    OFF2,
    NumberOfFilterTypes
};

#endif /* Enums_h */
