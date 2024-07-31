#include "protocol.h"
#include <zephyr/console/console.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/printk.h>


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 300

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)


// thread0 parameters
constexpr size_t thread0StackSize = 1024;
K_THREAD_STACK_DEFINE(/*sym*/ stack0_area, /*size*/ thread0StackSize);
struct k_thread thread0_data;
constexpr int thread0_priority = 7; // Numerically lower priorities takes precedence over numerically higher values.


/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);


static int gpio_init(void) {
	int ret;
	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	if(ret) {
		printk("E: gpio_init %d %d\n", __LINE__, ret);
		return ret;
	}
	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	if(ret) {
		printk("E: gpio_init %d %d\n", __LINE__, ret);
		return ret;
	}
	ret = gpio_is_ready_dt(&led0);
	if(ret) {
		printk("E: gpio_init %d %d\n", __LINE__, ret);
		return ret;
	}
	ret = gpio_is_ready_dt(&led1);
	if(ret) {
		printk("E: gpio_init %d %d\n", __LINE__, ret);
		return ret;
	}
	printk("I: gpio_init DONE\n");
	return 0;
}

void thread0Func(void *, void *, void *) {
	int cnt = 50;
	printk("I: thread0Func START\n");

	while(1) {
		// printk("I: thread0Func cnt=%d\n", cnt);
		gpio_pin_toggle_dt(&led1);

		// char *mem_ptr = reinterpret_cast<char*>(k_malloc(64));
		// printk("I: k_malloc %p\n", mem_ptr);
		// k_free(mem_ptr);

		k_msleep(500);

		if(--cnt == 0) {
			printk("I: thread0Func DONE\n");
			return;
		}
	}
}


int main(void) {
	int ret;

	/*
	https://docs.zephyrproject.org/latest/kernel/services/threads/index.html
	*/
	k_tid_t tid0 = k_thread_create(
		&thread0_data,
		stack0_area, // stack
		K_THREAD_STACK_SIZEOF(stack0_area), // stack_size in bytes
		thread0Func, // entry
		NULL, NULL, NULL,
		thread0_priority, // prio
		0, // options
		K_MSEC(1000)); // delay, K_NO_WAIT
	(void)tid0;

	while(1) {
		ret = gpio_pin_toggle_dt(&led0);
		if(ret < 0) {
			return 0;
		}
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}

SYS_INIT(gpio_init, APPLICATION, 90);
SYS_INIT(protocolInit, APPLICATION, 91);
