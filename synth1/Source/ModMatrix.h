//
//  ModMatrix.h
//  synth1
//
//  Created by Mathias Dietrich on 06.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ModMatrix_h
#define ModMatrix_h

#define MAX_SOURCES 128
#define MAX_DESTINATIONS 128

enum Transform{
    t_TRANSFORM_NONE = 0,
    t_TRANSFORM_UNIPOLAR_TO_BIPOLAR,
    t_TRANSFORM_BIPOLAR_TO_UNIPOLAR,
    t_TRANSFORM_MIDI_NORMALIZE,
    t_TRANSFORM_INVERT_MIDI_NORMALIZE,
    t_TRANSFORM_MIDI_TO_BIPOLAR,
    t_TRANSFORM_MIDI_TO_PAN,
    t_TRANSFORM_MIDI_SWITCH,
    t_TRANSFORM_MIDI_TO_ATTENUATION,
    t_TRANSFORM_NOTE_NUMBER_TO_FREQUENCY,
    t_MAX_TRANSFORMS /* not needed? */
};

enum ModSources{
    s_SOURCE_NONE = 0,

    s_SOURCE_UI_OSC1_FO,
    s_SOURCE_UI_OSC2_FO,
    s_SOURCE_UI_TO_OSC3_FO,
    s_SOURCE_UI_TO_OSC4_FO,
    s_SOURCE_UI_TO_ALL_OSC_FO,

    s_SOURCE_UI_FILTER1_FC,
    s_SOURCE_UI_FILTER2_FC,
    s_SOURCE_UI_ALL_FILTER_FC,
    s_SOURCE_UI_FILTER1_Q,
    s_SOURCE_UI_FILTER2_Q,
    s_SOURCE_UI_ALL_FILTER_Q,

    s_SOURCE_LFO1,
    s_SOURCE_LFO2,
    s_SOURCE_LFO1Q,                    /* QuadPhase outputs */
    s_SOURCE_LFO2Q,
    s_SOURCE_EG1,                        /* Exponential outputs */
    s_SOURCE_EG2,
    s_SOURCE_EG3,
    s_SOURCE_EG4,
    s_SOURCE_BIASED_EG1,                /* Exponential outputs with Sustain subtracted*/
    s_SOURCE_BIASED_EG2,
    s_SOURCE_BIASED_EG3,
    s_SOURCE_BIASED_EG4,
    s_SOURCE_VELOCITY,
    s_SOURCE_MIDI_VOLUME_CC07,        /* MIDI Volume */
    s_SOURCE_MIDI_PAN_CC10,            /* MIDI Pan */
    s_SOURCE_MIDI_EXPRESSION_CC11,    /* MIDI Expression */
    s_SOURCE_MODWHEEL,
    s_SOURCE_PITCHBEND,
    s_SOURCE_SUSTAIN_PEDAL,
    s_SOURCE_MIDI_NOTE_NUM,
    s_SOURCE_MIDI_JS_X,
    s_SOURCE_MIDI_JS_Y,
    s_MAX_SOURCES
};

enum ModDestinations{
    d_DEST_NONE = 0,

    // --- GUI control layer modulation (-1)
    d_DEST_UI_OSC1_FO,
    d_DEST_UI_OSC2_FO,
    d_DEST_UI_TO_OSC3_FO,
    d_DEST_UI_TO_OSC4_FO,
    d_DEST_UI_TO_ALL_OSC_FO,

    d_DEST_UI_FILTER1_FC,
    d_DEST_UI_FILTER2_FC,
    d_DEST_UI_ALL_FILTER_FC,
    d_DEST_UI_FILTER1_Q,
    d_DEST_UI_FILTER2_Q,
    d_DEST_UI_ALL_FILTER_Q,

