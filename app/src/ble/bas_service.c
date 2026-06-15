#include "bas_service.h"
#include <zephyr.h>
#include <bluetooth/gatt.h>
#include <bluetooth/bluetooth.h>

static uint8_t battery_level = 100;
static struct bt_gatt_ccc_cfg bas_ccc_cfg[BT_GATT_CCC_MAX] = {};

static void bas_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    ARG_UNUSED(attr);
    ARG_UNUSED(value);
}

static ssize_t read_battery(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                            void *buf, uint16_t len, uint16_t offset)
{
    const uint8_t *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value, sizeof(battery_level));
}

BT_GATT_SERVICE_DEFINE(bas_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(0x180F)),
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(0x2A19),
        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
        BT_GATT_PERM_READ,
        read_battery, NULL, &battery_level),
    BT_GATT_CCC(bas_ccc_cfg, bas_ccc_cfg_changed),
);

void bas_init(void)
{
    /* nothing to init for this minimal example */
}

void bas_set_level(uint8_t level)
{
    battery_level = level;
}

void bas_notify_level(void)
{
    /* attribute 2 is the characteristic value in the service definition */
    bt_gatt_notify(NULL, &bas_svc.attrs[2], &battery_level, sizeof(battery_level));
}
