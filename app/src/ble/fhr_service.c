#include "fhr_service.h"
#include <zephyr.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/gatt.h>
#include <string.h>

/* UUIDs from the project description */
static struct bt_uuid_128 fhr_svc_uuid = BT_UUID_INIT_128(
    0xf0,0xde,0xbc,0x9a,0x78,0x56,0x34,0x12,0x78,0x56,0x34,0x12,0x78,0x56,0x34,0x12);

static struct bt_uuid_128 fhr_measure_uuid = BT_UUID_INIT_128(
    0xf0,0xde,0xbc,0x9a,0x78,0x56,0x34,0x12,0x79,0x56,0x34,0x12,0x78,0x56,0x34,0x12);

static struct bt_uuid_128 fhr_ctrl_uuid = BT_UUID_INIT_128(
    0xf0,0xde,0xbc,0x9a,0x78,0x56,0x34,0x12,0x7a,0x56,0x34,0x12,0x78,0x56,0x34,0x12);

static uint16_t current_bpm = 0;
static uint8_t streaming_enabled = 0;

static struct bt_gatt_ccc_cfg fhr_ccc_cfg[BT_GATT_CCC_MAX] = {};

static void fhr_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    ARG_UNUSED(attr);
    ARG_UNUSED(value);
}

static ssize_t read_streaming(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                              void *buf, uint16_t len, uint16_t offset)
{
    const uint8_t *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value, sizeof(streaming_enabled));
}

static ssize_t write_streaming(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                               const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    ARG_UNUSED(conn);
    ARG_UNUSED(attr);
    ARG_UNUSED(offset);
    ARG_UNUSED(flags);

    if (len < 1) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    const uint8_t *v = buf;
    streaming_enabled = (*v) ? 1 : 0;
    return len;
}

BT_GATT_SERVICE_DEFINE(fhr_svc,
    BT_GATT_PRIMARY_SERVICE(&fhr_svc_uuid.uuid),
    BT_GATT_CHARACTERISTIC(&fhr_measure_uuid.uuid,
        BT_GATT_CHRC_NOTIFY,
        BT_GATT_PERM_NONE,
        NULL, NULL, &current_bpm),
    BT_GATT_CCC(fhr_ccc_cfg, fhr_ccc_cfg_changed),

    BT_GATT_CHARACTERISTIC(&fhr_ctrl_uuid.uuid,
        BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
        read_streaming, write_streaming, &streaming_enabled),
);

void fhr_init(void)
{
    /* nothing special for init in this minimal implementation */
}

void fhr_notify_measure(uint16_t bpm)
{
    current_bpm = bpm;
    bt_gatt_notify(NULL, &fhr_svc.attrs[1], &current_bpm, sizeof(current_bpm));
}

void fhr_set_streaming(bool enabled)
{
    streaming_enabled = enabled ? 1 : 0;
}

bool fhr_is_streaming(void)
{
    return streaming_enabled != 0;
}
