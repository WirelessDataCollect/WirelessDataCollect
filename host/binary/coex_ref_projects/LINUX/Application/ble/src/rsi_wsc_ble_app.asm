
rsi_wsc_ble_app:     file format elf32-i386


Disassembly of section .init:

080486b0 <_init>:
 80486b0:	53                   	push   %ebx
 80486b1:	83 ec 08             	sub    $0x8,%esp
 80486b4:	e8 4f 02 00 00       	call   8048908 <__x86.get_pc_thunk.bx>
 80486b9:	81 c3 47 3a 00 00    	add    $0x3a47,%ebx
 80486bf:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 80486c5:	85 c0                	test   %eax,%eax
 80486c7:	74 05                	je     80486ce <_init+0x1e>
 80486c9:	e8 d2 00 00 00       	call   80487a0 <__gmon_start__@plt>
 80486ce:	83 c4 08             	add    $0x8,%esp
 80486d1:	5b                   	pop    %ebx
 80486d2:	c3                   	ret    

Disassembly of section .plt:

080486e0 <pthread_mutex_unlock@plt-0x10>:
 80486e0:	ff 35 04 c1 04 08    	pushl  0x804c104
 80486e6:	ff 25 08 c1 04 08    	jmp    *0x804c108
 80486ec:	00 00                	add    %al,(%eax)
	...

080486f0 <pthread_mutex_unlock@plt>:
 80486f0:	ff 25 0c c1 04 08    	jmp    *0x804c10c
 80486f6:	68 00 00 00 00       	push   $0x0
 80486fb:	e9 e0 ff ff ff       	jmp    80486e0 <_init+0x30>

08048700 <printf@plt>:
 8048700:	ff 25 10 c1 04 08    	jmp    *0x804c110
 8048706:	68 08 00 00 00       	push   $0x8
 804870b:	e9 d0 ff ff ff       	jmp    80486e0 <_init+0x30>

08048710 <free@plt>:
 8048710:	ff 25 14 c1 04 08    	jmp    *0x804c114
 8048716:	68 10 00 00 00       	push   $0x10
 804871b:	e9 c0 ff ff ff       	jmp    80486e0 <_init+0x30>

08048720 <getchar@plt>:
 8048720:	ff 25 18 c1 04 08    	jmp    *0x804c118
 8048726:	68 18 00 00 00       	push   $0x18
 804872b:	e9 b0 ff ff ff       	jmp    80486e0 <_init+0x30>

08048730 <pthread_mutex_lock@plt>:
 8048730:	ff 25 1c c1 04 08    	jmp    *0x804c11c
 8048736:	68 20 00 00 00       	push   $0x20
 804873b:	e9 a0 ff ff ff       	jmp    80486e0 <_init+0x30>

08048740 <perror@plt>:
 8048740:	ff 25 20 c1 04 08    	jmp    *0x804c120
 8048746:	68 28 00 00 00       	push   $0x28
 804874b:	e9 90 ff ff ff       	jmp    80486e0 <_init+0x30>

08048750 <strcat@plt>:
 8048750:	ff 25 24 c1 04 08    	jmp    *0x804c124
 8048756:	68 30 00 00 00       	push   $0x30
 804875b:	e9 80 ff ff ff       	jmp    80486e0 <_init+0x30>

08048760 <strcpy@plt>:
 8048760:	ff 25 28 c1 04 08    	jmp    *0x804c128
 8048766:	68 38 00 00 00       	push   $0x38
 804876b:	e9 70 ff ff ff       	jmp    80486e0 <_init+0x30>

08048770 <getpid@plt>:
 8048770:	ff 25 2c c1 04 08    	jmp    *0x804c12c
 8048776:	68 40 00 00 00       	push   $0x40
 804877b:	e9 60 ff ff ff       	jmp    80486e0 <_init+0x30>

08048780 <malloc@plt>:
 8048780:	ff 25 30 c1 04 08    	jmp    *0x804c130
 8048786:	68 48 00 00 00       	push   $0x48
 804878b:	e9 50 ff ff ff       	jmp    80486e0 <_init+0x30>

08048790 <puts@plt>:
 8048790:	ff 25 34 c1 04 08    	jmp    *0x804c134
 8048796:	68 50 00 00 00       	push   $0x50
 804879b:	e9 40 ff ff ff       	jmp    80486e0 <_init+0x30>

080487a0 <__gmon_start__@plt>:
 80487a0:	ff 25 38 c1 04 08    	jmp    *0x804c138
 80487a6:	68 58 00 00 00       	push   $0x58
 80487ab:	e9 30 ff ff ff       	jmp    80486e0 <_init+0x30>

080487b0 <exit@plt>:
 80487b0:	ff 25 3c c1 04 08    	jmp    *0x804c13c
 80487b6:	68 60 00 00 00       	push   $0x60
 80487bb:	e9 20 ff ff ff       	jmp    80486e0 <_init+0x30>

080487c0 <__libc_start_main@plt>:
 80487c0:	ff 25 40 c1 04 08    	jmp    *0x804c140
 80487c6:	68 68 00 00 00       	push   $0x68
 80487cb:	e9 10 ff ff ff       	jmp    80486e0 <_init+0x30>

080487d0 <bind@plt>:
 80487d0:	ff 25 44 c1 04 08    	jmp    *0x804c144
 80487d6:	68 70 00 00 00       	push   $0x70
 80487db:	e9 00 ff ff ff       	jmp    80486e0 <_init+0x30>

080487e0 <putchar@plt>:
 80487e0:	ff 25 48 c1 04 08    	jmp    *0x804c148
 80487e6:	68 78 00 00 00       	push   $0x78
 80487eb:	e9 f0 fe ff ff       	jmp    80486e0 <_init+0x30>

080487f0 <__errno_location@plt>:
 80487f0:	ff 25 4c c1 04 08    	jmp    *0x804c14c
 80487f6:	68 80 00 00 00       	push   $0x80
 80487fb:	e9 e0 fe ff ff       	jmp    80486e0 <_init+0x30>

08048800 <sendto@plt>:
 8048800:	ff 25 50 c1 04 08    	jmp    *0x804c150
 8048806:	68 88 00 00 00       	push   $0x88
 804880b:	e9 d0 fe ff ff       	jmp    80486e0 <_init+0x30>

08048810 <sprintf@plt>:
 8048810:	ff 25 54 c1 04 08    	jmp    *0x804c154
 8048816:	68 90 00 00 00       	push   $0x90
 804881b:	e9 c0 fe ff ff       	jmp    80486e0 <_init+0x30>

08048820 <__isoc99_scanf@plt>:
 8048820:	ff 25 58 c1 04 08    	jmp    *0x804c158
 8048826:	68 98 00 00 00       	push   $0x98
 804882b:	e9 b0 fe ff ff       	jmp    80486e0 <_init+0x30>

08048830 <atoi@plt>:
 8048830:	ff 25 5c c1 04 08    	jmp    *0x804c15c
 8048836:	68 a0 00 00 00       	push   $0xa0
 804883b:	e9 a0 fe ff ff       	jmp    80486e0 <_init+0x30>

08048840 <socket@plt>:
 8048840:	ff 25 60 c1 04 08    	jmp    *0x804c160
 8048846:	68 a8 00 00 00       	push   $0xa8
 804884b:	e9 90 fe ff ff       	jmp    80486e0 <_init+0x30>

08048850 <pthread_create@plt>:
 8048850:	ff 25 64 c1 04 08    	jmp    *0x804c164
 8048856:	68 b0 00 00 00       	push   $0xb0
 804885b:	e9 80 fe ff ff       	jmp    80486e0 <_init+0x30>

08048860 <fputs@plt>:
 8048860:	ff 25 68 c1 04 08    	jmp    *0x804c168
 8048866:	68 b8 00 00 00       	push   $0xb8
 804886b:	e9 70 fe ff ff       	jmp    80486e0 <_init+0x30>

08048870 <recv@plt>:
 8048870:	ff 25 6c c1 04 08    	jmp    *0x804c16c
 8048876:	68 c0 00 00 00       	push   $0xc0
 804887b:	e9 60 fe ff ff       	jmp    80486e0 <_init+0x30>

08048880 <close@plt>:
 8048880:	ff 25 70 c1 04 08    	jmp    *0x804c170
 8048886:	68 c8 00 00 00       	push   $0xc8
 804888b:	e9 50 fe ff ff       	jmp    80486e0 <_init+0x30>

Disassembly of section .text:

08048890 <main>:
 * @section description
 * This is start of application.
 */

int main(int argc, char *argv[])
{
 8048890:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 8048894:	83 e4 f0             	and    $0xfffffff0,%esp
 8048897:	ff 71 fc             	pushl  -0x4(%ecx)
 804889a:	55                   	push   %ebp
 804889b:	89 e5                	mov    %esp,%ebp
 804889d:	51                   	push   %ecx
 804889e:	83 ec 14             	sub    $0x14,%esp
    RSI_DPRINT (RSI_PL3,"socket creation error\n");
#endif
    return 2;
  }
#endif
  retval = rsi_nl_socket_init();
 80488a1:	e8 f8 18 00 00       	call   804a19e <rsi_nl_socket_init>
  if (retval == -1) {
 80488a6:	66 40                	inc    %ax
 80488a8:	74 2b                	je     80488d5 <main+0x45>
    /* Error occurred! */
    return 2;
  }

  rsi_fill_genl_nl_hdrs_for_cmd();
 80488aa:	e8 2e 1b 00 00       	call   804a3dd <rsi_fill_genl_nl_hdrs_for_cmd>
#if 0//SPI_INTERFACE
  retval = rsi_update_info(MODULE_POWER_CYCLE);
#endif

#if 1
  if( (rc1 = pthread_create( &thread1, NULL, RecvThreadBody, (void*) message1)) )
 80488af:	8d 45 f4             	lea    -0xc(%ebp),%eax
 80488b2:	68 f4 a4 04 08       	push   $0x804a4f4
 80488b7:	68 f4 a2 04 08       	push   $0x804a2f4
 80488bc:	6a 00                	push   $0x0
 80488be:	50                   	push   %eax
 80488bf:	e8 8c ff ff ff       	call   8048850 <pthread_create@plt>
#endif
  //! send interrupt irq register frame to driver to register the interrupt irq
//  rsi_bt_register_interrupt_irq();
  
  //! calling ble_main
   ble_main();
 80488c4:	e8 cb 0b 00 00       	call   8049494 <ble_main>
#endif

  /**
   * Exit application
   */
  exit(0);
 80488c9:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 80488d0:	e8 db fe ff ff       	call   80487b0 <exit@plt>
}
 80488d5:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 80488d8:	b8 02 00 00 00       	mov    $0x2,%eax
 80488dd:	c9                   	leave  
 80488de:	8d 61 fc             	lea    -0x4(%ecx),%esp
 80488e1:	c3                   	ret    
 80488e2:	66 90                	xchg   %ax,%ax

080488e4 <_start>:
 80488e4:	31 ed                	xor    %ebp,%ebp
 80488e6:	5e                   	pop    %esi
 80488e7:	89 e1                	mov    %esp,%ecx
 80488e9:	83 e4 f0             	and    $0xfffffff0,%esp
 80488ec:	50                   	push   %eax
 80488ed:	54                   	push   %esp
 80488ee:	52                   	push   %edx
 80488ef:	68 d0 a4 04 08       	push   $0x804a4d0
 80488f4:	68 60 a4 04 08       	push   $0x804a460
 80488f9:	51                   	push   %ecx
 80488fa:	56                   	push   %esi
 80488fb:	68 90 88 04 08       	push   $0x8048890
 8048900:	e8 bb fe ff ff       	call   80487c0 <__libc_start_main@plt>
 8048905:	f4                   	hlt    
 8048906:	66 90                	xchg   %ax,%ax

08048908 <__x86.get_pc_thunk.bx>:
 8048908:	8b 1c 24             	mov    (%esp),%ebx
 804890b:	c3                   	ret    
 804890c:	0f 1f 40 00          	nopl   0x0(%eax)

08048910 <deregister_tm_clones>:
 8048910:	b8 33 c6 04 08       	mov    $0x804c633,%eax
 8048915:	2d 30 c6 04 08       	sub    $0x804c630,%eax
 804891a:	83 f8 06             	cmp    $0x6,%eax
 804891d:	77 01                	ja     8048920 <deregister_tm_clones+0x10>
 804891f:	c3                   	ret    
 8048920:	b8 00 00 00 00       	mov    $0x0,%eax
 8048925:	85 c0                	test   %eax,%eax
 8048927:	74 f6                	je     804891f <deregister_tm_clones+0xf>
 8048929:	55                   	push   %ebp
 804892a:	89 e5                	mov    %esp,%ebp
 804892c:	8d 64 24 e8          	lea    -0x18(%esp),%esp
 8048930:	c7 04 24 30 c6 04 08 	movl   $0x804c630,(%esp)
 8048937:	ff d0                	call   *%eax
 8048939:	c9                   	leave  
 804893a:	c3                   	ret    
 804893b:	90                   	nop
 804893c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

08048940 <register_tm_clones>:
 8048940:	b8 30 c6 04 08       	mov    $0x804c630,%eax
 8048945:	2d 30 c6 04 08       	sub    $0x804c630,%eax
 804894a:	c1 f8 02             	sar    $0x2,%eax
 804894d:	89 c2                	mov    %eax,%edx
 804894f:	c1 ea 1f             	shr    $0x1f,%edx
 8048952:	01 d0                	add    %edx,%eax
 8048954:	d1 f8                	sar    %eax
 8048956:	75 01                	jne    8048959 <register_tm_clones+0x19>
 8048958:	c3                   	ret    
 8048959:	ba 00 00 00 00       	mov    $0x0,%edx
 804895e:	85 d2                	test   %edx,%edx
 8048960:	74 f6                	je     8048958 <register_tm_clones+0x18>
 8048962:	55                   	push   %ebp
 8048963:	89 e5                	mov    %esp,%ebp
 8048965:	8d 64 24 e8          	lea    -0x18(%esp),%esp
 8048969:	89 44 24 04          	mov    %eax,0x4(%esp)
 804896d:	c7 04 24 30 c6 04 08 	movl   $0x804c630,(%esp)
 8048974:	ff d2                	call   *%edx
 8048976:	c9                   	leave  
 8048977:	c3                   	ret    
 8048978:	90                   	nop
 8048979:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

08048980 <__do_global_dtors_aux>:
 8048980:	80 3d 34 c6 04 08 00 	cmpb   $0x0,0x804c634
 8048987:	75 18                	jne    80489a1 <__do_global_dtors_aux+0x21>
 8048989:	55                   	push   %ebp
 804898a:	89 e5                	mov    %esp,%ebp
 804898c:	8d 64 24 f8          	lea    -0x8(%esp),%esp
 8048990:	e8 7b ff ff ff       	call   8048910 <deregister_tm_clones>
 8048995:	c6 05 34 c6 04 08 01 	movb   $0x1,0x804c634
 804899c:	90                   	nop
 804899d:	90                   	nop
 804899e:	90                   	nop
 804899f:	90                   	nop
 80489a0:	c9                   	leave  
 80489a1:	c3                   	ret    
 80489a2:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 80489a9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080489b0 <frame_dummy>:
 80489b0:	a1 08 c0 04 08       	mov    0x804c008,%eax
 80489b5:	85 c0                	test   %eax,%eax
 80489b7:	74 1f                	je     80489d8 <frame_dummy+0x28>
 80489b9:	b8 00 00 00 00       	mov    $0x0,%eax
 80489be:	85 c0                	test   %eax,%eax
 80489c0:	74 16                	je     80489d8 <frame_dummy+0x28>
 80489c2:	55                   	push   %ebp
 80489c3:	89 e5                	mov    %esp,%ebp
 80489c5:	8d 64 24 e8          	lea    -0x18(%esp),%esp
 80489c9:	c7 04 24 08 c0 04 08 	movl   $0x804c008,(%esp)
 80489d0:	ff d0                	call   *%eax
 80489d2:	c9                   	leave  
 80489d3:	e9 68 ff ff ff       	jmp    8048940 <register_tm_clones>
 80489d8:	e9 63 ff ff ff       	jmp    8048940 <register_tm_clones>
 80489dd:	0f 1f 00             	nopl   (%eax)

080489e0 <rsi_frame_read>:


int16 rsi_frame_read(uint8 *packet_buffer)
{
 80489e0:	55                   	push   %ebp
 80489e1:	89 e5                	mov    %esp,%ebp
 80489e3:	57                   	push   %edi
 80489e4:	56                   	push   %esi
    length += RSI_BT_FRAME_DESC_LEN;

    /* Debug: Print the length & contents of the packet */
#if 1//def RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL0,"Length of the packet: %d\n", length);
    for (i=0; i<length; i++) {
 80489e5:	31 f6                	xor    %esi,%esi
  exit(0);
}


int16 rsi_frame_read(uint8 *packet_buffer)
{
 80489e7:	53                   	push   %ebx
 80489e8:	83 ec 28             	sub    $0x28,%esp
#if 1//def RSI_DEBUG_PRINT
    int i;
#endif

    /* Do actual deque from the RX queue */
    pthread_mutex_lock(&linux_app_cbPtr->mutex1);
 80489eb:	68 72 c6 04 08       	push   $0x804c672
 80489f0:	e8 3b fd ff ff       	call   8048730 <pthread_mutex_lock@plt>
    rspPtr = rsi_dequeue_from_rcv_q();
 80489f5:	e8 c5 18 00 00       	call   804a2bf <rsi_dequeue_from_rcv_q>
    pthread_mutex_unlock(&linux_app_cbPtr->mutex1);
 80489fa:	c7 04 24 72 c6 04 08 	movl   $0x804c672,(%esp)
    int i;
#endif

    /* Do actual deque from the RX queue */
    pthread_mutex_lock(&linux_app_cbPtr->mutex1);
    rspPtr = rsi_dequeue_from_rcv_q();
 8048a01:	89 c3                	mov    %eax,%ebx
    pthread_mutex_unlock(&linux_app_cbPtr->mutex1);
 8048a03:	e8 e8 fc ff ff       	call   80486f0 <pthread_mutex_unlock@plt>

    /* Assign pointers to appropriate addresses */
    descPtr    = rspPtr->data + RSI_NL_HEAD_SIZE;
 8048a08:	8b 5b 04             	mov    0x4(%ebx),%ebx
#endif
    length += RSI_BT_FRAME_DESC_LEN;

    /* Debug: Print the length & contents of the packet */
#if 1//def RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL0,"Length of the packet: %d\n", length);
 8048a0b:	5a                   	pop    %edx
 8048a0c:	59                   	pop    %ecx
    pthread_mutex_lock(&linux_app_cbPtr->mutex1);
    rspPtr = rsi_dequeue_from_rcv_q();
    pthread_mutex_unlock(&linux_app_cbPtr->mutex1);

    /* Assign pointers to appropriate addresses */
    descPtr    = rspPtr->data + RSI_NL_HEAD_SIZE;
 8048a0d:	8d 43 18             	lea    0x18(%ebx),%eax
 8048a10:	89 45 e4             	mov    %eax,-0x1c(%ebp)

    /* Calculate length of the packet from the first two bytes of the frame descriptor */
#ifdef RSI_LITTLE_ENDIAN
    length = *(int16*)descPtr & 0x0fff;
 8048a13:	66 8b 43 18          	mov    0x18(%ebx),%ax
 8048a17:	66 25 ff 0f          	and    $0xfff,%ax
#else
    length = rsi_bytes2R_to_uint16(descPtr);
#endif
    length += RSI_BT_FRAME_DESC_LEN;
 8048a1b:	83 c0 10             	add    $0x10,%eax

    /* Debug: Print the length & contents of the packet */
#if 1//def RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL0,"Length of the packet: %d\n", length);
 8048a1e:	0f b7 f8             	movzwl %ax,%edi
 8048a21:	57                   	push   %edi
 8048a22:	68 00 a5 04 08       	push   $0x804a500
#ifdef RSI_LITTLE_ENDIAN
    length = *(int16*)descPtr & 0x0fff;
#else
    length = rsi_bytes2R_to_uint16(descPtr);
#endif
    length += RSI_BT_FRAME_DESC_LEN;
 8048a27:	66 89 45 e2          	mov    %ax,-0x1e(%ebp)

    /* Debug: Print the length & contents of the packet */
#if 1//def RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL0,"Length of the packet: %d\n", length);
 8048a2b:	e8 d0 fc ff ff       	call   8048700 <printf@plt>
 8048a30:	83 c4 10             	add    $0x10,%esp
    for (i=0; i<length; i++) {
        RSI_DPRINT (RSI_PL0, "0x%x ", descPtr[i]);
 8048a33:	50                   	push   %eax
 8048a34:	50                   	push   %eax
 8048a35:	0f b6 44 33 18       	movzbl 0x18(%ebx,%esi,1),%eax
 8048a3a:	50                   	push   %eax
 8048a3b:	68 1a a5 04 08       	push   $0x804a51a
 8048a40:	e8 bb fc ff ff       	call   8048700 <printf@plt>
        if (i == 15) {
 8048a45:	83 c4 10             	add    $0x10,%esp
 8048a48:	83 fe 0f             	cmp    $0xf,%esi
 8048a4b:	75 0d                	jne    8048a5a <rsi_frame_read+0x7a>
            RSI_DPRINT(RSI_PL0, "\n");
 8048a4d:	83 ec 0c             	sub    $0xc,%esp
 8048a50:	6a 0a                	push   $0xa
 8048a52:	e8 89 fd ff ff       	call   80487e0 <putchar@plt>
 8048a57:	83 c4 10             	add    $0x10,%esp
    length += RSI_BT_FRAME_DESC_LEN;

    /* Debug: Print the length & contents of the packet */
#if 1//def RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL0,"Length of the packet: %d\n", length);
    for (i=0; i<length; i++) {
 8048a5a:	46                   	inc    %esi
 8048a5b:	39 fe                	cmp    %edi,%esi
 8048a5d:	7c d4                	jl     8048a33 <rsi_frame_read+0x53>
        RSI_DPRINT (RSI_PL0, "0x%x ", descPtr[i]);
        if (i == 15) {
            RSI_DPRINT(RSI_PL0, "\n");
        }
    }
    RSI_DPRINT(RSI_PL0, "\n");
 8048a5f:	83 ec 0c             	sub    $0xc,%esp
 8048a62:	6a 0a                	push   $0xa
 8048a64:	e8 77 fd ff ff       	call   80487e0 <putchar@plt>
#endif

    /* Copy the packet into the buffer */
    memcpy(packet_buffer, descPtr, length);
 8048a69:	0f b7 4d e2          	movzwl -0x1e(%ebp),%ecx

    /* Return success */
    return 0;
}
 8048a6d:	31 c0                	xor    %eax,%eax
    }
    RSI_DPRINT(RSI_PL0, "\n");
#endif

    /* Copy the packet into the buffer */
    memcpy(packet_buffer, descPtr, length);
 8048a6f:	8b 7d 08             	mov    0x8(%ebp),%edi
 8048a72:	8b 75 e4             	mov    -0x1c(%ebp),%esi
 8048a75:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)

    /* Return success */
    return 0;
}
 8048a77:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048a7a:	5b                   	pop    %ebx
 8048a7b:	5e                   	pop    %esi
 8048a7c:	5f                   	pop    %edi
 8048a7d:	5d                   	pop    %ebp
 8048a7e:	c3                   	ret    
 8048a7f:	90                   	nop

08048a80 <rsi_bytes4_to_uint32>:
 * @param[in]     uint8 *dBuf,pointer to buffer to get the data from
 * @param[out]    none
 * @return        uint32, converted data
 */
uint32 rsi_bytes4_to_uint32(uint8 *dBuf)
{
 8048a80:	55                   	push   %ebp
 8048a81:	89 e5                	mov    %esp,%ebp
 8048a83:	8b 55 08             	mov    0x8(%ebp),%edx
   val |= dBuf[2] & 0x000000ff;
   val <<= 8;
   val |= dBuf[3] & 0x000000ff;

   return val;
}
 8048a86:	5d                   	pop    %ebp
 */
