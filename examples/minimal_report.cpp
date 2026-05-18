#include <ReportServerInterface.h>

extern "C" int GetReportApiVersion() {
    return ReportServerInterface::GetApiVersion();
}

int main() {
    return ReportServerInterface::GetApiVersion() > 0 ? 0 : 1;
}
