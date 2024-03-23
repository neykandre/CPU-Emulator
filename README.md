# CPU-Emulator
Algorithms C++ HW-2

## Usage

```sh
   ./emulatorCPU "flag" "file_path"
   ```
flags:
1. --mk_bin (-mb)

   make binary file from source file
2. --run_bin (-rb)

    execute binary made file
3. --run_file (-rf)

    execute file from source file

## Commands
| Command | Description |
| --- | --- |
| `begin` | The beginning of the *main* |
| `end` | The end of the *main* |
| `push value0` | Pushing a *value0* number to the top of the stack |
| `pop` | Removing a number from the top of the stack |
| `pushr reg0` | Pushing a number located on *reg0* to the top of the stack |
| `popr reg0` | Removing a number from the top of the stack and pushing this number to the *reg0* |
| `add` | Sum of the top two values from the stack is stored at the top of the stack. Operands are removed from the stack |
| `sub` | Difference of the top two values from the stack is stored at the top of the stack. Operands are removed from the stack |
| `mul` | Product of the top two values from the stack is stored at the top of the stack. Operands are removed from the stack |
| `div` | Quotient of the top two values from the stack is stored at the top of the stack. Operands are removed from the stack |
| `out` | Deleting a number from the top of the stack with output to the console |
| `in` | Reading a number from the console and saving it at the top of the stack |
| `jmp label` | Unconditional transition to the *label* |
| `jeq label` | Conditional transition to the *label* if the top two numbers on the stack are equal |
| `jne label` | Conditional transition to the *label* if the top two numbers on the stack are not equal |
| `ja label` | Conditional transition to the *label* if the top number on the stack is greater than the one following it |
| `jae label` | Conditional transition to the *label* if the top number on the stack is greater than or equal to the one following it |
| `jb label` | Conditional transition to the *label* if the top number on the stack is less than the one following it |
| `jbe label` | Conditional transition to the *label* if the top number on the stack is less than or equal to the one following it |
| `call label` | Calling a function whose body is located by the *label* |
| `ret` | Returns from the function with stack restoring |

## Registers
- eax
- ebx
- ecx
- edx

## Code example
recursive factorial
```asm
fac:
    push 1
    jae return
    pop

    popr eax
    pushr eax

    push 1
    pushr eax
    sub
    call fac
    mul
    jmp return
return:
    ret

begin
in
call fac
out
end
```
