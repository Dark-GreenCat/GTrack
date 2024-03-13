#include "power_hcl.h"

bool IsSleep;
bool IsStop;

void HCL_POWER_EnterSleepMode() {
    IsSleep = true;
    DEBUG("\n\n====== ENTER SLEEP MODE ======\n\n");
    HAL_SuspendTick();
    HAL_PWR_EnableSleepOnExit();

    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void HCL_POWER_EnterStopMode() {
    IsStop = true;
    DEBUG("\n\n====== ENTER STOP MODE ======\n\n");
    HAL_SuspendTick();

    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}
