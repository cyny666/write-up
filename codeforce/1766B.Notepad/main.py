case_number = int(input())
for i in range(case_number):
    length = int(input())
    string = str(input())
    index = length - 2
    flag = 0
    if length <= 3:
        print("NO")
        continue
    while index != 0 :
        substr = string[index:index+2]
        index = index - 1
        place = string.find(substr,0,index+1)
        if place != -1:
            print("YES ")
            flag = 1
            break
    if flag == 0 :
        print("NO ")