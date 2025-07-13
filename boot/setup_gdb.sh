#!/bin/bash
#qemu-system-arm -M lm3s6965evb -kernel bin/image.bin -gdb tcp::3333 -S -nographic
#arm-none-eabi-gdb int/image.elf -ex "target remote localhost:3333" \
                                -ex "x/10i $pc"
#!/bin/bash

SESSION="debug"

KERNEL="int/image.elf"
GDB="arm-none-eabi-gdb"
QEMU="qemu-system-arm"
QEMU_ARGS="-M lm3s6965evb -kernel bin/image.bin -gdb tcp::3333 -S -nographic"

tmux kill-session -t $SESSION 2>/dev/null

tmux new-session -d -s $SESSION -n debug

tmux send-keys -t $SESSION:1.0 "$QEMU $QEMU_ARGS" C-m

tmux split-window -h -t $SESSION:1

tmux send-keys -t $SESSION:1.1 "$GDB -ex 'target remote localhost:3333' -ex 'x/10i $pc' $KERNEL" C-m

tmux attach -t $SESSION
