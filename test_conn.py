#!/bin/env python3

import time
import struct

from socket import socket, AF_INET, SOCK_STREAM

PACKETS = {
    0x01: "connect",
    0x02: "ping",
    0x03: "pong",

    0x05: "join",
    0x06: "leave",

    0x10: "data",
    0x11: "position",
    0x12: "action",
}

def get_packet_name(id: int) -> str:
    if id in PACKETS:
        return PACKETS[id]

    return "unknown"

def main():
    sock = socket(AF_INET, SOCK_STREAM)

    sock.connect(("localhost", 8876))

    #sock.send(bytes.fromhex('08 11  01 00 00 00  01 00 00 00'))

    while True:
        size = struct.unpack('B', sock.recv(1))[0]
        packet_id = struct.unpack('B', sock.recv(1))[0]

        data = sock.recv(size)

        player_id = data[size - 1]

        packet_name = get_packet_name(packet_id)

        print(f'got packet ({packet_name}) from player {player_id}')
        print(f'\tdata = {data[:size-1]}')

        if packet_id == 0x11:
            x = struct.unpack('f', data[:4])[0]
            y = struct.unpack('f', data[4:8])[0]

            print(f'\tx = {x}, y = {y}')


if __name__ == '__main__':
    main()

