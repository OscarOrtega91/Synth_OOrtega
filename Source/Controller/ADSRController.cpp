/*
  ==============================================================================

    ADSRController.cpp
    Created: 8 Oct 2021 7:49:14pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include "ADSRController.h"

void ADSRController::updateADSR(const float attack,  const float decay, const float release, const float sustain){
    
    params.attack=attack;
    params.decay=decay;
    params.release=release;
    params.sustain=sustain;
    
    setParameters(params);
}
