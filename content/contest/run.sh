# ./run.sh A     compile A.cpp like the judge, test samples
# ./run.sh A d   debug: deb(...) on, sanitizers, no -O2
p=$1
if [ "$2" = d ]; then
  g++ -x c++ -std=gnu++23 -Wall -g -DLOCAL \
    -fsanitize=address,undefined -o $p $p.cpp || exit 1
else
  g++ -x c++ -std=gnu++23 -Wall -O2 -static -pipe \
    -o $p $p.cpp || exit 1
fi
ls $p*.in >/dev/null 2>&1 || { ./$p; exit; }  # no samples
for f in $p*.in; do
  echo "== $f"
  ./$p < $f > out.txt
  if diff -b out.txt ${f%.in}.ans >/dev/null; then
    echo OK
  else
    echo "WRONG, got:"; cat out.txt
  fi
done
