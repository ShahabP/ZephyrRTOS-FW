# FHR Monitor (Zephyr) — Simple Example

Overview
- A minimal Zephyr RTOS firmware project for Nordic nRF52840 simulating a wearable fetal heart rate (FHR) monitor.
- Implements a Standard Battery Service (BAS) and a custom Fetal Heart Rate Service (FHR).

Architecture
- app/src/
  - main.c — bluetooth init, advertising and connection handling
  - ble/ — BLE services
    - bas_service.{c,h} — Battery service (read + notify)
    - fhr_service.{c,h} — Custom FHR service (measurement notify, streaming control)
  - sim/ — simple simulators
    - battery_sim.{c,h} — battery level simulation
    - fhr_sim.{c,h} — fhr value generator
  - tasks/ — RTOS threads
    - battery_task.{c,h} — decreases battery every 60s and notifies
    - fhr_task.{c,h} — generates FHR every second and notifies if streaming enabled

BLE Services
- Device name: FHR_MONITOR (set in `prj.conf`)
- Battery Service (UUID 0x180F)
  - Battery Level (0x2A19): uint8_t, read + notify. Decreases every 60s.
- FHR Service (custom 128-bit UUIDs from spec)
  - FHR Measurement: uint16_t bpm, notify, generated 140–160 bpm while streaming
  - Streaming Control: uint8_t (0 = stop, 1 = start), read/write

Build
Prerequisites: Zephyr SDK and West setup per Zephyr docs.

From repository root:
```bash
cd app
west build -b nrf52840dk_nrf52840 .
```

Flash
```bash
west flash
```

Testing
- Unit tests use Zephyr `ztest`. From repository root:
```bash
cd app
west build -b native_posix tests
west run
```

CI/CD
- A GitHub Actions workflow is provided at `.github/workflows/ci.yml`.
- It runs on push and pull_request, installs Zephyr, runs `clang-format` (dry run), `cppcheck`, builds for `nrf52840dk_nrf52840`, and uploads `zephyr.hex` and `zephyr.bin` as artifacts.

Assumptions & Notes
- Implementation is intentionally small and straightforward to be easy to read and adapt.
- Uses simple pseudo-random `rand()` for FHR generation.
- The BAS and FHR services are implemented with the Zephyr GATT helpers; production code should include error handling, power management, and secure handling of BLE writes.

Future Improvements
- Use Zephyr random APIs and seed properly.
- Add real sensor integration and smoothing filters.
- Add authenticated pairing and security.
- Add more comprehensive unit and integration tests.
