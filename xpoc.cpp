#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include<netdb.h> 
#include<string.h> 
#include<unistd.h> 
#include<netinet/in.h> 
#include<fcntl.h> 
#include<time.h> 
#include<sys/types.h>
#include <pthread.h>
#include <net/if.h>
#include <errno.h>
#include <assert.h>

/*
<4>ip_setsockopt.....
<4>do_ip_setsockopt.....
<4>setsockopt Group....
<4>ip_setsockopt.....
<4>do_ip_setsockopt.....
<4>MCAST_JOIN_GROUP.....
<4>MCAST_JOIN_GROUP222.....
<4>MCAST_JOIN_GROU3333.....
<4>MCAST_JOIN_GROU444444.....
<4>ip_mc_join_group.....
<4>ip_mc_join_group addr : a0a02e0.....
<4>ip_mc_join_group2222.....
<4>accept4 1111...
<4>accept4 22222...
<4>accept4 33333...
<4>accept4 4444444...
<4>accept4 555555...
<4>accept4 666666...
<4>accept4 7777777...
<4>accept4 8888....
<4>accept4 9999....
<4>inet_csk_reqsk_queue_hash_add .....
<4>CPU: 0 PID: 1561 Comm: poc Not tainted 3.18.0+ #42
<4>Hardware name: ranchu (DT)
<0>Call trace:
<4>[<ffffffc0000897f0>] dump_backtrace+0x0/0x124
<4>[<ffffffc000089924>] show_stack+0x10/0x1c
<4>[<ffffffc000569734>] dump_stack+0x74/0xb8
<4>[<ffffffc0004854f8>] inet_csk_reqsk_queue_hash_add+0x30/0x140
<4>[<ffffffc000493c2c>] tcp_conn_request+0x554/0x6a0
<4>[<ffffffc00049bbbc>] tcp_v4_conn_request+0x70/0x7c
<4>[<ffffffc000492b68>] tcp_rcv_state_process+0x18c/0xcfc
<4>[<ffffffc00049acb8>] tcp_v4_do_rcv+0x8c/0x380
<4>[<ffffffc00049d5d0>] tcp_v4_rcv+0x7e8/0x7fc
<4>[<ffffffc000478fc0>] ip_local_deliver_finish+0xf4/0x298
<4>[<ffffffc00047963c>] ip_local_deliver+0xac/0xc4
<4>[<ffffffc0004791d4>] ip_rcv_finish+0x70/0x310
<4>[<ffffffc00047990c>] ip_rcv+0x2b8/0x3e8
<4>[<ffffffc0004122e8>] __netif_receive_skb_core+0x26c/0x74c
<4>[<ffffffc000412d88>] __netif_receive_skb+0x28/0x84
<4>[<ffffffc0004135cc>] process_backlog+0x94/0x17c
<4>[<ffffffc000417e2c>] net_rx_action+0x138/0x194
<4>[<ffffffc00009e394>] __do_softirq+0x110/0x268
<4>[<ffffffc00009e5a4>] do_softirq+0x5c/0x68
<4>[<ffffffc00009e660>] __local_bh_enable_ip+0xb0/0xd0
<4>[<ffffffc00047e790>] ip_finish_output+0x244/0x8a4
<4>[<ffffffc00047f108>] ip_output+0xbc/0xcc
<4>[<ffffffc00047d6b8>] ip_local_out_sk+0x38/0x48
<4>[<ffffffc00047d9f4>] ip_queue_xmit+0x118/0x38c
<4>[<ffffffc0004957c4>] tcp_transmit_skb+0x3d4/0x94c
<4>[<ffffffc0004989ec>] tcp_connect+0x8c0/0x9b0
<4>[<ffffffc00049a410>] tcp_v4_connect+0x240/0x3e8
<4>[<ffffffc0004b1360>] __inet_stream_connect+0x104/0x360
<4>[<ffffffc0004b15f4>] inet_stream_connect+0x38/0x58
<4>[<ffffffc0003fed54>] SyS_connect+0xd8/0x100
<4>accept4 1111...
<4>accept4 22222...
<4>accept4 33333...
<4>accept4 4444444...
<4>accept4 555555...
<4>accept4 666666...
<4>accept4 7777777...
<4>accept4 8888....
<4>accept4 9999....
<4>Hardware name: ranchu (DT)
<4>task: ffffffc016a1d240 ti: ffffffc01c5d8000 task.ti: ffffffc01c5d8000
<4>PC is at ip_mc_leave_src+0x28/0xa8
<4>LR is at ip_mc_drop_socket+0x60/0xac
<4>pc : [<ffffffc0004b3a4c>] lr : [<ffffffc0004b60d0>] pstate: 60000145
<4>sp : ffffffc01c5dbd60
<4>x29: ffffffc01c5dbd60 x28: ffffffc01c5d8000 
<4>x27: ffffffc00070d000 x26: 0000000000000039 
<4>x25: 0000000000000119 x24: ffffffc02d50ea10 
<4>x23: ffffffc000737900 x22: ffffffc03cbf0700 
<4>x21: ffffffc03cbf0700 x20: ffffffc03cad0dc0 
<4>x19: 000000736b636f4c x18: 00000000068528ac 
<4>x17: 000000736b269d4c x16: ffffffc00016f168 
<4>x15: 001dcd6500000000 x14: 0000000000000000 
<4>x13: 2074656b636f735f x12: 7265767265735f77 
<4>x11: 0000000000000000 x10: 000000000000000a 
<4>x9 : ae01b9db5c3c4424 x8 : 0000000000000039 
<4>x7 : ffffffc000751530 x6 : 0000000000000000 
<4>x5 : 0000000000000000 x4 : ffffffc01c5dbd20 
<4>x3 : 0000000000000000 x2 : 00000000656b6157 
<4>x1 : ffffffc03cad0dc0 x0 : 0000000000000000 
<4>
<4>PC: 0xffffffc0004b39cc:
<4>39cc  a9446bf9 a8c77bfd d65f03c0 aa1303e0 97fffad1 2a160000 34fffe60 f9400260
<4>39ec  97fffebe 17fffff0 8b37ce61 f9401020 128002b5 b4fffd80 d1000400 f9001020
<4>3a0c  17ffffc0 52800015 52800016 17ffffd1 12800240 17ffffac a9bd7bfd 910003fd
<4>3a2c  a90153f3 a9025bf5 aa0103f4 aa0003f5 f9400c33 aa0203e0 b9401422 b4000313
<4>3a4c  b9400663 91006264 91002021 52800005 97ffff7f 2a0003f6 aa1303e0 f9000e9f
<4>3a6c  910462a3 b8408413 91001a73 531e7673 885f7c61 4b130021 88027c61 35ffffa2
<4>3a8c  d2800101 97f0c806 2a1603e0 a94153f3 a9425bf5 a8c37bfd d65f03c0 91002021
<4>3aac  52800003 d2800004 52800005 97ffff68 a94153f3 a9425bf5 a8c37bfd d65f03c0
<4>
<4>LR: 0xffffffc0004b6050:
<4>6050  1a9f27f3 97f0adad 17fffff1 52800013 97f0adaa 17ffffee 52800003 17ffffe5
<4>6070  a9bc7bfd 910003fd a90153f3 a9025bf5 f9001bf7 f9417401 b4000401 aa0003f6
<4>6090  97fdca67 b0001417 910462d4 912402f7 f94176d3 b4000313 f9400261 aa1703e0
<4>60b0  f90176c1 b9401261 97ffe271 aa0003f5 aa1303e1 aa1603e0 aa1503e2 97fff656
<4>60d0  aa1503e0 b4000075 b9400a61 97fffb41 885f7e80 5100c000 88017e80 35ffffa1
<4>60f0  d2800401 8b010260 97f0be6c f94176d3 b5fffd53 97fdca5a a94153f3 a9425bf5
<4>6110  f9401bf7 a8c47bfd d65f03c0 f9401004 53003c63 b4000564 52800020 72b3c6e0
<4>6130  1b007c20 53177c00 f8605884 b5000084 1400001c f9401c84 b4000344 b9400880
<4>
<4>SP: 0xffffffc01c5dbce0:
<4>bce0  3cad0dc0 ffffffc0 3cbf0700 ffffffc0 3cbf0700 ffffffc0 00737900 ffffffc0
<4>bd00  2d50ea10 ffffffc0 00000119 00000000 00000039 00000000 0070d000 ffffffc0
<4>bd20  1c5d8000 ffffffc0 1c5dbd60 ffffffc0 004b60d0 ffffffc0 1c5dbd60 ffffffc0
<4>bd40  004b3a4c ffffffc0 60000145 00000000 1c5dbd70 ffffffc0 004aeaac ffffffc0
<4>bd60  1c5dbd90 ffffffc0 004b60d0 ffffffc0 3cad0dc0 ffffffc0 3cbf0818 ffffffc0
<4>bd80  00000000 00000000 3cbf0700 ffffffc0 1c5dbdd0 ffffffc0 004b0334 ffffffc0
<4>bda0  3cbf0700 ffffffc0 20d49680 ffffffc0 00000000 00000000 3e816520 ffffffc0
<4>bdc0  20c710c0 ffffffc0 2d50ea10 ffffffc0 1c5dbe00 ffffffc0 003fd8e4 ffffffc0
<4>
<4>X1: 0xffffffc03cad0d40:
<4>0d40  3cad0ec0 ffffffc0 00000000 00000000 00000000 00000000 00000000 00000000
<4>0d60  3cad0ee0 ffffffc0 00000020 00000000 00000000 00000000 00000000 00000000
<4>0d80  00000000 00000000 00000200 dead0000 00000002 00000000 00000000 00000000
<4>0da0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>0dc0  3cad0a00 ffffffc0 72656761 76726553 2e656369 656b6157 6b636f4c 00000073
<4>0de0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>0e00  168c0d10 ffffffc0 18ad13f0 ffffffc0 168c0d88 ffffffc0 168c0d88 ffffffc0
<4>0e20  00000001 00000000 00000000 00000000 3cad0460 ffffffc0 00000003 00000000
<4>
<4>X4: 0xffffffc01c5dbca0:
<4>bca0  65735f77 72657672 636f735f 2074656b 00000000 00000000 00000000 001dcd65
<4>bcc0  0016f168 ffffffc0 6b269d4c 00000073 068528ac 00000000 6b636f4c 00000073
<4>bce0  3cad0dc0 ffffffc0 3cbf0700 ffffffc0 3cbf0700 ffffffc0 00737900 ffffffc0
<4>bd00  2d50ea10 ffffffc0 00000119 00000000 00000039 00000000 0070d000 ffffffc0
<4>bd20  1c5d8000 ffffffc0 1c5dbd60 ffffffc0 004b60d0 ffffffc0 1c5dbd60 ffffffc0
<4>bd40  004b3a4c ffffffc0 60000145 00000000 1c5dbd70 ffffffc0 004aeaac ffffffc0
<4>bd60  1c5dbd90 ffffffc0 004b60d0 ffffffc0 3cad0dc0 ffffffc0 3cbf0818 ffffffc0
<4>bd80  00000000 00000000 3cbf0700 ffffffc0 1c5dbdd0 ffffffc0 004b0334 ffffffc0
<4>
<4>X7: 0xffffffc0007514b0:
<4>14b0  00000000 00000000 00000000 00000000 00000000 00000000 3e803400 ffffffc0
<4>14d0  00000000 00000000 3e824000 ffffffc0 3e824080 ffffffc0 3e814ec0 ffffffc0
<4>14f0  3e824040 ffffffc0 3e803600 ffffffc0 3e803800 ffffffc0 3e803a00 ffffffc0
<4>1510  3e803c00 ffffffc0 3e803e00 ffffffc0 00000000 00000000 3ffd9000 ffffffc0
<4>1530  00000000 00000000 00000000 00000000 3e8e6980 ffffffc0 00000001 00000000
<4>1550  008d008d 00000000 3e870bc0 ffffffc0 3e804600 ffffffc0 00010001 00000000
<4>1570  00718138 ffffffc0 3e828580 ffffffc0 00000000 00000000 3e801d80 ffffffc0
<4>1590  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>
<4>X16: 0xffffffc00016f0e8:
<4>f0e8  f90013f5 aa0003f3 aa0103f5 f9401c02 b40002e2 f9401402 f9403842 b4000242
<4>f108  d63f0040 2a0003f4 b9404660 377000e0 aa1303e0 aa1503e1 9400fc33 aa1303e0
<4>f128  aa1503e1 94012946 aa1303e0 94000af9 2a1403e0 a94153f3 f94013f5 a8c37bfd
<4>f148  d65f03c0 52800014 17fffff0 f0002800 9105c000 940fe74b 52800000 17fffff6
<4>f168  a9bf7bfd 910003e1 910003fd 9272c422 2a0003e1 f9400840 f944c400 940079b1
<4>f188  11080401 7100043f 54000109 121e7801 93407c00 3108103f 92800061 9a811000
<4>f1a8  a8c17bfd d65f03c0 92800060 a8c17bfd d65f03c0 a9bf7bfd 52800340 910003fd
<4>f1c8  97fcd091 53001c00 340000a0 94067d99 d2800000 a8c17bfd d65f03c0 92800000
<4>
<4>X20: 0xffffffc03cad0d40:
<4>0d40  3cad0ec0 ffffffc0 00000000 00000000 00000000 00000000 00000000 00000000
<4>0d60  3cad0ee0 ffffffc0 00000020 00000000 00000000 00000000 00000000 00000000
<4>0d80  00000000 00000000 00000200 dead0000 00000002 00000000 00000000 00000000
<4>0da0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>0dc0  3cad0a00 ffffffc0 72656761 76726553 2e656369 656b6157 6b636f4c 00000073
<4>0de0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>0e00  168c0d10 ffffffc0 18ad13f0 ffffffc0 168c0d88 ffffffc0 168c0d88 ffffffc0
<4>0e20  00000001 00000000 00000000 00000000 3cad0460 ffffffc0 00000003 00000000
<4>
<4>X21: 0xffffffc03cbf0680:
<4>0680  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>06a0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>06c0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>06e0  3cbf0700 ffffffc0 00000000 00000000 00000000 00000000 00000000 00000000
<4>0700  00000000 00000000 00000000 1a0a0000 000a0002 00000000 00000000 00000000
<4>0720  3cad0960 ffffffc0 00740320 ffffffc0 00000000 00000000 00000000 00000000
<4>0740  00000000 00000000 00000000 00000000 40000015 00000000 007ba428 ffffffc0
<4>0760  ffffffff 00000001 000c000c 00000000 00000000 00000000 3cbf0778 ffffffc0
<4>
<4>X22: 0xffffffc03cbf0680:
<4>0680  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>06a0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>06c0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>06e0  3cbf0700 ffffffc0 00000000 00000000 00000000 00000000 00000000 00000000
<4>0700  00000000 00000000 00000000 1a0a0000 000a0002 00000000 00000000 00000000
<4>0720  3cad0960 ffffffc0 00740320 ffffffc0 00000000 00000000 00000000 00000000
<4>0740  00000000 00000000 00000000 00000000 40000015 00000000 007ba428 ffffffc0
<4>0760  ffffffff 00000001 000c000c 00000000 00000000 00000000 3cbf0778 ffffffc0
<4>
<4>X23: 0xffffffc000737880:
<4>7880  00034000 00040000 00040000 00000000 00000080 00000000 00000000 00000000
<4>78a0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>78c0  00000010 00000000 00000001 00000000 007378d0 ffffffc0 007378d0 ffffffc0
<4>78e0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>7900  00000001 00000001 00020002 00000000 00738910 ffffffc0 00738910 ffffffc0
<4>7920  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>7940  00711388 ffffffc0 f0000373 00000000 3e805a00 ffffffc0 3e805a80 ffffffc0
<4>7960  00562a68 ffffffc0 0071b978 ffffffc0 00000000 00000001 00000002 00000000
<4>
<4>X24: 0xffffffc02d50e990:
<4>e990  00000000 00000000 3c94b180 ffffffc0 00000000 00000000 00000000 00000000
<4>e9b0  00000020 00000000 ffffffff ffffffff 00000000 00000000 00000000 00000000
<4>e9d0  00000000 00000000 2d50e9d8 ffffffc0 2d50e9d8 ffffffc0 2d50e9e8 ffffffc0
<4>e9f0  2d50e9e8 ffffffc0 20d5a418 ffffffc0 00000000 00000000 00171a5c ffffffc0
<4>ea10  3e816520 ffffffc0 20c710c0 ffffffc0 20d496b0 ffffffc0 005b93c0 ffffffc0
<4>ea30  00000000 00000000 00000000 00000000 00000002 00060003 00000001 00000000
<4>ea50  2d50ea50 ffffffc0 2d50ea50 ffffffc0 00000000 00000000 00000000 00000000
<4>ea70  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>
<4>X27: 0xffffffc00070cf80:
<4>cf80  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>cfa0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>cfc0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>cfe0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>d000  001b538c ffffffc0 001b5cd4 ffffffc0 001b6358 ffffffc0 001b6370 ffffffc0
<4>d020  001b6510 ffffffc0 001960d4 ffffffc0 001960f0 ffffffc0 0019610c ffffffc0
<4>d040  001961f8 ffffffc0 00196210 ffffffc0 00196228 ffffffc0 001962d0 ffffffc0
<4>d060  001962e8 ffffffc0 00196300 ffffffc0 00196398 ffffffc0 001963b4 ffffffc0
<4>
<4>X28: 0xffffffc01c5d7f80:
<4>7f80  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>7fa0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>7fc0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>7fe0  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>8000  00000000 00000000 ffffffff ffffffff 16a1d240 ffffffc0 0070f5d0 ffffffc0
<4>8020  000a8cec ffffffc0 00000000 00000000 00000000 00000000 00000000 00000000
<4>8040  00000000 00000000 00000000 00000000 00000002 00000000 57ac6e9d 00000000
<4>8060  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
<4>
<4>X29: 0xffffffc01c5dbce0:
<4>bce0  3cad0dc0 ffffffc0 3cbf0700 ffffffc0 3cbf0700 ffffffc0 00737900 ffffffc0
<4>bd00  2d50ea10 ffffffc0 00000119 00000000 00000039 00000000 0070d000 ffffffc0
<4>bd20  1c5d8000 ffffffc0 1c5dbd60 ffffffc0 004b60d0 ffffffc0 1c5dbd60 ffffffc0
<4>bd40  004b3a4c ffffffc0 60000145 00000000 1c5dbd70 ffffffc0 004aeaac ffffffc0
<4>bd60  1c5dbd90 ffffffc0 004b60d0 ffffffc0 3cad0dc0 ffffffc0 3cbf0818 ffffffc0
<4>bd80  00000000 00000000 3cbf0700 ffffffc0 1c5dbdd0 ffffffc0 004b0334 ffffffc0
<4>bda0  3cbf0700 ffffffc0 20d49680 ffffffc0 00000000 00000000 3e816520 ffffffc0
<4>bdc0  20c710c0 ffffffc0 2d50ea10 ffffffc0 1c5dbe00 ffffffc0 003fd8e4 ffffffc0
<4>
<0>Process poc (pid: 1560, stack limit = 0xffffffc01c5d8058)
<0>Stack: (0xffffffc01c5dbd60 to 0xffffffc01c5dc000)
<0>bd60: 1c5dbd90 ffffffc0 004b60d0 ffffffc0 3cad0dc0 ffffffc0 3cbf0818 ffffffc0
<0>bd80: 00000000 00000000 3cbf0700 ffffffc0 1c5dbdd0 ffffffc0 004b0334 ffffffc0
<0>bda0: 3cbf0700 ffffffc0 20d49680 ffffffc0 00000000 00000000 3e816520 ffffffc0
<0>bdc0: 20c710c0 ffffffc0 2d50ea10 ffffffc0 1c5dbe00 ffffffc0 003fd8e4 ffffffc0
<0>bde0: 20d49680 ffffffc0 00000008 00000000 20d496b0 ffffffc0 00171994 00000000
<0>be00: 1c5dbe20 ffffffc0 003fd96c ffffffc0 2d50ea00 ffffffc0 00171d7c ffffffc0
<0>be20: 1c5dbe30 ffffffc0 001718e4 ffffffc0 1c5dbe70 ffffffc0 00171a68 ffffffc0
<0>be40: 16a1dc40 ffffffc0 00000000 00000000 00751000 ffffffc0 16a1d240 ffffffc0
<0>be60: 60000000 00000000 00000015 00000000 1c5dbe80 ffffffc0 000b5068 ffffffc0
<0>be80: 1c5dbeb0 ffffffc0 000894e8 ffffffc0 00000004 00000000 6b578490 00000073
<0>bea0: ffffffff ffffffff 6b2b3060 00000073 6abc0f60 00000073 0008534c ffffffc0
<0>bec0: 00000000 00000000 00085430 ffffffc0 00000000 00000000 6ac2f000 00000073
<0>bee0: 00000011 00000000 6b2ea7e0 00000073 6b2ea7ee 00000073 6ac2f011 00000073
<0>bf00: 0000000a 00000000 0000000a 00000000 00000039 00000000 5c3c4424 ae01b9db
<0>bf20: 0000000a 00000000 00000000 00000000 65735f77 72657672 636f735f 2074656b
<0>bf40: 00000000 00000000 00000000 001dcd65 6b588f80 00000073 6b269d4c 00000073
<0>bf60: 068528ac 00000000 00000003 00000000 6b578490 00000073 00000004 00000000
<0>bf80: 6abc0f99 00000073 6b5784b0 00000073 6b5783d9 00000073 6b5783fb 00000073
<0>bfa0: 6b589008 00000073 6c6c6548 2e2e2e6f 00000010 00000000 6abc0f60 00000073
<0>bfc0: 6b269d5c 00000073 6abc0f50 00000073 6b2b3060 00000073 60000000 00000000
<0>bfe0: 00000003 00000000 00000039 00000000 00000000 00000000 00000000 00000000
<0>Call trace:
<4>[<ffffffc0004b3a4c>] ip_mc_leave_src+0x28/0xa8
<4>[<ffffffc0004b60cc>] ip_mc_drop_socket+0x5c/0xac
<4>[<ffffffc0004b0330>] inet_release+0x50/0xa4
<4>[<ffffffc0003fd8e0>] sock_release+0x1c/0x98
<4>[<ffffffc0003fd968>] sock_close+0xc/0x1c
<4>[<ffffffc0001718e0>] __fput+0x88/0x1b8
<4>[<ffffffc000171a64>] ____fput+0x8/0x14
<4>[<ffffffc0000b5064>] task_work_run+0x94/0xec
<4>[<ffffffc0000894e4>] do_notify_resume+0x54/0x68
<0>Code: f9400c33 aa0203e0 b9401422 b4000313 (b9400663) 

*/

