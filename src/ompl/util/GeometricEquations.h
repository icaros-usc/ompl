/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2015, University of Toronto
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the University of Toronto nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Jonathan Gammell */

#ifndef OMPL_UTIL_GEOMETRIC_EQUATIONS
#define OMPL_UTIL_GEOMETRIC_EQUATIONS

#include "ompl/export.h"

namespace ompl
{
    /* A collection of general geometric equations. */

    /** \brief The Lebesgue measure (i.e., "volume") of an n-dimensional ball of given radius. */
    OMPL_EXPORT
    double nBallMeasure(unsigned int N, double r);

    /** \brief The Lebesgue measure (i.e., "volume") of an n-dimensional ball with a unit radius. */
    OMPL_EXPORT
    double unitNBallMeasure(unsigned int N);

    /** \brief The Lebesgue measure (i.e., "volume") of an n-dimensional prolate hyperspheroid (a symmetric
     * hyperellipse) given as the distance between the foci and the transverse diameter */
    OMPL_EXPORT
    double prolateHyperspheroidMeasure(unsigned int N, double dFoci, double dTransverse);
}  // ompl

#endif
