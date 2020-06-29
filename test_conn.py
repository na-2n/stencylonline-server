#!/bin/env python3

import time
import struct

from enum import IntEnum
from socket import socket, AF_INET, SOCK_STREAM

class PacketId(IntEnum):
    PING     = 0x00

    JOIN     = 0x01
    LEAVE    = 0x02

    POSITION = 0x03
    SPAWN    = 0x04


def main():
    sock = socket(AF_INET, SOCK_STREAM)

    sock.connect(("localhost", 8876))

    print('connected')

    #                       len  id    x pos        y pos
    #sock.send(bytes.fromhex('08  03    00 00 00 00  00 00 00 00'))

    while True:
        size = struct.unpack('B', sock.recv(1))[0]
        packet_id = struct.unpack('B', sock.recv(1))[0]
        player_id = struct.unpack('B', sock.recv(1))[0]

        data = sock.recv(size) if size > 0 else b''

        packet_name = PacketId(packet_id).name

        print(f'\ngot packet ({packet_name}) from player {player_id}')
        print(f'\tdata = {data}')

        if packet_id == PacketId.POSITION:
            x = struct.unpack('f', data[:4])[0]
            y = struct.unpack('f', data[4:8])[0]

            print(f'\tx = {x}, y = {y}')


if __name__ == '__main__':
    main()