//*
#define HELLO_WORLD_SERVER_PORT    6666 
#define LENGTH_OF_LISTEN_QUEUE 1
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512


int server_init = 1;

void* thread_client(void* arg)
{

 	printf("client- start() is OK...\n");
    //设置一个socket地址结构client_addr,代表客户机internet地址, 端口
    struct sockaddr_in client_addr;

	//把一段内存区的内容全部设置为0
    bzero(&client_addr,sizeof(client_addr)); 
    client_addr.sin_family = AF_INET;    //internet协议族
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
    client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
    //创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if( client_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }
    //把客户机的socket和客户机的socket地址结构联系起来
    if( bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr)))
    {
        printf("Client Bind Port Failed!\n"); 
        exit(1);
    }
 
    //设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if(inet_aton("127.0.0.1",&server_addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
    {
        printf("Server IP Address Error!\n");
        exit(1);
    }
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr);
    //向服务器发起连接,连接成功后client_socket代表了客户机和服务器的一个socket连接
    if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
    {
        printf("Can Not Connect To %s!\n","127.0.0.1");
        exit(1);
    }
 
    char buffer[BUFFER_SIZE];
    bzero(buffer,BUFFER_SIZE);

	strcpy(buffer,"hi..server!");

    send(client_socket,buffer,BUFFER_SIZE,0);
 
    //从服务器接收数据到buffer中
    bzero(buffer,BUFFER_SIZE);
    int length = 0;
    while( length = recv(client_socket,buffer,BUFFER_SIZE,0))
    {
        if(length < 0)
        {
            printf("Recieve Data From Server %s Failed!\n", "127.0.0.1");
            break;
        }

	    printf("Recv Server data : [%s]\n",buffer);

        bzero(buffer,BUFFER_SIZE);

	    strcpy(buffer,"hi..server!\n");

    	send(client_socket,buffer,BUFFER_SIZE,0);
    }
    
     
    //close(fp);
    //关闭socket
    close(client_socket);
    return NULL;
}


