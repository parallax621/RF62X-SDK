extern "C"{
#include <rf627_sdk.h>
}
#include <iostream>
#include <cstring>
#include <stdarg.h>


#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

/** @brief Allocates an array in memory with elements initialized to 0.
 *
 * @param num - number of elements to allocate.
 * @param size - size of each element.
 * @return
 * - On success: returns a pointer to the allocated space.
 * - On error: NULL
 */
void* platform_calloc(rfSize num, rfSize size)
{
    return calloc(num, size);
}

/**
 * @brief malloc_t - ptr to function whish allocates memory block
 * Allocates a block of size bytes of memory, returning a pointer
 * to the beginning of the block.
 * @param size - Size of the memory block, in bytes.
 * @return On success, a pointer to the memory block allocated by the function.
 * If the function failed to allocate the requested block of memory, a null
 * pointer is returned.
 */
void* platform_malloc(rfSize size)
{
    return malloc(size);
}

/**
 * @brief realloc_t - ptr to function whish reallocates memory block
 * Changes the size of the memory block pointed to by ptr. The function may move
 * the memory block to a new location (whose address is returned by the function).
 * @param ptr - Pointer to a memory block previously allocated.
 * @param newsize - New size for the memory block, in bytes.
 * @return A pointer to the reallocated memory block, which may be either the
 * same as ptr or a new location.
 */
void* platform_realloc(void *ptr, rfSize newsize)
{
    return realloc(ptr, newsize);
}

/** @brief Deallocates or frees a memory block.
 *
 * @param data - Previously allocated memory block to be freed.
 */
void platform_free(void* data)
{
    free(data);
}

/**
 * @brief memset_t - ptr to function whish fills block of memory
 * Sets the first num bytes of the block of memory pointed by ptr to the
 * specified value (interpreted as an unsigned char).
 * @param memptr - Pointer to the block of memory to fill.
 * @param val - Value to be set.
 * @param num - Number of bytes to be set to the value.
 *              rfSize is an unsigned integral type.
 * @return ptr is returned.
 */
void* platform_memset(void* memptr, rfInt val, rfSize num)
{
    return memset(memptr, val, num);
}
/**
 * @brief memcpy_t - ptr to function whish copies block of memory
 * Copies the values of num bytes from the location pointed to by source
 * directly to the memory block pointed to by destination.
 * @param destination - Pointer to the destination array where the content is to
 *                      be copied, type-casted to a pointer of type void*.
 * @param source - Pointer to the source of data to be copied, type-casted to a
 *                 pointer of type const void*.
 * @param num - Number of bytes to copy. rfSize is an unsigned integral type.
 * @return destination is returned.
 */
void* platform_memcpy(void* destination, const void* source, rfSize num)
{
    return memcpy(destination, source, num);
}

/**
 * @brief memcmp_t - ptr to function whish compare two blocks of memory
 * Compares the first num bytes of the block of memory pointed by ptr1 to the
 * first num bytes pointed by ptr2, returning zero if they all match or a value
 * different from zero representing which is greater if they do not.
 * @param ptr1 - Pointer to block of memory.
 * @param ptr2 - Pointer to block of memory.
 * @param num - Number of bytes to compare.
 * @return  0 - if the contents of both memory blocks are equal,
 *         <0 - if the first byte that does not match in both memory blocks has
 * a lower value in ptr1 than in ptr2.
 *         >0 - if the first byte that does not match in both memory blocks has
 * a greater value in ptr1 than in ptr2.
 */
rfInt platform_memcmp(const void * ptr1, const void * ptr2, size_t num )
{
    return memcmp(ptr1, ptr2, num);
}

memory_platform_dependent_methods_t memory_methods = {
    .rf_calloc = platform_calloc,
    .rf_malloc = platform_malloc,
    .rf_realloc = platform_realloc,
    .rf_free = platform_free,

    .rf_memset = platform_memset,
    .rf_memcpy = platform_memcpy,
    .rf_memcmp = platform_memcmp
};

