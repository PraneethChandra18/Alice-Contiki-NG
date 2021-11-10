#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#include <stdio.h>

#define UDP_PORT 61618

#define SEND_INTERVAL		(4 * CLOCK_SECOND)

static struct simple_udp_connection broadcast_connection;

/*---------------------------------------------------------------------------*/
PROCESS(udp_process, "UDP broadcast process");
AUTOSTART_PROCESSES(&udp_process);
/*---------------------------------------------------------------------------*/
static void
receiver(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
  static int msg;

  msg++;
  printf("Data %d received length %d\n",
         msg, datalen);
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_process, ev, data)
{
  static struct etimer periodic_timer;
  uip_ipaddr_t addr;
  static int alive;
  const uip_ipaddr_t *default_prefix;

  PROCESS_BEGIN();

  default_prefix = uip_ds6_default_prefix();
  uip_ip6addr_copy(&addr, default_prefix);
  addr.u16[4] = UIP_HTONS(0x202);
  addr.u16[5] = UIP_HTONS(2);
  addr.u16[6] = UIP_HTONS(2);
  addr.u16[7] = UIP_HTONS(2);
  uip_ds6_addr_add(&addr, 0, ADDR_AUTOCONF);

  simple_udp_register(&broadcast_connection, UDP_PORT,
                      NULL, UDP_PORT,
                      receiver);

  etimer_set(&periodic_timer, 20 * CLOCK_SECOND);
  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
  etimer_set(&periodic_timer, SEND_INTERVAL);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    etimer_reset(&periodic_timer);
    alive++;
    printf("Alive %d\n", alive);

    /*printf("Sending broadcast\n");
      uip_create_linklocal_allnodes_mcast(&addr);
      simple_udp_sendto(&broadcast_connection, "Test", 4, &addr);*/
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
