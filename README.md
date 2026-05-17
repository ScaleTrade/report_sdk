# Report SDK

This directory contains the exported public header set for report modules.

Sync command:

```bash
./tools/sync_report_sdk.sh
```

Publish command:

```bash
./tools/publish_sdk.sh report
```

This command runs sync, smoke-check, creates a commit for `sdk/report` if the snapshot changed, and then pushes the SDK to the `report_sdk` remote with `git subtree`.

The command rebuilds:

- `sdk/report/include/ReportServerInterface.h`
- `sdk/report/include/Structures.h`
- `sdk/report/include/model/*`
- `sdk/report/include/rapidjson/*`

The SDK is intentionally read-only and report-oriented. It does not export the full plugin mutation surface.

Read-only report contract:

- `ReportServerInterface` is an abstract host interface, not a concrete runtime class
- report modules must not construct or store `ReportServerInterface` by value
- the host creates the runtime implementation and passes it to report entry points as `ReportServerInterface*`
- trade reads and calculations use `ReportTradeRecord`
- account, margin, and equity reads use `ReportAccountRecord`, `ReportMarginLevel`, and `ReportEquityRecord`
- symbol and group reads use `ReportSymbolRecord` and `ReportGroupRecord`
- `ReportGroupRecord::partial_close` mirrors the server group setting for partial-close permission; `0` means partial close is disabled for the group, non-zero means enabled
- `ReportGroupRecord::allow_sl_tp_slippage` mirrors the server group setting for SL/TP execution; `1` allows market-price slippage after SL/TP trigger, `0` closes exactly at the configured SL/TP level
- log and candle reads use `ReportServerLog` and `ReportCandleRecord`
- internal project `structures/*.hpp` are no longer the public report contract

Example:

- `sdk/report/examples/minimal_report.cpp`

Notes:

- Public headers are synced directly from the product tree. Do not edit `sdk/report/include/*` manually.
- RapidJSON is exported under `sdk/report/include/rapidjson`, and public headers use `#include <rapidjson/...>`.
- Consumer include path should point to `sdk/report/include`.
- `sdk_contract/report/*` is the canonical source for the exported report contracts; `sdk/report/include/model/*` is the synced snapshot.

Smoke-check:

```bash
./tools/check_sdk_headers.sh
```

This script re-syncs the SDKs and runs a syntax-only compile check for the SDK example files.
