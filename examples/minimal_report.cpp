#include <ReportServerInterface.h>

int main() {
    return ReportServerInterface::GetApiVersion() > 0 ? 0 : 1;
}
