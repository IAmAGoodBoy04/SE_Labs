from scapy.all import *
from scapy.layers.http import HTTP, HTTPRequest
from scapy.layers.inet import IP, TCP

web_server = "www.youtube.com"

ip = IP(dst=web_server)

tcp = TCP(dport=80) 

http_get = "GET / HTTP/1.1\r\nHost: " + web_server + "\r\n\r\n"

packet = ip/tcp/http_get

response = sr1(packet)

if response is None:
    print("No response received.")
else:
    print("Response received:")
    response.show()