    // --- LAYER 0 DESTINATIONS
    //     add more L0 destinations in this chunk
    //     see CModulationMatrix::checkDestinationLayer())
    d_DEST_LFO1_FO, // <- keep this first
    d_DEST_LFO2_FO,
    d_DEST_ALL_LFO_FO,
    d_DEST_LFO1_OUTPUT_AMP,
    d_DEST_LFO2_OUTPUT_AMP,
    d_DEST_ALL_LFO_OUTPUT_AMP,
    d_DEST_EG1_ATTACK_SCALING,
    d_DEST_EG2_ATTACK_SCALING,
    d_DEST_EG3_ATTACK_SCALING,
    d_DEST_EG4_ATTACK_SCALING,
    d_DEST_ALL_EG_ATTACK_SCALING,
    d_DEST_EG1_DECAY_SCALING,
    d_DEST_EG2_DECAY_SCALING,
    d_DEST_EG3_DECAY_SCALING,
    d_DEST_EG4_DECAY_SCALING,
    d_DEST_ALL_EG_DECAY_SCALING,
    d_DEST_EG1_SUSTAIN_OVERRIDE,
    d_DEST_EG2_SUSTAIN_OVERRIDE,
    d_DEST_EG3_SUSTAIN_OVERRIDE,
    d_DEST_EG4_SUSTAIN_OVERRIDE,
    d_DEST_ALL_EG_SUSTAIN_OVERRIDE, // <- keep this last
    // --- END OF LAYER 0 DESTINATIONS

    // --- LAYER 1 DESTINATIONS
    d_DEST_HARD_SYNC_RATIO,
    d_DEST_OSC1_FO,
    d_DEST_OSC2_FO,
    d_DEST_OSC3_FO,
    d_DEST_OSC4_FO,
    d_DEST_ALL_OSC_FO,
    d_DEST_OSC1_PULSEWIDTH,
    d_DEST_OSC2_PULSEWIDTH,
    d_DEST_OSC3_PULSEWIDTH,
    d_DEST_OSC4_PULSEWIDTH,
    d_DEST_ALL_OSC_PULSEWIDTH,
    d_DEST_OSC1_FO_RATIO,
    d_DEST_OSC2_FO_RATIO,
    d_DEST_OSC3_FO_RATIO,
    d_DEST_OSC4_FO_RATIO,
    d_DEST_ALL_OSC_FO_RATIO,
    d_DEST_OSC1_OUTPUT_AMP,
    d_DEST_OSC2_OUTPUT_AMP,
    d_DEST_OSC3_OUTPUT_AMP,
    d_DEST_OSC4_OUTPUT_AMP,
    d_DEST_ALL_OSC_OUTPUT_AMP,
    d_DEST_FILTER1_FC,
    d_DEST_FILTER2_FC,
    d_DEST_ALL_FILTER_FC,
    d_DEST_FILTER1_KEYTRACK,
    d_DEST_FILTER2_KEYTRACK,
    d_DEST_ALL_FILTER_KEYTRACK, // the control value, overriding the GUI
    d_DEST_FILTER1_Q,
    d_DEST_FILTER2_Q,
    d_DEST_ALL_FILTER_Q,
    d_DEST_VS_AC_AXIS,
    d_DEST_VS_BD_AXIS,
    d_DEST_DCA_VELOCITY,
    d_DEST_DCA_EG,
    d_DEST_DCA_AMP,
    d_DEST_DCA_PAN,
    // --- END OF LAYER 1 DESTINATIONS

    d_MAX_DESTINATIONS
};
struct ModMatrixRow
{
    // --- index of source
    int uSourceIndex;

    // --- index of destination
    int uDestinationIndex;

    // --- for GUI -> Control
    float dUIContolValue;

    // --- needs to default to 1.0 in case no GUI control
    std::atomic<float>* pModIntensity;    // <- "ucControl" in MMA DLS
    std::atomic<float>* pModRange;        // <- "lScale" in MMA DLS

    // --- transform on Source
    Transform uSourceTransform;

    // --- to easily turn on/off a modulation routing
    bool bEnable;
};

class ModMatrix{
    public:
    
    ModMatrixRow** m_ppMatrixCore;
    
        // --- current size depending on number of rows added
    int m_nSize;
    
        // sources: where each source (LFO, EG, ETC) writes its output value
    float m_dSources[s_MAX_SOURCES];

