# Report SDK

This directory contains the exported public header set for report modules.

Sync command:

```bash
./tools/sync_report_sdk.sh
```

The command rebuilds:

- `sdk/report/include/ReportServerInterface.h`
- `sdk/report/include/Structures.h`
- `sdk/report/include/structures/*`
- `sdk/report/include/rapidjson/*`

The SDK is intentionally read-only and report-oriented. It does not export the full plugin mutation surface.

Example:

- `sdk/report/examples/minimal_report.cpp`

Notes:

- Public headers are synced directly from the product tree. Do not edit `sdk/report/include/*` manually.
- RapidJSON is exported under `sdk/report/include/rapidjson`, and public headers use `#include <rapidjson/...>`.
- Consumer include path should point to `sdk/report/include`.

Smoke-check:

```bash
./tools/check_sdk_headers.sh
```

This script re-syncs the SDKs and runs a syntax-only compile check for the SDK example files.
