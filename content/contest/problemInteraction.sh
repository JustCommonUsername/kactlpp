# ./problemInteraction.sh A [args]: run ./A against ./interactor [args]
# Exit code is the interactor's (0 = OK). To log what A sends, put
# "| tee log |" in place of the "|" below.
p=$1; shift
rm -f fifo; mkfifo fifo
./$p < fifo | ./interactor "$@" > fifo
# Stress: for i in $(seq 1000); do ./problemInteraction.sh A $i \
#   || { echo "failed on seed $i"; break; }; done