    // destinations: where the newly calculated mod values are read from
    float m_dDestinations[d_MAX_DESTINATIONS];
    
    // config changes
    inline void clearMatrix()
    {
        if(!m_ppMatrixCore) return;

        for(int i=0; i<(s_MAX_SOURCES * d_MAX_DESTINATIONS); i++)
        {
            m_ppMatrixCore[i] = NULL;
        }
    }
    
    inline void clearSources()
    {
        for(int i=0; i< s_MAX_SOURCES; i++)
        {
            m_dSources[i] = 0.0;
        }
    }

    // called on each pass through the matrix
    inline void clearDestinations()
    {
        for(int i=0; i<d_MAX_DESTINATIONS; i++)
        {
            m_dDestinations[i] = 0.0;
        }
    }
    
    inline void addModMatrixRow(ModMatrixRow* pRow)
        {
            if(!m_ppMatrixCore)
                createMatrixCore();
    
            // add if not already existing
            if(!matrixRowExists(pRow->uSourceIndex, pRow->uDestinationIndex))
            {
                m_ppMatrixCore[m_nSize] = pRow;
                m_nSize++;
            }
            else
                delete pRow;
        }
    
        // check for duplicate row
        inline bool matrixRowExists(UINT uSourceIndex, UINT uDestinationIndex)
        {
            if(!m_ppMatrixCore) return false;
    
            for(int i=0; i<m_nSize; i++)
            {
                ModMatrixRow* pRow = m_ppMatrixCore[i];
                
                // find matching source/destination pairs
                if(pRow->uSourceIndex == uSourceIndex && pRow->uDestinationIndex == uDestinationIndex)
                {
                    return true;
                }
            }
            return false;
        }
    
        inline void createMatrixCore()
        {
            if(m_ppMatrixCore)
                delete [] m_ppMatrixCore;
    
            // --- dynamic allocation of matrix core
            m_ppMatrixCore = new ModMatrixRow*[s_MAX_SOURCES * d_MAX_DESTINATIONS];
            memset(m_ppMatrixCore, 0, s_MAX_SOURCES * d_MAX_DESTINATIONS*sizeof(modMatrixRow*));
        }
    
        // thie deletes the pointer too!
        inline void deleteModMatrix()
        {
            if(!m_ppMatrixCore) return;
    
            for(int i=0; i<m_nSize; i++)
            {
                // delete pointer
                ModMatrixRow* pRow = m_ppMatrixCore[i];
                delete pRow;
                m_nSize--;
            }
            m_nSize = 0;
            delete [] m_ppMatrixCore;
            m_ppMatrixCore = NULL;
        }
        
        inline bool enableModMatrixRow(UINT uSourceIndex, int uDestinationIndex, bool bEnable)
        {
            if(!m_ppMatrixCore) return false;
    
            for(int i=0; i<m_nSize; i++)
            {
                ModMatrixRow* pRow = m_ppMatrixCore[i];
                
                // find matching source/destination pairs
                if(pRow->uSourceIndex == uSourceIndex && pRow->uDestinationIndex == uDestinationIndex)
                {
                    pRow->bEnable = bEnable;
                    return true; // found it
                }
            }
            return false;
        }
    
    // --- returns true for queried layer
        inline bool checkDestinationLayer(int uLayer, ModMatrixRow* pRow)
        {
            bool bLayer0 = false;
            if(pRow->uDestinationIndex >= DEST_LFO1_FO &&
               pRow->uDestinationIndex <= DEST_ALL_EG_SUSTAIN_OVERRIDE)
                // then, we are layer 0; see synthfunctions.h
                bLayer0 = true;
    
            if(uLayer == 0)
                return bLayer0;
    
            if(uLayer == 1)
                return !bLayer0;
    
            return false;
        }
    
