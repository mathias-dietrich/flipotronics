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
    s_VELOCITY,
    s_AFTERTOUCH,
    s_MODWHEEL,
    s_KEYBOARD,
    s_EXPRESSION,
    s_ADSR0,
    s_ADSR1,
    s_ADSR2,
    s_LFO0,
    s_LFO1,
    s_LFO2,
    s_LFO3,
    s_FUNC0,
    s_FUNC1,
    s_FUNC2,
    s_RND0,
    s_RND1,
    s_RND2,
    s_COMB0,
    s_COMB1,
    s_COMB2,
    MACRO0,
    MACRO1,
    MACRO2,
    MACRO3,
    MACRO4,
    MACRO5,
    MACRO6,
    MACRO7,
    MACRO8,
    MACRO9,
    MACRO10,
    MACRO11,
    MACRO12,
    MACRO13,
    MACRO14,
    MACRO15,
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