/** @brief Method for outputting debugging information
 */
rfInt platform_printf(const rfChar* msg, ...)
{
    return printf(msg);
}


iostream_platform_dependent_methods_t iostream_methods = {
    .trace_info = platform_printf,
    .trace_warning = platform_printf,
    .trace_error = platform_printf
};

/** @brief The modbusHtoN_long_t function converts a u_long from host to TCP/IP
 *         network byte order (which is big-endian).
 *
 * @param hostlong - A 32-bit number in host byte order.
 * @return: The modbusHtoN_long_t function returns the value in TCP/IP's network
 *          byte order.
 */
rfUint32 platform_htonl(rfUint32 hostlong)
{
    return htonl(hostlong);
}

/** @brief The modbusHtoN_long_t function converts a u_long from TCP/IP network
 * order to host byte order (which is little-endian on Intel processors).
 *
 * @param netlong - A 32-bit number in TCP/IP network byte order.
 * @return: The modbusNtoH_long_t function returns the value supplied in the netlong parameter with the byte order reversed.
 */
rfUint32 platform_ntohl(rfUint32 netlong)
{
    return ntohl(netlong);
}

/** @brief The modbusHtoN_short_t function converts a u_short from host to TCP/IP network byte order (which is big-endian).
 *
 * @param hostlong - A 16-bit number in host byte order.
 * @return: The modbusHtoN_short_t function returns the value in TCP/IP's network byte order.
 */
rfUint16 platform_htons(rfUint16 hostshort)
{
    return htons(hostshort);
}

/** @brief The modbusHtoN_short_t function converts a u_short from TCP/IP network byte order to host byte order
 *
 * @param netshort - A 16-bit number in TCP/IP network byte order.
 * @return: The modbusNtoH_short_t function returns the value in host byte order.
 */
rfUint16 platform_ntohs(rfUint16 netshort)
{
    return ntohs(netshort);
}

/** @brief Pointer to TCP socket creation function
 *
 * @param af - The address family specification.
 * @param type - The type specification for the new socket.
 * @param protocol - The protocol to be used.
 * @return
 * - On success: If no error occurs, modbusCreateTcpSocket_t returns a descriptor referencing the new socket
 * - On error: NULL
 */
void* platform_create_socket(rfInt32 af, rfInt32 type, rfInt32 protocol)
{
    SOCKET* s = new SOCKET;
    *s = socket(af, type, protocol);
    return s;
}

/** @brief Pointer to the function that sets a socket option.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param level - The level at which the option is defined.
 * @param optname - The socket option for which the value is to be set.
 * @param optval - A pointer to the buffer in which the value for the requested option is specified.
 * @param optlen - The size, in bytes, of the buffer pointed to by the optval parameter.
 *  @return
 * - On success: If no error occurs, modbusSetSocketOption_t returns zero
 * - On error: -1
 */
rfInt8 platform_set_socket_option(
        void* socket, rfInt32 level, rfInt32 optname,
        const rfChar* optval, rfInt32 optlen)
{
    return setsockopt(*(SOCKET*)socket, level, optname, optval, optlen);
}

/** @brief Pointer to the function that sets a timeout for socket receive.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param msec - The timeout in millisec.
 *  @return
 * - On success: If no error occurs, returns zero
 * - On error: -1
 */
rfInt8 platform_set_socket_recv_timeout(void* socket, rfInt32 msec)
{
#ifdef _WIN32
    DWORD t = msec;
#else
    timeval t;
    t.tv_sec = msec / 1000;
    t.tv_usec = (msec % 1000) * 1000;
#endif
    return (setsockopt(*(SOCKET*)socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&t, sizeof(t)));
}

/** @brief Pointer to the function that establishes a connection to a specified socket
 *
 * @param socket - A descriptor identifying an unconnected socket.
 * @param name - A pointer to the SockAddr structure to which the connection should be established.
 * @param namelen - The length, in bytes, of the SockAddr structure pointed to by the name parameter.
 * @return
 * - On success: If no error occurs, modbusSocketConnect_t returns zero
 * - On error: -1
 */