uint32 rsi_bytes4_to_uint32(uint8 *dBuf)
{
   uint32            val;            //! the 32-bit value to return

   val = dBuf[0];
 8048a87:	0f b6 02             	movzbl (%edx),%eax
   val <<= 8;
   val |= dBuf[1] & 0x000000ff;
 8048a8a:	0f b6 4a 01          	movzbl 0x1(%edx),%ecx
uint32 rsi_bytes4_to_uint32(uint8 *dBuf)
{
   uint32            val;            //! the 32-bit value to return

   val = dBuf[0];
   val <<= 8;
 8048a8e:	c1 e0 08             	shl    $0x8,%eax
   val |= dBuf[1] & 0x000000ff;
 8048a91:	09 c8                	or     %ecx,%eax
   val <<= 8;
   val |= dBuf[2] & 0x000000ff;
 8048a93:	0f b6 4a 02          	movzbl 0x2(%edx),%ecx
   val <<= 8;
   val |= dBuf[3] & 0x000000ff;
 8048a97:	0f b6 52 03          	movzbl 0x3(%edx),%edx
   uint32            val;            //! the 32-bit value to return

   val = dBuf[0];
   val <<= 8;
   val |= dBuf[1] & 0x000000ff;
   val <<= 8;
 8048a9b:	c1 e0 08             	shl    $0x8,%eax
   val |= dBuf[2] & 0x000000ff;
 8048a9e:	09 c8                	or     %ecx,%eax
   val <<= 8;
 8048aa0:	c1 e0 08             	shl    $0x8,%eax
   val |= dBuf[3] & 0x000000ff;
 8048aa3:	09 d0                	or     %edx,%eax

   return val;
}
 8048aa5:	c3                   	ret    

08048aa6 <rsi_bytes4R_to_uint32>:
 * @param[in]    uint8 *dBuf,pointer to buffer to get the data from
 * @param[out]   none
 * @return       uint32, converted data
 */
uint32 rsi_bytes4R_to_uint32(uint8 *dBuf)
{
 8048aa6:	55                   	push   %ebp
 8048aa7:	89 e5                	mov    %esp,%ebp
 8048aa9:	8b 55 08             	mov    0x8(%ebp),%edx
   val |= dBuf[1] & 0x000000ff;
   val <<= 8;
   val |= dBuf[0] & 0x000000ff;

   return val;
}
 8048aac:	5d                   	pop    %ebp
 */
uint32 rsi_bytes4R_to_uint32(uint8 *dBuf)
{
   uint32            val;            //! the 32-bit value to return

   val = dBuf[3];
 8048aad:	0f b6 42 03          	movzbl 0x3(%edx),%eax
   val <<= 8;
   val |= dBuf[2] & 0x000000ff;
 8048ab1:	0f b6 4a 02          	movzbl 0x2(%edx),%ecx
uint32 rsi_bytes4R_to_uint32(uint8 *dBuf)
{
   uint32            val;            //! the 32-bit value to return

   val = dBuf[3];
   val <<= 8;
 8048ab5:	c1 e0 08             	shl    $0x8,%eax
   val |= dBuf[2] & 0x000000ff;
 8048ab8:	09 c8                	or     %ecx,%eax
   val <<= 8;
   val |= dBuf[1] & 0x000000ff;
 8048aba:	0f b6 4a 01          	movzbl 0x1(%edx),%ecx
   val <<= 8;
   val |= dBuf[0] & 0x000000ff;
 8048abe:	0f b6 12             	movzbl (%edx),%edx
   uint32            val;            //! the 32-bit value to return

   val = dBuf[3];
   val <<= 8;
   val |= dBuf[2] & 0x000000ff;
   val <<= 8;
 8048ac1:	c1 e0 08             	shl    $0x8,%eax
   val |= dBuf[1] & 0x000000ff;
 8048ac4:	09 c8                	or     %ecx,%eax
   val <<= 8;
 8048ac6:	c1 e0 08             	shl    $0x8,%eax
   val |= dBuf[0] & 0x000000ff;
 8048ac9:	09 d0                	or     %edx,%eax

   return val;
}
 8048acb:	c3                   	ret    

08048acc <rsi_bytes2_to_uint16>:
 * @param[in]     uint8 *dBuf,pointer to a buffer to get the data from
 * @param[out]    none
 * @return        uint16, converted data
 */
uint16 rsi_bytes2_to_uint16(uint8 *dBuf)
{
 8048acc:	55                   	push   %ebp
 8048acd:	89 e5                	mov    %esp,%ebp
 8048acf:	8b 55 08             	mov    0x8(%ebp),%edx
   val = dBuf[0];
   val <<= 8;
   val |= dBuf[1] & 0x000000ff;

   return val;
}
 8048ad2:	5d                   	pop    %ebp
 */
uint16 rsi_bytes2_to_uint16(uint8 *dBuf)
{
   uint16            val;            //! the 16-bit value to return

   val = dBuf[0];
 8048ad3:	0f b6 02             	movzbl (%edx),%eax
   val <<= 8;
   val |= dBuf[1] & 0x000000ff;
 8048ad6:	0f b6 52 01          	movzbl 0x1(%edx),%edx
uint16 rsi_bytes2_to_uint16(uint8 *dBuf)
{
   uint16            val;            //! the 16-bit value to return

   val = dBuf[0];
   val <<= 8;
 8048ada:	c1 e0 08             	shl    $0x8,%eax
   val |= dBuf[1] & 0x000000ff;
 8048add:	09 d0                	or     %edx,%eax

   return val;
}
 8048adf:	c3                   	ret    

08048ae0 <rsi_bytes6_to_ascii_mac_addr>:
 * @param[in]      uint8 *strBuf, pointer to a dummy String to hold the MAC address
 * @param[out]     none
 * @return         int8 * destString, pointer to the string with the data
 */
int8 * rsi_bytes6_to_ascii_mac_addr(uint8 *hexAddr,uint8 *strBuf)
{
 8048ae0:	55                   	push   %ebp
 8048ae1:	89 e5                	mov    %esp,%ebp
 8048ae3:	57                   	push   %edi
   uint8         i;                  //! loop counter
   uint8         cBuf[3];            //! character buffer
   uint8         *destString;

   strBuf[0] = 0;                     //! make  strcat think the array is empty
 8048ae4:	31 ff                	xor    %edi,%edi
 * @param[in]      uint8 *strBuf, pointer to a dummy String to hold the MAC address
 * @param[out]     none
 * @return         int8 * destString, pointer to the string with the data
 */
int8 * rsi_bytes6_to_ascii_mac_addr(uint8 *hexAddr,uint8 *strBuf)
{
 8048ae6:	56                   	push   %esi
 8048ae7:	53                   	push   %ebx
 8048ae8:	83 ec 1c             	sub    $0x1c,%esp
 8048aeb:	8b 5d 0c             	mov    0xc(%ebp),%ebx
   uint8         *destString;

   strBuf[0] = 0;                     //! make  strcat think the array is empty
   for (i = 0; i < 5; i++) {          //! MAC Address is 6 bytes long
      //! This will take care of the first5 bytes
      sprintf ((char *)cBuf, "%02x", (unsigned int)(((uint8*)hexAddr)[i]));
 8048aee:	8d 75 e5             	lea    -0x1b(%ebp),%esi
{
   uint8         i;                  //! loop counter
   uint8         cBuf[3];            //! character buffer
   uint8         *destString;

   strBuf[0] = 0;                     //! make  strcat think the array is empty
 8048af1:	c6 03 00             	movb   $0x0,(%ebx)
   for (i = 0; i < 5; i++) {          //! MAC Address is 6 bytes long
      //! This will take care of the first5 bytes
      sprintf ((char *)cBuf, "%02x", (unsigned int)(((uint8*)hexAddr)[i]));
 8048af4:	8b 55 08             	mov    0x8(%ebp),%edx
 8048af7:	50                   	push   %eax
 8048af8:	0f b6 04 3a          	movzbl (%edx,%edi,1),%eax
 8048afc:	47                   	inc    %edi
 8048afd:	50                   	push   %eax
 8048afe:	68 a3 a7 04 08       	push   $0x804a7a3
 8048b03:	56                   	push   %esi
 8048b04:	e8 07 fd ff ff       	call   8048810 <sprintf@plt>
      cBuf[2] = 0;                     //! terminate the string
      destString =(uint8 *) strcat((char *)strBuf,(char *) cBuf);
 8048b09:	58                   	pop    %eax
 8048b0a:	5a                   	pop    %edx

   strBuf[0] = 0;                     //! make  strcat think the array is empty
   for (i = 0; i < 5; i++) {          //! MAC Address is 6 bytes long
      //! This will take care of the first5 bytes
      sprintf ((char *)cBuf, "%02x", (unsigned int)(((uint8*)hexAddr)[i]));
      cBuf[2] = 0;                     //! terminate the string
 8048b0b:	c6 45 e7 00          	movb   $0x0,-0x19(%ebp)
      destString =(uint8 *) strcat((char *)strBuf,(char *) cBuf);
 8048b0f:	56                   	push   %esi
 8048b10:	53                   	push   %ebx
 8048b11:	e8 3a fc ff ff       	call   8048750 <strcat@plt>
      destString = (uint8 *)strcat((char *)strBuf, (char *)":");
 8048b16:	59                   	pop    %ecx
 8048b17:	58                   	pop    %eax
 8048b18:	68 3d a7 04 08       	push   $0x804a73d
 8048b1d:	53                   	push   %ebx
 8048b1e:	e8 2d fc ff ff       	call   8048750 <strcat@plt>
   uint8         i;                  //! loop counter
   uint8         cBuf[3];            //! character buffer
   uint8         *destString;

   strBuf[0] = 0;                     //! make  strcat think the array is empty
   for (i = 0; i < 5; i++) {          //! MAC Address is 6 bytes long
 8048b23:	83 c4 10             	add    $0x10,%esp
 8048b26:	83 ff 05             	cmp    $0x5,%edi
 8048b29:	75 c9                	jne    8048af4 <rsi_bytes6_to_ascii_mac_addr+0x14>
      cBuf[2] = 0;                     //! terminate the string
      destString =(uint8 *) strcat((char *)strBuf,(char *) cBuf);
      destString = (uint8 *)strcat((char *)strBuf, (char *)":");
   }
   //! take care of the last entry outside the loop, there is no . after the last octet
   sprintf ((char *)cBuf, "%02x", (unsigned int)(((uint8*)hexAddr)[i]));
 8048b2b:	8b 55 08             	mov    0x8(%ebp),%edx
 8048b2e:	50                   	push   %eax
 8048b2f:	0f b6 42 05          	movzbl 0x5(%edx),%eax
 8048b33:	50                   	push   %eax
 8048b34:	68 a3 a7 04 08       	push   $0x804a7a3
 8048b39:	56                   	push   %esi
 8048b3a:	e8 d1 fc ff ff       	call   8048810 <sprintf@plt>
   cBuf[2] = 0;                                             
   //! terminate the string
   destString = (uint8 *)strcat((char *)strBuf,(char *) cBuf);
 8048b3f:	5a                   	pop    %edx
 8048b40:	59                   	pop    %ecx
      destString =(uint8 *) strcat((char *)strBuf,(char *) cBuf);
      destString = (uint8 *)strcat((char *)strBuf, (char *)":");
   }
   //! take care of the last entry outside the loop, there is no . after the last octet
   sprintf ((char *)cBuf, "%02x", (unsigned int)(((uint8*)hexAddr)[i]));
   cBuf[2] = 0;                                             
 8048b41:	c6 45 e7 00          	movb   $0x0,-0x19(%ebp)
   //! terminate the string
   destString = (uint8 *)strcat((char *)strBuf,(char *) cBuf);
 8048b45:	56                   	push   %esi
 8048b46:	53                   	push   %ebx
 8048b47:	e8 04 fc ff ff       	call   8048750 <strcat@plt>
   return (int8 *) destString;
}
 8048b4c:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048b4f:	5b                   	pop    %ebx
 8048b50:	5e                   	pop    %esi
 8048b51:	5f                   	pop    %edi
 8048b52:	5d                   	pop    %ebp
 8048b53:	c3                   	ret    

08048b54 <rsi_swap_2bytes>:
 * @param[in]      uint8 *buffer,pointer to buffer of data to convert
 * @param[out]     none
 * @return         value returned in the array passed
 */
void rsi_swap_2bytes(uint8 *buffer)
{
 8048b54:	55                   	push   %ebp
 8048b55:	89 e5                	mov    %esp,%ebp
 8048b57:	8b 45 08             	mov    0x8(%ebp),%eax
   uint8         tmp;

   tmp = buffer[0];
 8048b5a:	8a 08                	mov    (%eax),%cl
   buffer[0] = buffer[1];
 8048b5c:	8a 50 01             	mov    0x1(%eax),%dl
   buffer[1] = tmp;
 8048b5f:	88 48 01             	mov    %cl,0x1(%eax)
void rsi_swap_2bytes(uint8 *buffer)
{
   uint8         tmp;

   tmp = buffer[0];
   buffer[0] = buffer[1];
 8048b62:	88 10                	mov    %dl,(%eax)
   buffer[1] = tmp;
}
 8048b64:	5d                   	pop    %ebp
 8048b65:	c3                   	ret    

08048b66 <rsi_swap_4bytes>:
 * @param[in]      uint8 *buffer,pointer to buffer of data to convert
 * @param[out]     none
 * @return         value returned in the array passed
 */
void rsi_swap_4bytes(uint8 *buffer)
{
 8048b66:	55                   	push   %ebp
 8048b67:	89 e5                	mov    %esp,%ebp
 8048b69:	8b 45 08             	mov    0x8(%ebp),%eax
   uint8         tmp;

   tmp = buffer[0];
 8048b6c:	8a 08                	mov    (%eax),%cl
   buffer[0] = buffer[3];
 8048b6e:	8a 50 03             	mov    0x3(%eax),%dl
   buffer[3] = tmp;
 8048b71:	88 48 03             	mov    %cl,0x3(%eax)
   tmp = buffer[1];
 8048b74:	8a 48 01             	mov    0x1(%eax),%cl
void rsi_swap_4bytes(uint8 *buffer)
{
   uint8         tmp;

   tmp = buffer[0];
   buffer[0] = buffer[3];
 8048b77:	88 10                	mov    %dl,(%eax)
   buffer[3] = tmp;
   tmp = buffer[1];
   buffer[1] = buffer[2];
 8048b79:	8a 50 02             	mov    0x2(%eax),%dl
   buffer[2] = tmp;
 8048b7c:	88 48 02             	mov    %cl,0x2(%eax)

   tmp = buffer[0];
   buffer[0] = buffer[3];
   buffer[3] = tmp;
   tmp = buffer[1];
   buffer[1] = buffer[2];
 8048b7f:	88 50 01             	mov    %dl,0x1(%eax)
   buffer[2] = tmp;
}
 8048b82:	5d                   	pop    %ebp
 8048b83:	c3                   	ret    

08048b84 <rsi_in_uint8_list>:
 * @param[in]      uint8 nargs,number of arguments
 * @param[out]     none
 * @return         value returned in the array passed
 */
int16 rsi_in_uint8_list(uint8 arg, uint8 *list, uint8 nargs)
{
 8048b84:	55                   	push   %ebp
   int16            retval;       //! return value, TRUE or FALSE
   uint8            i;            //! loop counter

   retval = RSI_FALSE;                                                
   //! start off with a false, if we find a match, then change to a true to return
   for (i = 0; i < nargs; i++) {
 8048b85:	31 c0                	xor    %eax,%eax
 * @param[in]      uint8 nargs,number of arguments
 * @param[out]     none
 * @return         value returned in the array passed
 */
int16 rsi_in_uint8_list(uint8 arg, uint8 *list, uint8 nargs)
{
 8048b87:	89 e5                	mov    %esp,%ebp
 8048b89:	8a 4d 08             	mov    0x8(%ebp),%cl
 8048b8c:	53                   	push   %ebx
 8048b8d:	8a 55 10             	mov    0x10(%ebp),%dl
   int16            retval;       //! return value, TRUE or FALSE
   uint8            i;            //! loop counter

   retval = RSI_FALSE;                                                
   //! start off with a false, if we find a match, then change to a true to return
   for (i = 0; i < nargs; i++) {
 8048b90:	eb 0a                	jmp    8048b9c <rsi_in_uint8_list+0x18>
      if (arg == list[i]) {
 8048b92:	8b 5d 0c             	mov    0xc(%ebp),%ebx
 8048b95:	40                   	inc    %eax
 8048b96:	3a 4c 03 ff          	cmp    -0x1(%ebx,%eax,1),%cl
 8048b9a:	74 08                	je     8048ba4 <rsi_in_uint8_list+0x20>
   int16            retval;       //! return value, TRUE or FALSE
   uint8            i;            //! loop counter

   retval = RSI_FALSE;                                                
   //! start off with a false, if we find a match, then change to a true to return
   for (i = 0; i < nargs; i++) {
 8048b9c:	38 c2                	cmp    %al,%dl
 8048b9e:	77 f2                	ja     8048b92 <rsi_in_uint8_list+0xe>
int16 rsi_in_uint8_list(uint8 arg, uint8 *list, uint8 nargs)
{
   int16            retval;       //! return value, TRUE or FALSE
   uint8            i;            //! loop counter

   retval = RSI_FALSE;                                                
 8048ba0:	31 c0                	xor    %eax,%eax
 8048ba2:	eb 05                	jmp    8048ba9 <rsi_in_uint8_list+0x25>
   //! start off with a false, if we find a match, then change to a true to return
   for (i = 0; i < nargs; i++) {
      if (arg == list[i]) {
         retval = RSI_TRUE;
 8048ba4:	b8 01 00 00 00       	mov    $0x1,%eax
         break;
      }
   }

   return retval;
}
 8048ba9:	5b                   	pop    %ebx
 8048baa:	5d                   	pop    %ebp
 8048bab:	c3                   	ret    

08048bac <rsi_bytes4_to_ascii_dot_addr>:
 * @param[in]      uint8 *strBuf, String Pointer to hold the Concatenated String
 * @param[out]     none
 * @return         char * destString, pointer to the string with the data
 */
int8 * rsi_bytes4_to_ascii_dot_addr(uint8 *hexAddr,uint8 *strBuf)
{
 8048bac:	55                   	push   %ebp
 8048bad:	89 e5                	mov    %esp,%ebp
 8048baf:	57                   	push   %edi
  uint8         i;                     //! loop counter
  uint8         ii;                    //! loop counter
  int8         cBuf[4];                //! character buffer
  int8         *destString;

  strBuf[0] = 0;                        //! make  strcat think the array is empty
 8048bb0:	31 ff                	xor    %edi,%edi
 * @param[in]      uint8 *strBuf, String Pointer to hold the Concatenated String
 * @param[out]     none
 * @return         char * destString, pointer to the string with the data
 */
int8 * rsi_bytes4_to_ascii_dot_addr(uint8 *hexAddr,uint8 *strBuf)
{
 8048bb2:	56                   	push   %esi
 8048bb3:	53                   	push   %ebx
 8048bb4:	83 ec 1c             	sub    $0x1c,%esp
 8048bb7:	8b 5d 0c             	mov    0xc(%ebp),%ebx
  strBuf[0] = 0;                        //! make  strcat think the array is empty
  for (i = 0; i < 3; i++) {             //! we are assuming IPV4, so 4 bytes
    //! This will take care of the first 3 bytes
    //! zero out the character buffer since we don't know how long the string will be
    for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }   
    sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
 8048bba:	8d 75 e4             	lea    -0x1c(%ebp),%esi
  uint8         i;                     //! loop counter
  uint8         ii;                    //! loop counter
  int8         cBuf[4];                //! character buffer
  int8         *destString;

  strBuf[0] = 0;                        //! make  strcat think the array is empty
 8048bbd:	c6 03 00             	movb   $0x0,(%ebx)
  for (i = 0; i < 3; i++) {             //! we are assuming IPV4, so 4 bytes
    //! This will take care of the first 3 bytes
    //! zero out the character buffer since we don't know how long the string will be
    for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }   
    sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
 8048bc0:	8b 55 08             	mov    0x8(%ebp),%edx
 8048bc3:	51                   	push   %ecx

  strBuf[0] = 0;                        //! make  strcat think the array is empty
  for (i = 0; i < 3; i++) {             //! we are assuming IPV4, so 4 bytes
    //! This will take care of the first 3 bytes
    //! zero out the character buffer since we don't know how long the string will be
    for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }   
 8048bc4:	c6 45 e4 00          	movb   $0x0,-0x1c(%ebp)
    sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
 8048bc8:	0f b6 04 3a          	movzbl (%edx,%edi,1),%eax
 8048bcc:	47                   	inc    %edi

  strBuf[0] = 0;                        //! make  strcat think the array is empty
  for (i = 0; i < 3; i++) {             //! we are assuming IPV4, so 4 bytes
    //! This will take care of the first 3 bytes
    //! zero out the character buffer since we don't know how long the string will be
    for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }   
 8048bcd:	c6 45 e5 00          	movb   $0x0,-0x1b(%ebp)
 8048bd1:	c6 45 e6 00          	movb   $0x0,-0x1a(%ebp)
 8048bd5:	c6 45 e7 00          	movb   $0x0,-0x19(%ebp)
    sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
 8048bd9:	50                   	push   %eax
 8048bda:	68 9c ad 04 08       	push   $0x804ad9c
 8048bdf:	56                   	push   %esi
 8048be0:	e8 2b fc ff ff       	call   8048810 <sprintf@plt>
    destString =(int8 *) strcat((char *)strBuf,(char *) cBuf);
 8048be5:	58                   	pop    %eax
 8048be6:	5a                   	pop    %edx
 8048be7:	56                   	push   %esi
 8048be8:	53                   	push   %ebx
 8048be9:	e8 62 fb ff ff       	call   8048750 <strcat@plt>
    destString = (int8 *)strcat((char *)strBuf,(char *) ".");
 8048bee:	59                   	pop    %ecx
 8048bef:	58                   	pop    %eax
 8048bf0:	68 37 a7 04 08       	push   $0x804a737
 8048bf5:	53                   	push   %ebx
 8048bf6:	e8 55 fb ff ff       	call   8048750 <strcat@plt>
  uint8         ii;                    //! loop counter
  int8         cBuf[4];                //! character buffer
  int8         *destString;

  strBuf[0] = 0;                        //! make  strcat think the array is empty
  for (i = 0; i < 3; i++) {             //! we are assuming IPV4, so 4 bytes
 8048bfb:	83 c4 10             	add    $0x10,%esp
 8048bfe:	83 ff 03             	cmp    $0x3,%edi
 8048c01:	75 bd                	jne    8048bc0 <rsi_bytes4_to_ascii_dot_addr+0x14>
    destString = (int8 *)strcat((char *)strBuf,(char *) ".");
  }
  //! take care of the last entry outside the loop, there is no . after the last octet
  //! zero out the character buffer since we don't know how long the string will be
  for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }      
  sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
 8048c03:	8b 55 08             	mov    0x8(%ebp),%edx
 8048c06:	50                   	push   %eax
    destString =(int8 *) strcat((char *)strBuf,(char *) cBuf);
    destString = (int8 *)strcat((char *)strBuf,(char *) ".");
  }
  //! take care of the last entry outside the loop, there is no . after the last octet
  //! zero out the character buffer since we don't know how long the string will be
  for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }      
 8048c07:	c6 45 e4 00          	movb   $0x0,-0x1c(%ebp)
  sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
 8048c0b:	0f b6 42 03          	movzbl 0x3(%edx),%eax
    destString =(int8 *) strcat((char *)strBuf,(char *) cBuf);
    destString = (int8 *)strcat((char *)strBuf,(char *) ".");
  }
  //! take care of the last entry outside the loop, there is no . after the last octet
  //! zero out the character buffer since we don't know how long the string will be
  for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }      
 8048c0f:	c6 45 e5 00          	movb   $0x0,-0x1b(%ebp)
 8048c13:	c6 45 e6 00          	movb   $0x0,-0x1a(%ebp)
 8048c17:	c6 45 e7 00          	movb   $0x0,-0x19(%ebp)
  sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
 8048c1b:	50                   	push   %eax
 8048c1c:	68 9c ad 04 08       	push   $0x804ad9c
 8048c21:	56                   	push   %esi
 8048c22:	e8 e9 fb ff ff       	call   8048810 <sprintf@plt>
  destString = (int8 *) strcat((char *)strBuf,(char *) cBuf);
 8048c27:	58                   	pop    %eax
 8048c28:	5a                   	pop    %edx
 8048c29:	56                   	push   %esi
 8048c2a:	53                   	push   %ebx
 8048c2b:	e8 20 fb ff ff       	call   8048750 <strcat@plt>
  return destString;
}
 8048c30:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048c33:	5b                   	pop    %ebx
 8048c34:	5e                   	pop    %esi
 8048c35:	5f                   	pop    %edi
 8048c36:	5d                   	pop    %ebp
 8048c37:	c3                   	ret    

08048c38 <asciihex_2_num>:
 * @param[in]  int8 ascii_hex_in, byte in ascii hex format
 * @return     value in hex num
 */
 
int8 asciihex_2_num(int8 ascii_hex_in)
{
 8048c38:	55                   	push   %ebp
 8048c39:	89 e5                	mov    %esp,%ebp
 8048c3b:	8a 55 08             	mov    0x8(%ebp),%dl
   if((ascii_hex_in >= '0') && (ascii_hex_in <= '9'))
 8048c3e:	8d 42 d0             	lea    -0x30(%edx),%eax
 8048c41:	3c 09                	cmp    $0x9,%al
 8048c43:	76 1a                	jbe    8048c5f <asciihex_2_num+0x27>
      return (ascii_hex_in - '0');
   if((ascii_hex_in >= 'A') && (ascii_hex_in <= 'F'))
 8048c45:	8d 42 bf             	lea    -0x41(%edx),%eax
 8048c48:	3c 05                	cmp    $0x5,%al
 8048c4a:	77 05                	ja     8048c51 <asciihex_2_num+0x19>
      return (ascii_hex_in - 'A' + 10);
 8048c4c:	8d 42 c9             	lea    -0x37(%edx),%eax
 8048c4f:	eb 0e                	jmp    8048c5f <asciihex_2_num+0x27>
   if((ascii_hex_in >= 'a') && (ascii_hex_in <= 'f'))      
 8048c51:	8d 4a 9f             	lea    -0x61(%edx),%ecx
      return (ascii_hex_in - 'a' + 10);
 8048c54:	31 c0                	xor    %eax,%eax
 8048c56:	83 ea 57             	sub    $0x57,%edx
 8048c59:	80 f9 05             	cmp    $0x5,%cl
 8048c5c:	0f 46 c2             	cmovbe %edx,%eax
   
   return 0;
}
 8048c5f:	5d                   	pop    %ebp
 8048c60:	c3                   	ret    

08048c61 <rsi_charhex_2_dec>:
 * @brief         Convert given ASCII hex notation to descimal notation (used for mac address)
 * @param[in]     int8 *cBuf, ASCII hex notation string
 * @return        value in integer
 */
int8 rsi_charhex_2_dec ( int8 *cBuf)
{
 8048c61:	55                   	push   %ebp
   int8 k=0;
   uint8 i;
   for(i=0;i<strlen((char*)cBuf);i++)
 8048c62:	31 c0                	xor    %eax,%eax
 * @brief         Convert given ASCII hex notation to descimal notation (used for mac address)
 * @param[in]     int8 *cBuf, ASCII hex notation string
 * @return        value in integer
 */
int8 rsi_charhex_2_dec ( int8 *cBuf)
{
 8048c64:	89 e5                	mov    %esp,%ebp
   int8 k=0;
   uint8 i;
   for(i=0;i<strlen((char*)cBuf);i++)
 8048c66:	83 c9 ff             	or     $0xffffffff,%ecx
 * @brief         Convert given ASCII hex notation to descimal notation (used for mac address)
 * @param[in]     int8 *cBuf, ASCII hex notation string
 * @return        value in integer
 */
int8 rsi_charhex_2_dec ( int8 *cBuf)
{
 8048c69:	57                   	push   %edi
   int8 k=0;
   uint8 i;
   for(i=0;i<strlen((char*)cBuf);i++)
 8048c6a:	8b 7d 08             	mov    0x8(%ebp),%edi
 * @brief         Convert given ASCII hex notation to descimal notation (used for mac address)
 * @param[in]     int8 *cBuf, ASCII hex notation string
 * @return        value in integer
 */
int8 rsi_charhex_2_dec ( int8 *cBuf)
{
 8048c6d:	56                   	push   %esi
 8048c6e:	53                   	push   %ebx
   int8 k=0;
 8048c6f:	31 db                	xor    %ebx,%ebx
   uint8 i;
   for(i=0;i<strlen((char*)cBuf);i++)
 8048c71:	f2 ae                	repnz scas %es:(%edi),%al
 8048c73:	31 ff                	xor    %edi,%edi
 8048c75:	f7 d1                	not    %ecx
 8048c77:	8d 71 ff             	lea    -0x1(%ecx),%esi
 8048c7a:	eb 14                	jmp    8048c90 <rsi_charhex_2_dec+0x2f>
    {
      k = ((k*16) + asciihex_2_num(cBuf[i])); 
 8048c7c:	8b 55 08             	mov    0x8(%ebp),%edx
 8048c7f:	c1 e3 04             	shl    $0x4,%ebx
 */
int8 rsi_charhex_2_dec ( int8 *cBuf)
{
   int8 k=0;
   uint8 i;
   for(i=0;i<strlen((char*)cBuf);i++)
 8048c82:	47                   	inc    %edi
    {
      k = ((k*16) + asciihex_2_num(cBuf[i])); 
 8048c83:	0f be 04 02          	movsbl (%edx,%eax,1),%eax
 8048c87:	50                   	push   %eax
 8048c88:	e8 ab ff ff ff       	call   8048c38 <asciihex_2_num>
 8048c8d:	5a                   	pop    %edx
 8048c8e:	01 c3                	add    %eax,%ebx
 */
int8 rsi_charhex_2_dec ( int8 *cBuf)
{
   int8 k=0;
   uint8 i;
   for(i=0;i<strlen((char*)cBuf);i++)
 8048c90:	89 fa                	mov    %edi,%edx
 8048c92:	0f b6 c2             	movzbl %dl,%eax
 8048c95:	39 f0                	cmp    %esi,%eax
 8048c97:	72 e3                	jb     8048c7c <rsi_charhex_2_dec+0x1b>
    {
      k = ((k*16) + asciihex_2_num(cBuf[i])); 
     }
    return k;
}    
 8048c99:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048c9c:	88 d8                	mov    %bl,%al
 8048c9e:	5b                   	pop    %ebx
 8048c9f:	5e                   	pop    %esi
 8048ca0:	5f                   	pop    %edi
 8048ca1:	5d                   	pop    %ebp
 8048ca2:	c3                   	ret    

08048ca3 <rsi_ascii_mac_address_to_6bytes>:
 * @param[in      int8 *asciiMacFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr, converted address is returned here 
 * @return        none
 */
void rsi_ascii_mac_address_to_6bytes(uint8 *hexAddr, int8 *asciiMacAddress)
{
 8048ca3:	55                   	push   %ebp
  uint8         cBufPos;            //! which char in the ASCII representation
  uint8         byteNum;            //! which byte in the 32BitHexAddress
  int8         cBuf[6];             //! temporary buffer

  byteNum = 0;
  cBufPos = 0;
 8048ca4:	31 d2                	xor    %edx,%edx
 * @param[in      int8 *asciiMacFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr, converted address is returned here 
 * @return        none
 */
void rsi_ascii_mac_address_to_6bytes(uint8 *hexAddr, int8 *asciiMacAddress)
{
 8048ca6:	89 e5                	mov    %esp,%ebp
 8048ca8:	57                   	push   %edi
 8048ca9:	56                   	push   %esi
  uint8         i;                  //! loop counter
  uint8         cBufPos;            //! which char in the ASCII representation
  uint8         byteNum;            //! which byte in the 32BitHexAddress
  int8         cBuf[6];             //! temporary buffer

  byteNum = 0;
 8048caa:	31 f6                	xor    %esi,%esi
 * @param[in      int8 *asciiMacFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr, converted address is returned here 
 * @return        none
 */
void rsi_ascii_mac_address_to_6bytes(uint8 *hexAddr, int8 *asciiMacAddress)
{
 8048cac:	53                   	push   %ebx
 8048cad:	83 ec 14             	sub    $0x14,%esp
  uint8         byteNum;            //! which byte in the 32BitHexAddress
  int8         cBuf[6];             //! temporary buffer

  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
 8048cb0:	c6 45 e3 00          	movb   $0x0,-0x1d(%ebp)
 8048cb4:	eb 36                	jmp    8048cec <rsi_ascii_mac_address_to_6bytes+0x49>
    //! this will take care of the first 5 octets
    if (asciiMacAddress[i] == ':') {      //! we are at the end of the address octet
 8048cb6:	8b 4d 0c             	mov    0xc(%ebp),%ecx
 8048cb9:	8a 04 19             	mov    (%ecx,%ebx,1),%al
 8048cbc:	3c 3a                	cmp    $0x3a,%al
 8048cbe:	75 21                	jne    8048ce1 <rsi_ascii_mac_address_to_6bytes+0x3e>
      cBuf[cBufPos] = 0;                  //! terminate the string
      cBufPos = 0;                        //! reset for the next char
      hexAddr[byteNum++] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);   //! convert the strint to an integer
 8048cc0:	8d 4d ee             	lea    -0x12(%ebp),%ecx
  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
    //! this will take care of the first 5 octets
    if (asciiMacAddress[i] == ':') {      //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                  //! terminate the string
 8048cc3:	0f b6 d2             	movzbl %dl,%edx
      cBufPos = 0;                        //! reset for the next char
      hexAddr[byteNum++] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);   //! convert the strint to an integer
 8048cc6:	89 f0                	mov    %esi,%eax
 8048cc8:	46                   	inc    %esi
 8048cc9:	51                   	push   %ecx
 8048cca:	0f b6 d8             	movzbl %al,%ebx
 8048ccd:	03 5d 08             	add    0x8(%ebp),%ebx
  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
    //! this will take care of the first 5 octets
    if (asciiMacAddress[i] == ':') {      //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                  //! terminate the string
 8048cd0:	c6 44 15 ee 00       	movb   $0x0,-0x12(%ebp,%edx,1)
      cBufPos = 0;                        //! reset for the next char
      hexAddr[byteNum++] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);   //! convert the strint to an integer
 8048cd5:	e8 87 ff ff ff       	call   8048c61 <rsi_charhex_2_dec>
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
    //! this will take care of the first 5 octets
    if (asciiMacAddress[i] == ':') {      //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                  //! terminate the string
      cBufPos = 0;                        //! reset for the next char
 8048cda:	31 d2                	xor    %edx,%edx
      hexAddr[byteNum++] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);   //! convert the strint to an integer
 8048cdc:	5f                   	pop    %edi
 8048cdd:	88 03                	mov    %al,(%ebx)
 8048cdf:	eb 08                	jmp    8048ce9 <rsi_ascii_mac_address_to_6bytes+0x46>
    }
    else {
      cBuf[cBufPos++] = asciiMacAddress[i];
 8048ce1:	0f b6 ca             	movzbl %dl,%ecx
 8048ce4:	42                   	inc    %edx
 8048ce5:	88 44 0d ee          	mov    %al,-0x12(%ebp,%ecx,1)
  uint8         byteNum;            //! which byte in the 32BitHexAddress
  int8         cBuf[6];             //! temporary buffer

  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
 8048ce9:	fe 45 e3             	incb   -0x1d(%ebp)
 8048cec:	8b 7d 0c             	mov    0xc(%ebp),%edi
 8048cef:	31 c0                	xor    %eax,%eax
 8048cf1:	83 c9 ff             	or     $0xffffffff,%ecx
 8048cf4:	0f b6 5d e3          	movzbl -0x1d(%ebp),%ebx
 8048cf8:	f2 ae                	repnz scas %es:(%edi),%al
 8048cfa:	f7 d1                	not    %ecx
 8048cfc:	49                   	dec    %ecx
 8048cfd:	39 cb                	cmp    %ecx,%ebx
 8048cff:	72 b5                	jb     8048cb6 <rsi_ascii_mac_address_to_6bytes+0x13>
      cBuf[cBufPos++] = asciiMacAddress[i];
    }
  }
  //! handle the last octet                  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                     //! terminate the string
  hexAddr[byteNum] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);      //! convert the strint to an integer
 8048d01:	8d 45 ee             	lea    -0x12(%ebp),%eax
    else {
      cBuf[cBufPos++] = asciiMacAddress[i];
    }
  }
  //! handle the last octet                  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                     //! terminate the string
 8048d04:	0f b6 d2             	movzbl %dl,%edx
  hexAddr[byteNum] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);      //! convert the strint to an integer
 8048d07:	50                   	push   %eax
 8048d08:	81 e6 ff 00 00 00    	and    $0xff,%esi
 8048d0e:	03 75 08             	add    0x8(%ebp),%esi
    else {
      cBuf[cBufPos++] = asciiMacAddress[i];
    }
  }
  //! handle the last octet                  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                     //! terminate the string
 8048d11:	c6 44 15 ee 00       	movb   $0x0,-0x12(%ebp,%edx,1)
  hexAddr[byteNum] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);      //! convert the strint to an integer
 8048d16:	e8 46 ff ff ff       	call   8048c61 <rsi_charhex_2_dec>
 8048d1b:	59                   	pop    %ecx
 8048d1c:	88 06                	mov    %al,(%esi)
}
 8048d1e:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048d21:	5b                   	pop    %ebx
 8048d22:	5e                   	pop    %esi
 8048d23:	5f                   	pop    %edi
 8048d24:	5d                   	pop    %ebp
 8048d25:	c3                   	ret    

08048d26 <rsi_ascii_dot_address_to_4bytes>:
 * @param[in]     int8 *asciiDotFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr,   Output value is passed back in the 4-byte Hex Address
 * @return        none
 */
void rsi_ascii_dot_address_to_4bytes(uint8 *hexAddr, int8 *asciiDotAddress)
{
 8048d26:	55                   	push   %ebp
  //! which byte in the 32BitHexAddress
  int8         cBuf[4];                                       
  //! character buffer

  byteNum = 0;
  cBufPos = 0;
 8048d27:	31 d2                	xor    %edx,%edx
 * @param[in]     int8 *asciiDotFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr,   Output value is passed back in the 4-byte Hex Address
 * @return        none
 */
void rsi_ascii_dot_address_to_4bytes(uint8 *hexAddr, int8 *asciiDotAddress)
{
 8048d29:	89 e5                	mov    %esp,%ebp
 8048d2b:	57                   	push   %edi
 8048d2c:	56                   	push   %esi
 8048d2d:	53                   	push   %ebx
  uint8         byteNum;                                       
  //! which byte in the 32BitHexAddress
  int8         cBuf[4];                                       
  //! character buffer

  byteNum = 0;
 8048d2e:	31 db                	xor    %ebx,%ebx
 * @param[in]     int8 *asciiDotFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr,   Output value is passed back in the 4-byte Hex Address
 * @return        none
 */
void rsi_ascii_dot_address_to_4bytes(uint8 *hexAddr, int8 *asciiDotAddress)
{
 8048d30:	83 ec 2c             	sub    $0x2c,%esp
  int8         cBuf[4];                                       
  //! character buffer

  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiDotAddress); i++) {
 8048d33:	c6 45 d7 00          	movb   $0x0,-0x29(%ebp)
 8048d37:	eb 39                	jmp    8048d72 <rsi_ascii_dot_address_to_4bytes+0x4c>
    //! this will take care of the first 3 octets
    if (asciiDotAddress[i] == '.') {                              
 8048d39:	8b 4d 0c             	mov    0xc(%ebp),%ecx
 8048d3c:	8a 04 31             	mov    (%ecx,%esi,1),%al
 8048d3f:	3c 2e                	cmp    $0x2e,%al
 8048d41:	75 24                	jne    8048d67 <rsi_ascii_dot_address_to_4bytes+0x41>
       //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                                       
      //! terminate the string
      cBufPos = 0;                                          
      //! reset for the next char
      hexAddr[byteNum++] = (uint8)atoi((char *)cBuf);                        
 8048d43:	83 ec 0c             	sub    $0xc,%esp
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiDotAddress); i++) {
    //! this will take care of the first 3 octets
    if (asciiDotAddress[i] == '.') {                              
       //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                                       
 8048d46:	0f b6 d2             	movzbl %dl,%edx
      //! terminate the string
      cBufPos = 0;                                          
      //! reset for the next char
      hexAddr[byteNum++] = (uint8)atoi((char *)cBuf);                        
 8048d49:	8d 45 e4             	lea    -0x1c(%ebp),%eax
 8048d4c:	0f b6 f3             	movzbl %bl,%esi
 8048d4f:	50                   	push   %eax
 8048d50:	43                   	inc    %ebx
 8048d51:	03 75 08             	add    0x8(%ebp),%esi
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiDotAddress); i++) {
    //! this will take care of the first 3 octets
    if (asciiDotAddress[i] == '.') {                              
       //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                                       
 8048d54:	c6 44 15 e4 00       	movb   $0x0,-0x1c(%ebp,%edx,1)
      //! terminate the string
      cBufPos = 0;                                          
      //! reset for the next char
      hexAddr[byteNum++] = (uint8)atoi((char *)cBuf);                        
 8048d59:	e8 d2 fa ff ff       	call   8048830 <atoi@plt>
 8048d5e:	83 c4 10             	add    $0x10,%esp
    //! this will take care of the first 3 octets
    if (asciiDotAddress[i] == '.') {                              
       //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                                       
      //! terminate the string
      cBufPos = 0;                                          
 8048d61:	31 d2                	xor    %edx,%edx
      //! reset for the next char
      hexAddr[byteNum++] = (uint8)atoi((char *)cBuf);                        
 8048d63:	88 06                	mov    %al,(%esi)
 8048d65:	eb 08                	jmp    8048d6f <rsi_ascii_dot_address_to_4bytes+0x49>
      //! convert the strint to an integer
    }
    else {
      cBuf[cBufPos++] = asciiDotAddress[i];
 8048d67:	0f b6 ca             	movzbl %dl,%ecx
 8048d6a:	42                   	inc    %edx
 8048d6b:	88 44 0d e4          	mov    %al,-0x1c(%ebp,%ecx,1)
  int8         cBuf[4];                                       
  //! character buffer

  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiDotAddress); i++) {
 8048d6f:	fe 45 d7             	incb   -0x29(%ebp)
 8048d72:	8b 7d 0c             	mov    0xc(%ebp),%edi
 8048d75:	31 c0                	xor    %eax,%eax
 8048d77:	83 c9 ff             	or     $0xffffffff,%ecx
 8048d7a:	0f b6 75 d7          	movzbl -0x29(%ebp),%esi
 8048d7e:	f2 ae                	repnz scas %es:(%edi),%al
 8048d80:	f7 d1                	not    %ecx
 8048d82:	49                   	dec    %ecx
 8048d83:	39 ce                	cmp    %ecx,%esi
 8048d85:	72 b2                	jb     8048d39 <rsi_ascii_dot_address_to_4bytes+0x13>
  }
  //! handle the last octet                                       
  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                                          
  //! terminate the string
  hexAddr[byteNum] = (uint8)atoi((char *)cBuf);                              
 8048d87:	83 ec 0c             	sub    $0xc,%esp
      cBuf[cBufPos++] = asciiDotAddress[i];
    }
  }
  //! handle the last octet                                       
  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                                          
 8048d8a:	0f b6 d2             	movzbl %dl,%edx
  //! terminate the string
  hexAddr[byteNum] = (uint8)atoi((char *)cBuf);                              
 8048d8d:	8d 45 e4             	lea    -0x1c(%ebp),%eax
 8048d90:	0f b6 db             	movzbl %bl,%ebx
 8048d93:	50                   	push   %eax
 8048d94:	03 5d 08             	add    0x8(%ebp),%ebx
      cBuf[cBufPos++] = asciiDotAddress[i];
    }
  }
  //! handle the last octet                                       
  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                                          
 8048d97:	c6 44 15 e4 00       	movb   $0x0,-0x1c(%ebp,%edx,1)
  //! terminate the string
  hexAddr[byteNum] = (uint8)atoi((char *)cBuf);                              
 8048d9c:	e8 8f fa ff ff       	call   8048830 <atoi@plt>
 8048da1:	83 c4 10             	add    $0x10,%esp
 8048da4:	88 03                	mov    %al,(%ebx)
  //! convert the strint to an integer
}
 8048da6:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048da9:	5b                   	pop    %ebx
 8048daa:	5e                   	pop    %esi
 8048dab:	5f                   	pop    %edi
 8048dac:	5d                   	pop    %ebp
 8048dad:	c3                   	ret    

08048dae <rs22_aToi>:
src_len          |  X  |     |     | len of the string

*END****************************************************************************/

uint16 rs22_aToi(uint8 *src, uint8 src_len)
{
 8048dae:	55                   	push   %ebp
   uint16 src_index = 0;
   uint16 temp = 0;
   
   for(src_index = 0; src_index < src_len; src_index++)
 8048daf:	31 d2                	xor    %edx,%edx
src_len          |  X  |     |     | len of the string

*END****************************************************************************/

uint16 rs22_aToi(uint8 *src, uint8 src_len)
{
 8048db1:	89 e5                	mov    %esp,%ebp
   uint16 src_index = 0;
   uint16 temp = 0;
 8048db3:	31 c0                	xor    %eax,%eax
src_len          |  X  |     |     | len of the string

*END****************************************************************************/

uint16 rs22_aToi(uint8 *src, uint8 src_len)
{
 8048db5:	56                   	push   %esi
   uint16 src_index = 0;
   uint16 temp = 0;
   
   for(src_index = 0; src_index < src_len; src_index++)
 8048db6:	0f b6 4d 0c          	movzbl 0xc(%ebp),%ecx
src_len          |  X  |     |     | len of the string

*END****************************************************************************/

uint16 rs22_aToi(uint8 *src, uint8 src_len)
{
 8048dba:	53                   	push   %ebx
   uint16 src_index = 0;
   uint16 temp = 0;
   
   for(src_index = 0; src_index < src_len; src_index++)
 8048dbb:	eb 0f                	jmp    8048dcc <rs22_aToi+0x1e>
   {
      temp = temp*10;
      temp = temp + (src[src_index] - 0x30);
 8048dbd:	8b 75 08             	mov    0x8(%ebp),%esi
   uint16 src_index = 0;
   uint16 temp = 0;
   
   for(src_index = 0; src_index < src_len; src_index++)
   {
      temp = temp*10;
 8048dc0:	6b c0 0a             	imul   $0xa,%eax,%eax
      temp = temp + (src[src_index] - 0x30);
 8048dc3:	0f b6 1c 16          	movzbl (%esi,%edx,1),%ebx
 8048dc7:	42                   	inc    %edx
 8048dc8:	8d 44 18 d0          	lea    -0x30(%eax,%ebx,1),%eax
uint16 rs22_aToi(uint8 *src, uint8 src_len)
{
   uint16 src_index = 0;
   uint16 temp = 0;
   
   for(src_index = 0; src_index < src_len; src_index++)
 8048dcc:	66 39 d1             	cmp    %dx,%cx
 8048dcf:	77 ec                	ja     8048dbd <rs22_aToi+0xf>
      temp = temp*10;
      temp = temp + (src[src_index] - 0x30);
   }

   return temp;
}
 8048dd1:	5b                   	pop    %ebx
 8048dd2:	5e                   	pop    %esi
 8048dd3:	5d                   	pop    %ebp
 8048dd4:	c3                   	ret    

08048dd5 <rsi_strrev>:
 * @return      zero
 * @section description 
 * This function is used to reverse the string  
 */
uint8 rsi_strrev(void *src, void *dst, uint8 len)
{
 8048dd5:	55                   	push   %ebp
 8048dd6:	89 e5                	mov    %esp,%ebp
 8048dd8:	57                   	push   %edi
 8048dd9:	56                   	push   %esi
 8048dda:	53                   	push   %ebx
 8048ddb:	51                   	push   %ecx
 8048ddc:	8a 45 10             	mov    0x10(%ebp),%al
 8048ddf:	8b 75 0c             	mov    0xc(%ebp),%esi
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
     
   src1 = src1 + len - 1;
 8048de2:	0f b6 c8             	movzbl %al,%ecx
 * @return      zero
 * @section description 
 * This function is used to reverse the string  
 */
uint8 rsi_strrev(void *src, void *dst, uint8 len)
{
 8048de5:	88 45 f3             	mov    %al,-0xd(%ebp)
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
     
   src1 = src1 + len - 1;
 8048de8:	8d 51 ff             	lea    -0x1(%ecx),%edx
     
   while(len-- != 0)
 8048deb:	31 c0                	xor    %eax,%eax
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
     
   src1 = src1 + len - 1;
 8048ded:	03 55 08             	add    0x8(%ebp),%edx
     
   while(len-- != 0)
 8048df0:	eb 0b                	jmp    8048dfd <rsi_strrev+0x28>
        *dst1++ = *src1--;
 8048df2:	8a 1c 02             	mov    (%edx,%eax,1),%bl
 * @param[in]   length of the string 
 * @return      zero
 * @section description 
 * This function is used to reverse the string  
 */
uint8 rsi_strrev(void *src, void *dst, uint8 len)
 8048df5:	89 c7                	mov    %eax,%edi
 8048df7:	48                   	dec    %eax
 8048df8:	f7 df                	neg    %edi
   src1 = src;
     
   src1 = src1 + len - 1;
     
   while(len-- != 0)
        *dst1++ = *src1--;
 8048dfa:	88 1c 3e             	mov    %bl,(%esi,%edi,1)
   dst1 = dst;
   src1 = src;
     
   src1 = src1 + len - 1;
     
   while(len-- != 0)
 8048dfd:	8a 5d f3             	mov    -0xd(%ebp),%bl
 8048e00:	8d 3c 03             	lea    (%ebx,%eax,1),%edi
 8048e03:	89 fb                	mov    %edi,%ebx
 8048e05:	84 db                	test   %bl,%bl
 8048e07:	75 e9                	jne    8048df2 <rsi_strrev+0x1d>
        *dst1++ = *src1--;
   *dst1 = '\0';
 8048e09:	c6 04 0e 00          	movb   $0x0,(%esi,%ecx,1)
   return 0;
}
 8048e0d:	31 c0                	xor    %eax,%eax
 8048e0f:	5a                   	pop    %edx
 8048e10:	5b                   	pop    %ebx
 8048e11:	5e                   	pop    %esi
 8048e12:	5f                   	pop    %edi
 8048e13:	5d                   	pop    %ebp
 8048e14:	c3                   	ret    

08048e15 <rsi_strcat>:
 * @section description 
 * This function is used to concatinate the source string to 
 * destination string  
 */
void rsi_strcat(void *src, void *dst, uint8 len)
{
 8048e15:	55                   	push   %ebp
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
  
   while(len-- != 0)
 8048e16:	31 c0                	xor    %eax,%eax
 * @section description 
 * This function is used to concatinate the source string to 
 * destination string  
 */
void rsi_strcat(void *src, void *dst, uint8 len)
{
 8048e18:	89 e5                	mov    %esp,%ebp
 8048e1a:	56                   	push   %esi
 8048e1b:	8a 55 10             	mov    0x10(%ebp),%dl
 8048e1e:	53                   	push   %ebx
 8048e1f:	8b 5d 08             	mov    0x8(%ebp),%ebx
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
  
   while(len-- != 0)
 8048e22:	eb 0a                	jmp    8048e2e <rsi_strcat+0x19>
    *dst1++ = *src1++;
 8048e24:	8a 0c 03             	mov    (%ebx,%eax,1),%cl
 8048e27:	8b 75 0c             	mov    0xc(%ebp),%esi
 8048e2a:	88 0c 06             	mov    %cl,(%esi,%eax,1)
 8048e2d:	40                   	inc    %eax
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
  
   while(len-- != 0)
 8048e2e:	38 c2                	cmp    %al,%dl
 8048e30:	75 f2                	jne    8048e24 <rsi_strcat+0xf>
    *dst1++ = *src1++;
   
}
 8048e32:	5b                   	pop    %ebx
 8048e33:	5e                   	pop    %esi
 8048e34:	5d                   	pop    %ebp
 8048e35:	c3                   	ret    

08048e36 <rsi_convert_ip_to_string>:
 * @return      none
 * @section description 
 * This function is used to convert ip address to string  
 */
uint16 rsi_convert_ip_to_string(uint8 *num_buff, uint8 *ip_buff)
{
 8048e36:	55                   	push   %ebp
   uint16 temp;
   uint16 num_index = 0, ip_index = 0;
   uint16 temp_index = 0, temp_index2 = 0;
    
    
   memset(ip_buff, 0, 17);
 8048e37:	b9 11 00 00 00       	mov    $0x11,%ecx
 * @return      none
 * @section description 
 * This function is used to convert ip address to string  
 */
uint16 rsi_convert_ip_to_string(uint8 *num_buff, uint8 *ip_buff)
{
 8048e3c:	89 e5                	mov    %esp,%ebp
   uint16 temp;
   uint16 num_index = 0, ip_index = 0;
   uint16 temp_index = 0, temp_index2 = 0;
    
    
   memset(ip_buff, 0, 17);
 8048e3e:	31 c0                	xor    %eax,%eax
 * @return      none
 * @section description 
 * This function is used to convert ip address to string  
 */
uint16 rsi_convert_ip_to_string(uint8 *num_buff, uint8 *ip_buff)
{
 8048e40:	57                   	push   %edi
 8048e41:	56                   	push   %esi
 8048e42:	53                   	push   %ebx
   uint16 temp;
   uint16 num_index = 0, ip_index = 0;
   uint16 temp_index = 0, temp_index2 = 0;
    
    
   memset(ip_buff, 0, 17);
 8048e43:	31 db                	xor    %ebx,%ebx
 * @return      none
 * @section description 
 * This function is used to convert ip address to string  
 */
uint16 rsi_convert_ip_to_string(uint8 *num_buff, uint8 *ip_buff)
{
 8048e45:	83 ec 20             	sub    $0x20,%esp
   uint16 temp;
   uint16 num_index = 0, ip_index = 0;
   uint16 temp_index = 0, temp_index2 = 0;
    
    
   memset(ip_buff, 0, 17);
 8048e48:	8b 7d 0c             	mov    0xc(%ebp),%edi
 8048e4b:	f3 aa                	rep stos %al,%es:(%edi)
uint16 rsi_convert_ip_to_string(uint8 *num_buff, uint8 *ip_buff)
{
    uint8 temp_buf[8];
   uint8 temp_buf2[8];
   uint16 temp;
   uint16 num_index = 0, ip_index = 0;
 8048e4d:	66 c7 45 e2 00 00    	movw   $0x0,-0x1e(%ebp)
    
    
   memset(ip_buff, 0, 17);
   while (num_index < 4)
   {
      temp = num_buff[num_index++];
 8048e53:	8b 45 08             	mov    0x8(%ebp),%eax
 8048e56:	31 c9                	xor    %ecx,%ecx
 8048e58:	66 8b 75 e2          	mov    -0x1e(%ebp),%si
 8048e5c:	0f b6 04 18          	movzbl (%eax,%ebx,1),%eax
 8048e60:	66 89 45 da          	mov    %ax,-0x26(%ebp)
 8048e64:	eb 02                	jmp    8048e68 <rsi_convert_ip_to_string+0x32>

      do
      {
         temp_buf[temp_index++] = (temp%10) + '0';
         temp = temp/10;
         ip_index++;
 8048e66:	89 fe                	mov    %edi,%esi
      temp = num_buff[num_index++];
      

      do
      {
         temp_buf[temp_index++] = (temp%10) + '0';
 8048e68:	66 8b 45 da          	mov    -0x26(%ebp),%ax
 8048e6c:	0f b7 f9             	movzwl %cx,%edi
 8048e6f:	31 d2                	xor    %edx,%edx
 8048e71:	89 7d d4             	mov    %edi,-0x2c(%ebp)
 8048e74:	bf 0a 00 00 00       	mov    $0xa,%edi
 8048e79:	41                   	inc    %ecx
 8048e7a:	66 f7 f7             	div    %di
 8048e7d:	8b 7d d4             	mov    -0x2c(%ebp),%edi
 8048e80:	66 89 55 d8          	mov    %dx,-0x28(%ebp)
 8048e84:	8a 55 d8             	mov    -0x28(%ebp),%dl
 8048e87:	66 89 45 da          	mov    %ax,-0x26(%ebp)
 8048e8b:	83 c2 30             	add    $0x30,%edx
         temp = temp/10;
         ip_index++;
      }while(temp);
 8048e8e:	66 85 c0             	test   %ax,%ax
      temp = num_buff[num_index++];
      

      do
      {
         temp_buf[temp_index++] = (temp%10) + '0';
 8048e91:	88 54 3d e4          	mov    %dl,-0x1c(%ebp,%edi,1)
         temp = temp/10;
         ip_index++;
 8048e95:	8d 7e 01             	lea    0x1(%esi),%edi
      }while(temp);
 8048e98:	75 cc                	jne    8048e66 <rsi_convert_ip_to_string+0x30>
      rsi_strrev(temp_buf, temp_buf2, temp_index);
 8048e9a:	0f b6 c9             	movzbl %cl,%ecx
 8048e9d:	51                   	push   %ecx
 8048e9e:	8d 45 ec             	lea    -0x14(%ebp),%eax
 8048ea1:	50                   	push   %eax
 8048ea2:	8d 55 e4             	lea    -0x1c(%ebp),%edx
 8048ea5:	52                   	push   %edx
 8048ea6:	89 4d dc             	mov    %ecx,-0x24(%ebp)
 8048ea9:	e8 27 ff ff ff       	call   8048dd5 <rsi_strrev>
       rsi_strcat(temp_buf2, ip_buff + temp_index2, temp_index);
 8048eae:	8b 4d dc             	mov    -0x24(%ebp),%ecx
 8048eb1:	0f b7 45 e2          	movzwl -0x1e(%ebp),%eax
 8048eb5:	03 45 0c             	add    0xc(%ebp),%eax
 8048eb8:	51                   	push   %ecx
 8048eb9:	50                   	push   %eax
 8048eba:	8d 45 ec             	lea    -0x14(%ebp),%eax
 8048ebd:	50                   	push   %eax
 8048ebe:	e8 52 ff ff ff       	call   8048e15 <rsi_strcat>
      
      temp_index = 0;
        if (num_index < 4)
 8048ec3:	83 c4 18             	add    $0x18,%esp
 8048ec6:	83 fb 03             	cmp    $0x3,%ebx
 8048ec9:	74 17                	je     8048ee2 <rsi_convert_ip_to_string+0xac>
           ip_buff[ip_index++] = '.';
 8048ecb:	8b 55 0c             	mov    0xc(%ebp),%edx
 8048ece:	0f b7 ff             	movzwl %di,%edi
 8048ed1:	83 c6 02             	add    $0x2,%esi
 8048ed4:	66 89 75 e2          	mov    %si,-0x1e(%ebp)
 8048ed8:	43                   	inc    %ebx
 8048ed9:	c6 04 3a 2e          	movb   $0x2e,(%edx,%edi,1)
 8048edd:	e9 71 ff ff ff       	jmp    8048e53 <rsi_convert_ip_to_string+0x1d>
         temp_index2 = ip_index;
         
   }
   
   return ip_index;
}
 8048ee2:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048ee5:	89 f8                	mov    %edi,%eax
 8048ee7:	5b                   	pop    %ebx
 8048ee8:	5e                   	pop    %esi
 8048ee9:	5f                   	pop    %edi
 8048eea:	5d                   	pop    %ebp
 8048eeb:	c3                   	ret    

08048eec <parseHex>:
 * @return      decimal value
 * @section description 
 * This function is used to convert the hex value to decimal value
 */
uint16 parseHex(uint8 *str )
{
 8048eec:	55                   	push   %ebp
 8048eed:	31 c9                	xor    %ecx,%ecx
 8048eef:	89 e5                	mov    %esp,%ebp
    uint16 value = 0;
 8048ef1:	31 c0                	xor    %eax,%eax
 * @return      decimal value
 * @section description 
 * This function is used to convert the hex value to decimal value
 */
uint16 parseHex(uint8 *str )
{
 8048ef3:	53                   	push   %ebx
    uint16 value = 0;
    uint8 i=0;

    for(i= 0 ;i <8 ; i++,++str ) 
      switch( *str )
 8048ef4:	8b 5d 08             	mov    0x8(%ebp),%ebx
 8048ef7:	8a 14 0b             	mov    (%ebx,%ecx,1),%dl
 8048efa:	80 fa 46             	cmp    $0x46,%dl
 8048efd:	77 0f                	ja     8048f0e <parseHex+0x22>
 8048eff:	80 fa 41             	cmp    $0x41,%dl
 8048f02:	73 1e                	jae    8048f22 <parseHex+0x36>
 8048f04:	8d 5a d0             	lea    -0x30(%edx),%ebx
 8048f07:	80 fb 09             	cmp    $0x9,%bl
 8048f0a:	77 29                	ja     8048f35 <parseHex+0x49>
 8048f0c:	eb 0a                	jmp    8048f18 <parseHex+0x2c>
 8048f0e:	8d 5a 9f             	lea    -0x61(%edx),%ebx
 8048f11:	80 fb 05             	cmp    $0x5,%bl
 8048f14:	77 1f                	ja     8048f35 <parseHex+0x49>
 8048f16:	eb 0a                	jmp    8048f22 <parseHex+0x36>
    {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            value = (value << 4) | (*str & 0xf);
 8048f18:	83 e2 0f             	and    $0xf,%edx
 8048f1b:	c1 e0 04             	shl    $0x4,%eax
 8048f1e:	09 d0                	or     %edx,%eax
            break;
 8048f20:	eb 0b                	jmp    8048f2d <parseHex+0x41>
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            value = (value << 4 | 9) + (*str & 0xf);
 8048f22:	c1 e0 04             	shl    $0x4,%eax
 8048f25:	83 e2 0f             	and    $0xf,%edx
 8048f28:	83 c8 09             	or     $0x9,%eax
 8048f2b:	01 d0                	add    %edx,%eax
 8048f2d:	41                   	inc    %ecx
uint16 parseHex(uint8 *str )
{
    uint16 value = 0;
    uint8 i=0;

    for(i= 0 ;i <8 ; i++,++str ) 
 8048f2e:	83 f9 08             	cmp    $0x8,%ecx
 8048f31:	75 c1                	jne    8048ef4 <parseHex+0x8>
            break;
        case '\0':
        default:
            return value;
    }
   return 0;
 8048f33:	31 c0                	xor    %eax,%eax
}
 8048f35:	5b                   	pop    %ebx
 8048f36:	5d                   	pop    %ebp
 8048f37:	c3                   	ret    

08048f38 <parse_ipv6_address>:
 * This function is used to convert IPV6 Address.
 * destination string  
 */

void parse_ipv6_address(uint32 *v6, uint8 *buf)
{
 8048f38:	55                   	push   %ebp
 8048f39:	89 e5                	mov    %esp,%ebp
 8048f3b:	57                   	push   %edi
 8048f3c:	56                   	push   %esi
  uint8 value = 0;
  uint8 offset = 0;
  uint8 index = 0;
  uint16 buffer_offset = 0;
 8048f3d:	31 f6                	xor    %esi,%esi
 * This function is used to convert IPV6 Address.
 * destination string  
 */

void parse_ipv6_address(uint32 *v6, uint8 *buf)
{
 8048f3f:	53                   	push   %ebx
  uint8 index = 0;
  uint16 buffer_offset = 0;
  uint8 temp_buff[10];
  temp_buff[0] = '\0';
  //! Total 8 octets
  for(index = 0; index < 8 ;index++)
 8048f40:	31 db                	xor    %ebx,%ebx
 * This function is used to convert IPV6 Address.
 * destination string  
 */

void parse_ipv6_address(uint32 *v6, uint8 *buf)
{
 8048f42:	83 ec 10             	sub    $0x10,%esp
  uint8 value = 0;
  uint8 offset = 0;
  uint8 index = 0;
  uint16 buffer_offset = 0;
  uint8 temp_buff[10];
  temp_buff[0] = '\0';
 8048f45:	c6 45 ea 00          	movb   $0x0,-0x16(%ebp)
 8048f49:	eb 5f                	jmp    8048faa <parse_ipv6_address+0x72>
  for(index = 0; index < 8 ;index++)
  {
    //! each octet contains max of 5 characters including . dot
    for(offset = 0;offset < 5 ; offset++)
    {
      value = buf[buffer_offset++];
 8048f4b:	8b 7d 0c             	mov    0xc(%ebp),%edi
 8048f4e:	0f b7 d6             	movzwl %si,%edx
 8048f51:	46                   	inc    %esi
 8048f52:	0f b6 c8             	movzbl %al,%ecx
 8048f55:	8a 14 17             	mov    (%edi,%edx,1),%dl
      if(value == '.')
 8048f58:	80 fa 2e             	cmp    $0x2e,%dl
 8048f5b:	74 0f                	je     8048f6c <parse_ipv6_address+0x34>
      {
        break;
      }
      temp_buff[offset] =  value;      
 8048f5d:	88 54 05 ea          	mov    %dl,-0x16(%ebp,%eax,1)
 8048f61:	40                   	inc    %eax
  temp_buff[0] = '\0';
  //! Total 8 octets
  for(index = 0; index < 8 ;index++)
  {
    //! each octet contains max of 5 characters including . dot
    for(offset = 0;offset < 5 ; offset++)
 8048f62:	83 f8 05             	cmp    $0x5,%eax
 8048f65:	75 e4                	jne    8048f4b <parse_ipv6_address+0x13>
 8048f67:	b9 05 00 00 00       	mov    $0x5,%ecx
      temp_buff[offset] =  value;      
    }
    temp_buff[offset]= '\0';
    if(index % 2 == 0)
    {
      v6[index/2] = (parseHex(temp_buff) << 16);
 8048f6c:	8b 55 08             	mov    0x8(%ebp),%edx
 8048f6f:	88 d8                	mov    %bl,%al
 8048f71:	d0 e8                	shr    %al
        break;
      }
      temp_buff[offset] =  value;      
    }
    temp_buff[offset]= '\0';
    if(index % 2 == 0)
 8048f73:	f6 c3 01             	test   $0x1,%bl
    {
      v6[index/2] = (parseHex(temp_buff) << 16);
 8048f76:	0f b6 c0             	movzbl %al,%eax
      {
        break;
      }
      temp_buff[offset] =  value;      
    }
    temp_buff[offset]= '\0';
 8048f79:	c6 44 0d ea 00       	movb   $0x0,-0x16(%ebp,%ecx,1)
    if(index % 2 == 0)
    {
      v6[index/2] = (parseHex(temp_buff) << 16);
 8048f7e:	8d 3c 82             	lea    (%edx,%eax,4),%edi
 8048f81:	8d 45 ea             	lea    -0x16(%ebp),%eax
        break;
      }
      temp_buff[offset] =  value;      
    }
    temp_buff[offset]= '\0';
    if(index % 2 == 0)
 8048f84:	75 0e                	jne    8048f94 <parse_ipv6_address+0x5c>
    {
      v6[index/2] = (parseHex(temp_buff) << 16);
 8048f86:	50                   	push   %eax
 8048f87:	e8 60 ff ff ff       	call   8048eec <parseHex>
 8048f8c:	59                   	pop    %ecx
 8048f8d:	c1 e0 10             	shl    $0x10,%eax
 8048f90:	89 07                	mov    %eax,(%edi)
 8048f92:	eb 0c                	jmp    8048fa0 <parse_ipv6_address+0x68>
    }
    else
    {
      v6[index/2] |= parseHex(temp_buff);
 8048f94:	50                   	push   %eax
 8048f95:	e8 52 ff ff ff       	call   8048eec <parseHex>
 8048f9a:	5a                   	pop    %edx
 8048f9b:	0f b7 c0             	movzwl %ax,%eax
 8048f9e:	09 07                	or     %eax,(%edi)
  uint8 index = 0;
  uint16 buffer_offset = 0;
  uint8 temp_buff[10];
  temp_buff[0] = '\0';
  //! Total 8 octets
  for(index = 0; index < 8 ;index++)
 8048fa0:	43                   	inc    %ebx
 8048fa1:	80 fb 08             	cmp    $0x8,%bl
    }
    else
    {
      v6[index/2] |= parseHex(temp_buff);
    }
    temp_buff[0] = '\0';
 8048fa4:	c6 45 ea 00          	movb   $0x0,-0x16(%ebp)
  uint8 index = 0;
  uint16 buffer_offset = 0;
  uint8 temp_buff[10];
  temp_buff[0] = '\0';
  //! Total 8 octets
  for(index = 0; index < 8 ;index++)
 8048fa8:	74 04                	je     8048fae <parse_ipv6_address+0x76>
 * This function is used to convert IPV6 Address.
 * destination string  
 */

void parse_ipv6_address(uint32 *v6, uint8 *buf)
{
 8048faa:	31 c0                	xor    %eax,%eax
 8048fac:	eb 9d                	jmp    8048f4b <parse_ipv6_address+0x13>
    {
      v6[index/2] |= parseHex(temp_buff);
    }
    temp_buff[0] = '\0';
  }
}
 8048fae:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8048fb1:	5b                   	pop    %ebx
 8048fb2:	5e                   	pop    %esi
 8048fb3:	5f                   	pop    %edi
 8048fb4:	5d                   	pop    %ebp
 8048fb5:	c3                   	ret    

08048fb6 <convert_lower_case_to_upper_case>:
 * @section description 
 * This function is used to convert the given lower case character to upper case
 * destination string  
 */
uint8 convert_lower_case_to_upper_case(uint8 lwrcase)
{
 8048fb6:	55                   	push   %ebp
 8048fb7:	89 e5                	mov    %esp,%ebp
 8048fb9:	8b 45 08             	mov    0x8(%ebp),%eax
  uint8 digit = (lwrcase >= 'a' && lwrcase <= 'f') ? (lwrcase-0x20) : lwrcase;
  return (digit >= 'A' && digit <= 'F') ? digit - 0x37 : digit - '0';
}
 8048fbc:	5d                   	pop    %ebp
 * @section description 
 * This function is used to convert the given lower case character to upper case
 * destination string  
 */
uint8 convert_lower_case_to_upper_case(uint8 lwrcase)
{
 8048fbd:	88 c2                	mov    %al,%dl
  uint8 digit = (lwrcase >= 'a' && lwrcase <= 'f') ? (lwrcase-0x20) : lwrcase;
 8048fbf:	8d 4a 9f             	lea    -0x61(%edx),%ecx
 8048fc2:	83 ea 20             	sub    $0x20,%edx
 8048fc5:	80 f9 05             	cmp    $0x5,%cl
 8048fc8:	0f 47 d0             	cmova  %eax,%edx
  return (digit >= 'A' && digit <= 'F') ? digit - 0x37 : digit - '0';
 8048fcb:	8d 4a bf             	lea    -0x41(%edx),%ecx
 8048fce:	8d 42 c9             	lea    -0x37(%edx),%eax
 8048fd1:	83 ea 30             	sub    $0x30,%edx
 8048fd4:	80 f9 05             	cmp    $0x5,%cl
 8048fd7:	0f 47 c2             	cmova  %edx,%eax
}
 8048fda:	c3                   	ret    
 8048fdb:	90                   	nop

08048fdc <rsi_ble_init_struct>:
	* rsi_sys_init should be done successfully. 		
 */
//UINT08 connect_addr[6]={0xc0,0xff,0xee,0xc0,0xff,0xee};
UINT08 connect_addr[6]={0xee,0xff,0xc0,0xee,0xff,0xc0};
INT16 rsi_ble_init_struct(UINT16  CommandType)
{
 8048fdc:	55                   	push   %ebp
 8048fdd:	89 e5                	mov    %esp,%ebp
 8048fdf:	57                   	push   %edi
 8048fe0:	56                   	push   %esi
 8048fe1:	53                   	push   %ebx
 8048fe2:	83 ec 14             	sub    $0x14,%esp
 8048fe5:	8b 75 08             	mov    0x8(%ebp),%esi
    RSI_BLE_API *uApiParams;
    INT16 ret_val;
    
    
    uApiParams = rsi_bt_AppControlBlock.uBLEApiInitParams;
 8048fe8:	8b 1d de c6 04 08    	mov    0x804c6de,%ebx
    
		printf("CMD TYPE %d\n",CommandType);
 8048fee:	0f b7 c6             	movzwl %si,%eax
    switch (CommandType) {
 8048ff1:	83 ee 75             	sub    $0x75,%esi
    INT16 ret_val;
    
    
    uApiParams = rsi_bt_AppControlBlock.uBLEApiInitParams;
    
		printf("CMD TYPE %d\n",CommandType);
 8048ff4:	50                   	push   %eax
 8048ff5:	68 20 a5 04 08       	push   $0x804a520
 8048ffa:	e8 01 f7 ff ff       	call   8048700 <printf@plt>
    switch (CommandType) {
 8048fff:	83 c4 10             	add    $0x10,%esp
 8049002:	66 83 fe 17          	cmp    $0x17,%si
 8049006:	0f 87 38 03 00 00    	ja     8049344 <rsi_ble_init_struct+0x368>
 804900c:	0f b7 f6             	movzwl %si,%esi
 804900f:	ff 24 b5 48 a5 04 08 	jmp    *0x804a548(,%esi,4)
        
        case RSI_BLE_REQ_ADVERTISE:
						 printf("ADVERTISE CMD \n");
 8049016:	83 ec 0c             	sub    $0xc,%esp
 8049019:	68 2d a5 04 08       	push   $0x804a52d
 804901e:	e8 6d f7 ff ff       	call   8048790 <puts@plt>
			
             memset (&uApiParams->uLeAdvertise, 0, sizeof (RSI_BLE_CMD_ADVERTISE));
             uApiParams->uLeAdvertise.AdvFrameSnd.Status        = RSI_BLE_ADV_STATUS;
 8049023:	c6 03 01             	movb   $0x1,(%ebx)
             uApiParams->uLeAdvertise.AdvFrameSnd.AdvertiseType = RSI_BLE_ADV_TYPE;
 8049026:	c6 43 01 18          	movb   $0x18,0x1(%ebx)
             uApiParams->uLeAdvertise.AdvFrameSnd.FilterType    = RSI_BLE_ADV_FILTER_TYPE;
 804902a:	c6 43 02 00          	movb   $0x0,0x2(%ebx)

             ret_val = rsi_ble_advertise(uApiParams);
 804902e:	89 1c 24             	mov    %ebx,(%esp)
 8049031:	e8 e2 0b 00 00       	call   8049c18 <rsi_ble_advertise>
 8049036:	e9 16 03 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             memset (&uApiParams->uLeScan, 0, sizeof (RSI_BLE_CMD_SCAN));
             uApiParams->uLeScan.ScanFrameSnd.Status     = RSI_BLE_SCAN_STATUS;           //1-scan enable, 0-scan disable
             uApiParams->uLeScan.ScanFrameSnd.Scantype   = RSI_BLE_SCAN_TYPE;             //scan type (active /passive)
             uApiParams->uLeScan.ScanFrameSnd.FilterType = RSI_BLE_SCAN_FILTER_TYPE;      //filter type

             ret_val = rsi_ble_scan(uApiParams);
 804903b:	83 ec 0c             	sub    $0xc,%esp
             ret_val = rsi_ble_advertise(uApiParams);
             break;

        case RSI_BLE_REQ_SCAN:
             memset (&uApiParams->uLeScan, 0, sizeof (RSI_BLE_CMD_SCAN));
             uApiParams->uLeScan.ScanFrameSnd.Status     = RSI_BLE_SCAN_STATUS;           //1-scan enable, 0-scan disable
 804903e:	c6 03 01             	movb   $0x1,(%ebx)
             uApiParams->uLeScan.ScanFrameSnd.Scantype   = RSI_BLE_SCAN_TYPE;             //scan type (active /passive)
 8049041:	c6 43 01 01          	movb   $0x1,0x1(%ebx)
             uApiParams->uLeScan.ScanFrameSnd.FilterType = RSI_BLE_SCAN_FILTER_TYPE;      //filter type
 8049045:	c6 43 02 00          	movb   $0x0,0x2(%ebx)

             ret_val = rsi_ble_scan(uApiParams);
 8049049:	53                   	push   %ebx
 804904a:	e8 e0 0b 00 00       	call   8049c2f <rsi_ble_scan>
 804904f:	e9 fd 02 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>

             break;

        case RSI_BLE_REQ_CONNECT:
             memset (&uApiParams->uLeConnect, 0, sizeof (RSI_BLE_CMD_CONNECT));
 8049054:	31 c0                	xor    %eax,%eax
 8049056:	89 df                	mov    %ebx,%edi
 8049058:	b9 07 00 00 00       	mov    $0x7,%ecx
             uApiParams->uLeConnect.ConnectFrameSnd.AddressType = RSI_BLE_CONN_ADDR_TYPE;        //remote device type
             memcpy (uApiParams->uLeConnect.ConnectFrameSnd.BDAddress,connect_addr,6); //remote device address
             ret_val = rsi_ble_connect(uApiParams);
 804905d:	83 ec 0c             	sub    $0xc,%esp
             ret_val = rsi_ble_scan(uApiParams);

             break;

        case RSI_BLE_REQ_CONNECT:
             memset (&uApiParams->uLeConnect, 0, sizeof (RSI_BLE_CMD_CONNECT));
 8049060:	f3 aa                	rep stos %al,%es:(%edi)
             uApiParams->uLeConnect.ConnectFrameSnd.AddressType = RSI_BLE_CONN_ADDR_TYPE;        //remote device type
             memcpy (uApiParams->uLeConnect.ConnectFrameSnd.BDAddress,connect_addr,6); //remote device address
 8049062:	a1 78 c1 04 08       	mov    0x804c178,%eax
 8049067:	89 43 01             	mov    %eax,0x1(%ebx)
 804906a:	a1 7c c1 04 08       	mov    0x804c17c,%eax
 804906f:	66 89 43 05          	mov    %ax,0x5(%ebx)
             ret_val = rsi_ble_connect(uApiParams);
 8049073:	53                   	push   %ebx
 8049074:	e8 cd 0b 00 00       	call   8049c46 <rsi_ble_connect>
 8049079:	e9 d3 02 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_DISCONNECT:
             ret_val = rsi_ble_disconnect();
 804907e:	e8 da 0b 00 00       	call   8049c5d <rsi_ble_disconnect>
             break;
 8049083:	e9 cc 02 00 00       	jmp    8049354 <rsi_ble_init_struct+0x378>

        case RSI_BLE_REQ_QUERY_DEVICE_STATE:
             ret_val = rsi_ble_query_device_state();
 8049088:	e8 e6 0b 00 00       	call   8049c73 <rsi_ble_query_device_state>
             break;
 804908d:	e9 c2 02 00 00       	jmp    8049354 <rsi_ble_init_struct+0x378>

        case RSI_BLE_REQ_UPDATE_HCI_PARAMS:
             ret_val = rsi_ble_update_hci_params();
 8049092:	e8 f2 0b 00 00       	call   8049c89 <rsi_ble_update_hci_params>
             break;
 8049097:	e9 b8 02 00 00       	jmp    8049354 <rsi_ble_init_struct+0x378>

        case RSI_BLE_REQ_START_ENCRYPTION:
             ret_val = rsi_ble_start_encryption();
 804909c:	e8 fe 0b 00 00       	call   8049c9f <rsi_ble_start_encryption>
             break;
 80490a1:	e9 ae 02 00 00       	jmp    8049354 <rsi_ble_init_struct+0x378>

        case RSI_BLE_REQ_SMP_PAIR_REQUEST:
             memset (&uApiParams->uLeSmpReq, 0, sizeof (RSI_BLE_CMD_SMP_PAIR_REQUEST));
             uApiParams->uLeSmpReq.SmpPairReqFrameSnd.IOCapability = 4;         //keyboard and display
             ret_val = rsi_ble_smp_pair_request(uApiParams);
 80490a6:	83 ec 0c             	sub    $0xc,%esp
             ret_val = rsi_ble_start_encryption();
             break;

        case RSI_BLE_REQ_SMP_PAIR_REQUEST:
             memset (&uApiParams->uLeSmpReq, 0, sizeof (RSI_BLE_CMD_SMP_PAIR_REQUEST));
             uApiParams->uLeSmpReq.SmpPairReqFrameSnd.IOCapability = 4;         //keyboard and display
 80490a9:	c6 03 04             	movb   $0x4,(%ebx)
             ret_val = rsi_ble_smp_pair_request(uApiParams);
 80490ac:	53                   	push   %ebx
 80490ad:	e8 03 0c 00 00       	call   8049cb5 <rsi_ble_smp_pair_request>
 80490b2:	e9 9a 02 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_SMP_RESPONSE:
             memset (&uApiParams->uLeSmpResp, 0, sizeof (RSI_BLE_CMD_SMP_RESPONSE));
             uApiParams->uLeSmpResp.SmpRespFrameSnd.IOCapability = 4;            //keyboard and display
             ret_val = rsi_ble_smp_response(uApiParams);
 80490b7:	83 ec 0c             	sub    $0xc,%esp
             ret_val = rsi_ble_smp_pair_request(uApiParams);
             break;

        case RSI_BLE_REQ_SMP_RESPONSE:
             memset (&uApiParams->uLeSmpResp, 0, sizeof (RSI_BLE_CMD_SMP_RESPONSE));
             uApiParams->uLeSmpResp.SmpRespFrameSnd.IOCapability = 4;            //keyboard and display
 80490ba:	c6 03 04             	movb   $0x4,(%ebx)
             ret_val = rsi_ble_smp_response(uApiParams);
 80490bd:	53                   	push   %ebx
 80490be:	e8 09 0c 00 00       	call   8049ccc <rsi_ble_smp_response>
 80490c3:	e9 89 02 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_SMP_PASSKEY:
             memset (&uApiParams->uLeSmppasskey, 0, sizeof (RSI_BLE_CMD_SMP_PASSKEY));
             uApiParams->uLeSmppasskey.SmpPasskeyFrameSnd.Passkey[0] = 0;  //passkey value
             ret_val = rsi_ble_smp_passkey(uApiParams);
 80490c8:	83 ec 0c             	sub    $0xc,%esp
             uApiParams->uLeSmpResp.SmpRespFrameSnd.IOCapability = 4;            //keyboard and display
             ret_val = rsi_ble_smp_response(uApiParams);
             break;

        case RSI_BLE_REQ_SMP_PASSKEY:
             memset (&uApiParams->uLeSmppasskey, 0, sizeof (RSI_BLE_CMD_SMP_PASSKEY));
 80490cb:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
             uApiParams->uLeSmppasskey.SmpPasskeyFrameSnd.Passkey[0] = 0;  //passkey value
             ret_val = rsi_ble_smp_passkey(uApiParams);
 80490d1:	53                   	push   %ebx
 80490d2:	e8 0c 0c 00 00       	call   8049ce3 <rsi_ble_smp_passkey>
 80490d7:	e9 75 02 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_QUERY_PROFILES_LIST:         
             ret_val = rsi_ble_query_profiles_list();
 80490dc:	e8 bb 0c 00 00       	call   8049d9c <rsi_ble_query_profiles_list>
             break;
 80490e1:	e9 6e 02 00 00       	jmp    8049354 <rsi_ble_init_struct+0x378>

        case RSI_BLE_REQ_QUERY_PROFILE:
             memset (&uApiParams->uLeSev, 0, sizeof (RSI_BLE_CMD_QUERY_PROFILE));
 80490e6:	31 c0                	xor    %eax,%eax
 80490e8:	89 df                	mov    %ebx,%edi
 80490ea:	b9 05 00 00 00       	mov    $0x5,%ecx
 80490ef:	f3 ab                	rep stos %eax,%es:(%edi)
             uApiParams->uLeSev.QueryProfileDescFrameSnd.ProfileUUID.size = RSI_BLE_UUID_SIZE;
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeSev.QueryProfileDescFrameSnd.ProfileUUID.Val.val16, RSI_BLE_PROFILE_UUID);
 80490f1:	8d 43 04             	lea    0x4(%ebx),%eax
             ret_val = rsi_ble_query_profiles_list();
             break;

        case RSI_BLE_REQ_QUERY_PROFILE:
             memset (&uApiParams->uLeSev, 0, sizeof (RSI_BLE_CMD_QUERY_PROFILE));
             uApiParams->uLeSev.QueryProfileDescFrameSnd.ProfileUUID.size = RSI_BLE_UUID_SIZE;
 80490f4:	c6 03 02             	movb   $0x2,(%ebx)
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeSev.QueryProfileDescFrameSnd.ProfileUUID.Val.val16, RSI_BLE_PROFILE_UUID);
 80490f7:	51                   	push   %ecx
 80490f8:	51                   	push   %ecx
 80490f9:	68 00 18 00 00       	push   $0x1800
 80490fe:	50                   	push   %eax
 80490ff:	e8 dc 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             ret_val = rsi_ble_query_profile(uApiParams);
 8049104:	89 1c 24             	mov    %ebx,(%esp)
 8049107:	e8 a6 0c 00 00       	call   8049db2 <rsi_ble_query_profile>
 804910c:	e9 40 02 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_QUERY_CHARACTERISTIC_SERVICES:
             memset (&uApiParams->uLeCharServ, 0, sizeof (RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES));
 8049111:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
             rsi_uint16_to_2bytes (uApiParams->uLeCharServ.QueryCharSerFrameSnd.StartHandle, RSI_BLE_CHAR_SERV_START_HANDLE);
 8049117:	50                   	push   %eax
 8049118:	50                   	push   %eax
 8049119:	6a 01                	push   $0x1
 804911b:	53                   	push   %ebx
 804911c:	e8 bf 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes (uApiParams->uLeCharServ.QueryCharSerFrameSnd.EndHandle, RSI_BLE_CHAR_SERV_END_HANDLE);
 8049121:	58                   	pop    %eax
 8049122:	5a                   	pop    %edx
 8049123:	8d 43 02             	lea    0x2(%ebx),%eax
 8049126:	68 ff ff 00 00       	push   $0xffff
 804912b:	50                   	push   %eax
 804912c:	e8 af 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             ret_val = rsi_ble_query_characteristic_services(uApiParams);
 8049131:	89 1c 24             	mov    %ebx,(%esp)
 8049134:	e8 90 0c 00 00       	call   8049dc9 <rsi_ble_query_characteristic_services>
 8049139:	e9 13 02 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_QUERY_INCLUDE_SERVICES:
             memset (&uApiParams->uLeIncServ, 0, sizeof (RSI_BLE_CMD_QUERY_INCLUDE_SERVICES));
 804913e:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
             rsi_uint16_to_2bytes (uApiParams->uLeIncServ.QueryIncludeServFrameSnd.StartHandle, RSI_BLE_INC_SERV_START_HANDLE);
 8049144:	51                   	push   %ecx
 8049145:	51                   	push   %ecx
 8049146:	6a 01                	push   $0x1
 8049148:	53                   	push   %ebx
 8049149:	e8 92 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes (uApiParams->uLeIncServ.QueryIncludeServFrameSnd.EndHandle, RSI_BLE_INC_SERV_END_HANDLE);
 804914e:	8d 43 02             	lea    0x2(%ebx),%eax
 8049151:	5e                   	pop    %esi
 8049152:	5f                   	pop    %edi
 8049153:	68 ff ff 00 00       	push   $0xffff
 8049158:	50                   	push   %eax
 8049159:	e8 82 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             ret_val = rsi_ble_query_include_service(uApiParams);
 804915e:	89 1c 24             	mov    %ebx,(%esp)
 8049161:	e8 7a 0c 00 00       	call   8049de0 <rsi_ble_query_include_service>
 8049166:	e9 e6 01 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_READ_CHAR_VALUE_BY_UUID:
             memset (&uApiParams->uLeCharVal, 0, sizeof (RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID));
 804916b:	31 c0                	xor    %eax,%eax
 804916d:	89 df                	mov    %ebx,%edi
 804916f:	b9 06 00 00 00       	mov    $0x6,%ecx
 8049174:	f3 ab                	rep stos %eax,%es:(%edi)
             rsi_uint16_to_2bytes (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.StartHandle, RSI_BLE_READ_CHAR_START_HANDLE);
 8049176:	51                   	push   %ecx
 8049177:	51                   	push   %ecx
 8049178:	6a 01                	push   $0x1
 804917a:	53                   	push   %ebx
 804917b:	e8 60 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.EndHandle, RSI_BLE_READ_CHAR_END_HANDLE);
 8049180:	8d 43 02             	lea    0x2(%ebx),%eax
 8049183:	5e                   	pop    %esi
 8049184:	5f                   	pop    %edi
 8049185:	68 ff ff 00 00       	push   $0xffff
 804918a:	50                   	push   %eax
 804918b:	e8 50 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.CharacterUUID.size = 2;
 8049190:	c6 43 04 02          	movb   $0x2,0x4(%ebx)
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.CharacterUUID.Val.val16, RSI_BLE_READ_CHAR_UUID);
 8049194:	58                   	pop    %eax
 8049195:	5a                   	pop    %edx
 8049196:	8d 43 08             	lea    0x8(%ebx),%eax
 8049199:	68 00 2a 00 00       	push   $0x2a00
 804919e:	50                   	push   %eax
 804919f:	e8 3c 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>

             ret_val = rsi_ble_read_char_value_by_UUID(uApiParams);
 80491a4:	89 1c 24             	mov    %ebx,(%esp)
 80491a7:	e8 4b 0c 00 00       	call   8049df7 <rsi_ble_read_char_value_by_UUID>
 80491ac:	e9 a0 01 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_QUERY_ATT_DESC:
             memset (&uApiParams->uLeAttDesc, 0, sizeof (RSI_BLE_CMD_QUERY_ATT_DESC));
 80491b1:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
             rsi_uint16_to_2bytes(uApiParams->uLeAttDesc.QueryAttFrameSnd.StartHandle, RSI_BLE_ATT_START_HANDLE);
 80491b7:	50                   	push   %eax
 80491b8:	50                   	push   %eax
 80491b9:	6a 01                	push   $0x1
 80491bb:	53                   	push   %ebx
 80491bc:	e8 1f 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes(uApiParams->uLeAttDesc.QueryAttFrameSnd.EndHandle, RSI_BLE_ATT_END_HANDLE);
 80491c1:	58                   	pop    %eax
 80491c2:	5a                   	pop    %edx
 80491c3:	8d 43 02             	lea    0x2(%ebx),%eax
 80491c6:	6a 05                	push   $0x5
 80491c8:	50                   	push   %eax
 80491c9:	e8 12 0d 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             ret_val = rsi_ble_query_att(uApiParams);
 80491ce:	89 1c 24             	mov    %ebx,(%esp)
 80491d1:	e8 38 0c 00 00       	call   8049e0e <rsi_ble_query_att>
 80491d6:	e9 76 01 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_QUERY_ATT_VALUE:
             memset (&uApiParams->uLeAttVal, 0, sizeof (RSI_BLE_CMD_QUERY_ATT_VALUE));
 80491db:	66 c7 03 00 00       	movw   $0x0,(%ebx)
             rsi_uint16_to_2bytes (uApiParams->uLeAttVal.QueryAttValFrameSnd.Handle, RSI_BLE_ATT_VAL_HANDLE);
 80491e0:	50                   	push   %eax
 80491e1:	50                   	push   %eax
 80491e2:	6a 03                	push   $0x3
 80491e4:	53                   	push   %ebx
 80491e5:	e8 f6 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             ret_val = rsi_ble_query_att_value(uApiParams);
 80491ea:	89 1c 24             	mov    %ebx,(%esp)
 80491ed:	e8 33 0c 00 00       	call   8049e25 <rsi_ble_query_att_value>
 80491f2:	e9 5a 01 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_QUERY_MULTIPLE_ATT_VALUES:
             memset (&uApiParams->uLeMulAttVals, 0, sizeof (RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES));
 80491f7:	31 c0                	xor    %eax,%eax
 80491f9:	89 df                	mov    %ebx,%edi
 80491fb:	b9 0b 00 00 00       	mov    $0xb,%ecx
 8049200:	f3 aa                	rep stos %al,%es:(%edi)
             uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.NumberOfHandles = RSI_BLE_MUL_NBR_OF_ATT;
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.Handles[0], RSI_BLE_MUL_ATT_HANDLE1);
 8049202:	8d 43 01             	lea    0x1(%ebx),%eax
             ret_val = rsi_ble_query_att_value(uApiParams);
             break;

        case RSI_BLE_REQ_QUERY_MULTIPLE_ATT_VALUES:
             memset (&uApiParams->uLeMulAttVals, 0, sizeof (RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES));
             uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.NumberOfHandles = RSI_BLE_MUL_NBR_OF_ATT;
 8049205:	c6 03 02             	movb   $0x2,(%ebx)
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.Handles[0], RSI_BLE_MUL_ATT_HANDLE1);
 8049208:	51                   	push   %ecx
 8049209:	51                   	push   %ecx
 804920a:	6a 02                	push   $0x2
 804920c:	50                   	push   %eax
 804920d:	e8 ce 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.Handles[1], RSI_BLE_MUL_ATT_HANDLE2);
 8049212:	8d 43 03             	lea    0x3(%ebx),%eax
 8049215:	5e                   	pop    %esi
 8049216:	5f                   	pop    %edi
 8049217:	6a 03                	push   $0x3
 8049219:	50                   	push   %eax
 804921a:	e8 c1 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>

             ret_val = rsi_ble_query_multi_att_values(uApiParams);
 804921f:	89 1c 24             	mov    %ebx,(%esp)
 8049222:	e8 15 0c 00 00       	call   8049e3c <rsi_ble_query_multi_att_values>
 8049227:	e9 25 01 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_QUERY_LONG_ATT_VALUE:
             memset (&uApiParams->uLeLongAttVal, 0, sizeof (RSI_BLE_CMD_QUERY_LONG_ATT_VALUE));
 804922c:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeLongAttVal.QueryLongAttValFrameSnd.Handle, RSI_BLE_LONG_ATT_HANDLE);
 8049232:	50                   	push   %eax
 8049233:	50                   	push   %eax
 8049234:	6a 03                	push   $0x3
 8049236:	53                   	push   %ebx
 8049237:	e8 a4 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeLongAttVal.QueryLongAttValFrameSnd.Offset, RSI_BLE_LONG_ATT_OFFSET);
 804923c:	58                   	pop    %eax
 804923d:	5a                   	pop    %edx
 804923e:	8d 43 02             	lea    0x2(%ebx),%eax
 8049241:	6a 02                	push   $0x2
 8049243:	50                   	push   %eax
 8049244:	e8 97 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>

             ret_val = rsi_ble_query_long_att_value(uApiParams);
 8049249:	89 1c 24             	mov    %ebx,(%esp)
 804924c:	e8 02 0c 00 00       	call   8049e53 <rsi_ble_query_long_att_value>
 8049251:	e9 fb 00 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_SET_ATT_VALUE:
             memset (&uApiParams->uLeSetAttVal, 0, sizeof (RSI_BLE_CMD_SET_ATT_VALUE));
 8049256:	31 c0                	xor    %eax,%eax
 8049258:	89 df                	mov    %ebx,%edi
 804925a:	b9 07 00 00 00       	mov    $0x7,%ecx
 804925f:	f3 ab                	rep stos %eax,%es:(%edi)
             rsi_uint16_to_2bytes (uApiParams->uLeSetAttVal.SetAttValFrameSnd.Handle, RSI_BLE_SET_ATT_HANDLE);
 8049261:	51                   	push   %ecx
 8049262:	51                   	push   %ecx
 8049263:	6a 34                	push   $0x34
 8049265:	53                   	push   %ebx
 8049266:	e8 75 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             uApiParams->uLeSetAttVal.SetAttValFrameSnd.Length = RSI_BLE_SET_ATT_LEN;
             rsi_uint16_to_2bytes(uApiParams->uLeSetAttVal.SetAttValFrameSnd.Value, RSI_BLE_SET_ATT_VAL);
 804926b:	8d 43 03             	lea    0x3(%ebx),%eax
             break;

        case RSI_BLE_REQ_SET_ATT_VALUE:
             memset (&uApiParams->uLeSetAttVal, 0, sizeof (RSI_BLE_CMD_SET_ATT_VALUE));
             rsi_uint16_to_2bytes (uApiParams->uLeSetAttVal.SetAttValFrameSnd.Handle, RSI_BLE_SET_ATT_HANDLE);
             uApiParams->uLeSetAttVal.SetAttValFrameSnd.Length = RSI_BLE_SET_ATT_LEN;
 804926e:	c6 43 02 02          	movb   $0x2,0x2(%ebx)
             rsi_uint16_to_2bytes(uApiParams->uLeSetAttVal.SetAttValFrameSnd.Value, RSI_BLE_SET_ATT_VAL);
 8049272:	5e                   	pop    %esi
 8049273:	5f                   	pop    %edi
 8049274:	6a 01                	push   $0x1
 8049276:	50                   	push   %eax
 8049277:	e8 64 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>

             ret_val = rsi_ble_set_att_value(uApiParams);
 804927c:	89 1c 24             	mov    %ebx,(%esp)
 804927f:	e8 e6 0b 00 00       	call   8049e6a <rsi_ble_set_att_value>
 8049284:	e9 c8 00 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_SET_ATT_VALUE_NO_ACK:
             memset (&uApiParams->uLeSetCmdAttVal, 0, sizeof (RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK));
 8049289:	31 c0                	xor    %eax,%eax
 804928b:	89 df                	mov    %ebx,%edi
 804928d:	b9 07 00 00 00       	mov    $0x7,%ecx
 8049292:	f3 ab                	rep stos %eax,%es:(%edi)
             rsi_uint16_to_2bytes (uApiParams->uLeSetCmdAttVal.SetAttValNoAckFrameSnd.Handle, RSI_BLE_SET_ATT_NO_ACK_HANDLE);
 8049294:	57                   	push   %edi
 8049295:	57                   	push   %edi
 8049296:	6a 34                	push   $0x34
 8049298:	53                   	push   %ebx
 8049299:	e8 42 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             uApiParams->uLeSetCmdAttVal.SetAttValNoAckFrameSnd.Length = RSI_BLE_SET_ATT_NO_ACK_LEN;
 804929e:	c6 43 02 02          	movb   $0x2,0x2(%ebx)
             rsi_uint16_to_2bytes(uApiParams->uLeSetCmdAttVal.SetAttValNoAckFrameSnd.Value, RSI_BLE_SET_ATT_NO_ACK_VAL);
 80492a2:	58                   	pop    %eax
 80492a3:	5a                   	pop    %edx
 80492a4:	8d 43 03             	lea    0x3(%ebx),%eax
 80492a7:	6a 00                	push   $0x0
 80492a9:	50                   	push   %eax
 80492aa:	e8 31 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>

             ret_val = rsi_ble_set_att_value_no_ack(uApiParams);
 80492af:	89 1c 24             	mov    %ebx,(%esp)
 80492b2:	e8 ca 0b 00 00       	call   8049e81 <rsi_ble_set_att_value_no_ack>
 80492b7:	e9 95 00 00 00       	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_SET_LONG_ATT_VALUE:
             memset (&uApiParams->uLeSetLongAttVal, 0, sizeof (RSI_BLE_CMD_SET_LONG_ATT_VALUE));
 80492bc:	31 c0                	xor    %eax,%eax
 80492be:	89 df                	mov    %ebx,%edi
 80492c0:	b9 2d 00 00 00       	mov    $0x2d,%ecx
 80492c5:	f3 aa                	rep stos %al,%es:(%edi)
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Handle, RSI_BLE_SET_LONG_ATT_HANDLE);
 80492c7:	50                   	push   %eax
 80492c8:	50                   	push   %eax
 80492c9:	6a 34                	push   $0x34
 80492cb:	53                   	push   %ebx
 80492cc:	e8 0f 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Offset, RSI_BLE_SET_LONG_ATT_OFFSET);
 80492d1:	58                   	pop    %eax
 80492d2:	5a                   	pop    %edx
 80492d3:	8d 43 02             	lea    0x2(%ebx),%eax
 80492d6:	6a 00                	push   $0x0
 80492d8:	50                   	push   %eax
 80492d9:	e8 02 0c 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Length = RSI_BLE_SET_LONG_ATT_LEN;
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Value, RSI_BLE_SET_LONG_ATT_VAL);
 80492de:	8d 43 05             	lea    0x5(%ebx),%eax

        case RSI_BLE_REQ_SET_LONG_ATT_VALUE:
             memset (&uApiParams->uLeSetLongAttVal, 0, sizeof (RSI_BLE_CMD_SET_LONG_ATT_VALUE));
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Handle, RSI_BLE_SET_LONG_ATT_HANDLE);
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Offset, RSI_BLE_SET_LONG_ATT_OFFSET);
             uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Length = RSI_BLE_SET_LONG_ATT_LEN;
 80492e1:	c6 43 04 02          	movb   $0x2,0x4(%ebx)
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Value, RSI_BLE_SET_LONG_ATT_VAL);
 80492e5:	59                   	pop    %ecx
 80492e6:	5e                   	pop    %esi
 80492e7:	6a 01                	push   $0x1
 80492e9:	50                   	push   %eax
 80492ea:	e8 f1 0b 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>

             ret_val = rsi_ble_set_long_att_value(uApiParams);
 80492ef:	89 1c 24             	mov    %ebx,(%esp)
 80492f2:	e8 a1 0b 00 00       	call   8049e98 <rsi_ble_set_long_att_value>
 80492f7:	eb 58                	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;

        case RSI_BLE_REQ_SET_PREPARE_LONG_ATT_VALUE:
             memset (&uApiParams->uLePrepairAttVal, 0, sizeof (RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE));
 80492f9:	31 c0                	xor    %eax,%eax
 80492fb:	89 df                	mov    %ebx,%edi
 80492fd:	b9 2d 00 00 00       	mov    $0x2d,%ecx
 8049302:	f3 aa                	rep stos %al,%es:(%edi)
             rsi_uint16_to_2bytes (uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Handle, RSI_BLE_PREP_LONG_ATT_HANDLE);
 8049304:	50                   	push   %eax
 8049305:	50                   	push   %eax
 8049306:	6a 34                	push   $0x34
 8049308:	53                   	push   %ebx
 8049309:	e8 d2 0b 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             rsi_uint16_to_2bytes (uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Offset, RSI_BLE_PREP_LONG_ATT_OFFSET);
 804930e:	8d 43 02             	lea    0x2(%ebx),%eax
 8049311:	5a                   	pop    %edx
 8049312:	59                   	pop    %ecx
 8049313:	6a 00                	push   $0x0
 8049315:	50                   	push   %eax
 8049316:	e8 c5 0b 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>
             uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Length = RSI_BLE_PREP_LONG_ATT_LEN;
             rsi_uint16_to_2bytes (uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Value, RSI_BLE_PREP_LONG_ATT_VAL);
 804931b:	8d 43 05             	lea    0x5(%ebx),%eax

        case RSI_BLE_REQ_SET_PREPARE_LONG_ATT_VALUE:
             memset (&uApiParams->uLePrepairAttVal, 0, sizeof (RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE));
             rsi_uint16_to_2bytes (uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Handle, RSI_BLE_PREP_LONG_ATT_HANDLE);
             rsi_uint16_to_2bytes (uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Offset, RSI_BLE_PREP_LONG_ATT_OFFSET);
             uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Length = RSI_BLE_PREP_LONG_ATT_LEN;
 804931e:	c6 43 04 02          	movb   $0x2,0x4(%ebx)
             rsi_uint16_to_2bytes (uApiParams->uLePrepairAttVal.SetPreLongAttValFrameSnd.Value, RSI_BLE_PREP_LONG_ATT_VAL);
 8049322:	5e                   	pop    %esi
 8049323:	5f                   	pop    %edi
 8049324:	6a 00                	push   $0x0
 8049326:	50                   	push   %eax
 8049327:	e8 b4 0b 00 00       	call   8049ee0 <rsi_uint16_to_2bytes>

             ret_val = rsi_ble_set_prep_long_att_value(uApiParams);
 804932c:	89 1c 24             	mov    %ebx,(%esp)
 804932f:	e8 7b 0b 00 00       	call   8049eaf <rsi_ble_set_prep_long_att_value>
 8049334:	eb 1b                	jmp    8049351 <rsi_ble_init_struct+0x375>

        case RSI_BLE_REQ_EXECUTE_LONG_ATT_VALUE_WRITE:
             memset (&uApiParams->uLeExecuteWrite, 0, sizeof (RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE));
             uApiParams->uLeExecuteWrite.ExeLongAttValWrFrameSnd.Flag = RSI_BLE_EXE_LONG_ATT_FLAG;

             ret_val = rsi_ble_execute_long_att_value(uApiParams);
 8049336:	83 ec 0c             	sub    $0xc,%esp
             ret_val = rsi_ble_set_prep_long_att_value(uApiParams);
             break;

        case RSI_BLE_REQ_EXECUTE_LONG_ATT_VALUE_WRITE:
             memset (&uApiParams->uLeExecuteWrite, 0, sizeof (RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE));
             uApiParams->uLeExecuteWrite.ExeLongAttValWrFrameSnd.Flag = RSI_BLE_EXE_LONG_ATT_FLAG;
 8049339:	c6 03 01             	movb   $0x1,(%ebx)

             ret_val = rsi_ble_execute_long_att_value(uApiParams);
 804933c:	53                   	push   %ebx
 804933d:	e8 84 0b 00 00       	call   8049ec6 <rsi_ble_execute_long_att_value>
 8049342:	eb 0d                	jmp    8049351 <rsi_ble_init_struct+0x375>
             break;
				default: 
						 printf("WRONG CMD \n");
 8049344:	83 ec 0c             	sub    $0xc,%esp
 8049347:	68 3c a5 04 08       	push   $0x804a53c
 804934c:	e8 3f f4 ff ff       	call   8048790 <puts@plt>
 8049351:	83 c4 10             	add    $0x10,%esp
    }
    
    return 0;    
}
 8049354:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8049357:	31 c0                	xor    %eax,%eax
 8049359:	5b                   	pop    %ebx
 804935a:	5e                   	pop    %esi
 804935b:	5f                   	pop    %edi
 804935c:	5d                   	pop    %ebp
 804935d:	c3                   	ret    
 804935e:	66 90                	xchg   %ax,%ax

08049360 <rsi_ble_init>:
}

volatile UINT16 first_cmd_pkt_rcvd = 0;
extern volatile int dbg_packet_pending ;
INT16 rsi_ble_init (void)
{
 8049360:	55                   	push   %ebp
 8049361:	89 e5                	mov    %esp,%ebp
 8049363:	56                   	push   %esi
 8049364:	53                   	push   %ebx
    INT16 RetVal;
    UINT16 ResponseType = 0;
		char ch = 'x';
    
    rsi_bt_ScannedDevsCount = 0;
 8049365:	c6 05 42 c6 04 08 00 	movb   $0x0,0x804c642

    /*Enable the H/W module interrupt*/
    rsi_irq_start();
 804936c:	e8 53 08 00 00       	call   8049bc4 <rsi_irq_start>
    
    while(1) {
        
       /* MCU receives an external interrupt from the module */
        if(rsi_bt_AppControlBlock.PacketPending == RSI_TRUE ) {
 8049371:	a1 e2 c6 04 08       	mov    0x804c6e2,%eax
 8049376:	48                   	dec    %eax
 8049377:	0f 85 e2 00 00 00    	jne    804945f <rsi_ble_init+0xff>
            printf("Response Rcvd xxxxxxxxxxx\n");
 804937d:	83 ec 0c             	sub    $0xc,%esp
 8049380:	68 a8 a5 04 08       	push   $0x804a5a8
 8049385:	e8 06 f4 ff ff       	call   8048790 <puts@plt>
            RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
 804938a:	c7 04 24 e6 c6 04 08 	movl   $0x804c6e6,(%esp)
 8049391:	e8 4a f6 ff ff       	call   80489e0 <rsi_frame_read>
  UINT08                   *payloadPtr = rsp + RSI_BT_FRAME_DESC_LEN;
  UINT16 ii;

  /* Retrieve response code from the received packet */
#ifdef RSI_LITTLE_ENDIAN
  temp_status = (*(UINT16 *)(descPtr + RSI_BT_STATUS_OFFSET));
 8049396:	66 8b 15 f2 c6 04 08 	mov    0x804c6f2,%dx
        if(rsi_bt_AppControlBlock.PacketPending == RSI_TRUE ) {
            printf("Response Rcvd xxxxxxxxxxx\n");
            RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
            rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);
            
            if(RetVal == 0) {
 804939d:	83 c4 10             	add    $0x10,%esp
  UINT16 ii;

  /* Retrieve response code from the received packet */
#ifdef RSI_LITTLE_ENDIAN
  temp_status = (*(UINT16 *)(descPtr + RSI_BT_STATUS_OFFSET));
  temp_rspCode = *((UINT16 *)(descPtr + RSI_BT_RSP_TYPE_OFFSET)); 
 80493a0:	8b 1d e8 c6 04 08    	mov    0x804c6e8,%ebx
        
       /* MCU receives an external interrupt from the module */
        if(rsi_bt_AppControlBlock.PacketPending == RSI_TRUE ) {
            printf("Response Rcvd xxxxxxxxxxx\n");
            RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
            rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);
 80493a6:	c7 05 9e c6 04 08 f2 	movl   $0x804c6f2,0x804c69e
 80493ad:	c6 04 08 

  /* Copy the response type and status to payloadPtr-4, payloadPtr-2
   * locations respectively.
   */
#ifdef RSI_LITTLE_ENDIAN
  *((UINT16 *)(payloadPtr - 2)) = temp_status;
 80493b0:	66 89 15 f4 c6 04 08 	mov    %dx,0x804c6f4
  *((UINT16 *)(payloadPtr - 4)) = temp_rspCode;
 80493b7:	66 89 1d f2 c6 04 08 	mov    %bx,0x804c6f2
        if(rsi_bt_AppControlBlock.PacketPending == RSI_TRUE ) {
            printf("Response Rcvd xxxxxxxxxxx\n");
            RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
            rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);
            
            if(RetVal == 0) {
 80493be:	66 85 c0             	test   %ax,%ax
 80493c1:	0f 85 88 00 00 00    	jne    804944f <rsi_ble_init+0xef>

#ifdef RSI_LITTLE_ENDIAN
                /* Retrieve response code from the received packet */ 
                ResponseType            = *(UINT16 *)(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);    
                rsi_bt_AppControlBlock.ErrorCode = *(UINT16 *)rsi_bt_AppControlBlock.ResponseFrame->Status;
 80493c7:	66 89 15 9c c6 04 08 	mov    %dx,0x804c69c
#else
                /* Retrieve response code from the received packet */
                ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
                rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(&rsi_bt_AppControlBlock.ResponseFrame->Status);
#endif
                printf("Response Rcvd %d\n",ResponseType);
 80493ce:	0f b7 f3             	movzwl %bx,%esi
 80493d1:	52                   	push   %edx
 80493d2:	52                   	push   %edx
 80493d3:	56                   	push   %esi
 80493d4:	68 c2 a5 04 08       	push   $0x804a5c2
 80493d9:	e8 22 f3 ff ff       	call   8048700 <printf@plt>
								if(first_cmd_pkt_rcvd == 1){
 80493de:	66 a1 38 c6 04 08    	mov    0x804c638,%ax
 80493e4:	83 c4 10             	add    $0x10,%esp
 80493e7:	66 48                	dec    %ax
 80493e9:	75 36                	jne    8049421 <rsi_ble_init+0xc1>
												rsi_ble_decode_rsp(ResponseType, rsi_bt_AppControlBlock.ErrorCode, (void*)&rsi_bt_AppControlBlock.ResponseFrame->uCmdRspPayLoad);
 80493eb:	50                   	push   %eax
 80493ec:	a1 9e c6 04 08       	mov    0x804c69e,%eax
 80493f1:	83 c0 04             	add    $0x4,%eax
 80493f4:	50                   	push   %eax
 80493f5:	0f b7 05 9c c6 04 08 	movzwl 0x804c69c,%eax
 80493fc:	50                   	push   %eax
 80493fd:	56                   	push   %esi
 80493fe:	e8 b4 03 00 00       	call   80497b7 <rsi_ble_decode_rsp>
												printf("Enter to continue...\n");
 8049403:	c7 04 24 d4 a5 04 08 	movl   $0x804a5d4,(%esp)
 804940a:	e8 81 f3 ff ff       	call   8048790 <puts@plt>
												ch = getchar();
 804940f:	e8 0c f3 ff ff       	call   8048720 <getchar@plt>
												getchar();
 8049414:	e8 07 f3 ff ff       	call   8048720 <getchar@plt>
												rsi_ble_app();
 8049419:	e8 62 02 00 00       	call   8049680 <rsi_ble_app>
 804941e:	83 c4 10             	add    $0x10,%esp
								}
                /* Switch between type of packet received */
                switch (ResponseType) {
 8049421:	66 81 fb 05 05       	cmp    $0x505,%bx
 8049426:	75 37                	jne    804945f <rsi_ble_init+0xff>

                    case RSI_BT_RSP_CARD_READY:
                         if(!rsi_bt_AppControlBlock.ErrorCode) {
 8049428:	66 83 3d 9c c6 04 08 	cmpw   $0x0,0x804c69c
 804942f:	00 
 8049430:	75 58                	jne    804948a <rsi_ble_init+0x12a>
                             if (RSI_BT_DEVICE_MODE == RSI_BLE_PERIPHERAL_MODE) {
                                 printf("Card ready received RSI_BLE_PERIPHERAL_MODE\n");
                             } else if (RSI_BT_DEVICE_MODE == RSI_BLE_CENTRAL_MODE) {
                                 printf("Card ready received  RSI_BLE_CENTRAL_MODE\n");
 8049432:	83 ec 0c             	sub    $0xc,%esp
 8049435:	68 e9 a5 04 08       	push   $0x804a5e9
 804943a:	e8 51 f3 ff ff       	call   8048790 <puts@plt>
                             }
			                       first_cmd_pkt_rcvd = 1;
 804943f:	66 c7 05 38 c6 04 08 	movw   $0x1,0x804c638
 8049446:	01 00 
  			                     rsi_ble_app();
 8049448:	e8 33 02 00 00       	call   8049680 <rsi_ble_app>
 804944d:	eb 0d                	jmp    804945c <rsi_ble_init+0xfc>
                         break;
#endif
                    default:;
                } //switch
            }
					  else printf("Error reading response ....\n");	//if frame read ret_val
 804944f:	83 ec 0c             	sub    $0xc,%esp
 8049452:	68 13 a6 04 08       	push   $0x804a613
 8049457:	e8 34 f3 ff ff       	call   8048790 <puts@plt>
 804945c:	83 c4 10             	add    $0x10,%esp
        } // if(rsi_bt_AppControlBlock.PacketPending == RSI_TRUE)

        rsi_bt_AppControlBlock.PacketPending = (rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0);
 804945f:	31 c0                	xor    %eax,%eax
 8049461:	66 83 3d 99 c6 04 08 	cmpw   $0x0,0x804c699
 8049468:	00 
 8049469:	0f 95 c0             	setne  %al
 804946c:	a3 e2 c6 04 08       	mov    %eax,0x804c6e2
				if(first_cmd_pkt_rcvd)
 8049471:	66 a1 38 c6 04 08    	mov    0x804c638,%ax
 8049477:	66 85 c0             	test   %ax,%ax
 804947a:	0f 84 f1 fe ff ff    	je     8049371 <rsi_ble_init+0x11>
					rsi_ble_app();
 8049480:	e8 fb 01 00 00       	call   8049680 <rsi_ble_app>
 8049485:	e9 e7 fe ff ff       	jmp    8049371 <rsi_ble_init+0x11>
    }   //while

    return 0;
}
 804948a:	8d 65 f8             	lea    -0x8(%ebp),%esp
 804948d:	83 c8 ff             	or     $0xffffffff,%eax
 8049490:	5b                   	pop    %ebx
 8049491:	5e                   	pop    %esi
 8049492:	5d                   	pop    %ebp
 8049493:	c3                   	ret    

08049494 <ble_main>:

RSI_BT_RESPONSE *rsi_bt_parse_response(UINT08 *rsp);
INT16 rsi_ble_init (void);

INT16 ble_main (void )
{
 8049494:	55                   	push   %ebp
 8049495:	89 e5                	mov    %esp,%ebp
 8049497:	83 ec 14             	sub    $0x14,%esp
  INT16   RetVal;
  UINT16  ResponseType;

  rsi_bt_AppControlBlock.uBLEApiInitParams = (RSI_BLE_API *)malloc(sizeof (RSI_BLE_API));
 804949a:	6a 33                	push   $0x33
 804949c:	e8 df f2 ff ff       	call   8048780 <malloc@plt>
 80494a1:	a3 de c6 04 08       	mov    %eax,0x804c6de
  
  /* Initialize the BLE functionality */
  if(rsi_ble_init()){
 80494a6:	e8 b5 fe ff ff       	call   8049360 <rsi_ble_init>
 80494ab:	83 c4 10             	add    $0x10,%esp
 80494ae:	66 85 c0             	test   %ax,%ax
 80494b1:	74 17                	je     80494ca <ble_main+0x36>
    printf("Error BLE init\n");
 80494b3:	83 ec 0c             	sub    $0xc,%esp
 80494b6:	68 2f a6 04 08       	push   $0x804a62f
 80494bb:	e8 d0 f2 ff ff       	call   8048790 <puts@plt>
    return 0;
 80494c0:	83 c4 10             	add    $0x10,%esp
 80494c3:	31 c0                	xor    %eax,%eax
 80494c5:	e9 06 01 00 00       	jmp    80495d0 <ble_main+0x13c>
   }

  printf("Came out of BLE INIT\n");
 80494ca:	83 ec 0c             	sub    $0xc,%esp
 80494cd:	68 3e a6 04 08       	push   $0x804a63e
 80494d2:	e8 b9 f2 ff ff       	call   8048790 <puts@plt>
  rsi_bt_AppControlBlock.PacketPending = (rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0);
 80494d7:	83 c4 10             	add    $0x10,%esp
 80494da:	31 c0                	xor    %eax,%eax
 80494dc:	66 83 3d 99 c6 04 08 	cmpw   $0x0,0x804c699
 80494e3:	00 
 80494e4:	0f 95 c0             	setne  %al
 80494e7:	a3 e2 c6 04 08       	mov    %eax,0x804c6e2
  
  while(1)
  {     

    /* MCU receives an external interrupt from the module */
    if( rsi_bt_AppControlBlock.PacketPending == RSI_TRUE )
 80494ec:	a1 e2 c6 04 08       	mov    0x804c6e2,%eax
 80494f1:	48                   	dec    %eax
 80494f2:	75 e6                	jne    80494da <ble_main+0x46>
    {
        printf("Dequeue packet \n");
 80494f4:	83 ec 0c             	sub    $0xc,%esp
 80494f7:	68 53 a6 04 08       	push   $0x804a653
 80494fc:	e8 8f f2 ff ff       	call   8048790 <puts@plt>
        RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
 8049501:	c7 04 24 e6 c6 04 08 	movl   $0x804c6e6,(%esp)
 8049508:	e8 d3 f4 ff ff       	call   80489e0 <rsi_frame_read>
  UINT08                   *payloadPtr = rsp + RSI_BT_FRAME_DESC_LEN;
  UINT16 ii;

  /* Retrieve response code from the received packet */
#ifdef RSI_LITTLE_ENDIAN
  temp_status = (*(UINT16 *)(descPtr + RSI_BT_STATUS_OFFSET));
 804950d:	66 8b 15 f2 c6 04 08 	mov    0x804c6f2,%dx
    {
        printf("Dequeue packet \n");
        RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
        rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);

        if(RetVal == 0)
 8049514:	83 c4 10             	add    $0x10,%esp
  UINT16 ii;

  /* Retrieve response code from the received packet */
#ifdef RSI_LITTLE_ENDIAN
  temp_status = (*(UINT16 *)(descPtr + RSI_BT_STATUS_OFFSET));
  temp_rspCode = *((UINT16 *)(descPtr + RSI_BT_RSP_TYPE_OFFSET)); 
 8049517:	8b 0d e8 c6 04 08    	mov    0x804c6e8,%ecx
    /* MCU receives an external interrupt from the module */
    if( rsi_bt_AppControlBlock.PacketPending == RSI_TRUE )
    {
        printf("Dequeue packet \n");
        RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
        rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);
 804951d:	c7 05 9e c6 04 08 f2 	movl   $0x804c6f2,0x804c69e
 8049524:	c6 04 08 

  /* Copy the response type and status to payloadPtr-4, payloadPtr-2
   * locations respectively.
   */
#ifdef RSI_LITTLE_ENDIAN
  *((UINT16 *)(payloadPtr - 2)) = temp_status;
 8049527:	66 89 15 f4 c6 04 08 	mov    %dx,0x804c6f4
  *((UINT16 *)(payloadPtr - 4)) = temp_rspCode;
 804952e:	66 89 0d f2 c6 04 08 	mov    %cx,0x804c6f2
    {
        printf("Dequeue packet \n");
        RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
        rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);

        if(RetVal == 0)
 8049535:	66 85 c0             	test   %ax,%ax
 8049538:	75 a0                	jne    80494da <ble_main+0x46>
            ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
            rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(&rsi_bt_AppControlBlock.ResponseFrame->Status);
#endif                    

            /* Switch between type of packet received */
            switch (ResponseType)
 804953a:	66 83 f9 7f          	cmp    $0x7f,%cx
        if(RetVal == 0)
        {
#ifdef RSI_LITTLE_ENDIAN
            /* Retrieve response code from the received packet */ 
            ResponseType            = *(UINT16 *)(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);    
            rsi_bt_AppControlBlock.ErrorCode = *(UINT16 *)rsi_bt_AppControlBlock.ResponseFrame->Status;
 804953e:	66 89 15 9c c6 04 08 	mov    %dx,0x804c69c
            ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
            rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(&rsi_bt_AppControlBlock.ResponseFrame->Status);
#endif                    

            /* Switch between type of packet received */
            switch (ResponseType)
 8049545:	74 37                	je     804957e <ble_main+0xea>
 8049547:	77 08                	ja     8049551 <ble_main+0xbd>
 8049549:	66 83 f9 77          	cmp    $0x77,%cx
 804954d:	75 8b                	jne    80494da <ble_main+0x46>
 804954f:	eb 14                	jmp    8049565 <ble_main+0xd1>
 8049551:	66 81 f9 81 00       	cmp    $0x81,%cx
 8049556:	74 49                	je     80495a1 <ble_main+0x10d>
 8049558:	66 81 f9 83 00       	cmp    $0x83,%cx
 804955d:	0f 85 77 ff ff ff    	jne    80494da <ble_main+0x46>
 8049563:	eb 5f                	jmp    80495c4 <ble_main+0x130>
            {
              case RSI_BLE_REQ_CONNECT:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
 8049565:	66 85 d2             	test   %dx,%dx
 8049568:	75 63                	jne    80495cd <ble_main+0x139>
                       RetVal = rsi_ble_init_struct(RSI_BLE_REQ_QUERY_PROFILES_LIST);
 804956a:	83 ec 0c             	sub    $0xc,%esp
 804956d:	6a 7f                	push   $0x7f
 804956f:	e8 68 fa ff ff       	call   8048fdc <rsi_ble_init_struct>
                       RetVal = rsi_ble_query_profiles_list();
 8049574:	e8 23 08 00 00       	call   8049d9c <rsi_ble_query_profiles_list>
 8049579:	e9 59 ff ff ff       	jmp    80494d7 <ble_main+0x43>
                       return -1;
                   }
                   break;

              case RSI_BLE_REQ_QUERY_PROFILES_LIST:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
 804957e:	66 85 d2             	test   %dx,%dx
 8049581:	75 4a                	jne    80495cd <ble_main+0x139>
                       RetVal = rsi_ble_init_struct(RSI_BLE_REQ_QUERY_CHARACTERISTIC_SERVICES);
 8049583:	83 ec 0c             	sub    $0xc,%esp
 8049586:	68 81 00 00 00       	push   $0x81
 804958b:	e8 4c fa ff ff       	call   8048fdc <rsi_ble_init_struct>
                       RetVal = rsi_ble_query_characteristic_services(&rsi_bt_AppControlBlock.uBLEApiInitParams->uLeCharServ);
 8049590:	58                   	pop    %eax
 8049591:	ff 35 de c6 04 08    	pushl  0x804c6de
 8049597:	e8 2d 08 00 00       	call   8049dc9 <rsi_ble_query_characteristic_services>
 804959c:	e9 36 ff ff ff       	jmp    80494d7 <ble_main+0x43>
                       return -1;
                   }
                   break;

              case RSI_BLE_REQ_QUERY_CHARACTERISTIC_SERVICES:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
 80495a1:	66 85 d2             	test   %dx,%dx
 80495a4:	75 27                	jne    80495cd <ble_main+0x139>
                       RetVal = rsi_ble_init_struct(RSI_BLE_REQ_READ_CHAR_VALUE_BY_UUID);
 80495a6:	83 ec 0c             	sub    $0xc,%esp
 80495a9:	68 83 00 00 00       	push   $0x83
 80495ae:	e8 29 fa ff ff       	call   8048fdc <rsi_ble_init_struct>
                       RetVal = rsi_ble_read_char_value_by_UUID(&rsi_bt_AppControlBlock.uBLEApiInitParams->uLeCharVal);
 80495b3:	59                   	pop    %ecx
 80495b4:	ff 35 de c6 04 08    	pushl  0x804c6de
 80495ba:	e8 38 08 00 00       	call   8049df7 <rsi_ble_read_char_value_by_UUID>
 80495bf:	e9 13 ff ff ff       	jmp    80494d7 <ble_main+0x43>
                       return -1;
                   }
                   break;

              case RSI_BLE_REQ_READ_CHAR_VALUE_BY_UUID:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
 80495c4:	66 85 d2             	test   %dx,%dx
 80495c7:	0f 84 0d ff ff ff    	je     80494da <ble_main+0x46>
              case RSI_BLE_REQ_CONNECT:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
                       RetVal = rsi_ble_init_struct(RSI_BLE_REQ_QUERY_PROFILES_LIST);
                       RetVal = rsi_ble_query_profiles_list();
                   } else {
                       return -1;
 80495cd:	83 c8 ff             	or     $0xffffffff,%eax
    }
    rsi_bt_AppControlBlock.PacketPending = (rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0);
  }  // while

  return 0;
}
 80495d0:	c9                   	leave  
 80495d1:	c3                   	ret    

080495d2 <rsi_bt_parse_response>:
 * @section description 
 * This API is used to parse the recieved response. This returns the 
 * pointer which points to rsptype, status, response payload in order.
 */
RSI_BT_RESPONSE *rsi_bt_parse_response(UINT08 *rsp)
{
 80495d2:	55                   	push   %ebp
 80495d3:	89 e5                	mov    %esp,%ebp
 80495d5:	8b 45 08             	mov    0x8(%ebp),%eax

  /* Copy the response type and status to payloadPtr-4, payloadPtr-2
   * locations respectively.
   */
#ifdef RSI_LITTLE_ENDIAN
  *((UINT16 *)(payloadPtr - 2)) = temp_status;
 80495d8:	66 8b 48 0c          	mov    0xc(%eax),%cx
  UINT16 ii;

  /* Retrieve response code from the received packet */
#ifdef RSI_LITTLE_ENDIAN
  temp_status = (*(UINT16 *)(descPtr + RSI_BT_STATUS_OFFSET));
  temp_rspCode = *((UINT16 *)(descPtr + RSI_BT_RSP_TYPE_OFFSET)); 
 80495dc:	66 8b 50 02          	mov    0x2(%eax),%dx

  /* Copy the response type and status to payloadPtr-4, payloadPtr-2
   * locations respectively.
   */
#ifdef RSI_LITTLE_ENDIAN
  *((UINT16 *)(payloadPtr - 2)) = temp_status;
 80495e0:	66 89 48 0e          	mov    %cx,0xe(%eax)
  *((UINT16 *)(payloadPtr - 4)) = temp_rspCode;
 80495e4:	66 89 50 0c          	mov    %dx,0xc(%eax)
  rsi_uint16_to_2bytes((payloadPtr - 4), temp_rspCode);
#endif

  temp_uCmdRspPtr = (RSI_BT_RESPONSE *)(payloadPtr - 4);

  return temp_uCmdRspPtr;
 80495e8:	83 c0 0c             	add    $0xc,%eax
}
 80495eb:	5d                   	pop    %ebp
 80495ec:	c3                   	ret    
 80495ed:	0f 1f 00             	nopl   (%eax)

080495f0 <print_options>:
        "PXPR_LINK_IS_LOST"
};


INT16 print_options(void)
{
 80495f0:	55                   	push   %ebp
 80495f1:	89 e5                	mov    %esp,%ebp
 80495f3:	53                   	push   %ebx
 80495f4:	31 db                	xor    %ebx,%ebx
 80495f6:	83 ec 14             	sub    $0x14,%esp
				UINT16 max_cmds = RSI_BLE_REQ_EXECUTE_LONG_ATT_VALUE_WRITE  - RSI_BLE_REQ_ADVERTISE + 1;
				int in_cmd;

				for  (ii = 0; ii < max_cmds; ii++)
				{
								if (ii == 0)
 80495f9:	66 85 db             	test   %bx,%bx
 80495fc:	75 0a                	jne    8049608 <print_options+0x18>
								{
												printf("\nBLE core commands \n=========================\n");
 80495fe:	83 ec 0c             	sub    $0xc,%esp
 8049601:	68 63 a6 04 08       	push   $0x804a663
 8049606:	eb 1e                	jmp    8049626 <print_options+0x36>
								}
								else if (ii == 6)
 8049608:	66 83 fb 06          	cmp    $0x6,%bx
 804960c:	75 0a                	jne    8049618 <print_options+0x28>
								{
												printf("\nBLE SMP commands \n=========================\n");
 804960e:	83 ec 0c             	sub    $0xc,%esp
 8049611:	68 91 a6 04 08       	push   $0x804a691
 8049616:	eb 0e                	jmp    8049626 <print_options+0x36>
								}
								else if (ii == 11)
 8049618:	66 83 fb 0b          	cmp    $0xb,%bx
 804961c:	75 10                	jne    804962e <print_options+0x3e>
								{
												printf("\nBLE GATT commands \n=========================\n");
 804961e:	83 ec 0c             	sub    $0xc,%esp
 8049621:	68 be a6 04 08       	push   $0x804a6be
 8049626:	e8 65 f1 ff ff       	call   8048790 <puts@plt>
 804962b:	83 c4 10             	add    $0x10,%esp
								}
								printf(" %d. %s\n",ii+1, ble_commands_str[ii]);
 804962e:	8b 04 9d d0 c5 04 08 	mov    0x804c5d0(,%ebx,4),%eax
        "PXPR_IMMEDIATE_ALERT",
        "PXPR_LINK_IS_LOST"
};


INT16 print_options(void)
 8049635:	43                   	inc    %ebx
								}
								else if (ii == 11)
								{
												printf("\nBLE GATT commands \n=========================\n");
								}
								printf(" %d. %s\n",ii+1, ble_commands_str[ii]);
 8049636:	51                   	push   %ecx
 8049637:	50                   	push   %eax
 8049638:	53                   	push   %ebx
 8049639:	68 ec a6 04 08       	push   $0x804a6ec
 804963e:	e8 bd f0 ff ff       	call   8048700 <printf@plt>
{
				UINT16 ii = 0;
				UINT16 max_cmds = RSI_BLE_REQ_EXECUTE_LONG_ATT_VALUE_WRITE  - RSI_BLE_REQ_ADVERTISE + 1;
				int in_cmd;

				for  (ii = 0; ii < max_cmds; ii++)
 8049643:	83 c4 10             	add    $0x10,%esp
 8049646:	83 fb 18             	cmp    $0x18,%ebx
 8049649:	75 ae                	jne    80495f9 <print_options+0x9>
								{
												printf("\nBLE GATT commands \n=========================\n");
								}
								printf(" %d. %s\n",ii+1, ble_commands_str[ii]);
				}
				printf("Enter your choice:\n");
 804964b:	83 ec 0c             	sub    $0xc,%esp
 804964e:	68 f5 a6 04 08       	push   $0x804a6f5
 8049653:	e8 38 f1 ff ff       	call   8048790 <puts@plt>
				scanf("%d",&in_cmd);
 8049658:	58                   	pop    %eax
 8049659:	5a                   	pop    %edx
 804965a:	8d 45 f4             	lea    -0xc(%ebp),%eax
 804965d:	50                   	push   %eax
 804965e:	68 9c ad 04 08       	push   $0x804ad9c
 8049663:	e8 b8 f1 ff ff       	call   8048820 <__isoc99_scanf@plt>
        if (in_cmd > max_cmds)
 8049668:	83 c4 10             	add    $0x10,%esp
 804966b:	83 7d f4 18          	cmpl   $0x18,-0xc(%ebp)
 804966f:	7e 07                	jle    8049678 <print_options+0x88>
        {
          in_cmd = -1;
 8049671:	c7 45 f4 ff ff ff ff 	movl   $0xffffffff,-0xc(%ebp)
        }

				return (INT16)in_cmd;
}
 8049678:	8b 45 f4             	mov    -0xc(%ebp),%eax
 804967b:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 804967e:	c9                   	leave  
 804967f:	c3                   	ret    

08049680 <rsi_ble_app>:

void rsi_ble_app(void)
{
 8049680:	55                   	push   %ebp
 8049681:	89 e5                	mov    %esp,%ebp
 8049683:	53                   	push   %ebx
 8049684:	50                   	push   %eax
				INT16 cmd;
				INT16 RetVal;
				char ch;

				cmd = print_options();
 8049685:	e8 66 ff ff ff       	call   80495f0 <print_options>

				if (cmd > 0)
 804968a:	66 85 c0             	test   %ax,%ax
{
				INT16 cmd;
				INT16 RetVal;
				char ch;

				cmd = print_options();
 804968d:	89 c3                	mov    %eax,%ebx

				if (cmd > 0)
 804968f:	7e 26                	jle    80496b7 <rsi_ble_app+0x37>
				{
								printf("Executing the command %s\n",ble_commands_str[cmd -1]);
 8049691:	50                   	push   %eax
 8049692:	50                   	push   %eax
 8049693:	0f bf c3             	movswl %bx,%eax
 8049696:	ff 34 85 cc c5 04 08 	pushl  0x804c5cc(,%eax,4)
								RetVal = rsi_ble_init_struct((cmd - 1) + RSI_BLE_REQ_ADVERTISE);
 804969d:	83 c3 74             	add    $0x74,%ebx
 80496a0:	0f b7 db             	movzwl %bx,%ebx

				cmd = print_options();

				if (cmd > 0)
				{
								printf("Executing the command %s\n",ble_commands_str[cmd -1]);
 80496a3:	68 08 a7 04 08       	push   $0x804a708
 80496a8:	e8 53 f0 ff ff       	call   8048700 <printf@plt>
								RetVal = rsi_ble_init_struct((cmd - 1) + RSI_BLE_REQ_ADVERTISE);
 80496ad:	89 1c 24             	mov    %ebx,(%esp)
 80496b0:	e8 27 f9 ff ff       	call   8048fdc <rsi_ble_init_struct>
 80496b5:	eb 0d                	jmp    80496c4 <rsi_ble_app+0x44>
				}
				else
								printf("Waiting for events ...\n");
 80496b7:	83 ec 0c             	sub    $0xc,%esp
 80496ba:	68 22 a7 04 08       	push   $0x804a722
 80496bf:	e8 cc f0 ff ff       	call   8048790 <puts@plt>
 80496c4:	83 c4 10             	add    $0x10,%esp
}
 80496c7:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 80496ca:	c9                   	leave  
 80496cb:	c3                   	ret    

080496cc <print_uuid>:

/* Process responses */
void print_uuid(UUID *t_uuid)
{
 80496cc:	55                   	push   %ebp
 80496cd:	89 e5                	mov    %esp,%ebp
 80496cf:	57                   	push   %edi
 80496d0:	56                   	push   %esi
 80496d1:	53                   	push   %ebx
				UINT16 jj;
				UINT08 *tmp_uuid;

				printf("UUID:");
				tmp_uuid = (UINT08*)&t_uuid->Val;
				for (jj = 0; jj < t_uuid->size; jj++)
 80496d2:	31 db                	xor    %ebx,%ebx
								printf("Waiting for events ...\n");
}

/* Process responses */
void print_uuid(UUID *t_uuid)
{
 80496d4:	83 ec 18             	sub    $0x18,%esp
 80496d7:	8b 75 08             	mov    0x8(%ebp),%esi
				UINT16 jj;
				UINT08 *tmp_uuid;

				printf("UUID:");
 80496da:	68 39 a7 04 08       	push   $0x804a739
 80496df:	e8 1c f0 ff ff       	call   8048700 <printf@plt>
				tmp_uuid = (UINT08*)&t_uuid->Val;
				for (jj = 0; jj < t_uuid->size; jj++)
 80496e4:	83 c4 10             	add    $0x10,%esp
{
				UINT16 jj;
				UINT08 *tmp_uuid;

				printf("UUID:");
				tmp_uuid = (UINT08*)&t_uuid->Val;
 80496e7:	8d 7e 04             	lea    0x4(%esi),%edi
				for (jj = 0; jj < t_uuid->size; jj++)
 80496ea:	eb 18                	jmp    8049704 <print_uuid+0x38>
				{
								printf("%02x",tmp_uuid[jj]); 
 80496ec:	50                   	push   %eax
 80496ed:	50                   	push   %eax
 80496ee:	0f b7 c3             	movzwl %bx,%eax
 80496f1:	0f b6 04 07          	movzbl (%edi,%eax,1),%eax
				UINT16 jj;
				UINT08 *tmp_uuid;

				printf("UUID:");
				tmp_uuid = (UINT08*)&t_uuid->Val;
				for (jj = 0; jj < t_uuid->size; jj++)
 80496f5:	43                   	inc    %ebx
				{
								printf("%02x",tmp_uuid[jj]); 
 80496f6:	50                   	push   %eax
 80496f7:	68 a3 a7 04 08       	push   $0x804a7a3
 80496fc:	e8 ff ef ff ff       	call   8048700 <printf@plt>
				UINT16 jj;
				UINT08 *tmp_uuid;

				printf("UUID:");
				tmp_uuid = (UINT08*)&t_uuid->Val;
				for (jj = 0; jj < t_uuid->size; jj++)
 8049701:	83 c4 10             	add    $0x10,%esp
 8049704:	0f b6 06             	movzbl (%esi),%eax
 8049707:	66 39 c3             	cmp    %ax,%bx
 804970a:	72 e0                	jb     80496ec <print_uuid+0x20>
				{
								printf("%02x",tmp_uuid[jj]); 
				}
				printf("\n");
 804970c:	c7 45 08 0a 00 00 00 	movl   $0xa,0x8(%ebp)
}
 8049713:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8049716:	5b                   	pop    %ebx
 8049717:	5e                   	pop    %esi
 8049718:	5f                   	pop    %edi
 8049719:	5d                   	pop    %ebp
				tmp_uuid = (UINT08*)&t_uuid->Val;
				for (jj = 0; jj < t_uuid->size; jj++)
				{
								printf("%02x",tmp_uuid[jj]); 
				}
				printf("\n");
 804971a:	e9 c1 f0 ff ff       	jmp    80487e0 <putchar@plt>

0804971f <print_profile_descriptor>:
}

void print_profile_descriptor(PROFILE_DESCRIPTOR *pd)
{
 804971f:	55                   	push   %ebp
 8049720:	89 e5                	mov    %esp,%ebp
 8049722:	53                   	push   %ebx
 8049723:	83 ec 0c             	sub    $0xc,%esp
 8049726:	8b 5d 08             	mov    0x8(%ebp),%ebx
				UINT08 *tmp_uuid;
				printf("StartHandle : %02x", *(UINT16*)pd->StartHandle);
 8049729:	0f b7 03             	movzwl (%ebx),%eax
 804972c:	50                   	push   %eax
 804972d:	68 3f a7 04 08       	push   $0x804a73f
 8049732:	e8 c9 ef ff ff       	call   8048700 <printf@plt>
				printf("EndHandle: %02x", *(UINT16*)pd->EndHandle);
 8049737:	58                   	pop    %eax
 8049738:	0f b7 43 02          	movzwl 0x2(%ebx),%eax
 804973c:	5a                   	pop    %edx
 804973d:	50                   	push   %eax
 804973e:	68 52 a7 04 08       	push   $0x804a752
 8049743:	e8 b8 ef ff ff       	call   8048700 <printf@plt>
				printf("uuid size: %02x", pd->ProfileUUID.size);
 8049748:	59                   	pop    %ecx
 8049749:	58                   	pop    %eax
 804974a:	0f b6 43 04          	movzbl 0x4(%ebx),%eax

				print_uuid(&pd->ProfileUUID);
 804974e:	83 c3 04             	add    $0x4,%ebx
void print_profile_descriptor(PROFILE_DESCRIPTOR *pd)
{
				UINT08 *tmp_uuid;
				printf("StartHandle : %02x", *(UINT16*)pd->StartHandle);
				printf("EndHandle: %02x", *(UINT16*)pd->EndHandle);
				printf("uuid size: %02x", pd->ProfileUUID.size);
 8049751:	50                   	push   %eax
 8049752:	68 62 a7 04 08       	push   $0x804a762
 8049757:	e8 a4 ef ff ff       	call   8048700 <printf@plt>

				print_uuid(&pd->ProfileUUID);
 804975c:	83 c4 10             	add    $0x10,%esp
 804975f:	89 5d 08             	mov    %ebx,0x8(%ebp)
}
 8049762:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 8049765:	c9                   	leave  
				UINT08 *tmp_uuid;
				printf("StartHandle : %02x", *(UINT16*)pd->StartHandle);
				printf("EndHandle: %02x", *(UINT16*)pd->EndHandle);
				printf("uuid size: %02x", pd->ProfileUUID.size);

				print_uuid(&pd->ProfileUUID);
 8049766:	e9 61 ff ff ff       	jmp    80496cc <print_uuid>

0804976b <print_servcie>:
}
void print_servcie(INCLUDE_SERVICE *is)
{
 804976b:	55                   	push   %ebp
 804976c:	89 e5                	mov    %esp,%ebp
 804976e:	53                   	push   %ebx
 804976f:	83 ec 0c             	sub    $0xc,%esp
 8049772:	8b 5d 08             	mov    0x8(%ebp),%ebx
				printf("Handle : %02x", *(UINT16*)is->Handle);
 8049775:	0f b7 03             	movzwl (%ebx),%eax
 8049778:	50                   	push   %eax
 8049779:	68 9a a7 04 08       	push   $0x804a79a
 804977e:	e8 7d ef ff ff       	call   8048700 <printf@plt>
				printf("Include Start Handle : %02x", *(UINT16*)is->IncludeStartHandle);
 8049783:	58                   	pop    %eax
 8049784:	0f b7 43 02          	movzwl 0x2(%ebx),%eax
 8049788:	5a                   	pop    %edx
 8049789:	50                   	push   %eax
 804978a:	68 72 a7 04 08       	push   $0x804a772
 804978f:	e8 6c ef ff ff       	call   8048700 <printf@plt>
				printf("Include End Handle : %02x", *(UINT16*)is->IncludeEndHandle);
 8049794:	59                   	pop    %ecx
 8049795:	58                   	pop    %eax
 8049796:	0f b7 43 04          	movzwl 0x4(%ebx),%eax
				print_uuid(&is->IncludeUUID);
 804979a:	83 c3 06             	add    $0x6,%ebx
}
void print_servcie(INCLUDE_SERVICE *is)
{
				printf("Handle : %02x", *(UINT16*)is->Handle);
				printf("Include Start Handle : %02x", *(UINT16*)is->IncludeStartHandle);
				printf("Include End Handle : %02x", *(UINT16*)is->IncludeEndHandle);
 804979d:	50                   	push   %eax
 804979e:	68 8e a7 04 08       	push   $0x804a78e
 80497a3:	e8 58 ef ff ff       	call   8048700 <printf@plt>
				print_uuid(&is->IncludeUUID);
 80497a8:	83 c4 10             	add    $0x10,%esp
 80497ab:	89 5d 08             	mov    %ebx,0x8(%ebp)
}
 80497ae:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 80497b1:	c9                   	leave  
void print_servcie(INCLUDE_SERVICE *is)
{
				printf("Handle : %02x", *(UINT16*)is->Handle);
				printf("Include Start Handle : %02x", *(UINT16*)is->IncludeStartHandle);
				printf("Include End Handle : %02x", *(UINT16*)is->IncludeEndHandle);
				print_uuid(&is->IncludeUUID);
 80497b2:	e9 15 ff ff ff       	jmp    80496cc <print_uuid>

080497b7 <rsi_ble_decode_rsp>:
}

void rsi_ble_decode_rsp(UINT16 rsp_type, UINT16 status, void *rsp)
{
 80497b7:	55                   	push   %ebp
 80497b8:	89 e5                	mov    %esp,%ebp
 80497ba:	57                   	push   %edi
 80497bb:	56                   	push   %esi
 80497bc:	53                   	push   %ebx
 80497bd:	83 ec 1c             	sub    $0x1c,%esp
 80497c0:	8b 75 08             	mov    0x8(%ebp),%esi
 80497c3:	8b 5d 10             	mov    0x10(%ebp),%ebx
 80497c6:	0f b7 45 0c          	movzwl 0xc(%ebp),%eax
				UINT16 ii;
				INT16 RetVal;

				if ( (rsp_type >= RSI_BLE_RSP_ADVERTISE) && (rsp_type <= RSI_BLE_RSP_EXECUTE_LONG_ATT_VALUE_WRITE))
 80497ca:	8d 56 8b             	lea    -0x75(%esi),%edx
 80497cd:	66 83 fa 17          	cmp    $0x17,%dx
 80497d1:	77 13                	ja     80497e6 <rsi_ble_decode_rsp+0x2f>
				{
				   printf("Received response type: %s, status:%02x\n", ble_commands_str[rsp_type - RSI_BLE_RSP_ADVERTISE], status);
 80497d3:	51                   	push   %ecx
 80497d4:	50                   	push   %eax
 80497d5:	0f b7 c6             	movzwl %si,%eax
 80497d8:	ff 34 85 fc c3 04 08 	pushl  0x804c3fc(,%eax,4)
 80497df:	68 a8 a7 04 08       	push   $0x804a7a8
 80497e4:	eb 1d                	jmp    8049803 <rsi_ble_decode_rsp+0x4c>
				}
				else if ( (rsp_type >= RSI_BLE_EVENT_ADVERTISE_REPORT) && (rsp_type <= RSI_BLE_EVENT_PXPR_LINK_IS_LOST ) )
 80497e6:	8d 96 f2 ea ff ff    	lea    -0x150e(%esi),%edx
 80497ec:	66 83 fa 14          	cmp    $0x14,%dx
 80497f0:	77 19                	ja     804980b <rsi_ble_decode_rsp+0x54>
				{
				   printf("Received event type: %s, status:%02x\n", ble_events_str[rsp_type - RSI_BLE_EVENT_ADVERTISE_REPORT], status);
 80497f2:	52                   	push   %edx
 80497f3:	50                   	push   %eax
 80497f4:	0f b7 c6             	movzwl %si,%eax
 80497f7:	ff 34 85 48 71 04 08 	pushl  0x8047148(,%eax,4)
 80497fe:	68 d1 a7 04 08       	push   $0x804a7d1
 8049803:	e8 f8 ee ff ff       	call   8048700 <printf@plt>
 8049808:	83 c4 10             	add    $0x10,%esp
				}

				switch (rsp_type)
 804980b:	66 81 fe 84 00       	cmp    $0x84,%si
 8049810:	0f 84 41 02 00 00    	je     8049a57 <rsi_ble_decode_rsp+0x2a0>
 8049816:	77 6a                	ja     8049882 <rsi_ble_decode_rsp+0xcb>
 8049818:	66 83 fe 7e          	cmp    $0x7e,%si
 804981c:	77 23                	ja     8049841 <rsi_ble_decode_rsp+0x8a>
 804981e:	66 83 fe 7a          	cmp    $0x7a,%si
 8049822:	0f 83 91 03 00 00    	jae    8049bb9 <rsi_ble_decode_rsp+0x402>
 8049828:	66 83 fe 75          	cmp    $0x75,%si
 804982c:	0f 82 74 03 00 00    	jb     8049ba6 <rsi_ble_decode_rsp+0x3ef>
 8049832:	66 83 fe 78          	cmp    $0x78,%si
 8049836:	0f 86 7d 03 00 00    	jbe    8049bb9 <rsi_ble_decode_rsp+0x402>
 804983c:	e9 a5 00 00 00       	jmp    80498e6 <rsi_ble_decode_rsp+0x12f>
 8049841:	66 81 fe 81 00       	cmp    $0x81,%si
 8049846:	0f 84 f6 00 00 00    	je     8049942 <rsi_ble_decode_rsp+0x18b>
 804984c:	77 19                	ja     8049867 <rsi_ble_decode_rsp+0xb0>
 804984e:	66 83 fe 7f          	cmp    $0x7f,%si
 8049852:	0f 84 a0 00 00 00    	je     80498f8 <rsi_ble_decode_rsp+0x141>
 8049858:	66 83 c6 80          	add    $0xff80,%si
 804985c:	0f 85 44 03 00 00    	jne    8049ba6 <rsi_ble_decode_rsp+0x3ef>
 8049862:	e9 cc 00 00 00       	jmp    8049933 <rsi_ble_decode_rsp+0x17c>
 8049867:	66 81 fe 82 00       	cmp    $0x82,%si
 804986c:	0f 84 53 01 00 00    	je     80499c5 <rsi_ble_decode_rsp+0x20e>
 8049872:	66 81 fe 83 00       	cmp    $0x83,%si
 8049877:	0f 85 29 03 00 00    	jne    8049ba6 <rsi_ble_decode_rsp+0x3ef>
 804987d:	e9 7e 01 00 00       	jmp    8049a00 <rsi_ble_decode_rsp+0x249>
 8049882:	66 81 fe 8c 00       	cmp    $0x8c,%si
 8049887:	77 21                	ja     80498aa <rsi_ble_decode_rsp+0xf3>
 8049889:	66 81 fe 88 00       	cmp    $0x88,%si
 804988e:	0f 83 25 03 00 00    	jae    8049bb9 <rsi_ble_decode_rsp+0x402>
 8049894:	66 81 fe 86 00       	cmp    $0x86,%si
 8049899:	0f 84 4d 02 00 00    	je     8049aec <rsi_ble_decode_rsp+0x335>
 804989f:	0f 87 90 02 00 00    	ja     8049b35 <rsi_ble_decode_rsp+0x37e>
 80498a5:	e9 f9 01 00 00       	jmp    8049aa3 <rsi_ble_decode_rsp+0x2ec>
 80498aa:	66 81 fe 20 15       	cmp    $0x1520,%si
 80498af:	0f 84 c9 02 00 00    	je     8049b7e <rsi_ble_decode_rsp+0x3c7>
 80498b5:	77 14                	ja     80498cb <rsi_ble_decode_rsp+0x114>
 80498b7:	66 81 ee 0e 15       	sub    $0x150e,%si
 80498bc:	66 83 fe 04          	cmp    $0x4,%si
 80498c0:	0f 87 e0 02 00 00    	ja     8049ba6 <rsi_ble_decode_rsp+0x3ef>
 80498c6:	e9 ee 02 00 00       	jmp    8049bb9 <rsi_ble_decode_rsp+0x402>
 80498cb:	66 81 fe 21 15       	cmp    $0x1521,%si
 80498d0:	0f 84 c1 02 00 00    	je     8049b97 <rsi_ble_decode_rsp+0x3e0>
 80498d6:	66 81 fe 22 15       	cmp    $0x1522,%si
 80498db:	0f 85 c5 02 00 00    	jne    8049ba6 <rsi_ble_decode_rsp+0x3ef>
 80498e1:	e9 d3 02 00 00       	jmp    8049bb9 <rsi_ble_decode_rsp+0x402>
								case RSI_BLE_RSP_DISCONNECT:
												break;
								case RSI_BLE_RSP_QUERY_DEVICE_STATE:
												{
																RSI_BLE_RESP_QUERY_DEVICE_STATE   *uQryDevState = rsp;
																printf("Device state :%02x\n",uQryDevState->DeviceState);
 80498e6:	0f b6 03             	movzbl (%ebx),%eax
 80498e9:	c7 45 08 f7 a7 04 08 	movl   $0x804a7f7,0x8(%ebp)
 80498f0:	89 45 0c             	mov    %eax,0xc(%ebp)
 80498f3:	e9 93 02 00 00       	jmp    8049b8b <rsi_ble_decode_rsp+0x3d4>
								case RSI_BLE_RSP_SMP_PASSKEY                  :
												break;
								case RSI_BLE_RSP_QUERY_PROFILES_LIST          :
												{
																RSI_BLE_RESP_QUERY_PROFILES_LIST   *uQryProfList = rsp;
																printf("Number of profiles: %d\n", uQryProfList->NumberOfProfiles);
 80498f8:	50                   	push   %eax
																for (ii = 0 ; ii < uQryProfList->NumberOfProfiles; ii++)
 80498f9:	31 f6                	xor    %esi,%esi
								case RSI_BLE_RSP_SMP_PASSKEY                  :
												break;
								case RSI_BLE_RSP_QUERY_PROFILES_LIST          :
												{
																RSI_BLE_RESP_QUERY_PROFILES_LIST   *uQryProfList = rsp;
																printf("Number of profiles: %d\n", uQryProfList->NumberOfProfiles);
 80498fb:	50                   	push   %eax
 80498fc:	0f b6 03             	movzbl (%ebx),%eax
 80498ff:	50                   	push   %eax
 8049900:	68 0b a8 04 08       	push   $0x804a80b
 8049905:	e8 f6 ed ff ff       	call   8048700 <printf@plt>
																for (ii = 0 ; ii < uQryProfList->NumberOfProfiles; ii++)
 804990a:	83 c4 10             	add    $0x10,%esp
 804990d:	eb 17                	jmp    8049926 <rsi_ble_decode_rsp+0x16f>
																{
																				print_profile_descriptor(&uQryProfList->ProfileDescriptor[ii]);
 804990f:	0f b7 c6             	movzwl %si,%eax
 8049912:	83 ec 0c             	sub    $0xc,%esp
 8049915:	6b c0 18             	imul   $0x18,%eax,%eax
												break;
								case RSI_BLE_RSP_QUERY_PROFILES_LIST          :
												{
																RSI_BLE_RESP_QUERY_PROFILES_LIST   *uQryProfList = rsp;
																printf("Number of profiles: %d\n", uQryProfList->NumberOfProfiles);
																for (ii = 0 ; ii < uQryProfList->NumberOfProfiles; ii++)
 8049918:	46                   	inc    %esi
																{
																				print_profile_descriptor(&uQryProfList->ProfileDescriptor[ii]);
 8049919:	8d 44 03 01          	lea    0x1(%ebx,%eax,1),%eax
 804991d:	50                   	push   %eax
 804991e:	e8 fc fd ff ff       	call   804971f <print_profile_descriptor>
												break;
								case RSI_BLE_RSP_QUERY_PROFILES_LIST          :
												{
																RSI_BLE_RESP_QUERY_PROFILES_LIST   *uQryProfList = rsp;
																printf("Number of profiles: %d\n", uQryProfList->NumberOfProfiles);
																for (ii = 0 ; ii < uQryProfList->NumberOfProfiles; ii++)
 8049923:	83 c4 10             	add    $0x10,%esp
 8049926:	0f b6 03             	movzbl (%ebx),%eax
 8049929:	66 39 c6             	cmp    %ax,%si
 804992c:	72 e1                	jb     804990f <rsi_ble_decode_rsp+0x158>
 804992e:	e9 86 02 00 00       	jmp    8049bb9 <rsi_ble_decode_rsp+0x402>
												}
												break;
								case RSI_BLE_RSP_QUERY_PROFILE                :
												{
																RSI_BLE_RESP_QUERY_PROFILE_DESCRIPTOR   *uQryProf = rsp;
																print_profile_descriptor(&uQryProf->ProfileDescriptor);
 8049933:	89 5d 08             	mov    %ebx,0x8(%ebp)
                case  RSI_BLE_EVENT_PXPR_LINK_IS_LOST   :
												break;
								default:
												printf("Wrong response type \n");
				}
}
 8049936:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8049939:	5b                   	pop    %ebx
 804993a:	5e                   	pop    %esi
 804993b:	5f                   	pop    %edi
 804993c:	5d                   	pop    %ebp
												}
												break;
								case RSI_BLE_RSP_QUERY_PROFILE                :
												{
																RSI_BLE_RESP_QUERY_PROFILE_DESCRIPTOR   *uQryProf = rsp;
																print_profile_descriptor(&uQryProf->ProfileDescriptor);
 804993d:	e9 dd fd ff ff       	jmp    804971f <print_profile_descriptor>
												break;
								case RSI_BLE_RSP_QUERY_CHARACTERISTIC_SERVICES:
												{
																RSI_BLE_RESP_QUERY_CHARACTERISTIC_SERVICES  *uQryCharServ = rsp;

																printf("Number of characteristic_services %d\n",uQryCharServ->NumberOfCharServices);
 8049942:	50                   	push   %eax

																printf("Characteristic services:\n");
																for (ii = 0; ii < uQryCharServ->NumberOfCharServices; ii++)
 8049943:	31 f6                	xor    %esi,%esi
												break;
								case RSI_BLE_RSP_QUERY_CHARACTERISTIC_SERVICES:
												{
																RSI_BLE_RESP_QUERY_CHARACTERISTIC_SERVICES  *uQryCharServ = rsp;

																printf("Number of characteristic_services %d\n",uQryCharServ->NumberOfCharServices);
 8049945:	50                   	push   %eax
 8049946:	0f b6 03             	movzbl (%ebx),%eax
 8049949:	50                   	push   %eax
 804994a:	68 23 a8 04 08       	push   $0x804a823
 804994f:	e8 ac ed ff ff       	call   8048700 <printf@plt>

																printf("Characteristic services:\n");
 8049954:	c7 04 24 49 a8 04 08 	movl   $0x804a849,(%esp)
 804995b:	e8 30 ee ff ff       	call   8048790 <puts@plt>
																for (ii = 0; ii < uQryCharServ->NumberOfCharServices; ii++)
 8049960:	83 c4 10             	add    $0x10,%esp
 8049963:	eb 53                	jmp    80499b8 <rsi_ble_decode_rsp+0x201>
																{
																				printf("Handle: %02x\n",*(UINT16*)uQryCharServ->CharacteristicService[ii].Handle);
 8049965:	0f b7 fe             	movzwl %si,%edi
																RSI_BLE_RESP_QUERY_CHARACTERISTIC_SERVICES  *uQryCharServ = rsp;

																printf("Number of characteristic_services %d\n",uQryCharServ->NumberOfCharServices);

																printf("Characteristic services:\n");
																for (ii = 0; ii < uQryCharServ->NumberOfCharServices; ii++)
 8049968:	46                   	inc    %esi
																{
																				printf("Handle: %02x\n",*(UINT16*)uQryCharServ->CharacteristicService[ii].Handle);
 8049969:	6b ff 19             	imul   $0x19,%edi,%edi
 804996c:	50                   	push   %eax
 804996d:	50                   	push   %eax
 804996e:	0f b7 44 3b 01       	movzwl 0x1(%ebx,%edi,1),%eax
 8049973:	50                   	push   %eax
 8049974:	68 80 a8 04 08       	push   $0x804a880
 8049979:	e8 82 ed ff ff       	call   8048700 <printf@plt>
																				printf("CharacterProperty: %02x\n",uQryCharServ->CharacteristicService[ii].CharacterProperty);
 804997e:	58                   	pop    %eax
 804997f:	5a                   	pop    %edx
 8049980:	8d 14 3b             	lea    (%ebx,%edi,1),%edx
 8049983:	0f b6 42 03          	movzbl 0x3(%edx),%eax
 8049987:	89 55 e4             	mov    %edx,-0x1c(%ebp)
 804998a:	50                   	push   %eax
 804998b:	68 62 a8 04 08       	push   $0x804a862
 8049990:	e8 6b ed ff ff       	call   8048700 <printf@plt>
																				printf("Char Handle: %02x\n", *(UINT16*)uQryCharServ->CharacteristicService[ii].CharacterHandle);
 8049995:	59                   	pop    %ecx
 8049996:	58                   	pop    %eax
 8049997:	0f b7 44 3b 04       	movzwl 0x4(%ebx,%edi,1),%eax
 804999c:	50                   	push   %eax
 804999d:	68 7b a8 04 08       	push   $0x804a87b
 80499a2:	e8 59 ed ff ff       	call   8048700 <printf@plt>
																				print_uuid(&uQryCharServ->CharacteristicService[ii].CharacterUUID);
 80499a7:	8b 55 e4             	mov    -0x1c(%ebp),%edx
 80499aa:	83 c2 06             	add    $0x6,%edx
 80499ad:	89 14 24             	mov    %edx,(%esp)
 80499b0:	e8 17 fd ff ff       	call   80496cc <print_uuid>
																RSI_BLE_RESP_QUERY_CHARACTERISTIC_SERVICES  *uQryCharServ = rsp;

																printf("Number of characteristic_services %d\n",uQryCharServ->NumberOfCharServices);

																printf("Characteristic services:\n");
																for (ii = 0; ii < uQryCharServ->NumberOfCharServices; ii++)
 80499b5:	83 c4 10             	add    $0x10,%esp
 80499b8:	0f b6 03             	movzbl (%ebx),%eax
 80499bb:	66 39 c6             	cmp    %ax,%si
 80499be:	72 a5                	jb     8049965 <rsi_ble_decode_rsp+0x1ae>
 80499c0:	e9 f4 01 00 00       	jmp    8049bb9 <rsi_ble_decode_rsp+0x402>
												}
												break;
								case RSI_BLE_RSP_QUERY_INCLUDE_SERVICES       :
												{
																RSI_BLE_RESP_QUERY_INCLUDE_SERVICE    *uQryIncServ = rsp;
																printf("NumberOfIncludeServices:%d\n",uQryIncServ->NumberOfIncludeServices);
 80499c5:	50                   	push   %eax
																for (ii = 0; ii < uQryIncServ->NumberOfIncludeServices; ii++)
 80499c6:	31 f6                	xor    %esi,%esi
												}
												break;
								case RSI_BLE_RSP_QUERY_INCLUDE_SERVICES       :
												{
																RSI_BLE_RESP_QUERY_INCLUDE_SERVICE    *uQryIncServ = rsp;
																printf("NumberOfIncludeServices:%d\n",uQryIncServ->NumberOfIncludeServices);
 80499c8:	50                   	push   %eax
 80499c9:	0f b6 03             	movzbl (%ebx),%eax
 80499cc:	50                   	push   %eax
 80499cd:	68 8e a8 04 08       	push   $0x804a88e
 80499d2:	e8 29 ed ff ff       	call   8048700 <printf@plt>
																for (ii = 0; ii < uQryIncServ->NumberOfIncludeServices; ii++)
 80499d7:	83 c4 10             	add    $0x10,%esp
 80499da:	eb 17                	jmp    80499f3 <rsi_ble_decode_rsp+0x23c>
																{
																				print_servcie(&uQryIncServ->IncludeServices[ii]);
 80499dc:	0f b7 c6             	movzwl %si,%eax
 80499df:	83 ec 0c             	sub    $0xc,%esp
 80499e2:	6b c0 1a             	imul   $0x1a,%eax,%eax
												break;
								case RSI_BLE_RSP_QUERY_INCLUDE_SERVICES       :
												{
																RSI_BLE_RESP_QUERY_INCLUDE_SERVICE    *uQryIncServ = rsp;
																printf("NumberOfIncludeServices:%d\n",uQryIncServ->NumberOfIncludeServices);
																for (ii = 0; ii < uQryIncServ->NumberOfIncludeServices; ii++)
 80499e5:	46                   	inc    %esi
																{
																				print_servcie(&uQryIncServ->IncludeServices[ii]);
 80499e6:	8d 44 03 01          	lea    0x1(%ebx,%eax,1),%eax
 80499ea:	50                   	push   %eax
 80499eb:	e8 7b fd ff ff       	call   804976b <print_servcie>
												break;
								case RSI_BLE_RSP_QUERY_INCLUDE_SERVICES       :
												{
																RSI_BLE_RESP_QUERY_INCLUDE_SERVICE    *uQryIncServ = rsp;
																printf("NumberOfIncludeServices:%d\n",uQryIncServ->NumberOfIncludeServices);
																for (ii = 0; ii < uQryIncServ->NumberOfIncludeServices; ii++)
 80499f0:	83 c4 10             	add    $0x10,%esp
 80499f3:	0f b6 03             	movzbl (%ebx),%eax
 80499f6:	66 39 c6             	cmp    %ax,%si
 80499f9:	72 e1                	jb     80499dc <rsi_ble_decode_rsp+0x225>
 80499fb:	e9 b9 01 00 00       	jmp    8049bb9 <rsi_ble_decode_rsp+0x402>
												break;
								case RSI_BLE_RSP_READ_CHAR_VALUE_BY_UUID      :
												{
																RSI_BLE_RESP_READ_CHAR_VALUE_BY_UUID   *uQryCharVal = rsp;

																printf("NumberOfValues:%d\n", uQryCharVal->NumberOfValues);
 8049a00:	50                   	push   %eax
																printf("Value:\n");
																for (ii = 0; ii < uQryCharVal->NumberOfValues; ii++)
 8049a01:	31 f6                	xor    %esi,%esi
												break;
								case RSI_BLE_RSP_READ_CHAR_VALUE_BY_UUID      :
												{
																RSI_BLE_RESP_READ_CHAR_VALUE_BY_UUID   *uQryCharVal = rsp;

																printf("NumberOfValues:%d\n", uQryCharVal->NumberOfValues);
 8049a03:	50                   	push   %eax
 8049a04:	0f b6 03             	movzbl (%ebx),%eax
 8049a07:	50                   	push   %eax
 8049a08:	68 aa a8 04 08       	push   $0x804a8aa
 8049a0d:	e8 ee ec ff ff       	call   8048700 <printf@plt>
																printf("Value:\n");
 8049a12:	c7 04 24 ec a8 04 08 	movl   $0x804a8ec,(%esp)
 8049a19:	e8 72 ed ff ff       	call   8048790 <puts@plt>
																for (ii = 0; ii < uQryCharVal->NumberOfValues; ii++)
 8049a1e:	83 c4 10             	add    $0x10,%esp
 8049a21:	eb 19                	jmp    8049a3c <rsi_ble_decode_rsp+0x285>
																{
																				printf("%02x", uQryCharVal->CharacterValue[ii]);
 8049a23:	0f b7 c6             	movzwl %si,%eax
												{
																RSI_BLE_RESP_READ_CHAR_VALUE_BY_UUID   *uQryCharVal = rsp;

																printf("NumberOfValues:%d\n", uQryCharVal->NumberOfValues);
																printf("Value:\n");
																for (ii = 0; ii < uQryCharVal->NumberOfValues; ii++)
 8049a26:	46                   	inc    %esi
																{
																				printf("%02x", uQryCharVal->CharacterValue[ii]);
 8049a27:	57                   	push   %edi
 8049a28:	57                   	push   %edi
 8049a29:	0f b6 44 03 01       	movzbl 0x1(%ebx,%eax,1),%eax
 8049a2e:	50                   	push   %eax
 8049a2f:	68 a3 a7 04 08       	push   $0x804a7a3
 8049a34:	e8 c7 ec ff ff       	call   8048700 <printf@plt>
												{
																RSI_BLE_RESP_READ_CHAR_VALUE_BY_UUID   *uQryCharVal = rsp;

																printf("NumberOfValues:%d\n", uQryCharVal->NumberOfValues);
																printf("Value:\n");
																for (ii = 0; ii < uQryCharVal->NumberOfValues; ii++)
 8049a39:	83 c4 10             	add    $0x10,%esp
 8049a3c:	0f b6 03             	movzbl (%ebx),%eax
 8049a3f:	66 39 c6             	cmp    %ax,%si
 8049a42:	72 df                	jb     8049a23 <rsi_ble_decode_rsp+0x26c>
																{
																				printf("%02x", uQryCharVal->CharacterValue[ii]);
																}
																printf("\n");
 8049a44:	c7 45 08 0a 00 00 00 	movl   $0xa,0x8(%ebp)
                case  RSI_BLE_EVENT_PXPR_LINK_IS_LOST   :
												break;
								default:
												printf("Wrong response type \n");
				}
}
 8049a4b:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8049a4e:	5b                   	pop    %ebx
 8049a4f:	5e                   	pop    %esi
 8049a50:	5f                   	pop    %edi
 8049a51:	5d                   	pop    %ebp
																printf("Value:\n");
																for (ii = 0; ii < uQryCharVal->NumberOfValues; ii++)
																{
																				printf("%02x", uQryCharVal->CharacterValue[ii]);
																}
																printf("\n");
 8049a52:	e9 89 ed ff ff       	jmp    80487e0 <putchar@plt>
												}
												break;
								case RSI_BLE_RSP_QUERY_ATT_DESC               :
												{
																RSI_BLE_RESP_QUERY_ATT_DESC   *uQryDescList = rsp;
																printf("NumberOfAttributes %d\n",uQryDescList->NumberOfAttributes);
 8049a57:	56                   	push   %esi
 8049a58:	56                   	push   %esi
 8049a59:	0f b6 03             	movzbl (%ebx),%eax
																for (ii = 0; ii < uQryDescList->NumberOfAttributes; ii++)
 8049a5c:	31 f6                	xor    %esi,%esi
												}
												break;
								case RSI_BLE_RSP_QUERY_ATT_DESC               :
												{
																RSI_BLE_RESP_QUERY_ATT_DESC   *uQryDescList = rsp;
																printf("NumberOfAttributes %d\n",uQryDescList->NumberOfAttributes);
 8049a5e:	50                   	push   %eax
 8049a5f:	68 bd a8 04 08       	push   $0x804a8bd
 8049a64:	e8 97 ec ff ff       	call   8048700 <printf@plt>
																for (ii = 0; ii < uQryDescList->NumberOfAttributes; ii++)
 8049a69:	83 c4 10             	add    $0x10,%esp
 8049a6c:	eb 28                	jmp    8049a96 <rsi_ble_decode_rsp+0x2df>
																{
																				printf("Handle %02x\n",*(UINT16*)uQryDescList->AttributeDescriptor[ii].Handle);
 8049a6e:	0f b7 fe             	movzwl %si,%edi
												break;
								case RSI_BLE_RSP_QUERY_ATT_DESC               :
												{
																RSI_BLE_RESP_QUERY_ATT_DESC   *uQryDescList = rsp;
																printf("NumberOfAttributes %d\n",uQryDescList->NumberOfAttributes);
																for (ii = 0; ii < uQryDescList->NumberOfAttributes; ii++)
 8049a71:	46                   	inc    %esi
																{
																				printf("Handle %02x\n",*(UINT16*)uQryDescList->AttributeDescriptor[ii].Handle);
 8049a72:	6b ff 16             	imul   $0x16,%edi,%edi
 8049a75:	51                   	push   %ecx
 8049a76:	51                   	push   %ecx
 8049a77:	0f b7 44 3b 01       	movzwl 0x1(%ebx,%edi,1),%eax
 8049a7c:	50                   	push   %eax
 8049a7d:	68 d4 a8 04 08       	push   $0x804a8d4
 8049a82:	e8 79 ec ff ff       	call   8048700 <printf@plt>
																				print_uuid(&uQryDescList->AttributeDescriptor[ii].AttributeTypeUUID);
 8049a87:	8d 44 3b 03          	lea    0x3(%ebx,%edi,1),%eax
 8049a8b:	89 04 24             	mov    %eax,(%esp)
 8049a8e:	e8 39 fc ff ff       	call   80496cc <print_uuid>
												break;
								case RSI_BLE_RSP_QUERY_ATT_DESC               :
												{
																RSI_BLE_RESP_QUERY_ATT_DESC   *uQryDescList = rsp;
																printf("NumberOfAttributes %d\n",uQryDescList->NumberOfAttributes);
																for (ii = 0; ii < uQryDescList->NumberOfAttributes; ii++)
 8049a93:	83 c4 10             	add    $0x10,%esp
 8049a96:	0f b6 03             	movzbl (%ebx),%eax
 8049a99:	66 39 c6             	cmp    %ax,%si
 8049a9c:	72 d0                	jb     8049a6e <rsi_ble_decode_rsp+0x2b7>
 8049a9e:	e9 16 01 00 00       	jmp    8049bb9 <rsi_ble_decode_rsp+0x402>
												}
												break;
								case RSI_BLE_RSP_QUERY_ATT_VALUE              :
												{
																RSI_BLE_RESP_QUERY_ATT_VALUE   *uQryAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryAttVal->NumberOfValues);
 8049aa3:	52                   	push   %edx
																printf("Value:\n");
																for (ii = 0; ii < uQryAttVal->NumberOfValues; ii++)
 8049aa4:	31 f6                	xor    %esi,%esi
												}
												break;
								case RSI_BLE_RSP_QUERY_ATT_VALUE              :
												{
																RSI_BLE_RESP_QUERY_ATT_VALUE   *uQryAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryAttVal->NumberOfValues);
 8049aa6:	52                   	push   %edx
 8049aa7:	0f b6 03             	movzbl (%ebx),%eax
 8049aaa:	50                   	push   %eax
 8049aab:	68 aa a8 04 08       	push   $0x804a8aa
 8049ab0:	e8 4b ec ff ff       	call   8048700 <printf@plt>
																printf("Value:\n");
 8049ab5:	c7 04 24 ec a8 04 08 	movl   $0x804a8ec,(%esp)
 8049abc:	e8 cf ec ff ff       	call   8048790 <puts@plt>
																for (ii = 0; ii < uQryAttVal->NumberOfValues; ii++)
 8049ac1:	83 c4 10             	add    $0x10,%esp
 8049ac4:	eb 19                	jmp    8049adf <rsi_ble_decode_rsp+0x328>
																{
																				printf("%02x ", uQryAttVal->AttributeValues[ii]);
 8049ac6:	50                   	push   %eax
 8049ac7:	50                   	push   %eax
 8049ac8:	0f b7 c6             	movzwl %si,%eax
 8049acb:	0f b6 44 03 01       	movzbl 0x1(%ebx,%eax,1),%eax
								case RSI_BLE_RSP_QUERY_ATT_VALUE              :
												{
																RSI_BLE_RESP_QUERY_ATT_VALUE   *uQryAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryAttVal->NumberOfValues);
																printf("Value:\n");
																for (ii = 0; ii < uQryAttVal->NumberOfValues; ii++)
 8049ad0:	46                   	inc    %esi
																{
																				printf("%02x ", uQryAttVal->AttributeValues[ii]);
 8049ad1:	50                   	push   %eax
 8049ad2:	68 e1 a8 04 08       	push   $0x804a8e1
 8049ad7:	e8 24 ec ff ff       	call   8048700 <printf@plt>
								case RSI_BLE_RSP_QUERY_ATT_VALUE              :
												{
																RSI_BLE_RESP_QUERY_ATT_VALUE   *uQryAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryAttVal->NumberOfValues);
																printf("Value:\n");
																for (ii = 0; ii < uQryAttVal->NumberOfValues; ii++)
 8049adc:	83 c4 10             	add    $0x10,%esp
 8049adf:	0f b6 03             	movzbl (%ebx),%eax
 8049ae2:	66 39 c6             	cmp    %ax,%si
 8049ae5:	72 df                	jb     8049ac6 <rsi_ble_decode_rsp+0x30f>
 8049ae7:	e9 58 ff ff ff       	jmp    8049a44 <rsi_ble_decode_rsp+0x28d>
												}
												break;
								case RSI_BLE_RSP_QUERY_MULTIPLE_ATT_VALUES    :
												{
																RSI_BLE_RESP_QUERY_MULTIPLE_ATT_VALUES  *uQryAttVals = rsp;
																printf("NumberOfValues:%d\n", uQryAttVals->NumberOfValues);
 8049aec:	50                   	push   %eax
																printf("Value:\n");
																for (ii = 0; ii < uQryAttVals->NumberOfValues; ii++)
 8049aed:	31 f6                	xor    %esi,%esi
												}
												break;
								case RSI_BLE_RSP_QUERY_MULTIPLE_ATT_VALUES    :
												{
																RSI_BLE_RESP_QUERY_MULTIPLE_ATT_VALUES  *uQryAttVals = rsp;
																printf("NumberOfValues:%d\n", uQryAttVals->NumberOfValues);
 8049aef:	50                   	push   %eax
 8049af0:	0f b6 03             	movzbl (%ebx),%eax
 8049af3:	50                   	push   %eax
 8049af4:	68 aa a8 04 08       	push   $0x804a8aa
 8049af9:	e8 02 ec ff ff       	call   8048700 <printf@plt>
																printf("Value:\n");
 8049afe:	c7 04 24 ec a8 04 08 	movl   $0x804a8ec,(%esp)
 8049b05:	e8 86 ec ff ff       	call   8048790 <puts@plt>
																for (ii = 0; ii < uQryAttVals->NumberOfValues; ii++)
 8049b0a:	83 c4 10             	add    $0x10,%esp
 8049b0d:	eb 19                	jmp    8049b28 <rsi_ble_decode_rsp+0x371>
																{
																				printf("%02x ", uQryAttVals->AttributeValues[ii]);
 8049b0f:	50                   	push   %eax
 8049b10:	50                   	push   %eax
 8049b11:	0f b7 c6             	movzwl %si,%eax
 8049b14:	0f b6 44 03 01       	movzbl 0x1(%ebx,%eax,1),%eax
								case RSI_BLE_RSP_QUERY_MULTIPLE_ATT_VALUES    :
												{
																RSI_BLE_RESP_QUERY_MULTIPLE_ATT_VALUES  *uQryAttVals = rsp;
																printf("NumberOfValues:%d\n", uQryAttVals->NumberOfValues);
																printf("Value:\n");
																for (ii = 0; ii < uQryAttVals->NumberOfValues; ii++)
 8049b19:	46                   	inc    %esi
																{
																				printf("%02x ", uQryAttVals->AttributeValues[ii]);
 8049b1a:	50                   	push   %eax
 8049b1b:	68 e1 a8 04 08       	push   $0x804a8e1
 8049b20:	e8 db eb ff ff       	call   8048700 <printf@plt>
								case RSI_BLE_RSP_QUERY_MULTIPLE_ATT_VALUES    :
												{
																RSI_BLE_RESP_QUERY_MULTIPLE_ATT_VALUES  *uQryAttVals = rsp;
																printf("NumberOfValues:%d\n", uQryAttVals->NumberOfValues);
																printf("Value:\n");
																for (ii = 0; ii < uQryAttVals->NumberOfValues; ii++)
 8049b25:	83 c4 10             	add    $0x10,%esp
 8049b28:	0f b6 03             	movzbl (%ebx),%eax
 8049b2b:	66 39 c6             	cmp    %ax,%si
 8049b2e:	72 df                	jb     8049b0f <rsi_ble_decode_rsp+0x358>
 8049b30:	e9 0f ff ff ff       	jmp    8049a44 <rsi_ble_decode_rsp+0x28d>
												}
												break;
								case RSI_BLE_RSP_QUERY_LONG_ATT_VALUE         :
												{
																RSI_BLE_RESP_QUERY_LONG_ATT_VALUE   *uQryLongAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryLongAttVal->NumberOfValues);
 8049b35:	50                   	push   %eax
																printf("Long Value:\n");
																for (ii = 0; ii < uQryLongAttVal->NumberOfValues; ii++)
 8049b36:	31 f6                	xor    %esi,%esi
												}
												break;
								case RSI_BLE_RSP_QUERY_LONG_ATT_VALUE         :
												{
																RSI_BLE_RESP_QUERY_LONG_ATT_VALUE   *uQryLongAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryLongAttVal->NumberOfValues);
 8049b38:	50                   	push   %eax
 8049b39:	0f b6 03             	movzbl (%ebx),%eax
 8049b3c:	50                   	push   %eax
 8049b3d:	68 aa a8 04 08       	push   $0x804a8aa
 8049b42:	e8 b9 eb ff ff       	call   8048700 <printf@plt>
																printf("Long Value:\n");
 8049b47:	c7 04 24 e7 a8 04 08 	movl   $0x804a8e7,(%esp)
 8049b4e:	e8 3d ec ff ff       	call   8048790 <puts@plt>
																for (ii = 0; ii < uQryLongAttVal->NumberOfValues; ii++)
 8049b53:	83 c4 10             	add    $0x10,%esp
 8049b56:	eb 19                	jmp    8049b71 <rsi_ble_decode_rsp+0x3ba>
																{
																				printf("%02x ", uQryLongAttVal->LongAttValue[ii]);
 8049b58:	50                   	push   %eax
 8049b59:	50                   	push   %eax
 8049b5a:	0f b7 c6             	movzwl %si,%eax
 8049b5d:	0f b6 44 03 01       	movzbl 0x1(%ebx,%eax,1),%eax
								case RSI_BLE_RSP_QUERY_LONG_ATT_VALUE         :
												{
																RSI_BLE_RESP_QUERY_LONG_ATT_VALUE   *uQryLongAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryLongAttVal->NumberOfValues);
																printf("Long Value:\n");
																for (ii = 0; ii < uQryLongAttVal->NumberOfValues; ii++)
 8049b62:	46                   	inc    %esi
																{
																				printf("%02x ", uQryLongAttVal->LongAttValue[ii]);
 8049b63:	50                   	push   %eax
 8049b64:	68 e1 a8 04 08       	push   $0x804a8e1
 8049b69:	e8 92 eb ff ff       	call   8048700 <printf@plt>
								case RSI_BLE_RSP_QUERY_LONG_ATT_VALUE         :
												{
																RSI_BLE_RESP_QUERY_LONG_ATT_VALUE   *uQryLongAttVal = rsp;
																printf("NumberOfValues:%d\n", uQryLongAttVal->NumberOfValues);
																printf("Long Value:\n");
																for (ii = 0; ii < uQryLongAttVal->NumberOfValues; ii++)
 8049b6e:	83 c4 10             	add    $0x10,%esp
 8049b71:	0f b6 03             	movzbl (%ebx),%eax
 8049b74:	66 39 c6             	cmp    %ax,%si
 8049b77:	72 df                	jb     8049b58 <rsi_ble_decode_rsp+0x3a1>
 8049b79:	e9 c6 fe ff ff       	jmp    8049a44 <rsi_ble_decode_rsp+0x28d>
												//RetVal = rsi_ble_smp_passkey(&rsi_bt_AppControlBlock.uBLEApiInitParams->uLeSmppasskey);
												break;
								case  RSI_BLE_EVENT_PXPR_LINK_LOSS_ALERT:
												{
                       	 	RSI_BLE_EVENT_PXP_LINKLOSS *uLinkLoss = rsp;
													printf("PXP Link loss alert: %d\n", uLinkLoss->LinkLossAlert);
 8049b7e:	0f b6 03             	movzbl (%ebx),%eax
 8049b81:	c7 45 08 f3 a8 04 08 	movl   $0x804a8f3,0x8(%ebp)
 8049b88:	89 45 0c             	mov    %eax,0xc(%ebp)
                case  RSI_BLE_EVENT_PXPR_LINK_IS_LOST   :
												break;
								default:
												printf("Wrong response type \n");
				}
}
 8049b8b:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8049b8e:	5b                   	pop    %ebx
 8049b8f:	5e                   	pop    %esi
 8049b90:	5f                   	pop    %edi
 8049b91:	5d                   	pop    %ebp
												//RetVal = rsi_ble_smp_passkey(&rsi_bt_AppControlBlock.uBLEApiInitParams->uLeSmppasskey);
												break;
								case  RSI_BLE_EVENT_PXPR_LINK_LOSS_ALERT:
												{
                       	 	RSI_BLE_EVENT_PXP_LINKLOSS *uLinkLoss = rsp;
													printf("PXP Link loss alert: %d\n", uLinkLoss->LinkLossAlert);
 8049b92:	e9 69 eb ff ff       	jmp    8048700 <printf@plt>
												}
												break;
                case  RSI_BLE_EVENT_PXPR_IMMEDIATE_ALERT:
												{
                        	RSI_BLE_EVENT_PXP_IMM_ALERT *uImmAlert = rsp;
													printf("PXP immeditate alert: %d\n", uImmAlert->ImmAlert);
 8049b97:	0f b6 03             	movzbl (%ebx),%eax
 8049b9a:	c7 45 08 0c a9 04 08 	movl   $0x804a90c,0x8(%ebp)
 8049ba1:	89 45 0c             	mov    %eax,0xc(%ebp)
 8049ba4:	eb e5                	jmp    8049b8b <rsi_ble_decode_rsp+0x3d4>
												}
												break;
                case  RSI_BLE_EVENT_PXPR_LINK_IS_LOST   :
												break;
								default:
												printf("Wrong response type \n");
 8049ba6:	c7 45 08 26 a9 04 08 	movl   $0x804a926,0x8(%ebp)
				}
}
 8049bad:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8049bb0:	5b                   	pop    %ebx
 8049bb1:	5e                   	pop    %esi
 8049bb2:	5f                   	pop    %edi
 8049bb3:	5d                   	pop    %ebp
												}
												break;
                case  RSI_BLE_EVENT_PXPR_LINK_IS_LOST   :
												break;
								default:
												printf("Wrong response type \n");
 8049bb4:	e9 d7 eb ff ff       	jmp    8048790 <puts@plt>
				}
}
 8049bb9:	8d 65 f4             	lea    -0xc(%ebp),%esp
 8049bbc:	5b                   	pop    %ebx
 8049bbd:	5e                   	pop    %esi
 8049bbe:	5f                   	pop    %edi
 8049bbf:	5d                   	pop    %ebp
 8049bc0:	c3                   	ret    
 8049bc1:	0f 1f 00             	nopl   (%eax)

08049bc4 <rsi_irq_start>:
 * @param[out]  none
 * @return              none
 * @description This HAL API should contain the code to initialize the register related to interrupts.
 */
void rsi_irq_start(void)
{
 8049bc4:	55                   	push   %ebp
 8049bc5:	89 e5                	mov    %esp,%ebp
}
 8049bc7:	5d                   	pop    %ebp
 8049bc8:	c3                   	ret    

08049bc9 <rsi_irq_disable>:
 * @param[out]  none
 * @return              none
 * @description This HAL API should contain the code to disable interrupts.
 */
void rsi_irq_disable(void)
{
 8049bc9:	55                   	push   %ebp
 8049bca:	89 e5                	mov    %esp,%ebp
}
 8049bcc:	5d                   	pop    %ebp
 8049bcd:	c3                   	ret    

08049bce <rsi_irq_enable>:
 * @param[out]  none
 * @return              none
 * @description This HAL API should contain the code to enable interrupts.
 */
void rsi_irq_enable(void)
{
 8049bce:	55                   	push   %ebp
 8049bcf:	89 e5                	mov    %esp,%ebp
}
 8049bd1:	5d                   	pop    %ebp
 8049bd2:	c3                   	ret    

08049bd3 <rsi_irq_clear_pending>:
 * @param[out]  none
 * @return              none
 * @description This HAL API should contain the code to clear the handled interrupts.
 */
void rsi_irq_clear_pending(void)
{
 8049bd3:	55                   	push   %ebp
 8049bd4:	89 e5                	mov    %esp,%ebp

}
 8049bd6:	5d                   	pop    %ebp
 8049bd7:	c3                   	ret    

08049bd8 <rsi_irq_status>:
 * @return                none
 * @description This API is used to check pending interrupts.
 */
uint8 rsi_irq_status(void)
{
  return rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0;
 8049bd8:	66 83 3d 9c c6 04 08 	cmpw   $0x0,0x804c69c
 8049bdf:	00 
 * @param[out]  uint8, interrupt status
 * @return                none
 * @description This API is used to check pending interrupts.
 */
uint8 rsi_irq_status(void)
{
 8049be0:	55                   	push   %ebp
 8049be1:	89 e5                	mov    %esp,%ebp
  return rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0;
 8049be3:	0f 95 c0             	setne  %al
}
 8049be6:	5d                   	pop    %ebp
 8049be7:	c3                   	ret    

08049be8 <rsi_bt_build_frame_descriptor>:
 * This API is used to build the frame descriptor for the BT packet which is supposed to be 
 * given to the firmware/module. 
 *
 */
void rsi_bt_build_frame_descriptor(RSI_BT_FRAME_DESC *uFrameDescFrame, UINT08 *Cmd)
{
 8049be8:	55                   	push   %ebp
 8049be9:	31 c9                	xor    %ecx,%ecx
 8049beb:	89 e5                	mov    %esp,%ebp
 8049bed:	8b 45 08             	mov    0x8(%ebp),%eax
 8049bf0:	8b 55 0c             	mov    0xc(%ebp),%edx
  UINT08        i;  
  for (i = 0; i < RSI_BT_FRAME_DESC_LEN; i++) 
  { 
    uFrameDescFrame->uFrmDscBuf[i] = 0x00; 
 8049bf3:	c6 04 08 00          	movb   $0x0,(%eax,%ecx,1)
 8049bf7:	41                   	inc    %ecx
 *
 */
void rsi_bt_build_frame_descriptor(RSI_BT_FRAME_DESC *uFrameDescFrame, UINT08 *Cmd)
{
  UINT08        i;  
  for (i = 0; i < RSI_BT_FRAME_DESC_LEN; i++) 
 8049bf8:	83 f9 10             	cmp    $0x10,%ecx
 8049bfb:	75 f6                	jne    8049bf3 <rsi_bt_build_frame_descriptor+0xb>
  
  /* Cmd0[0:7],Cmd1[0:3] together represent length of the payload for the frame command
   * Cmd1[4:7], indicates queue number 0000 - Management, 0001 - Data
   * Cmd2[0:8], Cmd3[0:7] together represent the Frame command type. 
   */
  uFrameDescFrame->uFrmDscBuf[0] = Cmd[0];      
 8049bfd:	8a 0a                	mov    (%edx),%cl
 8049bff:	88 08                	mov    %cl,(%eax)
  uFrameDescFrame->uFrmDscBuf[1] = (Cmd[1] | (2 << 12));
 8049c01:	8a 4a 01             	mov    0x1(%edx),%cl
 8049c04:	88 48 01             	mov    %cl,0x1(%eax)
  uFrameDescFrame->uFrmDscBuf[2] = Cmd[2];      
 8049c07:	8a 4a 02             	mov    0x2(%edx),%cl
 8049c0a:	88 48 02             	mov    %cl,0x2(%eax)
  uFrameDescFrame->uFrmDscBuf[3] = Cmd[3];      
 8049c0d:	8a 52 03             	mov    0x3(%edx),%dl
 8049c10:	88 50 03             	mov    %dl,0x3(%eax)

  return;
}
 8049c13:	5d                   	pop    %ebp
 8049c14:	c3                   	ret    
 8049c15:	0f 1f 00             	nopl   (%eax)

08049c18 <rsi_ble_advertise>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_advertise(RSI_BLE_CMD_ADVERTISE *uLEAdvertise)
{
 8049c18:	55                   	push   %ebp
 8049c19:	89 e5                	mov    %esp,%ebp
 8049c1b:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Advertise Mode Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEAdv, (UINT08 *)uLEAdvertise, sizeof(RSI_BLE_CMD_ADVERTISE));
 8049c1e:	6a 03                	push   $0x3
 8049c20:	ff 75 08             	pushl  0x8(%ebp)
 8049c23:	68 40 ad 04 08       	push   $0x804ad40
 8049c28:	e8 57 03 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049c2d:	c9                   	leave  
 8049c2e:	c3                   	ret    

08049c2f <rsi_ble_scan>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_scan(RSI_BLE_CMD_SCAN *uLEScan)
{
 8049c2f:	55                   	push   %ebp
 8049c30:	89 e5                	mov    %esp,%ebp
 8049c32:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nScan starts ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEScan, (UINT08 *)uLEScan, sizeof(RSI_BLE_CMD_SCAN));
 8049c35:	6a 03                	push   $0x3
 8049c37:	ff 75 08             	pushl  0x8(%ebp)
 8049c3a:	68 3c ad 04 08       	push   $0x804ad3c
 8049c3f:	e8 40 03 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049c44:	c9                   	leave  
 8049c45:	c3                   	ret    

08049c46 <rsi_ble_connect>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_connect(RSI_BLE_CMD_CONNECT *uLEConnect)
{
 8049c46:	55                   	push   %ebp
 8049c47:	89 e5                	mov    %esp,%ebp
 8049c49:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Connection start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEConn, (UINT08 *)uLEConnect, sizeof(RSI_BLE_CMD_CONNECT));
 8049c4c:	6a 07                	push   $0x7
 8049c4e:	ff 75 08             	pushl  0x8(%ebp)
 8049c51:	68 38 ad 04 08       	push   $0x804ad38
 8049c56:	e8 29 03 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049c5b:	c9                   	leave  
 8049c5c:	c3                   	ret    

08049c5d <rsi_ble_disconnect>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_disconnect(void)
{
 8049c5d:	55                   	push   %ebp
 8049c5e:	89 e5                	mov    %esp,%ebp
 8049c60:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nDisconnect start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEDisconn, NULL, 0);
 8049c63:	6a 00                	push   $0x0
 8049c65:	6a 00                	push   $0x0
 8049c67:	68 34 ad 04 08       	push   $0x804ad34
 8049c6c:	e8 13 03 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049c71:	c9                   	leave  
 8049c72:	c3                   	ret    

08049c73 <rsi_ble_query_device_state>:
 * This API is used to get local le device state.
 *
 * @section prerequisite 
 */
INT16 rsi_ble_query_device_state(void)
{
 8049c73:	55                   	push   %ebp
 8049c74:	89 e5                	mov    %esp,%ebp
 8049c76:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Device State start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryDevstate, NULL, 0);
 8049c79:	6a 00                	push   $0x0
 8049c7b:	6a 00                	push   $0x0
 8049c7d:	68 30 ad 04 08       	push   $0x804ad30
 8049c82:	e8 fd 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049c87:	c9                   	leave  
 8049c88:	c3                   	ret    

08049c89 <rsi_ble_update_hci_params>:
 * This API is used to .
 *
 * @section prerequisite 
 */
INT16 rsi_ble_update_hci_params(void)
{
 8049c89:	55                   	push   %ebp
 8049c8a:	89 e5                	mov    %esp,%ebp
 8049c8c:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nUpdate hci parameters start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdHciParams, NULL, 0);
 8049c8f:	6a 00                	push   $0x0
 8049c91:	6a 00                	push   $0x0
 8049c93:	68 2c ad 04 08       	push   $0x804ad2c
 8049c98:	e8 e7 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049c9d:	c9                   	leave  
 8049c9e:	c3                   	ret    

08049c9f <rsi_ble_start_encryption>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_start_encryption(void)
{
 8049c9f:	55                   	push   %ebp
 8049ca0:	89 e5                	mov    %esp,%ebp
 8049ca2:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nStart Encryption start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdStartEnc, NULL, 0);
 8049ca5:	6a 00                	push   $0x0
 8049ca7:	6a 00                	push   $0x0
 8049ca9:	68 28 ad 04 08       	push   $0x804ad28
 8049cae:	e8 d1 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049cb3:	c9                   	leave  
 8049cb4:	c3                   	ret    

08049cb5 <rsi_ble_smp_pair_request>:
 * This API is used to send the SMP pair request command to connected remote device.
 *
 * @section prerequisite 
 */
INT16 rsi_ble_smp_pair_request(RSI_BLE_CMD_SMP_PAIR_REQUEST *uSMPPairRequest)
{
 8049cb5:	55                   	push   %ebp
 8049cb6:	89 e5                	mov    %esp,%ebp
 8049cb8:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n SMP Pair Request start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSMPPairReq, (UINT08 *)uSMPPairRequest, sizeof(RSI_BLE_CMD_SMP_PAIR_REQUEST));
 8049cbb:	6a 01                	push   $0x1
 8049cbd:	ff 75 08             	pushl  0x8(%ebp)
 8049cc0:	68 24 ad 04 08       	push   $0x804ad24
 8049cc5:	e8 ba 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049cca:	c9                   	leave  
 8049ccb:	c3                   	ret    

08049ccc <rsi_ble_smp_response>:
 * This API is used to .
 *
 * @section prerequisite 
 */
INT16 rsi_ble_smp_response(RSI_BLE_CMD_SMP_RESPONSE *uSMPResponse)
{
 8049ccc:	55                   	push   %ebp
 8049ccd:	89 e5                	mov    %esp,%ebp
 8049ccf:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n SMP Response start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSMPResp, (UINT08 *)uSMPResponse, sizeof(RSI_BLE_CMD_SMP_RESPONSE));
 8049cd2:	6a 01                	push   $0x1
 8049cd4:	ff 75 08             	pushl  0x8(%ebp)
 8049cd7:	68 20 ad 04 08       	push   $0x804ad20
 8049cdc:	e8 a3 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049ce1:	c9                   	leave  
 8049ce2:	c3                   	ret    

08049ce3 <rsi_ble_smp_passkey>:
 * This API is used to .                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
 INT16 rsi_ble_smp_passkey(RSI_BLE_CMD_SMP_PASSKEY *uSMPPasskey)                                                                                                            													                                                              													      
{                                                                                                            													      
 8049ce3:	55                   	push   %ebp
 8049ce4:	89 e5                	mov    %esp,%ebp
 8049ce6:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n SMP passkey start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSMPPasskey, (UINT08 *)uSMPPasskey, sizeof(RSI_BLE_CMD_SMP_PASSKEY));													      
 8049ce9:	6a 04                	push   $0x4
 8049ceb:	ff 75 08             	pushl  0x8(%ebp)
 8049cee:	68 1c ad 04 08       	push   $0x804ad1c
 8049cf3:	e8 8c 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049cf8:	c9                   	leave  
 8049cf9:	c3                   	ret    
 8049cfa:	66 90                	xchg   %ax,%ax

08049cfc <rsi_bt_set_local_name>:
 *
 * @section prerequisite 
 */

INT16 rsi_bt_set_local_name(RSI_BT_CMD_SET_LOCAL_NAME *uSetLocalName)
{
 8049cfc:	55                   	push   %ebp
 8049cfd:	89 e5                	mov    %esp,%ebp
 8049cff:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Local Name Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetLocalName, (UINT08 *)uSetLocalName, sizeof(RSI_BT_CMD_SET_LOCAL_NAME));
 8049d02:	6a 33                	push   $0x33
 8049d04:	ff 75 08             	pushl  0x8(%ebp)
 8049d07:	68 5c ad 04 08       	push   $0x804ad5c
 8049d0c:	e8 73 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049d11:	c9                   	leave  
 8049d12:	c3                   	ret    

08049d13 <rsi_bt_query_local_name>:
 * @section prerequisite 
 * none
 */

INT16 rsi_bt_query_local_name(void)
{
 8049d13:	55                   	push   %ebp
 8049d14:	89 e5                	mov    %esp,%ebp
 8049d16:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Local Name Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLocalName, NULL, 0);
 8049d19:	6a 00                	push   $0x0
 8049d1b:	6a 00                	push   $0x0
 8049d1d:	68 58 ad 04 08       	push   $0x804ad58
 8049d22:	e8 5d 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049d27:	c9                   	leave  
 8049d28:	c3                   	ret    

08049d29 <rsi_bt_set_local_cod>:
 * This API is used to set the Class of the BT module.
 *
 * @section prerequisite 
 */
INT16 rsi_bt_set_local_cod(RSI_BT_CMD_SET_LOCAL_COD *uSetLocalCOD)
{
 8049d29:	55                   	push   %ebp
 8049d2a:	89 e5                	mov    %esp,%ebp
 8049d2c:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Local COD Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetLocalCOD, (UINT08 *)uSetLocalCOD, sizeof(RSI_BT_CMD_SET_LOCAL_COD));
 8049d2f:	6a 04                	push   $0x4
 8049d31:	ff 75 08             	pushl  0x8(%ebp)
 8049d34:	68 54 ad 04 08       	push   $0x804ad54
 8049d39:	e8 46 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049d3e:	c9                   	leave  
 8049d3f:	c3                   	ret    

08049d40 <rsi_bt_query_local_cod>:
 * none
 */


INT16 rsi_bt_query_local_cod(void)
{
 8049d40:	55                   	push   %ebp
 8049d41:	89 e5                	mov    %esp,%ebp
 8049d43:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Local Name Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLocalName, NULL, 0);
 8049d46:	6a 00                	push   $0x0
 8049d48:	6a 00                	push   $0x0
 8049d4a:	68 58 ad 04 08       	push   $0x804ad58
 8049d4f:	e8 30 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049d54:	c9                   	leave  
 8049d55:	c3                   	ret    

08049d56 <rsi_bt_query_rssi>:
 * @section prerequisite
 * none
 */

INT16 rsi_bt_query_rssi(RSI_BT_CMD_QUERY_RSSI *uQueryRSSI)
{
 8049d56:	55                   	push   %ebp
 8049d57:	89 e5                	mov    %esp,%ebp
 8049d59:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery RSSI Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryRSSI, (UINT08 *)uQueryRSSI, sizeof(RSI_BT_CMD_QUERY_RSSI));
 8049d5c:	6a 06                	push   $0x6
 8049d5e:	ff 75 08             	pushl  0x8(%ebp)
 8049d61:	68 4c ad 04 08       	push   $0x804ad4c
 8049d66:	e8 19 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049d6b:	c9                   	leave  
 8049d6c:	c3                   	ret    

08049d6d <rsi_bt_query_link_quality>:
 * @section prerequisite 
 *
 */

INT16 rsi_bt_query_link_quality(RSI_BT_CMD_QUERY_LINK_QUALITY *uQueryLinkQuality)
{
 8049d6d:	55                   	push   %ebp
 8049d6e:	89 e5                	mov    %esp,%ebp
 8049d70:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Link Quality Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLinkQuality, (UINT08 *)uQueryLinkQuality, sizeof(RSI_BT_CMD_QUERY_LINK_QUALITY));
 8049d73:	6a 06                	push   $0x6
 8049d75:	ff 75 08             	pushl  0x8(%ebp)
 8049d78:	68 48 ad 04 08       	push   $0x804ad48
 8049d7d:	e8 02 02 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049d82:	c9                   	leave  
 8049d83:	c3                   	ret    

08049d84 <rsi_bt_query_local_bd_address>:
 * @section prerequisite 
 * none
 */

INT16 rsi_bt_query_local_bd_address(void)
{
 8049d84:	55                   	push   %ebp
 8049d85:	89 e5                	mov    %esp,%ebp
 8049d87:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Local BD Address Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLocalBDAddr, NULL, 0);
 8049d8a:	6a 00                	push   $0x0
 8049d8c:	6a 00                	push   $0x0
 8049d8e:	68 44 ad 04 08       	push   $0x804ad44
 8049d93:	e8 ec 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049d98:	c9                   	leave  
 8049d99:	c3                   	ret    
 8049d9a:	66 90                	xchg   %ax,%ax

08049d9c <rsi_ble_query_profiles_list>:
 * @section prerequisite
 * This API must be used after connecting with the remote device.
 */

INT16 rsi_ble_query_profiles_list(void)
{
 8049d9c:	55                   	push   %ebp
 8049d9d:	89 e5                	mov    %esp,%ebp
 8049d9f:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery profile list Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryProfList, NULL, 0);
 8049da2:	6a 00                	push   $0x0
 8049da4:	6a 00                	push   $0x0
 8049da6:	68 18 ad 04 08       	push   $0x804ad18
 8049dab:	e8 d4 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049db0:	c9                   	leave  
 8049db1:	c3                   	ret    

08049db2 <rsi_ble_query_profile>:
 * @section prerequisite 
 * This API must be used after connecting with the remote device.
 */

INT16 rsi_ble_query_profile(RSI_BLE_CMD_QUERY_PROFILE *uGetProfile)
{
 8049db2:	55                   	push   %ebp
 8049db3:	89 e5                	mov    %esp,%ebp
 8049db5:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery profile descriptor starts ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryProfDesc, (UINT08 *)uGetProfile, sizeof(RSI_BLE_CMD_QUERY_PROFILE));
 8049db8:	6a 14                	push   $0x14
 8049dba:	ff 75 08             	pushl  0x8(%ebp)
 8049dbd:	68 14 ad 04 08       	push   $0x804ad14
 8049dc2:	e8 bd 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049dc7:	c9                   	leave  
 8049dc8:	c3                   	ret    

08049dc9 <rsi_ble_query_characteristic_services>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_query_characteristic_services(RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES *uGetCharacteristicServices)
{
 8049dc9:	55                   	push   %ebp
 8049dca:	89 e5                	mov    %esp,%ebp
 8049dcc:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Characterstic services start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryCharServ, (UINT08 *)uGetCharacteristicServices, sizeof(RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES));
 8049dcf:	6a 04                	push   $0x4
 8049dd1:	ff 75 08             	pushl  0x8(%ebp)
 8049dd4:	68 10 ad 04 08       	push   $0x804ad10
 8049dd9:	e8 a6 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049dde:	c9                   	leave  
 8049ddf:	c3                   	ret    

08049de0 <rsi_ble_query_include_service>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_query_include_service(RSI_BLE_CMD_QUERY_INCLUDE_SERVICES *uGetIncludeService)
{
 8049de0:	55                   	push   %ebp
 8049de1:	89 e5                	mov    %esp,%ebp
 8049de3:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Include Service start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryIncludeServ, (UINT08 *)uGetIncludeService, sizeof(RSI_BLE_CMD_QUERY_INCLUDE_SERVICES));
 8049de6:	6a 04                	push   $0x4
 8049de8:	ff 75 08             	pushl  0x8(%ebp)
 8049deb:	68 0c ad 04 08       	push   $0x804ad0c
 8049df0:	e8 8f 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049df5:	c9                   	leave  
 8049df6:	c3                   	ret    

08049df7 <rsi_ble_read_char_value_by_UUID>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_read_char_value_by_UUID(RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID *uReadCharValueByUUID)
{
 8049df7:	55                   	push   %ebp
 8049df8:	89 e5                	mov    %esp,%ebp
 8049dfa:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Read Char Val By UUID start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdReadCharValByUUID, (UINT08 *)uReadCharValueByUUID, sizeof(RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID));
 8049dfd:	6a 18                	push   $0x18
 8049dff:	ff 75 08             	pushl  0x8(%ebp)
 8049e02:	68 08 ad 04 08       	push   $0x804ad08
 8049e07:	e8 78 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049e0c:	c9                   	leave  
 8049e0d:	c3                   	ret    

08049e0e <rsi_ble_query_att>:
 *
 * @section prerequisite 
 */

INT16 rsi_ble_query_att(RSI_BLE_CMD_QUERY_ATT_DESC *uGetDescriptor)
{
 8049e0e:	55                   	push   %ebp
 8049e0f:	89 e5                	mov    %esp,%ebp
 8049e11:	83 ec 0c             	sub    $0xc,%esp

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Descriptor start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryAtt, (UINT08 *)uGetDescriptor, sizeof(RSI_BLE_CMD_QUERY_ATT_DESC));
 8049e14:	6a 04                	push   $0x4
 8049e16:	ff 75 08             	pushl  0x8(%ebp)
 8049e19:	68 04 ad 04 08       	push   $0x804ad04
 8049e1e:	e8 61 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049e23:	c9                   	leave  
 8049e24:	c3                   	ret    

08049e25 <rsi_ble_query_att_value>:
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_query_att_value(RSI_BLE_CMD_QUERY_ATT_VALUE *uGetAttributeValue)                                                                                                            													                                                              													      
{                                                                                                            													      
 8049e25:	55                   	push   %ebp
 8049e26:	89 e5                	mov    %esp,%ebp
 8049e28:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Attribute Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryAttVal, (UINT08 *)uGetAttributeValue, sizeof(RSI_BLE_CMD_QUERY_ATT_VALUE));													      
 8049e2b:	6a 02                	push   $0x2
 8049e2d:	ff 75 08             	pushl  0x8(%ebp)
 8049e30:	68 00 ad 04 08       	push   $0x804ad00
 8049e35:	e8 4a 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049e3a:	c9                   	leave  
 8049e3b:	c3                   	ret    

08049e3c <rsi_ble_query_multi_att_values>:
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_query_multi_att_values(RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES *uGetMultipleAttValues)                                                                                   													                                                              													      
{                                                                                                            													      
 8049e3c:	55                   	push   %ebp
 8049e3d:	89 e5                	mov    %esp,%ebp
 8049e3f:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Multi Att Values start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryMulAttVal, (UINT08 *)uGetMultipleAttValues, sizeof(RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES));													      
 8049e42:	6a 0b                	push   $0xb
 8049e44:	ff 75 08             	pushl  0x8(%ebp)
 8049e47:	68 fc ac 04 08       	push   $0x804acfc
 8049e4c:	e8 33 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049e51:	c9                   	leave  
 8049e52:	c3                   	ret    

08049e53 <rsi_ble_query_long_att_value>:
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_query_long_att_value(RSI_BLE_CMD_QUERY_LONG_ATT_VALUE *uGetLongAttValue)                                                                                      													                                                              													      
{                                                                                                            													      
 8049e53:	55                   	push   %ebp
 8049e54:	89 e5                	mov    %esp,%ebp
 8049e56:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Query long att value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLongAttVal, (UINT08 *)uGetLongAttValue, sizeof(RSI_BLE_CMD_QUERY_LONG_ATT_VALUE));													      
 8049e59:	6a 04                	push   $0x4
 8049e5b:	ff 75 08             	pushl  0x8(%ebp)
 8049e5e:	68 f8 ac 04 08       	push   $0x804acf8
 8049e63:	e8 1c 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049e68:	c9                   	leave  
 8049e69:	c3                   	ret    

08049e6a <rsi_ble_set_att_value>:
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_set_att_value(RSI_BLE_CMD_SET_ATT_VALUE *uSetAttValue)                                                                                                        													                                                              													      
{                                                                                                            													      
 8049e6a:	55                   	push   %ebp
 8049e6b:	89 e5                	mov    %esp,%ebp
 8049e6d:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set Att Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetAttVal, (UINT08 *)uSetAttValue, sizeof(RSI_BLE_CMD_SET_ATT_VALUE));													      
 8049e70:	6a 1c                	push   $0x1c
 8049e72:	ff 75 08             	pushl  0x8(%ebp)
 8049e75:	68 f4 ac 04 08       	push   $0x804acf4
 8049e7a:	e8 05 01 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049e7f:	c9                   	leave  
 8049e80:	c3                   	ret    

08049e81 <rsi_ble_set_att_value_no_ack>:
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_set_att_value_no_ack(RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK *uSetAttValueNoAck)                                                                                                            													                                                              													      
{                                                                                                            													      
 8049e81:	55                   	push   %ebp
 8049e82:	89 e5                	mov    %esp,%ebp
 8049e84:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set att value no ack start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetAttValNoAck, (UINT08 *)uSetAttValueNoAck, sizeof(RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK));													      
 8049e87:	6a 1c                	push   $0x1c
 8049e89:	ff 75 08             	pushl  0x8(%ebp)
 8049e8c:	68 f0 ac 04 08       	push   $0x804acf0
 8049e91:	e8 ee 00 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049e96:	c9                   	leave  
 8049e97:	c3                   	ret    

08049e98 <rsi_ble_set_long_att_value>:
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_set_long_att_value(RSI_BLE_CMD_SET_LONG_ATT_VALUE *uSetLongAttValue)                                                                                                           													                                                              													      
{                                                                                                            													      
 8049e98:	55                   	push   %ebp
 8049e99:	89 e5                	mov    %esp,%ebp
 8049e9b:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set long att value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetLongAttVal, (UINT08 *)uSetLongAttValue, sizeof(RSI_BLE_CMD_SET_LONG_ATT_VALUE));													      
 8049e9e:	6a 2d                	push   $0x2d
 8049ea0:	ff 75 08             	pushl  0x8(%ebp)
 8049ea3:	68 ec ac 04 08       	push   $0x804acec
 8049ea8:	e8 d7 00 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049ead:	c9                   	leave  
 8049eae:	c3                   	ret    

08049eaf <rsi_ble_set_prep_long_att_value>:
 * @section prerequisite                                                                                     													      
 */


INT16 rsi_ble_set_prep_long_att_value(RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE *uSetPrepLongAttValue)                                                                                                         													                                                              													      
{                                                                                                            													      
 8049eaf:	55                   	push   %ebp
 8049eb0:	89 e5                	mov    %esp,%ebp
 8049eb2:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set prep Long Att Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetPrepLongAttVal, (UINT08 *)uSetPrepLongAttValue, sizeof(RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE));													      
 8049eb5:	6a 2d                	push   $0x2d
 8049eb7:	ff 75 08             	pushl  0x8(%ebp)
 8049eba:	68 e8 ac 04 08       	push   $0x804ace8
 8049ebf:	e8 c0 00 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049ec4:	c9                   	leave  
 8049ec5:	c3                   	ret    

08049ec6 <rsi_ble_execute_long_att_value>:
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_execute_long_att_value(RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE *uExecuteLongAttValue)                                                                                                           													                                                              													      
{                                                                                                            													      
 8049ec6:	55                   	push   %ebp
 8049ec7:	89 e5                	mov    %esp,%ebp
 8049ec9:	83 ec 0c             	sub    $0xc,%esp
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Execute Long Att Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdExeLongAttVal, (UINT08 *)uExecuteLongAttValue, sizeof(RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE));													      
 8049ecc:	6a 01                	push   $0x1
 8049ece:	ff 75 08             	pushl  0x8(%ebp)
 8049ed1:	68 e4 ac 04 08       	push   $0x804ace4
 8049ed6:	e8 a9 00 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;                                                                                             													      
}                                                                                                            													      
 8049edb:	c9                   	leave  
 8049edc:	c3                   	ret    
 8049edd:	0f 1f 00             	nopl   (%eax)

08049ee0 <rsi_uint16_to_2bytes>:
 * @param[in]       uint16 data to convert
 * @param[out]      none
 * @return          none
 */
void rsi_uint16_to_2bytes(uint8 *dBuf, uint16 val)
{
 8049ee0:	55                   	push   %ebp
 8049ee1:	89 e5                	mov    %esp,%ebp
 8049ee3:	8b 55 08             	mov    0x8(%ebp),%edx
 8049ee6:	8b 45 0c             	mov    0xc(%ebp),%eax
  dBuf[0] = val & 0x00ff;
 8049ee9:	88 02                	mov    %al,(%edx)
  dBuf[1] = (val >> 8) & 0x00ff;
 8049eeb:	66 c1 e8 08          	shr    $0x8,%ax
 8049eef:	88 42 01             	mov    %al,0x1(%edx)
}
 8049ef2:	5d                   	pop    %ebp
 8049ef3:	c3                   	ret    

08049ef4 <rsi_uint32_to_4bytes>:
 * @param[in]       uint32 data to convert
 * @param[out]      none
 * @return          none
 */
void rsi_uint32_to_4bytes(uint8 *dBuf, uint32 val)
{
 8049ef4:	55                   	push   %ebp
 8049ef5:	89 e5                	mov    %esp,%ebp
 8049ef7:	8b 55 0c             	mov    0xc(%ebp),%edx
 8049efa:	8b 45 08             	mov    0x8(%ebp),%eax
  dBuf[0] = val & 0x000000ff;
  dBuf[1] = (val >> 8) & 0x000000ff;
 8049efd:	89 d1                	mov    %edx,%ecx
 8049eff:	c1 e9 08             	shr    $0x8,%ecx
 8049f02:	88 48 01             	mov    %cl,0x1(%eax)
  dBuf[2] = (val >> 16) & 0x000000ff;
 8049f05:	89 d1                	mov    %edx,%ecx
 * @param[out]      none
 * @return          none
 */
void rsi_uint32_to_4bytes(uint8 *dBuf, uint32 val)
{
  dBuf[0] = val & 0x000000ff;
 8049f07:	88 10                	mov    %dl,(%eax)
  dBuf[1] = (val >> 8) & 0x000000ff;
  dBuf[2] = (val >> 16) & 0x000000ff;
 8049f09:	c1 e9 10             	shr    $0x10,%ecx
  dBuf[3] = (val >> 24) & 0x000000ff;
 8049f0c:	c1 ea 18             	shr    $0x18,%edx
 */
void rsi_uint32_to_4bytes(uint8 *dBuf, uint32 val)
{
  dBuf[0] = val & 0x000000ff;
  dBuf[1] = (val >> 8) & 0x000000ff;
  dBuf[2] = (val >> 16) & 0x000000ff;
 8049f0f:	88 48 02             	mov    %cl,0x2(%eax)
  dBuf[3] = (val >> 24) & 0x000000ff;
 8049f12:	88 50 03             	mov    %dl,0x3(%eax)
}
 8049f15:	5d                   	pop    %ebp
 8049f16:	c3                   	ret    

08049f17 <rsi_bytes2R_to_uint16>:
 * @param[in]       uint8 *dBuf,pointer to a buffer to get the data from
 * @param[out]      none
 * @return          uint16, converted data
 */
uint16 rsi_bytes2R_to_uint16(uint8 *dBuf)
{
 8049f17:	55                   	push   %ebp
 8049f18:	89 e5                	mov    %esp,%ebp
 8049f1a:	8b 55 08             	mov    0x8(%ebp),%edx
  uint16        val;    
  val = dBuf[1];
  val <<= 8;
  val |= dBuf[0] & 0x000000ff;
  return val;
}
 8049f1d:	5d                   	pop    %ebp
 * @return          uint16, converted data
 */
uint16 rsi_bytes2R_to_uint16(uint8 *dBuf)
{
  uint16        val;    
  val = dBuf[1];
 8049f1e:	0f b6 42 01          	movzbl 0x1(%edx),%eax
  val <<= 8;
  val |= dBuf[0] & 0x000000ff;
 8049f22:	0f b6 12             	movzbl (%edx),%edx
 */
uint16 rsi_bytes2R_to_uint16(uint8 *dBuf)
{
  uint16        val;    
  val = dBuf[1];
  val <<= 8;
 8049f25:	c1 e0 08             	shl    $0x8,%eax
  val |= dBuf[0] & 0x000000ff;
 8049f28:	09 d0                	or     %edx,%eax
  return val;
}
 8049f2a:	c3                   	ret    
 8049f2b:	90                   	nop

08049f2c <rsi_bt_register_interrupt_irq>:
 *              0  = SUCCESS
 * @section description 
 * This API is used to register the interrupt irq.
 */
INT16 rsi_bt_register_interrupt_irq(void)
{
 8049f2c:	55                   	push   %ebp
 8049f2d:	89 e5                	mov    %esp,%ebp
 8049f2f:	83 ec 1c             	sub    $0x1c,%esp


#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nunblocking interrupt");
#endif
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameRegisterInterruptIrq, NULL, 0);
 8049f32:	6a 00                	push   $0x0
 8049f34:	6a 00                	push   $0x0
 8049f36:	8d 45 f4             	lea    -0xc(%ebp),%eax
 8049f39:	50                   	push   %eax
 */
INT16 rsi_bt_register_interrupt_irq(void)
{
  INT16     retval;
  /* set unblock interrupt frame */  
  UINT08      rsi_frameRegisterInterruptIrq[RSI_BYTES_4] = {0x01, 0x00, 0xEE, 0x00};
 8049f3a:	c6 45 f4 01          	movb   $0x1,-0xc(%ebp)
 8049f3e:	c6 45 f5 00          	movb   $0x0,-0xb(%ebp)
 8049f42:	c6 45 f6 ee          	movb   $0xee,-0xa(%ebp)
 8049f46:	c6 45 f7 00          	movb   $0x0,-0x9(%ebp)


#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nunblocking interrupt");
#endif
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameRegisterInterruptIrq, NULL, 0);
 8049f4a:	e8 35 00 00 00       	call   8049f84 <rsi_bt_execute_cmd>
  return retval;
}
 8049f4f:	c9                   	leave  
 8049f50:	c3                   	ret    
 8049f51:	0f 1f 00             	nopl   (%eax)

08049f54 <rsi_bt_buildFrameDescriptor>:
 * @param[in]   uint8 *cmd,Indicates type of the packet(data or management)
 * @param[out]  none
 * @return      none
 */
void rsi_bt_buildFrameDescriptor(RSI_BT_FRAME_DESC *uFrameDscFrame, uint8 *cmd)
{
 8049f54:	55                   	push   %ebp
 8049f55:	31 c9                	xor    %ecx,%ecx
 8049f57:	89 e5                	mov    %esp,%ebp
 8049f59:	8b 45 08             	mov    0x8(%ebp),%eax
 8049f5c:	8b 55 0c             	mov    0xc(%ebp),%edx
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_buildFrameDescriptor:\n");
#endif
  for (i = 0; i < RSI_BT_FRAME_DESC_LEN; i++)
  {
    uFrameDscFrame->uFrmDscBuf[i] = 0x00;
 8049f5f:	c6 04 08 00          	movb   $0x0,(%eax,%ecx,1)
 8049f63:	41                   	inc    %ecx
{
  uint8 i;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_buildFrameDescriptor:\n");
#endif
  for (i = 0; i < RSI_BT_FRAME_DESC_LEN; i++)
 8049f64:	83 f9 10             	cmp    $0x10,%ecx
 8049f67:	75 f6                	jne    8049f5f <rsi_bt_buildFrameDescriptor+0xb>
  }       //! zero the frame descriptor buffer
  //! data or management frame type
  //! uFrameDscFrame->uFrmDscBuf[14] = cmd[2];
  //! The first two bytes have different functions for management frames and
  //! control frames, but these are set in the pre-defined
  uFrameDscFrame->uFrmDscBuf[0] = cmd[0];
 8049f69:	8a 0a                	mov    (%edx),%cl
 8049f6b:	88 08                	mov    %cl,(%eax)
  //! arrays which are the argument passed to this function, so we just set the two values
  uFrameDscFrame->uFrmDscBuf[1] = (cmd[1] | (2 << 4));
 8049f6d:	8a 4a 01             	mov    0x1(%edx),%cl
 8049f70:	83 c9 20             	or     $0x20,%ecx
 8049f73:	88 48 01             	mov    %cl,0x1(%eax)
  uFrameDscFrame->uFrmDscBuf[2] = cmd[2] ;
 8049f76:	8a 4a 02             	mov    0x2(%edx),%cl
 8049f79:	88 48 02             	mov    %cl,0x2(%eax)
  uFrameDscFrame->uFrmDscBuf[3] = cmd[3] ;
 8049f7c:	8a 52 03             	mov    0x3(%edx),%dl
 8049f7f:	88 50 03             	mov    %dl,0x3(%eax)

  return;
}
 8049f82:	5d                   	pop    %ebp
 8049f83:	c3                   	ret    

08049f84 <rsi_bt_execute_cmd>:
 * @section description
 * This is a common function used to process a command to the Wi-Fi module.
 */

int16 rsi_bt_execute_cmd(uint8 *descparam, uint8 *payloadparam, uint16 size_param)
{
 8049f84:	55                   	push   %ebp
 8049f85:	89 e5                	mov    %esp,%ebp
 8049f87:	56                   	push   %esi
 8049f88:	53                   	push   %ebx
 8049f89:	83 ec 20             	sub    $0x20,%esp
 8049f8c:	0f b7 75 10          	movzwl 0x10(%ebp),%esi
#ifdef SPI_INTERFACE
  while(rsi_buffer_isFull());
#endif

  //! Build 16 bytes, send/receive command descriptor frame
  rsi_bt_buildFrameDescriptor(&uFrameDscFrame,descparam);
 8049f90:	ff 75 08             	pushl  0x8(%ebp)
 8049f93:	8d 5d e8             	lea    -0x18(%ebp),%ebx
 8049f96:	53                   	push   %ebx
 8049f97:	e8 b8 ff ff ff       	call   8049f54 <rsi_bt_buildFrameDescriptor>

  cmd_buff = rsi_alloc_and_init_cmdbuff((uint8 *)&uFrameDscFrame,payloadparam,size_param);
 8049f9c:	83 ec 0c             	sub    $0xc,%esp
 8049f9f:	56                   	push   %esi
 8049fa0:	ff 75 0c             	pushl  0xc(%ebp)
 8049fa3:	53                   	push   %ebx
 8049fa4:	e8 c5 03 00 00       	call   804a36e <rsi_alloc_and_init_cmdbuff>

  if(rsi_send_usr_cmd(cmd_buff, GET_SEND_LENGTH(cmd_buff)) < 0)
 8049fa9:	83 c4 18             	add    $0x18,%esp
#endif

  //! Build 16 bytes, send/receive command descriptor frame
  rsi_bt_buildFrameDescriptor(&uFrameDscFrame,descparam);

  cmd_buff = rsi_alloc_and_init_cmdbuff((uint8 *)&uFrameDscFrame,payloadparam,size_param);
 8049fac:	89 c6                	mov    %eax,%esi

  //! Free the command buffer
  rsi_free(cmd_buff);

  return retval;
}
 8049fae:	0f b7 00             	movzwl (%eax),%eax
  //! Build 16 bytes, send/receive command descriptor frame
  rsi_bt_buildFrameDescriptor(&uFrameDscFrame,descparam);

  cmd_buff = rsi_alloc_and_init_cmdbuff((uint8 *)&uFrameDscFrame,payloadparam,size_param);

  if(rsi_send_usr_cmd(cmd_buff, GET_SEND_LENGTH(cmd_buff)) < 0)
 8049fb1:	50                   	push   %eax
 8049fb2:	56                   	push   %esi
 8049fb3:	e8 66 04 00 00       	call   804a41e <rsi_send_usr_cmd>
  {
    RSI_DPRINT(RSI_PL13,"Unable to issue command\n");
  }

  //! Free the command buffer
  rsi_free(cmd_buff);
 8049fb8:	89 34 24             	mov    %esi,(%esp)
 * This is a common function used to process a command to the Wi-Fi module.
 */

int16 rsi_bt_execute_cmd(uint8 *descparam, uint8 *payloadparam, uint16 size_param)
{
  int16                                         retval = 0;
 8049fbb:	66 c1 f8 0f          	sar    $0xf,%ax
 8049fbf:	83 e0 fe             	and    $0xfffffffe,%eax
  {
    RSI_DPRINT(RSI_PL13,"Unable to issue command\n");
  }

  //! Free the command buffer
  rsi_free(cmd_buff);
 8049fc2:	89 45 e4             	mov    %eax,-0x1c(%ebp)
 8049fc5:	e8 46 e7 ff ff       	call   8048710 <free@plt>

  return retval;
}
 8049fca:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 8049fcd:	8d 65 f8             	lea    -0x8(%ebp),%esp
 8049fd0:	5b                   	pop    %ebx
 8049fd1:	5e                   	pop    %esi
 8049fd2:	5d                   	pop    %ebp
 8049fd3:	c3                   	ret    

08049fd4 <rsi_sendto_fd>:
 *              0  = SUCCESS
 * @section description
 * This API is used to send the netlink message to Kernel.
 */
int32 rsi_sendto_fd(int32 s, const uint8 *buf, int32 bufLen)
{
 8049fd4:	55                   	push   %ebp
  int32 r;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 8049fd5:	b9 03 00 00 00       	mov    $0x3,%ecx
 *              0  = SUCCESS
 * @section description
 * This API is used to send the netlink message to Kernel.
 */
int32 rsi_sendto_fd(int32 s, const uint8 *buf, int32 bufLen)
{
 8049fda:	89 e5                	mov    %esp,%ebp
  int32 r;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 8049fdc:	31 c0                	xor    %eax,%eax
 *              0  = SUCCESS
 * @section description
 * This API is used to send the netlink message to Kernel.
 */
int32 rsi_sendto_fd(int32 s, const uint8 *buf, int32 bufLen)
{
 8049fde:	57                   	push   %edi
 8049fdf:	56                   	push   %esi
  int32 r;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 8049fe0:	8d 55 dc             	lea    -0x24(%ebp),%edx
 *              0  = SUCCESS
 * @section description
 * This API is used to send the netlink message to Kernel.
 */
int32 rsi_sendto_fd(int32 s, const uint8 *buf, int32 bufLen)
{
 8049fe3:	53                   	push   %ebx
  int32 r;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 8049fe4:	89 d7                	mov    %edx,%edi
 *              0  = SUCCESS
 * @section description
 * This API is used to send the netlink message to Kernel.
 */
int32 rsi_sendto_fd(int32 s, const uint8 *buf, int32 bufLen)
{
 8049fe6:	83 ec 1c             	sub    $0x1c,%esp
 8049fe9:	8b 75 0c             	mov    0xc(%ebp),%esi
  int32 r;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 8049fec:	f3 ab                	rep stos %eax,%es:(%edi)
 *              0  = SUCCESS
 * @section description
 * This API is used to send the netlink message to Kernel.
 */
int32 rsi_sendto_fd(int32 s, const uint8 *buf, int32 bufLen)
{
 8049fee:	8b 5d 10             	mov    0x10(%ebp),%ebx
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
  nladdr.nl_family = AF_NETLINK;

  while ((r = sendto(s, buf, bufLen, 0, (struct sockaddr *) &nladdr,
 8049ff1:	89 d7                	mov    %edx,%edi

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
  nladdr.nl_family = AF_NETLINK;
 8049ff3:	66 c7 45 dc 10 00    	movw   $0x10,-0x24(%ebp)

  while ((r = sendto(s, buf, bufLen, 0, (struct sockaddr *) &nladdr,
 8049ff9:	eb 14                	jmp    804a00f <rsi_sendto_fd+0x3b>
                     sizeof(nladdr))) < bufLen)
  {
    if (r > 0)
 8049ffb:	85 c0                	test   %eax,%eax
 8049ffd:	7e 06                	jle    804a005 <rsi_sendto_fd+0x31>
    {
      buf += r;
 8049fff:	01 c6                	add    %eax,%esi
      bufLen -= r;
 804a001:	29 c3                	sub    %eax,%ebx
 804a003:	eb 0a                	jmp    804a00f <rsi_sendto_fd+0x3b>
    }
    else if (errno != EAGAIN)
 804a005:	e8 e6 e7 ff ff       	call   80487f0 <__errno_location@plt>
 804a00a:	83 38 0b             	cmpl   $0xb,(%eax)
 804a00d:	75 1c                	jne    804a02b <rsi_sendto_fd+0x57>
  RSI_DPRINT(RSI_PL14,"\nrsi_sendto_fd:\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
  nladdr.nl_family = AF_NETLINK;

  while ((r = sendto(s, buf, bufLen, 0, (struct sockaddr *) &nladdr,
 804a00f:	50                   	push   %eax
 804a010:	50                   	push   %eax
 804a011:	6a 0c                	push   $0xc
 804a013:	57                   	push   %edi
 804a014:	6a 00                	push   $0x0
 804a016:	53                   	push   %ebx
 804a017:	56                   	push   %esi
 804a018:	ff 75 08             	pushl  0x8(%ebp)
 804a01b:	e8 e0 e7 ff ff       	call   8048800 <sendto@plt>
 804a020:	83 c4 20             	add    $0x20,%esp
 804a023:	39 d8                	cmp    %ebx,%eax
 804a025:	7c d4                	jl     8049ffb <rsi_sendto_fd+0x27>
    }
    else if (errno != EAGAIN)
      return -1;
  }

  return 0;
 804a027:	31 c0                	xor    %eax,%eax
 804a029:	eb 03                	jmp    804a02e <rsi_sendto_fd+0x5a>
    {
      buf += r;
      bufLen -= r;
    }
    else if (errno != EAGAIN)
      return -1;
 804a02b:	83 c8 ff             	or     $0xffffffff,%eax
  }

  return 0;
}
 804a02e:	8d 65 f4             	lea    -0xc(%ebp),%esp
 804a031:	5b                   	pop    %ebx
 804a032:	5e                   	pop    %esi
 804a033:	5f                   	pop    %edi
 804a034:	5d                   	pop    %ebp
 804a035:	c3                   	ret    

0804a036 <rsi_get_family_id>:
 * @section description
 * This API is used to probe the controller in genetlink
 * to find the family id for the CTRL_PKT_TXRX family.
 */
int32 rsi_get_family_id(int32 sd)
{
 804a036:	55                   	push   %ebp
  rsi_nlPkt_t *family_req, *ans;
  int32 id = 0;
  struct nlattr *na;
  int32 rep_len;
  uint8 *req_buff = NULL, *rsp_buff = NULL;
  uint8 family_name[25] = "CTRL_PKT_TXRX";
 804a037:	b9 0e 00 00 00       	mov    $0xe,%ecx
 * @section description
 * This API is used to probe the controller in genetlink
 * to find the family id for the CTRL_PKT_TXRX family.
 */
int32 rsi_get_family_id(int32 sd)
{
 804a03c:	89 e5                	mov    %esp,%ebp
  rsi_nlPkt_t *family_req, *ans;
  int32 id = 0;
  struct nlattr *na;
  int32 rep_len;
  uint8 *req_buff = NULL, *rsp_buff = NULL;
  uint8 family_name[25] = "CTRL_PKT_TXRX";
 804a03e:	31 c0                	xor    %eax,%eax
 * @section description
 * This API is used to probe the controller in genetlink
 * to find the family id for the CTRL_PKT_TXRX family.
 */
int32 rsi_get_family_id(int32 sd)
{
 804a040:	57                   	push   %edi
 804a041:	56                   	push   %esi
  rsi_nlPkt_t *family_req, *ans;
  int32 id = 0;
  struct nlattr *na;
  int32 rep_len;
  uint8 *req_buff = NULL, *rsp_buff = NULL;
  uint8 family_name[25] = "CTRL_PKT_TXRX";
 804a042:	be b5 ad 04 08       	mov    $0x804adb5,%esi
 * @section description
 * This API is used to probe the controller in genetlink
 * to find the family id for the CTRL_PKT_TXRX family.
 */
int32 rsi_get_family_id(int32 sd)
{
 804a047:	53                   	push   %ebx
 804a048:	83 ec 48             	sub    $0x48,%esp
  rsi_nlPkt_t *family_req, *ans;
  int32 id = 0;
  struct nlattr *na;
  int32 rep_len;
  uint8 *req_buff = NULL, *rsp_buff = NULL;
  uint8 family_name[25] = "CTRL_PKT_TXRX";
 804a04b:	8d 7d cf             	lea    -0x31(%ebp),%edi
 804a04e:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 804a050:	8d 7d dd             	lea    -0x23(%ebp),%edi

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_get_family_id:\n");
#endif
  req_buff = rsi_malloc(NLMSG_LENGTH(GENL_HDRLEN) +
 804a053:	83 ce ff             	or     $0xffffffff,%esi
 804a056:	8d 55 cf             	lea    -0x31(%ebp),%edx
  rsi_nlPkt_t *family_req, *ans;
  int32 id = 0;
  struct nlattr *na;
  int32 rep_len;
  uint8 *req_buff = NULL, *rsp_buff = NULL;
  uint8 family_name[25] = "CTRL_PKT_TXRX";
 804a059:	b1 0b                	mov    $0xb,%cl
 804a05b:	f3 aa                	rep stos %al,%es:(%edi)

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_get_family_id:\n");
#endif
  req_buff = rsi_malloc(NLMSG_LENGTH(GENL_HDRLEN) +
 804a05d:	89 d7                	mov    %edx,%edi
 804a05f:	89 f1                	mov    %esi,%ecx
 804a061:	f2 ae                	repnz scas %es:(%edi),%al
 804a063:	89 55 c4             	mov    %edx,-0x3c(%ebp)
 804a066:	f7 d1                	not    %ecx
 804a068:	83 c1 07             	add    $0x7,%ecx
 804a06b:	83 e1 fc             	and    $0xfffffffc,%ecx
 804a06e:	83 c1 14             	add    $0x14,%ecx
 804a071:	51                   	push   %ecx
 804a072:	e8 09 e7 ff ff       	call   8048780 <malloc@plt>
                        NLMSG_ALIGN(strlen((char*)family_name) + 1 + NLA_HDRLEN));

  family_req = (rsi_nlPkt_t *)req_buff;

  /* Get family name */
  family_req->n.nlmsg_type = GENL_ID_CTRL;
 804a077:	66 c7 40 04 10 00    	movw   $0x10,0x4(%eax)
  uint8 family_name[25] = "CTRL_PKT_TXRX";

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_get_family_id:\n");
#endif
  req_buff = rsi_malloc(NLMSG_LENGTH(GENL_HDRLEN) +
 804a07d:	89 c3                	mov    %eax,%ebx

  family_req = (rsi_nlPkt_t *)req_buff;

  /* Get family name */
  family_req->n.nlmsg_type = GENL_ID_CTRL;
  family_req->n.nlmsg_flags = NLM_F_REQUEST;
 804a07f:	66 c7 40 06 01 00    	movw   $0x1,0x6(%eax)
  family_req->n.nlmsg_seq = 0;
 804a085:	c7 40 08 00 00 00 00 	movl   $0x0,0x8(%eax)
  family_req->n.nlmsg_pid = getpid();
 804a08c:	e8 df e6 ff ff       	call   8048770 <getpid@plt>
  family_req->g.version = 0x1;

  na = (struct nlattr *) GENLMSG_DATA(req_buff);
  na->nla_type = CTRL_ATTR_FAMILY_NAME;
  /*------change here--------*/
  na->nla_len = strlen((char*)family_name) + 1 + NLA_HDRLEN;
 804a091:	89 f1                	mov    %esi,%ecx
  /* Get family name */
  family_req->n.nlmsg_type = GENL_ID_CTRL;
  family_req->n.nlmsg_flags = NLM_F_REQUEST;
  family_req->n.nlmsg_seq = 0;
  family_req->n.nlmsg_pid = getpid();
  family_req->n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
 804a093:	c7 03 14 00 00 00    	movl   $0x14,(%ebx)
  family_req->g.cmd = CTRL_CMD_GETFAMILY;
 804a099:	c6 43 10 03          	movb   $0x3,0x10(%ebx)
  family_req->g.version = 0x1;
 804a09d:	c6 43 11 01          	movb   $0x1,0x11(%ebx)

  na = (struct nlattr *) GENLMSG_DATA(req_buff);
  na->nla_type = CTRL_ATTR_FAMILY_NAME;
 804a0a1:	66 c7 43 16 02 00    	movw   $0x2,0x16(%ebx)

  /* Get family name */
  family_req->n.nlmsg_type = GENL_ID_CTRL;
  family_req->n.nlmsg_flags = NLM_F_REQUEST;
  family_req->n.nlmsg_seq = 0;
  family_req->n.nlmsg_pid = getpid();
 804a0a7:	89 43 0c             	mov    %eax,0xc(%ebx)
  family_req->g.version = 0x1;

  na = (struct nlattr *) GENLMSG_DATA(req_buff);
  na->nla_type = CTRL_ATTR_FAMILY_NAME;
  /*------change here--------*/
  na->nla_len = strlen((char*)family_name) + 1 + NLA_HDRLEN;
 804a0aa:	8b 55 c4             	mov    -0x3c(%ebp),%edx
 804a0ad:	31 c0                	xor    %eax,%eax
 804a0af:	89 d7                	mov    %edx,%edi
 804a0b1:	f2 ae                	repnz scas %es:(%edi),%al
  strcpy((char*)NLA_DATA(na),(char*) family_name);
 804a0b3:	8d 43 18             	lea    0x18(%ebx),%eax
  family_req->g.version = 0x1;

  na = (struct nlattr *) GENLMSG_DATA(req_buff);
  na->nla_type = CTRL_ATTR_FAMILY_NAME;
  /*------change here--------*/
  na->nla_len = strlen((char*)family_name) + 1 + NLA_HDRLEN;
 804a0b6:	f7 d1                	not    %ecx
 804a0b8:	8d 71 04             	lea    0x4(%ecx),%esi
 804a0bb:	66 89 73 14          	mov    %si,0x14(%ebx)
  strcpy((char*)NLA_DATA(na),(char*) family_name);
 804a0bf:	5e                   	pop    %esi
 804a0c0:	5f                   	pop    %edi
 804a0c1:	52                   	push   %edx
 804a0c2:	50                   	push   %eax
 804a0c3:	e8 98 e6 ff ff       	call   8048760 <strcpy@plt>

  family_req->n.nlmsg_len += NLMSG_ALIGN(na->nla_len);
 804a0c8:	0f b7 43 14          	movzwl 0x14(%ebx),%eax

  if (rsi_sendto_fd(sd, (req_buff), family_req->n.nlmsg_len) < 0)
 804a0cc:	83 c4 0c             	add    $0xc,%esp
  na->nla_type = CTRL_ATTR_FAMILY_NAME;
  /*------change here--------*/
  na->nla_len = strlen((char*)family_name) + 1 + NLA_HDRLEN;
  strcpy((char*)NLA_DATA(na),(char*) family_name);

  family_req->n.nlmsg_len += NLMSG_ALIGN(na->nla_len);
 804a0cf:	83 c0 03             	add    $0x3,%eax
 804a0d2:	83 e0 fc             	and    $0xfffffffc,%eax
 804a0d5:	03 03                	add    (%ebx),%eax
 804a0d7:	89 03                	mov    %eax,(%ebx)

  if (rsi_sendto_fd(sd, (req_buff), family_req->n.nlmsg_len) < 0)
 804a0d9:	50                   	push   %eax
 804a0da:	53                   	push   %ebx
 804a0db:	ff 75 08             	pushl  0x8(%ebp)
 804a0de:	e8 f1 fe ff ff       	call   8049fd4 <rsi_sendto_fd>
 804a0e3:	83 c4 10             	add    $0x10,%esp
 804a0e6:	85 c0                	test   %eax,%eax
 804a0e8:	0f 88 a3 00 00 00    	js     804a191 <rsi_get_family_id+0x15b>
    return -1;
  else
    rsi_free(req_buff);
 804a0ee:	83 ec 0c             	sub    $0xc,%esp
 804a0f1:	53                   	push   %ebx
 804a0f2:	e8 19 e6 ff ff       	call   8048710 <free@plt>

  rsp_buff = rsi_malloc(MAX_RCV_SIZE);
 804a0f7:	c7 04 24 40 06 00 00 	movl   $0x640,(%esp)
 804a0fe:	e8 7d e6 ff ff       	call   8048780 <malloc@plt>
  ans = (rsi_nlPkt_t *)rsp_buff;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"waiting to recv family_id\n");
#endif
  rep_len = recv(sd, ans, MAX_RCV_SIZE, 0);
 804a103:	6a 00                	push   $0x0
 804a105:	68 40 06 00 00       	push   $0x640
 804a10a:	50                   	push   %eax
  if (rsi_sendto_fd(sd, (req_buff), family_req->n.nlmsg_len) < 0)
    return -1;
  else
    rsi_free(req_buff);

  rsp_buff = rsi_malloc(MAX_RCV_SIZE);
 804a10b:	89 c3                	mov    %eax,%ebx
  ans = (rsi_nlPkt_t *)rsp_buff;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"waiting to recv family_id\n");
#endif
  rep_len = recv(sd, ans, MAX_RCV_SIZE, 0);
 804a10d:	ff 75 08             	pushl  0x8(%ebp)
 804a110:	e8 5b e7 ff ff       	call   8048870 <recv@plt>
  if (rep_len < 0)
 804a115:	83 c4 20             	add    $0x20,%esp
 804a118:	85 c0                	test   %eax,%eax
 804a11a:	79 0f                	jns    804a12b <rsi_get_family_id+0xf5>
  {
    perror("recv");
 804a11c:	83 ec 0c             	sub    $0xc,%esp
 804a11f:	68 60 ad 04 08       	push   $0x804ad60
 804a124:	e8 17 e6 ff ff       	call   8048740 <perror@plt>
 804a129:	eb 38                	jmp    804a163 <rsi_get_family_id+0x12d>
    return -1;
  }

  /* Validate response message */
  if (!NLMSG_OK((&ans->n), rep_len))
 804a12b:	83 f8 0f             	cmp    $0xf,%eax
 804a12e:	7e 0b                	jle    804a13b <rsi_get_family_id+0x105>
 804a130:	8b 13                	mov    (%ebx),%edx
 804a132:	83 fa 0f             	cmp    $0xf,%edx
 804a135:	76 04                	jbe    804a13b <rsi_get_family_id+0x105>
 804a137:	39 c2                	cmp    %eax,%edx
 804a139:	76 0f                	jbe    804a14a <rsi_get_family_id+0x114>
  {
    fprintf(stderr, "invalid reply message\n");
 804a13b:	51                   	push   %ecx
 804a13c:	51                   	push   %ecx
 804a13d:	ff 35 30 c6 04 08    	pushl  0x804c630
 804a143:	68 65 ad 04 08       	push   $0x804ad65
 804a148:	eb 14                	jmp    804a15e <rsi_get_family_id+0x128>
    return -1;
  }

  if (ans->n.nlmsg_type == NLMSG_ERROR)
 804a14a:	66 83 7b 04 02       	cmpw   $0x2,0x4(%ebx)
 804a14f:	75 17                	jne    804a168 <rsi_get_family_id+0x132>
  { /* error */
    fprintf(stderr, "received error\n");
 804a151:	52                   	push   %edx
 804a152:	52                   	push   %edx
 804a153:	ff 35 30 c6 04 08    	pushl  0x804c630
 804a159:	68 7c ad 04 08       	push   $0x804ad7c
 804a15e:	e8 fd e6 ff ff       	call   8048860 <fputs@plt>
 804a163:	83 c4 10             	add    $0x10,%esp
 804a166:	eb 29                	jmp    804a191 <rsi_get_family_id+0x15b>
    return -1;
  }

  na = (struct nlattr *) GENLMSG_DATA(ans);
  na = (struct nlattr *) ((char *) na + NLA_ALIGN(na->nla_len));
 804a168:	0f b7 43 14          	movzwl 0x14(%ebx),%eax
 * to find the family id for the CTRL_PKT_TXRX family.
 */
int32 rsi_get_family_id(int32 sd)
{
  rsi_nlPkt_t *family_req, *ans;
  int32 id = 0;
 804a16c:	31 f6                	xor    %esi,%esi
    fprintf(stderr, "received error\n");
    return -1;
  }

  na = (struct nlattr *) GENLMSG_DATA(ans);
  na = (struct nlattr *) ((char *) na + NLA_ALIGN(na->nla_len));
 804a16e:	83 c0 03             	add    $0x3,%eax
 804a171:	83 e0 fc             	and    $0xfffffffc,%eax
 804a174:	8d 44 03 14          	lea    0x14(%ebx,%eax,1),%eax
  if (na->nla_type == CTRL_ATTR_FAMILY_ID)
 804a178:	66 83 78 02 01       	cmpw   $0x1,0x2(%eax)
 804a17d:	75 04                	jne    804a183 <rsi_get_family_id+0x14d>
  {
    id = *(__u16 *) NLA_DATA(na);
 804a17f:	0f b7 70 04          	movzwl 0x4(%eax),%esi
  }

  rsi_free(rsp_buff);
 804a183:	83 ec 0c             	sub    $0xc,%esp
 804a186:	53                   	push   %ebx
 804a187:	e8 84 e5 ff ff       	call   8048710 <free@plt>
 804a18c:	83 c4 10             	add    $0x10,%esp
 804a18f:	eb 03                	jmp    804a194 <rsi_get_family_id+0x15e>
  strcpy((char*)NLA_DATA(na),(char*) family_name);

  family_req->n.nlmsg_len += NLMSG_ALIGN(na->nla_len);

  if (rsi_sendto_fd(sd, (req_buff), family_req->n.nlmsg_len) < 0)
    return -1;
 804a191:	83 ce ff             	or     $0xffffffff,%esi
  }

  rsi_free(rsp_buff);

  return id;
}
 804a194:	8d 65 f4             	lea    -0xc(%ebp),%esp
 804a197:	89 f0                	mov    %esi,%eax
 804a199:	5b                   	pop    %ebx
 804a19a:	5e                   	pop    %esi
 804a19b:	5f                   	pop    %edi
 804a19c:	5d                   	pop    %ebp
 804a19d:	c3                   	ret    

0804a19e <rsi_nl_socket_init>:
 *              0  = SUCCESS
 * @section description
 * This API is used to create a netlink socket and to bind the same.
 */
int32 rsi_nl_socket_init(void)
{
 804a19e:	55                   	push   %ebp
 804a19f:	89 e5                	mov    %esp,%ebp
 804a1a1:	57                   	push   %edi
 804a1a2:	56                   	push   %esi
 804a1a3:	53                   	push   %ebx
 804a1a4:	83 ec 20             	sub    $0x20,%esp
  struct sockaddr_nl local;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_create_nl_socket\n");
#endif
  fd = socket(AF_NETLINK, SOCK_RAW, protocol);
 804a1a7:	6a 10                	push   $0x10
 804a1a9:	6a 03                	push   $0x3
 804a1ab:	6a 10                	push   $0x10
 804a1ad:	e8 8e e6 ff ff       	call   8048840 <socket@plt>
  if (fd < 0)
 804a1b2:	83 c4 10             	add    $0x10,%esp
 804a1b5:	85 c0                	test   %eax,%eax
  struct sockaddr_nl local;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_create_nl_socket\n");
#endif
  fd = socket(AF_NETLINK, SOCK_RAW, protocol);
 804a1b7:	89 c3                	mov    %eax,%ebx
  if (fd < 0)
 804a1b9:	79 0f                	jns    804a1ca <rsi_nl_socket_init+0x2c>
  {
    perror("socket");
 804a1bb:	83 ec 0c             	sub    $0xc,%esp
 804a1be:	68 8c ad 04 08       	push   $0x804ad8c
 804a1c3:	e8 78 e5 ff ff       	call   8048740 <perror@plt>
 804a1c8:	eb 75                	jmp    804a23f <rsi_nl_socket_init+0xa1>
    return -1;
  }

  memset(&local, 0, sizeof(local));
 804a1ca:	8d 75 dc             	lea    -0x24(%ebp),%esi
 804a1cd:	31 c0                	xor    %eax,%eax
 804a1cf:	b9 03 00 00 00       	mov    $0x3,%ecx
 804a1d4:	89 f7                	mov    %esi,%edi
 804a1d6:	f3 ab                	rep stos %eax,%es:(%edi)
  local.nl_family = AF_NETLINK;
  local.nl_groups = groups;
  local.nl_pid    = PORT_ID;
  printf("port id: %d",local.nl_pid);
 804a1d8:	50                   	push   %eax
 804a1d9:	50                   	push   %eax
 804a1da:	68 33 33 00 00       	push   $0x3333
 804a1df:	68 93 ad 04 08       	push   $0x804ad93
    perror("socket");
    return -1;
  }

  memset(&local, 0, sizeof(local));
  local.nl_family = AF_NETLINK;
 804a1e4:	66 c7 45 dc 10 00    	movw   $0x10,-0x24(%ebp)
  local.nl_groups = groups;
  local.nl_pid    = PORT_ID;
 804a1ea:	c7 45 e0 33 33 00 00 	movl   $0x3333,-0x20(%ebp)
  printf("port id: %d",local.nl_pid);
 804a1f1:	e8 0a e5 ff ff       	call   8048700 <printf@plt>
  printf("port id: %d",local.nl_pid);
 804a1f6:	58                   	pop    %eax
 804a1f7:	5a                   	pop    %edx
 804a1f8:	ff 75 e0             	pushl  -0x20(%ebp)
 804a1fb:	68 93 ad 04 08       	push   $0x804ad93
 804a200:	e8 fb e4 ff ff       	call   8048700 <printf@plt>
  printf("port id: %d",local.nl_pid);
 804a205:	59                   	pop    %ecx
 804a206:	5f                   	pop    %edi
 804a207:	ff 75 e0             	pushl  -0x20(%ebp)
 804a20a:	68 93 ad 04 08       	push   $0x804ad93
 804a20f:	e8 ec e4 ff ff       	call   8048700 <printf@plt>
  printf("port id: %d",local.nl_pid);
 804a214:	58                   	pop    %eax
 804a215:	5a                   	pop    %edx
 804a216:	ff 75 e0             	pushl  -0x20(%ebp)
 804a219:	68 93 ad 04 08       	push   $0x804ad93
 804a21e:	e8 dd e4 ff ff       	call   8048700 <printf@plt>
  if (bind(fd, (struct sockaddr *) &local, sizeof(local)) < 0)
 804a223:	83 c4 0c             	add    $0xc,%esp
 804a226:	6a 0c                	push   $0xc
 804a228:	56                   	push   %esi
 804a229:	53                   	push   %ebx
 804a22a:	e8 a1 e5 ff ff       	call   80487d0 <bind@plt>
 804a22f:	83 c4 10             	add    $0x10,%esp
 804a232:	85 c0                	test   %eax,%eax
 804a234:	79 0f                	jns    804a245 <rsi_nl_socket_init+0xa7>
    goto error;

  return fd;

error:
  close(fd);
 804a236:	83 ec 0c             	sub    $0xc,%esp
 804a239:	53                   	push   %ebx
 804a23a:	e8 41 e6 ff ff       	call   8048880 <close@plt>
 804a23f:	83 c4 10             	add    $0x10,%esp
  return -1;
 804a242:	83 cb ff             	or     $0xffffffff,%ebx
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_nl_socket_init\n");
#endif
  linux_app_cbPtr->nl_sd = rsi_create_nl_socket(NETLINK_GENERIC,0);

  if(linux_app_cbPtr->nl_sd < 0)
 804a245:	83 fb ff             	cmp    $0xffffffff,%ebx
  int32 retval = 0;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_nl_socket_init\n");
#endif
  linux_app_cbPtr->nl_sd = rsi_create_nl_socket(NETLINK_GENERIC,0);
 804a248:	89 1d 48 c6 04 08    	mov    %ebx,0x804c648

  if(linux_app_cbPtr->nl_sd < 0)
 804a24e:	74 11                	je     804a261 <rsi_nl_socket_init+0xc3>
    RSI_DPRINT(RSI_PL13,"create failure\n");
#endif
    return 0;
  }

  linux_app_cbPtr->family_id = rsi_get_family_id(linux_app_cbPtr->nl_sd);
 804a250:	83 ec 0c             	sub    $0xc,%esp
 804a253:	53                   	push   %ebx
 804a254:	e8 dd fd ff ff       	call   804a036 <rsi_get_family_id>

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"family id: %ld\n",linux_app_cbPtr->family_id);
#endif

  return retval;
 804a259:	83 c4 10             	add    $0x10,%esp
    RSI_DPRINT(RSI_PL13,"create failure\n");
#endif
    return 0;
  }

  linux_app_cbPtr->family_id = rsi_get_family_id(linux_app_cbPtr->nl_sd);
 804a25c:	a3 50 c6 04 08       	mov    %eax,0x804c650
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"family id: %ld\n",linux_app_cbPtr->family_id);
#endif

  return retval;
}
 804a261:	8d 65 f4             	lea    -0xc(%ebp),%esp
 804a264:	31 c0                	xor    %eax,%eax
 804a266:	5b                   	pop    %ebx
 804a267:	5e                   	pop    %esi
 804a268:	5f                   	pop    %edi
 804a269:	5d                   	pop    %ebp
 804a26a:	c3                   	ret    

0804a26b <rsi_enqueue_to_rcv_q>:
 * This API is used to enqueue the received packet from kernel
 * to receive queue.
 */
volatile int dbg_packet_pending = 0;
void rsi_enqueue_to_rcv_q(pkt_struct_t *Pkt)
{
 804a26b:	55                   	push   %ebp
 804a26c:	89 e5                	mov    %esp,%ebp
 804a26e:	83 ec 08             	sub    $0x8,%esp
  pkt_queue_t *rcv_q = &rsi_linux_app_cb.rcv_queue;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_enqueue_to_rcv_q:\n");
#endif
  if(rcv_q->tail == NULL)
 804a271:	8b 15 98 c6 04 08    	mov    0x804c698,%edx
 * This API is used to enqueue the received packet from kernel
 * to receive queue.
 */
volatile int dbg_packet_pending = 0;
void rsi_enqueue_to_rcv_q(pkt_struct_t *Pkt)
{
 804a277:	8b 45 08             	mov    0x8(%ebp),%eax
  pkt_queue_t *rcv_q = &rsi_linux_app_cb.rcv_queue;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_enqueue_to_rcv_q:\n");
#endif
  if(rcv_q->tail == NULL)
 804a27a:	85 d2                	test   %edx,%edx
 804a27c:	75 07                	jne    804a285 <rsi_enqueue_to_rcv_q+0x1a>
  {
    rcv_q->head = Pkt;
 804a27e:	a3 94 c6 04 08       	mov    %eax,0x804c694
 804a283:	eb 02                	jmp    804a287 <rsi_enqueue_to_rcv_q+0x1c>
  }
  else
  {
    rcv_q->tail->next  = Pkt;
 804a285:	89 02                	mov    %eax,(%edx)
  }
  rcv_q->tail = Pkt;
  rcv_q->tail->next = NULL;
  rcv_q->pending_pkt_count++;
#ifdef BT_ENABLE
  printf("Packet pending is set\n");
 804a287:	83 ec 0c             	sub    $0xc,%esp
  }
  else
  {
    rcv_q->tail->next  = Pkt;
  }
  rcv_q->tail = Pkt;
 804a28a:	a3 98 c6 04 08       	mov    %eax,0x804c698
  rcv_q->tail->next = NULL;
 804a28f:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
  rcv_q->pending_pkt_count++;
#ifdef BT_ENABLE
  printf("Packet pending is set\n");
 804a295:	68 9f ad 04 08       	push   $0x804ad9f
  {
    rcv_q->tail->next  = Pkt;
  }
  rcv_q->tail = Pkt;
  rcv_q->tail->next = NULL;
  rcv_q->pending_pkt_count++;
 804a29a:	66 ff 05 9c c6 04 08 	incw   0x804c69c
#ifdef BT_ENABLE
  printf("Packet pending is set\n");
 804a2a1:	e8 ea e4 ff ff       	call   8048790 <puts@plt>
  rsi_bt_AppControlBlock.PacketPending = RSI_TRUE;
  dbg_packet_pending = 1;
 804a2a6:	83 c4 10             	add    $0x10,%esp
  rcv_q->tail = Pkt;
  rcv_q->tail->next = NULL;
  rcv_q->pending_pkt_count++;
#ifdef BT_ENABLE
  printf("Packet pending is set\n");
  rsi_bt_AppControlBlock.PacketPending = RSI_TRUE;
 804a2a9:	c7 05 e2 c6 04 08 01 	movl   $0x1,0x804c6e2
 804a2b0:	00 00 00 
  dbg_packet_pending = 1;
 804a2b3:	c7 05 44 c6 04 08 01 	movl   $0x1,0x804c644
 804a2ba:	00 00 00 
#elif WLAN_ENABLE
  rsi_app_cb.pkt_pending = RSI_TRUE;
#endif  
  
  return;
}
 804a2bd:	c9                   	leave  
 804a2be:	c3                   	ret    

0804a2bf <rsi_dequeue_from_rcv_q>:
  pkt_queue_t *rcv_q = &rsi_linux_app_cb.rcv_queue;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_dequeue_from_rcv_q:\n");
#endif
  if(rcv_q->pending_pkt_count > 0)
 804a2bf:	a1 9c c6 04 08       	mov    0x804c69c,%eax
 * @section description
 * This API is used to dequeue the packets from receive queue
 * when packets are pending in queue.
 */
pkt_struct_t *rsi_dequeue_from_rcv_q(void)
{
 804a2c4:	55                   	push   %ebp
 804a2c5:	89 e5                	mov    %esp,%ebp
  pkt_queue_t *rcv_q = &rsi_linux_app_cb.rcv_queue;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_dequeue_from_rcv_q:\n");
#endif
  if(rcv_q->pending_pkt_count > 0)
 804a2c7:	66 85 c0             	test   %ax,%ax
 804a2ca:	74 24                	je     804a2f0 <rsi_dequeue_from_rcv_q+0x31>
  {
    rcv_q->pending_pkt_count--;
 804a2cc:	48                   	dec    %eax
 804a2cd:	66 a3 9c c6 04 08    	mov    %ax,0x804c69c
    Pkt = rcv_q->head;
 804a2d3:	a1 94 c6 04 08       	mov    0x804c694,%eax
    rcv_q->head = rcv_q->head->next;
 804a2d8:	8b 10                	mov    (%eax),%edx
    if(rcv_q->head == NULL)
 804a2da:	85 d2                	test   %edx,%edx
#endif
  if(rcv_q->pending_pkt_count > 0)
  {
    rcv_q->pending_pkt_count--;
    Pkt = rcv_q->head;
    rcv_q->head = rcv_q->head->next;
 804a2dc:	89 15 94 c6 04 08    	mov    %edx,0x804c694
    if(rcv_q->head == NULL)
 804a2e2:	75 0e                	jne    804a2f2 <rsi_dequeue_from_rcv_q+0x33>
    {
      rcv_q->tail = NULL;
 804a2e4:	c7 05 98 c6 04 08 00 	movl   $0x0,0x804c698
 804a2eb:	00 00 00 
 804a2ee:	eb 02                	jmp    804a2f2 <rsi_dequeue_from_rcv_q+0x33>
 * This API is used to dequeue the packets from receive queue
 * when packets are pending in queue.
 */
pkt_struct_t *rsi_dequeue_from_rcv_q(void)
{
  pkt_struct_t *Pkt = NULL;
 804a2f0:	31 c0                	xor    %eax,%eax
      rcv_q->tail = NULL;
    }
  }

  return Pkt;
}
 804a2f2:	5d                   	pop    %ebp
 804a2f3:	c3                   	ret    

0804a2f4 <RecvThreadBody>:
 * @section description
 * This is Recv thread function which will receive packets
 * from kernel over netlink socket
 */
void * RecvThreadBody(void * arg )
{
 804a2f4:	55                   	push   %ebp
 804a2f5:	89 e5                	mov    %esp,%ebp
 804a2f7:	53                   	push   %ebx
 804a2f8:	53                   	push   %ebx
  RSI_DPRINT(RSI_PL14,"\nRecvThreadBody:\n");
#endif
  RSI_DPRINT(RSI_PL13,"%s\n",s);
  while(1)
  {
    rcvPktPtr = (pkt_struct_t*)rsi_malloc(RSI_MAX_PAYLOAD_SIZE + RSI_RXPKT_HEAD_ROOM);
 804a2f9:	83 ec 0c             	sub    $0xc,%esp
 804a2fc:	68 50 06 00 00       	push   $0x650
 804a301:	e8 7a e4 ff ff       	call   8048780 <malloc@plt>
    if(rcvPktPtr == NULL)
 804a306:	83 c4 10             	add    $0x10,%esp
 804a309:	85 c0                	test   %eax,%eax
  RSI_DPRINT(RSI_PL14,"\nRecvThreadBody:\n");
#endif
  RSI_DPRINT(RSI_PL13,"%s\n",s);
  while(1)
  {
    rcvPktPtr = (pkt_struct_t*)rsi_malloc(RSI_MAX_PAYLOAD_SIZE + RSI_RXPKT_HEAD_ROOM);
 804a30b:	89 c3                	mov    %eax,%ebx
    if(rcvPktPtr == NULL)
 804a30d:	74 58                	je     804a367 <RecvThreadBody+0x73>
#endif
      return NULL;
    }
    rcvPktPtr->data = (uint8 *)(((uint8 *)rcvPktPtr) +  RSI_RXPKT_HEAD_ROOM);

    rsp_len = recv(rsi_linux_app_cb.nl_sd, rcvPktPtr->data , RSI_MAX_PAYLOAD_SIZE, 0);
 804a30f:	6a 00                	push   $0x0
 804a311:	68 40 06 00 00       	push   $0x640
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
      return NULL;
    }
    rcvPktPtr->data = (uint8 *)(((uint8 *)rcvPktPtr) +  RSI_RXPKT_HEAD_ROOM);
 804a316:	8d 40 10             	lea    0x10(%eax),%eax

    rsp_len = recv(rsi_linux_app_cb.nl_sd, rcvPktPtr->data , RSI_MAX_PAYLOAD_SIZE, 0);
 804a319:	50                   	push   %eax
 804a31a:	ff 35 48 c6 04 08    	pushl  0x804c648
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
      return NULL;
    }
    rcvPktPtr->data = (uint8 *)(((uint8 *)rcvPktPtr) +  RSI_RXPKT_HEAD_ROOM);
 804a320:	89 43 04             	mov    %eax,0x4(%ebx)

    rsp_len = recv(rsi_linux_app_cb.nl_sd, rcvPktPtr->data , RSI_MAX_PAYLOAD_SIZE, 0);
 804a323:	e8 48 e5 ff ff       	call   8048870 <recv@plt>
    if(rsp_len < 0)
 804a328:	83 c4 10             	add    $0x10,%esp
 804a32b:	85 c0                	test   %eax,%eax
 804a32d:	79 12                	jns    804a341 <RecvThreadBody+0x4d>
    {
      perror("recv");
 804a32f:	83 ec 0c             	sub    $0xc,%esp
 804a332:	68 60 ad 04 08       	push   $0x804ad60
 804a337:	e8 04 e4 ff ff       	call   8048740 <perror@plt>
      return NULL;
 804a33c:	83 c4 10             	add    $0x10,%esp
 804a33f:	eb 26                	jmp    804a367 <RecvThreadBody+0x73>
    }

    
    pthread_mutex_lock(&rsi_linux_app_cb.mutex1);
 804a341:	83 ec 0c             	sub    $0xc,%esp
 804a344:	68 74 c6 04 08       	push   $0x804c674
 804a349:	e8 e2 e3 ff ff       	call   8048730 <pthread_mutex_lock@plt>
    rsi_enqueue_to_rcv_q(rcvPktPtr);
 804a34e:	89 1c 24             	mov    %ebx,(%esp)
 804a351:	e8 15 ff ff ff       	call   804a26b <rsi_enqueue_to_rcv_q>
    pthread_mutex_unlock(&rsi_linux_app_cb.mutex1);
 804a356:	c7 04 24 74 c6 04 08 	movl   $0x804c674,(%esp)
 804a35d:	e8 8e e3 ff ff       	call   80486f0 <pthread_mutex_unlock@plt>
  }
 804a362:	83 c4 10             	add    $0x10,%esp
 804a365:	eb 92                	jmp    804a2f9 <RecvThreadBody+0x5>
}
 804a367:	31 c0                	xor    %eax,%eax
 804a369:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 804a36c:	c9                   	leave  
 804a36d:	c3                   	ret    

0804a36e <rsi_alloc_and_init_cmdbuff>:
 * @section description
 * This API is used to allocate a buffer for the command to send and
 * initializing it with all the header bytes, Desc and payload filled.
 */
uint8 *rsi_alloc_and_init_cmdbuff(uint8 *Desc, uint8 *payload, uint16 payload_size)
{
 804a36e:	55                   	push   %ebp
 804a36f:	89 e5                	mov    %esp,%ebp
 804a371:	57                   	push   %edi
 804a372:	56                   	push   %esi
  RSI_DPRINT(RSI_PL14,"\nrsi_alloc_and_init_cmdbuff\n");
#endif
  cmd_buff = rsi_malloc(payload_size + RSI_FRAME_DESC_LEN + RSI_NL_HEAD_SIZE);
  req = (rsi_nlPkt_t *)cmd_buff;

  memcpy(cmd_buff, rsi_linux_app_cb.rsi_glbl_genl_nl_hdr, RSI_NL_HEAD_SIZE - 4);
 804a373:	be 54 c6 04 08       	mov    $0x804c654,%esi
 * @section description
 * This API is used to allocate a buffer for the command to send and
 * initializing it with all the header bytes, Desc and payload filled.
 */
uint8 *rsi_alloc_and_init_cmdbuff(uint8 *Desc, uint8 *payload, uint16 payload_size)
{
 804a378:	53                   	push   %ebx
 804a379:	83 ec 28             	sub    $0x28,%esp
 804a37c:	8b 5d 10             	mov    0x10(%ebp),%ebx
  struct nlattr  *na;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_alloc_and_init_cmdbuff\n");
#endif
  cmd_buff = rsi_malloc(payload_size + RSI_FRAME_DESC_LEN + RSI_NL_HEAD_SIZE);
 804a37f:	0f b7 c3             	movzwl %bx,%eax
 804a382:	89 45 e4             	mov    %eax,-0x1c(%ebp)
 804a385:	83 c0 28             	add    $0x28,%eax
 804a388:	50                   	push   %eax
 804a389:	e8 f2 e3 ff ff       	call   8048780 <malloc@plt>
  req = (rsi_nlPkt_t *)cmd_buff;

  memcpy(cmd_buff, rsi_linux_app_cb.rsi_glbl_genl_nl_hdr, RSI_NL_HEAD_SIZE - 4);
 804a38e:	b9 05 00 00 00       	mov    $0x5,%ecx
  na = (struct nlattr *) GENLMSG_DATA(cmd_buff);
  na->nla_type = 1; //!DOC_EXMPL_A_MSG
  na->nla_len = payload_size + RSI_FRAME_DESC_LEN + NLA_HDRLEN + 2; //!message length
  memcpy(NLA_DATA(na), Desc, RSI_FRAME_DESC_LEN);

  if(payload_size)
 804a393:	83 c4 10             	add    $0x10,%esp
 804a396:	66 85 db             	test   %bx,%bx
  RSI_DPRINT(RSI_PL14,"\nrsi_alloc_and_init_cmdbuff\n");
#endif
  cmd_buff = rsi_malloc(payload_size + RSI_FRAME_DESC_LEN + RSI_NL_HEAD_SIZE);
  req = (rsi_nlPkt_t *)cmd_buff;

  memcpy(cmd_buff, rsi_linux_app_cb.rsi_glbl_genl_nl_hdr, RSI_NL_HEAD_SIZE - 4);
 804a399:	89 c7                	mov    %eax,%edi
  struct nlattr  *na;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_alloc_and_init_cmdbuff\n");
#endif
  cmd_buff = rsi_malloc(payload_size + RSI_FRAME_DESC_LEN + RSI_NL_HEAD_SIZE);
 804a39b:	89 c2                	mov    %eax,%edx
  req = (rsi_nlPkt_t *)cmd_buff;

  memcpy(cmd_buff, rsi_linux_app_cb.rsi_glbl_genl_nl_hdr, RSI_NL_HEAD_SIZE - 4);
 804a39d:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
  /*compose message*/
  na = (struct nlattr *) GENLMSG_DATA(cmd_buff);
  na->nla_type = 1; //!DOC_EXMPL_A_MSG
 804a39f:	66 c7 40 16 01 00    	movw   $0x1,0x16(%eax)
  na->nla_len = payload_size + RSI_FRAME_DESC_LEN + NLA_HDRLEN + 2; //!message length
 804a3a5:	8d 43 16             	lea    0x16(%ebx),%eax
 804a3a8:	66 89 42 14          	mov    %ax,0x14(%edx)
  memcpy(NLA_DATA(na), Desc, RSI_FRAME_DESC_LEN);
 804a3ac:	8d 42 18             	lea    0x18(%edx),%eax
 804a3af:	8b 75 08             	mov    0x8(%ebp),%esi
 804a3b2:	89 c7                	mov    %eax,%edi
 804a3b4:	b1 04                	mov    $0x4,%cl
 804a3b6:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)

  if(payload_size)
 804a3b8:	74 0d                	je     804a3c7 <rsi_alloc_and_init_cmdbuff+0x59>
    memcpy(NLA_DATA(na) + RSI_FRAME_DESC_LEN, payload, payload_size);
 804a3ba:	8d 42 28             	lea    0x28(%edx),%eax
 804a3bd:	8b 75 0c             	mov    0xc(%ebp),%esi
 804a3c0:	8b 4d e4             	mov    -0x1c(%ebp),%ecx
 804a3c3:	89 c7                	mov    %eax,%edi
 804a3c5:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
  req->n.nlmsg_len += NLMSG_ALIGN(na->nla_len);
 804a3c7:	0f b7 42 14          	movzwl 0x14(%edx),%eax
 804a3cb:	83 c0 03             	add    $0x3,%eax
 804a3ce:	83 e0 fc             	and    $0xfffffffc,%eax
 804a3d1:	01 02                	add    %eax,(%edx)

  return cmd_buff;
}
 804a3d3:	89 d0                	mov    %edx,%eax
 804a3d5:	8d 65 f4             	lea    -0xc(%ebp),%esp
 804a3d8:	5b                   	pop    %ebx
 804a3d9:	5e                   	pop    %esi
 804a3da:	5f                   	pop    %edi
 804a3db:	5d                   	pop    %ebp
 804a3dc:	c3                   	ret    

0804a3dd <rsi_fill_genl_nl_hdrs_for_cmd>:
 * @section description
 * This API is used to fill the global array which will be used
 * to fill the header information for the commands to send afterward.
 */
void rsi_fill_genl_nl_hdrs_for_cmd(void)
{
 804a3dd:	55                   	push   %ebp
 804a3de:	89 e5                	mov    %esp,%ebp
 804a3e0:	83 ec 08             	sub    $0x8,%esp
#endif
  req = (rsi_nlPkt_t *)(rsi_linux_app_cb.rsi_glbl_genl_nl_hdr);

  /* Send command needed */
  req->n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
  req->n.nlmsg_type = rsi_linux_app_cb.family_id;
 804a3e3:	a1 50 c6 04 08       	mov    0x804c650,%eax
  RSI_DPRINT(RSI_PL14,"\nrsi_fill_genl_nl_hdrs_for_cmd\n");
#endif
  req = (rsi_nlPkt_t *)(rsi_linux_app_cb.rsi_glbl_genl_nl_hdr);

  /* Send command needed */
  req->n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
 804a3e8:	c7 05 54 c6 04 08 14 	movl   $0x14,0x804c654
 804a3ef:	00 00 00 
  req->n.nlmsg_type = rsi_linux_app_cb.family_id;
  req->n.nlmsg_flags = NLM_F_REQUEST;
 804a3f2:	66 c7 05 5a c6 04 08 	movw   $0x1,0x804c65a
 804a3f9:	01 00 
  req->n.nlmsg_seq = 60;
 804a3fb:	c7 05 5c c6 04 08 3c 	movl   $0x3c,0x804c65c
 804a402:	00 00 00 
#endif
  req = (rsi_nlPkt_t *)(rsi_linux_app_cb.rsi_glbl_genl_nl_hdr);

  /* Send command needed */
  req->n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
  req->n.nlmsg_type = rsi_linux_app_cb.family_id;
 804a405:	66 a3 58 c6 04 08    	mov    %ax,0x804c658
  req->n.nlmsg_flags = NLM_F_REQUEST;
  req->n.nlmsg_seq = 60;
  req->n.nlmsg_pid = getpid();
 804a40b:	e8 60 e3 ff ff       	call   8048770 <getpid@plt>
  req->g.cmd = 1;
 804a410:	c6 05 64 c6 04 08 01 	movb   $0x1,0x804c664
  /* Send command needed */
  req->n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
  req->n.nlmsg_type = rsi_linux_app_cb.family_id;
  req->n.nlmsg_flags = NLM_F_REQUEST;
  req->n.nlmsg_seq = 60;
  req->n.nlmsg_pid = getpid();
 804a417:	a3 60 c6 04 08       	mov    %eax,0x804c660
  req->g.cmd = 1;

  return;
}
 804a41c:	c9                   	leave  
 804a41d:	c3                   	ret    

0804a41e <rsi_send_usr_cmd>:
 * @section description
 * This API is used to send the command from user space to kernel
 * space over netlink socket.
 */
int16 rsi_send_usr_cmd(uint8 *buff, uint16 bufLen)
{
 804a41e:	55                   	push   %ebp
  int retval = 0;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_send_usr_cmd\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 804a41f:	31 c0                	xor    %eax,%eax
 * @section description
 * This API is used to send the command from user space to kernel
 * space over netlink socket.
 */
int16 rsi_send_usr_cmd(uint8 *buff, uint16 bufLen)
{
 804a421:	89 e5                	mov    %esp,%ebp
  int retval = 0;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_send_usr_cmd\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 804a423:	b9 03 00 00 00       	mov    $0x3,%ecx
 * @section description
 * This API is used to send the command from user space to kernel
 * space over netlink socket.
 */
int16 rsi_send_usr_cmd(uint8 *buff, uint16 bufLen)
{
 804a428:	57                   	push   %edi
 804a429:	53                   	push   %ebx
  int retval = 0;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_send_usr_cmd\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 804a42a:	8d 55 ec             	lea    -0x14(%ebp),%edx
 * @section description
 * This API is used to send the command from user space to kernel
 * space over netlink socket.
 */
int16 rsi_send_usr_cmd(uint8 *buff, uint16 bufLen)
{
 804a42d:	83 ec 18             	sub    $0x18,%esp
 804a430:	0f b7 5d 0c          	movzwl 0xc(%ebp),%ebx
  int retval = 0;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_send_usr_cmd\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
 804a434:	89 d7                	mov    %edx,%edi
 804a436:	f3 ab                	rep stos %eax,%es:(%edi)
  nladdr.nl_family = AF_NETLINK;

  retval = sendto(rsi_linux_app_cb.nl_sd, (char *)buff, bufLen, 0,
 804a438:	6a 0c                	push   $0xc
 804a43a:	52                   	push   %edx
 804a43b:	6a 00                	push   $0x0
 804a43d:	53                   	push   %ebx
 804a43e:	ff 75 08             	pushl  0x8(%ebp)
 804a441:	ff 35 48 c6 04 08    	pushl  0x804c648

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_send_usr_cmd\n");
#endif
  memset(&nladdr, 0, sizeof(nladdr));
  nladdr.nl_family = AF_NETLINK;
 804a447:	66 c7 45 ec 10 00    	movw   $0x10,-0x14(%ebp)

  retval = sendto(rsi_linux_app_cb.nl_sd, (char *)buff, bufLen, 0,
 804a44d:	e8 ae e3 ff ff       	call   8048800 <sendto@plt>
                  (struct sockaddr *) &nladdr, sizeof(nladdr));

  return retval;
}
 804a452:	8d 65 f8             	lea    -0x8(%ebp),%esp
 804a455:	5b                   	pop    %ebx
 804a456:	5f                   	pop    %edi
 804a457:	5d                   	pop    %ebp
 804a458:	c3                   	ret    
 804a459:	0f 1f 80 00 00 00 00 	nopl   0x0(%eax)

0804a460 <__libc_csu_init>:
 804a460:	55                   	push   %ebp
 804a461:	57                   	push   %edi
 804a462:	31 ff                	xor    %edi,%edi
 804a464:	56                   	push   %esi
 804a465:	53                   	push   %ebx
 804a466:	e8 9d e4 ff ff       	call   8048908 <__x86.get_pc_thunk.bx>
 804a46b:	81 c3 95 1c 00 00    	add    $0x1c95,%ebx
 804a471:	83 ec 1c             	sub    $0x1c,%esp
 804a474:	8b 6c 24 30          	mov    0x30(%esp),%ebp
 804a478:	8d b3 04 ff ff ff    	lea    -0xfc(%ebx),%esi
 804a47e:	e8 2d e2 ff ff       	call   80486b0 <_init>
 804a483:	8d 83 00 ff ff ff    	lea    -0x100(%ebx),%eax
 804a489:	29 c6                	sub    %eax,%esi
 804a48b:	c1 fe 02             	sar    $0x2,%esi
 804a48e:	85 f6                	test   %esi,%esi
 804a490:	74 27                	je     804a4b9 <__libc_csu_init+0x59>
 804a492:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 804a498:	8b 44 24 38          	mov    0x38(%esp),%eax
 804a49c:	89 2c 24             	mov    %ebp,(%esp)
 804a49f:	89 44 24 08          	mov    %eax,0x8(%esp)
 804a4a3:	8b 44 24 34          	mov    0x34(%esp),%eax
 804a4a7:	89 44 24 04          	mov    %eax,0x4(%esp)
 804a4ab:	ff 94 bb 00 ff ff ff 	call   *-0x100(%ebx,%edi,4)
 804a4b2:	83 c7 01             	add    $0x1,%edi
 804a4b5:	39 f7                	cmp    %esi,%edi
 804a4b7:	75 df                	jne    804a498 <__libc_csu_init+0x38>
 804a4b9:	83 c4 1c             	add    $0x1c,%esp
 804a4bc:	5b                   	pop    %ebx
 804a4bd:	5e                   	pop    %esi
 804a4be:	5f                   	pop    %edi
 804a4bf:	5d                   	pop    %ebp
 804a4c0:	c3                   	ret    
 804a4c1:	eb 0d                	jmp    804a4d0 <__libc_csu_fini>
 804a4c3:	90                   	nop
 804a4c4:	90                   	nop
 804a4c5:	90                   	nop
 804a4c6:	90                   	nop
 804a4c7:	90                   	nop
 804a4c8:	90                   	nop
 804a4c9:	90                   	nop
 804a4ca:	90                   	nop
 804a4cb:	90                   	nop
 804a4cc:	90                   	nop
 804a4cd:	90                   	nop
 804a4ce:	90                   	nop
 804a4cf:	90                   	nop

0804a4d0 <__libc_csu_fini>:
 804a4d0:	f3 c3                	repz ret 
 804a4d2:	66 90                	xchg   %ax,%ax

Disassembly of section .fini:

0804a4d4 <_fini>:
 804a4d4:	53                   	push   %ebx
 804a4d5:	83 ec 08             	sub    $0x8,%esp
 804a4d8:	e8 2b e4 ff ff       	call   8048908 <__x86.get_pc_thunk.bx>
 804a4dd:	81 c3 23 1c 00 00    	add    $0x1c23,%ebx
 804a4e3:	83 c4 08             	add    $0x8,%esp
 804a4e6:	5b                   	pop    %ebx
 804a4e7:	c3                   	ret    
