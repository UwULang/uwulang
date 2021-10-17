import random

def main():
    code = input()
    OwO = [i for i in code]

    UwU = [0]
    ptr = 0
    length = 1

    # precomplie
    front_ptr = 0
    back_ptr = len(OwO) - 1
    if code.count('😒') != code.count('😡'):
        raise Exception("Invalid")
        return 

    jump_table = dict()
    # help from https://github.com/pocmo/Python-Brainfuck/blob/master/brainfuck.py
    temp_bracestack = []
    for index, item in enumerate(OwO):
        if item == '😒':
            temp_bracestack.append(index)
        elif item == '😡':
            start = temp_bracestack.pop()
            # doubly indexed jump table
            jump_table[start] = index
            jump_table[index] = start

    code_ptr = 0
    while code_ptr < len(OwO):
        item = OwO[code_ptr]
        if item == '\n': return
        elif item == '👆': UwU[ptr]+=1
        elif item == '👇': UwU[ptr]-=1
        elif item == '😳': 
            userInput = input()[0]
            UwU[ptr] = ord(userInput)
        elif item == '🥺': print(chr(UwU[ptr]), end='')
        elif item == '🥴': UwU[ptr] = random.randint(0, 128)
        elif item == '👈':
            if ptr == 0: continue
            else: ptr-=1
        elif item == '👉':
            if ptr < length - 1: ptr += 1
            else: 
                UwU.append(0)
                length += 1
                ptr += 1
        # if block start and current is 0, go to end 😡
        elif item == '😒' and UwU[ptr] == 0: code_ptr = jump_table[code_ptr]
        # if block end and current is not 0, go to start
        elif item == '😡' and UwU[ptr] != 0: code_ptr = jump_table[code_ptr]

        code_ptr+=1

    return

if __name__ == "__main__":
    main()
