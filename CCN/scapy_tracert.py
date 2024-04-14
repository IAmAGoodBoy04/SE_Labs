from scapy.all import *

def traceroute(dest_ip, max_hops=30):
    ttl = 1
    while True:
        packet = IP(dst=dest_ip, ttl=ttl) / UDP(dport=33434)
        reply = sr1(packet, verbose=0, timeout=2)
        if reply is None:
            print(f"{ttl}. no reply")
        elif reply.type == 3:
            print(f"{ttl}. {reply.src}")
            break
        else:
            print(f"{ttl}. {reply.src}")
        ttl += 1
        if ttl > max_hops:
            break

traceroute("8.8.8.8")