rfUint8 platform_socket_connect(
        void* socket, rf_sockaddr_in* name, rfInt32 namelen)
{
    return connect(*(SOCKET*)socket, (sockaddr*)name, namelen);
}

/** @brief Pointer to the function that associates a local address with a socket.
 *
 * @param socket - A descriptor identifying an unconnected socket.
 * @param name - A pointer to the SockAddr structure to which the connection should be established.
 * @param namelen - The length, in bytes, of the SockAddr structure pointed to by the name parameter.
 * @return
 * - On success: If no error occurs, modbusSocketBind_t returns zero
 * - On error: -1
 */
rfUint8 platform_socket_bind(
        void* socket, rf_sockaddr_in* name, rfInt32 namelen)
{
    return bind(*(SOCKET*)socket, (sockaddr*)name, namelen);
}

/** @brief Pointer to the function that places a socket in a state in which it is listening for an incoming connection.
 *
 * @param socket - A descriptor identifying a bound, unconnected socket.
 * @param backlog - The maximum length of the queue of pending connections.
 * @return
 * - On success: If no error occurs, modbusSocketListen_t returns zero
 * - On error: -1
 */
rfUint8 platform_socket_listen(
        void* socket, rfInt32 backlog)
{
    return listen(*(SOCKET*)socket, backlog);
}

/** @brief Pointer to the function that permits an incoming connection attempt on a socket.
 *
 * @param socket - A descriptor that identifies a socket that has been placed in a listening
 * 				  state with the modbusSocketListen_t function. The connection is actually
 * 				  made with the socket that is returned by accept.
 * @param name - An optional pointer to a buffer that receives the address of the connecting
 * 				entity, as known to the communications layer. The exact format of the addr
 * 				parameter is determined by the address family that was established when
 * 				the socket from the SockAddr structure was created.
 * @param addrlen - An optional pointer to an integer that contains the length of structure
 * 				   pointed to by the addr parameter.
 * @return
 * - On success: If no error occurs, modbusSocketAccept_t returns value is a handle for the
 * 				socket on which the actual connection is made
 * - On error  : NULL
 */
void* platform_socket_accept(
        void* socket, rf_sockaddr_in* addr, rfInt32* addrlen)
{
    SOCKET* s = new SOCKET();
    *s = accept(*(SOCKET*)socket, (sockaddr*)addr, addrlen);
    return s;
}

/** @brief Pointer to the function that closes an existing socket.
 *
 * @param socket - A descriptor identifying the socket to close.
 * @return
 * - On success: If no error occurs, modbusCloseTcpSocket_t returns zero.
 * - On error: -1
 */
rfUint8 platform_close_socket(void* socket)
{
    if (*(SOCKET*)socket != INVALID_SOCKET) {
#ifdef _WIN32
        return closesocket(*(SOCKET*)socket);
#else
        return close(s);
#endif
    }
    return -1;
}

/** @brief Pointer to the send function that sends data on a TCP connected socket
 *
 * @param socket - A descriptor identifying a connected socket.
 * @param buf - A pointer to a buffer containing the data to be transmitted.
 * @param len - The length, in bytes, of the data in buffer pointed to by the buf parameter.
 * @return
 * - On success: If no error occurs, send returns the total number of bytes sent, which can be less
 * 				than the number requested to be sent in the len parameter
 * - On error: -1
 */
rfSsize platform_send_tcp_data(void* socket, const void *buf, rfSize len)
{
    if (!buf || !len) {
        return -1;
    }
    return send(*(SOCKET*)socket, (char*)buf, len, 0);
}

