import sys
import re
with open("gdb_output.txt", "r") as file:
    lines = file.readlines()
# Fill content with non-zero values
content = bytearray(0xaa for i in range(300))

pattern = r"\$[0-9]+ = {<text variable, no debug info>} (0x[0-9a-f]+)"

# Extract addresses
addresses = []
for line in lines:
    match = re.search(pattern, line)
    if match:
        addresses.append(int(match.group(1), 16))

# Map extracted addresses to their respective variables
if len(addresses) >= 3:
    system_addr = addresses[0]  # Address of system()
    exit_addr = addresses[1]    # Address of exit()
    execv_addr = addresses[2]   # Address of execv()
    
# Write the addresses to a file
    with open("addresses.txt", "a") as file:
        file.write(f"{hex(system_addr)}\n")
        file.write(f"{hex(exit_addr)}\n")
        file.write(f"{hex(execv_addr)}\n")
else:
    print("Error: Not enough addresses found in the GDB output.")