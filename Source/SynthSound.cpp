/*
  ==============================================================================

    SynthSound.cpp
    Created: 6 Oct 2021 7:08:08pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include "SynthSound.h"

bool SynthSound::appliesToNote(int midiNoteNumber){
    return true;
}
bool SynthSound::appliesToChannel (int midiChannel){
    return true;
}
