# Stress test: runs good (brute force) and bad (your solution)
# on random tests from caseGen until the outputs differ.
# Compile all three first, then: python3 tester.py
import subprocess

def run(cmd, inp=None):
	return subprocess.run(cmd, input=inp, capture_output=True,
	                      text=True, shell=True).stdout

for t in range(1, 100001):
	inp = run(f"./caseGen {t}")
	a = run("./good", inp).split()
	if not a:
		print("good printed nothing: compiled? right name?")
		break
	b = run("./bad", inp).split()
	if a != b:
		print("FAILED on seed", t, "input:")
		print(inp)
		print("good:", *a)
		print("bad: ", *b)
		break
	if t % 100 == 0:
		print("ok", t)
