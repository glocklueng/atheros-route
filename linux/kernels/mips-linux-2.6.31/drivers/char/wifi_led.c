#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>     /* kmalloc() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/cdev.h>
#include <asm/system.h>     /* cli(), *_flags */
#include <asm/uaccess.h>    /* copy_*_user */

#include <linux/slab.h>
#include <linux/device.h>


#include <linux/semaphore.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <asm/io.h>
#include <asm/div64.h>

#include <atheros.h>

#define	GPIO4	(0x1 << 4)
#define	GPIO13	(0x1 << 13)
#define	GPIO19	(0x1 << 19)
#define	GPIO21	(0x1 << 21)
#define	GPIO22	(0x1 << 22)

struct wifiled_dev{
    int column;
    int page;

    struct cdev cdev;
};

int led_major = 254;
int led_minor = 0;

static struct class *my_class;
struct wifiled_dev *led_device;

char test_data[]="wifiled";

void ath_gpio_out_val(int gpio, int val);
void ath_gpio_config_output(int gpio);
	
static void display_reg(void)
{
	u32 reg;

	ath_reg_rmw_clear(ATH_GPIO_OUT, 0x1<<13); 
	ath_reg_rmw_clear(ATH_GPIO_OUT_FUNCTION3, 0xff00<<0);
	ath_reg_rmw_set(ATH_GPIO_OUT_FUNCTION3,0x33<<8); 

	reg = ath_reg_rd(ATH_GPIO_OE);
	printk(KERN_WARNING "ATH_GPIO_OE:%x \n", reg);
}

static void lc65xx_init(void)
{
	/* pull down, lc65xx gpio5 pull up */
    ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO22);
	/* lc65xx reset */
	ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO19);
	mdelay(50);
	ath_reg_rmw_set(ATH_GPIO_OUT, GPIO19);
}

static int led_dri_write(
    struct file *filp,
    const char __user *buf,
    size_t count,
    loff_t *ppos)
{
    unsigned long err;
    char* kbuf;
    
    kbuf = kmalloc(count+1, GFP_KERNEL);    
    err = copy_from_user(kbuf, buf, count);

    if(strncmp(buf,"enable",6) == 0)
    {

    }
    else if(!strncmp(buf,"test_on", strlen("test_on")))
    {
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO4);
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO13);
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO21);
	}
    else if(!strncmp(buf,"test_off", strlen("test_off")))
    {
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO4);
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO13);
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO21);
	}
    else if(!strncmp(buf,"led1_on", strlen("led1_on")))
    {
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO4);
	}
    else if(!strncmp(buf,"led1_off", strlen("led1_off")))
    {
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO4);
	}
    else if(!strncmp(buf,"led2_on", strlen("led2_on")))
    {
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO13);
	}
    else if(!strncmp(buf,"led2_off", strlen("led2_off")))
    {
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO13);
	}
    else if(!strncmp(buf,"led3_on", strlen("led3_on")))
    {
		ath_reg_rmw_clear(ATH_GPIO_OUT_FUNCTION5, 0xffff<<8);
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO21);
	}
	else if(!strncmp(buf,"led3_off", strlen("led3_off")))
    {
		ath_reg_rmw_clear(ATH_GPIO_OUT_FUNCTION5, 0xffff<<8);
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO21);
	}
    else if(!strncmp(buf,"lc65xx_reset", strlen("lc65xx_reset")))
    {
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO19);
		mdelay(50);
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO19);
	}
	else if(!strncmp(buf,"sw2shell", strlen("sw2shell")))
    {
        ath_reg_rmw_set(ATH_GPIO_OUT, GPIO22);
	}
	else if(!strncmp(buf,"sw2at", strlen("sw2at")))
    {
        ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO22);
	}

    kfree(kbuf);

    return err ? -EINVAL : count;
}

#define REG_GET 0
#define REG_SET 1


struct file_operations wifiled_fops = {
    .owner = THIS_MODULE,
    .write = led_dri_write,
};

