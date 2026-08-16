import sys, os, random
d, sep = sys.argv[1], ("\n" if sys.argv[2] == "nl" else sys.argv[2])
os.makedirs(d, exist_ok=True)
def w(name, s):
    open(os.path.join(d, name), "wb").write(s.encode("latin-1"))
w("empty",    "")
w("nosep",    "hello world, no separator at all")
w("onlysep",  sep)
w("seps5",    sep * 5)
w("one",      "a" + sep)
w("trail",    "first" + sep + "second" + sep + "third" + sep)
w("notrail",  "first" + sep + "second" + sep + "third")
w("bounds",   "x" * 41 + sep + "y" * 42 + sep + "z" * 43 + sep)
w("mixed",    "".join("x" * n + sep for n in range(0, 131)) + "tail without sep")
w("longline", "L" * 16384 + sep + "end" + sep)
random.seed(42)
alpha = "abcdefgh IJKL0123.,-"
w("big", "".join(
    "".join(random.choice(alpha) for _ in range(random.randint(0, 120))) + sep
    for _ in range(20000)))
