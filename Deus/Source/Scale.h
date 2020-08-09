//
//  Scale.h
//  Deus
//
//  Created by Mathias Dietrich on 09.08.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Scale_h
#define Scale_h
/*
 Chromatic 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
 Major 0, 2, 4, 5, 7, 9, 11
 Natural Minor 0, 2, 3, 5, 7, 8, 10
 Harmonic Minor 0, 2, 3, 5, 7, 8,11
 Melodic Minor 0, 2, 3, 5, 7, 9, 11
 Dorian 0, 2, 3, 5, 7, 9, 10
 Phrygian 0, 1, 3, 4, 5, 7, 8, 10
 Lydian 0, 2, 4, 6, 7, 9, 11
 Mixolydian 0, 2, 4, 5, 7, 9, 10
 Locrian 0, 1, 3, 5, 6, 8, 10
 Major Pentatonic 0, 2, 4, 7, 9
 Minor Pentatonic 0, 3, 5, 7, 10
 Blues 0, 3, 5, 6, 7, 10
 Fifth 0, 5
 Custom [User's Choice]
 */
class Scale{
public:
    
    Scale(){

    }
    
    constexpr static const int chromatic[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    constexpr static const int major[] = { 0, 2, 4, 5, 7, 9, 11};
    constexpr static const int minorNat[]= {0, 2, 3, 5, 7, 8, 10};
    constexpr static const int minorHar[]= {0, 2, 3, 5, 7, 8,11};
    constexpr static const int minorMin[] = {0, 2, 3, 5, 7, 9, 11};
    constexpr static const int dorian[]= {0, 2, 3, 5, 7, 9, 10};
    constexpr static const int phryg[]= {0, 1, 3, 4, 5, 7, 8, 10};
    constexpr  static const int lydian[]= {0, 2, 4, 6, 7, 9, 11};
    constexpr static const int mixolydian[]= {0, 2, 4, 5, 7, 9, 10};
    constexpr static const int locrian[] = {0, 1, 3, 5, 6, 8, 10};
    constexpr static const int penthatonicMaj[] = {0, 2, 4, 7, 9};
    constexpr static const int penthatonicMin[] = {0, 3, 5, 7, 10};
    constexpr static const int blues[] = {0, 3, 5, 6, 7, 10};
    constexpr static const int fifth[] = {0, 5};
    static const int custom[];
    
    int scale[];
    
};


#endif /* Scale_h */
