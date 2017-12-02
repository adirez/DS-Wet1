//
// Created by adire on 30-Nov-17.
//

#include "library1.h"
#include "Colosseum.h"
#include "iostream"

using std::cout;
using std::endl;

void *Init() {
    Colosseum *DS;
    try {
        DS = new Colosseum();
    } catch (...) {
        return NULL;
    }
    return DS;
}

StatusType AddTrainer(void *DS, int trainerID) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->addTrainer(trainerID);
    } catch (MemoryProblem &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyAlreadyExists &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType BuyGladiator(void *DS, int gladiatorID, int trainerID, int level) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->buyGladiator(gladiatorID, trainerID, level);
    } catch (MemoryProblem &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyAlreadyExists &e) {
        return FAILURE;
    } catch (KeyNotFound &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType FreeGladiator(void *DS, int gladiatorID) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->freeGladiator(gladiatorID);
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyNotFound &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType LevelUp(void *DS, int gladiatorID, int levelIncrease) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->levelUp(gladiatorID, levelIncrease);
    } catch (MemoryProblem &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyNotFound &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetTopGladiator(void *DS, int trainerID, int *gladiatorID) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        *gladiatorID = colosseum->getTopGladiator(trainerID);
    } catch (MemoryProblem &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyNotFound &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllGladiatorsByLevel(void *DS, int trainerID, int **gladiators, int *numOfGladiator){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->getAllGladiatorsByLevel(trainerID, numOfGladiator, gladiators);
    } catch (MemoryProblem &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyNotFound &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType UpgradeGladiator(void *DS, int gladiatorID, int upgradedID) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->updateGladiator(gladiatorID, upgradedID);
    } catch (MemoryProblem &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyNotFound &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType UpdateLevels(void *DS, int stimulantCode, int stimulantFactor){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->updateLevels(stimulantCode, stimulantFactor);
    } catch (MemoryProblem &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyNotFound &e) {
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void** DS){
    if (DS != NULL) {
        delete(((Colosseum*)*DS));
        *DS = NULL;
    }
}