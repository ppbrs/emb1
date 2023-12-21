#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 300

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

static int gpio_init(void) {
	int ret;

	if(!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	if(ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	if(ret < 0) {
		return 0;
	}
	printk("I: gpio_init DONE\n");
	return 0;
}

int main(void) {
	int ret;

	while(1) {
		ret = gpio_pin_toggle_dt(&led0);
		if(ret < 0) {
			return 0;
		}
		ret = gpio_pin_toggle_dt(&led1);
		if(ret < 0) {
			return 0;
		}
		k_msleep(SLEEP_TIME_MS);
		printk("D: toggle\n");
	}
	return 0;
}

SYS_INIT(gpio_init, APPLICATION, 90);