/** @brief Pointer to the send function that sends data on a UDP socket
 *
 * @param socket - A descriptor identifying a socket.
 * @param buf - A pointer to a buffer containing the message to be sent.
 * @param len - The size of the message in bytes.
 * @param dest_addr - Points to a sockaddr_in structure containing the destination address.
 * @param addrlen - Specifies the length of the sockaddr_in structure pointed to by the dest_addr argument.
 * @return
 * - On success: If no error occurs, send returns the total number of bytes sent, which can be less
 * 				than the number requested to be sent in the len parameter
 * - On error: -1
 */
rfSsize platform_send_udp_data(
        void* socket, const void *data, rfSize len,
        const rf_sockaddr_in *dest_addr, rf_socklen_t addrlen)
{
    if (!data || !len) {
        return -1;
    }
    return sendto(*(SOCKET*)socket, (char*)data, len,
                  0, (sockaddr*)dest_addr, addrlen);
}

/**
 * @brief Pointer to the function that receive message from socket and capture address of sender.
 * @param sockfd - Specifies a socket descriptor from which data should be received.
 * @param buf - Specifies the buffer in which to place the message.
 * @param len - Specifies the length of the buffer area.
 * @param src_addr - Specifies a socket address structure to record the address of the message sender.
 * @param addrlen - Specifies the length of the sender's address.
 * @return If successful - the number of bytes received. On failure, it returns a value of -1
 */
rfSsize platform_recv_from(
        void* socket, void *buf, rfSize len,
        rf_sockaddr_in *src_addr, rf_socklen_t *addrlen)
{
    rfSsize nret;
    rf_socklen_t from_size;
    rf_sockaddr_in from_addr;
    from_size = sizeof(from_addr);
    if (*(SOCKET*)socket == INVALID_SOCKET) {
        return -1;
    }
    nret = recvfrom(*(SOCKET*)socket, (char*)buf, (int)len, 0, (sockaddr*)&from_addr, (int*)addrlen);
    if (nret > 0)
    {
        if (src_addr) {
            memcpy(src_addr, &from_addr, sizeof(from_addr));
        }
        return nret;
    }
    else
    {
        return -1;
    }
}

network_platform_dependent_methods_t network_methods = {
    .hton_long = platform_htonl,
    .ntoh_long = platform_ntohl,
    .hton_short = platform_htons,
    .ntoh_short = platform_ntohs,

    .create_socket = platform_create_socket,
    .set_socket_option = platform_set_socket_option,
    .set_socket_recv_timeout = platform_set_socket_recv_timeout,
    .socket_connect = platform_socket_connect,
    .socket_bind = platform_socket_bind,
    .socket_listen = platform_socket_listen,
    .socket_accept = platform_socket_accept,
    .close_socket = platform_close_socket,

    .send_tcp_data = platform_send_tcp_data,
    .send_udp_data = platform_send_udp_data,

    .recv_from = platform_recv_from
};

network_platform_dependent_settings_t adapter_settings =
{
    .host_ip_addr = inet_addr("127.0.0.1"),
    .host_mask = inet_addr("255.255.255.0")
};


extern BOOL EnumAdapterAddresses();
extern void FreeAdapterAddresses();
extern int GetAdaptersCount();
extern const char* GetAdapterAddress(int index);
/* windows sockets tweaks */
extern BOOL WinSockInit();







int main()
{
#if (defined _WIN32)// && !defined __MINGW32__)
    WinSockInit();
#endif
    FreeAdapterAddresses();
    EnumAdapterAddresses();

    std::cout << sdk_version() << std::endl;

    init_platform_dependent_methods(
                &memory_methods, &iostream_methods, &network_methods, &adapter_settings);

    vector_t* scanners = (vector_t*)calloc(1, sizeof(vector_t));
    vector_init(scanners);

    for (int i=0; i<GetAdaptersCount(); i++)
    {
        adapter_settings.host_ip_addr = inet_addr(GetAdapterAddress(i));
        change_platform_adapter_settings(&adapter_settings);
        search(scanners, kRF627_OLD, kSERVICE_PROTOKOL);
    }

    std::cout << vector_count(scanners) << std::endl;
}


























