#include "bossAI.h"
#include "bossAction.h"
#include "playerMovement.h"

BOSS boss{
	1050,		//posX
	150,		//posY
	1350,		//posX2
	704,		//posY2
	0			//actType
};

void bossAction() {
	switch (boss.actType) {
	case IDLE:
		HandleIdleState();
		break;

	case ATTACKING:
		HandleAttackingState();
		break;

	default:
		break;
	}
}