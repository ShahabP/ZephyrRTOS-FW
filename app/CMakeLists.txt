cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(fhr_monitor)

target_sources(app PRIVATE
    src/main.c
    src/ble/bas_service.c
    src/ble/fhr_service.c
    src/tasks/battery_task.c
    src/tasks/fhr_task.c
    src/sim/battery_sim.c
    src/sim/fhr_sim.c
)

target_include_directories(app PRIVATE src)
