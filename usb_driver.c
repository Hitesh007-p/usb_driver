#include <linux/usb.h>
#include <linux/module.h>

static struct usb_device *device; 

static struct usb_device_id usb_table[] = {
    { USB_DEVICE(0xcb32, 0x132f) },
    { } 
};
MODULE_DEVICE_TABLE(usb, usb_table);

static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;

    iface_desc = interface->cur_altsetting;
    printk(KERN_INFO "Pen i/f %d now probed: (%04x:%04x)\n",
           iface_desc->desc.bInterfaceNumber,
           id->idVendor, id->idProduct);
    printk(KERN_INFO "ID->bNumEndpoints: %02X\n",
           iface_desc->desc.bNumEndpoints);
    printk(KERN_INFO "ID->bInterfaceClass: %02X\n",
           iface_desc->desc.bInterfaceClass);

    for (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
        endpoint = &iface_desc->endpoint[i].desc;
        printk(KERN_INFO "Endpoint address: %02X\n", endpoint->bEndpointAddress);
        printk(KERN_INFO "Endpoint attributes: %02X\n", endpoint->bmAttributes);
        printk(KERN_INFO "Endpoint max packet size: %02X\n", endpoint->wMaxPacketSize);
    }

    device = interface_to_usbdev(interface);
    return 0;
}

static void usb_disconnect(struct usb_interface *interface)
{
    struct usb_device *dev = usb_get_intfdata(interface);
    usb_put_dev(dev);
    dev_info(&interface->dev, "USB device disconnected\n");
}

static struct usb_driver usb_driver = {
    .name = "usb_driver",
    .id_table = usb_table,
    .probe = usb_probe,
    .disconnect = usb_disconnect,
    .supports_autosuspend = 1, 
};

static int __init usb_init(void)
{
    int result;
    result = usb_register(&usb_driver);
    if (result < 0) {
        pr_err("usb registration failed with %d\n", result);
        return result;  // Return the error code
    }
    printk(KERN_INFO "USB driver registered\n");
    return 0;
}

module_init(usb_init);

static void __exit usb_exit(void)
{
    usb_deregister(&usb_driver);
    printk(KERN_INFO "USB driver deregistered\n");
}

module_exit(usb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hitesh");
MODULE_DESCRIPTION("USB Driver");