    inline ModMatrixRow* createMatrixRow(int uSource, int uDestination, std::atomic<float>* pIntensity, std::atomic<float>* pRange, Transform uTransform, bool bEnable = true)
    {
        ModMatrixRow* pRow = new ModMatrixRow;
        pRow->uSourceIndex = uSource;
        pRow->uDestinationIndex = uDestination;
        pRow->pModIntensity = pIntensity; // 0->1
        pRow->pModRange = pRange;
        pRow->uSourceTransform = uTransform; // for AmpMod
        pRow->bEnable = bEnable; // on/off
        pRow->dUIContolValue = 0.0;
        return pRow;
    }
    
    
    // go through each row and transfer/accumulate sources into destinations
        // destination += source*intensity*range
        inline void doModulationMatrix(int uModLayer)
        {
            if(!m_ppMatrixCore) return;
    
            // clear dest registers
            clearDestinations();
    
            for(int i=0; i<m_nSize; i++)
            {
                // get the row
                ModMatrixRow* pRow = m_ppMatrixCore[i];
    
                // --- this should never happen!
                if(!pRow) continue;
    
                // --- if disabled, skip row
                if(!pRow->bEnable) continue;
    
                // --- check the mod layer
                if(!checkDestinationLayer(uModLayer, pRow)) continue;
    
                // get the source value
                double dSource = m_dSources[pRow->uSourceIndex];
    
                switch(pRow->uSourceTransform)
                {
                    case t_TRANSFORM_UNIPOLAR_TO_BIPOLAR:
                        dSource = unipolarToBipolar(dSource);
                        break;
                    
                    case t_TRANSFORM_BIPOLAR_TO_UNIPOLAR:
                        dSource = bipolarToUnipolar(dSource);
                        break;
                
                    case t_TRANSFORM_MIDI_TO_ATTENUATION:
                        dSource = mmaMIDItoAtten(dSource);
                        break;
                
                    case t_TRANSFORM_MIDI_TO_PAN:
                        dSource = midiToPanValue(dSource);
                        break;
    
                    case t_TRANSFORM_MIDI_SWITCH:
                        dSource = dSource > 63 ? 1.0 : 0.0;
                        break;
    
                    case t_TRANSFORM_MIDI_TO_BIPOLAR:
                        dSource = midiToBipolar(dSource);
                        break;
    
                    case t_TRANSFORM_NOTE_NUMBER_TO_FREQUENCY:
                        dSource = midiFreqTable[(UINT)dSource];
                        break;
                
                    case t_TRANSFORM_MIDI_NORMALIZE:
                        dSource/= 127.0; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
                        break;
                    
                    case t_TRANSFORM_INVERT_MIDI_NORMALIZE:
                        dSource/= 127.0; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
                        dSource = 1.0 - dSource; // 1->0 NOTE: MMA DLS uses divide-by-128 instead!, 0.9999->0
                        break;
    
                    default:
                        break;
                }
    
                // destination += source*intensity*range
                //
                double dModValue = dSource*(*pRow->pModIntensity)*(*pRow->pModRange);
    
                // first check DEST_ALL types
                switch(pRow->uDestinationIndex)
                {
                    case d_DEST_ALL_OSC_FO:
                        m_dDestinations[d_DEST_OSC1_FO] += dModValue;
                        m_dDestinations[d_DEST_OSC2_FO] += dModValue;
                        m_dDestinations[d_DEST_OSC3_FO] += dModValue;
                        m_dDestinations[d_DEST_OSC4_FO] += dModValue;
                        m_dDestinations[d_DEST_ALL_OSC_FO] += dModValue;
                        break;
    
                    case d_DEST_ALL_OSC_PULSEWIDTH:
                        m_dDestinations[d_DEST_OSC1_PULSEWIDTH] += dModValue;
                        m_dDestinations[d_DEST_OSC2_PULSEWIDTH] += dModValue;
                        m_dDestinations[d_DEST_OSC3_PULSEWIDTH] += dModValue;
                        m_dDestinations[d_DEST_OSC4_PULSEWIDTH] += dModValue;
                        m_dDestinations[d_DEST_ALL_OSC_PULSEWIDTH] += dModValue;
                        break;
                    
                    case d_DEST_ALL_OSC_FO_RATIO:
                        m_dDestinations[d_DEST_OSC1_FO_RATIO] += dModValue;
                        m_dDestinations[d_DEST_OSC2_FO_RATIO] += dModValue;
                        m_dDestinations[d_DEST_OSC3_FO_RATIO] += dModValue;
                        m_dDestinations[d_DEST_OSC4_FO_RATIO] += dModValue;
                        m_dDestinations[d_DEST_ALL_OSC_FO_RATIO] += dModValue;
                        break;
    
                    case d_DEST_ALL_OSC_OUTPUT_AMP:
                        m_dDestinations[d_DEST_OSC1_OUTPUT_AMP] += dModValue;
                        m_dDestinations[d_DEST_OSC2_OUTPUT_AMP] += dModValue;
                        m_dDestinations[d_DEST_OSC3_OUTPUT_AMP] += dModValue;
                        m_dDestinations[d_DEST_OSC4_OUTPUT_AMP] += dModValue;
                        m_dDestinations[d_DEST_ALL_OSC_OUTPUT_AMP] += dModValue;
                        break;
    
                    case d_DEST_ALL_LFO_FO:
                        m_dDestinations[d_DEST_LFO1_FO] += dModValue;
                        m_dDestinations[d_DEST_LFO2_FO] += dModValue;
                        m_dDestinations[d_DEST_ALL_LFO_FO] += dModValue;
                        break;
    
                    case d_DEST_ALL_LFO_OUTPUT_AMP:
                        m_dDestinations[d_DEST_LFO1_OUTPUT_AMP] += dModValue;
                        m_dDestinations[d_DEST_LFO2_OUTPUT_AMP] += dModValue;
                        m_dDestinations[d_DEST_ALL_LFO_OUTPUT_AMP] += dModValue;
                        break;
    
                    case d_DEST_ALL_FILTER_FC:
                        m_dDestinations[d_DEST_FILTER1_FC] += dModValue;
                        m_dDestinations[d_DEST_FILTER2_FC] += dModValue;
                        m_dDestinations[d_DEST_ALL_FILTER_FC] += dModValue;
                        break;
    
                    case d_DEST_ALL_FILTER_KEYTRACK:
                        m_dDestinations[d_DEST_FILTER1_KEYTRACK] += dModValue;
                        m_dDestinations[d_DEST_FILTER2_KEYTRACK] += dModValue;
                        m_dDestinations[d_DEST_ALL_FILTER_KEYTRACK] += dModValue;
                        break;
    
                    case d_DEST_ALL_EG_ATTACK_SCALING:
                        m_dDestinations[d_DEST_EG1_ATTACK_SCALING] += dModValue;
                        m_dDestinations[d_DEST_EG2_ATTACK_SCALING] += dModValue;
                        m_dDestinations[d_DEST_EG3_ATTACK_SCALING] += dModValue;
                        m_dDestinations[d_DEST_EG4_ATTACK_SCALING] += dModValue;
                        m_dDestinations[d_DEST_ALL_EG_ATTACK_SCALING] += dModValue;
                        break;
    
                    case d_DEST_ALL_EG_DECAY_SCALING:
                        m_dDestinations[d_DEST_EG1_DECAY_SCALING] += dModValue;
                        m_dDestinations[d_DEST_EG2_DECAY_SCALING] += dModValue;
                        m_dDestinations[d_DEST_EG3_DECAY_SCALING] += dModValue;
                        m_dDestinations[d_DEST_EG4_DECAY_SCALING] += dModValue;
                        m_dDestinations[d_DEST_ALL_EG_DECAY_SCALING] += dModValue;
                        break;
    
                    case d_DEST_ALL_EG_SUSTAIN_OVERRIDE:
                        m_dDestinations[d_DEST_EG1_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[d_DEST_EG2_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[d_DEST_EG3_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[d_DEST_EG4_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[d_DEST_ALL_EG_SUSTAIN_OVERRIDE] += dModValue;
                        break;
    
                    // for all "single" source/dest, this is the modulation
                    default:
                        m_dDestinations[pRow->uDestinationIndex] += dModValue;
                }
            }
        }
    
    private:
};
#endif /* ModMatrix_h */
