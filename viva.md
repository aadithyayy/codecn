# 🧠 Networking & Simulation Resources

A collection of essential networking and simulation study resources with quick topic summaries, references, and viva preparation.

---

## 1. 🧩 Networking Commands  
**Link:** [Networking Commands in Linux](https://itworkshopktu2024.blogspot.com/2024/11/networking-commands-in-linux.html)  

**Overview:**  
Networking commands in Linux are used to configure, monitor, and troubleshoot network connections. Key commands include:
- `ifconfig` / `ip` – configure network interfaces  
- `ping`, `traceroute` – test connectivity and path  
- `netstat`, `ss` – view active connections and ports  
- `nslookup`, `dig` – DNS lookups  
- `scp`, `ssh`, `ftp` – remote file transfer and access  

Understanding these helps diagnose network issues and verify configurations.

---

## 2. 🧮 Wireshark  
**Link:** [How to Use Wireshark](https://www.varonis.com/blog/how-to-use-wireshark)  

**Overview:**  
Wireshark is a network protocol analyzer that captures and inspects packets in real time. It helps visualize how data travels across a network, detect anomalies, and analyze protocols like TCP, UDP, HTTP, and ICMP. It’s widely used for:
- Packet capture and filtering  
- Performance analysis  
- Debugging network applications  
- Security auditing and intrusion detection  

---

## 3. 🌐 Cisco Packet Tracer  
**Links:**  
- [Beginner’s Guide to Routing (Medium)](https://medium.com/developer-student-clubs-tiet/beginners-guide-to-routing-in-cisco-packet-tracer-608f8a156d94)  
- [Video Tutorial](https://youtu.be/qZB_biPOBwA)  

**Overview:**  
Cisco Packet Tracer is a powerful network simulation tool used for designing, testing, and visualizing computer networks. It allows users to:
- Create virtual LANs, routers, and switches  
- Configure routing protocols (RIP, OSPF, etc.)  
- Test packet flow and connectivity  
- Learn networking concepts without real hardware  

It’s a go-to tool for students learning networking and preparing for CCNA-level labs.

---

## 4. 📘 Modules 1-4  
**Link:** [Module 1-4 Notes](https://drive.google.com/file/d/1QdZHzgB9FdApSe-HjQfE-KT9gX9bELKR/view?usp=sharing)  

**Overview:**  
These modules typically cover the **core of computer networking concepts**, including:  
- **Module 1:** Basics of data communication, network models (OSI, TCP/IP)  
- **Module 2:** Data link layer protocols and framing  
- **Module 3:** Network layer concepts, IP addressing, and routing algorithms  
- **Module 4:** Transport and application layers, TCP/UDP, and network services  

Together, they build the foundation for understanding how data travels through interconnected systems.

---

## 💻 TOP NETWORKING VIVA QUESTIONS (and Model Answers)

---

### 🧩 1. **How is a website displayed on your computer?**
**Answer:**  
When you type a website’s URL:  
1. The browser sends a **DNS request** to find the website’s **IP address**.  
2. The browser then **connects to the web server** using **TCP** (usually on port 80 or 443).  
3. An **HTTP/HTTPS request** is sent to the server.  
4. The server responds with **HTML, CSS, JS files**, which the browser renders to display the webpage.  
**Keywords:** DNS, TCP connection, HTTP request, rendering.

---

### 🌐 2. **What happens when you enter a URL in your browser?**
**Answer:**  
1. **DNS lookup** → Converts domain name to IP.  
2. **Browser establishes TCP connection** with server.  
3. Sends **HTTP/HTTPS request**.  
4. **Server responds** with web data.  
5. **Browser renders** content for display.

---

### 🧭 3. **What is the difference between IP address and MAC address?**
**Answer:**  
* **IP Address**: Logical address used for identifying devices across networks. Changes with network.  
* **MAC Address**: Physical address embedded in the NIC, unique for each device. Doesn’t change.  
**Example:** IP = your postal address; MAC = your fingerprint.

---

### ⚙️ 4. **What is the difference between a switch and a router?**
**Answer:**  
* **Switch** connects devices **within** a LAN using **MAC addresses** (Layer 2).  
* **Router** connects **different networks** using **IP addresses** (Layer 3).  
**Example:** Switch = local delivery inside a building; Router = courier to other cities.

---

### 📡 5. **What is the purpose of DNS?**
**Answer:**  
DNS (Domain Name System) **translates domain names** (like `www.google.com`) into **IP addresses** (like `142.250.190.14`) that computers use to communicate.

---

### 🧱 6. **What is the difference between TCP and UDP?**
| Feature     | TCP                             | UDP                  |
| ----------- | ------------------------------- | -------------------- |
| Type        | Connection-oriented             | Connectionless       |
| Reliability | Reliable (ACKs, retransmission) | Unreliable           |
| Speed       | Slower                          | Faster               |
| Example     | HTTP, FTP                       | DNS, Video streaming |

---

### 📦 7. **What is an IP packet?**
**Answer:**  
An **IP packet** is a unit of data that includes:  
* **Header:** Source & destination IPs, TTL, etc.  
* **Payload:** Actual data (like a TCP segment).

---

### 🧩 8. **What is ARP?**
**Answer:**  
ARP (Address Resolution Protocol) maps an **IP address to a MAC address** within a LAN.  
**Example:** When you want to send data to `192.168.1.10`, ARP finds its MAC address first.

---

### 🔀 9. **What is the difference between hub, bridge, and switch?**
| Device     | Layer | Function                                   |
| ---------- | ----- | ------------------------------------------ |
| **Hub**    | 1     | Broadcasts to all                          |
| **Bridge** | 2     | Filters traffic between LANs               |
| **Switch** | 2     | Sends to specific device using MAC address |

---

### 🛰️ 10. **What is the role of a router in a network?**
**Answer:**  
A router connects **different networks**, decides the **best path** for data, and forwards packets based on **IP addresses**.

---

### 🔐 11. **What is a gateway?**
**Answer:**  
A gateway is a device that **connects two networks using different protocols**. It performs **protocol translation** (e.g., between HTTP and FTP, or IPv4 and IPv6).

---

### 🧠 12. **What is a subnet mask and why is it used?**
**Answer:**  
A **subnet mask** divides an IP address into **network** and **host** portions.  
It helps identify which part of an IP address belongs to the **network** and which to the **device**.  
Example:  
`IP: 192.168.1.5`  
`Mask: 255.255.255.0` → Network: `192.168.1.0`

---

### 🌍 13. **What is the difference between IPv4 and IPv6?**
| Feature      | IPv4        | IPv6         |
| ------------ | ----------- | ------------ |
| Address Size | 32 bits     | 128 bits     |
| Example      | 192.168.0.1 | 2001:0db8::1 |
| Header Size  | Variable    | Fixed        |
| NAT Needed   | Yes         | No           |

---

### ⚡ 14. **What is a MAC address used for?**
**Answer:**  
It uniquely identifies a **device’s network interface** on a LAN for **frame delivery** at the Data Link Layer.

---

### 🔁 15. **What are protocols?**
**Answer:**  
Protocols are **rules and standards** that define how data is transmitted and received across a network.  
**Example:** TCP/IP, HTTP, FTP, DNS.

---

### 📡 16. **What is CSMA/CD and where is it used?**
**Answer:**  
CSMA/CD (Carrier Sense Multiple Access with Collision Detection) is used in **Ethernet LANs**.  
Nodes **listen** before transmitting and **stop** immediately if a collision is detected.

---

### 🧩 17. **What is the purpose of the OSI model?**
**Answer:**  
The OSI model divides networking functions into **7 layers**, helping in **standardization**, **troubleshooting**, and **protocol design**.  
**Mnemonic:**  
👉 *All People Seem To Need Data Processing*  
(Application → Presentation → Session → Transport → Network → Data Link → Physical)

---

### 🧾 18. **What is an IP address?**
**Answer:**  
An IP address is a **logical identifier** for a device on a network.  
Used for routing packets between source and destination.

---

### 🛰️ 19. **What are the 7 layers of the OSI model?**
| Layer           | Function                    | Example Protocol |
| --------------- | --------------------------- | ---------------- |
| 7. Application  | User interface              | HTTP, FTP        |
| 6. Presentation | Data translation/encryption | SSL, JPEG        |
| 5. Session      | Manages sessions            | NetBIOS          |
| 4. Transport    | End-to-end delivery         | TCP, UDP         |
| 3. Network      | Routing                     | IP               |
| 2. Data Link    | MAC, framing                | Ethernet         |
| 1. Physical     | Transmission                | Cables, Hubs     |

---

### 📬 20. **What is the difference between unicast, multicast, and broadcast?**
| Type          | Description                  | Example          |
| ------------- | ---------------------------- | ---------------- |
| **Unicast**   | One-to-one                   | Sending email    |
| **Multicast** | One-to-many (specific group) | Video conference |
| **Broadcast** | One-to-all                   | ARP Request      |

---

## 🎯 BONUS: How to Answer in a Viva
✅ **Be structured:**  
> “When we do X, first this happens, then that…”

✅ **Use examples:**  
> “For example, when you open Google.com…”

✅ **Keep it short and clear:**  
1–3 sentences maximum — your teacher wants clarity, not length.

✅ **Use keywords:**  
DNS, IP, MAC, TCP, packet, frame — they show technical understanding.
