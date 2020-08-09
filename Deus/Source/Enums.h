//
//  Enums.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Enums_h
#define Enums_h

enum MatrixSource{
    s_NONE = 0,
    s_VELOCITY = 1,
    s_AFTERTOUCH = 2,
    s_MODWHEEL = 3,
    s_KEYBOARD = 4,
    s_EXPRESSION = 5,
    s_ADSR0 = 6,
    s_ADSR1 = 7,
    s_ADSR2 = 8,
    s_LFO0 = 9,
    s_LFO1 = 10,
    s_LFO2 = 11,
    s_LFO3 = 12,
    s_FUNC0 = 13,
    s_FUNC1 = 14,
    s_FUNC2 = 15,
    s_RND0 = 16,
    s_RND1 = 17,
    s_RND2 = 18,
    s_COMB0 = 19,
    s_COMB1 = 20,
    s_COMB2 = 21,
    MACRO0 = 22,
    MACRO1 = 23,
    MACRO2 = 24,
    MACRO3 = 25,
    MACRO4 = 26,
    MACRO5 = 27,
    MACRO6 = 28,
    MACRO7 = 29,
    MACRO8 = 30,
    MACRO9 = 31,
    MACRO10 = 32,
    MACRO11 = 33,
    MACRO12 = 34,
    MACRO13 = 35,
    MACRO14 = 36,
    MACRO15 = 37,
    s_SOURCESCOUNT 
};

enum MatrixDest{
    d_NONE = 0,
    d_OSC0_PITCH,
    d_OSC0_VOL,
    d_FILTER0_CUTOFF,
    d_TARGETSCOUNT
};

enum E_Global {
    
    gMasterVolume = 0,
    gNoOfVoices = 1,
    gGGLOBALCOUNT
};

enum E_Module {
    mOSCAnalog0=0,
    mOSCAnalog1=1,
    mOSCWave0=2,
    mOSCWave1=3,
    mOSCSample0=4,
    mOSCSample1=5,
    mFilter0=6,
    mFilter1=7,
    mAdsr0=8,
    mAdsr1=9,
    mAdsr2=10,
    mLFO0=11,
    mLFO1=12,
    mLFO2=13,
    mLFO3=14,
    mAmp=15,
    mInput=16,
    mLFX0=17,
    mLFX1=18,
    mLFX2=19,
    mLFX3=20,
    mMacro=21,
    mBlank=22,
    mMatrix=23,
    mGlobal=24,
    mDelay=25,
    mUnknown=26,
    mMODULECOUNT
};

enum E_Master {mEdit, mLibrary, mPerform, mArp, mSetup, mDebug};

enum E_ViewMode { vPlot=1, vSpectrum, vADSR1, vADSR2, vADSR3, vADSR4, vLFO1, vLFO2, vLFO3, vLFO4, vWave, vCurve, vDebug, vTable, vNone };

enum E_WaveType { wSin, wSaw, wTriangle, wSquare, wShark, wWhite, wPink, wBrown, wTable };

enum E_UnitType { uFloat, uDouble, uInt, uBool, uTertiar, uString, uHZ, uTune, uDb, uColorCode, uWaveType, uTimeMsec, uPhase, uCurve, uMidiNote, uDevision, uProcent, uChordMode, uArpMode, uFilterType, uUnknown};

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
