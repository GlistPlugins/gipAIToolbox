/*
 * gipAIToolbox.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Noyan Culum
*/

#ifndef SRC_GIPAITOOLBOX_H_
#define SRC_GIPAITOOLBOX_H_

#include "gBaseComponent.h"

#include "AIToolbox/Bandit/Experience.hpp"



class gipAIToolbox : public gBaseComponent{
public:
	gipAIToolbox();
	virtual ~gipAIToolbox();
};

#endif /* SRC_GIPAITOOLBOX_H_ */