//server ....
void* thread_server(void* arg)
{
    //设置一个socket地址结构server_addr,代表服务器internet地址, 端口
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr)); //把一段内存区的内容全部设置为0
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    //server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

    struct	group_req group = {0};
    struct sockaddr_in *psin;

	psin = (struct sockaddr_in *)&group.gr_group;
    psin->sin_family = AF_INET;
    psin->sin_addr.s_addr = htonl(inet_addr("10.10.2.224"));

    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("Create Socket Failed!");
        exit(1);
    }

    { 
	   int opt =1;
       //IPPROTO_IP
       setsockopt(server_socket, SOL_IP, MCAST_JOIN_GROUP, &group, sizeof (group));
	}

    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT); 
        exit(1);
    }

        
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
   {
       printf("Server Listen Failed!"); 
       exit(1);
    }

	
    while (1) 
    {

        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
 
 
        printf ("accept..... \n");
        server_init = 0;        
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0)
        {
            close(server_socket);
            printf("Server Accept Failed!\n");
            break;
        }
        
        
        printf ("close new_server_socket \n");
        //first free.......
        close(new_server_socket);
        sleep(10);
        printf ("close socket fd \n");
         //first free.......
        close(server_socket);

        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
        if (length < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }

        printf("Recv Client data : [%s]\n",buffer);


            bzero(buffer, BUFFER_SIZE);

        strcpy(buffer,"Hello...");

        if(send(new_server_socket,buffer,BUFFER_SIZE,0)<0)
        {
            printf("Send File:Failed\n");
            break;
        }

        close(new_server_socket);
    }

    close(server_socket);
    return NULL;
}


int main(int argc,char* argv[])
{	
	server_init = 1;
	pthread_t id_server,id_client;
	pthread_create(&id_server,NULL,thread_server,NULL);
	while(server_init)
	{
		sleep(1);
	}
	pthread_create(&id_client,NULL,thread_client,NULL);

	getchar();

    printf("exit...\n");
	return 0;
}
//*/
