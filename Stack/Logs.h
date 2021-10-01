#ifndef LOGS_H_INCLUDED
#define LOGS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const char LOG_FILE_NAME[] = "Stack_log.txt";

void OpenLogs(void);
void CloseLogs(void);

#endif
