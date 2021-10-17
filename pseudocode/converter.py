'''
Doesn't actually work, use golang version 💩

'''

hashtable = {
    "+": "👆",
    "-": "👇",
    ">": "👉",
    "<": "👈",
    ".": "🥺",
    ",": "😳",
    "?": "🥴",
    "[": "😒",
    "]": "😡",
    '\n': '',
    '\0': '',
}

def convert(item):
    return hashtable[item]

def main():
    items = input()
    output = ''
    for item in items:
        output += hashtable[item]
    # print(''.join(list(map(convert, items))))

    print(output)
    # for item in items:
    #     print(item)
    return

if __name__ == "__main__":
    main()
