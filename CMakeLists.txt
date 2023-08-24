cmake_minimum_required (VERSION 3.19.0)

##### PLUGIN NAME #####
set(pluginname gipAIToolbox)


##### PLUGIN PATHS #####
set(PLUGIN_DIR ${PLUGINS_DIR}/${pluginname})
set(PLUGIN_LIBS_DIR ${PLUGIN_DIR}/libs)


##### PLUGIN SOURCES #####
list(APPEND PLUGIN_SRCS
			${PLUGIN_DIR}/src/gipAIToolbox.cpp
			${PLUGIN_LIBS_DIR}/src/Utils/Adam.cpp
			${PLUGIN_LIBS_DIR}/src/Utils/Combinatorics.cpp
			${PLUGIN_LIBS_DIR}/src/Utils/Probability.cpp
			${PLUGIN_LIBS_DIR}/src/Utils/Polytope.cpp
			${PLUGIN_LIBS_DIR}/src/Utils/StorageEigen.cpp			
			${PLUGIN_LIBS_DIR}/src/Tools/Statistics.cpp			
			${PLUGIN_LIBS_DIR}/src/Bandit/Experience.cpp
			${PLUGIN_LIBS_DIR}/src/Bandit/Policies/EpsilonPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Bandit/Policies/RandomPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Bandit/Policies/QGreedyPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Bandit/Policies/QSoftmaxPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Bandit/Policies/ThompsonSamplingPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Impl/CassandraParser.cpp
			${PLUGIN_LIBS_DIR}/src/Impl/Seeder.cpp
			${PLUGIN_LIBS_DIR}/src/Bandit/Policies/LRPPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Bandit/Policies/ESRLPolicy.cpp			
			${PLUGIN_LIBS_DIR}/src/MDP/SparseModel.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/IO.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Model.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Experience.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/SparseExperience.cpp	
			${PLUGIN_LIBS_DIR}/src/MDP/Utils.cpp		
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/QLearning.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/RLearning.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/DoubleQLearning.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/HystereticQLearning.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/SARSA.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/ExpectedSARSA.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/SARSAL.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/ValueIteration.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/PolicyIteration.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Algorithms/Utils/OffPolicyTemplate.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/PolicyWrapper.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/Policy.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/EpsilonPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/QPolicyInterface.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/QGreedyPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/QSoftmaxPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/WoLFPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Policies/PGAAPPPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/MDP/Environments/Utils/GridWorld.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Utils.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/IO.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/AMDP.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/GapMin.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/SARSOP.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/IncrementalPruning.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/LinearSupport.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/PBVI.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/PERSEUS.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/BlindStrategies.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/FastInformedBound.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/QMDP.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Algorithms/Witness.cpp
			${PLUGIN_LIBS_DIR}/src/POMDP/Policies/Policy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Utils/Trie.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Utils/FasterTrie.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Utils/Core.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Utils/FactoredMatrix.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Utils/FactoredVectorOps.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Utils/FactoredMatrix2DOps.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Utils/BayesianNetwork.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Algorithms/Utils/VariableElimination.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Algorithms/Utils/MaxPlus.cpp			
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Algorithms/Utils/MultiObjectiveVariableElimination.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Algorithms/Utils/UCVE.cpp		
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Experience.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Policies/QGreedyPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Policies/SingleActionPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Policies/RandomPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Policies/EpsilonPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Policies/ThompsonSamplingPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Policies/LLRPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/Bandit/Policies/MAUCEPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Utils/LP/LpSolveWrapper.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/CooperativeExperience.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/CooperativeMaximumLikelihoodModel.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/CooperativeThompsonModel.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/CooperativeModel.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Utils.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Policies/EpsilonPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Policies/QGreedyPolicy.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Algorithms//Utils/FactoredLP.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Algorithms/Utils/CPSQueue.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Algorithms/SparseCooperativeQLearning.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Algorithms/CooperativeQLearning.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Algorithms/JointActionLearner.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Algorithms/LinearProgramming.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Environments/SysAdminRing.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Environments/SysAdminGrid.cpp
			${PLUGIN_LIBS_DIR}/src/Factored/MDP/Environments/TigerAntelope.cpp
)


##### PLUGIN HEADERS #####
list(APPEND PLUGIN_INCLUDES
			${PLUGIN_DIR}/src
			${PLUGIN_LIBS_DIR}/include	
			${PLUGIN_LIBS_DIR}/include/AIToolbox			
			${PLUGIN_LIBS_DIR}/include/boost
			${PLUGIN_LIBS_DIR}/include/eigen
			${PLUGIN_LIBS_DIR}/include/eigen/Eigen/src
			${PLUGIN_LIBS_DIR}/include/lpsolve
			)


##### PLUGIN DEPENDENCY LOCATIONS (IF ANY) #####
if(WIN32)
	list(APPEND PLUGIN_LINKDIRS
				${PLUGIN_LIBS_DIR}/lib/win32
				${PLUGIN_LIBS_DIR}/bin
	)
	
	#set(PLUGIN_LIBDIRS ${PLUGIN_LIBS_DIR}/lib/win32)
	list(APPEND PLUGIN_LIBDIRS
				${PLUGIN_LIBS_DIR}/lib/win32
	)
elseif(LINUX)
	#Linux libs here
elseif(APPLE)
	#Macos libs here
endif(WIN32)


##### PLUGIN DEPENDENCY LINKING (IF ANY) #####					
if(WIN32)
	list(APPEND PLUGIN_LINKLIBS
			lpsolve55
	)
elseif(LINUX)
	list(APPEND PLUGIN_LINKLIBS
				#Lib names
	)
elseif(APPLE)
	list(APPEND PLUGIN_LINKLIBS
				#Lib names
	)
endif(WIN32)
    