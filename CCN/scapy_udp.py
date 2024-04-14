from scapy.all import IP, UDP, sr1

def send_udp_packet(ip, port, payload):
    udp_packet = IP(dst=ip) / UDP(dport=port) / payload
    udp_response = sr1(udp_packet, timeout=1)

    if udp_response:
        print(f"Received reply from {ip}:{port}: {udp_response.show()}")
    else:
        print(f"No reply from {ip}:{port}")

send_udp_packet('172.16.31.64', 53, 'Hello world')
