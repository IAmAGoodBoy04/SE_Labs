from scapy.all import *

def ping(ip):
    icmp_request = IP(dst=ip) / ICMP()
    icmp_response = sr1(icmp_request, timeout=1)

    if icmp_response:
        print(f"Received reply from {ip}")
        print(icmp_response.show())
    else:
        print(f"No reply from {ip}")


ping('142.250.183.174')
