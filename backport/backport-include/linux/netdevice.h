#ifndef __BACKPORT_NETDEVICE_H
#define __BACKPORT_NETDEVICE_H
#include_next <linux/netdevice.h>
#include <linux/netdev_features.h>
#include <linux/version.h>

/* older kernels don't include this here, we need it */
#include <linux/ethtool.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0))
#define netdev_set_default_ethtool_ops LINUX_BACKPORT(netdev_set_default_ethtool_ops)
extern void netdev_set_default_ethtool_ops(struct net_device *dev,
					   const struct ethtool_ops *ops);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
#define __dev_addr_sync LINUX_BACKPORT(__dev_addr_sync)
extern int __dev_addr_sync(struct dev_addr_list **to, int *to_count, struct dev_addr_list **from, int *from_count);
#define __dev_addr_unsync LINUX_BACKPORT(__dev_addr_unsync)
extern void __dev_addr_unsync(struct dev_addr_list **to, int *to_count, struct dev_addr_list **from, int *from_count);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0)
/*
 * BQL was added as of v3.3 but some Linux distributions
 * have backported BQL to their v3.2 kernels or older. To
 * address this we assume that they also enabled CONFIG_BQL
 * and test for that here and simply avoid adding the static
 * inlines if it was defined
 */
#ifndef CONFIG_BQL
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,26))
static inline void netdev_tx_sent_queue(struct netdev_queue *dev_queue,
					unsigned int bytes)
{
}
#endif

static inline void netdev_sent_queue(struct net_device *dev, unsigned int bytes)
{
}

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,26))
static inline void netdev_tx_completed_queue(struct netdev_queue *dev_queue,
					     unsigned pkts, unsigned bytes)
{
}
#endif

static inline void netdev_completed_queue(struct net_device *dev,
					  unsigned pkts, unsigned bytes)
{
}

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,26))
static inline void netdev_tx_reset_queue(struct netdev_queue *q)
{
}
#endif

static inline void netdev_reset_queue(struct net_device *dev_queue)
{
}
#endif /* CONFIG_BQL */
#endif /* < 3.3 */

#endif /* __BACKPORT_NETDEVICE_H */
