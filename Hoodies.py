n = int(input())

course1, course2, course3, course4, order = [], [], [], [], []
isOne, isTwo, isThree, isFour = False, False, False, False
for i in range(0, n):
    s = input()

    if s[0] == 'E':
        if s[2] == '1':
            course1.append(s[4:])
            if not isOne:
                order.append('1')
                isOne = True
        elif s[2] == '2':
            course2.append(s[4:])
            if not isTwo:
                order.append('2')
                isTwo = True

        elif s[2] == '3':
            course3.append(s[4:])
            if not isThree:
                order.append('3')
                isThree = True
        elif s[2] == '4':
            course4.append(s[4:])
            if not isFour:
                order.append('4')
                isFour = True
    elif s[0] == 'D':
        ch = order.__getitem__(0)

        if ch == '1':
            if len(course1) != 0:
                print(ch + " " + course1.pop(0))

            if len(course1) == 0:
                order.pop(0)
                isOne = False
        elif ch == '2':
            if len(course2) != 0:
                print(ch + " " + course2.pop(0))

            if len(course2) == 0:
                order.pop(0)
                isTwo = False
        elif ch == '3':
            if len(course3) != 0:
                print(ch + " " + course3.pop(0))

            if len(course3) == 0:
                order.pop(0)
                isThree = False
        elif ch == '4':
            if len(course4) != 0:
                print(ch + " " + course4.pop(0))

            if len(course4) == 0:
                order.pop(0)
                isFour = False
