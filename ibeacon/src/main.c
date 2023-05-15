
#include <zephyr/types.h>
#include <stddef.h>
#include <sys/printk.h>
#include <sys/util.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

#pragma pack(1)
struct advertising_data
{
	uint8_t name[8];
	uint8_t age;
	uint8_t salary;
	uint8_t hightinfeet;
	uint8_t bloodgroup[1];
};
#pragma pack(0)

struct advertising_data adv_data = {
	.name = "Dushyant",
	.age = 100,
	.salary = 40,
	.hightinfeet = 53,
	.bloodgroup = 'A'
};
static const struct bt_data ad[] = {
	BT_DATA(0x15, &adv_data, sizeof(adv_data)),
};
const struct bt_le_adv_param param ={
	.id = 0,
	.sid = 0,
	.secondary_max_skip = 0,
	.options = BT_LE_ADV_OPT_USE_NAME, 
	.interval_min = 0x00a0,
	.interval_max = 0x00f0,
	.peer = (void *)0,
};
void update_the_ADV_data(uint8_t *name, uint8_t age, uint8_t salary, uint8_t hight, uint8_t *BG);
static void bt_ready(int err)
{
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("Bluetooth initialized\n");
	/* Start advertising */
	//err = bt_le_adv_start(BT_LE_ADV_NCONN, ad, ARRAY_SIZE(ad),NULL, 0);
	//err = bt_le_adv_start(BT_LE_ADV_NCONN_NAME, ad, ARRAY_SIZE(ad),NULL, 0);
	err = bt_le_adv_start(&param, ad, ARRAY_SIZE(ad),NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}
	printk("iBeacon started\n");
}

void main(void)
{
	int err;
	printk("Starting iBeacon Demo\n");
        update_the_ADV_data("Raunak",101,90,70,'B');
	err = bt_enable(bt_ready);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
	}
}

void update_the_ADV_data(uint8_t *name, uint8_t age, uint8_t salary, uint8_t hight, uint8_t *BG)
{
    strncpy((char *)adv_data.name, name, sizeof(adv_data.name) - 1);
    adv_data.age = age;
    adv_data.salary = salary;
    adv_data.hightinfeet = hight;
    adv_data.bloodgroup[0] = BG;
}
