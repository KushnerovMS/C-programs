#include "Logs.h"

FILE * Logs = nullptr;

void OpenLogs(void)
{
    Logs = fopen(LOG_FILE_NAME, "a");
    fprintf(Logs, "Built on: %s at %s\n\n", __DATE__, __TIME__);
    assert(Logs);
}

void CloseLogs(void)
{
    fclose(Logs);
}
