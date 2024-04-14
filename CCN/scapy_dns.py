from scapy.all import *

ip='8.8.8.8'
icmp_request = IP(dst=ip) / UDP(dport=53) / DNS(rd=1,qd=DNSQR(qname='www.google.com'))
icmp_response = sr1(icmp_request, verbose=0)

if icmp_response:
    print(f"Received reply from {ip}")
    print(icmp_response.show())
else:
    print(f"No reply from {ip}")

