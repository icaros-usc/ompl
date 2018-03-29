/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2008, Willow Garage, Inc.
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
*   * Neither the name of the Willow Garage nor the names of its
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

/* Author: Ioan Sucan */

#ifndef OMPL_GEOMETRIC_GENETIC_SEARCH_
#define OMPL_GEOMETRIC_GENETIC_SEARCH_

#include "ompl/base/SpaceInformation.h"
#include "ompl/base/goals/GoalRegion.h"
#include "ompl/geometric/HillClimbing.h"
#include "ompl/util/Console.h"

namespace ompl
{
    namespace geometric
    {
        /**
           @anchor GeneticSearch

           @par Short description

           GeneticSearch does search for valid states using a genetic algorithm

           @par External documentation
        */

        /** \brief Genetic Algorithm for searching valid states */
        class OMPL_EXPORT GeneticSearch
        {
        public:
            /** \brief Construct an instance of a genetic algorithm for inverse kinematics given the space information
             * to search within */
            GeneticSearch(const base::SpaceInformationPtr &si);
            ~GeneticSearch();

            /** \brief Find a state that fits the request */
            bool solve(double solveTime, const base::GoalRegion &goal, base::State *result,
                       const std::vector<base::State *> &hint = std::vector<base::State *>());

            /** \brief Set the number of steps to perform when using hill climbing to improve an individual in the
             * population */
            void setMaxImproveSteps(unsigned int maxSteps)
            {
                hc_.setMaxImproveSteps(maxSteps);
            }

            /** \brief Get the number of steps to perform when using hill climbing to improve an individual in the
             * population */
            unsigned int getMaxImproveSteps() const
            {
                return hc_.getMaxImproveSteps();
            }

            /** \brief Set the state validity flag; if this is false, states are not checked for validity */
            void setValidityCheck(bool valid)
            {
                checkValidity_ = valid;
                hc_.setValidityCheck(valid);
            }

            /** \brief Get the state validity flag; if this is false, states are not checked for validity */
            bool getValidityCheck() const
            {
                return checkValidity_;
            }

            /** \brief Set the flag that determines whether improvements using hill climbing should be attempted for
             * solutions generated by the genetic algorithm. */
            void setTryImprove(bool flag)
            {
                tryImprove_ = flag;
            }

            /** \brief Returns true if improvements using hill climbing should be attempted for solutions generated by
             * the genetic algorithm. Returns false otherwise. */
            bool getTryImprove() const
            {
                return tryImprove_;
            }

            /** \brief Set the number of individuals in the population */
            void setPoolSize(unsigned int size)
            {
                poolSize_ = size;
            }

            /** \brief Get the number number of individuals in the population */
            unsigned int getPoolSize() const
            {
                return poolSize_;
            }

            /** \brief Set the number of individuals to mutate at each generation. */
            void setPoolMutationSize(unsigned int size)
            {
                poolMutation_ = size;
            }

            /** \brief Get the number of individuals that are mutated at each generation */
            unsigned int getPoolMutationSize() const
            {
                return poolMutation_;
            }

            /** \brief Set the number of individuals to randomly sample at each generation */
            void setPoolRandomSize(unsigned int size)
            {
                poolRandom_ = size;
            }

            /** \brief Get the number of individuals to randomly sample at each generation */
            unsigned int getPoolRandomSize() const
            {
                return poolRandom_;
            }

            /** \brief Set the range (distance) to be used when sampling around a state */
            void setRange(double distance)
            {
                maxDistance_ = distance;
            }

            /** \brief Get the range GeneticSearch is using */
            double getRange() const
            {
                return maxDistance_;
            }

            /** \brief Clear the pool of samples */
            void clear();

        private:
            /** \brief Use hill climbing to attempt to get a state closer to the goal */
            void tryToImprove(const base::GoalRegion &goal, base::State *state, double distance);

            /** \brief Return true if the state is to be considered valid. This function always returns true if checking
             * of validity is disabled. */
            bool valid(const base::State *state) const
            {
                return checkValidity_ ? si_->isValid(state) : true;
            }

            struct OMPL_EXPORT Individual
            {
                base::State *state;
                double distance;
                bool valid;
            };

            struct OMPL_EXPORT IndividualSort
            {
                bool operator()(const Individual &a, const Individual &b)
                {
                    if (a.valid == b.valid)
                        return a.distance < b.distance;
                    return a.valid;
                }
            };

            HillClimbing hc_;
            base::SpaceInformationPtr si_;
            base::StateSamplerPtr sampler_;
            std::vector<Individual> pool_;
            unsigned int poolSize_;
            unsigned int poolMutation_;
            unsigned int poolRandom_;
            unsigned int generations_;
            bool checkValidity_;
            bool tryImprove_;

            double maxDistance_;
        };
    }
}

#endif
