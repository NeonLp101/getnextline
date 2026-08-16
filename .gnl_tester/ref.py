import sys
sep = "\n" if sys.argv[1] == "nl" else sys.argv[1]
data = open(sys.argv[2], "rb").read().decode("latin-1")
lines, cur = [], ""
for ch in data:
    cur += ch
    if ch == sep:
        lines.append(cur)
        cur = ""
if cur:
    lines.append(cur)
out = "".join(f"{len(l)}:{l}" for l in lines)
sys.stdout.buffer.write(out.encode("latin-1"))