static void led_dri_setup_cdev(struct wifiled_dev *dev)
{
    int err; 
    int devno = MKDEV(led_major, led_minor);

    cdev_init(&dev->cdev, &wifiled_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add (&dev->cdev, devno, 1);
    /* Fail gracefully if need be */
    if (err)
        printk(KERN_NOTICE "Error %d adding wifiled", err);
}

static int w2m_gpio_init(void)
{
	unsigned int rddata;

	/* set GPIO as output and init */
	ath_reg_rmw_clear(ATH_GPIO_OE, GPIO4|GPIO13|GPIO19|GPIO21|GPIO22);

	/* set function1 */
	rddata = ath_reg_rd(ATH_GPIO_OUT_FUNCTION1);
	rddata = rddata & 0xffffff00;
	//rddata = rddata | ATH_GPIO_OUT_FUNCTION1_ENABLE_GPIO_4(0x00);
	ath_reg_wr(ATH_GPIO_OUT_FUNCTION4, rddata);

	/* set function3 */
	rddata = ath_reg_rd(ATH_GPIO_OUT_FUNCTION3);
	rddata = rddata & 0xffff00ff;
	ath_reg_wr(ATH_GPIO_OUT_FUNCTION3, rddata);

	/* set function4 */
	rddata = ath_reg_rd(ATH_GPIO_OUT_FUNCTION4);
	rddata = rddata & 0x00ffffff;
	ath_reg_wr(ATH_GPIO_OUT_FUNCTION4, rddata);

	/* set function5 */
	rddata = ath_reg_rd(ATH_GPIO_OUT_FUNCTION5);
	rddata = rddata & 0xff0000ff;
	ath_reg_wr(ATH_GPIO_OUT_FUNCTION5, rddata);

	ath_reg_rmw_clear(ATH_GPIO_OUT, GPIO4|GPIO13|GPIO19|GPIO21|GPIO22);

	/* lc65xx switch to shell */
	lc65xx_init();

	return 0;
}

static int __init led_dri_init(void)
{
    int result;
    dev_t dev = 0;

    printk(KERN_WARNING "wifiled: start\n");


    if (led_major) {
        dev = MKDEV(led_major, led_minor);
        result = register_chrdev_region(dev, 1, "wifiled");
    } else {
        result = alloc_chrdev_region(&dev, led_minor, 1,
                "wifiled");
        led_major = MAJOR(dev);
    }
    if (result < 0) {
        printk(KERN_WARNING "wifiled : can't get major %d\n", led_major);
        return result;
    }

    led_device = kmalloc(sizeof(struct wifiled_dev), GFP_KERNEL);
    if (!led_device) {
        result = -ENOMEM;
        goto fail;  /* Make this more graceful */
    }
    memset(led_device, 0, sizeof(struct wifiled_dev));

    led_dri_setup_cdev(led_device);

    my_class = class_create(THIS_MODULE,"wifi_led");
    if(IS_ERR(my_class))
    {
        printk(KERN_WARNING "wifi_led:failed in creating class.\n");
        return -1;
    }
    device_create(my_class,NULL,MKDEV(led_major, 0), NULL,"wifiled");

	/* gpio init for w2m */
	w2m_gpio_init();

    return 0; /* succeed */

fail:
    return result;
}

static void __exit led_module_cleanup(void)
{
    dev_t devno = MKDEV(led_major, led_minor);

    device_destroy(my_class, devno);
    class_destroy(my_class);

    /* Get rid of our char dev entries */
    if (led_device) {
        cdev_del(&led_device[0].cdev);
        kfree(led_device);
    }

    /* cleanup_module is never called if registering failed */
    unregister_chrdev_region(devno, 1);

    printk("Good-bye, wifi_led module was removed!\n");
}

module_init(led_dri_init);
module_exit(led_module_cleanup);

MODULE_LICENSE("GPL");
