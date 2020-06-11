//
//  Enum.h
//  synth1
//
//  Created by Mathias Dietrich on 01.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Enum_h
#define Enum_h

enum E_WaveType { wSin, wSaw, wTriangle, wSquare, wShark, wWhite, wPink, wBrown, wTable };

enum E_UnitType { uFloat, uDouble, uInt, uBool, uTertiar, uString, uHZ, uDb, uColorCode, uWaveType, uTimeMsec, uPhase, uUnknown};

enum E_ParamType { pVol, pBalance, pFreq, pDelay, pTime, pTimeSpan, pMidiNote, pAngle, pText, pImageUrl, pUrl, pLocation, pSize, pColo, pControl, pSysex };

enum E_FileType { fWav,fAiff, fCaf, fMP3, fBank, fPatch, fSettings, fImage, fRaw, fMidi };


#endif /* Enum_h */
